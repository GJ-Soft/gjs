#include "SColaPtr.h"


#include "TiposBasicosConfig.h"




SColaPtr * SColpCrear ()
{
	SColaPtr * p_colObj;
	
	p_colObj = (SColaPtr *) MemReservar ( sizeof ( SColaPtr ) );
	if ( ES_VALIDO ( p_colObj ) )
	{
		p_colObj->p_lisObjetos = SLispCrear ();
		SLispDesactivarLiberacionMemoria ( p_colObj->p_lisObjetos );
	}
	return ( p_colObj );
}

void SColpDestruir ( SColaPtr ** p_p_colObj, int iLiberar )
{
	SColaPtr * p_colObj;
	
	if ( ES_VALIDO ( p_p_colObj ) )
	{
		p_colObj = *p_p_colObj;

		if ( ES_VALIDO ( p_colObj ) )
		{
			if ( iLiberar == 1 )
			{
				SLispActivarLiberacionMemoria ( p_colObj->p_lisObjetos );
			}
			SLispDestruir ( &(p_colObj->p_lisObjetos) );
			MemLiberar ( (void **) p_p_colObj );
		}
	}
}

int SColpEsValida ( SColaPtr * p_colObj )
{
	int iRes;

	if ( ES_VALIDO ( p_colObj ) )
	{
		iRes = SLispEsValida ( p_colObj->p_lisObjetos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SColpNumElementos ( SColaPtr * p_colObj )
{
	int iRes;

	if ( ES_VALIDO ( p_colObj ) )
	{
		iRes = SLispNumElementos ( p_colObj->p_lisObjetos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SColpEstaVacia ( SColaPtr * p_colObj )
{
	int iRes;

	if ( ES_VALIDO ( p_colObj ) )
	{
		iRes = SLispEstaVacia ( p_colObj->p_lisObjetos );
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

byte * SColpPrimero ( SColaPtr * p_colObj )
{
	byte * p_bymRes;

	if ( SColpEstaVacia ( p_colObj ) == 0 )
	{
		p_bymRes = SLispElemento ( p_colObj->p_lisObjetos, 0 );
	}
	else
	{
		p_bymRes = NULL;
	}
	return ( p_bymRes );
}

byte * SColpUltimo ( SColaPtr * p_colObj )
{
	byte * p_bymRes;

	if ( SColpEstaVacia ( p_colObj ) == 0 )
	{
		p_bymRes = SLispElemento ( p_colObj->p_lisObjetos, 
								  SLispNumElementos ( p_colObj->p_lisObjetos ) - 1 );
	}
	else
	{
		p_bymRes = NULL;
	}
	return ( p_bymRes );
}

byte * SColpElemento ( SColaPtr * p_colObj, int iElem )
{
	byte * p_bymRes;

	if ( SColpEstaVacia ( p_colObj ) == 0 )
	{
		p_bymRes = SLispElemento ( p_colObj->p_lisObjetos, iElem );
	}
	else
	{
		p_bymRes = NULL;
	}
	return ( p_bymRes );
}

byte * SColpDesencolar ( SColaPtr * p_colObj )
{
	byte *	p_bymRes;
	int		iActLib;

	if ( SColpEstaVacia ( p_colObj ) == 0 )
	{
		p_bymRes = SLispElemento ( p_colObj->p_lisObjetos, 0 );
		if ( ES_VALIDO ( p_bymRes ) )
		{
			/* Se desactiva la liberacion para que al eliminar no se libere el dato devuelto. */
			iActLib = SLispLiberacionMemoriaActivada ( p_colObj->p_lisObjetos );
			SLispDesactivarLiberacionMemoria ( p_colObj->p_lisObjetos );
			if ( SLispEliminarElem ( p_colObj->p_lisObjetos, 0 ) == 0 )
			{
				p_bymRes = NULL;
			}
			if ( iActLib == 1 )
			{
				SLispActivarLiberacionMemoria ( p_colObj->p_lisObjetos );
			}
		}
	}
	else
	{
		p_bymRes = NULL;
	}
	return ( p_bymRes );
}

int SColpEncolar ( SColaPtr * p_colObj, byte * p_bymObj )
{
	int iRes;

	if ( ( SColpEsValida ( p_colObj ) == 1 ) && ES_VALIDO ( p_bymObj ) )
	{
		iRes = SLispInsertarAlFinal ( p_colObj->p_lisObjetos, p_bymObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SColpEliminarPrimero ( SColaPtr * p_colObj )
{
	int	iRes;

	if ( SColpEstaVacia ( p_colObj ) == 0 )
	{
		iRes = SLispEliminarElem ( p_colObj->p_lisObjetos, 0 );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SColpEliminarUltimo ( SColaPtr * p_colObj )
{
	int	iRes;

	if ( SColpEstaVacia ( p_colObj ) == 0 )
	{
		iRes = SLispEliminarElem ( p_colObj->p_lisObjetos, 
								  SLispNumElementos ( p_colObj->p_lisObjetos ) - 1 );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SColpEliminar ( SColaPtr * p_colObj, int iElem )
{
	int	iRes;

	if ( SColpEstaVacia ( p_colObj ) == 0 )
	{
		iRes = SLispEliminarElem ( p_colObj->p_lisObjetos, iElem );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SColpVaciar ( SColaPtr * p_colObj, int iLiberar )
{
	int	iRes;

	if ( SColpEstaVacia ( p_colObj ) == 0 )
	{
		if ( iLiberar == 1 )
		{
			SLispActivarLiberacionMemoria ( p_colObj->p_lisObjetos );
		}
		iRes = SLispVaciar ( p_colObj->p_lisObjetos );
		SLispDesactivarLiberacionMemoria ( p_colObj->p_lisObjetos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SListaPtr * SColpLista ( SColaPtr * p_colObj )
{
	SListaPtr * p_lisRes;

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


int	SColpLiberacionMemoriaActivada ( SColaPtr * p_colObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_colObj ) )
	{
		iRes = SLispLiberacionMemoriaActivada ( p_colObj->p_lisObjetos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

void SColpActivarLiberacionMemoria ( SColaPtr * p_colObj )
{
	if ( ES_VALIDO ( p_colObj ) )
	{
		SLispActivarLiberacionMemoria ( p_colObj->p_lisObjetos );
	}
}

void SColpDesactivarLiberacionMemoria ( SColaPtr * p_colObj )
{
	if ( ES_VALIDO ( p_colObj ) )
	{
		SLispDesactivarLiberacionMemoria ( p_colObj->p_lisObjetos );
	}
}