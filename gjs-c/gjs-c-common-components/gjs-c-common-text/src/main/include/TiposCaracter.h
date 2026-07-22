/******************************************************************************/
/*                                  TiposCaracter.h                           */
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

#ifndef _ORG_GJS_C_CC_TIPOSCARACTER_H
#define _ORG_GJS_C_CC_TIPOSCARACTER_H







#define TIP_CAR_DIGITO						'9'
#define TIP_CAR_LETRA						'@'
#define TIP_CAR_SIGNO						'&'
#define TIP_CAR_ESPACIO						' '
#define TIP_CAR_LETRADIG					'#'
#define TIP_CAR_ALFANUMERICO				'$'
#define TIP_CAR_CUALQUIERA					'?'




int TipCarEsValido ( char cCod );

int TipCarEsCualquiera ( char cCod );
int TipCarEsDigito ( char cCod );
int TipCarEsLetra ( char cCod );
int TipCarEsSigno ( char cCod );
int TipCarEsLetraDigito ( char cCod );
int TipCarEsAlfanumerico ( char cCod );



#endif






