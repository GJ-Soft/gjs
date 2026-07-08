#include "SPilaEnteros.h"

#include "TiposBasicosConfig.h"




SPilaEnteros * SPilEntCrear ()
{
	SPilaEnteros * p_pilObj;
	
	p_pilObj = (SPilaEnteros *) MemReservar ( sizeof ( SPilaEnteros ) );
	if ( ES_VALIDO ( p_pilObj ) )
	{
		p_pilObj->p_pilDatos = SPilCrear ();
	}
	return ( p_pilObj );
}

void SPilEntDestruir ( SPilaEnteros ** p_p_pilObj )
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

int SPilEntEsValida ( SPilaEnteros * p_pilObj )
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

int SPilEntEstaVacia ( SPilaEnteros * p_pilObj )
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

int SPilEntNumElementos ( SPilaEnteros * p_pilObj )
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

int SPilEntPrimero ( SPilaEnteros * p_pilObj )
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
			iRes = -1;
		}
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SPilEntDesapilar ( SPilaEnteros * p_pilObj )
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
			iRes = -1;
		}
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SPilEntApilar ( SPilaEnteros * p_pilObj, int iDato )
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

int SPilEntEliminarPrimero ( SPilaEnteros * p_pilObj )
{
	int iRes;

	if ( ES_VALIDO ( p_pilObj ) )
	{
		iRes = SPilEliminarPrimero ( p_pilObj->p_pilDatos );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SPilEntVaciar ( SPilaEnteros * p_pilObj )
{
	int iRes;

	if ( ES_VALIDO ( p_pilObj ) )
	{
		iRes = SPilVaciar ( p_pilObj->p_pilDatos );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

