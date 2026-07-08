
#ifndef _ORG_GJS_C_CC_ENTRADASALIDA_H
#define _ORG_GJS_C_CC_ENTRADASALIDA_H



#include <stdio.h>
#include <stdarg.h>


int SisObtenerDescriptor ( FILE * p_fObj );

int SisAsincEscribir ( int iDescriptor, const char * p_cText );
int SisAsincEscribirConFormato ( int iDescriptor, const char * p_cFormato, ... );
int SisAsincEscribirConFormatoExt ( int iDescriptor, const char * p_cFormato, va_list valArgumentos );

int SisConAsincEscribir ( const char * p_cText );
int SisConAsincEscribirConFormato ( const char * p_cFormato, ... );
int SisConAsincEscribirConFormatoExt ( const char * p_cFormato, va_list valArgumentos );


#endif

