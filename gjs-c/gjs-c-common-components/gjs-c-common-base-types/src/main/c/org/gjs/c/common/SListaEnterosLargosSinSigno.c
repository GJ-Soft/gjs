#include "SListaEnterosLargosSinSigno.h"

#include "TiposBasicosConfig.h"




SListaEnterosLargosSinSigno * SLisEntLssCrear ()
{
	SListaEnterosLargosSinSigno * p_lisObj;
	
	p_lisObj = (SListaEnterosLargosSinSigno *) MemReservar ( sizeof ( SListaEnterosLargosSinSigno ) );
	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_lisObj->p_lisDatos = SLisCrear ();
	}
	return ( p_lisObj );
}

void SLisEntLssDestruir ( SListaEnterosLargosSinSigno ** p_p_lisObj )
{
	SListaEnterosLargosSinSigno * p_lisObj;
	
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

int SLisEntLssEsValida ( SListaEnterosLargosSinSigno * p_lisObj )
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

int SLisEntLssEstaVacia ( SListaEnterosLargosSinSigno * p_lisObj )
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

int SLisEntLssNumElementos ( SListaEnterosLargosSinSigno * p_lisObj )
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

unsigned long SLisEntLssElemento ( SListaEnterosLargosSinSigno * p_lisObj, int iElem )
{
	unsigned long	ulRes;
	SElemento *		p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_elmObj = SLisElemento ( p_lisObj->p_lisDatos, iElem );
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

int SLisEntLssEstablecerElem ( SListaEnterosLargosSinSigno * p_lisObj, int iPos, unsigned long ulDato )
{
	int			iRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_elmObj = SLisElemento ( p_lisObj->p_lisDatos, iPos );
		if ( ES_VALIDO ( p_elmObj ) )
		{
			iRes = SElmEscribirEnteroLargoSinSigno ( p_elmObj, ulDato );
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

int SLisEntLssInsertarElem ( SListaEnterosLargosSinSigno * p_lisObj, int iPosAnt, unsigned long ulDato )
{
	int			iRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_elmObj = SElmCrearEnteroLargoSinSigno ();
		if ( ES_VALIDO ( p_elmObj ) )
		{
			if ( SElmEscribirEnteroLargoSinSigno ( p_elmObj, ulDato ) == 1 )
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

int SLisEntLssInsertarAlInicio ( SListaEnterosLargosSinSigno * p_lisObj, unsigned long ulDato )
{
	return ( SLisEntLssInsertarElem ( p_lisObj, -1, ulDato ) );
}

int SLisEntLssInsertarAlFinal ( SListaEnterosLargosSinSigno * p_lisObj, unsigned long ulDato )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLisEntLssInsertarElem ( p_lisObj, SLisEntLssNumElementos ( p_lisObj ), ulDato );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SLisEntLssEliminarElem ( SListaEnterosLargosSinSigno * p_lisObj, int iElem )
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

int SLisEntLssVaciar ( SListaEnterosLargosSinSigno * p_lisObj )
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

int SLisEntLssPosicion ( SListaEnterosLargosSinSigno * p_lisObj )
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

unsigned long SLisEntLssActual ( SListaEnterosLargosSinSigno * p_lisObj )
{
	SElemento *		p_elmObj;
	unsigned long	ulRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_elmObj = ( SElemento * ) SLisActual ( p_lisObj->p_lisDatos );
		if ( ES_VALIDO ( p_elmObj ) )
		{
			ulRes = SElmEnteroLargoSinSigno ( p_elmObj );
		}
		else
		{
			ERROR_ESTABLECER( ERR_POSICION_INVALIDA );
			ulRes = 0;
		}
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

void SLisEntLssInicio ( SListaEnterosLargosSinSigno * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLisInicio ( p_lisObj->p_lisDatos );
	}
}

void SLisEntLssFinal ( SListaEnterosLargosSinSigno * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLisFinal ( p_lisObj->p_lisDatos );
	}
}

void SLisEntLssSiguiente ( SListaEnterosLargosSinSigno * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLisSiguiente ( p_lisObj->p_lisDatos );
	}
}

void SLisEntLssAnterior ( SListaEnterosLargosSinSigno * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLisAnterior ( p_lisObj->p_lisDatos );
	}
}

void SLisEntLssMoverA ( SListaEnterosLargosSinSigno * p_lisObj, int iElem )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLisMoverA ( p_lisObj->p_lisDatos, iElem );
	}
}

void SLisEntLssDeposicionar ( SListaEnterosLargosSinSigno * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLisDeposicionar ( p_lisObj->p_lisDatos );
	}
}

int SLisEntLssEsNulo ( SListaEnterosLargosSinSigno * p_lisObj )
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

int SLisEntLssEstaEnFinal ( SListaEnterosLargosSinSigno * p_lisObj )
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

int SLisEntLssEstaEnInicio ( SListaEnterosLargosSinSigno * p_lisObj )
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

int SLisEntLssInsertar ( SListaEnterosLargosSinSigno * p_lisObj, unsigned long ulDato )
{
	return ( SLisEntLssInsertarDetras ( p_lisObj, ulDato ) );
}

int SLisEntLssInsertarOrdenado ( SListaEnterosLargosSinSigno * p_lisObj, unsigned long ulDato )
{
	int			iRes;
	int			iElem;
	int			iNumElems;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = 0;
		iNumElems = SLisEntLssNumElementos ( p_lisObj );
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
			while ( ES_VALIDO ( p_elmObj ) && ( ulDato >= SElmEnteroLargoSinSigno ( p_elmObj ) ) )
			{
				iElem = iElem + 1;
				p_elmObj = SElmSucesor ( p_elmObj );
			}
			iRes = SLisEntLssInsertarElem ( p_lisObj, iElem - 1, ulDato );
		}
		else
		{
			iRes = SLisEntLssInsertar ( p_lisObj, ulDato );
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisEntLssInsertarDelante ( SListaEnterosLargosSinSigno * p_lisObj, unsigned long ulDato )
{
	int			iRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_elmObj = SElmCrearEnteroLargoSinSigno ();
		if ( ES_VALIDO ( p_elmObj ) )
		{
			if ( SElmEscribirEnteroLargoSinSigno ( p_elmObj, ulDato ) == 1 )
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

int SLisEntLssInsertarDetras ( SListaEnterosLargosSinSigno * p_lisObj, unsigned long ulDato )
{
	int			iRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_elmObj = SElmCrearEnteroLargoSinSigno ();
		if ( ES_VALIDO ( p_elmObj ) )
		{
			if ( SElmEscribirEnteroLargoSinSigno ( p_elmObj, ulDato ) == 1 )
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

int SLisEntLssEliminar ( SListaEnterosLargosSinSigno * p_lisObj )
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

int SLisEntLssExiste ( SListaEnterosLargosSinSigno * p_lisObj, unsigned long ulDato )
{
	int			iRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_lisObj )  ) 
	{
		iRes = 0;
		/* La generica, no SLisEntLssElemento: esa devuelve el VALOR. */
		p_elmObj = SLisElemento ( p_lisObj->p_lisDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) && ( iRes == 0 ) )
		{
			if ( SElmEnteroLargoSinSigno ( p_elmObj ) == ulDato )
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

int SLisEntLssBuscar ( SListaEnterosLargosSinSigno * p_lisObj, unsigned long ulDato )
{
	int			iRes;
	int			iElem;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iElem = 0;
		iRes = -1;
		/* La generica, no SLisEntLssElemento: esa devuelve el VALOR. */
		p_elmObj = SLisElemento ( p_lisObj->p_lisDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) && ( iRes == -1 ) )
		{
			if ( SElmEnteroLargoSinSigno ( p_elmObj ) == ulDato )
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

int SLisEntLssEstaOrdenada ( SListaEnterosLargosSinSigno * p_lisObj )
{
	unsigned long	ulDatoAnt;
	unsigned long	ulDato;
	SElemento *		p_elmObj;
	int				iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = 1;
		ulDatoAnt = 0;
		/* La generica, no SLisEntLssElemento: esa devuelve el VALOR. */
		p_elmObj = SLisElemento ( p_lisObj->p_lisDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) && ( iRes == 1 ) )
		{
			ulDato = SElmEnteroLargoSinSigno ( p_elmObj );
			if ( ulDatoAnt > ulDato )
			{
				iRes = 0;
			}
			ulDatoAnt = ulDato;
			p_elmObj = SElmSucesorExt ( p_elmObj, 1 );
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SListaEnterosLargosSinSigno * SLisEntLssOrdenar ( SListaEnterosLargosSinSigno * p_lisObj )
{
	int								iError;
	unsigned long					ulDato;
	SElemento *						p_elmObj;
	SListaEnterosLargosSinSigno *	p_lisRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_lisRes = SLisEntLssCrear ();
		iError = MemEsInvalida ( p_lisRes );
		/* La generica, no SLisEntLssElemento: esa devuelve el VALOR. */
		p_elmObj = SLisElemento ( p_lisObj->p_lisDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) && ( iError == 0 ) )
		{
			ulDato = SElmEnteroLargoSinSigno ( p_elmObj );
			if ( SLisEntLssInsertarOrdenado ( p_lisRes, ulDato ) != 1 )
			{
				iError = 1;
			}
			p_elmObj = SElmSucesorExt ( p_elmObj, 1 );
		}
		if ( iError == 1 )
		{
			SLisEntLssDestruir ( &p_lisRes );
			ERROR_ESTABLECER ( ERR_GENERAL_OPERATIVO );
		}
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

SListaEnterosLargosSinSigno * SLisEntLssExtraerUnicos ( SListaEnterosLargosSinSigno * p_lisObj )
{
	return ( SLisEntLssExtraerUnicosExt ( p_lisObj, 0 ) );
}

SListaEnterosLargosSinSigno * SLisEntLssExtraerUnicosExt ( SListaEnterosLargosSinSigno * p_lisObj, int iOrdenar )
{
	int								iError;
	unsigned long					ulDato;
	SElemento *						p_elmObj;
	SListaEnterosLargosSinSigno *	p_lisRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_lisRes = SLisEntLssCrear ();
		iError = MemEsInvalida ( p_lisRes );
		/* La generica, no SLisEntLssElemento: esa devuelve el VALOR. */
		p_elmObj = SLisElemento ( p_lisObj->p_lisDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) && ( iError == 0 ) )
		{
			ulDato = SElmEnteroLargoSinSigno ( p_elmObj );
			if ( SLisEntLssExiste ( p_lisRes, ulDato ) == 0 )
			{
				if ( iOrdenar == 0 )
				{
					if ( SLisEntLssInsertar ( p_lisRes, ulDato ) != 1 )
					{
						iError = 1;
					}
				}
				else
				{
					if ( SLisEntLssInsertarOrdenado ( p_lisRes, ulDato ) != 1 )
					{
						iError = 1;
					}
				}
			}
			p_elmObj = SElmSucesorExt ( p_elmObj, 1 );
		}
		if ( iError == 1 )
		{
			SLisEntLssDestruir ( &p_lisRes );
			ERROR_ESTABLECER ( ERR_GENERAL_OPERATIVO );
		}
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

int SLisEntLssTieneRepetidos ( SListaEnterosLargosSinSigno * p_lisObj )
{
	int								iRes;
	int								iError;
	unsigned long					ulDato;
	SElemento *						p_elmObj;
	SListaEnterosLargosSinSigno *	p_lisDistintos;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = 0;
		p_lisDistintos = SLisEntLssCrear ();
		iError = MemEsInvalida ( p_lisDistintos );
		/* La generica, no SLisEntLssElemento: esa devuelve el VALOR. */
		p_elmObj = SLisElemento ( p_lisObj->p_lisDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) && ( iError == 0 ) && ( iRes == 0 ) )
		{
			ulDato = SElmEnteroLargoSinSigno ( p_elmObj );
			if ( SLisEntLssExiste ( p_lisDistintos, ulDato ) == 1 )
			{
				iRes = 1;
			}
			else
			{
				if ( SLisEntLssInsertarOrdenado ( p_lisDistintos, ulDato ) != 1 )
				{
					iError = 1;
				}
			}
			p_elmObj = SElmSucesorExt ( p_elmObj, 1 );
		}
		SLisEntLssDestruir ( &p_lisDistintos );
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


unsigned long SLisEntLssMin ( SListaEnterosLargosSinSigno * p_lisObj )
{
	unsigned long	ulDato;
	unsigned long	ulRes;
	SElemento *		p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		ulRes = ULONG_MAX;
		/* La generica, no SLisEntLssElemento: esa devuelve el VALOR. */
		p_elmObj = SLisElemento ( p_lisObj->p_lisDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) )
		{
			ulDato = SElmEnteroLargoSinSigno ( p_elmObj );
			if ( ulDato < ulRes )
			{
				ulRes = ulDato;
			}
			p_elmObj = SElmSucesorExt ( p_elmObj, 1 );
		}
	}
	else
	{
		ERROR_ESTABLECER ( ERR_PARAMETROS );
		ulRes = 0;
	}
	return ( ulRes );
}

unsigned long SLisEntLssMax ( SListaEnterosLargosSinSigno * p_lisObj )
{
	unsigned long	ulDato;
	unsigned long	ulRes;
	SElemento *		p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		ulRes = 0;
		/* La generica, no SLisEntLssElemento: esa devuelve el VALOR. */
		p_elmObj = SLisElemento ( p_lisObj->p_lisDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) )
		{
			ulDato = SElmEnteroLargoSinSigno ( p_elmObj );
			if ( ulDato > ulRes )
			{
				ulRes = ulDato;
			}
			p_elmObj = SElmSucesorExt ( p_elmObj, 1 );
		}
	}
	else
	{
		ERROR_ESTABLECER ( ERR_PARAMETROS );
		ulRes = 0;
	}
	return ( ulRes );
}

void SLisEntLssObtenerParametros ( SListaEnterosLargosSinSigno * p_lisObj, unsigned long * p_ulMin, unsigned long * p_ulMax, double * p_dMed )
{
	unsigned long	ulDato;
	int				iNumElems;
	SElemento *		p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_ulMin ) && ES_VALIDO ( p_ulMax ) && ES_VALIDO ( p_dMed ) )
	{
		*p_ulMin = ULONG_MAX;
		*p_ulMax = 0;
		*p_dMed = 0.0;
		/* O(1): la lista lleva la cuenta, no hay que recorrerla otra vez. */
		iNumElems = SLisEntLssNumElementos ( p_lisObj );
		/* La generica, no SLisEntLssElemento: esa devuelve el VALOR. */
		p_elmObj = SLisElemento ( p_lisObj->p_lisDatos, 0 );
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

int SLisEntLssDefinidaPositiva ( SListaEnterosLargosSinSigno * p_lisObj )
{
	unsigned long	ulDato;
	int				iRes;
	SElemento *		p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = 1;
		/* La generica, no SLisEntLssElemento: esa devuelve el VALOR. */
		p_elmObj = SLisElemento ( p_lisObj->p_lisDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) && ( iRes == 1 ) )
		{
			ulDato = SElmEnteroLargoSinSigno ( p_elmObj );
			if ( ulDato == 0 )
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



