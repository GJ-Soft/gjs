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

#ifndef _ORG_GJS_C_CC_CPP_ASCIIESTANDAR_H
#define _ORG_GJS_C_CC_CPP_ASCIIESTANDAR_H



#include <ASCIICodigos.h>




namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {



int ASCIICodigo ( char cVal );
char ASCIICaracter ( int iCod );

bool ASCIIEsCodigoControl ( char cVal );
bool ASCIIEsNUL ( char cVal );
bool ASCIIEsSOH ( char cVal );
bool ASCIIEsSTX ( char cVal );
bool ASCIIEsETX ( char cVal );
bool ASCIIEsEOT ( char cVal );
bool ASCIIEsENQ ( char cVal );
bool ASCIIEsACK ( char cVal );
bool ASCIIEsBEL ( char cVal );
bool ASCIIEsBS  ( char cVal );
bool ASCIIEsTAB ( char cVal );
bool ASCIIEsLF ( char cVal );
bool ASCIIEsVT ( char cVal );
bool ASCIIEsFF ( char cVal );
bool ASCIIEsCR ( char cVal );
bool ASCIIEsSO ( char cVal );
bool ASCIIEsST ( char cVal );
bool ASCIIEsSLE ( char cVal );
bool ASCIIEsDC1 ( char cVal );
bool ASCIIEsDC2 ( char cVal );
bool ASCIIEsDC3 ( char cVal );
bool ASCIIEsDC4 ( char cVal );
bool ASCIIEsNAK ( char cVal );
bool ASCIIEsSYN ( char cVal );
bool ASCIIEsETB ( char cVal );
bool ASCIIEsCAN ( char cVal );
bool ASCIIEsEM ( char cVal );
bool ASCIIEsSTB ( char cVal );
bool ASCIIEsESC ( char cVal );
bool ASCIIEsFS ( char cVal );
bool ASCIIEsGS ( char cVal );
bool ASCIIEsRS ( char cVal );
bool ASCIIEsUS ( char cVal );
bool ASCIIEsDEL ( char cVal );



			}
		}
	}
}


#endif






