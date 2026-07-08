/******************************************************************************/
/*                               CadenasBase.h                                */
/*----------------------------------------------------------------------------*/
/* Librería:  GBase                                                           */
/* Versión:   1.0.0                                                           */
/* Fecha:     28/06/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene los prototipos de unas cuantas rutinas    */
/* para el manejo general de cadenas.                                         */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _CADENASBASE_H
#define _CADENASBASE_H


#include <ConstantesBase.h>
#include <UniChar.h>




char * CadCrear ( int iLong );
int CadLongitud ( const char * p_cAsciiz );
int CadLongitudSeg ( const char * p_cAsciiz, int iMax );
void CadInicializar ( char * p_cAsciiz, int iMax );
char * CadDuplicar ( const char * p_cAsciiz );
char * CadDuplicarSeg ( const char * p_cAsciiz, int iMax );

unichar * CadUniCrear ( int iLong );
int CadUniLongitud ( const unichar * p_ucValor );
int CadUniLongitudSeg ( const unichar * p_ucValor, int iMax );
void CadUniInicializar ( unichar * p_ucValor, int iMax );
unichar * CadUniDuplicar ( const unichar * p_ucValor );


int CadComparar ( const char * p_cAsciiz1, const char * p_cAsciiz2 );
int CadCompararExt ( const char * p_cAsciiz1, const char * p_cAsciiz2, int iMax1, int iMax2 );

int CadEsAlfanumericoValido ( const char * p_cAsciiz );
int CadEsAlfanumericoValidoExt ( const char * p_cAsciiz, int iMax );

const char * CadValorSeguro ( const char * p_cAsciiz );
void CadImprimir ( const char * p_cAsciiz );
void CadImprimirEnLineas ( const char * p_cAsciiz, int iTamLinea );



#endif






