#include "SSecuenciaEnteros.h"

#include "TiposBasicosConfig.h"


extern int _SLisIntBuscarSiguiente ( SLista * p_lisDatos, int iDato, int iPos );
extern int _SLisIntRepeticiones ( SLista * p_lisDatos, int iDato );

static SSecuenciaEnteros * _SSecIntEnvolver ( SSecuencia * p_secDatos );
static SSecuenciaEnteros * _SSecIntEnvolverExtraidos ( SSecuenciaEnteros * p_secObj, SSecuencia * p_secExt );




SSecuenciaEnteros * SSecIntCrear ()
{
	SSecuenciaEnteros * p_secObj;
	
	p_secObj = (SSecuenciaEnteros *) MemReservar ( sizeof ( SSecuenciaEnteros ) );
	if ( ES_VALIDO ( p_secObj ) )
	{
		p_secObj->p_secDatos = SSecCrear ();
	}
	return ( p_secObj );
}

/* Secuencia con COPIAS de los valores de la lista, que no se toca. */
SSecuenciaEnteros * SSecIntCrearDesdeLista ( SListaEnteros * p_lisValores )
{
	SSecuenciaEnteros * p_secRes;

	if ( ES_VALIDO ( p_lisValores ) )
	{
		p_secRes = _SSecIntEnvolver ( SSecCrearDesdeLista ( p_lisValores->p_lisDatos ) );
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

void SSecIntDestruir ( SSecuenciaEnteros ** p_p_secObj )
{
	SSecuenciaEnteros * p_secObj;
	
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

int SSecIntEsValida ( SSecuenciaEnteros * p_secObj )
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

int SSecIntEstaVacia ( SSecuenciaEnteros * p_secObj )
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

int SSecIntNumElementos ( SSecuenciaEnteros * p_secObj )
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

int SSecIntElemento ( SSecuenciaEnteros * p_secObj, int iElem )
{
	int			iRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_secObj ) )
	{
		p_elmObj = SSecElemento ( p_secObj->p_secDatos, iElem );
		if ( ES_VALIDO ( p_elmObj ) )
		{
			iRes = SElmEntero ( p_elmObj );
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

int SSecIntInsertar ( SSecuenciaEnteros * p_secObj, int iDato )
{
	int			iRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_secObj ) )
	{
		p_elmObj = SElmCrearEntero ();
		if ( ES_VALIDO ( p_elmObj ) )
		{
			if ( SElmEscribirEntero ( p_elmObj, iDato ) == 1 )
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

int SSecIntModificar ( SSecuenciaEnteros * p_secObj, int iElem, int iDato )
{
	int			iRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_secObj ) )
	{
		p_elmObj = SSecElemento ( p_secObj->p_secDatos, iElem );
		if ( ES_VALIDO ( p_elmObj ) )
		{
			iRes = SElmEscribirEntero ( p_elmObj, iDato );
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

int SSecIntEliminar ( SSecuenciaEnteros * p_secObj, int iElem )
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

int SSecIntVaciar ( SSecuenciaEnteros * p_secObj )
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

int SSecIntExiste ( SSecuenciaEnteros * p_secObj, int iDato )
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
			if ( SElmEntero ( p_elmObj ) == iDato )
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

/* Busquedas por la cadena, compartidas con SListaEnteros. Repeticiones:
   cuantos iguales hay, 0 si ninguno. Buscar es BuscarPrimero: la posicion del
   primero igual, o -1. BuscarSiguiente busca DETRAS de iPos: con -1, desde el
   principio. */
int SSecIntRepeticiones ( SSecuenciaEnteros * p_secObj, int iDato )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = _SLisIntRepeticiones ( SSecLista ( p_secObj->p_secDatos ), iDato );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecIntBuscar ( SSecuenciaEnteros * p_secObj, int iDato )
{
	return ( SSecIntBuscarPrimero ( p_secObj, iDato ) );
}

int SSecIntBuscarPrimero ( SSecuenciaEnteros * p_secObj, int iDato )
{
	return ( SSecIntBuscarSiguiente ( p_secObj, iDato, -1 ) );
}

int SSecIntBuscarSiguiente ( SSecuenciaEnteros * p_secObj, int iDato, int iPos )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = _SLisIntBuscarSiguiente ( SSecLista ( p_secObj->p_secDatos ), iDato, iPos );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

SSecuenciaEnteros * SSecIntExtraerUnicos ( SSecuenciaEnteros * p_secObj )
{
	int					iError;
	int					iDato;
	SSecuenciaEnteros *	p_secRes;
	SElemento *			p_elmObj;

	if ( ES_VALIDO ( p_secObj ) )
	{
		p_secRes = SSecIntCrear ();
		iError = MemEsInvalida ( p_secRes );
		/* Se recorre la CADENA de elementos, no por indice: SSecElemento
		   entra por el extremo mas cercano, asi que un barrido por indice
		   seria cuadratico. Igual que en SListaEnteros. */
		p_elmObj = SSecElemento ( p_secObj->p_secDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) && ( iError == 0 ) )
		{
			iDato = SElmEntero ( p_elmObj );
			if ( SSecIntExiste ( p_secRes, iDato ) == 0 )
			{
				if ( SSecIntInsertar ( p_secRes, iDato ) != 1 )
				{
					iError = 1;
				}
			}
			p_elmObj = SElmSucesor ( p_elmObj );
		}
		if ( iError == 1 )
		{
			SSecIntDestruir ( &p_secRes );
			ERROR_ESTABLECER ( ERR_GENERAL_OPERATIVO );
		}
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

int SSecIntTieneRepetidos ( SSecuenciaEnteros * p_secObj )
{
	int					iRes;
	int					iError;
	int					iDato;
	SSecuenciaEnteros *	p_secDistintos;
	SElemento *			p_elmObj;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = 0;
		p_secDistintos = SSecIntCrear ();
		iError = MemEsInvalida ( p_secDistintos );
		/* Se recorre la CADENA de elementos, no por indice: SSecElemento
		   entra por el extremo mas cercano, asi que un barrido por indice
		   seria cuadratico. Igual que en SListaEnteros. */
		p_elmObj = SSecElemento ( p_secObj->p_secDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) && ( iError == 0 ) && ( iRes == 0 ) )
		{
			iDato = SElmEntero ( p_elmObj );
			if ( SSecIntExiste ( p_secDistintos, iDato ) == 1 )
			{
				iRes = 1;
			}
			else
			{
				if ( SSecIntInsertar ( p_secDistintos, iDato ) != 1 )
				{
					iError = 1;
				}
			}
			p_elmObj = SElmSucesor ( p_elmObj );
		}
		SSecIntDestruir ( &p_secDistintos );
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

int SSecIntMin ( SSecuenciaEnteros * p_secObj )
{
	int			iDato;
	int			iRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = INT_MAX;
		/* Se recorre la CADENA de elementos, no por indice: SSecElemento
		   entra por el extremo mas cercano, asi que un barrido por indice
		   seria cuadratico. Igual que en SListaEnteros. */
		p_elmObj = SSecElemento ( p_secObj->p_secDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) )
		{
			iDato = SElmEntero ( p_elmObj );
			if ( iDato < iRes )
			{
				iRes = iDato;
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

int SSecIntMax ( SSecuenciaEnteros * p_secObj )
{
	int			iDato;
	int			iRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = INT_MIN;
		/* Se recorre la CADENA de elementos, no por indice: SSecElemento
		   entra por el extremo mas cercano, asi que un barrido por indice
		   seria cuadratico. Igual que en SListaEnteros. */
		p_elmObj = SSecElemento ( p_secObj->p_secDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) )
		{
			iDato = SElmEntero ( p_elmObj );
			if ( iDato > iRes )
			{
				iRes = iDato;
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

void SSecIntObtenerParametros ( SSecuenciaEnteros * p_secObj, int * p_iMin, int * p_iMax, double * p_dMed )
{
	int			iDato;
	int			iNumElems;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_secObj ) && ES_VALIDO ( p_iMin ) && ES_VALIDO ( p_iMax ) && ES_VALIDO ( p_dMed ) )
	{
		*p_iMin = INT_MAX;
		*p_iMax = INT_MIN;
		*p_dMed = 0.0;
		iNumElems = SSecIntNumElementos ( p_secObj );
		/* Se recorre la CADENA de elementos, no por indice: SSecElemento
		   entra por el extremo mas cercano, asi que un barrido por indice
		   seria cuadratico. Igual que en SListaEnteros. */
		p_elmObj = SSecElemento ( p_secObj->p_secDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) )
		{
			iDato = SElmEntero ( p_elmObj );
			if ( iDato > *p_iMax )
			{
				*p_iMax = iDato;
			}
			if ( iDato < *p_iMin )
			{
				*p_iMin = iDato;
			}
			*p_dMed = *p_dMed + (double) iDato;
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

int SSecIntDefinidaPositiva ( SSecuenciaEnteros * p_secObj )
{
	int			iDato;
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
			iDato = SElmEntero ( p_elmObj );
			if ( iDato <= 0 )
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

int SSecIntSemidefinidaPositiva ( SSecuenciaEnteros * p_secObj )
{
	int			iDato;
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
			iDato = SElmEntero ( p_elmObj );
			if ( iDato < 0 )
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
SSecuencia * SSecIntSecuencia ( SSecuenciaEnteros * p_secObj )
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

SLista * SSecIntLista ( SSecuenciaEnteros * p_secObj )
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
SListaEnteros * SSecIntListaInt ( SSecuenciaEnteros * p_secObj )
{
	SListaEnteros *	p_lisRes;
	SLista *		p_lisDatos;

	if ( ES_VALIDO ( p_secObj ) )
	{
		p_lisDatos = SLisDuplicar ( SSecIntLista ( p_secObj ) );
		p_lisRes = SLisIntEncapsular ( p_lisDatos );
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
int SSecIntExistenTodos ( SSecuenciaEnteros * p_secObj, SSecuenciaEnteros * p_secValores )
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

int SSecIntExisteAlguno ( SSecuenciaEnteros * p_secObj, SSecuenciaEnteros * p_secValores )
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

int SSecIntExistenTodosLista ( SSecuenciaEnteros * p_secObj, SListaEnteros * p_lisValores )
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

int SSecIntExisteAlgunoLista ( SSecuenciaEnteros * p_secObj, SListaEnteros * p_lisValores )
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
int SSecIntEliminarSecuencia ( SSecuenciaEnteros * p_secObj, SSecuenciaEnteros * p_secValores )
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

int SSecIntEliminarLista ( SSecuenciaEnteros * p_secObj, SListaEnteros * p_lisValores )
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
int SSecIntConcatenar ( SSecuenciaEnteros * p_secObj, SSecuenciaEnteros * p_secValores )
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

int SSecIntConcatenarLista ( SSecuenciaEnteros * p_secObj, SListaEnteros * p_lisValores )
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
SSecuenciaEnteros * SSecIntExtraerSecuencia ( SSecuenciaEnteros * p_secObj, SSecuenciaEnteros * p_secValores )
{
	SSecuenciaEnteros *	p_secRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ES_VALIDO ( p_secValores ) )
		{
			p_secRes = _SSecIntEnvolverExtraidos ( p_secObj, SSecExtraerSecuencia ( p_secObj->p_secDatos, p_secValores->p_secDatos ) );
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

SSecuenciaEnteros * SSecIntExtraerLista ( SSecuenciaEnteros * p_secObj, SListaEnteros * p_lisValores )
{
	SSecuenciaEnteros *	p_secRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			p_secRes = _SSecIntEnvolverExtraidos ( p_secObj, SSecExtraerLista ( p_secObj->p_secDatos, p_lisValores->p_lisDatos ) );
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
SSecuenciaEnteros * SSecIntUnion ( SSecuenciaEnteros * p_secValores1, SSecuenciaEnteros * p_secValores2 )
{
	SSecuenciaEnteros *	p_secRes;

	if ( ES_VALIDO ( p_secValores1 ) )
	{
		if ( ES_VALIDO ( p_secValores2 ) )
		{
			p_secRes = _SSecIntEnvolver ( SSecUnion ( p_secValores1->p_secDatos, p_secValores2->p_secDatos ) );
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

SSecuenciaEnteros * SSecIntInterseccion ( SSecuenciaEnteros * p_secValores1, SSecuenciaEnteros * p_secValores2 )
{
	SSecuenciaEnteros *	p_secRes;

	if ( ES_VALIDO ( p_secValores1 ) )
	{
		if ( ES_VALIDO ( p_secValores2 ) )
		{
			p_secRes = _SSecIntEnvolver ( SSecInterseccion ( p_secValores1->p_secDatos, p_secValores2->p_secDatos ) );
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

SSecuenciaEnteros * SSecIntDiferencia ( SSecuenciaEnteros * p_secValores1, SSecuenciaEnteros * p_secValores2 )
{
	SSecuenciaEnteros *	p_secRes;

	if ( ES_VALIDO ( p_secValores1 ) )
	{
		if ( ES_VALIDO ( p_secValores2 ) )
		{
			p_secRes = _SSecIntEnvolver ( SSecDiferencia ( p_secValores1->p_secDatos, p_secValores2->p_secDatos ) );
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

SSecuenciaEnteros * SSecIntUnionLista ( SSecuenciaEnteros * p_secValores1, SListaEnteros * p_lisValores2 )
{
	SSecuenciaEnteros *	p_secRes;

	if ( ES_VALIDO ( p_secValores1 ) )
	{
		if ( ES_VALIDO ( p_lisValores2 ) )
		{
			p_secRes = _SSecIntEnvolver ( SSecUnionLista ( p_secValores1->p_secDatos, p_lisValores2->p_lisDatos ) );
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

SSecuenciaEnteros * SSecIntInterseccionLista ( SSecuenciaEnteros * p_secValores1, SListaEnteros * p_lisValores2 )
{
	SSecuenciaEnteros *	p_secRes;

	if ( ES_VALIDO ( p_secValores1 ) )
	{
		if ( ES_VALIDO ( p_lisValores2 ) )
		{
			p_secRes = _SSecIntEnvolver ( SSecInterseccionLista ( p_secValores1->p_secDatos, p_lisValores2->p_lisDatos ) );
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

SSecuenciaEnteros * SSecIntDiferenciaLista ( SSecuenciaEnteros * p_secValores1, SListaEnteros * p_lisValores2 )
{
	SSecuenciaEnteros *	p_secRes;

	if ( ES_VALIDO ( p_secValores1 ) )
	{
		if ( ES_VALIDO ( p_lisValores2 ) )
		{
			p_secRes = _SSecIntEnvolver ( SSecDiferenciaLista ( p_secValores1->p_secDatos, p_lisValores2->p_lisDatos ) );
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
static SSecuenciaEnteros * _SSecIntEnvolver ( SSecuencia * p_secDatos )
{
	SSecuenciaEnteros * p_secRes;

	if ( ES_VALIDO ( p_secDatos ) )
	{
		p_secRes = (SSecuenciaEnteros *) MemReservar ( sizeof ( SSecuenciaEnteros ) );
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
static SSecuenciaEnteros * _SSecIntEnvolverExtraidos ( SSecuenciaEnteros * p_secObj, SSecuencia * p_secExt )
{
	SSecuenciaEnteros * p_secRes;

	if ( ES_VALIDO ( p_secExt ) )
	{
		p_secRes = (SSecuenciaEnteros *) MemReservar ( sizeof ( SSecuenciaEnteros ) );
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

