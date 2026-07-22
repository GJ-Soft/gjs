/*                           SistemaInformacion.c	                          */
/*----------------------------------------------------------------------------*/
/* Librería:  Sistema                                                         */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de código fuente que contiene la implementación de la algunas      */
/* rutinas generales de información del sistema.                              */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/



#include "SistemaInformacion.h"

#include "SistemaTiempo.h"
#include "SContadorCiclos.h"
#include "TiposSistema.h"

#include "SistemaConfig.h"



char * _g_p_cSisDirTemporal = NULL;


int SisTipo ()
{
	int iRes;

# if ( defined ( WIN ) )
	iRes = TIP_SIS_WINDOWS;
# elif ( defined ( POSIX ) )
	iRes = TIP_SIS_POSIX;
# elif ( defined ( MACKINTOSH ) )
	iRes = TIP_SIS_MACKINTOSH;
# else // DOS
	iRes = TIP_SIS_DOS;
# endif
	return ( iRes );
}

int SisSistema ()
{
	int iRes;

# if ( defined ( WIN ) )
	OSVERSIONINFO osinfDatos;

	if ( GetVersionEx ( &osinfDatos ) != 0 )
	{
		if ( osinfDatos.dwPlatformId == VER_PLATFORM_WIN32s ) 
		{
			// Win32s on Windows 3.1.  
			iRes = SIS_WINDOWS_32S;
		}
		else if ( osinfDatos.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS ) 
		{
			// Win32 on Windows 95 or Windows 98. For Windows 95, dwMinorVersion is zero.
			//For Windows 98, dwMinorVersion is greater than zero. 
			if ( osinfDatos.dwMajorVersion == 4 )
			{
				if ( osinfDatos.dwMinorVersion == 0 ) 
				{
					iRes = SIS_WINDOWS_95;
				}
				else if ( osinfDatos.dwMinorVersion == 10 ) 
				{
					iRes = SIS_WINDOWS_98;
				}
				else if ( osinfDatos.dwMinorVersion == 90 ) // Windows Me
				{
					iRes = SIS_WINDOWS_ME;
				}
				else
				{
					iRes = SIS_DESCONOCIDO;
				}
			}
			else
			{
				iRes = SIS_DESCONOCIDO;
			}
		}
		else if ( osinfDatos.dwPlatformId == VER_PLATFORM_WIN32_NT ) 
		{
			// Win32 on Windows NT. 
			if ( osinfDatos.dwMajorVersion == 4 ) // The operating system is Windows NT 4.0, Windows Me, Windows 98, or Windows 95. 
			{
				if ( osinfDatos.dwMinorVersion == 0 ) 
				{
					iRes = SIS_WINDOWS_NT;
				}
				else
				{
					iRes = SIS_DESCONOCIDO;
				}
			}
			else if ( osinfDatos.dwMajorVersion == 5 ) // The operating system is Windows Server 2003 R2, Windows Server 2003, Windows XP, or Windows 2000. 
			{
				if ( osinfDatos.dwMinorVersion == 1 ) // Windows XP
				{
					iRes = SIS_WINDOWS_XP;
				}
				else if ( osinfDatos.dwMinorVersion == 2 ) // Windows Server 2003 R2, Windows Server 2003, or Windows XP Professional x64 Edition.
				{
					iRes = SIS_WINDOWS_2003;
				}
				else
				{
					iRes = SIS_DESCONOCIDO;
				}
			}
			else if ( osinfDatos.dwMajorVersion == 6 ) // The operating system is Windows Vista or Windows Server "Longhorn". 
			{
				if ( osinfDatos.dwMinorVersion == 0 ) // Windows Vista, Windows Server "Longhorn"
				{
					iRes = SIS_WINDOWS_VISTA;
				}
				else
				{
					iRes = SIS_DESCONOCIDO;
				}
			}
			else
			{
				iRes = SIS_DESCONOCIDO;
			}
		}
		else
		{
			iRes = SIS_DESCONOCIDO;
		}
 	}
	else
	{
		iRes = SIS_DESCONOCIDO;
	}
# else 
	iRes = SIS_DESCONOCIDO;
# endif
	return ( iRes );
}

double SisVersion ()
{
	double dRes;

# if ( defined ( WIN ) )
	double			dMult;
	OSVERSIONINFO	osinfDatos;

	if ( GetVersionEx ( &osinfDatos ) != 0 )
	{
		dMult = MatExponencialConExponenteEntero ( 0.1, NumDigitosEnteroLargoSinSigno ( (unsigned long) osinfDatos.dwMinorVersion ) );
		dRes = osinfDatos.dwMajorVersion * 1.0 + osinfDatos.dwMinorVersion * dMult;
	}
	else
	{
		dRes = 0.0;
	}
# else 
	dRes = 0.0;
# endif
	return ( dRes );
}

int SisEsDos ()
{
	return ( TipSisEsDOS ( SisTipo () ) );
}

int SisEsWindows ()
{
	return ( TipSisEsWindows ( SisTipo () ) );
}

int SisEsPosix ()
{
	return ( TipSisEsPosix ( SisTipo () ) );
}

int SisEsMackintosh ()
{
	return ( TipSisEsMacKintosh ( SisTipo () ) );
}

int SisIntegraGUI ()
{
	int iRes;

	if ( SisEsWindows () == 1 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return (  iRes );
}

int SisPermiteBifurcarProcesos ()
{
	int iRes;

	if ( SisEsPosix () == 1 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return (  iRes );
}

int SisArquitecturaProcesador ()
{
	int iRes;

# if ( defined ( WIN ) )
	SYSTEM_INFO sysinfDatos;
	
	GetSystemInfo ( &sysinfDatos );
	if ( sysinfDatos.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL )
	{
		iRes = PROC_ARQ_INTEL;
	}
	else if ( sysinfDatos.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_MIPS )
	{
		iRes = PROC_ARQ_MIPS;
	}
	else if ( sysinfDatos.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_ALPHA )
	{
		iRes = PROC_ARQ_ALPHA;
	}
	else if ( sysinfDatos.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_PPC )
	{
		iRes = PROC_ARQ_PPC;
	}
	else
	{
		iRes = PROC_ARQ_DESCONOCIDO;
	}
# else
	// PENDIENTE:
	iRes = PROC_ARQ_DESCONOCIDO;
# endif
	return ( iRes );
}

int SisArquitecturaProcesadorEsIntel ()
{
	int iRes;

	if ( SisArquitecturaProcesador () == PROC_ARQ_INTEL )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SisArquitecturaProcesadorEsMIPS ()
{
	int iRes;

	if ( SisArquitecturaProcesador () == PROC_ARQ_MIPS )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SisArquitecturaProcesadorEsAlpha ()
{
	int iRes;

	if ( SisArquitecturaProcesador () == PROC_ARQ_ALPHA )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SisArquitecturaProcesadorEsPPC ()
{
	int iRes;

	if ( SisArquitecturaProcesador () == PROC_ARQ_PPC )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SisProcesador ()
{
	int iRes;

# if ( defined ( WIN ) )
	SYSTEM_INFO sysinfDatos;
	
	GetSystemInfo ( &sysinfDatos );
	if ( sysinfDatos.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL )
	{
		if ( sysinfDatos.wProcessorLevel == 3 )
		{
			iRes = PROC_INTEL_80386;
		}
		else if ( sysinfDatos.wProcessorLevel == 4 )
		{
			iRes = PROC_INTEL_80486;
		}
		else if ( sysinfDatos.wProcessorLevel == 5 )
		{
			iRes = PROC_INTEL_PENTIUM;
		}
		else
		{
			iRes = PROC_DESCONOCIDO;
		}
	}	
	else if ( sysinfDatos.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_MIPS )
	{
		if ( sysinfDatos.wProcessorLevel == 4 )
		{
			iRes = PROC_MIPS_R4000;
		}
		else
		{
			iRes = PROC_DESCONOCIDO;
		}
	}
	else if ( sysinfDatos.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_ALPHA )
	{
		if ( sysinfDatos.wProcessorLevel == 21064 )
		{
			iRes = PROC_ALPHA_21064;
		}
		else if ( sysinfDatos.wProcessorLevel == 21064 )
		{
			iRes = PROC_ALPHA_21066;
		}
		else if ( sysinfDatos.wProcessorLevel == 21164 )
		{
			iRes = PROC_ALPHA_21164;
		}
		else
		{
			iRes = PROC_DESCONOCIDO;
		}
	}
	else if ( sysinfDatos.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_PPC )
	{
		if ( sysinfDatos.wProcessorLevel == 1 )
		{
			iRes = PROC_PPC_601;
		}
		else if ( sysinfDatos.wProcessorLevel == 3 )
		{
			iRes = PROC_PPC_603;
		}
		else if ( sysinfDatos.wProcessorLevel == 4 )
		{
			iRes = PROC_PPC_604;
		}
		else if ( sysinfDatos.wProcessorLevel == 6 )
		{
			iRes = PROC_PPC_603_PLUS;
		}
		else if ( sysinfDatos.wProcessorLevel == 9 )
		{
			iRes = PROC_PPC_604_PLUS;
		}
		else if ( sysinfDatos.wProcessorLevel == 20 )
		{
			iRes = PROC_PPC_620;
		}
		else
		{
			iRes = PROC_DESCONOCIDO;
		}
	}
	else
	{
		iRes = PROC_DESCONOCIDO;
	}
# else
	// Deteccion de la arquitectura por macros del compilador ( arquitectura del
	// binario ). ARM/otros no tienen constante -> PROC_ARQ_DESCONOCIDO.
#	if ( defined ( __x86_64__ ) || defined ( __i386__ ) || defined ( __amd64__ ) )
	iRes = PROC_ARQ_INTEL;
#	elif ( defined ( __mips__ ) )
	iRes = PROC_ARQ_MIPS;
#	elif ( defined ( __alpha__ ) )
	iRes = PROC_ARQ_ALPHA;
#	elif ( defined ( __powerpc__ ) || defined ( __ppc__ ) || defined ( __PPC__ ) )
	iRes = PROC_ARQ_PPC;
#	else
	iRes = PROC_ARQ_DESCONOCIDO;
#	endif
# endif
	return ( iRes );
}

int SisNumProcesadores ()
{
	int iRes;

# if ( defined ( WIN ) )
	SYSTEM_INFO sysinfDatos;
	
	GetSystemInfo ( &sysinfDatos );
	iRes = (int) sysinfDatos.dwNumberOfProcessors;
# else
	// PENDIENTE:
	iRes = -1;
# endif
	return ( iRes );
}

int SisProcesadorPuedeFallarPuntoFlotante ()
{
	int iRes;

# if ( defined ( WIN ) )
	if ( IsProcessorFeaturePresent ( PF_FLOATING_POINT_PRECISION_ERRATA ) != 0 )
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

int SisProcesadorEmulaPuntoFlotante ()
{
	int iRes;

# if ( defined ( WIN ) )
	if ( IsProcessorFeaturePresent ( PF_FLOATING_POINT_EMULATED ) != 0 )
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

int SisProcesadorAdmiteMMX ()
{
	int iRes;

# if ( defined ( WIN ) )
	if ( IsProcessorFeaturePresent ( PF_MMX_INSTRUCTIONS_AVAILABLE ) != 0 )
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

int SisProcesadorAdmiteInstruccionesDeBytesAlpha ()
{
	int iRes;

# if ( defined ( WIN ) )
	if ( IsProcessorFeaturePresent ( PF_ALPHA_BYTE_INSTRUCTIONS ) != 0 )
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

unsigned long SisTamPagina ()
{
	unsigned long ulRes;

# if ( defined ( WIN ) )
	SYSTEM_INFO sysinfDatos;
	
	GetSystemInfo ( &sysinfDatos );
	ulRes = (unsigned long) sysinfDatos.dwPageSize;
# else
	ulRes = (unsigned long) getpagesize ();
# endif
	return ( ulRes );
}

unsigned long SisMemTamBloqueMinimo ()
{
	unsigned long ulRes;

# if ( defined ( WIN ) )
	SYSTEM_INFO sysinfDatos;
	
	GetSystemInfo ( &sysinfDatos );
	ulRes = (unsigned long) sysinfDatos.dwAllocationGranularity;
# else
	ulRes = (unsigned long) getpagesize ();
# endif
	return ( ulRes );
}

void * SisMemAplicDireccionMinima ()
{
	void * p_vRes;

# if ( defined ( WIN ) )
	SYSTEM_INFO sysinfDatos;
	
	GetSystemInfo ( &sysinfDatos );
	p_vRes = (void *) sysinfDatos.lpMinimumApplicationAddress;
# else
	// PENDIENTE:
	p_vRes = NULL;
# endif
	return ( p_vRes );
}

void * SisMemAplicDireccionMaxima ()
{
	void * p_vRes;

# if ( defined ( WIN ) )
	SYSTEM_INFO sysinfDatos;
	
	GetSystemInfo ( &sysinfDatos );
	p_vRes = (void *) sysinfDatos.lpMaximumApplicationAddress;
# else
	// PENDIENTE:
	p_vRes = NULL;
# endif
	return ( p_vRes );
}

#if ( defined ( WIN ) )
char * SisDirectorioSistema ()
{
	const char * 	p_cRes;
	SBuffer	*		p_bufDatos;
	
	p_bufDatos = SBufCrear ( SIS_SO_MAX_TAM_BUFFER );
	if ( ES_VALIDO ( p_bufDatos ) )
	{
		if ( GetWindowsDirectory ( (LPTSTR) SBufDireccion ( p_bufDatos ), (UINT) SBufTam ( p_bufDatos ) ) > 0 )
		{
			p_cRes = SBufDuplicarCadena ( p_bufDatos );
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
	return ( p_cRes );
}
#endif

char * SisDirectorioTemporal ()
{
	char * p_cRes;
#if ( defined ( WIN ) || !defined ( DOS ) )
	SBuffer	*		p_bufDatos;
#endif
	
#if ( defined ( WIN ) || !defined ( DOS ) )
	if ( ES_VALIDO ( _g_p_cSisDirTemporal ) )
	{
		p_cRes = CadDuplicar ( _g_p_cSisDirTemporal );
	}
	else
	{
		p_bufDatos = SBufCrear ( SIS_SO_MAX_TAM_BUFFER );
		if ( ES_VALIDO ( p_bufDatos ) )
		{
#		 if ( defined ( WIN ) )
			if ( GetTempPath ( (DWORD) SBufTam ( p_bufDatos ), (LPTSTR) SBufDireccion ( p_bufDatos ) ) > 0 )
#		 else
				// PENDIENTE:
			if ( 0 )
#		 endif
			{
				p_cRes = SBufDuplicarCadena ( p_bufDatos );
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
#else
	p_cRes = CadDuplicar ( _g_p_cSisDirTemporal );
#endif
	return ( p_cRes );
}

double SisVelocidadCPU ()
{
	double				dRes = 0.0;
	SContadorCiclos *	p_cntcCPU;
	int64_t				i64Valor;
	int64_t				i64Resto;
	
	p_cntcCPU = SConCicCrear ();
	SConCicIniciar ( p_cntcCPU );
# if ( defined ( WIN ) )
	Sleep(1000);
# else
	sleep ( 1 );
# endif
	SConCicParar ( p_cntcCPU );
	i64Valor = SConCicValor ( p_cntcCPU ) / 100000;
	i64Resto = SConCicValor ( p_cntcCPU ) % 100000;
    dRes = ((double) i64Valor) + 0.00001 * ((double) i64Resto);
	return ( dRes );
}

void SisInicializarDirectorios ( const char * p_cDirTemporal )
{
	MemLiberarCadena ( &_g_p_cSisDirTemporal );
	_g_p_cSisDirTemporal = CadDuplicar ( p_cDirTemporal );
	if ( SisExisteDirectorio ( _g_p_cSisDirTemporal ) == 0 )
	{
		SisCrearDirectorio ( _g_p_cSisDirTemporal );
	}
}



void _SisLiberarVariable_g_p_cSisDirTemporal ()
{
	MemLiberar ( (void **) &_g_p_cSisDirTemporal );
}


