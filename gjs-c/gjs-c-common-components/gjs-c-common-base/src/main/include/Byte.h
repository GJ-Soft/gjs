/******************************************************************************/
/*                                   Byte.h                                   */
/*----------------------------------------------------------------------------*/
/* Librería:  GBase                                                           */
/* Versión:   1.0.0                                                           */
/* Fecha:     28/06/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene los prototipos de algunas rutinas de      */
/* carácter general de manejo de bytes.                                       */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _BYTE_H
#define _BYTE_H


#include <BaseConfig.h>


nibble ByteNibbleInferior ( byte byDato );
nibble ByteNibbleSuperior ( byte byDato );

byte ByteComponer ( nibble nibSup, nibble nibInf );


char * ByteAHex ( byte byValor, char * p_cValor );
byte HexAByte ( const char * p_cValor );





#endif






