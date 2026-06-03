/******************************************************************************/
/*                                  Tipos.h                                   */
/*----------------------------------------------------------------------------*/
/* Librería:  GBase                                                           */
/* Versión:   1.0.0                                                           */
/* Fecha:     28/06/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene la definición de los diferentes           */
/* super-tipos de datos, junto con algunas rutinas de validación, consulta    */
/* y manejo de los mismos.                                                    */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_TIPOS_H
#define _ORG_GJS_C_CC_TIPOS_H






/* Tipos especiales: */
#define TIP_NINGUNO						-1
#define TIP_DESCONOCIDO					0

/* Tipos básicos: */
#define TIP_NUMERO						1
#define TIP_CARACTER					2
#define TIP_BOOLEANO					3
#define TIP_BYTE						4

/* Tipos básicos de tipo vector : */
#define TIP_CADENA						5
#define TIP_BINARIO						6

/* Tipos básicos especiales: */
#define TIP_OBJETO						7
#define TIP_TIEMPO						8

/* Subtipos numéricos: */
#define TIP_NUMERO_NATURAL				10
#define TIP_NUMERO_ENTERO				11
#define TIP_NUMERO_REAL					12
#define TIP_NUMERO_HEXADECIMAL			13

/* Subtipos binarios: */
#define TIP_BINARIO_16					60
#define TIP_BINARIO_32					61
#define TIP_BINARIO_64					62
#define TIP_BINARIO_128					63

/* Subtipos fecha: */
#define TIP_TIEMPO_FECHA				80
#define TIP_TIEMPO_HORA					81
#define TIP_TIEMPO_FECHA_HORA			82



#define TIP_TXT_NINGUNO					"Ninguno"
#define TIP_TXT_DESCONOCIDO				"Desconocido"
#define TIP_TXT_NUMERO					"Numero"
#define TIP_TXT_CARACTER				"Caracter"
#define TIP_TXT_BYTE					"Byte"
#define TIP_TXT_CADENA					"Cadena"
#define TIP_TXT_BOOLEANO				"Booleano"
#define TIP_TXT_TIEMPO					"Tiempo"
#define TIP_TXT_BINARIO					"Binario"
#define TIP_TXT_OBJETO					"Objeto"
#define TIP_TXT_NUMERO_NATURAL			"Natural"
#define TIP_TXT_NUMERO_ENTERO			"Entero"
#define TIP_TXT_NUMERO_REAL				"Real"
#define TIP_TXT_NUMERO_HEXADECIMAL		"Hexadecimal"
#define TIP_TXT_BINARIO_16				"Word"
#define TIP_TXT_BINARIO_32				"DWord"
#define TIP_TXT_BINARIO_64				"QWord"
#define TIP_TXT_BINARIO_128				"OWord"
#define TIP_TXT_TIEMPO_FECHA			"Fecha"
#define TIP_TXT_TIEMPO_HORA				"Hora"
#define TIP_TXT_TIEMPO_FECHA_HORA		"FechaHora"






const char * TipLiteral ( int iCod );
int TipCodigo ( const char * p_cTipo );
int TipEsValido ( int iCod );
int TipEsEstrictamenteValido ( int iCod );

int TipEsNinguno ( int iCod );
int TipEsDesconocido ( int iCod );
int TipEsNumero ( int iCod );
int TipEsCadena ( int iCod );
int TipEsBooleano ( int iCod );
int TipEsCaracter ( int iCod );
int TipEsByte ( int iCod );
int TipEsFecha ( int iCod );
int TipEsBinario ( int iCod );
int TipEsObjeto ( int iCod );
int TipEsTiempo ( int iCod );

int TipEsNatural ( int iCod );
int TipEsEntero ( int iCod );
int TipEsReal ( int iCod );
int TipEsHexadecimal ( int iCod );

int TipEsFecha ( int iCod );
int TipEsHora ( int iCod );
int TipEsFechaHora ( int iCod );

int TipEsDeTamVariable ( int iCod );
int TipTam ( int iCod );

#endif






