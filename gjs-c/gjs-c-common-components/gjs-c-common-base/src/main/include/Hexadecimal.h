/******************************************************************************/
/*                               Hexadecimal.h                                */
/*----------------------------------------------------------------------------*/
/* Librería:  GBase                                                           */
/* Versión:   1.0.0                                                           */
/* Fecha:     28/06/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene los prototipos de algunas rutinas de      */
/* carácter general de manejo de valores hexadecimales.                       */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_HEXADECIMAL_H
#define _ORG_GJS_C_CC_HEXADECIMAL_H




/* Digitos hexadecimales: */
#define HEX_0		'0'
#define HEX_1		'1'
#define HEX_2		'2'
#define HEX_3		'3'
#define HEX_4		'4'
#define HEX_5		'5'
#define HEX_6		'6'
#define HEX_7		'7'
#define HEX_8		'8'
#define HEX_9		'9'
#define HEX_A 		'A'
#define HEX_B		'B'
#define HEX_C		'C'
#define HEX_D		'D'
#define HEX_E		'E'
#define HEX_F		'F'




int HexEsValido ( char cVal );
int HexEsNumValido ( int iVal );

int HexValor ( char cVal );
char HexDigito ( int iVal );



#endif






