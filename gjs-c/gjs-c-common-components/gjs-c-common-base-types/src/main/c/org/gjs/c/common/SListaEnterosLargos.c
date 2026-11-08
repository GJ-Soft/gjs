#include "SListaEnterosLargos.h"

#include "TiposBasicosConfig.h"


static SListaEnterosLargos * _SLisIntlEnvolver ( SLista * p_lisDatos );




SListaEnterosLargos * SLisIntlCrear ()
{
	SListaEnterosLargos * p_lisObj;
	
	p_lisObj = (SListaEnterosLargos *) MemReservar ( sizeof ( SListaEnterosLargos ) );
	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_lisObj->p_lisDatos = SLisCrear ();
	}
	return ( p_lisObj );
}

void SLisIntlDestruir ( SListaEnterosLargos ** p_p_lisObj )
{
	SListaEnterosLargos * p_lisObj;
	
	if ( ES_VALIDO ( p_p_lisObj ) )
	{
		p_lisObj = *p_p_lisObj;

		if ( ES_VALIDO ( p_lisObj ) )
		{
			SLisDestruir ( &(p_lisObj->p_lisDatos) );
			MemLiberar ( (void **) p_p_lisObj );
		}
	}
}

int SLisIntlEsValida ( SListaEnterosLargos * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLisEsValida ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisIntlEstaVacia ( SListaEnterosLargos * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLisEstaVacia ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisIntlNumElementos ( SListaEnterosLargos * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLisNumElementos ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

long SLisIntlElemento ( SListaEnterosLargos * p_lisObj, int iElem )
{
	long		lRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_elmObj = SLisElemento ( p_lisObj->p_lisDatos, iElem );
		if ( ES_VALIDO ( p_elmObj ) )
		{
			lRes = SElmEnteroLargo ( p_elmObj );
		}
		else
		{
			lRes = -1;
		}
	}
	else
	{
		lRes = -1;
	}
	return ( lRes );
}

int SLisIntlEstablecerElem ( SListaEnterosLargos * p_lisObj, int iPos, long lDato )
{
	int			iRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_elmObj = SLisElemento ( p_lisObj->p_lisDatos, iPos );
		if ( ES_VALIDO ( p_elmObj ) )
		{
			iRes = SElmEscribirEnteroLargo ( p_elmObj, lDato );
		}
		else
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

int SLisIntlInsertarElem ( SListaEnterosLargos * p_lisObj, int iPosAnt, long lDato )
{
	int			iRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_elmObj = SElmCrearEnteroLargo ();
		if ( ES_VALIDO ( p_elmObj ) )
		{
			if ( SElmEscribirEnteroLargo ( p_elmObj, lDato ) == 1 )
			{
				iRes = SLisInsertarElem ( p_lisObj->p_lisDatos, iPosAnt, p_elmObj );
			}
			else 
			{
				iRes = -1;
			}
			if ( iRes != 1 )
			{
				SElmDestruir ( &p_elmObj );
			}
		}
		else
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

int SLisIntlInsertarAlInicio ( SListaEnterosLargos * p_lisObj, long lDato )
{
	return ( SLisIntlInsertarElem ( p_lisObj, -1, lDato ) );
}

int SLisIntlInsertarAlFinal ( SListaEnterosLargos * p_lisObj, long lDato )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLisIntlInsertarElem ( p_lisObj, SLisIntlNumElementos ( p_lisObj ), lDato );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SLisIntlEliminarElem ( SListaEnterosLargos * p_lisObj, int iElem )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLisEliminarElem ( p_lisObj->p_lisDatos, iElem );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SLisIntlVaciar ( SListaEnterosLargos * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLisVaciar ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SLisIntlPosicion ( SListaEnterosLargos * p_lisObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLisPosicion ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

long SLisIntlActual ( SListaEnterosLargos * p_lisObj )
{
	SElemento *	p_elmObj;
	long		lRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_elmObj = ( SElemento * ) SLisActual ( p_lisObj->p_lisDatos );
		if ( ES_VALIDO ( p_elmObj ) )
		{
			lRes = SElmEnteroLargo ( p_elmObj );
		}
		else
		{
			ERROR_ESTABLECER( ERR_POSICION_INVALIDA );
			lRes = 0;
		}
	}
	else
	{
		lRes = 0;
	}
	return ( lRes );
}

void SLisIntlInicio ( SListaEnterosLargos * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLisInicio ( p_lisObj->p_lisDatos );
	}
}

void SLisIntlFinal ( SListaEnterosLargos * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLisFinal ( p_lisObj->p_lisDatos );
	}
}

void SLisIntlSiguiente ( SListaEnterosLargos * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLisSiguiente ( p_lisObj->p_lisDatos );
	}
}

void SLisIntlAnterior ( SListaEnterosLargos * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLisAnterior ( p_lisObj->p_lisDatos );
	}
}

void SLisIntlMoverA ( SListaEnterosLargos * p_lisObj, int iElem )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLisMoverA ( p_lisObj->p_lisDatos, iElem );
	}
}

void SLisIntlDeposicionar ( SListaEnterosLargos * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLisDeposicionar ( p_lisObj->p_lisDatos );
	}
}

int SLisIntlEsNulo ( SListaEnterosLargos * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		iRes = SLisEsNulo ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisIntlEstaPosicionada ( SListaEnterosLargos * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLisEstaPosicionada ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisIntlEstaEnFinal ( SListaEnterosLargos * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		iRes = SLisEstaEnFinal ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisIntlEstaEnInicio ( SListaEnterosLargos * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		iRes = SLisEstaEnInicio ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisIntlInsertar ( SListaEnterosLargos * p_lisObj, long lDato )
{
	return ( SLisIntlInsertarDetras ( p_lisObj, lDato ) );
}

int SLisIntlInsertarOrdenado ( SListaEnterosLargos * p_lisObj, long lDato )
{
	int			iRes;
	int			iElem;
	int			iNumElems;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = 0;
		iNumElems = SLisIntlNumElementos ( p_lisObj );
		if ( iNumElems > 0 )
		{
			/* La busqueda va POR LA CADENA, no por indice. Desde que
			   SLisElemento no usa el cursor, cada acceso por indice cuesta media
			   lista: buscando asi, esta funcion era O(n^2) y ordenar una lista
			   entera salia O(n^3) —con 4000 elementos no terminaba—.

			   Se para en el primer elemento MAYOR que el dato, o al final de la
			   cadena. En los dos casos el sitio donde insertar es iElem - 1:
			   con iElem = 0 vale -1, que SLisInsertarElem entiende como "al
			   principio", y con iElem = iNumElems apunta al ultimo, o sea que
			   inserta detras de el. */
			iElem = 0;
			p_elmObj = SLisElemento ( p_lisObj->p_lisDatos, 0 );
			while ( ES_VALIDO ( p_elmObj ) && ( lDato >= SElmEnteroLargo ( p_elmObj ) ) )
			{
				iElem = iElem + 1;
				p_elmObj = SElmSucesor ( p_elmObj );
			}
			iRes = SLisIntlInsertarElem ( p_lisObj, iElem - 1, lDato );
		}
		else
		{
			iRes = SLisIntlInsertar ( p_lisObj, lDato );
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisIntlInsertarDelante ( SListaEnterosLargos * p_lisObj, long lDato )
{
	int			iRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_elmObj = SElmCrearEnteroLargo ();
		if ( ES_VALIDO ( p_elmObj ) )
		{
			if ( SElmEscribirEnteroLargo ( p_elmObj, lDato ) == 1 )
			{
				iRes = SLisInsertarDelante ( p_lisObj->p_lisDatos, p_elmObj );
			}
			else
			{
				iRes = -1;
			}
			if ( iRes != 1 )
			{
				SElmDestruir ( &p_elmObj );
			}
		}
		else
		{
			iRes = -1;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisIntlInsertarDetras ( SListaEnterosLargos * p_lisObj, long lDato )
{
	int			iRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_elmObj = SElmCrearEnteroLargo ();
		if ( ES_VALIDO ( p_elmObj ) )
		{
			if ( SElmEscribirEnteroLargo ( p_elmObj, lDato ) == 1 )
			{
				iRes = SLisInsertarDetras ( p_lisObj->p_lisDatos, p_elmObj );
			}
			else
			{
				iRes = -1;
			}
			if ( iRes != 1 )
			{
				SElmDestruir ( &p_elmObj );
			}
		}
		else
		{
			iRes = -1;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisIntlEliminar ( SListaEnterosLargos * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		iRes = SLisEliminar ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisIntlExiste ( SListaEnterosLargos * p_lisObj, long lDato )
{
	int			iRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_lisObj )  ) 
	{
		iRes = 0;
		/* La generica, no SLisIntlElemento: esa devuelve el VALOR. */
		p_elmObj = SLisElemento ( p_lisObj->p_lisDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) && ( iRes == 0 ) )
		{
			if ( SElmEnteroLargo ( p_elmObj ) == lDato )
			{
				iRes = 1;
			}
			p_elmObj = SElmSucesorExt ( p_elmObj, 1 );
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

/* Busquedas por la cadena de una SLista de long, compartidas con
   SSecuenciaEnterosLargos ( por eso no son static ). BuscarSiguiente devuelve la
   posicion del siguiente igual DETRAS de iPos, o -1: con iPos = -1 busca
   desde el principio, y un iPos menor da -1. Repeticiones cuenta los iguales. */
int _SLisIntlBuscarSiguiente ( SLista * p_lisDatos, long lDato, int iPos )
{
	int			iRes;
	int			iEnc;
	SElemento *	p_elmObj;

	if ( iPos >= -1 )
	{
		iRes = iPos + 1;
		/* La generica, no la tipada: esa devuelve el VALOR. */
		p_elmObj = SLisElemento ( p_lisDatos, iRes );
		iEnc = 0;
		while ( ES_VALIDO ( p_elmObj ) && ( iEnc == 0 ) )
		{
			if ( SElmEnteroLargo ( p_elmObj ) == lDato )
			{
				iEnc = 1;
			}
			else
			{
				p_elmObj = SElmSucesor ( p_elmObj );
				iRes = iRes + 1;
			}
		}
		if ( iEnc == 0 )
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

int _SLisIntlRepeticiones ( SLista * p_lisDatos, long lDato )
{
	int			iRes;
	SElemento *	p_elmObj;

	iRes = 0;
	p_elmObj = SLisElemento ( p_lisDatos, 0 );
	while ( ES_VALIDO ( p_elmObj ) )
	{
		if ( SElmEnteroLargo ( p_elmObj ) == lDato )
		{
			iRes = iRes + 1;
		}
		p_elmObj = SElmSucesor ( p_elmObj );
	}
	return ( iRes );
}

/* Repeticiones: cuantos iguales hay, 0 si ninguno. Buscar es BuscarPrimero:
   la posicion del primero igual, o -1. */
int SLisIntlRepeticiones ( SListaEnterosLargos * p_lisObj, long lDato )
{
	int	iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = _SLisIntlRepeticiones ( p_lisObj->p_lisDatos, lDato );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisIntlBuscar ( SListaEnterosLargos * p_lisObj, long lDato )
{
	return ( SLisIntlBuscarPrimero ( p_lisObj, lDato ) );
}

int SLisIntlBuscarPrimero ( SListaEnterosLargos * p_lisObj, long lDato )
{
	return ( SLisIntlBuscarSiguiente ( p_lisObj, lDato, -1 ) );
}

int SLisIntlBuscarSiguiente ( SListaEnterosLargos * p_lisObj, long lDato, int iPos )
{
	int	iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = _SLisIntlBuscarSiguiente ( p_lisObj->p_lisDatos, lDato, iPos );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SLisIntlEstaOrdenada ( SListaEnterosLargos * p_lisObj )
{
	long		lDatoAnt;
	long		lDato;
	SElemento *	p_elmObj;
	int			iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = 1;
		lDatoAnt = LONG_MIN;
		/* La generica, no SLisIntlElemento: esa devuelve el VALOR. */
		p_elmObj = SLisElemento ( p_lisObj->p_lisDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) && ( iRes == 1 ) )
		{
			lDato = SElmEnteroLargo ( p_elmObj );
			if ( lDatoAnt > lDato )
			{
				iRes = 0;
			}
			lDatoAnt = lDato;
			p_elmObj = SElmSucesorExt ( p_elmObj, 1 );
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SListaEnterosLargos * SLisIntlOrdenar ( SListaEnterosLargos * p_lisObj )
{
	int						iError;
	long					lDato;
	SElemento *				p_elmObj;
	SListaEnterosLargos *	p_lisRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_lisRes = SLisIntlCrear ();
		iError = MemEsInvalida ( p_lisRes );
		/* La generica, no SLisIntlElemento: esa devuelve el VALOR. */
		p_elmObj = SLisElemento ( p_lisObj->p_lisDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) && ( iError == 0 ) )
		{
			lDato = SElmEnteroLargo ( p_elmObj );
			if ( SLisIntlInsertarOrdenado ( p_lisRes, lDato ) != 1 )
			{
				iError = 1;
			}
			p_elmObj = SElmSucesorExt ( p_elmObj, 1 );
		}
		if ( iError == 1 )
		{
			SLisIntlDestruir ( &p_lisRes );
			ERROR_ESTABLECER ( ERR_GENERAL_OPERATIVO );
		}
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

SListaEnterosLargos * SLisIntlExtraerUnicos ( SListaEnterosLargos * p_lisObj )
{
	return ( SLisIntlExtraerUnicosExt ( p_lisObj, 0 ) );
}

SListaEnterosLargos * SLisIntlExtraerUnicosExt ( SListaEnterosLargos * p_lisObj, int iOrdenar )
{
	int						iError;
	long					lDato;
	SElemento *				p_elmObj;
	SListaEnterosLargos *	p_lisRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_lisRes = SLisIntlCrear ();
		iError = MemEsInvalida ( p_lisRes );
		/* La generica, no SLisIntlElemento: esa devuelve el VALOR. */
		p_elmObj = SLisElemento ( p_lisObj->p_lisDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) && ( iError == 0 ) )
		{
			lDato = SElmEnteroLargo ( p_elmObj );
			if ( SLisIntlExiste ( p_lisRes, lDato ) == 0 )
			{
				if ( iOrdenar == 0 )
				{
					if ( SLisIntlInsertar ( p_lisRes, lDato ) != 1 )
					{
						iError = 1;
					}
				}
				else
				{
					if ( SLisIntlInsertarOrdenado ( p_lisRes, lDato ) != 1 )
					{
						iError = 1;
					}
				}
			}
			p_elmObj = SElmSucesorExt ( p_elmObj, 1 );
		}
		if ( iError == 1 )
		{
			SLisIntlDestruir ( &p_lisRes );
			ERROR_ESTABLECER ( ERR_GENERAL_OPERATIVO );
		}
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

int SLisIntlTieneRepetidos ( SListaEnterosLargos * p_lisObj )
{
	int						iRes;
	int						iError;
	long					lDato;
	SElemento *				p_elmObj;
	SListaEnterosLargos *	p_lisDistintos;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = 0;
		p_lisDistintos = SLisIntlCrear ();
		iError = MemEsInvalida ( p_lisDistintos );
		/* La generica, no SLisIntlElemento: esa devuelve el VALOR. */
		p_elmObj = SLisElemento ( p_lisObj->p_lisDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) && ( iError == 0 ) && ( iRes == 0 ) )
		{
			lDato = SElmEnteroLargo ( p_elmObj );
			if ( SLisIntlExiste ( p_lisDistintos, lDato ) == 1 )
			{
				iRes = 1;
			}
			else
			{
				if ( SLisIntlInsertarOrdenado ( p_lisDistintos, lDato ) != 1 )
				{
					iError = 1;
				}
			}
			p_elmObj = SElmSucesorExt ( p_elmObj, 1 );
		}
		SLisIntlDestruir ( &p_lisDistintos );
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


long SLisIntlMin ( SListaEnterosLargos * p_lisObj )
{
	long		lDato;
	long		lRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		lRes = LONG_MAX;
		/* La generica, no SLisIntlElemento: esa devuelve el VALOR. */
		p_elmObj = SLisElemento ( p_lisObj->p_lisDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) )
		{
			lDato = SElmEnteroLargo ( p_elmObj );
			if ( lDato < lRes )
			{
				lRes = lDato;
			}
			p_elmObj = SElmSucesorExt ( p_elmObj, 1 );
		}
	}
	else
	{
		ERROR_ESTABLECER ( ERR_PARAMETROS );
		lRes = 0;
	}
	return ( lRes );
}

long SLisIntlMax ( SListaEnterosLargos * p_lisObj )
{
	long		lDato;
	long		lRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		lRes = LONG_MIN;
		/* La generica, no SLisIntlElemento: esa devuelve el VALOR. */
		p_elmObj = SLisElemento ( p_lisObj->p_lisDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) )
		{
			lDato = SElmEnteroLargo ( p_elmObj );
			if ( lDato > lRes )
			{
				lRes = lDato;
			}
			p_elmObj = SElmSucesorExt ( p_elmObj, 1 );
		}
	}
	else
	{
		ERROR_ESTABLECER ( ERR_PARAMETROS );
		lRes = 0;
	}
	return ( lRes );
}

void SLisIntlObtenerParametros ( SListaEnterosLargos * p_lisObj, long * p_lMin, long * p_lMax, double * p_dMed )
{
	long		lDato;
	int			iNumElems;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lMin ) && ES_VALIDO ( p_lMax ) && ES_VALIDO ( p_dMed ) )
	{
		*p_lMin = LONG_MAX;
		*p_lMax = LONG_MIN;
		*p_dMed = 0.0;
		/* O(1): la lista lleva la cuenta, no hay que recorrerla otra vez. */
		iNumElems = SLisIntlNumElementos ( p_lisObj );
		/* La generica, no SLisIntlElemento: esa devuelve el VALOR. */
		p_elmObj = SLisElemento ( p_lisObj->p_lisDatos, 0 );
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
			p_elmObj = SElmSucesorExt ( p_elmObj, 1 );
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

int SLisIntlDefinidaPositiva ( SListaEnterosLargos * p_lisObj )
{
	long		lDato;
	int			iRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = 1;
		/* La generica, no SLisIntlElemento: esa devuelve el VALOR. */
		p_elmObj = SLisElemento ( p_lisObj->p_lisDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) && ( iRes == 1 ) )
		{
			lDato = SElmEnteroLargo ( p_elmObj );
			if ( lDato <= 0 )
			{
				iRes = 0;
			}
			p_elmObj = SElmSucesorExt ( p_elmObj, 1 );
		}
	}
	else
	{
		ERROR_ESTABLECER ( ERR_PARAMETROS );
		iRes = 0;
	}
	return ( iRes );
}

int SLisIntlSemidefinidaPositiva ( SListaEnterosLargos * p_lisObj )
{
	long		lDato;
	int			iRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = 1;
		/* La generica, no SLisIntlElemento: esa devuelve el VALOR. */
		p_elmObj = SLisElemento ( p_lisObj->p_lisDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) && ( iRes == 1 ) )
		{
			lDato = SElmEnteroLargo ( p_elmObj );
			if ( lDato < 0 )
			{
				iRes = 0;
			}
			p_elmObj = SElmSucesorExt ( p_elmObj, 1 );
		}
	}
	else
	{
		ERROR_ESTABLECER ( ERR_PARAMETROS );
		iRes = 0;
	}
	return ( iRes );
}

/* Copia de los valores, en el mismo orden; NULL si falla alguna copia. */
SListaEnterosLargos * SLisIntlDuplicar ( SListaEnterosLargos * p_lisObj )
{
	SListaEnterosLargos * p_lisRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_lisRes = _SLisIntlEnvolver ( SLisDuplicar ( p_lisObj->p_lisDatos ) );
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

/* Operaciones con otras listas: delegan en las de SLista, que recorren la
   cadena y no mueven el cursor de la lista de valores. Ver Listas.md. */
int SLisIntlExistenTodos ( SListaEnterosLargos * p_lisObj, SListaEnterosLargos * p_lisValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			iRes = SLisExistenTodos ( p_lisObj->p_lisDatos, p_lisValores->p_lisDatos );
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

int SLisIntlExisteAlguno ( SListaEnterosLargos * p_lisObj, SListaEnterosLargos * p_lisValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			iRes = SLisExisteAlguno ( p_lisObj->p_lisDatos, p_lisValores->p_lisDatos );
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

int SLisIntlInsertarLista ( SListaEnterosLargos * p_lisObj, SListaEnterosLargos * p_lisValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			iRes = SLisInsertarLista ( p_lisObj->p_lisDatos, p_lisValores->p_lisDatos );
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

int SLisIntlConcatenarLista ( SListaEnterosLargos * p_lisObj, SListaEnterosLargos * p_lisValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			iRes = SLisConcatenarLista ( p_lisObj->p_lisDatos, p_lisValores->p_lisDatos );
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

int SLisIntlInsertarListaDup ( SListaEnterosLargos * p_lisObj, SListaEnterosLargos * p_lisValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			iRes = SLisInsertarListaDup ( p_lisObj->p_lisDatos, p_lisValores->p_lisDatos );
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

int SLisIntlConcatenarListaDup ( SListaEnterosLargos * p_lisObj, SListaEnterosLargos * p_lisValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			iRes = SLisConcatenarListaDup ( p_lisObj->p_lisDatos, p_lisValores->p_lisDatos );
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

/* Envuelve en una SListaEnterosLargos la SLista que devuelve una operacion de SLista,
   y se queda con ella. No se usa SLisIntlCrear porque ese crea su propia SLista
   vacia, que al sustituirla quedaba sin liberar. Con p_lisDatos nula devuelve
   NULL, y si no puede reservar la envoltura destruye p_lisDatos. */
static SListaEnterosLargos * _SLisIntlEnvolver ( SLista * p_lisDatos )
{
	SListaEnterosLargos * p_lisRes;

	if ( ES_VALIDO ( p_lisDatos ) )
	{
		p_lisRes = (SListaEnterosLargos *) MemReservar ( sizeof ( SListaEnterosLargos ) );
		if ( ES_VALIDO ( p_lisRes ) )
		{
			p_lisRes->p_lisDatos = p_lisDatos;
		}
		else
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

SListaEnterosLargos * SLisIntlExtraerLista ( SListaEnterosLargos * p_lisObj, SListaEnterosLargos * p_lisValores )
{
	SListaEnterosLargos * p_lisRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			p_lisRes = _SLisIntlEnvolver ( SLisExtraerLista ( p_lisObj->p_lisDatos, p_lisValores->p_lisDatos ) );
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

/* Destruye la primera aparicion de cada valor de p_lisValores; ver
   SLisEliminarLista. */
int SLisIntlEliminarLista ( SListaEnterosLargos * p_lisObj, SListaEnterosLargos * p_lisValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			iRes = SLisEliminarLista ( p_lisObj->p_lisDatos, p_lisValores->p_lisDatos );
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

SListaEnterosLargos * SLisIntlUnion ( SListaEnterosLargos * p_lisValores1, SListaEnterosLargos * p_lisValores2 )
{
	SListaEnterosLargos * p_lisRes;

	if ( ES_VALIDO ( p_lisValores1 ) )
	{
		if ( ES_VALIDO ( p_lisValores2 ) )
		{
			p_lisRes = _SLisIntlEnvolver ( SLisUnion ( p_lisValores1->p_lisDatos, p_lisValores2->p_lisDatos ) );
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

SListaEnterosLargos * SLisIntlInterseccion ( SListaEnterosLargos * p_lisValores1, SListaEnterosLargos * p_lisValores2 )
{
	SListaEnterosLargos * p_lisRes;

	if ( ES_VALIDO ( p_lisValores1 ) )
	{
		if ( ES_VALIDO ( p_lisValores2 ) )
		{
			p_lisRes = _SLisIntlEnvolver ( SLisInterseccion ( p_lisValores1->p_lisDatos, p_lisValores2->p_lisDatos ) );
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

SListaEnterosLargos * SLisIntlDiferencia ( SListaEnterosLargos * p_lisValores1, SListaEnterosLargos * p_lisValores2 )
{
	SListaEnterosLargos * p_lisRes;

	if ( ES_VALIDO ( p_lisValores1 ) )
	{
		if ( ES_VALIDO ( p_lisValores2 ) )
		{
			p_lisRes = _SLisIntlEnvolver ( SLisDiferencia ( p_lisValores1->p_lisDatos, p_lisValores2->p_lisDatos ) );
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


