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

unsigned long long SisMemoriaHeapMin ()
{
	unsigned long long ullRes;

# if ( defined ( WIN ) )
	// Error:
	ullRes = 0;
# else
    FILE * 				fProc;
	unsigned long long  ullMin;
	unsigned long long  ullMax;
	
    fProc = fopen( "/proc/self/maps", "r" );
    if ( ES_VALIDO ( fProc ) )
    {
        if ( fscanf ( fProc, "%llx-%llx", &ullMin, &ullMax ) == 2 )
		{
			ullRes = ullMin;
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

unsigned long long SisMemoriaHeapMax ()
{
	unsigned long long ullRes;

# if ( defined ( WIN ) )
	// Error:
	ullRes = 0;
# else
    FILE * 				fProc;
	unsigned long long  ullMin;
	unsigned long long  ullMax;
	
    fProc = fopen( "/proc/self/maps", "r" );
    if ( ES_VALIDO ( fProc ) )
    {
        if ( fscanf ( fProc, "%llx-%llx", &ullMin, &ullMax ) == 2 )
		{
			ullRes = ullMax;
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
