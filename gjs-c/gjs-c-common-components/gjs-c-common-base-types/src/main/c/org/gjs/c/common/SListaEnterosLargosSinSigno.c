#include "SListaEnterosLargosSinSigno.h"

#include "TiposBasicosConfig.h"





SListaEnterosLargosSinSigno * SLisIntLssCrear ()
{
	SListaEnterosLargosSinSigno * p_lisObj;
	
	p_lisObj = (SListaEnterosLargosSinSigno *) MemReservar ( sizeof ( SListaEnterosLargosSinSigno ) );
	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_lisObj->p_lisDatos = SLisCrear ();
	}
	return ( p_lisObj );
}

/* La lista pasa a ser de la lista de enteros, que la destruye con ella. Si
   la lista no es valida, o no se puede crear, devuelve NULL y la lista sigue
   siendo del llamante. */
SListaEnterosLargosSinSigno * SLisIntLssEncapsular ( SLista * p_lisDatos )
{
	SListaEnterosLargosSinSigno * p_lisRes;

	if ( SLisEsValida ( p_lisDatos ) == 1 )
	{
		p_lisRes = (SListaEnterosLargosSinSigno *) MemReservar ( sizeof ( SListaEnterosLargosSinSigno ) );
		if ( ES_VALIDO ( p_lisRes ) )
		{
			p_lisRes->p_lisDatos = p_lisDatos;
		}
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

void SLisIntLssDestruir ( SListaEnterosLargosSinSigno ** p_p_lisObj )
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

int SLisIntLssEsValida ( SListaEnterosLargosSinSigno * p_lisObj )
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

int SLisIntLssEstaVacia ( SListaEnterosLargosSinSigno * p_lisObj )
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

int SLisIntLssNumElementos ( SListaEnterosLargosSinSigno * p_lisObj )
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

unsigned long SLisIntLssElemento ( SListaEnterosLargosSinSigno * p_lisObj, int iElem )
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

int SLisIntLssEstablecerElem ( SListaEnterosLargosSinSigno * p_lisObj, int iPos, unsigned long ulDato )
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

int SLisIntLssInsertarElem ( SListaEnterosLargosSinSigno * p_lisObj, int iPosAnt, unsigned long ulDato )
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

int SLisIntLssInsertarAlInicio ( SListaEnterosLargosSinSigno * p_lisObj, unsigned long ulDato )
{
	return ( SLisIntLssInsertarElem ( p_lisObj, -1, ulDato ) );
}

int SLisIntLssInsertarAlFinal ( SListaEnterosLargosSinSigno * p_lisObj, unsigned long ulDato )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLisIntLssInsertarElem ( p_lisObj, SLisIntLssNumElementos ( p_lisObj ), ulDato );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisIntLssEliminarElem ( SListaEnterosLargosSinSigno * p_lisObj, int iElem )
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

int SLisIntLssVaciar ( SListaEnterosLargosSinSigno * p_lisObj )
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

int SLisIntLssPosicion ( SListaEnterosLargosSinSigno * p_lisObj )
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

unsigned long SLisIntLssActual ( SListaEnterosLargosSinSigno * p_lisObj )
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

void SLisIntLssInicio ( SListaEnterosLargosSinSigno * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLisInicio ( p_lisObj->p_lisDatos );
	}
}

void SLisIntLssFinal ( SListaEnterosLargosSinSigno * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLisFinal ( p_lisObj->p_lisDatos );
	}
}

void SLisIntLssSiguiente ( SListaEnterosLargosSinSigno * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLisSiguiente ( p_lisObj->p_lisDatos );
	}
}

void SLisIntLssAnterior ( SListaEnterosLargosSinSigno * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLisAnterior ( p_lisObj->p_lisDatos );
	}
}

void SLisIntLssMoverA ( SListaEnterosLargosSinSigno * p_lisObj, int iElem )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLisMoverA ( p_lisObj->p_lisDatos, iElem );
	}
}

void SLisIntLssDeposicionar ( SListaEnterosLargosSinSigno * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLisDeposicionar ( p_lisObj->p_lisDatos );
	}
}

int SLisIntLssEsNulo ( SListaEnterosLargosSinSigno * p_lisObj )
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

int SLisIntLssEstaPosicionada ( SListaEnterosLargosSinSigno * p_lisObj )
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

int SLisIntLssEstaEnFinal ( SListaEnterosLargosSinSigno * p_lisObj )
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

int SLisIntLssEstaEnInicio ( SListaEnterosLargosSinSigno * p_lisObj )
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

int SLisIntLssInsertar ( SListaEnterosLargosSinSigno * p_lisObj, unsigned long ulDato )
{
	return ( SLisIntLssInsertarDetras ( p_lisObj, ulDato ) );
}

int SLisIntLssInsertarOrdenado ( SListaEnterosLargosSinSigno * p_lisObj, unsigned long ulDato )
{
	int			iRes;
	int			iElem;
	int			iNumElems;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = 0;
		iNumElems = SLisIntLssNumElementos ( p_lisObj );
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
			iRes = SLisIntLssInsertarElem ( p_lisObj, iElem - 1, ulDato );
		}
		else
		{
			iRes = SLisIntLssInsertar ( p_lisObj, ulDato );
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisIntLssInsertarDelante ( SListaEnterosLargosSinSigno * p_lisObj, unsigned long ulDato )
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

int SLisIntLssInsertarDetras ( SListaEnterosLargosSinSigno * p_lisObj, unsigned long ulDato )
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

int SLisIntLssEliminar ( SListaEnterosLargosSinSigno * p_lisObj )
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

int SLisIntLssExiste ( SListaEnterosLargosSinSigno * p_lisObj, unsigned long ulDato )
{
	int			iRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_lisObj )  ) 
	{
		iRes = 0;
		/* La generica, no SLisIntLssElemento: esa devuelve el VALOR. */
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

/* Busquedas por la cadena de una SLista de unsigned long, compartidas con
   SSecuenciaEnterosLargosSinSigno ( por eso no son static ). BuscarSiguiente devuelve la
   posicion del siguiente igual DETRAS de iPos, o -1: con iPos = -1 busca
   desde el principio, y un iPos menor da -1. Repeticiones cuenta los iguales. */
int _SLisIntLssBuscarSiguiente ( SLista * p_lisDatos, unsigned long ulDato, int iPos )
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
			if ( SElmEnteroLargoSinSigno ( p_elmObj ) == ulDato )
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

int _SLisIntLssRepeticiones ( SLista * p_lisDatos, unsigned long ulDato )
{
	int			iRes;
	SElemento *	p_elmObj;

	iRes = 0;
	p_elmObj = SLisElemento ( p_lisDatos, 0 );
	while ( ES_VALIDO ( p_elmObj ) )
	{
		if ( SElmEnteroLargoSinSigno ( p_elmObj ) == ulDato )
		{
			iRes = iRes + 1;
		}
		p_elmObj = SElmSucesor ( p_elmObj );
	}
	return ( iRes );
}

/* Repeticiones: cuantos iguales hay, 0 si ninguno. Buscar es BuscarPrimero:
   la posicion del primero igual, o -1. */
int SLisIntLssRepeticiones ( SListaEnterosLargosSinSigno * p_lisObj, unsigned long ulDato )
{
	int	iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = _SLisIntLssRepeticiones ( p_lisObj->p_lisDatos, ulDato );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisIntLssBuscar ( SListaEnterosLargosSinSigno * p_lisObj, unsigned long ulDato )
{
	return ( SLisIntLssBuscarPrimero ( p_lisObj, ulDato ) );
}

int SLisIntLssBuscarPrimero ( SListaEnterosLargosSinSigno * p_lisObj, unsigned long ulDato )
{
	return ( SLisIntLssBuscarSiguiente ( p_lisObj, ulDato, -1 ) );
}

int SLisIntLssBuscarSiguiente ( SListaEnterosLargosSinSigno * p_lisObj, unsigned long ulDato, int iPos )
{
	int	iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = _SLisIntLssBuscarSiguiente ( p_lisObj->p_lisDatos, ulDato, iPos );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SLisIntLssEstaOrdenada ( SListaEnterosLargosSinSigno * p_lisObj )
{
	unsigned long	ulDatoAnt;
	unsigned long	ulDato;
	SElemento *		p_elmObj;
	int				iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = 1;
		ulDatoAnt = 0;
		/* La generica, no SLisIntLssElemento: esa devuelve el VALOR. */
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

SListaEnterosLargosSinSigno * SLisIntLssOrdenar ( SListaEnterosLargosSinSigno * p_lisObj )
{
	int								iError;
	unsigned long					ulDato;
	SElemento *						p_elmObj;
	SListaEnterosLargosSinSigno *	p_lisRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_lisRes = SLisIntLssCrear ();
		iError = MemEsInvalida ( p_lisRes );
		/* La generica, no SLisIntLssElemento: esa devuelve el VALOR. */
		p_elmObj = SLisElemento ( p_lisObj->p_lisDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) && ( iError == 0 ) )
		{
			ulDato = SElmEnteroLargoSinSigno ( p_elmObj );
			if ( SLisIntLssInsertarOrdenado ( p_lisRes, ulDato ) != 1 )
			{
				iError = 1;
			}
			p_elmObj = SElmSucesorExt ( p_elmObj, 1 );
		}
		if ( iError == 1 )
		{
			SLisIntLssDestruir ( &p_lisRes );
			ERROR_ESTABLECER ( ERR_GENERAL_OPERATIVO );
		}
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

SListaEnterosLargosSinSigno * SLisIntLssExtraerUnicos ( SListaEnterosLargosSinSigno * p_lisObj )
{
	return ( SLisIntLssExtraerUnicosExt ( p_lisObj, 0 ) );
}

SListaEnterosLargosSinSigno * SLisIntLssExtraerUnicosExt ( SListaEnterosLargosSinSigno * p_lisObj, int iOrdenar )
{
	int								iError;
	unsigned long					ulDato;
	SElemento *						p_elmObj;
	SListaEnterosLargosSinSigno *	p_lisRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_lisRes = SLisIntLssCrear ();
		iError = MemEsInvalida ( p_lisRes );
		/* La generica, no SLisIntLssElemento: esa devuelve el VALOR. */
		p_elmObj = SLisElemento ( p_lisObj->p_lisDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) && ( iError == 0 ) )
		{
			ulDato = SElmEnteroLargoSinSigno ( p_elmObj );
			if ( SLisIntLssExiste ( p_lisRes, ulDato ) == 0 )
			{
				if ( iOrdenar == 0 )
				{
					if ( SLisIntLssInsertar ( p_lisRes, ulDato ) != 1 )
					{
						iError = 1;
					}
				}
				else
				{
					if ( SLisIntLssInsertarOrdenado ( p_lisRes, ulDato ) != 1 )
					{
						iError = 1;
					}
				}
			}
			p_elmObj = SElmSucesorExt ( p_elmObj, 1 );
		}
		if ( iError == 1 )
		{
			SLisIntLssDestruir ( &p_lisRes );
			ERROR_ESTABLECER ( ERR_GENERAL_OPERATIVO );
		}
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

int SLisIntLssTieneRepetidos ( SListaEnterosLargosSinSigno * p_lisObj )
{
	int								iRes;
	int								iError;
	unsigned long					ulDato;
	SElemento *						p_elmObj;
	SListaEnterosLargosSinSigno *	p_lisDistintos;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = 0;
		p_lisDistintos = SLisIntLssCrear ();
		iError = MemEsInvalida ( p_lisDistintos );
		/* La generica, no SLisIntLssElemento: esa devuelve el VALOR. */
		p_elmObj = SLisElemento ( p_lisObj->p_lisDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) && ( iError == 0 ) && ( iRes == 0 ) )
		{
			ulDato = SElmEnteroLargoSinSigno ( p_elmObj );
			if ( SLisIntLssExiste ( p_lisDistintos, ulDato ) == 1 )
			{
				iRes = 1;
			}
			else
			{
				if ( SLisIntLssInsertarOrdenado ( p_lisDistintos, ulDato ) != 1 )
				{
					iError = 1;
				}
			}
			p_elmObj = SElmSucesorExt ( p_elmObj, 1 );
		}
		SLisIntLssDestruir ( &p_lisDistintos );
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


unsigned long SLisIntLssMin ( SListaEnterosLargosSinSigno * p_lisObj )
{
	unsigned long	ulDato;
	unsigned long	ulRes;
	SElemento *		p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		ulRes = ULONG_MAX;
		/* La generica, no SLisIntLssElemento: esa devuelve el VALOR. */
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

unsigned long SLisIntLssMax ( SListaEnterosLargosSinSigno * p_lisObj )
{
	unsigned long	ulDato;
	unsigned long	ulRes;
	SElemento *		p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		ulRes = 0;
		/* La generica, no SLisIntLssElemento: esa devuelve el VALOR. */
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

void SLisIntLssObtenerParametros ( SListaEnterosLargosSinSigno * p_lisObj, unsigned long * p_ulMin, unsigned long * p_ulMax, double * p_dMed )
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
		iNumElems = SLisIntLssNumElementos ( p_lisObj );
		/* La generica, no SLisIntLssElemento: esa devuelve el VALOR. */
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

int SLisIntLssDefinidaPositiva ( SListaEnterosLargosSinSigno * p_lisObj )
{
	unsigned long	ulDato;
	int				iRes;
	SElemento *		p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = 1;
		/* La generica, no SLisIntLssElemento: esa devuelve el VALOR. */
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

/* Copia de los valores, en el mismo orden; NULL si falla alguna copia. */
SListaEnterosLargosSinSigno * SLisIntLssDuplicar ( SListaEnterosLargosSinSigno * p_lisObj )
{
	SListaEnterosLargosSinSigno *	p_lisRes;
	SLista *						p_lisDatos;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_lisDatos = SLisDuplicar ( p_lisObj->p_lisDatos );
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

/* Operaciones con otras listas: delegan en las de SLista, que recorren la
   cadena y no mueven el cursor de la lista de valores. Ver Listas.md. */
int SLisIntLssExistenTodos ( SListaEnterosLargosSinSigno * p_lisObj, SListaEnterosLargosSinSigno * p_lisValores )
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

int SLisIntLssExisteAlguno ( SListaEnterosLargosSinSigno * p_lisObj, SListaEnterosLargosSinSigno * p_lisValores )
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

int SLisIntLssInsertarLista ( SListaEnterosLargosSinSigno * p_lisObj, SListaEnterosLargosSinSigno * p_lisValores )
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

int SLisIntLssConcatenarLista ( SListaEnterosLargosSinSigno * p_lisObj, SListaEnterosLargosSinSigno * p_lisValores )
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

int SLisIntLssInsertarListaDup ( SListaEnterosLargosSinSigno * p_lisObj, SListaEnterosLargosSinSigno * p_lisValores )
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

int SLisIntLssConcatenarListaDup ( SListaEnterosLargosSinSigno * p_lisObj, SListaEnterosLargosSinSigno * p_lisValores )
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

SListaEnterosLargosSinSigno * SLisIntLssExtraerLista ( SListaEnterosLargosSinSigno * p_lisObj, SListaEnterosLargosSinSigno * p_lisValores )
{
	SListaEnterosLargosSinSigno *	p_lisRes;
	SLista *						p_lisDatos;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			p_lisDatos = SLisExtraerLista ( p_lisObj->p_lisDatos, p_lisValores->p_lisDatos );
			p_lisRes = SLisIntLssEncapsular ( p_lisDatos );
			if ( ES_NULO ( p_lisRes ) )
			{
				/* No se pierde lo extraido: vuelve al final de p_lisObj. */
				SLisConcatenarLista ( p_lisObj->p_lisDatos, p_lisDatos );
				SLisDestruir ( &p_lisDatos );
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

/* Destruye todas las apariciones de cada valor de p_lisValores; ver
   SLisEliminarLista. */
int SLisIntLssEliminarLista ( SListaEnterosLargosSinSigno * p_lisObj, SListaEnterosLargosSinSigno * p_lisValores )
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

SListaEnterosLargosSinSigno * SLisIntLssUnion ( SListaEnterosLargosSinSigno * p_lisValores1, SListaEnterosLargosSinSigno * p_lisValores2 )
{
	SListaEnterosLargosSinSigno *	p_lisRes;
	SLista *						p_lisDatos;

	if ( ES_VALIDO ( p_lisValores1 ) )
	{
		if ( ES_VALIDO ( p_lisValores2 ) )
		{
			p_lisDatos = SLisUnion ( p_lisValores1->p_lisDatos, p_lisValores2->p_lisDatos );
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
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

SListaEnterosLargosSinSigno * SLisIntLssInterseccion ( SListaEnterosLargosSinSigno * p_lisValores1, SListaEnterosLargosSinSigno * p_lisValores2 )
{
	SListaEnterosLargosSinSigno *	p_lisRes;
	SLista *						p_lisDatos;

	if ( ES_VALIDO ( p_lisValores1 ) )
	{
		if ( ES_VALIDO ( p_lisValores2 ) )
		{
			p_lisDatos = SLisInterseccion ( p_lisValores1->p_lisDatos, p_lisValores2->p_lisDatos );
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
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

SListaEnterosLargosSinSigno * SLisIntLssDiferencia ( SListaEnterosLargosSinSigno * p_lisValores1, SListaEnterosLargosSinSigno * p_lisValores2 )
{
	SListaEnterosLargosSinSigno *	p_lisRes;
	SLista *						p_lisDatos;

	if ( ES_VALIDO ( p_lisValores1 ) )
	{
		if ( ES_VALIDO ( p_lisValores2 ) )
		{
			p_lisDatos = SLisDiferencia ( p_lisValores1->p_lisDatos, p_lisValores2->p_lisDatos );
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
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}


