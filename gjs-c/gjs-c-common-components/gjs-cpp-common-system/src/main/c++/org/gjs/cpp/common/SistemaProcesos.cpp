/***************************************************************************/
/*                         SistemaProcesos.cpp                             */
/*-------------------------------------------------------------------------*/
/* Librería: Sistema                                                       */
/* Versión:  1.1.0                                                         */
/* Fecha:    26/10/2006                                                    */
/* Autor:    Ginés Jiménez Sánchez                                         */
/*-------------------------------------------------------------------------*/
/* Descripción:                                                            */
/* Fichero de código fuente que contiene la implementación de las rutinas  */
/* de carácter general de información acerca de los procesos en ejecución, */
/* así como algunas rutinas de gestión de los mismos.                      */  
/*-------------------------------------------------------------------------*/
/* NOTA DEL AUTOR:                                                         */
/* Este módulo está extraído de una librería más completa creada por el    */
/* mismo autor. Por favor, el autor ruega que se le informe de cualquier   */
/* error detectado, así como cualquier añadido o modificación realizado.   */
/* Pueden reportar de los mismos enviando un correo electrónico a la       */
/* dirección: gines_jimenez@safe-mail.net. Gracias.                        */
/***************************************************************************/
#include "CommonSystemConfig.h"


#include "SistemaProcesos.h"

#include <map>
#include <mutex>
#include <chrono>
#include <sstream>
#include <system_error>
/* pthread_cancel y pthread_getschedparam: los dos compiladores usan el modelo
   de hilos posix, tambien el cruzado de MinGW-w64 sobre winpthreads. */
#include <pthread.h>
/* kill () y SIGTERM, para las funciones de subproceso en POSIX. errno, para
   distinguir 'no existe' de 'existe pero no es mio'. */
#include <csignal>
#include <cerrno>





#if ( defined ( UNIX ) || defined ( LINUX ) )
#	define _DISP_TMP_INFO_PROCESOS					"/dev/ps"
#endif

using namespace std;

namespace org
{
	namespace gjs
	{
		namespace cpp
		{
			namespace common
			{

# if ( ! defined ( WIN ) || ! defined ( _PSAPI_H_ ) )
string * _g_p_sSisNomProceso = NULL;
#endif


extern void MemLimpiar ( void * p_vBloque, int iNumBytes );


#if ( !defined ( WIN ) )
void SisProcInicializar ( const string & sNomProceso )
{
	if ( ES_VALIDO ( _g_p_sSisNomProceso ) )
	{
		delete _g_p_sSisNomProceso;
	}
	_g_p_sSisNomProceso = new string ( sNomProceso );
}

void SisProcFinalizar ()
{
	delete _g_p_sSisNomProceso;
	_g_p_sSisNomProceso = NULL;
}
#endif




long SisPID ()
{
	long lPID;

# if ( defined ( WIN ) )
	lPID = (long) GetCurrentProcessId ();
# else
	lPID = getpid ();
# endif
	return ( lPID );
}

string SisPIDCadena ()
{
	return ( ToString ( SisPID () ) );
}

# if ( !defined ( WIN ) )
/* Cierto si la cadena no esta vacia y es toda digitos. Se usa para quedarse con
   las entradas de /proc que son un PID, descartando las demas ( cpuinfo, self,
   registry... ). */
static bool _SisEsSoloDigitos ( const char * p_cNombre )
{
	bool		bRes;
	int			iPos;

	bRes = false;
	if ( ES_VALIDO ( p_cNombre ) )
	{
		iPos = 0;
		bRes = true;
		while ( ( p_cNombre [ iPos ] != '\0' ) && bRes )
		{
			if ( ( p_cNombre [ iPos ] < '0' ) || ( p_cNombre [ iPos ] > '9' ) )
			{
				bRes = false;
			}
			iPos = iPos + 1;
		}
		if ( iPos == 0 )
		{
			bRes = false;
		}
	}
	return ( bRes );
}

/******************************************************************************/
/* Lectura de /proc                                                           */
/*----------------------------------------------------------------------------*/
/* Linux y Cygwin tienen /proc con el mismo formato. Con una DIFERENCIA        */
/* IMPORTANTE en Cygwin: solo lista los procesos de Cygwin, no los del resto   */
/* de Windows ( medido: 6 frente a los cientos que hay en la maquina ). Por eso*/
/* las funciones que RECORREN /proc buscando otros procesos dan una respuesta  */
/* parcial en ese modo, y asi queda dicho en cada una. Las que preguntan por el*/
/* proceso actual, o por uno cuyo PID ya se tiene, van bien en los dos.        */
/******************************************************************************/

/* Numero de campo dentro de /proc/<pid>/stat contando el estado como el 1
   ( o sea, saltandose el pid y el nombre ). Ver _SisCampoStat. */
#define SIS_PROC_CAMPO_PPID			2
#define SIS_PROC_CAMPO_UTIME		12
#define SIS_PROC_CAMPO_STIME		13

/* Que parte del tiempo de CPU se quiere. */
#define SIS_CPU_COMPLETO				0
#define SIS_CPU_NUCLEO				1
#define SIS_CPU_USUARIO				2


/* Contenido de /proc/<pid>/<que>, o cadena vacia si no se pudo leer. */
static string _SisLeerDeProc ( long lPID, const string & sQue )
{
	string			sRes;
	ostringstream	ossRuta;

	ossRuta << "/proc/" << lPID << "/" << sQue;
	ifstream ficDato ( ossRuta.str () );
	if ( ficDato.is_open () )
	{
		getline ( ficDato, sRes );
	}
	return ( sRes );
}

/* Devuelve el campo numero iCampo de /proc/<pid>/stat contando DESDE EL ESTADO,
   que es el 1. Hay que empezar a contar ahi porque el campo anterior es el
   nombre del ejecutable, va entre parentesis y puede llevar espacios y hasta
   parentesis dentro; contar desde el principio de la linea no vale. Por eso se
   busca el ULTIMO parentesis de cierre. Devuelve 0 si no lo encuentra. */
static unsigned long _SisCampoStat ( const string & sStat, int iCampo )
{
	unsigned long	ulRes = 0;
	size_t			uCierre = sStat.rfind ( ')' );

	if ( uCierre != string::npos )
	{
		istringstream	issCampos ( sStat.substr ( uCierre + 1 ) );
		string			sCampo;
		int				iActual = 0;

		while ( issCampos >> sCampo )
		{
			iActual = iActual + 1;
			if ( iActual == iCampo )
			{
				try
				{
					ulRes = stoul ( sCampo );
				}
				catch ( ... )
				{
					ulRes = 0;
				}
				break;
			}
		}
	}
	return ( ulRes );
}

/* PID del padre de un proceso, o 0 si no se pudo averiguar. */
static long _SisPPIDDeProceso ( long lPID )
{
	long	lRes = 0;
	string	sStat = _SisLeerDeProc ( lPID, "stat" );

	if ( ! sStat.empty () )
	{
		lRes = ( long ) _SisCampoStat ( sStat, SIS_PROC_CAMPO_PPID );
	}
	return ( lRes );
}

/* Nombre del fichero ejecutable de un proceso, sin la ruta, leyendo el enlace
   /proc/<pid>/exe. Cadena vacia si no se pudo. */
static string _SisNombreEjecutableDeProceso ( long lPID )
{
	string			sRes;
	ostringstream	ossRuta;
	vector<char>	vecDestino ( MAXPATHLEN );

	ossRuta << "/proc/" << lPID << "/exe";
	ssize_t sLongitud = readlink ( ossRuta.str ().c_str (), vecDestino.data (),
								   vecDestino.size () - 1 );
	if ( sLongitud > 0 )
	{
		vecDestino [ sLongitud ] = '\0';
		sRes = SisRutaFichero ( string ( vecDestino.data () ) );
	}
	return ( sRes );
}

/* Tiempo de CPU de un proceso, en MILISEGUNDOS, que es lo que devuelve la rama
   de Windows. */
static unsigned long _SisTiempoCPUDeProceso ( long lPID, int iModo )
{
	unsigned long	ulRes = 0;
	string			sStat = _SisLeerDeProc ( lPID, "stat" );

	if ( ! sStat.empty () )
	{
		unsigned long ulTics = 0;

		if ( iModo != SIS_CPU_NUCLEO )
		{
			ulTics = ulTics + _SisCampoStat ( sStat, SIS_PROC_CAMPO_UTIME );
		}
		if ( iModo != SIS_CPU_USUARIO )
		{
			ulTics = ulTics + _SisCampoStat ( sStat, SIS_PROC_CAMPO_STIME );
		}
		/* Los campos vienen en tics de reloj. Cuantos hay por segundo lo dice el
		   sistema y NO se puede dar por sabido: son 100 en Linux y 1000 en
		   Cygwin ( medido el 2026-09-18 ). */
		long lTicsPorSegundo = sysconf ( _SC_CLK_TCK );
		if ( lTicsPorSegundo > 0 )
		{
			ulRes = ( ulTics * 1000UL ) / ( unsigned long ) lTicsPorSegundo;
		}
	}
	return ( ulRes );
}

/* Recorre /proc. Si bContar es cierto cuenta los procesos cuyo padre es lPadre
   y devuelve la cuenta; si no, busca uno cuyo ejecutable se llame como se pide
   y devuelve su PID, o -1. */
static long _SisRecorrerProcesos ( const string & sEjecutable, long lPadre, bool bContar )
{
	long	lRes = bContar ? 0 : -1;
	DIR *	p_dirProc = opendir ( "/proc" );

	if ( ES_VALIDO ( p_dirProc ) )
	{
		struct dirent * p_entDato = readdir ( p_dirProc );

		while ( ES_VALIDO ( p_entDato ) )
		{
			if ( _SisEsSoloDigitos ( p_entDato->d_name ) )
			{
				long lPID = strtol ( p_entDato->d_name, NULL, 10 );

				if ( bContar )
				{
					if ( _SisPPIDDeProceso ( lPID ) == lPadre )
					{
						lRes = lRes + 1;
					}
				}
				else if ( lRes < 0 )
				{
					if ( _SisNombreEjecutableDeProceso ( lPID ) == sEjecutable )
					{
						lRes = lPID;
					}
				}
			}
			p_entDato = readdir ( p_dirProc );
		}
		closedir ( p_dirProc );
	}
	return ( lRes );
}

# endif


string SisNombreProceso ()
{
	string		sRes = "";
# if ( ( defined ( WIN ) ) && ( defined ( _PSAPI_H_ ) ) )
	HANDLE		hProceso;
	HMODULE		hModulo;
    DWORD		dwTam;
//# elif ( defined ( LINUX ) )
//	struct task_struct * p_tskProceso;
# endif

# if ( ( defined ( WIN ) ) && ( defined ( _PSAPI_H_ ) ) )
 	vector<char> buffer ( MAXPATHLEN );
	hProceso = OpenProcess ( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, GetCurrentProcessId () );
	if ( hProceso != NULL )
	{
		if ( EnumProcessModules ( hProceso, &hModulo, sizeof ( hModulo ), &dwTam ) != 0 )
		{
			if ( GetModuleBaseName ( hProceso, hModulo, ( LPSTR ) buffer.data (), ( ( DWORD ) buffer.size () ) / sizeof ( char ) ) > 0 )
			{
				sRes = string ( buffer.data () );
			}
		}
		CloseHandle ( hProceso );
	}
# else
	/* Si alguien fijo el nombre a mano con el setter, manda ese. Si no, se saca
	   del sistema, que era justo lo que faltaba: SisRutaEjecutable ya
	   resuelve /proc/self/exe, y de ahi el nombre del fichero, que es lo que
	   devuelve GetModuleBaseName en la rama de Windows. */
	if ( ES_VALIDO ( _g_p_sSisNomProceso ) )
	{
		sRes = *_g_p_sSisNomProceso;
	}
	else
	{
		sRes = SisRutaFichero ( SisRutaEjecutable () );
	}
# endif
	return ( sRes );
}

string SisRutaEjecutable ()
{
	string	sRes = "";
	vector<char> buffer ( MAXPATHLEN );
# if ( ( defined ( WIN ) ) && ( defined ( _PSAPI_H_ ) ) )
	HANDLE		hProceso;
	int			iTam;
# else
	string	sDir;
#  if ( !defined ( GNU ) )
#  endif
# endif

# if ( ( defined ( WIN ) ) && ( defined ( _PSAPI_H_ ) ) )
	hProceso = OpenProcess ( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, GetCurrentProcessId () );
	if ( hProceso != NULL )
	{
		iTam = (int) GetModuleFileNameEx ( hProceso, NULL, (LPTSTR) buffer.data (), (DWORD) buffer.size () );
		if ( iTam > 0 )
		{
			sRes = string ( buffer.data() );
		}
		CloseHandle ( hProceso );
	}
# elif ( defined ( GNU ) )
	// En Linux/Cygwin la via fiable es el enlace simbolico /proc/self/exe.
	{
		ssize_t iLong = readlink ( "/proc/self/exe", buffer.data (), buffer.size () - 1 );
		if ( iLong > 0 )
		{
			buffer [ (size_t) iLong ] = '\0';
			sRes = string ( buffer.data () );
		}
	}
	// Reserva: componer la ruta con el nombre del proceso, SOLO si esta definido
	// ( evita desreferenciar un puntero nulo cuando no se ha llamado a SisInicializar ).
	if ( sRes.empty () && ES_VALIDO ( _g_p_sSisNomProceso ) )
	{
		if ( SisEsRutaValida ( *_g_p_sSisNomProceso ) == 1 )
		{
			sRes = string ( *_g_p_sSisNomProceso );
		}
		else
		{
			if ( getcwd ( buffer.data (), buffer.size () ) != NULL )
			{
				sDir = string ( buffer.data () );
			}
			sRes = SisComponerRuta ( sDir, *_g_p_sSisNomProceso );
		}
	}
# else
	if ( getcwd ( (string) buffer.data (), (size_t) buffer.size() () ) != NULL )
	{
		sDir = string ( buffer.data() );
		if ( ES_VALIDO ( sDir ) )
		{
			sRes = SisComponerRuta ( sDir, *_g_p_sSisNomProceso );
		}
	}
# endif
	return ( sRes );
}

string SisDirectorioEjecutable ()
{
	string sRes;

	string sRuta = SisRutaEjecutable ();
	sRes = SisRutaDirectorio ( sRuta );
	return ( sRes );
}

string SisFicheroEjecutable ()
{
	string sRes;

	string sRuta = SisRutaEjecutable ();
	sRes = SisRutaFichero ( sRuta );
	return ( sRes );
}

/* Solo en Windows. El titulo es un dato DEL PROCESO: se lo pasa quien lo
   arranca y se lee con GetStartupInfo. En POSIX no existe tal cosa; lo mas
   parecido es el titulo de la ventana del terminal, que no es del proceso
   sino del emulador, se pone mandandole una secuencia de escape y NO se
   puede leer de vuelta. Devolver otra cosa seria mentir, asi que la funcion
   simplemente no se declara fuera de Windows. */
#if ( defined ( WIN ) )
string SisTituloProceso ()
{
	string sRes = "";
	STARTUPINFO		stupinfDatos;

	GetStartupInfo ( &stupinfDatos );
	if ( ES_VALIDO ( stupinfDatos.lpTitle ) )
	{
		sRes = string ( stupinfDatos.lpTitle );
	}
	return ( sRes );
}

HINSTANCE SisWinIdProceso ()
{
	return ( GetModuleHandle ( NULL ) );
}

#endif

/*
int SisProcesoEsDeGUI ()
{
	int iRes;

# if ( defined ( WIN ) )
	STARTUPINFO		stupinfDatos;

	GetStartupInfo ( &stupinfDatos );
	if ( stupinfDatos.dwFlags & STARTF_USESHOWWINDOW != 0 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
# else
	// PENDIENTE:
	iRes = 0;
# endif
	return ( bRes );
}

int SisProcesoEsDeConsola ()
{
	int iRes;

# if ( defined ( WIN ) )
	STARTUPINFO		stupinfDatos;

	GetStartupInfo ( &stupinfDatos );
	if ( stupinfDatos.dwFlags & STARTF_USESHOWWINDOW != 0 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
# else
	// PENDIENTE:
	iRes = 0;
# endif
	return ( bRes );
}
*/

std::thread::id SisTID ()
{
	return ( std::this_thread::get_id() );
}

string SisTIDCadena ()
{
	/* ToString no tiene sobrecarga para thread::id, que solo sabe volcarse a
	   un flujo. */
	std::ostringstream ossRes;
	ossRes << SisTID ();
	return ( ossRes.str () );
}

int SisNumSubprocesos ()
{
	int			iRes;
# if ( defined ( WIN ) )
	HANDLE				hSnapshot;
	PROCESSENTRY32		pe32Datos;
	int					iFinal;
	DWORD				dwYo;

	/* Cuenta los procesos HIJOS de este, que es lo que dice la cabecera al
	   agrupar esta funcion bajo "Subprocesos" y lo que la distingue de
	   SisNumProcesos. Antes contaba todos los procesos de la maquina que se
	   pudieran abrir, que no es ni una cosa ni la otra. */
	dwYo = GetCurrentProcessId ();
	hSnapshot = CreateToolhelp32Snapshot ( TH32CS_SNAPPROCESS, 0 );
	if ( hSnapshot != INVALID_HANDLE_VALUE )
	{
		pe32Datos.dwSize = sizeof ( PROCESSENTRY32 );
		if ( Process32First ( hSnapshot, &pe32Datos ) != 0 )
		{
			iFinal = 0;
			iRes = 0;
			while ( iFinal == 0 )
			{
				if ( pe32Datos.th32ParentProcessID == dwYo )
				{
					iRes = iRes + 1;
				}
				if ( Process32Next ( hSnapshot, &pe32Datos ) == 0 )
				{
					iFinal = 1;
				}
			}
		}
		else
		{
			iRes = 0;
		}
		CloseHandle ( hSnapshot );
	}
	else
	{
		iRes = 0;
	}
# else
	/* Recorriendo /proc y mirando el padre de cada uno. LIMITACION EN CYGWIN:
	   /proc solo lista procesos de Cygwin, asi que un hijo lanzado que no lo
	   sea no se cuenta. En Linux la cuenta es completa. */
	iRes = ( int ) _SisRecorrerProcesos ( "", ( long ) getpid (), true );
# endif
	return ( iRes );
}

long SisCrearSubproceso ( const string & sEjecutable, const string & sParametros, int iHeredarDescriptores, int iCerrarConsola )
{
	long lPID = -1;

# if ( defined ( WIN ) )
	PROCESS_INFORMATION prcinfDatos;
	STARTUPINFO			stupintDatos;
	BOOL				bHeredar;
	DWORD				dwFlags;
	string				sComando;
	int					iTam;
# else
	pid_t				pidRes;
	int					iUltDescrip;
	int					iDescrip;
#  if ( defined ( GNU ) )
	string			sArg;
#  endif
#endif

# if ( defined ( WIN ) )
	if ( ! sEjecutable.empty () )
	{
		// Set up the start up info struct.
		MemLimpiar ( (void *) &stupintDatos, (int) sizeof ( STARTUPINFO ) );
		stupintDatos.cb = sizeof ( STARTUPINFO );
		dwFlags = NORMAL_PRIORITY_CLASS;
		if ( iHeredarDescriptores == 1 )
		{
			bHeredar = TRUE;
		}
		else
		{
			bHeredar = FALSE;
			dwFlags = dwFlags + DETACHED_PROCESS;
		}
		iTam = sEjecutable.length();
		if ( ! sParametros.empty () )
		{
			iTam = iTam + sParametros.length () + 1;
		}

		sComando = sEjecutable;
		if ( ! sParametros.empty () )
		{
			sComando = format ( "{} {}", sComando, sParametros );
		}

		if ( CreateProcess ( sEjecutable.c_str(), (LPSTR) sComando.c_str(), NULL, NULL, bHeredar, dwFlags, NULL, NULL, &stupintDatos, &prcinfDatos ) != 0 )
		{
			lPID = (long) prcinfDatos.dwProcessId;
		}
	}	
# else
	pidRes = fork ();
	if ( pidRes > 0 )
	{
		// Padre: Retorna el PID del subproceso:
		lPID = (long) pidRes;
	}
	else if ( pidRes == 0 )
	{
		// Hijo: Retorna 0 o ejecuta el ejecutable:
		if ( iHeredarDescriptores == 0 )
		{
			iUltDescrip = dup ( 0 );
			for ( iDescrip = 3; iDescrip <= iUltDescrip; iDescrip = iDescrip + 1 )
			{
				close ( iDescrip  );
			}
			if ( iCerrarConsola == 1 )
			{
				close ( 0 );
				close ( 1 );
				close ( 2 );
			}
		}

		if ( ! sParametros.empty () )
		{
			/* Portado del stack C, que ya armaba el argv a mano con CadPalabraExt y
			   MemReservar. Aqui sale mas corto: Separar da los trozos y el vector se
			   encarga de la memoria. execv quiere un array terminado en NULL cuyo
			   primer elemento es el propio ejecutable.

			   Se hace igual con GNU y sin el: la version C tenia dos ramas porque una
			   estaba a medias, no porque hicieran falta. */
			vector < string > vecArgs = Separar ( sParametros, { " " } );
			vector < char * > vecArgv;

			vecArgv.push_back ( const_cast < char * > ( sEjecutable.c_str () ) );
			for ( string & sArg : vecArgs )
			{
				if ( ! sArg.empty () )
				{
					vecArgv.push_back ( const_cast < char * > ( sArg.c_str () ) );
				}
			}
			vecArgv.push_back ( NULL );

			if ( execv ( sEjecutable.c_str (), vecArgv.data () ) < 0 )
			{
				/* Solo se llega aqui si execv falla: si va bien no vuelve. */
				exit ( -1 );
			}
		}
		else
		{
			if ( execl ( sEjecutable.c_str(), sEjecutable.c_str(), NULL) < 0 )
			{
				exit ( -1 );
			}
		}
	}
#endif
	return ( lPID );
}

/* Cierto si lPIDHijo es hijo de lPIDPadre.

   En Windows hay que recorrerse la foto de procesos de Toolhelp, que es la unica
   que trae el PID del padre. En POSIX lo dice el campo 4 de /proc/<pid>/stat, que
   es lo que ya lee _SisPPIDDeProceso.

   OJO en Cygwin: /proc solo lista procesos de Cygwin ( no los nativos de
   Windows ), asi que un hijo lanzado fuera de Cygwin no aparece y esto contesta
   que no lo es. Es la misma limitacion que arrastran SisProgramaEnEjecucion y
   SisProcesoPID. */
static bool _SisEsSubproceso ( long lPIDPadre, long lPIDHijo )
{
    bool bRes = false;

# if ( !defined ( WIN ) )
    bRes = ( _SisPPIDDeProceso ( lPIDHijo ) == lPIDPadre );
# else
    HANDLE hSnapshot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
    if ( ES_MANEJADOR_VALIDO ( hSnapshot ) )
	{
		PROCESSENTRY32 pe;
		pe.dwSize = sizeof(PROCESSENTRY32);

		if ( Process32First( hSnapshot, &pe )  ) 
		{
			do 
			{
				if ( pe.th32ProcessID == (DWORD) lPIDHijo )
				{
					if ( pe.th32ParentProcessID == (DWORD) lPIDPadre )
					{
						bRes = true;
					}
					break; 
				}
			} 
			while ( Process32Next( hSnapshot, &pe ) );
		}
		CloseHandle(hSnapshot);
	}
# endif
    return ( bRes );
}


bool SisExisteSubproceso ( long lPID )
{
	bool bRes = false;

# if ( defined ( WIN ) )
	/* Sin OpenProcess previo: la foto de Toolhelp que mira _SisEsSubproceso ya
	   contesta las dos cosas —si el PID existe y quien es su padre—, asi que
	   abrirlo antes no anadia nada. Y si quitaba: pedir PROCESS_ALL_ACCESS falla
	   contra un proceso elevado o protegido, y entonces esto contestaba "no
	   existe" sobre un hijo que si existia. */
	bRes = _SisEsSubproceso ( SisPID (), lPID );
# else
	/* kill con la senal 0 no manda nada: solo comprueba que el proceso existe y
	   que se le podria senalar. Si falla con EPERM el proceso existe, lo que pasa
	   es que es de otro usuario, y a efectos de 'existe' cuenta igual.

	   Antes esta rama no tocaba bRes, asi que en POSIX contestaba siempre que no:
	   y SisFinalizarSubproceso, que esta guardada por su resultado, no llegaba a
	   intentar nada. */
	if ( kill ( (pid_t) lPID, 0 ) == 0 )
	{
		bRes = true;
	}
	else
	{
		bRes = ( errno == EPERM );
	}
# endif
	return ( bRes );
}

bool SisFinalizarSubproceso ( long lPID )
{
	bool bRes = false;

	if ( SisExisteSubproceso ( lPID ) )
	{
# if ( defined ( WIN ) )
		HANDLE hProceso;
		
		hProceso = OpenProcess ( PROCESS_ALL_ACCESS, FALSE, (DWORD) lPID );
		if ( hProceso != NULL )
		{
			bRes = ( TerminateProcess ( hProceso, 0 ) != 0 );
			CloseHandle ( hProceso );
		}
# else
		/* SIGTERM es el equivalente de lo que hace TerminateProcess arriba: pedir
		   al proceso que termine. Si la ignora no hay mas que hacer desde aqui;
		   matarla a la fuerza seria SIGKILL, y eso es otra decision. */
		bRes = ( kill ( (pid_t) lPID, SIGTERM ) == 0 );
# endif
	}
	return ( bRes );
}

/* ---------------------------------------------------------------------------
   Hilos.

   std::thread::id es un identificador opaco a proposito: no se construye a
   partir de nada, no convierte a entero, y el estandar no ofrece ninguna
   operacion que actue sobre un hilo teniendo solo su id. Por eso el modulo
   lleva su propio registro de los hilos que ha creado: es lo unico que permite
   recuperar el native_handle () y, con el, hacer lo que el estandar no cubre.

   Los dos compiladores que se usan ( el de Cygwin y el cruzado de MinGW-w64 )
   declaran "Thread model: posix", asi que native_handle () es un pthread_t en
   las dos plataformas y la implementacion es la misma. De ahi que aqui no haya
   ni una rama #if de plataforma.
   --------------------------------------------------------------------------- */

static std::map < std::thread::id, std::thread >	_mapHilos;
static std::mutex									_mtxHilos;

/* Da de baja el hilo. Hay que soltarlo antes de borrarlo: destruir un
   std::thread todavia unible llama a terminate (). */
static void _OlvidarHilo ( std::thread::id thTID )
{
	std::lock_guard < std::mutex > lckGuarda ( _mtxHilos );
	auto itHilo = _mapHilos.find ( thTID );
	if ( itHilo != _mapHilos.end () )
	{
		if ( itHilo->second.joinable () )
		{
			itHilo->second.detach ();
		}
		_mapHilos.erase ( itHilo );
	}
}

/* Envoltura del codigo del usuario, para darse de baja al terminar. El mutex
   evita la carrera del hilo tan corto que acaba antes de que SisCrearHilo lo
   haya llegado a registrar: la baja no puede adelantarse al alta. */
static void _EjecutarHilo ( PTR_FUNCION_HILO p_funCodigo, void * p_vParam )
{
	p_funCodigo ( p_vParam );
	_OlvidarHilo ( std::this_thread::get_id () );
}

int SisNumHilos ()
{
	std::lock_guard < std::mutex > lckGuarda ( _mtxHilos );
	return ( (int) _mapHilos.size () );
}

std::thread::id SisCrearHilo ( PTR_FUNCION_HILO p_funCodigo, void * p_vParam )
{
	std::thread::id thHilo;

	if ( ES_VALIDO ( p_funCodigo ) )
	{
		try
		{
			std::lock_guard < std::mutex > lckGuarda ( _mtxHilos );
			std::thread thNuevo ( _EjecutarHilo, p_funCodigo, p_vParam );
			thHilo = thNuevo.get_id ();
			_mapHilos.emplace ( thHilo, std::move ( thNuevo ) );
		}
		catch ( const std::system_error & )
		{
			/* No se pudo lanzar: se devuelve el id vacio. */
			thHilo = std::thread::id ();
		}
	}
	return ( thHilo );
}

bool SisExisteHilo ( std::thread::id thTID )
{
	std::lock_guard < std::mutex > lckGuarda ( _mtxHilos );
	return ( _mapHilos.find ( thTID ) != _mapHilos.end () );
}

/* Suspender y reanudar no tienen forma portable: POSIX nunca tuvo equivalente
   de SuspendThread, y en Windows tampoco se alcanza, porque con el modelo de
   hilos posix native_handle () da un pthread_t y no un HANDLE de Win32 ( el
   puente pthread_getw32threadhandle_np no esta en este winpthreads ). Se
   devuelve false en lugar de fingir que funciona. */
bool SisSuspenderHilo ( std::thread::id thTID )
{
	( void ) thTID;
	return ( false );
}

bool SisReanudarHilo ( std::thread::id thTID )
{
	( void ) thTID;
	return ( false );
}

/* Cancela el hilo. Solo surte efecto cuando el hilo alcanza un punto de
   cancelacion ( sleep, read, wait... ); un hilo en un bucle de calculo puro
   puede no enterarse nunca. Al cancelarse no pasa por _EjecutarHilo, asi que
   la baja del registro se hace aqui. */
bool SisFinalizarHilo ( std::thread::id thTID )
{
	bool bRes = false;

	std::lock_guard < std::mutex > lckGuarda ( _mtxHilos );
	auto itHilo = _mapHilos.find ( thTID );
	if ( itHilo != _mapHilos.end () )
	{
		bRes = ( pthread_cancel ( itHilo->second.native_handle () ) == 0 );
		if ( itHilo->second.joinable () )
		{
			itHilo->second.detach ();
		}
		_mapHilos.erase ( itHilo );
	}
	return ( bRes );
}

bool SisCambiarASiguienteHilo ()
{
	std::this_thread::yield ();
	return ( true );
}

int SisHiloPrioridad ( std::thread::id thTID )
{
	int					iRes = 0;
	int					iPolitica;
	struct sched_param	schpDatos;

	std::lock_guard < std::mutex > lckGuarda ( _mtxHilos );
	auto itHilo = _mapHilos.find ( thTID );
	if ( itHilo != _mapHilos.end () )
	{
		if ( pthread_getschedparam ( itHilo->second.native_handle (), &iPolitica, &schpDatos ) == 0 )
		{
			iRes = schpDatos.sched_priority;
		}
	}
	return ( iRes );
}



int SisNumProcesos ()
{
	int			iRes = 0;
# if ( defined ( WIN ) )
#  if ( defined ( _EnumProcesses ) )
	DWORD		dwTamOcupado;
	int			iNumProcesos;
    int			iProceso;
	DWORD *		p_dwProcesos;

 	vector<unsigned char> buffer ( SIS_SO_MAX_TAM_BUFFER );
	p_dwProcesos = (DWORD *) buffer.data();
	// PENDIENTE: Puede ser que sea necesario más tamaño (comprobar caso SBufTam ( p_bufDatos )== dwTamOcupado):
	if ( EnumProcesses ( p_dwProcesos, (DWORD) buffer.size(), &dwTamOcupado) != 0 )
	{
		iNumProcesos = dwTamOcupado / sizeof ( DWORD );
		iProceso = 0;
		iRes = 0;
		while ( iProceso < iNumProcesos ) 
		{
			if ( p_dwProcesos [ iProceso ] != 0 )
			{
				iRes = iRes + 1;
			}
			iProceso = iProceso + 1;
		}
	}
#  else
	HANDLE				hSnapshot;
	PROCESSENTRY32		pe32Datos;
	int					iFinal;

	hSnapshot = CreateToolhelp32Snapshot ( TH32CS_SNAPPROCESS, 0 );
	if ( hSnapshot != INVALID_HANDLE_VALUE )
	{
		pe32Datos.dwSize = sizeof ( PROCESSENTRY32 );
		if ( Process32First ( hSnapshot, &pe32Datos ) != 0 )
		{
			iFinal = 0;
			iRes = 0;
			while ( iFinal == 0 )
			{
				iRes = iRes + 1;
				if ( Process32Next ( hSnapshot, &pe32Datos ) == 0 )
				{
					iFinal = 1;
				}
			}
		}
		CloseHandle ( hSnapshot );
	}
#  endif
# else
	/* Mismo recorrido de /proc que SisListaProcesos, contando en vez de
	   guardando. La misma LIMITACION EN CYGWIN: solo cuenta procesos Cygwin. */
	DIR *			p_dirProc;
	struct dirent *	p_entDato;

	p_dirProc = opendir ( "/proc" );
	if ( ES_VALIDO ( p_dirProc ) )
	{
		p_entDato = readdir ( p_dirProc );
		while ( ES_VALIDO ( p_entDato ) )
		{
			if ( _SisEsSoloDigitos ( p_entDato->d_name ) )
			{
				iRes = iRes + 1;
			}
			p_entDato = readdir ( p_dirProc );
		}
		closedir ( p_dirProc );
	}
# endif
	return ( iRes );
}

list<long> * SisListaProcesos ()
{
	list<long> * p_lislPID = NULL;
# if ( defined ( WIN ) )
	int						iError;
#  if ( defined ( _EnumProcesses ) )
	vector<unsigned char>   buffer = vector<unsigned char> ( SIS_SO_MAX_TAM_BUFFER );
	DWORD					dwTamOcupado;
	int						iNumProcesos;
    int						iProceso;
	DWORD *					p_dwProcesos;
#  else
	HANDLE					hSnapshot;
	PROCESSENTRY32			pe32Datos;
	int						iFinal;
#  endif
# endif

# if ( defined ( WIN ) )
#  if ( defined ( _EnumProcesses ) )
	p_dwProcesos = (DWORD *) buffer.data();
	// PENDIENTE: Puede ser que sea necesario más tamaño (comprobar caso SBufTam ( p_bufDatos )== dwTamOcupado):
	if ( EnumProcesses( p_dwProcesos, (DWORD) buffer.size(), &dwTamOcupado) != 0 )
	{
		iNumProcesos = dwTamOcupado / sizeof ( DWORD );
		iProceso = 0;
		iError = 0;
		p_lislPID = new list<long> ();
		while ( ( iProceso < iNumProcesos ) && ( iError == 0 ) )
		{
			if ( p_dwProcesos [ iProceso ] != 0 )
			{
				p_lislPID->push_back ( ( long ) p_dwProcesos [iProceso] );
			}
			iProceso = iProceso + 1;
		}
	}
#  else
	hSnapshot = CreateToolhelp32Snapshot ( TH32CS_SNAPPROCESS, 0 );
	if ( hSnapshot != INVALID_HANDLE_VALUE )
	{
		p_lislPID = new list<long> ();
		pe32Datos.dwSize = sizeof ( PROCESSENTRY32 );
		if ( Process32First ( hSnapshot, &pe32Datos ) != 0 )
		{
			iError = 0;
			iFinal = 0;
			// Process32First ya ha dejado el primer proceso en pe32Datos: se
			// mete y solo despues se pide el siguiente. Al reves se perdia uno.
			while ( ( iFinal == 0 ) && ( iError == 0 ) )
			{
				p_lislPID->push_back ( ( long ) pe32Datos.th32ProcessID );
				if ( Process32Next ( hSnapshot, &pe32Datos ) == 0 )
				{
					iFinal = 1;
				}
			}
		}
		else
		{
			p_lislPID = NULL;
		}
		CloseHandle ( hSnapshot );
	}
	else
	{
		p_lislPID = NULL;
	}

#  endif
# else
	/* En POSIX la lista de procesos se saca recorriendo /proc: cada
	   subdirectorio cuyo nombre es todo digitos es un PID.

	   LIMITACION EN CYGWIN: el /proc de Cygwin solo lista los procesos Cygwin,
	   no los del sistema, asi que bajo Cygwin esta funcion devuelve un punado
	   de PID. Windows nativo toma la rama de arriba, que si los ve todos, y en
	   Linux nativo /proc si da la lista completa. */
	DIR *			p_dirProc;
	struct dirent *	p_entDato;

	p_dirProc = opendir ( "/proc" );
	if ( ES_VALIDO ( p_dirProc ) )
	{
		p_lislPID = new list<long> ();
		p_entDato = readdir ( p_dirProc );
		while ( ES_VALIDO ( p_entDato ) )
		{
			if ( _SisEsSoloDigitos ( p_entDato->d_name ) )
			{
				p_lislPID->push_back ( atol ( p_entDato->d_name ) );
			}
			p_entDato = readdir ( p_dirProc );
		}
		closedir ( p_dirProc );
	}
	else
	{
		p_lislPID = NULL;
	}
# endif
	return ( p_lislPID );
}

bool SisExisteProceso ( long lPID )
{
	bool bRes = false;

# if ( defined ( WIN ) )
	HANDLE hProceso;
	// Se supone que sobre los subprocesos se tiene acceso total:
	hProceso = OpenProcess ( PROCESS_ALL_ACCESS, FALSE, (DWORD) lPID );
	if ( hProceso != NULL )
	{
		bRes = true;
		CloseHandle ( hProceso );
	}
# else
	/* Lo mismo que hace SisExisteSubproceso: kill con la senal 0 no manda nada,
	   solo comprueba. Y si falla con EPERM el proceso esta, lo que pasa es que
	   es de otro usuario; a efectos de "existe" cuenta igual.
	   Esta via NO depende de /proc, asi que en Cygwin tambien ve los procesos
	   que no son de Cygwin. */
	if ( kill ( ( pid_t ) lPID, 0 ) == 0 )
	{
		bRes = true;
	}
	else if ( errno == EPERM )
	{
		bRes = true;
	}
# endif
	return ( bRes );
}

bool SisProcesoEnEjecucion ( long lPID )
{
	bool bRes = false;

# if ( defined ( WIN ) )
	HANDLE	hProceso;
	DWORD	dwCodFin;

	hProceso = OpenProcess ( PROCESS_QUERY_INFORMATION, FALSE, (DWORD) lPID );
	if ( hProceso != NULL )
	{
		if ( GetExitCodeProcess ( hProceso, &dwCodFin ) != 0 )
		{
			bRes = ( dwCodFin == STILL_ACTIVE );
		}
	}
	CloseHandle ( hProceso );
# else
	int 		iEstado;
	long		lResSis;

	lResSis = waitpid ( lPID, &iEstado, WNOHANG );
 	if ( lResSis == lPID )
	{
		bRes = ( ! WIFEXITED ( iEstado ) && ! WIFSIGNALED ( iEstado ) );
	}
	else if ( lResSis == 0 )
	{	
		bRes = true;
	}
# endif
	return ( bRes );
}

bool SisProgramaEnEjecucion ( const string & sEjecutable )
{
	bool bRes = false;
# if ( defined ( WIN ) )
	HANDLE				hSnapshot;
	PROCESSENTRY32		pe32Datos;
	int					iFinal;
# endif
	if ( ! sEjecutable.empty() )
	{
#	 if ( defined ( WIN ) )
		hSnapshot = CreateToolhelp32Snapshot ( TH32CS_SNAPPROCESS, 0 );
		if ( hSnapshot != INVALID_HANDLE_VALUE )
		{
			pe32Datos.dwSize = sizeof ( PROCESSENTRY32 );
			if ( Process32First ( hSnapshot, &pe32Datos ) != 0 )
			{
				iFinal = 0;
				while ( ( iFinal == 0 ) && ! bRes )
				{
					if ( strcmp ( sEjecutable.c_str(), pe32Datos.szExeFile ) == 0 )
					{
						bRes = true;
					}
					else if ( Process32Next ( hSnapshot, &pe32Datos ) == 0 )
					{
						iFinal = 1;
					}
				}
			}
			CloseHandle ( hSnapshot );
		}
#		 else
			/* Recorriendo /proc y comparando con el nombre del ejecutable de
			   cada proceso, que es lo que compara la rama de Windows con
			   szExeFile. LIMITACION EN CYGWIN: /proc solo lista procesos de
			   Cygwin, con lo que aqui la respuesta es parcial en ese modo. */
			bRes = ( _SisRecorrerProcesos ( sEjecutable, 0, false ) >= 0 );
#		 endif
 	}
	return ( bRes );
}

long SisProcesoPID ( const string & sEjecutable )
{
	long				lRes = - 1;
# if ( defined ( WIN ) )
	HANDLE				hSnapshot;
	PROCESSENTRY32		pe32Datos;
	int					iFinal;
# endif
	
	if ( ! sEjecutable.empty () )
	{
#	  if ( defined ( WIN ) )
		hSnapshot = CreateToolhelp32Snapshot ( TH32CS_SNAPPROCESS, 0 );
		if ( hSnapshot != INVALID_HANDLE_VALUE )
		{
			pe32Datos.dwSize = sizeof ( PROCESSENTRY32 );
			if ( Process32First ( hSnapshot, &pe32Datos ) != 0 )
			{
				iFinal = 0;
				lRes = -1;
				while ( ( iFinal == 0 ) && ( lRes < 0 ) )
				{
					if ( sEjecutable == pe32Datos.szExeFile )
					{
						lRes = pe32Datos.th32ProcessID;
					}
					else if ( Process32Next ( hSnapshot, &pe32Datos ) == 0 )
					{
						iFinal = 1;
					}
				}
			}
			CloseHandle ( hSnapshot );
		}
#	 else
		/* Mismo recorrido que SisProgramaEnEjecucion, quedandose con el PID en
		   vez de con el si o el no. Misma LIMITACION EN CYGWIN. */
		lRes = _SisRecorrerProcesos ( sEjecutable, 0, false );
#	 endif
	}
	return ( lRes );
}

/*
typedef struct tagPROCESSENTRY32 {  DWORD dwSize;  DWORD cntUsage;  DWORD th32ProcessID;  ULONG_PTR th32DefaultHeapID;  DWORD th32ModuleID;  DWORD cntThreads;  DWORD th32ParentProcessID;  LONG pcPriClassBase;  DWORD dwFlags;  TCHAR szExeFile[MAXPATHLEN];
} PROCESSENTRY32,
*/
unsigned long SisProcesoTiempoCPU ( long lPID )
{
	unsigned long	ulRes = 0;
# if ( defined ( WIN ) )
	FILETIME	ftimCreacion;
	FILETIME	ftimFinalizacion;
	FILETIME	ftimSistema;
	FILETIME	ftimUsuario;
	SYSTEMTIME	systimValor;
	HANDLE		hProceso;
		
	hProceso = OpenProcess ( PROCESS_ALL_ACCESS, FALSE, (DWORD) lPID );
	if ( hProceso != NULL )
	{
		if ( GetProcessTimes ( hProceso, &ftimCreacion, &ftimFinalizacion, 
								&ftimSistema, &ftimUsuario ) != 0 )
		{
			if ( FileTimeToSystemTime ( &ftimSistema, &systimValor ) != 0 )
			{
				ulRes = systimValor.wDay * 86400000 + 
					    systimValor.wHour * 3600000 +
						systimValor.wMinute * 60000 +
						systimValor.wSecond * 1000 +
						systimValor.wMilliseconds;

				if ( FileTimeToSystemTime ( &ftimUsuario, &systimValor ) != 0 )
				{
					ulRes = ulRes +
							systimValor.wDay * 86400000 + 
							systimValor.wHour * 3600000 +
							systimValor.wMinute * 60000 +
							systimValor.wSecond * 1000 +
							systimValor.wMilliseconds;
				}
			}
		}
		CloseHandle ( hProceso );
	}
# else
	/* De /proc/<pid>/stat, que da el tiempo total: nucleo mas usuario, como
	   hace la rama de Windows. */
	ulRes = _SisTiempoCPUDeProceso ( lPID, SIS_CPU_COMPLETO );
# endif
	return ( ulRes );
}

unsigned long SisProcesoTiempoCPUModoNucleo ( long lPID )
{
	unsigned long	ulRes = 0;
# if ( defined ( WIN ) )
	FILETIME	ftimCreacion;
	FILETIME	ftimFinalizacion;
	FILETIME	ftimSistema;
	FILETIME	ftimUsuario;
	SYSTEMTIME	systimValor;
	HANDLE		hProceso;
		
	hProceso = OpenProcess ( PROCESS_ALL_ACCESS, FALSE, (DWORD) lPID );
	if ( hProceso != NULL )
	{
		if ( GetProcessTimes ( hProceso, &ftimCreacion, &ftimFinalizacion, 
								&ftimSistema, &ftimUsuario ) != 0 )
		{
			if ( FileTimeToSystemTime ( &ftimSistema, &systimValor ) != 0 )
			{
				ulRes = systimValor.wDay * 86400000 + 
					    systimValor.wHour * 3600000 +
						systimValor.wMinute * 60000 +
						systimValor.wSecond * 1000 +
						systimValor.wMilliseconds;
			}
		}
		CloseHandle ( hProceso );
	}
# else
	/* De /proc/<pid>/stat: solo el tiempo de nucleo, el campo stime. */
	ulRes = _SisTiempoCPUDeProceso ( lPID, SIS_CPU_NUCLEO );
# endif
	return ( ulRes );
}

unsigned long SisProcesoTiempoCPUModoUsuario ( long lPID )
{
	unsigned long	ulRes = 0;
# if ( defined ( WIN ) )
	FILETIME	ftimCreacion;
	FILETIME	ftimFinalizacion;
	FILETIME	ftimSistema;
	FILETIME	ftimUsuario;
	SYSTEMTIME	systimValor;
	HANDLE		hProceso;
		
	hProceso = OpenProcess ( PROCESS_ALL_ACCESS, FALSE, (DWORD) lPID );
	if ( hProceso != NULL )
	{
		if ( GetProcessTimes ( hProceso, &ftimCreacion, &ftimFinalizacion, 
								&ftimSistema, &ftimUsuario ) != 0 )
		{
			if ( FileTimeToSystemTime ( &ftimUsuario, &systimValor ) != 0 )
			{
				ulRes = systimValor.wDay * 86400000 + 
						systimValor.wHour * 3600000 +
						systimValor.wMinute * 60000 +
						systimValor.wSecond * 1000 +
						systimValor.wMilliseconds;
			}
		}
		CloseHandle ( hProceso );
	}
# else
	/* De /proc/<pid>/stat: solo el tiempo de usuario, el campo utime. */
	ulRes = _SisTiempoCPUDeProceso ( lPID, SIS_CPU_USUARIO );
# endif
	return ( ulRes );
}


bool SisFinalizarProceso ( long lPID )
{
	bool bRes = false;

#  if ( defined ( WIN ) )
	if ( SisExisteProceso ( lPID ) == 1 )
	{
		HANDLE hProceso;
		
		hProceso = OpenProcess ( PROCESS_ALL_ACCESS, FALSE, (DWORD) lPID );
		if ( hProceso != NULL )
		{
			bRes = ( TerminateProcess ( hProceso, 0 ) != 0 );
			CloseHandle ( hProceso );
		}
	}
# else
	/* Portado del stack C, que ya lo tenia resuelto. SIGKILL y no SIGTERM porque
	   esta es la equivalente de TerminateProcess: finaliza, no pide que termine.
	   El waitpid recoge al hijo para no dejar un zombi; con WNOHANG no bloquea si
	   el proceso no era hijo nuestro. */
	int iEstado;

	if ( kill ( (pid_t) lPID, SIGKILL ) == 0 )
	{
		waitpid ( (pid_t) lPID, &iEstado, WNOHANG );
		bRes = true;
	}
# endif
	return ( bRes );
}

static void * _HiloVigilarPadre ( void * p_arg )
{
# if ( defined ( WIN ) ) 
    DWORD       pidPadre;
    HANDLE      hPadre;
    HANDLE      hSnap;
    PROCESSENTRY32 pe;
    DWORD       pidPropio;
# else
	pid_t pidPadre;
# endif

# if ( defined ( WIN ) )
	pidPadre = 0;
	hPadre  = NULL;

    hSnap = CreateToolhelp32Snapshot ( TH32CS_SNAPPROCESS, 0 );
    if ( hSnap != INVALID_HANDLE_VALUE ) 
	{
        pe.dwSize = sizeof(pe);
        pidPropio = GetCurrentProcessId ();

        if ( Process32First( hSnap, &pe ) ) 
		{
            do {
                if ( pe.th32ProcessID == pidPropio ) 
				{
                    pidPadre = pe.th32ParentProcessID;
                    break;
                }
            } while ( Process32Next( hSnap, &pe ) );
        }
        CloseHandle ( hSnap );
    }

    /* Abrir handle al padre para poder vigilarlo */
    if ( pidPadre != 0 ) 
	{
        hPadre = OpenProcess ( SYNCHRONIZE, FALSE, pidPadre );
    }
# else
	pidPadre = getppid ();
# endif

# if ( defined ( WIN ) )
	/* Sin manejador no hay a quien vigilar. Que OpenProcess falle ( permisos,
	   o el padre ya no esta cuando arranca el hilo ) NO es lo mismo que el
	   padre haya muerto, asi que se abandona la vigilancia en lugar de matar
	   al proceso, que es lo que hacia antes. */
	if ( ES_MANEJADOR_NULO ( hPadre ) )
	{
		return ( NULL );
	}
# endif

    while ( 1 )
    {
		/* Una sola espera para las dos plataformas. */
		std::this_thread::sleep_for ( std::chrono::seconds ( 1 ) );

# if ( defined ( WIN ) )

        if ( WaitForSingleObject ( hPadre, 0 ) == WAIT_OBJECT_0 )
		{
            /* El padre ha muerto, el hijo se autotermina. En Windows se sale
               sin senales, a proposito. */
			CloseHandle ( hPadre );
            ExitProcess ( 1 );
        }
# else
		// SisConAsincEscribirConFormato ( "BUCLE HILO %lu/%lu\n",  getppid (), pidPadre );
        if ( getppid () != pidPadre )
        {
            /* El padre ha muerto, el hijo se autotermina */
            raise ( SIGTERM );
        }
# endif
    }
	return ( NULL );
}

thread::id SisLanzarHiloVigilanciaPadre ()
{
	return ( SisCrearHilo ( _HiloVigilarPadre, NULL ) );
}


			}
		}
	}
}
