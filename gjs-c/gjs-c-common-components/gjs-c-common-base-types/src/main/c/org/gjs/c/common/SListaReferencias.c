#include "SListaReferencias.h"

#include "TiposBasicosConfig.h"




SListaReferencias * SLisRefCrear ()
{
	SListaReferencias * p_lisObj;
	
	p_lisObj = (SListaReferencias *) MemReservar ( sizeof ( SListaReferencias ) );
	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_lisObj->p_lisDatos = SLispCrear ();
		SLispDesactivarLiberacionMemoria ( p_lisObj->p_lisDatos );
	}
	return ( p_lisObj );
}

void SLisRefDestruir ( SListaReferencias ** p_p_lisObj )
{
	SListaReferencias * p_lisObj;
	
	if ( ES_VALIDO ( p_p_lisObj ) )
	{
		p_lisObj = *p_p_lisObj;

		if ( ES_VALIDO ( p_lisObj ) )
		{
			SLisRefVaciar ( p_lisObj );
			SLispDestruir ( &(p_lisObj->p_lisDatos) );
			MemLiberar ( (void **) p_p_lisObj );
		}
	}
}

int SLisRefEsValida ( SListaReferencias * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLispEsValida ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisRefEstaVacia ( SListaReferencias * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLispEstaVacia ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

int SLisRefNumElementos ( SListaReferencias * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLispNumElementos ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SReferencia * SLisRefElemento ( SListaReferencias * p_lisObj, int iElem )
{
	SReferencia *	p_refRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_refRes = (SReferencia *) SLispElemento ( p_lisObj->p_lisDatos, iElem );
	}
	else
	{
		p_refRes = NULL;
	}
	return ( p_refRes );
}

const char * SLisRefAliasElemento ( SListaReferencias * p_lisObj, int iElem )
{
	const char * 	p_cRes;
	SReferencia *	p_refObj;
	
	p_refObj = SLisRefElemento ( p_lisObj, iElem );
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

void * SLisRefDatosElemento ( SListaReferencias * p_lisObj, int iElem )
{
	void * 			p_vRes;
	SReferencia *	p_refObj;
	
	p_refObj = SLisRefElemento ( p_lisObj, iElem );
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

int SLisRefInsertar ( SListaReferencias * p_lisObj, SReferencia * p_refDatos )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		SLispInicio ( p_lisObj->p_lisDatos );
		while ( SRefEsMenor ( ( SReferencia * ) SLispActual ( p_lisObj->p_lisDatos ), p_refDatos ) &&
			( SLispEstaEnFinal ( p_lisObj->p_lisDatos ) == 0 ) )
		{
			SLispSiguiente ( p_lisObj->p_lisDatos );
		}
		if ( SRefEsMenor ( ( SReferencia * ) SLispActual ( p_lisObj->p_lisDatos ), p_refDatos ) == 1 )
		{
			iRes = SLispInsertar ( p_lisObj->p_lisDatos, ( byte * ) p_refDatos );
		}
		else
		{
			iRes = SLispInsertarDelante ( p_lisObj->p_lisDatos, ( byte * ) p_refDatos );
		}
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SLisRefInsertarExt ( SListaReferencias * p_lisObj, const char * p_cAlias, void * p_vDato )
{
	int iRes;

	SReferencia * p_refObj = SRefCrear ( p_cAlias, p_vDato );
	if ( ES_VALIDO ( p_refObj ) )
	{
		iRes = SLisRefInsertar ( p_lisObj, p_refObj );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SLisRefVaciar ( SListaReferencias * p_lisObj )
{
	int 			iRes;
	SReferencia * 	p_refObj;
	SElementoPtr *	p_elpObj;
	SElementoPtr *	p_elpSig;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		/* Por la CADENA, no por indice: el indice entra por el extremo mas
		   cercano, asi que un recorrido completo sale cuadratico. */
		p_elpObj = SLispElementoPtr ( p_lisObj->p_lisDatos, 0 );
		while ( ES_VALIDO ( p_elpObj ) )
		{
			/* El sucesor, ANTES de destruir: aqui solo se suelta el dato, no el
			   nodo, pero cogerlo antes deja la funcion a salvo de que eso
			   cambie. */
			p_elpSig = SElpSucesor ( p_elpObj );
			p_refObj = (SReferencia *) SElpDatos ( p_elpObj );
			SRefDestruir ( &p_refObj );
			p_elpObj = p_elpSig;
		}
		iRes = SLispVaciar ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SLisRefEliminar ( SListaReferencias * p_lisObj, const char * p_cAlias )
{
	int				iEnc;
	int				iElem;
	int				iRes;
	SReferencia *	p_refRes;
	SElementoPtr *	p_elpObj;

	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_cAlias ) )
	{
		iEnc = 0;
		iElem = 0;
		iRes = 0;
		/* Por la CADENA, no por indice: el indice entra por el extremo mas
		   cercano, asi que un recorrido completo sale cuadratico. */
		p_elpObj = SLispElementoPtr ( p_lisObj->p_lisDatos, 0 );
		while ( ES_VALIDO ( p_elpObj ) && ( iEnc == 0 ) )
		{
			p_refRes = (SReferencia *) SElpDatos ( p_elpObj );
			if ( CadComparar ( SRefObtenerAlias ( p_refRes ), p_cAlias ) == COMP_IGUAL )
			{
				iEnc = 1;
				/* Se sigue eliminando por indice, que es lo que sabe hacer
				   EliminarElem; por eso se lleva la cuenta. Y NO se avanza
				   despues: al eliminar, p_elpObj queda colgando. */
				iRes = SLisRefEliminarElem ( p_lisObj, iElem );
			}
			else
			{
				iElem = iElem + 1;
				p_elpObj = SElpSucesor ( p_elpObj );
			}
		}
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SLisRefEliminarElem ( SListaReferencias * p_lisObj, int iElem )
{
	int 			iRes;
	SReferencia * 	p_refObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_refObj = SLisRefElemento ( p_lisObj, iElem );
		SRefDestruir ( &p_refObj );
		iRes = SLispEliminarElem ( p_lisObj->p_lisDatos, iElem );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SLisRefExiste ( SListaReferencias * p_lisObj, const char * p_cAlias )
{
	int				iRes;
	SElementoPtr *	p_elpObj;

	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_cAlias )  )
	{
		iRes = 0;
		/* Por la CADENA, no por indice: el indice entra por el extremo mas
		   cercano, asi que un recorrido completo sale cuadratico. */
		p_elpObj = SLispElementoPtr ( p_lisObj->p_lisDatos, 0 );
		while ( ES_VALIDO ( p_elpObj ) && ( iRes == 0 ) )
		{
			if ( CadComparar ( SRefObtenerAlias ( (SReferencia *) SElpDatos ( p_elpObj ) ), p_cAlias ) == COMP_IGUAL )
			{
				iRes = 1;
			}
			p_elpObj = SElpSucesor ( p_elpObj );
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SReferencia * SLisRefBuscar ( SListaReferencias * p_lisObj, const char * p_cAlias )
{
	SReferencia *	p_refRes;
	SReferencia *	p_refAct;
	SElementoPtr *	p_elpObj;

	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_cAlias )  )
	{
		p_refRes = NULL;
		/* Por la CADENA, no por indice: el indice entra por el extremo mas
		   cercano, asi que un recorrido completo sale cuadratico. */
		p_elpObj = SLispElementoPtr ( p_lisObj->p_lisDatos, 0 );
		while ( ES_VALIDO ( p_elpObj ) && ( p_refRes == NULL ) )
		{
			/* Una sola lectura: antes se pedia el elemento dos veces, una para
			   comparar y otra para devolverlo. */
			p_refAct = (SReferencia *) SElpDatos ( p_elpObj );
			if ( CadComparar ( SRefObtenerAlias ( p_refAct ), p_cAlias ) == COMP_IGUAL )
			{
				p_refRes = p_refAct;
			}
			p_elpObj = SElpSucesor ( p_elpObj );
		}
	}
	else
	{
		p_refRes = NULL;
	}
	return ( p_refRes );
}

int	SLisRefLiberacionMemoriaActivada ( SListaReferencias * p_lisObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		iRes = SLispLiberacionMemoriaActivada ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

void SLisRefActivarLiberacionMemoria ( SListaReferencias * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLispActivarLiberacionMemoria ( p_lisObj->p_lisDatos );
	}
}

void SLisRefDesactivarLiberacionMemoria ( SListaReferencias * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLispDesactivarLiberacionMemoria ( p_lisObj->p_lisDatos );
	}
}



