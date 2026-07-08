#include "SListaValores.h"

#include "TiposDatosConfig.h"




SListaValores * SLisValCrear ()
{
	SListaValores * p_lisObj;
	
	p_lisObj = (SListaValores *) MemReservar ( sizeof ( SListaValores ) );
	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_lisObj->p_lisDatos = SLispCrear ();
		if ( ES_VALIDO ( p_lisObj->p_lisDatos ) )
		{
			SLispDesactivarLiberacionMemoria ( p_lisObj->p_lisDatos );
		}
		else
		{
			MemLiberar ( (void **) &p_lisObj );
		}
	}
	return ( p_lisObj );
}

void SLisValDestruir ( SListaValores ** p_p_lisObj )
{
	SListaValores * p_lisObj;
	
	if ( ES_VALIDO ( p_p_lisObj ) )
	{
		p_lisObj = *p_p_lisObj;

		if ( ES_VALIDO ( p_lisObj ) )
		{
			SLisValVaciar ( p_lisObj );
			SLispDestruir ( &(p_lisObj->p_lisDatos) );
			MemLiberar ( (void **) p_p_lisObj );
		}
	}
}

int SLisValEsValida ( SListaValores * p_lisObj )
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

int SLisValEstaVacia ( SListaValores * p_lisObj )
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

int SLisValNumElementos ( SListaValores * p_lisObj )
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

SValor * SLisValElemento ( SListaValores * p_lisObj, int iElem )
{
	SValor *	p_valRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_valRes = (SValor *) SLispElemento ( p_lisObj->p_lisDatos, iElem );
	}
	else
	{
		p_valRes = NULL;
	}
	return ( p_valRes );
}

int SLisValEstablecerElem ( SListaValores * p_lisObj, int iElem, SValor * p_valDatos )
{
	int		iRes;
	SValor *	p_valAnt;	

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_valAnt = (SValor *) SLispElemento ( p_lisObj->p_lisDatos, iElem );
		iRes = SLispEstablecerElem ( p_lisObj->p_lisDatos, iElem, (byte *) p_valDatos );
		if ( iRes != 1 )
		{
			SValDestruir ( &p_valAnt );
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisValInsertarElem ( SListaValores * p_lisObj, int iPosAnt, SValor * p_valDatos )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLispInsertarElem ( p_lisObj->p_lisDatos, iPosAnt, (byte *) p_valDatos );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SLisValInsertarAlInicio ( SListaValores * p_lisObj, SValor * p_valDatos )
{
	return ( SLisValInsertarElem ( p_lisObj, -1, p_valDatos ) );
}

int SLisValInsertarAlFinal ( SListaValores * p_lisObj, SValor * p_valDatos )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLisValInsertarElem ( p_lisObj, SLisValNumElementos ( p_lisObj ), p_valDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisValEliminarElem ( SListaValores * p_lisObj, int iElem )
{
	int 		iRes;
	SValor * 	p_valObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_valObj = SLisValElemento ( p_lisObj, iElem );
		SValDestruir ( &p_valObj );
		iRes = SLispEliminarElem ( p_lisObj->p_lisDatos, iElem );		
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisValVaciar ( SListaValores * p_lisObj )
{
	int 		iRes;
	int			iNumElems;
	SValor * 	p_valObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iNumElems = SLisValNumElementos ( p_lisObj );
		for ( int iElem = 0; iElem < iNumElems; iElem = iElem + 1 )
		{
			p_valObj = SLisValElemento ( p_lisObj, iElem );
			SValDestruir ( &p_valObj );
		}
		iRes = SLispVaciar ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SLisValPosicion ( SListaValores * p_lisObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLispPosicion ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

SValor * SLisValActual ( SListaValores * p_lisObj )
{
	SValor *	p_valRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_valRes = (SValor *) SLispActual ( p_lisObj->p_lisDatos );
	}
	else
	{
		p_valRes = NULL;
	}
	return ( p_valRes );
}

void SLisValInicio ( SListaValores * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLispInicio ( p_lisObj->p_lisDatos );
	}
}

void SLisValFinal ( SListaValores * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLispFinal ( p_lisObj->p_lisDatos );
	}
}

void SLisValSiguiente ( SListaValores * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLispSiguiente ( p_lisObj->p_lisDatos );
	}
}

void SLisValAnterior ( SListaValores * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLispAnterior ( p_lisObj->p_lisDatos );
	}
}

void SLisValMoverA ( SListaValores * p_lisObj, int iElem )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLispMoverA ( p_lisObj->p_lisDatos, iElem );
	}
}

void SLisValDeposicionar ( SListaValores * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLispDeposicionar ( p_lisObj->p_lisDatos );
	}
}

int SLisValEsNulo ( SListaValores * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		iRes = SLispEsNulo ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisValEstaEnFinal ( SListaValores * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		iRes = SLispEstaEnFinal ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisValEstaEnInicio ( SListaValores * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		iRes = SLispEstaEnInicio ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisValEstablecer ( SListaValores * p_lisObj, SValor * p_valDatos )
{
	SValor *	p_valAnt;  
	int			iRes;

	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		p_valAnt = (SValor *) SLispActual ( p_lisObj->p_lisDatos );
		iRes = SLispEstablecer ( p_lisObj->p_lisDatos, (byte *) p_valDatos );
		if ( iRes != 1 )
		{
			SValDestruir ( &p_valAnt );
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisValInsertar ( SListaValores * p_lisObj, SValor * p_valDatos )
{
	return ( SLisValInsertarAlFinal ( p_lisObj, p_valDatos ) );
}

int SLisValInsertarDelante ( SListaValores * p_lisObj, SValor * p_valDatos )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		iRes = SLispInsertarDelante ( p_lisObj->p_lisDatos, (byte *) p_valDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisValInsertarDetras ( SListaValores * p_lisObj, SValor * p_valDatos )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		iRes = SLispInsertarDetras ( p_lisObj->p_lisDatos, (byte *) p_valDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisValEliminar ( SListaValores * p_lisObj )
{
	int 		iRes;
	SValor * 	p_valObj;

	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		p_valObj = SLisValActual ( p_lisObj );
		SValDestruir ( &p_valObj );
		iRes = SLispEliminar ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisValExiste ( SListaValores * p_lisObj, SValor * p_valDatos )
{
	int iRes;
	int iElem;
	int iNumElems;

	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_valDatos ) )
	{
		iRes = 0;
		iElem = 0;
		iNumElems = SLisValNumElementos ( p_lisObj );
		while ( ( iElem < iNumElems ) && ( iRes == 0 ) )
		{
			iRes = SValEsIgualNoTipado ( SLisValElemento ( p_lisObj, iElem ), p_valDatos );
			iElem = iElem + 1;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisValBuscar ( SListaValores * p_lisObj, SValor * p_valDatos )
{
	int iRes;
	int iElem;
	int iNumElems;

	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_valDatos ) )
	{
		iRes = -1;
		iElem = 0;
		iNumElems = SLisValNumElementos ( p_lisObj );
		while ( ( iElem < iNumElems ) && ( iRes == -1 ) )
		{
			if ( SValEsIgualNoTipado ( SLisValElemento ( p_lisObj, iElem ), p_valDatos ) )
			{
				iRes = iElem;
			}
			iElem = iElem + 1;
		}
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}



