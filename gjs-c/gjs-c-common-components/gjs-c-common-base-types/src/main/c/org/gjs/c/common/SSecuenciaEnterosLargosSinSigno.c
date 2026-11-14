#include "SSecuenciaEnterosLargosSinSigno.h"


#include "TiposBasicosConfig.h"


extern int _SLisIntLssBuscarSiguiente ( SLista * p_lisDatos, unsigned long ulDato, int iPos );
extern int _SLisIntLssRepeticiones ( SLista * p_lisDatos, unsigned long ulDato );

static SSecuenciaEnterosLargosSinSigno * _SSecIntLssEnvolver ( SSecuencia * p_secDatos );
static SSecuenciaEnterosLargosSinSigno * _SSecIntLssEnvolverExtraidos ( SSecuenciaEnterosLargosSinSigno * p_secObj, SSecuencia * p_secExt );



SSecuenciaEnterosLargosSinSigno * SSecIntLssCrear ()
{
	SSecuenciaEnterosLargosSinSigno * p_secObj;
	
	p_secObj = (SSecuenciaEnterosLargosSinSigno *) MemReservar ( sizeof ( SSecuenciaEnterosLargosSinSigno ) );
	if ( ES_VALIDO ( p_secObj ) )
	{
		p_secObj->p_secDatos = SSecCrear ();
	}
	return ( p_secObj );
}

/* Secuencia con COPIAS de los valores de la lista, que no se toca. */
SSecuenciaEnterosLargosSinSigno * SSecIntLssCrearDesdeLista ( SListaEnterosLargosSinSigno * p_lisValores )
{
	SSecuenciaEnterosLargosSinSigno * p_secRes;

	if ( ES_VALIDO ( p_lisValores ) )
	{
		p_secRes = _SSecIntLssEnvolver ( SSecCrearDesdeLista ( p_lisValores->p_lisDatos ) );
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

void SSecIntLssDestruir ( SSecuenciaEnterosLargosSinSigno ** p_p_secObj )
{
	SSecuenciaEnterosLargosSinSigno * p_secObj;
	
	if ( ES_VALIDO ( p_p_secObj ) )
	{
		p_secObj = *p_p_secObj;

		if ( ES_VALIDO ( p_secObj ) )
		{
			SSecDestruir ( &(p_secObj->p_secDatos) );
			MemLiberar ( (void **) p_p_secObj );
		}
	}
}

int SSecIntLssEsValida ( SSecuenciaEnterosLargosSinSigno * p_secObj )
{
	int iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SSecEsValida ( p_secObj->p_secDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecIntLssEstaVacia ( SSecuenciaEnterosLargosSinSigno * p_secObj )
{
	int iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SSecEstaVacia ( p_secObj->p_secDatos );
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

int SSecIntLssNumElementos ( SSecuenciaEnterosLargosSinSigno * p_secObj )
{
	int iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SSecNumElementos ( p_secObj->p_secDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

unsigned long SSecIntLssElemento ( SSecuenciaEnterosLargosSinSigno * p_secObj, int iElem )
{
	unsigned long	ulRes;
	SElemento *		p_elmObj;

	if ( ES_VALIDO ( p_secObj ) )
	{
		p_elmObj = SSecElemento ( p_secObj->p_secDatos, iElem );
		if ( ES_VALIDO ( p_elmObj ) )
		{
			ulRes = SElmEnteroLargoSinSigno ( p_elmObj );
		}
		else
		{
			ulRes = 0;
		}
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

int SSecIntLssInsertar ( SSecuenciaEnterosLargosSinSigno * p_secObj, unsigned long ulDato )
{
	int			iRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_secObj ) )
	{
		p_elmObj = SElmCrearEnteroLargoSinSigno ();
		if ( ES_VALIDO ( p_elmObj ) )
		{
			if ( SElmEscribirEnteroLargoSinSigno ( p_elmObj, ulDato ) == 1 )
			{
				iRes = SSecInsertar ( p_secObj->p_secDatos, p_elmObj );
			}
			else
			{
				iRes = 0;
			}
			if ( iRes != 1 )
			{
				SElmDestruir ( &p_elmObj );
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

int SSecIntLssEliminar ( SSecuenciaEnterosLargosSinSigno * p_secObj, int iElem )
{
	int iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SSecEliminar ( p_secObj->p_secDatos, iElem );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecIntLssVaciar ( SSecuenciaEnterosLargosSinSigno * p_secObj )
{
	int iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SSecVaciar ( p_secObj->p_secDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecIntLssExiste ( SSecuenciaEnterosLargosSinSigno * p_secObj, unsigned long ulDato )
{
	int			iRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_secObj ) ) 
	{
		iRes = 0;
		/* Se recorre la CADENA de elementos, no por indice: SSecElemento
		   entra por el extremo mas cercano, asi que un barrido por indice
		   seria cuadratico. Igual que en SListaEnteros. */
		p_elmObj = SSecElemento ( p_secObj->p_secDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) && ( iRes == 0 ) )
		{
			if ( SElmEnteroLargoSinSigno ( p_elmObj ) == ulDato )
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
	return ( iRes );
}

/* Busquedas por la cadena, compartidas con SListaEnterosLargosSinSigno. Repeticiones:
   cuantos iguales hay, 0 si ninguno. Buscar es BuscarPrimero: la posicion del
   primero igual, o -1. BuscarSiguiente busca DETRAS de iPos: con -1, desde el
   principio. */
int SSecIntLssRepeticiones ( SSecuenciaEnterosLargosSinSigno * p_secObj, unsigned long ulDato )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = _SLisIntLssRepeticiones ( SSecLista ( p_secObj->p_secDatos ), ulDato );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecIntLssBuscar ( SSecuenciaEnterosLargosSinSigno * p_secObj, unsigned long ulDato )
{
	return ( SSecIntLssBuscarPrimero ( p_secObj, ulDato ) );
}

int SSecIntLssBuscarPrimero ( SSecuenciaEnterosLargosSinSigno * p_secObj, unsigned long ulDato )
{
	return ( SSecIntLssBuscarSiguiente ( p_secObj, ulDato, -1 ) );
}

int SSecIntLssBuscarSiguiente ( SSecuenciaEnterosLargosSinSigno * p_secObj, unsigned long ulDato, int iPos )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = _SLisIntLssBuscarSiguiente ( SSecLista ( p_secObj->p_secDatos ), ulDato, iPos );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

SSecuenciaEnterosLargosSinSigno * SSecIntLssExtraerUnicos ( SSecuenciaEnterosLargosSinSigno * p_secObj )
{
	int									iError;
	unsigned long						ulDato;
	SSecuenciaEnterosLargosSinSigno *	p_secRes;
	SElemento *							p_elmObj;

	if ( ES_VALIDO ( p_secObj ) )
	{
		p_secRes = SSecIntLssCrear ();
		iError = MemEsInvalida ( p_secRes );
		/* Se recorre la CADENA de elementos, no por indice: SSecElemento
		   entra por el extremo mas cercano, asi que un barrido por indice
		   seria cuadratico. Igual que en SListaEnteros. */
		p_elmObj = SSecElemento ( p_secObj->p_secDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) && ( iError == 0 ) )
		{
			ulDato = SElmEnteroLargoSinSigno ( p_elmObj );
			if ( SSecIntLssExiste ( p_secRes, ulDato ) == 0 )
			{
				if ( SSecIntLssInsertar ( p_secRes, ulDato ) != 1 )
				{
					iError = 1;
				}
			}
			p_elmObj = SElmSucesor ( p_elmObj );
		}
		if ( iError == 1 )
		{
			SSecIntLssDestruir ( &p_secRes );
			ERROR_ESTABLECER ( ERR_GENERAL_OPERATIVO );
		}
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

int SSecIntLssTieneRepetidos ( SSecuenciaEnterosLargosSinSigno * p_secObj )
{
	int									iRes;
	int									iError;
	unsigned long						ulDato;
	SSecuenciaEnterosLargosSinSigno *	p_secDistintos;
	SElemento *							p_elmObj;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = 0;
		p_secDistintos = SSecIntLssCrear ();
		iError = MemEsInvalida ( p_secDistintos );
		/* Se recorre la CADENA de elementos, no por indice: SSecElemento
		   entra por el extremo mas cercano, asi que un barrido por indice
		   seria cuadratico. Igual que en SListaEnteros. */
		p_elmObj = SSecElemento ( p_secObj->p_secDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) && ( iError == 0 ) && ( iRes == 0 ) )
		{
			ulDato = SElmEnteroLargoSinSigno ( p_elmObj );
			if ( SSecIntLssExiste ( p_secDistintos, ulDato ) == 1 )
			{
				iRes = 1;
			}
			else
			{
				if ( SSecIntLssInsertar ( p_secDistintos, ulDato ) != 1 )
				{
					iError = 1;
				}
			}
			p_elmObj = SElmSucesor ( p_elmObj );
		}
		SSecIntLssDestruir ( &p_secDistintos );
		if ( iError == 1 )
		{
			ERROR_ESTABLECER ( ERR_GENERAL_OPERATIVO );
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

unsigned long SSecIntLssMin ( SSecuenciaEnterosLargosSinSigno * p_secObj )
{
	unsigned long	ulDato;
	unsigned long	ulRes;
	SElemento *		p_elmObj;

	if ( ES_VALIDO ( p_secObj ) )
	{
		ulRes = ULONG_MAX;
		/* Se recorre la CADENA de elementos, no por indice: SSecElemento
		   entra por el extremo mas cercano, asi que un barrido por indice
		   seria cuadratico. Igual que en SListaEnteros. */
		p_elmObj = SSecElemento ( p_secObj->p_secDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) )
		{
			ulDato = SElmEnteroLargoSinSigno ( p_elmObj );
			if ( ulDato < ulRes )
			{
				ulRes = ulDato;
			}
			p_elmObj = SElmSucesor ( p_elmObj );
		}
	}
	else
	{
		ERROR_ESTABLECER ( ERR_PARAMETROS );
		ulRes = 0;
	}
	return ( ulRes );
}

unsigned long SSecIntLssMax ( SSecuenciaEnterosLargosSinSigno * p_secObj )
{
	unsigned long	ulDato;
	unsigned long	ulRes;
	SElemento *		p_elmObj;

	if ( ES_VALIDO ( p_secObj ) )
	{
		ulRes = 0;
		/* Se recorre la CADENA de elementos, no por indice: SSecElemento
		   entra por el extremo mas cercano, asi que un barrido por indice
		   seria cuadratico. Igual que en SListaEnteros. */
		p_elmObj = SSecElemento ( p_secObj->p_secDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) )
		{
			ulDato = SElmEnteroLargoSinSigno ( p_elmObj );
			if ( ulDato > ulRes )
			{
				ulRes = ulDato;
			}
			p_elmObj = SElmSucesor ( p_elmObj );
		}
	}
	else
	{
		ERROR_ESTABLECER ( ERR_PARAMETROS );
		ulRes = 0;
	}
	return ( ulRes );
}

void SSecIntLssObtenerParametros ( SSecuenciaEnterosLargosSinSigno * p_secObj, unsigned long * p_ulMin, unsigned long * p_ulMax, double * p_dMed )
{
	unsigned long	ulDato;
	int				iNumElems;
	SElemento *		p_elmObj;

	if ( ES_VALIDO ( p_secObj ) && ES_VALIDO ( p_ulMin ) && ES_VALIDO ( p_ulMax ) && ES_VALIDO ( p_dMed ) )
	{
		*p_ulMin = ULONG_MAX;
		*p_ulMax = 0;
		*p_dMed = 0.0;
		iNumElems = SSecIntLssNumElementos ( p_secObj );
		/* Se recorre la CADENA de elementos, no por indice: SSecElemento
		   entra por el extremo mas cercano, asi que un barrido por indice
		   seria cuadratico. Igual que en SListaEnteros. */
		p_elmObj = SSecElemento ( p_secObj->p_secDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) )
		{
			ulDato = SElmEnteroLargoSinSigno ( p_elmObj );
			if ( ulDato > *p_ulMax )
			{
				*p_ulMax = ulDato;
			}
			if ( ulDato < *p_ulMin )
			{
				*p_ulMin = ulDato;
			}
			*p_dMed = *p_dMed + (double) ulDato;
			p_elmObj = SElmSucesor ( p_elmObj );
		}
		if ( iNumElems > 0 )
		{
			*p_dMed = *p_dMed / iNumElems;
		}
	}
	else
	{
		ERROR_ESTABLECER ( ERR_PARAMETROS );
	}
}

int SSecIntLssDefinidaPositiva ( SSecuenciaEnterosLargosSinSigno * p_secObj )
{
	unsigned long	ulDato;
	int				iRes;
	SElemento *		p_elmObj;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = 1;
		/* Se recorre la CADENA de elementos, no por indice: SSecElemento
		   entra por el extremo mas cercano, asi que un barrido por indice
		   seria cuadratico. Igual que en SListaEnteros. */
		p_elmObj = SSecElemento ( p_secObj->p_secDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) && ( iRes == 1 ) )
		{
			ulDato = SElmEnteroLargoSinSigno ( p_elmObj );
			if ( ulDato == 0 )
			{
				iRes = 0;
			}
			p_elmObj = SElmSucesor ( p_elmObj );
		}
	}
	else
	{
		ERROR_ESTABLECER ( ERR_PARAMETROS );
		iRes = 0;
	}
	return ( iRes );
}

/* La secuencia interna, y la lista de esa secuencia. */
SSecuencia * SSecIntLssSecuencia ( SSecuenciaEnterosLargosSinSigno * p_secObj )
{
	SSecuencia * p_secRes;

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

SLista * SSecIntLssLista ( SSecuenciaEnterosLargosSinSigno * p_secObj )
{
	SLista * p_lisRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		p_lisRes = SSecLista ( p_secObj->p_secDatos );
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

/* Lista nueva con COPIAS de los valores, en el mismo orden. */
SListaEnterosLargosSinSigno * SSecIntLssListaIntLss ( SSecuenciaEnterosLargosSinSigno * p_secObj )
{
	SListaEnterosLargosSinSigno *	p_lisRes;
	SLista *						p_lisDatos;

	if ( ES_VALIDO ( p_secObj ) )
	{
		p_lisDatos = SLisDuplicar ( SSecIntLssLista ( p_secObj ) );
		p_lisRes = SLisIntLssEncapsular ( p_lisDatos );
		if ( ES_NULO ( p_lisRes ) )
		{
			SLisDestruir ( &p_lisDatos );
		}
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

/* Las operaciones con otras secuencias y listas delegan en las de
   SSecuencia, con su misma semantica ( ver Secuencias.md ). */
int SSecIntLssExistenTodos ( SSecuenciaEnterosLargosSinSigno * p_secObj, SSecuenciaEnterosLargosSinSigno * p_secValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ES_VALIDO ( p_secValores ) )
		{
			iRes = SSecExistenTodos ( p_secObj->p_secDatos, p_secValores->p_secDatos );
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

int SSecIntLssExisteAlguno ( SSecuenciaEnterosLargosSinSigno * p_secObj, SSecuenciaEnterosLargosSinSigno * p_secValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ES_VALIDO ( p_secValores ) )
		{
			iRes = SSecExisteAlguno ( p_secObj->p_secDatos, p_secValores->p_secDatos );
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

int SSecIntLssExistenTodosLista ( SSecuenciaEnterosLargosSinSigno * p_secObj, SListaEnterosLargosSinSigno * p_lisValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			iRes = SSecExistenTodosLista ( p_secObj->p_secDatos, p_lisValores->p_lisDatos );
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

int SSecIntLssExisteAlgunoLista ( SSecuenciaEnterosLargosSinSigno * p_secObj, SListaEnterosLargosSinSigno * p_lisValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			iRes = SSecExisteAlgunoLista ( p_secObj->p_secDatos, p_lisValores->p_lisDatos );
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

/* Eliminar destruye todas las apariciones de cada valor. */
int SSecIntLssEliminarSecuencia ( SSecuenciaEnterosLargosSinSigno * p_secObj, SSecuenciaEnterosLargosSinSigno * p_secValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ES_VALIDO ( p_secValores ) )
		{
			iRes = SSecEliminarSecuencia ( p_secObj->p_secDatos, p_secValores->p_secDatos );
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

int SSecIntLssEliminarLista ( SSecuenciaEnterosLargosSinSigno * p_secObj, SListaEnterosLargosSinSigno * p_lisValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			iRes = SSecEliminarLista ( p_secObj->p_secDatos, p_lisValores->p_lisDatos );
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

/* Concatenar anade al final COPIAS de los valores, que no se tocan. */
int SSecIntLssConcatenar ( SSecuenciaEnterosLargosSinSigno * p_secObj, SSecuenciaEnterosLargosSinSigno * p_secValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ES_VALIDO ( p_secValores ) )
		{
			iRes = SSecConcatenarDup ( p_secObj->p_secDatos, p_secValores->p_secDatos );
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

int SSecIntLssConcatenarLista ( SSecuenciaEnterosLargosSinSigno * p_secObj, SListaEnterosLargosSinSigno * p_lisValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			iRes = SSecConcatenarListaDup ( p_secObj->p_secDatos, p_lisValores->p_lisDatos );
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

/* Las Extraer MUEVEN los valores a una secuencia nueva. Si no se puede
   crear, vuelven al final de p_secObj y se devuelve NULL. */
SSecuenciaEnterosLargosSinSigno * SSecIntLssExtraerSecuencia ( SSecuenciaEnterosLargosSinSigno * p_secObj, SSecuenciaEnterosLargosSinSigno * p_secValores )
{
	SSecuenciaEnterosLargosSinSigno *	p_secRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ES_VALIDO ( p_secValores ) )
		{
			p_secRes = _SSecIntLssEnvolverExtraidos ( p_secObj, SSecExtraerSecuencia ( p_secObj->p_secDatos, p_secValores->p_secDatos ) );
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

SSecuenciaEnterosLargosSinSigno * SSecIntLssExtraerLista ( SSecuenciaEnterosLargosSinSigno * p_secObj, SListaEnterosLargosSinSigno * p_lisValores )
{
	SSecuenciaEnterosLargosSinSigno *	p_secRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			p_secRes = _SSecIntLssEnvolverExtraidos ( p_secObj, SSecExtraerLista ( p_secObj->p_secDatos, p_lisValores->p_lisDatos ) );
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

/* Union, Interseccion y Diferencia crean una secuencia nueva con COPIAS de
   los valores; si algo falla, NULL. */
SSecuenciaEnterosLargosSinSigno * SSecIntLssUnion ( SSecuenciaEnterosLargosSinSigno * p_secValores1, SSecuenciaEnterosLargosSinSigno * p_secValores2 )
{
	SSecuenciaEnterosLargosSinSigno *	p_secRes;

	if ( ES_VALIDO ( p_secValores1 ) )
	{
		if ( ES_VALIDO ( p_secValores2 ) )
		{
			p_secRes = _SSecIntLssEnvolver ( SSecUnion ( p_secValores1->p_secDatos, p_secValores2->p_secDatos ) );
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

SSecuenciaEnterosLargosSinSigno * SSecIntLssInterseccion ( SSecuenciaEnterosLargosSinSigno * p_secValores1, SSecuenciaEnterosLargosSinSigno * p_secValores2 )
{
	SSecuenciaEnterosLargosSinSigno *	p_secRes;

	if ( ES_VALIDO ( p_secValores1 ) )
	{
		if ( ES_VALIDO ( p_secValores2 ) )
		{
			p_secRes = _SSecIntLssEnvolver ( SSecInterseccion ( p_secValores1->p_secDatos, p_secValores2->p_secDatos ) );
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

SSecuenciaEnterosLargosSinSigno * SSecIntLssDiferencia ( SSecuenciaEnterosLargosSinSigno * p_secValores1, SSecuenciaEnterosLargosSinSigno * p_secValores2 )
{
	SSecuenciaEnterosLargosSinSigno *	p_secRes;

	if ( ES_VALIDO ( p_secValores1 ) )
	{
		if ( ES_VALIDO ( p_secValores2 ) )
		{
			p_secRes = _SSecIntLssEnvolver ( SSecDiferencia ( p_secValores1->p_secDatos, p_secValores2->p_secDatos ) );
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

SSecuenciaEnterosLargosSinSigno * SSecIntLssUnionLista ( SSecuenciaEnterosLargosSinSigno * p_secValores1, SListaEnterosLargosSinSigno * p_lisValores2 )
{
	SSecuenciaEnterosLargosSinSigno *	p_secRes;

	if ( ES_VALIDO ( p_secValores1 ) )
	{
		if ( ES_VALIDO ( p_lisValores2 ) )
		{
			p_secRes = _SSecIntLssEnvolver ( SSecUnionLista ( p_secValores1->p_secDatos, p_lisValores2->p_lisDatos ) );
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

SSecuenciaEnterosLargosSinSigno * SSecIntLssInterseccionLista ( SSecuenciaEnterosLargosSinSigno * p_secValores1, SListaEnterosLargosSinSigno * p_lisValores2 )
{
	SSecuenciaEnterosLargosSinSigno *	p_secRes;

	if ( ES_VALIDO ( p_secValores1 ) )
	{
		if ( ES_VALIDO ( p_lisValores2 ) )
		{
			p_secRes = _SSecIntLssEnvolver ( SSecInterseccionLista ( p_secValores1->p_secDatos, p_lisValores2->p_lisDatos ) );
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

SSecuenciaEnterosLargosSinSigno * SSecIntLssDiferenciaLista ( SSecuenciaEnterosLargosSinSigno * p_secValores1, SListaEnterosLargosSinSigno * p_lisValores2 )
{
	SSecuenciaEnterosLargosSinSigno *	p_secRes;

	if ( ES_VALIDO ( p_secValores1 ) )
	{
		if ( ES_VALIDO ( p_lisValores2 ) )
		{
			p_secRes = _SSecIntLssEnvolver ( SSecDiferenciaLista ( p_secValores1->p_secDatos, p_lisValores2->p_lisDatos ) );
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

/* Envuelve una secuencia ya creada; si no hay o no se puede envolver, NULL y
   la secuencia se destruye. */
static SSecuenciaEnterosLargosSinSigno * _SSecIntLssEnvolver ( SSecuencia * p_secDatos )
{
	SSecuenciaEnterosLargosSinSigno * p_secRes;

	if ( ES_VALIDO ( p_secDatos ) )
	{
		p_secRes = (SSecuenciaEnterosLargosSinSigno *) MemReservar ( sizeof ( SSecuenciaEnterosLargosSinSigno ) );
		if ( ES_VALIDO ( p_secRes ) )
		{
			p_secRes->p_secDatos = p_secDatos;
		}
		else
		{
			SSecDestruir ( &p_secDatos );
		}
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

/* Envuelve lo que haya sacado una Extraer de SSecuencia. Si no se
   puede, los valores vuelven al final de p_secObj: no se pierden. */
static SSecuenciaEnterosLargosSinSigno * _SSecIntLssEnvolverExtraidos ( SSecuenciaEnterosLargosSinSigno * p_secObj, SSecuencia * p_secExt )
{
	SSecuenciaEnterosLargosSinSigno * p_secRes;

	if ( ES_VALIDO ( p_secExt ) )
	{
		p_secRes = (SSecuenciaEnterosLargosSinSigno *) MemReservar ( sizeof ( SSecuenciaEnterosLargosSinSigno ) );
		if ( ES_VALIDO ( p_secRes ) )
		{
			p_secRes->p_secDatos = p_secExt;
		}
		else
		{
			SSecConcatenar ( p_secObj->p_secDatos, p_secExt );
			SSecDestruir ( &p_secExt );
		}
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

