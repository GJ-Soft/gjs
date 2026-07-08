
#include "SIndicador.h"

#include "TiposBasicosConfig.h"



SIndicador * SIndCrear ( unsigned long ulMax )
{
	SIndicador * p_indObj;
	
	if ( ulMax > 0 )
	{
		p_indObj = (SIndicador *) MemReservar ( sizeof ( SIndicador ) );
		if ( ES_VALIDO ( p_indObj ) )
		{
			p_indObj->ulMax = ulMax;
			p_indObj->ulValor = 0;
		}
	}
	else
	{
		p_indObj = NULL;
	}
	return ( p_indObj );
}

void SIndDestruir ( SIndicador ** p_p_indObj )
{
	SIndicador * p_indObj;
	
	if ( ES_VALIDO ( p_p_indObj ) )
	{
		p_indObj = *p_p_indObj;

		if ( ES_VALIDO ( p_indObj ) )
		{
			MemLiberar ( (void **) p_p_indObj );
		}
	}
}

int SIndEsValido ( SIndicador * p_indObj )
{
	int iRes;

	if ( ES_VALIDO ( p_indObj ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

unsigned long SIndValor ( SIndicador * p_indObj )
{
	unsigned long ulRes;

	if ( ES_VALIDO ( p_indObj ) )
	{
		ulRes = p_indObj->ulValor;
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

unsigned long SIndMax ( SIndicador * p_indObj )
{
	unsigned long ulRes;

	if ( ES_VALIDO ( p_indObj ) )
	{
		ulRes = p_indObj->ulMax;
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

int SIndInicio ( SIndicador * p_indObj )
{
	int iRes;

	if ( ES_VALIDO ( p_indObj ) )
	{
		p_indObj->ulValor = 0;
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SIndFinal ( SIndicador * p_indObj )
{
	int iRes;

	if ( ES_VALIDO ( p_indObj ) )
	{
		p_indObj->ulValor = p_indObj->ulMax;
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SIndIncrementar ( SIndicador * p_indObj )
{
	return ( SIndIncrementarExt ( p_indObj, 1 ) );
}

int SIndDecrementar ( SIndicador * p_indObj )
{
	return ( SIndDecrementarExt ( p_indObj, 1 ) );
}

int SIndIncrementarExt ( SIndicador * p_indObj, unsigned long ulValor )
{
	int iRes;

	if ( ES_VALIDO ( p_indObj ) && ( ulValor > 0 ) )
	{
		if ( p_indObj->ulValor + ulValor <= p_indObj->ulMax )
		{
			p_indObj->ulValor = p_indObj->ulValor + ulValor;
			iRes = 1;
		}
		else
		{
			p_indObj->ulValor = p_indObj->ulMax;
			iRes = 0;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SIndDecrementarExt ( SIndicador * p_indObj, unsigned long ulValor )
{
	int iRes;

	if ( ES_VALIDO ( p_indObj ) && ( ulValor > 0 ) )
	{
		if ( p_indObj->ulValor >= ulValor )
		{
			p_indObj->ulValor = p_indObj->ulValor - ulValor;
			iRes = 1;
		}
		else
		{
			p_indObj->ulValor = 0;
			iRes = 0;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SIndMoverA ( SIndicador * p_indObj, unsigned long ulValor )
{
	int iRes;

	if ( ES_VALIDO ( p_indObj ) )
	{
		if ( ulValor <= p_indObj->ulMax )
		{
			p_indObj->ulValor = ulValor;
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

int SIndEstaEnFinal ( SIndicador * p_indObj )
{
	int iRes;

	if ( ES_VALIDO ( p_indObj ) )
	{
		if ( p_indObj->ulValor == p_indObj->ulMax )
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

int SIndEstaEnInicio ( SIndicador * p_indObj )
{
	int iRes;

	if ( ES_VALIDO ( p_indObj ) )
	{
		if ( p_indObj->ulValor == 0 )
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

int SIndPuedeIncrementar ( SIndicador * p_indObj, unsigned long ulValor )
{
	int iRes;

	if ( ES_VALIDO ( p_indObj ) && ( ulValor > 0 ) )
	{
		if ( p_indObj->ulValor + ulValor <= p_indObj->ulMax )
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

int SIndPuedeDecrementar ( SIndicador * p_indObj, unsigned long ulValor )
{
	int iRes;

	if ( ES_VALIDO ( p_indObj ) && ( ulValor > 0 ) )
	{
		if ( p_indObj->ulValor >= ulValor )
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

int SIndPuedeMoverA ( SIndicador * p_indObj, unsigned long ulValor )
{
	int iRes;

	if ( ES_VALIDO ( p_indObj ) )
	{
		if ( ulValor <= p_indObj->ulMax )
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
