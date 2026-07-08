#include "SPilaLiterales.h"

#include "TiposBasicosConfig.h"



SPilaLiterales * SPilLitCrear ()
{
	SPilaLiterales * p_pilObj;
	
	p_pilObj = (SPilaLiterales *) MemReservar ( sizeof ( SPilaLiterales ) );
	if ( ES_VALIDO ( p_pilObj ) )
	{
		p_pilObj->p_pilDatos = SPilpCrear ();
	}
	return ( p_pilObj );
}

void SPilLitDestruir ( SPilaLiterales ** p_p_pilObj )
{
	SPilaLiterales * p_pilObj;
	
	if ( ES_VALIDO ( p_p_pilObj ) )
	{
		p_pilObj = *p_p_pilObj;

		if ( ES_VALIDO ( p_pilObj ) )
		{
			SPilpDestruir ( &(p_pilObj->p_pilDatos), 1 );
			MemLiberar ( (void **) p_p_pilObj );
		}
	}
}

int SPilLitEsValida ( SPilaLiterales * p_pilObj )
{
	int iRes;

	if ( ES_VALIDO ( p_pilObj ) )
	{
		iRes = SPilpEsValida ( p_pilObj->p_pilDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SPilLitEstaVacia ( SPilaLiterales * p_pilObj )
{
	int iRes;

	if ( ES_VALIDO ( p_pilObj ) )
	{
		iRes = SPilpEstaVacia ( p_pilObj->p_pilDatos );
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

int SPilLitNumElementos ( SPilaLiterales * p_pilObj )
{
	int iRes;

	if ( ES_VALIDO ( p_pilObj ) )
	{
		iRes = SPilpNumElementos ( p_pilObj->p_pilDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

char * SPilLitPrimero ( SPilaLiterales * p_pilObj )
{
	char *	p_cRes;

	if ( ES_VALIDO ( p_pilObj ) )
	{
		p_cRes = (char *) SPilpPrimero ( p_pilObj->p_pilDatos );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

char * SPilLitDesapilar ( SPilaLiterales * p_pilObj )
{
	char * p_cRes;

	if ( ES_VALIDO ( p_pilObj ) )
	{
		p_cRes = (char *) SPilpDesapilar ( p_pilObj->p_pilDatos );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SPilLitApilar ( SPilaLiterales * p_pilObj, char * p_cDato )
{
	int		iRes;
	char *	p_cElem;

	if ( ES_VALIDO ( p_pilObj ) && ES_VALIDO ( p_cDato ) )
	{
		p_cElem = CadDuplicar ( p_cDato );
		if ( ES_VALIDO ( p_cElem ) )
		{
			iRes = SPilpApilar ( p_pilObj->p_pilDatos, (byte *) p_cElem );
			if ( iRes != 1 )
			{
				MemLiberar ( (void **) &p_cElem );
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

int SPilLitEliminarPrimero ( SPilaLiterales * p_pilObj )
{
	int iRes;

	if ( ES_VALIDO ( p_pilObj ) )
	{
		iRes = SPilpEliminarPrimero ( p_pilObj->p_pilDatos );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SPilLitVaciar ( SPilaLiterales * p_pilObj )
{
	int iRes;

	if ( ES_VALIDO ( p_pilObj ) )
	{
		iRes = SPilpVaciar ( p_pilObj->p_pilDatos, 1 );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

