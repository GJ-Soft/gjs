#include "SSecuenciaUnicaPtr.h"

#include "TiposBasicosConfig.h"


/* Los helpers comparan con fSonIguales si no es NULL y, si no, con iNumBytes;
   y copian con fDuplicar si no es NULL y, si no, con iNumBytes. */
static int _SSecpUnTieneRepetidos ( SListaPtr * p_lisDatos, int iNumBytes, PFUNINTPBPB fSonIguales );
static int _SSecpUnExiste ( SSecuenciaPtr * p_secObj, SElementoPtr * p_elpDatos, int iNumBytes, PFUNINTPBPB fSonIguales );
static int _SSecpUnInsertar ( SSecuenciaUnicaPtr * p_secObj, SElementoPtr * p_elpDatos, int iNumBytes, PFUNINTPBPB fSonIguales );
static int _SSecpUnCopiar ( SSecuenciaPtr * p_secDest, SListaPtr * p_lisValores, int iNumBytes, PFUNINTPBPB fSonIguales, PFUNPBYTEPB fDuplicar );
static int _SSecpUnMover ( SSecuenciaPtr * p_secDest, SListaPtr * p_lisValores, int iNumBytes, PFUNINTPBPB fSonIguales );
static SSecuenciaUnicaPtr * _SSecpUnCrearDesdeLista ( SListaPtr * p_lisValores, int iNumBytes, PFUNINTPBPB fSonIguales, PFUNPBYTEPB fDuplicar );
static SSecuenciaUnicaPtr * _SSecpUnUnir ( SSecuenciaUnicaPtr * p_secValores1, SSecuenciaUnicaPtr * p_secValores2, int iNumBytes, PFUNINTPBPB fSonIguales, PFUNPBYTEPB fDuplicar );
static SSecuenciaUnicaPtr * _SSecpUnEnvolver ( SSecuenciaPtr * p_secDatos );
static SSecuenciaUnicaPtr * _SSecpUnEnvolverExtraidos ( SSecuenciaUnicaPtr * p_secObj, SSecuenciaPtr * p_secExt );



SSecuenciaUnicaPtr * SSecpUnCrear ()
{
	SSecuenciaUnicaPtr * p_secObj;

	p_secObj = (SSecuenciaUnicaPtr *) MemReservar ( sizeof ( SSecuenciaUnicaPtr ) );
	if ( ES_VALIDO ( p_secObj ) )
	{
		p_secObj->p_secDatos = SSecpCrear ();
	}
	return ( p_secObj );
}

/* Secuencia con COPIAS de los datos de la lista, que no se toca; los repetidos
   se copian una vez, en el orden de su primera aparicion. Comparan y copian
   con iNumBytes, o con fSonIguales y fDuplicar en las Ext. Si falla alguna
   copia, NULL. */
SSecuenciaUnicaPtr * SSecpUnCrearDesdeLista ( SListaPtr * p_lisValores, int iNumBytes )
{
	return ( _SSecpUnCrearDesdeLista ( p_lisValores, iNumBytes, NULL, NULL ) );
}

SSecuenciaUnicaPtr * SSecpUnCrearDesdeListaExt ( SListaPtr * p_lisValores, PFUNINTPBPB fSonIguales, PFUNPBYTEPB fDuplicar )
{
	return ( _SSecpUnCrearDesdeLista ( p_lisValores, 0, fSonIguales, fDuplicar ) );
}

SSecuenciaUnicaPtr * SSecpUnCrearDesdeSecuencia ( SSecuenciaPtr * p_secValores, int iNumBytes )
{
	return ( _SSecpUnCrearDesdeLista ( SSecpLista ( p_secValores ), iNumBytes, NULL, NULL ) );
}

SSecuenciaUnicaPtr * SSecpUnCrearDesdeSecuenciaExt ( SSecuenciaPtr * p_secValores, PFUNINTPBPB fSonIguales, PFUNPBYTEPB fDuplicar )
{
	return ( _SSecpUnCrearDesdeLista ( SSecpLista ( p_secValores ), 0, fSonIguales, fDuplicar ) );
}

void SSecpUnDestruir ( SSecuenciaUnicaPtr ** p_p_secObj )
{
	SSecuenciaUnicaPtr * p_secObj;

	if ( ES_VALIDO ( p_p_secObj ) )
	{
		p_secObj = *p_p_secObj;

		if ( ES_VALIDO ( p_secObj ) )
		{
			SSecpDestruir ( &(p_secObj->p_secDatos) );
			MemLiberar ( (void **) p_p_secObj );
		}
	}
}

/* Valida, y sin repetidos segun iNumBytes o fSonIguales. Comprobarlo recorre
   la secuencia para cada elemento: las demas funciones no la llaman, porque
   Insertar y las operaciones ya mantienen la secuencia sin repetidos. */
int SSecpUnEsValida ( SSecuenciaUnicaPtr * p_secObj, int iNumBytes )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( SSecpEsValida ( p_secObj->p_secDatos ) == 1 )
		{
			iRes = 1 - _SSecpUnTieneRepetidos ( SSecpLista ( p_secObj->p_secDatos ), iNumBytes, NULL );
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

int SSecpUnEsValidaExt ( SSecuenciaUnicaPtr * p_secObj, PFUNINTPBPB fSonIguales )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( SSecpEsValida ( p_secObj->p_secDatos ) == 1 )
		{
			if ( ES_VALIDO ( fSonIguales ) )
			{
				iRes = 1 - _SSecpUnTieneRepetidos ( SSecpLista ( p_secObj->p_secDatos ), 0, fSonIguales );
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

int SSecpUnNumElementos ( SSecuenciaUnicaPtr * p_secObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SSecpNumElementos ( p_secObj->p_secDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecpUnEstaVacia ( SSecuenciaUnicaPtr * p_secObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SSecpEstaVacia ( p_secObj->p_secDatos );
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

byte * SSecpUnElemento ( SSecuenciaUnicaPtr * p_secObj, int iElem )
{
	byte *	p_byRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		p_byRes = SSecpElemento ( p_secObj->p_secDatos, iElem );
	}
	else
	{
		p_byRes = NULL;
	}
	return ( p_byRes );
}

SElementoPtr * SSecpUnElementoPtr ( SSecuenciaUnicaPtr * p_secObj, int iElem )
{
	SElementoPtr *	p_elpRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		p_elpRes = SSecpElementoPtr ( p_secObj->p_secDatos, iElem );
	}
	else
	{
		p_elpRes = NULL;
	}
	return ( p_elpRes );
}

/* Busquedas: delegan en las de SSecuenciaPtr. Comparan iNumBytes, o con
   fSonIguales en las Ext; las Ptr, con los datos de un elemento, que no hace
   falta que este en la secuencia. Buscar da la posicion, o -1. */
int SSecpUnExiste ( SSecuenciaUnicaPtr * p_secObj, byte * p_byDatos, int iNumBytes )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SSecpExiste ( p_secObj->p_secDatos, p_byDatos, iNumBytes );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecpUnExistePtr ( SSecuenciaUnicaPtr * p_secObj, SElementoPtr * p_elpDatos, int iNumBytes )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SSecpExistePtr ( p_secObj->p_secDatos, p_elpDatos, iNumBytes );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecpUnExisteExt ( SSecuenciaUnicaPtr * p_secObj, byte * p_byDatos, PFUNINTPBPB fSonIguales )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SSecpExisteExt ( p_secObj->p_secDatos, p_byDatos, fSonIguales );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecpUnExisteExtPtr ( SSecuenciaUnicaPtr * p_secObj, SElementoPtr * p_elpDatos, PFUNINTPBPB fSonIguales )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SSecpExisteExtPtr ( p_secObj->p_secDatos, p_elpDatos, fSonIguales );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecpUnBuscar ( SSecuenciaUnicaPtr * p_secObj, byte * p_byDatos, int iNumBytes )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SSecpBuscar ( p_secObj->p_secDatos, p_byDatos, iNumBytes );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SSecpUnBuscarPtr ( SSecuenciaUnicaPtr * p_secObj, SElementoPtr * p_elpDatos, int iNumBytes )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SSecpBuscarPtr ( p_secObj->p_secDatos, p_elpDatos, iNumBytes );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SSecpUnBuscarExt ( SSecuenciaUnicaPtr * p_secObj, byte * p_byDatos, PFUNINTPBPB fSonIguales )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SSecpBuscarExt ( p_secObj->p_secDatos, p_byDatos, fSonIguales );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SSecpUnBuscarExtPtr ( SSecuenciaUnicaPtr * p_secObj, SElementoPtr * p_elpDatos, PFUNINTPBPB fSonIguales )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SSecpBuscarExtPtr ( p_secObj->p_secDatos, p_elpDatos, fSonIguales );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

/* Insertan al final si no hay otro igual; si lo hay, 0 y el dato sigue
   siendo del llamante. Las Ptr enganchan ese mismo elemento. */
int SSecpUnInsertar ( SSecuenciaUnicaPtr * p_secObj, byte * p_byDatos, int iNumBytes )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ES_VALIDO ( p_byDatos ) )
		{
			if ( SSecpExiste ( p_secObj->p_secDatos, p_byDatos, iNumBytes ) == 0 )
			{
				iRes = SSecpInsertar ( p_secObj->p_secDatos, p_byDatos );
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

int SSecpUnInsertarPtr ( SSecuenciaUnicaPtr * p_secObj, SElementoPtr * p_elpDatos, int iNumBytes )
{
	return ( _SSecpUnInsertar ( p_secObj, p_elpDatos, iNumBytes, NULL ) );
}

int SSecpUnInsertarExt ( SSecuenciaUnicaPtr * p_secObj, byte * p_byDatos, PFUNINTPBPB fSonIguales )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ES_VALIDO ( p_byDatos ) )
		{
			if ( SSecpExisteExt ( p_secObj->p_secDatos, p_byDatos, fSonIguales ) == 0 )
			{
				iRes = SSecpInsertar ( p_secObj->p_secDatos, p_byDatos );
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

int SSecpUnInsertarExtPtr ( SSecuenciaUnicaPtr * p_secObj, SElementoPtr * p_elpDatos, PFUNINTPBPB fSonIguales )
{
	return ( _SSecpUnInsertar ( p_secObj, p_elpDatos, 0, fSonIguales ) );
}

int SSecpUnEliminar ( SSecuenciaUnicaPtr * p_secObj, int iElem )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SSecpEliminar ( p_secObj->p_secDatos, iElem );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

byte * SSecpUnExtraer ( SSecuenciaUnicaPtr * p_secObj, int iElem )
{
	byte *	p_byRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		p_byRes = SSecpExtraer ( p_secObj->p_secDatos, iElem );
	}
	else
	{
		p_byRes = NULL;
	}
	return ( p_byRes );
}

SElementoPtr * SSecpUnExtraerPtr ( SSecuenciaUnicaPtr * p_secObj, int iElem )
{
	SElementoPtr *	p_elpRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		p_elpRes = SSecpExtraerPtr ( p_secObj->p_secDatos, iElem );
	}
	else
	{
		p_elpRes = NULL;
	}
	return ( p_elpRes );
}

int SSecpUnVaciar ( SSecuenciaUnicaPtr * p_secObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SSecpVaciar ( p_secObj->p_secDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

/* Secuencia nueva con copias de los datos, en el mismo orden: de iNumBytes,
   o con fDuplicar. */
SSecuenciaUnicaPtr * SSecpUnDuplicar ( SSecuenciaUnicaPtr * p_secObj, int iNumBytes )
{
	SSecuenciaUnicaPtr *	p_secRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		p_secRes = _SSecpUnEnvolver ( SSecpDuplicar ( p_secObj->p_secDatos, iNumBytes ) );
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

SSecuenciaUnicaPtr * SSecpUnDuplicarExt ( SSecuenciaUnicaPtr * p_secObj, PFUNPBYTEPB fDuplicar )
{
	SSecuenciaUnicaPtr *	p_secRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		p_secRes = _SSecpUnEnvolver ( SSecpDuplicarExt ( p_secObj->p_secDatos, fDuplicar ) );
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

/* La secuencia interna, y la lista de esa secuencia. */
SSecuenciaPtr * SSecpUnSecuencia ( SSecuenciaUnicaPtr * p_secObj )
{
	SSecuenciaPtr *	p_secRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		p_secRes = p_secObj->p_secDatos;
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

SListaPtr * SSecpUnLista ( SSecuenciaUnicaPtr * p_secObj )
{
	return ( SSecpLista ( SSecpUnSecuencia ( p_secObj ) ) );
}

int SSecpUnLiberacionMemoriaActivada ( SSecuenciaUnicaPtr * p_secObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SSecpLiberacionMemoriaActivada ( p_secObj->p_secDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

void SSecpUnActivarLiberacionMemoria ( SSecuenciaUnicaPtr * p_secObj )
{
	if ( ES_VALIDO ( p_secObj ) )
	{
		SSecpActivarLiberacionMemoria ( p_secObj->p_secDatos );
	}
}

void SSecpUnDesactivarLiberacionMemoria ( SSecuenciaUnicaPtr * p_secObj )
{
	if ( ES_VALIDO ( p_secObj ) )
	{
		SSecpDesactivarLiberacionMemoria ( p_secObj->p_secDatos );
	}
}

/* Las operaciones con otras secuencias y listas tienen tres formas: con otra
   secuencia unica, con una secuencia y con una lista; las dos primeras pasan
   la lista de la segunda. Comparan con iNumBytes, o con fSonIguales en las
   Ext, y copian con iNumBytes o con fDuplicar. */
int SSecpUnExistenTodos ( SSecuenciaUnicaPtr * p_secObj, SSecuenciaUnicaPtr * p_secValores, int iNumBytes )
{
	int	iRes;

	if ( ES_VALIDO ( p_secValores ) )
	{
		iRes = SSecpUnExistenTodosSecuencia ( p_secObj, p_secValores->p_secDatos, iNumBytes );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecpUnExistenTodosSecuencia ( SSecuenciaUnicaPtr * p_secObj, SSecuenciaPtr * p_secValores, int iNumBytes )
{
	int	iRes;

	if ( ES_VALIDO ( p_secValores ) )
	{
		iRes = SSecpUnExistenTodosLista ( p_secObj, SSecpLista ( p_secValores ), iNumBytes );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecpUnExistenTodosLista ( SSecuenciaUnicaPtr * p_secObj, SListaPtr * p_lisValores, int iNumBytes )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			iRes = SSecpExistenTodosLista ( p_secObj->p_secDatos, p_lisValores, iNumBytes );
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

int SSecpUnExisteAlguno ( SSecuenciaUnicaPtr * p_secObj, SSecuenciaUnicaPtr * p_secValores, int iNumBytes )
{
	int	iRes;

	if ( ES_VALIDO ( p_secValores ) )
	{
		iRes = SSecpUnExisteAlgunoSecuencia ( p_secObj, p_secValores->p_secDatos, iNumBytes );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecpUnExisteAlgunoSecuencia ( SSecuenciaUnicaPtr * p_secObj, SSecuenciaPtr * p_secValores, int iNumBytes )
{
	int	iRes;

	if ( ES_VALIDO ( p_secValores ) )
	{
		iRes = SSecpUnExisteAlgunoLista ( p_secObj, SSecpLista ( p_secValores ), iNumBytes );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecpUnExisteAlgunoLista ( SSecuenciaUnicaPtr * p_secObj, SListaPtr * p_lisValores, int iNumBytes )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			iRes = SSecpExisteAlgunoLista ( p_secObj->p_secDatos, p_lisValores, iNumBytes );
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

int SSecpUnExistenTodosExt ( SSecuenciaUnicaPtr * p_secObj, SSecuenciaUnicaPtr * p_secValores, PFUNINTPBPB fSonIguales )
{
	int	iRes;

	if ( ES_VALIDO ( p_secValores ) )
	{
		iRes = SSecpUnExistenTodosSecuenciaExt ( p_secObj, p_secValores->p_secDatos, fSonIguales );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecpUnExistenTodosSecuenciaExt ( SSecuenciaUnicaPtr * p_secObj, SSecuenciaPtr * p_secValores, PFUNINTPBPB fSonIguales )
{
	int	iRes;

	if ( ES_VALIDO ( p_secValores ) )
	{
		iRes = SSecpUnExistenTodosListaExt ( p_secObj, SSecpLista ( p_secValores ), fSonIguales );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecpUnExistenTodosListaExt ( SSecuenciaUnicaPtr * p_secObj, SListaPtr * p_lisValores, PFUNINTPBPB fSonIguales )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			iRes = SSecpExistenTodosListaExt ( p_secObj->p_secDatos, p_lisValores, fSonIguales );
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

int SSecpUnExisteAlgunoExt ( SSecuenciaUnicaPtr * p_secObj, SSecuenciaUnicaPtr * p_secValores, PFUNINTPBPB fSonIguales )
{
	int	iRes;

	if ( ES_VALIDO ( p_secValores ) )
	{
		iRes = SSecpUnExisteAlgunoSecuenciaExt ( p_secObj, p_secValores->p_secDatos, fSonIguales );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecpUnExisteAlgunoSecuenciaExt ( SSecuenciaUnicaPtr * p_secObj, SSecuenciaPtr * p_secValores, PFUNINTPBPB fSonIguales )
{
	int	iRes;

	if ( ES_VALIDO ( p_secValores ) )
	{
		iRes = SSecpUnExisteAlgunoListaExt ( p_secObj, SSecpLista ( p_secValores ), fSonIguales );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecpUnExisteAlgunoListaExt ( SSecuenciaUnicaPtr * p_secObj, SListaPtr * p_lisValores, PFUNINTPBPB fSonIguales )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			iRes = SSecpExisteAlgunoListaExt ( p_secObj->p_secDatos, p_lisValores, fSonIguales );
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

int SSecpUnEliminarSecuenciaUn ( SSecuenciaUnicaPtr * p_secObj, SSecuenciaUnicaPtr * p_secValores, int iNumBytes )
{
	int	iRes;

	if ( ES_VALIDO ( p_secValores ) )
	{
		iRes = SSecpUnEliminarSecuencia ( p_secObj, p_secValores->p_secDatos, iNumBytes );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecpUnEliminarSecuencia ( SSecuenciaUnicaPtr * p_secObj, SSecuenciaPtr * p_secValores, int iNumBytes )
{
	int	iRes;

	if ( ES_VALIDO ( p_secValores ) )
	{
		iRes = SSecpUnEliminarLista ( p_secObj, SSecpLista ( p_secValores ), iNumBytes );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecpUnEliminarLista ( SSecuenciaUnicaPtr * p_secObj, SListaPtr * p_lisValores, int iNumBytes )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			iRes = SSecpEliminarLista ( p_secObj->p_secDatos, p_lisValores, iNumBytes );
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

int SSecpUnEliminarSecuenciaUnExt ( SSecuenciaUnicaPtr * p_secObj, SSecuenciaUnicaPtr * p_secValores, PFUNINTPBPB fSonIguales )
{
	int	iRes;

	if ( ES_VALIDO ( p_secValores ) )
	{
		iRes = SSecpUnEliminarSecuenciaExt ( p_secObj, p_secValores->p_secDatos, fSonIguales );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecpUnEliminarSecuenciaExt ( SSecuenciaUnicaPtr * p_secObj, SSecuenciaPtr * p_secValores, PFUNINTPBPB fSonIguales )
{
	int	iRes;

	if ( ES_VALIDO ( p_secValores ) )
	{
		iRes = SSecpUnEliminarListaExt ( p_secObj, SSecpLista ( p_secValores ), fSonIguales );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecpUnEliminarListaExt ( SSecuenciaUnicaPtr * p_secObj, SListaPtr * p_lisValores, PFUNINTPBPB fSonIguales )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			iRes = SSecpEliminarListaExt ( p_secObj->p_secDatos, p_lisValores, fSonIguales );
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

/* Concatenar MUEVE al final los datos que no esten ya; los que estan se
   quedan en la de entrada, y de los repetidos de esta solo pasa el primero.
   Las Dup anaden COPIAS de los que falten y no tocan la de entrada. */
int SSecpUnConcatenar ( SSecuenciaUnicaPtr * p_secObj, SSecuenciaUnicaPtr * p_secValores, int iNumBytes )
{
	int	iRes;

	if ( ES_VALIDO ( p_secValores ) )
	{
		iRes = SSecpUnConcatenarSecuencia ( p_secObj, p_secValores->p_secDatos, iNumBytes );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecpUnConcatenarSecuencia ( SSecuenciaUnicaPtr * p_secObj, SSecuenciaPtr * p_secValores, int iNumBytes )
{
	int	iRes;

	if ( ES_VALIDO ( p_secValores ) )
	{
		iRes = SSecpUnConcatenarLista ( p_secObj, SSecpLista ( p_secValores ), iNumBytes );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecpUnConcatenarLista ( SSecuenciaUnicaPtr * p_secObj, SListaPtr * p_lisValores, int iNumBytes )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			iRes = _SSecpUnMover ( p_secObj->p_secDatos, p_lisValores, iNumBytes, NULL );
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

int SSecpUnConcatenarExt ( SSecuenciaUnicaPtr * p_secObj, SSecuenciaUnicaPtr * p_secValores, PFUNINTPBPB fSonIguales )
{
	int	iRes;

	if ( ES_VALIDO ( p_secValores ) )
	{
		iRes = SSecpUnConcatenarSecuenciaExt ( p_secObj, p_secValores->p_secDatos, fSonIguales );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecpUnConcatenarSecuenciaExt ( SSecuenciaUnicaPtr * p_secObj, SSecuenciaPtr * p_secValores, PFUNINTPBPB fSonIguales )
{
	int	iRes;

	if ( ES_VALIDO ( p_secValores ) )
	{
		iRes = SSecpUnConcatenarListaExt ( p_secObj, SSecpLista ( p_secValores ), fSonIguales );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecpUnConcatenarListaExt ( SSecuenciaUnicaPtr * p_secObj, SListaPtr * p_lisValores, PFUNINTPBPB fSonIguales )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			iRes = _SSecpUnMover ( p_secObj->p_secDatos, p_lisValores, 0, fSonIguales );
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

int SSecpUnConcatenarDup ( SSecuenciaUnicaPtr * p_secObj, SSecuenciaUnicaPtr * p_secValores, int iNumBytes )
{
	int	iRes;

	if ( ES_VALIDO ( p_secValores ) )
	{
		iRes = SSecpUnConcatenarSecuenciaDup ( p_secObj, p_secValores->p_secDatos, iNumBytes );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecpUnConcatenarSecuenciaDup ( SSecuenciaUnicaPtr * p_secObj, SSecuenciaPtr * p_secValores, int iNumBytes )
{
	int	iRes;

	if ( ES_VALIDO ( p_secValores ) )
	{
		iRes = SSecpUnConcatenarListaDup ( p_secObj, SSecpLista ( p_secValores ), iNumBytes );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecpUnConcatenarListaDup ( SSecuenciaUnicaPtr * p_secObj, SListaPtr * p_lisValores, int iNumBytes )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			iRes = _SSecpUnCopiar ( p_secObj->p_secDatos, p_lisValores, iNumBytes, NULL, NULL );
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

int SSecpUnConcatenarDupExt ( SSecuenciaUnicaPtr * p_secObj, SSecuenciaUnicaPtr * p_secValores, PFUNINTPBPB fSonIguales, PFUNPBYTEPB fDuplicar )
{
	int	iRes;

	if ( ES_VALIDO ( p_secValores ) )
	{
		iRes = SSecpUnConcatenarSecuenciaDupExt ( p_secObj, p_secValores->p_secDatos, fSonIguales, fDuplicar );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecpUnConcatenarSecuenciaDupExt ( SSecuenciaUnicaPtr * p_secObj, SSecuenciaPtr * p_secValores, PFUNINTPBPB fSonIguales, PFUNPBYTEPB fDuplicar )
{
	int	iRes;

	if ( ES_VALIDO ( p_secValores ) )
	{
		iRes = SSecpUnConcatenarListaDupExt ( p_secObj, SSecpLista ( p_secValores ), fSonIguales, fDuplicar );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecpUnConcatenarListaDupExt ( SSecuenciaUnicaPtr * p_secObj, SListaPtr * p_lisValores, PFUNINTPBPB fSonIguales, PFUNPBYTEPB fDuplicar )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			iRes = _SSecpUnCopiar ( p_secObj->p_secDatos, p_lisValores, 0, fSonIguales, fDuplicar );
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

/* Las Extraer MUEVEN los datos a una secuencia unica nueva, que hereda la
   liberacion del origen. Si no se puede crear, vuelven al final de p_secObj
   y se devuelve NULL. */
SSecuenciaUnicaPtr * SSecpUnExtraerSecuenciaUn ( SSecuenciaUnicaPtr * p_secObj, SSecuenciaUnicaPtr * p_secValores, int iNumBytes )
{
	SSecuenciaUnicaPtr *	p_secRes;

	if ( ES_VALIDO ( p_secValores ) )
	{
		p_secRes = SSecpUnExtraerSecuencia ( p_secObj, p_secValores->p_secDatos, iNumBytes );
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

SSecuenciaUnicaPtr * SSecpUnExtraerSecuencia ( SSecuenciaUnicaPtr * p_secObj, SSecuenciaPtr * p_secValores, int iNumBytes )
{
	SSecuenciaUnicaPtr *	p_secRes;

	if ( ES_VALIDO ( p_secValores ) )
	{
		p_secRes = SSecpUnExtraerLista ( p_secObj, SSecpLista ( p_secValores ), iNumBytes );
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

SSecuenciaUnicaPtr * SSecpUnExtraerLista ( SSecuenciaUnicaPtr * p_secObj, SListaPtr * p_lisValores, int iNumBytes )
{
	SSecuenciaUnicaPtr *	p_secRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			p_secRes = _SSecpUnEnvolverExtraidos ( p_secObj, SSecpExtraerLista ( p_secObj->p_secDatos, p_lisValores, iNumBytes ) );
		}
		else
		{
			p_secRes = NULL;
		}
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

SSecuenciaUnicaPtr * SSecpUnExtraerSecuenciaUnExt ( SSecuenciaUnicaPtr * p_secObj, SSecuenciaUnicaPtr * p_secValores, PFUNINTPBPB fSonIguales )
{
	SSecuenciaUnicaPtr *	p_secRes;

	if ( ES_VALIDO ( p_secValores ) )
	{
		p_secRes = SSecpUnExtraerSecuenciaExt ( p_secObj, p_secValores->p_secDatos, fSonIguales );
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

SSecuenciaUnicaPtr * SSecpUnExtraerSecuenciaExt ( SSecuenciaUnicaPtr * p_secObj, SSecuenciaPtr * p_secValores, PFUNINTPBPB fSonIguales )
{
	SSecuenciaUnicaPtr *	p_secRes;

	if ( ES_VALIDO ( p_secValores ) )
	{
		p_secRes = SSecpUnExtraerListaExt ( p_secObj, SSecpLista ( p_secValores ), fSonIguales );
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

SSecuenciaUnicaPtr * SSecpUnExtraerListaExt ( SSecuenciaUnicaPtr * p_secObj, SListaPtr * p_lisValores, PFUNINTPBPB fSonIguales )
{
	SSecuenciaUnicaPtr *	p_secRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			p_secRes = _SSecpUnEnvolverExtraidos ( p_secObj, SSecpExtraerListaExt ( p_secObj->p_secDatos, p_lisValores, fSonIguales ) );
		}
		else
		{
			p_secRes = NULL;
		}
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

/* Union: copias de la primera y, detras, de las de la segunda que no estan
   en la primera. Interseccion y Diferencia, copias en el orden de la
   primera. Si algo falla, NULL. */
SSecuenciaUnicaPtr * SSecpUnUnion ( SSecuenciaUnicaPtr * p_secValores1, SSecuenciaUnicaPtr * p_secValores2, int iNumBytes )
{
	SSecuenciaUnicaPtr *	p_secRes;

	if ( ES_VALIDO ( p_secValores1 ) )
	{
		if ( ES_VALIDO ( p_secValores2 ) )
		{
			p_secRes = _SSecpUnUnir ( p_secValores1, p_secValores2, iNumBytes, NULL, NULL );
		}
		else
		{
			p_secRes = NULL;
		}
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

SSecuenciaUnicaPtr * SSecpUnInterseccion ( SSecuenciaUnicaPtr * p_secValores1, SSecuenciaUnicaPtr * p_secValores2, int iNumBytes )
{
	SSecuenciaUnicaPtr *	p_secRes;

	if ( ES_VALIDO ( p_secValores1 ) )
	{
		if ( ES_VALIDO ( p_secValores2 ) )
		{
			p_secRes = _SSecpUnEnvolver ( SSecpInterseccion ( p_secValores1->p_secDatos, p_secValores2->p_secDatos, iNumBytes ) );
		}
		else
		{
			p_secRes = NULL;
		}
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

SSecuenciaUnicaPtr * SSecpUnDiferencia ( SSecuenciaUnicaPtr * p_secValores1, SSecuenciaUnicaPtr * p_secValores2, int iNumBytes )
{
	SSecuenciaUnicaPtr *	p_secRes;

	if ( ES_VALIDO ( p_secValores1 ) )
	{
		if ( ES_VALIDO ( p_secValores2 ) )
		{
			p_secRes = _SSecpUnEnvolver ( SSecpDiferencia ( p_secValores1->p_secDatos, p_secValores2->p_secDatos, iNumBytes ) );
		}
		else
		{
			p_secRes = NULL;
		}
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

SSecuenciaUnicaPtr * SSecpUnUnionExt ( SSecuenciaUnicaPtr * p_secValores1, SSecuenciaUnicaPtr * p_secValores2, PFUNINTPBPB fSonIguales, PFUNPBYTEPB fDuplicar )
{
	SSecuenciaUnicaPtr *	p_secRes;

	if ( ES_VALIDO ( p_secValores1 ) )
	{
		if ( ES_VALIDO ( p_secValores2 ) )
		{
			p_secRes = _SSecpUnUnir ( p_secValores1, p_secValores2, 0, fSonIguales, fDuplicar );
		}
		else
		{
			p_secRes = NULL;
		}
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

SSecuenciaUnicaPtr * SSecpUnInterseccionExt ( SSecuenciaUnicaPtr * p_secValores1, SSecuenciaUnicaPtr * p_secValores2, PFUNINTPBPB fSonIguales, PFUNPBYTEPB fDuplicar )
{
	SSecuenciaUnicaPtr *	p_secRes;

	if ( ES_VALIDO ( p_secValores1 ) )
	{
		if ( ES_VALIDO ( p_secValores2 ) )
		{
			p_secRes = _SSecpUnEnvolver ( SSecpInterseccionExt ( p_secValores1->p_secDatos, p_secValores2->p_secDatos, fSonIguales, fDuplicar ) );
		}
		else
		{
			p_secRes = NULL;
		}
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

SSecuenciaUnicaPtr * SSecpUnDiferenciaExt ( SSecuenciaUnicaPtr * p_secValores1, SSecuenciaUnicaPtr * p_secValores2, PFUNINTPBPB fSonIguales, PFUNPBYTEPB fDuplicar )
{
	SSecuenciaUnicaPtr *	p_secRes;

	if ( ES_VALIDO ( p_secValores1 ) )
	{
		if ( ES_VALIDO ( p_secValores2 ) )
		{
			p_secRes = _SSecpUnEnvolver ( SSecpDiferenciaExt ( p_secValores1->p_secDatos, p_secValores2->p_secDatos, fSonIguales, fDuplicar ) );
		}
		else
		{
			p_secRes = NULL;
		}
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}


static int _SSecpUnTieneRepetidos ( SListaPtr * p_lisDatos, int iNumBytes, PFUNINTPBPB fSonIguales )
{
	int				iRes;
	int				iPos;
	int				iSig;
	SElementoPtr *	p_elpObj;

	iRes = 0;
	iPos = 0;
	/* Por la CADENA, no por indice: el indice entra por el extremo mas
	   cercano, asi que un recorrido completo sale cuadratico. */
	p_elpObj = SLispElementoPtr ( p_lisDatos, 0 );
	while ( ES_VALIDO ( p_elpObj ) && ( iRes == 0 ) )
	{
		if ( ES_VALIDO ( fSonIguales ) )
		{
			iSig = SLispBuscarSiguienteExtPtr ( p_lisDatos, p_elpObj, iPos, fSonIguales );
		}
		else
		{
			iSig = SLispBuscarSiguientePtr ( p_lisDatos, p_elpObj, iPos, iNumBytes );
		}
		if ( iSig >= 0 )
		{
			iRes = 1;
		}
		iPos = iPos + 1;
		p_elpObj = SElpSucesor ( p_elpObj );
	}
	return ( iRes );
}

static int _SSecpUnExiste ( SSecuenciaPtr * p_secObj, SElementoPtr * p_elpDatos, int iNumBytes, PFUNINTPBPB fSonIguales )
{
	int iRes;

	if ( ES_VALIDO ( fSonIguales ) )
	{
		iRes = SSecpExisteExtPtr ( p_secObj, p_elpDatos, fSonIguales );
	}
	else
	{
		iRes = SSecpExistePtr ( p_secObj, p_elpDatos, iNumBytes );
	}
	return ( iRes );
}

static int _SSecpUnInsertar ( SSecuenciaUnicaPtr * p_secObj, SElementoPtr * p_elpDatos, int iNumBytes, PFUNINTPBPB fSonIguales )
{
	int iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ES_VALIDO ( p_elpDatos ) )
		{
			if ( _SSecpUnExiste ( p_secObj->p_secDatos, p_elpDatos, iNumBytes, fSonIguales ) == 0 )
			{
				iRes = SSecpInsertarPtr ( p_secObj->p_secDatos, p_elpDatos );
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

/* Anade al final de p_secDest copias de los datos de p_lisValores que no esten
   ya. 0 si p_secDest no es valida, si es la misma lista o si falla una copia;
   lo copiado hasta ahi se queda. */
static int _SSecpUnCopiar ( SSecuenciaPtr * p_secDest, SListaPtr * p_lisValores, int iNumBytes, PFUNINTPBPB fSonIguales, PFUNPBYTEPB fDuplicar )
{
	int				iRes;
	SElementoPtr *	p_elpObj;
	SElementoPtr *	p_elpNuevo;

	if ( SSecpEsValida ( p_secDest ) == 1 )
	{
		if ( SSecpLista ( p_secDest ) != p_lisValores )
		{
			iRes = 1;
			p_elpObj = SLispElementoPtr ( p_lisValores, 0 );
			while ( ES_VALIDO ( p_elpObj ) && ( iRes == 1 ) )
			{
				if ( _SSecpUnExiste ( p_secDest, p_elpObj, iNumBytes, fSonIguales ) == 0 )
				{
					if ( ES_VALIDO ( fDuplicar ) )
					{
						p_elpNuevo = SElpDuplicarExt ( p_elpObj, fDuplicar );
					}
					else
					{
						p_elpNuevo = SElpDuplicar ( p_elpObj, iNumBytes );
					}
					if ( SSecpInsertarPtr ( p_secDest, p_elpNuevo ) != 1 )
					{
						SElpDestruir ( &p_elpNuevo );
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
	return ( iRes );
}

/* Mueve al final de p_secDest los elementos de p_lisValores que no esten ya;
   los demas se quedan en p_lisValores. Si no se puede insertar uno, vuelve al
   final de p_lisValores: no se pierde. */
static int _SSecpUnMover ( SSecuenciaPtr * p_secDest, SListaPtr * p_lisValores, int iNumBytes, PFUNINTPBPB fSonIguales )
{
	int				iRes;
	int				iPos;
	SElementoPtr *	p_elpObj;
	SElementoPtr *	p_elpSig;
	SElementoPtr *	p_elpExt;

	if ( SSecpEsValida ( p_secDest ) == 1 )
	{
		if ( SSecpLista ( p_secDest ) != p_lisValores )
		{
			iRes = 1;
			iPos = 0;
			p_elpObj = SLispElementoPtr ( p_lisValores, 0 );
			while ( ES_VALIDO ( p_elpObj ) && ( iRes == 1 ) )
			{
				/* El sucesor, ANTES de extraer. */
				p_elpSig = SElpSucesor ( p_elpObj );
				if ( _SSecpUnExiste ( p_secDest, p_elpObj, iNumBytes, fSonIguales ) == 0 )
				{
					p_elpExt = SLispExtraerElemPtr ( p_lisValores, iPos );
					if ( SSecpInsertarPtr ( p_secDest, p_elpExt ) != 1 )
					{
						SLispInsertarAlFinalPtr ( p_lisValores, p_elpExt );
						iRes = 0;
					}
				}
				else
				{
					iPos = iPos + 1;
				}
				p_elpObj = p_elpSig;
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

static SSecuenciaUnicaPtr * _SSecpUnCrearDesdeLista ( SListaPtr * p_lisValores, int iNumBytes, PFUNINTPBPB fSonIguales, PFUNPBYTEPB fDuplicar )
{
	SSecuenciaUnicaPtr * p_secRes;

	if ( SLispEsValida ( p_lisValores ) == 1 )
	{
		p_secRes = SSecpUnCrear ();
		if ( _SSecpUnCopiar ( SSecpUnSecuencia ( p_secRes ), p_lisValores, iNumBytes, fSonIguales, fDuplicar ) != 1 )
		{
			SSecpUnDestruir ( &p_secRes );
		}
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

static SSecuenciaUnicaPtr * _SSecpUnUnir ( SSecuenciaUnicaPtr * p_secValores1, SSecuenciaUnicaPtr * p_secValores2, int iNumBytes, PFUNINTPBPB fSonIguales, PFUNPBYTEPB fDuplicar )
{
	SSecuenciaUnicaPtr * p_secRes;

	if ( ES_VALIDO ( fDuplicar ) )
	{
		p_secRes = SSecpUnDuplicarExt ( p_secValores1, fDuplicar );
	}
	else
	{
		p_secRes = SSecpUnDuplicar ( p_secValores1, iNumBytes );
	}
	if ( _SSecpUnCopiar ( SSecpUnSecuencia ( p_secRes ), SSecpUnLista ( p_secValores2 ), iNumBytes, fSonIguales, fDuplicar ) != 1 )
	{
		SSecpUnDestruir ( &p_secRes );
	}
	return ( p_secRes );
}

/* Envuelve una secuencia ya creada, que no tiene repetidos; si no hay o no se
   puede envolver, NULL y la secuencia se destruye. */
static SSecuenciaUnicaPtr * _SSecpUnEnvolver ( SSecuenciaPtr * p_secDatos )
{
	SSecuenciaUnicaPtr * p_secRes;

	if ( ES_VALIDO ( p_secDatos ) )
	{
		p_secRes = (SSecuenciaUnicaPtr *) MemReservar ( sizeof ( SSecuenciaUnicaPtr ) );
		if ( ES_VALIDO ( p_secRes ) )
		{
			p_secRes->p_secDatos = p_secDatos;
		}
		else
		{
			SSecpDestruir ( &p_secDatos );
		}
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

/* Envuelve lo que haya sacado una Extraer de SSecuenciaPtr. Si no se puede, los
   datos vuelven al final de p_secObj: no se pierden. */
static SSecuenciaUnicaPtr * _SSecpUnEnvolverExtraidos ( SSecuenciaUnicaPtr * p_secObj, SSecuenciaPtr * p_secExt )
{
	SSecuenciaUnicaPtr * p_secRes;

	if ( ES_VALIDO ( p_secExt ) )
	{
		p_secRes = (SSecuenciaUnicaPtr *) MemReservar ( sizeof ( SSecuenciaUnicaPtr ) );
		if ( ES_VALIDO ( p_secRes ) )
		{
			p_secRes->p_secDatos = p_secExt;
		}
		else
		{
			SSecpConcatenar ( p_secObj->p_secDatos, p_secExt );
			SSecpDestruir ( &p_secExt );
		}
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}
