/******************************************************************************/
/*                                 SCampo.h                                  */
/*----------------------------------------------------------------------------*/
/* Librería:  Texto                                                           */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene la definición de la clase de datos        */
/* SCampo, destinada a gestionar el mantenimiento de una cadena que          */
/* almacene un dato etiquetado como Nombre.                                   */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_SCAMPO_H
#define _ORG_GJS_C_CC_SCAMPO_H





#include <SCadena.h>


typedef int (* PFUNINTPCAD)(SCadena *);



typedef struct 
{
	SCadena *		p_cadValor;
	PFUNINTPCAD		fValidacion;

} SCampo;




SCampo * SCampCrearDef ( PFUNINTPCAD fValidacion );
SCampo * SCampCrear ( PFUNINTPCAD fValidacion, int iMaxTam );

void SCampDestruir ( SCampo ** p_p_campObj );

int SCampMaxLongitud ( SCampo * p_campObj );
int SCampLongitud ( SCampo * p_campObj );

SCadena * SCampValor ( SCampo * p_campObj );
const char * SCampValorLit ( SCampo * p_campObj );

int SCampEsValido ( SCampo * p_campObj );

int SCampEstablecer ( SCampo * p_campObj, SCadena * p_cadValor );
int SCampEstablecerLit ( SCampo * p_campObj, const char * p_cValor );

int SCampLimpiar ( SCampo * p_campObj );
int SCampEstaVacio ( SCampo * p_campObj );

int SCampAsignar ( SCampo * p_campObj, SCampo * p_campValor );
SCampo * SCampDuplicar ( SCampo * p_campObj );

int SCampEsIgual ( SCampo * p_campObj, SCampo * p_campValor );
int SCampEsMenor ( SCampo * p_campObj, SCampo * p_campValor );
int SCampEsMayor ( SCampo * p_campObj, SCampo * p_campValor );
int SCampEsDiferente ( SCampo * p_campObj, SCampo * p_campValor );
int SCampEsMenorIg ( SCampo * p_campObj, SCampo * p_campValor );
int SCampEsMayorIg ( SCampo * p_campObj, SCampo * p_campValor );

int SCampEsIgualCad ( SCampo * p_campObj, SCadena * p_cadValor );
int SCampEsMenorCad ( SCampo * p_campObj, SCadena * p_cadValor );
int SCampEsMayorCad ( SCampo * p_campObj, SCadena * p_cadValor );
int SCampEsDiferenteCad ( SCampo * p_campObj, SCadena * p_cadValor );
int SCampEsMenorIgCad ( SCampo * p_campObj, SCadena * p_cadValor );
int SCampEsMayorIgCad ( SCampo * p_campObj, SCadena * p_cadValor );

int SCampEsIgualLit ( SCampo * p_campObj, const char * p_cadValor );
int SCampEsMenorLit ( SCampo * p_campObj, const char * p_cadValor );
int SCampEsMayorLit ( SCampo * p_campObj, const char * p_cadValor );
int SCampEsDiferenteLit ( SCampo * p_campObj, const char * p_cadValor );
int SCampEsMenorIgLit ( SCampo * p_campObj, const char * p_cadValor );
int SCampEsMayorIgLit ( SCampo * p_campObj, const char * p_cadValor );

int SCampComparar ( SCampo * p_campObj, SCampo * p_campValor );
int SCampCompararCad ( SCampo * p_campObj, SCadena * p_cadValor );
int SCampCompararLit ( SCampo * p_campObj, const char * p_cValor );

int SCampCumpleExpReg ( SCampo * p_campObj, const char * p_cExpReg );



#endif

