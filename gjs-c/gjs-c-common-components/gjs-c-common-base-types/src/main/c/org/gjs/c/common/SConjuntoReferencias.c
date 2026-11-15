#include "SConjuntoReferencias.h"

#include "TiposBasicosConfig.h"


static int _SCnjRefComparar ( void * p_vVal1, void * p_vVal2 );



/* Conjunto de referencias ordenado por alias, sin alias repetidos. El conjunto
   no libera nada por su cuenta: es el que destruye sus referencias. */
SConjuntoReferencias * SCnjRefCrear ()
{
	SConjuntoReferencias * p_cnjObj;

	p_cnjObj = (SConjuntoReferencias *) MemReservar ( sizeof ( SConjuntoReferencias ) );
	if ( ES_VALIDO ( p_cnjObj ) )
	{
		p_cnjObj->p_cnjDatos = SCnjpCrear ( _SCnjRefComparar );
		if ( ES_VALIDO ( p_cnjObj->p_cnjDatos ) )
		{
			SCnjpDesactivarLiberacionMemoria ( p_cnjObj->p_cnjDatos );
		}
		else
		{
			MemLiberar ( (void **) &p_cnjObj );
		}
	}
	return ( p_cnjObj );
}

void SCnjRefDestruir ( SConjuntoReferencias ** p_p_cnjObj )
{
	SConjuntoReferencias * p_cnjObj;

	if ( ES_VALIDO ( p_p_cnjObj ) )
	{
		p_cnjObj = *p_p_cnjObj;

		if ( ES_VALIDO ( p_cnjObj ) )
		{
			SCnjRefVaciar ( p_cnjObj );
			SCnjpDestruir ( &(p_cnjObj->p_cnjDatos) );
			MemLiberar ( (void **) p_p_cnjObj );
		}
	}
}

int SCnjRefEsValido ( SConjuntoReferencias * p_cnjObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		iRes = SCnjpEsValido ( p_cnjObj->p_cnjDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCnjRefEstaVacio ( SConjuntoReferencias * p_cnjObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		iRes = SCnjpEstaVacio ( p_cnjObj->p_cnjDatos );
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

int SCnjRefNumElementos ( SConjuntoReferencias * p_cnjObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		iRes = SCnjpNumElementos ( p_cnjObj->p_cnjDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

/* Existe y Buscar localizan por alias con la busqueda del conjunto, usando
   como sonda una referencia en la pila: no reservan nada. La sonda lleva un
   dato cualquiera no nulo porque SRefComparar solo compara referencias
   validas. Buscar devuelve la referencia, que sigue siendo del conjunto, o
   NULL. */
int SCnjRefExiste ( SConjuntoReferencias * p_cnjObj, const char * p_cAlias )
{
	int			iRes;
	SReferencia	refSonda;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		if ( ES_VALIDO ( p_cAlias ) )
		{
			refSonda.p_cAlias = (char *) p_cAlias;
			refSonda.p_vDatos = (void *) p_cAlias;
			iRes = SCnjpExiste ( p_cnjObj->p_cnjDatos, (byte *) &refSonda );
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

SReferencia * SCnjRefBuscar ( SConjuntoReferencias * p_cnjObj, const char * p_cAlias )
{
	SReferencia *	p_refRes;
	SReferencia		refSonda;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		if ( ES_VALIDO ( p_cAlias ) )
		{
			refSonda.p_cAlias = (char *) p_cAlias;
			refSonda.p_vDatos = (void *) p_cAlias;
			p_refRes = SCnjRefElemento ( p_cnjObj, SCnjpBuscar ( p_cnjObj->p_cnjDatos, (byte *) &refSonda ) );
		}
		else
		{
			p_refRes = NULL;
		}
	}
	else
	{
		p_refRes = NULL;
	}
	return ( p_refRes );
}

/* Por posicion, en el orden de los alias. */
SReferencia * SCnjRefElemento ( SConjuntoReferencias * p_cnjObj, int iElem )
{
	SReferencia *	p_refRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		p_refRes = (SReferencia *) SCnjpElemento ( p_cnjObj->p_cnjDatos, iElem );
	}
	else
	{
		p_refRes = NULL;
	}
	return ( p_refRes );
}

const char * SCnjRefAliasElemento ( SConjuntoReferencias * p_cnjObj, int iElem )
{
	const char *	p_cRes;
	SReferencia *	p_refObj;

	p_refObj = SCnjRefElemento ( p_cnjObj, iElem );
	if ( ES_VALIDO ( p_refObj ) )
	{
		p_cRes = SRefObtenerAlias ( p_refObj );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

void * SCnjRefDatosElemento ( SConjuntoReferencias * p_cnjObj, int iElem )
{
	void *			p_vRes;
	SReferencia *	p_refObj;

	p_refObj = SCnjRefElemento ( p_cnjObj, iElem );
	if ( ES_VALIDO ( p_refObj ) )
	{
		p_vRes = SRefObtenerDatos ( p_refObj );
	}
	else
	{
		p_vRes = NULL;
	}
	return ( p_vRes );
}

/* La referencia pasa a ser del conjunto. Si no es valida o ya hay una con el
   mismo alias, 0 y sigue siendo del llamante. InsertarExt la crea y, si no
   entra, la destruye. */
int SCnjRefInsertar ( SConjuntoReferencias * p_cnjObj, SReferencia * p_refDatos )
{
	int iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		if ( SRefEsValida ( p_refDatos ) == 1 )
		{
			iRes = SCnjpInsertarElem ( p_cnjObj->p_cnjDatos, (byte *) p_refDatos );
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

int SCnjRefInsertarExt ( SConjuntoReferencias * p_cnjObj, const char * p_cAlias, void * p_vDato )
{
	int				iRes;
	SReferencia *	p_refObj;

	p_refObj = SRefCrear ( p_cAlias, p_vDato );
	iRes = SCnjRefInsertar ( p_cnjObj, p_refObj );
	if ( iRes != 1 )
	{
		SRefDestruir ( &p_refObj );
	}
	return ( iRes );
}

/* Eliminar y EliminarElem destruyen la referencia; 0 si no esta. */
int SCnjRefEliminar ( SConjuntoReferencias * p_cnjObj, const char * p_cAlias )
{
	int			iRes;
	SReferencia	refSonda;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		if ( ES_VALIDO ( p_cAlias ) )
		{
			refSonda.p_cAlias = (char *) p_cAlias;
			refSonda.p_vDatos = (void *) p_cAlias;
			iRes = SCnjRefEliminarElem ( p_cnjObj, SCnjpBuscar ( p_cnjObj->p_cnjDatos, (byte *) &refSonda ) );
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

int SCnjRefEliminarElem ( SConjuntoReferencias * p_cnjObj, int iElem )
{
	int				iRes;
	SReferencia *	p_refObj;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		p_refObj = (SReferencia *) SCnjpExtraerElem ( p_cnjObj->p_cnjDatos, iElem );
		if ( ES_VALIDO ( p_refObj ) )
		{
			SRefDestruir ( &p_refObj );
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

int SCnjRefVaciar ( SConjuntoReferencias * p_cnjObj )
{
	int				iRes;
	SReferencia *	p_refObj;
	SElementoPtr *	p_elpObj;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		/* Por la CADENA, no por indice: el indice entra por el extremo mas
		   cercano, asi que un recorrido completo sale cuadratico. Aqui solo se
		   suelta el dato; los nodos los quita SCnjpVaciar. */
		p_elpObj = SCnjpElementoPtr ( p_cnjObj->p_cnjDatos, 0 );
		while ( ES_VALIDO ( p_elpObj ) )
		{
			p_refObj = (SReferencia *) SElpDatos ( p_elpObj );
			SRefDestruir ( &p_refObj );
			p_elpObj = SElpSucesor ( p_elpObj );
		}
		iRes = SCnjpVaciar ( p_cnjObj->p_cnjDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


/* Comparador del conjunto: el orden de los alias, en el -1 / 0 / 1 que espera
   la lista ordenada. */
static int _SCnjRefComparar ( void * p_vVal1, void * p_vVal2 )
{
	int iRes;

	iRes = SRefComparar ( (SReferencia *) p_vVal1, (SReferencia *) p_vVal2 );
	if ( iRes == COMP_MENOR )
	{
		iRes = -1;
	}
	else if ( iRes == COMP_MAYOR )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}
