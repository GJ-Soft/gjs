#include "SListaEnteros.h"

#include "TiposBasicosConfig.h"




SListaEnteros * SLisIntCrear ()
{
	SListaEnteros * p_lisObj;
	
	p_lisObj = (SListaEnteros *) MemReservar ( sizeof ( SListaEnteros ) );
	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_lisObj->p_lisDatos = SLisCrear ();
	}
	return ( p_lisObj );
}

void SLisIntDestruir ( SListaEnteros ** p_p_lisObj )
{
	SListaEnteros * p_lisObj;
	
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

int SLisIntEsValida ( SListaEnteros * p_lisObj )
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

int SLisIntEstaVacia ( SListaEnteros * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLisEstaVacia ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

int SLisIntNumElementos ( SListaEnteros * p_lisObj )
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

int SLisIntElemento ( SListaEnteros * p_lisObj, int iElem )
{
	int			iRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_elmObj = SLisElemento ( p_lisObj->p_lisDatos, iElem );
		if ( ES_VALIDO ( p_elmObj ) )
		{
			iRes = SElmEntero ( p_elmObj );
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

int SLisIntEstablecerElem ( SListaEnteros * p_lisObj, int iPos, int iDato )
{
	int			iRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_elmObj = SLisElemento ( p_lisObj->p_lisDatos, iPos );
		if ( ES_VALIDO ( p_elmObj ) )
		{
			iRes = SElmEscribirEntero ( p_elmObj, iDato );
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

int SLisIntInsertarElem ( SListaEnteros * p_lisObj, int iPosAnt, int iDato )
{
	int			iRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_elmObj = SElmCrearEntero ();
		if ( ES_VALIDO ( p_elmObj ) )
		{
			if ( SElmEscribirEntero ( p_elmObj, iDato ) == 1 )
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

int SLisIntInsertarAlInicio ( SListaEnteros * p_lisObj, int iDato )
{
	return ( SLisIntInsertarElem ( p_lisObj, -1, iDato ) );
}

int SLisIntInsertarAlFinal ( SListaEnteros * p_lisObj, int iDato )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLisIntInsertarElem ( p_lisObj, SLisIntNumElementos ( p_lisObj ), iDato );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SLisIntEliminarElem ( SListaEnteros * p_lisObj, int iElem )
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

int SLisIntVaciar ( SListaEnteros * p_lisObj )
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

int SLisIntPosicion ( SListaEnteros * p_lisObj )
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

int SLisIntActual ( SListaEnteros * p_lisObj )
{
	SElemento *		p_elmObj;
	int				iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_elmObj = ( SElemento * ) SLisActual ( p_lisObj->p_lisDatos );
		if ( ES_VALIDO ( p_elmObj ) )
		{
			iRes = SElmEntero ( p_elmObj );
		}
		else
		{
			ERROR_ESTABLECER( ERR_POSICION_INVALIDA );
			iRes = 0;
		}
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

void SLisIntInicio ( SListaEnteros * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLisInicio ( p_lisObj->p_lisDatos );
	}
}

void SLisIntFinal ( SListaEnteros * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLisFinal ( p_lisObj->p_lisDatos );
	}
}

void SLisIntSiguiente ( SListaEnteros * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLisSiguiente ( p_lisObj->p_lisDatos );
	}
}

void SLisIntAnterior ( SListaEnteros * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLisAnterior ( p_lisObj->p_lisDatos );
	}
}

void SLisIntMoverA ( SListaEnteros * p_lisObj, int iElem )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLisMoverA ( p_lisObj->p_lisDatos, iElem );
	}
}

void SLisIntDeposicionar ( SListaEnteros * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLisDeposicionar ( p_lisObj->p_lisDatos );
	}
}

int SLisIntEsNulo ( SListaEnteros * p_lisObj )
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

int SLisIntEstaEnFinal ( SListaEnteros * p_lisObj )
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

int SLisIntEstaEnInicio ( SListaEnteros * p_lisObj )
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

int SLisIntInsertar ( SListaEnteros * p_lisObj, int iDato )
{
	return ( SLisIntInsertarDetras ( p_lisObj, iDato ) );
}

int SLisIntInsertarOrdenado ( SListaEnteros * p_lisObj, int iDato )
{
	int			iRes;
	int			iElem;
	int			iNumElems;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = 0;
		iNumElems = SLisIntNumElementos ( p_lisObj );
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
			while ( ES_VALIDO ( p_elmObj ) && ( iDato >= SElmEntero ( p_elmObj ) ) )
			{
				iElem = iElem + 1;
				p_elmObj = SElmSucesor ( p_elmObj );
			}
			iRes = SLisIntInsertarElem ( p_lisObj, iElem - 1, iDato );
		}
		else
		{
			iRes = SLisIntInsertar ( p_lisObj, iDato );
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisIntInsertarDelante ( SListaEnteros * p_lisObj, int iDato )
{
	int			iRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_elmObj = SElmCrearEntero ();
		if ( ES_VALIDO ( p_elmObj ) )
		{
			if ( SElmEscribirEntero ( p_elmObj, iDato ) == 1 )
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

int SLisIntInsertarDetras ( SListaEnteros * p_lisObj, int iDato )
{
	int			iRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_elmObj = SElmCrearEntero ();
		if ( ES_VALIDO ( p_elmObj ) )
		{
			if ( SElmEscribirEntero ( p_elmObj, iDato ) == 1 )
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

int SLisIntEliminar ( SListaEnteros * p_lisObj )
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

int SLisIntExiste ( SListaEnteros * p_lisObj, int iDato )
{
	int 		iRes;
	SElemento * p_elmObj;

	if ( ES_VALIDO ( p_lisObj )  ) 
	{
		iRes = 0;
		/* La generica, no SLisIntElemento: esa devuelve el VALOR. */
		p_elmObj = SLisElemento ( p_lisObj->p_lisDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) && ( iRes == 0 ) )
		{
			if ( SElmEntero ( p_elmObj ) == iDato )
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

int SLisIntBuscar ( SListaEnteros * p_lisObj, int iDato )
{
	int 		iRes;
	int			iElem;
	SElemento * p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iElem = 0;
		iRes = -1;
		/* La generica, no SLisIntElemento: esa devuelve el VALOR. */
		p_elmObj = SLisElemento ( p_lisObj->p_lisDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) && ( iRes == -1 ) )
		{
			if ( SElmEntero ( p_elmObj ) == iDato )
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

int SLisIntEstaOrdenada ( SListaEnteros * p_lisObj )
{
	int	 		iDatoAnt;
	int 		iDato;
	SElemento * p_elmObj;
	int			iRes;		

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = 1;
		iDatoAnt = INT_MIN;
		/* La generica, no SLisIntElemento: esa devuelve el VALOR. */
		p_elmObj = SLisElemento ( p_lisObj->p_lisDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) && ( iRes == 1 ) )
		{
			iDato = SElmEntero ( p_elmObj );
			if ( iDatoAnt > iDato )
			{
				iRes = 0;
			}
			iDatoAnt = iDato;
			p_elmObj = SElmSucesorExt ( p_elmObj, 1 );
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SListaEnteros * SLisIntOrdenar ( SListaEnteros * p_lisObj )
{
	int 			iError;
	int 			iDato;
	SElemento * 	p_elmObj;
	SListaEnteros *	p_lisRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_lisRes = SLisIntCrear ();
		iError = MemEsInvalida ( p_lisRes );
		/* La generica, no SLisIntElemento: esa devuelve el VALOR. */
		p_elmObj = SLisElemento ( p_lisObj->p_lisDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) && ( iError == 0 ) )
		{
			iDato = SElmEntero ( p_elmObj );
			if ( SLisIntInsertarOrdenado ( p_lisRes, iDato ) != 1 )
			{
				iError = 1;
			}
			p_elmObj = SElmSucesorExt ( p_elmObj, 1 );
		}
		if ( iError == 1 )
		{
			SLisIntDestruir ( &p_lisRes );
			ERROR_ESTABLECER ( ERR_GENERAL_OPERATIVO );
		}
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

SListaEnteros * SLisIntExtraerUnicos ( SListaEnteros * p_lisObj )
{
	return ( SLisIntExtraerUnicosExt ( p_lisObj, 0 ) );
}

SListaEnteros * SLisIntExtraerUnicosExt ( SListaEnteros * p_lisObj, int iOrdenar )
{
	int 			iError;
	int 			iDato;
	SElemento * 	p_elmObj;
	SListaEnteros *	p_lisRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_lisRes = SLisIntCrear ();
		iError = MemEsInvalida ( p_lisRes );
		/* La generica, no SLisIntElemento: esa devuelve el VALOR. */
		p_elmObj = SLisElemento ( p_lisObj->p_lisDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) && ( iError == 0 ) )
		{
			iDato = SElmEntero ( p_elmObj );
			if ( SLisIntExiste ( p_lisRes, iDato ) == 0 )
			{
				if ( iOrdenar == 0 )
				{
					if ( SLisIntInsertar ( p_lisRes, iDato ) != 1 )
					{
						iError = 1;
					}
				}
				else
				{
					if ( SLisIntInsertarOrdenado ( p_lisRes, iDato ) != 1 )
					{
						iError = 1;
					}
				}
			}
			p_elmObj = SElmSucesorExt ( p_elmObj, 1 );
		}
		if ( iError == 1 )
		{
			SLisIntDestruir ( &p_lisRes );
			ERROR_ESTABLECER ( ERR_GENERAL_OPERATIVO );
		}
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

int SLisIntTieneRepetidos ( SListaEnteros * p_lisObj )
{
	int 			iRes;
	int 			iError;
	int 			iDato;
	SElemento * 	p_elmObj;
	SListaEnteros *	p_lisDistintos;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = 0;
		p_lisDistintos = SLisIntCrear ();
		iError = MemEsInvalida ( p_lisDistintos );
		/* La generica, no SLisIntElemento: esa devuelve el VALOR. */
		p_elmObj = SLisElemento ( p_lisObj->p_lisDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) && ( iError == 0 ) && ( iRes == 0 ) )
		{
			iDato = SElmEntero ( p_elmObj );
			if ( SLisIntExiste ( p_lisDistintos, iDato ) == 1 )
			{
				iRes = 1;
			}
			else
			{
				if ( SLisIntInsertarOrdenado ( p_lisDistintos, iDato ) != 1 )
				{
					iError = 1;
				}
			}
			p_elmObj = SElmSucesorExt ( p_elmObj, 1 );
		}
		SLisIntDestruir ( &p_lisDistintos );
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


int SLisIntMin ( SListaEnteros * p_lisObj )
{
	int 			iDato;
	int				iRes;
	SElemento * 	p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = INT_MAX;
		/* La generica, no SLisIntElemento: esa devuelve el VALOR. */
		p_elmObj = SLisElemento ( p_lisObj->p_lisDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) )
		{
			iDato = SElmEntero ( p_elmObj );
			if ( iDato < iRes )
			{
				iRes = iDato;
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

int SLisIntMax ( SListaEnteros * p_lisObj )
{
	int 			iDato;
	int				iRes;
	SElemento * 	p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = INT_MIN;
		/* La generica, no SLisIntElemento: esa devuelve el VALOR. */
		p_elmObj = SLisElemento ( p_lisObj->p_lisDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) )
		{
			iDato = SElmEntero ( p_elmObj );
			if ( iDato > iRes )
			{
				iRes = iDato;
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

void SLisIntObtenerParametros ( SListaEnteros * p_lisObj, int * p_iMin, int * p_iMax, double * p_dMed )
{
	int 			iDato;
	int				iNumElems;
	SElemento * 	p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_iMin ) && ES_VALIDO ( p_iMax ) && ES_VALIDO ( p_dMed ) )
	{
		*p_iMin = INT_MAX;
		*p_iMax = INT_MIN;
		*p_dMed = 0.0;
		/* O(1): la lista lleva la cuenta, no hay que recorrerla otra vez. */
		iNumElems = SLisIntNumElementos ( p_lisObj );
		/* La generica, no SLisIntElemento: esa devuelve el VALOR. */
		p_elmObj = SLisElemento ( p_lisObj->p_lisDatos, 0 );
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

int SLisIntDefinidaPositiva ( SListaEnteros * p_lisObj )
{
	int 			iDato;
	int				iRes;
	SElemento * 	p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = 1;
		/* La generica, no SLisIntElemento: esa devuelve el VALOR. */
		p_elmObj = SLisElemento ( p_lisObj->p_lisDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) && ( iRes == 1 ) )
		{
			iDato = SElmEntero ( p_elmObj );
			if ( iDato <= 0 )
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

int SLisIntSemidefinidaPositiva ( SListaEnteros * p_lisObj )
{
	int 			iDato;
	int				iRes;
	SElemento * 	p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = 1;
		/* La generica, no SLisIntElemento: esa devuelve el VALOR. */
		p_elmObj = SLisElemento ( p_lisObj->p_lisDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) && ( iRes == 1 ) )
		{
			iDato = SElmEntero ( p_elmObj );
			if ( iDato < 0 )
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



