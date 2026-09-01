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





#include <SCampo.h>






typedef struct 
{
	SCampo *	p_campValor;

} SDescripcion;



SDescripcion * SDescCrearDef ();
SDescripcion * SDescCrear ( int iMaxTam );
SDescripcion * SDescCrearValor ( SCadena * p_cadValor );
SDescripcion * SDescCrearValorLit ( const char * p_cValor );
SDescripcion * SDescCrearValorExt ( SCadena * p_cadValor, int iMaxTam );
SDescripcion * SDescCrearValorLitExt ( const char * p_cValor, int iMaxTam );


void SDescDestruir ( SDescripcion ** p_p_descObj );

int SDescMaxLongitud ( SDescripcion * p_descObj );
int SDescLongitud ( SDescripcion * p_descObj );

SCadena * SDescValor ( SDescripcion * p_descObj );
const char * SDescValorLit ( SDescripcion * p_descObj );

int SDescEsValida ( SDescripcion * p_descObj );

int SDescEstablecer ( SDescripcion * p_descObj, SCadena * p_cadValor );
int SDescEstablecerLit ( SDescripcion * p_descObj, const char * p_cValor );

int SDescLimpiar ( SDescripcion * p_descObj );
int SDescEstaVacia ( SDescripcion * p_descObj );

int SDescAsignar ( SDescripcion * p_descObj, SDescripcion * p_descValor );
int SDescAsignarCampo ( SDescripcion * p_descObj, SCampo * p_campValor );
SDescripcion * SDescDuplicar ( SDescripcion * p_descObj );

int SDescEsIgual ( SDescripcion * p_descObj, SDescripcion * p_descValor );
int SDescEsMenor ( SDescripcion * p_descObj, SDescripcion * p_descValor );
int SDescEsMayor ( SDescripcion * p_descObj, SDescripcion * p_descValor );
int SDescEsDiferente ( SDescripcion * p_descObj, SDescripcion * p_descValor );
int SDescEsMenorIg ( SDescripcion * p_descObj, SDescripcion * p_descValor );
int SDescEsMayorIg ( SDescripcion * p_descObj, SDescripcion * p_descValor );

int SDescEsIgualCampo ( SDescripcion * p_descObj, SCampo * p_campValor );
int SDescEsMenorCampo ( SDescripcion * p_descObj, SCampo * p_campValor );
int SDescEsMayorCampo ( SDescripcion * p_descObj, SCampo * p_campValor );
int SDescEsDiferenteCampo ( SDescripcion * p_descObj, SCampo * p_campValor );
int SDescEsMenorIgCampo ( SDescripcion * p_descObj, SCampo * p_campValor );
int SDescEsMayorIgCampo ( SDescripcion * p_descObj, SCampo * p_campValor );

int SDescEsIgualCad ( SDescripcion * p_descObj, SCadena * p_cadValor );
int SDescEsMenorCad ( SDescripcion * p_descObj, SCadena * p_cadValor );
int SDescEsMayorCad ( SDescripcion * p_descObj, SCadena * p_cadValor );
int SDescEsDiferenteCad ( SDescripcion * p_descObj, SCadena * p_cadValor );
int SDescEsMenorIgCad ( SDescripcion * p_descObj, SCadena * p_cadValor );
int SDescEsMayorIgCad ( SDescripcion * p_descObj, SCadena * p_cadValor );

int SDescEsIgualLit ( SDescripcion * p_descObj, const char * p_cadValor );
int SDescEsMenorLit ( SDescripcion * p_descObj, const char * p_cadValor );
int SDescEsMayorLit ( SDescripcion * p_descObj, const char * p_cadValor );
int SDescEsDiferenteLit ( SDescripcion * p_descObj, const char * p_cadValor );
int SDescEsMenorIgLit ( SDescripcion * p_descObj, const char * p_cadValor );
int SDescEsMayorIgLit ( SDescripcion * p_descObj, const char * p_cadValor );

int SDescComparar ( SDescripcion * p_descObj, SDescripcion * p_descValor );
int SDescCompararCampo ( SDescripcion * p_descObj, SCampo * p_campValor );
int SDescCompararCad ( SDescripcion * p_descObj, SCadena * p_cadValor );
int SDescCompararLit ( SDescripcion * p_descObj, const char * p_cValor );

int SDescCumpleExpReg ( SDescripcion * p_descObj, const char * p_cExpReg );




#endif

