#include "SPilaPtr.h"

#include "TiposBasicosConfig.h"


int _SPilpApilarPtr ( SPilaPtr * p_pilObj, SElementoPtr * p_elpObj );



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
		if ( SPilpEsValida ( p_pilObj ) == 1 )
		{
			ERROR_ESTABLECER_FORM ( ERR_PILA_VACIA, ERR_TXT_PILA_VACIA );
		}
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
		if ( SPilpEsValida ( p_pilObj ) == 1 )
		{
			ERROR_ESTABLECER_FORM ( ERR_PILA_VACIA, ERR_TXT_PILA_VACIA );
		}
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

/* MUEVE los nodos de p_lisValores a la pila, de la cabeza a la cola: el ultimo
   de la lista queda en la cima. p_lisValores queda vacia. Como con
   SPilpApilar, la pila no libera los datos salvo que se destruya con
   iLiberar = 1.

   Si uno no se puede apilar vuelve a la cabeza de p_lisValores y se para con
   ERR_INSERCION_LISTA: lo apilado hasta ahi se queda y lo que falta sigue en
   p_lisValores, sin perder nada. */
int SPilpApilarTodos ( SPilaPtr * p_pilObj, SListaPtr * p_lisValores )
{
	int				iRes;
	SElementoPtr *	p_elpObj;

	if ( SPilpEsValida ( p_pilObj ) == 1 )
	{
		if ( SLispEsValida ( p_lisValores ) == 1 )
		{
			iRes = 1;
			/* SLispExtraerPtr deja el cursor en el siguiente, que es la nueva cabeza. */
			SLispInicio ( p_lisValores );
			while ( ( iRes == 1 ) && ( SLispEstaPosicionada ( p_lisValores ) == 1 ) )
			{
				p_elpObj = SLispExtraerPtr ( p_lisValores );
				if ( ES_VALIDO ( p_elpObj ) )
				{
					if ( _SPilpApilarPtr ( p_pilObj, p_elpObj ) != 1 )
					{
						SLispInsertarAlInicioPtr ( p_lisValores, p_elpObj );
						ERROR_ESTABLECER_FORM ( ERR_INSERCION_LISTA, ERR_TXT_INSERCION_LISTA );
						iRes = 0;
					}
				}
				else
				{
					ERROR_ESTABLECER_FORM ( ERR_INSERCION_LISTA, ERR_TXT_INSERCION_LISTA );
					iRes = 0;
				}
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

/* Apila COPIAS de los datos de p_lisValores, de la cabeza a la cola, sin tocar
   la lista ni su cursor: con fDuplicar o, si es nulo, de iNumBytes. Las copias
   son memoria nueva y, como con SPilpApilar, la pila no las libera salvo que se
   destruya con iLiberar = 1. Si falla una copia ( ERR_COPIA_OBJETO ) o un
   apilado ( ERR_INSERCION_LISTA ) se para, y lo apilado hasta ahi se queda. */
static int _SPilpApilarTodosDup ( SPilaPtr * p_pilObj, SListaPtr * p_lisValores, int iNumBytes, PFUNPBYTEPB fDuplicar )
{
	int				iRes;
	SElementoPtr *	p_elpObj;
	SElementoPtr *	p_elpNuevo;

	if ( SPilpEsValida ( p_pilObj ) == 1 )
	{
		if ( SLispEsValida ( p_lisValores ) == 1 )
		{
			iRes = 1;
			p_elpObj = p_lisValores->p_elpPrimero;
			while ( ES_VALIDO ( p_elpObj ) && ( iRes == 1 ) )
			{
				if ( ES_VALIDO ( fDuplicar ) )
				{
					p_elpNuevo = SElpDuplicarExt ( p_elpObj, fDuplicar );
				}
				else
				{
					p_elpNuevo = SElpDuplicar ( p_elpObj, iNumBytes );
				}
				if ( ES_NULO ( p_elpNuevo ) )
				{
					ERROR_ESTABLECER ( ERR_COPIA_OBJETO );
					iRes = 0;
				}
				else if ( _SPilpApilarPtr ( p_pilObj, p_elpNuevo ) != 1 )
				{
					SElpDestruir ( &p_elpNuevo );
					ERROR_ESTABLECER_FORM ( ERR_INSERCION_LISTA, ERR_TXT_INSERCION_LISTA );
					iRes = 0;
				}
				p_elpObj = SElpSucesor ( p_elpObj );
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

int SPilpApilarTodosDup ( SPilaPtr * p_pilObj, SListaPtr * p_lisValores, int iNumBytes )
{
	return ( _SPilpApilarTodosDup ( p_pilObj, p_lisValores, iNumBytes, NULL ) );
}

int SPilpApilarTodosDupExt ( SPilaPtr * p_pilObj, SListaPtr * p_lisValores, PFUNPBYTEPB fDuplicar )
{
	int iRes;

	if ( ES_VALIDO ( fDuplicar ) )
	{
		iRes = _SPilpApilarTodosDup ( p_pilObj, p_lisValores, 0, fDuplicar );
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

int _SPilpApilarPtr ( SPilaPtr * p_pilObj, SElementoPtr * p_elpObj )
{
	int iRes;

	if ( ( SPilpEsValida ( p_pilObj ) == 1 ) && ES_VALIDO ( p_elpObj ) )
	{
		iRes = SLispInsertarAlInicioPtr ( p_pilObj->p_lisObjetos, p_elpObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}
