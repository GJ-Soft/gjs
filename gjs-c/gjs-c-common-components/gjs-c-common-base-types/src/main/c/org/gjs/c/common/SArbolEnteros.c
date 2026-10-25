#include "SArbolEnteros.h"

#include "TiposBasicosConfig.h"





SArbolEnteros * SArbIntCrear () 
{
	SArbolEnteros * p_arbObj;
	
	p_arbObj = (SArbolEnteros *) MemReservar ( sizeof ( SArbolEnteros ) );
	if ( ES_VALIDO ( p_arbObj ) )
	{
		p_arbObj->p_arbObj = SArbCrear ();
	}
	return ( p_arbObj );
}

void SArbIntDestruir ( SArbolEnteros ** p_p_arbObj )
{
	SArbolEnteros * p_arbObj;
	
	if ( ES_VALIDO ( p_p_arbObj ) )
	{
		p_arbObj = *p_p_arbObj;
		if ( ES_VALIDO ( p_arbObj ) )
		{
			SArbDestruir ( &(p_arbObj->p_arbObj) );
			MemLiberar ( (void **) p_p_arbObj );
		}
	}
}

int SArbIntRaiz ( SArbolEnteros * p_arbObj )
{
	int iRes;

	if ( ES_VALIDO ( p_arbObj ) )
	{
		iRes = SNodEntero ( SArbRaiz ( p_arbObj->p_arbObj ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbIntEstablecerRaiz ( SArbolEnteros * p_arbObj, int iValor )
{
	int 		iRes;
	SNodo *		p_nodObj;

	if ( ES_VALIDO ( p_arbObj ) )
	{
		p_nodObj = SNodCrearEntero ( iValor );	
		if ( SArbEstablecerRaiz ( p_arbObj->p_arbObj, p_nodObj ) == 1 )
		{
			iRes = 1;
		}
		else
		{
			SNodDestruir ( &p_nodObj, 0 );
			iRes = 0;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbIntEstaVacio ( SArbolEnteros * p_arbObj )
{
	int iRes;

	if ( ES_VALIDO ( p_arbObj ) )
	{
		iRes = SArbEstaVacio ( p_arbObj->p_arbObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbIntNiveles ( SArbolEnteros * p_arbObj )
{
	int iNiveles;

	if ( ES_VALIDO ( p_arbObj ) )
	{
		iNiveles = SArbNiveles ( p_arbObj->p_arbObj );
	}
	else
	{
		iNiveles = 0;
	}
	return ( iNiveles );
}

int SArbIntNumNodos ( SArbolEnteros * p_arbObj )
{
	int iNodos;

	if ( ES_VALIDO ( p_arbObj ) )
	{
		iNodos = SArbNumNodos ( p_arbObj->p_arbObj );
	}
	else
	{
		iNodos = 0;
	}
	return ( iNodos );
}

int SArbIntVaciar ( SArbolEnteros * p_arbObj )
{
	int iRes;

	if ( ES_VALIDO ( p_arbObj ) )
	{
		iRes = SArbVaciar ( p_arbObj->p_arbObj );
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

int SArbIntActual ( SArbolEnteros * p_arbObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_arbObj ) )
	{
		iRes = SNodEntero ( SArbActual ( p_arbObj->p_arbObj ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbIntEstActual ( SArbolEnteros * p_arbObj, int iValor )
{
	int 		iRes;

	if ( ES_VALIDO ( p_arbObj ) )
	{
		iRes = SNodEstablecerEntero ( SArbActual ( p_arbObj->p_arbObj ), iValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbIntMoverARaiz ( SArbolEnteros * p_arbObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_arbObj ) )
	{
		iRes = SArbMoverARaiz ( p_arbObj->p_arbObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbIntMoverAPadre ( SArbolEnteros * p_arbObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_arbObj ) )
	{
		iRes = SArbMoverAPadre ( p_arbObj->p_arbObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbIntMoverAHijo ( SArbolEnteros * p_arbObj, int iHijo )
{
	int iRes;
	
	if ( ES_VALIDO ( p_arbObj ) )
	{
		iRes = SArbMoverAHijo ( p_arbObj->p_arbObj, iHijo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbIntMoverAPrimHijo ( SArbolEnteros * p_arbObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_arbObj ) )
	{
		iRes = SArbMoverAPrimHijo ( p_arbObj->p_arbObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbIntMoverAUltHijo ( SArbolEnteros * p_arbObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_arbObj ) )
	{
		iRes = SArbMoverAUltHijo ( p_arbObj->p_arbObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbIntMoverAPrimHermano ( SArbolEnteros * p_arbObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_arbObj ) )
	{
		iRes = SArbMoverAPrimHermano ( p_arbObj->p_arbObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbIntMoverASigHermano ( SArbolEnteros * p_arbObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_arbObj ) )
	{
		iRes = SArbMoverASigHermano ( p_arbObj->p_arbObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbIntMoverAAntHermano ( SArbolEnteros * p_arbObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_arbObj ) )
	{
		iRes = SArbMoverAAntHermano ( p_arbObj->p_arbObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbIntMoverAUltHermano ( SArbolEnteros * p_arbObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_arbObj ) )
	{
		iRes = SArbMoverAUltHermano ( p_arbObj->p_arbObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbIntMoverAPrimPreorden ( SArbolEnteros * p_arbObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_arbObj ) )
	{
		iRes = SArbMoverAPrimPreorden ( p_arbObj->p_arbObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbIntMoverASigPreorden ( SArbolEnteros * p_arbObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_arbObj ) )
	{
		iRes = SArbMoverASigPreorden ( p_arbObj->p_arbObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbIntMoverAPrimPostorden ( SArbolEnteros * p_arbObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_arbObj ) )
	{
		iRes = SArbMoverAPrimPostorden ( p_arbObj->p_arbObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbIntMoverASigPostorden ( SArbolEnteros * p_arbObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_arbObj ) )
	{
		iRes = SArbMoverASigPostorden ( p_arbObj->p_arbObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

void SArbIntDesposicionar ( SArbolEnteros * p_arbObj )
{
	if ( ES_VALIDO ( p_arbObj ) )
	{
		SArbDesposicionar ( p_arbObj->p_arbObj );
	}
}

int	SArbIntEstaPosicionado ( SArbolEnteros * p_arbObj )
{
	int iRes;

	if ( ES_VALIDO ( p_arbObj ) )
	{
		iRes = SArbEstaPosicionado ( p_arbObj->p_arbObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbIntEnraizar ( SArbolEnteros * p_arbObj, int iValor )
{
	SNodo * 	p_nodObj;
	int 		iRes;

	if ( ES_VALIDO ( p_arbObj ) )
	{
		p_nodObj = SNodCrearEntero ( iValor );	
		if ( SArbEnraizar ( p_arbObj->p_arbObj, p_nodObj ) == 1 )
		{
			iRes = 1;
		}
		else
		{
			SNodDestruir ( &p_nodObj, 0 );
			iRes = 0;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbIntVerificar ( SArbolEnteros * p_arbObj, int iCorregir )
{
	int iRes;

	if ( ES_VALIDO ( p_arbObj ) )
	{
		iRes = SArbVerificar ( p_arbObj->p_arbObj, iCorregir );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}




