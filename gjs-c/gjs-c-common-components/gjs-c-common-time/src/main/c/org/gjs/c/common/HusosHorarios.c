#include "HusosHorarios.h"

#include "Calculo.h"
#include "TiempoConfig.h"



int HusEsValido ( int iHuso )
{
	int iRes;

	if ( ( iHuso >= 0 ) && ( iHuso < 25 ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int HusId ( int iGrad, int iMin, int iSeg )
{
	int iRes;

	if ( ( ( iGrad > -180 ) && ( iGrad < 180 ) &&
		   ( iMin >= 0 ) && ( iMin < 60 ) &&
		   ( iSeg >= 0 ) && ( iSeg < 60 ) ) ||
		 ( ( iGrad == 180 ) && ( iMin == 0 ) && ( iSeg == 0 ) ) )
	{
		iRes = iGrad / GEO_HUS_GRADOS;
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int HusIdAng ( double dAng )
{
	int iRes;

	if ( ( dAng > -180.0 ) && ( dAng <= 180.0 ) )
	{
		iRes = ConvRealDobleAEntero ( dAng / GEO_HUS_GRADOS, 0 );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int HusGradosMeridianoEste ( int iHuso )
{
	int iRes;

	if ( HusEsValido ( iHuso ) == 1 )
	{
		if ( iHuso < GEO_HUS_345 )
		{
			iRes = ( iHuso + 1 ) * GEO_HUS_GRADOS;
		}
		else
		{
			iRes = 0;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int HusGradosMeridianoOeste ( int iHuso )
{
	int iRes;

	if ( HusEsValido ( iHuso ) == 1 )
	{
		iRes = iHuso * GEO_HUS_GRADOS;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

double HusAnguloMeridianoEste ( int iHuso )
{
	double dRes;

	if ( HusEsValido ( iHuso ) == 1 )
	{
		if ( iHuso < GEO_HUS_345 )
		{
			dRes = ( iHuso + 1 ) * PI / 12;
		}
		else
		{
			dRes = 0.0;
		}
	}
	else
	{
		dRes = 0;
	}
	return ( dRes );
}

double HusAnguloMeridianoOeste ( int iHuso )
{
	double dRes;

	if ( HusEsValido ( iHuso ) == 1 )
	{
		dRes = iHuso * PI / 12;
	}
	else
	{
		dRes = 0;
	}
	return ( dRes );
}

