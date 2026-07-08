
#include "SContador.h"

#include "TiposBasicosConfig.h"



SContador * SCntCrear ( unsigned long ulMin, unsigned long ulMax )
{
	SContador * p_cntObj;
	
	if ( ulMin <= ulMax )
	{
		p_cntObj = (SContador *) MemReservar ( sizeof ( SContador ) );
		if ( ES_VALIDO ( p_cntObj ) )
		{
			p_cntObj->ulMin = ulMin;
			p_cntObj->ulMax = ulMax;
			p_cntObj->ulValor = p_cntObj->ulMin;
		}
	}
	else
	{
		p_cntObj = NULL;
	}
	return ( p_cntObj );
}

void SCntDestruir ( SContador ** p_p_cntObj )
{
	SContador * p_cntObj;
	
	if ( ES_VALIDO ( p_p_cntObj ) )
	{
		p_cntObj = *p_p_cntObj;

		if ( ES_VALIDO ( p_cntObj ) )
		{
			MemLiberar ( (void **) p_p_cntObj );
		}
	}
}

unsigned long SCntValor ( SContador * p_cntObj )
{
	unsigned long ulRes;

	if ( ES_VALIDO ( p_cntObj ) )
	{
		ulRes = p_cntObj->ulValor;
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

unsigned long SCntMin ( SContador * p_cntObj )
{
	unsigned long ulRes;

	if ( ES_VALIDO ( p_cntObj ) )
	{
		ulRes = p_cntObj->ulMin;
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

unsigned long SCntMax ( SContador * p_cntObj )
{
	unsigned long ulRes;

	if ( ES_VALIDO ( p_cntObj ) )
	{
		ulRes = p_cntObj->ulMax;
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

int SCntIniciar ( SContador * p_cntObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cntObj ) )
	{
		p_cntObj->ulValor = p_cntObj->ulMin;
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCntIncrementar ( SContador * p_cntObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cntObj ) )
	{
		if ( p_cntObj->ulValor < p_cntObj->ulMax )
		{
			p_cntObj->ulValor = p_cntObj->ulValor + 1;
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

int SCntDecrementar ( SContador * p_cntObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cntObj ) )
	{
		if ( p_cntObj->ulValor > p_cntObj->ulMin )
		{
			p_cntObj->ulValor = p_cntObj->ulValor - 1;
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

int SCntEstaEnValorMax ( SContador * p_cntObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cntObj ) )
	{
		if ( p_cntObj->ulValor == p_cntObj->ulMax )
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

int SCntEstaEnValorMin ( SContador * p_cntObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cntObj ) )
	{
		if ( p_cntObj->ulValor == p_cntObj->ulMin )
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

