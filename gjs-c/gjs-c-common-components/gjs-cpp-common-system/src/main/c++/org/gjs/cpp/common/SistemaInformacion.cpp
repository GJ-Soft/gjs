/******************************************************************************/
/*                           SistemaInformacion.cpp                           */
/*----------------------------------------------------------------------------*/
/* Librer�a:  Sistema                                                         */
/* Versi�n:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Gin�s Jim�nez S�nchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripci�n:                                                               */
/* Fichero de c�digo fuente que contiene la implementaci�n de la algunas      */
/* rutinas generales de informaci�n del sistema.                              */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/


#include "CommonSystemConfig.h"

#include "SistemaInformacion.h"

#include "SistemaTiempo.h"
#include "CContadorCiclos.h"

#include <fstream>
#include <cstdio>
#include <cstring>

/* utsname y resource ya entran por la rama POSIX de CommonSystemConfig.h, que
   es la que toma Cygwin. Se repiten aqui, que es donde se usan; el guardian de
   cada cabecera evita el doble proceso. */
#if ( ! defined ( WIN ) )
#	include <sys/utsname.h>
#	include <sys/resource.h>
#	include <sys/wait.h>
#	include <unistd.h>
#	include <fcntl.h>
#endif

/* Patron para averiguar el orden de bytes: los cuatro octetos son distintos y no
   simetricos, de modo que el valor y su inverso no coinciden. */
#define _SISTEMA_UINT_PRUEBA_BYTE_1		0x4D
#define _SISTEMA_UINT_PRUEBA_BYTE_4		0xD4
#define _SISTEMA_UINT_PRUEBA			0x4D7BB7D4

/* Intervalo de medida de SisVelocidadCPU. 100 ms bastan y no bloquean. */
#define _SISTEMA_MEDIDA_CPU_MILIS		100
#include <string>



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
	// En POSIX/Linux ( y Cygwin ) se identifica el procesador leyendo /proc/cpuinfo.
	iRes = PROC_DESCONOCIDO;
	{
		ifstream cpuinfo ( "/proc/cpuinfo" );
		if ( cpuinfo.is_open () )
		{
			string	sLinea;
			string	sVendor;
			int		iFamilia = -1;
			int		iModelo  = -1;
			bool	bFin = false;

			// Se lee solo el primer procesador ( hasta la primera linea en blanco ).
			while ( ! bFin && getline ( cpuinfo, sLinea ) )
			{
				if ( sLinea.empty () )
				{
					bFin = true;
				}
				else if ( sLinea.rfind ( "vendor_id", 0 ) == 0 )
				{
					size_t iSep = sLinea.find ( ':' );
					if ( iSep != string::npos )
					{
						sVendor = Trim ( sLinea.substr ( iSep + 1 ) );
					}
				}
				else if ( sLinea.rfind ( "cpu family", 0 ) == 0 )
				{
					size_t iSep = sLinea.find ( ':' );
					if ( iSep != string::npos )
					{
						iFamilia = (int) ToInt ( Trim ( sLinea.substr ( iSep + 1 ) ) );
					}
				}
				else if ( ( sLinea.rfind ( "model", 0 ) == 0 ) &&
						  ( sLinea.rfind ( "model name", 0 ) != 0 ) )
				{
					size_t iSep = sLinea.find ( ':' );
					if ( iSep != string::npos )
					{
						iModelo = (int) ToInt ( Trim ( sLinea.substr ( iSep + 1 ) ) );
					}
				}
			}
			cpuinfo.close ();

			if ( sVendor == "GenuineIntel" )
			{
				if ( iFamilia == 5 )
				{
					iRes = PROC_INTEL_PENTIUM;
				}
				else if ( iFamilia == 6 )
				{
					// La familia 6 abarca desde el Pentium Pro hasta los Core actuales:
					// se distinguen los antiguos por el numero de modelo; el resto son Core.
					if ( iModelo == 1 )
					{
						iRes = PROC_INTEL_PENTIUM_PRO;
					}
					else if ( ( iModelo == 3 ) || ( iModelo == 5 ) || ( iModelo == 6 ) )
					{
						iRes = PROC_INTEL_PENTIUM_II;
					}
					else if ( ( iModelo == 7 ) || ( iModelo == 8 ) ||
							  ( iModelo == 10 ) || ( iModelo == 11 ) )
					{
						iRes = PROC_INTEL_PENTIUM_III;
					}
					else
					{
						iRes = PROC_INTEL_CORE;
					}
				}
				else if ( iFamilia == 15 )
				{
					iRes = PROC_INTEL_PENTIUM_4;
				}
				else
				{
					iRes = PROC_INTEL;
				}
			}
			else if ( sVendor == "AuthenticAMD" )
			{
				iRes = ( sizeof ( void * ) == 8 ) ? PROC_AMD_64 : PROC_AMD;
			}
		}
	}

	// Reserva si /proc/cpuinfo no existe o no identifico el procesador ( otro POSIX ).
	if ( iRes == PROC_DESCONOCIDO )
	{
# if ( defined ( __aarch64__ ) )
		iRes = PROC_ARM64;
# elif ( defined ( __arm__ ) )
		iRes = PROC_ARM;
# else
		int iArq = SisArquitecturaProcesador ();
		if ( iArq == PROC_ARQ_INTEL )
		{
			iRes = ( sizeof ( void * ) == 8 ) ? PROC_X86_64 : PROC_X86;
		}
		else if ( iArq == PROC_ARQ_MIPS )
		{
			iRes = PROC_MIPS_R4000;
		}
		else if ( iArq == PROC_ARQ_ALPHA )
		{
			iRes = PROC_ALPHA_21164;
		}
		else if ( iArq == PROC_ARQ_PPC )
		{
			iRes = PROC_PPC_620;
		}
# endif
	}
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
	long lNumProcs = sysconf ( _SC_NPROCESSORS_ONLN );
	iRes = ( lNumProcs > 0 ) ? (int) lNumProcs : 1;
# endif
	return ( iRes );
}

# if ( ! defined ( WIN ) )

/******************************************************************************/
/* Lectura de /proc/cpuinfo                                                   */
/*----------------------------------------------------------------------------*/
/* Las preguntas sobre las capacidades del procesador se contestan con         */
/* /proc/cpuinfo, que Linux y Cygwin traen con el mismo formato ( comprobado   */
/* el 2026-09-18 ). Se usa eso y no __builtin_cpu_supports para que valga      */
/* igual fuera de x86: en otro procesador las banderas simplemente no estan,   */
/* que es la respuesta correcta.                                              */
/******************************************************************************/

#define SIS_INFO_FIC_CPU			"/proc/cpuinfo"
#define SIS_INFO_FIC_DIR_MIN		"/proc/sys/vm/mmap_min_addr"
#define SIS_INFO_VAR_TEMPORAL		"TMPDIR"

/* Tres respuestas, no dos: NO_ESTA cuando el campo no aparece en cpuinfo. */
enum class CampoCpu { NO_ESTA, QUE_NO, QUE_SI };


/* Valor del campo "nombre : valor" de /proc/cpuinfo, o cadena vacia si el
   campo no esta. Solo mira el primer procesador: las capacidades son las
   mismas en todos. */
static string _SisCpuInfoCampo ( const string & sCampo )
{
	string		sRes;
	ifstream	ficCpu ( SIS_INFO_FIC_CPU );
	string		sLinea;

	while ( sRes.empty () && getline ( ficCpu, sLinea ) )
	{
		if ( sLinea.compare ( 0, sCampo.size (), sCampo ) == 0 )
		{
			size_t uPos = sLinea.find_first_not_of ( " \t", sCampo.size () );

			/* Detras del nombre solo puede venir relleno y los dos puntos: asi
			   "fpu" no casa con "fpu_exception". */
			if ( ( uPos != string::npos ) && ( sLinea [ uPos ] == ':' ) )
			{
				size_t uValor = sLinea.find_first_not_of ( " \t", uPos + 1 );

				if ( uValor != string::npos )
				{
					sRes = sLinea.substr ( uValor );
				}
			}
		}
	}
	return ( sRes );
}

static CampoCpu _SisCpuInfoSiNo ( const string & sCampo )
{
	CampoCpu	cpuRes;
	string		sValor = _SisCpuInfoCampo ( sCampo );

	if ( sValor.empty () )
	{
		cpuRes = CampoCpu::NO_ESTA;
	}
	else if ( sValor == "yes" )
	{
		cpuRes = CampoCpu::QUE_SI;
	}
	else
	{
		cpuRes = CampoCpu::QUE_NO;
	}
	return ( cpuRes );
}

/* Cierto si la linea "flags" trae esa bandera. Se compara la palabra entera,
   que si no "sse" casaria dentro de "sse2". */
static bool _SisCpuTieneBandera ( const string & sBandera )
{
	bool			bRes = false;
	istringstream	issFlags ( _SisCpuInfoCampo ( "flags" ) );
	string			sTrozo;

	while ( ! bRes && ( issFlags >> sTrozo ) )
	{
		if ( sTrozo == sBandera )
		{
			bRes = true;
		}
	}
	return ( bRes );
}

# endif


bool SisProcesadorPuedeFallarPuntoFlotante ()
{
	bool bRes = false;

# if ( defined ( WIN ) )
	if ( IsProcessorFeaturePresent ( PF_FLOATING_POINT_PRECISION_ERRATA ) != 0 )
	{
		bRes = true;
	}
# else
	/* Lo que pregunta la version de Windows con PF_FLOATING_POINT_PRECISION_ERRATA
	   es el fallo de division del Pentium del 94. En POSIX eso tiene nombre
	   propio en /proc/cpuinfo: el campo fdiv_bug. Solo aparece en los
	   procesadores afectados, asi que si no esta la respuesta es que no. */
	bRes = ( _SisCpuInfoSiNo ( "fdiv_bug" ) == CampoCpu::QUE_SI );
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
	/* Emular el punto flotante es lo que hace el sistema cuando NO hay unidad
	   de coma flotante. En /proc/cpuinfo eso es el campo fpu. Ojo con el caso
	   de que el campo no este: eso no es un "no hay fpu", es que no se sabe, y
	   entonces no se puede afirmar que se emule. */
	bRes = ( _SisCpuInfoSiNo ( "fpu" ) == CampoCpu::QUE_NO );
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
	bRes = _SisCpuTieneBandera ( "mmx" );
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
	/* BWX, las instrucciones de byte y palabra que los primeros Alpha no
	   tenian. Fuera del Alpha esto no es un pendiente: la respuesta es que no,
	   y es la correcta. Se comprueba la arquitectura para dejarlo dicho en el
	   codigo y no en un comentario: si algun dia se compila para Alpha, esta
	   rama es la que habra que rellenar. */
	if ( SisArquitecturaProcesador () == PROC_ARQ_ALPHA )
	{
		bRes = _SisCpuTieneBandera ( "bwx" );
	}
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
	/* POSIX no tiene un GetSystemInfo que diga el rango util del espacio de
	   direcciones. Linux publica el limite de abajo en
	   /proc/sys/vm/mmap_min_addr; Cygwin NO trae ese fichero ( comprobado ), y
	   ahi se usa el mismo valor que Memoria.h da por bueno, que responde a esta
	   misma pregunta y ya esta afinado por arquitectura. */
	unsigned long	ulMinimo = 0;
	ifstream		ficMin ( SIS_INFO_FIC_DIR_MIN );

	p_vRes = ( void * ) ( size_t ) MEM_LIM_INF;
	if ( ficMin.is_open () )
	{
		if ( ficMin >> ulMinimo )
		{
			p_vRes = ( void * ) ( size_t ) ulMinimo;
		}
	}
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
	/* Por arriba no hay nada que leer: el limite es el final del espacio de
	   usuario, que depende de la arquitectura y no del sistema en marcha. Es
	   justo el valor que Memoria.h usa para decidir si un puntero es creible,
	   asi que se toma de ahi y no se inventa otro. */
	p_vRes = ( void * ) ( size_t ) MEM_LIM_SUP;
# endif
	return ( p_vRes );
}

#if ( defined ( WIN ) )
string * SisDirectorioSistema ()
{
	string * p_sRes = NULL;
	
	/* La funcion entera esta dentro de un #if defined ( WIN ), asi que las
	   ramas de no-WIN que habia aqui dentro eran codigo muerto: nunca se
	   compilaban, y sus marcas engordaban la lista de pendientes de POSIX sin
	   ser pendientes de nada. */
	unsigned int uiSize = GetWindowsDirectoryA ( nullptr, 0 );	// tamano necesario
	std::vector<char> buffer ( uiSize );

	if ( GetWindowsDirectoryA ( (LPTSTR) buffer.data (), (UINT) uiSize ) > 0 )
	{
		p_sRes = new string ( buffer.data () );
	}
	return ( p_sRes );
}
#endif

string * SisDirectorioTemporal ()
{
	string * p_sRes = NULL;
	
# if ( defined ( WIN ) )
	std::vector<char> buffer ( MAXPATHLEN );
	if ( GetTempPath ( (DWORD) buffer.size (), (LPTSTR)  buffer.data () ) > 0 )
	{
		p_sRes = new string ( buffer.data () );
	}
#else
	/* Si alguien fijo el temporal a mano con el setter, manda ese. Si no, el
	   convenio de POSIX: la variable TMPDIR si esta puesta, y si no el temporal
	   por defecto. P_tmpdir lo define <cstdio> y ya vale "/tmp" tanto en Linux
	   como en Cygwin ( comprobado ), asi que no hace falta cablear la ruta.
	   Esto NO estaba marcado como pendiente, pero era el mismo hueco que la
	   version de C y se arregla a la vez para no dejar los dos stacks
	   diciendo cosas distintas. */
	if ( ES_VALIDO ( g_p_sSisDirTemporal ) )
	{
		p_sRes = new string ( *g_p_sSisDirTemporal );
	}
	else
	{
		const char * p_cValor = getenv ( SIS_INFO_VAR_TEMPORAL );

		if ( ( p_cValor != NULL ) && ( p_cValor [ 0 ] != '\0' ) )
		{
			p_sRes = new string ( p_cValor );
		}
		else
		{
			p_sRes = new string ( P_tmpdir );
		}
	}
#endif
	return ( p_sRes );
}


/* Nombre interno del sistema, el sysname de uname: "Linux",
   "CYGWIN_NT-10.0-26100"... En Windows nativo no hay equivalente -uname no existe
   y las APIs de version dan el nombre comercial, no la familia-, asi que se
   devuelve la constante, que es lo que buscan SisEsWindows y compania.
   Devuelve const char * y no string *, como los directorios de este mismo
   fichero: aquello es memoria que el llamante libera, y esto un estatico que no
   se libera nunca. Asi queda ademas igual que la version de C. */
const char * SisSistema ()
{
	static char cNombre [ 96 ] = "";

	if ( cNombre [ 0 ] == 0 )
	{
#	  if ( defined ( WIN ) )
		snprintf ( cNombre, sizeof ( cNombre ), "%s", "Windows" );
#	  else
		struct utsname	utsnInfo;

		if ( uname ( &utsnInfo ) == 0 )
		{
			snprintf ( cNombre, sizeof ( cNombre ), "%s", utsnInfo.sysname );
		}
		else
		{
			snprintf ( cNombre, sizeof ( cNombre ), "%s", "Desconocido" );
		}
#	  endif
	}
	return ( cNombre );
}

/* Version interna del sistema, el campo release de uname. En Windows nativo
   devuelve NULL: lo que dan alli las APIs es la version comercial, que no es lo
   mismo y ademas miente sin manifiesto de compatibilidad. */
const char * SisVersion ()
{
#  if ( defined ( WIN ) )
	return ( NULL );
#  else
	static char		cVersion [ 96 ] = "";
	struct utsname	utsnInfo;

	if ( cVersion [ 0 ] == 0 )
	{
		if ( uname ( &utsnInfo ) == 0 )
		{
			snprintf ( cVersion, sizeof ( cVersion ), "%s", utsnInfo.release );
		}
	}
	return ( cVersion [ 0 ] == 0 ? NULL : cVersion );
#  endif
}

/* Bytes de una palabra: el ancho de un puntero, que es lo que decide si los
   punteros de este proceso caben en 4 u 8 bytes. No hace falta ninguna API ni
   ramas por plataforma; lo resuelve el compilador.
   OJO con lo que NO es: no es la arquitectura de la maquina. Un proceso de 32
   bits sobre un Windows de 64 devuelve 4, que es la respuesta correcta para quien
   pregunta por sus punteros. */
int SisTamPalabraMemoria ()
{
	return ( (int) sizeof ( void * ) );
}

bool SisEsArquitectura64Bits ()
{
	return ( SisTamPalabraMemoria () == 8 );
}

bool SisEsArquitectura32Bits ()
{
	return ( SisTamPalabraMemoria () == 4 );
}

/* Orden de bytes: 0 si el menos significativo va primero (Intel y compania), 1 si
   va el mas significativo, -1 si no es ninguno de los dos (ordenes mixtos tipo
   PDP). Se resuelve con una union, sin tocar el disco. */
static int _SisObtenerOrdenBytes ()
{
	int				iOrdenBytes;
	unsigned int	uiValor = (unsigned int) _SISTEMA_UINT_PRUEBA;
	unsigned char	ucBytes [ sizeof ( unsigned int ) ];

	// memcpy y no un union: en C++ leer un miembro del union que no es el
	// ultimo escrito es comportamiento indefinido.
	std::memcpy ( ucBytes, &uiValor, sizeof ( uiValor ) );
	if ( ucBytes [ 0 ] == _SISTEMA_UINT_PRUEBA_BYTE_4 )
	{
		iOrdenBytes = 0;
	}
	else if ( ucBytes [ 0 ] == _SISTEMA_UINT_PRUEBA_BYTE_1 )
	{
		iOrdenBytes = 1;
	}
	else
	{
		iOrdenBytes = -1;
	}
	return ( iOrdenBytes );
}

int SisOrdenBytes ()
{
	return ( _SisObtenerOrdenBytes () );
}

bool SisOrdenBytesEsNormal ()
{
	return ( _SisObtenerOrdenBytes () == 0 );
}

bool SisOrdenBytesEsInvertido ()
{
	return ( _SisObtenerOrdenBytes () == 1 );
}

/* getrlimit es POSIX, no de Windows. Y RLIMIT_NPROC no es estandar -no existe en
   Cygwin, solo en Linux y BSD-, asi que aqui va sysconf, que si lo es. */
long SisMaxNumProcesosPorUsuario ()
{
	long	lRes;

#	if ( defined ( POSIX ) )
	lRes = sysconf ( _SC_CHILD_MAX );
#	else
	// En Windows no hay limite por usuario que consultar.
	lRes = LONG_MAX;
#	endif
	return ( lRes );
}

bool SisAdmiteSubprocesos ()
{
	bool bRes;

#	if ( defined ( WIN ) )
	// No existe algo parecido a un fork, pero se supone que la creacion de
	// subprocesos funciona.
	bRes = true;
#	else
	pid_t	pidProc;

	bRes = false;
	pidProc = fork ();
	if ( pidProc > 0 )
	{
		// Sin el waitpid el hijo queda de zombi hasta que termine el proceso.
		waitpid ( pidProc, NULL, 0 );
		bRes = true;
	}
	else if ( pidProc == 0 )
	{
		_exit ( 0 );
	}
#	endif
	return ( bRes );
}

# if ( defined ( POSIX ) )
/* getrlimit dice "sin limite" con RLIM_INFINITY, que es el mayor valor de
   rlim_t. Pasarlo a long con un cast daba -1, o sea el MISMO valor que se usa
   para "no se sabe". Y no es un caso raro: medido el 2026-09-19, RLIMIT_CPU y
   RLIMIT_FSIZE valen RLIM_INFINITY en cualquier Linux o Cygwin recien
   arrancado, con lo que esas dos funciones contestaban "error" en el caso
   normal. Se traduce a LONG_MAX, que es lo que ya devuelve la rama de Windows
   cuando no hay limite que consultar. */
static long _SisLimiteALong ( rlim_t rlimValor )
{
	long	lRes;

	if ( rlimValor == RLIM_INFINITY )
	{
		lRes = LONG_MAX;
	}
	else if ( rlimValor > ( rlim_t ) LONG_MAX )
	{
		lRes = LONG_MAX;
	}
	else
	{
		lRes = ( long ) rlimValor;
	}
	return ( lRes );
}
# endif

long SisMaxTamFicheroProceso ()
{
	long			lRes;
#	if ( defined ( POSIX ) )
	struct rlimit	rlimInfo;

	if ( getrlimit ( RLIMIT_FSIZE, &rlimInfo ) == 0 )
	{
		lRes = _SisLimiteALong ( rlimInfo.rlim_cur );
	}
	else
	{
		lRes = -1;
	}
#	else
	// En Windows el limite lo pone el sistema de ficheros.
	lRes = LONG_MAX;
#	endif
	return ( lRes );
}

/* RLIMIT_CPU, no RLIMIT_SPU: esa constante no existe en ninguna parte. */
long SisMaxTiempoCPUProceso ()
{
	long			lRes;
#	if ( defined ( POSIX ) )
	struct rlimit	rlimInfo;

	if ( getrlimit ( RLIMIT_CPU, &rlimInfo ) == 0 )
	{
		lRes = _SisLimiteALong ( rlimInfo.rlim_cur );
	}
	else
	{
		lRes = -1;
	}
#	else
	// Windows no limita el tiempo de CPU por proceso.
	lRes = LONG_MAX;
#	endif
	return ( lRes );
}

long SisDescriptoresESTotalesProceso ()
{
	long			lRes;
#	if ( defined ( POSIX ) )
	struct rlimit	rlimInfo;

	if ( getrlimit ( RLIMIT_NOFILE, &rlimInfo ) == 0 )
	{
		lRes = _SisLimiteALong ( rlimInfo.rlim_cur );
	}
	else
	{
		lRes = -1;
	}
#	else
	/* El equivalente de RLIMIT_NOFILE en Windows es el limite de la tabla de
	   descriptores de la CRT: 512 por defecto, ampliable a 8192 con
	   _setmaxstdio. NO se usa GetProcessHandleCount, que seria lo que suena:
	   ese cuenta los manejadores del NUCLEO —ficheros, eventos, hilos, claves
	   del registro...— y da otra cosa. Medido en un programa que no habia
	   abierto nada: 61 manejadores de nucleo frente a 3 descriptores. */
	lRes = ( long ) _getmaxstdio ();
#	endif
	return ( lRes );
}

/* Los descriptores realmente abiertos, no el limite. Se cuentan probando cada uno
   con fcntl, que es POSIX y no depende de /proc; recorrer hasta el limite es
   barato porque son unos pocos miles. */
long SisDescriptoresESUtilizadosProceso ()
{
	long	lRes;
#	if ( defined ( POSIX ) )
	long	lLimite;
	long	lDesc;

	lLimite = SisDescriptoresESTotalesProceso ();
	if ( lLimite < 0 )
	{
		lRes = -1;
	}
	else
	{
		lRes = 0;
		for ( lDesc = 0; lDesc < lLimite; lDesc = lDesc + 1 )
		{
			if ( fcntl ( (int) lDesc, F_GETFD ) != -1 )
			{
				lRes = lRes + 1;
			}
		}
	}
#	else
	/* Mismo recorrido que la rama POSIX, sobre la tabla de la CRT:
	   _get_osfhandle devuelve -1 en los huecos. */
	{
		int		iMax;
		int		iDesc;

		iMax = _getmaxstdio ();
		lRes = 0;
		for ( iDesc = 0; iDesc < iMax; iDesc = iDesc + 1 )
		{
			if ( _get_osfhandle ( iDesc ) != -1 )
			{
				lRes = lRes + 1;
			}
		}
	}
#	endif
	return ( lRes );
}

long SisDescriptoresESDisponiblesProceso ()
{
	long lTotales;
	long lUtilizados;
	long lRes;

	lTotales = SisDescriptoresESTotalesProceso ();
	lUtilizados = SisDescriptoresESUtilizadosProceso ();
	if ( ( lTotales >= 0 ) && ( lUtilizados >= 0 ) )
	{
		lRes = lTotales - lUtilizados;
	}
	else
	{
		lRes = -1;
	}
	return ( lRes );
}

/* Velocidad en MHz.
   Antes dividia los ciclos entre 100000, que no da MHz ni GHz sino unidades de
   100 kHz: para una CPU de 3 GHz devolvia 30000. Y el rodeo de division entera
   mas resto equivalia exactamente a dividir entre 100000.0, porque 0.00001 es
   1/100000; no hacia falta, un uint64 de miles de millones cabe exacto en la
   mantisa de 53 bits de un double.
   Se mide el intervalo REAL con el reloj monotono en vez de dar por hecho que la
   espera dura lo pedido, que ningun sistema garantiza. Bastan 100 ms.
   OJO con lo que mide: en todo x86 moderno el contador de ciclos es invariante,
   avanza a la frecuencia nominal con independencia de a que velocidad este
   corriendo el nucleo. Esto devuelve por tanto la frecuencia NOMINAL, no la
   instantanea, y no refleja el turbo ni el reposo. */
double SisVelocidadCPU ()
{
	double				dRes = 0.0;
	CContadorCiclos		cntcCPU = CContadorCiclos ();
	uint64_t			ui64Ciclos;
	struct timespec		tspIni;
	struct timespec		tspFin;
	double				dSegundos;

	clock_gettime ( CLOCK_MONOTONIC, &tspIni );
	cntcCPU.Iniciar ();
	SisEsperar ( _SISTEMA_MEDIDA_CPU_MILIS );
	cntcCPU.Parar ();
	clock_gettime ( CLOCK_MONOTONIC, &tspFin );
	ui64Ciclos = cntcCPU.Valor ();

	dSegundos = ( (double) ( tspFin.tv_sec - tspIni.tv_sec ) ) +
				( (double) ( tspFin.tv_nsec - tspIni.tv_nsec ) ) / 1000000000.0;
	if ( dSegundos > 0.0 )
	{
		dRes = ( (double) ui64Ciclos ) / ( dSegundos * 1000000.0 );
	}
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




