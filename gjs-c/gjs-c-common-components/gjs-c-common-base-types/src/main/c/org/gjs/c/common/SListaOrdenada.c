#include "SListaOrdenada.h"


#include "TiposBasicosConfig.h"


int SLisOrdBuscarSitio ( SListaOrdenada * p_lisObj, SBloque * p_blqDatos );


SListaOrdenada * SLisOrdCrear ( PFUNINTPVPV fComparar )
{
	SListaOrdenada * p_lisObj;
	
	p_lisObj = (SListaOrdenada *) MemReservar ( sizeof ( SListaOrdenada ) );
	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_lisObj->p_lisContenido = SLisCrear ();
		p_lisObj->p_cmpObj = SCmpCrear ( fComparar );
		if ( ES_NULO ( p_lisObj->p_lisContenido ) || ES_NULO ( p_lisObj->p_cmpObj ) )
		{
			SLisOrdDestruir ( &p_lisObj );
		}
	}
	return ( p_lisObj );
}

void SLisOrdDestruir ( SListaOrdenada ** p_p_lisObj )
{
	SListaOrdenada * p_lisObj;
	
	if ( ES_VALIDO ( p_p_lisObj ) )
	{
		p_lisObj = *p_p_lisObj;

		if ( ES_VALIDO ( p_lisObj ) )
		{
			SLisDestruir ( &(p_lisObj->p_lisContenido) );
			SCmpDestruir ( &(p_lisObj->p_cmpObj) );
			MemLiberar ( (void **) p_p_lisObj );
		}
	}
}

int SLisOrdEsValida ( SListaOrdenada * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( ( SLisEsValida ( p_lisObj->p_lisContenido ) == 1 ) &&
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

int SLisOrdNumElementos ( SListaOrdenada * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLisNumElementos ( p_lisObj->p_lisContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisOrdEstaVacia ( SListaOrdenada * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLisEstaVacia ( p_lisObj->p_lisContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SElemento * SLisOrdElemento ( SListaOrdenada * p_lisObj, int iElem )
{
	SElemento * p_elmRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_elmRes = SLisElemento ( p_lisObj->p_lisContenido, iElem );
	}
	else
	{
		p_elmRes = NULL;
	}
	return ( p_elmRes );
}

int SLisOrdInsertarElem ( SListaOrdenada * p_lisObj, SElemento * p_elmObj )
{
	int iRes;
	int iPosAnt;

	if ( ( SLisOrdEsValida ( p_lisObj ) == 1 ) && ( SElmEsValido ( p_elmObj ) == 1 ) )
	{
		iPosAnt = SLisOrdBuscarSitio ( p_lisObj, SElmDatos ( p_elmObj ) );

		if ( iPosAnt < 0 ) 
		{
			SLisInicio ( p_lisObj->p_lisContenido );
			iRes = SLisInsertarDelante ( p_lisObj->p_lisContenido, p_elmObj );
		}
		else if ( iPosAnt >= p_lisObj->p_lisContenido->iNumElementos )
		{
			SLisFinal ( p_lisObj->p_lisContenido );
			iRes = SLisInsertarDetras ( p_lisObj->p_lisContenido, p_elmObj );
		}
		else  
		{
			SLisMoverA ( p_lisObj->p_lisContenido, iPosAnt );
			if ( ES_NULO ( p_lisObj->p_lisContenido->p_elmActual ) ) 
			{
				iRes = -1;
			}
			else 
			{
				iRes = SLisInsertar ( p_lisObj->p_lisContenido, p_elmObj );
			}
		}
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SLisOrdEliminarElem ( SListaOrdenada * p_lisObj, int iElem )
{
	int	iRes;

	if ( SLisOrdEsValida ( p_lisObj ) == 1 ) 
	{
		iRes = SLisEliminarElem ( p_lisObj->p_lisContenido, iElem );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisOrdVaciar ( SListaOrdenada * p_lisObj )
{
	int	iRes;

	if ( SLisOrdEsValida ( p_lisObj ) == 1 ) 
	{
		iRes = SLisVaciar ( p_lisObj->p_lisContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisOrdPosicion ( SListaOrdenada * p_lisObj )
{
	int	iRes;

	if ( SLisOrdEsValida ( p_lisObj ) == 1 ) 
	{
		iRes = SLisPosicion ( p_lisObj->p_lisContenido );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

SElemento * SLisOrdActual ( SListaOrdenada * p_lisObj )
{
	SElemento * p_elmRes;

	if ( SLisOrdEsValida ( p_lisObj ) == 1 ) 
	{
		p_elmRes = SLisActual ( p_lisObj->p_lisContenido );
	}
	else
	{
		p_elmRes = NULL;
	}
	return ( p_elmRes );
}

void SLisOrdInicio ( SListaOrdenada * p_lisObj )
{
	if ( SLisOrdEsValida ( p_lisObj ) == 1 ) 
	{
		SLisInicio ( p_lisObj->p_lisContenido );
	}
}

void SLisOrdFinal ( SListaOrdenada * p_lisObj )
{
	if ( SLisOrdEsValida ( p_lisObj ) == 1 ) 
	{
		SLisFinal ( p_lisObj->p_lisContenido );
	}
}

void SLisOrdSiguiente ( SListaOrdenada * p_lisObj )
{
	if ( SLisOrdEsValida ( p_lisObj ) == 1 ) 
	{
		SLisSiguiente ( p_lisObj->p_lisContenido );
	}
}

void SLisOrdAnterior ( SListaOrdenada * p_lisObj )
{
	if ( SLisOrdEsValida ( p_lisObj ) == 1 ) 
	{
		SLisAnterior ( p_lisObj->p_lisContenido );
	}
}

void SLisOrdMoverA ( SListaOrdenada * p_lisObj, int iElem )
{
	if ( SLisOrdEsValida ( p_lisObj ) == 1 ) 
	{
		SLisMoverA ( p_lisObj->p_lisContenido, iElem );
	}
}

void SLisOrdDeposicionar ( SListaOrdenada * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) )
	{
		SLisDeposicionar ( p_lisObj->p_lisContenido );
	}
}

int SLisOrdBuscar ( SListaOrdenada * p_lisObj, SBloque * p_blqDatos )
{
	int			iRes;
	int			iEnc;
	SElemento * p_elmObj;

	if ( ( SLisOrdEsValida ( p_lisObj ) == 1 ) && ES_VALIDO ( p_blqDatos ) )
	{
		p_elmObj = p_lisObj->p_lisContenido->p_elmPrimero;
		iRes = 0;
		iEnc = 0;
		while ( ( iRes < p_lisObj->p_lisContenido->iNumElementos ) && ( iEnc == 0 ) &&
			ES_VALIDO ( p_elmObj ) )
		{
			int iCmp = SCmpEvaluarBloque ( p_lisObj->p_cmpObj, SElmDatos ( p_elmObj ), p_blqDatos );
			if ( iCmp < 0 )
			{
				p_elmObj = SElmSucesor ( p_elmObj );
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

int SLisOrdBuscarExt ( SListaOrdenada * p_lisObj, byte * p_byDatos )
{
	int			iRes;
	int			iEnc;
	SElemento * p_elmObj;

	if ( ( SLisOrdEsValida ( p_lisObj ) == 1 ) && ES_VALIDO ( p_byDatos ) )
	{
		p_elmObj = p_lisObj->p_lisContenido->p_elmPrimero;
		iRes = 0;
		iEnc = 0;
		while ( ( iRes < p_lisObj->p_lisContenido->iNumElementos ) && ( iEnc == 0 ) &&
			ES_VALIDO ( p_elmObj ) )
		{
			int iCmp = SCmpEvaluarBloqueExt ( p_lisObj->p_cmpObj, SElmDatos ( p_elmObj ), p_byDatos );
			if ( iCmp < 0 )
			{
				p_elmObj = SElmSucesor ( p_elmObj );
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

int SLisOrdBuscarSitio ( SListaOrdenada * p_lisObj, SBloque * p_blqDatos )
{
	int			iRes;
	int			iEnc;
	SElemento * p_elmObj;

	if ( ( SLisOrdEsValida ( p_lisObj ) == 1 ) && ( SBlqEsValido ( p_blqDatos ) == 1 ) )
	{
		p_elmObj = p_lisObj->p_lisContenido->p_elmPrimero;
		iRes = -1;
		iEnc = 0;
		while ( ( iRes < p_lisObj->p_lisContenido->iNumElementos ) && ( iEnc == 0 ) &&
			ES_VALIDO ( p_elmObj ) )
		{
			int iCmp = SCmpEvaluarBloque ( p_lisObj->p_cmpObj, SElmDatos ( p_elmObj ), p_blqDatos );
			if ( iCmp <= 0 )
			{
				p_elmObj = SElmSucesor ( p_elmObj );
				iRes = iRes + 1;
			}
			else
			{
				iEnc = 1;
			}
		}
		if ( ( iEnc == 0 ) && ( iRes < p_lisObj->p_lisContenido->iNumElementos ) )
		{
			iRes = p_lisObj->p_lisContenido->iNumElementos + 1;
		}
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SLisOrdEsNulo ( SListaOrdenada * p_lisObj )
{
	int iRes;

	if ( SLisOrdEsValida ( p_lisObj ) == 1 ) 
	{
		iRes = SLisEsNulo ( p_lisObj->p_lisContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisOrdEstaEnFinal ( SListaOrdenada * p_lisObj )
{
	int iRes;

	if ( SLisOrdEsValida ( p_lisObj ) == 1 ) 
	{
		iRes = SLisEstaEnFinal ( p_lisObj->p_lisContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisOrdEstaEnInicio ( SListaOrdenada * p_lisObj )
{
	int iRes;

	if ( SLisOrdEsValida ( p_lisObj ) == 1 ) 
	{
		iRes = SLisEstaEnInicio ( p_lisObj->p_lisContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisOrdEliminar ( SListaOrdenada * p_lisObj )
{
	int			iRes;

	if ( SLisOrdEsValida ( p_lisObj ) == 1 ) 
	{
		iRes = SLisEliminar ( p_lisObj->p_lisContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


