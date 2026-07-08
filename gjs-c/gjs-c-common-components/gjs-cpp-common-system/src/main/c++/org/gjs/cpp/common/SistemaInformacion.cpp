/******************************************************************************/
/*                           SistemaInformacion.cpp                           */
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


#include "CommonSystemConfig.h"

#include "SistemaInformacion.h"

#include "SistemaTiempo.h"
#include "CContadorCiclos.h"


#	include <unistd.h>


using namespace std;

namespace org
{
	namespace gjs
	{
		namespace cpp
		{
			namespace common
			{



static string * g_p_sSisDirTemporal = NULL;





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
				else if ( osinfDatos.dwMinorVersion == 90 ) // Windows Me
				{
					iRes = SIS_WINDOWS_ME;
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
	double dRes = 0.0;

# if ( defined ( WIN ) )
	OSVERSIONINFO osinfDatos;

	if ( GetVersionEx ( &osinfDatos ) != 0 )
	{
		dMult = MatExponencialConExponenteEntero ( 0.1, NumDigitosEnteroLargoSinSigno ( (unsigned long) osinfDatos.dwMinorVersion ) );
		dRes = osinfDatos.dwMajorVersion * 1.0 + osinfDatos.dwMinorVersion * dMult;
	}
# else 
	// TODO
# endif
	return ( dRes );
}

bool SisEsDos ()
{
	return ( TipSisEsDOS ( SisTipo () ) );
}

bool SisEsWindows ()
{
	return ( TipSisEsWindows ( SisTipo () ) );
}

bool SisEsPosix ()
{
	return ( TipSisEsPosix ( SisTipo () ) );
}

bool SisEsMackintosh ()
{
	return ( TipSisEsMacKintosh ( SisTipo () ) );
}

bool SisIntegraGUI ()
{
	return ( SisEsWindows ()  );
}

bool SisPermiteBifurcarProcesos ()
{
	return ( SisEsPosix () );
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

bool SisArquitecturaProcesadorEsIntel ()
{
	return ( SisArquitecturaProcesador () == PROC_ARQ_INTEL );
}

bool SisArquitecturaProcesadorEsMIPS ()
{
	return ( SisArquitecturaProcesador () == PROC_ARQ_MIPS );
}

bool SisArquitecturaProcesadorEsAlpha ()
{
	return ( SisArquitecturaProcesador () == PROC_ARQ_ALPHA );
}

bool SisArquitecturaProcesadorEsPPC ()
{
	return ( SisArquitecturaProcesador () == PROC_ARQ_PPC );
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
	// PENDIENTE:
	iRes = PROC_DESCONOCIDO;
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

bool SisProcesadorPuedeFallarPuntoFlotante ()
{
	bool bRes = false;

# if ( defined ( WIN ) )
	if ( IsProcessorFeaturePresent ( PF_FLOATING_POINT_PRECISION_ERRATA ) != 0 )
	{
		bRes = true;
	}
# else
	// PENDIENTE:
# endif
	return ( bRes );
}

bool SisProcesadorEmulaPuntoFlotante ()
{
	bool bRes = false;

# if ( defined ( WIN ) )
	if ( IsProcessorFeaturePresent ( PF_FLOATING_POINT_EMULATED ) != 0 )
	{
		bRes = true;
	}
# else
	// PENDIENTE:
# endif
	return ( bRes );
}

bool SisProcesadorAdmiteMMX ()
{
	bool bRes = false;

# if ( defined ( WIN ) )
	if ( IsProcessorFeaturePresent ( PF_MMX_INSTRUCTIONS_AVAILABLE ) != 0 )
	{
		bRes = true;
	}
# else
	// PENDIENTE:
# endif
	return ( bRes );
}

bool SisProcesadorAdmiteInstruccionesDeBytesAlpha ()
{
	bool bRes = false;

# if ( defined ( WIN ) )
	if ( IsProcessorFeaturePresent ( PF_ALPHA_BYTE_INSTRUCTIONS ) != 0 )
	{
		bRes = true;
	}
# else
	// PENDIENTE:
# endif
	return ( bRes );
}

unsigned long SisTamPagina ()
{
	unsigned long ulRes;

# if ( defined ( WIN ) )
	SYSTEM_INFO sysinfDatos;
	
	GetSystemInfo ( &sysinfDatos );
	ulRes = (unsigned long) sysinfDatos.dwPageSize;
# else
	ulRes = (unsigned long) sysconf ( _SC_PAGESIZE );
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
	ulRes = (unsigned long) sysconf ( _SC_PAGESIZE );
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

#if ( defined ( WIN ) || defined ( DOS ) )
string * SisDirectorioSistema ()
{
	
#	 if ( defined ( WIN ) )
	unsigned int uiSize = GetWindowsDirectoryA ( nullptr, 0 ); // tamaño necesario
#	 else
	// TODO
	unsigned int uiSize = 0;
#	 endif
	std::vector<char> buffer ( size );

#	 if ( defined ( WIN ) )
	GetWindowsDirectoryA ( buffer.data (), size );
#	 else
	// PENDIENTE
#	 endif
	return ( new string ( buffer.data () ) );
}
#endif

string * SisDirectorioTemporal ()
{
#	 if ( defined ( WIN ) )
	unsigned int uiSize = GetTempPathA ( nullptr, 0 ); // tamaño necesario
	std::vector<char> buffer ( size );
	GetTempPathA ( buffer.data (), size );
	return ( new string ( buffer.data () ) );
#	 else
	return ( g_p_sSisDirTemporal );
#	 endif
}

double SisVelocidadCPU ()
{
	double				dRes = 0.0;
	CContadorCiclos 	cntcCPU = CContadorCiclos ();
	int64_t				i64Valor;
	int64_t				i64Resto;
	
	cntcCPU.Iniciar ();
	sleep(1000); 
	cntcCPU.Parar ();
	i64Valor = cntcCPU.Valor () / 100000;
	i64Resto = cntcCPU.Valor () % 100000;
    dRes = ((double) i64Valor) + 0.00001 * ((double) i64Resto);
	return ( dRes );
}

void SisInicializarDirectorios ( const char * p_cDirTemporal )
{
	SisInicializarDirectorios( string ( p_cDirTemporal ) );
}

void SisInicializarDirectorios ( const string & sDirTemporal )
{
	delete g_p_sSisDirTemporal;
	g_p_sSisDirTemporal = new string ( sDirTemporal );
	if ( !SisExisteDirectorio ( *g_p_sSisDirTemporal )  )
	{
		SisCrearDirectorio ( *g_p_sSisDirTemporal );
	}
}



void _SisLiberarVariable_g_p_sSisDirTemporal ()
{
	 delete g_p_sSisDirTemporal;
	 g_p_sSisDirTemporal = NULL;
}



			}
		}
	}
}




