
#include "SIndicador2D.h"


#include "TiposBasicosConfig.h"


SIndicador2D * SInd2DCrear ( unsigned long ulMax1, unsigned long ulMax2 )
{
	SIndicador2D * p_indObj;
	
	if ( ( ulMax1 > 0 ) && ( ulMax2 > 0 ) )
	{
		p_indObj = (SIndicador2D *) MemReservar ( sizeof ( SIndicador2D ) );
		if ( ES_VALIDO ( p_indObj ) )
		{
			p_indObj->p_indDimension1 = SIndCrear ( ulMax1 );
			p_indObj->p_indDimension2 = SIndCrear ( ulMax2 );
		}
	}
	else
	{
		p_indObj = NULL;
	}
	return ( p_indObj );
}

void SInd2DDestruir ( SIndicador2D ** p_p_indObj )
{
	SIndicador2D * p_indObj;
	
	if ( ES_VALIDO ( p_p_indObj ) )
	{
		p_indObj = *p_p_indObj;

		if ( ES_VALIDO ( p_indObj ) )
		{
			SIndDestruir ( &(p_indObj->p_indDimension1) );
			SIndDestruir ( &(p_indObj->p_indDimension2) );
			MemLiberar ( (void **) p_p_indObj );
		}
	}
}

int SInd2DEsValido ( SIndicador2D * p_indObj )
{
	int iRes;

	if ( ES_VALIDO ( p_indObj ) )
	{
		if ( ( SIndEsValido ( p_indObj->p_indDimension1 ) == 1 ) &&
			 ( SIndEsValido ( p_indObj->p_indDimension2 ) == 1 ) )
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

SIndicador * SInd2DDimension1 ( SIndicador2D * p_indObj )
{
	SIndicador * p_indRes;

	if ( ES_VALIDO ( p_indObj ) )
	{
		p_indRes = p_indObj->p_indDimension1;
	}
	else
	{
		p_indRes = NULL;
	}
	return ( p_indRes );
}

SIndicador * SInd2DDimension2 ( SIndicador2D * p_indObj )
{
	SIndicador * p_indRes;

	if ( ES_VALIDO ( p_indObj ) )
	{
		p_indRes = p_indObj->p_indDimension2;
	}
	else
	{
		p_indRes = NULL;
	}
	return ( p_indRes );
}

unsigned long SInd2DValor1 ( SIndicador2D * p_indObj )
{
	unsigned long ulRes;

	if ( ES_VALIDO ( p_indObj ) )
	{
		ulRes = SIndValor ( p_indObj->p_indDimension1 );
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

unsigned long SInd2DMax1 ( SIndicador2D * p_indObj )
{
	unsigned long ulRes;

	if ( ES_VALIDO ( p_indObj ) )
	{
		ulRes = SIndMax ( p_indObj->p_indDimension1 );
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

unsigned long SInd2DValor2 ( SIndicador2D * p_indObj )
{
	unsigned long ulRes;

	if ( ES_VALIDO ( p_indObj ) )
	{
		ulRes = SIndValor ( p_indObj->p_indDimension2 );
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

unsigned long SInd2DMax2 ( SIndicador2D * p_indObj )
{
	unsigned long ulRes;

	if ( ES_VALIDO ( p_indObj ) )
	{
		ulRes = SIndMax ( p_indObj->p_indDimension2 );
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

int SInd2DInicio ( SIndicador2D * p_indObj )
{
	int iRes;

	if ( ES_VALIDO ( p_indObj ) )
	{
		if ( ( SIndInicio ( p_indObj->p_indDimension1 ) == 1 ) &&
			 ( SIndInicio ( p_indObj->p_indDimension2 ) == 1 ) )
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

int SInd2DFinal ( SIndicador2D * p_indObj )
{
	int iRes;

	if ( ES_VALIDO ( p_indObj ) )
	{
		if ( ( SIndFinal ( p_indObj->p_indDimension1 ) == 1 ) &&
			 ( SIndFinal ( p_indObj->p_indDimension2 ) == 1 ) )
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

int SInd2DIncrementar ( SIndicador2D * p_indObj, unsigned long ulValor1, unsigned long ulValor2 )
{
	int iRes;

	if ( ES_VALIDO ( p_indObj ) )
	{
		if ( ( SIndPuedeIncrementar ( p_indObj->p_indDimension1, ulValor1 ) == 1 ) &&
			 ( SIndPuedeIncrementar ( p_indObj->p_indDimension2, ulValor2 ) == 1 ) )
		{
			SIndIncrementarExt ( p_indObj->p_indDimension1, ulValor1 );
			SIndIncrementarExt ( p_indObj->p_indDimension2, ulValor2 );
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

int SInd2DDecrementar ( SIndicador2D * p_indObj, unsigned long ulValor1, unsigned long ulValor2 )
{
	int iRes;

	if ( ES_VALIDO ( p_indObj ) )
	{
		if ( ( SIndPuedeDecrementar ( p_indObj->p_indDimension1, ulValor1 ) == 1 ) &&
			 ( SIndPuedeDecrementar ( p_indObj->p_indDimension2, ulValor2 ) == 1 ) )
		{
			SIndDecrementarExt ( p_indObj->p_indDimension1, ulValor1 );
			SIndDecrementarExt ( p_indObj->p_indDimension2, ulValor2 );
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

int SInd2DMoverA ( SIndicador2D * p_indObj, unsigned long ulValor1, unsigned long ulValor2 )
{
	int iRes;

	if ( ES_VALIDO ( p_indObj ) )
	{
		if ( ( SIndPuedeMoverA ( p_indObj->p_indDimension1, ulValor1 ) == 1 ) &&
			 ( SIndPuedeMoverA ( p_indObj->p_indDimension2, ulValor2 ) == 1 ) )
		{
			SIndMoverA ( p_indObj->p_indDimension1, ulValor1 );
			SIndMoverA ( p_indObj->p_indDimension2, ulValor2 );
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

int SInd2DEstaEnFinal ( SIndicador2D * p_indObj )
{
	int iRes;

	if ( ES_VALIDO ( p_indObj ) )
	{
		if ( ( SIndEstaEnFinal ( p_indObj->p_indDimension1 ) == 1 ) &&
			 ( SIndEstaEnFinal ( p_indObj->p_indDimension2 ) == 1 ) )
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

int SInd2DEstaEnInicio ( SIndicador2D * p_indObj )
{
	int iRes;

	if ( ES_VALIDO ( p_indObj ) )
	{
		if ( ( SIndEstaEnInicio ( p_indObj->p_indDimension1 ) == 1 ) &&
			 ( SIndEstaEnInicio ( p_indObj->p_indDimension2 ) == 1 ) )
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

int SInd2DEstaEnFinal1 ( SIndicador2D * p_indObj )
{
	int iRes;

	if ( ES_VALIDO ( p_indObj ) )
	{
		iRes = SIndEstaEnFinal ( p_indObj->p_indDimension1 );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SInd2DEstaEnInicio1 ( SIndicador2D * p_indObj )
{
	int iRes;

	if ( ES_VALIDO ( p_indObj ) )
	{
		iRes = SIndEstaEnInicio ( p_indObj->p_indDimension1 );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SInd2DEstaEnFinal2 ( SIndicador2D * p_indObj )
{
	int iRes;

	if ( ES_VALIDO ( p_indObj ) )
	{
		iRes = SIndEstaEnFinal ( p_indObj->p_indDimension2 );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SInd2DEstaEnInicio2 ( SIndicador2D * p_indObj )
{
	int iRes;

	if ( ES_VALIDO ( p_indObj ) )
	{
		iRes = SIndEstaEnInicio ( p_indObj->p_indDimension2 );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

