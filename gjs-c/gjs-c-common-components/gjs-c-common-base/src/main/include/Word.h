/******************************************************************************/
/*                                Word.h                                      */
/*----------------------------------------------------------------------------*/
/* Librería:  GBase                                                           */
/* Versión:   1.0.0                                                           */
/* Fecha:     28/06/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene los prototipos de algunas rutinas de      */
/* carácter general de manejo de palabras de 2 bytes.                         */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_WORD_H
#define _ORG_GJS_C_CC_WORD_H


#include <BaseConfig.h>





/* Rutinas: */
byte WordByteInferior ( word wDato );
byte WordByteSuperior ( word wDato );

word WordComponer ( byte bySup, byte byInf );



#endif
