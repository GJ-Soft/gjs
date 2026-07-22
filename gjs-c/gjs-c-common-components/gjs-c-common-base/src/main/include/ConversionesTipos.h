/******************************************************************************/
/*                            ConversionesTipos.h                             */
/*----------------------------------------------------------------------------*/
/* Librería:  GBase                                                           */
/* Versión:   1.0.0                                                           */
/* Fecha:     28/06/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene la los prototipos de algunas rutinas      */
/* generales de conversión entre tipos de datos básicos.                      */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_CONVERSIONESTIPOS_H
#define _ORG_GJS_C_CC_CONVERSIONESTIPOS_H




// FALTA CONVERTIR CADENA A READ Y REAL DOBLE:
char ConvDigitoACaracter ( int iDigito );
int ConvCaracterADigito ( char cDigito );

int ConvRealAEntero ( float fVal, int iTruncar );
long ConvRealAEnteroLargo ( float fVal, int iTruncar );
#if ( defined ( LLONG ) )
llong ConvRealAEnteroDobleLargo ( float fVal, int iTruncar );
ullong ConvRealAEnteroDobleLargoSinSigno ( float fVal, int iTruncar );
#endif
int ConvRealDobleAEntero ( double dVal, int iTruncar );
long ConvRealDobleAEnteroLargo ( double dVal, int iTruncar );
#if ( defined ( LLONG ) )
llong ConvRealDobleAEnteroDobleLargo ( double dVal, int iTruncar );
ullong ConvRealDobleAEnteroDobleLargoSinSigno ( double dVal, int iTruncar );
#endif
unsigned int ConvRealAEnteroSinSigno ( float fVal, int iTruncar );
unsigned long ConvRealAEnteroLargoSinSigno ( float fVal, int iTruncar );
unsigned int ConvRealDobleAEnteroSinSigno ( double dVal, int iTruncar );
unsigned long ConvRealDobleAEnteroLargoSinSigno ( double dVal, int iTruncar );

int	ConvCadenaAEntero ( const char * p_cVal );
long ConvCadenaAEnteroLargo ( const char * p_cVal );
unsigned int ConvCadenaAEnteroSinSigno ( const char * p_cVal );
unsigned long ConvCadenaAEnteroLargoSinSigno ( const char * p_cVal );
#if ( defined ( LLONG ) )
llong ConvCadenaAEnteroDobleLargo ( const char * p_cVal );
ullong ConvCadenaAEnteroDobleLargoSinSigno ( const char * p_cVal );
#endif

char * ConvEnteroACadena ( int iVal );
char * ConvEnteroLargoACadena ( long lVal );
char * ConvEnteroSinSignoACadena ( unsigned int uiVal );
char * ConvEnteroLargoSinSignoACadena ( unsigned long ulVal );
#if ( defined ( LLONG ) )
char * ConvEnteroDobleLargoACadena ( llong llVal );
char * ConvEnteroDobleLargoSinSignoACadena ( ullong ullVal );
#endif
char * ConvRealACadena ( float fVal );
char * ConvRealDobleACadena ( double dVal );

char * ConvEnteroACadenaHex ( int iVal );
char * ConvEnteroSinSignoACadenaHex ( unsigned int uiVal );
char * ConvEnteroLargoSinSignoACadenaHex ( unsigned long ulVal );
int	ConvCadenaHexAEntero ( const char * p_cVal );
long ConvCadenaHexAEnteroLargo ( const char * p_cVal );
unsigned int ConvCadenaHexAEnteroSinSigno ( const char * p_cVal );
unsigned long ConvCadenaHexAEnteroLargoSinSigno ( const char * p_cVal );
#if ( defined ( LLONG ) )
llong ConvCadenaHexAEnteroDobleLargo ( const char * p_cVal );
ullong ConvCadenaHexAEnteroDobleLargoSinSigno ( const char * p_cVal );
#endif


#endif






