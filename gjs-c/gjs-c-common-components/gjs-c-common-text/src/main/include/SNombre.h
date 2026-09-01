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





#include <SCampo.h>




typedef struct 
{
	SCampo *	p_campValor;

} SNombre;




SNombre * SNomCrearDef ();
SNombre * SNomCrear ( int iMaxTam );
SNombre * SNomCrearValor ( SCadena * p_cadValor );
SNombre * SNomCrearValorLit ( const char * p_cValor );
SNombre * SNomCrearValorExt ( SCadena * p_cadValor, int iMaxTam );
SNombre * SNomCrearValorLitExt ( const char * p_cValor, int iMaxTam );

void SNomDestruir ( SNombre ** p_p_nomObj );

int SNomMaxLongitud ( SNombre * p_nomObj );
int SNomLongitud ( SNombre * p_nomObj );

SCadena * SNomValor ( SNombre * p_nomObj );
const char * SNomValorLit ( SNombre * p_nomObj );

int SNomEsValido ( SNombre * p_nomObj );

int SNomEstablecer ( SNombre * p_nomObj, SCadena * p_cadValor );
int SNomEstablecerLit ( SNombre * p_nomObj, const char * p_cValor );

int SNomLimpiar ( SNombre * p_nomObj );
int SNomEstaVacio ( SNombre * p_nomObj );

int SNomAsignar ( SNombre * p_nomObj, SNombre * p_nomValor );
int SNomAsignarCampo ( SNombre * p_nomObj, SCampo * p_campValor );
SNombre * SNomDuplicar ( SNombre * p_nomObj );

int SNomEsIgual ( SNombre * p_nomObj, SNombre * p_nomValor );
int SNomEsMenor ( SNombre * p_nomObj, SNombre * p_nomValor );
int SNomEsMayor ( SNombre * p_nomObj, SNombre * p_nomValor );
int SNomEsDiferente ( SNombre * p_nomObj, SNombre * p_nomValor );
int SNomEsMenorIg ( SNombre * p_nomObj, SNombre * p_nomValor );
int SNomEsMayorIg ( SNombre * p_nomObj, SNombre * p_nomValor );

int SNomEsIgualCampo ( SNombre * p_nomObj, SCampo * p_campValor );
int SNomEsMenorCampo ( SNombre * p_nomObj, SCampo * p_campValor );
int SNomEsMayorCampo ( SNombre * p_nomObj, SCampo * p_campValor );
int SNomEsDiferenteCampo ( SNombre * p_nomObj, SCampo * p_campValor );
int SNomEsMenorIgCampo ( SNombre * p_nomObj, SCampo * p_campValor );
int SNomEsMayorIgCampo ( SNombre * p_nomObj, SCampo * p_campValor );

int SNomEsIgualCad ( SNombre * p_nomObj, SCadena * p_cadValor );
int SNomEsMenorCad ( SNombre * p_nomObj, SCadena * p_cadValor );
int SNomEsMayorCad ( SNombre * p_nomObj, SCadena * p_cadValor );
int SNomEsDiferenteCad ( SNombre * p_nomObj, SCadena * p_cadValor );
int SNomEsMenorIgCad ( SNombre * p_nomObj, SCadena * p_cadValor );
int SNomEsMayorIgCad ( SNombre * p_nomObj, SCadena * p_cadValor );

int SNomEsIgualLit ( SNombre * p_nomObj, const char * p_cadValor );
int SNomEsMenorLit ( SNombre * p_nomObj, const char * p_cadValor );
int SNomEsMayorLit ( SNombre * p_nomObj, const char * p_cadValor );
int SNomEsDiferenteLit ( SNombre * p_nomObj, const char * p_cadValor );
int SNomEsMenorIgLit ( SNombre * p_nomObj, const char * p_cadValor );
int SNomEsMayorIgLit ( SNombre * p_nomObj, const char * p_cadValor );

int SNomComparar ( SNombre * p_nomObj, SNombre * p_nomValor );
int SNomCompararCampo ( SNombre * p_nomObj, SCampo * p_campValor );
int SNomCompararCad ( SNombre * p_nomObj, SCadena * p_cadValor );
int SNomCompararLit ( SNombre * p_nomObj, const char * p_cValor );

int SNomCumpleExpReg ( SNombre * p_nomObj, const char * p_cExpReg );


unsigned int SNomHash ( SNombre * p_nomObj );





#endif

