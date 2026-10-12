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

#include <Precompilacion.h>





#include <SCadena.h>





typedef struct
{
	SCadena *	p_cadValor;

} SToken;


SToken * STokCrear ( int iLong );
SToken * STokGenerar ( SCadena * p_cadValor );
SToken * STokGenerarLit ( const char * p_cValor );

void STokDestruir ( SToken ** p_p_tokObj );

int STokInicializar ( SToken * p_tokObj, int iLong ); 
int STokVaciar ( SToken * p_tokObj );

int STokEstaVacio ( SToken * p_tokObj );

SCadena * STokValor ( SToken * p_tokObj );
const char * STokValorLit ( SToken * p_tokObj );

char STokCaracter ( SToken * p_tokObj, int iCar );
int STokEstablecerCaracter ( SToken * p_tokObj, int iCar, char cVal );

int STokCopiar ( SToken * p_tokObj, SToken * p_tokValor );
int STokCopiarCadena ( SToken * p_tokObj, SCadena * p_cadValor );
int STokCopiarLiteral ( SToken * p_tokObj, const char * p_cadValor );
int STokCopiarCaracter ( SToken * p_tokObj, char cValor );

int STokCopiarConFormato ( SToken * p_tokObj, const char * p_cFormato, ...) FORMATO_PRINTF ( 2, 3 );

int STokLongitud ( SToken * p_tokObj );
int STokMaxTam ( SToken * p_tokObj );

int STokAsignar ( SToken * p_tokObj, SToken * p_tokValor );
int STokEstablecer ( SToken * p_tokObj, SCadena * p_cadValor );
int STokEstablecerLit ( SToken * p_tokObj, const char * p_cadValor );

SToken * STokDuplicar ( SToken * p_tokObj );
SCadena * STokDuplicarCadena ( SToken * p_tokObj );
char * STokDuplicarValor ( SToken * p_tokObj );

int STokEsIgual ( SToken * p_tokObj, SToken * p_tokValor );
int STokEsMenor ( SToken * p_tokObj, SToken * p_tokValor );
int STokEsMayor ( SToken * p_tokObj, SToken * p_tokValor );
int STokEsDiferente ( SToken * p_tokObj, SToken * p_tokValor );

int STokEsIgualCad ( SToken * p_tokObj, SCadena * p_cadValor );
int STokEsMenorCad ( SToken * p_tokObj, SCadena * p_cadValor );
int STokEsMayorCad ( SToken * p_tokObj, SCadena * p_cadValor );
int STokEsDiferenteCad ( SToken * p_tokObj, SCadena * p_cadValor );

int STokEsIgualLit ( SToken * p_tokObj, const char * p_cadValor );
int STokEsMenorLit ( SToken * p_tokObj, const char * p_cadValor );
int STokEsMayorLit ( SToken * p_tokObj, const char * p_cadValor );
int STokEsDiferenteLit ( SToken * p_tokObj, const char * p_cadValor );

int STokComparar ( SToken * p_tokObj, SToken * p_tokValor );
int STokCompararCad ( SToken * p_tokObj, SCadena * p_cadValor );
int STokCompararLit ( SToken * p_tokObj, const char * p_cValor );

int STokCumpleExpReg ( SToken * p_tokObj, const char * p_cExpReg );





#endif



