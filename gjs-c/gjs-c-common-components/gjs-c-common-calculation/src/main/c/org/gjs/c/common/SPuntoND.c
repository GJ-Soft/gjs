#include "SPuntoND.h"

#include "CalculoConfig.h"
#include "CalculoOperaciones.h"




/* 1 si el punto es valido y iCoord esta entre 1 y su dimension. */
static int _SPntNDEsCoordenada ( SPuntoND * p_pntObj, int iCoord )
{
	int iRes;

	if ( SPntNDEsValido ( p_pntObj ) == 1 )
	{
		if ( iCoord > 0 )
		{
			if ( iCoord <= p_pntObj->iDims )
			{
				iRes = 1;
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
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SPuntoND * SPntNDCrear ( int iDims )
{
	SPuntoND * 	p_pntObj;
	int 		iCoord;

	if ( iDims > 0 )
	{
		p_pntObj = (SPuntoND *) MemReservar ( sizeof ( SPuntoND ) );
		if ( ES_VALIDO ( p_pntObj ) )
		{
			p_pntObj->iDims = iDims;
			p_pntObj->p_dX = (double *) MemReservar ( iDims * sizeof ( double ) );
			if ( ES_VALIDO ( p_pntObj->p_dX ) )
			{
				for ( iCoord = 0; iCoord < iDims; iCoord = iCoord + 1 )
				{
					p_pntObj->p_dX [ iCoord ] = 0.0;
				}
			}
			else
			{
				MemLiberar ( (void **) &p_pntObj );
			}
		}
	}
	else
	{
		p_pntObj = NULL;
	}
	return ( p_pntObj );
}

SPuntoND * SPntNDCrearExt ( int iDims, const double * p_dValores )
{
	SPuntoND * 	p_pntObj;
	int 		iCoord;

	if ( ES_VALIDO ( p_dValores ) )
	{
		p_pntObj = SPntNDCrear ( iDims );
		if ( ES_VALIDO ( p_pntObj ) )
		{
			for ( iCoord = 0; iCoord < iDims; iCoord = iCoord + 1 )
			{
				p_pntObj->p_dX [ iCoord ] = p_dValores [ iCoord ];
			}
		}
	}
	else
	{
		p_pntObj = NULL;
	}
	return ( p_pntObj );
}

SPuntoND * SPntNDEncapsular ( int iDims, double * p_dValores )
{
	SPuntoND * 	p_pntObj;

	if ( iDims > 0 )
	{
		if ( ES_VALIDO ( p_dValores ) )
		{
			p_pntObj = (SPuntoND *) MemReservar ( sizeof ( SPuntoND ) );
			if ( ES_VALIDO ( p_pntObj ) )
			{
				p_pntObj->iDims = iDims;
				p_pntObj->p_dX = p_dValores;
			}
		}
		else
		{
			p_pntObj = NULL;
		}
	}
	else
	{
		p_pntObj = NULL;
	}
	return ( p_pntObj );
}

void SPntNDDestruir ( SPuntoND ** p_p_pntObj )
{
	SPuntoND * p_pntObj;

	if ( ES_VALIDO ( p_p_pntObj ) )
	{
		p_pntObj = *p_p_pntObj;
		if ( ES_VALIDO ( p_pntObj ) )
		{
			MemLiberar ( (void **) &(p_pntObj->p_dX) );
			MemLiberar ( (void **) p_p_pntObj );
		}
	}
}

int SPntNDDim ( SPuntoND * p_pntObj )
{
	int iRes;

	if ( SPntNDEsValido ( p_pntObj ) == 1 )
	{
		iRes = p_pntObj->iDims;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

double SPntNDX ( SPuntoND * p_pntObj, int iCoord )
{
	double dRes;

	if ( _SPntNDEsCoordenada ( p_pntObj, iCoord ) == 1 )
	{
		dRes = p_pntObj->p_dX [ iCoord - 1 ];
	}
	else
	{
		dRes = 0.0;
	}
	return ( dRes );
}

int SPntNDEsValido ( SPuntoND * p_pntObj )
{
	int iRes;

	if ( ES_VALIDO ( p_pntObj ) )
	{
		if ( p_pntObj->iDims > 0 )
		{
			if ( ES_VALIDO ( p_pntObj->p_dX ) )
			{
				iRes = 1;
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
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SPntNDEstablecerX ( SPuntoND * p_pntObj, int iCoord, double dX )
{
	int iRes;

	if ( _SPntNDEsCoordenada ( p_pntObj, iCoord ) == 1 )
	{
		p_pntObj->p_dX [ iCoord - 1 ] = dX;
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SPntNDAsignar ( SPuntoND * p_pntObj, SPuntoND * p_pntVal )
{
	int	iCoord;
	int iRes;

	if ( SPntNDEsCompatible ( p_pntObj, p_pntVal ) == 1 )
	{
		for ( iCoord = 0; iCoord < p_pntObj->iDims; iCoord = iCoord + 1 )
		{
			p_pntObj->p_dX [ iCoord ] = p_pntVal->p_dX [ iCoord ];
		}
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SPntNDEsCompatible ( SPuntoND * p_pntObj, SPuntoND * p_pntVal )
{
	int iRes;

	if ( SPntNDEsValido ( p_pntObj ) == 1 )
	{
		if ( SPntNDEsValido ( p_pntVal ) == 1 )
		{
			if ( p_pntObj->iDims == p_pntVal->iDims )
			{
				iRes = 1;
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
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SPntNDEsVectorCompatible ( SPuntoND * p_pntObj, SVectorND * p_vecVal )
{
	int iRes;

	if ( SPntNDEsValido ( p_pntObj ) == 1 )
	{
		if ( SVecNDEsValido ( p_vecVal ) == 1 )
		{
			if ( p_pntObj->iDims == SVecNDDim ( p_vecVal ) )
			{
				iRes = 1;
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
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SPntNDEsIgual ( SPuntoND * p_pntObj, SPuntoND * p_pntVal )
{
	int iCoord;
	int iRes;

	if ( SPntNDEsCompatible ( p_pntObj, p_pntVal ) == 1 )
	{
		iRes = 1;
		iCoord = 0;
		while ( ( iRes == 1 ) && ( iCoord < p_pntObj->iDims ) )
		{
			iRes = MatEsIgual ( p_pntObj->p_dX [ iCoord ], p_pntVal->p_dX [ iCoord ] );
			iCoord = iCoord + 1;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SPntNDEsMenor ( SPuntoND * p_pntObj, SPuntoND * p_pntVal )
{
	int iRes;

	if ( SPntNDEsCompatible ( p_pntObj, p_pntVal ) == 1 )
	{
		iRes = MatEsMenor ( SPntNDDistanciaAlOrigen ( p_pntObj ), SPntNDDistanciaAlOrigen ( p_pntVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SPntNDEsMayor ( SPuntoND * p_pntObj, SPuntoND * p_pntVal )
{
	int iRes;

	if ( SPntNDEsCompatible ( p_pntObj, p_pntVal ) == 1 )
	{
		iRes = MatEsMayor ( SPntNDDistanciaAlOrigen ( p_pntObj ), SPntNDDistanciaAlOrigen ( p_pntVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SVectorND * SPntNDVector ( SPuntoND * p_pntObj )
{
	SVectorND * p_vecRes;

	if ( SPntNDEsValido ( p_pntObj ) == 1 )
	{
		p_vecRes = SVecNDCrearExt ( p_pntObj->iDims, p_pntObj->p_dX );
	}
	else
	{
		p_vecRes = NULL;
	}
	return ( p_vecRes );
}

int SPntNDDesplazar ( SPuntoND * p_pntObj, SVectorND * p_vecDesp )
{
	int		iRes;
	int		iCoord;

	if ( SPntNDEsVectorCompatible ( p_pntObj, p_vecDesp ) == 1 )
	{
		for ( iCoord = 1; iCoord <= p_pntObj->iDims; iCoord = iCoord + 1 )
		{
			p_pntObj->p_dX [ iCoord - 1 ] = p_pntObj->p_dX [ iCoord - 1 ] + SVecNDX ( p_vecDesp, iCoord );
		}
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

double SPntNDDistanciaAlOrigen ( SPuntoND * p_pntObj )
{
	double 	dRes;

	if ( SPntNDEsValido ( p_pntObj ) == 1 )
	{
		dRes = MatHipotenusaND ( p_pntObj->iDims, p_pntObj->p_dX );
	}
	else
	{
		dRes = -1.0;
	}
	return ( dRes );
}

double SPntNDDistancia ( SPuntoND * p_pntObj, SPuntoND * p_pntVal )
{
	double 	dRes;
	int 	iCoord;

	if ( SPntNDEsCompatible ( p_pntObj, p_pntVal ) == 1 )
	{
		dRes = 0.0;
		for ( iCoord = 0; iCoord < p_pntObj->iDims; iCoord = iCoord + 1 )
		{
			dRes = dRes + MatCuadrado ( p_pntVal->p_dX [ iCoord ] - p_pntObj->p_dX [ iCoord ] );
		}
		dRes = sqrt ( dRes );
	}
	else
	{
		dRes = -1.0;
	}
	return ( dRes );
}

SVectorND * SPntNDVectorHacia ( SPuntoND * p_pntObj, SPuntoND * p_pntVal )
{
	int			iCoord;
	SVectorND * p_vecRes;

	if ( SPntNDEsCompatible ( p_pntObj, p_pntVal ) == 1 )
	{
		p_vecRes = SVecNDCrear ( p_pntObj->iDims );
		if ( ES_VALIDO ( p_vecRes ) )
		{
			for ( iCoord = 1; iCoord <= p_pntObj->iDims; iCoord = iCoord + 1 )
			{
				SVecNDEstablecerX ( p_vecRes, iCoord, p_pntVal->p_dX [ iCoord - 1 ] - p_pntObj->p_dX [ iCoord - 1 ] );
			}
		}
	}
	else
	{
		p_vecRes = NULL;
	}
	return ( p_vecRes );
}

SPuntoND * SPntNDDuplicar ( SPuntoND * p_pntObj )
{
	SPuntoND * 	p_pntRes;

	if ( SPntNDEsValido ( p_pntObj ) == 1 )
	{
		p_pntRes = SPntNDCrearExt ( p_pntObj->iDims, p_pntObj->p_dX );
	}
	else
	{
		p_pntRes = NULL;
	}
	return ( p_pntRes );
}
