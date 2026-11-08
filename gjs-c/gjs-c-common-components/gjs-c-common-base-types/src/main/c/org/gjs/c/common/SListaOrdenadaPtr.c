#include "SListaOrdenadaPtr.h"


#include "TiposBasicosConfig.h"



int SLispOrdBuscarSitio ( SListaOrdenadaPtr * p_lisObj, byte * p_byDatos );

static SListaOrdenadaPtr * _SLispOrdCrearDesdeLista ( SListaPtr * p_lisValores, PFUNINTPVPV fComparar, int iNumBytes, PFUNPBYTEPB fDuplicar );
//SElementoPtr * _SLispOrdExtraerPtr ( SListaOrdenadaPtr * p_lisObj );
SElementoPtr * _SLispOrdExtraerElemPtr ( SListaOrdenadaPtr * p_lisObj, int iElem );
int _SLispOrdInsertarElemPtr ( SListaOrdenadaPtr * p_lisObj, SElementoPtr * p_elpDatos );

extern SElementoPtr * _SLispExtraerPtr ( SListaPtr * p_lisObj );
extern SElementoPtr * _SLispExtraerElemPtr ( SListaPtr * p_lisObj, int iElem );
extern int _SLispInsertarAlInicioPtr ( SListaPtr * p_lisObj, SElementoPtr * p_elpDatos );
extern int _SLispInsertarPtr ( SListaPtr * p_lisObj, SElementoPtr * p_elpDatos );
extern int _SLispInsertarDelantePtr ( SListaPtr * p_lisObj, SElementoPtr * p_elpDatos );
extern int _SLispInsertarDetrasPtr ( SListaPtr * p_lisObj, SElementoPtr * p_elpDatos );



SListaOrdenadaPtr * SLispOrdCrear ( PFUNINTPVPV fComparar )
{
	SListaOrdenadaPtr *	p_lisObj;
	SComparador *		p_cmpObj;

	p_cmpObj = SCmpCrear ( fComparar );
	p_lisObj = SLispOrdEncapsular ( p_cmpObj );
	if ( ES_NULO ( p_lisObj ) )
	{
		SCmpDestruir ( &p_cmpObj );
	}
	return ( p_lisObj );
}

/* Lista vacia que se queda con p_cmpObj: desde ahi lo destruye SLispOrdDestruir.
   Si falla devuelve NULL y p_cmpObj sigue siendo del llamante. */
SListaOrdenadaPtr * SLispOrdEncapsular ( SComparador * p_cmpObj )
{
	SListaOrdenadaPtr * p_lisObj;

	if ( SCmpEsValido ( p_cmpObj ) == 1 )
	{
		p_lisObj = (SListaOrdenadaPtr *) MemReservar ( sizeof ( SListaOrdenadaPtr ) );
		if ( ES_VALIDO ( p_lisObj ) )
		{
			p_lisObj->p_lispContenido = SLispCrear ();
			if ( ES_VALIDO ( p_lisObj->p_lispContenido ) )
			{
				p_lisObj->p_cmpObj = p_cmpObj;
			}
			else
			{
				/* No con SLispOrdDestruir: destruiria p_cmpObj, que sigue
				   siendo del llamante. */
				MemLiberar ( (void **) &p_lisObj );
			}
		}
	}
	else
	{
		p_lisObj = NULL;
	}
	return ( p_lisObj );
}

/* Lista ordenada con COPIAS de los datos de p_lisValores, que no se toca, y
   duena de ellas: SLispOrdCrearDesdeLista copia iNumBytes y la Ext usa
   fDuplicar. Con p_lisValores no valida, iNumBytes <= 0 o sin fDuplicar, NULL. Si falla alguna
   copia se devuelve lo copiado hasta ahi, ordenado, con el error
   ERR_COPIA_LISTA. */
SListaOrdenadaPtr * SLispOrdCrearDesdeLista ( SListaPtr * p_lisValores, PFUNINTPVPV fComparar, int iNumBytes )
{
	SListaOrdenadaPtr * p_lisRes;

	if ( iNumBytes > 0 )
	{
		p_lisRes = _SLispOrdCrearDesdeLista ( p_lisValores, fComparar, iNumBytes, NULL );
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

SListaOrdenadaPtr * SLispOrdCrearDesdeListaExt ( SListaPtr * p_lisValores, PFUNINTPVPV fComparar, PFUNPBYTEPB fDuplicar )
{
	SListaOrdenadaPtr * p_lisRes;

	if ( ES_VALIDO ( fDuplicar ) )
	{
		p_lisRes = _SLispOrdCrearDesdeLista ( p_lisValores, fComparar, 0, fDuplicar );
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

/* Lista vacia con una copia ( SCmpDuplicar ) del comparador de p_lisEjemplo,
   que no se toca. Con p_lisEjemplo no valida, NULL. */
SListaOrdenadaPtr * SLispOrdCrearIgual ( SListaOrdenadaPtr * p_lisEjemplo )
{
	SListaOrdenadaPtr *	p_lisObj;
	SComparador *		p_cmpObj;

	if ( SLispOrdEsValida ( p_lisEjemplo ) == 1 )
	{
		p_cmpObj = SCmpDuplicar ( p_lisEjemplo->p_cmpObj );
		p_lisObj = SLispOrdEncapsular ( p_cmpObj );
		if ( ES_NULO ( p_lisObj ) )
		{
			SCmpDestruir ( &p_cmpObj );
		}
	}
	else
	{
		p_lisObj = NULL;
	}
	return ( p_lisObj );
}

/* Copia cada dato con fDuplicar o, si es nulo, con MemDuplicar de iNumBytes.

   Se inserta con la liberacion DESACTIVADA: si una insercion falla, la lista
   libera el dato en unos casos ( fallo al enlazar ) y en otros no ( fallo al
   crear el nodo ), y asi no lo libera nunca y se libera aqui, una sola vez. Al
   terminar se activa, porque las copias son de la lista: SLispEliminar y
   SLispVaciar miran la liberacion de la lista, no la del nodo. */
static SListaOrdenadaPtr * _SLispOrdCrearDesdeLista ( SListaPtr * p_lisValores, PFUNINTPVPV fComparar, int iNumBytes, PFUNPBYTEPB fDuplicar )
{
	SListaOrdenadaPtr *	p_lisObj;
	SElementoPtr *		p_elpObj;
	byte *				p_byCopia;
	int					iError;

	if ( SLispEsValida ( p_lisValores ) == 1 )
	{
		p_lisObj = SLispOrdCrear ( fComparar );
		if ( ES_VALIDO ( p_lisObj ) )
		{
			SLispOrdDesactivarLiberacionMemoria ( p_lisObj );
			iError = 0;
			p_elpObj = p_lisValores->p_elpPrimero;
			while ( ES_VALIDO ( p_elpObj ) && ( iError == 0 ) )
			{
				if ( ES_VALIDO ( fDuplicar ) )
				{
					p_byCopia = fDuplicar ( SElpDatos ( p_elpObj ) );
				}
				else
				{
					p_byCopia = (byte *) MemDuplicar ( SElpDatos ( p_elpObj ), iNumBytes );
				}
				if ( SLispOrdInsertarElem ( p_lisObj, p_byCopia ) != 1 )
				{
					MemLiberar ( (void **) &p_byCopia );
					iError = 1;
				}
				p_elpObj = SElpSucesor ( p_elpObj );
			}
			SLispOrdActivarLiberacionMemoria ( p_lisObj );
			if ( iError == 1 )
			{
				ERROR_ESTABLECER_FORM ( ERR_COPIA_LISTA, ERR_TXT_COPIA_LISTA );
			}
		}
	}
	else
	{
		p_lisObj = NULL;
	}
	return ( p_lisObj );
}

void SLispOrdDestruir ( SListaOrdenadaPtr ** p_p_lisObj )
{
	SListaOrdenadaPtr * p_lisObj;
	
	if ( ES_VALIDO ( p_p_lisObj ) )
	{
		p_lisObj = *p_p_lisObj;

		if ( ES_VALIDO ( p_lisObj ) )
		{
			SLispDestruir ( &(p_lisObj->p_lispContenido) );
			SCmpDestruir ( &(p_lisObj->p_cmpObj) );
			MemLiberar ( (void **) p_p_lisObj );
		}
	}
}

int SLispOrdEsValida ( SListaOrdenadaPtr * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( ( SLispEsValida ( p_lisObj->p_lispContenido ) == 1 ) &&
			  (	SCmpEsValido ( p_lisObj->p_cmpObj ) == 1 ) )
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

int SLispOrdNumElementos ( SListaOrdenadaPtr * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLispNumElementos ( p_lisObj->p_lispContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLispOrdEstaVacia ( SListaOrdenadaPtr * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLispEstaVacia ( p_lisObj->p_lispContenido );
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

byte * SLispOrdElemento ( SListaOrdenadaPtr * p_lisObj, int iElem )
{
	byte *			p_byRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( ( iElem >= 0 ) && ( iElem < p_lisObj->p_lispContenido->iNumElementos ) )
		{
			p_byRes = SLispElemento ( p_lisObj->p_lispContenido, iElem );
		}
		else
		{
			p_byRes = NULL;
		}
	}
	else
	{
		p_byRes = NULL;
	}
	return ( p_byRes );
}

int SLispOrdInsertarElem ( SListaOrdenadaPtr * p_lisObj, byte * p_byDatos )
{
	int iRes;
	int iPosAnt;

	if ( ( SLispOrdEsValida ( p_lisObj ) == 1 ) && ES_VALIDO ( p_byDatos ) )
	{
		iPosAnt = SLispOrdBuscarSitio ( p_lisObj, p_byDatos );

		if ( iPosAnt < 0 ) 
		{
			SLispInicio ( p_lisObj->p_lispContenido );
			iRes = SLispInsertarDelante ( p_lisObj->p_lispContenido, p_byDatos );
		}
		else if ( iPosAnt >= p_lisObj->p_lispContenido->iNumElementos )
		{
			SLispFinal ( p_lisObj->p_lispContenido );
			iRes = SLispInsertarDetras ( p_lisObj->p_lispContenido, p_byDatos );
		}
		else  
		{
			SLispMoverA ( p_lisObj->p_lispContenido, iPosAnt );
			if ( ES_NULO ( p_lisObj->p_lispContenido->p_elpActual ) ) 
			{
				iRes = 0;
			}
			else 
			{
				iRes = SLispInsertar ( p_lisObj->p_lispContenido, p_byDatos );
			}
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLispOrdEliminarElem ( SListaOrdenadaPtr * p_lisObj, int iElem )
{
	int	iRes;

	if ( SLispOrdEsValida ( p_lisObj ) == 1 ) 
	{
		iRes = SLispEliminarElem ( p_lisObj->p_lispContenido, iElem );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLispOrdVaciar ( SListaOrdenadaPtr * p_lisObj )
{
	int	iRes;

	if ( SLispOrdEsValida ( p_lisObj ) == 1 ) 
	{
		iRes = SLispVaciar ( p_lisObj->p_lispContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLispOrdPosicion ( SListaOrdenadaPtr * p_lisObj )
{
	int	iRes;

	if ( SLispOrdEsValida ( p_lisObj ) == 1 ) 
	{
		iRes = SLispPosicion ( p_lisObj->p_lispContenido );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

byte * SLispOrdActual ( SListaOrdenadaPtr * p_lisObj )
{
	byte *			p_byRes;

	if ( SLispOrdEsValida ( p_lisObj ) == 1 ) 
	{
		p_byRes = SLispActual ( p_lisObj->p_lispContenido );
	}
	else
	{
		p_byRes = NULL;
	}
	return ( p_byRes );
}

SElementoPtr * SLispOrdActualPtr ( SListaOrdenadaPtr * p_lisObj )
{
	SElementoPtr *			p_elpRes;

	if ( SLispOrdEsValida ( p_lisObj ) == 1 ) 
	{
		p_elpRes = SLispActualPtr ( p_lisObj->p_lispContenido );
	}
	else
	{
		p_elpRes = NULL;
	}
	return ( p_elpRes );
}

int SLispOrdEstaPosicionada ( SListaOrdenadaPtr * p_lisObj )
{
	int	iRes;

	if ( SLispOrdEsValida ( p_lisObj ) == 1 )
	{
		iRes = SLispEstaPosicionada ( p_lisObj->p_lispContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

void SLispOrdInicio ( SListaOrdenadaPtr * p_lisObj )
{
	if ( SLispOrdEsValida ( p_lisObj ) == 1 ) 
	{
		SLispInicio ( p_lisObj->p_lispContenido );
	}
}

void SLispOrdFinal ( SListaOrdenadaPtr * p_lisObj )
{
	if ( SLispOrdEsValida ( p_lisObj ) == 1 ) 
	{
		SLispFinal ( p_lisObj->p_lispContenido );
	}
}

void SLispOrdSiguiente ( SListaOrdenadaPtr * p_lisObj )
{
	if ( SLispOrdEsValida ( p_lisObj ) == 1 ) 
	{
		SLispSiguiente ( p_lisObj->p_lispContenido );
	}
}

void SLispOrdAnterior ( SListaOrdenadaPtr * p_lisObj )
{
	if ( SLispOrdEsValida ( p_lisObj ) == 1 ) 
	{
		SLispAnterior ( p_lisObj->p_lispContenido );
	}
}

void SLispOrdMoverA ( SListaOrdenadaPtr * p_lisObj, int iElem )
{
	if ( SLispOrdEsValida ( p_lisObj ) == 1 ) 
	{
		SLispMoverA ( p_lisObj->p_lispContenido, iElem );
	}
}

void SLispOrdDeposicionar ( SListaOrdenadaPtr * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) )
	{
		SLispDeposicionar ( p_lisObj->p_lispContenido );
	}
}

/* Busquedas. La igualdad la decide el comparador, y como los iguales estan
   juntos se avanza mientras el elemento sea menor y se para en el primero que
   no lo es: no se recorre el resto de la lista.

   Existe da 1 o 0; Repeticiones, cuantos iguales hay ( 0 si ninguno, tambien
   con un nulo ); Buscar ( que es BuscarPrimero ) y BuscarSiguiente, la
   posicion o -1. BuscarSiguiente busca DETRAS de iPos: con -1, desde el
   principio, y un iPos menor da -1. Ninguna mueve el cursor. Para recorrer
   los repetidos:

	   iPos = BuscarPrimero ( ... );
	   while ( iPos >= 0 )
	   {
		   ...
		   iPos = BuscarSiguiente ( ..., iPos );
	   }

   Las Elem / Ptr buscan con los datos del elemento, que no hace falta que
   este en la lista; sin elemento dan -1 ( 0 Existe y Repeticiones ). */
int SLispOrdExiste ( SListaOrdenadaPtr * p_lisObj, byte * p_byDatos )
{
	int	iRes;

	if ( SLispOrdBuscarPrimero ( p_lisObj, p_byDatos ) >= 0 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLispOrdExistePtr ( SListaOrdenadaPtr * p_lisObj, SElementoPtr * p_elpDatos )
{
	int	iRes;

	if ( SLispOrdBuscarPrimeroPtr ( p_lisObj, p_elpDatos ) >= 0 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLispOrdRepeticiones ( SListaOrdenadaPtr * p_lisObj, byte * p_byDatos )
{
	int				iRes;
	int				iCmp;
	SElementoPtr *	p_elpObj;

	iRes = 0;
	if ( ( SLispOrdEsValida ( p_lisObj ) == 1 ) && ES_VALIDO ( p_byDatos ) )
	{
		p_elpObj = p_lisObj->p_lispContenido->p_elpPrimero;
		iCmp = -1;
		while ( ES_VALIDO ( p_elpObj ) && ( iCmp <= 0 ) )
		{
			iCmp = SCmpEvaluar ( p_lisObj->p_cmpObj, (void *) SElpDatos ( p_elpObj ), (void *) p_byDatos );
			if ( iCmp == 0 )
			{
				iRes = iRes + 1;
			}
			p_elpObj = SElpSucesor ( p_elpObj );
		}
	}
	return ( iRes );
}

int SLispOrdRepeticionesPtr ( SListaOrdenadaPtr * p_lisObj, SElementoPtr * p_elpDatos )
{
	int	iRes;

	if ( ES_VALIDO ( p_elpDatos ) )
	{
		iRes = SLispOrdRepeticiones ( p_lisObj, SElpDatos ( p_elpDatos ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLispOrdBuscar ( SListaOrdenadaPtr * p_lisObj, byte * p_byDatos )
{
	return ( SLispOrdBuscarPrimero ( p_lisObj, p_byDatos ) );
}

int SLispOrdBuscarPtr ( SListaOrdenadaPtr * p_lisObj, SElementoPtr * p_elpDatos )
{
	return ( SLispOrdBuscarPrimeroPtr ( p_lisObj, p_elpDatos ) );
}

int SLispOrdBuscarPrimero ( SListaOrdenadaPtr * p_lisObj, byte * p_byDatos )
{
	return ( SLispOrdBuscarSiguiente ( p_lisObj, p_byDatos, -1 ) );
}

int SLispOrdBuscarPrimeroPtr ( SListaOrdenadaPtr * p_lisObj, SElementoPtr * p_elpDatos )
{
	return ( SLispOrdBuscarSiguientePtr ( p_lisObj, p_elpDatos, -1 ) );
}

int SLispOrdBuscarSiguiente ( SListaOrdenadaPtr * p_lisObj, byte * p_byDatos, int iPos )
{
	int				iRes;
	int				iCmp;
	SElementoPtr *	p_elpObj;

	if ( ( SLispOrdEsValida ( p_lisObj ) == 1 ) && ES_VALIDO ( p_byDatos ) && ( iPos >= -1 ) )
	{
		iRes = iPos + 1;
		p_elpObj = SLispElementoPtr ( p_lisObj->p_lispContenido, iRes );
		iCmp = -1;
		while ( ES_VALIDO ( p_elpObj ) && ( iCmp < 0 ) )
		{
			iCmp = SCmpEvaluar ( p_lisObj->p_cmpObj, (void *) SElpDatos ( p_elpObj ), (void *) p_byDatos );
			if ( iCmp < 0 )
			{
				p_elpObj = SElpSucesor ( p_elpObj );
				iRes = iRes + 1;
			}
		}
		if ( iCmp != 0 )
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

int SLispOrdBuscarSiguientePtr ( SListaOrdenadaPtr * p_lisObj, SElementoPtr * p_elpDatos, int iPos )
{
	int	iRes;

	if ( ES_VALIDO ( p_elpDatos ) )
	{
		iRes = SLispOrdBuscarSiguiente ( p_lisObj, SElpDatos ( p_elpDatos ), iPos );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

/* Posicion detras de la que va p_byDatos: -1 al principio, y mas alla del ultimo
   ( iNumElementos + 1 ) al final. Los iguales van detras de los que ya estan.

   Via rapida: si no es menor que el ultimo va al final sin recorrer la lista,
   asi que insertar datos que ya llegan en orden cuesta O(1) cada uno. */
int SLispOrdBuscarSitio ( SListaOrdenadaPtr * p_lisObj, byte * p_byDatos )
{
	int				iRes;
	int				iEnc;
	int				iAlFinal;
	SElementoPtr * 	p_elpObj;

	if ( ( SLispOrdEsValida ( p_lisObj ) == 1 ) && ES_VALIDO ( p_byDatos ) )
	{
		iAlFinal = 0;
		p_elpObj = p_lisObj->p_lispContenido->p_elpUltimo;
		if ( ES_VALIDO ( p_elpObj ) )
		{
			if ( SCmpEvaluar ( p_lisObj->p_cmpObj, (void *) SElpDatos ( p_elpObj ), (void *) p_byDatos ) <= 0 )
			{
				iAlFinal = 1;
			}
		}

		if ( iAlFinal == 1 )
		{
			iRes = p_lisObj->p_lispContenido->iNumElementos + 1;
		}
		else
		{
			p_elpObj = p_lisObj->p_lispContenido->p_elpPrimero;
			iRes = -1;
			iEnc = 0;
			while ( ( iRes < p_lisObj->p_lispContenido->iNumElementos ) && ( iEnc == 0 ) &&
				ES_VALIDO ( p_elpObj ) )
			{
				int iCmp = SCmpEvaluar ( p_lisObj->p_cmpObj, (void *) SElpDatos ( p_elpObj ), (void *) p_byDatos );
				if ( iCmp <= 0 )
				{
					p_elpObj = SElpSucesor ( p_elpObj );
					iRes = iRes + 1;
				}
				else
				{
					iEnc = 1;
				}
			}
			if ( ( iEnc == 0 ) && ( iRes < p_lisObj->p_lispContenido->iNumElementos ) )
			{
				iRes = p_lisObj->p_lispContenido->iNumElementos + 1;
			}
		}
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SLispOrdEsNulo ( SListaOrdenadaPtr * p_lisObj )
{
	int iRes;

	if ( SLispOrdEsValida ( p_lisObj ) == 1 ) 
	{
		iRes = SLispEsNulo ( p_lisObj->p_lispContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLispOrdEstaEnFinal ( SListaOrdenadaPtr * p_lisObj )
{
	int iRes;

	if ( SLispOrdEsValida ( p_lisObj ) == 1 ) 
	{
		iRes = SLispEstaEnFinal ( p_lisObj->p_lispContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLispOrdEstaEnInicio ( SListaOrdenadaPtr * p_lisObj )
{
	int iRes;

	if ( SLispOrdEsValida ( p_lisObj ) == 1 ) 
	{
		iRes = SLispEstaEnInicio ( p_lisObj->p_lispContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLispOrdEliminar ( SListaOrdenadaPtr * p_lisObj )
{
	int				iRes;

	if ( SLispOrdEsValida ( p_lisObj ) == 1 ) 
	{
		iRes = SLispEliminar ( p_lisObj->p_lispContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int	SLispOrdLiberacionMemoriaActivada ( SListaOrdenadaPtr * p_lisObj )
{
	int	iRes;

	if ( SLispOrdEsValida ( p_lisObj ) == 1 ) 
	{
		iRes = SLispLiberacionMemoriaActivada ( p_lisObj->p_lispContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

void SLispOrdActivarLiberacionMemoria ( SListaOrdenadaPtr * p_lisObj )
{
	if ( SLispOrdEsValida ( p_lisObj ) == 1 ) 
	{
		SLispActivarLiberacionMemoria ( p_lisObj->p_lispContenido );
	}
}

void SLispOrdDesactivarLiberacionMemoria ( SListaOrdenadaPtr * p_lisObj )
{
	if ( SLispOrdEsValida ( p_lisObj ) == 1 ) 
	{
		SLispDesactivarLiberacionMemoria ( p_lisObj->p_lispContenido );
	}
}

/* Copia con su propio comparador ( SLispOrdCrearIgual ) y COPIAS de los datos,
   insertadas una a una con SLispOrdInsertarElem: con fDuplicar o, si es nulo,
   con MemDuplicar de iNumBytes. La copia es duena de ellas aunque el original
   no lo sea; la liberacion se desactiva mientras se inserta, por lo mismo que
   en _SLispOrdCrearDesdeLista. Si falla alguna copia, NULL. */
static SListaOrdenadaPtr * _SLispOrdDuplicar ( SListaOrdenadaPtr * p_lisObj, int iNumBytes, PFUNPBYTEPB fDuplicar )
{
	SListaOrdenadaPtr *	p_lisRes;
	SElementoPtr *		p_elpObj;
	byte *				p_byCopia;
	int					iError;

	p_lisRes = SLispOrdCrearIgual ( p_lisObj );
	if ( ES_VALIDO ( p_lisRes ) )
	{
		SLispOrdDesactivarLiberacionMemoria ( p_lisRes );
		iError = 0;
		p_elpObj = p_lisObj->p_lispContenido->p_elpPrimero;
		while ( ES_VALIDO ( p_elpObj ) && ( iError == 0 ) )
		{
			if ( ES_VALIDO ( fDuplicar ) )
			{
				p_byCopia = fDuplicar ( SElpDatos ( p_elpObj ) );
			}
			else
			{
				p_byCopia = (byte *) MemDuplicar ( SElpDatos ( p_elpObj ), iNumBytes );
			}
			if ( SLispOrdInsertarElem ( p_lisRes, p_byCopia ) != 1 )
			{
				MemLiberar ( (void **) &p_byCopia );
				iError = 1;
			}
			p_elpObj = SElpSucesor ( p_elpObj );
		}
		SLispOrdActivarLiberacionMemoria ( p_lisRes );
		if ( iError == 1 )
		{
			SLispOrdDestruir ( &p_lisRes );
		}
	}
	return ( p_lisRes );
}

SListaOrdenadaPtr * SLispOrdDuplicar ( SListaOrdenadaPtr * p_lisObj, int iNumBytes )
{
	SListaOrdenadaPtr * p_lisRes;

	if ( SLispOrdEsValida ( p_lisObj ) == 1 )
	{
		if ( iNumBytes > 0 )
		{
			p_lisRes = _SLispOrdDuplicar ( p_lisObj, iNumBytes, NULL );
		}
		else
		{
			p_lisRes = NULL;
		}
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

SListaPtr * SLispOrdDuplicarLista ( SListaOrdenadaPtr * p_lisObj, int iNumBytes )
{
	SListaPtr * p_lisRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_lisRes = SLispDuplicar ( p_lisObj->p_lispContenido, iNumBytes );
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

SListaOrdenadaPtr * SLispOrdDuplicarExt ( SListaOrdenadaPtr * p_lisObj, PFUNPBYTEPB fDuplicar )
{
	SListaOrdenadaPtr * p_lisRes;

	if ( SLispOrdEsValida ( p_lisObj ) == 1 )
	{
		if ( ES_VALIDO ( fDuplicar ) )
		{
			p_lisRes = _SLispOrdDuplicar ( p_lisObj, 0, fDuplicar );
		}
		else
		{
			p_lisRes = NULL;
		}
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

SListaPtr * SLispOrdDuplicarListaExt ( SListaOrdenadaPtr * p_lisObj, PFUNPBYTEPB fDuplicar )
{
	SListaPtr * p_lisRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_lisRes = SLispDuplicarExt ( p_lisObj->p_lispContenido, fDuplicar );
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}


int SLispOrdExistenTodos ( SListaOrdenadaPtr * p_lisObj, SListaOrdenadaPtr * p_lisValores )
{
	int iRes;

	if ( SLispOrdEsValida ( p_lisValores ) == 1 )
	{
		iRes = SLispOrdExistenTodosLista ( p_lisObj, p_lisValores->p_lispContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLispOrdExisteAlguno ( SListaOrdenadaPtr * p_lisObj, SListaOrdenadaPtr * p_lisValores )
{
	int iRes;

	if ( SLispOrdEsValida ( p_lisValores ) == 1 )
	{
		iRes = SLispOrdExisteAlgunoLista ( p_lisObj, p_lisValores->p_lispContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

/* Con p_lisValores vacia, 1: no falta ninguno. */
int SLispOrdExistenTodosLista ( SListaOrdenadaPtr * p_lisObj, SListaPtr * p_lisValores )
{
	SElementoPtr * 	p_elpObj;
	int				iRes;

	if ( SLispOrdEsValida ( p_lisObj ) == 1 )
	{
		if ( SLispEsValida ( p_lisValores ) == 1 )
		{
			iRes = 1;
			p_elpObj = p_lisValores->p_elpPrimero;
			while ( ES_VALIDO ( p_elpObj ) && ( iRes == 1 ) )
			{
				/* SLisOrdBuscar da la posicion o -1, no un booleano. */
				if ( SLispOrdBuscar ( p_lisObj, SElpDatos ( p_elpObj ) ) < 0 )
				{
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

int SLispOrdExisteAlgunoLista ( SListaOrdenadaPtr * p_lisObj, SListaPtr * p_lisValores )
{
	SElementoPtr * 	p_elpObj;
	int				iRes;

	if ( SLispOrdEsValida ( p_lisObj ) == 1 )
	{
		if ( SLispEsValida ( p_lisValores ) == 1 )
		{
			iRes = 0;
			p_elpObj = p_lisValores->p_elpPrimero;
			while ( ES_VALIDO ( p_elpObj ) && ( iRes == 0 ) )
			{
				if ( SLispOrdBuscar ( p_lisObj, SElpDatos ( p_elpObj ) ) >= 0 )
				{
					iRes = 1;
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

int SLispOrdEliminarListaOrd ( SListaOrdenadaPtr * p_lisObj, SListaOrdenadaPtr * p_lisValores )
{
	int	iRes;

	if ( SLispOrdEsValida ( p_lisValores ) == 1 )
	{
		iRes = SLispOrdEliminarLista ( p_lisObj, p_lisValores->p_lispContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

/* Elimina ( destruye ) de p_lisObj la primera aparicion de cada valor de
   p_lisValores: un valor repetido en p_lisValores elimina dos apariciones. Lo
   que no se encuentra se ignora. p_lisValores no se toca. Como en
   ExtraerLista, la igualdad la decide el comparador de p_lisObj.

   Devuelve 1 si ha podido eliminar todo lo encontrado; si falla una eliminacion
   se para y devuelve 0, y lo eliminado hasta ahi se queda eliminado. Con la
   misma lista en los dos argumentos se devuelve 0 sin tocar nada.

   Los datos se liberan o no segun la liberacion de p_lisObj. */
int SLispOrdEliminarLista ( SListaOrdenadaPtr * p_lisObj, SListaPtr * p_lisValores )
{
	SElementoPtr *	p_elpObj;
	int				iPos;
	int				iRes;

	if ( SLispOrdEsValida ( p_lisObj ) == 1 )
	{
		if ( SLispEsValida ( p_lisValores ) == 1 )
		{
			if ( p_lisObj->p_lispContenido != p_lisValores )
			{
				iRes = 1;
				p_elpObj = p_lisValores->p_elpPrimero;
				while ( ES_VALIDO ( p_elpObj ) && ( iRes == 1 ) )
				{
					iPos = SLispOrdBuscar ( p_lisObj, SElpDatos ( p_elpObj ) );
					if ( iPos >= 0 )
					{
						if ( SLispOrdEliminarElem ( p_lisObj, iPos ) != 1 )
						{
							iRes = 0;
						}
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
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int SLispOrdInsertarListaOrd ( SListaOrdenadaPtr * p_lisObj, SListaOrdenadaPtr * p_lisValores )
{
	int iRes;

	if ( SLispOrdEsValida ( p_lisValores ) == 1 )
	{
		iRes = SLispOrdInsertarLista ( p_lisObj, p_lisValores->p_lispContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

/* MUEVE los elementos de p_lisValores, cada uno a su sitio; p_lisValores queda
   vacia. Se sacan siempre de la cabeza, asi que si p_lisValores es el
   contenido de otra lista ordenada sigue ordenada mientras se vacia.

   Si un elemento no se puede insertar se devuelve a la cabeza de p_lisValores
   y se para con el error ERR_INSERCION_LISTA: lo movido hasta ahi se queda
   movido y lo que falta sigue en p_lisValores, sin perder nada.

   Con la misma lista en los dos argumentos se devuelve 0 sin tocar nada. */
int SLispOrdInsertarLista ( SListaOrdenadaPtr * p_lisObj, SListaPtr * p_lisValores )
{
	SElementoPtr * 	p_elpObj;
	int				iRes;

	if ( SLispOrdEsValida ( p_lisObj ) == 1 )
	{
		if ( SLispEsValida ( p_lisValores ) == 1 )
		{
			if ( p_lisObj->p_lispContenido != p_lisValores )
			{
				iRes = 1;
				while ( ( iRes == 1 ) && ( p_lisValores->iNumElementos > 0 ) )
				{
					SLispInicio ( p_lisValores );
					p_elpObj = _SLispExtraerPtr ( p_lisValores );
					if ( ES_VALIDO ( p_elpObj ) )
					{
						if ( _SLispOrdInsertarElemPtr ( p_lisObj, p_elpObj ) != 1 )
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
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLispOrdInsertarListaOrdDup ( SListaOrdenadaPtr * p_lisObj, SListaOrdenadaPtr * p_lisValores, int iNumBytes )
{
	int iRes;

	if ( SLispOrdEsValida ( p_lisValores ) == 1 )
	{
		iRes = SLispOrdInsertarListaDup ( p_lisObj, p_lisValores->p_lispContenido, iNumBytes );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

/* Las Dup insertan COPIAS ( SElpDuplicar ) y no tocan p_lisValores. Con la
   misma lista en los dos argumentos se devuelve 0: se insertaria en la cadena
   que se esta recorriendo. Si falla una copia ( ERR_COPIA_OBJETO ) o una
   insercion ( ERR_INSERCION_LISTA ) se para, y lo insertado hasta ahi se queda. */
int SLispOrdInsertarListaDup ( SListaOrdenadaPtr * p_lisObj, SListaPtr * p_lisValores, int iNumBytes )
{
	SElementoPtr * 	p_elpObj;
	SElementoPtr * 	p_elpNuevo;
	int				iRes;

	if ( SLispOrdEsValida ( p_lisObj ) == 1 )
	{
		if ( SLispEsValida ( p_lisValores ) == 1 )
		{
			if ( p_lisObj->p_lispContenido != p_lisValores )
			{
				iRes = 1;
				p_elpObj = p_lisValores->p_elpPrimero;
				while ( ES_VALIDO ( p_elpObj ) && ( iRes == 1 ) )
				{
					p_elpNuevo = SElpDuplicar ( p_elpObj, iNumBytes );
					if ( ES_NULO ( p_elpNuevo ) )
					{
						ERROR_ESTABLECER ( ERR_COPIA_OBJETO );
						iRes = 0;
					}
					else if ( _SLispOrdInsertarElemPtr ( p_lisObj, p_elpNuevo ) != 1 )
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
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLispOrdInsertarListaOrdDupExt ( SListaOrdenadaPtr * p_lisObj, SListaOrdenadaPtr * p_lisValores, PFUNPBYTEPB fDuplicar )
{
	int iRes;

	if ( SLispOrdEsValida ( p_lisValores ) == 1 )
	{
		iRes = SLispOrdInsertarListaDupExt ( p_lisObj, p_lisValores->p_lispContenido, fDuplicar );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLispOrdInsertarListaDupExt ( SListaOrdenadaPtr * p_lisObj, SListaPtr * p_lisValores, PFUNPBYTEPB fDuplicar )
{
	SElementoPtr * 	p_elpObj;
	SElementoPtr * 	p_elpNuevo;
	int				iRes;

	if ( SLispOrdEsValida ( p_lisObj ) == 1 )
	{
		if ( SLispEsValida ( p_lisValores ) == 1 )
		{
			if ( p_lisObj->p_lispContenido != p_lisValores )
			{
				iRes = 1;
				p_elpObj = p_lisValores->p_elpPrimero;
				while ( ES_VALIDO ( p_elpObj ) && ( iRes == 1 ) )
				{
					p_elpNuevo = SElpDuplicarExt ( p_elpObj, fDuplicar );
					if ( ES_NULO ( p_elpNuevo ) )
					{
						ERROR_ESTABLECER ( ERR_COPIA_OBJETO );
						iRes = 0;
					}
					else if ( _SLispOrdInsertarElemPtr ( p_lisObj, p_elpNuevo ) != 1 )
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
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SListaOrdenadaPtr * SLispOrdExtraerListaOrd ( SListaOrdenadaPtr * p_lisObj, SListaOrdenadaPtr * p_lisValores )
{
	SListaOrdenadaPtr * p_lisRes;

	if ( SLispOrdEsValida ( p_lisValores ) == 1 )
	{
		p_lisRes = SLispOrdExtraerLista ( p_lisObj, p_lisValores->p_lispContenido );
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

/* Saca de p_lisObj, a una lista nueva con una copia de su comparador, la
   primera aparicion de cada valor de p_lisValores: un valor repetido en
   p_lisValores saca dos apariciones. Lo que no se encuentra se ignora. Los
   elementos se mueven, no se copian, y la lista nueva los ordena y hereda la
   liberacion de p_lisObj: si p_lisObj no era duena de sus datos, la nueva
   tampoco.

   Si un elemento no se puede insertar en la nueva, vuelve a su sitio en
   p_lisObj y se para: se devuelve lo extraido hasta ahi, con el error
   ERR_INSERCION_LISTA. Lo mismo si no se puede sacar uno que se ha encontrado.

   Con la misma lista en los dos argumentos se devuelve NULL. */
SListaOrdenadaPtr * SLispOrdExtraerLista ( SListaOrdenadaPtr * p_lisObj, SListaPtr * p_lisValores )
{
	SListaOrdenadaPtr *	p_lisRes;
	SElementoPtr *		p_elpObj;
	SElementoPtr *		p_elpExt;
	int					iPos;
	int					iError;

	if ( SLispOrdEsValida ( p_lisObj ) == 1 )
	{
		if ( SLispEsValida ( p_lisValores ) == 1 )
		{
			if ( p_lisObj->p_lispContenido != p_lisValores )
			{
				p_lisRes = SLispOrdCrearIgual ( p_lisObj );
				if ( ES_VALIDO ( p_lisRes ) )
				{
					if ( SLispOrdLiberacionMemoriaActivada ( p_lisObj ) == 0 )
					{
						SLispOrdDesactivarLiberacionMemoria ( p_lisRes );
					}
					iError = 0;
					p_elpObj = p_lisValores->p_elpPrimero;
					while ( ES_VALIDO ( p_elpObj ) && ( iError == 0 ) )
					{
						iPos = SLispOrdBuscar ( p_lisObj, SElpDatos ( p_elpObj ) );
						if ( iPos >= 0 )
						{
							p_elpExt = _SLispOrdExtraerElemPtr ( p_lisObj, iPos );
							if ( ES_VALIDO ( p_elpExt ) )
							{
								if ( _SLispOrdInsertarElemPtr ( p_lisRes, p_elpExt ) != 1 )
								{
									if ( _SLispOrdInsertarElemPtr ( p_lisObj, p_elpExt ) != 1 )
									{
										SElpDestruir ( &p_elpExt );
									}
									iError = 1;
								}
							}
							else
							{
								iError = 1;
							}
						}
						p_elpObj = SElpSucesor ( p_elpObj );
					}
					if ( iError == 1 )
					{
						ERROR_ESTABLECER_FORM ( ERR_INSERCION_LISTA, ERR_TXT_INSERCION_LISTA );
					}
				}
			}
			else
			{
				p_lisRes = NULL;
			}
		}
		else
		{
			p_lisRes = NULL;
		}
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

/* Interseccion y diferencia. La igualdad la decide el comparador de
   p_lisValores1, y el resultado lleva COPIAS: con fDuplicar o, si es nulo, de
   iNumBytes. */

/* 1 si en p_lisValores hay algun dato igual a p_byDatos segun p_cmpObj. */
static int _SLispOrdEstaEnLista ( SComparador * p_cmpObj, SListaPtr * p_lisValores, byte * p_byDatos )
{
	SElementoPtr *	p_elpObj;
	int				iRes;

	iRes = 0;
	p_elpObj = p_lisValores->p_elpPrimero;
	while ( ES_VALIDO ( p_elpObj ) && ( iRes == 0 ) )
	{
		if ( SCmpEvaluar ( p_cmpObj, (void *) SElpDatos ( p_elpObj ), (void *) p_byDatos ) == 0 )
		{
			iRes = 1;
		}
		p_elpObj = SElpSucesor ( p_elpObj );
	}
	return ( iRes );
}

/* Copia p_elpObj en p_lisRes. 1 si sale bien; si no, no queda nada a medias. */
static int _SLispOrdInsertarCopia ( SListaOrdenadaPtr * p_lisRes, SElementoPtr * p_elpObj, int iNumBytes, PFUNPBYTEPB fDuplicar )
{
	SElementoPtr *	p_elpNuevo;
	int				iRes;

	if ( ES_VALIDO ( fDuplicar ) )
	{
		p_elpNuevo = SElpDuplicarExt ( p_elpObj, fDuplicar );
	}
	else
	{
		p_elpNuevo = SElpDuplicar ( p_elpObj, iNumBytes );
	}
	iRes = _SLispOrdInsertarElemPtr ( p_lisRes, p_elpNuevo );
	if ( iRes != 1 )
	{
		SElpDestruir ( &p_elpNuevo );
	}
	return ( iRes );
}

/* Los de p_lisValores1 que estan ( iEstan = 1 ) o no estan ( iEstan = 0 ) en
   p_lisValores2, que puede estar en cualquier orden: cada elemento de
   p_lisValores1 se busca en toda p_lisValores2, O(n*m). Si falla una copia,
   NULL. */
static SListaOrdenadaPtr * _SLispOrdFiltrar ( SListaOrdenadaPtr * p_lisValores1, SListaPtr * p_lisValores2, int iEstan, int iNumBytes, PFUNPBYTEPB fDuplicar )
{
	SListaOrdenadaPtr *	p_lisRes;
	SElementoPtr *		p_elpObj;
	int					iError;

	p_lisRes = SLispOrdCrearIgual ( p_lisValores1 );
	if ( ES_VALIDO ( p_lisRes ) )
	{
		iError = 0;
		p_elpObj = p_lisValores1->p_lispContenido->p_elpPrimero;
		while ( ES_VALIDO ( p_elpObj ) && ( iError == 0 ) )
		{
			if ( _SLispOrdEstaEnLista ( p_lisValores1->p_cmpObj, p_lisValores2, SElpDatos ( p_elpObj ) ) == iEstan )
			{
				if ( _SLispOrdInsertarCopia ( p_lisRes, p_elpObj, iNumBytes, fDuplicar ) != 1 )
				{
					iError = 1;
				}
			}
			p_elpObj = SElpSucesor ( p_elpObj );
		}
		if ( iError == 1 )
		{
			SLispOrdDestruir ( &p_lisRes );
		}
	}
	return ( p_lisRes );
}

/* Como _SLispOrdFiltrar, pero p_lisValores2 esta ordenada con el mismo criterio
   que p_lisValores1, asi que se recorren las dos en paralelo, O(n+m), sin
   volver atras: para cada elemento de p_lisValores1 se salta en p_lisValores2
   lo que es menor que el, y esta si el primero que no es menor es igual. Los
   repetidos de p_lisValores1 se comparan todos con el mismo, asi que salen
   todos, como en _SLispOrdFiltrar. Los cursores no se tocan. */
static SListaOrdenadaPtr * _SLispOrdFiltrarEnParalelo ( SListaOrdenadaPtr * p_lisValores1, SListaPtr * p_lisValores2, int iEstan, int iNumBytes, PFUNPBYTEPB fDuplicar )
{
	SListaOrdenadaPtr *	p_lisRes;
	SElementoPtr *		p_elpObj1;
	SElementoPtr *		p_elpObj2;
	int					iCmp;
	int					iEsta;
	int					iError;

	p_lisRes = SLispOrdCrearIgual ( p_lisValores1 );
	if ( ES_VALIDO ( p_lisRes ) )
	{
		iError = 0;
		p_elpObj1 = p_lisValores1->p_lispContenido->p_elpPrimero;
		p_elpObj2 = p_lisValores2->p_elpPrimero;
		while ( ES_VALIDO ( p_elpObj1 ) && ( iError == 0 ) )
		{
			iCmp = 1;
			while ( ES_VALIDO ( p_elpObj2 ) && ( iCmp > 0 ) )
			{
				iCmp = SCmpEvaluar ( p_lisValores1->p_cmpObj, (void *) SElpDatos ( p_elpObj1 ), (void *) SElpDatos ( p_elpObj2 ) );
				if ( iCmp > 0 )
				{
					p_elpObj2 = SElpSucesor ( p_elpObj2 );
				}
			}
			/* Si p_lisValores2 se ha acabado, iCmp se ha quedado > 0. */
			if ( iCmp == 0 )
			{
				iEsta = 1;
			}
			else
			{
				iEsta = 0;
			}
			if ( iEsta == iEstan )
			{
				if ( _SLispOrdInsertarCopia ( p_lisRes, p_elpObj1, iNumBytes, fDuplicar ) != 1 )
				{
					iError = 1;
				}
			}
			p_elpObj1 = SElpSucesor ( p_elpObj1 );
		}
		if ( iError == 1 )
		{
			SLispOrdDestruir ( &p_lisRes );
		}
	}
	return ( p_lisRes );
}

/* Elige el recorrido: en paralelo si p_lisValores2 es otra lista ordenada con
   la misma funcion de comparacion; si no, buscando cada elemento. p_lisValores2
   es la SListaOrdenadaPtr, o NULL si es una SListaPtr suelta ( p_lisContenido2 ).
   Hace falta fDuplicar o, si es nulo, iNumBytes > 0. */
static SListaOrdenadaPtr * _SLispOrdFiltrarElegir ( SListaOrdenadaPtr * p_lisValores1, SListaOrdenadaPtr * p_lisValores2, SListaPtr * p_lisContenido2, int iEstan, int iNumBytes, PFUNPBYTEPB fDuplicar )
{
	SListaOrdenadaPtr *	p_lisRes;
	int					iCopiable;

	if ( ES_VALIDO ( fDuplicar ) )
	{
		iCopiable = 1;
	}
	else if ( iNumBytes > 0 )
	{
		iCopiable = 1;
	}
	else
	{
		iCopiable = 0;
	}

	if ( SLispOrdEsValida ( p_lisValores1 ) == 1 )
	{
		if ( SLispEsValida ( p_lisContenido2 ) == 1 )
		{
			if ( iCopiable == 1 )
			{
				if ( ES_VALIDO ( p_lisValores2 ) &&
					 ( p_lisValores2->p_cmpObj->fComparar == p_lisValores1->p_cmpObj->fComparar ) )
				{
					p_lisRes = _SLispOrdFiltrarEnParalelo ( p_lisValores1, p_lisContenido2, iEstan, iNumBytes, fDuplicar );
				}
				else
				{
					p_lisRes = _SLispOrdFiltrar ( p_lisValores1, p_lisContenido2, iEstan, iNumBytes, fDuplicar );
				}
			}
			else
			{
				p_lisRes = NULL;
			}
		}
		else
		{
			p_lisRes = NULL;
		}
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

/* Las que generan una lista nueva la devuelven con COPIAS y una copia del
   comparador de p_lisValores1; si algo falla, NULL. */
SListaOrdenadaPtr * SLispOrdUnion ( SListaOrdenadaPtr * p_lisValores1, SListaOrdenadaPtr * p_lisValores2, int iNumBytes )
{
	SListaOrdenadaPtr * p_lisRes;

	if ( SLispOrdEsValida ( p_lisValores2 ) == 1 )
	{
		p_lisRes = SLispOrdUnionLista ( p_lisValores1, p_lisValores2->p_lispContenido, iNumBytes );
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

SListaOrdenadaPtr * SLispOrdInterseccion ( SListaOrdenadaPtr * p_lisValores1, SListaOrdenadaPtr * p_lisValores2, int iNumBytes )
{
	SListaOrdenadaPtr * p_lisRes;

	if ( SLispOrdEsValida ( p_lisValores2 ) == 1 )
	{
		p_lisRes = _SLispOrdFiltrarElegir ( p_lisValores1, p_lisValores2, p_lisValores2->p_lispContenido, 1, iNumBytes, NULL );
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

SListaOrdenadaPtr * SLispOrdDiferencia ( SListaOrdenadaPtr * p_lisValores1, SListaOrdenadaPtr * p_lisValores2, int iNumBytes )
{
	SListaOrdenadaPtr * p_lisRes;

	if ( SLispOrdEsValida ( p_lisValores2 ) == 1 )
	{
		p_lisRes = _SLispOrdFiltrarElegir ( p_lisValores1, p_lisValores2, p_lisValores2->p_lispContenido, 0, iNumBytes, NULL );
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

/* Todos los de las dos, ordenados: lo que este en ambas sale dos veces. */
SListaOrdenadaPtr * SLispOrdUnionLista ( SListaOrdenadaPtr * p_lisValores1, SListaPtr * p_lisValores2, int iNumBytes )
{
	SListaOrdenadaPtr * p_lisRes;

	if ( SLispOrdEsValida ( p_lisValores1 ) == 1 )
	{
		if ( SLispEsValida ( p_lisValores2 ) == 1 )
		{
			p_lisRes = SLispOrdDuplicar ( p_lisValores1, iNumBytes );
			if ( ES_VALIDO ( p_lisRes ) )
			{
				if ( SLispOrdInsertarListaDup ( p_lisRes, p_lisValores2, iNumBytes ) != 1 )
				{
					SLispOrdDestruir ( &p_lisRes );
				}
			}
		}
		else
		{
			p_lisRes = NULL;
		}
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

/* Los de p_lisValores1 que estan en p_lisValores2. */
SListaOrdenadaPtr * SLispOrdInterseccionLista ( SListaOrdenadaPtr * p_lisValores1, SListaPtr * p_lisValores2, int iNumBytes )
{
	return ( _SLispOrdFiltrarElegir ( p_lisValores1, NULL, p_lisValores2, 1, iNumBytes, NULL ) );
}

/* Los de p_lisValores1 que NO estan en p_lisValores2. */
SListaOrdenadaPtr * SLispOrdDiferenciaLista ( SListaOrdenadaPtr * p_lisValores1, SListaPtr * p_lisValores2, int iNumBytes )
{
	return ( _SLispOrdFiltrarElegir ( p_lisValores1, NULL, p_lisValores2, 0, iNumBytes, NULL ) );
}

SListaOrdenadaPtr * SLispOrdUnionExt ( SListaOrdenadaPtr * p_lisValores1, SListaOrdenadaPtr * p_lisValores2, PFUNPBYTEPB fDuplicar )
{
	SListaOrdenadaPtr * p_lisRes;

	if ( SLispOrdEsValida ( p_lisValores2 ) == 1 )
	{
		p_lisRes = SLispOrdUnionListaExt ( p_lisValores1, p_lisValores2->p_lispContenido, fDuplicar );
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

SListaOrdenadaPtr * SLispOrdInterseccionExt ( SListaOrdenadaPtr * p_lisValores1, SListaOrdenadaPtr * p_lisValores2, PFUNPBYTEPB fDuplicar )
{
	SListaOrdenadaPtr * p_lisRes;

	if ( SLispOrdEsValida ( p_lisValores2 ) == 1 )
	{
		p_lisRes = _SLispOrdFiltrarElegir ( p_lisValores1, p_lisValores2, p_lisValores2->p_lispContenido, 1, 0, fDuplicar );
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

SListaOrdenadaPtr * SLispOrdDiferenciaExt ( SListaOrdenadaPtr * p_lisValores1, SListaOrdenadaPtr * p_lisValores2, PFUNPBYTEPB fDuplicar )
{
	SListaOrdenadaPtr * p_lisRes;

	if ( SLispOrdEsValida ( p_lisValores2 ) == 1 )
	{
		p_lisRes = _SLispOrdFiltrarElegir ( p_lisValores1, p_lisValores2, p_lisValores2->p_lispContenido, 0, 0, fDuplicar );
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

/* Todos los de las dos, ordenados: lo que este en ambas sale dos veces. */
SListaOrdenadaPtr * SLispOrdUnionListaExt ( SListaOrdenadaPtr * p_lisValores1, SListaPtr * p_lisValores2, PFUNPBYTEPB fDuplicar )
{
	SListaOrdenadaPtr * p_lisRes;

	if ( SLispOrdEsValida ( p_lisValores1 ) == 1 )
	{
		if ( SLispEsValida ( p_lisValores2 ) == 1 )
		{
			p_lisRes = SLispOrdDuplicarExt ( p_lisValores1, fDuplicar );
			if ( ES_VALIDO ( p_lisRes ) )
			{
				if ( SLispOrdInsertarListaDupExt ( p_lisRes, p_lisValores2, fDuplicar ) != 1 )
				{
					SLispOrdDestruir ( &p_lisRes );
				}
			}
		}
		else
		{
			p_lisRes = NULL;
		}
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

/* Los de p_lisValores1 que estan en p_lisValores2. */
SListaOrdenadaPtr * SLispOrdInterseccionListaExt ( SListaOrdenadaPtr * p_lisValores1, SListaPtr * p_lisValores2, PFUNPBYTEPB fDuplicar )
{
	return ( _SLispOrdFiltrarElegir ( p_lisValores1, NULL, p_lisValores2, 1, 0, fDuplicar ) );
}

/* Los de p_lisValores1 que NO estan en p_lisValores2. */
SListaOrdenadaPtr * SLispOrdDiferenciaListaExt ( SListaOrdenadaPtr * p_lisValores1, SListaPtr * p_lisValores2, PFUNPBYTEPB fDuplicar )
{
	return ( _SLispOrdFiltrarElegir ( p_lisValores1, NULL, p_lisValores2, 0, 0, fDuplicar ) );
}

SElementoPtr * _SLispOrdExtraerElemPtr ( SListaOrdenadaPtr * p_lisObj, int iElem )
{
	SElementoPtr * p_elpRes;

	if ( SLispOrdEsValida ( p_lisObj ) == 1 )
	{
		p_elpRes = _SLispExtraerElemPtr ( p_lisObj->p_lispContenido, iElem );
	}
	else
	{
		p_elpRes = NULL;
	}
	return ( p_elpRes );
}

/*
SElementoPtr * _SLispOrdExtraerPtr ( SListaOrdenadaPtr * p_lisObj )
{
	SElementoPtr * p_elpRes;

	if ( SLispOrdEsValida ( p_lisObj ) == 1 )
	{
		p_elpRes = _SLispExtraerPtr ( p_lisObj->p_lispContenido );
	}
	else
	{
		p_elpRes = NULL;
	}
	return ( p_elpRes );
}
*/

int _SLispOrdInsertarElemPtr ( SListaOrdenadaPtr * p_lisObj, SElementoPtr * p_elpDatos )
{
	int iRes;
	int iPosAnt;

	if ( ( SLispOrdEsValida ( p_lisObj ) == 1 ) && ES_VALIDO ( p_elpDatos ) )
	{
		iPosAnt = SLispOrdBuscarSitio ( p_lisObj, SElpDatos ( p_elpDatos ) );

		if ( iPosAnt < 0 ) 
		{
			SLispInicio ( p_lisObj->p_lispContenido );
			iRes = _SLispInsertarDelantePtr ( p_lisObj->p_lispContenido, p_elpDatos );
		}
		else if ( iPosAnt >= p_lisObj->p_lispContenido->iNumElementos )
		{
			SLispFinal ( p_lisObj->p_lispContenido );
			iRes = _SLispInsertarDetrasPtr ( p_lisObj->p_lispContenido, p_elpDatos );
		}
		else  
		{
			SLispMoverA ( p_lisObj->p_lispContenido, iPosAnt );
			if ( ES_NULO ( p_lisObj->p_lispContenido->p_elpActual ) ) 
			{
				iRes = 0;
			}
			else 
			{
				iRes = _SLispInsertarPtr ( p_lisObj->p_lispContenido, p_elpDatos );
			}
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

