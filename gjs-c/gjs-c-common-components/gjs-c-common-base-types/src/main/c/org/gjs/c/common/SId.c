#include "SId.h"


#include "TiposBasicosConfig.h"



SId * SIdCrearDef ()
{
	SId * p_idObj;
	
	p_idObj = (SId *) MemReservar ( sizeof ( SId ) );
	if ( ES_VALIDO ( p_idObj ) )
	{
		p_idObj->ulValor = 0;
	}
	return ( p_idObj );
}

SId * SIdCrear ( unsigned long ulValor )
{
	SId * p_idObj;
	
	p_idObj = SIdCrearDef ();
	if ( ES_VALIDO ( p_idObj ) )
	{
		SIdEstablecer ( p_idObj, ulValor );
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

int SIdAsignar ( SId * p_idObj, SId * p_idValor )
{
	int iRes;

	if ( ES_VALIDO ( p_idObj ) && ES_VALIDO ( p_idValor ) )
	{
		iRes = SIdEstablecer ( p_idObj, SIdValor ( p_idValor ) );
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

	if ( ES_VALIDO ( p_idObj ) && ES_VALIDO ( p_idVal ) )
	{
		iRes = SIdEsIgualNum ( p_idObj, SIdValor ( p_idVal ) );
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

	if ( ES_VALIDO ( p_idObj ) && ES_VALIDO ( p_idVal ) )
	{
		iRes = SIdEsMenorNum ( p_idObj, SIdValor ( p_idVal ) );
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

	if ( ES_VALIDO ( p_idObj ) && ES_VALIDO ( p_idVal ) )
	{
		iRes = SIdEsMayorNum ( p_idObj, SIdValor ( p_idVal ) );
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

	if ( ES_VALIDO ( p_idObj ) && ES_VALIDO ( p_idVal1 ) && 
		 ES_VALIDO ( p_idVal2 ) )
	{
		iRes = SIdEstaEnRangoNum ( p_idObj, SIdValor ( p_idVal1 ), SIdValor ( p_idVal2 ) );
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

	if ( ES_VALIDO ( p_idObj ) && ES_VALIDO ( p_idVal ) )
	{
		iRes = SIdEsMenorIgNum ( p_idObj, SIdValor ( p_idVal ) );
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

	if ( ES_VALIDO ( p_idObj ) && ES_VALIDO ( p_idVal ) )
	{
		iRes = SIdEsMayorIgNum ( p_idObj, SIdValor ( p_idVal ) );
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

	if ( ES_VALIDO ( p_idObj ) && ES_VALIDO ( p_idVal1 ) && 
		 ES_VALIDO ( p_idVal2 ) )
	{
		iRes = SIdEstaEnRangoIgNum ( p_idObj, SIdValor ( p_idVal1 ), SIdValor ( p_idVal2 ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SIdEsIgualNum ( SId * p_idObj, unsigned long ulId )
{
	int iRes;

	if ( ES_VALIDO ( p_idObj ) ) 
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

int SIdEsMenorNum ( SId * p_idObj, unsigned long ulId )
{
	int iRes;

	if ( ES_VALIDO ( p_idObj ) ) 
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

int SIdEsMayorNum ( SId * p_idObj, unsigned long ulId )
{
	int iRes;

	if ( ES_VALIDO ( p_idObj ) ) 
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

int SIdEstaEnRangoNum ( SId * p_idObj, unsigned long ulId1, unsigned long ulId2 )
{
	int iRes;

	if ( ES_VALIDO ( p_idObj ) ) 
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

int SIdEsMenorIgNum ( SId * p_idObj, unsigned long ulId )
{
	int iRes;

	if ( ES_VALIDO ( p_idObj ) ) 
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

int SIdEsMayorIgNum ( SId * p_idObj, unsigned long ulId )
{
	int iRes;

	if ( ES_VALIDO ( p_idObj ) ) 
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

int SIdEstaEnRangoIgNum ( SId * p_idObj, unsigned long ulId1, unsigned long ulId2 )
{
	int iRes;

	if ( ES_VALIDO ( p_idObj ) ) 
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

int SIdComparar ( SId * p_idObj, SId * p_idVal )
{
	int iRes;

	if ( ES_VALIDO ( p_idObj ) && ES_VALIDO ( p_idVal ) )
	{
		iRes = SIdCompararNum ( p_idObj, SIdValor ( p_idVal ) );
	}
	else if  ( ES_VALIDO ( p_idObj ) )
	{
		iRes = COMP_MAYOR;
	}
	else if  ( ES_VALIDO ( p_idVal ) )
	{
		iRes = COMP_MENOR;
	}
	else
	{
		iRes = COMP_IGUAL;
	}
	return ( iRes );
}

int SIdCompararNum ( SId * p_idObj, unsigned long ulId )
{
	int iRes;

	if ( ES_VALIDO ( p_idObj ) ) 
	{
		if ( p_idObj->ulValor < ulId )
		{
			iRes = COMP_MENOR;
		}
		else if ( p_idObj->ulValor > ulId )
		{
			iRes = COMP_MAYOR;
		}
		else
		{
			iRes = COMP_IGUAL;
		}
	}
	else
	{
		iRes = COMP_MENOR;
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

