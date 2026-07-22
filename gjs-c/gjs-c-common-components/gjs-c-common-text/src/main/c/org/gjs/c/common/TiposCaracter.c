/******************************************************************************/
/*                               TiposCaracter.cpp                            */
/*----------------------------------------------------------------------------*/
/* Librería:  GTexto                                                          */
/* Versión:   1.0.0                                                           */
/* Fecha:     30-06-2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de código fuente que contiene la implementación de las rutinas     */
/* de ...                                                                     */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#include "TiposCaracter.h"

#include "TextoConfig.h"







int TipCarEsValido ( char cCod )
{
	int iRes;

	if ( ( cCod == TIP_CAR_DIGITO ) ||
		 ( cCod == TIP_CAR_LETRA ) ||
		 ( cCod == TIP_CAR_SIGNO ) ||
		 ( cCod == TIP_CAR_LETRADIG ) ||
		 ( cCod == TIP_CAR_ALFANUMERICO ) ||
		 ( cCod == TIP_CAR_CUALQUIERA ) )
	{
		iRes = 1;
	}
	else 
	{
		iRes = 0;
	}
	return ( iRes );
}

int TipCarEsDigito ( char cCod )
{
	int iRes;

	if ( cCod == TIP_CAR_DIGITO ) 
	{
		iRes = 1;
	}
	else 
	{
		iRes = 0;
	}
	return ( iRes );
}

int TipCarEsLetra ( char cCod )
{
	int iRes;

	if ( cCod == TIP_CAR_LETRA ) 
	{
		iRes = 1;
	}
	else 
	{
		iRes = 0;
	}
	return ( iRes );
}

int TipCarEsSigno ( char cCod )
{
	int iRes;

	if ( cCod == TIP_CAR_SIGNO )
	{
		iRes = 1;
	}
	else 
	{
		iRes = 0;
	}
	return ( iRes );
}

int TipCarEsLetraDigito ( char cCod )
{
	int iRes;

	if ( cCod == TIP_CAR_LETRADIG )
	{
		iRes = 1;
	}
	else 
	{
		iRes = 0;
	}
	return ( iRes );
}

int TipCarEsAlfanumerico ( char cCod )
{
	int iRes;

	if ( cCod == TIP_CAR_ALFANUMERICO )
	{
		iRes = 1;
	}
	else 
	{
		iRes = 0;
	}
	return ( iRes );
}

int TipCarEsCualquiera ( char cCod )
{
	int iRes;

	if ( cCod == TIP_CAR_CUALQUIERA )
	{
		iRes = 1;
	}
	else 
	{
		iRes = 0;
	}
	return ( iRes );
}

