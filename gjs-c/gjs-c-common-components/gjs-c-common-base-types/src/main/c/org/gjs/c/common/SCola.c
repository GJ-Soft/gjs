#include "SCola.h"



#include "TiposBasicosConfig.h"



SCola * SColCrear ()
{
	SCola * p_colObj;
	
	p_colObj = (SCola *) MemReservar ( sizeof ( SCola ) );
	if ( ES_VALIDO ( p_colObj ) )
	{
		p_colObj->p_lisObjetos = SLisCrear ();
	}
	return ( p_colObj );
}

void SColDestruir ( SCola ** p_p_colObj )
{
	SCola * p_colObj;
	
	if ( ES_VALIDO ( p_p_colObj ) )
	{
		p_colObj = *p_p_colObj;

		if ( ES_VALIDO ( p_colObj ) )
		{
			SLisDestruir ( &(p_colObj->p_lisObjetos) );
			MemLiberar ( (void **) p_p_colObj );
		}
	}
}

int SColEsValida ( SCola * p_colObj )
{
	int iRes;

	if ( ES_VALIDO ( p_colObj ) )
	{
		iRes = SLisEsValida ( p_colObj->p_lisObjetos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SColNumElementos ( SCola * p_colObj )
{
	int iRes;

	if ( ES_VALIDO ( p_colObj ) )
	{
		iRes = SLisNumElementos ( p_colObj->p_lisObjetos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SColEstaVacia ( SCola * p_colObj )
{
	int iRes;

	if ( ES_VALIDO ( p_colObj ) )
	{
		iRes = SLisEstaVacia ( p_colObj->p_lisObjetos );
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

SElemento * SColPrimero ( SCola * p_colObj )
{
	SElemento * p_elmRes;

	if ( SColEstaVacia ( p_colObj ) == 0 )
	{
		p_elmRes = SLisElemento ( p_colObj->p_lisObjetos, 0 );
	}
	else
	{
		p_elmRes = NULL;
	}
	return ( p_elmRes );
}

SElemento * SColUltimo ( SCola * p_colObj )
{
	SElemento * p_elmRes;

	if ( SColEstaVacia ( p_colObj ) == 0 )
	{
		p_elmRes = SLisElemento ( p_colObj->p_lisObjetos, 
								  SLisNumElementos ( p_colObj->p_lisObjetos ) - 1 );
	}
	else
	{
		p_elmRes = NULL;
	}
	return ( p_elmRes );
}

SElemento * SColElemento ( SCola * p_colObj, int iElem )
{
	SElemento * p_elmRes;

	if ( SColEstaVacia ( p_colObj ) == 0 )
	{
		p_elmRes = SLisElemento ( p_colObj->p_lisObjetos, iElem );
	}
	else
	{
		p_elmRes = NULL;
	}
	return ( p_elmRes );
}

SElemento * SColDesencolar ( SCola * p_colObj )
{
	SElemento * p_elmRes;

	if ( SColEstaVacia ( p_colObj ) == 0 )
	{
		p_elmRes = SLisExtraerElem ( p_colObj->p_lisObjetos, 0 );
	}
	else
	{
		p_elmRes = NULL;
	}
	return ( p_elmRes );
}

int SColEncolar ( SCola * p_colObj, SElemento * p_elmObj )
{
	int iRes;

	if ( ( SColEsValida ( p_colObj ) == 1 ) && ES_VALIDO ( p_elmObj ) )
	{
		iRes = SLisInsertarAlFinal ( p_colObj->p_lisObjetos, p_elmObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SColEliminarPrimero ( SCola * p_colObj )
{
	int	iRes;

	if ( SColEstaVacia ( p_colObj ) == 0 )
	{
		iRes = SLisEliminarElem ( p_colObj->p_lisObjetos, 0 );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SColEliminarUltimo ( SCola * p_colObj )
{
	int	iRes;

	if ( SColEstaVacia ( p_colObj ) == 0 )
	{
		iRes = SLisEliminarElem ( p_colObj->p_lisObjetos, 
								  SLisNumElementos ( p_colObj->p_lisObjetos ) - 1 );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SColEliminar ( SCola * p_colObj, int iElem )
{
	int	iRes;

	if ( SColEstaVacia ( p_colObj ) == 0 )
	{
		iRes = SLisEliminarElem ( p_colObj->p_lisObjetos, iElem );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SColVaciar ( SCola * p_colObj )
{
	int	iRes;

	if ( SColEstaVacia ( p_colObj ) == 0 )
	{
		iRes = SLisVaciar ( p_colObj->p_lisObjetos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SLista * SColLista ( SCola * p_colObj )
{
	SLista * p_lisRes;

	if ( ES_VALIDO ( p_colObj ) )
	{
		p_lisRes = p_colObj->p_lisObjetos;
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}
