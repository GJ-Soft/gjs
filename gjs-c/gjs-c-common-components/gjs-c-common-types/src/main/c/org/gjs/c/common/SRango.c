
#include "SRango.h"


#include "TiposBasicosConfig.h"


SRango * SRngCrear ( int iMin, int iMax )
{
	SRango * p_rngObj;
	
	if ( ( iMin <= iMax ) )
	{
		p_rngObj = (SRango *) MemReservar ( sizeof ( SRango ) );
		if ( ES_VALIDO ( p_rngObj ) )
		{
			p_rngObj->iMin = iMin;
			p_rngObj->iMax = iMax;
		}
	}
	else
	{
		p_rngObj = NULL;
	}
	return ( p_rngObj );
}

void SRngDestruir ( SRango ** p_p_rngObj )
{
	SRango * p_rngObj;
	
	if ( ES_VALIDO ( p_p_rngObj ) )
	{
		p_rngObj = *p_p_rngObj;

		if ( ES_VALIDO ( p_rngObj ) )
		{
			MemLiberar ( (void **) p_p_rngObj );
		}
	}
}

int SRngEsValido ( SRango * p_rngObj )
{
	int iRes;

	if ( ES_VALIDO ( p_rngObj ) )
	{
		if ( p_rngObj->iMin <= p_rngObj->iMax )
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

int SRngMin ( SRango * p_rngObj )
{
	int iRes;

	if ( ES_VALIDO ( p_rngObj ) )
	{
		iRes = p_rngObj->iMin;
	}
	else
	{
		iRes = INT_MAX;
	}
	return ( iRes );
}

int SRngMax ( SRango * p_rngObj )
{
	int iRes;

	if ( ES_VALIDO ( p_rngObj ) )
	{
		iRes = p_rngObj->iMax;
	}
	else
	{
		iRes = INT_MIN;
	}
	return ( iRes );
}

int SRngAmplitud ( SRango * p_rngObj )
{
	int iRes;

	if ( ES_VALIDO ( p_rngObj ) )
	{
		iRes = p_rngObj->iMax - p_rngObj->iMin;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SRngEstablecerMin ( SRango * p_rngObj, int iMin )
{
	int iRes;

	if ( ES_VALIDO ( p_rngObj ) )
	{
		p_rngObj->iMin = iMin;
		iRes = SRngEsValido  ( p_rngObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SRngEstablecerMax ( SRango * p_rngObj, int iMax  )
{
	int iRes;

	if ( ES_VALIDO ( p_rngObj ) )
	{
		p_rngObj->iMax = iMax;
		iRes = SRngEsValido  ( p_rngObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SRngEstaIncluido ( SRango * p_rngObj, int iVal )
{
	int iRes;

	if ( ES_VALIDO ( p_rngObj ) )
	{
		if ( ( p_rngObj->iMin <= iVal ) &&
			 ( p_rngObj->iMax >= iVal ) )
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

