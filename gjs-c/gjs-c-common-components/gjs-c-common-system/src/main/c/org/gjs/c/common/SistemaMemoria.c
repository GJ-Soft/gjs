/******************************************************************************/
/*                             SistemaMemoria.cpp                             */
/*----------------------------------------------------------------------------*/
/* Librería:  Sistema                                                         */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de código fuente que contiene la implementación de las rutinas     */
/* de carácter general de reserva y liberación de espacios de memoria.        */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#include "SistemaMemoria.h"


#include "SistemaConfig.h"



unsigned long long SisMemoriaTotal ()
{
	unsigned long long ullRes;

# if ( defined ( WIN ) )
	MEMORYSTATUSEX memstatInfo;

	memstatInfo.dwLength = sizeof ( memstatInfo );
	if ( GlobalMemoryStatusEx ( &memstatInfo ) )
	{
		ullRes = (unsigned long long) memstatInfo.ullTotalVirtual;
	}
	else
	{
		// Error:
		ullRes = 0;
	}
# else
	struct rlimit	rlimInfo; 
	//struct rusage 	rusgInfo; 

	if ( getrlimit ( RLIMIT_AS, &rlimInfo ) == 0 )
	{
		ullRes = rlimInfo.rlim_cur; 
	}
	else
	{
		// Error:
		ullRes = 0;
	}
# endif

	return ( ullRes );
}

unsigned long long SisMemoriaDisponible ()
{
	unsigned long long ullRes;

# if ( defined ( WIN ) )
	MEMORYSTATUSEX memstatInfo;

	memstatInfo.dwLength = sizeof ( memstatInfo );
	if ( GlobalMemoryStatusEx ( &memstatInfo ) )
	{
		ullRes = (unsigned long long) memstatInfo.ullAvailVirtual;
	}
	else
	{
		// Error:
		ullRes = 0;
	}
# else
	ullRes = SisMemoriaTotal () - SisMemoriaOcupada();
# endif

	return ( ullRes );
}

unsigned long long SisMemoriaOcupada ()
{
	unsigned long long ullRes;

# if ( defined ( WIN ) )
	MEMORYSTATUSEX memstatInfo;

	memstatInfo.dwLength = sizeof ( memstatInfo );
	if ( GlobalMemoryStatusEx ( &memstatInfo ) )
	{
		ullRes = (unsigned long long) (memstatInfo.ullTotalVirtual - memstatInfo.ullAvailVirtual);
	}
	else
	{
		// Error:
		ullRes = 0;
	}
# else
    FILE * 	fProc;
	long	lPaginas;
	long 	lTamPagina;
	
	// Abrimos el archivo de estado de memoria del propio proceso
    fProc = fopen( "/proc/self/statm", "r" );
    if ( ES_VALIDO ( fProc ) )
    {
        // El primer valor es el tamaño de la memoria virtual en páginas
        if ( fscanf ( fProc, "%ld", &lPaginas ) == 1 )
        {
            // Obtenemos cuántos bytes mide una página en esta arquitectura (ej. 4096 bytes)
            lTamPagina = sysconf( _SC_PAGESIZE );
            
            // Páginas ocupadas * Bytes por página = Total de bytes virtuales ocupados
            ullRes = (unsigned long long) lPaginas * lTamPagina;
        }
		else
		{
			ullRes = 0;
		}
        fclose(fProc);
    }
	else
	{
		ullRes = 0;
	}
# endif

	return ( ullRes );
}

double SisMemoriaDisponiblePorc ()
{
	double				 dRes;
	unsigned long long   ulMemDisp;
	unsigned long long   ulMemTotal;

	ulMemDisp = SisMemoriaDisponible ();
	ulMemTotal = SisMemoriaTotal ();
	dRes = (ulMemDisp * 100.0) / (ulMemTotal * 1.0 );
	return ( dRes );
}	

double SisMemoriaOcupadaPorc ()
{
	double			dRes;
	unsigned long long   ulMemOcup;
	unsigned long long   ulMemTotal;

	ulMemOcup = SisMemoriaOcupada ();
	ulMemTotal = SisMemoriaTotal ();
	dRes = (ulMemOcup * 100.0) / (ulMemTotal * 1.0 );
	return ( dRes );
}	

unsigned long long SisMemoriaFisicaTotal ()
{
	unsigned long long ullRes;

# if ( defined ( WIN ) )
	MEMORYSTATUSEX memstatInfo;

	memstatInfo.dwLength = sizeof ( memstatInfo );
	if ( GlobalMemoryStatusEx ( &memstatInfo ) )
	{
		ullRes = (unsigned long long) memstatInfo.ullTotalPhys;
	}
	else
	{
		// Error:
		ullRes = 0;
	}
# else
	struct sysinfo info;

    // sysinfo devuelve 0 si tiene éxito, -1 si falla
    if ( sysinfo( &info ) == 0 ) 
    {
		// totalram (páginas/bloques de hardware) * mem_unit (bytes por bloque)
        ullRes = (unsigned long long)info.totalram * info.mem_unit;
	}	
	else
	{
		// Error:
		ullRes = 0;
	}
# endif

	return ( ullRes );
}

unsigned long long SisMemoriaFisicaDisponible ()
{
	unsigned long long ullRes;

# if ( defined ( WIN ) )
	MEMORYSTATUSEX memstatInfo;

	memstatInfo.dwLength = sizeof ( memstatInfo );
	if ( GlobalMemoryStatusEx ( &memstatInfo ) )
	{
		ullRes = (unsigned long long) memstatInfo.ullAvailPhys;
	}
	else
	{
		// Error:
		ullRes = 0;
	}
# else
	struct sysinfo info;

    // sysinfo devuelve 0 si tiene éxito, -1 si falla
    if ( sysinfo( &info ) == 0 ) 
    {
		// Versión optimizada (Memoria libre + memoria de intercambio rápido)
		ullRes = ((unsigned long long)info.freeram + info.bufferram) * info.mem_unit;
	}	
	else
	{
		// Error:
		ullRes = 0;
	}
# endif

	return ( ullRes );
}

unsigned long long SisMemoriaFisicaOcupada ()
{
	unsigned long long ullRes;

# if ( defined ( WIN ) )
	MEMORYSTATUSEX memstatInfo;

	memstatInfo.dwLength = sizeof ( memstatInfo );
	if ( GlobalMemoryStatusEx ( &memstatInfo ) )
	{
		ullRes = (unsigned long long) (memstatInfo.ullTotalPhys - memstatInfo.ullAvailPhys);
	}
	else
	{
		// Error:
		ullRes = 0;
	}
# else
	struct sysinfo info;

    // sysinfo devuelve 0 si tiene éxito, -1 si falla
    if ( sysinfo( &info ) == 0 ) 
    {
		ullRes = ((unsigned long long)info.totalram - ((unsigned long long)info.freeram + info.bufferram)) * info.mem_unit;
	}	
	else
	{
		// Error:
		ullRes = 0;
	}
# endif

	return ( ullRes );
}

unsigned long long SisMemoriaFicPaginacionTotal ()
{
	unsigned long long ullRes;

# if ( defined ( WIN ) )
	MEMORYSTATUSEX memstatInfo;

	memstatInfo.dwLength = sizeof ( memstatInfo );
	if ( GlobalMemoryStatusEx ( &memstatInfo ) )
	{
		ullRes = (unsigned long long) memstatInfo.ullTotalPageFile;
	}
	else
	{
		// Error:
		ullRes = 0;
	}
# else
	struct sysinfo info;

    // sysinfo devuelve 0 si tiene éxito, -1 si falla
    if ( sysinfo( &info ) == 0 ) 
    {
		// Equivalente estricto al "Commit Limit" de Windows (RAM Total + SWAP Total)
		ullRes = ((unsigned long long)info.totalram + info.totalswap) * info.mem_unit;
    }	
	else
	{
		// Error:
		ullRes = 0;
	}
# endif

	return ( ullRes );
}

unsigned long long SisMemoriaFicPaginacionDisponible ()
{
	unsigned long long ullRes;

# if ( defined ( WIN ) )
	MEMORYSTATUSEX memstatInfo;

	memstatInfo.dwLength = sizeof ( memstatInfo );
	if ( GlobalMemoryStatusEx ( &memstatInfo ) )
	{
		ullRes = (unsigned long long) memstatInfo.ullAvailPageFile;
	}
	else
	{
		// Error:
		ullRes = 0;
	}
# else
	struct sysinfo info;

    // sysinfo devuelve 0 si tiene éxito, -1 si falla
    if ( sysinfo( &info ) == 0 ) 
    {
		// Equivalente estricto al espacio total comprometible libre (RAM Libre + SWAP Libre)
		ullRes = ((unsigned long long)info.freeram + info.freeswap) * info.mem_unit;
    }	
	else
	{
		// Error:
		ullRes = 0;
	}
# endif

	return ( ullRes );
}

unsigned long long SisMemoriaFicPaginacionOcupada ()
{
	unsigned long long ullRes;

# if ( defined ( WIN ) )
	MEMORYSTATUSEX memstatInfo;

	memstatInfo.dwLength = sizeof ( memstatInfo );
	if ( GlobalMemoryStatusEx ( &memstatInfo ) )
	{
		ullRes = (unsigned long long) (memstatInfo.ullTotalPageFile - memstatInfo.ullAvailPageFile);
	}
	else
	{
		// Error:
		ullRes = 0;
	}
# else
	struct sysinfo info;

    // sysinfo devuelve 0 si tiene éxito, -1 si falla
    if ( sysinfo( &info ) == 0 ) 
    {
		// Equivalente estricto al "Commit Limit" de Windows (RAM Total + SWAP Total)
		ullRes = (((unsigned long long)info.totalram + info.totalswap) - ((unsigned long long)info.freeram + info.freeswap) ) * info.mem_unit;
    }	
	else
	{
		// Error:
		ullRes = 0;
	}
# endif

	return ( ullRes );
}

unsigned long long SisMemoriaHeapTotal ()
{
	return ( SisMemoriaHeapMax () - SisMemoriaHeapMin () );
}

# if ( ! defined ( WIN ) )

#	define SIS_MAX_TAM_LINEA_MAPS		512

/* Limites del monton segun /proc/self/maps. Antes se leia con un fscanf suelto
   que se quedaba con la PRIMERA linea del fichero, que no es el monton sino el
   primer mapeo del proceso: Min y Max salian de esa misma linea, y por eso
   SisMemoriaHeapTotal () daba el tamano de esa region y no el del monton.

   Las lineas del monton son las que llevan [heap] al final. En Linux hay una; en
   Cygwin hay dos, la parte con paginas confirmadas y la reservada a continuacion,
   asi que se toma el principio de la primera y el final de la ultima. Ojo con
   buscar solo "heap": [cygheap] y [win heap 0 default grow] son otras regiones, y
   ninguna de las dos contiene "[heap]". */
static int _SisMemoriaHeapLimites ( unsigned long long * p_ullMin, unsigned long long * p_ullMax )
{
	int					iRes = 0;
	FILE *				fProc;
	char				cLinea [ SIS_MAX_TAM_LINEA_MAPS ];
	unsigned long long	ullIni;
	unsigned long long	ullFin;

	fProc = fopen ( "/proc/self/maps", "r" );
	if ( ES_VALIDO ( fProc ) )
	{
		while ( ES_VALIDO ( fgets ( cLinea, sizeof ( cLinea ), fProc ) ) )
		{
			if ( ES_VALIDO ( strstr ( cLinea, "[heap]" ) ) &&
				 ( sscanf ( cLinea, "%llx-%llx", &ullIni, &ullFin ) == 2 ) )
			{
				if ( iRes == 0 )
				{
					*p_ullMin = ullIni;
					iRes = 1;
				}
				*p_ullMax = ullFin;
			}
		}
		fclose ( fProc );
	}
	return ( iRes );
}

# endif

unsigned long long SisMemoriaHeapMin ()
{
	unsigned long long ullRes;

# if ( defined ( WIN ) )
	// Error:
	ullRes = 0;
# else
	unsigned long long  ullMin;
	unsigned long long  ullMax;

	if ( _SisMemoriaHeapLimites ( &ullMin, &ullMax ) == 1 )
	{
		ullRes = ullMin;
	}
	else
	{
		// Error:
		ullRes = 0;
	}
# endif

	return ( ullRes );
}

unsigned long long SisMemoriaHeapMax ()
{
	unsigned long long ullRes;

# if ( defined ( WIN ) )
	// Error:
	ullRes = 0;
# else
	unsigned long long  ullMin;
	unsigned long long  ullMax;

	if ( _SisMemoriaHeapLimites ( &ullMin, &ullMax ) == 1 )
	{
		ullRes = ullMax;
	}
	else
	{
		// Error:
		ullRes = 0;
	}
# endif

	return ( ullRes );
}
