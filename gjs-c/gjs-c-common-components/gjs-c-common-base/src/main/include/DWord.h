/******************************************************************************/
/*                                DWord.h                                     */
/*----------------------------------------------------------------------------*/
/* Librería:  GBase                                                           */
/* Versión:   1.0.0                                                           */
/* Fecha:     28/06/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene los prototipos de algunas rutinas de      */
/* carácter general de manejo de palabras de 4 bytes.                         */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_DWORD_H
#define _ORG_GJS_C_CC_DWORD_H


#include <BaseConfig.h>




/* Rutinas: */
word DWordWordInferior ( dword dwDato );
word DWordWordSuperior ( dword dwDato );

dword DWordComponer ( word wSup, word wInf );


#endif
