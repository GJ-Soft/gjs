#include "SListaOrdenada.h"


#include "TiposBasicosConfig.h"


int SLisOrdBuscarSitio ( SListaOrdenada * p_lisObj, SBloque * p_blqDatos );


SListaOrdenada * SLisOrdCrear ( PFUNINTPVPV fComparar )
{
	SListaOrdenada *	p_lisObj;
	SComparador *		p_cmpObj;

	p_cmpObj = SCmpCrear ( fComparar );
	p_lisObj = SLisOrdEncapsular ( p_cmpObj );
	if ( ES_NULO ( p_lisObj ) )
	{
		SCmpDestruir ( &p_cmpObj );
	}
	return ( p_lisObj );
}

/* Lista vacia que se queda con p_cmpObj: desde ahi lo destruye SLisOrdDestruir.
   Si falla devuelve NULL y p_cmpObj sigue siendo del llamante. */
SListaOrdenada * SLisOrdEncapsular ( SComparador * p_cmpObj )
{
	SListaOrdenada * p_lisObj;

	if ( SCmpEsValido ( p_cmpObj ) == 1 )
	{
		p_lisObj = (SListaOrdenada *) MemReservar ( sizeof ( SListaOrdenada ) );
		if ( ES_VALIDO ( p_lisObj ) )
		{
			p_lisObj->p_lisContenido = SLisCrear ();
			if ( ES_VALIDO ( p_lisObj->p_lisContenido ) )
			{
				p_lisObj->p_cmpObj = p_cmpObj;
			}
			else
			{
				/* No con SLisOrdDestruir: destruiria p_cmpObj, que sigue
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

/* Lista ordenada con COPIAS ( SElmDuplicar ) de los elementos de p_lisValores,
   que no se toca. Con p_lisValores no valida, NULL. Si falla alguna copia se
   devuelve lo copiado hasta ahi, ordenado, con el error ERR_COPIA_LISTA. */
SListaOrdenada * SLisOrdCrearDesdeLista ( SLista * p_lisValores, PFUNINTPVPV fComparar )
{
	SListaOrdenada *	p_lisObj;
	SElemento *			p_elmObj;
	SElemento *			p_elmNuevo;
	int					iError;

	if ( SLisEsValida ( p_lisValores ) == 1 )
	{
		p_lisObj = SLisOrdCrear ( fComparar );
		if ( ES_VALIDO ( p_lisObj ) )
		{
			iError = 0;
			p_elmObj = p_lisValores->p_elmPrimero;
			while ( ES_VALIDO ( p_elmObj ) && ( iError == 0 ) )
			{
				p_elmNuevo = SElmDuplicar ( p_elmObj );
				if ( SLisOrdInsertarElem ( p_lisObj, p_elmNuevo ) != 1 )
				{
					SElmDestruir ( &p_elmNuevo );
					iError = 1;
				}
				p_elmObj = SElmSucesor ( p_elmObj );
			}
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

/* Lista vacia con una copia ( SCmpDuplicar ) del comparador de p_lisEjemplo,
   que no se toca. Con p_lisEjemplo no valida, NULL. */
SListaOrdenada * SLisOrdCrearIgual ( SListaOrdenada * p_lisEjemplo )
{
	SListaOrdenada *	p_lisObj;
	SComparador *		p_cmpObj;

	if ( SLisOrdEsValida ( p_lisEjemplo ) == 1 )
	{
		p_cmpObj = SCmpDuplicar ( p_lisEjemplo->p_cmpObj );
		p_lisObj = SLisOrdEncapsular ( p_cmpObj );
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

void SLisOrdDestruir ( SListaOrdenada ** p_p_lisObj )
{
	SListaOrdenada * p_lisObj;
	
	if ( ES_VALIDO ( p_p_lisObj ) )
	{
		p_lisObj = *p_p_lisObj;

		if ( ES_VALIDO ( p_lisObj ) )
		{
			SLisDestruir ( &(p_lisObj->p_lisContenido) );
			SCmpDestruir ( &(p_lisObj->p_cmpObj) );
			MemLiberar ( (void **) p_p_lisObj );
		}
	}
}

int SLisOrdEsValida ( SListaOrdenada * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( ( SLisEsValida ( p_lisObj->p_lisContenido ) == 1 ) &&
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

int SLisOrdNumElementos ( SListaOrdenada * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLisNumElementos ( p_lisObj->p_lisContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisOrdEstaVacia ( SListaOrdenada * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLisEstaVacia ( p_lisObj->p_lisContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SElemento * SLisOrdElemento ( SListaOrdenada * p_lisObj, int iElem )
{
	SElemento * p_elmRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_elmRes = SLisElemento ( p_lisObj->p_lisContenido, iElem );
	}
	else
	{
		p_elmRes = NULL;
	}
	return ( p_elmRes );
}

int SLisOrdInsertarElem ( SListaOrdenada * p_lisObj, SElemento * p_elmObj )
{
	int iRes;
	int iPosAnt;

	if ( ( SLisOrdEsValida ( p_lisObj ) == 1 ) && ( SElmEsValido ( p_elmObj ) == 1 ) )
	{
		iPosAnt = SLisOrdBuscarSitio ( p_lisObj, SElmDatos ( p_elmObj ) );

		if ( iPosAnt < 0 ) 
		{
			SLisInicio ( p_lisObj->p_lisContenido );
			iRes = SLisInsertarDelante ( p_lisObj->p_lisContenido, p_elmObj );
		}
		else if ( iPosAnt >= p_lisObj->p_lisContenido->iNumElementos )
		{
			SLisFinal ( p_lisObj->p_lisContenido );
			iRes = SLisInsertarDetras ( p_lisObj->p_lisContenido, p_elmObj );
		}
		else  
		{
			SLisMoverA ( p_lisObj->p_lisContenido, iPosAnt );
			if ( ES_NULO ( p_lisObj->p_lisContenido->p_elmActual ) ) 
			{
				iRes = 0;
			}
			else 
			{
				iRes = SLisInsertar ( p_lisObj->p_lisContenido, p_elmObj );
			}
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisOrdEliminarElem ( SListaOrdenada * p_lisObj, int iElem )
{
	int	iRes;

	if ( SLisOrdEsValida ( p_lisObj ) == 1 ) 
	{
		iRes = SLisEliminarElem ( p_lisObj->p_lisContenido, iElem );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SElemento * SLisOrdExtraerElem ( SListaOrdenada * p_lisObj, int iElem )
{
	SElemento * p_elmRes;

	if ( SLisOrdEsValida ( p_lisObj ) == 1 ) 
	{
		p_elmRes = SLisExtraerElem ( p_lisObj->p_lisContenido, iElem );
	}
	else
	{
		p_elmRes = NULL;
	}
	return ( p_elmRes );
}

int SLisOrdVaciar ( SListaOrdenada * p_lisObj )
{
	int	iRes;

	if ( SLisOrdEsValida ( p_lisObj ) == 1 ) 
	{
		iRes = SLisVaciar ( p_lisObj->p_lisContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisOrdPosicion ( SListaOrdenada * p_lisObj )
{
	int	iRes;

	if ( SLisOrdEsValida ( p_lisObj ) == 1 ) 
	{
		iRes = SLisPosicion ( p_lisObj->p_lisContenido );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

SElemento * SLisOrdActual ( SListaOrdenada * p_lisObj )
{
	SElemento * p_elmRes;

	if ( SLisOrdEsValida ( p_lisObj ) == 1 ) 
	{
		p_elmRes = SLisActual ( p_lisObj->p_lisContenido );
	}
	else
	{
		p_elmRes = NULL;
	}
	return ( p_elmRes );
}

int SLisOrdEstaPosicionada ( SListaOrdenada * p_lisObj )
{
	int	iRes;

	if ( SLisOrdEsValida ( p_lisObj ) == 1 )
	{
		iRes = SLisEstaPosicionada ( p_lisObj->p_lisContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


void SLisOrdInicio ( SListaOrdenada * p_lisObj )
{
	if ( SLisOrdEsValida ( p_lisObj ) == 1 ) 
	{
		SLisInicio ( p_lisObj->p_lisContenido );
	}
}

void SLisOrdFinal ( SListaOrdenada * p_lisObj )
{
	if ( SLisOrdEsValida ( p_lisObj ) == 1 ) 
	{
		SLisFinal ( p_lisObj->p_lisContenido );
	}
}

void SLisOrdSiguiente ( SListaOrdenada * p_lisObj )
{
	if ( SLisOrdEsValida ( p_lisObj ) == 1 ) 
	{
		SLisSiguiente ( p_lisObj->p_lisContenido );
	}
}

void SLisOrdAnterior ( SListaOrdenada * p_lisObj )
{
	if ( SLisOrdEsValida ( p_lisObj ) == 1 ) 
	{
		SLisAnterior ( p_lisObj->p_lisContenido );
	}
}

void SLisOrdMoverA ( SListaOrdenada * p_lisObj, int iElem )
{
	if ( SLisOrdEsValida ( p_lisObj ) == 1 ) 
	{
		SLisMoverA ( p_lisObj->p_lisContenido, iElem );
	}
}

void SLisOrdDeposicionar ( SListaOrdenada * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) )
	{
		SLisDeposicionar ( p_lisObj->p_lisContenido );
	}
}

/* Compara los datos de p_elmObj con p_blqDatos o, si es NULL, con p_byDatos. */
static int _SLisOrdComparar ( SListaOrdenada * p_lisObj, SElemento * p_elmObj, SBloque * p_blqDatos, byte * p_byDatos )
{
	int iRes;

	if ( ES_VALIDO ( p_blqDatos ) )
	{
		iRes = SCmpEvaluarBloque ( p_lisObj->p_cmpObj, SElmDatos ( p_elmObj ), p_blqDatos );
	}
	else
	{
		iRes = SCmpEvaluarBloqueExt ( p_lisObj->p_cmpObj, SElmDatos ( p_elmObj ), p_byDatos );
	}
	return ( iRes );
}

static int _SLisOrdBuscarSiguiente ( SListaOrdenada * p_lisObj, SBloque * p_blqDatos, byte * p_byDatos, int iPos )
{
	int			iRes;
	int			iCmp;
	SElemento *	p_elmObj;

	if ( ( SLisOrdEsValida ( p_lisObj ) == 1 ) && ( iPos >= -1 ) )
	{
		iRes = iPos + 1;
		p_elmObj = SLisElemento ( p_lisObj->p_lisContenido, iRes );
		iCmp = -1;
		while ( ES_VALIDO ( p_elmObj ) && ( iCmp < 0 ) )
		{
			iCmp = _SLisOrdComparar ( p_lisObj, p_elmObj, p_blqDatos, p_byDatos );
			if ( iCmp < 0 )
			{
				p_elmObj = SElmSucesor ( p_elmObj );
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

static int _SLisOrdRepeticiones ( SListaOrdenada * p_lisObj, SBloque * p_blqDatos, byte * p_byDatos )
{
	int			iRes;
	int			iCmp;
	SElemento *	p_elmObj;

	iRes = 0;
	if ( SLisOrdEsValida ( p_lisObj ) == 1 )
	{
		p_elmObj = p_lisObj->p_lisContenido->p_elmPrimero;
		iCmp = -1;
		while ( ES_VALIDO ( p_elmObj ) && ( iCmp <= 0 ) )
		{
			iCmp = _SLisOrdComparar ( p_lisObj, p_elmObj, p_blqDatos, p_byDatos );
			if ( iCmp == 0 )
			{
				iRes = iRes + 1;
			}
			p_elmObj = SElmSucesor ( p_elmObj );
		}
	}
	return ( iRes );
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
int SLisOrdExisteElem ( SListaOrdenada * p_lisObj, SElemento * p_elmObj )
{
	int	iRes;

	if ( SLisOrdBuscarPrimeroElem ( p_lisObj, p_elmObj ) >= 0 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisOrdExiste ( SListaOrdenada * p_lisObj, SBloque * p_blqDatos )
{
	int	iRes;

	if ( SLisOrdBuscarPrimero ( p_lisObj, p_blqDatos ) >= 0 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisOrdExisteExt ( SListaOrdenada * p_lisObj, byte * p_byDatos )
{
	int	iRes;

	if ( SLisOrdBuscarPrimeroExt ( p_lisObj, p_byDatos ) >= 0 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisOrdRepeticionesElem ( SListaOrdenada * p_lisObj, SElemento * p_elmObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_elmObj ) )
	{
		iRes = SLisOrdRepeticiones ( p_lisObj, SElmDatos ( p_elmObj ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisOrdRepeticiones ( SListaOrdenada * p_lisObj, SBloque * p_blqDatos )
{
	int	iRes;

	if ( ES_VALIDO ( p_blqDatos ) )
	{
		iRes = _SLisOrdRepeticiones ( p_lisObj, p_blqDatos, NULL );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisOrdRepeticionesExt ( SListaOrdenada * p_lisObj, byte * p_byDatos )
{
	int	iRes;

	if ( ES_VALIDO ( p_byDatos ) )
	{
		iRes = _SLisOrdRepeticiones ( p_lisObj, NULL, p_byDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisOrdBuscarElem ( SListaOrdenada * p_lisObj, SElemento * p_elmObj )
{
	return ( SLisOrdBuscarPrimeroElem ( p_lisObj, p_elmObj ) );
}

int SLisOrdBuscar ( SListaOrdenada * p_lisObj, SBloque * p_blqDatos )
{
	return ( SLisOrdBuscarPrimero ( p_lisObj, p_blqDatos ) );
}

int SLisOrdBuscarExt ( SListaOrdenada * p_lisObj, byte * p_byDatos )
{
	return ( SLisOrdBuscarPrimeroExt ( p_lisObj, p_byDatos ) );
}

int SLisOrdBuscarPrimeroElem ( SListaOrdenada * p_lisObj, SElemento * p_elmObj )
{
	return ( SLisOrdBuscarSiguienteElem ( p_lisObj, p_elmObj, -1 ) );
}

int SLisOrdBuscarPrimero ( SListaOrdenada * p_lisObj, SBloque * p_blqDatos )
{
	return ( SLisOrdBuscarSiguiente ( p_lisObj, p_blqDatos, -1 ) );
}

int SLisOrdBuscarPrimeroExt ( SListaOrdenada * p_lisObj, byte * p_byDatos )
{
	return ( SLisOrdBuscarSiguienteExt ( p_lisObj, p_byDatos, -1 ) );
}

int SLisOrdBuscarSiguienteElem ( SListaOrdenada * p_lisObj, SElemento * p_elmObj, int iPos )
{
	int	iRes;

	if ( ES_VALIDO ( p_elmObj ) )
	{
		iRes = SLisOrdBuscarSiguiente ( p_lisObj, SElmDatos ( p_elmObj ), iPos );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SLisOrdBuscarSiguiente ( SListaOrdenada * p_lisObj, SBloque * p_blqDatos, int iPos )
{
	int	iRes;

	if ( ES_VALIDO ( p_blqDatos ) )
	{
		iRes = _SLisOrdBuscarSiguiente ( p_lisObj, p_blqDatos, NULL, iPos );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SLisOrdBuscarSiguienteExt ( SListaOrdenada * p_lisObj, byte * p_byDatos, int iPos )
{
	int	iRes;

	if ( ES_VALIDO ( p_byDatos ) )
	{
		iRes = _SLisOrdBuscarSiguiente ( p_lisObj, NULL, p_byDatos, iPos );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

/* Posicion detras de la que va p_blqDatos: -1 al principio, y mas alla del ultimo
   ( iNumElementos + 1 ) al final. Los iguales van detras de los que ya estan.

   Via rapida: si no es menor que el ultimo va al final sin recorrer la lista,
   asi que insertar datos que ya llegan en orden cuesta O(1) cada uno. */
int SLisOrdBuscarSitio ( SListaOrdenada * p_lisObj, SBloque * p_blqDatos )
{
	int			iRes;
	int			iEnc;
	int			iAlFinal;
	SElemento * p_elmObj;

	if ( ( SLisOrdEsValida ( p_lisObj ) == 1 ) && ( SBlqEsValido ( p_blqDatos ) == 1 ) )
	{
		iAlFinal = 0;
		p_elmObj = p_lisObj->p_lisContenido->p_elmUltimo;
		if ( ES_VALIDO ( p_elmObj ) )
		{
			if ( SCmpEvaluarBloque ( p_lisObj->p_cmpObj, SElmDatos ( p_elmObj ), p_blqDatos ) <= 0 )
			{
				iAlFinal = 1;
			}
		}

		if ( iAlFinal == 1 )
		{
			iRes = p_lisObj->p_lisContenido->iNumElementos + 1;
		}
		else
		{
			p_elmObj = p_lisObj->p_lisContenido->p_elmPrimero;
			iRes = -1;
			iEnc = 0;
			while ( ( iRes < p_lisObj->p_lisContenido->iNumElementos ) && ( iEnc == 0 ) &&
				ES_VALIDO ( p_elmObj ) )
			{
				int iCmp = SCmpEvaluarBloque ( p_lisObj->p_cmpObj, SElmDatos ( p_elmObj ), p_blqDatos );
				if ( iCmp <= 0 )
				{
					p_elmObj = SElmSucesor ( p_elmObj );
					iRes = iRes + 1;
				}
				else
				{
					iEnc = 1;
				}
			}
			if ( ( iEnc == 0 ) && ( iRes < p_lisObj->p_lisContenido->iNumElementos ) )
			{
				iRes = p_lisObj->p_lisContenido->iNumElementos + 1;
			}
		}
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SLisOrdEsNulo ( SListaOrdenada * p_lisObj )
{
	int iRes;

	if ( SLisOrdEsValida ( p_lisObj ) == 1 ) 
	{
		iRes = SLisEsNulo ( p_lisObj->p_lisContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisOrdEstaEnFinal ( SListaOrdenada * p_lisObj )
{
	int iRes;

	if ( SLisOrdEsValida ( p_lisObj ) == 1 ) 
	{
		iRes = SLisEstaEnFinal ( p_lisObj->p_lisContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisOrdEstaEnInicio ( SListaOrdenada * p_lisObj )
{
	int iRes;

	if ( SLisOrdEsValida ( p_lisObj ) == 1 ) 
	{
		iRes = SLisEstaEnInicio ( p_lisObj->p_lisContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisOrdEliminar ( SListaOrdenada * p_lisObj )
{
	int	iRes;

	if ( SLisOrdEsValida ( p_lisObj ) == 1 ) 
	{
		iRes = SLisEliminar ( p_lisObj->p_lisContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

/* Copia con su propio comparador ( SLisOrdCrearIgual ) y COPIAS de los
   elementos, insertadas una a una con SLisOrdInsertarElem. Si falla alguna
   copia, NULL. */
SListaOrdenada * SLisOrdDuplicar ( SListaOrdenada * p_lisObj )
{
	SListaOrdenada *	p_lisRes;
	SElemento *			p_elmObj;
	SElemento *			p_elmNuevo;
	int					iError;

	if ( SLisOrdEsValida ( p_lisObj ) == 1 )
	{
		p_lisRes = SLisOrdCrearIgual ( p_lisObj );
		if ( ES_VALIDO ( p_lisRes ) )
		{
			iError = 0;
			p_elmObj = p_lisObj->p_lisContenido->p_elmPrimero;
			while ( ES_VALIDO ( p_elmObj ) && ( iError == 0 ) )
			{
				p_elmNuevo = SElmDuplicar ( p_elmObj );
				if ( SLisOrdInsertarElem ( p_lisRes, p_elmNuevo ) != 1 )
				{
					SElmDestruir ( &p_elmNuevo );
					iError = 1;
				}
				p_elmObj = SElmSucesor ( p_elmObj );
			}
			if ( iError == 1 )
			{
				SLisOrdDestruir ( &p_lisRes );
			}
		}
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

SLista * SLisOrdDuplicarLista ( SListaOrdenada * p_lisObj )
{
	SLista * p_lisRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_lisRes = SLisDuplicar ( p_lisObj->p_lisContenido );
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

/* Operaciones con otras listas. La igualdad entre elementos la decide siempre
   el comparador de la lista ordenada ( el de p_lisObj o p_lisValores1 ), no la
   comparacion byte a byte de SLisBuscar. Las de SListaOrdenada delegan en las
   de SLista pasando su contenido. */

/* 1 si en p_lisValores hay algun elemento igual a p_blqDatos segun p_cmpObj. */
static int _SLisOrdEstaEnLista ( SComparador * p_cmpObj, SLista * p_lisValores, SBloque * p_blqDatos )
{
	SElemento * p_elmObj;
	int			iRes;

	iRes = 0;
	p_elmObj = p_lisValores->p_elmPrimero;
	while ( ES_VALIDO ( p_elmObj ) && ( iRes == 0 ) )
	{
		if ( SCmpEvaluarBloque ( p_cmpObj, SElmDatos ( p_elmObj ), p_blqDatos ) == 0 )
		{
			iRes = 1;
		}
		p_elmObj = SElmSucesor ( p_elmObj );
	}
	return ( iRes );
}

/* COPIAS de los de p_lisValores1 que estan ( iEstan = 1 ) o no estan
   ( iEstan = 0 ) en p_lisValores2, que puede estar en cualquier orden: cada
   elemento de p_lisValores1 se busca en toda p_lisValores2, O(n*m). Si falla
   una copia, NULL. */
static SListaOrdenada * _SLisOrdFiltrar ( SListaOrdenada * p_lisValores1, SLista * p_lisValores2, int iEstan )
{
	SListaOrdenada *	p_lisRes;
	SElemento *			p_elmObj;
	SElemento *			p_elmNuevo;
	int					iError;

	p_lisRes = SLisOrdCrearIgual ( p_lisValores1 );
	if ( ES_VALIDO ( p_lisRes ) )
	{
		iError = 0;
		p_elmObj = p_lisValores1->p_lisContenido->p_elmPrimero;
		while ( ES_VALIDO ( p_elmObj ) && ( iError == 0 ) )
		{
			if ( _SLisOrdEstaEnLista ( p_lisValores1->p_cmpObj, p_lisValores2, SElmDatos ( p_elmObj ) ) == iEstan )
			{
				p_elmNuevo = SElmDuplicar ( p_elmObj );
				if ( SLisOrdInsertarElem ( p_lisRes, p_elmNuevo ) != 1 )
				{
					SElmDestruir ( &p_elmNuevo );
					iError = 1;
				}
			}
			p_elmObj = SElmSucesor ( p_elmObj );
		}
		if ( iError == 1 )
		{
			SLisOrdDestruir ( &p_lisRes );
		}
	}
	return ( p_lisRes );
}

/* Como _SLisOrdFiltrar, pero p_lisValores2 esta ordenada con el mismo criterio
   que p_lisValores1, asi que se recorren las dos en paralelo, O(n+m), sin
   volver atras: para cada elemento de p_lisValores1 se salta en p_lisValores2
   lo que es menor que el, y esta si el primero que no es menor es igual. Los
   repetidos de p_lisValores1 se comparan todos con el mismo, asi que salen
   todos, como en _SLisOrdFiltrar. Los cursores no se tocan. */
static SListaOrdenada * _SLisOrdFiltrarEnParalelo ( SListaOrdenada * p_lisValores1, SLista * p_lisValores2, int iEstan )
{
	SListaOrdenada *	p_lisRes;
	SElemento *			p_elmObj1;
	SElemento *			p_elmObj2;
	SElemento *			p_elmNuevo;
	int					iCmp;
	int					iEsta;
	int					iError;

	p_lisRes = SLisOrdCrearIgual ( p_lisValores1 );
	if ( ES_VALIDO ( p_lisRes ) )
	{
		iError = 0;
		p_elmObj1 = p_lisValores1->p_lisContenido->p_elmPrimero;
		p_elmObj2 = p_lisValores2->p_elmPrimero;
		while ( ES_VALIDO ( p_elmObj1 ) && ( iError == 0 ) )
		{
			iCmp = 1;
			while ( ES_VALIDO ( p_elmObj2 ) && ( iCmp > 0 ) )
			{
				iCmp = SCmpEvaluarBloque ( p_lisValores1->p_cmpObj, SElmDatos ( p_elmObj1 ), SElmDatos ( p_elmObj2 ) );
				if ( iCmp > 0 )
				{
					p_elmObj2 = SElmSucesor ( p_elmObj2 );
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
				p_elmNuevo = SElmDuplicar ( p_elmObj1 );
				if ( SLisOrdInsertarElem ( p_lisRes, p_elmNuevo ) != 1 )
				{
					SElmDestruir ( &p_elmNuevo );
					iError = 1;
				}
			}
			p_elmObj1 = SElmSucesor ( p_elmObj1 );
		}
		if ( iError == 1 )
		{
			SLisOrdDestruir ( &p_lisRes );
		}
	}
	return ( p_lisRes );
}

/* Elige el recorrido: en paralelo si p_lisValores2 es otra lista ordenada con
   la misma funcion de comparacion; si no, buscando cada elemento. p_lisValores2
   es la SListaOrdenada, o NULL si es una SLista suelta ( p_lisContenido2 ). */
static SListaOrdenada * _SLisOrdFiltrarElegir ( SListaOrdenada * p_lisValores1, SListaOrdenada * p_lisValores2, SLista * p_lisContenido2, int iEstan )
{
	SListaOrdenada * p_lisRes;

	if ( SLisOrdEsValida ( p_lisValores1 ) == 1 )
	{
		if ( SLisEsValida ( p_lisContenido2 ) == 1 )
		{
			if ( ES_VALIDO ( p_lisValores2 ) &&
				 ( p_lisValores2->p_cmpObj->fComparar == p_lisValores1->p_cmpObj->fComparar ) )
			{
				p_lisRes = _SLisOrdFiltrarEnParalelo ( p_lisValores1, p_lisContenido2, iEstan );
			}
			else
			{
				p_lisRes = _SLisOrdFiltrar ( p_lisValores1, p_lisContenido2, iEstan );
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

int SLisOrdExistenTodos ( SListaOrdenada * p_lisObj, SListaOrdenada * p_lisValores )
{
	int iRes;

	if ( SLisOrdEsValida ( p_lisValores ) == 1 )
	{
		iRes = SLisOrdExistenTodosLista ( p_lisObj, p_lisValores->p_lisContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisOrdExisteAlguno ( SListaOrdenada * p_lisObj, SListaOrdenada * p_lisValores )
{
	int iRes;

	if ( SLisOrdEsValida ( p_lisValores ) == 1 )
	{
		iRes = SLisOrdExisteAlgunoLista ( p_lisObj, p_lisValores->p_lisContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

/* Con p_lisValores vacia, 1: no falta ninguno. */
int SLisOrdExistenTodosLista ( SListaOrdenada * p_lisObj, SLista * p_lisValores )
{
	SElemento * p_elmObj;
	int			iRes;

	if ( SLisOrdEsValida ( p_lisObj ) == 1 )
	{
		if ( SLisEsValida ( p_lisValores ) == 1 )
		{
			iRes = 1;
			p_elmObj = p_lisValores->p_elmPrimero;
			while ( ES_VALIDO ( p_elmObj ) && ( iRes == 1 ) )
			{
				/* SLisOrdBuscar da la posicion o -1, no un booleano. */
				if ( SLisOrdBuscar ( p_lisObj, SElmDatos ( p_elmObj ) ) < 0 )
				{
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

int SLisOrdExisteAlgunoLista ( SListaOrdenada * p_lisObj, SLista * p_lisValores )
{
	SElemento * p_elmObj;
	int			iRes;

	if ( SLisOrdEsValida ( p_lisObj ) == 1 )
	{
		if ( SLisEsValida ( p_lisValores ) == 1 )
		{
			iRes = 0;
			p_elmObj = p_lisValores->p_elmPrimero;
			while ( ES_VALIDO ( p_elmObj ) && ( iRes == 0 ) )
			{
				if ( SLisOrdBuscar ( p_lisObj, SElmDatos ( p_elmObj ) ) >= 0 )
				{
					iRes = 1;
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

int SLisOrdEliminarListaOrd ( SListaOrdenada * p_lisObj, SListaOrdenada * p_lisValores )
{
	int	iRes;

	if ( SLisOrdEsValida ( p_lisValores ) == 1 )
	{
		iRes = SLisOrdEliminarLista ( p_lisObj, p_lisValores->p_lisContenido );
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
   misma lista en los dos argumentos se devuelve 0 sin tocar nada. */
int SLisOrdEliminarLista ( SListaOrdenada * p_lisObj, SLista * p_lisValores )
{
	SElemento *	p_elmObj;
	int			iPos;
	int			iRes;

	if ( SLisOrdEsValida ( p_lisObj ) == 1 )
	{
		if ( SLisEsValida ( p_lisValores ) == 1 )
		{
			if ( p_lisObj->p_lisContenido != p_lisValores )
			{
				iRes = 1;
				p_elmObj = p_lisValores->p_elmPrimero;
				while ( ES_VALIDO ( p_elmObj ) && ( iRes == 1 ) )
				{
					iPos = SLisOrdBuscar ( p_lisObj, SElmDatos ( p_elmObj ) );
					if ( iPos >= 0 )
					{
						if ( SLisOrdEliminarElem ( p_lisObj, iPos ) != 1 )
						{
							iRes = 0;
						}
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
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisOrdInsertarListaOrd ( SListaOrdenada * p_lisObj, SListaOrdenada * p_lisValores )
{
	int iRes;

	if ( SLisOrdEsValida ( p_lisValores ) == 1 )
	{
		iRes = SLisOrdInsertarLista ( p_lisObj, p_lisValores->p_lisContenido );
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
int SLisOrdInsertarLista ( SListaOrdenada * p_lisObj, SLista * p_lisValores )
{
	SElemento * p_elmObj;
	int			iRes;

	if ( SLisOrdEsValida ( p_lisObj ) == 1 )
	{
		if ( SLisEsValida ( p_lisValores ) == 1 )
		{
			if ( p_lisObj->p_lisContenido != p_lisValores )
			{
				iRes = 1;
				while ( ( iRes == 1 ) && ( p_lisValores->iNumElementos > 0 ) )
				{
					SLisInicio ( p_lisValores );
					p_elmObj = SLisExtraer ( p_lisValores );
					if ( ES_VALIDO ( p_elmObj ) )
					{
						if ( SLisOrdInsertarElem ( p_lisObj, p_elmObj ) != 1 )
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
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisOrdInsertarListaOrdDup ( SListaOrdenada * p_lisObj, SListaOrdenada * p_lisValores )
{
	int iRes;

	if ( SLisOrdEsValida ( p_lisValores ) == 1 )
	{
		iRes = SLisOrdInsertarListaDup ( p_lisObj, p_lisValores->p_lisContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

/* Las Dup insertan COPIAS ( SElmDuplicar ) y no tocan p_lisValores. Con la
   misma lista en los dos argumentos se devuelve 0: se insertaria en la cadena
   que se esta recorriendo. Si falla una copia ( ERR_COPIA_OBJETO ) o una
   insercion ( ERR_INSERCION_LISTA ) se para, y lo insertado hasta ahi se queda. */
int SLisOrdInsertarListaDup ( SListaOrdenada * p_lisObj, SLista * p_lisValores )
{
	SElemento * p_elmObj;
	SElemento * p_elmNuevo;
	int			iRes;

	if ( SLisOrdEsValida ( p_lisObj ) == 1 )
	{
		if ( SLisEsValida ( p_lisValores ) == 1 )
		{
			if ( p_lisObj->p_lisContenido != p_lisValores )
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
					else if ( SLisOrdInsertarElem ( p_lisObj, p_elmNuevo ) != 1 )
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
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SListaOrdenada * SLisOrdExtraerListaOrd ( SListaOrdenada * p_lisObj, SListaOrdenada * p_lisValores )
{
	SListaOrdenada * p_lisRes;

	if ( SLisOrdEsValida ( p_lisValores ) == 1 )
	{
		p_lisRes = SLisOrdExtraerLista ( p_lisObj, p_lisValores->p_lisContenido );
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
   elementos se mueven, no se copian, y la lista nueva los ordena.

   Si un elemento no se puede insertar en la nueva, vuelve a su sitio en
   p_lisObj y se para: se devuelve lo extraido hasta ahi, con el error
   ERR_INSERCION_LISTA. Lo mismo si no se puede sacar uno que se ha encontrado.

   Con la misma lista en los dos argumentos se devuelve NULL. */
SListaOrdenada * SLisOrdExtraerLista ( SListaOrdenada * p_lisObj, SLista * p_lisValores )
{
	SListaOrdenada *	p_lisRes;
	SElemento *			p_elmObj;
	SElemento *			p_elmExt;
	int					iPos;
	int					iError;

	if ( SLisOrdEsValida ( p_lisObj ) == 1 )
	{
		if ( SLisEsValida ( p_lisValores ) == 1 )
		{
			if ( p_lisObj->p_lisContenido != p_lisValores )
			{
				p_lisRes = SLisOrdCrearIgual ( p_lisObj );
				if ( ES_VALIDO ( p_lisRes ) )
				{
					iError = 0;
					p_elmObj = p_lisValores->p_elmPrimero;
					while ( ES_VALIDO ( p_elmObj ) && ( iError == 0 ) )
					{
						iPos = SLisOrdBuscar ( p_lisObj, SElmDatos ( p_elmObj ) );
						if ( iPos >= 0 )
						{
							p_elmExt = SLisOrdExtraerElem ( p_lisObj, iPos );
							if ( ES_VALIDO ( p_elmExt ) )
							{
								if ( SLisOrdInsertarElem ( p_lisRes, p_elmExt ) != 1 )
								{
									if ( SLisOrdInsertarElem ( p_lisObj, p_elmExt ) != 1 )
									{
										SElmDestruir ( &p_elmExt );
									}
									iError = 1;
								}
							}
							else
							{
								iError = 1;
							}
						}
						p_elmObj = SElmSucesor ( p_elmObj );
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

/* Las que generan una lista nueva la devuelven con COPIAS y una copia del
   comparador de p_lisValores1; si algo falla, NULL. */
SListaOrdenada * SLisOrdUnion ( SListaOrdenada * p_lisValores1, SListaOrdenada * p_lisValores2 )
{
	SListaOrdenada * p_lisRes;

	if ( SLisOrdEsValida ( p_lisValores2 ) == 1 )
	{
		p_lisRes = SLisOrdUnionLista ( p_lisValores1, p_lisValores2->p_lisContenido );
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

SListaOrdenada * SLisOrdInterseccion ( SListaOrdenada * p_lisValores1, SListaOrdenada * p_lisValores2 )
{
	SListaOrdenada * p_lisRes;

	if ( SLisOrdEsValida ( p_lisValores2 ) == 1 )
	{
		p_lisRes = _SLisOrdFiltrarElegir ( p_lisValores1, p_lisValores2, p_lisValores2->p_lisContenido, 1 );
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

SListaOrdenada * SLisOrdDiferencia ( SListaOrdenada * p_lisValores1, SListaOrdenada * p_lisValores2 )
{
	SListaOrdenada * p_lisRes;

	if ( SLisOrdEsValida ( p_lisValores2 ) == 1 )
	{
		p_lisRes = _SLisOrdFiltrarElegir ( p_lisValores1, p_lisValores2, p_lisValores2->p_lisContenido, 0 );
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

/* Todos los de las dos, ordenados: lo que este en ambas sale dos veces. */
SListaOrdenada * SLisOrdUnionLista ( SListaOrdenada * p_lisValores1, SLista * p_lisValores2 )
{
	SListaOrdenada * p_lisRes;

	if ( SLisOrdEsValida ( p_lisValores1 ) == 1 )
	{
		if ( SLisEsValida ( p_lisValores2 ) == 1 )
		{
			p_lisRes = SLisOrdDuplicar ( p_lisValores1 );
			if ( ES_VALIDO ( p_lisRes ) )
			{
				if ( SLisOrdInsertarListaDup ( p_lisRes, p_lisValores2 ) != 1 )
				{
					SLisOrdDestruir ( &p_lisRes );
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
SListaOrdenada * SLisOrdInterseccionLista ( SListaOrdenada * p_lisValores1, SLista * p_lisValores2 )
{
	return ( _SLisOrdFiltrarElegir ( p_lisValores1, NULL, p_lisValores2, 1 ) );
}

/* Los de p_lisValores1 que NO estan en p_lisValores2. */
SListaOrdenada * SLisOrdDiferenciaLista ( SListaOrdenada * p_lisValores1, SLista * p_lisValores2 )
{
	return ( _SLisOrdFiltrarElegir ( p_lisValores1, NULL, p_lisValores2, 0 ) );
}
