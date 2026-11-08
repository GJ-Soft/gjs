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

/* MUEVE los elementos de p_lisValores al final de la cola, de la cabeza a la
   cola de la lista, asi que salen en el mismo orden. p_lisValores queda vacia.

   Si uno no se puede encolar vuelve a la cabeza de p_lisValores y se para con
   ERR_INSERCION_LISTA: lo encolado hasta ahi se queda y lo que falta sigue en
   p_lisValores, sin perder nada. */
int SColEncolarTodos ( SCola * p_colObj, SLista * p_lisValores )
{
	int			iRes;
	SElemento *	p_elmObj;

	if ( SColEsValida ( p_colObj ) == 1 )
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
					if ( SColEncolar ( p_colObj, p_elmObj ) != 1 )
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

/* Encola COPIAS ( SElmDuplicar ) de los elementos de p_lisValores, en su orden,
   sin tocar la lista ni su cursor. Si falla una copia ( ERR_COPIA_OBJETO ) o un
   encolado ( ERR_INSERCION_LISTA ) se para, y lo encolado hasta ahi se queda. */
int SColEncolarTodosDup ( SCola * p_colObj, SLista * p_lisValores )
{
	int			iRes;
	SElemento *	p_elmObj;
	SElemento *	p_elmNuevo;

	if ( SColEsValida ( p_colObj ) == 1 )
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
				else if ( SColEncolar ( p_colObj, p_elmNuevo ) != 1 )
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
