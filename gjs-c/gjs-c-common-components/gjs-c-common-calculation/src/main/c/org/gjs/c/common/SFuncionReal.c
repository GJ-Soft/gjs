#include "SFuncionReal.h"

#include "CalculoConfig.h"



static double FunRealComponer ( PFUNREAL p_fObj1, PFUNREAL p_fObj2, double x );



double FunRealComponer ( PFUNREAL p_fObj1, PFUNREAL p_fObj2, double x ) 
{
    return p_fObj1 ( p_fObj2 ( x ) );
}



SFuncionReal * SFunRCrear ( PFUNREAL p_fCalculo )
{
	SFuncionReal * p_funObj;

	if ( ES_VALIDO ( p_fCalculo ) )
	{
		p_funObj = ( SFuncionReal * ) MemReservar ( sizeof ( SFuncionReal ) );
		if ( ES_VALIDO ( p_funObj ) )
		{
			p_funObj->p_fCalculo = p_fCalculo;
		}
	}
	else
	{
		p_funObj = NULL;
	}
	return ( p_funObj );
}

SFuncionReal * SFunRCrearComposicion ( PFUNREAL p_fCalculo, SFuncionReal* p_funInterna )
{
	SFuncionReal * p_funObj = SFunRCrear ( p_fCalculo );
	if ( ES_VALIDO ( p_funObj ) )
	{
		p_funObj->p_funInterior = (struct SFuncionReal *) p_funInterna;
	}
	return ( p_funObj );
}

void SFunRDestruir ( SFuncionReal ** p_p_funObj )
{
	SFuncionReal * p_funObj;
	SFuncionReal * p_funInt;

	if ( ES_VALIDO ( p_p_funObj ) )
	{
		p_funObj = * p_p_funObj;
		if ( ES_VALIDO ( p_funObj ) )
		{
			p_funInt = SFunRFuncionInterior ( p_funObj );
			SFunRDestruir ( &p_funInt );
			MemLiberar ( ( void ** ) p_p_funObj );
		}
	}
}

int SFunREsValida ( SFuncionReal * p_funObj )
{
	int iRes;

	if ( ES_VALIDO ( p_funObj ) )
	{
		if ( ES_VALIDO ( p_funObj->p_fCalculo ) )
		{
			if ( ES_VALIDO ( p_funObj->p_funInterior ) )
			{
				iRes = SFunREsValida ( SFunRFuncionInterior ( p_funObj ) );
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
	}
	else
	{
		iRes = 0;
	}
	return (iRes);
}

SFuncionReal * SFunRFuncionInterior ( SFuncionReal * p_funObj ) 
{
	SFuncionReal * p_funRes;

	if ( ES_VALIDO ( p_funObj ) )
	{
		p_funRes = (SFuncionReal *) p_funObj->p_funInterior;
	}
	else
	{
		p_funRes = NULL;
	}
	return ( p_funRes );
}

int SFunREsCompuesta ( SFuncionReal * p_funObj )
{
	int iRes;

	if ( ES_VALIDO ( p_funObj ) )
	{
		if ( ES_VALIDO ( p_funObj->p_funInterior ) )
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
	return (iRes);
}

double SFunREvaluar ( SFuncionReal * p_funObj, double dValor )
{
	double dRes;

	if ( ( SFunREsValida ( p_funObj ) == 1 ) )
	{
		if ( ES_VALIDO ( p_funObj->p_funInterior ) )
		{
			dRes = SFunREvaluar ( SFunRFuncionInterior ( p_funObj ), dValor );
		} 
		else
		{
			dRes = dValor;
		}
		dRes = p_funObj->p_fCalculo ( dRes );
	}
	else
	{
		dRes = 0.0;
	}
	return ( dRes );
}

void SFunRComponer ( SFuncionReal * p_funObj, SFuncionReal * p_funInterna )
{
	if ( ( SFunREsValida ( p_funObj ) == 1 ) && ( SFunREsValida ( p_funInterna ) == 1 ) )
	{
		p_funObj->p_funInterior = ( struct SFuncionReal * ) p_funInterna;
	}
}

SFuncionReal * SFunRDuplicar ( SFuncionReal * p_funObj )
{
	SFuncionReal * p_funRes;

	if ( ES_VALIDO ( p_funObj ) )
	{
		p_funRes = SFunRCrearComposicion ( p_funObj->p_fCalculo, SFunRDuplicar ( SFunRFuncionInterior ( p_funObj ) ) );
	}
	else 
	{
		p_funRes = NULL;
	}
	return ( p_funRes );
}

SFuncionReal * SFunRValorAbsoluto ( SFuncionReal * p_funObj )
{
	return ( SFunRCrearComposicion ( MatRealAbsoluto, p_funObj ) );
}

SFuncionReal * SFunRNegada ( SFuncionReal * p_funObj )
{
	return ( SFunRCrearComposicion ( MatRealNegar, p_funObj ) );
}

SFuncionReal * SFunRInversa ( SFuncionReal * p_funObj )
{
	return ( SFunRCrearComposicion ( MatRealInvertir, p_funObj ) );
}

