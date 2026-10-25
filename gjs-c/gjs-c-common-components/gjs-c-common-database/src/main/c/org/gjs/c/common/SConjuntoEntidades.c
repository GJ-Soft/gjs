#include "SConjuntoEntidades.h"
          
#include "TiposBaseDatosConfig.h"


static int _SEntComparar ( void * p_vVal1, void * p_vVal2 )
{
    int 		iRes;
    SEntidad * 	p_entVal1 = (SEntidad *) p_vVal1;
    SEntidad * 	p_entVal2 = (SEntidad *) p_vVal2;
    iRes = SEntComparar ( p_entVal1, p_entVal2 );
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


SConjuntoEntidades * SCnjEntCrear ()
{
	SConjuntoEntidades * p_cnjObj;
	
	p_cnjObj = (SConjuntoEntidades *) MemReservar ( sizeof ( SConjuntoEntidades ) );
	if ( ES_VALIDO ( p_cnjObj ) )
	{
		p_cnjObj->p_cnjDatos = SCnjpCrear ( _SEntComparar );
		SCnjpDesactivarLiberacionMemoria ( p_cnjObj->p_cnjDatos );
	}
	return ( p_cnjObj );
}

void SCnjEntDestruir ( SConjuntoEntidades ** p_p_cnjObj )
{
	SConjuntoEntidades * p_cnjObj;
	
	if ( ES_VALIDO ( p_p_cnjObj ) )
	{
		p_cnjObj = *p_p_cnjObj;

		if ( ES_VALIDO ( p_cnjObj ) )
		{
			SCnjEntVaciar ( p_cnjObj );
			SCnjpDestruir ( &(p_cnjObj->p_cnjDatos) );
			MemLiberar ( (void **) p_p_cnjObj );
		}
	}
}

int SCnjEntEsValido ( SConjuntoEntidades * p_cnjObj )
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

int SCnjEntEstaVacio ( SConjuntoEntidades * p_cnjObj )
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

int SCnjEntNumElementos ( SConjuntoEntidades * p_cnjObj )
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

SEntidad * SCnjEntElemento ( SConjuntoEntidades * p_cnjObj, int iElem )
{
	SEntidad *	p_cRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		p_cRes = (SEntidad *) SCnjpElemento ( p_cnjObj->p_cnjDatos, iElem );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

SEntidad * SCnjEntPrimero ( SConjuntoEntidades * p_cnjObj )
{
	SEntidad * p_cRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		p_cRes = (SEntidad *) SCnjpPrimero ( p_cnjObj->p_cnjDatos );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

SEntidad * SCnjEntUltimo ( SConjuntoEntidades * p_cnjObj )
{
	SEntidad * p_cRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		p_cRes = (SEntidad *) SCnjpUltimo ( p_cnjObj->p_cnjDatos );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SCnjEntPosicion ( SConjuntoEntidades * p_cnjObj, SEntidad * p_entDato )
{
	int iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		iRes = SCnjpPosicion ( p_cnjObj->p_cnjDatos, (byte *) p_entDato );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SCnjEntInsertar ( SConjuntoEntidades * p_cnjObj, SEntidad * p_entDato )
{
	int			iRes;

	if ( ES_VALIDO ( p_cnjObj ) && ES_VALIDO ( p_entDato ) )
	{
		iRes = SCnjpInsertarElem ( p_cnjObj->p_cnjDatos, (byte *) p_entDato );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SCnjEntEliminar ( SConjuntoEntidades * p_cnjObj, int iElem )
{
	int 		iRes;
	SEntidad * 	p_entObj;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		p_entObj = SCnjEntElemento ( p_cnjObj, iElem );
		if ( ES_VALIDO ( p_entObj ) )
		{
			iRes = SCnjpEliminarElem ( p_cnjObj->p_cnjDatos, iElem );
			if ( iRes == 1 )
			{
				SEntDestruir ( &p_entObj );
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

SEntidad * SCnjEntExtraer ( SConjuntoEntidades * p_cnjObj, int iElem )
{
	SEntidad * 	p_entRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		p_entRes = SCnjEntElemento ( p_cnjObj, iElem );
		if ( ES_VALIDO ( p_entRes ) )
		{
			if ( SCnjpEliminarElem ( p_cnjObj->p_cnjDatos, iElem ) != 1 )
			{
				p_entRes = NULL;
			}
		}
	}
	else
	{
		p_entRes = NULL;
	}
	return ( p_entRes );
}

int SCnjEntVaciar ( SConjuntoEntidades * p_cnjObj )
{
	int 		iRes;
	SEntidad * 	p_entObj;
	int			iNumElems;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		iNumElems = SCnjEntNumElementos ( p_cnjObj );
		for ( int iElem = 0; iElem < iNumElems; iElem = iElem + 1 )
		{
			p_entObj = SCnjEntElemento ( p_cnjObj, iElem );
			SEntDestruir ( &p_entObj );
		}
		iRes = SCnjpVaciar ( p_cnjObj->p_cnjDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCnjEntExiste ( SConjuntoEntidades * p_cnjObj, SEntidad * p_entDato )
{
	int iRes;

	if ( ES_VALIDO ( p_cnjObj ) ) 
	{
		iRes = SCnjpExiste ( p_cnjObj->p_cnjDatos, (byte *) p_entDato );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCnjEntBuscar ( SConjuntoEntidades * p_cnjObj, SEntidad * p_entDato )
{
	int iRes;
	
	if ( ES_VALIDO ( p_cnjObj ) ) 
	{
		iRes = SCnjpBuscar ( p_cnjObj->p_cnjDatos, (byte *) p_entDato );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SCnjEntExisteId ( SConjuntoEntidades * p_cnjObj, SId * p_idEntidad )
{
	int iRes;
	
	if ( ES_VALIDO ( p_idEntidad ) ) 
	{
		iRes = SCnjEntExisteValorId ( p_cnjObj, SIdValor ( p_idEntidad ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );	
}

int SCnjEntExisteValorId ( SConjuntoEntidades * p_cnjObj, unsigned long ulId )
{
	int 		iRes;
	SEntidad * 	p_entRef;
	
	if ( ES_VALIDO ( p_cnjObj ) && ( ulId > 0 ) ) 
	{
		p_entRef = SEntCrear ( ulId );
		iRes = SCnjEntExiste ( p_cnjObj, p_entRef );
		SEntDestruir ( &p_entRef );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );	
}

int SCnjEntBuscarId ( SConjuntoEntidades * p_cnjObj, SId * p_idEntidad )
{
	int iRes;
	
	if ( ES_VALIDO ( p_idEntidad ) ) 
	{
		iRes = SCnjEntBuscarValorId ( p_cnjObj, SIdValor ( p_idEntidad ) );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );	
}

int SCnjEntBuscarValorId ( SConjuntoEntidades * p_cnjObj, unsigned long ulId )
{
	int 		iRes;
	SEntidad * 	p_entRef;
	
	if ( ES_VALIDO ( p_cnjObj ) && ( ulId > 0 ) ) 
	{
		p_entRef = SEntCrear ( ulId );
		iRes = SCnjEntBuscar ( p_cnjObj, p_entRef );
		SEntDestruir ( &p_entRef );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );	
}
