#include "SSecuenciaEnterosLargosSinSigno.h"


#include "TiposBasicosConfig.h"



SSecuenciaEnterosLargosSinSigno * SSecEntLssCrear ()
{
	SSecuenciaEnterosLargosSinSigno * p_secObj;
	
	p_secObj = (SSecuenciaEnterosLargosSinSigno *) MemReservar ( sizeof ( SSecuenciaEnterosLargosSinSigno ) );
	if ( ES_VALIDO ( p_secObj ) )
	{
		p_secObj->p_secDatos = SSecCrear ();
	}
	return ( p_secObj );
}

void SSecEntLssDestruir ( SSecuenciaEnterosLargosSinSigno ** p_p_secObj )
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

int SSecEntLssEsValida ( SSecuenciaEnterosLargosSinSigno * p_secObj )
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

int SSecEntLssEstaVacia ( SSecuenciaEnterosLargosSinSigno * p_secObj )
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

int SSecEntLssNumElementos ( SSecuenciaEnterosLargosSinSigno * p_secObj )
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

unsigned long SSecEntLssElemento ( SSecuenciaEnterosLargosSinSigno * p_secObj, int iElem )
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

int SSecEntLssInsertar ( SSecuenciaEnterosLargosSinSigno * p_secObj, unsigned long ulDato )
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

int SSecEntLssEliminar ( SSecuenciaEnterosLargosSinSigno * p_secObj, int iElem )
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

int SSecEntLssVaciar ( SSecuenciaEnterosLargosSinSigno * p_secObj )
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

int SSecEntLssExiste ( SSecuenciaEnterosLargosSinSigno * p_secObj, unsigned long ulDato )
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

SSecuenciaEnterosLargosSinSigno * SSecEntLssExtraerUnicos ( SSecuenciaEnterosLargosSinSigno * p_secObj )
{
	int									iError;
	unsigned long						ulDato;
	SSecuenciaEnterosLargosSinSigno *	p_secRes;
	SElemento *							p_elmObj;

	if ( ES_VALIDO ( p_secObj ) )
	{
		p_secRes = SSecEntLssCrear ();
		iError = MemEsInvalida ( p_secRes );
		/* Se recorre la CADENA de elementos, no por indice: SSecElemento
		   entra por el extremo mas cercano, asi que un barrido por indice
		   seria cuadratico. Igual que en SListaEnteros. */
		p_elmObj = SSecElemento ( p_secObj->p_secDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) && ( iError == 0 ) )
		{
			ulDato = SElmEnteroLargoSinSigno ( p_elmObj );
			if ( SSecEntLssExiste ( p_secRes, ulDato ) == 0 )
			{
				if ( SSecEntLssInsertar ( p_secRes, ulDato ) != 1 )
				{
					iError = 1;
				}
			}
			p_elmObj = SElmSucesor ( p_elmObj );
		}
		if ( iError == 1 )
		{
			SSecEntLssDestruir ( &p_secRes );
			ERROR_ESTABLECER ( ERR_GENERAL_OPERATIVO );
		}
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

int SSecEntLssTieneRepetidos ( SSecuenciaEnterosLargosSinSigno * p_secObj )
{
	int									iRes;
	int									iError;
	unsigned long						ulDato;
	SSecuenciaEnterosLargosSinSigno *	p_secDistintos;
	SElemento *							p_elmObj;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = 0;
		p_secDistintos = SSecEntLssCrear ();
		iError = MemEsInvalida ( p_secDistintos );
		/* Se recorre la CADENA de elementos, no por indice: SSecElemento
		   entra por el extremo mas cercano, asi que un barrido por indice
		   seria cuadratico. Igual que en SListaEnteros. */
		p_elmObj = SSecElemento ( p_secObj->p_secDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) && ( iError == 0 ) && ( iRes == 0 ) )
		{
			ulDato = SElmEnteroLargoSinSigno ( p_elmObj );
			if ( SSecEntLssExiste ( p_secDistintos, ulDato ) == 1 )
			{
				iRes = 1;
			}
			else
			{
				if ( SSecEntLssInsertar ( p_secDistintos, ulDato ) != 1 )
				{
					iError = 1;
				}
			}
			p_elmObj = SElmSucesor ( p_elmObj );
		}
		SSecEntLssDestruir ( &p_secDistintos );
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

unsigned long SSecEntLssMin ( SSecuenciaEnterosLargosSinSigno * p_secObj )
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

unsigned long SSecEntLssMax ( SSecuenciaEnterosLargosSinSigno * p_secObj )
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

void SSecEntLssObtenerParametros ( SSecuenciaEnterosLargosSinSigno * p_secObj, unsigned long * p_ulMin, unsigned long * p_ulMax, double * p_dMed )
{
	unsigned long	ulDato;
	int				iNumElems;
	SElemento *		p_elmObj;

	if ( ES_VALIDO ( p_secObj ) && ES_VALIDO ( p_ulMin ) && ES_VALIDO ( p_ulMax ) && ES_VALIDO ( p_dMed ) )
	{
		*p_ulMin = ULONG_MAX;
		*p_ulMax = 0;
		*p_dMed = 0.0;
		iNumElems = SSecEntLssNumElementos ( p_secObj );
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

int SSecEntLssDefinidaPositiva ( SSecuenciaEnterosLargosSinSigno * p_secObj )
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
