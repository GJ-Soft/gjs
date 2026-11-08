#include "SSecuenciaPtr.h"


#include "TiposBasicosConfig.h"




SSecuenciaPtr * SSecpCrear ()
{
	SSecuenciaPtr * p_secObj;
	
	p_secObj = (SSecuenciaPtr *) MemReservar ( sizeof ( SSecuenciaPtr ) );
	if ( ES_VALIDO ( p_secObj ) )
	{
		p_secObj->p_lisDatos = SLispCrear ();
	}
	return ( p_secObj );
}

/* Secuencia con COPIAS de los datos de p_lisValores, que no se toca: de
   iNumBytes, o hechas con fDuplicar en la Ext. La secuencia es duena de las
   copias. */
SSecuenciaPtr * SSecpCrearDesdeLista ( SListaPtr * p_lisValores, int iNumBytes )
{
	SSecuenciaPtr *	p_secObj;
	SListaPtr *		p_lisDatos;

	p_lisDatos = SLispDuplicar ( p_lisValores, iNumBytes );
	if ( ES_VALIDO ( p_lisDatos ) )
	{
		p_secObj = SSecpEncapsularLista ( p_lisDatos );
		if ( ES_NULO ( p_secObj ) )
		{
			SLispDestruir ( &p_lisDatos );
		}
	}
	else
	{
		p_secObj = NULL;
	}
	return ( p_secObj );
}

SSecuenciaPtr * SSecpCrearDesdeListaExt ( SListaPtr * p_lisValores, PFUNPBYTEPB fDuplicar )
{
	SSecuenciaPtr *	p_secObj;
	SListaPtr *		p_lisDatos;

	p_lisDatos = SLispDuplicarExt ( p_lisValores, fDuplicar );
	if ( ES_VALIDO ( p_lisDatos ) )
	{
		p_secObj = SSecpEncapsularLista ( p_lisDatos );
		if ( ES_NULO ( p_secObj ) )
		{
			SLispDestruir ( &p_lisDatos );
		}
	}
	else
	{
		p_secObj = NULL;
	}
	return ( p_secObj );
}

/* La lista pasa a ser de la secuencia, que la destruye con ella. Si la lista
   no es valida, o no se puede crear la secuencia, devuelve NULL y la lista
   sigue siendo del llamante. */
SSecuenciaPtr * SSecpEncapsularLista ( SListaPtr * p_lisValores )
{
	SSecuenciaPtr * p_secObj;

	if ( SLispEsValida ( p_lisValores ) == 1 )
	{
		p_secObj = (SSecuenciaPtr *) MemReservar ( sizeof ( SSecuenciaPtr ) );
		if ( ES_VALIDO ( p_secObj ) )
		{
			p_secObj->p_lisDatos = p_lisValores;
		}
	}
	else
	{
		p_secObj = NULL;
	}
	return ( p_secObj );
}

void SSecpDestruir ( SSecuenciaPtr ** p_p_secObj )
{
	SSecuenciaPtr * p_secObj;
	
	if ( ES_VALIDO ( p_p_secObj ) )
	{
		p_secObj = *p_p_secObj;

		if ( ES_VALIDO ( p_secObj ) )
		{
			SLispDestruir ( &(p_secObj->p_lisDatos) );
			MemLiberar ( (void **) p_p_secObj );
		}
	}
}

int SSecpEsValida ( SSecuenciaPtr * p_secObj )
{
	int iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SLispEsValida ( p_secObj->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecpNumElementos ( SSecuenciaPtr * p_secObj )
{
	int iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SLispNumElementos ( p_secObj->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecpEstaVacia ( SSecuenciaPtr * p_secObj )
{
	int iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SLispEstaVacia ( p_secObj->p_lisDatos );
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

byte * SSecpElemento ( SSecuenciaPtr * p_secObj, int iElem )
{
	byte * p_byRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		p_byRes = SLispElemento ( p_secObj->p_lisDatos, iElem );
	}
	else
	{
		p_byRes = NULL;
	}
	return ( p_byRes );
}

/* El ELEMENTO en esa posicion, no el dato. Gemela de SSecpElemento en
   SSecuenciaPtr; ver SLispElementoPtr. */
SElementoPtr * SSecpElementoPtr ( SSecuenciaPtr * p_secObj, int iElem )
{
	SElementoPtr * p_elpRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		p_elpRes = SLispElementoPtr ( p_secObj->p_lisDatos, iElem );
	}
	else
	{
		p_elpRes = NULL;
	}
	return ( p_elpRes );
}

/* Busquedas: delegan en las de SListaPtr. Comparan iNumBytes, o con
   fSonIguales en las Ext; las Ptr, con los datos de un elemento, que no hace
   falta que este en la secuencia. Existe da 1 o 0, Repeticiones cuantos iguales
   hay ( 0 si ninguno ), y Buscar ( que es BuscarPrimero ) y BuscarSiguiente la
   posicion o -1. BuscarSiguiente busca DETRAS de iPos: con -1, desde el
   principio. */
int SSecpExiste ( SSecuenciaPtr * p_secObj, byte * p_byDatos, int iNumBytes )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SLispExiste ( p_secObj->p_lisDatos, p_byDatos, iNumBytes );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecpExistePtr ( SSecuenciaPtr * p_secObj, SElementoPtr * p_elpDatos, int iNumBytes )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SLispExistePtr ( p_secObj->p_lisDatos, p_elpDatos, iNumBytes );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecpExisteExt ( SSecuenciaPtr * p_secObj, byte * p_byDatos, PFUNINTPBPB fSonIguales )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SLispExisteExt ( p_secObj->p_lisDatos, p_byDatos, fSonIguales );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecpExisteExtPtr ( SSecuenciaPtr * p_secObj, SElementoPtr * p_elpDatos, PFUNINTPBPB fSonIguales )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SLispExisteExtPtr ( p_secObj->p_lisDatos, p_elpDatos, fSonIguales );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecpRepeticiones ( SSecuenciaPtr * p_secObj, byte * p_byDatos, int iNumBytes )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SLispRepeticiones ( p_secObj->p_lisDatos, p_byDatos, iNumBytes );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecpRepeticionesPtr ( SSecuenciaPtr * p_secObj, SElementoPtr * p_elpDatos, int iNumBytes )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SLispRepeticionesPtr ( p_secObj->p_lisDatos, p_elpDatos, iNumBytes );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecpRepeticionesExt ( SSecuenciaPtr * p_secObj, byte * p_byDatos, PFUNINTPBPB fSonIguales )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SLispRepeticionesExt ( p_secObj->p_lisDatos, p_byDatos, fSonIguales );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecpRepeticionesExtPtr ( SSecuenciaPtr * p_secObj, SElementoPtr * p_elpDatos, PFUNINTPBPB fSonIguales )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SLispRepeticionesExtPtr ( p_secObj->p_lisDatos, p_elpDatos, fSonIguales );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecpBuscar ( SSecuenciaPtr * p_secObj, byte * p_byDatos, int iNumBytes )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SLispBuscar ( p_secObj->p_lisDatos, p_byDatos, iNumBytes );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SSecpBuscarPtr ( SSecuenciaPtr * p_secObj, SElementoPtr * p_elpDatos, int iNumBytes )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SLispBuscarPtr ( p_secObj->p_lisDatos, p_elpDatos, iNumBytes );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SSecpBuscarExt ( SSecuenciaPtr * p_secObj, byte * p_byDatos, PFUNINTPBPB fSonIguales )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SLispBuscarExt ( p_secObj->p_lisDatos, p_byDatos, fSonIguales );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SSecpBuscarExtPtr ( SSecuenciaPtr * p_secObj, SElementoPtr * p_elpDatos, PFUNINTPBPB fSonIguales )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SLispBuscarExtPtr ( p_secObj->p_lisDatos, p_elpDatos, fSonIguales );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SSecpBuscarPrimero ( SSecuenciaPtr * p_secObj, byte * p_byDatos, int iNumBytes )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SLispBuscarPrimero ( p_secObj->p_lisDatos, p_byDatos, iNumBytes );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SSecpBuscarPrimeroPtr ( SSecuenciaPtr * p_secObj, SElementoPtr * p_elpDatos, int iNumBytes )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SLispBuscarPrimeroPtr ( p_secObj->p_lisDatos, p_elpDatos, iNumBytes );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SSecpBuscarPrimeroExt ( SSecuenciaPtr * p_secObj, byte * p_byDatos, PFUNINTPBPB fSonIguales )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SLispBuscarPrimeroExt ( p_secObj->p_lisDatos, p_byDatos, fSonIguales );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SSecpBuscarPrimeroExtPtr ( SSecuenciaPtr * p_secObj, SElementoPtr * p_elpDatos, PFUNINTPBPB fSonIguales )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SLispBuscarPrimeroExtPtr ( p_secObj->p_lisDatos, p_elpDatos, fSonIguales );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SSecpBuscarSiguiente ( SSecuenciaPtr * p_secObj, byte * p_byDatos, int iPos, int iNumBytes )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SLispBuscarSiguiente ( p_secObj->p_lisDatos, p_byDatos, iPos, iNumBytes );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SSecpBuscarSiguientePtr ( SSecuenciaPtr * p_secObj, SElementoPtr * p_elpDatos, int iPos, int iNumBytes )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SLispBuscarSiguientePtr ( p_secObj->p_lisDatos, p_elpDatos, iPos, iNumBytes );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SSecpBuscarSiguienteExt ( SSecuenciaPtr * p_secObj, byte * p_byDatos, int iPos, PFUNINTPBPB fSonIguales )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SLispBuscarSiguienteExt ( p_secObj->p_lisDatos, p_byDatos, iPos, fSonIguales );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SSecpBuscarSiguienteExtPtr ( SSecuenciaPtr * p_secObj, SElementoPtr * p_elpDatos, int iPos, PFUNINTPBPB fSonIguales )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SLispBuscarSiguienteExtPtr ( p_secObj->p_lisDatos, p_elpDatos, iPos, fSonIguales );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SSecpInsertar ( SSecuenciaPtr * p_secObj, byte * p_byDatos )
{
	int iRes;

	if ( ( SSecpEsValida ( p_secObj ) == 1 ) && ES_VALIDO ( p_byDatos ) )
	{
		iRes = SLispInsertarAlFinal ( p_secObj->p_lisDatos, p_byDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecpEliminar ( SSecuenciaPtr * p_secObj, int iElem )
{
	int	iRes;

	if ( SSecpEsValida ( p_secObj ) == 1 ) 
	{
		iRes = SLispEliminarElem ( p_secObj->p_lisDatos, iElem );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecpVaciar ( SSecuenciaPtr * p_secObj )
{
	int	iRes;

	if ( SSecpEsValida ( p_secObj ) == 1 ) 
	{
		iRes = SLispVaciar ( p_secObj->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

/* Secuencia nueva con copias de los datos, en el mismo orden: de iNumBytes, o
   hechas con fDuplicar en la Ext. */
SSecuenciaPtr * SSecpDuplicar ( SSecuenciaPtr * p_secObj, int iNumBytes )
{
	SSecuenciaPtr * p_secRes;

	if ( SSecpEsValida ( p_secObj ) == 1 )
	{
		p_secRes = SSecpCrearDesdeLista ( p_secObj->p_lisDatos, iNumBytes );
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

SSecuenciaPtr * SSecpDuplicarExt ( SSecuenciaPtr * p_secObj, PFUNPBYTEPB fDuplicar )
{
	SSecuenciaPtr * p_secRes;

	if ( SSecpEsValida ( p_secObj ) == 1 )
	{
		p_secRes = SSecpCrearDesdeListaExt ( p_secObj->p_lisDatos, fDuplicar );
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

SListaPtr * SSecpLista ( SSecuenciaPtr * p_secObj )
{
	SListaPtr * p_lisRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		p_lisRes = p_secObj->p_lisDatos;
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

int	SSecpLiberacionMemoriaActivada ( SSecuenciaPtr * p_secObj )
{
	int	iRes;

	if ( SSecpEsValida ( p_secObj ) == 1 ) 
	{
		iRes = SLispLiberacionMemoriaActivada ( p_secObj->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

void SSecpActivarLiberacionMemoria ( SSecuenciaPtr * p_secObj )
{
	if ( SSecpEsValida ( p_secObj ) == 1 ) 
	{
		SLispActivarLiberacionMemoria ( p_secObj->p_lisDatos );
	}
}

void SSecpDesactivarLiberacionMemoria ( SSecuenciaPtr * p_secObj )
{
	if ( SSecpEsValida ( p_secObj ) == 1 ) 
	{
		SLispDesactivarLiberacionMemoria ( p_secObj->p_lisDatos );
	}
}

/* Las operaciones con otras secuencias y listas delegan en las de SListaPtr,
   con su misma semantica ( ver Listas.md ); las de secuencia pasan la lista de
   la segunda. Las que crean una secuencia nueva devuelven NULL si la de
   SListaPtr falla, nunca una secuencia sin lista. */
int SSecpExistenTodos ( SSecuenciaPtr * p_secObj, SSecuenciaPtr * p_secValores, int iNumBytes )
{
	int iRes;

	if ( SSecpEsValida ( p_secValores ) == 1 )
	{
		iRes = SSecpExistenTodosLista ( p_secObj, p_secValores->p_lisDatos, iNumBytes );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecpExisteAlguno ( SSecuenciaPtr * p_secObj, SSecuenciaPtr * p_secValores, int iNumBytes )
{
	int iRes;

	if ( SSecpEsValida ( p_secValores ) == 1 )
	{
		iRes = SSecpExisteAlgunoLista ( p_secObj, p_secValores->p_lisDatos, iNumBytes );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecpExistenTodosLista ( SSecuenciaPtr * p_secObj, SListaPtr * p_lisValores, int iNumBytes )
{
	int	iRes;

	if ( SSecpEsValida ( p_secObj ) == 1 )
	{
		iRes = SLispExistenTodos ( p_secObj->p_lisDatos, p_lisValores, iNumBytes );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecpExisteAlgunoLista ( SSecuenciaPtr * p_secObj, SListaPtr * p_lisValores, int iNumBytes )
{
	int iRes;

	if ( SSecpEsValida ( p_secObj ) == 1 )
	{
		iRes = SLispExisteAlguno ( p_secObj->p_lisDatos, p_lisValores, iNumBytes );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecpExistenTodosExt ( SSecuenciaPtr * p_secObj, SSecuenciaPtr * p_secValores, PFUNINTPBPB fSonIguales )
{
	int iRes;

	if ( SSecpEsValida ( p_secValores ) == 1 )
	{
		iRes = SSecpExistenTodosListaExt ( p_secObj, p_secValores->p_lisDatos, fSonIguales );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecpExisteAlgunoExt ( SSecuenciaPtr * p_secObj, SSecuenciaPtr * p_secValores, PFUNINTPBPB fSonIguales )
{
	int iRes;

	if ( SSecpEsValida ( p_secValores ) == 1 )
	{
		iRes = SSecpExisteAlgunoListaExt ( p_secObj, p_secValores->p_lisDatos, fSonIguales );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecpExistenTodosListaExt ( SSecuenciaPtr * p_secObj, SListaPtr * p_lisValores, PFUNINTPBPB fSonIguales )
{
	int iRes;

	if ( SSecpEsValida ( p_secObj ) == 1 )
	{
		iRes = SLispExistenTodosExt ( p_secObj->p_lisDatos, p_lisValores, fSonIguales );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecpExisteAlgunoListaExt ( SSecuenciaPtr * p_secObj, SListaPtr * p_lisValores, PFUNINTPBPB fSonIguales )
{
	int iRes;

	if ( SSecpEsValida ( p_secObj ) == 1 )
	{
		iRes = SLispExisteAlgunoExt ( p_secObj->p_lisDatos, p_lisValores, fSonIguales );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecpEliminarSecuencia ( SSecuenciaPtr * p_secObj, SSecuenciaPtr * p_secValores, int iNumBytes )
{
	int	iRes;

	if ( SSecpEsValida ( p_secValores ) == 1 )
	{
		iRes = SSecpEliminarLista ( p_secObj, p_secValores->p_lisDatos, iNumBytes );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecpEliminarLista ( SSecuenciaPtr * p_secObj, SListaPtr * p_lisValores, int iNumBytes )
{
	int iRes;

	if ( SSecpEsValida ( p_secObj ) == 1 )
	{
		iRes = SLispEliminarLista ( p_secObj->p_lisDatos, p_lisValores, iNumBytes );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecpEliminarSecuenciaExt ( SSecuenciaPtr * p_secObj, SSecuenciaPtr * p_secValores, PFUNINTPBPB fSonIguales )
{
	int	iRes;

	if ( SSecpEsValida ( p_secValores ) == 1 )
	{
		iRes = SSecpEliminarListaExt ( p_secObj, p_secValores->p_lisDatos, fSonIguales );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecpEliminarListaExt ( SSecuenciaPtr * p_secObj, SListaPtr * p_lisValores, PFUNINTPBPB fSonIguales )
{
	int iRes;

	if ( SSecpEsValida ( p_secObj ) == 1 )
	{
		iRes = SLispEliminarListaExt ( p_secObj->p_lisDatos, p_lisValores, fSonIguales );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecpConcatenar ( SSecuenciaPtr * p_secObj, SSecuenciaPtr * p_secValores )
{
	int iRes;

	if ( SSecpEsValida ( p_secValores ) == 1 )
	{
		iRes = SSecpConcatenarLista ( p_secObj, p_secValores->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecpConcatenarLista ( SSecuenciaPtr * p_secObj, SListaPtr * p_lisValores )
{
	int iRes;

	if ( SSecpEsValida ( p_secObj ) == 1 )
	{
		iRes = SLispConcatenarLista ( p_secObj->p_lisDatos, p_lisValores );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecpConcatenarDup ( SSecuenciaPtr * p_secObj, SSecuenciaPtr * p_secValores, int iNumBytes )
{
	int iRes;

	if ( SSecpEsValida ( p_secValores ) == 1 )
	{
		iRes = SSecpConcatenarListaDup ( p_secObj, p_secValores->p_lisDatos, iNumBytes );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecpConcatenarListaDup ( SSecuenciaPtr * p_secObj, SListaPtr * p_lisValores, int iNumBytes )
{
	int iRes;

	if ( SSecpEsValida ( p_secObj ) == 1 )
	{
		iRes = SLispConcatenarListaDup ( p_secObj->p_lisDatos, p_lisValores, iNumBytes );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecpConcatenarDupExt ( SSecuenciaPtr * p_secObj, SSecuenciaPtr * p_secValores, PFUNPBYTEPB fDuplicar )
{
	int iRes;

	if ( SSecpEsValida ( p_secValores ) == 1 )
	{
		iRes = SSecpConcatenarListaDupExt ( p_secObj, p_secValores->p_lisDatos, fDuplicar );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecpConcatenarListaDupExt ( SSecuenciaPtr * p_secObj, SListaPtr * p_lisValores, PFUNPBYTEPB fDuplicar )
{
	int iRes;

	if ( SSecpEsValida ( p_secObj ) == 1 )
	{
		iRes = SLispConcatenarListaDupExt ( p_secObj->p_lisDatos, p_lisValores, fDuplicar );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SSecuenciaPtr * SSecpExtraerSecuencia ( SSecuenciaPtr * p_secObj, SSecuenciaPtr * p_secValores, int iNumBytes )
{
	SSecuenciaPtr *	p_secRes;

	if ( SSecpEsValida ( p_secValores ) == 1 )
	{
		p_secRes = SSecpExtraerLista ( p_secObj, p_secValores->p_lisDatos, iNumBytes );
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

SSecuenciaPtr * SSecpExtraerLista ( SSecuenciaPtr * p_secObj, SListaPtr * p_lisValores, int iNumBytes )
{
	SSecuenciaPtr *	p_secRes;
	SListaPtr *		p_lisDatos;

	if ( SSecpEsValida ( p_secObj ) == 1 )
	{
		p_lisDatos = SLispExtraerLista ( p_secObj->p_lisDatos, p_lisValores, iNumBytes );
		p_secRes = SSecpEncapsularLista ( p_lisDatos );
		if ( ES_NULO ( p_secRes ) )
		{
			/* No se pierde lo extraido: vuelve al final de p_secObj. */
			SLispConcatenarLista ( p_secObj->p_lisDatos, p_lisDatos );
			SLispDestruir ( &p_lisDatos );
		}
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

SSecuenciaPtr * SSecpExtraerSecuenciaExt ( SSecuenciaPtr * p_secObj, SSecuenciaPtr * p_secValores, PFUNINTPBPB fSonIguales )
{
	SSecuenciaPtr *	p_secRes;

	if ( SSecpEsValida ( p_secValores ) == 1 )
	{
		p_secRes = SSecpExtraerListaExt ( p_secObj, p_secValores->p_lisDatos, fSonIguales );
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

SSecuenciaPtr * SSecpExtraerListaExt ( SSecuenciaPtr * p_secObj, SListaPtr * p_lisValores, PFUNINTPBPB fSonIguales )
{
	SSecuenciaPtr *	p_secRes;
	SListaPtr *		p_lisDatos;

	if ( SSecpEsValida ( p_secObj ) == 1 )
	{
		p_lisDatos = SLispExtraerListaExt ( p_secObj->p_lisDatos, p_lisValores, fSonIguales );
		p_secRes = SSecpEncapsularLista ( p_lisDatos );
		if ( ES_NULO ( p_secRes ) )
		{
			/* No se pierde lo extraido: vuelve al final de p_secObj. */
			SLispConcatenarLista ( p_secObj->p_lisDatos, p_lisDatos );
			SLispDestruir ( &p_lisDatos );
		}
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

SSecuenciaPtr * SSecpUnion ( SSecuenciaPtr * p_secValores1, SSecuenciaPtr * p_secValores2, int iNumBytes )
{
	SSecuenciaPtr *	p_secRes;

	if ( SSecpEsValida ( p_secValores2 ) == 1 )
	{
		p_secRes = SSecpUnionLista ( p_secValores1, p_secValores2->p_lisDatos, iNumBytes );
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

SSecuenciaPtr * SSecpInterseccion ( SSecuenciaPtr * p_secValores1, SSecuenciaPtr * p_secValores2, int iNumBytes )
{
	SSecuenciaPtr *	p_secRes;

	if ( SSecpEsValida ( p_secValores2 ) == 1 )
	{
		p_secRes = SSecpInterseccionLista ( p_secValores1, p_secValores2->p_lisDatos, iNumBytes );
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

SSecuenciaPtr * SSecpDiferencia ( SSecuenciaPtr * p_secValores1, SSecuenciaPtr * p_secValores2, int iNumBytes )
{
	SSecuenciaPtr *	p_secRes;

	if ( SSecpEsValida ( p_secValores2 ) == 1 )
	{
		p_secRes = SSecpDiferenciaLista ( p_secValores1, p_secValores2->p_lisDatos, iNumBytes );
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

SSecuenciaPtr * SSecpUnionLista ( SSecuenciaPtr * p_secValores1, SListaPtr * p_lisValores2, int iNumBytes )
{
	SSecuenciaPtr *	p_secRes;
	SListaPtr *		p_lisDatos;

	if ( SSecpEsValida ( p_secValores1 ) == 1 )
	{
		p_lisDatos = SLispUnion ( p_secValores1->p_lisDatos, p_lisValores2, iNumBytes );
		p_secRes = SSecpEncapsularLista ( p_lisDatos );
		if ( ES_NULO ( p_secRes ) )
		{
			SLispDestruir ( &p_lisDatos );
		}
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

SSecuenciaPtr * SSecpInterseccionLista ( SSecuenciaPtr * p_secValores1, SListaPtr * p_lisValores2, int iNumBytes )
{
	SSecuenciaPtr *	p_secRes;
	SListaPtr *		p_lisDatos;

	if ( SSecpEsValida ( p_secValores1 ) == 1 )
	{
		p_lisDatos = SLispInterseccion ( p_secValores1->p_lisDatos, p_lisValores2, iNumBytes );
		p_secRes = SSecpEncapsularLista ( p_lisDatos );
		if ( ES_NULO ( p_secRes ) )
		{
			SLispDestruir ( &p_lisDatos );
		}
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

SSecuenciaPtr * SSecpDiferenciaLista ( SSecuenciaPtr * p_secValores1, SListaPtr * p_lisValores2, int iNumBytes )
{
	SSecuenciaPtr *	p_secRes;
	SListaPtr *		p_lisDatos;

	if ( SSecpEsValida ( p_secValores1 ) == 1 )
	{
		p_lisDatos = SLispDiferencia ( p_secValores1->p_lisDatos, p_lisValores2, iNumBytes );
		p_secRes = SSecpEncapsularLista ( p_lisDatos );
		if ( ES_NULO ( p_secRes ) )
		{
			SLispDestruir ( &p_lisDatos );
		}
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

SSecuenciaPtr * SSecpUnionExt ( SSecuenciaPtr * p_secValores1, SSecuenciaPtr * p_secValores2, PFUNPBYTEPB fDuplicar )
{
	SSecuenciaPtr *	p_secRes;

	if ( SSecpEsValida ( p_secValores2 ) == 1 )
	{
		p_secRes = SSecpUnionListaExt ( p_secValores1, p_secValores2->p_lisDatos, fDuplicar );
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

SSecuenciaPtr * SSecpInterseccionExt ( SSecuenciaPtr * p_secValores1, SSecuenciaPtr * p_secValores2, PFUNINTPBPB fSonIguales, PFUNPBYTEPB fDuplicar )
{
	SSecuenciaPtr *	p_secRes;

	if ( SSecpEsValida ( p_secValores2 ) == 1 )
	{
		p_secRes = SSecpInterseccionListaExt ( p_secValores1, p_secValores2->p_lisDatos, fSonIguales, fDuplicar );
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

SSecuenciaPtr * SSecpDiferenciaExt ( SSecuenciaPtr * p_secValores1, SSecuenciaPtr * p_secValores2, PFUNINTPBPB fSonIguales, PFUNPBYTEPB fDuplicar )
{
	SSecuenciaPtr *	p_secRes;

	if ( SSecpEsValida ( p_secValores2 ) == 1 )
	{
		p_secRes = SSecpDiferenciaListaExt ( p_secValores1, p_secValores2->p_lisDatos, fSonIguales, fDuplicar );
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

SSecuenciaPtr * SSecpUnionListaExt ( SSecuenciaPtr * p_secValores1, SListaPtr * p_lisValores2, PFUNPBYTEPB fDuplicar )
{
	SSecuenciaPtr *	p_secRes;
	SListaPtr *		p_lisDatos;

	if ( SSecpEsValida ( p_secValores1 ) == 1 )
	{
		p_lisDatos = SLispUnionExt ( p_secValores1->p_lisDatos, p_lisValores2, fDuplicar );
		p_secRes = SSecpEncapsularLista ( p_lisDatos );
		if ( ES_NULO ( p_secRes ) )
		{
			SLispDestruir ( &p_lisDatos );
		}
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

SSecuenciaPtr * SSecpInterseccionListaExt ( SSecuenciaPtr * p_secValores1, SListaPtr * p_lisValores2, PFUNINTPBPB fSonIguales, PFUNPBYTEPB fDuplicar )
{
	SSecuenciaPtr *	p_secRes;
	SListaPtr *		p_lisDatos;

	if ( SSecpEsValida ( p_secValores1 ) == 1 )
	{
		p_lisDatos = SLispInterseccionExt ( p_secValores1->p_lisDatos, p_lisValores2, fSonIguales, fDuplicar );
		p_secRes = SSecpEncapsularLista ( p_lisDatos );
		if ( ES_NULO ( p_secRes ) )
		{
			SLispDestruir ( &p_lisDatos );
		}
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

SSecuenciaPtr * SSecpDiferenciaListaExt ( SSecuenciaPtr * p_secValores1, SListaPtr * p_lisValores2, PFUNINTPBPB fSonIguales, PFUNPBYTEPB fDuplicar )
{
	SSecuenciaPtr *	p_secRes;
	SListaPtr *		p_lisDatos;

	if ( SSecpEsValida ( p_secValores1 ) == 1 )
	{
		p_lisDatos = SLispDiferenciaExt ( p_secValores1->p_lisDatos, p_lisValores2, fSonIguales, fDuplicar );
		p_secRes = SSecpEncapsularLista ( p_lisDatos );
		if ( ES_NULO ( p_secRes ) )
		{
			SLispDestruir ( &p_lisDatos );
		}
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

