#include "SListaEntidades.h"

#include "TiposBaseDatosConfig.h"




SListaEntidades * SLisEntCrear ()
{
	SListaEntidades * p_lisObj;
	
	p_lisObj = (SListaEntidades *) MemReservar ( sizeof ( SListaEntidades ) );
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

void SLisEntDestruir ( SListaEntidades ** p_p_lisObj )
{
	SListaEntidades * p_lisObj;
	
	if ( ES_VALIDO ( p_p_lisObj ) )
	{
		p_lisObj = *p_p_lisObj;

		if ( ES_VALIDO ( p_lisObj ) )
		{
			SLisEntVaciar ( p_lisObj );
			SLispDestruir ( &(p_lisObj->p_lisDatos) );
			MemLiberar ( (void **) p_p_lisObj );
		}
	}
}

int SLisEntEsValida ( SListaEntidades * p_lisObj )
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

int SLisEntEstaVacia ( SListaEntidades * p_lisObj )
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

int SLisEntNumElementos ( SListaEntidades * p_lisObj )
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

SEntidad * SLisEntElemento ( SListaEntidades * p_lisObj, int iElem )
{
	SEntidad *	p_cRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_cRes = (SEntidad *) SLispElemento ( p_lisObj->p_lisDatos, iElem );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SLisEntEstablecerElem ( SListaEntidades * p_lisObj, int iElem, SEntidad * p_entDatos )
{
	int			iRes;
	SEntidad *	p_entAnt;	

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_entAnt = (SEntidad *) SLispElemento ( p_lisObj->p_lisDatos, iElem );
		if ( SLispEstablecerElem ( p_lisObj->p_lisDatos, iElem, (byte *) p_entDatos ) == 1 )
		{
			iRes = 1;
			if ( p_entAnt != p_entDatos )
			{
				SEntDestruir ( &p_entAnt );
			}
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

int SLisEntInsertarElem ( SListaEntidades * p_lisObj, int iPosAnt, SEntidad * p_entDatos )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLispInsertarElem ( p_lisObj->p_lisDatos, iPosAnt, (byte *) p_entDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisEntInsertarAlInicio ( SListaEntidades * p_lisObj, SEntidad * p_entDatos )
{
	return ( SLisEntInsertarElem ( p_lisObj, -1, p_entDatos ) );
}

int SLisEntInsertarAlFinal ( SListaEntidades * p_lisObj, SEntidad * p_entDatos )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLisEntInsertarElem ( p_lisObj, SLisEntNumElementos ( p_lisObj ), p_entDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisEntEliminarElem ( SListaEntidades * p_lisObj, int iElem )
{
	int 		iRes;
	SEntidad * 	p_entObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_entObj = SLisEntElemento ( p_lisObj, iElem );
		if ( ES_VALIDO ( p_entObj ) ) 
		{
			iRes = SLispEliminarElem ( p_lisObj->p_lisDatos, iElem );
			if ( iRes == 1 ) 
			{
				SEntDestruir ( &p_entObj );	
			}
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

SEntidad * SLisEntExtraerElem ( SListaEntidades * p_lisObj, int iElem )
{
	SEntidad * 	p_entRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_entRes = SLisEntElemento ( p_lisObj, iElem );
		if ( ES_VALIDO ( p_entRes ) )
		{
			if ( SLispEliminarElem ( p_lisObj->p_lisDatos, iElem ) != 1 )
			{
				p_entRes = NULL;
			}
		}
	}
	else
	{
		p_entRes = NULL;
	}
	return ( p_entRes );
}

int SLisEntVaciar ( SListaEntidades * p_lisObj )
{
	int 		iRes;
	SEntidad * 	p_entObj;
	int			iNumElems;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iNumElems = SLisEntNumElementos ( p_lisObj );
		for ( int iElem = 0; iElem < iNumElems; iElem = iElem + 1 )
		{
			p_entObj = SLisEntElemento ( p_lisObj, iElem );
			SEntDestruir ( &p_entObj );
		}
		iRes = SLispVaciar ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisEntPosicion ( SListaEntidades * p_lisObj )
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

SEntidad * SLisEntActual ( SListaEntidades * p_lisObj )
{
	SEntidad *	p_cRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_cRes = (SEntidad *) SLispActual ( p_lisObj->p_lisDatos );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

void SLisEntInicio ( SListaEntidades * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLispInicio ( p_lisObj->p_lisDatos );
	}
}

void SLisEntFinal ( SListaEntidades * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLispFinal ( p_lisObj->p_lisDatos );
	}
}

void SLisEntSiguiente ( SListaEntidades * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLispSiguiente ( p_lisObj->p_lisDatos );
	}
}

void SLisEntAnterior ( SListaEntidades * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLispAnterior ( p_lisObj->p_lisDatos );
	}
}

void SLisEntMoverA ( SListaEntidades * p_lisObj, int iElem )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLispMoverA ( p_lisObj->p_lisDatos, iElem );
	}
}

void SLisEntDeposicionar ( SListaEntidades * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLispDeposicionar ( p_lisObj->p_lisDatos );
	}
}

int SLisEntEsNulo ( SListaEntidades * p_lisObj )
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

int SLisEntEstaEnFinal ( SListaEntidades * p_lisObj )
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

int SLisEntEstaEnInicio ( SListaEntidades * p_lisObj )
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

int SLisEntEstablecer ( SListaEntidades * p_lisObj, SEntidad * p_entDatos )
{
	SEntidad *	p_entAnt;  
	int			iRes;

	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		p_entAnt = (SEntidad *) SLispActual ( p_lisObj->p_lisDatos );
		iRes = SLispEstablecer ( p_lisObj->p_lisDatos, (byte *) p_entDatos );
		if ( ( iRes == 1 ) && ( p_entAnt != p_entDatos ) )
		{
			SEntDestruir ( &p_entAnt );
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int SLisEntInsertar ( SListaEntidades * p_lisObj, SEntidad * p_entDatos )
{
	return ( SLisEntInsertarDetras ( p_lisObj, p_entDatos ) );
}

int SLisEntInsertarDelante ( SListaEntidades * p_lisObj, SEntidad * p_entDatos )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		iRes = SLispInsertarDelante ( p_lisObj->p_lisDatos, (byte *) p_entDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisEntInsertarDetras ( SListaEntidades * p_lisObj, SEntidad * p_entDatos )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		iRes = SLispInsertarDetras ( p_lisObj->p_lisDatos, (byte *) p_entDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisEntEliminar ( SListaEntidades * p_lisObj )
{
	int 		iRes;
	SEntidad * 	p_entAnt;

	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		p_entAnt = SLisEntActual ( p_lisObj );
		if ( ES_VALIDO ( p_entAnt ) )
		{
			iRes = SLispEliminar ( p_lisObj->p_lisDatos );
			if ( iRes == 1 )
			{
				SEntDestruir ( &p_entAnt );
			}
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

int SLisEntExiste ( SListaEntidades * p_lisObj, SEntidad * p_entDatos )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_entDatos )  ) 
	{
		iRes = SLisEntExisteId ( p_lisObj, SEntId ( p_entDatos ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisEntExisteId ( SListaEntidades * p_lisObj, SId * p_idEntidad )
{
	int iRes;
	int iElem;
	int	iNumElems;

	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_idEntidad )  ) 
	{
		iRes = 0;
		iElem = 0;
		iNumElems = SLisEntNumElementos ( p_lisObj );
		while ( ( iElem < iNumElems ) && ( iRes == 0 ) )
		{
			if ( SEntEsIgualId ( SLisEntElemento ( p_lisObj, iElem ), p_idEntidad ) == 1 )
			{
				iRes = 1;
			}
			iElem = iElem + 1;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisEntExisteValorId ( SListaEntidades * p_lisObj, unsigned long ulId )
{
	int iRes;
	int iElem;
	int	iNumElems;

	if ( ES_VALIDO ( p_lisObj ) && ( ulId > 0 ) ) 
	{
		iRes = 0;
		iElem = 0;
		iNumElems = SLisEntNumElementos ( p_lisObj );
		while ( ( iElem < iNumElems ) && ( iRes == 0 ) )
		{
			if ( SEntEsIgualNum ( SLisEntElemento ( p_lisObj, iElem ), ulId ) == 1 )
			{
				iRes = 1;
			}
			iElem = iElem + 1;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int SLisEntBuscar ( SListaEntidades * p_lisObj, SEntidad * p_entDatos )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_entDatos )  ) 
	{
		iRes = SLisEntBuscarId ( p_lisObj, SEntId ( p_entDatos ) );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}


int SLisEntBuscarId ( SListaEntidades * p_lisObj, SId * p_idEntidad )
{
	int iRes;
	int iElem;
	int	iNumElems;

	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_idEntidad ) )
	{
		iRes = -1;
		iElem = 0;
		iNumElems = SLisEntNumElementos ( p_lisObj );
		while ( ( iElem < iNumElems ) && ( iRes == -1 ) )
		{
			if ( SEntEsIgualId ( SLisEntElemento ( p_lisObj, iElem ), p_idEntidad ) == 1 )
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

int SLisEntBuscarValorId ( SListaEntidades * p_lisObj, unsigned long ulId )
{
	int iRes;
	int iElem;
	int	iNumElems;

	if ( ES_VALIDO ( p_lisObj ) && ( ulId > 0 ) )
	{
		iRes = -1;
		iElem = 0;
		iNumElems = SLisEntNumElementos ( p_lisObj );
		while ( ( iElem < iNumElems ) && ( iRes == -1 ) )
		{
			if ( SEntEsIgualNum ( SLisEntElemento ( p_lisObj, iElem ), ulId ) == 1 )
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

