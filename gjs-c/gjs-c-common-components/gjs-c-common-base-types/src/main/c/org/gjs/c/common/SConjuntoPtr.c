#include "SConjuntoPtr.h"


#include "TiposBasicosConfig.h"







/* 1 si en p_lisObj hay dos datos iguales segun su comparador. Como estan
   ordenados, basta con comparar cada uno con el anterior. */
static int _SCnjpTieneRepetidos ( SListaOrdenadaPtr * p_lisObj )
{
	SElementoPtr *	p_elpAnt;
	SElementoPtr *	p_elpObj;
	int				iRes;

	iRes = 0;
	p_elpAnt = p_lisObj->p_lispContenido->p_elpPrimero;
	if ( ES_VALIDO ( p_elpAnt ) )
	{
		p_elpObj = SElpSucesor ( p_elpAnt );
		while ( ES_VALIDO ( p_elpObj ) && ( iRes == 0 ) )
		{
			if ( SCmpEvaluarEsIgual ( p_lisObj->p_cmpObj, SElpDatos ( p_elpAnt ), SElpDatos ( p_elpObj ) ) == 1 )
			{
				iRes = 1;
			}
			p_elpAnt = p_elpObj;
			p_elpObj = SElpSucesor ( p_elpObj );
		}
	}
	return ( iRes );
}

/* Inserta en p_cnjObj copias de los datos de la cadena que empieza en
   p_elpPrimero que no esten ya: un dato que ya esta, o que se repite en la
   cadena, entra una sola vez. Copia con fDuplicar si viene y, si no, iNumBytes
   bytes. Devuelve 1, o 0 si falla una copia o una insercion; lo insertado
   hasta ahi se queda. */
static int _SCnjpInsertarCopias ( SConjuntoPtr * p_cnjObj, SElementoPtr * p_elpPrimero, int iNumBytes, PFUNPBYTEPB fDuplicar )
{
	SElementoPtr *	p_elpObj;
	byte *			p_byNuevo;
	int				iRes;

	iRes = 1;
	p_elpObj = p_elpPrimero;
	while ( ES_VALIDO ( p_elpObj ) && ( iRes == 1 ) )
	{
		if ( SCnjpExiste ( p_cnjObj, SElpDatos ( p_elpObj ) ) == 0 )
		{
			if ( ES_VALIDO ( fDuplicar ) )
			{
				p_byNuevo = fDuplicar ( SElpDatos ( p_elpObj ) );
			}
			else
			{
				p_byNuevo = (byte *) MemDuplicar ( SElpDatos ( p_elpObj ), iNumBytes );
			}
			if ( ES_NULO ( p_byNuevo ) )
			{
				ERROR_ESTABLECER ( ERR_COPIA_OBJETO );
				iRes = 0;
			}
			else if ( SLispOrdInsertarElem ( p_cnjObj->p_lispContenido, p_byNuevo ) != 1 )
			{
				MemLiberar ( (void **) &p_byNuevo );
				ERROR_ESTABLECER_FORM ( ERR_INSERCION_LISTA, ERR_TXT_INSERCION_LISTA );
				iRes = 0;
			}
		}
		p_elpObj = SElpSucesor ( p_elpObj );
	}
	return ( iRes );
}

/* Envuelve en un conjunto una lista ordenada recien creada, o la destruye si
   no se puede: nunca se pierde ni se devuelve un conjunto sin lista. */
static SConjuntoPtr * _SCnjpEnvolver ( SListaOrdenadaPtr * p_lisObj )
{
	SConjuntoPtr * p_cnjRes;

	p_cnjRes = SCnjpEncapsularLista ( p_lisObj );
	if ( ES_NULO ( p_cnjRes ) )
	{
		SLispOrdDestruir ( &p_lisObj );
	}
	return ( p_cnjRes );
}

/* Saca un conjunto de lo que haya extraido una de las Extraer de la lista
   ordenada. Si no se puede crear, lo extraido vuelve a p_cnjObj. */
static SConjuntoPtr * _SCnjpEnvolverExtraidos ( SConjuntoPtr * p_cnjObj, SListaOrdenadaPtr * p_lisExt )
{
	SConjuntoPtr * p_cnjRes;

	p_cnjRes = SCnjpEncapsularLista ( p_lisExt );
	if ( ES_NULO ( p_cnjRes ) )
	{
		SLispOrdInsertarListaOrd ( p_cnjObj->p_lispContenido, p_lisExt );
		SLispOrdDestruir ( &p_lisExt );
	}
	return ( p_cnjRes );
}

/* Conjunto nuevo desde una lista, con copias de los datos distintos. */
static SConjuntoPtr * _SCnjpCrearDesdeLista ( SListaPtr * p_lisValores, PFUNINTPVPV fComparar, int iNumBytes, PFUNPBYTEPB fDuplicar )
{
	SConjuntoPtr *	p_cnjObj;

	p_cnjObj = SCnjpCrear ( fComparar );
	if ( SCnjpEsValido ( p_cnjObj ) == 1 )
	{
		if ( _SCnjpInsertarCopias ( p_cnjObj, p_lisValores->p_elpPrimero, iNumBytes, fDuplicar ) != 1 )
		{
			SCnjpDestruir ( &p_cnjObj );
		}
	}
	else
	{
		SCnjpDestruir ( &p_cnjObj );
	}
	return ( p_cnjObj );
}

/* Conjunto nuevo desde la union: copia el primero y le anade copias de lo
   que falte de la segunda lista. */
static SConjuntoPtr * _SCnjpUnir ( SConjuntoPtr * p_cnjValores1, SListaPtr * p_lisValores2, int iNumBytes, PFUNPBYTEPB fDuplicar )
{
	SConjuntoPtr *	p_cnjRes;

	if ( ES_VALIDO ( fDuplicar ) )
	{
		p_cnjRes = SCnjpDuplicarExt ( p_cnjValores1, fDuplicar );
	}
	else
	{
		p_cnjRes = SCnjpDuplicar ( p_cnjValores1, iNumBytes );
	}
	if ( ES_VALIDO ( p_cnjRes ) )
	{
		if ( _SCnjpInsertarCopias ( p_cnjRes, p_lisValores2->p_elpPrimero, iNumBytes, fDuplicar ) != 1 )
		{
			SCnjpDestruir ( &p_cnjRes );
		}
	}
	return ( p_cnjRes );
}



SConjuntoPtr * SCnjpCrear ( PFUNINTPVPV fComparar )
{
	SConjuntoPtr * p_cnjObj;
	
	p_cnjObj = (SConjuntoPtr *) MemReservar ( sizeof ( SConjuntoPtr ) );
	if ( ES_VALIDO ( p_cnjObj ) )
	{
		p_cnjObj->p_lispContenido = SLispOrdCrear ( fComparar );
	}
	return ( p_cnjObj );
}

/* Conjunto nuevo, ordenado con fComparar, con copias de iNumBytes bytes de los
   datos distintos de p_lisValores: los repetidos entran una vez. Es dueno de
   las copias. Si falla una, NULL. */
SConjuntoPtr * SCnjpCrearDesdeLista ( SListaPtr * p_lisValores, PFUNINTPVPV fComparar, int iNumBytes )
{
	SConjuntoPtr *	p_cnjObj;

	if ( SLispEsValida ( p_lisValores ) == 1 )
	{
		p_cnjObj = _SCnjpCrearDesdeLista ( p_lisValores, fComparar, iNumBytes, NULL );
	}
	else
	{
		p_cnjObj = NULL;
	}
	return ( p_cnjObj );
}

/* Como SCnjpCrearDesdeLista, copiando con fDuplicar. */
SConjuntoPtr * SCnjpCrearDesdeListaExt ( SListaPtr * p_lisValores, PFUNINTPVPV fComparar, PFUNPBYTEPB fDuplicar )
{
	SConjuntoPtr *	p_cnjObj;

	if ( SLispEsValida ( p_lisValores ) == 1 )
	{
		if ( ES_VALIDO ( fDuplicar ) )
		{
			p_cnjObj = _SCnjpCrearDesdeLista ( p_lisValores, fComparar, 0, fDuplicar );
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

/* El conjunto se queda con p_lisValores, sin copiarla, y la destruye al
   destruirse. Si la lista tiene datos repetidos no es un conjunto: NULL, y la
   lista sigue siendo del llamante. */
SConjuntoPtr * SCnjpEncapsularLista ( SListaOrdenadaPtr * p_lisValores )
{
	SConjuntoPtr * p_cnjObj;

	if ( SLispOrdEsValida ( p_lisValores ) == 1 )
	{
		if ( _SCnjpTieneRepetidos ( p_lisValores ) == 0 )
		{
			p_cnjObj = (SConjuntoPtr *) MemReservar ( sizeof ( SConjuntoPtr ) );
			if ( ES_VALIDO ( p_cnjObj ) )
			{
				p_cnjObj->p_lispContenido = p_lisValores;
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

void SCnjpDestruir ( SConjuntoPtr ** p_p_cnjObj )
{
	SConjuntoPtr * p_cnjObj;
	
	if ( ES_VALIDO ( p_p_cnjObj ) )
	{
		p_cnjObj = *p_p_cnjObj;

		if ( ES_VALIDO ( p_cnjObj ) )
		{
			SLispOrdDestruir ( &(p_cnjObj->p_lispContenido) );
			MemLiberar ( (void **) p_p_cnjObj );
		}
	}
}

int SCnjpEsValido ( SConjuntoPtr * p_cnjObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		if ( SLispOrdEsValida ( p_cnjObj->p_lispContenido ) == 1 )
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

int SCnjpNumElementos ( SConjuntoPtr * p_cnjObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		iRes = SLispOrdNumElementos ( p_cnjObj->p_lispContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCnjpEstaVacio ( SConjuntoPtr * p_cnjObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		iRes = SLispOrdEstaVacia ( p_cnjObj->p_lispContenido );
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

byte * SCnjpElemento ( SConjuntoPtr * p_cnjObj, int iElem )
{
	byte *	p_byRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		p_byRes = SLispOrdElemento ( p_cnjObj->p_lispContenido, iElem );
	}
	else
	{
		p_byRes = NULL;
	}
	return ( p_byRes );
}

SElementoPtr * SCnjpElementoPtr ( SConjuntoPtr * p_cnjObj, int iElem )
{
	SElementoPtr * p_elpRes;

	if ( SCnjpEsValido ( p_cnjObj ) == 1 )
	{
		p_elpRes = SLispElementoPtr ( p_cnjObj->p_lispContenido->p_lispContenido, iElem );
	}
	else
	{
		p_elpRes = NULL;
	}
	return ( p_elpRes );
}

byte * SCnjpPrimero ( SConjuntoPtr * p_cnjObj )
{
	byte * p_byRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		p_byRes = SLispOrdElemento ( p_cnjObj->p_lispContenido, 0 );
	}
	else
	{
		p_byRes = NULL;
	}
	return ( p_byRes );
}

byte * SCnjpUltimo ( SConjuntoPtr * p_cnjObj )
{
	byte * p_byRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		p_byRes = SLispOrdElemento ( p_cnjObj->p_lispContenido, SCnjpNumElementos ( p_cnjObj ) - 1 );
	}
	else
	{
		p_byRes = NULL;
	}
	return ( p_byRes );
}

int SCnjpPosicion ( SConjuntoPtr * p_cnjObj, byte * p_byObj )
{
	return ( SCnjpBuscar ( p_cnjObj, p_byObj ) );
}

int SCnjpInsertarElem ( SConjuntoPtr * p_cnjObj, byte * p_byDatos )
{
	int iRes;

	if ( ( SCnjpEsValido ( p_cnjObj ) == 1 ) && ES_VALIDO ( p_byDatos ) )
	{
		if ( SCnjpExiste ( p_cnjObj, p_byDatos ) == 0 )
		{
			iRes = SLispOrdInsertarElem ( p_cnjObj->p_lispContenido, p_byDatos );
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

int SCnjpEliminarElem ( SConjuntoPtr * p_cnjObj, int iElem )
{
	int	iRes;

	if ( SCnjpEsValido ( p_cnjObj ) == 1 ) 
	{
		iRes = SLispOrdEliminarElem ( p_cnjObj->p_lispContenido, iElem );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

byte * SCnjpExtraerElem ( SConjuntoPtr * p_cnjObj, int iElem )
{
	byte * p_byRes;

	if ( SCnjpEsValido ( p_cnjObj ) == 1 ) 
	{
		p_byRes = SLispOrdExtraerElem ( p_cnjObj->p_lispContenido, iElem );
	}
	else
	{
		p_byRes = NULL;
	}
	return ( p_byRes );
}

SElementoPtr * SCnjpExtraerElemPtr ( SConjuntoPtr * p_cnjObj, int iElem )
{
	SElementoPtr * p_elpRes;

	if ( SCnjpEsValido ( p_cnjObj ) == 1 ) 
	{
		p_elpRes = SLispExtraerElemPtr ( p_cnjObj->p_lispContenido->p_lispContenido, iElem );
	}
	else
	{
		p_elpRes = NULL;
	}
	return ( p_elpRes );
}

int SCnjpVaciar ( SConjuntoPtr * p_cnjObj )
{
	int	iRes;

	if ( SCnjpEsValido ( p_cnjObj ) == 1 ) 
	{
		iRes = SLispOrdVaciar ( p_cnjObj->p_lispContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCnjpExiste ( SConjuntoPtr * p_cnjObj, byte * p_byDatos )
{
	int			iRes;

	if ( SCnjpEsValido ( p_cnjObj ) == 1 )
	{
		if ( SLispOrdBuscar ( p_cnjObj->p_lispContenido, p_byDatos ) >= 0 )
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

int SCnjpExistePtr ( SConjuntoPtr * p_cnjObj, SElementoPtr * p_elpDatos )
{
	int	iRes;

	if ( SCnjpEsValido ( p_cnjObj ) == 1 )
	{
		iRes = SLispOrdExistePtr ( p_cnjObj->p_lispContenido, p_elpDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCnjpBuscar ( SConjuntoPtr * p_cnjObj, byte * p_byDatos )
{
	int			iRes;

	if ( SCnjpEsValido ( p_cnjObj ) == 1 )
	{
		iRes = SLispOrdBuscar ( p_cnjObj->p_lispContenido, p_byDatos );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SCnjpBuscarPtr ( SConjuntoPtr * p_cnjObj, SElementoPtr * p_elpDatos )
{
	int	iRes;

	if ( SCnjpEsValido ( p_cnjObj ) == 1 )
	{
		iRes = SLispOrdBuscarPtr ( p_cnjObj->p_lispContenido, p_elpDatos );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int	SCnjpLiberacionMemoriaActivada ( SConjuntoPtr * p_cnjObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_cnjObj ) )
	{
		iRes = SLispOrdLiberacionMemoriaActivada ( p_cnjObj->p_lispContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

void SCnjpActivarLiberacionMemoria ( SConjuntoPtr * p_cnjObj )
{
	if ( ES_VALIDO ( p_cnjObj ) )
	{
		SLispOrdActivarLiberacionMemoria ( p_cnjObj->p_lispContenido );
	}
}

void SCnjpDesactivarLiberacionMemoria ( SConjuntoPtr * p_cnjObj )
{
	if ( ES_VALIDO ( p_cnjObj ) )
	{
		SLispOrdDesactivarLiberacionMemoria ( p_cnjObj->p_lispContenido );
	}
}

/* La lista ordenada de dentro: sigue siendo del conjunto. */
SListaOrdenadaPtr * SCnjpLista ( SConjuntoPtr * p_cnjObj )
{
	SListaOrdenadaPtr * p_lisRes;

	if ( SCnjpEsValido ( p_cnjObj ) == 1 )
	{
		p_lisRes = p_cnjObj->p_lispContenido;
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

/* Conjunto nuevo con copias de los datos y una copia del comparador; es
   dueno de las copias. */
SConjuntoPtr * SCnjpDuplicar ( SConjuntoPtr * p_cnjObj, int iNumBytes )
{
	SConjuntoPtr *	p_cnjRes;

	if ( SCnjpEsValido ( p_cnjObj ) == 1 )
	{
		p_cnjRes = _SCnjpEnvolver ( SLispOrdDuplicar ( p_cnjObj->p_lispContenido, iNumBytes ) );
	}
	else
	{
		p_cnjRes = NULL;
	}
	return ( p_cnjRes );
}

SConjuntoPtr * SCnjpDuplicarExt ( SConjuntoPtr * p_cnjObj, PFUNPBYTEPB fDuplicar )
{
	SConjuntoPtr *	p_cnjRes;

	if ( SCnjpEsValido ( p_cnjObj ) == 1 )
	{
		p_cnjRes = _SCnjpEnvolver ( SLispOrdDuplicarExt ( p_cnjObj->p_lispContenido, fDuplicar ) );
	}
	else
	{
		p_cnjRes = NULL;
	}
	return ( p_cnjRes );
}

/* Las operaciones con otros conjuntos y listas delegan en las de
   SListaOrdenadaPtr, con su misma semantica ( ver Listas.md ): la igualdad la
   decide el comparador del conjunto. Las de Conjunto pasan la lista del
   segundo. Las que crean un conjunto nuevo devuelven NULL si la de la lista
   falla, nunca un conjunto sin lista. */
int SCnjpExistenTodos ( SConjuntoPtr * p_cnjObj, SConjuntoPtr * p_cnjValores )
{
	int	iRes;

	if ( SCnjpEsValido ( p_cnjValores ) == 1 )
	{
		iRes = SCnjpExistenTodosListaOrd ( p_cnjObj, p_cnjValores->p_lispContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCnjpExisteAlguno ( SConjuntoPtr * p_cnjObj, SConjuntoPtr * p_cnjValores )
{
	int	iRes;

	if ( SCnjpEsValido ( p_cnjValores ) == 1 )
	{
		iRes = SCnjpExisteAlgunoListaOrd ( p_cnjObj, p_cnjValores->p_lispContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCnjpExistenTodosListaOrd ( SConjuntoPtr * p_cnjObj, SListaOrdenadaPtr * p_lisValores )
{
	int	iRes;

	if ( SCnjpEsValido ( p_cnjObj ) == 1 )
	{
		iRes = SLispOrdExistenTodos ( p_cnjObj->p_lispContenido, p_lisValores );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCnjpExisteAlgunoListaOrd ( SConjuntoPtr * p_cnjObj, SListaOrdenadaPtr * p_lisValores )
{
	int	iRes;

	if ( SCnjpEsValido ( p_cnjObj ) == 1 )
	{
		iRes = SLispOrdExisteAlguno ( p_cnjObj->p_lispContenido, p_lisValores );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCnjpExistenTodosLista ( SConjuntoPtr * p_cnjObj, SListaPtr * p_lisValores )
{
	int	iRes;

	if ( SCnjpEsValido ( p_cnjObj ) == 1 )
	{
		iRes = SLispOrdExistenTodosLista ( p_cnjObj->p_lispContenido, p_lisValores );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCnjpExisteAlgunoLista ( SConjuntoPtr * p_cnjObj, SListaPtr * p_lisValores )
{
	int	iRes;

	if ( SCnjpEsValido ( p_cnjObj ) == 1 )
	{
		iRes = SLispOrdExisteAlgunoLista ( p_cnjObj->p_lispContenido, p_lisValores );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

/* Los datos que se eliminan se liberan segun la liberacion del conjunto. */
int SCnjpEliminarConjunto ( SConjuntoPtr * p_cnjObj, SConjuntoPtr * p_cnjValores )
{
	int	iRes;

	if ( SCnjpEsValido ( p_cnjValores ) == 1 )
	{
		iRes = SCnjpEliminarListaOrd ( p_cnjObj, p_cnjValores->p_lispContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCnjpEliminarListaOrd ( SConjuntoPtr * p_cnjObj, SListaOrdenadaPtr * p_lisValores )
{
	int	iRes;

	if ( SCnjpEsValido ( p_cnjObj ) == 1 )
	{
		iRes = SLispOrdEliminarListaOrd ( p_cnjObj->p_lispContenido, p_lisValores );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCnjpEliminarLista ( SConjuntoPtr * p_cnjObj, SListaPtr * p_lisValores )
{
	int	iRes;

	if ( SCnjpEsValido ( p_cnjObj ) == 1 )
	{
		iRes = SLispOrdEliminarLista ( p_cnjObj->p_lispContenido, p_lisValores );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

/* Las Insertar meten COPIAS de los datos que no esten ya en el conjunto,
   de iNumBytes bytes o hechas con fDuplicar; los demas se ignoran. Devuelven
   1, o 0 si falla una copia o una insercion ( lo insertado hasta ahi se
   queda ). Las copias son del conjunto si tiene la liberacion activada. */
int SCnjpInsertar ( SConjuntoPtr * p_cnjObj, SConjuntoPtr * p_cnjValores, int iNumBytes )
{
	int	iRes;

	if ( SCnjpEsValido ( p_cnjValores ) == 1 )
	{
		iRes = SCnjpInsertarListaOrd ( p_cnjObj, p_cnjValores->p_lispContenido, iNumBytes );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCnjpInsertarListaOrd ( SConjuntoPtr * p_cnjObj, SListaOrdenadaPtr * p_lisValores, int iNumBytes )
{
	int	iRes;

	if ( SLispOrdEsValida ( p_lisValores ) == 1 )
	{
		iRes = SCnjpInsertarLista ( p_cnjObj, p_lisValores->p_lispContenido, iNumBytes );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCnjpInsertarLista ( SConjuntoPtr * p_cnjObj, SListaPtr * p_lisValores, int iNumBytes )
{
	int	iRes;

	if ( SCnjpEsValido ( p_cnjObj ) == 1 )
	{
		if ( SLispEsValida ( p_lisValores ) == 1 )
		{
			iRes = _SCnjpInsertarCopias ( p_cnjObj, p_lisValores->p_elpPrimero, iNumBytes, NULL );
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

int SCnjpInsertarExt ( SConjuntoPtr * p_cnjObj, SConjuntoPtr * p_cnjValores, PFUNPBYTEPB fDuplicar )
{
	int	iRes;

	if ( SCnjpEsValido ( p_cnjValores ) == 1 )
	{
		iRes = SCnjpInsertarListaOrdExt ( p_cnjObj, p_cnjValores->p_lispContenido, fDuplicar );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCnjpInsertarListaOrdExt ( SConjuntoPtr * p_cnjObj, SListaOrdenadaPtr * p_lisValores, PFUNPBYTEPB fDuplicar )
{
	int	iRes;

	if ( SLispOrdEsValida ( p_lisValores ) == 1 )
	{
		iRes = SCnjpInsertarListaExt ( p_cnjObj, p_lisValores->p_lispContenido, fDuplicar );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCnjpInsertarListaExt ( SConjuntoPtr * p_cnjObj, SListaPtr * p_lisValores, PFUNPBYTEPB fDuplicar )
{
	int	iRes;

	if ( SCnjpEsValido ( p_cnjObj ) == 1 )
	{
		if ( SLispEsValida ( p_lisValores ) == 1 )
		{
			if ( ES_VALIDO ( fDuplicar ) )
			{
				iRes = _SCnjpInsertarCopias ( p_cnjObj, p_lisValores->p_elpPrimero, 0, fDuplicar );
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
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

/* Las Extraer MUEVEN los datos a un conjunto nuevo con una copia del
   comparador y la liberacion del original. Si no se puede crear el
   conjunto, lo extraido vuelve a p_cnjObj y se devuelve NULL. */
SConjuntoPtr * SCnjpExtraerConjunto ( SConjuntoPtr * p_cnjObj, SConjuntoPtr * p_cnjValores )
{
	SConjuntoPtr *	p_cnjRes;

	if ( SCnjpEsValido ( p_cnjValores ) == 1 )
	{
		p_cnjRes = SCnjpExtraerListaOrd ( p_cnjObj, p_cnjValores->p_lispContenido );
	}
	else
	{
		p_cnjRes = NULL;
	}
	return ( p_cnjRes );
}

SConjuntoPtr * SCnjpExtraerListaOrd ( SConjuntoPtr * p_cnjObj, SListaOrdenadaPtr * p_lisValores )
{
	SConjuntoPtr *	p_cnjRes;

	if ( SCnjpEsValido ( p_cnjObj ) == 1 )
	{
		p_cnjRes = _SCnjpEnvolverExtraidos ( p_cnjObj, SLispOrdExtraerListaOrd ( p_cnjObj->p_lispContenido, p_lisValores ) );
	}
	else
	{
		p_cnjRes = NULL;
	}
	return ( p_cnjRes );
}

SConjuntoPtr * SCnjpExtraerLista ( SConjuntoPtr * p_cnjObj, SListaPtr * p_lisValores )
{
	SConjuntoPtr *	p_cnjRes;

	if ( SCnjpEsValido ( p_cnjObj ) == 1 )
	{
		p_cnjRes = _SCnjpEnvolverExtraidos ( p_cnjObj, SLispOrdExtraerLista ( p_cnjObj->p_lispContenido, p_lisValores ) );
	}
	else
	{
		p_cnjRes = NULL;
	}
	return ( p_cnjRes );
}

/* Union, Interseccion y Diferencia crean un conjunto nuevo con COPIAS, de
   iNumBytes bytes o hechas con fDuplicar, y una copia del comparador del
   primero; si algo falla, NULL. La union es la de conjuntos: lo que esta en
   los dos sale una vez. */
SConjuntoPtr * SCnjpUnion ( SConjuntoPtr * p_cnjValores1, SConjuntoPtr * p_cnjValores2, int iNumBytes )
{
	SConjuntoPtr *	p_cnjRes;

	if ( SCnjpEsValido ( p_cnjValores2 ) == 1 )
	{
		p_cnjRes = SCnjpUnionListaOrd ( p_cnjValores1, p_cnjValores2->p_lispContenido, iNumBytes );
	}
	else
	{
		p_cnjRes = NULL;
	}
	return ( p_cnjRes );
}

SConjuntoPtr * SCnjpInterseccion ( SConjuntoPtr * p_cnjValores1, SConjuntoPtr * p_cnjValores2, int iNumBytes )
{
	SConjuntoPtr *	p_cnjRes;

	if ( SCnjpEsValido ( p_cnjValores2 ) == 1 )
	{
		p_cnjRes = SCnjpInterseccionListaOrd ( p_cnjValores1, p_cnjValores2->p_lispContenido, iNumBytes );
	}
	else
	{
		p_cnjRes = NULL;
	}
	return ( p_cnjRes );
}

SConjuntoPtr * SCnjpDiferencia ( SConjuntoPtr * p_cnjValores1, SConjuntoPtr * p_cnjValores2, int iNumBytes )
{
	SConjuntoPtr *	p_cnjRes;

	if ( SCnjpEsValido ( p_cnjValores2 ) == 1 )
	{
		p_cnjRes = SCnjpDiferenciaListaOrd ( p_cnjValores1, p_cnjValores2->p_lispContenido, iNumBytes );
	}
	else
	{
		p_cnjRes = NULL;
	}
	return ( p_cnjRes );
}

SConjuntoPtr * SCnjpUnionListaOrd ( SConjuntoPtr * p_cnjValores1, SListaOrdenadaPtr * p_lisValores2, int iNumBytes )
{
	SConjuntoPtr *	p_cnjRes;

	if ( SLispOrdEsValida ( p_lisValores2 ) == 1 )
	{
		p_cnjRes = SCnjpUnionLista ( p_cnjValores1, p_lisValores2->p_lispContenido, iNumBytes );
	}
	else
	{
		p_cnjRes = NULL;
	}
	return ( p_cnjRes );
}

SConjuntoPtr * SCnjpInterseccionListaOrd ( SConjuntoPtr * p_cnjValores1, SListaOrdenadaPtr * p_lisValores2, int iNumBytes )
{
	SConjuntoPtr *	p_cnjRes;

	if ( SCnjpEsValido ( p_cnjValores1 ) == 1 )
	{
		p_cnjRes = _SCnjpEnvolver ( SLispOrdInterseccion ( p_cnjValores1->p_lispContenido, p_lisValores2, iNumBytes ) );
	}
	else
	{
		p_cnjRes = NULL;
	}
	return ( p_cnjRes );
}

SConjuntoPtr * SCnjpDiferenciaListaOrd ( SConjuntoPtr * p_cnjValores1, SListaOrdenadaPtr * p_lisValores2, int iNumBytes )
{
	SConjuntoPtr *	p_cnjRes;

	if ( SCnjpEsValido ( p_cnjValores1 ) == 1 )
	{
		p_cnjRes = _SCnjpEnvolver ( SLispOrdDiferencia ( p_cnjValores1->p_lispContenido, p_lisValores2, iNumBytes ) );
	}
	else
	{
		p_cnjRes = NULL;
	}
	return ( p_cnjRes );
}

SConjuntoPtr * SCnjpUnionLista ( SConjuntoPtr * p_cnjValores1, SListaPtr * p_lisValores2, int iNumBytes )
{
	SConjuntoPtr *	p_cnjRes;

	if ( SLispEsValida ( p_lisValores2 ) == 1 )
	{
		p_cnjRes = _SCnjpUnir ( p_cnjValores1, p_lisValores2, iNumBytes, NULL );
	}
	else
	{
		p_cnjRes = NULL;
	}
	return ( p_cnjRes );
}

SConjuntoPtr * SCnjpInterseccionLista ( SConjuntoPtr * p_cnjValores1, SListaPtr * p_lisValores2, int iNumBytes )
{
	SConjuntoPtr *	p_cnjRes;

	if ( SCnjpEsValido ( p_cnjValores1 ) == 1 )
	{
		p_cnjRes = _SCnjpEnvolver ( SLispOrdInterseccionLista ( p_cnjValores1->p_lispContenido, p_lisValores2, iNumBytes ) );
	}
	else
	{
		p_cnjRes = NULL;
	}
	return ( p_cnjRes );
}

SConjuntoPtr * SCnjpDiferenciaLista ( SConjuntoPtr * p_cnjValores1, SListaPtr * p_lisValores2, int iNumBytes )
{
	SConjuntoPtr *	p_cnjRes;

	if ( SCnjpEsValido ( p_cnjValores1 ) == 1 )
	{
		p_cnjRes = _SCnjpEnvolver ( SLispOrdDiferenciaLista ( p_cnjValores1->p_lispContenido, p_lisValores2, iNumBytes ) );
	}
	else
	{
		p_cnjRes = NULL;
	}
	return ( p_cnjRes );
}

SConjuntoPtr * SCnjpUnionExt ( SConjuntoPtr * p_cnjValores1, SConjuntoPtr * p_cnjValores2, PFUNPBYTEPB fDuplicar )
{
	SConjuntoPtr *	p_cnjRes;

	if ( SCnjpEsValido ( p_cnjValores2 ) == 1 )
	{
		p_cnjRes = SCnjpUnionListaOrdExt ( p_cnjValores1, p_cnjValores2->p_lispContenido, fDuplicar );
	}
	else
	{
		p_cnjRes = NULL;
	}
	return ( p_cnjRes );
}

SConjuntoPtr * SCnjpInterseccionExt ( SConjuntoPtr * p_cnjValores1, SConjuntoPtr * p_cnjValores2, PFUNPBYTEPB fDuplicar )
{
	SConjuntoPtr *	p_cnjRes;

	if ( SCnjpEsValido ( p_cnjValores2 ) == 1 )
	{
		p_cnjRes = SCnjpInterseccionListaOrdExt ( p_cnjValores1, p_cnjValores2->p_lispContenido, fDuplicar );
	}
	else
	{
		p_cnjRes = NULL;
	}
	return ( p_cnjRes );
}

SConjuntoPtr * SCnjpDiferenciaExt ( SConjuntoPtr * p_cnjValores1, SConjuntoPtr * p_cnjValores2, PFUNPBYTEPB fDuplicar )
{
	SConjuntoPtr *	p_cnjRes;

	if ( SCnjpEsValido ( p_cnjValores2 ) == 1 )
	{
		p_cnjRes = SCnjpDiferenciaListaOrdExt ( p_cnjValores1, p_cnjValores2->p_lispContenido, fDuplicar );
	}
	else
	{
		p_cnjRes = NULL;
	}
	return ( p_cnjRes );
}

SConjuntoPtr * SCnjpUnionListaOrdExt ( SConjuntoPtr * p_cnjValores1, SListaOrdenadaPtr * p_lisValores2, PFUNPBYTEPB fDuplicar )
{
	SConjuntoPtr *	p_cnjRes;

	if ( SLispOrdEsValida ( p_lisValores2 ) == 1 )
	{
		p_cnjRes = SCnjpUnionListaExt ( p_cnjValores1, p_lisValores2->p_lispContenido, fDuplicar );
	}
	else
	{
		p_cnjRes = NULL;
	}
	return ( p_cnjRes );
}

SConjuntoPtr * SCnjpInterseccionListaOrdExt ( SConjuntoPtr * p_cnjValores1, SListaOrdenadaPtr * p_lisValores2, PFUNPBYTEPB fDuplicar )
{
	SConjuntoPtr *	p_cnjRes;

	if ( SCnjpEsValido ( p_cnjValores1 ) == 1 )
	{
		p_cnjRes = _SCnjpEnvolver ( SLispOrdInterseccionExt ( p_cnjValores1->p_lispContenido, p_lisValores2, fDuplicar ) );
	}
	else
	{
		p_cnjRes = NULL;
	}
	return ( p_cnjRes );
}

SConjuntoPtr * SCnjpDiferenciaListaOrdExt ( SConjuntoPtr * p_cnjValores1, SListaOrdenadaPtr * p_lisValores2, PFUNPBYTEPB fDuplicar )
{
	SConjuntoPtr *	p_cnjRes;

	if ( SCnjpEsValido ( p_cnjValores1 ) == 1 )
	{
		p_cnjRes = _SCnjpEnvolver ( SLispOrdDiferenciaExt ( p_cnjValores1->p_lispContenido, p_lisValores2, fDuplicar ) );
	}
	else
	{
		p_cnjRes = NULL;
	}
	return ( p_cnjRes );
}

SConjuntoPtr * SCnjpUnionListaExt ( SConjuntoPtr * p_cnjValores1, SListaPtr * p_lisValores2, PFUNPBYTEPB fDuplicar )
{
	SConjuntoPtr *	p_cnjRes;

	if ( SLispEsValida ( p_lisValores2 ) == 1 )
	{
		if ( ES_VALIDO ( fDuplicar ) )
		{
			p_cnjRes = _SCnjpUnir ( p_cnjValores1, p_lisValores2, 0, fDuplicar );
		}
		else
		{
			p_cnjRes = NULL;
		}
	}
	else
	{
		p_cnjRes = NULL;
	}
	return ( p_cnjRes );
}

SConjuntoPtr * SCnjpInterseccionListaExt ( SConjuntoPtr * p_cnjValores1, SListaPtr * p_lisValores2, PFUNPBYTEPB fDuplicar )
{
	SConjuntoPtr *	p_cnjRes;

	if ( SCnjpEsValido ( p_cnjValores1 ) == 1 )
	{
		p_cnjRes = _SCnjpEnvolver ( SLispOrdInterseccionListaExt ( p_cnjValores1->p_lispContenido, p_lisValores2, fDuplicar ) );
	}
	else
	{
		p_cnjRes = NULL;
	}
	return ( p_cnjRes );
}

SConjuntoPtr * SCnjpDiferenciaListaExt ( SConjuntoPtr * p_cnjValores1, SListaPtr * p_lisValores2, PFUNPBYTEPB fDuplicar )
{
	SConjuntoPtr *	p_cnjRes;

	if ( SCnjpEsValido ( p_cnjValores1 ) == 1 )
	{
		p_cnjRes = _SCnjpEnvolver ( SLispOrdDiferenciaListaExt ( p_cnjValores1->p_lispContenido, p_lisValores2, fDuplicar ) );
	}
	else
	{
		p_cnjRes = NULL;
	}
	return ( p_cnjRes );
}


