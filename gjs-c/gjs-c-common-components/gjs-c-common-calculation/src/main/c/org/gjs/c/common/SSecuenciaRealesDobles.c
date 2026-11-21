#include "SSecuenciaRealesDobles.h"

#include "CalculoConfig.h"
#include "CalculoOperaciones.h"

/* Las comparaciones con tolerancia, sobre la lista de la secuencia, son las de
   SListaRealesDobles: ver alli la igualdad entre reales. */
extern int _SLisRealdBuscarSiguiente ( SLista * p_lisDatos, double dDato, int iPos );
extern int _SLisRealdRepeticiones ( SLista * p_lisDatos, double dDato );
extern int _SLisRealdExistenTodos ( SLista * p_lisObj, SLista * p_lisValores );
extern int _SLisRealdExisteAlguno ( SLista * p_lisObj, SLista * p_lisValores );
extern int _SLisRealdEliminarLista ( SLista * p_lisObj, SLista * p_lisValores );
extern SLista * _SLisRealdExtraerLista ( SLista * p_lisObj, SLista * p_lisValores );
extern SLista * _SLisRealdInterseccion ( SLista * p_lisValores1, SLista * p_lisValores2 );
extern SLista * _SLisRealdDiferencia ( SLista * p_lisValores1, SLista * p_lisValores2 );

static SSecuenciaRealesDobles * _SSecRealdEnvolver ( SSecuencia * p_secDatos );
static SSecuenciaRealesDobles * _SSecRealdEnvolverLista ( SLista * p_lisDatos );
static SSecuenciaRealesDobles * _SSecRealdEnvolverExtraidos ( SSecuenciaRealesDobles * p_secObj, SLista * p_lisExt );




SSecuenciaRealesDobles * SSecRealdCrear ()
{
	SSecuenciaRealesDobles * p_secObj;
	
	p_secObj = (SSecuenciaRealesDobles *) MemReservar ( sizeof ( SSecuenciaRealesDobles ) );
	if ( ES_VALIDO ( p_secObj ) )
	{
		p_secObj->p_secDatos = SSecCrear ();
	}
	return ( p_secObj );
}

/* Secuencia con COPIAS de los valores de la lista, que no se toca. */
SSecuenciaRealesDobles * SSecRealdCrearDesdeLista ( SListaRealesDobles * p_lisValores )
{
	SSecuenciaRealesDobles * p_secRes;

	if ( ES_VALIDO ( p_lisValores ) )
	{
		p_secRes = _SSecRealdEnvolver ( SSecCrearDesdeLista ( p_lisValores->p_lisDatos ) );
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

/* Secuencia con los iNumValores primeros de p_dValores, en orden. Con 0
   valores da una secuencia vacia; NULL si el vector es nulo, el numero es
   negativo o falla alguna insercion. */
SSecuenciaRealesDobles * SSecRealdCrearDesdeVector ( const double * p_dValores, int iNumValores )
{
	SSecuenciaRealesDobles *	p_secRes;
	int							iPos;
	int							iError;

	if ( ES_VALIDO ( p_dValores ) )
	{
		if ( iNumValores >= 0 )
		{
			p_secRes = SSecRealdCrear ();
			if ( ES_VALIDO ( p_secRes ) )
			{
				iError = 0;
				iPos = 0;
				while ( ( iError == 0 ) && ( iPos < iNumValores ) )
				{
					if ( SSecRealdInsertar ( p_secRes, p_dValores [ iPos ] ) == 1 )
					{
						iPos = iPos + 1;
					}
					else
					{
						iError = 1;
					}
				}
				if ( iError == 1 )
				{
					SSecRealdDestruir ( &p_secRes );
				}
			}
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

void SSecRealdDestruir ( SSecuenciaRealesDobles ** p_p_secObj )
{
	SSecuenciaRealesDobles * p_secObj;
	
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

int SSecRealdEsValida ( SSecuenciaRealesDobles * p_secObj )
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

int SSecRealdEstaVacia ( SSecuenciaRealesDobles * p_secObj )
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

int SSecRealdNumElementos ( SSecuenciaRealesDobles * p_secObj )
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

double SSecRealdElemento ( SSecuenciaRealesDobles * p_secObj, int iElem )
{
	double		dRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_secObj ) )
	{
		p_elmObj = SSecElemento ( p_secObj->p_secDatos, iElem );
		if ( ES_VALIDO ( p_elmObj ) )
		{
			dRes = SElmRealDoble ( p_elmObj );
		}
		else
		{
			dRes = 0;
		}
	}
	else
	{
		dRes = 0;
	}
	return ( dRes );
}

int SSecRealdInsertar ( SSecuenciaRealesDobles * p_secObj, double dDato )
{
	int			iRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_secObj ) )
	{
		p_elmObj = SElmCrearRealDoble ();
		if ( ES_VALIDO ( p_elmObj ) )
		{
			if ( SElmEscribirRealDoble ( p_elmObj, dDato ) == 1 )
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

int SSecRealdModificar ( SSecuenciaRealesDobles * p_secObj, int iElem, double dDato )
{
	int			iRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_secObj ) )
	{
		p_elmObj = SSecElemento ( p_secObj->p_secDatos, iElem );
		if ( ES_VALIDO ( p_elmObj ) )
		{
			iRes = SElmEscribirRealDoble ( p_elmObj, dDato );
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

int SSecRealdEliminar ( SSecuenciaRealesDobles * p_secObj, int iElem )
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

int SSecRealdVaciar ( SSecuenciaRealesDobles * p_secObj )
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

/* Igualdad con tolerancia, como en SListaRealesDobles. Se recorre la CADENA
   de elementos, no por indice: SSecElemento entra por el extremo mas cercano,
   asi que un barrido por indice seria cuadratico. */
int SSecRealdExiste ( SSecuenciaRealesDobles * p_secObj, double dDato )
{
	int iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( _SLisRealdBuscarSiguiente ( SSecLista ( p_secObj->p_secDatos ), dDato, -1 ) >= 0 )
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

/* Repeticiones: cuantos iguales hay, 0 si ninguno. Buscar es BuscarPrimero:
   la posicion del primero igual, o -1. BuscarSiguiente busca DETRAS de iPos:
   con -1, desde el principio. */
int SSecRealdRepeticiones ( SSecuenciaRealesDobles * p_secObj, double dDato )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = _SLisRealdRepeticiones ( SSecLista ( p_secObj->p_secDatos ), dDato );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecRealdBuscar ( SSecuenciaRealesDobles * p_secObj, double dDato )
{
	return ( SSecRealdBuscarPrimero ( p_secObj, dDato ) );
}

int SSecRealdBuscarPrimero ( SSecuenciaRealesDobles * p_secObj, double dDato )
{
	return ( SSecRealdBuscarSiguiente ( p_secObj, dDato, -1 ) );
}

int SSecRealdBuscarSiguiente ( SSecuenciaRealesDobles * p_secObj, double dDato, int iPos )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = _SLisRealdBuscarSiguiente ( SSecLista ( p_secObj->p_secDatos ), dDato, iPos );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

/* Secuencia nueva con un valor por cada grupo de iguales: el primero que
   aparece. */
SSecuenciaRealesDobles * SSecRealdExtraerUnicos ( SSecuenciaRealesDobles * p_secObj )
{
	int							iError;
	double						dDato;
	SSecuenciaRealesDobles *	p_secRes;
	SElemento *					p_elmObj;

	if ( ES_VALIDO ( p_secObj ) )
	{
		p_secRes = SSecRealdCrear ();
		iError = MemEsInvalida ( p_secRes );
		p_elmObj = SSecElemento ( p_secObj->p_secDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) && ( iError == 0 ) )
		{
			dDato = SElmRealDoble ( p_elmObj );
			if ( SSecRealdExiste ( p_secRes, dDato ) == 0 )
			{
				if ( SSecRealdInsertar ( p_secRes, dDato ) != 1 )
				{
					iError = 1;
				}
			}
			p_elmObj = SElmSucesor ( p_elmObj );
		}
		if ( iError == 1 )
		{
			SSecRealdDestruir ( &p_secRes );
			ERROR_ESTABLECER ( ERR_GENERAL_OPERATIVO );
		}
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

int SSecRealdTieneRepetidos ( SSecuenciaRealesDobles * p_secObj )
{
	int							iRes;
	int							iError;
	double						dDato;
	SSecuenciaRealesDobles *	p_secDistintos;
	SElemento *					p_elmObj;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = 0;
		p_secDistintos = SSecRealdCrear ();
		iError = MemEsInvalida ( p_secDistintos );
		p_elmObj = SSecElemento ( p_secObj->p_secDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) && ( iError == 0 ) && ( iRes == 0 ) )
		{
			dDato = SElmRealDoble ( p_elmObj );
			if ( SSecRealdExiste ( p_secDistintos, dDato ) == 1 )
			{
				iRes = 1;
			}
			else
			{
				if ( SSecRealdInsertar ( p_secDistintos, dDato ) != 1 )
				{
					iError = 1;
				}
			}
			p_elmObj = SElmSucesor ( p_elmObj );
		}
		SSecRealdDestruir ( &p_secDistintos );
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

/* Con la secuencia vacia, Min da DBL_MAX y Max -DBL_MAX, como en
   SListaRealesDobles. */
double SSecRealdMin ( SSecuenciaRealesDobles * p_secObj )
{
	double		dDato;
	double		dRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_secObj ) )
	{
		dRes = DBL_MAX;
		p_elmObj = SSecElemento ( p_secObj->p_secDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) )
		{
			dDato = SElmRealDoble ( p_elmObj );
			if ( dDato < dRes )
			{
				dRes = dDato;
			}
			p_elmObj = SElmSucesor ( p_elmObj );
		}
	}
	else
	{
		ERROR_ESTABLECER ( ERR_PARAMETROS );
		dRes = 0.0;
	}
	return ( dRes );
}

double SSecRealdMax ( SSecuenciaRealesDobles * p_secObj )
{
	double		dDato;
	double		dRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_secObj ) )
	{
		dRes = -DBL_MAX;
		p_elmObj = SSecElemento ( p_secObj->p_secDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) )
		{
			dDato = SElmRealDoble ( p_elmObj );
			if ( dDato > dRes )
			{
				dRes = dDato;
			}
			p_elmObj = SElmSucesor ( p_elmObj );
		}
	}
	else
	{
		ERROR_ESTABLECER ( ERR_PARAMETROS );
		dRes = 0.0;
	}
	return ( dRes );
}

void SSecRealdObtenerParametros ( SSecuenciaRealesDobles * p_secObj, double * p_dMin, double * p_dMax, double * p_dMed )
{
	double		dDato;
	int			iNumElems;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ES_VALIDO ( p_dMin ) )
		{
			if ( ES_VALIDO ( p_dMax ) )
			{
				if ( ES_VALIDO ( p_dMed ) )
				{
					*p_dMin = DBL_MAX;
					*p_dMax = -DBL_MAX;
					*p_dMed = 0.0;
					iNumElems = SSecRealdNumElementos ( p_secObj );
					p_elmObj = SSecElemento ( p_secObj->p_secDatos, 0 );
					while ( ES_VALIDO ( p_elmObj ) )
					{
						dDato = SElmRealDoble ( p_elmObj );
						if ( dDato > *p_dMax )
						{
							*p_dMax = dDato;
						}
						if ( dDato < *p_dMin )
						{
							*p_dMin = dDato;
						}
						*p_dMed = *p_dMed + dDato;
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
			else
			{
				ERROR_ESTABLECER ( ERR_PARAMETROS );
			}
		}
		else
		{
			ERROR_ESTABLECER ( ERR_PARAMETROS );
		}
	}
	else
	{
		ERROR_ESTABLECER ( ERR_PARAMETROS );
	}
}

/* Con tolerancia, como en SListaRealesDobles: un valor casi cero cuenta como
   cero. */
int SSecRealdDefinidaPositiva ( SSecuenciaRealesDobles * p_secObj )
{
	int			iRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = 1;
		p_elmObj = SSecElemento ( p_secObj->p_secDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) && ( iRes == 1 ) )
		{
			if ( MatEsMayor ( SElmRealDoble ( p_elmObj ), 0.0 ) == 0 )
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

int SSecRealdSemidefinidaPositiva ( SSecuenciaRealesDobles * p_secObj )
{
	int			iRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = 1;
		p_elmObj = SSecElemento ( p_secObj->p_secDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) && ( iRes == 1 ) )
		{
			if ( MatEsMenor ( SElmRealDoble ( p_elmObj ), 0.0 ) == 1 )
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
SSecuencia * SSecRealdSecuencia ( SSecuenciaRealesDobles * p_secObj )
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

SLista * SSecRealdLista ( SSecuenciaRealesDobles * p_secObj )
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
SListaRealesDobles * SSecRealdListaReald ( SSecuenciaRealesDobles * p_secObj )
{
	SListaRealesDobles *	p_lisRes;
	SLista *				p_lisDatos;

	if ( ES_VALIDO ( p_secObj ) )
	{
		p_lisDatos = SLisDuplicar ( SSecRealdLista ( p_secObj ) );
		p_lisRes = SLisRealdEncapsular ( p_lisDatos );
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

/* Operaciones con otras secuencias y listas. Las que comparan valores van
   por las de SListaRealesDobles, con tolerancia, sobre la lista de cada
   secuencia; las que solo copian, Union incluida, delegan en las de
   SSecuencia. */
int SSecRealdExistenTodos ( SSecuenciaRealesDobles * p_secObj, SSecuenciaRealesDobles * p_secValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ES_VALIDO ( p_secValores ) )
		{
			iRes = _SLisRealdExistenTodos ( SSecLista ( p_secObj->p_secDatos ), SSecLista ( p_secValores->p_secDatos ) );
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

int SSecRealdExisteAlguno ( SSecuenciaRealesDobles * p_secObj, SSecuenciaRealesDobles * p_secValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ES_VALIDO ( p_secValores ) )
		{
			iRes = _SLisRealdExisteAlguno ( SSecLista ( p_secObj->p_secDatos ), SSecLista ( p_secValores->p_secDatos ) );
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

int SSecRealdExistenTodosLista ( SSecuenciaRealesDobles * p_secObj, SListaRealesDobles * p_lisValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			iRes = _SLisRealdExistenTodos ( SSecLista ( p_secObj->p_secDatos ), p_lisValores->p_lisDatos );
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

int SSecRealdExisteAlgunoLista ( SSecuenciaRealesDobles * p_secObj, SListaRealesDobles * p_lisValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			iRes = _SLisRealdExisteAlguno ( SSecLista ( p_secObj->p_secDatos ), p_lisValores->p_lisDatos );
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
int SSecRealdEliminarSecuencia ( SSecuenciaRealesDobles * p_secObj, SSecuenciaRealesDobles * p_secValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ES_VALIDO ( p_secValores ) )
		{
			iRes = _SLisRealdEliminarLista ( SSecLista ( p_secObj->p_secDatos ), SSecLista ( p_secValores->p_secDatos ) );
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

int SSecRealdEliminarLista ( SSecuenciaRealesDobles * p_secObj, SListaRealesDobles * p_lisValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			iRes = _SLisRealdEliminarLista ( SSecLista ( p_secObj->p_secDatos ), p_lisValores->p_lisDatos );
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
int SSecRealdConcatenar ( SSecuenciaRealesDobles * p_secObj, SSecuenciaRealesDobles * p_secValores )
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

int SSecRealdConcatenarLista ( SSecuenciaRealesDobles * p_secObj, SListaRealesDobles * p_lisValores )
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
SSecuenciaRealesDobles * SSecRealdExtraerSecuencia ( SSecuenciaRealesDobles * p_secObj, SSecuenciaRealesDobles * p_secValores )
{
	SSecuenciaRealesDobles *	p_secRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ES_VALIDO ( p_secValores ) )
		{
			p_secRes = _SSecRealdEnvolverExtraidos ( p_secObj, _SLisRealdExtraerLista ( SSecLista ( p_secObj->p_secDatos ), SSecLista ( p_secValores->p_secDatos ) ) );
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

SSecuenciaRealesDobles * SSecRealdExtraerLista ( SSecuenciaRealesDobles * p_secObj, SListaRealesDobles * p_lisValores )
{
	SSecuenciaRealesDobles *	p_secRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			p_secRes = _SSecRealdEnvolverExtraidos ( p_secObj, _SLisRealdExtraerLista ( SSecLista ( p_secObj->p_secDatos ), p_lisValores->p_lisDatos ) );
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
SSecuenciaRealesDobles * SSecRealdUnion ( SSecuenciaRealesDobles * p_secValores1, SSecuenciaRealesDobles * p_secValores2 )
{
	SSecuenciaRealesDobles *	p_secRes;

	if ( ES_VALIDO ( p_secValores1 ) )
	{
		if ( ES_VALIDO ( p_secValores2 ) )
		{
			p_secRes = _SSecRealdEnvolver ( SSecUnion ( p_secValores1->p_secDatos, p_secValores2->p_secDatos ) );
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

SSecuenciaRealesDobles * SSecRealdInterseccion ( SSecuenciaRealesDobles * p_secValores1, SSecuenciaRealesDobles * p_secValores2 )
{
	SSecuenciaRealesDobles *	p_secRes;

	if ( ES_VALIDO ( p_secValores1 ) )
	{
		if ( ES_VALIDO ( p_secValores2 ) )
		{
			p_secRes = _SSecRealdEnvolverLista ( _SLisRealdInterseccion ( SSecLista ( p_secValores1->p_secDatos ), SSecLista ( p_secValores2->p_secDatos ) ) );
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

SSecuenciaRealesDobles * SSecRealdDiferencia ( SSecuenciaRealesDobles * p_secValores1, SSecuenciaRealesDobles * p_secValores2 )
{
	SSecuenciaRealesDobles *	p_secRes;

	if ( ES_VALIDO ( p_secValores1 ) )
	{
		if ( ES_VALIDO ( p_secValores2 ) )
		{
			p_secRes = _SSecRealdEnvolverLista ( _SLisRealdDiferencia ( SSecLista ( p_secValores1->p_secDatos ), SSecLista ( p_secValores2->p_secDatos ) ) );
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

SSecuenciaRealesDobles * SSecRealdUnionLista ( SSecuenciaRealesDobles * p_secValores1, SListaRealesDobles * p_lisValores2 )
{
	SSecuenciaRealesDobles *	p_secRes;

	if ( ES_VALIDO ( p_secValores1 ) )
	{
		if ( ES_VALIDO ( p_lisValores2 ) )
		{
			p_secRes = _SSecRealdEnvolver ( SSecUnionLista ( p_secValores1->p_secDatos, p_lisValores2->p_lisDatos ) );
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

SSecuenciaRealesDobles * SSecRealdInterseccionLista ( SSecuenciaRealesDobles * p_secValores1, SListaRealesDobles * p_lisValores2 )
{
	SSecuenciaRealesDobles *	p_secRes;

	if ( ES_VALIDO ( p_secValores1 ) )
	{
		if ( ES_VALIDO ( p_lisValores2 ) )
		{
			p_secRes = _SSecRealdEnvolverLista ( _SLisRealdInterseccion ( SSecLista ( p_secValores1->p_secDatos ), p_lisValores2->p_lisDatos ) );
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

SSecuenciaRealesDobles * SSecRealdDiferenciaLista ( SSecuenciaRealesDobles * p_secValores1, SListaRealesDobles * p_lisValores2 )
{
	SSecuenciaRealesDobles *	p_secRes;

	if ( ES_VALIDO ( p_secValores1 ) )
	{
		if ( ES_VALIDO ( p_lisValores2 ) )
		{
			p_secRes = _SSecRealdEnvolverLista ( _SLisRealdDiferencia ( SSecLista ( p_secValores1->p_secDatos ), p_lisValores2->p_lisDatos ) );
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
static SSecuenciaRealesDobles * _SSecRealdEnvolver ( SSecuencia * p_secDatos )
{
	SSecuenciaRealesDobles * p_secRes;

	if ( ES_VALIDO ( p_secDatos ) )
	{
		p_secRes = (SSecuenciaRealesDobles *) MemReservar ( sizeof ( SSecuenciaRealesDobles ) );
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

/* Envuelve una lista nueva, de COPIAS, en una secuencia; si no hay o no se
   puede, NULL y la lista se destruye. */
static SSecuenciaRealesDobles * _SSecRealdEnvolverLista ( SLista * p_lisDatos )
{
	SSecuenciaRealesDobles *	p_secRes;
	SSecuencia *				p_secDatos;

	if ( ES_VALIDO ( p_lisDatos ) )
	{
		p_secDatos = SSecEncapsularLista ( p_lisDatos );
		if ( ES_VALIDO ( p_secDatos ) )
		{
			p_secRes = _SSecRealdEnvolver ( p_secDatos );
		}
		else
		{
			SLisDestruir ( &p_lisDatos );
			p_secRes = NULL;
		}
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

/* Envuelve lo que haya sacado _SLisRealdExtraerLista de la lista de p_secObj.
   Si no se puede, los valores vuelven al final de p_secObj: no se pierden. */
static SSecuenciaRealesDobles * _SSecRealdEnvolverExtraidos ( SSecuenciaRealesDobles * p_secObj, SLista * p_lisExt )
{
	SSecuenciaRealesDobles *	p_secRes;
	SSecuencia *				p_secExt;

	if ( ES_VALIDO ( p_lisExt ) )
	{
		p_secExt = SSecEncapsularLista ( p_lisExt );
		if ( ES_VALIDO ( p_secExt ) )
		{
			p_secRes = (SSecuenciaRealesDobles *) MemReservar ( sizeof ( SSecuenciaRealesDobles ) );
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
			SLisConcatenarLista ( SSecLista ( p_secObj->p_secDatos ), p_lisExt );
			SLisDestruir ( &p_lisExt );
			p_secRes = NULL;
		}
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

