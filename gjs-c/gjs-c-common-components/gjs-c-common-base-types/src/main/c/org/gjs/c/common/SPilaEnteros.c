#include "SPilaEnteros.h"

#include "TiposBasicosConfig.h"




SPilaEnteros * SPilIntCrear ()
{
	SPilaEnteros * p_pilObj;
	
	p_pilObj = (SPilaEnteros *) MemReservar ( sizeof ( SPilaEnteros ) );
	if ( ES_VALIDO ( p_pilObj ) )
	{
		p_pilObj->p_pilDatos = SPilCrear ();
	}
	return ( p_pilObj );
}

void SPilIntDestruir ( SPilaEnteros ** p_p_pilObj )
{
	SPilaEnteros * p_pilObj;
	
	if ( ES_VALIDO ( p_p_pilObj ) )
	{
		p_pilObj = *p_p_pilObj;

		if ( ES_VALIDO ( p_pilObj ) )
		{
			SPilDestruir ( &(p_pilObj->p_pilDatos) );
			MemLiberar ( (void **) p_p_pilObj );
		}
	}
}

int SPilIntEsValida ( SPilaEnteros * p_pilObj )
{
	int iRes;

	if ( ES_VALIDO ( p_pilObj ) )
	{
		iRes = SPilEsValida ( p_pilObj->p_pilDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SPilIntEstaVacia ( SPilaEnteros * p_pilObj )
{
	int iRes;

	if ( ES_VALIDO ( p_pilObj ) )
	{
		iRes = SPilEstaVacia ( p_pilObj->p_pilDatos );
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

int SPilIntNumElementos ( SPilaEnteros * p_pilObj )
{
	int iRes;

	if ( ES_VALIDO ( p_pilObj ) )
	{
		iRes = SPilNumElementos ( p_pilObj->p_pilDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SPilIntPrimero ( SPilaEnteros * p_pilObj )
{
	int			iRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_pilObj ) )
	{
		p_elmObj = SPilPrimero ( p_pilObj->p_pilDatos );
		if ( ES_VALIDO ( p_elmObj ) )
		{
			iRes = SElmEntero ( p_elmObj );
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

int SPilIntDesapilar ( SPilaEnteros * p_pilObj )
{
	int			iRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_pilObj ) )
	{
		p_elmObj = SPilDesapilar ( p_pilObj->p_pilDatos );
		if ( ES_VALIDO ( p_elmObj ) )
		{
			iRes = SElmEntero ( p_elmObj );
			SElmDestruir ( &p_elmObj );
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

int SPilIntApilar ( SPilaEnteros * p_pilObj, int iDato )
{
	int			iRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_pilObj ) )
	{
		p_elmObj = SElmCrearEntero ();
		if ( ES_VALIDO ( p_elmObj ) )
		{
			if ( SElmEscribirEntero ( p_elmObj, iDato ) == 1 )
			{
				iRes = SPilApilar ( p_pilObj->p_pilDatos, p_elmObj );
			}
			else
			{
				iRes = 0;
			}
			if ( iRes != 1 )
			{
				SElmDestruir ( &p_elmObj );
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

int SPilIntApilarTodos ( SPilaEnteros * p_pilObj, SListaEnteros * p_lisValores )
{
	int iRes;

	if ( ES_VALIDO ( p_pilObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			iRes = SPilApilarTodos ( p_pilObj->p_pilDatos, p_lisValores->p_lisDatos );
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

int SPilIntApilarTodosDup ( SPilaEnteros * p_pilObj, SListaEnteros * p_lisValores )
{
	int iRes;

	if ( ES_VALIDO ( p_pilObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			iRes = SPilApilarTodosDup ( p_pilObj->p_pilDatos, p_lisValores->p_lisDatos );
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

int SPilIntEliminarPrimero ( SPilaEnteros * p_pilObj )
{
	int iRes;

	if ( ES_VALIDO ( p_pilObj ) )
	{
		iRes = SPilEliminarPrimero ( p_pilObj->p_pilDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SPilIntVaciar ( SPilaEnteros * p_pilObj )
{
	int iRes;

	if ( ES_VALIDO ( p_pilObj ) )
	{
		iRes = SPilVaciar ( p_pilObj->p_pilDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

