#include "SListaParametros.h"

#include "TiposDatosConfig.h"




SListaParametros * SLisParCrear ()
{
	SListaParametros * p_lisObj;
	
	p_lisObj = (SListaParametros *) MemReservar ( sizeof ( SListaParametros ) );
	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_lisObj->p_lisDatos = SLispCrear ();
		SLispDesactivarLiberacionMemoria ( p_lisObj->p_lisDatos );
	}
	return ( p_lisObj );
}

void SLisParDestruir ( SListaParametros ** p_p_lisObj )
{
	SListaParametros * p_lisObj;
	
	if ( ES_VALIDO ( p_p_lisObj ) )
	{
		p_lisObj = *p_p_lisObj;

		if ( ES_VALIDO ( p_lisObj ) )
		{
			SLisParVaciar ( p_lisObj );
			SLispDestruir ( &(p_lisObj->p_lisDatos) );
			MemLiberar ( (void **) p_p_lisObj );
		}
	}
}

int SLisParEsValida ( SListaParametros * p_lisObj )
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

int SLisParEstaVacia ( SListaParametros * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLispEstaVacia ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisParNumElementos ( SListaParametros * p_lisObj )
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

SParametro * SLisParElemento ( SListaParametros * p_lisObj, int iElem )
{
	SParametro *	p_parRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_parRes = (SParametro *) SLispElemento ( p_lisObj->p_lisDatos, iElem );
	}
	else
	{
		p_parRes = NULL;
	}
	return ( p_parRes );
}

int SLisParEstablecerElem ( SListaParametros * p_lisObj, int iElem, SParametro * p_parDatos )
{
	int				iRes;
	SParametro *	p_parAnt;	

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_parAnt = (SParametro *) SLispElemento ( p_lisObj->p_lisDatos, iElem );
		iRes = SLispEstablecerElem ( p_lisObj->p_lisDatos, iElem, (byte *) p_parDatos );
		if ( iRes != 1 )
		{
			SParDestruir ( &p_parAnt );
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisParInsertarElem ( SListaParametros * p_lisObj, int iPosAnt, SParametro * p_parDatos )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLispInsertarElem ( p_lisObj->p_lisDatos, iPosAnt, (byte *) p_parDatos );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SLisParInsertarAlInicio ( SListaParametros * p_lisObj, SParametro * p_parDatos )
{
	return ( SLisParInsertarElem ( p_lisObj, -1, p_parDatos ) );
}

int SLisParInsertarAlFinal ( SListaParametros * p_lisObj, SParametro * p_parDatos )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLisParInsertarElem ( p_lisObj, SLisParNumElementos ( p_lisObj ), p_parDatos );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SLisParEliminarElem ( SListaParametros * p_lisObj, int iElem )
{
	int 			iRes;
	SParametro * 	p_parObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_parObj = SLisParElemento ( p_lisObj, iElem );
		SParDestruir ( &p_parObj );
		iRes = SLispEliminarElem ( p_lisObj->p_lisDatos, iElem );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SLisParVaciar ( SListaParametros * p_lisObj )
{
	int 			iRes;
	int				iNumElems;
	SParametro * 	p_parObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iNumElems = SLisParNumElementos ( p_lisObj );
		for ( int iElem = 0; iElem < iNumElems; iElem = iElem + 1 )
		{
			p_parObj = SLisParElemento ( p_lisObj, iElem );
			SParDestruir ( &p_parObj );
		}
		iRes = SLispVaciar ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SLisParPosicion ( SListaParametros * p_lisObj )
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

SParametro * SLisParActual ( SListaParametros * p_lisObj )
{
	SParametro *	p_parRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_parRes = (SParametro *) SLispActual ( p_lisObj->p_lisDatos );
	}
	else
	{
		p_parRes = NULL;
	}
	return ( p_parRes );
}

void SLisParInicio ( SListaParametros * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLispInicio ( p_lisObj->p_lisDatos );
	}
}

void SLisParFinal ( SListaParametros * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLispFinal ( p_lisObj->p_lisDatos );
	}
}

void SLisParSiguiente ( SListaParametros * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLispSiguiente ( p_lisObj->p_lisDatos );
	}
}

void SLisParAnterior ( SListaParametros * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLispAnterior ( p_lisObj->p_lisDatos );
	}
}

void SLisParMoverA ( SListaParametros * p_lisObj, int iElem )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLispMoverA ( p_lisObj->p_lisDatos, iElem );
	}
}

void SLisParDeposicionar ( SListaParametros * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLispDeposicionar ( p_lisObj->p_lisDatos );
	}
}

int SLisParEsNulo ( SListaParametros * p_lisObj )
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

int SLisParEstaEnFinal ( SListaParametros * p_lisObj )
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

int SLisParEstaEnInicio ( SListaParametros * p_lisObj )
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

int SLisParEstablecer ( SListaParametros * p_lisObj, SParametro * p_parDatos )
{
	SParametro *	p_parAnt;  
	int		iRes;

	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		p_parAnt = (SParametro *) SLispActual ( p_lisObj->p_lisDatos );
		iRes = SLispEstablecer ( p_lisObj->p_lisDatos, (byte *) p_parDatos );
		if ( iRes != 1 )
		{
			SParDestruir ( &p_parAnt );
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int SLisParInsertar ( SListaParametros * p_lisObj, SParametro * p_parDatos )
{
	return ( SLisParInsertarDetras ( p_lisObj, p_parDatos ) );
}

int SLisParInsertarDelante ( SListaParametros * p_lisObj, SParametro * p_parDatos )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		iRes = SLispInsertarDelante ( p_lisObj->p_lisDatos, (byte *) p_parDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisParInsertarDetras ( SListaParametros * p_lisObj, SParametro * p_parDatos )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		iRes = SLispInsertarDetras ( p_lisObj->p_lisDatos, (byte *) p_parDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisParEliminar ( SListaParametros * p_lisObj )
{
	int 			iRes;
	SParametro * 	p_parObj;

	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		p_parObj = SLisParActual ( p_lisObj );
		SParDestruir ( &p_parObj );
		iRes = SLispEliminar ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisParExiste ( SListaParametros * p_lisObj, SParametro * p_parDatos )
{
	int 			iRes;
	int 			iElem;
	int				iNumElems;
	SParametro * 	p_parElem;

	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_parDatos )  ) 
	{
		iRes = 0;
		iElem = 0;
		iNumElems = SLisParNumElementos ( p_lisObj );
		while ( ( iElem < iNumElems ) && ( iRes == 0 ) )
		{
			p_parElem = SLisParElemento ( p_lisObj, iElem );
			if ( SCadEsIgual ( SParNombre ( p_parElem ), SParNombre ( p_parDatos ) ) == 1 )
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

int SLisParBuscar ( SListaParametros * p_lisObj, SParametro * p_parDatos )
{
	int 			iRes;
	int 			iElem;
	int				iNumElems;
	SParametro *	 p_parElem;

	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_parDatos ) )
	{
		iRes = -1;
		iElem = 0;
		iNumElems = SLisParNumElementos ( p_lisObj );
		while ( ( iElem < iNumElems ) && ( iRes == 0 ) )
		{
			p_parElem = SLisParElemento ( p_lisObj, iElem );
			if ( SCadEsIgual ( SParNombre ( p_parElem ), SParNombre ( p_parDatos ) ) == 1 )
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

