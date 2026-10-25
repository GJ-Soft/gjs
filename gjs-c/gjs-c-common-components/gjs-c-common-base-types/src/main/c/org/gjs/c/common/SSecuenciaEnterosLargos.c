#include "SSecuenciaEnterosLargos.h"

#include "TiposBasicosConfig.h"



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


