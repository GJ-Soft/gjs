#include "SConjuntoLiterales.h"
          
#include "TiposBasicosConfig.h"


int _CadComparar ( void * p_vVal1, void * p_vVal2 )
{
    int 	iRes;
    char * 	p_cVal1 = (char *) p_vVal1;
    char * 	p_cVal2 = (char *) p_vVal2;
    iRes = CadComparar ( p_cVal1, p_cVal2 );
	if ( iRes == COMP_MENOR ) 
	{
		iRes = -1;
	}
	else if ( iRes == COMP_MAYOR ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
    return ( iRes );
}


SConjuntoLiterales * SCnjLitCrear ()
{
	SConjuntoLiterales * p_cnjObj;
	
	p_cnjObj = (SConjuntoLiterales *) MemReservar ( sizeof ( SConjuntoLiterales ) );
	if ( ES_VALIDO ( p_cnjObj ) )
	{
		p_cnjObj->p_cnjDatos = SCnjpCrear ( _CadComparar );
		SCnjpActivarLiberacionMemoria ( p_cnjObj->p_cnjDatos );
	}
	return ( p_cnjObj );
}

void SCnjLitDestruir ( SConjuntoLiterales ** p_p_cnjObj )
{
	SConjuntoLiterales * p_cnjObj;
	
	if ( ES_VALIDO ( p_p_cnjObj ) )
	{
		p_cnjObj = *p_p_cnjObj;

		if ( ES_VALIDO ( p_cnjObj ) )
		{
			SCnjpDestruir ( &(p_cnjObj->p_cnjDatos) );
			MemLiberar ( (void **) p_p_cnjObj );
		}
	}
}

int SCnjLitEsValido ( SConjuntoLiterales * p_cnjObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		iRes = SCnjpEsValido ( p_cnjObj->p_cnjDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCnjLitEstaVacio ( SConjuntoLiterales * p_cnjObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		iRes = SCnjpEstaVacio ( p_cnjObj->p_cnjDatos );
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

int SCnjLitNumElementos ( SConjuntoLiterales * p_cnjObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		iRes = SCnjpNumElementos ( p_cnjObj->p_cnjDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

char * SCnjLitElemento ( SConjuntoLiterales * p_cnjObj, int iElem )
{
	char *	p_cRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		p_cRes = (char *) SCnjpElemento ( p_cnjObj->p_cnjDatos, iElem );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SCnjLitInsertar ( SConjuntoLiterales * p_cnjObj, const char * p_cDato )
{
	int		iRes;
	char *	p_cElem;

	if ( ES_VALIDO ( p_cnjObj ) && ES_VALIDO ( p_cDato ) )
	{
		p_cElem = CadDuplicar ( p_cDato );
		if ( ES_VALIDO ( p_cElem ) )
		{
			iRes = SCnjpInsertarElem ( p_cnjObj->p_cnjDatos, (byte *) p_cElem );
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

int SCnjLitEliminar ( SConjuntoLiterales * p_cnjObj, int iElem )
{
	int iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		iRes = SCnjpEliminarElem ( p_cnjObj->p_cnjDatos, iElem );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCnjLitVaciar ( SConjuntoLiterales * p_cnjObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		iRes = SCnjpVaciar ( p_cnjObj->p_cnjDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCnjLitExiste ( SConjuntoLiterales * p_cnjObj, const char * p_cDato )
{
	int iRes;

	if ( ES_VALIDO ( p_cnjObj ) ) 
	{
		iRes = SCnjpExiste ( p_cnjObj->p_cnjDatos, (byte *) p_cDato );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCnjLitBuscar ( SConjuntoLiterales * p_cnjObj, const char * p_cDato )
{
	int iRes;
	
	if ( ES_VALIDO ( p_cnjObj ) ) 
	{
		iRes = SCnjpBuscar ( p_cnjObj->p_cnjDatos, (byte *) p_cDato );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}
