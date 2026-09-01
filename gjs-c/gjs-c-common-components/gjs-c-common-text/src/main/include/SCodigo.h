/******************************************************************************/
/*                                 SCodigo.h                                  */
/*----------------------------------------------------------------------------*/
/* Librería:  Texto                                                           */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene la definición de la clase de datos        */
/* SCodigo, destinada a gestionar el mantenimiento de una cadena que          */
/* almacene un dato etiquetado como Codigo.                                   */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_SCODIGO_H
#define _ORG_GJS_C_CC_SCODIGO_H





#include <SCampo.h>




typedef struct 
{
	SCampo *	p_campValor;

} SCodigo;




SCodigo * SCodCrearDef ();
SCodigo * SCodCrear ( int iMaxTam );
SCodigo * SCodCrearValor ( SCadena * p_cadValor );
SCodigo * SCodCrearValorLit ( const char * p_cValor );
SCodigo * SCodCrearValorExt ( SCadena * p_cadValor, int iMaxTam );
SCodigo * SCodCrearValorLitExt ( const char * p_cValor, int iMaxTam );

void SCodDestruir ( SCodigo ** p_p_codObj );

int SCodMaxLongitud ( SCodigo * p_codObj );
int SCodLongitud ( SCodigo * p_codObj );

SCadena * SCodValor ( SCodigo * p_codObj );
const char * SCodValorLit ( SCodigo * p_codObj );

int SCodEsValido ( SCodigo * p_codObj );

int SCodEstablecer ( SCodigo * p_codObj, SCadena * p_cadValor );
int SCodEstablecerLit ( SCodigo * p_codObj, const char * p_cValor );

int SCodLimpiar ( SCodigo * p_codObj );
int SCodEstaVacio ( SCodigo * p_codObj );

int SCodAsignar ( SCodigo * p_codObj, SCodigo * p_codValor );
int SCodAsignarCampo ( SCodigo * p_codObj, SCampo * p_campValor );
SCodigo * SCodDuplicar ( SCodigo * p_codObj );

int SCodEsIgual ( SCodigo * p_codObj, SCodigo * p_codValor );
int SCodEsMenor ( SCodigo * p_codObj, SCodigo * p_codValor );
int SCodEsMayor ( SCodigo * p_codObj, SCodigo * p_codValor );
int SCodEsDiferente ( SCodigo * p_codObj, SCodigo * p_codValor );
int SCodEsMenorIg ( SCodigo * p_codObj, SCodigo * p_codValor );
int SCodEsMayorIg ( SCodigo * p_codObj, SCodigo * p_codValor );

int SCodEsIgualCampo ( SCodigo * p_codObj, SCampo * p_campValor );
int SCodEsMenorCampo ( SCodigo * p_codObj, SCampo * p_campValor );
int SCodEsMayorCampo ( SCodigo * p_codObj, SCampo * p_campValor );
int SCodEsDiferenteCampo ( SCodigo * p_codObj, SCampo * p_campValor );
int SCodEsMenorIgCampo ( SCodigo * p_codObj, SCampo * p_campValor );
int SCodEsMayorIgCampo ( SCodigo * p_codObj, SCampo * p_campValor );

int SCodEsIgualCad ( SCodigo * p_codObj, SCadena * p_cadValor );
int SCodEsMenorCad ( SCodigo * p_codObj, SCadena * p_cadValor );
int SCodEsMayorCad ( SCodigo * p_codObj, SCadena * p_cadValor );
int SCodEsDiferenteCad ( SCodigo * p_codObj, SCadena * p_cadValor );
int SCodEsMenorIgCad ( SCodigo * p_codObj, SCadena * p_cadValor );
int SCodEsMayorIgCad ( SCodigo * p_codObj, SCadena * p_cadValor );

int SCodEsIgualLit ( SCodigo * p_codObj, const char * p_cadValor );
int SCodEsMenorLit ( SCodigo * p_codObj, const char * p_cadValor );
int SCodEsMayorLit ( SCodigo * p_codObj, const char * p_cadValor );
int SCodEsDiferenteLit ( SCodigo * p_codObj, const char * p_cadValor );
int SCodEsMenorIgLit ( SCodigo * p_codObj, const char * p_cadValor );
int SCodEsMayorIgLit ( SCodigo * p_codObj, const char * p_cadValor );

int SCodComparar ( SCodigo * p_codObj, SCodigo * p_codValor );
int SCodCompararCampo ( SCodigo * p_codObj, SCampo * p_campValor );
int SCodCompararCad ( SCodigo * p_codObj, SCadena * p_cadValor );
int SCodCompararLit ( SCodigo * p_codObj, const char * p_cValor );

int SCodCumpleExpReg ( SCodigo * p_codObj, const char * p_cExpReg );


unsigned int SCodHash ( SCodigo * p_codObj );



#endif

