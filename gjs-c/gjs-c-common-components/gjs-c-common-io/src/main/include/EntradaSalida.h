
#ifndef _ORG_GJS_C_CC_ENTRADASALIDA_H
#define _ORG_GJS_C_CC_ENTRADASALIDA_H

#include <Precompilacion.h>



#include <stdio.h>
#include <stdarg.h>

/* 0 = cerrado, 1 = abierto pero redirigido, 2 = abierto y es terminal */
int SisEstadoDescriptor ( int iDescriptor );

int SisObtenerDescriptor ( FILE * p_fObj );

int SisAsincEscribir ( int iDescriptor, const char * p_cText );
int SisAsincEscribirConFormato ( int iDescriptor, const char * p_cFormato, ... ) FORMATO_PRINTF ( 2, 3 );
int SisAsincEscribirConFormatoExt ( int iDescriptor, const char * p_cFormato, va_list valArgumentos );

int SisConAsincEscribir ( const char * p_cText );
int SisConAsincEscribirConFormato ( const char * p_cFormato, ... ) FORMATO_PRINTF ( 1, 2 );
int SisConAsincEscribirConFormatoExt ( const char * p_cFormato, va_list valArgumentos );


#endif

