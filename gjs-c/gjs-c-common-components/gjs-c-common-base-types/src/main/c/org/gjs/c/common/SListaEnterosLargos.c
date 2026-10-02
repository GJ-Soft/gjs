#include "SListaEnterosLargos.h"

#include "TiposBasicosConfig.h"




SListaEnterosLargos * SLisEntlCrear ()
{
	SListaEnterosLargos * p_lisObj;
	
	p_lisObj = (SListaEnterosLargos *) MemReservar ( sizeof ( SListaEnterosLargos ) );
	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_lisObj->p_lisDatos = SLisCrear ();
	}
	return ( p_lisObj );
}

void SLisEntlDestruir ( SListaEnterosLargos ** p_p_lisObj )
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

int SLisEntlEsValida ( SListaEnterosLargos * p_lisObj )
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

int SLisEntlEstaVacia ( SListaEnterosLargos * p_lisObj )
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

int SLisEntlNumElementos ( SListaEnterosLargos * p_lisObj )
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

long SLisEntlElemento ( SListaEnterosLargos * p_lisObj, int iElem )
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

int SLisEntlEstablecerElem ( SListaEnterosLargos * p_lisObj, int iPos, long lDato )
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

int SLisEntlInsertarElem ( SListaEnterosLargos * p_lisObj, int iPosAnt, long lDato )
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

int SLisEntlInsertarAlInicio ( SListaEnterosLargos * p_lisObj, long lDato )
{
	return ( SLisEntlInsertarElem ( p_lisObj, -1, lDato ) );
}

int SLisEntlInsertarAlFinal ( SListaEnterosLargos * p_lisObj, long lDato )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLisEntlInsertarElem ( p_lisObj, SLisEntlNumElementos ( p_lisObj ), lDato );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SLisEntlEliminarElem ( SListaEnterosLargos * p_lisObj, int iElem )
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

int SLisEntlVaciar ( SListaEnterosLargos * p_lisObj )
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

int SLisEntlPosicion ( SListaEnterosLargos * p_lisObj )
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

long SLisEntlActual ( SListaEnterosLargos * p_lisObj )
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

void SLisEntlInicio ( SListaEnterosLargos * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLisInicio ( p_lisObj->p_lisDatos );
	}
}

void SLisEntlFinal ( SListaEnterosLargos * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLisFinal ( p_lisObj->p_lisDatos );
	}
}

void SLisEntlSiguiente ( SListaEnterosLargos * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLisSiguiente ( p_lisObj->p_lisDatos );
	}
}

void SLisEntlAnterior ( SListaEnterosLargos * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLisAnterior ( p_lisObj->p_lisDatos );
	}
}

void SLisEntlMoverA ( SListaEnterosLargos * p_lisObj, int iElem )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLisMoverA ( p_lisObj->p_lisDatos, iElem );
	}
}

void SLisEntlDeposicionar ( SListaEnterosLargos * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLisDeposicionar ( p_lisObj->p_lisDatos );
	}
}

int SLisEntlEsNulo ( SListaEnterosLargos * p_lisObj )
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

int SLisEntlEstaEnFinal ( SListaEnterosLargos * p_lisObj )
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

int SLisEntlEstaEnInicio ( SListaEnterosLargos * p_lisObj )
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

int SLisEntlInsertar ( SListaEnterosLargos * p_lisObj, long lDato )
{
	return ( SLisEntlInsertarDetras ( p_lisObj, lDato ) );
}

int SLisEntlInsertarOrdenado ( SListaEnterosLargos * p_lisObj, long lDato )
{
	int			iRes;
	int			iElem;
	int			iNumElems;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = 0;
		iNumElems = SLisEntlNumElementos ( p_lisObj );
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
			iRes = SLisEntlInsertarElem ( p_lisObj, iElem - 1, lDato );
		}
		else
		{
			iRes = SLisEntlInsertar ( p_lisObj, lDato );
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisEntlInsertarDelante ( SListaEnterosLargos * p_lisObj, long lDato )
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

int SLisEntlInsertarDetras ( SListaEnterosLargos * p_lisObj, long lDato )
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

int SLisEntlEliminar ( SListaEnterosLargos * p_lisObj )
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

int SLisEntlExiste ( SListaEnterosLargos * p_lisObj, long lDato )
{
	int			iRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_lisObj )  ) 
	{
		iRes = 0;
		/* La generica, no SLisEntlElemento: esa devuelve el VALOR. */
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

int SLisEntlBuscar ( SListaEnterosLargos * p_lisObj, long lDato )
{
	int			iRes;
	int			iElem;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iElem = 0;
		iRes = -1;
		/* La generica, no SLisEntlElemento: esa devuelve el VALOR. */
		p_elmObj = SLisElemento ( p_lisObj->p_lisDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) && ( iRes == -1 ) )
		{
			if ( SElmEnteroLargo ( p_elmObj ) == lDato )
			{
				iRes = iElem;
			}
			iElem = iElem + 1;
			p_elmObj = SElmSucesorExt ( p_elmObj, 1 );
		}
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SLisEntlEstaOrdenada ( SListaEnterosLargos * p_lisObj )
{
	long		lDatoAnt;
	long		lDato;
	SElemento *	p_elmObj;
	int			iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = 1;
		lDatoAnt = LONG_MIN;
		/* La generica, no SLisEntlElemento: esa devuelve el VALOR. */
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

SListaEnterosLargos * SLisEntlOrdenar ( SListaEnterosLargos * p_lisObj )
{
	int						iError;
	long					lDato;
	SElemento *				p_elmObj;
	SListaEnterosLargos *	p_lisRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_lisRes = SLisEntlCrear ();
		iError = MemEsInvalida ( p_lisRes );
		/* La generica, no SLisEntlElemento: esa devuelve el VALOR. */
		p_elmObj = SLisElemento ( p_lisObj->p_lisDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) && ( iError == 0 ) )
		{
			lDato = SElmEnteroLargo ( p_elmObj );
			if ( SLisEntlInsertarOrdenado ( p_lisRes, lDato ) != 1 )
			{
				iError = 1;
			}
			p_elmObj = SElmSucesorExt ( p_elmObj, 1 );
		}
		if ( iError == 1 )
		{
			SLisEntlDestruir ( &p_lisRes );
			ERROR_ESTABLECER ( ERR_GENERAL_OPERATIVO );
		}
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

SListaEnterosLargos * SLisEntlExtraerUnicos ( SListaEnterosLargos * p_lisObj )
{
	return ( SLisEntlExtraerUnicosExt ( p_lisObj, 0 ) );
}

SListaEnterosLargos * SLisEntlExtraerUnicosExt ( SListaEnterosLargos * p_lisObj, int iOrdenar )
{
	int						iError;
	long					lDato;
	SElemento *				p_elmObj;
	SListaEnterosLargos *	p_lisRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_lisRes = SLisEntlCrear ();
		iError = MemEsInvalida ( p_lisRes );
		/* La generica, no SLisEntlElemento: esa devuelve el VALOR. */
		p_elmObj = SLisElemento ( p_lisObj->p_lisDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) && ( iError == 0 ) )
		{
			lDato = SElmEnteroLargo ( p_elmObj );
			if ( SLisEntlExiste ( p_lisRes, lDato ) == 0 )
			{
				if ( iOrdenar == 0 )
				{
					if ( SLisEntlInsertar ( p_lisRes, lDato ) != 1 )
					{
						iError = 1;
					}
				}
				else
				{
					if ( SLisEntlInsertarOrdenado ( p_lisRes, lDato ) != 1 )
					{
						iError = 1;
					}
				}
			}
			p_elmObj = SElmSucesorExt ( p_elmObj, 1 );
		}
		if ( iError == 1 )
		{
			SLisEntlDestruir ( &p_lisRes );
			ERROR_ESTABLECER ( ERR_GENERAL_OPERATIVO );
		}
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

int SLisEntlTieneRepetidos ( SListaEnterosLargos * p_lisObj )
{
	int						iRes;
	int						iError;
	long					lDato;
	SElemento *				p_elmObj;
	SListaEnterosLargos *	p_lisDistintos;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = 0;
		p_lisDistintos = SLisEntlCrear ();
		iError = MemEsInvalida ( p_lisDistintos );
		/* La generica, no SLisEntlElemento: esa devuelve el VALOR. */
		p_elmObj = SLisElemento ( p_lisObj->p_lisDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) && ( iError == 0 ) && ( iRes == 0 ) )
		{
			lDato = SElmEnteroLargo ( p_elmObj );
			if ( SLisEntlExiste ( p_lisDistintos, lDato ) == 1 )
			{
				iRes = 1;
			}
			else
			{
				if ( SLisEntlInsertarOrdenado ( p_lisDistintos, lDato ) != 1 )
				{
					iError = 1;
				}
			}
			p_elmObj = SElmSucesorExt ( p_elmObj, 1 );
		}
		SLisEntlDestruir ( &p_lisDistintos );
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


long SLisEntlMin ( SListaEnterosLargos * p_lisObj )
{
	long		lDato;
	long		lRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		lRes = LONG_MAX;
		/* La generica, no SLisEntlElemento: esa devuelve el VALOR. */
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

long SLisEntlMax ( SListaEnterosLargos * p_lisObj )
{
	long		lDato;
	long		lRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		lRes = LONG_MIN;
		/* La generica, no SLisEntlElemento: esa devuelve el VALOR. */
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

void SLisEntlObtenerParametros ( SListaEnterosLargos * p_lisObj, long * p_lMin, long * p_lMax, double * p_dMed )
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
		iNumElems = SLisEntlNumElementos ( p_lisObj );
		/* La generica, no SLisEntlElemento: esa devuelve el VALOR. */
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

int SLisEntlDefinidaPositiva ( SListaEnterosLargos * p_lisObj )
{
	long		lDato;
	int			iRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = 1;
		/* La generica, no SLisEntlElemento: esa devuelve el VALOR. */
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

int SLisEntlSemidefinidaPositiva ( SListaEnterosLargos * p_lisObj )
{
	long		lDato;
	int			iRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = 1;
		/* La generica, no SLisEntlElemento: esa devuelve el VALOR. */
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





