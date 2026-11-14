#include "SConjunto.h"


#include "TiposBasicosConfig.h"





/* 1 si en p_lisObj hay dos elementos iguales segun su comparador. Como estan
   ordenados, basta con comparar cada uno con el anterior. */
static int _SCnjTieneRepetidos ( SListaOrdenada * p_lisObj )
{
	SElemento *	p_elmAnt;
	SElemento *	p_elmObj;
	int			iRes;

	iRes = 0;
	p_elmAnt = p_lisObj->p_lisContenido->p_elmPrimero;
	if ( ES_VALIDO ( p_elmAnt ) )
	{
		p_elmObj = SElmSucesor ( p_elmAnt );
		while ( ES_VALIDO ( p_elmObj ) && ( iRes == 0 ) )
		{
			if ( SCmpEvaluarBloqueEsIgual ( p_lisObj->p_cmpObj, SElmDatos ( p_elmAnt ), SElmDatos ( p_elmObj ) ) == 1 )
			{
				iRes = 1;
			}
			p_elmAnt = p_elmObj;
			p_elmObj = SElmSucesor ( p_elmObj );
		}
	}
	return ( iRes );
}

/* Inserta en p_cnjObj copias ( SElmDuplicar ) de los valores de la cadena que
   empieza en p_elmPrimero que no esten ya: un valor que ya esta, o que se
   repite en la cadena, entra una sola vez. Devuelve 1, o 0 si falla una copia
   o una insercion; lo insertado hasta ahi se queda. */
static int _SCnjInsertarCopias ( SConjunto * p_cnjObj, SElemento * p_elmPrimero )
{
	SElemento *	p_elmObj;
	SElemento *	p_elmNuevo;
	int			iRes;

	iRes = 1;
	p_elmObj = p_elmPrimero;
	while ( ES_VALIDO ( p_elmObj ) && ( iRes == 1 ) )
	{
		if ( SCnjExiste ( p_cnjObj, SElmDatos ( p_elmObj ) ) == 0 )
		{
			p_elmNuevo = SElmDuplicar ( p_elmObj );
			if ( ES_NULO ( p_elmNuevo ) )
			{
				ERROR_ESTABLECER ( ERR_COPIA_OBJETO );
				iRes = 0;
			}
			else if ( SLisOrdInsertarElem ( p_cnjObj->p_lisContenido, p_elmNuevo ) != 1 )
			{
				SElmDestruir ( &p_elmNuevo );
				ERROR_ESTABLECER_FORM ( ERR_INSERCION_LISTA, ERR_TXT_INSERCION_LISTA );
				iRes = 0;
			}
		}
		p_elmObj = SElmSucesor ( p_elmObj );
	}
	return ( iRes );
}

/* Envuelve en un conjunto una lista ordenada recien creada, o la destruye si
   no se puede: nunca se pierde ni se devuelve un conjunto sin lista. */
static SConjunto * _SCnjEnvolver ( SListaOrdenada * p_lisObj )
{
	SConjunto * p_cnjRes;

	p_cnjRes = SCnjEncapsularLista ( p_lisObj );
	if ( ES_NULO ( p_cnjRes ) )
	{
		SLisOrdDestruir ( &p_lisObj );
	}
	return ( p_cnjRes );
}

/* Saca un conjunto de lo que haya extraido una de las Extraer de la lista
   ordenada. Si no se puede crear, lo extraido vuelve a p_cnjObj. */
static SConjunto * _SCnjEnvolverExtraidos ( SConjunto * p_cnjObj, SListaOrdenada * p_lisExt )
{
	SConjunto * p_cnjRes;

	p_cnjRes = SCnjEncapsularLista ( p_lisExt );
	if ( ES_NULO ( p_cnjRes ) )
	{
		SLisOrdInsertarListaOrd ( p_cnjObj->p_lisContenido, p_lisExt );
		SLisOrdDestruir ( &p_lisExt );
	}
	return ( p_cnjRes );
}



SConjunto * SCnjCrear ( PFUNINTPVPV fComparar )
{
	SConjunto * p_cnjObj;
	
	p_cnjObj = (SConjunto *) MemReservar ( sizeof ( SConjunto ) );
	if ( ES_VALIDO ( p_cnjObj ) )
	{
		p_cnjObj->p_lisContenido = SLisOrdCrear ( fComparar );
	}
	return ( p_cnjObj );
}

/* Conjunto nuevo, ordenado con fComparar, con copias de los valores distintos
   de p_lisValores: los repetidos entran una vez. Si falla una copia, NULL. */
SConjunto * SCnjCrearDesdeLista ( SLista * p_lisValores, PFUNINTPVPV fComparar )
{
	SConjunto *	p_cnjObj;

	if ( SLisEsValida ( p_lisValores ) == 1 )
	{
		p_cnjObj = SCnjCrear ( fComparar );
		if ( SCnjEsValido ( p_cnjObj ) == 1 )
		{
			if ( _SCnjInsertarCopias ( p_cnjObj, p_lisValores->p_elmPrimero ) != 1 )
			{
				SCnjDestruir ( &p_cnjObj );
			}
		}
		else
		{
			SCnjDestruir ( &p_cnjObj );
		}
	}
	else
	{
		p_cnjObj = NULL;
	}
	return ( p_cnjObj );
}

/* El conjunto se queda con p_lisValores, sin copiarla, y la destruye al
   destruirse. Si la lista tiene valores repetidos no es un conjunto: NULL, y
   la lista sigue siendo del llamante. */
SConjunto * SCnjEncapsularLista ( SListaOrdenada * p_lisValores )
{
	SConjunto * p_cnjObj;

	if ( SLisOrdEsValida ( p_lisValores ) == 1 )
	{
		if ( _SCnjTieneRepetidos ( p_lisValores ) == 0 )
		{
			p_cnjObj = (SConjunto *) MemReservar ( sizeof ( SConjunto ) );
			if ( ES_VALIDO ( p_cnjObj ) )
			{
				p_cnjObj->p_lisContenido = p_lisValores;
			}
		}
		else
		{
			p_cnjObj = NULL;
		}
	}
	else
	{
		p_cnjObj = NULL;
	}
	return ( p_cnjObj );
}

void SCnjDestruir ( SConjunto ** p_p_cnjObj )
{
	SConjunto * p_cnjObj;
	
	if ( ES_VALIDO ( p_p_cnjObj ) )
	{
		p_cnjObj = *p_p_cnjObj;

		if ( ES_VALIDO ( p_cnjObj ) )
		{
			SLisOrdDestruir ( &(p_cnjObj->p_lisContenido) );
			MemLiberar ( (void **) p_p_cnjObj );
		}
	}
}

int SCnjEsValido ( SConjunto * p_cnjObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		if ( SLisOrdEsValida ( p_cnjObj->p_lisContenido ) == 1 )
		{
			iRes = 1;
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

int SCnjNumElementos ( SConjunto * p_cnjObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		iRes = SLisOrdNumElementos ( p_cnjObj->p_lisContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCnjEstaVacio ( SConjunto * p_cnjObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		iRes = SLisOrdEstaVacia ( p_cnjObj->p_lisContenido );
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

SElemento * SCnjElemento ( SConjunto * p_cnjObj, int iElem )
{
	SElemento * p_elmRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		p_elmRes = SLisOrdElemento ( p_cnjObj->p_lisContenido, iElem );
	}
	else
	{
		p_elmRes = NULL;
	}
	return ( p_elmRes );
}

SElemento * SCnjPrimero ( SConjunto * p_cnjObj )
{
	SElemento * p_elmRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		p_elmRes = SLisOrdElemento ( p_cnjObj->p_lisContenido, 0 );
	}
	else
	{
		p_elmRes = NULL;
	}
	return ( p_elmRes );
}

SElemento * SCnjUltimo ( SConjunto * p_cnjObj )
{
	SElemento * p_elmRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		p_elmRes = SLisOrdElemento ( p_cnjObj->p_lisContenido, SCnjNumElementos ( p_cnjObj ) - 1 );
	}
	else
	{
		p_elmRes = NULL;
	}
	return ( p_elmRes );
}

int SCnjPosicion ( SConjunto * p_cnjObj, SElemento * p_elmObj )
{
	int iRes;

	if ( ES_VALIDO ( p_elmObj ) )
	{
		iRes = SCnjBuscar ( p_cnjObj, SElmDatos ( p_elmObj ) );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SCnjInsertarElem ( SConjunto * p_cnjObj, SElemento * p_elmObj )
{
	int iRes;

	if ( ( SCnjEsValido ( p_cnjObj ) == 1 ) && ( SElmEsValido ( p_elmObj ) == 1 ) )
	{
		if ( SCnjExiste ( p_cnjObj, SElmDatos ( p_elmObj ) ) == 0 )
		{
			iRes = SLisOrdInsertarElem ( p_cnjObj->p_lisContenido, p_elmObj );
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

int SCnjEliminarElem ( SConjunto * p_cnjObj, int iElem )
{
	int	iRes;

	if ( SCnjEsValido ( p_cnjObj ) == 1 ) 
	{
		iRes = SLisOrdEliminarElem ( p_cnjObj->p_lisContenido, iElem );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SElemento * SCnjExtraerElem ( SConjunto * p_cnjObj, int iElem )
{
	SElemento * p_elmRes;

	if ( SCnjEsValido ( p_cnjObj ) == 1 ) 
	{
		p_elmRes = SLisOrdExtraerElem ( p_cnjObj->p_lisContenido, iElem );
	}
	else
	{
		p_elmRes = NULL;
	}
	return ( p_elmRes );
}

int SCnjVaciar ( SConjunto * p_cnjObj )
{
	int	iRes;

	if ( SCnjEsValido ( p_cnjObj ) == 1 ) 
	{
		iRes = SLisOrdVaciar ( p_cnjObj->p_lisContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCnjExiste ( SConjunto * p_cnjObj, SBloque * p_blqDatos )
{
	int iRes;

	if ( SCnjEsValido ( p_cnjObj ) == 1 )
	{
		if ( SLisOrdBuscar ( p_cnjObj->p_lisContenido, p_blqDatos ) >= 0 )
		{
			iRes = 1;
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

int SCnjExisteExt ( SConjunto * p_cnjObj, byte * p_byDatos )
{
	int iRes;

	if ( SCnjEsValido ( p_cnjObj ) == 1 )
	{
		if ( SLisOrdBuscarExt ( p_cnjObj->p_lisContenido, p_byDatos ) >= 0 )
		{
			iRes = 1;
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

int SCnjBuscar ( SConjunto * p_cnjObj, SBloque * p_blqDatos )
{
	int iRes;

	if ( SCnjEsValido ( p_cnjObj ) == 1 )
	{
		iRes = SLisOrdBuscar ( p_cnjObj->p_lisContenido, p_blqDatos );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SCnjBuscarExt ( SConjunto * p_cnjObj, byte * p_byDatos )
{
	int	iRes;

	if ( SCnjEsValido ( p_cnjObj ) == 1 )
	{
		iRes = SLisOrdBuscarExt ( p_cnjObj->p_lisContenido, p_byDatos );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

SElemento * SCnjBuscarElem ( SConjunto * p_cnjObj, SBloque * p_blqDatos )
{
	SElemento * p_elmRes;
	int			iElem;

	if ( SCnjEsValido ( p_cnjObj ) == 1 )
	{
		iElem = SLisOrdBuscar ( p_cnjObj->p_lisContenido, p_blqDatos );
		if ( iElem >= 0 )
		{
			p_elmRes = SLisOrdElemento ( p_cnjObj->p_lisContenido, iElem );
		}
		else
		{
			p_elmRes = NULL;
		}
	}
	else
	{
		p_elmRes = NULL;
	}
	return ( p_elmRes );
}

SElemento * SCnjBuscarElemExt ( SConjunto * p_cnjObj, byte * p_byDatos )
{
	SElemento * p_elmRes;
	int			iElem;

	if ( SCnjEsValido ( p_cnjObj ) == 1 )
	{
		iElem = SLisOrdBuscarExt ( p_cnjObj->p_lisContenido, p_byDatos );
		if ( iElem >= 0 )
		{
			p_elmRes = SLisOrdElemento ( p_cnjObj->p_lisContenido, iElem );
		}
		else
		{
			p_elmRes = NULL;
		}
	}
	else
	{
		p_elmRes = NULL;
	}
	return ( p_elmRes );
}

/* La lista ordenada de dentro: sigue siendo del conjunto. */
SListaOrdenada * SCnjLista ( SConjunto * p_cnjObj )
{
	SListaOrdenada * p_lisRes;

	if ( SCnjEsValido ( p_cnjObj ) == 1 )
	{
		p_lisRes = p_cnjObj->p_lisContenido;
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

/* Conjunto nuevo con copias de los valores y una copia del comparador. */
SConjunto * SCnjDuplicar ( SConjunto * p_cnjObj )
{
	SConjunto * p_cnjRes;

	if ( SCnjEsValido ( p_cnjObj ) == 1 )
	{
		p_cnjRes = _SCnjEnvolver ( SLisOrdDuplicar ( p_cnjObj->p_lisContenido ) );
	}
	else
	{
		p_cnjRes = NULL;
	}
	return ( p_cnjRes );
}

/* Las operaciones con otros conjuntos y listas delegan en las de
   SListaOrdenada, con su misma semantica ( ver Listas.md ): la igualdad la
   decide el comparador del conjunto. Las de Conjunto pasan la lista del
   segundo. Las que crean un conjunto nuevo devuelven NULL si la de la lista
   falla, nunca un conjunto sin lista. */
int SCnjExistenTodos ( SConjunto * p_cnjObj, SConjunto * p_cnjValores )
{
	int iRes;

	if ( SCnjEsValido ( p_cnjValores ) == 1 )
	{
		iRes = SCnjExistenTodosListaOrd ( p_cnjObj, p_cnjValores->p_lisContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCnjExisteAlguno ( SConjunto * p_cnjObj, SConjunto * p_cnjValores )
{
	int iRes;

	if ( SCnjEsValido ( p_cnjValores ) == 1 )
	{
		iRes = SCnjExisteAlgunoListaOrd ( p_cnjObj, p_cnjValores->p_lisContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCnjExistenTodosListaOrd ( SConjunto * p_cnjObj, SListaOrdenada * p_lisValores )
{
	int	iRes;

	if ( SCnjEsValido ( p_cnjObj ) == 1 )
	{
		iRes = SLisOrdExistenTodos ( p_cnjObj->p_lisContenido, p_lisValores );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCnjExisteAlgunoListaOrd ( SConjunto * p_cnjObj, SListaOrdenada * p_lisValores )
{
	int iRes;

	if ( SCnjEsValido ( p_cnjObj ) == 1 )
	{
		iRes = SLisOrdExisteAlguno ( p_cnjObj->p_lisContenido, p_lisValores );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCnjExistenTodosLista ( SConjunto * p_cnjObj, SLista * p_lisValores )
{
	int	iRes;

	if ( SCnjEsValido ( p_cnjObj ) == 1 )
	{
		iRes = SLisOrdExistenTodosLista ( p_cnjObj->p_lisContenido, p_lisValores );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCnjExisteAlgunoLista ( SConjunto * p_cnjObj, SLista * p_lisValores )
{
	int iRes;

	if ( SCnjEsValido ( p_cnjObj ) == 1 )
	{
		iRes = SLisOrdExisteAlgunoLista ( p_cnjObj->p_lisContenido, p_lisValores );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

/* Las Insertar meten COPIAS de los valores que no esten ya en el conjunto;
   los demas se ignoran. Devuelven 1, o 0 si falla una copia o una insercion
   ( lo insertado hasta ahi se queda ). Los valores no se tocan. */
int SCnjInsertarConjunto ( SConjunto * p_cnjObj, SConjunto * p_cnjValores )
{
	int iRes;

	if ( SCnjEsValido ( p_cnjValores ) == 1 )
	{
		iRes = SCnjInsertarListaOrd ( p_cnjObj, p_cnjValores->p_lisContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCnjInsertarListaOrd ( SConjunto * p_cnjObj, SListaOrdenada * p_lisValores )
{
	int iRes;

	if ( SLisOrdEsValida ( p_lisValores ) == 1 )
	{
		iRes = SCnjInsertarLista ( p_cnjObj, p_lisValores->p_lisContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCnjInsertarLista ( SConjunto * p_cnjObj, SLista * p_lisValores )
{
	int iRes;

	if ( SCnjEsValido ( p_cnjObj ) == 1 )
	{
		if ( SLisEsValida ( p_lisValores ) == 1 )
		{
			iRes = _SCnjInsertarCopias ( p_cnjObj, p_lisValores->p_elmPrimero );
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

int SCnjEliminarConjunto ( SConjunto * p_cnjObj, SConjunto * p_cnjValores )
{
	int	iRes;

	if ( SCnjEsValido ( p_cnjValores ) == 1 )
	{
		iRes = SCnjEliminarListaOrd ( p_cnjObj, p_cnjValores->p_lisContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCnjEliminarListaOrd ( SConjunto * p_cnjObj, SListaOrdenada * p_lisValores )
{
	int iRes;

	if ( SCnjEsValido ( p_cnjObj ) == 1 )
	{
		iRes = SLisOrdEliminarListaOrd ( p_cnjObj->p_lisContenido, p_lisValores );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCnjEliminarLista ( SConjunto * p_cnjObj, SLista * p_lisValores )
{
	int iRes;

	if ( SCnjEsValido ( p_cnjObj ) == 1 )
	{
		iRes = SLisOrdEliminarLista ( p_cnjObj->p_lisContenido, p_lisValores );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

/* Las Extraer MUEVEN los elementos a un conjunto nuevo con una copia del
   comparador. Si no se puede crear el conjunto, lo extraido vuelve a
   p_cnjObj y se devuelve NULL. */
SConjunto * SCnjExtraerConjunto ( SConjunto * p_cnjObj, SConjunto * p_cnjValores )
{
	SConjunto *	p_cnjRes;

	if ( SCnjEsValido ( p_cnjValores ) == 1 )
	{
		p_cnjRes = SCnjExtraerListaOrd ( p_cnjObj, p_cnjValores->p_lisContenido );
	}
	else
	{
		p_cnjRes = NULL;
	}
	return ( p_cnjRes );
}

SConjunto * SCnjExtraerListaOrd ( SConjunto * p_cnjObj, SListaOrdenada * p_lisValores )
{
	SConjunto *	p_cnjRes;

	if ( SCnjEsValido ( p_cnjObj ) == 1 )
	{
		p_cnjRes = _SCnjEnvolverExtraidos ( p_cnjObj, SLisOrdExtraerListaOrd ( p_cnjObj->p_lisContenido, p_lisValores ) );
	}
	else
	{
		p_cnjRes = NULL;
	}
	return ( p_cnjRes );
}

SConjunto * SCnjExtraerLista ( SConjunto * p_cnjObj, SLista * p_lisValores )
{
	SConjunto *	p_cnjRes;

	if ( SCnjEsValido ( p_cnjObj ) == 1 )
	{
		p_cnjRes = _SCnjEnvolverExtraidos ( p_cnjObj, SLisOrdExtraerLista ( p_cnjObj->p_lisContenido, p_lisValores ) );
	}
	else
	{
		p_cnjRes = NULL;
	}
	return ( p_cnjRes );
}

/* Union, Interseccion y Diferencia crean un conjunto nuevo con COPIAS y una
   copia del comparador del primero; si algo falla, NULL. La union es la de
   conjuntos: lo que esta en los dos sale una vez. */
SConjunto * SCnjUnion ( SConjunto * p_cnjValores1, SConjunto * p_cnjValores2 )
{
	SConjunto *	p_cnjRes;

	if ( SCnjEsValido ( p_cnjValores2 ) == 1 )
	{
		p_cnjRes = SCnjUnionListaOrd ( p_cnjValores1, p_cnjValores2->p_lisContenido );
	}
	else
	{
		p_cnjRes = NULL;
	}
	return ( p_cnjRes );
}

SConjunto * SCnjInterseccion ( SConjunto * p_cnjValores1, SConjunto * p_cnjValores2 )
{
	SConjunto *	p_cnjRes;

	if ( SCnjEsValido ( p_cnjValores2 ) == 1 )
	{
		p_cnjRes = SCnjInterseccionListaOrd ( p_cnjValores1, p_cnjValores2->p_lisContenido );
	}
	else
	{
		p_cnjRes = NULL;
	}
	return ( p_cnjRes );
}

SConjunto * SCnjDiferencia ( SConjunto * p_cnjValores1, SConjunto * p_cnjValores2 )
{
	SConjunto *	p_cnjRes;

	if ( SCnjEsValido ( p_cnjValores2 ) == 1 )
	{
		p_cnjRes = SCnjDiferenciaListaOrd ( p_cnjValores1, p_cnjValores2->p_lisContenido );
	}
	else
	{
		p_cnjRes = NULL;
	}
	return ( p_cnjRes );
}

SConjunto * SCnjUnionListaOrd ( SConjunto * p_cnjValores1, SListaOrdenada * p_lisValores2 )
{
	SConjunto *	p_cnjRes;

	if ( SLisOrdEsValida ( p_lisValores2 ) == 1 )
	{
		p_cnjRes = SCnjUnionLista ( p_cnjValores1, p_lisValores2->p_lisContenido );
	}
	else
	{
		p_cnjRes = NULL;
	}
	return ( p_cnjRes );
}

SConjunto * SCnjInterseccionListaOrd ( SConjunto * p_cnjValores1, SListaOrdenada * p_lisValores2 )
{
	SConjunto *	p_cnjRes;

	if ( SCnjEsValido ( p_cnjValores1 ) == 1 )
	{
		p_cnjRes = _SCnjEnvolver ( SLisOrdInterseccion ( p_cnjValores1->p_lisContenido, p_lisValores2 ) );
	}
	else
	{
		p_cnjRes = NULL;
	}
	return ( p_cnjRes );
}

SConjunto * SCnjDiferenciaListaOrd ( SConjunto * p_cnjValores1, SListaOrdenada * p_lisValores2 )
{
	SConjunto *	p_cnjRes;

	if ( SCnjEsValido ( p_cnjValores1 ) == 1 )
	{
		p_cnjRes = _SCnjEnvolver ( SLisOrdDiferencia ( p_cnjValores1->p_lisContenido, p_lisValores2 ) );
	}
	else
	{
		p_cnjRes = NULL;
	}
	return ( p_cnjRes );
}

SConjunto * SCnjUnionLista ( SConjunto * p_cnjValores1, SLista * p_lisValores2 )
{
	SConjunto *	p_cnjRes;

	if ( SLisEsValida ( p_lisValores2 ) == 1 )
	{
		p_cnjRes = SCnjDuplicar ( p_cnjValores1 );
		if ( ES_VALIDO ( p_cnjRes ) )
		{
			if ( _SCnjInsertarCopias ( p_cnjRes, p_lisValores2->p_elmPrimero ) != 1 )
			{
				SCnjDestruir ( &p_cnjRes );
			}
		}
	}
	else
	{
		p_cnjRes = NULL;
	}
	return ( p_cnjRes );
}

SConjunto * SCnjInterseccionLista ( SConjunto * p_cnjValores1, SLista * p_lisValores2 )
{
	SConjunto *	p_cnjRes;

	if ( SCnjEsValido ( p_cnjValores1 ) == 1 )
	{
		p_cnjRes = _SCnjEnvolver ( SLisOrdInterseccionLista ( p_cnjValores1->p_lisContenido, p_lisValores2 ) );
	}
	else
	{
		p_cnjRes = NULL;
	}
	return ( p_cnjRes );
}

SConjunto * SCnjDiferenciaLista ( SConjunto * p_cnjValores1, SLista * p_lisValores2 )
{
	SConjunto *	p_cnjRes;

	if ( SCnjEsValido ( p_cnjValores1 ) == 1 )
	{
		p_cnjRes = _SCnjEnvolver ( SLisOrdDiferenciaLista ( p_cnjValores1->p_lisContenido, p_lisValores2 ) );
	}
	else
	{
		p_cnjRes = NULL;
	}
	return ( p_cnjRes );
}


