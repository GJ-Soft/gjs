/******************************************************************************/
/*                                OrdenBytes.h                                */
/*----------------------------------------------------------------------------*/
/* Librería:  GBase                                                           */
/* Versión:   1.0.0                                                           */
/* Fecha:     28/06/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene los prototipos de unas cuantas rutinas    */
/* para detectar el orden de bytes en memoria de la máquina: big endian,      */
/* little endian o mixto.                                                     */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_ORDENBYTES_H
#define _ORG_GJS_C_CC_ORDENBYTES_H


#include <BaseConfig.h>




#define BYTE_ORDEN_INVERTIDO		0
#define BYTE_ORDEN_NORMAL			1
#define BYTE_ORDEN_MIXTO			2







int BytesOrden4 ();
int BytesOrden2 ();

int BytesOrdenNormal ();
int BytesOrdenInvertido ();
int BytesOrdenMixto ();

int * BytesOrden ();

int BytesInvertir ( byte * p_byValor, int iTam, int iSoloSiOrdenInvertido );
int BytesInvertirEntero ( int * p_iValor, int iSoloSiOrdenInvertido );
int BytesInvertirEnteroLargo ( long * p_lValor, int iSoloSiOrdenInvertido );
int BytesInvertirReal ( float * p_fValor, int iSoloSiOrdenInvertido );
int BytesInvertirRealDoble ( double * p_dValor, int iSoloSiOrdenInvertido );
int BytesInvertirCaracter ( unichar * p_cValor, int iSoloSiOrdenInvertido );

int BytesPonerEnOrdenInvertido ( byte * p_byValor, int iTam );
int BytesPonerEnOrdenInvertidoEntero ( int * p_iValor );
int BytesPonerEnOrdenInvertidoEnteroLargo ( long * p_lValor );
int BytesPonerEnOrdenInvertidoReal ( float * p_fValor );
int BytesPonerEnOrdenInvertidoRealDoble ( double * p_dValor );
int BytesPonerEnOrdenInvertidoCaracter ( unichar * p_cValor );

int BytesPonerEnOrdenNormal ( byte * p_byValor, int iTam );
int BytesPonerEnOrdenNormalEntero ( int * p_iValor );
int BytesPonerEnOrdenNormalEnteroLargo ( long * p_lValor );
int BytesPonerEnOrdenNormalReal ( float * p_fValor );
int BytesPonerEnOrdenNormalRealDoble ( double * p_dValor );
int BytesPonerEnOrdenNormalCaracter ( unichar * p_cValor );

int BytesOrdenar ( byte * p_byValor, int iTam, int iOrden );
int BytesOrdenarEntero ( int * p_iValor, int iOrden );
int BytesOrdenarEnteroLargo ( long * p_lValor, int iOrden );
int BytesOrdenarReal ( float * p_fValor, int iOrden );
int BytesOrdenarRealDoble ( double * p_dValor, int iOrden );
int BytesOrdenarCaracter ( unichar * p_cValor, int iOrden );


#endif






