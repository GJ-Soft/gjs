/******************************************************************************/
/*                                 SNombre.h                                  */
/*----------------------------------------------------------------------------*/
/* Librería:  Texto                                                           */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene la definición de la clase de datos        */
/* SNombre, destinada a gestionar el mantenimiento de una cadena que          */
/* almacene un dato etiquetado como Nombre.                                   */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_SNOMBRE_H
#define _ORG_GJS_C_CC_SNOMBRE_H





#include <SCadena.h>




typedef struct 
{
	SCadena *	p_cadValor;

} SNombre;




SNombre * SNomCrearDef ();
SNombre * SNomCrear ( int iMaxTam );

void SNomDestruir ( SNombre ** p_p_nomObj );

int SNomMaxLongitud ( SNombre * p_nomObj );
int SNomLongitud ( SNombre * p_nomObj );

SCadena * SNomValor ( SNombre * p_nomObj );
const char * SNomValorConstante ( SNombre * p_nomObj );

int SNomEstablecerCad ( SNombre * p_nomObj, SCadena * p_cadValor );
int SNomEstablecer ( SNombre * p_nomObj, const char * p_cValor );

int SNomLimpiar ( SNombre * p_nomObj );
int SNomEstaVacio ( SNombre * p_nomObj );




#endif

