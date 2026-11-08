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
		if ( ES_NULO ( p_elmRes ) )
		{
			ERROR_ESTABLECER_FORM ( ERR_PILA_VACIA, ERR_TXT_PILA_VACIA );
		}
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
		if ( ES_NULO ( p_elmRes ) )
		{
			ERROR_ESTABLECER_FORM ( ERR_PILA_VACIA, ERR_TXT_PILA_VACIA );
		}
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

/* MUEVE los elementos de p_lisValores a la pila, de la cabeza a la cola: el
   ultimo de la lista queda en la cima. p_lisValores queda vacia.

   Si uno no se puede apilar vuelve a la cabeza de p_lisValores y se para con
   ERR_INSERCION_LISTA: lo apilado hasta ahi se queda y lo que falta sigue en
   p_lisValores, sin perder nada. */
int SPilApilarTodos ( SPila * p_pilObj, SLista * p_lisValores )
{
	int			iRes;
	SElemento *	p_elmObj;

	if ( SPilEsValida ( p_pilObj ) == 1 )
	{
		if ( SLisEsValida ( p_lisValores ) == 1 )
		{
			iRes = 1;
			/* SLisExtraer deja el cursor en el siguiente, que es la nueva cabeza. */
			SLisInicio ( p_lisValores );
			while ( ( iRes == 1 ) && ( SLisEstaPosicionada ( p_lisValores ) == 1 ) )
			{
				p_elmObj = SLisExtraer ( p_lisValores );
				if ( ES_VALIDO ( p_elmObj ) )
				{
					if ( SPilApilar ( p_pilObj, p_elmObj ) != 1 )
					{
						SLisInsertarAlInicio ( p_lisValores, p_elmObj );
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

/* Apila COPIAS ( SElmDuplicar ) de los elementos de p_lisValores, de la cabeza
   a la cola, sin tocar la lista ni su cursor. Si falla una copia
   ( ERR_COPIA_OBJETO ) o un apilado ( ERR_INSERCION_LISTA ) se para, y lo
   apilado hasta ahi se queda. */
int SPilApilarTodosDup ( SPila * p_pilObj, SLista * p_lisValores )
{
	int			iRes;
	SElemento *	p_elmObj;
	SElemento *	p_elmNuevo;

	if ( SPilEsValida ( p_pilObj ) == 1 )
	{
		if ( SLisEsValida ( p_lisValores ) == 1 )
		{
			iRes = 1;
			p_elmObj = p_lisValores->p_elmPrimero;
			while ( ES_VALIDO ( p_elmObj ) && ( iRes == 1 ) )
			{
				p_elmNuevo = SElmDuplicar ( p_elmObj );
				if ( ES_NULO ( p_elmNuevo ) )
				{
					ERROR_ESTABLECER ( ERR_COPIA_OBJETO );
					iRes = 0;
				}
				else if ( SPilApilar ( p_pilObj, p_elmNuevo ) != 1 )
				{
					SElmDestruir ( &p_elmNuevo );
					ERROR_ESTABLECER_FORM ( ERR_INSERCION_LISTA, ERR_TXT_INSERCION_LISTA );
					iRes = 0;
				}
				p_elmObj = SElmSucesor ( p_elmObj );
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
