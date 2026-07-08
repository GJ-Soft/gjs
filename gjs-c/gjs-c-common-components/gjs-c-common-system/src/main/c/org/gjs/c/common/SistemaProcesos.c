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

char * SisNombreProceso ()
{
	char *		p_cRes;
# if ( ( defined ( WIN ) ) && ( defined ( _PSAPI_H_ ) ) )
	HANDLE		hProceso;
	HMODULE		hModulo;
    DWORD		dwTam;
	SBuffer	*	p_bufDatos;
# endif

# if ( ( defined ( WIN ) ) && ( defined ( _PSAPI_H_ ) ) )
 	p_bufDatos = SBufCrear ( MAXPATHLEN );
	if ( ES_VALIDO ( p_bufDatos ) )
	{
		hProceso = OpenProcess ( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, GetCurrentProcessId () );
		if ( ES_VALIDO ( hProceso ) )
		{
			if ( EnumProcessModules ( hProceso, &hModulo, sizeof ( hModulo ), (LPDWORD) &dwTam ) != 0 )
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
	// PENDIENTE: Mejorar para obtenerlo dinámicamente:
	p_cRes = CadDuplicar ( _g_p_sSisNomProceso );
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
		if ( ES_VALIDO ( hProceso ) )
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

char * SisTituloProceso ()
{
	char * p_cRes;

# if ( defined ( WIN ) )
	STARTUPINFO		stupinfDatos;

	GetStartupInfo ( (LPSTARTUPINFO) &stupinfDatos );
	if ( ES_VALIDO ( stupinfDatos.lpTitle ) )
	{
		p_cRes = CadDuplicar ( stupinfDatos.lpTitle );
	}
	else
	{
		p_cRes = NULL;
	}
# else
	// PENDIENTE:
	p_cRes = NULL;
# endif
	return ( p_cRes );
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
	return ( iRes );
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
				if ( ES_VALIDO ( hProceso ) )
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
#			  if ( defined ( GNU ) )
				iNumArgs = CadNumPalabrasExt ( p_cParametros, ' ', 0 );
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
							p_cArg = CadPalabraExt ( p_cParametros, iArg, ' ', 0 );
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
				else 
				{
					if ( execl ( p_cEjecutable, p_cEjecutable, NULL ) < 0 )
#			  else
				// PENDIENTE: Hacer lo mismo para el paso como cadenas:
					if ( execv ( p_cEjecutable, p_cParametros ) < 0 )
#			  endif
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

// PENDIUENTE: Dque sea un proceso hijo
int SisExisteSubproceso ( long lPID )
{
	int	iRes;

# if ( defined ( WIN ) )
	HANDLE hProceso;
	// Se supone que sobre los subprocesos se tiene acceso total:
	hProceso = OpenProcess ( PROCESS_ALL_ACCESS, FALSE, (DWORD) lPID );
	if ( ES_VALIDO ( hProceso ) )
	{
		iRes = 1;
		CloseHandle ( hProceso );
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

int SisFinalizarSubproceso ( long lPID )
{
	int	iRes;

	if ( SisExisteSubproceso ( lPID ) == 1 )
	{
# if ( defined ( WIN ) )
		HANDLE hProceso;
		
		hProceso = OpenProcess ( PROCESS_ALL_ACCESS, FALSE, (DWORD) lPID );
		if ( ES_VALIDO ( hProceso ) )
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
	// PENDIENTE:
		iRes = 0;
# endif
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
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

thread SisCrearHilo ( PTR_FUNCION_HILO p_funCodigo, void * p_vParam, int iSuspender )
{
	thread			thHilo;
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
		if ( ES_VALIDO ( hHilo ) ) 
		{
			thHilo = (thread) dwId;
		}
		else
		{
			thHilo = (thread) 0;
		}
# else
		thId = 0;
		pthread_attr_init ( &thattHilo );
		pthread_attr_setdetachstate ( &thattHilo, PTHREAD_CREATE_DETACHED );

		if ( pthread_create ( &thId, &thattHilo, p_funCodigo, p_vParam ) == 0 )
		{
			thHilo = (thread) thId;
		}
		else
		{
			thHilo = (thread) 0;
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

int SisExisteHilo ( thread thTID )
{
	int			iRes;

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
		PFUNHNDDWBDW p_fOpenThread;

		p_fOpenThread = (PFUNHNDDWBDW) SisLibPrimitiva ( "kernel32", "OpenThread" );
		if ( ES_VALIDO ( p_fOpenThread ) )
		{
			hHilo = p_fOpenThread ( SYNCHRONIZE | THREAD_QUERY_INFORMATION, FALSE, thTID );
		}
		else
		{
			hHilo = NULL;
		}
	}
#  endif
	if ( ES_VALIDO ( hHilo ) )
	{
		iRes = 1;
		CloseHandle ( hHilo );
	}
	else
	{
		iRes = 0;
	}
# else
	thId = (pthread_t) thTID;
#  if ( defined ( pthread_getcpuclockid ) )
	if ( pthread_getcpuclockid ( thId, &clkCPU ) == 0 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
#  else
	// TODO
	iRes = 0;
#  endif
# endif
	return ( iRes );
}

int SisSuspenderHilo ( thread thTID )
{
	int			iRes;

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
	if ( ES_VALIDO ( hHilo ) )
	{
		if ( SuspendThread ( hHilo ) != 0xFFFFFFFF )
		{
			iRes = 1;
		}
		else
		{
			iRes = 0;
		}
		CloseHandle ( hHilo );
	}
	else
	{
		iRes = 0;
	}
# else
	//PENDIENTE: No se puede hacer igual: hay que montar una historia
	iRes = 0;
# endif
	return ( iRes );
}

int SisReanudarHilo ( thread thTID )
{
	int			iRes;

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
	if ( ES_VALIDO ( hHilo ) )
	{
		if ( ResumeThread ( hHilo ) != 0xFFFFFFFF )
		{
			iRes = 1;
		}
		else
		{
			iRes = 0;
		}
		CloseHandle ( hHilo );
	}
	else
	{
		iRes = 0;
	}
# else
	//PENDIENTE: No se puede hacer igual: hay que montar una historia
	iRes = 1;
# endif
	return ( iRes );
}

int SisFinalizarHilo ( thread thTID )
{
	int			iRes;

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
	if ( ES_VALIDO ( hHilo ) )
	{
		if ( TerminateThread ( hHilo, 0 ) != -1 )
		{
			iRes = 1;
		}
		else
		{
			iRes = 0;
		}
		CloseHandle ( hHilo );
	}
	else
	{
		iRes = 0;
	}
# else
	thId = (pthread_t) thTID;
	if ( pthread_cancel ( thId ) == 0 )
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

int SisCambiarASiguienteHilo ()
{
	int iRes;

# if ( defined ( WIN ) )
	//if ( SwitchToThread () != 0 )
	if ( 0 )
	{
		iRes = 1;
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

int SisHiloPrioridad ( thread thTID )
{
	int			iRes;

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
	if ( ES_VALIDO ( hHilo ) )
	{
		iRes = GetThreadPriority ( hHilo );
		if ( iRes == THREAD_PRIORITY_ERROR_RETURN )
		{
			iRes = 0;
		}
		CloseHandle ( hHilo );
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

/*
unsigned long SisHiloTiempoCPU ( thread thTID )
{
	unsigned long	ulRes;
# if ( defined ( WIN ) )
	FILETIME	ftimCreacion;
	FILETIME	ftimFinalizacion;
	FILETIME	ftimSistema;
	FILETIME	ftimUsuario;
	SYSTEMTIME	systimValor;
	HANDLE		hHilo;
		
#  if ( defined ( OpenThread ) )
	{
		hHilo = OpenThread ( SYNCHRONIZE, FALSE, thTID );
	}
#  else
	{
		*//*
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
		*//*
		hHilo = NULL;
	}
#  endif
	if ( hHilo != NULL )
	{
		if ( GetThreadTimes ( hHilo, &ftimCreacion, &ftimFinalizacion, 
								&ftimSistema, &ftimUsuario ) != 0 )
		{
			if ( FileTimeToSystemTime ( &ftimSistema, &systimValor ) != 0 )
			{
				ulRes = TiempoNumSegundos ( systimValor.wDay, systimValor.wHour, 
											systimValor.wMinute, systimValor.wSecond );
				if ( FileTimeToSystemTime ( &ftimUsuario, &systimValor ) != 0 )
				{
					ulRes = ulRes +
								TiempoNumSegundos ( systimValor.wDay, systimValor.wHour, 
													systimValor.wMinute, systimValor.wSecond );
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
		CloseHandle ( hHilo );
	}
	else
	{
		ulRes = 0;
	}
# else
	// PENDIENTE:
	ulRes = 0;
# endif
	return ( ulRes );
}
*/

/*
DWORD WINAPI ThreadProc(
  LPVOID lpParameter   // thread data
);
		ResumeThread ( hHilo );
		
		llTiempo = p_cronTiempo->Computo ();
		while ( ( GetThreadPriority ( hHilo) != THREAD_PRIORITY_ERROR_RETURN ) && ( llTiempo < AI_TIEMPO_CRITICO_SDE ) )
		{
			Sleep ( (DWORD) 100 );
			if ( ES_VALIDO ( p_cronTiempo ) )
			{
				llTiempo = p_cronTiempo->Computo ();
			}
			else
			{
				llTiempo = 0;
			}
		}
		if ( GetThreadPriority ( hHilo ) != THREAD_PRIORITY_ERROR_RETURN )
		{
			TerminateThread ( hHilo, 0 );
		}
*/
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
	// PENDIENTE:
	iRes = 0;
# endif
	return ( iRes );
}

#if ( defined ( CPP ) )
CListaEnterosLargos * SisListaProcesos ()
{
	CListaEnterosLargos *	p_lislPID;
	int						iError;

# if ( defined ( WIN ) )
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
#  if ( defined ( DEVPS_GET_NUM_PIDS ) )
	int						iDesc;
	int						iNumProcesos;
    int						iProceso;
#  endif
# endif

# if ( defined ( WIN ) )
#  if ( defined ( _EnumProcesses ) )
 	p_bufDatos = SBufCrear ( SIS_SO_MAX_TAM_BUFFER );
	if ( ES_VALIDO ( p_bufDatos ) )
	{
		p_dwProcesos = (DWORD *) SBufDireccion ( p_bufDatos );
		// PENDIENTE: Puede ser que sea necesario más tamaño (comprobar caso SBufTam ( p_bufDatos )== dwTamOcupado):
		if ( EnumProcesses( p_dwProcesos, (DWORD) SBufTam ( p_bufDatos ), &dwTamOcupado ) != 0 )
		{
			iNumProcesos = dwTamOcupado / sizeof ( DWORD );
			iProceso = 0;
			iError = 0;
			p_lislPID = new CListaEnterosLargos ();
			if ( ES_VALIDO ( p_lislPID ) )
			{
				while ( ( iProceso < iNumProcesos ) && ( iError == 0 ) )
				{
					if ( p_dwProcesos [ iProceso ] != 0 )
					{
						if ( p_lislPID->Insertar ( (long) p_dwProcesos [ iProceso ] ) == 0 )
						{
							iError = 1;
						}
					}
					iProceso = iProceso + 1;
				}
				if ( iError == 1 )
				{
					DESTRUIR ( CListaEnterosLargos, p_lislPID );
				}
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
		p_lislPID = new CListaEnterosLargos ();
		if ( ES_VALIDO ( p_lislPID ) )
		{
			pe32Datos.dwSize = sizeof ( PROCESSENTRY32 );
			if ( Process32First ( hSnapshot, &pe32Datos ) != 0 )
			{
				iFinal = 0;
				iError = 0;
				while ( ( iFinal == 0 ) && ( iError == 0 ) )
				{
					if ( Process32Next ( hSnapshot, &pe32Datos ) != 0 )
					{
						if ( p_lislPID->Insertar ( (long) pe32Datos.th32ProcessID ) == 0 )
						{
							iError = 1;
						}
					}
					else
					{
						iFinal = 1;
					}
				}
				if ( iError == 1 )
				{
					DESTRUIR ( CListaEnterosLargos, p_lislPID );
				}
			}
			else
			{
				p_lislPID = NULL;
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
#  if ( defined ( DEVPS_GET_NUM_PIDS ) )
	iDesc = open ( _DISP_TMP_INFO_PROCESOS, O_RDONLY );
	if ( iDesc >= 0 ) 
	{
		if ( ioctl ( iDesc, DEVPS_GET_NUM_PIDS, &iNumProcesos ) >= 0 ) 
		{
			p_pidLista = (pid_t *) MemReservar ( iNumProcesos + 10, sizeof ( pid_t ) );
			if ( ES_VALIDO ( p_pidLista ) )
			{
				p_pidLista [ 0 ] = iNumProcesos + 10;

				if ( ioctl ( iDesc, DEVPS_GET_PID_LIST, p_pidLista ) >= 0 )
				{
					iProceso = 0;
					iError = 0;
					p_lislPID = new CListaEnterosLargos ();
					if ( ES_VALIDO ( p_lislPID ) )
					{
						while ( ( iProceso < iNumProcesos + 10 ) && ( iError == 0 ) )
						{
							if ( p_pidLista [ iProceso ] >= 0 )
							{
								if ( p_lislPID->Insertar ( (long) p_pidLista [ iProceso ] ) == 0 )
								{
									iError = 1;
								}
							}
							iProceso = iProceso + 1;
						}
						if ( iError == 1 )
						{
							DESTRUIR ( CListaEnterosLargos, p_lislPID );
						}
					}
				}
				else
				{
					p_lislPID = NULL;
				}
				MemLiberar ( (void **) &p_pidLista );
			}
			else
			{
				p_lislPID = NULL;
			}
		}
		else
		{
			p_lislPID = NULL;
		}
		close ( iDesc );
	}
	else
	{
		p_lislPID = NULL;
	}
#  else
	// PENDIENTE:
	iError = 0;
	p_lislPID = NULL;
#  endif
# endif
	return ( p_lislPID );
}
#endif

int SisExisteProceso ( long lPID )
{
	int		iRes;

# if ( defined ( WIN ) )
	HANDLE hProceso;
	// Se supone que sobre los subprocesos se tiene acceso total:
	hProceso = OpenProcess ( PROCESS_ALL_ACCESS, FALSE, (DWORD) lPID );
	if ( ES_VALIDO ( hProceso ) )
	{
		iRes = 1;
		CloseHandle ( hProceso );
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

int SisProcesoEnEjecucion ( long lPID )
{
	int		iRes;

# if ( defined ( WIN ) )
	HANDLE	hProceso;
	DWORD	dwCodFin;

	hProceso = OpenProcess ( PROCESS_QUERY_INFORMATION, FALSE, (DWORD) lPID );
	if ( ES_VALIDO ( hProceso ) )
	{
		if ( GetExitCodeProcess ( hProceso, (LPDWORD) &dwCodFin ) != 0 )
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
			// PENDIENTE:
			iRes = 0;
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
			// PENDIENTE:
			lRes = -1;
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
	if ( ES_VALIDO ( hProceso ) )
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
	// PENDIENTE:
	ulRes = 0;
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
	if ( ES_VALIDO ( hProceso ) )
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
	// PENDIENTE:
	ulRes = 0;
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
	if ( ES_VALIDO ( hProceso ) )
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
	// PENDIENTE:
	ulRes = 0;
# endif
	return ( ulRes );
}

/*
#if ( defined ( LLONG ) )
llong SisProcesoHoraCreacion ( long lPID )
{
	llong		llRes;
# if ( defined ( WIN ) )
	FILETIME	ftimCreacion;
	FILETIME	ftimFinalizacion;
	FILETIME	ftimSistema;
	FILETIME	ftimUsuario;
	SYSTEMTIME	systimValor;
	HANDLE		hProceso;
		
	hProceso = OpenProcess ( PROCESS_QUERY_INFORMATION, FALSE, (DWORD) lPID );
	if ( ES_VALIDO ( hProceso ) )
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
#else
unsigned long SisProcesoHoraCreacion ( long lPID )
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
	if ( ES_VALIDO ( hProceso ) )
	{
		if ( GetProcessTimes ( hProceso, &ftimCreacion, &ftimFinalizacion, 
								&ftimSistema, &ftimUsuario ) != 0 )
		{
			if ( FileTimeToSystemTime ( &ftimCreacion, &systimValor ) != 0 )
			{
				ulRes = FecFormHoras ( systimValor.wYear, systimValor.wMonth, systimValor.wDay,
											systimValor.wHour, systimValor.wMinute, systimValor.wSecond );
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
	// PENDIENTE:
	ulRes = 0;
# endif
	return ( ulRes );
}
#endif
*/

int SisFinalizarProceso ( long lPID )
{
	int		iRes;

#  if ( defined ( WIN ) )
	if ( SisExisteProceso ( lPID ) == 1 )
	{
		HANDLE hProceso;
		
		hProceso = OpenProcess ( PROCESS_ALL_ACCESS, FALSE, (DWORD) lPID );
		if ( ES_VALIDO ( hProceso ) )
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


 # if ( defined ( WIN ) )
int _HiloVigilarPadre ( void * p_arg )
# else
void * _HiloVigilarPadre ( void * p_arg )
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
	SisConAsincEscribir ( "El HILO SE HA ARRANCADO\n" );

    while ( 1 )
    {
# if ( defined ( WIN ) )
		Sleep(1000);  /* milisegundos en Windows */

        if ( ES_NULO ( hPadre ) || ( WaitForSingleObject ( hPadre, 0 ) == WAIT_OBJECT_0 ) )
		{
            /* El padre ha muerto, el hijo se autotermina */
            if ( ES_VALIDO ( hPadre ) ) 
			{
				CloseHandle(hPadre);
			}
            ExitProcess(1);
        }
# else
        sleep( 1 );
	SisConAsincEscribirConFormato ( "BUCLE HILO %lu/%lu\n",  getppid (), pidPadre );
        if ( getppid () != pidPadre )
        {
			SisConAsincEscribir ( "EL PADRE HA MUERTO!!!!\n" );
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