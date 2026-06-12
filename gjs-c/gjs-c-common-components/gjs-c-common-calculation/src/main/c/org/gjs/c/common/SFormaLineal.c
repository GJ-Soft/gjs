
#include "SFormaLineal.h"

#include "CalculoConfig.h"






SFormaLineal * SFrmLinCrear ( int iNumVariables )
{
	int				iCoef;
	SFormaLineal * p_frmlinObj;
	
	if ( iNumVariables > 0 )
	{
		p_frmlinObj= (SFormaLineal *) MemReservar ( sizeof ( SFormaLineal ) );
		if ( ES_VALIDO ( p_frmlinObj ) )
		{
			p_frmlinObj->iNumVariables = iNumVariables;
			p_frmlinObj->p_dCoeficientes = (double *) MemReservar ( iNumVariables * sizeof ( double ) );
			if ( ES_VALIDO ( p_frmlinObj->p_dCoeficientes ) )
			{
				for ( iCoef = 0; iCoef < p_frmlinObj->iNumVariables; iCoef = iCoef + 1 )
				{
					p_frmlinObj->p_dCoeficientes [ iCoef ] = 0.0;
				}
			}
			else
			{
				MemLiberar ( (void **) &p_frmlinObj );
			}
		}
	}
	else
	{
		p_frmlinObj = NULL;
	}
	return ( p_frmlinObj );
}

SFormaLineal * SFrmLinCrearExt ( int iNumVariables, ... )
{
	SFormaLineal * p_frmlinObj;
	va_list		valCoeficientes;
	double 		dValor;
	int			iValor;

	p_frmlinObj= SFrmLinCrear ( iNumVariables );
	if ( ES_VALIDO ( p_frmlinObj ) )
	{
		if ( iNumVariables > 0 )
		{
			va_start ( valCoeficientes, iNumVariables );
			iValor = 0; 
			while ( iValor < p_frmlinObj->iNumVariables )
			{
				dValor = va_arg ( valCoeficientes, double );
				p_frmlinObj->p_dCoeficientes [ iValor ] = dValor;
				iValor = iValor + 1;
			}
			va_end ( valCoeficientes );
		}
		else
		{
			p_frmlinObj = NULL;
		}
	}
	return ( p_frmlinObj );
}

SFormaLineal * SFrmLinCrear1 ( double dCoef )
{
	SFormaLineal * p_frmlinObj;

	p_frmlinObj= SFrmLinCrear ( 1 );
	if ( ES_VALIDO ( p_frmlinObj ) )
	{
		p_frmlinObj->p_dCoeficientes [ 0 ] = dCoef;
	}
	return ( p_frmlinObj );
}

SFormaLineal * SFrmLinCrear2 ( double dCoef1, double dCoef2 )
{
	SFormaLineal * p_frmlinObj;

	p_frmlinObj= SFrmLinCrear ( 2 );
	if ( ES_VALIDO ( p_frmlinObj ) )
	{
		p_frmlinObj->p_dCoeficientes [ 0 ] = dCoef1;
		p_frmlinObj->p_dCoeficientes [ 1 ] = dCoef2;
	}
	return ( p_frmlinObj );
}

SFormaLineal * SFrmLinCrear3 ( double dCoef1, double dCoef2, double dCoef3 )
{
	SFormaLineal * p_frmlinObj;

	p_frmlinObj= SFrmLinCrear ( 3 );
	if ( ES_VALIDO ( p_frmlinObj ) )
	{
		p_frmlinObj->p_dCoeficientes [ 0 ] = dCoef1;
		p_frmlinObj->p_dCoeficientes [ 1 ] = dCoef2;
		p_frmlinObj->p_dCoeficientes [ 2 ] = dCoef3;
	}
	return ( p_frmlinObj );
}

void SFrmLinDestruir ( SFormaLineal ** p_p_frmlinObj )
{
	SFormaLineal * p_frmlinObj;
	
	if ( ES_VALIDO ( p_p_frmlinObj ) )
	{
		p_frmlinObj = *p_p_frmlinObj;

		if ( ES_VALIDO ( p_frmlinObj ) )
		{
			MemLiberar ( (void **) &(p_frmlinObj->p_dCoeficientes) );
			MemLiberar ( (void **) p_p_frmlinObj );
		}
	}
}

int SFrmLinEsValido ( SFormaLineal * p_frmlinObj )
{
	int iRes;

	if ( ES_VALIDO ( p_frmlinObj ) )
	{
		if ( ( p_frmlinObj->iNumVariables > 0 ) && ES_VALIDO ( p_frmlinObj->p_dCoeficientes ) )
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

int SFrmLinNumVariables ( SFormaLineal * p_frmlinObj )
{
	int iRes;

	if ( ES_VALIDO ( p_frmlinObj ) )
	{
		iRes = p_frmlinObj->iNumVariables;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


double SFrmLinCoeficiente ( SFormaLineal * p_frmlinObj, int iCoeficiente )
{
	double dRes;

	if ( ES_VALIDO ( p_frmlinObj ) )
	{
		if ( ( iCoeficiente >= 0 ) && ( iCoeficiente < p_frmlinObj->iNumVariables ) )
		{
			dRes = p_frmlinObj->p_dCoeficientes [ iCoeficiente ];
		}
		else
		{
			dRes = 0.0;
		}
	}
	else
	{
		dRes = 0.0;
	}
	return ( dRes );
}

double SFrmLinCoeficiente1 ( SFormaLineal * p_frmlinObj )
{
	return ( SFrmLinCoeficiente ( p_frmlinObj, 0 ) );
}

double SFrmLinCoeficiente2 ( SFormaLineal * p_frmlinObj )
{
	return ( SFrmLinCoeficiente ( p_frmlinObj, 1 ) );
}

double SFrmLinCoeficiente3 ( SFormaLineal * p_frmlinObj )
{
	return ( SFrmLinCoeficiente ( p_frmlinObj, 2 ) );
}

int SFrmLinEstablecerCoeficiente ( SFormaLineal * p_frmlinObj, int iCoeficiente, double dValor )
{
	int iRes;

	if ( ES_VALIDO ( p_frmlinObj ) )
	{
		if ( ( iCoeficiente >= 0 ) && ( iCoeficiente < p_frmlinObj->iNumVariables ) )
		{
			p_frmlinObj->p_dCoeficientes [ iCoeficiente ] = dValor;
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

double * SFrmLinVectorValores ( SFormaLineal * p_frmlinObj )
{
	double * p_dRes;
	
	if ( SFrmLinEsValido ( p_frmlinObj ) == 1 )
	{
		p_dRes = (double *) MemReservar ( p_frmlinObj->iNumVariables * sizeof ( double ) );
		if ( ES_VALIDO ( p_dRes ) )
		{
			for ( int i = 0; i < p_frmlinObj->iNumVariables; i = i + 1 )
			{
				p_dRes [ i ] = 0.0;
			}
		}
	}
	else
	{
		p_dRes = NULL;
	}
	return ( p_dRes );
}

double SFrmLinEvaluar ( SFormaLineal * p_frmlinObj, double * p_dValores )
{
	int		iCoef;
	double 	dRes;

	if ( ( SFrmLinEsValido ( p_frmlinObj ) == 1 ) && ES_VALIDO ( p_dValores ) )
	{
		dRes = 0.0;
		for ( iCoef = 0; iCoef < p_frmlinObj->iNumVariables; iCoef = iCoef + 1 )
		{
			dRes = dRes + p_frmlinObj->p_dCoeficientes [ iCoef ] * p_dValores [ iCoef ];
		}
	}
	else
	{
		dRes = 0.0;
	}
	return ( dRes );
}

double SFrmLinEvaluarExt ( SFormaLineal * p_frmlinObj, ... )
{
	int			iCoef;
	double 		dRes;
	va_list		valCoeficientes;
	double 		dValor;

	if ( SFrmLinEsValido ( p_frmlinObj ) == 1 ) 
	{
		dRes = 0.0;
		va_start ( valCoeficientes, p_frmlinObj );
		for ( iCoef = 0; iCoef < p_frmlinObj->iNumVariables; iCoef = iCoef + 1 )
		{
			dValor = va_arg ( valCoeficientes, double );
			dRes = dRes + p_frmlinObj->p_dCoeficientes [ iCoef ] * dValor;
		}
		va_end ( valCoeficientes );
	}
	else
	{
		dRes = 0.0;
	}
	return ( dRes );
}

int SFrmLinMultiplicar ( SFormaLineal * p_frmlinObj, double dValor )
{
	int iRes;
	int	iCoef;

	if ( SFrmLinEsValido ( p_frmlinObj ) == 1 )
	{
		for ( iCoef = 0; iCoef < p_frmlinObj->iNumVariables; iCoef = iCoef + 1 )
		{
			p_frmlinObj->p_dCoeficientes [ iCoef ] = p_frmlinObj->p_dCoeficientes [ iCoef ] * dValor;
		}
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFrmLinSumar ( SFormaLineal * p_frmlinObj, SFormaLineal * p_frmlinValor )
{
	int iRes;
	int	iCoef;

	if ( ( SFrmLinEsValido ( p_frmlinObj ) == 1 ) && ( SFrmLinEsValido ( p_frmlinValor ) == 1 ) )
	{
		for ( iCoef = 0; iCoef < p_frmlinObj->iNumVariables; iCoef = iCoef + 1 )
		{
			p_frmlinObj->p_dCoeficientes [ iCoef ] = p_frmlinObj->p_dCoeficientes [ iCoef ] + SFrmLinCoeficiente ( p_frmlinValor, iCoef );
		}
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SFormaLineal * SFrmLinDuplicar  ( SFormaLineal * p_frmlinObj )
{
	SFormaLineal *	p_frmlinRes;
	int				iCoef;

	if ( ES_VALIDO ( p_frmlinObj ) )
	{
		p_frmlinRes = SFrmLinCrear ( p_frmlinObj->iNumVariables );
		for ( iCoef = 0; iCoef < p_frmlinObj->iNumVariables; iCoef = iCoef + 1 )
		{
			SFrmLinEstablecerCoeficiente ( p_frmlinRes, iCoef, p_frmlinObj->p_dCoeficientes [ iCoef ] );
		}
	}
	else
	{
		p_frmlinRes = NULL;
	}
	return ( p_frmlinRes );
}

