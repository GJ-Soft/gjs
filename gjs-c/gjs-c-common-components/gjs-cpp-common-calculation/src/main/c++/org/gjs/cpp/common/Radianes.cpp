
#include "Radianes.h"

#include "CommonCalculationConfig.h"




bool RadEntreCeroY2Pi ( double dRadianes )
{
	bool bRes;

	if ( ( dRadianes >= 0.0 ) && ( dRadianes < D_PI ) )
	{
		bRes = true;
	}
	else
	{
		bRes = false;
	}
	return ( bRes );
}

bool RadEntreMenosPiYPi ( double dRadianes )
{
	bool bRes;

	if ( ( dRadianes >= -PI ) && ( dRadianes <= PI ) )
	{
		bRes = true;
	}
	else
	{
		bRes = false;
	}
	return ( bRes );
}

int RadNumeroVueltas  ( double dRadianes )
{
	return ( ToInt ( trunc ( dRadianes / D_PI ) ) );
}

int RadCuadrante  ( double dRadianes )
{
	double dNorm;

	dNorm = RadNormalizar ( dRadianes, 0 );
	return ( ( ToInt ( trunc ( dNorm / PI_M ) ) % 4 ) + 1 );
}

int RadSemiplanoX  ( double dRadianes )
{
	double dNorm;

	dNorm = RadNormalizar ( dRadianes, 0 );
	return ( ( ToInt ( trunc ( dNorm / PI ) ) % 2 ) + 1 );
}

int RadSemiplanoY  ( double dRadianes )
{
	int iRes;
	int iCuad;

	iCuad = RadCuadrante ( dRadianes );
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

double RadNormalizar ( double dRadianes, int iNegativos )
{
	double dRes;

	if ( iNegativos == 1 )
	{
		dRes = fmod ( dRadianes, D_PI );
	}
	else
	{
		dRes = fmod ( dRadianes, D_PI );
		if ( dRes < 0.0 )
		{
			dRes = D_PI - fabs ( dRes );
		}
	}
	return ( dRes );
}

double RadNormalizarPi ( double dRadianes )
{
	double dRes;

	dRes = fmod ( dRadianes, PI );
	return ( dRes );
}

double RadNormalizarPiMedios ( double dRadianes )
{
	double dRes;

	dRes = fmod ( dRadianes, PI_M );
	return ( dRes );
}

double RadObtenerAngulo ( double dRadianes )
{
	double dRes;

	dRes = ( dRadianes * 180.0 ) / PI;
	return ( dRes );
}

double RadEstablecerAngulo ( double dAngulo )
{
	double dRes;

	dRes =  dAngulo * PI / 180.0;
	return ( dRes );
}

