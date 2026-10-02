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




char ConvDigitoACaracter ( int iDigito );
int ConvCaracterADigito ( char cDigito );

int ConvRealAEntero ( float fVal, int iTruncar );
long ConvRealAEnteroLargo ( float fVal, int iTruncar );
long long ConvRealAEnteroDobleLargo ( float fVal, int iTruncar );
unsigned long long ConvRealAEnteroDobleLargoSinSigno ( float fVal, int iTruncar );
int ConvRealDobleAEntero ( double dVal, int iTruncar );
long ConvRealDobleAEnteroLargo ( double dVal, int iTruncar );
long long ConvRealDobleAEnteroDobleLargo ( double dVal, int iTruncar );
unsigned long long ConvRealDobleAEnteroDobleLargoSinSigno ( double dVal, int iTruncar );
unsigned int ConvRealAEnteroSinSigno ( float fVal, int iTruncar );
unsigned long ConvRealAEnteroLargoSinSigno ( float fVal, int iTruncar );
unsigned int ConvRealDobleAEnteroSinSigno ( double dVal, int iTruncar );
unsigned long ConvRealDobleAEnteroLargoSinSigno ( double dVal, int iTruncar );

int	ConvCadenaAEntero ( const char * p_cVal );
long ConvCadenaAEnteroLargo ( const char * p_cVal );
unsigned int ConvCadenaAEnteroSinSigno ( const char * p_cVal );
unsigned long ConvCadenaAEnteroLargoSinSigno ( const char * p_cVal );
long long ConvCadenaAEnteroDobleLargo ( const char * p_cVal );
unsigned long long ConvCadenaAEnteroDobleLargoSinSigno ( const char * p_cVal );
float ConvCadenaAReal ( const char * p_cVal );
double ConvCadenaARealDoble ( const char * p_cVal );

char * ConvEnteroACadena ( int iVal );
char * ConvEnteroLargoACadena ( long lVal );
char * ConvEnteroSinSignoACadena ( unsigned int uiVal );
char * ConvEnteroLargoSinSignoACadena ( unsigned long ulVal );
char * ConvEnteroDobleLargoACadena ( long long llVal );
char * ConvEnteroDobleLargoSinSignoACadena ( unsigned long long ullVal );
char * ConvRealACadena ( float fVal );
char * ConvRealDobleACadena ( double dVal );

char * ConvEnteroACadenaHex ( int iVal );
char * ConvEnteroSinSignoACadenaHex ( unsigned int uiVal );
char * ConvEnteroLargoSinSignoACadenaHex ( unsigned long ulVal );
int	ConvCadenaHexAEntero ( const char * p_cVal );
long ConvCadenaHexAEnteroLargo ( const char * p_cVal );
unsigned int ConvCadenaHexAEnteroSinSigno ( const char * p_cVal );
unsigned long ConvCadenaHexAEnteroLargoSinSigno ( const char * p_cVal );
long long ConvCadenaHexAEnteroDobleLargo ( const char * p_cVal );
unsigned long long ConvCadenaHexAEnteroDobleLargoSinSigno ( const char * p_cVal );


#endif






