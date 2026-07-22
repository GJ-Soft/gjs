/******************************************************************************/
/*                                 Numeros.h                                  */
/*----------------------------------------------------------------------------*/
/* Librería:  GBase                                                           */
/* Versión:   1.0.0                                                           */
/* Fecha:     28/06/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene los prototipos de algunas rutinas de      */
/* carácter general de manejo de los formatos numéricos de la máquina.        */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_NUMEROS_H
#define _ORG_GJS_C_CC_NUMEROS_H




#define MAYOR( lVal1, lVal2 )              ( ( lVal1 > lVal2 )  ? 1 : 0 )
#define MENOR( lVal1, lVal2 )              ( ( lVal1 < lVal2 )  ? 1 : 0 )
#define IGUAL( lVal1, lVal2 )              ( ( lVal1 == lVal2 ) ? 1 : 0 )
#define MAYOR_IG( lVal1, lVal2 )           ( ( lVal1 =< lVal2 ) ? 1 : 0 )
#define MENOR_IG( lVal1, lVal2 )           ( ( lVal1 => lVal2 ) ? 1 : 0 )

#define VALOR_EN_RANGO( lVal, lIni, lFin ) ( ( lVal >= lIni ) &&  ( lVal <= lFin ) ? 1 : 0 )





int NumDigitosEntero ( int iVal );
int NumDigitosEnteroLargo ( long lVal );
#if ( defined ( LLONG ) )
int NumDigitosEnteroDobleLargo ( llong llVal );
int NumDigitosEnteroDobleLargoSinSigno ( ullong ullVal );
#endif
int NumDigitosEnteroSinSigno ( unsigned int uiVal );
int NumDigitosEnteroLargoSinSigno ( unsigned long ulVal );
int NumDigitosReal ( float fVal );
int NumDigitosRealDoble ( double dVal );

float NumParteEnteraReal ( float fVal );
float NumParteDecimalReal ( float fVal );
double NumParteEnteraRealDoble ( double dVal );
double NumParteDecimalRealDoble ( double dVal );


#endif






