/******************************************************************************/
/*                            SistemaImpresoras.h                             */
/*----------------------------------------------------------------------------*/
/* Librería:  Sistema                                                         */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene los prototipos de algunas rutinas de      */
/* de carácter general de manejo de impresoras.                               */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_SISTEMAIMPRESORAS_H
#define _ORG_GJS_C_CC_SISTEMAIMPRESORAS_H





#include <Precompilacion.h>


#if ( defined ( WIN ) )



int SisImpresionPosible ();

int SisImprimir ( const char * p_cTexto );


#endif


#endif





