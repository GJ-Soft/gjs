#include "SListaRealesDobles.h"

#include "CalculoConfig.h"
#include "CalculoOperaciones.h"



SListaRealesDobles * SLisRealdCrear ()
{
	SListaRealesDobles * p_lisObj;
	
	p_lisObj = (SListaRealesDobles *) MemReservar ( sizeof ( SListaRealesDobles ) );
	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_lisObj->p_lisDatos = SLisCrear ();
	}
	return ( p_lisObj );
}

void SLisRealdDestruir ( SListaRealesDobles ** p_p_lisObj )
{
	SListaRealesDobles * p_lisObj;
	
	if ( ES_VALIDO ( p_p_lisObj ) )
	{
		p_lisObj = *p_p_lisObj;

		if ( ES_VALIDO ( p_lisObj ) )
		{
			SLisDestruir ( &(p_lisObj->p_lisDatos) );
			MemLiberar ( (void **) p_p_lisObj );
		}
	}
}

int SLisRealdEsValida ( SListaRealesDobles * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLisEsValida ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisRealdEstaVacia ( SListaRealesDobles * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLisEstaVacia ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

int SLisRealdNumElementos ( SListaRealesDobles * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLisNumElementos ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

double SLisRealdElemento ( SListaRealesDobles * p_lisObj, int iElem )
{
	double		dRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_elmObj = SLisElemento ( p_lisObj->p_lisDatos, iElem );
		if ( ES_VALIDO ( p_elmObj ) )
		{
			dRes = SElmRealDoble ( p_elmObj );
		}
		else
		{
			dRes = 0;
		}
	}
	else
	{
		dRes = 0;
	}
	return ( dRes );
}

int SLisRealdInsertarElem ( SListaRealesDobles * p_lisObj, int iPosAnt, double dDato )
{
	int			iRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_elmObj = SElmCrearRealDoble ();
		if ( ES_VALIDO ( p_elmObj ) )
		{
			if ( SElmEscribirRealDoble ( p_elmObj, dDato ) == 1 )
			{
				iRes = SLisInsertarElem ( p_lisObj->p_lisDatos, iPosAnt, p_elmObj );
			}
			else
			{
				iRes = -1;
			}
			if ( iRes != 1 )
			{
				SElmDestruir ( &p_elmObj );
			}
		}
		else
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

int SLisRealdInsertarAlInicio ( SListaRealesDobles * p_lisObj, double dDato )
{
	return ( SLisRealdInsertarElem ( p_lisObj, -1, dDato ) );
}

int SLisRealdInsertarAlFinal ( SListaRealesDobles * p_lisObj, double dDato )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLisRealdInsertarElem ( p_lisObj, SLisRealdNumElementos ( p_lisObj ), dDato );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SLisRealdEliminarElem ( SListaRealesDobles * p_lisObj, int iElem )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLisEliminarElem ( p_lisObj->p_lisDatos, iElem );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SLisRealdVaciar ( SListaRealesDobles * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLisVaciar ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SLisRealdPosicion ( SListaRealesDobles * p_lisObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLisPosicion ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

double SLisRealdActual ( SListaRealesDobles * p_lisObj )
{
	double		dRes;
	SElemento * p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_elmObj = SLisActual ( p_lisObj->p_lisDatos );
		if ( ES_VALIDO ( p_elmObj ) )
		{
			dRes = SElmRealDoble ( p_elmObj );
		}
		else
		{
			ERROR_ESTABLECER( ERR_POSICION_INVALIDA );
			dRes = 0.0;
		}
	}
	else
	{
		dRes = 0.0;
	}
	return ( dRes );
}

void SLisRealdInicio ( SListaRealesDobles * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLisInicio ( p_lisObj->p_lisDatos );
	}
}

void SLisRealdFinal ( SListaRealesDobles * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLisFinal ( p_lisObj->p_lisDatos );
	}
}

void SLisRealdSiguiente ( SListaRealesDobles * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLisSiguiente ( p_lisObj->p_lisDatos );
	}
}

void SLisRealdAnterior ( SListaRealesDobles * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLisAnterior ( p_lisObj->p_lisDatos );
	}
}

void SLisRealdMoverA ( SListaRealesDobles * p_lisObj, int iElem )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLisMoverA ( p_lisObj->p_lisDatos, iElem );
	}
}

void SLisRealdDeposicionar ( SListaRealesDobles * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLisDeposicionar ( p_lisObj->p_lisDatos );
	}
}

int SLisRealdEsNulo ( SListaRealesDobles * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		iRes = SLisEsNulo ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisRealdEstaEnFinal ( SListaRealesDobles * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		iRes = SLisEstaEnFinal ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisRealdEstaEnInicio ( SListaRealesDobles * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		iRes = SLisEstaEnInicio ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisRealdInsertar ( SListaRealesDobles * p_lisObj, double dDato )
{
	return ( SLisRealdInsertarDetras ( p_lisObj, dDato ) );
}

int SLisRealdInsertarDelante ( SListaRealesDobles * p_lisObj, double dDato )
{
	int			iRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_elmObj = SElmCrearRealDoble ();
		if ( ES_VALIDO ( p_elmObj ) )
		{
			if ( SElmEscribirRealDoble ( p_elmObj, dDato ) == 1 )
			{
				iRes = SLisInsertarDelante ( p_lisObj->p_lisDatos, p_elmObj );
			}
			else
			{
				iRes = -1;
			}
			if ( iRes != 1 )
			{
				SElmDestruir ( &p_elmObj );
			}
		}
		else
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

int SLisRealdInsertarDetras ( SListaRealesDobles * p_lisObj, double dDato )
{
	int			iRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_elmObj = SElmCrearRealDoble ();
		if ( ES_VALIDO ( p_elmObj ) )
		{
			if ( SElmEscribirRealDoble ( p_elmObj, dDato ) == 1 )
			{
				iRes = SLisInsertarDetras ( p_lisObj->p_lisDatos, p_elmObj );
			}
			else
			{
				iRes = -1;
			}
			if ( iRes != 1 )
			{
				SElmDestruir ( &p_elmObj );
			}
		}
		else
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

int SLisRealdEliminar ( SListaRealesDobles * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		iRes = SLisEliminar ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisRealdExiste ( SListaRealesDobles * p_lisObj, double dDato )
{
	int iRes;
	int iElem;

	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		iRes = 0;
		iElem = 0;
		while ( ( iElem < SLisRealdNumElementos ( p_lisObj ) ) && ( iRes == 0 ) )
		{
			if ( MatEsIgual ( SLisRealdElemento ( p_lisObj, iElem ), dDato ) == 1 )
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

int SLisRealdBuscar ( SListaRealesDobles * p_lisObj, double dDato )
{
	int iRes;
	int iElem;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = -1;
		iElem = 0;
		while ( ( iElem < SLisRealdNumElementos ( p_lisObj ) ) && ( iRes == -1 ) )
		{
			if ( MatEsIgual ( SLisRealdElemento ( p_lisObj, iElem ), dDato ) == 1 )
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




