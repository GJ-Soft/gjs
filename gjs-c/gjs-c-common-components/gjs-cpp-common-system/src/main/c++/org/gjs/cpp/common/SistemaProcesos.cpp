/***************************************************************************/
/*                         SistemaProcesos.cpp                             */
/*-------------------------------------------------------------------------*/
/* Librer�a: Sistema                                                       */
/* Versi�n:  1.1.0                                                         */
/* Fecha:    26/10/2006                                                    */
/* Autor:    Gin�s Jim�nez S�nchez                                         */
/*-------------------------------------------------------------------------*/
/* Descripci�n:                                                            */
/* Fichero de c�digo fuente que contiene la implementaci�n de las rutinas  */
/* de car�cter general de informaci�n acerca de los procesos en ejecuci�n, */
/* as� como algunas rutinas de gesti�n de los mismos.                      */  
/*-------------------------------------------------------------------------*/
/* NOTA DEL AUTOR:                                                         */
/* Este m�dulo est� extra�do de una librer�a m�s completa creada por el    */
/* mismo autor. Por favor, el autor ruega que se le informe de cualquier   */
/* error detectado, as� como cualquier a�adido o modificaci�n realizado.   */
/* Pueden reportar de los mismos enviando un correo electr�nico a la       */
/* direcci�n: gines_jimenez@safe-mail.net. Gracias.                        */
/***************************************************************************/
#include "CommonSystemConfig.h"


#include "SistemaProcesos.h"





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
	// PENDIENTE: Mejorar para obtenerlo din�micamente:
	if ( ES_VALIDO ( _g_p_sSisNomProceso ) )
	{
		sRes = *_g_p_sSisNomProceso;
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

string SisTituloProceso ()
{
	string sRes = "";

# if ( defined ( WIN ) )
	STARTUPINFO		stupinfDatos;

	GetStartupInfo ( (LPSTARTUPINFO) &stupinfDatos );
	if ( ES_VALIDO ( stupinfDatos.lpTitle ) )
	{
		sRes = string ( stupinfDatos.lpTitle );
	}
# else
	// PENDIENTE:
# endif
	return ( sRes );
}

#if ( defined ( WIN ) )

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

	GetStartupInfo ( (LPSTARTUPINFO) &stupinfDatos );
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

	GetStartupInfo ( (LPSTARTUPINFO) &stupinfDatos );
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

thread_id SisTID ()
{
	thread_id thTID;

# if ( defined ( WIN ) )
	thTID = (thread_id) GetCurrentThreadId ();
# else
	thTID = (thread_id) pthread_self ();
# endif
	return ( thTID );
}

string SisTIDCadena ()
{
	return ( ToString ( SisTID () ) );
}

int SisNumSubprocesos ()
{
	int			iRes;		
# if ( defined ( WIN ) )
	HANDLE				hProceso;
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
				hProceso = OpenProcess ( PROCESS_ALL_ACCESS, FALSE, (DWORD) pe32Datos.th32ProcessID );
				if ( hProceso != NULL )
				{
					iRes = iRes + 1;
					CloseHandle ( hProceso );
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
	// PENDIENTE:
	iRes = 0;
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
	int				iNumArgs;
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
#		  if ( defined ( GNU ) )
			iNumArgs = NumPalabras ( sParametros, ' ' );
			if ( iNumArgs > 0 )
			{ 
				// TODO 
			}
			else
			{
				if ( execl ( sEjecutable.c_str(), sEjecutable.c_str(), NULL) < 0 )
				{
					exit ( -1 );
				}
			}
#		  else
			// PENDIENTE: Hacer lo mismo para el paso como cadenas:
			if ( execv ( sEjecutable.c_str(), sParametros.c_str ()  ) < 0 )
			{
				// Error: Destruir el hijo;
				exit ( -1 );
			}
#		  endif
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

// PENDIUENTE: Determinar que sea un proceso hijo
bool SisExisteSubproceso ( long lPID )
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
	// PENDIENTE:
# endif
	return ( bRes );
}

bool SisFinalizarSubproceso ( long lPID )
{
	bool bRes = false;

	if ( SisExisteSubproceso ( lPID ) == 1 )
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
	// PENDIENTE:
# endif
	}
	return ( bRes );
}

int SisNumHilos ()
{
	int iRes;

# if ( defined ( WIN ) )
	HANDLE				hSnapshot;
	PROCESSENTRY32		pe32Datos;

	hSnapshot = CreateToolhelp32Snapshot ( TH32CS_SNAPPROCESS, 0 );
	if ( hSnapshot != INVALID_HANDLE_VALUE )
	{
		pe32Datos.dwSize = sizeof ( PROCESSENTRY32 );
		if ( Process32First ( hSnapshot, &pe32Datos ) != 0 )
		{
			iRes = (int) pe32Datos.cntThreads;
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
	//PENDIENTE:
	iRes = 0;
# endif
	return ( iRes );
}

// PENDIENTE: GetThreadId s�lo funciona en VISTA:
thread_id SisCrearHilo ( PTR_FUNCION_HILO p_funCodigo, void * p_vParam, int iSuspender )
{
	thread_id			thHilo;
# if ( defined ( WIN ) )
	HANDLE			hHilo;
	DWORD			dwId;
	LPVOID			lpParam;
	DWORD			dwFlags;
# else
	pthread_t		thId;
	pthread_attr_t  thattHilo;
# endif

	if ( ES_VALIDO ( p_funCodigo ) )
	{
# if ( defined ( WIN ) )
		lpParam = (LPVOID) p_vParam;
		dwId = 0;
		if ( iSuspender == 1 )
		{
			dwFlags = CREATE_SUSPENDED;
		}
		else
		{
			dwFlags = 0;
		}
		hHilo = CreateThread ( (LPSECURITY_ATTRIBUTES)NULL, (DWORD)0, (LPTHREAD_START_ROUTINE)p_funCodigo, lpParam, dwFlags, (LPDWORD)&dwId ); 
		if ( ES_MANEJADOR_VALIDO ( hHilo ) ) 
		{
			thHilo = (thread_id) dwId;
		}
		else
		{
			thHilo = (thread_id) 0;
		}
# else
		thId = 0;
		pthread_attr_init ( &thattHilo );
		pthread_attr_setdetachstate ( &thattHilo, PTHREAD_CREATE_DETACHED );

		if ( pthread_create ( &thId, &thattHilo, p_funCodigo, p_vParam ) == 0 )
		{
			thHilo = (thread_id) thId;
		}
		else
		{
			thHilo = (thread_id) 0;
		}
		pthread_attr_destroy ( &thattHilo );
# endif
	}
	else
	{
		thHilo = 0;
	}
	return ( thHilo );
}

bool SisExisteHilo ( thread_id thTID )
{
	bool bRes = false;

# if ( defined ( WIN ) )
	HANDLE		hHilo;
# else
	pthread_t	thId;
#  if ( defined ( pthread_getcpuclockid ) )
	clockid_t	clkCPU;
#  endif
# endif

# if ( defined ( WIN ) )
//#  if ( !defined ( OPENTHREAD_INDEFINIDO ) )
#  if ( defined ( OpenThread ) )
	{
		hHilo = OpenThread ( SYNCHRONIZE, FALSE, thTID );
	}
#  else
	{
	/*
		PFUNHNDDWBDW p_fOpenThread;

		p_fOpenThread = (PFUNHNDDWBDW) SisLibPrimitiva ( "kernel32", "OpenThread" );
		if ( ES_VALIDO ( p_fOpenThread ) )
		{
			hHilo = p_fOpenThread ( SYNCHRONIZE, FALSE, thTID );
		}
		else
		{
			hHilo = NULL;
		}
	*/
		hHilo = NULL;
	}
#  endif
	if ( ES_MANEJADOR_VALIDO ( hHilo ) )
	{
		bRes = true;
		CloseHandle ( hHilo );
	}
# else
	thId = (pthread_t) thTID;
#  if ( defined ( pthread_getcpuclockid ) )
	bRes = ( pthread_getcpuclockid ( thId, &clkCPU ) == 0 );
#  else
	// PEDNIENTE
#  endif
# endif
	return ( bRes );
}

bool SisSuspenderHilo ( thread_id thTID )
{
	bool bRes = false;

# if ( defined ( WIN ) )
	HANDLE		hHilo;
# else
	//pthread_t	thId;
# endif

# if ( defined ( WIN ) )
#  if ( defined ( OpenThread ) )
	{
		hHilo = OpenThread ( SYNCHRONIZE, FALSE, thTID );
	}
#  else
	{
		/*
		PFUNHNDDWBDW p_fOpenThread;

		p_fOpenThread = (PFUNHNDDWBDW) SisLibPrimitiva ( "kernel32", "OpenThread" );
		if ( ES_VALIDO ( p_fOpenThread ) )
		{
			hHilo = p_fOpenThread ( SYNCHRONIZE, FALSE, thTID );
		}
		else
		{
		}
		*/
		hHilo = NULL;
	}
#  endif
	if ( ES_MANEJADOR_VALIDO ( hHilo ) )
	{
		bRes = ( SuspendThread ( hHilo ) != 0xFFFFFFFF );
		CloseHandle ( hHilo );
	}
# else
	//PENDIENTE: No se puede hacer igual: hay que montar una historia
# endif
	return ( bRes );
}

bool SisReanudarHilo ( thread_id thTID )
{
	bool bRes = false;

# if ( defined ( WIN ) )
	HANDLE		hHilo;
# else
	//pthread_t	thId;
# endif

# if ( defined ( WIN ) )
#  if ( defined ( OpenThread ) )
	{
		hHilo = OpenThread ( SYNCHRONIZE, FALSE, thTID );
	}
#  else
	{
		/*
		PFUNHNDDWBDW p_fOpenThread;

		p_fOpenThread = (PFUNHNDDWBDW) SisLibPrimitiva ( "kernel32", "OpenThread" );
		if ( ES_VALIDO ( p_fOpenThread ) )
		{
			hHilo = p_fOpenThread ( SYNCHRONIZE, FALSE, thTID );
		}
		else
		{
			hHilo = NULL;
		}
		*/
		hHilo = NULL;
	}
#  endif
	if ( ES_MANEJADOR_VALIDO ( hHilo ) )
	{
		bRes = ( ResumeThread ( hHilo ) != 0xFFFFFFFF );
		CloseHandle ( hHilo );
	}
# else
	//PENDIENTE: No se puede hacer igual: hay que montar una historia
# endif
	return ( bRes );
}

bool SisFinalizarHilo ( thread_id thTID )
{
	bool bRes = false;

# if ( defined ( WIN ) )
	HANDLE		hHilo;
	//DWORD		dwIdHilo;
# else
	pthread_t	thId;
# endif

# if ( defined ( WIN ) )
#  if ( defined ( OpenThread ) )
	{
		hHilo = OpenThread ( SYNCHRONIZE, FALSE, thTID );
	}
#  else
	{
		/*
		PFUNHNDDWBDW p_fOpenThread;

		p_fOpenThread = (PFUNHNDDWBDW) SisLibPrimitiva ( "kernel32", "OpenThread" );
		if ( ES_VALIDO ( p_fOpenThread ) )
		{
			dwIdHilo = (DWORD) thTID;
			hHilo = p_fOpenThread ( SYNCHRONIZE, FALSE, dwIdHilo );
		}
		else
		{
			hHilo = NULL;
		}
		*/
		hHilo = NULL;
	}
#  endif
	if ( ES_MANEJADOR_VALIDO ( hHilo ) )
	{
		bRes = ( TerminateThread ( hHilo, 0 ) != -1 );
		CloseHandle ( hHilo );
	}
# else
	thId = (pthread_t) thTID;
	bRes = ( pthread_cancel ( thId ) == 0 );
# endif
	return ( bRes );
}

bool SisCambiarASiguienteHilo ()
{
	bool bRes = false;

# if ( defined ( WIN ) )
	//if ( SwitchToThread () != 0 )
	if ( false )
	{
		bRes = true;
	}
# else
	//PENDIENTE:
# endif
	return ( bRes );
}

int SisHiloPrioridad ( thread_id thTID )
{
	int			iRes = 0;

# if ( defined ( WIN ) )
	HANDLE		hHilo;
# else
	//pthread_t	thId;
# endif

# if ( defined ( WIN ) )
#  if ( defined ( OpenThread ) )
	{
		hHilo = OpenThread ( SYNCHRONIZE, FALSE, thTID );
	}
#  else
	{
		/*
		PFUNHNDDWBDW p_fOpenThread;

		p_fOpenThread = (PFUNHNDDWBDW) SisLibPrimitiva ( "kernel32", "OpenThread" );
		if ( ES_VALIDO ( p_fOpenThread ) )
		{
			hHilo = p_fOpenThread ( SYNCHRONIZE, FALSE, thTID );
		}
		else
		{
			hHilo = NULL;
		}
		*/
		hHilo = NULL;
	}
#  endif
	if ( ES_MANEJADOR_VALIDO ( hHilo ) )
	{
		iRes = GetThreadPriority ( hHilo );
		if ( iRes == THREAD_PRIORITY_ERROR_RETURN )
		{
			iRes = 0;
		}
		CloseHandle ( hHilo );
	}
# else
	//PENDIENTE:
# endif
	return ( iRes );
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
# endif


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
	// PENDIENTE: Puede ser que sea necesario m�s tama�o (comprobar caso SBufTam ( p_bufDatos )== dwTamOcupado):
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
	// PENDIENTE: Puede ser que sea necesario m�s tama�o (comprobar caso SBufTam ( p_bufDatos )== dwTamOcupado):
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
	   no los del sistema. Compilando en modo Cygwin POSIX ( el de por defecto )
	   esta funcion devuelve un punado de PID, mientras que en estilo Windows
	   devuelve todos los del equipo. En Linux nativo si es la lista completa. */
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
	// PENDIENTE:
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
			// PENDIENTE:
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
		// PENDIENTE:
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
	// PENDIENTE:
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
	// PENDIENTE:
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
	// PENDIENTE:
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
	int iEstado;

	// TODO
	//if ( ::kill  ( lPID, SIGKILL ) == 0 )
	if ( false )
	{
		waitpid ( lPID, &iEstado, WNOHANG );
		bRes = true;
	}
# endif
	return ( bRes );
}


			}
		}
	}
}
