/*****************************************************************************/
/*                          SistemaInformacion.c	                          */
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
#include "VariablesEntorno.h"

#include "SistemaConfig.h"

/* utsname ya entra por la rama POSIX de SistemaConfig.h, que es la que toma
   Cygwin. Se repite aqui, que es donde se usa; el guardian de la cabecera
   evita el doble proceso. */
#if ( ! defined ( WIN ) )
#	include <sys/utsname.h>
#endif

/* clock_gettime y CLOCK_MONOTONIC para SisVelocidadCPU. Estan en los tres
   compiladores que se usan: el de Cygwin y el cruzado de MinGW los traen. */
#include <time.h>

#define _SISTEMA_UINT_PRUEBA_BYTE_1		0x4D
#define _SISTEMA_UINT_PRUEBA_BYTE_2		0x7B
#define _SISTEMA_UINT_PRUEBA_BYTE_3		0xB7
#define _SISTEMA_UINT_PRUEBA_BYTE_4		0xD4

#define _SISTEMA_UINT_PRUEBA			0x4D7BB7D4
#define _SISTEMA_UINT_PRUEBA_INV		0xD4B77B4D

/* Intervalo de medida de SisVelocidadCPU. 100 ms bastan y no bloquean. */
#define _SISTEMA_MEDIDA_CPU_MILIS		100

#define _SISTEMA_FIC_PRUEBA				"_SSISTEMA_PRUEBA.tmp"



char * _g_p_cSisDirTemporal = NULL;


static int _SisObtenerOrdenBytes ();
static int _SisVerificarSubprocesos ();


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

/* Nombre interno del sistema, el que da uname en su campo sysname: "Linux",
   "CYGWIN_NT-10.0-26100"... En Windows nativo no hay equivalente -uname no
   existe y las APIs de version dan el nombre comercial, no la familia-, asi
   que se devuelve la constante, que es lo que buscan SisEsWindows y compania.
   La cadena la conserva un estatico: el llamante no la libera. */
const char * SisSistema ()
{
	static char cNombre [ 96 ] = "";

	if ( cNombre [ 0 ] == '\0' )
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

/* Version interna del sistema, el campo release de uname: "3.6.10-1.x86_64",
   "6.8.0-45-generic"... En Windows nativo devuelve NULL: lo que dan alli las
   APIs es la version comercial, que no es lo mismo y ademas miente sin
   manifiesto de compatibilidad. El llamante tiene que contar con el NULL. */
const char * SisVersion ()
{
#  if ( defined ( WIN ) )
	return ( NULL );
#  else
	static char		cVersion [ 96 ] = "";
	struct utsname	utsnInfo;

	if ( cVersion [ 0 ] == '\0' )
	{
		if ( uname ( &utsnInfo ) == 0 )
		{
			snprintf ( cVersion, sizeof ( cVersion ), "%s", utsnInfo.release );
		}
	}
	return ( cVersion [ 0 ] == '\0' ? NULL : cVersion );
#  endif
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

# if ( ! defined ( WIN ) )

/******************************************************************************/
/* Lectura de /proc/cpuinfo                                                   */
/*----------------------------------------------------------------------------*/
/* Las preguntas sobre las capacidades del procesador se contestan con         */
/* /proc/cpuinfo, que Linux y Cygwin traen con el mismo formato ( comprobado   */
/* el 2026-09-18 ).                                                           */
/*                                                                            */
/* Se usa eso y NO __builtin_cpu_supports, que seria lo evidente, por dos      */
/* razones: solo existe en x86, y desde aqui no hay forma de saber si se esta  */
/* en x86, porque el BaseConfig.h del stack C define __i386__ a mano en        */
/* cualquier POSIX y ese macro deja de servir para preguntarlo. Con cpuinfo no */
/* hay ese problema: en un procesador que no sea x86 las banderas simplemente  */
/* no estan, que es la respuesta correcta.                                    */
/******************************************************************************/

#define SIS_INFO_FIC_CPU			"/proc/cpuinfo"
#define SIS_INFO_FIC_DIR_MIN		"/proc/sys/vm/mmap_min_addr"
#define SIS_INFO_TAM_LINEA			2048
#define SIS_INFO_VAR_TEMPORAL		"TMPDIR"

/* Tres respuestas, no dos: -1 si el campo no esta en cpuinfo. */
#define SIS_INFO_NO_ESTA			-1
#define SIS_INFO_QUE_NO				0
#define SIS_INFO_QUE_SI				1


/* Valor del campo "nombre : valor" de /proc/cpuinfo, duplicado ( hay que
   liberarlo ), o NULL si el campo no esta. Solo mira el primer procesador,
   que es lo que interesa: las capacidades son las mismas en todos. */
static char * _SisCpuInfoCampo ( const char * p_cCampo )
{
	char *		p_cRes;
	FILE *		p_filCpu;
	char		cLinea [ SIS_INFO_TAM_LINEA ];
	size_t		uLongCampo;
	char *		p_cDosPuntos;
	char *		p_cValor;
	char *		p_cFinal;

	p_cRes = NULL;
	uLongCampo = strlen ( p_cCampo );
	p_filCpu = fopen ( SIS_INFO_FIC_CPU, "r" );
	if ( p_filCpu != NULL )
	{
		while ( ( ES_NULO ( p_cRes ) ) && ( fgets ( cLinea, sizeof ( cLinea ), p_filCpu ) != NULL ) )
		{
			if ( strncmp ( cLinea, p_cCampo, uLongCampo ) == 0 )
			{
				/* Detras del nombre solo puede venir relleno y los dos puntos:
				   asi "fpu" no casa con "fpu_exception". */
				p_cDosPuntos = cLinea + uLongCampo;
				while ( ( *p_cDosPuntos == ' ' ) || ( *p_cDosPuntos == ASCII_TAB ) )
				{
					p_cDosPuntos = p_cDosPuntos + 1;
				}
				if ( *p_cDosPuntos == ':' )
				{
					p_cValor = p_cDosPuntos + 1;
					while ( ( *p_cValor == ' ' ) || ( *p_cValor == ASCII_TAB ) )
					{
						p_cValor = p_cValor + 1;
					}
					p_cFinal = strchr ( p_cValor, ASCII_LF );
					if ( p_cFinal != NULL )
					{
						*p_cFinal = ASCII_NUL;
					}
					p_cRes = CadDuplicar ( p_cValor );
				}
			}
		}
		fclose ( p_filCpu );
	}
	return ( p_cRes );
}

/* SIS_INFO_QUE_SI, SIS_INFO_QUE_NO o SIS_INFO_NO_ESTA. La diferencia importa:
   que un campo no aparezca no siempre significa lo mismo que un "no". */
static int _SisCpuInfoSiNo ( const char * p_cCampo )
{
	int		iRes;
	char *	p_cValor;

	p_cValor = _SisCpuInfoCampo ( p_cCampo );
	if ( ES_VALIDO ( p_cValor ) )
	{
		if ( CadComparar ( p_cValor, "yes" ) == COMP_IGUAL )
		{
			iRes = SIS_INFO_QUE_SI;
		}
		else
		{
			iRes = SIS_INFO_QUE_NO;
		}
		MemLiberar ( (void **) &p_cValor );
	}
	else
	{
		iRes = SIS_INFO_NO_ESTA;
	}
	return ( iRes );
}

/* Cierto si la linea "flags" del procesador trae esa bandera. Se compara la
   palabra entera, que si no "sse" casaria dentro de "sse2". */
static int _SisCpuTieneBandera ( const char * p_cBandera )
{
	int			iRes;
	char *		p_cFlags;
	char *		p_cTrozo;
	size_t		uLongitud;

	iRes = 0;
	p_cFlags = _SisCpuInfoCampo ( "flags" );
	if ( ES_VALIDO ( p_cFlags ) )
	{
		uLongitud = strlen ( p_cBandera );
		p_cTrozo = strstr ( p_cFlags, p_cBandera );
		while ( ( p_cTrozo != NULL ) && ( iRes == 0 ) )
		{
			if ( ( p_cTrozo == p_cFlags ) || ( *( p_cTrozo - 1 ) == ' ' ) )
			{
				if ( ( p_cTrozo [ uLongitud ] == ' ' ) || ( p_cTrozo [ uLongitud ] == ASCII_NUL ) )
				{
					iRes = 1;
				}
			}
			p_cTrozo = strstr ( p_cTrozo + 1, p_cBandera );
		}
		MemLiberar ( (void **) &p_cFlags );
	}
	return ( iRes );
}

# endif


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
	else if ( sysinfDatos.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64 )
	{
		/* x64 es la misma familia que x86, y sin esta rama cualquier Windows de
		   64 bits ( o sea, todos ) contestaba DESCONOCIDO y
		   SisArquitecturaProcesadorEsIntel decia que no. */
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
	/* De uname, que es lo que hay en POSIX. El campo machine trae el nombre de
	   la arquitectura ( x86_64, i686, aarch64, mips... ) y se compara por el
	   principio, que las variantes son sufijos ( mips64, ppc64le... ). */
	static const struct
	{
		const char *	p_cPrefijo;
		int				iArquitectura;
	} arqConocidas [] =
	{
		{ "x86_64",		PROC_ARQ_INTEL },
		{ "amd64",		PROC_ARQ_INTEL },
		{ "i386",		PROC_ARQ_INTEL },
		{ "i486",		PROC_ARQ_INTEL },
		{ "i586",		PROC_ARQ_INTEL },
		{ "i686",		PROC_ARQ_INTEL },
		{ "mips",		PROC_ARQ_MIPS },
		{ "alpha",		PROC_ARQ_ALPHA },
		{ "ppc",		PROC_ARQ_PPC },
		{ "powerpc",	PROC_ARQ_PPC }
	};
	struct utsname	utsDatos;
	unsigned		uIdx;

	iRes = PROC_ARQ_DESCONOCIDO;
	if ( uname ( &utsDatos ) == 0 )
	{
		for ( uIdx = 0; uIdx < ( sizeof ( arqConocidas ) / sizeof ( arqConocidas [ 0 ] ) ); uIdx++ )
		{
			if ( strncmp ( utsDatos.machine, arqConocidas [ uIdx ].p_cPrefijo,
						   strlen ( arqConocidas [ uIdx ].p_cPrefijo ) ) == 0 )
			{
				iRes = arqConocidas [ uIdx ].iArquitectura;
				break;
			}
		}
	}
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
	/* Portado del stack C++, que ya lo tenia resuelto. */
	long lNumProcs = sysconf ( _SC_NPROCESSORS_ONLN );

	if ( lNumProcs > 0 )
	{
		iRes = (int) lNumProcs;
	}
	else
	{
		iRes = 1;
	}
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
	/* Lo que pregunta la version de Windows con PF_FLOATING_POINT_PRECISION_ERRATA
	   es el fallo de division del Pentium del 94. En POSIX eso tiene nombre
	   propio en /proc/cpuinfo: el campo fdiv_bug. Solo aparece en los
	   procesadores afectados, asi que si no esta la respuesta es que no. */
	if ( _SisCpuInfoSiNo ( "fdiv_bug" ) == SIS_INFO_QUE_SI )
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
	/* Emular el punto flotante es lo que hace el sistema cuando NO hay unidad
	   de coma flotante. En /proc/cpuinfo eso es el campo fpu. Ojo con el caso
	   de que el campo no este: eso no es un "no hay fpu", es que no se sabe, y
	   entonces no se puede afirmar que se emule. */
	if ( _SisCpuInfoSiNo ( "fpu" ) == SIS_INFO_QUE_NO )
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
	iRes = _SisCpuTieneBandera ( "mmx" );
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
	/* BWX, las instrucciones de byte y palabra que los primeros Alpha no
	   tenian. Fuera del Alpha esto no es un pendiente: la respuesta es que no,
	   y es la correcta. Se comprueba la arquitectura para dejarlo dicho en el
	   codigo y no en un comentario: si algun dia se compila para Alpha, esta
	   rama es la que habra que rellenar leyendo las extensiones que Linux
	   publica ahi en el campo "platform string" de /proc/cpuinfo. */
	if ( SisArquitecturaProcesador () == PROC_ARQ_ALPHA )
	{
		iRes = _SisCpuTieneBandera ( "bwx" );
	}
	else
	{
		iRes = 0;
	}
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
	/* POSIX no tiene un GetSystemInfo que diga el rango util del espacio de
	   direcciones. Linux publica el limite de abajo en
	   /proc/sys/vm/mmap_min_addr; Cygwin NO trae ese fichero ( comprobado ), y
	   ahi se usa el mismo valor que Memoria.h da por bueno, que responde a esta
	   misma pregunta y ya esta afinado por arquitectura. */
	FILE *			p_filMin;
	unsigned long	ulMinimo;

	p_vRes = (void *) (size_t) MEM_LIM_INF;
	p_filMin = fopen ( SIS_INFO_FIC_DIR_MIN, "r" );
	if ( p_filMin != NULL )
	{
		if ( fscanf ( p_filMin, "%lu", &ulMinimo ) == 1 )
		{
			p_vRes = (void *) (size_t) ulMinimo;
		}
		fclose ( p_filMin );
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
	p_vRes = (void *) (size_t) MEM_LIM_SUP;
# endif
	return ( p_vRes );
}

/* Bytes de una palabra: el ancho de un puntero, que es lo que decide si los
   punteros de este proceso caben en 4 u 8 bytes. No hace falta ninguna API
   ni ramas por plataforma; lo resuelve el compilador.
   OJO con lo que NO es: no es la arquitectura de la maquina. Un proceso de 32
   bits sobre un Windows de 64 devuelve 4, que es la respuesta correcta para
   quien pregunta por sus punteros. Para el ancho de la maquina haria falta
   GetNativeSystemInfo en Windows y el campo machine de uname en POSIX. */
int SisTamPalabraMemoria ()
{
	return ( (int) sizeof ( void * ) );
}

int SisEsArquitectura64Bits ()
{
	int iRes;

	if ( SisTamPalabraMemoria () == 8 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SisEsArquitectura32Bits ()
{
	int iRes;

	if ( SisTamPalabraMemoria () == 4 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SisOrdenBytes ()
{
	return ( _SisObtenerOrdenBytes () );
}

int SisOrdenBytesEsNormal ()
{
	int iRes;
	
	if ( SisOrdenBytes () == 0 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SisOrdenBytesEsInvertido ()
{
	int iRes;
	
	if ( SisOrdenBytes () == 1 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


#if ( defined ( WIN ) )
char * SisDirectorioSistema ()
{
	char * 		p_cRes;
	SBuffer	*	p_bufDatos;
	
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
#if ( !defined ( WIN ) && !defined ( DOS ) )
	char *			p_cValor;
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
			{
				p_cRes = SBufDuplicarCadena ( p_bufDatos );
			}
			else
			{
				p_cRes = NULL;
			}
#		 else
			/* El convenio de POSIX: la variable TMPDIR si esta puesta, y si no
			   el temporal por defecto. P_tmpdir lo define <stdio.h> y ya vale
			   "/tmp" tanto en Linux como en Cygwin ( comprobado ), asi que no
			   hace falta cablear la ruta aqui. El buffer no se usa en esta
			   rama, pero se deja creado y destruido igual para no partir la
			   estructura de la funcion. */
			p_cValor = VarEntObtValor ( SIS_INFO_VAR_TEMPORAL );
			if ( ES_VALIDO ( p_cValor ) )
			{
				if ( CadLongitud ( p_cValor ) > 0 )
				{
					p_cRes = CadDuplicar ( p_cValor );
				}
				else
				{
					p_cRes = CadDuplicar ( P_tmpdir );
				}
				MemLiberar ( (void **) &p_cValor );
			}
			else
			{
				p_cRes = CadDuplicar ( P_tmpdir );
			}
#		 endif
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
	SContadorCiclos *	p_cntcCPU;
	uint64_t			ui64Ciclos;
	struct timespec		tspIni;
	struct timespec		tspFin;
	double				dSegundos;

	p_cntcCPU = SConCicCrear ();
	if ( ES_VALIDO ( p_cntcCPU ) )
	{
		clock_gettime ( CLOCK_MONOTONIC, &tspIni );
		SConCicIniciar ( p_cntcCPU );
		SisEsperar ( _SISTEMA_MEDIDA_CPU_MILIS );
		ui64Ciclos = SConCicParar ( p_cntcCPU );
		clock_gettime ( CLOCK_MONOTONIC, &tspFin );

		dSegundos = ( (double) ( tspFin.tv_sec - tspIni.tv_sec ) ) +
					( (double) ( tspFin.tv_nsec - tspIni.tv_nsec ) ) / 1000000000.0;
		if ( dSegundos > 0.0 )
		{
			dRes = ( (double) ui64Ciclos ) / ( dSegundos * 1000000.0 );
		}
		SConCicDestruir ( &p_cntcCPU );
	}
	return ( dRes );
}

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

int SisAdmiteSubprocesos ()
{
	return ( _SisVerificarSubprocesos () );
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
	// En Windows el limite lo pone el sistema de ficheros, no el proceso.
	lRes = LONG_MAX;
#	endif
	return ( lRes );
}

long SisMaxTiempoCPUProceso ()
{
	long			lRes;
/* RLIMIT_CPU, no RLIMIT_SPU: esa constante no existe en ninguna parte. */
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

/* Los descriptores realmente abiertos, no el limite: antes esta funcion era una
   copia literal de SisDescriptoresESTotalesProceso, con lo que Disponibles daba siempre
   cero. Se cuentan probando cada descriptor con fcntl, que es POSIX y no depende
   de /proc; recorrer hasta el limite es barato porque son unos pocos miles. */
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

/* Orden de bytes de la maquina: 0 si el menos significativo va primero (Intel y
   compania), 1 si va el mas significativo, -1 si no se reconoce.
   Antes esto se averiguaba ESCRIBIENDO cuatro bytes en un fichero temporal del
   directorio de trabajo y volviendolos a leer como un entero. Funcionaba, pero
   dependia de poder escribir en el directorio actual, dejaba un fichero suelto en
   cada llamada, y arrastraba dos defectos: iOrdenBytes se devolvia sin asignar si
   la segunda apertura fallaba o si el valor no casaba con ninguna de las dos
   constantes, y el fclose del final quedaba FUERA de su if, con lo que se cerraba
   un FILE * invalido. Una union responde lo mismo sin tocar el disco. */
static int _SisObtenerOrdenBytes ()
{
	int				iOrdenBytes;
	union
	{
		unsigned int	uiValor;
		unsigned char	ucBytes [ sizeof ( unsigned int ) ];
	} uPrueba;

	uPrueba.uiValor = (unsigned int) _SISTEMA_UINT_PRUEBA;
	if ( uPrueba.ucBytes [ 0 ] == _SISTEMA_UINT_PRUEBA_BYTE_4 )
	{
		/* El byte menos significativo en la direccion mas baja. */
		iOrdenBytes = 0;
	}
	else if ( uPrueba.ucBytes [ 0 ] == _SISTEMA_UINT_PRUEBA_BYTE_1 )
	{
		/* El mas significativo primero. */
		iOrdenBytes = 1;
	}
	else
	{
		/* Ordenes mixtos, como el PDP: ni uno ni otro. */
		iOrdenBytes = -1;
	}
	return ( iOrdenBytes );
}

static int _SisVerificarSubprocesos ()
{
	int iAdmiteSubprocesos;
	
# if ( defined ( WIN ) )
	// No existe algo parecido a un fork, pero suponemos que funciona la creación de subprocesos:
	iAdmiteSubprocesos = 1;
# else
    pid_t	pidProc;

	/* Resto del codigo orientado a objeto anterior: aqui ya no hay p_sisObj. */
	iAdmiteSubprocesos = 0;
	pidProc = fork ();
	if ( pidProc > 0 )
	{
		/* Sin el waitpid el hijo queda de zombi hasta que termine el proceso. */
		waitpid ( pidProc, NULL, 0 );
		iAdmiteSubprocesos = 1;
	}
	else if ( pidProc == 0 )
	{
		_exit ( 0 );
	}
# endif
	return ( iAdmiteSubprocesos );
}

