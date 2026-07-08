#include "SReferencia.h"

#include "TiposBasicosConfig.h"


SReferencia * SRefCrear ( const char * p_cAlias, void * p_vDatos )
{
	SReferencia * p_refObj;
	
	p_refObj = (SReferencia *) MemReservar ( sizeof ( SReferencia ) );
	if ( ES_VALIDO ( p_refObj ) )
	{
		p_refObj->p_cAlias = NULL;
		p_refObj->p_vDatos = NULL;
		if ( SRefEstablecerAlias ( p_refObj,  p_cAlias ) == 1 )
		{
			p_refObj->p_vDatos = p_vDatos;
		}
		else
		{
			SRefDestruir ( &p_refObj );
		}
	}
	return ( p_refObj );
}

void SRefDestruir ( SReferencia ** p_p_refObj )
{
	SReferencia * p_refObj;
	
	if ( ES_VALIDO ( p_p_refObj ) )
	{
		p_refObj = *p_p_refObj;

		if ( ES_VALIDO ( p_refObj ) )
		{
			MemLiberar ( (void **) &(p_refObj->p_cAlias) );
			MemLiberar ( (void **) p_p_refObj );
		}
	}
}

int SRefEsValida ( SReferencia * p_refObj )
{
	int iRes;

	if ( ES_VALIDO ( p_refObj ) )
	{
		if ( ( CadEsAlfanumericoValido ( p_refObj->p_cAlias ) == 1 ) &&
			 ES_VALIDO ( p_refObj->p_vDatos ) )
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

const char * SRefObtenerAlias ( SReferencia * p_refObj )
{
	const char * p_cRes;

	if ( ES_VALIDO ( p_refObj ) )
	{
		p_cRes = p_refObj->p_cAlias;
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

void * SRefObtenerDatos ( SReferencia * p_refObj )
{
	void * p_vRes;

	if ( ES_VALIDO ( p_refObj ) )
	{
		p_vRes = p_refObj->p_vDatos;
	}
	else
	{
		p_vRes = NULL;
	}
	return ( p_vRes );
}

int SRefEstablecer ( SReferencia * p_refObj, const char * p_cAlias,void * p_vDatos )
{
	int	iRes;

	if ( SRefEstablecerAlias ( p_refObj, p_cAlias ) == 1 )
	{
		iRes = SRefEstablecerDatos ( p_refObj, p_vDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SRefEstablecerAlias ( SReferencia * p_refObj, const char * p_cAlias )
{
	int iRes;

	if ( ES_VALIDO ( p_refObj )  )
	{
		if ( CadEsAlfanumericoValido ( p_cAlias ) == 1 )
		{
			MemLiberar ( ( void ** ) &( p_refObj->p_cAlias ) );
			p_refObj->p_cAlias = CadDuplicar( p_cAlias );
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

int SRefEstablecerDatos ( SReferencia * p_refObj, void * p_vDatos )
{
	int iRes;

	if ( ES_VALIDO ( p_refObj ) )
	{
		p_refObj->p_vDatos = p_vDatos;
		iRes = SRefEsValida ( p_refObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SReferencia * SRefDuplicar (  SReferencia * p_refObj )
{
	SReferencia *		p_refRes;

	if ( SRefEsValida ( p_refObj ) == 1 ) 
	{
		p_refRes = SRefCrear ( p_refObj->p_cAlias, p_refObj->p_vDatos );
	}
	else
	{
		p_refRes = NULL;
	}
	return ( p_refRes );
}

int SRefEsIgual ( SReferencia * p_refObj1, SReferencia * p_refObj2 )
{
	int iRes;

	if ( ( SRefEsValida ( p_refObj1 ) == 1 ) && ( SRefEsValida ( p_refObj2 ) == 1 ) )
	{
		if ( CadComparar ( p_refObj1->p_cAlias, p_refObj2->p_cAlias ) == COMP_IGUAL )
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

int SRefEsMenor ( SReferencia * p_refObj1, SReferencia * p_refObj2 )
{
	int iRes;

	if ( ( SRefEsValida ( p_refObj1 ) == 1 ) && ( SRefEsValida ( p_refObj2 ) == 1 ) )
	{
		if ( CadComparar ( p_refObj1->p_cAlias, p_refObj2->p_cAlias ) == COMP_MENOR )
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

int SRefEsMayor ( SReferencia * p_refObj1, SReferencia * p_refObj2 )
{
	int iRes;

	if ( ( SRefEsValida ( p_refObj1 ) == 1 ) && ( SRefEsValida ( p_refObj2 ) == 1 ) )
	{
		if ( CadComparar ( p_refObj1->p_cAlias, p_refObj2->p_cAlias ) == COMP_MAYOR )
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



int SRefEsIgualLit ( SReferencia * p_refObj, const char * p_cAlias )
{
	int iRes;

	if ( ( SRefEsValida ( p_refObj ) == 1 ) && ( CadEsAlfanumericoValido ( p_cAlias ) == 1 ) )
	{
		if ( CadComparar ( p_refObj->p_cAlias, p_cAlias ) == COMP_IGUAL )
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

int SRefEsMenorLit ( SReferencia * p_refObj, const char * p_cAlias )
{
	int iRes;

	if ( ( SRefEsValida ( p_refObj ) == 1 ) && ( CadEsAlfanumericoValido ( p_cAlias ) == 1 ) )
	{
		if ( CadComparar ( p_refObj->p_cAlias, p_cAlias ) == COMP_MENOR )
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

int SRefEsMayorLit ( SReferencia * p_refObj, const char * p_cAlias )
{
	int iRes;

	if ( ( SRefEsValida ( p_refObj ) == 1 ) && ( CadEsAlfanumericoValido ( p_cAlias ) == 1 ) )
	{
		if ( CadComparar ( p_refObj->p_cAlias, p_cAlias ) == COMP_MAYOR )
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

unsigned int SRefHash ( SReferencia * p_refObj )
{
	unsigned int uiRes = 0;

	if ( ES_VALIDO ( p_refObj ) )
	{
		uiRes = HashCadena ( p_refObj->p_cAlias );
	}
	return ( uiRes );
}


