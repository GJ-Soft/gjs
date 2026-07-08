
#include "SEntidadId.h"

#include "TiposDatosConfig.h"






SEntidadId * SEntIdCrear ( unsigned long ulId, const char * p_cNombre )
{
	SEntidadId *	p_entObj;
	
	if ( ulId > 0 ) 
	{
		p_entObj= (SEntidadId *) MemReservar ( sizeof ( SEntidadId ) );
		if ( ES_VALIDO ( p_entObj ) )
		{
			p_entObj->ulId = ulId;
			p_entObj->p_cadNombre = SCadGenerar ( p_cNombre );
		}
	}
	else
	{
		p_entObj = NULL;
	}
	return ( p_entObj );
}

SEntidadId * SEntIdEncapsular ( unsigned long ulId, SCadena * p_cadNombre )
{
	SEntidadId * p_entObj;

	if ( ulId > 0 )
	{
		p_entObj = ( SEntidadId * ) MemReservar ( sizeof ( SEntidadId ) );
		if ( ES_VALIDO ( p_entObj ) )
		{
			p_entObj->ulId = ulId;
			p_entObj->p_cadNombre = p_cadNombre;
		}
	}
	else
	{
		p_entObj = NULL;
	}
	return ( p_entObj );
}

void SEntIdDestruir ( SEntidadId ** p_p_entObj )
{
	SEntidadId * p_entObj;

	if ( ES_VALIDO ( p_p_entObj ) )
	{
		p_entObj = *p_p_entObj;

		if ( ES_VALIDO ( p_entObj ) )
		{
			SCadDestruir ( &( p_entObj->p_cadNombre ) );
			MemLiberar ( (void **) p_p_entObj );
		}
	}
}

int SEntIdEsValido ( SEntidadId * p_entObj )
{
	int iRes;

	if ( ES_VALIDO ( p_entObj ) )
	{
		if ( ( p_entObj->ulId > 0 ) && ( SCadEstaVacia ( p_entObj->p_cadNombre ) == 0 ) )
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

unsigned long SEntIdId ( SEntidadId * p_entObj )
{
	unsigned long ulRes;

	if ( ES_VALIDO ( p_entObj ) )
	{
		ulRes = p_entObj->ulId;
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}


int SEntIdEstablecerId ( SEntidadId * p_entObj, unsigned long ulId )
{
	int iRes;

	if ( ES_VALIDO ( p_entObj ) && ( ulId > 0 ) )
	{
		p_entObj->ulId = ulId;
		iRes = SEntIdEsValido ( p_entObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SCadena * SEntIdNombre ( SEntidadId * p_entObj )
{
	SCadena * p_cadRes;

	if ( ES_VALIDO ( p_entObj ) )
	{
		p_cadRes = p_entObj->p_cadNombre;
	}
	else
	{
		p_cadRes = NULL;
	}
	return ( p_cadRes );
}

int SEntIdEstablecerNombre ( SEntidadId * p_entObj, SCadena * p_cadNombre )
{
	int iRes;

	if ( ES_VALIDO ( p_entObj ) )
	{
		SCadDestruir ( &( p_entObj->p_cadNombre ) );
		if ( ES_VALIDO ( p_cadNombre ) )
		{
			p_entObj->p_cadNombre = p_cadNombre;
			iRes = SEntIdEsValido ( p_entObj );
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

int SEntIdEstablecerNombreLit ( SEntidadId * p_entObj, const char * p_cNombre )
{
	int iRes;

	if ( ES_VALIDO ( p_entObj ) )
	{
		SCadDestruir ( &( p_entObj->p_cadNombre ) );
		if ( ES_VALIDO ( p_cNombre ) )
		{
			p_entObj->p_cadNombre = SCadGenerar ( p_cNombre );
			iRes = SEntIdEsValido ( p_entObj );
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


