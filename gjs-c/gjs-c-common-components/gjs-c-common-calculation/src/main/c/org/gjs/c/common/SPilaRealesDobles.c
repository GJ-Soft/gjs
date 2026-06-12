#include "SPilaRealesDobles.h"

#include "CalculoConfig.h"
#include "CalculoOperaciones.h"



SPilaRealesDobles * SPilRealdCrear ()
{
	SPilaRealesDobles * p_pilObj;
	
	p_pilObj = (SPilaRealesDobles *) MemReservar ( sizeof ( SPilaRealesDobles ) );
	if ( ES_VALIDO ( p_pilObj ) )
	{
		p_pilObj->p_pilDatos = SPilCrear ();
	}
	return ( p_pilObj );
}

void SPilRealdDestruir ( SPilaRealesDobles ** p_p_pilObj )
{
	SPilaRealesDobles * p_pilObj;
	
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

int SPilRealdEsValida ( SPilaRealesDobles * p_pilObj )
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

int SPilRealdEstaVacia ( SPilaRealesDobles * p_pilObj )
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

int SPilRealdNumElementos ( SPilaRealesDobles * p_pilObj )
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

double SPilRealdPrimero ( SPilaRealesDobles * p_pilObj )
{
	double		dRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_pilObj ) )
	{
		p_elmObj = SPilPrimero ( p_pilObj->p_pilDatos );
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

double SPilRealdDesapilar ( SPilaRealesDobles * p_pilObj )
{
	double		dRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_pilObj ) )
	{
		p_elmObj = SPilDesapilar ( p_pilObj->p_pilDatos );
		if ( ES_VALIDO ( p_elmObj ) )
		{
			dRes = SElmRealDoble ( p_elmObj );
			SElmDestruir ( &p_elmObj );
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

int SPilRealdApilar ( SPilaRealesDobles * p_pilObj, double dDato )
{
	int			iRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_pilObj ) )
	{
		p_elmObj = SElmCrearRealDoble ();
		if ( ES_VALIDO ( p_elmObj ) )
		{
			if ( SElmEscribirRealDoble ( p_elmObj, dDato ) == 1 )
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

int SPilRealdEliminarPrimero ( SPilaRealesDobles * p_pilObj )
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

int SPilRealdVaciar ( SPilaRealesDobles * p_pilObj )
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

