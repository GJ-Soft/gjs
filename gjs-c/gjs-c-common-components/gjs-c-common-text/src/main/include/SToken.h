/******************************************************************************/
/*                                 SToken.h                                   */
/*----------------------------------------------------------------------------*/
/* Librería:  GCadenas                                                        */
/* Versión:   1.0.0                                                           */
/* Fecha:     30/06/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene la definición de la clase de datos        */
/* SToken, destinada a almancenar un dato de tipo cadena y a proveer          */
/* diferentes operaciones sobre ésta.                                         */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_STOKEN_H
#define _ORG_GJS_C_CC_STOKEN_H





#include <SCadena.h>





typedef struct
{
	SCadena *	p_cadValor;

} SToken;


SToken * STokCrear ( int iLong );
SToken * STokGenerar ( SCadena * p_cadValor );
SToken * STokGenerarExt ( const char * p_cValor );

void STokDestruir ( SToken ** p_p_tokObj );

int STokInicializar ( SToken * p_tokObj, int iLong ); 
int STokVaciar ( SToken * p_tokObj );

int STokEstaVacio ( SToken * p_tokObj );

SCadena * STokCadena ( SToken * p_tokObj );
char * STokValor ( SToken * p_tokObj );
const char * STokValorConstante ( SToken * p_tokObj );

char STokCaracter ( SToken * p_tokObj, int iCar );
int STokEstablecerCaracter ( SToken * p_tokObj, int iCar, char cVal );

int STokCopiar ( SToken * p_tokObj, SToken * p_tokValor );
int STokCopiarCadena ( SToken * p_tokObj, SCadena * p_cadValor );
int STokCopiarLiteral ( SToken * p_tokObj, const char * p_cadValor );
int STokCopiarCaracter ( SToken * p_tokObj, char cValor );

int STokCopiarConFormato ( SToken * p_tokObj, const char * p_cFormato, ...);

int STokLongitud ( SToken * p_tokObj );
int STokMaxTam ( SToken * p_tokObj );

int STokAsignar ( SToken * p_tokObj, SToken * p_tokValor );
int STokAsignarCadena ( SToken * p_tokObj, SCadena * p_cadValor );
int STokAsignarLiteral ( SToken * p_tokObj, const char * p_cadValor );

SToken * STokDuplicar ( SToken * p_tokObj );
SCadena * STokDuplicarCadena ( SToken * p_tokObj );
char * STokDuplicarValor ( SToken * p_tokObj );

int STokEsIgual ( SToken * p_tokObj, SToken * p_tokValor );
int STokEsMenor ( SToken * p_tokObj, SToken * p_tokValor );
int STokEsMayor ( SToken * p_tokObj, SToken * p_tokValor );
int STokEsDiferente ( SToken * p_tokObj, SToken * p_tokValor );

int STokCadenaEsIgual ( SToken * p_tokObj, SCadena * p_cadValor );
int STokCadenaEsMenor ( SToken * p_tokObj, SCadena * p_cadValor );
int STokCadenaEsMayor ( SToken * p_tokObj, SCadena * p_cadValor );
int STokCadenaEsDiferente ( SToken * p_tokObj, SCadena * p_cadValor );

int STokLiteralEsIgual ( SToken * p_tokObj, const char * p_cadValor );
int STokLiteralEsMenor ( SToken * p_tokObj, const char * p_cadValor );
int STokLiteralEsMayor ( SToken * p_tokObj, const char * p_cadValor );
int STokLiteralEsDiferente ( SToken * p_tokObj, const char * p_cadValor );

int STokCumpleExpReg ( SToken * p_tokObj, const char * p_cExpReg );





#endif



