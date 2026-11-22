#include "SMatrizCuadradaND.h"

#include "CalculoConfig.h"




/* Envuelve una matriz recien calculada; si no puede, la destruye. */
static SMatrizCuadradaND * _SMatNDEnvolver ( SMatrizNxM * p_matAux )
{
	SMatrizCuadradaND *	p_matRes;

	if ( ES_VALIDO ( p_matAux ) )
	{
		p_matRes = SMatNDEncapsular ( p_matAux );
		if ( ES_NULO ( p_matRes ) )
		{
			SMatNxMDestruir ( &p_matAux );
		}
	}
	else
	{
		p_matRes = NULL;
	}
	return ( p_matRes );
}

SMatrizCuadradaND * SMatNDCrear ( int iDims )
{
	return ( _SMatNDEnvolver ( SMatNxMCrear ( iDims, iDims ) ) );
}

SMatrizCuadradaND * SMatNDCrearExt ( int iDims, const double * p_dValores )
{
	return ( _SMatNDEnvolver ( SMatNxMCrearExt ( iDims, iDims, p_dValores ) ) );
}

SMatrizCuadradaND * SMatNDEncapsular ( SMatrizNxM * p_matVal )
{
	SMatrizCuadradaND * p_matObj;

	if ( SMatNxMEsCuadrada ( p_matVal ) == 1 )
	{
		p_matObj = (SMatrizCuadradaND *) MemReservar ( sizeof ( SMatrizCuadradaND ) );
		if ( ES_VALIDO ( p_matObj ) )
		{
			p_matObj->p_matObj = p_matVal;
		}
	}
	else
	{
		p_matObj = NULL;
	}
	return ( p_matObj );
}

SMatrizCuadradaND * SMatNDUnos ( int iDims )
{
	return ( _SMatNDEnvolver ( SMatNxMUnos ( iDims, iDims ) ) );
}

SMatrizCuadradaND * SMatNDIdentidad ( int iDims )
{
	return ( _SMatNDEnvolver ( SMatNxMIdentidad ( iDims, iDims ) ) );
}

void SMatNDDestruir ( SMatrizCuadradaND ** p_p_matObj )
{
	SMatrizCuadradaND * p_matObj;

	if ( ES_VALIDO ( p_p_matObj ) )
	{
		p_matObj = *p_p_matObj;
		if ( ES_VALIDO ( p_matObj ) )
		{
			SMatNxMDestruir ( &(p_matObj->p_matObj) );
			MemLiberar ( (void **) p_p_matObj );
		}
	}
}

int SMatNDDim ( SMatrizCuadradaND * p_matObj )
{
	int iRes;

	if ( SMatNDEsValida ( p_matObj ) == 1 )
	{
		iRes = SMatNxMFilas ( p_matObj->p_matObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

double SMatNDX ( SMatrizCuadradaND * p_matObj, int iFila, int iColumna )
{
	return ( SMatNxMX ( SMatNDMatrizNxM ( p_matObj ), iFila, iColumna ) );
}

int SMatNDEsValida ( SMatrizCuadradaND * p_matObj )
{
	int iRes;

	if ( ES_VALIDO ( p_matObj ) )
	{
		iRes = SMatNxMEsCuadrada ( p_matObj->p_matObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SMatNDEsCompatible ( SMatrizCuadradaND * p_matObj, SMatrizCuadradaND * p_matVal )
{
	return ( SMatNxMEsCompatible ( SMatNDMatrizNxM ( p_matObj ), SMatNDMatrizNxM ( p_matVal ) ) );
}

int SMatNDEsVectorCompatible ( SMatrizCuadradaND * p_matObj, SVectorND * p_vecVal )
{
	return ( SMatNxMEsCompatibleFila ( SMatNDMatrizNxM ( p_matObj ), p_vecVal ) );
}

int SMatNDEstablecerX ( SMatrizCuadradaND * p_matObj, int iFila, int iColumna, double dX )
{
	return ( SMatNxMEstablecerX ( SMatNDMatrizNxM ( p_matObj ), iFila, iColumna, dX ) );
}

int SMatNDAsignar ( SMatrizCuadradaND * p_matObj, SMatrizCuadradaND * p_matVal )
{
	return ( SMatNxMAsignar ( SMatNDMatrizNxM ( p_matObj ), SMatNDMatrizNxM ( p_matVal ) ) );
}

int SMatNDAsignarNxM ( SMatrizCuadradaND * p_matObj, SMatrizNxM * p_matVal )
{
	return ( SMatNxMAsignar ( SMatNDMatrizNxM ( p_matObj ), p_matVal ) );
}

SVectorND * SMatNDVectorFila ( SMatrizCuadradaND * p_matObj, int iFila )
{
	return ( SMatNxMVectorFila ( SMatNDMatrizNxM ( p_matObj ), iFila ) );
}

SVectorND * SMatNDVectorColumna ( SMatrizCuadradaND * p_matObj, int iColumna )
{
	return ( SMatNxMVectorColumna ( SMatNDMatrizNxM ( p_matObj ), iColumna ) );
}

int SMatNDAsignarVectorFila ( SMatrizCuadradaND * p_matObj, int iFila, SVectorND * p_vecVal )
{
	return ( SMatNxMAsignarVectorFila ( SMatNDMatrizNxM ( p_matObj ), iFila, p_vecVal ) );
}

int SMatNDAsignarVectorColumna ( SMatrizCuadradaND * p_matObj, int iColumna, SVectorND * p_vecVal )
{
	return ( SMatNxMAsignarVectorColumna ( SMatNDMatrizNxM ( p_matObj ), iColumna, p_vecVal ) );
}

int SMatNDEsDiagonal ( SMatrizCuadradaND * p_matObj )
{
	return ( SMatNxMEsDiagonal ( SMatNDMatrizNxM ( p_matObj ) ) );
}

double SMatNDDeterminante ( SMatrizCuadradaND * p_matObj )
{
	return ( SMatNxMDeterminante ( SMatNDMatrizNxM ( p_matObj ) ) );
}

double SMatNDAdjunto ( SMatrizCuadradaND * p_matObj, int iFila, int iColumna )
{
	return ( SMatNxMAdjunto ( SMatNDMatrizNxM ( p_matObj ), iFila, iColumna ) );
}

int SMatNDSumar ( SMatrizCuadradaND * p_matObj, SMatrizCuadradaND * p_matVal )
{
	return ( SMatNxMSumar ( SMatNDMatrizNxM ( p_matObj ), SMatNDMatrizNxM ( p_matVal ) ) );
}

int SMatNDRestar ( SMatrizCuadradaND * p_matObj, SMatrizCuadradaND * p_matVal )
{
	return ( SMatNxMRestar ( SMatNDMatrizNxM ( p_matObj ), SMatNDMatrizNxM ( p_matVal ) ) );
}

SMatrizCuadradaND * SMatNDTranspuesta ( SMatrizCuadradaND * p_matObj )
{
	return ( _SMatNDEnvolver ( SMatNxMTranspuesta ( SMatNDMatrizNxM ( p_matObj ) ) ) );
}

SMatrizCuadradaND * SMatNDAdjunta ( SMatrizCuadradaND * p_matObj )
{
	return ( _SMatNDEnvolver ( SMatNxMAdjunta ( SMatNDMatrizNxM ( p_matObj ) ) ) );
}

SMatrizCuadradaND * SMatNDInversa ( SMatrizCuadradaND * p_matObj )
{
	return ( _SMatNDEnvolver ( SMatNxMInversa ( SMatNDMatrizNxM ( p_matObj ) ) ) );
}

int SMatNDMultiplicarEscalar ( SMatrizCuadradaND * p_matObj, double dVal )
{
	return ( SMatNxMMultiplicarEscalar ( SMatNDMatrizNxM ( p_matObj ), dVal ) );
}

SMatrizCuadradaND * SMatNDMultiplicar ( SMatrizCuadradaND * p_matObj, SMatrizCuadradaND * p_matVal )
{
	return ( _SMatNDEnvolver ( SMatNxMMultiplicar ( SMatNDMatrizNxM ( p_matObj ), SMatNDMatrizNxM ( p_matVal ) ) ) );
}

SVectorND * SMatNDMultiplicarPorIzq ( SMatrizCuadradaND * p_matObj, SVectorND * p_vecVal )
{
	return ( SMatNxMMultiplicarPorIzq ( SMatNDMatrizNxM ( p_matObj ), p_vecVal ) );
}

SVectorND * SMatNDMultiplicarPorDer ( SMatrizCuadradaND * p_matObj, SVectorND * p_vecVal )
{
	return ( SMatNxMMultiplicarPorDer ( SMatNDMatrizNxM ( p_matObj ), p_vecVal ) );
}

SMatrizCuadradaND * SMatNDDuplicar ( SMatrizCuadradaND * p_matObj )
{
	return ( _SMatNDEnvolver ( SMatNxMDuplicar ( SMatNDMatrizNxM ( p_matObj ) ) ) );
}

/* Nula si la matriz no es valida: asi las demas pueden delegar sin mirar,
   porque las de SMatrizNxM tratan la nula como no valida. */
SMatrizNxM * SMatNDMatrizNxM ( SMatrizCuadradaND * p_matObj )
{
	SMatrizNxM * p_matRes;

	if ( SMatNDEsValida ( p_matObj ) == 1 )
	{
		p_matRes = p_matObj->p_matObj;
	}
	else
	{
		p_matRes = NULL;
	}
	return ( p_matRes );
}

int SMatNDInicializarCero ( SMatrizCuadradaND * p_matObj )
{
	return ( SMatNxMInicializarCero ( SMatNDMatrizNxM ( p_matObj ) ) );
}

int SMatNDInicializarUnos ( SMatrizCuadradaND * p_matObj )
{
	return ( SMatNxMInicializarUnos ( SMatNDMatrizNxM ( p_matObj ) ) );
}

int SMatNDInicializarIdentidad ( SMatrizCuadradaND * p_matObj )
{
	return ( SMatNxMInicializarIdentidad ( SMatNDMatrizNxM ( p_matObj ) ) );
}
