/******************************************************************************/
/*                              FormatoCadena.h                               */
/*----------------------------------------------------------------------------*/
/* Librería:  GBase                                                           */
/* Versión:   1.0.0                                                           */
/* Fecha:     28/06/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene el prototipo de una rutina general        */
/* espacial para generar cadenas formateadas a partir de un formato y una     */
/* serie indeterminada de argumentos.                                         */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_FORMATOCADENA_H
#define _ORG_GJS_C_CC_FORMATOCADENA_H



#include <stdarg.h>






int FrmCadena ( char * p_cCadena, const char * p_cFormato, va_list valArgumentos, int iMaxTam );




#endif






