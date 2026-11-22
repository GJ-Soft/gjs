#include "SVectorND.h"

#include "CalculoConfig.h"
#include "CalculoOperaciones.h"




/* 1 si el vector es valido y iCoord esta entre 1 y su dimension. */
static int _SVecNDEsCoordenada ( SVectorND * p_vecObj, int iCoord )
{
	int iRes;

	if ( SVecNDEsValido ( p_vecObj ) == 1 )
	{
		if ( iCoord > 0 )
		{
			if ( iCoord <= p_vecObj->iDims )
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

SVectorND * SVecNDCrear ( int iDims )
{
	SVectorND * 	p_vecObj;
	int 			iCoord;

	if ( iDims > 0 )
	{
		p_vecObj = (SVectorND *) MemReservar ( sizeof ( SVectorND ) );
		if ( ES_VALIDO ( p_vecObj ) )
		{
			p_vecObj->iDims = iDims;
			p_vecObj->p_dX = (double *) MemReservar ( iDims * sizeof ( double ) );
			if ( ES_VALIDO ( p_vecObj->p_dX ) )
			{
				for ( iCoord = 0; iCoord < iDims; iCoord = iCoord + 1 )
				{
					p_vecObj->p_dX [ iCoord ] = 0.0;
				}
			}
			else
			{
				MemLiberar ( (void **) &p_vecObj );
			}
		}
	}
	else
	{
		p_vecObj = NULL;
	}
	return ( p_vecObj );
}

SVectorND * SVecNDCrearExt ( int iDims, const double * p_dValores )
{
	SVectorND * 	p_vecObj;
	int 			iCoord;

	if ( ES_VALIDO ( p_dValores ) )
	{
		p_vecObj = SVecNDCrear ( iDims );
		if ( ES_VALIDO ( p_vecObj ) )
		{
			for ( iCoord = 0; iCoord < iDims; iCoord = iCoord + 1 )
			{
				p_vecObj->p_dX [ iCoord ] = p_dValores [ iCoord ];
			}
		}
	}
	else
	{
		p_vecObj = NULL;
	}
	return ( p_vecObj );
}

SVectorND * SVecNDEncapsular ( int iDims, double * p_dValores )
{
	SVectorND * 	p_vecObj;

	if ( iDims > 0 )
	{
		if ( ES_VALIDO ( p_dValores ) )
		{
			p_vecObj = (SVectorND *) MemReservar ( sizeof ( SVectorND ) );
			if ( ES_VALIDO ( p_vecObj ) )
			{
				p_vecObj->iDims = iDims;
				p_vecObj->p_dX = p_dValores;
			}
		}
		else
		{
			p_vecObj = NULL;
		}
	}
	else
	{
		p_vecObj = NULL;
	}
	return ( p_vecObj );
}

SVectorND * SVecNDUnitario ( int iDims, int iCoord )
{
	SVectorND * 	p_vecObj;

	p_vecObj = SVecNDCrear ( iDims );
	if ( ES_VALIDO ( p_vecObj ) )
	{
		if ( SVecNDInicializarUnitario ( p_vecObj, iCoord ) == 0 )
		{
			SVecNDDestruir ( &p_vecObj );
		}
	}
	return ( p_vecObj );
}

void SVecNDDestruir ( SVectorND ** p_p_vecObj )
{
	SVectorND * p_vecObj;

	if ( ES_VALIDO ( p_p_vecObj ) )
	{
		p_vecObj = *p_p_vecObj;
		if ( ES_VALIDO ( p_vecObj ) )
		{
			MemLiberar ( (void **) &(p_vecObj->p_dX) );
			MemLiberar ( (void **) p_p_vecObj );
		}
	}
}

int SVecNDDim ( SVectorND * p_vecObj )
{
	int iRes;

	if ( SVecNDEsValido ( p_vecObj ) == 1 )
	{
		iRes = p_vecObj->iDims;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

double SVecNDX ( SVectorND * p_vecObj, int iCoord )
{
	double dRes;

	if ( _SVecNDEsCoordenada ( p_vecObj, iCoord ) == 1 )
	{
		dRes = p_vecObj->p_dX [ iCoord - 1 ];
	}
	else
	{
		dRes = 0.0;
	}
	return ( dRes );
}

int SVecNDEsValido ( SVectorND * p_vecObj )
{
	int iRes;

	if ( ES_VALIDO ( p_vecObj ) )
	{
		if ( p_vecObj->iDims > 0 )
		{
			if ( ES_VALIDO ( p_vecObj->p_dX ) )
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

int SVecNDEsCompatible ( SVectorND * p_vecObj, SVectorND * p_vecVal )
{
	int iRes;

	if ( SVecNDEsValido ( p_vecObj ) == 1 )
	{
		if ( SVecNDEsValido ( p_vecVal ) == 1 )
		{
			if ( p_vecObj->iDims == p_vecVal->iDims )
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

int SVecNDEstablecerX ( SVectorND * p_vecObj, int iCoord, double dX )
{
	int iRes;

	if ( _SVecNDEsCoordenada ( p_vecObj, iCoord ) == 1 )
	{
		p_vecObj->p_dX [ iCoord - 1 ] = dX;
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SVecNDAsignar ( SVectorND * p_vecObj, SVectorND * p_vecVal )
{
	int	iCoord;
	int iRes;

	if ( SVecNDEsCompatible ( p_vecObj, p_vecVal ) == 1 )
	{
		for ( iCoord = 0; iCoord < p_vecObj->iDims; iCoord = iCoord + 1 )
		{
			p_vecObj->p_dX [ iCoord ] = p_vecVal->p_dX [ iCoord ];
		}
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

double SVecNDNorma ( SVectorND * p_vecObj )
{
	double dRes;

	if ( SVecNDEsValido ( p_vecObj ) == 1 )
	{
		dRes = MatHipotenusaND ( p_vecObj->iDims, p_vecObj->p_dX );
	}
	else
	{
		ERROR_ESTABLECER ( ERR_PARAMETROS );
		dRes = -1.0;
	}
	return ( dRes );
}

double SVecNDPendiente ( SVectorND * p_vecObj, int iDim2, int iDim1 )
{
	double dRes;
	double dX;
	double dY;

	if ( _SVecNDEsCoordenada ( p_vecObj, iDim1 ) == 1 )
	{
		if ( _SVecNDEsCoordenada ( p_vecObj, iDim2 ) == 1 )
		{
			if ( iDim1 != iDim2 )
			{
				dY = p_vecObj->p_dX [ iDim2 - 1 ];
				dX = p_vecObj->p_dX [ iDim1 - 1 ];
				if ( MatEsIgual ( dX, 0.0 ) == 0 )
				{
					dRes = dY / dX;
				}
				else if ( MatEsMayor ( dY, 0.0 ) == 1 )
				{
					dRes = DBL_MAX;
				}
				else if ( MatEsMenor ( dY, 0.0 ) == 1 )
				{
					dRes = -DBL_MAX;
				}
				else
				{
					dRes = 0.0;
				}
			}
			else
			{
				ERROR_ESTABLECER ( ERR_PARAMETROS );
				dRes = -1.0;
			}
		}
		else
		{
			ERROR_ESTABLECER ( ERR_PARAMETROS );
			dRes = -1.0;
		}
	}
	else
	{
		ERROR_ESTABLECER ( ERR_PARAMETROS );
		dRes = -1.0;
	}
	return ( dRes );
}

double SVecNDAngulo ( SVectorND * p_vecObj, int iDim2, int iDim1 )
{
	double dRes;

	if ( _SVecNDEsCoordenada ( p_vecObj, iDim1 ) == 1 )
	{
		if ( _SVecNDEsCoordenada ( p_vecObj, iDim2 ) == 1 )
		{
			if ( iDim1 != iDim2 )
			{
				dRes = atan2 ( p_vecObj->p_dX [ iDim2 - 1 ], p_vecObj->p_dX [ iDim1 - 1 ] );
			}
			else
			{
				ERROR_ESTABLECER ( ERR_PARAMETROS );
				dRes = -1.0;
			}
		}
		else
		{
			ERROR_ESTABLECER ( ERR_PARAMETROS );
			dRes = -1.0;
		}
	}
	else
	{
		ERROR_ESTABLECER ( ERR_PARAMETROS );
		dRes = -1.0;
	}
	return ( dRes );
}

int SVecNDInvertirDireccion ( SVectorND * p_vecObj )
{
	return ( SVecNDMultiplicar ( p_vecObj, -1.0 ) );
}

int SVecNDSumar ( SVectorND * p_vecObj, SVectorND * p_vecVal )
{
	int iCoord;
	int iRes;

	if ( SVecNDEsCompatible ( p_vecObj, p_vecVal ) == 1 )
	{
		for ( iCoord = 0; iCoord < p_vecObj->iDims; iCoord = iCoord + 1 )
		{
			p_vecObj->p_dX [ iCoord ] = p_vecObj->p_dX [ iCoord ] + p_vecVal->p_dX [ iCoord ];
		}
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SVecNDRestar ( SVectorND * p_vecObj, SVectorND * p_vecVal )
{
	int iCoord;
	int iRes;

	if ( SVecNDEsCompatible ( p_vecObj, p_vecVal ) == 1 )
	{
		for ( iCoord = 0; iCoord < p_vecObj->iDims; iCoord = iCoord + 1 )
		{
			p_vecObj->p_dX [ iCoord ] = p_vecObj->p_dX [ iCoord ] - p_vecVal->p_dX [ iCoord ];
		}
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SVecNDMultiplicar ( SVectorND * p_vecObj, double dVal )
{
	int iCoord;
	int iRes;

	if ( SVecNDEsValido ( p_vecObj ) == 1 )
	{
		for ( iCoord = 0; iCoord < p_vecObj->iDims; iCoord = iCoord + 1 )
		{
			p_vecObj->p_dX [ iCoord ] = p_vecObj->p_dX [ iCoord ] * dVal;
		}
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

double SVecNDProductoEscalar ( SVectorND * p_vecObj, SVectorND * p_vecVal )
{
	int		iCoord;
	double	dRes;

	if ( SVecNDEsCompatible ( p_vecObj, p_vecVal ) == 1 )
	{
		dRes = 0.0;
		for ( iCoord = 0; iCoord < p_vecObj->iDims; iCoord = iCoord + 1 )
		{
			dRes = dRes + p_vecObj->p_dX [ iCoord ] * p_vecVal->p_dX [ iCoord ];
		}
	}
	else
	{
		ERROR_ESTABLECER ( ERR_PARAMETROS );
		dRes = -1.0;
	}
	return ( dRes );
}

SVectorND * SVecNDProductoVectorial ( SVectorND * p_vecObj, SVectorND * p_vecVal )
{
	SVectorND * p_vecRes;
	double *	p_dA;
	double *	p_dB;

	if ( SVecNDEsCompatible ( p_vecObj, p_vecVal ) == 1 )
	{
		if ( p_vecObj->iDims == 3 )
		{
			p_vecRes = SVecNDCrear ( 3 );
			if ( ES_VALIDO ( p_vecRes ) )
			{
				p_dA = p_vecObj->p_dX;
				p_dB = p_vecVal->p_dX;
				p_vecRes->p_dX [ 0 ] = p_dA [ 1 ] * p_dB [ 2 ] - p_dA [ 2 ] * p_dB [ 1 ];
				p_vecRes->p_dX [ 1 ] = p_dA [ 2 ] * p_dB [ 0 ] - p_dA [ 0 ] * p_dB [ 2 ];
				p_vecRes->p_dX [ 2 ] = p_dA [ 0 ] * p_dB [ 1 ] - p_dA [ 1 ] * p_dB [ 0 ];
			}
		}
		else
		{
			p_vecRes = NULL;
		}
	}
	else
	{
		p_vecRes = NULL;
	}
	return ( p_vecRes );
}

int SVecNDNormalizar ( SVectorND * p_vecObj )
{
	int		iRes;
	double	dNorma;

	if ( SVecNDEsValido ( p_vecObj ) == 1 )
	{
		dNorma = SVecNDNorma ( p_vecObj );
		if ( MatEsIgual ( dNorma, 0.0 ) == 0 )
		{
			iRes = SVecNDMultiplicar ( p_vecObj, 1.0 / dNorma );
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

/* Cauchy-Schwarz: | a . b | = |a| |b| solo si uno es multiplo del otro. Se
   compara el coseno del angulo que forman con 1, para que la tolerancia no
   dependa del tamano de los vectores. */
int SVecNDEsLinealmenteDependiente ( SVectorND * p_vecObj, SVectorND * p_vecVal )
{
	int		iRes;
	double	dNormas;

	if ( SVecNDEsCompatible ( p_vecObj, p_vecVal ) == 1 )
	{
		dNormas = SVecNDNorma ( p_vecObj ) * SVecNDNorma ( p_vecVal );
		if ( MatEsIgual ( dNormas, 0.0 ) == 0 )
		{
			iRes = MatEsIgual ( fabs ( SVecNDProductoEscalar ( p_vecObj, p_vecVal ) ) / dNormas, 1.0 );
		}
		else
		{
			iRes = 1;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SVecNDEsLinealmenteIndependiente ( SVectorND * p_vecObj, SVectorND * p_vecVal )
{
	int iRes;

	if ( SVecNDEsCompatible ( p_vecObj, p_vecVal ) == 1 )
	{
		if ( SVecNDEsLinealmenteDependiente ( p_vecObj, p_vecVal ) == 1 )
		{
			iRes = 0;
		}
		else
		{
			iRes = 1;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SVectorND * SVecNDDuplicar ( SVectorND * p_vecObj )
{
	SVectorND * 	p_vecRes;

	if ( SVecNDEsValido ( p_vecObj ) == 1 )
	{
		p_vecRes = SVecNDCrearExt ( p_vecObj->iDims, p_vecObj->p_dX );
	}
	else
	{
		p_vecRes = NULL;
	}
	return ( p_vecRes );
}

double * SVecNDValores ( SVectorND * p_vecObj )
{
	double * 	p_dRes;

	if ( SVecNDEsValido ( p_vecObj ) == 1 )
	{
		p_dRes = p_vecObj->p_dX;
	}
	else
	{
		p_dRes = NULL;
	}
	return ( p_dRes );
}

int SVecNDInicializarCero ( SVectorND * p_vecObj )
{
	int iCoord;
	int iRes;

	if ( SVecNDEsValido ( p_vecObj ) == 1 )
	{
		for ( iCoord = 0; iCoord < p_vecObj->iDims; iCoord = iCoord + 1 )
		{
			p_vecObj->p_dX [ iCoord ] = 0.0;
		}
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SVecNDInicializarUnitario ( SVectorND * p_vecObj, int iCoord )
{
	int iRes;

	if ( _SVecNDEsCoordenada ( p_vecObj, iCoord ) == 1 )
	{
		SVecNDInicializarCero ( p_vecObj );
		p_vecObj->p_dX [ iCoord - 1 ] = 1.0;
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SVectorND * SVecNDSuma ( SVectorND * p_vecDatosX, SVectorND * p_vecDatosY )
{
	SVectorND *	p_vecRes;

	if ( SVecNDEsCompatible ( p_vecDatosX, p_vecDatosY ) == 1 )
	{
		p_vecRes = SVecNDDuplicar ( p_vecDatosX );
		if ( ES_VALIDO ( p_vecRes ) )
		{
			SVecNDSumar ( p_vecRes, p_vecDatosY );
		}
	}
	else
	{
		p_vecRes = NULL;
	}
	return ( p_vecRes );
}

SVectorND * SVecNDDiferencia ( SVectorND * p_vecDatosX, SVectorND * p_vecDatosY )
{
	SVectorND *	p_vecRes;

	if ( SVecNDEsCompatible ( p_vecDatosX, p_vecDatosY ) == 1 )
	{
		p_vecRes = SVecNDDuplicar ( p_vecDatosX );
		if ( ES_VALIDO ( p_vecRes ) )
		{
			SVecNDRestar ( p_vecRes, p_vecDatosY );
		}
	}
	else
	{
		p_vecRes = NULL;
	}
	return ( p_vecRes );
}
