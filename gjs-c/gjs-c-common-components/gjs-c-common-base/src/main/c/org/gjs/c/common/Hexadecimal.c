/******************************************************************************/
/*                              Hexadecimal.cpp                               */
/*----------------------------------------------------------------------------*/
/* Librería:  GBase                                                           */
/* Versión:   1.0.0                                                           */
/* Fecha:     28/06/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de código fuente que contiene la implementación de las rutinas     */
/* de carácter general de manejo de valores hexadecimales.                    */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#include "Hexadecimal.h"






int HexEsValido ( char cVal )
{
	int iRes;

	if ( ( ( cVal >= '0' ) && ( cVal <= '9' ) ) ||
		 ( ( cVal >= 'A' ) && ( cVal <= 'F' ) ) ||
		 ( ( cVal >= 'a' ) && ( cVal <= 'f' ) ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int HexEsNumValido ( int iVal )
{
	int iRes;

	if ( ( iVal >= 0 ) && ( iVal < 16 ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int HexValor ( char cVal )
{
	int iRes;

	if ( ( cVal >= '0' ) && ( cVal <= '9' ) ) 
	{
		iRes = (int) cVal - (int) '0';
	}
	else if ( ( cVal >= 'A' ) && ( cVal <= 'F' ) ) 
	{
		iRes = 10 + ( (int) cVal - (int) 'A' );
	}
	else if ( ( cVal >= 'a' ) && ( cVal <= 'f' ) )
	{
		iRes = 10 + ( (int) cVal - (int) 'a' );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

char HexDigito ( int iVal )
{
	char cRes;

	if ( ( iVal >= 0 ) && ( iVal < 10 ) )
	{
		cRes = (char)( (int) '0' + iVal );
	}
	else if ( ( iVal >= 10 ) && ( iVal < 16 ) )
	{
		cRes = (char)( (int) 'A' + ( iVal - 10 ) );
	}
	else
	{
		cRes = (char) 0;
	}
	return ( cRes );
}










