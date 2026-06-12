#include "SExtremoDominioReal.h"

#include "CalculoConfig.h"


SExtremoDominioReal * SExdRCrear ( double dValor, int iIncluido )
{
	SExtremoDominioReal * p_exdRes;

	p_exdRes = (SExtremoDominioReal *) MemReservar ( sizeof ( SExtremoDominioReal ) );
	if ( ES_VALIDO ( p_exdRes ) )
	{
		if ( iIncluido == 1 )
		{
			p_exdRes->iIncluido = 1;
		}
		else
		{
			p_exdRes->iIncluido = 0;
		}
		p_exdRes->iInfinito = 0;
		p_exdRes->dValor = dValor;
	}
	return ( p_exdRes );
}

SExtremoDominioReal * SExdRCrearInfinito ()
{
	SExtremoDominioReal * p_exdRes;

	p_exdRes = (SExtremoDominioReal *) MemReservar ( sizeof ( SExtremoDominioReal ) );
	if ( ES_VALIDO ( p_exdRes ) )
	{
		p_exdRes->iIncluido = 0;
		p_exdRes->iInfinito = 1;
		p_exdRes->dValor = 0.0;
	}
	return ( p_exdRes );
}

SExtremoDominioReal * SExdRCrearMenosInfinito ()
{
	SExtremoDominioReal * p_exdRes;

	p_exdRes = (SExtremoDominioReal *) MemReservar ( sizeof ( SExtremoDominioReal ) );
	if ( ES_VALIDO ( p_exdRes ) )
	{
		p_exdRes->iIncluido = 0;
		p_exdRes->iInfinito = -1;
		p_exdRes->dValor = 0.0;
	}
	return ( p_exdRes );
}

void SExdRDestruir ( SExtremoDominioReal ** p_p_exdObj )
{
	SExtremoDominioReal *	p_exdObj;

	if ( ES_VALIDO ( p_p_exdObj ) )
	{
		p_exdObj = *p_p_exdObj;
		if ( ES_VALIDO ( p_exdObj ) )
		{
			MemLiberar ( (void **) p_p_exdObj );
		}
	}
}

int SExdREsValido ( SExtremoDominioReal * p_exdObj )
{
	int iRes;

	if ( ES_VALIDO ( p_exdObj ) )
	{
		if ( ( p_exdObj->iInfinito == -1 ) || ( p_exdObj->iInfinito == 1 ) )
		{
			if ( ( p_exdObj->dValor == 0.0 ) && ( p_exdObj->iIncluido == 0 ) )
			{
				iRes = 1;
			}
			else
			{
				iRes = 0;
			}
		}
		else if ( p_exdObj->iInfinito == 0 )
		{
			if ( ( p_exdObj->iIncluido == 1 ) || ( p_exdObj->iIncluido == 0 ) )
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

double SExdRValor ( SExtremoDominioReal * p_exdObj )
{
	double dRes;

	if ( ES_VALIDO ( p_exdObj ) )
	{
		if ( p_exdObj->iInfinito == 1 )
		{
			dRes = DBL_MAX;
		}
		else if ( p_exdObj->iInfinito == -1 )
		{
			dRes = -DBL_MAX;
		}
		else
		{
			dRes = p_exdObj->dValor;
		}
	}
	else
	{
		dRes = 0.0;
	}
	return ( dRes );
}

int SExdREstaIncluido ( SExtremoDominioReal * p_exdObj )
{
	int iRes;

	if ( ES_VALIDO ( p_exdObj ) )
	{
		if ( p_exdObj->iIncluido == 1 )
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

int SExdREsInfinito ( SExtremoDominioReal * p_exdObj )
{
	int iRes;

	if ( ES_VALIDO ( p_exdObj ) )
	{
		if ( p_exdObj->iInfinito == 1 )
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

int SExdREsMenosInfinito ( SExtremoDominioReal * p_exdObj )
{
	int iRes;

	if ( ES_VALIDO ( p_exdObj ) )
	{
		if ( p_exdObj->iInfinito == -1 )
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

SExtremoDominioReal * SExdRDuplicar ( SExtremoDominioReal * p_exdObj )
{
	SExtremoDominioReal * p_exdRes;

	if ( ES_VALIDO ( p_exdObj ) )
	{
		if ( SExdREsInfinito ( p_exdObj ) == 1 )
		{
			p_exdRes = SExdRCrearInfinito ();
		}
		else if ( SExdREsMenosInfinito ( p_exdObj ) == 1 )
		{
			p_exdRes = SExdRCrearMenosInfinito ();
		}
		else
		{
			p_exdRes = SExdRCrear ( p_exdObj->dValor, p_exdObj->iIncluido );
		}
	}
	else
	{
		p_exdRes = NULL;
	}
	return ( p_exdRes );
}

