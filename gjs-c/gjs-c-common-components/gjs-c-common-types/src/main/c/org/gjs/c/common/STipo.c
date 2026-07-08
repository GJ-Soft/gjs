
#include "STipo.h"

#include "TiposDatosConfig.h"








STipo * STipCrearDef () 
{
	STipo * p_tipObj;
	
	p_tipObj = (STipo *) MemReservar ( sizeof ( STipo ) );
	if ( ES_VALIDO ( p_tipObj ) )
	{
		p_tipObj->iCodigo = TIP_NINGUNO;
	}
	return ( p_tipObj );
}

STipo * STipCrear ( int iCodigo ) 
{
	STipo * p_tipObj;
	
	p_tipObj = (STipo *) MemReservar ( sizeof ( STipo ) );
	if ( ES_VALIDO ( p_tipObj ) )
	{
		p_tipObj->iCodigo = iCodigo;
	}
	return ( p_tipObj );
}

STipo * STipCrearLit ( const char * p_cTipo )
{
	return ( STipCrear ( TipCodigo ( p_cTipo ) ) );
}

void STipDestruir ( STipo ** p_p_tipObj ) 
{
	if ( ES_VALIDO ( p_p_tipObj ) )
	{
		MemLiberar ( (void **) p_p_tipObj );
	}
}

int STipCodigo ( STipo * p_tipObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_tipObj ) )
	{
		iRes = p_tipObj->iCodigo;
	}
	else
	{
		iRes = TIP_NINGUNO;
	}
	return ( iRes );
}

void STipEstablecerCodigo ( STipo * p_tipObj, int iCodigo )
{
	if ( ES_VALIDO ( p_tipObj ) )
	{
		p_tipObj->iCodigo = iCodigo;
	}
}

const char * STipLiteral ( STipo * p_tipObj )
{
	const char * p_cRes;
	
	if ( ES_VALIDO ( p_tipObj ) )
	{
		p_cRes = TipLiteral ( p_tipObj->iCodigo );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int STipEsValido ( STipo * p_tipObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_tipObj ) )
	{
		iRes = TipEsValido ( p_tipObj->iCodigo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int STipEsEstrictamenteValido ( STipo * p_tipObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_tipObj ) )
	{
		iRes = TipEsEstrictamenteValido ( p_tipObj->iCodigo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int STipEsNinguno ( STipo * p_tipObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_tipObj ) )
	{
		iRes = TipEsNinguno ( p_tipObj->iCodigo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int STipEsDesconocido ( STipo * p_tipObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_tipObj ) )
	{
		iRes = TipEsDesconocido ( p_tipObj->iCodigo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int STipEsNumero ( STipo * p_tipObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_tipObj ) )
	{
		iRes = TipEsNumero ( p_tipObj->iCodigo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int STipEsCadena ( STipo * p_tipObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_tipObj ) )
	{
		iRes = TipEsCadena ( p_tipObj->iCodigo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int STipEsBooleano ( STipo * p_tipObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_tipObj ) )
	{
		iRes = TipEsBooleano ( p_tipObj->iCodigo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int STipEsFecha ( STipo * p_tipObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_tipObj ) )
	{
		iRes = TipEsFecha ( p_tipObj->iCodigo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int STipEsBinario ( STipo * p_tipObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_tipObj ) )
	{
		iRes = TipEsBinario ( p_tipObj->iCodigo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int STipEsObjeto ( STipo * p_tipObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_tipObj ) )
	{
		iRes = TipEsObjeto ( p_tipObj->iCodigo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int STipEsNatural ( STipo * p_tipObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_tipObj ) )
	{
		iRes = TipEsNatural ( p_tipObj->iCodigo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}
int STipEsEntero ( STipo * p_tipObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_tipObj ) )
	{
		iRes = TipEsEntero ( p_tipObj->iCodigo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}
int STipEsReal ( STipo * p_tipObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_tipObj ) )
	{
		iRes = TipEsReal ( p_tipObj->iCodigo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}
int STipEsHexadecimal ( STipo * p_tipObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_tipObj ) )
	{
		iRes = TipEsHexadecimal ( p_tipObj->iCodigo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int STipEsDeTamVariable ( STipo * p_tipObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_tipObj ) )
	{
		iRes = TipEsDeTamVariable ( p_tipObj->iCodigo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int STipTam ( STipo * p_tipObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_tipObj ) )
	{
		iRes = TipTam ( p_tipObj->iCodigo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}
