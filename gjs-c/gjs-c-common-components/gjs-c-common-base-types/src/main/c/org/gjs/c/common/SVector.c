#include "SVector.h"


#include "TiposBasicosConfig.h"




SVector * SVecCrear ( int iNumElementos )
{
	SVector * p_vecObj;
	
	if ( iNumElementos > 0 )
	{
		p_vecObj = (SVector *) MemReservar ( sizeof ( SVector ) );
		if ( ES_VALIDO ( p_vecObj ) )
		{
			p_vecObj->iNumElementos = iNumElementos;
			p_vecObj->p_p_conElementos = (SContenido **) MemReservar ( iNumElementos * sizeof ( SContenido * ) );
			if ( ES_NULO ( p_vecObj->p_p_conElementos ) )
			{
				MemLiberar ( (void **) &p_vecObj );
			}
		}
	}
	else
	{
		p_vecObj = NULL;
	}
	return ( p_vecObj );
}

void SVecDestruir ( SVector ** p_p_vecObj )
{
	SVector *	p_vecObj;
	if ( ES_VALIDO ( p_p_vecObj ) )
	{
		p_vecObj = *p_p_vecObj;

		if ( ES_VALIDO ( p_vecObj ) )
		{
			SVecLimpiar ( p_vecObj );
			MemLiberar ( (void **) &(p_vecObj->p_p_conElementos) );
			MemLiberar ( (void **) p_p_vecObj );
		}
	}
}

int SVecEsValido ( SVector * p_vecObj )
{
	int iRes;

	if ( ES_VALIDO ( p_vecObj ) )
	{
		if ( ( p_vecObj->iNumElementos > 0 ) && ES_VALIDO ( p_vecObj->p_p_conElementos ) )
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

int SVecNumElementos ( SVector * p_vecObj )
{
	int iRes;

	if ( ES_VALIDO ( p_vecObj ) )
	{
		iRes = p_vecObj->iNumElementos;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SContenido * SVecElemento ( SVector * p_vecObj, int iElem )
{
	SContenido * p_conRes;

	if ( SVecEsValido ( p_vecObj ) == 1 )
	{
		if ( ( iElem >= 0 ) && ( iElem < p_vecObj->iNumElementos ) )
		{
			p_conRes = p_vecObj->p_p_conElementos [ iElem ];
		}
		else
		{
			p_conRes = NULL;
		}
	}
	else
	{
		p_conRes = NULL;
	}
	return ( p_conRes );
}

int SVecAsignar ( SVector * p_vecObj, int iElem, SContenido * p_conObj )
{
	int iRes;

	if ( SVecEsValido ( p_vecObj ) == 1 )
	{
		if ( ( iElem >= 0 ) && ( iElem < p_vecObj->iNumElementos ) )
		{
			SConDestruir ( &(p_vecObj->p_p_conElementos [ iElem ]) );
			p_vecObj->p_p_conElementos [ iElem ] = p_conObj;
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

int SVecLimpiarElemento ( SVector * p_vecObj, int iElem )
{
	int iRes;

	if ( SVecEsValido ( p_vecObj ) == 1 )
	{
		if ( ( iElem >= 0 ) && ( iElem < p_vecObj->iNumElementos ) )
		{
			SConDestruir ( &(p_vecObj->p_p_conElementos [ iElem ]) );
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

int SVecLimpiar ( SVector * p_vecObj )
{
	int iRes;
	int	iElem;
	
	if ( SVecEsValido ( p_vecObj ) == 1 )
	{
		for ( iElem = 0; iElem < p_vecObj->iNumElementos; iElem = iElem + 1 )
		{
			SConDestruir ( &(p_vecObj->p_p_conElementos [ iElem ]) );
		}

		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

