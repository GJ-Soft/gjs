#include "SMatrizNxM.h"

#include "CalculoConfig.h"
#include "CalculoOperaciones.h"




/* Posicion en el array de la fila iF y la columna iC, contadas desde 1. */
#define _SMATNXM_POS( p_matObj, iF, iC )	( ( (iF) - 1 ) * (p_matObj)->iColumnas + (iC) - 1 )



/* 1 si la matriz es valida y la posicion esta dentro de ella. */
static int _SMatNxMEsPosicion ( SMatrizNxM * p_matObj, int iFila, int iColumna )
{
	int iRes;

	if ( SMatNxMEsValida ( p_matObj ) == 1 )
	{
		if ( iFila > 0 )
		{
			if ( iFila <= p_matObj->iFilas )
			{
				if ( iColumna > 0 )
				{
					if ( iColumna <= p_matObj->iColumnas )
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

static int _SMatNxMRellenar ( SMatrizNxM * p_matObj, double dX )
{
	int iPos;
	int iRes;

	if ( SMatNxMEsValida ( p_matObj ) == 1 )
	{
		for ( iPos = 0; iPos < p_matObj->iFilas * p_matObj->iColumnas; iPos = iPos + 1 )
		{
			p_matObj->p_dX [ iPos ] = dX;
		}
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

/* Intercambia las filas iF1 e iF2 (desde 0) de un array de iN x iN. */
static void _SMatNxMIntercambiarFilas ( double * p_dA, int iN, int iF1, int iF2 )
{
	int		iC;
	double	dAux;

	for ( iC = 0; iC < iN; iC = iC + 1 )
	{
		dAux = p_dA [ iF1 * iN + iC ];
		p_dA [ iF1 * iN + iC ] = p_dA [ iF2 * iN + iC ];
		p_dA [ iF2 * iN + iC ] = dAux;
	}
}

/* Fila (desde iDesde) con el mayor valor absoluto en la columna iC. */
static int _SMatNxMFilaPivote ( double * p_dA, int iN, int iC, int iDesde )
{
	int iF;
	int iRes;

	iRes = iDesde;
	for ( iF = iDesde + 1; iF < iN; iF = iF + 1 )
	{
		if ( fabs ( p_dA [ iF * iN + iC ] ) > fabs ( p_dA [ iRes * iN + iC ] ) )
		{
			iRes = iF;
		}
	}
	return ( iRes );
}

/* Determinante de un array de iN x iN por eliminacion gaussiana con pivote
   parcial. Deja el array triangulado. */
static double _SMatNxMDeterminanteArray ( double * p_dA, int iN )
{
	int		iC;
	int		iF;
	int		iK;
	int		iPiv;
	double	dRes;
	double	dFactor;

	dRes = 1.0;
	iC = 0;
	while ( ( iC < iN ) && ( dRes != 0.0 ) )
	{
		iPiv = _SMatNxMFilaPivote ( p_dA, iN, iC, iC );
		if ( MatEsIgual ( p_dA [ iPiv * iN + iC ], 0.0 ) == 1 )
		{
			dRes = 0.0;
		}
		else
		{
			if ( iPiv != iC )
			{
				_SMatNxMIntercambiarFilas ( p_dA, iN, iPiv, iC );
				dRes = -dRes;
			}
			dRes = dRes * p_dA [ iC * iN + iC ];
			for ( iF = iC + 1; iF < iN; iF = iF + 1 )
			{
				dFactor = p_dA [ iF * iN + iC ] / p_dA [ iC * iN + iC ];
				for ( iK = iC; iK < iN; iK = iK + 1 )
				{
					p_dA [ iF * iN + iK ] = p_dA [ iF * iN + iK ] - dFactor * p_dA [ iC * iN + iK ];
				}
			}
		}
		iC = iC + 1;
	}
	return ( dRes );
}

SMatrizNxM * SMatNxMCrear ( int iFilas, int iColumnas )
{
	SMatrizNxM * 	p_matObj;

	if ( iFilas > 0 )
	{
		if ( iColumnas > 0 )
		{
			p_matObj = (SMatrizNxM *) MemReservar ( sizeof ( SMatrizNxM ) );
			if ( ES_VALIDO ( p_matObj ) )
			{
				p_matObj->iFilas = iFilas;
				p_matObj->iColumnas = iColumnas;
				p_matObj->p_dX = (double *) MemReservar ( iFilas * iColumnas * sizeof ( double ) );
				if ( ES_VALIDO ( p_matObj->p_dX ) )
				{
					_SMatNxMRellenar ( p_matObj, 0.0 );
				}
				else
				{
					MemLiberar ( (void **) &p_matObj );
				}
			}
		}
		else
		{
			p_matObj = NULL;
		}
	}
	else
	{
		p_matObj = NULL;
	}
	return ( p_matObj );
}

SMatrizNxM * SMatNxMCrearExt ( int iFilas, int iColumnas, const double * p_dValores )
{
	SMatrizNxM * 	p_matObj;
	int 			iPos;

	if ( ES_VALIDO ( p_dValores ) )
	{
		p_matObj = SMatNxMCrear ( iFilas, iColumnas );
		if ( ES_VALIDO ( p_matObj ) )
		{
			for ( iPos = 0; iPos < iFilas * iColumnas; iPos = iPos + 1 )
			{
				p_matObj->p_dX [ iPos ] = p_dValores [ iPos ];
			}
		}
	}
	else
	{
		p_matObj = NULL;
	}
	return ( p_matObj );
}

SMatrizNxM * SMatNxMEncapsular ( int iFilas, int iColumnas, double * p_dValores )
{
	SMatrizNxM * 	p_matObj;

	if ( iFilas > 0 )
	{
		if ( iColumnas > 0 )
		{
			if ( ES_VALIDO ( p_dValores ) )
			{
				p_matObj = (SMatrizNxM *) MemReservar ( sizeof ( SMatrizNxM ) );
				if ( ES_VALIDO ( p_matObj ) )
				{
					p_matObj->iFilas = iFilas;
					p_matObj->iColumnas = iColumnas;
					p_matObj->p_dX = p_dValores;
				}
			}
			else
			{
				p_matObj = NULL;
			}
		}
		else
		{
			p_matObj = NULL;
		}
	}
	else
	{
		p_matObj = NULL;
	}
	return ( p_matObj );
}

SMatrizNxM * SMatNxMUnos ( int iFilas, int iColumnas )
{
	SMatrizNxM * 	p_matObj;

	p_matObj = SMatNxMCrear ( iFilas, iColumnas );
	if ( ES_VALIDO ( p_matObj ) )
	{
		SMatNxMInicializarUnos ( p_matObj );
	}
	return ( p_matObj );
}

SMatrizNxM * SMatNxMIdentidad ( int iFilas, int iColumnas )
{
	SMatrizNxM * 	p_matObj;

	p_matObj = SMatNxMCrear ( iFilas, iColumnas );
	if ( ES_VALIDO ( p_matObj ) )
	{
		SMatNxMInicializarIdentidad ( p_matObj );
	}
	return ( p_matObj );
}

void SMatNxMDestruir ( SMatrizNxM ** p_p_matObj )
{
	SMatrizNxM * p_matObj;

	if ( ES_VALIDO ( p_p_matObj ) )
	{
		p_matObj = *p_p_matObj;
		if ( ES_VALIDO ( p_matObj ) )
		{
			MemLiberar ( (void **) &(p_matObj->p_dX) );
			MemLiberar ( (void **) p_p_matObj );
		}
	}
}

int SMatNxMFilas ( SMatrizNxM * p_matObj )
{
	int iRes;

	if ( SMatNxMEsValida ( p_matObj ) == 1 )
	{
		iRes = p_matObj->iFilas;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SMatNxMColumnas ( SMatrizNxM * p_matObj )
{
	int iRes;

	if ( SMatNxMEsValida ( p_matObj ) == 1 )
	{
		iRes = p_matObj->iColumnas;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

double SMatNxMX ( SMatrizNxM * p_matObj, int iFila, int iColumna )
{
	double dRes;

	if ( _SMatNxMEsPosicion ( p_matObj, iFila, iColumna ) == 1 )
	{
		dRes = p_matObj->p_dX [ _SMATNXM_POS ( p_matObj, iFila, iColumna ) ];
	}
	else
	{
		dRes = 0.0;
	}
	return ( dRes );
}

int SMatNxMEsValida ( SMatrizNxM * p_matObj )
{
	int iRes;

	if ( ES_VALIDO ( p_matObj ) )
	{
		if ( p_matObj->iFilas > 0 )
		{
			if ( p_matObj->iColumnas > 0 )
			{
				if ( ES_VALIDO ( p_matObj->p_dX ) )
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
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SMatNxMEsCompatible ( SMatrizNxM * p_matObj, SMatrizNxM * p_matVal )
{
	int iRes;

	if ( SMatNxMEsValida ( p_matObj ) == 1 )
	{
		if ( SMatNxMEsValida ( p_matVal ) == 1 )
		{
			if ( p_matObj->iFilas == p_matVal->iFilas )
			{
				if ( p_matObj->iColumnas == p_matVal->iColumnas )
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
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SMatNxMEsCompatibleFila ( SMatrizNxM * p_matObj, SVectorND * p_vecVal )
{
	int iRes;

	if ( SMatNxMEsValida ( p_matObj ) == 1 )
	{
		if ( SVecNDEsValido ( p_vecVal ) == 1 )
		{
			if ( p_matObj->iColumnas == SVecNDDim ( p_vecVal ) )
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

int SMatNxMEsCompatibleColumna ( SMatrizNxM * p_matObj, SVectorND * p_vecVal )
{
	int iRes;

	if ( SMatNxMEsValida ( p_matObj ) == 1 )
	{
		if ( SVecNDEsValido ( p_vecVal ) == 1 )
		{
			if ( p_matObj->iFilas == SVecNDDim ( p_vecVal ) )
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

int SMatNxMPuedeMultiplicar ( SMatrizNxM * p_matObj, SMatrizNxM * p_matVal )
{
	int iRes;

	if ( SMatNxMEsValida ( p_matObj ) == 1 )
	{
		if ( SMatNxMEsValida ( p_matVal ) == 1 )
		{
			if ( p_matObj->iColumnas == p_matVal->iFilas )
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

int SMatNxMEstablecerX ( SMatrizNxM * p_matObj, int iFila, int iColumna, double dX )
{
	int iRes;

	if ( _SMatNxMEsPosicion ( p_matObj, iFila, iColumna ) == 1 )
	{
		p_matObj->p_dX [ _SMATNXM_POS ( p_matObj, iFila, iColumna ) ] = dX;
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SMatNxMAsignar ( SMatrizNxM * p_matObj, SMatrizNxM * p_matVal )
{
	int iPos;
	int iRes;

	if ( SMatNxMEsCompatible ( p_matObj, p_matVal ) == 1 )
	{
		for ( iPos = 0; iPos < p_matObj->iFilas * p_matObj->iColumnas; iPos = iPos + 1 )
		{
			p_matObj->p_dX [ iPos ] = p_matVal->p_dX [ iPos ];
		}
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SVectorND * SMatNxMVectorFila ( SMatrizNxM * p_matObj, int iFila )
{
	SVectorND *	p_vecRes;

	if ( _SMatNxMEsPosicion ( p_matObj, iFila, 1 ) == 1 )
	{
		p_vecRes = SVecNDCrearExt ( p_matObj->iColumnas, &(p_matObj->p_dX [ _SMATNXM_POS ( p_matObj, iFila, 1 ) ]) );
	}
	else
	{
		p_vecRes = NULL;
	}
	return ( p_vecRes );
}

SVectorND * SMatNxMVectorColumna ( SMatrizNxM * p_matObj, int iColumna )
{
	int			iF;
	SVectorND * p_vecRes;

	if ( _SMatNxMEsPosicion ( p_matObj, 1, iColumna ) == 1 )
	{
		p_vecRes = SVecNDCrear ( p_matObj->iFilas );
		if ( ES_VALIDO ( p_vecRes ) )
		{
			for ( iF = 1; iF <= p_matObj->iFilas; iF = iF + 1 )
			{
				SVecNDEstablecerX ( p_vecRes, iF, p_matObj->p_dX [ _SMATNXM_POS ( p_matObj, iF, iColumna ) ] );
			}
		}
	}
	else
	{
		p_vecRes = NULL;
	}
	return ( p_vecRes );
}

int SMatNxMAsignarVectorFila ( SMatrizNxM * p_matObj, int iFila, SVectorND * p_vecVal )
{
	int iC;
	int iRes;

	if ( _SMatNxMEsPosicion ( p_matObj, iFila, 1 ) == 1 )
	{
		if ( SMatNxMEsCompatibleFila ( p_matObj, p_vecVal ) == 1 )
		{
			for ( iC = 1; iC <= p_matObj->iColumnas; iC = iC + 1 )
			{
				p_matObj->p_dX [ _SMATNXM_POS ( p_matObj, iFila, iC ) ] = SVecNDX ( p_vecVal, iC );
			}
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
	return ( iRes );
}

int SMatNxMAsignarVectorColumna ( SMatrizNxM * p_matObj, int iColumna, SVectorND * p_vecVal )
{
	int iF;
	int iRes;

	if ( _SMatNxMEsPosicion ( p_matObj, 1, iColumna ) == 1 )
	{
		if ( SMatNxMEsCompatibleColumna ( p_matObj, p_vecVal ) == 1 )
		{
			for ( iF = 1; iF <= p_matObj->iFilas; iF = iF + 1 )
			{
				p_matObj->p_dX [ _SMATNXM_POS ( p_matObj, iF, iColumna ) ] = SVecNDX ( p_vecVal, iF );
			}
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
	return ( iRes );
}

int SMatNxMEsCuadrada ( SMatrizNxM * p_matObj )
{
	int iRes;

	if ( SMatNxMEsValida ( p_matObj ) == 1 )
	{
		if ( p_matObj->iFilas == p_matObj->iColumnas )
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
	return ( iRes );
}

int SMatNxMEsDiagonal ( SMatrizNxM * p_matObj )
{
	int iF;
	int iC;
	int iRes;

	if ( SMatNxMEsCuadrada ( p_matObj ) == 1 )
	{
		iRes = 1;
		iF = 1;
		while ( ( iRes == 1 ) && ( iF <= p_matObj->iFilas ) )
		{
			iC = 1;
			while ( ( iRes == 1 ) && ( iC <= p_matObj->iColumnas ) )
			{
				if ( iF != iC )
				{
					iRes = MatEsIgual ( p_matObj->p_dX [ _SMATNXM_POS ( p_matObj, iF, iC ) ], 0.0 );
				}
				iC = iC + 1;
			}
			iF = iF + 1;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

double SMatNxMDeterminante ( SMatrizNxM * p_matObj )
{
	SMatrizNxM *	p_matAux;
	double			dRes;

	if ( SMatNxMEsCuadrada ( p_matObj ) == 1 )
	{
		p_matAux = SMatNxMDuplicar ( p_matObj );
		if ( ES_VALIDO ( p_matAux ) )
		{
			dRes = _SMatNxMDeterminanteArray ( p_matAux->p_dX, p_matAux->iFilas );
			SMatNxMDestruir ( &p_matAux );
		}
		else
		{
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

double SMatNxMAdjunto ( SMatrizNxM * p_matObj, int iFila, int iColumna )
{
	SMatrizNxM *	p_matMenor;
	int				iF;
	int				iC;
	int				iPos;
	double			dRes;

	if ( SMatNxMEsCuadrada ( p_matObj ) == 1 )
	{
		if ( _SMatNxMEsPosicion ( p_matObj, iFila, iColumna ) == 1 )
		{
			if ( p_matObj->iFilas == 1 )
			{
				dRes = 1.0;
			}
			else
			{
				p_matMenor = SMatNxMCrear ( p_matObj->iFilas - 1, p_matObj->iColumnas - 1 );
				if ( ES_VALIDO ( p_matMenor ) )
				{
					iPos = 0;
					for ( iF = 1; iF <= p_matObj->iFilas; iF = iF + 1 )
					{
						for ( iC = 1; iC <= p_matObj->iColumnas; iC = iC + 1 )
						{
							if ( iF != iFila )
							{
								if ( iC != iColumna )
								{
									p_matMenor->p_dX [ iPos ] = p_matObj->p_dX [ _SMATNXM_POS ( p_matObj, iF, iC ) ];
									iPos = iPos + 1;
								}
							}
						}
					}
					dRes = _SMatNxMDeterminanteArray ( p_matMenor->p_dX, p_matMenor->iFilas );
					if ( ( iFila + iColumna ) % 2 == 1 )
					{
						dRes = -dRes;
					}
					SMatNxMDestruir ( &p_matMenor );
				}
				else
				{
					dRes = -1.0;
				}
			}
		}
		else
		{
			dRes = -1.0;
		}
	}
	else
	{
		dRes = -1.0;
	}
	return ( dRes );
}

int SMatNxMSumar ( SMatrizNxM * p_matObj, SMatrizNxM * p_matVal )
{
	int iPos;
	int iRes;

	if ( SMatNxMEsCompatible ( p_matObj, p_matVal ) == 1 )
	{
		for ( iPos = 0; iPos < p_matObj->iFilas * p_matObj->iColumnas; iPos = iPos + 1 )
		{
			p_matObj->p_dX [ iPos ] = p_matObj->p_dX [ iPos ] + p_matVal->p_dX [ iPos ];
		}
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SMatNxMRestar ( SMatrizNxM * p_matObj, SMatrizNxM * p_matVal )
{
	int iPos;
	int iRes;

	if ( SMatNxMEsCompatible ( p_matObj, p_matVal ) == 1 )
	{
		for ( iPos = 0; iPos < p_matObj->iFilas * p_matObj->iColumnas; iPos = iPos + 1 )
		{
			p_matObj->p_dX [ iPos ] = p_matObj->p_dX [ iPos ] - p_matVal->p_dX [ iPos ];
		}
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SMatrizNxM * SMatNxMTranspuesta ( SMatrizNxM * p_matObj )
{
	int				iF;
	int				iC;
	SMatrizNxM *	p_matRes;

	if ( SMatNxMEsValida ( p_matObj ) == 1 )
	{
		p_matRes = SMatNxMCrear ( p_matObj->iColumnas, p_matObj->iFilas );
		if ( ES_VALIDO ( p_matRes ) )
		{
			for ( iF = 1; iF <= p_matObj->iFilas; iF = iF + 1 )
			{
				for ( iC = 1; iC <= p_matObj->iColumnas; iC = iC + 1 )
				{
					p_matRes->p_dX [ _SMATNXM_POS ( p_matRes, iC, iF ) ] = p_matObj->p_dX [ _SMATNXM_POS ( p_matObj, iF, iC ) ];
				}
			}
		}
	}
	else
	{
		p_matRes = NULL;
	}
	return ( p_matRes );
}

SMatrizNxM * SMatNxMAdjunta ( SMatrizNxM * p_matObj )
{
	int				iF;
	int				iC;
	SMatrizNxM *	p_matRes;

	if ( SMatNxMEsCuadrada ( p_matObj ) == 1 )
	{
		p_matRes = SMatNxMCrear ( p_matObj->iFilas, p_matObj->iColumnas );
		if ( ES_VALIDO ( p_matRes ) )
		{
			for ( iF = 1; iF <= p_matObj->iFilas; iF = iF + 1 )
			{
				for ( iC = 1; iC <= p_matObj->iColumnas; iC = iC + 1 )
				{
					p_matRes->p_dX [ _SMATNXM_POS ( p_matRes, iC, iF ) ] = SMatNxMAdjunto ( p_matObj, iF, iC );
				}
			}
		}
	}
	else
	{
		p_matRes = NULL;
	}
	return ( p_matRes );
}

/* Gauss-Jordan con pivote parcial: lo que se le hace a la copia de la matriz
   hasta dejarla en la identidad, se le hace a la identidad, que acaba en la
   inversa. */
SMatrizNxM * SMatNxMInversa ( SMatrizNxM * p_matObj )
{
	SMatrizNxM *	p_matAux;
	SMatrizNxM *	p_matRes;
	double *		p_dA;
	double *		p_dI;
	double			dFactor;
	int				iN;
	int				iC;
	int				iF;
	int				iK;
	int				iPiv;
	int				iSingular;

	if ( SMatNxMEsCuadrada ( p_matObj ) == 1 )
	{
		iN = p_matObj->iFilas;
		p_matRes = SMatNxMIdentidad ( iN, iN );
		if ( ES_VALIDO ( p_matRes ) )
		{
			p_matAux = SMatNxMDuplicar ( p_matObj );
			if ( ES_VALIDO ( p_matAux ) )
			{
				p_dA = p_matAux->p_dX;
				p_dI = p_matRes->p_dX;
				iSingular = 0;
				iC = 0;
				while ( ( iSingular == 0 ) && ( iC < iN ) )
				{
					iPiv = _SMatNxMFilaPivote ( p_dA, iN, iC, iC );
					if ( MatEsIgual ( p_dA [ iPiv * iN + iC ], 0.0 ) == 1 )
					{
						iSingular = 1;
					}
					else
					{
						if ( iPiv != iC )
						{
							_SMatNxMIntercambiarFilas ( p_dA, iN, iPiv, iC );
							_SMatNxMIntercambiarFilas ( p_dI, iN, iPiv, iC );
						}
						dFactor = p_dA [ iC * iN + iC ];
						for ( iK = 0; iK < iN; iK = iK + 1 )
						{
							p_dA [ iC * iN + iK ] = p_dA [ iC * iN + iK ] / dFactor;
							p_dI [ iC * iN + iK ] = p_dI [ iC * iN + iK ] / dFactor;
						}
						for ( iF = 0; iF < iN; iF = iF + 1 )
						{
							if ( iF != iC )
							{
								dFactor = p_dA [ iF * iN + iC ];
								for ( iK = 0; iK < iN; iK = iK + 1 )
								{
									p_dA [ iF * iN + iK ] = p_dA [ iF * iN + iK ] - dFactor * p_dA [ iC * iN + iK ];
									p_dI [ iF * iN + iK ] = p_dI [ iF * iN + iK ] - dFactor * p_dI [ iC * iN + iK ];
								}
							}
						}
					}
					iC = iC + 1;
				}
				if ( iSingular == 1 )
				{
					SMatNxMDestruir ( &p_matRes );
				}
				SMatNxMDestruir ( &p_matAux );
			}
			else
			{
				SMatNxMDestruir ( &p_matRes );
			}
		}
	}
	else
	{
		p_matRes = NULL;
	}
	return ( p_matRes );
}

int SMatNxMMultiplicarEscalar ( SMatrizNxM * p_matObj, double dVal )
{
	int iPos;
	int iRes;

	if ( SMatNxMEsValida ( p_matObj ) == 1 )
	{
		for ( iPos = 0; iPos < p_matObj->iFilas * p_matObj->iColumnas; iPos = iPos + 1 )
		{
			p_matObj->p_dX [ iPos ] = p_matObj->p_dX [ iPos ] * dVal;
		}
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SMatrizNxM * SMatNxMMultiplicar ( SMatrizNxM * p_matObj, SMatrizNxM * p_matVal )
{
	int				iF;
	int				iC;
	int				iK;
	SMatrizNxM *	p_matRes;
	double			dX;

	if ( SMatNxMPuedeMultiplicar ( p_matObj, p_matVal ) == 1 )
	{
		p_matRes = SMatNxMCrear ( p_matObj->iFilas, p_matVal->iColumnas );
		if ( ES_VALIDO ( p_matRes ) )
		{
			for ( iF = 1; iF <= p_matObj->iFilas; iF = iF + 1 )
			{
				for ( iC = 1; iC <= p_matVal->iColumnas; iC = iC + 1 )
				{
					dX = 0.0;
					for ( iK = 1; iK <= p_matObj->iColumnas; iK = iK + 1 )
					{
						dX = dX + p_matObj->p_dX [ _SMATNXM_POS ( p_matObj, iF, iK ) ] *
								  p_matVal->p_dX [ _SMATNXM_POS ( p_matVal, iK, iC ) ];
					}
					p_matRes->p_dX [ _SMATNXM_POS ( p_matRes, iF, iC ) ] = dX;
				}
			}
		}
	}
	else
	{
		p_matRes = NULL;
	}
	return ( p_matRes );
}

SVectorND * SMatNxMMultiplicarPorIzq ( SMatrizNxM * p_matObj, SVectorND * p_vecVal )
{
	int			iF;
	int			iC;
	SVectorND *	p_vecRes;
	double		dX;

	if ( SMatNxMEsCompatibleColumna ( p_matObj, p_vecVal ) == 1 )
	{
		p_vecRes = SVecNDCrear ( p_matObj->iColumnas );
		if ( ES_VALIDO ( p_vecRes ) )
		{
			for ( iC = 1; iC <= p_matObj->iColumnas; iC = iC + 1 )
			{
				dX = 0.0;
				for ( iF = 1; iF <= p_matObj->iFilas; iF = iF + 1 )
				{
					dX = dX + SVecNDX ( p_vecVal, iF ) * p_matObj->p_dX [ _SMATNXM_POS ( p_matObj, iF, iC ) ];
				}
				SVecNDEstablecerX ( p_vecRes, iC, dX );
			}
		}
	}
	else
	{
		p_vecRes = NULL;
	}
	return ( p_vecRes );
}

SVectorND * SMatNxMMultiplicarPorDer ( SMatrizNxM * p_matObj, SVectorND * p_vecVal )
{
	int			iF;
	int			iC;
	SVectorND *	p_vecRes;
	double		dX;

	if ( SMatNxMEsCompatibleFila ( p_matObj, p_vecVal ) == 1 )
	{
		p_vecRes = SVecNDCrear ( p_matObj->iFilas );
		if ( ES_VALIDO ( p_vecRes ) )
		{
			for ( iF = 1; iF <= p_matObj->iFilas; iF = iF + 1 )
			{
				dX = 0.0;
				for ( iC = 1; iC <= p_matObj->iColumnas; iC = iC + 1 )
				{
					dX = dX + p_matObj->p_dX [ _SMATNXM_POS ( p_matObj, iF, iC ) ] * SVecNDX ( p_vecVal, iC );
				}
				SVecNDEstablecerX ( p_vecRes, iF, dX );
			}
		}
	}
	else
	{
		p_vecRes = NULL;
	}
	return ( p_vecRes );
}

SMatrizNxM * SMatNxMDuplicar ( SMatrizNxM * p_matObj )
{
	SMatrizNxM * 	p_matRes;

	if ( SMatNxMEsValida ( p_matObj ) == 1 )
	{
		p_matRes = SMatNxMCrearExt ( p_matObj->iFilas, p_matObj->iColumnas, p_matObj->p_dX );
	}
	else
	{
		p_matRes = NULL;
	}
	return ( p_matRes );
}

double * SMatNxMValores ( SMatrizNxM * p_matObj )
{
	double * p_dRes;

	if ( SMatNxMEsValida ( p_matObj ) == 1 )
	{
		p_dRes = p_matObj->p_dX;
	}
	else
	{
		p_dRes = NULL;
	}
	return ( p_dRes );
}

double * SMatNxMValoresFila ( SMatrizNxM * p_matObj, int iFila )
{
	double * p_dRes;

	if ( _SMatNxMEsPosicion ( p_matObj, iFila, 1 ) == 1 )
	{
		p_dRes = &(p_matObj->p_dX [ _SMATNXM_POS ( p_matObj, iFila, 1 ) ]);
	}
	else
	{
		p_dRes = NULL;
	}
	return ( p_dRes );
}

int SMatNxMInicializarCero ( SMatrizNxM * p_matObj )
{
	return ( _SMatNxMRellenar ( p_matObj, 0.0 ) );
}

int SMatNxMInicializarUnos ( SMatrizNxM * p_matObj )
{
	return ( _SMatNxMRellenar ( p_matObj, 1.0 ) );
}

int SMatNxMInicializarIdentidad ( SMatrizNxM * p_matObj )
{
	int iF;
	int iRes;

	if ( _SMatNxMRellenar ( p_matObj, 0.0 ) == 1 )
	{
		for ( iF = 1; ( iF <= p_matObj->iFilas ) && ( iF <= p_matObj->iColumnas ); iF = iF + 1 )
		{
			p_matObj->p_dX [ _SMATNXM_POS ( p_matObj, iF, iF ) ] = 1.0;
		}
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}
