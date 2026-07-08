#include "SVectorPtr.h"


#include "TiposBasicosConfig.h"




SVectorPtr * SVecpCrear ( int iNumElementos )
{
	SVectorPtr * p_vecObj;
	
	if ( iNumElementos > 0 )
	{
		p_vecObj = (SVectorPtr *) MemReservar ( sizeof ( SVectorPtr ) );
		if ( ES_VALIDO ( p_vecObj ) )
		{
			p_vecObj->iNumElementos = iNumElementos;
			p_vecObj->p_p_byElementos = (byte **) MemReservar ( iNumElementos * sizeof ( byte * ) );
			p_vecObj->iLiberar = 0;
			if ( ES_NULO ( p_vecObj->p_p_byElementos ) )
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

void SVecpDestruir ( SVectorPtr ** p_p_vecObj )
{
	SVectorPtr *	p_vecObj;
	if ( ES_VALIDO ( p_p_vecObj ) )
	{
		p_vecObj = *p_p_vecObj;

		if ( ES_VALIDO ( p_vecObj ) )
		{
			SVecpLimpiar ( p_vecObj );
			MemLiberar ( (void **) &(p_vecObj->p_p_byElementos) );
			MemLiberar ( (void **) p_p_vecObj );
		}
	}
}

int SVecpEsValido ( SVectorPtr * p_vecObj )
{
	int iRes;

	if ( ES_VALIDO ( p_vecObj ) )
	{
		if ( ( p_vecObj->iNumElementos > 0 ) && ES_VALIDO ( p_vecObj->p_p_byElementos ) )
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

int SVecpNumElementos ( SVectorPtr * p_vecObj )
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

byte * SVecpElemento ( SVectorPtr * p_vecObj, int iElem )
{
	byte * p_byRes;

	if ( SVecpEsValido ( p_vecObj ) == 1 )
	{
		if ( ( iElem >= 0 ) && ( iElem < p_vecObj->iNumElementos ) )
		{
			p_byRes = p_vecObj->p_p_byElementos [ iElem ];
		}
		else
		{
			p_byRes = NULL;
		}
	}
	else
	{
		p_byRes = NULL;
	}
	return ( p_byRes );
}

int SVecpAsignar ( SVectorPtr * p_vecObj, int iElem, byte * p_byObj )
{
	int iRes;

	if ( SVecpEsValido ( p_vecObj ) == 1 )
	{
		if ( ( iElem >= 0 ) && ( iElem < p_vecObj->iNumElementos ) )
		{
			if ( p_vecObj->iLiberar == 1 )
			{
				MemLiberar ( (void **) &(p_vecObj->p_p_byElementos [ iElem ]) );
			}
			p_vecObj->p_p_byElementos [ iElem ] = p_byObj;
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

int SVecpLimpiarElemento ( SVectorPtr * p_vecObj, int iElem )
{
	int iRes;

	if ( SVecpEsValido ( p_vecObj ) == 1 )
	{
		if ( ( iElem >= 0 ) && ( iElem < p_vecObj->iNumElementos ) )
		{
			if ( p_vecObj->iLiberar == 1 )
			{
				MemLiberar ( (void **) &(p_vecObj->p_p_byElementos [ iElem ]) );
			}
			p_vecObj->p_p_byElementos [ iElem ] = NULL;
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

int SVecpLimpiar ( SVectorPtr * p_vecObj )
{
	int iRes;
	int	iElem;
	
	if ( SVecpEsValido ( p_vecObj ) == 1 )
	{
		for ( iElem = 0; iElem < p_vecObj->iNumElementos; iElem = iElem + 1 )
		{
			if ( p_vecObj->iLiberar == 1 )
			{
				MemLiberar ( (void **) &(p_vecObj->p_p_byElementos [ iElem ]) );
			}
		}

		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int	SVecpLiberacionMemoriaActivada ( SVectorPtr * p_vecObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_vecObj ) )
	{
		iRes = p_vecObj->iLiberar;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

void SVecpActivarLiberacionMemoria ( SVectorPtr * p_vecObj )
{
	if ( ES_VALIDO ( p_vecObj ) )
	{
		p_vecObj->iLiberar = 1;
	}
}

void SVecpDesactivarLiberacionMemoria ( SVectorPtr * p_vecObj )
{
	if ( ES_VALIDO ( p_vecObj ) )
	{
		p_vecObj->iLiberar = 0;
	}
}
