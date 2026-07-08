
#include "SUbicacion.h"

#include "TiposDatosConfig.h"









SUbicacion * SUbcCrearDef () 
{
	SUbicacion * p_ubcObj;
	
	p_ubcObj = (SUbicacion *) MemReservar ( sizeof ( SUbicacion ) );
	if ( ES_VALIDO ( p_ubcObj ) )
	{
		SUbcEstablecer ( p_ubcObj, -1, 0 );
	}
	return ( p_ubcObj );
}

SUbicacion * SUbcCrear ( long lPos, long lTam ) 
{
	SUbicacion * p_ubcObj;
	
	p_ubcObj = (SUbicacion *) MemReservar ( sizeof ( SUbicacion ) );
	if ( ES_VALIDO ( p_ubcObj ) )
	{
		SUbcEstablecer ( p_ubcObj, lPos, lTam );
	}
	return ( p_ubcObj );
}

void SUbcDestruir ( SUbicacion ** p_p_ubcObj )
{
	if ( ES_VALIDO ( p_p_ubcObj ) )
	{
		MemLiberar ( (void **) p_p_ubcObj );
	}
}

long SUbcPos ( SUbicacion * p_ubcObj )
{
	long lRes;
	
	if ( ES_VALIDO ( p_ubcObj ) )
	{
		lRes = p_ubcObj->lPos;
	}
	else
	{
		lRes = -1;
	}
	return ( lRes );
}

long SUbcTam ( SUbicacion * p_ubcObj )
{
	long lRes;
	
	if ( ES_VALIDO ( p_ubcObj ) )
	{
		lRes = p_ubcObj->lTam;
	}
	else
	{
		lRes = 0;
	}
	return ( lRes );
}

void SUbcEstablecer ( SUbicacion * p_ubcObj, long lPos, long lTam )
{
	if ( ES_VALIDO ( p_ubcObj ) )
	{
		p_ubcObj->lPos = lPos;
		p_ubcObj->lTam = lTam;
	}
}

void SUbcEstablecerPos ( SUbicacion * p_ubcObj, long lPos )
{
	if ( ES_VALIDO ( p_ubcObj ) )
	{
		p_ubcObj->lPos = lPos;
	}
}

void SUbcEstablecerTam ( SUbicacion * p_ubcObj, long lTam )
{
	if ( ES_VALIDO ( p_ubcObj ) )
	{
		p_ubcObj->lTam = lTam;
	}
}

int SUbcDesplazar ( SUbicacion * p_ubcObj, long lDesp )
{
	int iRes;

	if ( ES_VALIDO ( p_ubcObj ) )
	{
		if ( lDesp + p_ubcObj->lPos >= 0 )
		{
			p_ubcObj->lPos = p_ubcObj->lPos + lDesp;
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

int SUbcEsValida ( SUbicacion * p_ubcObj )
{
	int iRes;

	if ( ES_VALIDO ( p_ubcObj ) )
	{
		if ( ( p_ubcObj->lPos >= 0 ) && ( p_ubcObj->lTam > 0 ) )
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



