/******************************************************************************/
/*                                Angulos.cpp                                 */
/*----------------------------------------------------------------------------*/
/* Librer�a:  Calculo                                                         */
/* Versi�n:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Gin�s Jim�nez S�nchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripci�n:                                                               */
/* Fichero de cabecera que contiene la implementaci�n de algunas rutinas      */
/* que implementan algunas funciones sencillas de manejo de �ngulos.          */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#include "Angulos.h"

#include "CommonCalculationConfig.h"




bool AngEntreCeroY2Pi ( double dAngulo )
{
	bool bRes;

	if ( ( dAngulo >= 0.0 ) && ( dAngulo < 360.0 ) )
	{
		bRes = true;
	}
	else
	{
		bRes = false;
	}
	return ( bRes );
}

bool AngEntreMenosPiYPi ( double dAngulo )
{
	bool bRes;

	if ( ( dAngulo >= -180.0 ) && ( dAngulo <= 180.0 ) )
	{
		bRes = true;
	}
	else
	{
		bRes = false;
	}
	return ( bRes );
}

bool AngEntreMenosPiMediosYPiMedios ( double dAngulo )
{
	bool bRes;

	if ( ( dAngulo >= -90.0 ) && ( dAngulo <= 90.0 ) )
	{
		bRes = true;
	}
	else
	{
		bRes = false;
	}
	return ( bRes );
}

bool AngEntreCeroYPiMedios ( double dAngulo )
{
	bool bRes;

	if ( ( dAngulo >= 0.0 ) && ( dAngulo <= 90.0 ) )
	{
		bRes = true;
	}
	else
	{
		bRes = false;
	}
	return ( bRes );
}

double AngNormalizar ( double dAngulo, int iNegativos )
{
	double dRes;

	if ( iNegativos == 1 )
	{
		dRes = fmod ( dAngulo, 360.0 );
	}
	else
	{
		dRes = fmod ( dAngulo, 360.0 );
		if ( dRes < 0.0 )
		{
			dRes = 360.0 - fabs ( dRes );
		}
	}
	return ( dRes );
}

double AngNormalizarPi ( double dAngulo )
{
	double dRes;

	dRes = fmod ( dAngulo, 180.0 );
	return ( dRes );
}

double AngNormalizarPiMedios ( double dAngulo )
{
	double dRes;

	dRes = fmod ( dAngulo, 90.0 );
	return ( dRes );
}

int AngNumeroVueltas  ( double dAngulo )
{
	return ( ToInt ( trunc ( dAngulo / 360.0 ) ) );
}

int AngCuadrante  ( double dAngulo )
{
	double dNorm;

	dNorm = AngNormalizar ( dAngulo, 0 );
	return ( ( ToInt ( trunc ( dNorm / 90.0 ) ) % 4 ) + 1 );
}

int AngSemiplanoX  ( double dAngulo )
{
	double dNorm;

	dNorm = AngNormalizar ( dAngulo, 0 );
	return ( ( ToInt ( trunc ( dNorm / 180.0 ) ) % 2 ) + 1 );
}

int AngSemiplanoY  ( double dAngulo )
{
	int iRes;
	int iCuad;

	iCuad = AngCuadrante ( dAngulo );
	if ( ( iCuad == 1 ) || ( iCuad == 4 ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 2;
	}
	return ( iRes );
}

double AngObtenerRadianes ( double dAngulo )
{
	double dRes;

	dRes = ( dAngulo * PI_32 ) / 180.0;
	return ( dRes );
}

double AngEstablecerRadianes ( double dRadianes )
{
	double dRes;

	dRes = ( dRadianes * 180.0 ) / PI;
	return ( dRes );
}

