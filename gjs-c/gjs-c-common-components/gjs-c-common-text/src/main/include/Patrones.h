/******************************************************************************/
/*                               Patrones.h                                   */
/*----------------------------------------------------------------------------*/
/* Librería:  GTexto                                                          */
/* Versión:   1.0.0                                                           */
/* Fecha:     30-06-2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene la definición de constantes para las      */
/* diferentes páginas de código estándar existentes.                          */
/*----------------------------------------------------------------------------*/
/*                        gines-jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_PATRONES_H
#define _ORG_GJS_C_CC_PATRONES_H










char * PatCrear ( int iTam );

int PatEsValido ( const char * p_cPatron );
char PatCaracter ( char * p_cPatron, int iCar );
int PatEstablecerCaracter ( char * p_cPatron, int iCar, char cValor );


int PatEsSubpatron ( const char * p_cPatron, const char * p_cSubpatron );
int PatEvaluar ( const char * p_cPatron, const char * p_cCadena );
char * PatValorInicial ( const char * p_cPatron );
char * PatValorFinal ( const char * p_cPatron );
int PatIncrementarValor ( const char * p_cPatron, char * p_cCadena );
int PatDecrementarValor ( const char * p_cPatron, char * p_cCadena );
int PatIncrementarValorDesde ( const char * p_cPatron, char * p_cCadena, int iPos );
int PatDecrementarValorDesde ( const char * p_cPatron, char * p_cCadena, int iPos );



#endif






