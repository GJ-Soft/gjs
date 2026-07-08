#include "SPilaPtr.h"

#include "TiposBasicosConfig.h"


SPilaPtr * SPilpCrear ()
{
	SPilaPtr * p_pilObj;
	
	p_pilObj = (SPilaPtr *) MemReservar ( sizeof ( SPilaPtr ) );
	if ( ES_VALIDO ( p_pilObj ) )
	{
		p_pilObj->p_lisObjetos = SLispCrear ();
		SLispDesactivarLiberacionMemoria ( p_pilObj->p_lisObjetos );
	}
	return ( p_pilObj );
}

void SPilpDestruir ( SPilaPtr ** p_p_pilObj, int iLiberar )
{
	SPilaPtr * p_pilObj;
	
	if ( ES_VALIDO ( p_p_pilObj ) )
	{
		p_pilObj = *p_p_pilObj;

		if ( ES_VALIDO ( p_pilObj ) )
		{
			if ( iLiberar == 1 )
			{
				SLispActivarLiberacionMemoria ( p_pilObj->p_lisObjetos );
			}
			SLispDestruir ( &(p_pilObj->p_lisObjetos) );
			MemLiberar ( (void **) p_p_pilObj );
		}
	}
}

int SPilpEsValida ( SPilaPtr * p_pilObj )
{
	int iRes;

	if ( ES_VALIDO ( p_pilObj ) )
	{
		iRes = SLispEsValida ( p_pilObj->p_lisObjetos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SPilpNumElementos ( SPilaPtr * p_pilObj )
{
	int iRes;

	if ( ES_VALIDO ( p_pilObj ) )
	{
		iRes = SLispNumElementos ( p_pilObj->p_lisObjetos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SPilpEstaVacia ( SPilaPtr * p_pilObj )
{
	int iRes;

	if ( ES_VALIDO ( p_pilObj ) )
	{
		iRes = SLispEstaVacia ( p_pilObj->p_lisObjetos );
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

byte * SPilpPrimero ( SPilaPtr * p_pilObj )
{
	byte * p_byRes;

	if ( SPilpEstaVacia ( p_pilObj ) == 0 )
	{
		p_byRes = SLispElemento ( p_pilObj->p_lisObjetos, 0 );
	}
	else
	{
		p_byRes = NULL;
	}
	return ( p_byRes );
}

byte * SPilpDesapilar ( SPilaPtr * p_pilObj )
{
	byte *	p_byRes;
	int		iActLib;

	if ( SPilpEstaVacia ( p_pilObj ) == 0 )
	{
		p_byRes = SLispElemento ( p_pilObj->p_lisObjetos, 0 );
		if ( ES_VALIDO ( p_byRes ) )
		{
			iActLib = SLispLiberacionMemoriaActivada ( p_pilObj->p_lisObjetos );
			SLispDesactivarLiberacionMemoria ( p_pilObj->p_lisObjetos );
			if ( SLispEliminarElem ( p_pilObj->p_lisObjetos, 0 ) == 0 )
			{
				p_byRes = NULL;
			}
			if ( iActLib == 1 )
			{
				SLispActivarLiberacionMemoria ( p_pilObj->p_lisObjetos );
			}
		}
	}
	else
	{
		p_byRes = NULL;
	}
	return ( p_byRes );
}

int SPilpApilar ( SPilaPtr * p_pilObj, byte * p_byObj )
{
	int iRes;

	if ( ( SPilpEsValida ( p_pilObj ) == 1 ) && ES_VALIDO ( p_byObj ) )
	{
		iRes = SLispInsertarAlInicio ( p_pilObj->p_lisObjetos, p_byObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SPilpEliminarPrimero ( SPilaPtr * p_pilObj )
{
	int	iRes;

	if ( SPilpEstaVacia ( p_pilObj ) == 0 )
	{
		iRes = SLispEliminarElem ( p_pilObj->p_lisObjetos, 0 );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SPilpVaciar ( SPilaPtr * p_pilObj, int iLiberar )
{
	int	iRes;

	if ( SPilpEsValida ( p_pilObj ) == 1 ) 
	{
		if ( iLiberar == 1 )
		{
			SLispActivarLiberacionMemoria ( p_pilObj->p_lisObjetos );
		}
		iRes = SLispVaciar ( p_pilObj->p_lisObjetos );
		SLispDesactivarLiberacionMemoria ( p_pilObj->p_lisObjetos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SListaPtr * SPilpLista ( SPilaPtr * p_pilObj )
{
	SListaPtr * p_lisRes;

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


int	SPilpLiberacionMemoriaActivada ( SPilaPtr * p_pilObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_pilObj ) )
	{
		iRes = SLispLiberacionMemoriaActivada ( p_pilObj->p_lisObjetos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

void SPilpActivarLiberacionMemoria ( SPilaPtr * p_pilObj )
{
	if ( ES_VALIDO ( p_pilObj ) )
	{
		SLispActivarLiberacionMemoria ( p_pilObj->p_lisObjetos );
	}
}

void SPilpDesactivarLiberacionMemoria ( SPilaPtr * p_pilObj )
{
	if ( ES_VALIDO ( p_pilObj ) )
	{
		SLispDesactivarLiberacionMemoria ( p_pilObj->p_lisObjetos );
	}
}