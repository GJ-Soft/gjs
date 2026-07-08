#include "SListaOrdenadaPtr.h"


#include "TiposBasicosConfig.h"



int SLispOrdBuscarSitio ( SListaOrdenadaPtr * p_lisObj, byte * p_byDatos );



SListaOrdenadaPtr * SLispOrdCrear ( PFUNINTPVPV fComparar )
{
	SListaOrdenadaPtr * p_lisObj;
	
	p_lisObj = (SListaOrdenadaPtr *) MemReservar ( sizeof ( SListaOrdenadaPtr ) );
	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_lisObj->p_lispContenido = SLispCrear ();
		p_lisObj->p_cmpObj = SCmpCrear ( fComparar );
		if ( ES_NULO ( p_lisObj->p_lispContenido ) || ES_NULO ( p_lisObj->p_cmpObj ) )
		{
			SLispOrdDestruir ( &p_lisObj );
		}
	}
	return ( p_lisObj );
}

void SLispOrdDestruir ( SListaOrdenadaPtr ** p_p_lisObj )
{
	SListaOrdenadaPtr * p_lisObj;
	
	if ( ES_VALIDO ( p_p_lisObj ) )
	{
		p_lisObj = *p_p_lisObj;

		if ( ES_VALIDO ( p_lisObj ) )
		{
			SLispDestruir ( &(p_lisObj->p_lispContenido) );
			SCmpDestruir ( &(p_lisObj->p_cmpObj) );
			MemLiberar ( (void **) p_p_lisObj );
		}
	}
}

int SLispOrdEsValida ( SListaOrdenadaPtr * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( ( SLispEsValida ( p_lisObj->p_lispContenido ) == 1 ) &&
			  (	SCmpEsValido ( p_lisObj->p_cmpObj ) == 1 ) )
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

int SLispOrdNumElementos ( SListaOrdenadaPtr * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLispNumElementos ( p_lisObj->p_lispContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLispOrdEstaVacia ( SListaOrdenadaPtr * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLispEstaVacia ( p_lisObj->p_lispContenido );
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

byte * SLispOrdElemento ( SListaOrdenadaPtr * p_lisObj, int iElem )
{
	byte *			p_byRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( ( iElem >= 0 ) && ( iElem < p_lisObj->p_lispContenido->iNumElementos ) )
		{
			p_byRes = SLispElemento ( p_lisObj->p_lispContenido, iElem );
		}
		else
		{
			p_byRes = NULL;
		}
	}
	else
	{
		p_byRes = NULL;
	}
	return ( p_byRes );
}

int SLispOrdInsertarElem ( SListaOrdenadaPtr * p_lisObj, byte * p_byDatos )
{
	int iRes;
	int iPosAnt;

	if ( ( SLispOrdEsValida ( p_lisObj ) == 1 ) && ES_VALIDO ( p_byDatos ) )
	{
		iPosAnt = SLispOrdBuscarSitio ( p_lisObj, p_byDatos );

		if ( iPosAnt < 0 ) 
		{
			SLispInicio ( p_lisObj->p_lispContenido );
			iRes = SLispInsertarDelante ( p_lisObj->p_lispContenido, p_byDatos );
		}
		else if ( iPosAnt >= p_lisObj->p_lispContenido->iNumElementos )
		{
			SLispFinal ( p_lisObj->p_lispContenido );
			iRes = SLispInsertarDetras ( p_lisObj->p_lispContenido, p_byDatos );
		}
		else  
		{
			SLispMoverA ( p_lisObj->p_lispContenido, iPosAnt );
			if ( ES_NULO ( p_lisObj->p_lispContenido->p_elpActual ) ) 
			{
				iRes = -1;
			}
			else 
			{
				iRes = SLispInsertar ( p_lisObj->p_lispContenido, p_byDatos );
			}
		}
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SLispOrdEliminarElem ( SListaOrdenadaPtr * p_lisObj, int iElem )
{
	int	iRes;

	if ( SLispOrdEsValida ( p_lisObj ) == 1 ) 
	{
		iRes = SLispEliminarElem ( p_lisObj->p_lispContenido, iElem );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLispOrdVaciar ( SListaOrdenadaPtr * p_lisObj )
{
	int	iRes;

	if ( SLispOrdEsValida ( p_lisObj ) == 1 ) 
	{
		iRes = SLispVaciar ( p_lisObj->p_lispContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLispOrdPosicion ( SListaOrdenadaPtr * p_lisObj )
{
	int	iRes;

	if ( SLispOrdEsValida ( p_lisObj ) == 1 ) 
	{
		iRes = SLispPosicion ( p_lisObj->p_lispContenido );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

byte * SLispOrdActual ( SListaOrdenadaPtr * p_lisObj )
{
	byte *			p_byRes;

	if ( SLispOrdEsValida ( p_lisObj ) == 1 ) 
	{
		p_byRes = SLispActual ( p_lisObj->p_lispContenido );
	}
	else
	{
		p_byRes = NULL;
	}
	return ( p_byRes );
}

void SLispOrdInicio ( SListaOrdenadaPtr * p_lisObj )
{
	if ( SLispOrdEsValida ( p_lisObj ) == 1 ) 
	{
		SLispInicio ( p_lisObj->p_lispContenido );
	}
}

void SLispOrdFinal ( SListaOrdenadaPtr * p_lisObj )
{
	if ( SLispOrdEsValida ( p_lisObj ) == 1 ) 
	{
		SLispFinal ( p_lisObj->p_lispContenido );
	}
}

void SLispOrdSiguiente ( SListaOrdenadaPtr * p_lisObj )
{
	if ( SLispOrdEsValida ( p_lisObj ) == 1 ) 
	{
		SLispSiguiente ( p_lisObj->p_lispContenido );
	}
}

void SLispOrdAnterior ( SListaOrdenadaPtr * p_lisObj )
{
	if ( SLispOrdEsValida ( p_lisObj ) == 1 ) 
	{
		SLispAnterior ( p_lisObj->p_lispContenido );
	}
}

void SLispOrdMoverA ( SListaOrdenadaPtr * p_lisObj, int iElem )
{
	if ( SLispOrdEsValida ( p_lisObj ) == 1 ) 
	{
		SLispMoverA ( p_lisObj->p_lispContenido, iElem );
	}
}

void SLispOrdDeposicionar ( SListaOrdenadaPtr * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) )
	{
		SLispDeposicionar ( p_lisObj->p_lispContenido );
	}
}

int SLispOrdBuscar ( SListaOrdenadaPtr * p_lisObj, byte * p_byDatos )
{
	int				iRes;
	int				iEnc;
	SElementoPtr *	p_elpObj;

	if ( ( SLispOrdEsValida ( p_lisObj ) == 1 ) && ES_VALIDO ( p_byDatos ) )
	{
		p_elpObj = p_lisObj->p_lispContenido->p_elpPrimero;
		iRes = 0;
		iEnc = 0;
		while ( ( iRes < p_lisObj->p_lispContenido->iNumElementos ) && ( iEnc == 0 ) &&
			ES_VALIDO ( p_elpObj ) )
		{
			int iCmp = SCmpEvaluar ( p_lisObj->p_cmpObj, (void *) SElpDatos ( p_elpObj ), (void *) p_byDatos );
			if ( iCmp < 0 )
			{
				p_elpObj = SElpSucesor ( p_elpObj );
				iRes = iRes + 1;
			}
			else 
			{
				iEnc = 1;
				if ( iCmp != 0 )
				{	
					iRes = -1;
				}
			}
		}
		if ( iEnc == 0 )
		{
			iRes = -1;
		}
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}


int SLispOrdBuscarSitio ( SListaOrdenadaPtr * p_lisObj, byte * p_byDatos )
{
	int				iRes;
	int				iEnc;
	SElementoPtr * 	p_elpObj;

	if ( ( SLispOrdEsValida ( p_lisObj ) == 1 ) && ES_VALIDO ( p_byDatos ) )
	{
		p_elpObj = p_lisObj->p_lispContenido->p_elpPrimero;
		iRes = -1;
		iEnc = 0;
		while ( ( iRes < p_lisObj->p_lispContenido->iNumElementos ) && ( iEnc == 0 ) &&
			ES_VALIDO ( p_elpObj ) )
		{
			int iCmp = SCmpEvaluar ( p_lisObj->p_cmpObj, (void *) SElpDatos ( p_elpObj ), (void *) p_byDatos );
			if ( iCmp <= 0 )
			{
				p_elpObj = SElpSucesor ( p_elpObj );
				iRes = iRes + 1;
			}
			else
			{
				iEnc = 1;
			}
		}
		if ( ( iEnc == 0 ) && ( iRes < p_lisObj->p_lispContenido->iNumElementos ) )
		{
			iRes = p_lisObj->p_lispContenido->iNumElementos + 1;
		}
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SLispOrdEsNulo ( SListaOrdenadaPtr * p_lisObj )
{
	int iRes;

	if ( SLispOrdEsValida ( p_lisObj ) == 1 ) 
	{
		iRes = SLispEsNulo ( p_lisObj->p_lispContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLispOrdEstaEnFinal ( SListaOrdenadaPtr * p_lisObj )
{
	int iRes;

	if ( SLispOrdEsValida ( p_lisObj ) == 1 ) 
	{
		iRes = SLispEstaEnFinal ( p_lisObj->p_lispContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLispOrdEstaEnInicio ( SListaOrdenadaPtr * p_lisObj )
{
	int iRes;

	if ( SLispOrdEsValida ( p_lisObj ) == 1 ) 
	{
		iRes = SLispEstaEnInicio ( p_lisObj->p_lispContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLispOrdEliminar ( SListaOrdenadaPtr * p_lisObj )
{
	int				iRes;

	if ( SLispOrdEsValida ( p_lisObj ) == 1 ) 
	{
		iRes = SLispEliminar ( p_lisObj->p_lispContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int	SLispOrdLiberacionMemoriaActivada ( SListaOrdenadaPtr * p_lisObj )
{
	int	iRes;

	if ( SLispOrdEsValida ( p_lisObj ) == 1 ) 
	{
		iRes = SLispLiberacionMemoriaActivada ( p_lisObj->p_lispContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

void SLispOrdActivarLiberacionMemoria ( SListaOrdenadaPtr * p_lisObj )
{
	if ( SLispOrdEsValida ( p_lisObj ) == 1 ) 
	{
		SLispActivarLiberacionMemoria ( p_lisObj->p_lispContenido );
	}
}

void SLispOrdDesactivarLiberacionMemoria ( SListaOrdenadaPtr * p_lisObj )
{
	if ( SLispOrdEsValida ( p_lisObj ) == 1 ) 
	{
		SLispDesactivarLiberacionMemoria ( p_lisObj->p_lispContenido );
	}
}


