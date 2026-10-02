/******************************************************************************/
/*                                TestAndSet.h                                */
/*----------------------------------------------------------------------------*/
/* Librería:  Sistema                                                         */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene los prototipos de las rutinas tas y       */
/* tar, para los casos en que no vengan en las librerías del compilador.      */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_TESTANDSET_H
#define _ORG_GJS_C_CC_TESTANDSET_H



#include <Precompilacion.h>



#if ( defined ( WIN ) )

#	if ( !defined ( tas ) )
#		define tas(ptr) (InterlockedExchange((volatile LONG *)(ptr), 1))
#		define tar(ptr) (InterlockedExchange((volatile LONG *)(ptr), 0))
#	endif

#elif ( defined ( POSIX ) )

#	if ( !defined ( tas ) )

#		if ( defined ( xchg ) )
#			define tas(ptr) (xchg((ptr),1))
#			define tar(ptr) (xchg((ptr),0))
#		else
	
static inline int _tas_impl(volatile int *ptr, int val) {
    int result;
    __asm__ __volatile__(
        "xchgl %0, %1"
        : "=r" (result), "+m" (*ptr)
        : "0" (val)
        : "memory"
    );
    return result;
}

#			define tas(ptr) (_tas_impl((ptr), 1))
#			define tar(ptr) (_tas_impl((ptr), 0))

#		endif

#	endif

#else
	// TODO
#endif

#endif





