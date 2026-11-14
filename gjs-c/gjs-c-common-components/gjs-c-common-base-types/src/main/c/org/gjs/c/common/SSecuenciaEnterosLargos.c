#include "SSecuenciaEnterosLargos.h"

#include "TiposBasicosConfig.h"


extern int _SLisIntlBuscarSiguiente ( SLista * p_lisDatos, long lDato, int iPos );
extern int _SLisIntlRepeticiones ( SLista * p_lisDatos, long lDato );

static SSecuenciaEnterosLargos * _SSecIntlEnvolver ( SSecuencia * p_secDatos );
static SSecuenciaEnterosLargos * _SSecIntlEnvolverExtraidos ( SSecuenciaEnterosLargos * p_secObj, SSecuencia * p_secExt );



SSecuenciaEnterosLargos * SSecIntlCrear ()
{
	SSecuenciaEnterosLargos * p_secObj;
	
	p_secObj = (SSecuenciaEnterosLargos *) MemReservar ( sizeof ( SSecuenciaEnterosLargos ) );
	if ( ES_VALIDO ( p_secObj ) )
	{
		p_secObj->p_secDatos = SSecCrear ();
	}
	return ( p_secObj );
}

/* Secuencia con COPIAS de los valores de la lista, que no se toca. */
SSecuenciaEnterosLargos * SSecIntlCrearDesdeLista ( SListaEnterosLargos * p_lisValores )
{
	SSecuenciaEnterosLargos * p_secRes;

	if ( ES_VALIDO ( p_lisValores ) )
	{
		p_secRes = _SSecIntlEnvolver ( SSecCrearDesdeLista ( p_lisValores->p_lisDatos ) );
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

void SSecIntlDestruir ( SSecuenciaEnterosLargos ** p_p_secObj )
{
	SSecuenciaEnterosLargos * p_secObj;
	
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

int SSecIntlEsValida ( SSecuenciaEnterosLargos * p_secObj )
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

int SSecIntlEstaVacia ( SSecuenciaEnterosLargos * p_secObj )
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

int SSecIntlNumElementos ( SSecuenciaEnterosLargos * p_secObj )
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

long SSecIntlElemento ( SSecuenciaEnterosLargos * p_secObj, int iElem )
{
	long		lRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_secObj ) )
	{
		p_elmObj = SSecElemento ( p_secObj->p_secDatos, iElem );
		if ( ES_VALIDO ( p_elmObj ) )
		{
			lRes = SElmEnteroLargo ( p_elmObj );
		}
		else
		{
			lRes = 0;
		}
	}
	else
	{
		lRes = 0;
	}
	return ( lRes );
}

int SSecIntlInsertar ( SSecuenciaEnterosLargos * p_secObj, long lDato )
{
	int			iRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_secObj ) )
	{
		p_elmObj = SElmCrearEnteroLargo ();
		if ( ES_VALIDO ( p_elmObj ) )
		{
			if ( SElmEscribirEnteroLargo ( p_elmObj, lDato ) == 1 )
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

int SSecIntlEliminar ( SSecuenciaEnterosLargos * p_secObj, int iElem )
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

int SSecIntlVaciar ( SSecuenciaEnterosLargos * p_secObj )
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

int SSecIntlExiste ( SSecuenciaEnterosLargos * p_secObj, long lDato )
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
			if ( SElmEnteroLargo ( p_elmObj ) == lDato )
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

/* Busquedas por la cadena, compartidas con SListaEnterosLargos. Repeticiones:
   cuantos iguales hay, 0 si ninguno. Buscar es BuscarPrimero: la posicion del
   primero igual, o -1. BuscarSiguiente busca DETRAS de iPos: con -1, desde el
   principio. */
int SSecIntlRepeticiones ( SSecuenciaEnterosLargos * p_secObj, long lDato )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = _SLisIntlRepeticiones ( SSecLista ( p_secObj->p_secDatos ), lDato );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecIntlBuscar ( SSecuenciaEnterosLargos * p_secObj, long lDato )
{
	return ( SSecIntlBuscarPrimero ( p_secObj, lDato ) );
}

int SSecIntlBuscarPrimero ( SSecuenciaEnterosLargos * p_secObj, long lDato )
{
	return ( SSecIntlBuscarSiguiente ( p_secObj, lDato, -1 ) );
}

int SSecIntlBuscarSiguiente ( SSecuenciaEnterosLargos * p_secObj, long lDato, int iPos )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = _SLisIntlBuscarSiguiente ( SSecLista ( p_secObj->p_secDatos ), lDato, iPos );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

SSecuenciaEnterosLargos * SSecIntlExtraerUnicos ( SSecuenciaEnterosLargos * p_secObj )
{
	int							iError;
	long						lDato;
	SSecuenciaEnterosLargos *	p_secRes;
	SElemento *					p_elmObj;

	if ( ES_VALIDO ( p_secObj ) )
	{
		p_secRes = SSecIntlCrear ();
		iError = MemEsInvalida ( p_secRes );
		/* Se recorre la CADENA de elementos, no por indice: SSecElemento
		   entra por el extremo mas cercano, asi que un barrido por indice
		   seria cuadratico. Igual que en SListaEnteros. */
		p_elmObj = SSecElemento ( p_secObj->p_secDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) && ( iError == 0 ) )
		{
			lDato = SElmEnteroLargo ( p_elmObj );
			if ( SSecIntlExiste ( p_secRes, lDato ) == 0 )
			{
				if ( SSecIntlInsertar ( p_secRes, lDato ) != 1 )
				{
					iError = 1;
				}
			}
			p_elmObj = SElmSucesor ( p_elmObj );
		}
		if ( iError == 1 )
		{
			SSecIntlDestruir ( &p_secRes );
			ERROR_ESTABLECER ( ERR_GENERAL_OPERATIVO );
		}
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

int SSecIntlTieneRepetidos ( SSecuenciaEnterosLargos * p_secObj )
{
	int							iRes;
	int							iError;
	long						lDato;
	SSecuenciaEnterosLargos *	p_secDistintos;
	SElemento *					p_elmObj;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = 0;
		p_secDistintos = SSecIntlCrear ();
		iError = MemEsInvalida ( p_secDistintos );
		/* Se recorre la CADENA de elementos, no por indice: SSecElemento
		   entra por el extremo mas cercano, asi que un barrido por indice
		   seria cuadratico. Igual que en SListaEnteros. */
		p_elmObj = SSecElemento ( p_secObj->p_secDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) && ( iError == 0 ) && ( iRes == 0 ) )
		{
			lDato = SElmEnteroLargo ( p_elmObj );
			if ( SSecIntlExiste ( p_secDistintos, lDato ) == 1 )
			{
				iRes = 1;
			}
			else
			{
				if ( SSecIntlInsertar ( p_secDistintos, lDato ) != 1 )
				{
					iError = 1;
				}
			}
			p_elmObj = SElmSucesor ( p_elmObj );
		}
		SSecIntlDestruir ( &p_secDistintos );
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

long SSecIntlMin ( SSecuenciaEnterosLargos * p_secObj )
{
	long		lDato;
	long		lRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_secObj ) )
	{
		lRes = LONG_MAX;
		/* Se recorre la CADENA de elementos, no por indice: SSecElemento
		   entra por el extremo mas cercano, asi que un barrido por indice
		   seria cuadratico. Igual que en SListaEnteros. */
		p_elmObj = SSecElemento ( p_secObj->p_secDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) )
		{
			lDato = SElmEnteroLargo ( p_elmObj );
			if ( lDato < lRes )
			{
				lRes = lDato;
			}
			p_elmObj = SElmSucesor ( p_elmObj );
		}
	}
	else
	{
		ERROR_ESTABLECER ( ERR_PARAMETROS );
		lRes = 0;
	}
	return ( lRes );
}

long SSecIntlMax ( SSecuenciaEnterosLargos * p_secObj )
{
	long		lDato;
	long		lRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_secObj ) )
	{
		lRes = LONG_MIN;
		/* Se recorre la CADENA de elementos, no por indice: SSecElemento
		   entra por el extremo mas cercano, asi que un barrido por indice
		   seria cuadratico. Igual que en SListaEnteros. */
		p_elmObj = SSecElemento ( p_secObj->p_secDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) )
		{
			lDato = SElmEnteroLargo ( p_elmObj );
			if ( lDato > lRes )
			{
				lRes = lDato;
			}
			p_elmObj = SElmSucesor ( p_elmObj );
		}
	}
	else
	{
		ERROR_ESTABLECER ( ERR_PARAMETROS );
		lRes = 0;
	}
	return ( lRes );
}

void SSecIntlObtenerParametros ( SSecuenciaEnterosLargos * p_secObj, long * p_lMin, long * p_lMax, double * p_dMed )
{
	long		lDato;
	int			iNumElems;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_secObj ) && ES_VALIDO ( p_lMin ) && ES_VALIDO ( p_lMax ) && ES_VALIDO ( p_dMed ) )
	{
		*p_lMin = LONG_MAX;
		*p_lMax = LONG_MIN;
		*p_dMed = 0.0;
		iNumElems = SSecIntlNumElementos ( p_secObj );
		/* Se recorre la CADENA de elementos, no por indice: SSecElemento
		   entra por el extremo mas cercano, asi que un barrido por indice
		   seria cuadratico. Igual que en SListaEnteros. */
		p_elmObj = SSecElemento ( p_secObj->p_secDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) )
		{
			lDato = SElmEnteroLargo ( p_elmObj );
			if ( lDato > *p_lMax )
			{
				*p_lMax = lDato;
			}
			if ( lDato < *p_lMin )
			{
				*p_lMin = lDato;
			}
			*p_dMed = *p_dMed + (double) lDato;
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

int SSecIntlDefinidaPositiva ( SSecuenciaEnterosLargos * p_secObj )
{
	long		lDato;
	int			iRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = 1;
		/* Se recorre la CADENA de elementos, no por indice: SSecElemento
		   entra por el extremo mas cercano, asi que un barrido por indice
		   seria cuadratico. Igual que en SListaEnteros. */
		p_elmObj = SSecElemento ( p_secObj->p_secDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) && ( iRes == 1 ) )
		{
			lDato = SElmEnteroLargo ( p_elmObj );
			if ( lDato <= 0 )
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

int SSecIntlSemidefinidaPositiva ( SSecuenciaEnterosLargos * p_secObj )
{
	long		lDato;
	int			iRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = 1;
		/* Se recorre la CADENA de elementos, no por indice: SSecElemento
		   entra por el extremo mas cercano, asi que un barrido por indice
		   seria cuadratico. Igual que en SListaEnteros. */
		p_elmObj = SSecElemento ( p_secObj->p_secDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) && ( iRes == 1 ) )
		{
			lDato = SElmEnteroLargo ( p_elmObj );
			if ( lDato < 0 )
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
SSecuencia * SSecIntlSecuencia ( SSecuenciaEnterosLargos * p_secObj )
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

SLista * SSecIntlLista ( SSecuenciaEnterosLargos * p_secObj )
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
SListaEnterosLargos * SSecIntlListaIntl ( SSecuenciaEnterosLargos * p_secObj )
{
	SListaEnterosLargos *	p_lisRes;
	SLista *				p_lisDatos;

	if ( ES_VALIDO ( p_secObj ) )
	{
		p_lisDatos = SLisDuplicar ( SSecIntlLista ( p_secObj ) );
		p_lisRes = SLisIntlEncapsular ( p_lisDatos );
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
int SSecIntlExistenTodos ( SSecuenciaEnterosLargos * p_secObj, SSecuenciaEnterosLargos * p_secValores )
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

int SSecIntlExisteAlguno ( SSecuenciaEnterosLargos * p_secObj, SSecuenciaEnterosLargos * p_secValores )
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

int SSecIntlExistenTodosLista ( SSecuenciaEnterosLargos * p_secObj, SListaEnterosLargos * p_lisValores )
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

int SSecIntlExisteAlgunoLista ( SSecuenciaEnterosLargos * p_secObj, SListaEnterosLargos * p_lisValores )
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
int SSecIntlEliminarSecuencia ( SSecuenciaEnterosLargos * p_secObj, SSecuenciaEnterosLargos * p_secValores )
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

int SSecIntlEliminarLista ( SSecuenciaEnterosLargos * p_secObj, SListaEnterosLargos * p_lisValores )
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
int SSecIntlConcatenar ( SSecuenciaEnterosLargos * p_secObj, SSecuenciaEnterosLargos * p_secValores )
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

int SSecIntlConcatenarLista ( SSecuenciaEnterosLargos * p_secObj, SListaEnterosLargos * p_lisValores )
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
SSecuenciaEnterosLargos * SSecIntlExtraerSecuencia ( SSecuenciaEnterosLargos * p_secObj, SSecuenciaEnterosLargos * p_secValores )
{
	SSecuenciaEnterosLargos *	p_secRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ES_VALIDO ( p_secValores ) )
		{
			p_secRes = _SSecIntlEnvolverExtraidos ( p_secObj, SSecExtraerSecuencia ( p_secObj->p_secDatos, p_secValores->p_secDatos ) );
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

SSecuenciaEnterosLargos * SSecIntlExtraerLista ( SSecuenciaEnterosLargos * p_secObj, SListaEnterosLargos * p_lisValores )
{
	SSecuenciaEnterosLargos *	p_secRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			p_secRes = _SSecIntlEnvolverExtraidos ( p_secObj, SSecExtraerLista ( p_secObj->p_secDatos, p_lisValores->p_lisDatos ) );
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
SSecuenciaEnterosLargos * SSecIntlUnion ( SSecuenciaEnterosLargos * p_secValores1, SSecuenciaEnterosLargos * p_secValores2 )
{
	SSecuenciaEnterosLargos *	p_secRes;

	if ( ES_VALIDO ( p_secValores1 ) )
	{
		if ( ES_VALIDO ( p_secValores2 ) )
		{
			p_secRes = _SSecIntlEnvolver ( SSecUnion ( p_secValores1->p_secDatos, p_secValores2->p_secDatos ) );
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

SSecuenciaEnterosLargos * SSecIntlInterseccion ( SSecuenciaEnterosLargos * p_secValores1, SSecuenciaEnterosLargos * p_secValores2 )
{
	SSecuenciaEnterosLargos *	p_secRes;

	if ( ES_VALIDO ( p_secValores1 ) )
	{
		if ( ES_VALIDO ( p_secValores2 ) )
		{
			p_secRes = _SSecIntlEnvolver ( SSecInterseccion ( p_secValores1->p_secDatos, p_secValores2->p_secDatos ) );
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

SSecuenciaEnterosLargos * SSecIntlDiferencia ( SSecuenciaEnterosLargos * p_secValores1, SSecuenciaEnterosLargos * p_secValores2 )
{
	SSecuenciaEnterosLargos *	p_secRes;

	if ( ES_VALIDO ( p_secValores1 ) )
	{
		if ( ES_VALIDO ( p_secValores2 ) )
		{
			p_secRes = _SSecIntlEnvolver ( SSecDiferencia ( p_secValores1->p_secDatos, p_secValores2->p_secDatos ) );
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

SSecuenciaEnterosLargos * SSecIntlUnionLista ( SSecuenciaEnterosLargos * p_secValores1, SListaEnterosLargos * p_lisValores2 )
{
	SSecuenciaEnterosLargos *	p_secRes;

	if ( ES_VALIDO ( p_secValores1 ) )
	{
		if ( ES_VALIDO ( p_lisValores2 ) )
		{
			p_secRes = _SSecIntlEnvolver ( SSecUnionLista ( p_secValores1->p_secDatos, p_lisValores2->p_lisDatos ) );
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

SSecuenciaEnterosLargos * SSecIntlInterseccionLista ( SSecuenciaEnterosLargos * p_secValores1, SListaEnterosLargos * p_lisValores2 )
{
	SSecuenciaEnterosLargos *	p_secRes;

	if ( ES_VALIDO ( p_secValores1 ) )
	{
		if ( ES_VALIDO ( p_lisValores2 ) )
		{
			p_secRes = _SSecIntlEnvolver ( SSecInterseccionLista ( p_secValores1->p_secDatos, p_lisValores2->p_lisDatos ) );
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

SSecuenciaEnterosLargos * SSecIntlDiferenciaLista ( SSecuenciaEnterosLargos * p_secValores1, SListaEnterosLargos * p_lisValores2 )
{
	SSecuenciaEnterosLargos *	p_secRes;

	if ( ES_VALIDO ( p_secValores1 ) )
	{
		if ( ES_VALIDO ( p_lisValores2 ) )
		{
			p_secRes = _SSecIntlEnvolver ( SSecDiferenciaLista ( p_secValores1->p_secDatos, p_lisValores2->p_lisDatos ) );
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
static SSecuenciaEnterosLargos * _SSecIntlEnvolver ( SSecuencia * p_secDatos )
{
	SSecuenciaEnterosLargos * p_secRes;

	if ( ES_VALIDO ( p_secDatos ) )
	{
		p_secRes = (SSecuenciaEnterosLargos *) MemReservar ( sizeof ( SSecuenciaEnterosLargos ) );
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
static SSecuenciaEnterosLargos * _SSecIntlEnvolverExtraidos ( SSecuenciaEnterosLargos * p_secObj, SSecuencia * p_secExt )
{
	SSecuenciaEnterosLargos * p_secRes;

	if ( ES_VALIDO ( p_secExt ) )
	{
		p_secRes = (SSecuenciaEnterosLargos *) MemReservar ( sizeof ( SSecuenciaEnterosLargos ) );
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

