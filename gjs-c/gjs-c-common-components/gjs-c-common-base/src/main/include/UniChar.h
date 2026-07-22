/******************************************************************************/
/*                                 UniChar.h                                  */
/*----------------------------------------------------------------------------*/
/* Librería:  GBase                                                           */
/* Versión:   1.0.0                                                           */
/* Fecha:     28/06/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene la definición de un tipo de datos         */
/* para manejar cadenas UNICODE, y algunas rutinas de conversión.             */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_UNICHAR_H
#define _ORG_GJS_C_CC_UNICHAR_H


typedef unsigned short unichar;


char UnicodeAscii ( unichar ucValor );
unichar AsciiAUnicode ( char cValor );

char * CadUnicodeAAsciiz ( const unichar * p_ucUnicode );
unichar * CadAsciizAUnicode ( const char * p_cAsciiz );




#endif






