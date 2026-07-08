/******************************************************************************/
/*                             SistemaTiempo.c                               */
/*----------------------------------------------------------------------------*/
/* Librería:  Sistema                                                         */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de código fuente que contiene la implementación de las rutinas     */
/* de carácter general de manejo de tiempos y temporizaciones.                */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#include "SistemaTiempo.h"


#include "SistemaConfig.h"





void SisEsperar ( int iMiliSegs )
{
	if ( iMiliSegs > 0 )
	{
#  	  if ( defined ( WIN ) )
		Sleep ( (DWORD) iMiliSegs );
#	  else
		struct timespec ts;

        ts.tv_sec  = iMiliSegs / 1000;
        ts.tv_nsec = ( iMiliSegs % 1000 ) * 1000000L;

        nanosleep ( &ts, NULL );
# 	  endif
	}
}



#if ( defined ( VC ) )
	
#include <intrin.h>

uint64_t SisCiclosCPU ()
{
    int dummy[4];

    __cpuid(dummy, 0);
    return __rdtsc();
}

#else

uint64_t SisCiclosCPU ()
{
	uint64_t uiCiclos;

# if ( defined(__i386__) || defined(__x86_64__) )
	unsigned int uiLow;
	unsigned int uiHigh;

	__asm__ volatile (
		"cpuid\n\t"
		"rdtsc\n\t"
		: "=a"( uiLow ), "=d"( uiHigh )
		:
		: "%rbx", "%rcx"
		);
	uiCiclos = ( ( uint64_t ) uiHigh << 32 ) | uiLow;	
# elif defined(__aarch64__)
	asm volatile(
		"mrs %0, cntvct_el0"
		: "=r"(uiCiclos)
);
# elif defined(__riscv)
	asm volatile(
		"rdcycle %0"
		: "=r"(uiCiclos)
	);
# else
    struct timespec ts;

    clock_gettime( CLOCK_MONOTONIC, &ts );

    uiCiclos = (uint64_t)ts.tv_sec * 1000000000ULL +
           (uint64_t)ts.tv_nsec;
# endif
	return ( uiCiclos );
}

#endif



