

#include "SGeneradorId.h"


#include "TiposBasicosConfig.h"








SGeneradorId * SGenIdCrear ( unsigned long ulIdInicial, unsigned long ulUltimoId, unsigned long ulIdFinal )
{
	SGeneradorId * p_genidObj;
	
	if ( ( ulIdInicial > 0 ) && ( ( ulIdFinal > ulIdInicial ) || ( ulIdFinal == 0 ) ) &&
		  ( ulUltimoId >= ulIdInicial - 1 ) && ( ( ulUltimoId <= ulIdFinal ) || ( ulIdFinal == 0 ) ) )
	{
		p_genidObj = (SGeneradorId *) MemReservar ( sizeof ( SGeneradorId ) );
		if ( ES_VALIDO ( p_genidObj ) )
		{
			p_genidObj->ulIdInicial = ulIdInicial;
			p_genidObj->ulIdFinal = ulIdFinal;
			p_genidObj->ulUltimoId = ulUltimoId; 
		}
	}
	else
	{
		p_genidObj = NULL;
	}
	return ( p_genidObj );
}

SGeneradorId * SGenIdCrearDef ()
{
	return ( SGenIdCrear ( 1, 0, 0 ) );
}

void SGenIdDestruir ( SGeneradorId ** p_p_genidObj )
{
	SGeneradorId * p_genidObj;
	
	if ( ES_VALIDO ( p_p_genidObj ) )
	{
		p_genidObj = *p_p_genidObj;

		if ( ES_VALIDO ( p_genidObj ) )
		{
			MemLiberar ( (void **) p_p_genidObj );
		}
	}
}

unsigned long SGenIdInicial ( SGeneradorId * p_genidObj )
{
	unsigned long ulRes;

	if ( ES_VALIDO ( p_genidObj ) )
	{
		ulRes = p_genidObj->ulIdInicial;
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

unsigned long SGenIdFinal ( SGeneradorId * p_genidObj )
{
	unsigned long ulRes;

	if ( ES_VALIDO ( p_genidObj ) )
	{
		ulRes = p_genidObj->ulIdFinal;
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

unsigned long SGenIdUltimo ( SGeneradorId * p_genidObj )
{
	unsigned long ulRes;

	if ( ES_VALIDO ( p_genidObj ) )
	{
		ulRes = p_genidObj->ulUltimoId;
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

unsigned long SGenIdSig ( SGeneradorId * p_genidObj )
{
	unsigned long ulRes;

	if ( SGenIdEsValido ( p_genidObj ) == 1 )
	{
		if ( p_genidObj->ulUltimoId == 0 )
		{
			ulRes = p_genidObj->ulIdInicial;
		}
		else
		{
			if ( p_genidObj->ulIdFinal > 0 )
			{
				if ( p_genidObj->ulUltimoId < p_genidObj->ulIdFinal )
				{
					ulRes = p_genidObj->ulUltimoId + 1;
				}
				else
				{
					ulRes = p_genidObj->ulIdInicial;
				}
			}
			else
			{
				if ( p_genidObj->ulUltimoId < ULONG_MAX )
				{
					ulRes = p_genidObj->ulUltimoId + 1;
				}
				else
				{
					ulRes = p_genidObj->ulIdInicial;
				}
			}
		}
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

unsigned long SGenIdAsignarSig ( SGeneradorId * p_genidObj )
{
	unsigned long ulRes;

	if ( SGenIdEsValido ( p_genidObj ) == 1 )
	{
		p_genidObj->ulUltimoId = SGenIdSig ( p_genidObj );
		ulRes = p_genidObj->ulUltimoId;
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

int SGenIdEsValido ( SGeneradorId * p_genidObj )
{
	int iRes;

	if ( ES_VALIDO ( p_genidObj ) )
	{
		if ( ( p_genidObj->ulIdInicial > 0 ) && 
			 ( ( p_genidObj->ulIdInicial < p_genidObj->ulIdFinal ) || ( p_genidObj->ulIdFinal == 0 ) ) &&
			 ( ( p_genidObj->ulUltimoId == 0 ) ||
			   ( ( p_genidObj->ulUltimoId >= p_genidObj->ulIdInicial ) && 
			     ( ( p_genidObj->ulUltimoId <= p_genidObj->ulIdFinal ) || ( p_genidObj->ulIdFinal == 0 ) ) ) ) )
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

int SGenIdIniciar ( SGeneradorId * p_genidObj )
{
	int iRes;

	if ( SGenIdEsValido ( p_genidObj ) == 1 )
	{
		p_genidObj->ulUltimoId = 0;
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SGenIdEsIgual ( SGeneradorId * p_genidObj, SGeneradorId * p_genidValor )
{
	int iRes;

	if ( ( SGenIdEsValido ( p_genidObj ) == 1 ) && ( SGenIdEsValido ( p_genidValor ) == 1 ) )
	{
		if ( ( p_genidObj->ulUltimoId == SGenIdUltimo ( p_genidValor ) ) &&
			( p_genidObj->ulIdInicial == SGenIdInicial ( p_genidValor ) ) &&
			( p_genidObj->ulIdFinal == SGenIdFinal ( p_genidValor ) ) )
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

SGeneradorId * SGenIdDuplicar ( SGeneradorId * p_genidObj )
{
	SGeneradorId * p_genidRes = NULL;
	if ( ES_VALIDO ( p_genidObj ) )
	{
		p_genidRes = SGenIdCrear ( p_genidObj->ulIdInicial, p_genidObj->ulUltimoId, p_genidObj->ulIdFinal );
	}
	return ( p_genidRes );
}
