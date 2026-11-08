#include "SColaPtr.h"


#include "TiposBasicosConfig.h"


int _SColpEncolarPtr ( SColaPtr * p_colObj, SElementoPtr * p_elpObj );

extern SElementoPtr * _SLispExtraerPtr ( SListaPtr * p_lisObj );
extern int _SLispInsertarAlInicioPtr ( SListaPtr * p_lisObj, SElementoPtr * p_elpDatos );
extern int _SLispInsertarAlFinalPtr ( SListaPtr * p_lisObj, SElementoPtr * p_elpDatos );



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

/* MUEVE los nodos de p_lisValores al final de la cola, de la cabeza a la cola
   de la lista, asi que salen en el mismo orden. p_lisValores queda vacia. Como
   con SColpEncolar, la cola no libera los datos salvo que se destruya con
   iLiberar = 1.

   Si uno no se puede encolar vuelve a la cabeza de p_lisValores y se para con
   ERR_INSERCION_LISTA: lo encolado hasta ahi se queda y lo que falta sigue en
   p_lisValores, sin perder nada. */
int SColpEncolarTodos ( SColaPtr * p_colObj, SListaPtr * p_lisValores )
{
	int				iRes;
	SElementoPtr *	p_elpObj;

	if ( SColpEsValida ( p_colObj ) == 1 )
	{
		if ( SLispEsValida ( p_lisValores ) == 1 )
		{
			iRes = 1;
			/* _SLispExtraerPtr deja el cursor en el siguiente, que es la nueva cabeza. */
			SLispInicio ( p_lisValores );
			while ( ( iRes == 1 ) && ( SLispEstaPosicionada ( p_lisValores ) == 1 ) )
			{
				p_elpObj = _SLispExtraerPtr ( p_lisValores );
				if ( ES_VALIDO ( p_elpObj ) )
				{
					if ( _SColpEncolarPtr ( p_colObj, p_elpObj ) != 1 )
					{
						_SLispInsertarAlInicioPtr ( p_lisValores, p_elpObj );
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

/* Encola COPIAS de los datos de p_lisValores, en su orden, sin tocar la lista
   ni su cursor: con fDuplicar o, si es nulo, de iNumBytes. Las copias son
   memoria nueva y, como con SColpEncolar, la cola no las libera salvo que se
   destruya con iLiberar = 1. Si falla una copia ( ERR_COPIA_OBJETO ) o un
   encolado ( ERR_INSERCION_LISTA ) se para, y lo encolado hasta ahi se queda. */
static int _SColpEncolarTodosDup ( SColaPtr * p_colObj, SListaPtr * p_lisValores, int iNumBytes, PFUNPBYTEPB fDuplicar )
{
	int				iRes;
	SElementoPtr *	p_elpObj;
	SElementoPtr *	p_elpNuevo;

	if ( SColpEsValida ( p_colObj ) == 1 )
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
				else if ( _SColpEncolarPtr ( p_colObj, p_elpNuevo ) != 1 )
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

int SColpEncolarTodosDup ( SColaPtr * p_colObj, SListaPtr * p_lisValores, int iNumBytes )
{
	return ( _SColpEncolarTodosDup ( p_colObj, p_lisValores, iNumBytes, NULL ) );
}

int SColpEncolarTodosDupExt ( SColaPtr * p_colObj, SListaPtr * p_lisValores, PFUNPBYTEPB fDuplicar )
{
	int iRes;

	if ( ES_VALIDO ( fDuplicar ) )
	{
		iRes = _SColpEncolarTodosDup ( p_colObj, p_lisValores, 0, fDuplicar );
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


int _SColpEncolarPtr ( SColaPtr * p_colObj, SElementoPtr * p_elpObj )
{
	int iRes;

	if ( ( SColpEsValida ( p_colObj ) == 1 ) && ES_VALIDO ( p_elpObj ) )
	{
		iRes = _SLispInsertarAlFinalPtr ( p_colObj->p_lisObjetos, p_elpObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}
