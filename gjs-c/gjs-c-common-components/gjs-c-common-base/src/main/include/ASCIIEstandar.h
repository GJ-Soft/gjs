/******************************************************************************/
/*                              ASCIIEstandar.h                               */
/*----------------------------------------------------------------------------*/
/* Librería:  GBase                                                           */
/* Versión:   1.0.0                                                           */
/* Fecha:     28/06/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene los prototipos de algunas rutinas de      */
/* carácter general de consulta y conversión de carácteres en la              */
/* codificación ASCII estandar (0-127).                                       */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_ASCIIESTANDAR_H
#define _ORG_GJS_C_CC_ASCIIESTANDAR_H


#include <BaseConfig.h>
#include <ASCIICodigos.h>




int ASCIICodigo ( char cVal );
char ASCIICaracter ( int iCod );

int ASCIIEsCodigoControl ( char cVal );
int ASCIIEsCodigoNoImprimible ( char cVal );
int ASCIIEsCodigoControlImprimible ( char cVal );
int ASCIIEsNUL ( char cVal );
int ASCIIEsSOH ( char cVal );
int ASCIIEsSTX ( char cVal );
int ASCIIEsETX ( char cVal );
int ASCIIEsEOT ( char cVal );
int ASCIIEsENQ ( char cVal );
int ASCIIEsACK ( char cVal );
int ASCIIEsBEL ( char cVal );
int ASCIIEsBS  ( char cVal );
int ASCIIEsTAB ( char cVal );
int ASCIIEsLF ( char cVal );
int ASCIIEsVT ( char cVal );
int ASCIIEsFF ( char cVal );
int ASCIIEsCR ( char cVal );
int ASCIIEsSO ( char cVal );
int ASCIIEsST ( char cVal );
int ASCIIEsSLE ( char cVal );
int ASCIIEsDC1 ( char cVal );
int ASCIIEsDC2 ( char cVal );
int ASCIIEsDC3 ( char cVal );
int ASCIIEsDC4 ( char cVal );
int ASCIIEsNAK ( char cVal );
int ASCIIEsSYN ( char cVal );
int ASCIIEsETB ( char cVal );
int ASCIIEsCAN ( char cVal );
int ASCIIEsEM ( char cVal );
int ASCIIEsSTB ( char cVal );
int ASCIIEsESC ( char cVal );
int ASCIIEsFS ( char cVal );
int ASCIIEsGS ( char cVal );
int ASCIIEsRS ( char cVal );
int ASCIIEsUS ( char cVal );
int ASCIIEsDEL ( char cVal );



#endif






