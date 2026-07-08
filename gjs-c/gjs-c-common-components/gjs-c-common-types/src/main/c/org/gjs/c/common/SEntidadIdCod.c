
#include "SEntidadIdCod.h"

#include "TiposDatosConfig.h"






SEntidadIdCod * SEntIdCodCrear ( unsigned long ulId, const char * p_cCodigo, const char * p_cNombre )
{
	SEntidadIdCod *	p_entObj;
	
	if ( ulId > 0 ) 
	{
		p_entObj= (SEntidadIdCod *) MemReservar ( sizeof ( SEntidadIdCod ) );
		if ( ES_VALIDO ( p_entObj ) )
		{
			p_entObj->ulId = ulId;
			p_entObj->p_cadCodigo = SCadGenerar ( p_cCodigo );
			p_entObj->p_cadNombre = SCadGenerar ( p_cNombre );
		}
	}
	else
	{
		p_entObj = NULL;
	}
	return ( p_entObj );
}

SEntidadIdCod * SEntIdCodEncapsular ( unsigned long ulId, SCadena * p_cadCodigo, SCadena * p_cadNombre )
{
	SEntidadIdCod * p_entObj;

	if ( ulId > 0 )
	{
		p_entObj = ( SEntidadIdCod * ) MemReservar ( sizeof ( SEntidadIdCod ) );
		if ( ES_VALIDO ( p_entObj ) )
		{
			p_entObj->ulId = ulId;
			p_entObj->p_cadCodigo = p_cadCodigo;
			p_entObj->p_cadNombre = p_cadNombre;
		}
	}
	else
	{
		p_entObj = NULL;
	}
	return ( p_entObj );
}

void SEntIdCodDestruir ( SEntidadIdCod ** p_p_entObj )
{
	SEntidadIdCod * p_entObj;

	if ( ES_VALIDO ( p_p_entObj ) )
	{
		p_entObj = *p_p_entObj;

		if ( ES_VALIDO ( p_entObj ) )
		{
			SCadDestruir ( &(p_entObj->p_cadCodigo) );
			SCadDestruir ( &(p_entObj->p_cadNombre) );
			MemLiberar ( (void **) p_p_entObj );
		}
	}
}

int SEntIdCodEsValido ( SEntidadIdCod * p_entObj )
{
	int iRes;

	if ( ES_VALIDO ( p_entObj ) )
	{
		if ( ( p_entObj->ulId > 0 ) && ( SCadEsToken ( p_entObj->p_cadCodigo ) == 1 ) && 
			 ( SCadEstaVacia ( p_entObj->p_cadNombre ) == 0 ) )
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

unsigned long SEntIdCodId ( SEntidadIdCod * p_entObj )
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

int SEntIdCodEstablecerId ( SEntidadIdCod * p_entObj, unsigned long ulId )
{
	int iRes;

	if ( ES_VALIDO ( p_entObj ) && ( ulId > 0 ) )
	{
		p_entObj->ulId = ulId;
		iRes = SEntIdCodEsValido ( p_entObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SCadena * SEntIdCodCodigo ( SEntidadIdCod * p_entObj )
{
	SCadena * p_cadRes;

	if ( ES_VALIDO ( p_entObj ) )
	{
		p_cadRes = p_entObj->p_cadCodigo;
	}
	else
	{
		p_cadRes = NULL;
	}
	return ( p_cadRes );
}

int SEntIdCodEstablecerCodigo ( SEntidadIdCod * p_entObj, SCadena * p_cadCodigo )
{
	int iRes;

	if ( ES_VALIDO ( p_entObj ) )
	{
		SCadDestruir ( &( p_entObj->p_cadCodigo ) );
		if ( ES_VALIDO ( p_cadCodigo ) )
		{
			p_entObj->p_cadCodigo = p_cadCodigo;
			iRes = SEntIdCodEsValido ( p_entObj );
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

int SEntIdCodEstablecerCodigoLit ( SEntidadIdCod * p_entObj, const char * p_cCodigo )
{
	int iRes;

	if ( ES_VALIDO ( p_entObj ) )
	{
		SCadDestruir ( &( p_entObj->p_cadCodigo ) );
		if ( ES_VALIDO ( p_cCodigo ) )
		{
			p_entObj->p_cadCodigo = SCadGenerar ( p_cCodigo );
			iRes = SEntIdCodEsValido ( p_entObj );
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

SCadena * SEntIdCodNombre ( SEntidadIdCod * p_entObj )
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

int SEntIdCodEstablecerNombre ( SEntidadIdCod * p_entObj, SCadena * p_cadNombre )
{
	int iRes;

	if ( ES_VALIDO ( p_entObj ) )
	{
		SCadDestruir ( &( p_entObj->p_cadNombre ) );
		if ( ES_VALIDO ( p_cadNombre ) )
		{
			p_entObj->p_cadNombre = p_cadNombre;
			iRes = SEntIdCodEsValido ( p_entObj );
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

int SEntIdCodEstablecerNombreLit ( SEntidadIdCod * p_entObj, const char * p_cNombre )
{
	int iRes;

	if ( ES_VALIDO ( p_entObj ) )
	{
		SCadDestruir ( &( p_entObj->p_cadNombre ) );
		if ( ES_VALIDO ( p_cNombre ) )
		{
			p_entObj->p_cadNombre = SCadGenerar ( p_cNombre );
			iRes = SEntIdCodEsValido ( p_entObj );
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


