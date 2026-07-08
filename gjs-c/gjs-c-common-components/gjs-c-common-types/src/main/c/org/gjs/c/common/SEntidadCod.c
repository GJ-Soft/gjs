
#include "SEntidadCod.h"

#include "TiposDatosConfig.h"




SEntidadCod * SEntCodCrear ( const char * p_cCodigo, const char * p_cNombre )
{
	SEntidadCod *	p_entObj;
	
	p_entObj= (SEntidadCod *) MemReservar ( sizeof ( SEntidadCod ) );
	if ( ES_VALIDO ( p_entObj ) )
	{
		p_entObj->p_cadCodigo = SCadGenerar ( p_cCodigo );
		p_entObj->p_cadNombre = SCadGenerar ( p_cNombre );
	}
	return ( p_entObj );
}

SEntidadCod * SEntCodEncapsular ( SCadena * p_cadCodigo, SCadena * p_cadNombre )
{
	SEntidadCod * p_entObj;

	p_entObj = ( SEntidadCod * ) MemReservar ( sizeof ( SEntidadCod ) );
	if ( ES_VALIDO ( p_entObj ) )
	{
		p_entObj->p_cadCodigo = p_cadCodigo;
		p_entObj->p_cadNombre = p_cadNombre;
	}
	return ( p_entObj );
}

void SEntCodDestruir ( SEntidadCod ** p_p_entObj )
{
	SEntidadCod * p_entObj;

	if ( ES_VALIDO ( p_p_entObj ) )
	{
		p_entObj = *p_p_entObj;

		if ( ES_VALIDO ( p_entObj ) )
		{
			SCadDestruir ( &( p_entObj->p_cadCodigo ) );
			SCadDestruir ( &( p_entObj->p_cadNombre ) );
			MemLiberar ( (void **) p_p_entObj );
		}
	}
}

int SEntCodEsValido ( SEntidadCod * p_entObj )
{
	int iRes;

	if ( ES_VALIDO ( p_entObj ) )
	{
		if ( ( SCadEsToken ( p_entObj->p_cadCodigo ) == 1 ) && 
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

SCadena * SEntCodCodigo ( SEntidadCod * p_entObj )
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

int SEntCodEstablecerCodigo ( SEntidadCod * p_entObj, SCadena * p_cadCodigo )
{
	int iRes;

	if ( ES_VALIDO ( p_entObj ) )
	{
		SCadDestruir ( &( p_entObj->p_cadCodigo ) );
		if ( ES_VALIDO ( p_cadCodigo ) )
		{
			p_entObj->p_cadCodigo = p_cadCodigo;
			iRes = SEntCodEsValido ( p_entObj );
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

int SEntCodEstablecerCodigoLit ( SEntidadCod * p_entObj, const char * p_cCodigo )
{
	int iRes;

	if ( ES_VALIDO ( p_entObj ) )
	{
		SCadDestruir ( &( p_entObj->p_cadCodigo ) );
		if ( ES_VALIDO ( p_cCodigo ) )
		{
			p_entObj->p_cadCodigo = SCadGenerar ( p_cCodigo );
			iRes = SEntCodEsValido ( p_entObj );
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

SCadena * SEntCodNombre ( SEntidadCod * p_entObj )
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

int SEntCodEstablecerNombre ( SEntidadCod * p_entObj, SCadena * p_cadNombre )
{
	int iRes;

	if ( ES_VALIDO ( p_entObj ) )
	{
		SCadDestruir ( &( p_entObj->p_cadNombre ) );
		if ( ES_VALIDO ( p_cadNombre ) )
		{
			p_entObj->p_cadNombre = p_cadNombre;
			iRes = SEntCodEsValido ( p_entObj );
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

int SEntCodEstablecerNombreLit ( SEntidadCod * p_entObj, const char * p_cNombre )
{
	int iRes;

	if ( ES_VALIDO ( p_entObj ) )
	{
		SCadDestruir ( &( p_entObj->p_cadNombre ) );
		if ( ES_VALIDO ( p_cNombre ) )
		{
			p_entObj->p_cadNombre = SCadGenerar ( p_cNombre );
			iRes = SEntCodEsValido ( p_entObj );
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


