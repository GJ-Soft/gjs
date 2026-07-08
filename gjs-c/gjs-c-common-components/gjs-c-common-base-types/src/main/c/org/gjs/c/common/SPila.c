#include "SPila.h"



#include "TiposBasicosConfig.h"



SPila * SPilCrear ()
{
	SPila * p_pilObj;
	
	p_pilObj = (SPila *) MemReservar ( sizeof ( SPila ) );
	if ( ES_VALIDO ( p_pilObj ) )
	{
		p_pilObj->p_lisObjetos = SLisCrear ();
	}
	return ( p_pilObj );
}

void SPilDestruir ( SPila ** p_p_pilObj )
{
	SPila * p_pilObj;
	
	if ( ES_VALIDO ( p_p_pilObj ) )
	{
		p_pilObj = *p_p_pilObj;

		if ( ES_VALIDO ( p_pilObj ) )
		{
			SLisDestruir ( &(p_pilObj->p_lisObjetos) );
			MemLiberar ( (void **) p_p_pilObj );
		}
	}
}

int SPilEsValida ( SPila * p_pilObj )
{
	int iRes;

	if ( ES_VALIDO ( p_pilObj ) )
	{
		iRes = SLisEsValida ( p_pilObj->p_lisObjetos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SPilNumElementos ( SPila * p_pilObj )
{
	int iRes;

	if ( ES_VALIDO ( p_pilObj ) )
	{
		iRes = SLisNumElementos ( p_pilObj->p_lisObjetos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SPilEstaVacia ( SPila * p_pilObj )
{
	int iRes;

	if ( ES_VALIDO ( p_pilObj ) )
	{
		iRes = SLisEstaVacia ( p_pilObj->p_lisObjetos );
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

SElemento * SPilPrimero ( SPila * p_pilObj )
{
	SElemento * p_elmRes;

	if ( ES_VALIDO ( p_pilObj ) )
	{
		p_elmRes = SLisElemento ( p_pilObj->p_lisObjetos, 0 );
	}
	else
	{
		p_elmRes = NULL;
	}
	return ( p_elmRes );
}

SElemento * SPilDesapilar ( SPila * p_pilObj )
{
	SElemento * p_elmRes;

	if ( ES_VALIDO ( p_pilObj ) )
	{
		p_elmRes = SLisExtraerElem ( p_pilObj->p_lisObjetos, 0 );
	}
	else
	{
		p_elmRes = NULL;
	}
	return ( p_elmRes );
}

int SPilApilar ( SPila * p_pilObj, SElemento * p_elmObj )
{
	int iRes;

	if ( ( SPilEsValida ( p_pilObj ) == 1 ) && ES_VALIDO ( p_elmObj ) )
	{
		iRes = SLisInsertarAlInicio ( p_pilObj->p_lisObjetos, p_elmObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SPilEliminarPrimero ( SPila * p_pilObj )
{
	int	iRes;

	if ( SPilEsValida ( p_pilObj ) == 1 ) 
	{
		iRes = SLisEliminarElem ( p_pilObj->p_lisObjetos, 0 );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SPilVaciar ( SPila * p_pilObj )
{
	int	iRes;

	if ( SPilEsValida ( p_pilObj ) == 1 ) 
	{
		iRes = SLisVaciar ( p_pilObj->p_lisObjetos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SLista * SPilLista ( SPila * p_pilObj )
{
	SLista * p_lisRes;

	if ( ES_VALIDO ( p_pilObj ) )
	{
		p_lisRes = p_pilObj->p_lisObjetos;
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}
