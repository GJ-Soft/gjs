
#include "Radianes.h"

#include "CalculoConfig.h"




int RadEntreCeroY2Pi ( double dRadianes )
{
	int iRes;

	if ( ( dRadianes >= 0.0 ) && ( dRadianes < D_PI ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int RadEntreMenosPiYPi ( double dRadianes )
{
	int iRes;

	if ( ( dRadianes >= -PI ) && ( dRadianes <= PI ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int RadNumeroVueltas  ( double dRadianes )
{
	return ( ConvRealDobleAEntero ( dRadianes / D_PI, 1 ) );
}

int RadCuadrante  ( double dRadianes )
{
	double dNorm;

	dNorm = RadNormalizar ( dRadianes, 0 );
	return ( ( ConvRealDobleAEntero ( dNorm / PI_M, 1 ) % 4 ) + 1 );
}

int RadSemiplanoX  ( double dRadianes )
{
	double dNorm;

	dNorm = RadNormalizar ( dRadianes, 0 );
	return ( ( ConvRealDobleAEntero ( dNorm / PI, 1 ) % 2 ) + 1 );
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

