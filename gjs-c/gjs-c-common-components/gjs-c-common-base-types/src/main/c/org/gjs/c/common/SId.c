#include "SId.h"


#include "TiposBasicosConfig.h"



SId * SIdCrear ()
{
	SId * p_idObj;
	
	p_idObj = (SId *) MemReservar ( sizeof ( SId ) );
	if ( ES_VALIDO ( p_idObj ) )
	{
		p_idObj->ulValor = 0;
	}
	return ( p_idObj );
}

void SIdDestruir ( SId ** p_p_idObj )
{
	SId * p_idObj;
	
	if ( ES_VALIDO ( p_p_idObj ) )
	{
		p_idObj = *p_p_idObj;

		if ( ES_VALIDO ( p_idObj ) )
		{
			MemLiberar ( (void **) p_p_idObj );
		}
	}
}

int SIdEsValido ( SId * p_idObj )
{
	int iRes;

	if ( ES_VALIDO ( p_idObj ) )
	{
		if ( p_idObj->ulValor > 0 )
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

unsigned long SIdValor ( SId * p_idObj )
{
	unsigned long ulRes;

	if ( ES_VALIDO ( p_idObj ) )
	{
		ulRes = p_idObj->ulValor;
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

int SIdEstablecer ( SId * p_idObj, unsigned long ulValor )
{
	int iRes;

	if ( ES_VALIDO ( p_idObj ) )
	{
		p_idObj->ulValor = ulValor;
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SIdEsIgual ( SId * p_idObj, SId * p_idVal )
{
	int iRes;

	if ( ( SIdEsValido ( p_idObj ) == 1 ) && ( SIdEsValido ( p_idVal ) == 1 ) )
	{
		iRes = SIdEsIgualEnt ( p_idObj, SIdValor ( p_idVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SIdEsMenor ( SId * p_idObj, SId * p_idVal )
{
	int iRes;

	if ( ( SIdEsValido ( p_idObj ) == 1 ) && ( SIdEsValido ( p_idVal ) == 1 ) )
	{
		iRes = SIdEsMenorEnt ( p_idObj, SIdValor ( p_idVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SIdEsMayor ( SId * p_idObj, SId * p_idVal )
{
	int iRes;

	if ( ( SIdEsValido ( p_idObj ) == 1 ) && ( SIdEsValido ( p_idVal ) == 1 ) )
	{
		iRes = SIdEsMayorEnt ( p_idObj, SIdValor ( p_idVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SIdEstaEnRango ( SId * p_idObj, SId * p_idVal1, SId * p_idVal2 )
{
	int iRes;

	if ( ( SIdEsValido ( p_idObj ) == 1 ) && ( SIdEsValido ( p_idVal1 ) == 1 ) && 
		 ( SIdEsValido ( p_idVal2 ) == 1 ) )
	{
		iRes = SIdEstaEnRangoEnt ( p_idObj, SIdValor ( p_idVal1 ), SIdValor ( p_idVal2 ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SIdEsMenorIg ( SId * p_idObj, SId * p_idVal )
{
	int iRes;

	if ( ( SIdEsValido ( p_idObj ) == 1 ) && ( SIdEsValido ( p_idVal ) == 1 ) )
	{
		iRes = SIdEsMenorIgEnt ( p_idObj, SIdValor ( p_idVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SIdEsMayorIg ( SId * p_idObj, SId * p_idVal )
{
	int iRes;

	if ( ( SIdEsValido ( p_idObj ) == 1 ) && ( SIdEsValido ( p_idVal ) == 1 ) )
	{
		iRes = SIdEsMayorIgEnt ( p_idObj, SIdValor ( p_idVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SIdEstaEnRangoIg ( SId * p_idObj, SId * p_idVal1, SId * p_idVal2 )
{
	int iRes;

	if ( ( SIdEsValido ( p_idObj ) == 1 ) && ( SIdEsValido ( p_idVal1 ) == 1 ) && 
		 ( SIdEsValido ( p_idVal2 ) == 1 ) )
	{
		iRes = SIdEstaEnRangoIgEnt ( p_idObj, SIdValor ( p_idVal1 ), SIdValor ( p_idVal2 ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SIdEsIgualEnt ( SId * p_idObj, unsigned long ulId )
{
	int iRes;

	if ( SIdEsValido ( p_idObj ) == 1 ) 
	{
		if ( p_idObj->ulValor == ulId )
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

int SIdEsMenorEnt ( SId * p_idObj, unsigned long ulId )
{
	int iRes;

	if ( SIdEsValido ( p_idObj ) == 1 ) 
	{
		if ( p_idObj->ulValor < ulId )
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

int SIdEsMayorEnt ( SId * p_idObj, unsigned long ulId )
{
	int iRes;

	if ( SIdEsValido ( p_idObj ) == 1 ) 
	{
		if ( p_idObj->ulValor > ulId )
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

int SIdEstaEnRangoEnt ( SId * p_idObj, unsigned long ulId1, unsigned long ulId2 )
{
	int iRes;

	if ( SIdEsValido ( p_idObj ) == 1 ) 
	{
		if ( ( p_idObj->ulValor > ulId1 ) && ( p_idObj->ulValor < ulId2 ) )
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

int SIdEsMenorIgEnt ( SId * p_idObj, unsigned long ulId )
{
	int iRes;

	if ( SIdEsValido ( p_idObj ) == 1 ) 
	{
		if ( p_idObj->ulValor <= ulId )
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

int SIdEsMayorIgEnt ( SId * p_idObj, unsigned long ulId )
{
	int iRes;

	if ( SIdEsValido ( p_idObj ) == 1 ) 
	{
		if ( p_idObj->ulValor >= ulId )
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

int SIdEstaEnRangoIgEnt ( SId * p_idObj, unsigned long ulId1, unsigned long ulId2 )
{
	int iRes;

	if ( SIdEsValido ( p_idObj ) == 1 ) 
	{
		if ( ( p_idObj->ulValor >= ulId1 ) && ( p_idObj->ulValor <= ulId2 ) )
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

unsigned int SIdHash ( SId * p_idObj )
{
	unsigned int uiRes = 0;

	if ( ES_VALIDO ( p_idObj ) )
	{
		uiRes = HashEnteroLargoSinSigno ( p_idObj->ulValor );
	}
	return ( uiRes );
}

