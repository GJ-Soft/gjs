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




#define MAYOR( lVal1, lVal2 )              ( ( ( lVal1 ) > ( lVal2 ) )  ? 1 : 0 )
#define MENOR( lVal1, lVal2 )              ( ( ( lVal1 ) < ( lVal2 ) )  ? 1 : 0 )
#define IGUAL( lVal1, lVal2 )              ( ( ( lVal1 ) == ( lVal2 ) ) ? 1 : 0 )
#define MAYOR_IG( lVal1, lVal2 )           ( ( ( lVal1 ) >= ( lVal2 ) ) ? 1 : 0 )
#define MENOR_IG( lVal1, lVal2 )           ( ( ( lVal1 ) <= ( lVal2 ) ) ? 1 : 0 )

#define VALOR_EN_RANGO( lVal, lIni, lFin ) ( ( ( lVal ) >= ( lIni ) ) &&  ( ( lVal ) <= ( lFin ) ) ? 1 : 0 )





int NumDigitosEntero ( int iVal );
int NumDigitosEnteroLargo ( long lVal );
int NumDigitosEnteroDobleLargo ( long long llVal );
int NumDigitosEnteroDobleLargoSinSigno ( unsigned long long ullVal );
int NumDigitosEnteroSinSigno ( unsigned int uiVal );
int NumDigitosEnteroLargoSinSigno ( unsigned long ulVal );
int NumDigitosReal ( float fVal );
int NumDigitosRealDoble ( double dVal );

float NumParteEnteraReal ( float fVal );
float NumParteDecimalReal ( float fVal );
double NumParteEnteraRealDoble ( double dVal );
double NumParteDecimalRealDoble ( double dVal );

int MaxDigitosEntero ();
int MaxDigitosEnteroLargo ();
int MaxDigitosEnteroDobleLargo ();
int MaxDigitosEnteroDobleLargoSinSigno ();
int MaxDigitosEnteroSinSigno ();
int MaxDigitosEnteroLargoSinSigno ();
/* En coma flotante "el maximo de digitos" son DOS numeros distintos, segun
   hacia donde vaya la ida y vuelta, y confundirlos pierde datos:

     Significativos  cuantos digitos puede escribir el usuario y recuperarlos
                     intactos                       decimal -> binario -> decimal
     Reproducir      cuantos digitos hay que IMPRIMIR para no perder nada del
                     valor que ya esta en memoria   binario -> decimal -> binario

   Medido el 2026-09-19 con 200.000 float al azar: imprimiendo con los 6
   digitos de Significativos, 192.782 NO vuelven a ser el mismo float. Con los
   9 de Reproducir, ninguno falla. Se ve en un caso: 0.1f con 6 digitos se
   escribe "0.1", y al releerlo sale otro float; con 9 sale "0.100000001", que
   si vuelve igual.

   Para serializar, Reproducir. Para validar o mostrar, Significativos. */
int MaxDigitosSignificativosReal ();
int MaxDigitosSignificativosRealDoble ();
int MaxDigitosReproducirReal ();
int MaxDigitosReproducirRealDoble ();

/* Exponente decimal maximo: la potencia de diez mas alta representable.
   OJO con lo que NO acota: no limita la longitud de una cadena valida. Un
   "1.000...000" con miles de ceros, o un "0.000...000123", son numeros
   perfectamente validos y tan largos como se quiera. Esto sirve para saber si
   un valor cabe, no para dimensionar la cadena que lo escribe.
   El minimo, si algun dia hace falta, es FLT_MIN_10_EXP / DBL_MIN_10_EXP
   ( -37 y -307 ), y solo vale para los normalizados: los subnormales bajan
   mas. */
int MaxExponenteReal ();
int MaxExponenteRealDoble ();


#endif






