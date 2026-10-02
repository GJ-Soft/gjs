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

#include "SistemaProcesos.h"


#include "SistemaConfig.h"

/* pthread para el registro de hilos y para las operaciones sobre ellos. Los
   dos compiladores lo tienen: Cygwin por POSIX y MinGW-w64 por winpthreads. */
#include <SistemaTiempo.h>
#include <pthread.h>
#include <sched.h>
/* kill () y SIGTERM, para las funciones de subproceso en POSIX. errno, para
   distinguir 'no existe' de 'existe pero no es mio'. */
#include <signal.h>
#include <errno.h>


// De momento SistemaLiberías sólo funciona para WIN:
#if ( defined ( WIN ) )
#	include "SistemaLibrerias.h"
#endif





#if ( defined ( POSIX ) )
#	define _DISP_TMP_INFO_PROCESOS					"/dev/ps"
#endif



# if ( ! defined ( WIN ) || ! defined ( _PSAPI_H_ ) )
char * _g_p_sSisNomProceso = NULL;
#endif



#if ( !defined ( WIN ) )
void SisProcInicializar ( const char * p_cNomProceso )
{
	if ( ES_VALIDO ( p_cNomProceso ) )
	{
		_g_p_sSisNomProceso = CadDuplicar ( p_cNomProceso );
	}
}

void SisProcFinalizar ()
{
	MemLiberar ( (void **) &_g_p_sSisNomProceso );
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

char * SisPIDCadena ()
{
	char *	p_cRes;
	SCadenaConv *	p_cadPID;

	p_cadPID = SCadcCrear ( 10 );
	if ( ES_VALIDO ( p_cadPID ) )
	{
		SCadcCopiarEnteroLargo ( p_cadPID, SisPID () );
		p_cRes = CadDuplicar ( SCadcValor ( p_cadPID ) );
		SCadcDestruir ( &p_cadPID );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

# if ( !defined ( WIN ) )
/* Cierto si la cadena no esta vacia y es toda digitos. Se usa para quedarse con
   las entradas de /proc que son un PID, descartando las demas ( cpuinfo, self,
   registry... ). */
static int _SisEsSoloDigitos ( const char * p_cNombre )
{
	int			iRes;
	int			iPos;

	iRes = 0;
	if ( ES_VALIDO ( p_cNombre ) )
	{
		iPos = 0;
		iRes = 1;
		while ( ( p_cNombre [ iPos ] != '\0' ) && ( iRes == 1 ) )
		{
			if ( ( p_cNombre [ iPos ] < '0' ) || ( p_cNombre [ iPos ] > '9' ) )
			{
				iRes = 0;
			}
			iPos = iPos + 1;
		}
		if ( iPos == 0 )
		{
			iRes = 0;
		}
	}
	return ( iRes );
}

# if ( ! defined ( WIN ) )

/******************************************************************************/
/* Lectura de /proc                                                           */
/*----------------------------------------------------------------------------*/
/* Todo lo que hay debajo sale de /proc, que Linux y Cygwin tienen con el mismo*/
/* formato. Con una DIFERENCIA IMPORTANTE en Cygwin: /proc solo lista los      */
/* procesos de Cygwin, no los del resto de Windows ( medido: 6 frente a los    */
/* cientos que hay en la maquina ). Por eso las funciones que RECORREN /proc   */
/* buscando otros procesos dan una respuesta parcial en ese modo, y asi queda  */
/* dicho en cada una. Las que preguntan por el proceso actual, o por uno cuyo  */
/* PID ya se tiene, van bien en los dos.                                      */
/******************************************************************************/

#define SIS_PROC_TAM_LINEA			1024

/* Numero de campo dentro de /proc/<pid>/stat, contando el estado como el 1
   ( o sea, saltandose el pid y el nombre ). Ver _SisCampoStat. */
#define SIS_PROC_CAMPO_PPID			2
#define SIS_PROC_CAMPO_UTIME		12
#define SIS_PROC_CAMPO_STIME		13

/* Que parte del tiempo de CPU se quiere. */
#define SIS_CPU_COMPLETO				0
#define SIS_CPU_NUCLEO				1
#define SIS_CPU_USUARIO				2


/* Deja en el destino el contenido de /proc/<pid>/<que>, terminado en nulo.
   Devuelve 1 si pudo leer algo. */
static int _SisLeerDeProc ( long lPID, const char * p_cQue, char * p_cDestino, size_t uTam )
{
	int		iRes;
	FILE *	p_filDato;
	char	cRuta [ MAXPATHLEN ];
	size_t	uLeido;

	snprintf ( cRuta, sizeof ( cRuta ), "/proc/%ld/%s", lPID, p_cQue );
	p_filDato = fopen ( cRuta, "r" );
	if ( p_filDato != NULL )
	{
		uLeido = fread ( p_cDestino, 1, uTam - 1, p_filDato );
		p_cDestino [ uLeido ] = ASCII_NUL;
		fclose ( p_filDato );
		if ( uLeido > 0 )
		{
			iRes = 1;
		}
		else
		{
			iRes = 0;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

/* Devuelve el campo numero iCampo de /proc/<pid>/stat contando DESDE EL ESTADO,
   que es el 1. Hay que empezar a contar ahi porque el campo anterior es el
   nombre del ejecutable, va entre parentesis y puede llevar espacios y hasta
   parentesis dentro; contar desde el principio de la linea no vale. Por eso se
   busca el ULTIMO parentesis de cierre. Devuelve 0 si no lo encuentra, que en
   los usos de aqui es el mismo valor que devolvia antes la rama entera. */
static unsigned long _SisCampoStat ( const char * p_cStat, int iCampo )
{
	unsigned long	ulRes;
	const char *	p_cResto;
	int				iActual;
	int				iHecho;

	ulRes = 0;
	p_cResto = strrchr ( p_cStat, ')' );
	if ( p_cResto != NULL )
	{
		p_cResto = p_cResto + 1;
		iActual = 0;
		iHecho = 0;
		while ( ( *p_cResto != ASCII_NUL ) && ( iHecho == 0 ) )
		{
			while ( *p_cResto == ' ' )
			{
				p_cResto = p_cResto + 1;
			}
			if ( *p_cResto != ASCII_NUL )
			{
				iActual = iActual + 1;
				if ( iActual == iCampo )
				{
					ulRes = strtoul ( p_cResto, NULL, 10 );
					iHecho = 1;
				}
				else
				{
					while ( ( *p_cResto != ' ' ) && ( *p_cResto != ASCII_NUL ) )
					{
						p_cResto = p_cResto + 1;
					}
				}
			}
		}
	}
	return ( ulRes );
}

/* PID del padre de un proceso, o 0 si no se pudo averiguar. */
static long _SisPPIDDeProceso ( long lPID )
{
	long	lRes;
	char	cStat [ SIS_PROC_TAM_LINEA ];

	if ( _SisLeerDeProc ( lPID, "stat", cStat, sizeof ( cStat ) ) == 1 )
	{
		lRes = (long) _SisCampoStat ( cStat, SIS_PROC_CAMPO_PPID );
	}
	else
	{
		lRes = 0;
	}
	return ( lRes );
}

/* Ruta del ejecutable de un proceso, leyendo el enlace /proc/<pid>/exe.
   Devuelve una copia que hay que liberar, o NULL. */
static char * _SisEjecutableDeProceso ( long lPID )
{
	char *		p_cRes;
	char		cRuta [ MAXPATHLEN ];
	char		cDestino [ MAXPATHLEN ];
	ssize_t		sLongitud;

	snprintf ( cRuta, sizeof ( cRuta ), "/proc/%ld/exe", lPID );
	sLongitud = readlink ( cRuta, cDestino, sizeof ( cDestino ) - 1 );
	if ( sLongitud > 0 )
	{
		cDestino [ sLongitud ] = ASCII_NUL;
		p_cRes = CadDuplicar ( cDestino );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

/* Nombre del fichero ejecutable de un proceso, sin la ruta. Copia a liberar. */
static char * _SisNombreEjecutableDeProceso ( long lPID )
{
	char *	p_cRes;
	char *	p_cRuta;

	p_cRuta = _SisEjecutableDeProceso ( lPID );
	if ( ES_VALIDO ( p_cRuta ) )
	{
		p_cRes = SisRutaFichero ( p_cRuta );
		MemLiberar ( (void **) &p_cRuta );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

/* Tiempo de CPU de un proceso, en MILISEGUNDOS, que es lo que devuelve la rama
   de Windows. */
static unsigned long _SisTiempoCPUDeProceso ( long lPID, int iModo )
{
	unsigned long	ulRes;
	unsigned long	ulTics;
	char			cStat [ SIS_PROC_TAM_LINEA ];
	long			lTicsPorSegundo;

	ulRes = 0;
	if ( _SisLeerDeProc ( lPID, "stat", cStat, sizeof ( cStat ) ) == 1 )
	{
		ulTics = 0;
		if ( iModo != SIS_CPU_NUCLEO )
		{
			ulTics = ulTics + _SisCampoStat ( cStat, SIS_PROC_CAMPO_UTIME );
		}
		if ( iModo != SIS_CPU_USUARIO )
		{
			ulTics = ulTics + _SisCampoStat ( cStat, SIS_PROC_CAMPO_STIME );
		}
		/* Los campos vienen en tics de reloj. Cuantos hay por segundo lo dice el
		   sistema y NO se puede dar por sabido: son 100 en Linux y 1000 en
		   Cygwin ( medido el 2026-09-18 ). */
		lTicsPorSegundo = sysconf ( _SC_CLK_TCK );
		if ( lTicsPorSegundo > 0 )
		{
			ulRes = ( ulTics * 1000UL ) / (unsigned long) lTicsPorSegundo;
		}
	}
	return ( ulRes );
}

/* Recorre /proc buscando un proceso cuyo ejecutable se llame como se pide.
   Devuelve su PID, o -1. Si p_iContarHijos vale 1, en vez de buscar por nombre
   cuenta los procesos cuyo padre es el que se pasa, y devuelve la cuenta. */
static long _SisRecorrerProcesos ( const char * p_cEjecutable, long lPadre, int iContar )
{
	long			lRes;
	DIR *			p_dirProc;
	struct dirent *	p_entDato;
	char *			p_cNombre;
	long			lPID;

	if ( iContar == 1 )
	{
		lRes = 0;
	}
	else
	{
		lRes = -1;
	}
	p_dirProc = opendir ( "/proc" );
	if ( ES_VALIDO ( p_dirProc ) )
	{
		p_entDato = readdir ( p_dirProc );
		while ( ES_VALIDO ( p_entDato ) )
		{
			if ( _SisEsSoloDigitos ( p_entDato->d_name ) )
			{
				lPID = strtol ( p_entDato->d_name, NULL, 10 );
				if ( iContar == 1 )
				{
					if ( _SisPPIDDeProceso ( lPID ) == lPadre )
					{
						lRes = lRes + 1;
					}
				}
				else
				{
					if ( lRes < 0 )
					{
						p_cNombre = _SisNombreEjecutableDeProceso ( lPID );
						if ( ES_VALIDO ( p_cNombre ) )
						{
							if ( CadComparar ( p_cNombre, p_cEjecutable ) == COMP_IGUAL )
							{
								lRes = lPID;
							}
							MemLiberar ( (void **) &p_cNombre );
						}
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
# endif

char * SisNombreProceso ()
{
	char *		p_cRes;
# if ( ( defined ( WIN ) ) && ( defined ( _PSAPI_H_ ) ) )
	HANDLE		hProceso;
	HMODULE		hModulo;
    DWORD		dwTam;
	SBuffer	*	p_bufDatos;
# else
	char *		p_cRuta;
# endif

# if ( ( defined ( WIN ) ) && ( defined ( _PSAPI_H_ ) ) )
 	p_bufDatos = SBufCrear ( MAXPATHLEN );
	if ( ES_VALIDO ( p_bufDatos ) )
	{
		hProceso = OpenProcess ( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, GetCurrentProcessId () );
		if ( ES_MANEJADOR_VALIDO ( hProceso ) )
		{
			if ( EnumProcessModules ( hProceso, &hModulo, sizeof ( hModulo ), &dwTam ) != 0 )
			{
				if ( GetModuleBaseName ( hProceso, hModulo, (LPSTR) SBufDireccion ( p_bufDatos ), ((DWORD) SBufTam ( p_bufDatos )) / sizeof ( char ) ) > 0 )
				{
					p_cRes = SBufDuplicarCadena ( p_bufDatos );
				}
				else
				{
					p_cRes = NULL;
				}
			}
			else
			{
				p_cRes = NULL;
			}
			CloseHandle ( hProceso );
		}
		else
		{
			p_cRes = NULL;
		}
		SBufDestruir ( &p_bufDatos );
	}
	else
	{
		p_cRes = NULL;
	}
# else
	/* Si alguien fijo el nombre a mano con el setter, manda ese. Si no, se saca
	   del sistema, que era justo lo que faltaba: /proc/self/exe
	   apunta al ejecutable, y de ahi el nombre del fichero, que es lo que
	   devuelve GetModuleBaseName en la rama de Windows. */
	if ( ES_VALIDO ( _g_p_sSisNomProceso ) )
	{
		p_cRes = CadDuplicar ( _g_p_sSisNomProceso );
	}
	else
	{
		p_cRuta = _SisEjecutableDeProceso ( (long) getpid () );
		if ( ES_VALIDO ( p_cRuta ) )
		{
			p_cRes = SisRutaFichero ( p_cRuta );
			MemLiberar ( (void **) &p_cRuta );
		}
		else
		{
			p_cRes = NULL;
		}
	}
# endif
	return ( p_cRes );
}

char * SisRutaEjecutable ()
{
	char *		p_cRes;
	SBuffer *	p_bufDatos;
# if ( ( defined ( WIN ) ) && ( defined ( _PSAPI_H_ ) ) )
	HANDLE		hProceso;
	int			iTam;
# else
	char *		p_cDir;
# endif

# if ( ( defined ( WIN ) ) && ( defined ( _PSAPI_H_ ) ) )
 	p_bufDatos = SBufCrear ( MAXPATHLEN );
	if ( ES_VALIDO ( p_bufDatos ) )
	{
		hProceso = OpenProcess ( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, GetCurrentProcessId () );
		if ( ES_MANEJADOR_VALIDO ( hProceso ) )
		{
			iTam = (int) GetModuleFileNameEx ( hProceso, NULL, (LPTSTR) SBufDireccion ( p_bufDatos ), (DWORD) SBufTam ( p_bufDatos ) );
			if ( iTam > 0 )
			{
				p_cRes = SBufDuplicarCadena ( p_bufDatos );
			}
			else
			{
				p_cRes = NULL;
			}
			CloseHandle ( hProceso );
		}
		else
		{
			p_cRes = NULL;
		}
		SBufDestruir ( &p_bufDatos );
	}
	else
	{
		p_cRes = NULL;
	}
# elif ( defined ( GNU ) )
	p_cDir = NULL;
	p_cRes = NULL;
	if ( ES_VALIDO ( _g_p_sSisNomProceso ) )
	{
		if ( SisEsRutaValida ( _g_p_sSisNomProceso ) == 1 )
		{
			p_cRes = CadDuplicar ( _g_p_sSisNomProceso );
		}
		else
		{
			p_bufDatos = SBufCrear ( MAXPATHLEN );
			if ( ES_VALIDO ( p_bufDatos ) )
			{
				if ( getcwd ( ( char * ) SBufDireccion ( p_bufDatos ), ( size_t ) SBufTam ( p_bufDatos ) ) != NULL )
				{
					p_cDir = SBufDuplicarCadena ( p_bufDatos );
					if ( ES_VALIDO ( p_cDir ) )
					{
						p_cRes = SisComponerRuta ( p_cDir, _g_p_sSisNomProceso, 0 );
						MemLiberar ( ( void ** ) &p_cDir );
					}
					else
					{
						p_cRes = NULL;
					}
				}
				else
				{
					p_cRes = NULL;
				}
				SBufDestruir ( &p_bufDatos );
			}
			else
			{
				p_cRes = NULL;
			}
		}
	}
	else
	{
		p_bufDatos = SBufCrear ( MAXPATHLEN );
		if ( ES_VALIDO ( p_bufDatos ) )
		{
			if ( getcwd ( ( char * ) SBufDireccion ( p_bufDatos ), ( size_t ) SBufTam ( p_bufDatos ) ) != NULL )
			{
				p_cDir = SBufDuplicarCadena ( p_bufDatos );
				if ( ES_VALIDO ( p_cDir ) )
				{
					p_cRes = SisComponerRuta ( p_cDir, _g_p_sSisNomProceso, 0 );
					MemLiberar ( ( void ** ) &p_cDir );
				}
				else
				{
					p_cRes = NULL;
				}
			}
			else
			{
				p_cRes = NULL;
			}
			SBufDestruir ( &p_bufDatos );
		}
	}
# else
 	p_bufDatos = SBufCrear ( MAXPATHLEN );
	if ( ES_VALIDO ( p_bufDatos ) )
	{
		if ( getcwd ( (char *) SBufDireccion ( p_bufDatos ), (size_t) SBufTam ( p_bufDatos ) ) != NULL )
		{
			p_cDir = SBufDuplicarCadena ( p_bufDatos );
			if ( ES_VALIDO ( p_cDir ) )
			{
				p_cRes = SisComponerRuta ( p_cDir, _g_p_sSisNomProceso, 0 );
				MemLiberar ( (void **) &p_cDir );
			}
			else
			{
				p_cRes = NULL;
			}
		}
		else
		{
			p_cRes = NULL;
		}
		SBufDestruir ( &p_bufDatos );
	}
	else
	{
		p_cRes = NULL;
	}
# endif
	return ( p_cRes );
}

char * SisDirectorioEjecutable ()
{
	char * p_cRuta;
	char * p_cRes;

	p_cRuta = SisRutaEjecutable ();
	if ( ES_VALIDO ( p_cRuta ) )
	{
		p_cRes = SisRutaDirectorio ( p_cRuta );
		MemLiberar ( (void **) &p_cRuta );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

char * SisFicheroEjecutable ()
{
	char * p_cRuta;
	char * p_cRes;

	p_cRuta = SisRutaEjecutable ();
	if ( ES_VALIDO ( p_cRuta ) )
	{
		p_cRes = SisRutaFichero ( p_cRuta );
		MemLiberar ( (void **) &p_cRuta );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

# if ( defined ( WIN ) )

char * SisTituloProceso ()
{
	char * p_cRes;

	STARTUPINFO		stupinfDatos;

	GetStartupInfo ( &stupinfDatos );
	if ( ES_VALIDO ( stupinfDatos.lpTitle ) )
	{
		p_cRes = CadDuplicar ( stupinfDatos.lpTitle );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
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
	return ( iRes );
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
	return ( iRes );
}
*/

thread SisTID ()
{
	thread thTID;

# if ( defined ( WIN ) )
	thTID = (thread) GetCurrentThreadId ();
# else
	thTID = (thread) pthread_self ();
# endif
	return ( thTID );
}

char * SisTIDCadena ()
{
	char *	p_cRes;
	SCadenaConv *	p_cadTID;

	p_cadTID = SCadcCrear ( 10 );
	if ( ES_VALIDO ( p_cadTID ) )
	{
		SCadcCopiarEnteroLargo ( p_cadTID, SisTID () );
		p_cRes = CadDuplicar ( SCadcValor ( p_cadTID ) );
		SCadcDestruir ( &p_cadTID );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
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
	iRes = (int) _SisRecorrerProcesos ( NULL, (long) getpid (), 1 );
# endif
	return ( iRes );
}

long SisCrearSubproceso ( const char * p_cEjecutable, const char * p_cParametros, int iHeredarDescriptores, int iCerrarConsola )
{
	long lPID;

# if ( defined ( WIN ) )
	PROCESS_INFORMATION prcinfDatos;
	STARTUPINFO			stupintDatos;
	BOOL				bHeredar;
	DWORD				dwFlags;
	char *				p_cComando;
	int					iTam;
# else
	pid_t				pidRes;
	int					iUltDescrip;
	int					iDescrip;
#  if ( defined ( GNU ) )
	char **				p_p_cArgv;
	char *				p_cArg;
	int					iNumArgs;
	int					iArg;
	int					iError;
#  endif
#endif

# if ( defined ( WIN ) )
	if ( ES_VALIDO ( p_cEjecutable ) )
	{
		// Set up the start up info struct.
		MemLimpiar ( (void *) &stupintDatos, sizeof ( STARTUPINFO ) );
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
		iTam = CadLongitud ( p_cEjecutable );
		if ( ES_VALIDO ( p_cParametros ) )
		{
			iTam = iTam + CadLongitud ( p_cParametros ) + 1;
		}

		p_cComando = CadCrear ( iTam );
		if ( ES_VALIDO ( p_cComando ) )
		{
			CadCopiar ( p_cComando, p_cEjecutable );
			if ( ES_VALIDO ( p_cParametros ) )
			{
				CadConcatenarCaracter ( p_cComando, ' ' );
				CadConcatenar ( p_cComando, p_cParametros );
			}

			if ( CreateProcess ( p_cEjecutable, p_cComando, NULL, NULL, bHeredar, dwFlags, NULL, NULL, &stupintDatos, &prcinfDatos ) != 0 )
			{
				lPID = (long) prcinfDatos.dwProcessId;
			}
			else
			{
				lPID = -1;
			}
			MemLiberar ( (void **) &p_cComando );
		}
		else
		{
			lPID = -1;
		}
	}	
	else
	{
		lPID = -1;
	}
# else
	pidRes = fork ();
	if ( pidRes < 0 )
	{
		//Padre: Error en la creación del subproceso:
		lPID = -1;
	}
	else if ( pidRes > 0 )
	{
		// Padre: Retorna el PID del subproceso:
		lPID = (long) pidRes;
	}
	else
	{
		lPID = 0;
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

		if ( ES_VALIDO ( p_cEjecutable ) )
		{
			if ( ES_VALIDO ( p_cParametros ) )
			{
				/* Aqui habia un reparto #if defined ( GNU ) / #else. No tenia
				   sentido: armar el argv es codigo del propio repo
				   ( CadNumPalabrasExt, CadPalabraExt, MemReservar ), no tiene
				   nada de GNU. Y la rama de enfrente, la que nunca se compila
				   porque Precompilacion.h define GNU salvo con CC, llamaba a
				   execv pasandole la cadena de parametros donde va un vector de
				   punteros: no habria compilado nunca. Fuera el reparto. */
				/* Ojo con la firma: el segundo parametro NO es el separador, es el
				   indicador de "separar signos", y el tercero es el maximo de
				   caracteres a mirar. Pasaba ' ' y 0, con lo que CadLongitudSeg se
				   quedaba en cero caracteres, la cuenta salia 0 y los parametros se
				   perdian SIEMPRE: el hijo arrancaba sin ninguno. Comprobado. El
				   separador ya es el espacio por defecto, y -1 es sin limite. */
				iNumArgs = CadNumPalabrasExt ( p_cParametros, 0, -1 );
				if ( iNumArgs > 0 )
				{ 
					p_p_cArgv = (char **) MemReservar ( ( iNumArgs + 2 ) * sizeof ( char * ) );
					if ( ES_VALIDO ( p_p_cArgv ) )
					{
						for ( iArg = 0; iArg < iNumArgs + 2; iArg = iArg + 1 )
						{
							p_p_cArgv [ iArg ] = NULL;
						}

						p_p_cArgv [ 0 ] = CadDuplicar ( p_cEjecutable );
						iArg = 0;
						iError = 0;
						while ( ( iArg < iNumArgs ) && ( iError == 0 ) )
						{ 
							p_cArg = CadPalabraExt ( p_cParametros, iArg, 0, -1 );
							if ( ES_VALIDO ( p_cArg ) )
							{
								p_p_cArgv [ iArg + 1 ] = p_cArg;
							}
							else
							{
								iError = 1;
							}
							iArg = iArg + 1;
						}	

						if ( iError == 0 )
						{
							if ( execv ( p_cEjecutable, p_p_cArgv ) < 0 )
							{
								exit ( -1 );
							}
						}

                        for ( iArg = 0; iArg < iNumArgs; iArg = iArg + 1 )
                        {
                                MemLiberar ( (void **) &(p_p_cArgv [ iArg ]) );
                        }
						MemLiberar ( (void **) &p_p_cArgv );

						exit ( -1 );
					}
					else
					{
						if ( execl ( p_cEjecutable, p_cEjecutable, NULL ) < 0 )
						{
							exit ( -1 );
						}
					}
				}
				/* El #else de aqui abajo partia la sentencia por la mitad: el 'else {'
				   solo existia en la rama GNU y el '}' final lo compartian las dos, asi
				   que la rama sin GNU cerraba una llave que nadie habia abierto. No se
				   notaba porque Precompilacion.h define GNU siempre salvo que este CC,
				   pero dejaba el fichero sin compilar en esa configuracion, y el
				   analizador estatico no podia parsearlo: SistemaProcesos.c se quedaba
				   sin analizar entero. Ahora cada rama es una sentencia completa. */
				else 
				{
					if ( execl ( p_cEjecutable, p_cEjecutable, NULL ) < 0 )
					{
						// Error: Destruir el hijo;
						exit ( -1 );
					}
				}
			}
			else
			{
				if ( execl ( p_cEjecutable, p_cEjecutable, NULL ) < 0 )
				{
					exit ( -1 );
				}
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
static int _SisEsSubproceso ( long lPIDPadre, long lPIDHijo )
{
    int iRes = 0;

# if ( !defined ( WIN ) )
    if ( _SisPPIDDeProceso ( lPIDHijo ) == lPIDPadre )
	{
		iRes = 1;
	}
# else
    HANDLE hSnapshot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
    if ( ES_MANEJADOR_VALIDO ( hSnapshot ) )
	{
		PROCESSENTRY32 pe;
		pe.dwSize = sizeof(PROCESSENTRY32);

		if ( Process32First( hSnapshot, &pe ) != 0 ) 
		{
			do 
			{
				if ( pe.th32ProcessID == (DWORD) lPIDHijo )
				{
					if ( pe.th32ParentProcessID == (DWORD) lPIDPadre )
					{
						iRes = 1;
					}
					break; 
				}
			} 
			while ( Process32Next( hSnapshot, &pe ) != 0 );
		}
		CloseHandle(hSnapshot);
	}
# endif
    return ( iRes );
}

int SisExisteSubproceso ( long lPID )
{
	int	iRes;

# if ( defined ( WIN ) )
	/* Sin OpenProcess previo: la foto de Toolhelp que mira _SisEsSubproceso ya
	   contesta las dos cosas —si el PID existe y quien es su padre—, asi que
	   abrirlo antes no anadia nada. Y si quitaba: pedir PROCESS_ALL_ACCESS falla
	   contra un proceso elevado o protegido, y entonces esto contestaba "no
	   existe" sobre un hijo que si existia. */
	iRes = _SisEsSubproceso ( SisPID (), lPID );
# else
	/* kill con la senal 0 no manda nada: solo comprueba que el proceso existe y
	   que se le podria senalar. Si falla con EPERM el proceso existe, lo que pasa
	   es que es de otro usuario, y a efectos de 'existe' cuenta igual.

	   Antes esta rama devolvia 0 siempre, con lo que en POSIX no solo mentia ella:
	   SisFinalizarSubproceso esta guardada por su resultado y no llegaba a
	   intentar nada. */
	if ( kill ( (pid_t) lPID, 0 ) == 0 )
	{
		iRes = 1;
	}
	else if ( errno == EPERM )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
# endif
	return ( iRes );
}

int SisFinalizarSubproceso ( long lPID )
{
	int	iRes;

	if ( SisExisteSubproceso ( lPID ) == 1 )
	{
# if ( defined ( WIN ) )
		HANDLE hProceso;
		
		hProceso = OpenProcess ( PROCESS_ALL_ACCESS, FALSE, (DWORD) lPID );
		if ( ES_MANEJADOR_VALIDO ( hProceso ) )
		{
			if ( TerminateProcess ( hProceso, 0 ) != 0 )
			{
				iRes = 1;
			}
			else
			{
				iRes = 0;
			}
			CloseHandle ( hProceso );
		}
		else
		{
			iRes = 0;
		}
# else
		/* SIGTERM es el equivalente de lo que hace TerminateProcess arriba: pedir
		   al proceso que termine. Si la ignora no hay mas que hacer desde aqui;
		   matarla a la fuerza seria SIGKILL, y eso es otra decision. */
		if ( kill ( (pid_t) lPID, SIGTERM ) == 0 )
		{
			iRes = 1;
		}
		else
		{
			iRes = 0;
		}
# endif
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

/* ---------------------------------------------------------------------------
   Registro de los hilos creados por esta API.

   Los hilos POSIX se crean desprendidos ( PTHREAD_CREATE_DETACHED ), asi que en
   cuanto terminan su pthread_t deja de ser valido y usarlo es comportamiento
   indefinido. En Windows pasa algo parecido con los identificadores, que el
   sistema reutiliza. El registro guarda, mientras el hilo vive, lo que hace
   falta para operar sobre el: el HANDLE en Windows y el pthread_t en POSIX.

   Es tambien lo que hace que SisExisteHilo pueda responder de verdad y que
   SisNumHilos cuente algo con sentido. Mismo modelo que el stack de C++.
   --------------------------------------------------------------------------- */

typedef struct _SisNodoHilo
{
	thread					thTID;
# if ( defined ( WIN ) )
	HANDLE					hHilo;
# else
	pthread_t				thId;
# endif
	struct _SisNodoHilo *	p_nodSiguiente;
} _SisNodoHilo;

static _SisNodoHilo *	_p_nodHilos = NULL;
static pthread_mutex_t	_mtxHilos = PTHREAD_MUTEX_INITIALIZER;

/* Busca en el registro. Hay que llamarla con _mtxHilos tomado. */
static _SisNodoHilo * _SisBuscarHilo ( thread thTID )
{
	_SisNodoHilo * p_nodAct;

	p_nodAct = _p_nodHilos;
	while ( ES_VALIDO ( p_nodAct ) && ( p_nodAct->thTID != thTID ) )
	{
		p_nodAct = p_nodAct->p_nodSiguiente;
	}
	return ( p_nodAct );
}

/* Da de baja el hilo y suelta lo que llevaba asociado. */
static void _SisOlvidarHilo ( thread thTID )
{
	_SisNodoHilo *	p_nodAct;
	_SisNodoHilo *	p_nodPrevio;

	pthread_mutex_lock ( &_mtxHilos );
	p_nodPrevio = NULL;
	p_nodAct = _p_nodHilos;
	while ( ES_VALIDO ( p_nodAct ) && ( p_nodAct->thTID != thTID ) )
	{
		p_nodPrevio = p_nodAct;
		p_nodAct = p_nodAct->p_nodSiguiente;
	}
	if ( ES_VALIDO ( p_nodAct ) )
	{
		if ( ES_VALIDO ( p_nodPrevio ) )
		{
			p_nodPrevio->p_nodSiguiente = p_nodAct->p_nodSiguiente;
		}
		else
		{
			_p_nodHilos = p_nodAct->p_nodSiguiente;
		}
# if ( defined ( WIN ) )
		if ( ES_MANEJADOR_VALIDO ( p_nodAct->hHilo ) )
		{
			CloseHandle ( p_nodAct->hHilo );
		}
# endif
		MemLiberar ( ( void ** ) &p_nodAct );
	}
	pthread_mutex_unlock ( &_mtxHilos );
}

int SisNumHilos ()
{
	int				iRes;
	_SisNodoHilo *	p_nodAct;

	iRes = 0;
	pthread_mutex_lock ( &_mtxHilos );
	p_nodAct = _p_nodHilos;
	while ( ES_VALIDO ( p_nodAct ) )
	{
		iRes = iRes + 1;
		p_nodAct = p_nodAct->p_nodSiguiente;
	}
	pthread_mutex_unlock ( &_mtxHilos );
	return ( iRes );
}

/* Argumento de la envoltura: se reserva en el creador y lo suelta el hilo. */
typedef struct
{
	PTR_FUNCION_HILO	p_funCodigo;
	void *				p_vParam;
} _SisArgHilo;

/* Envoltura del codigo del usuario, para darse de baja al terminar. El mutex
   evita la carrera del hilo tan corto que acaba antes de que SisCrearHilo lo
   haya llegado a registrar: la baja no puede adelantarse al alta. */
# if ( defined ( WIN ) )
static DWORD WINAPI _SisEjecutarHilo ( LPVOID p_vArg )
# else
static void * _SisEjecutarHilo ( void * p_vArg )
# endif
{
	_SisArgHilo *		p_argHilo;
	PTR_FUNCION_HILO	p_funCodigo;
	void *				p_vParam;

	p_argHilo = ( _SisArgHilo * ) p_vArg;
	p_funCodigo = p_argHilo->p_funCodigo;
	p_vParam = p_argHilo->p_vParam;
	MemLiberar ( ( void ** ) &p_argHilo );

	p_funCodigo ( p_vParam );
	_SisOlvidarHilo ( SisTID () );

# if ( defined ( WIN ) )
	return ( 0 );
# else
	return ( NULL );
# endif
}

thread SisCrearHilo ( PTR_FUNCION_HILO p_funCodigo, void * p_vParam, int iSuspender )
{
	thread			thHilo;
	_SisArgHilo *	p_argHilo;
	_SisNodoHilo *	p_nodNuevo;
# if ( defined ( WIN ) )
	HANDLE			hHilo;
	DWORD			dwId;
	DWORD			dwBanderas;
# else
	pthread_t		thId;
	pthread_attr_t	thattHilo;
# endif

	thHilo = ( thread ) 0;
	if ( ES_VALIDO ( p_funCodigo ) )
	{
		p_argHilo = ( _SisArgHilo * ) MemReservar ( sizeof ( _SisArgHilo ) );
		p_nodNuevo = ( _SisNodoHilo * ) MemReservar ( sizeof ( _SisNodoHilo ) );
		if ( ES_VALIDO ( p_argHilo ) && ES_VALIDO ( p_nodNuevo ) )
		{
			p_argHilo->p_funCodigo = p_funCodigo;
			p_argHilo->p_vParam = p_vParam;

			pthread_mutex_lock ( &_mtxHilos );
# if ( defined ( WIN ) )
			dwId = 0;
			dwBanderas = ( iSuspender == 1 ) ? CREATE_SUSPENDED : 0;
			hHilo = CreateThread ( NULL, 0, _SisEjecutarHilo, ( LPVOID ) p_argHilo,
								   dwBanderas, &dwId );
			if ( ES_MANEJADOR_VALIDO ( hHilo ) )
			{
				thHilo = ( thread ) dwId;
				p_nodNuevo->thTID = thHilo;
				p_nodNuevo->hHilo = hHilo;
			}
# else
			/* iSuspender se ignora: POSIX no sabe crear un hilo detenido. */
			thId = 0;
			pthread_attr_init ( &thattHilo );
			pthread_attr_setdetachstate ( &thattHilo, PTHREAD_CREATE_DETACHED );
			if ( pthread_create ( &thId, &thattHilo, _SisEjecutarHilo, p_argHilo ) == 0 )
			{
				thHilo = ( thread ) thId;
				p_nodNuevo->thTID = thHilo;
				p_nodNuevo->thId = thId;
			}
			pthread_attr_destroy ( &thattHilo );
# endif
			if ( thHilo != ( thread ) 0 )
			{
				p_nodNuevo->p_nodSiguiente = _p_nodHilos;
				_p_nodHilos = p_nodNuevo;
				p_nodNuevo = NULL;
				p_argHilo = NULL;
			}
			pthread_mutex_unlock ( &_mtxHilos );
		}
		/* Lo que no se haya llegado a usar se suelta. */
		MemLiberar ( ( void ** ) &p_argHilo );
		MemLiberar ( ( void ** ) &p_nodNuevo );
	}
	return ( thHilo );
}

int SisExisteHilo ( thread thTID )
{
	int iRes;

	pthread_mutex_lock ( &_mtxHilos );
	iRes = ES_VALIDO ( _SisBuscarHilo ( thTID ) ) ? 1 : 0;
	pthread_mutex_unlock ( &_mtxHilos );
	return ( iRes );
}

/* Suspender y reanudar solo existen en Windows. POSIX nunca tuvo equivalente de
   SuspendThread, y lo que se intento con senales no es seguro, asi que en POSIX
   se devuelve 0 en vez de fingir que funciona.
   ( En el stack de C++ tampoco funcionan en Windows, porque alli std::thread va
   sobre winpthreads y native_handle () da un pthread_t, no un HANDLE. Aqui el
   hilo lo crea CreateThread, asi que el HANDLE si esta disponible. ) */
int SisSuspenderHilo ( thread thTID )
{
	int				iRes;
# if ( defined ( WIN ) )
	_SisNodoHilo *	p_nodHilo;

	iRes = 0;
	pthread_mutex_lock ( &_mtxHilos );
	p_nodHilo = _SisBuscarHilo ( thTID );
	if ( ES_VALIDO ( p_nodHilo ) )
	{
		iRes = ( SuspendThread ( p_nodHilo->hHilo ) != ( DWORD ) -1 ) ? 1 : 0;
	}
	pthread_mutex_unlock ( &_mtxHilos );
# else
	( void ) thTID;
	iRes = 0;
# endif
	return ( iRes );
}

int SisReanudarHilo ( thread thTID )
{
	int				iRes;
# if ( defined ( WIN ) )
	_SisNodoHilo *	p_nodHilo;

	iRes = 0;
	pthread_mutex_lock ( &_mtxHilos );
	p_nodHilo = _SisBuscarHilo ( thTID );
	if ( ES_VALIDO ( p_nodHilo ) )
	{
		iRes = ( ResumeThread ( p_nodHilo->hHilo ) != ( DWORD ) -1 ) ? 1 : 0;
	}
	pthread_mutex_unlock ( &_mtxHilos );
# else
	( void ) thTID;
	iRes = 0;
# endif
	return ( iRes );
}




SListaEnterosLargos * SisListaProcesos ()
{
	SListaEnterosLargos * p_lislPID = NULL;
# if ( defined ( WIN ) )
	int						iError;
#  if ( defined ( _EnumProcesses ) )
 	SBuffer	*				p_bufDatos;
	DWORD					dwTamOcupado;
	int						iNumProcesos;
    int						iProceso;
	DWORD *					p_dwProcesos;
#  else
	HANDLE					hSnapshot;
	PROCESSENTRY32			pe32Datos;
	int						iFinal;
#  endif
# else
	DIR *					p_dirProc;
	struct dirent *			p_entDato;
# endif

# if ( defined ( WIN ) )
#  if ( defined ( _EnumProcesses ) )
 	p_bufDatos = SBufCrear ( SIS_SO_MAX_TAM_BUFFER );
	if ( ES_VALIDO ( p_bufDatos ) )
	{
		p_lislPID = SLisEntlCrear ();
		p_dwProcesos = (DWORD *) SBufDireccion ( p_bufDatos );
		// PENDIENTE: Puede ser que sea necesario más tamaño (comprobar caso SBufTam ( p_bufDatos )== dwTamOcupado):
		if ( EnumProcesses ( p_dwProcesos, (DWORD) SBufTam ( p_bufDatos ), &dwTamOcupado ) != 0 )
		{
			iNumProcesos = dwTamOcupado / sizeof ( DWORD );
			iProceso = 0;
			iError = 0;
			while ( ( iProceso < iNumProcesos ) && ( iError == 0 ) )
			{
				if ( p_dwProcesos [ iProceso ] != 0 )
				{
					SLisEntlInsertar ( p_lislPID, ( long ) p_dwProcesos [iProceso] );
				}
				iProceso = iProceso + 1;
			}
		}
		else
		{
			p_lislPID = NULL;
		}
		SBufDestruir ( &p_bufDatos );
	}
	else
	{
		p_lislPID = NULL;
	}
#  else
	hSnapshot = CreateToolhelp32Snapshot ( TH32CS_SNAPPROCESS, 0 );
	if ( hSnapshot != INVALID_HANDLE_VALUE )
	{
		p_lislPID = SLisEntlCrear ();
		pe32Datos.dwSize = sizeof ( PROCESSENTRY32 );
		if ( Process32First ( hSnapshot, &pe32Datos ) != 0 )
		{
			iError = 0;
			iFinal = 0;
			// Process32First ya ha dejado el primer proceso en pe32Datos: se
			// mete y solo despues se pide el siguiente. Al reves se perdia uno.
			while ( ( iFinal == 0 ) && ( iError == 0 ) )
			{
				SLisEntlInsertar ( p_lislPID, ( long ) pe32Datos.th32ProcessID );
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
	p_dirProc = opendir ( "/proc" );
	if ( ES_VALIDO ( p_dirProc ) )
	{
		p_lislPID = SLisEntlCrear ();
		if ( ES_VALIDO ( p_lislPID ) )
		{
			p_entDato = readdir ( p_dirProc );
			while ( ES_VALIDO ( p_entDato ) )
			{
				if ( _SisEsSoloDigitos ( p_entDato->d_name ) )
				{
					SLisEntlInsertar ( p_lislPID, atol ( p_entDato->d_name ) );
				}
				p_entDato = readdir ( p_dirProc );
			}
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


/* Termina el hilo por las malas. En Windows TerminateThread no deja que el hilo
   limpie nada; en POSIX pthread_cancel solo surte efecto cuando el hilo alcanza
   un punto de cancelacion ( sleep, read, wait... ), asi que uno metido en un
   bucle de calculo puro puede no enterarse nunca. Al no volver por la envoltura,
   la baja del registro se hace aqui. */
int SisFinalizarHilo ( thread thTID )
{
	int				iRes;
	_SisNodoHilo *	p_nodHilo;

	iRes = 0;
	pthread_mutex_lock ( &_mtxHilos );
	p_nodHilo = _SisBuscarHilo ( thTID );
	if ( ES_VALIDO ( p_nodHilo ) )
	{
# if ( defined ( WIN ) )
		iRes = ( TerminateThread ( p_nodHilo->hHilo, 0 ) != 0 ) ? 1 : 0;
# else
		iRes = ( pthread_cancel ( p_nodHilo->thId ) == 0 ) ? 1 : 0;
# endif
	}
	pthread_mutex_unlock ( &_mtxHilos );
	if ( iRes == 1 )
	{
		_SisOlvidarHilo ( thTID );
	}
	return ( iRes );
}

int SisCambiarASiguienteHilo ()
{
	/* sched_yield esta en las dos plataformas: en Cygwin por POSIX y en MinGW
	   por winpthreads. No hace falta rama. */
	return ( ( sched_yield () == 0 ) ? 1 : 0 );
}

int SisHiloPrioridad ( thread thTID )
{
	int					iRes;
	_SisNodoHilo *		p_nodHilo;
# if ( !defined ( WIN ) )
	int					iPolitica;
	struct sched_param	schpDatos;
# endif

	iRes = 0;
	pthread_mutex_lock ( &_mtxHilos );
	p_nodHilo = _SisBuscarHilo ( thTID );
	if ( ES_VALIDO ( p_nodHilo ) )
	{
# if ( defined ( WIN ) )
		iRes = GetThreadPriority ( p_nodHilo->hHilo );
		if ( iRes == THREAD_PRIORITY_ERROR_RETURN )
		{
			iRes = 0;
		}
# else
		if ( pthread_getschedparam ( p_nodHilo->thId, &iPolitica, &schpDatos ) == 0 )
		{
			iRes = schpDatos.sched_priority;
		}
# endif
	}
	pthread_mutex_unlock ( &_mtxHilos );
	return ( iRes );
}

/* Tiempo de CPU consumido por el hilo, en milisegundos. */
unsigned long SisHiloTiempoCPU ( thread thTID )
{
	unsigned long		ulRes;
	_SisNodoHilo *		p_nodHilo;
# if ( defined ( WIN ) )
	FILETIME			ftimCreacion;
	FILETIME			ftimFinalizacion;
	FILETIME			ftimSistema;
	FILETIME			ftimUsuario;
	ULARGE_INTEGER		uliSistema;
	ULARGE_INTEGER		uliUsuario;
# else
	clockid_t			clkCPU;
	struct timespec		tspDatos;
# endif

	ulRes = 0;
	pthread_mutex_lock ( &_mtxHilos );
	p_nodHilo = _SisBuscarHilo ( thTID );
	if ( ES_VALIDO ( p_nodHilo ) )
	{
# if ( defined ( WIN ) )
		if ( GetThreadTimes ( p_nodHilo->hHilo, &ftimCreacion, &ftimFinalizacion,
							  &ftimSistema, &ftimUsuario ) != 0 )
		{
			/* Los FILETIME cuentan en unidades de 100 ns. */
			uliSistema.LowPart = ftimSistema.dwLowDateTime;
			uliSistema.HighPart = ftimSistema.dwHighDateTime;
			uliUsuario.LowPart = ftimUsuario.dwLowDateTime;
			uliUsuario.HighPart = ftimUsuario.dwHighDateTime;
			ulRes = ( unsigned long ) ( ( uliSistema.QuadPart + uliUsuario.QuadPart ) / 10000 );
		}
# else
		if ( pthread_getcpuclockid ( p_nodHilo->thId, &clkCPU ) == 0 )
		{
			if ( clock_gettime ( clkCPU, &tspDatos ) == 0 )
			{
				ulRes = ( unsigned long ) ( ( tspDatos.tv_sec * 1000 ) +
											( tspDatos.tv_nsec / 1000000 ) );
			}
		}
# endif
	}
	pthread_mutex_unlock ( &_mtxHilos );
	return ( ulRes );
}


int SisNumProcesos ()
{
	int			iRes;
# if ( defined ( WIN ) )
#  if ( defined ( _EnumProcesses ) )
 	SBuffer	*	p_bufDatos;
	DWORD		dwTamOcupado;
	int			iNumProcesos;
    int			iProceso;
	DWORD *		p_dwProcesos;
#  endif
# else
	DIR *			p_dirProc;
	struct dirent *	p_entDato;
# endif

	iRes = 0;
# if ( defined ( WIN ) )
#  if ( defined ( _EnumProcesses ) )
 	p_bufDatos = SBufCrear ( SIS_SO_MAX_TAM_BUFFER );
	if ( ES_VALIDO ( p_bufDatos ) )
	{
		p_dwProcesos = (DWORD *) SBufDireccion ( p_bufDatos );
		// PENDIENTE: Puede ser que sea necesario más tamaño (comprobar caso SBufTam ( p_bufDatos )== dwTamOcupado):
		if ( EnumProcesses ( p_dwProcesos, (DWORD) SBufTam ( p_bufDatos ), &dwTamOcupado ) != 0 )
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
		else
		{
			iRes = 0;
		}
		SBufDestruir ( &p_bufDatos );
	}
	else
	{
		iRes = 0;
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
#  endif
# else
	/* Mismo recorrido de /proc que SisListaProcesos, contando en vez de
	   guardando. La misma LIMITACION EN CYGWIN: solo cuenta procesos Cygwin. */
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


int SisExisteProceso ( long lPID )
{
	int		iRes;

# if ( defined ( WIN ) )
	HANDLE hProceso;
	// Se supone que sobre los subprocesos se tiene acceso total:
	hProceso = OpenProcess ( PROCESS_ALL_ACCESS, FALSE, (DWORD) lPID );
	if ( ES_MANEJADOR_VALIDO ( hProceso ) )
	{
		iRes = 1;
		CloseHandle ( hProceso );
	}
	else
	{
		iRes = 0;
	}
# else
	/* Lo mismo que hace SisExisteSubproceso: kill con la senal 0 no manda nada,
	   solo comprueba. Y si falla con EPERM el proceso esta, lo que pasa es que
	   es de otro usuario; a efectos de "existe" cuenta igual.
	   Esta via NO depende de /proc, asi que en Cygwin tambien ve los procesos
	   que no son de Cygwin. */
	if ( kill ( (pid_t) lPID, 0 ) == 0 )
	{
		iRes = 1;
	}
	else if ( errno == EPERM )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
# endif
	return ( iRes );
}

int SisProcesoEnEjecucion ( long lPID )
{
	int		iRes;

# if ( defined ( WIN ) )
	HANDLE	hProceso;
	DWORD	dwCodFin;

	hProceso = OpenProcess ( PROCESS_QUERY_INFORMATION, FALSE, (DWORD) lPID );
	if ( ES_MANEJADOR_VALIDO ( hProceso ) )
	{
		if ( GetExitCodeProcess ( hProceso, &dwCodFin ) != 0 )
		{
			if ( dwCodFin == STILL_ACTIVE )
			{
				iRes = 1;
			}
			else
			{
				iRes = 0;
			}
		}
		else
		{
			iRes = 0;
		}
		CloseHandle ( hProceso );
	}
	else
	{
		iRes = 0;
	}
# else
	int 		iEstado;
	long		lResSis;

	lResSis = waitpid ( lPID, &iEstado, WNOHANG );
 	if ( lResSis == lPID )
	{
		if ( WIFEXITED ( iEstado ) || WIFSIGNALED ( iEstado ) )
		{
			iRes = 0;
		}
		else
		{
			iRes = 1;
		}
	}
	else if ( lResSis == 0 )
	{	
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
# endif
	return ( iRes );
}

int SisProgramaEnEjecucion ( const char * p_cEjecutable )
{
	SCadena *			p_cadNombre;
	int					iRes;
# if ( defined ( WIN ) )
	HANDLE				hSnapshot;
	PROCESSENTRY32		pe32Datos;
	int					iFinal;
# endif

	if ( ES_VALIDO ( p_cEjecutable ) )
	{
		p_cadNombre = SCadGenerar ( p_cEjecutable );
		if ( ES_VALIDO ( p_cadNombre ) )
		{
#		 if ( defined ( WIN ) )
			hSnapshot = CreateToolhelp32Snapshot ( TH32CS_SNAPPROCESS, 0 );
			if ( hSnapshot != INVALID_HANDLE_VALUE )
			{
				pe32Datos.dwSize = sizeof ( PROCESSENTRY32 );
				if ( Process32First ( hSnapshot, &pe32Datos ) != 0 )
				{
					iFinal = 0;
					iRes = 0;
					while ( ( iFinal == 0 ) && ( iRes == 0 ) )
					{
						if ( SCadEsIgualLiteral ( p_cadNombre, pe32Datos.szExeFile ) == 1 )
						{
							iRes = 1;
						}
						else if ( Process32Next ( hSnapshot, &pe32Datos ) == 0 )
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
#		 else
			/* Recorriendo /proc y comparando con el nombre del ejecutable de
			   cada proceso, que es lo que compara la rama de Windows con
			   szExeFile. LIMITACION EN CYGWIN: /proc solo lista procesos de
			   Cygwin, con lo que aqui la respuesta es parcial en ese modo. */
			if ( _SisRecorrerProcesos ( p_cEjecutable, 0, 0 ) >= 0 )
			{
				iRes = 1;
			}
			else
			{
				iRes = 0;
			}
#		 endif
			SCadDestruir ( &p_cadNombre );
		}
		else
		{
			iRes = 0;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

long SisProcesoPID ( const char * p_cEjecutable )
{
	long				lRes;
	SCadena *			p_cadNombre;
# if ( defined ( WIN ) )
	HANDLE				hSnapshot;
	PROCESSENTRY32		pe32Datos;
	int					iFinal;
# endif
	
	if ( ES_VALIDO ( p_cEjecutable ) )
	{
		p_cadNombre = SCadGenerar ( p_cEjecutable );
		if ( ES_VALIDO ( p_cadNombre ) )
		{
#		  if ( defined ( WIN ) )
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
						if ( SCadEsIgualLiteral ( p_cadNombre, pe32Datos.szExeFile ) == 1 )
						{
							lRes = pe32Datos.th32ProcessID;
						}
						else if ( Process32Next ( hSnapshot, &pe32Datos ) == 0 )
						{
							iFinal = 1;
						}
					}
				}
				else
				{
					lRes = -1;
				}
				CloseHandle ( hSnapshot );
			}
			else
			{
				lRes = -1;
			}
#		 else
			/* Mismo recorrido que SisProgramaEnEjecucion, quedandose con el PID
			   en vez de con el si o el no. Misma LIMITACION EN CYGWIN. */
			lRes = _SisRecorrerProcesos ( p_cEjecutable, 0, 0 );
#		 endif
			SCadDestruir ( &p_cadNombre );
		}
		else
		{
			lRes = -1;
		}
	}
	else
	{
		lRes = -1;
	}
	return ( lRes );
}

/*
typedef struct tagPROCESSENTRY32 {  DWORD dwSize;  DWORD cntUsage;  DWORD th32ProcessID;  ULONG_PTR th32DefaultHeapID;  DWORD th32ModuleID;  DWORD cntThreads;  DWORD th32ParentProcessID;  LONG pcPriClassBase;  DWORD dwFlags;  TCHAR szExeFile[MAXPATHLEN];
} PROCESSENTRY32,
*/
unsigned long SisProcesoTiempoCPU ( long lPID )
{
	unsigned long	ulRes;
# if ( defined ( WIN ) )
	FILETIME	ftimCreacion;
	FILETIME	ftimFinalizacion;
	FILETIME	ftimSistema;
	FILETIME	ftimUsuario;
	SYSTEMTIME	systimValor;
	HANDLE		hProceso;
		
	hProceso = OpenProcess ( PROCESS_ALL_ACCESS, FALSE, (DWORD) lPID );
	if ( ES_MANEJADOR_VALIDO ( hProceso ) )
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
				else
				{
					ulRes = 0;
				}
			}
			else
			{
				ulRes = 0;
			}
		}
		else
		{
			ulRes = 0;
		}
		CloseHandle ( hProceso );
	}
	else
	{
		ulRes = 0;
	}
# else
	/* De /proc/<pid>/stat, que da el tiempo total: nucleo mas usuario, como hace la rama de Windows. */
	ulRes = _SisTiempoCPUDeProceso ( lPID, SIS_CPU_COMPLETO );
# endif
	return ( ulRes );
}

unsigned long SisProcesoTiempoCPUModoNucleo ( long lPID )
{
	unsigned long	ulRes;
# if ( defined ( WIN ) )
	FILETIME	ftimCreacion;
	FILETIME	ftimFinalizacion;
	FILETIME	ftimSistema;
	FILETIME	ftimUsuario;
	SYSTEMTIME	systimValor;
	HANDLE		hProceso;
		
	hProceso = OpenProcess ( PROCESS_ALL_ACCESS, FALSE, (DWORD) lPID );
	if ( ES_MANEJADOR_VALIDO ( hProceso ) )
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
			else
			{
				ulRes = 0;
			}
		}
		else
		{
			ulRes = 0;
		}
		CloseHandle ( hProceso );
	}
	else
	{
		ulRes = 0;
	}
# else
	/* De /proc/<pid>/stat, que da solo el tiempo de nucleo ( el campo stime ). */
	ulRes = _SisTiempoCPUDeProceso ( lPID, SIS_CPU_NUCLEO );
# endif
	return ( ulRes );
}

unsigned long SisProcesoTiempoCPUModoUsuario ( long lPID )
{
	unsigned long	ulRes;
# if ( defined ( WIN ) )
	FILETIME	ftimCreacion;
	FILETIME	ftimFinalizacion;
	FILETIME	ftimSistema;
	FILETIME	ftimUsuario;
	SYSTEMTIME	systimValor;
	HANDLE		hProceso;
		
	hProceso = OpenProcess ( PROCESS_ALL_ACCESS, FALSE, (DWORD) lPID );
	if ( ES_MANEJADOR_VALIDO ( hProceso ) )
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
			else
			{
				ulRes = 0;
			}
		}
		else
		{
			ulRes = 0;
		}
		CloseHandle ( hProceso );
	}
	else
	{
		ulRes = 0;
	}
# else
	/* De /proc/<pid>/stat, que da solo el tiempo de usuario ( el campo utime ). */
	ulRes = _SisTiempoCPUDeProceso ( lPID, SIS_CPU_USUARIO );
# endif
	return ( ulRes );
}

/*
long long SisProcesoHoraCreacion ( long lPID )
{
	long long	llRes;
# if ( defined ( WIN ) )
	FILETIME	ftimCreacion;
	FILETIME	ftimFinalizacion;
	FILETIME	ftimSistema;
	FILETIME	ftimUsuario;
	SYSTEMTIME	systimValor;
	HANDLE		hProceso;
		
	hProceso = OpenProcess ( PROCESS_QUERY_INFORMATION, FALSE, (DWORD) lPID );
	if ( ES_MANEJADOR_VALIDO ( hProceso ) )
	{
		if ( GetProcessTimes ( hProceso, &ftimCreacion, &ftimFinalizacion, 
								&ftimSistema, &ftimUsuario ) != 0 )
		{
			//if ( FileTimeToSystemTime ( &ftimCreacion, &systimValor ) != 0 )
			if ( FileTimeToSystemTime ( &ftimSistema, &systimValor ) != 0 )
			{
				llRes = FecFormHoras ( systimValor.wYear, systimValor.wMonth, systimValor.wDay,
											systimValor.wHour, systimValor.wMinute, systimValor.wSecond );
			}
			else
			{
				llRes = 0;
			}
		}
		else
		{
			llRes = 0;
		}
		CloseHandle ( hProceso );
	}
	else
	{
		llRes = 0;
	}
# else
	// PENDIENTE:
	llRes = 0;
# endif
	return ( llRes );
}
*/

int SisFinalizarProceso ( long lPID )
{
	int		iRes;

#  if ( defined ( WIN ) )
	if ( SisExisteProceso ( lPID ) == 1 )
	{
		HANDLE hProceso;
		
		hProceso = OpenProcess ( PROCESS_ALL_ACCESS, FALSE, (DWORD) lPID );
		if ( ES_MANEJADOR_VALIDO ( hProceso ) )
		{
			if ( TerminateProcess ( hProceso, 0 ) != 0 )
			{
				iRes = 1;
			}
			else
			{
				iRes = 0;
			}
			CloseHandle ( hProceso );
		}
		else
		{
			iRes = 0;
		}
	}
	else
	{
		iRes = 0;
	}
# else
	int iEstado;

	if ( kill ( lPID, SIGKILL ) == 0 )
	{
		waitpid ( lPID, &iEstado, WNOHANG );
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
# endif
	return ( iRes );
}


/* static: no esta declarada en ninguna cabecera y solo la usa
   SisLanzarHiloVigilanciaPadre, aqui al lado. */
# if ( defined ( WIN ) )
static int _HiloVigilarPadre ( void * p_arg )
# else
static void * _HiloVigilarPadre ( void * p_arg )
# endif
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
		return ( 0 );
	}
# endif
    while ( 1 )
    {
		/* Una sola espera para las dos plataformas. */
		SisEsperar ( 1000 );

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
# if ( defined ( WIN ) )
	return ( 0 );
# else
    return ( NULL );
# endif
}

thread SisLanzarHiloVigilanciaPadre ()
{
	return ( SisCrearHilo ( _HiloVigilarPadre, NULL, 0 ) );
}
