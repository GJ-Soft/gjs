/******************************************************************************/
/*                                 SDescripcion.h                                  */
/*----------------------------------------------------------------------------*/
/* Librería:  Texto                                                           */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene la definición de la clase de datos        */
/* SDescripcion, destinada a gestionar el mantenimiento de una cadena que          */
/* almacene un dato etiquetado como Descripcion.                                   */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_SDESCRIPCION_H
#define _ORG_GJS_C_CC_SDESCRIPCION_H





#include <SCadena.h>




typedef struct 
{
	SCadena *	p_cadValor;

} SDescripcion;



SDescripcion * SDescCrearDef ();
SDescripcion * SDescCrear ( int iMaxTam );

void SDescDestruir ( SDescripcion ** p_p_descObj );

int SDescMaxLongitud ( SDescripcion * p_descObj );
int SDescLongitud ( SDescripcion * p_descObj );

SCadena * SDescValor ( SDescripcion * p_descObj );
const char * SDescValorConstante ( SDescripcion * p_descObj );

int SDescEstablecerCad ( SDescripcion * p_descObj, SCadena * p_cadValor );
int SDescEstablecer ( SDescripcion * p_descObj, const char * p_cValor );

int SDescLimpiar ( SDescripcion * p_descObj );
int SDescEstaVacio ( SDescripcion * p_descObj );




#endif

