#include "SArbolBinEnteros.h"

#include "TiposBasicosConfig.h"









SArbolBinEnteros * SArbBinIntCrear () 
{
	SArbolBinEnteros * p_arbbObj;
	
	p_arbbObj = (SArbolBinEnteros *) MemReservar ( sizeof ( SArbolBinEnteros ) );
	if ( ES_VALIDO ( p_arbbObj ) )
	{
		p_arbbObj->p_arbbObj = SArbBinCrear ();
	}
	return ( p_arbbObj );
}

void SArbBinIntDestruir ( SArbolBinEnteros ** p_p_arbbObj )
{
	SArbolBinEnteros * p_arbbObj;
	
	if ( ES_VALIDO ( p_p_arbbObj ) )
	{
		p_arbbObj = *p_p_arbbObj;
		if ( ES_VALIDO ( p_arbbObj ) )
		{
			SArbBinDestruir ( &(p_arbbObj->p_arbbObj) );
			MemLiberar ( (void **) p_p_arbbObj );
		}
	}
}

int SArbBinIntRaiz ( SArbolBinEnteros * p_arbbObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_arbbObj ) )
	{
		iRes = SNodBinEntero ( SArbBinRaiz ( p_arbbObj->p_arbbObj ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbBinIntEstablecerRaiz ( SArbolBinEnteros * p_arbbObj, int iValor )
{
	int 		iRes;
	SNodoBin *	p_nodbObj;

	if ( ES_VALIDO ( p_arbbObj ) )
	{
		p_nodbObj = SNodBinCrearEntero ( iValor );	
		if ( SArbBinEstablecerRaiz ( p_arbbObj->p_arbbObj, p_nodbObj ) == 1 )
		{
			iRes = 1;
		}
		else
		{
			SNodBinDestruir ( &p_nodbObj, 0 );
			iRes = 0;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbBinIntEstaVacio ( SArbolBinEnteros * p_arbbObj )
{
	int iRes;

	if ( ES_VALIDO ( p_arbbObj ) )
	{
		iRes = SArbBinEstaVacio ( p_arbbObj->p_arbbObj );
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

int SArbBinIntNiveles ( SArbolBinEnteros * p_arbbObj )
{
	int iNiveles;

	if ( ES_VALIDO ( p_arbbObj ) )
	{
		iNiveles = SArbBinNiveles ( p_arbbObj->p_arbbObj );
	}
	else
	{
		iNiveles = 0;
	}
	return ( iNiveles );
}

int SArbBinIntNumNodos ( SArbolBinEnteros * p_arbbObj )
{
	int iNodos;

	if ( ES_VALIDO ( p_arbbObj ) )
	{
		iNodos = SArbBinNumNodos ( p_arbbObj->p_arbbObj );
	}
	else
	{
		iNodos = 0;
	}
	return ( iNodos );
}

void SArbBinIntVaciar ( SArbolBinEnteros * p_arbbObj )
{
	if ( ES_VALIDO ( p_arbbObj ) )
	{
		SArbBinVaciar ( p_arbbObj->p_arbbObj );
	}
}

int SArbBinIntActual ( SArbolBinEnteros * p_arbbObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_arbbObj ) )
	{
		iRes = SNodBinEntero ( SArbBinActual ( p_arbbObj->p_arbbObj ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbBinIntEstActual ( SArbolBinEnteros * p_arbbObj, int iValor )
{
	int 		iRes;

	if ( ES_VALIDO ( p_arbbObj ) )
	{
		iRes = SNodBinEstablecerEntero ( SArbBinActual ( p_arbbObj->p_arbbObj ), iValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbBinIntPadre ( SArbolBinEnteros * p_arbbObj )
{
	int iRes;

	if ( ES_VALIDO ( p_arbbObj ) )
	{
		iRes = SNodBinEntero ( SArbBinPadre ( p_arbbObj->p_arbbObj ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbBinIntHijoDer ( SArbolBinEnteros * p_arbbObj )
{
	int iRes;

	if ( ES_VALIDO ( p_arbbObj ) )
	{
		iRes = SNodBinEntero ( SArbBinHijoDer ( p_arbbObj->p_arbbObj ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbBinIntHijoIzq ( SArbolBinEnteros * p_arbbObj )
{
	int iRes;

	if ( ES_VALIDO ( p_arbbObj ) )
	{
		iRes = SNodBinEntero ( SArbBinHijoIzq ( p_arbbObj->p_arbbObj ) );
	}
	else
	{
		iRes = 0;
	}
	return (iRes );
}

int SArbBinIntTienePadre ( SArbolBinEnteros * p_arbbObj )
{
	int iRes;

	if ( ES_VALIDO ( p_arbbObj ) )
	{
		iRes = SArbBinTienePadre ( p_arbbObj->p_arbbObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbBinIntTieneHijos ( SArbolBinEnteros * p_arbbObj )
{
	int iRes;

	if ( ES_VALIDO ( p_arbbObj ) )
	{
		iRes = SArbBinTieneHijos ( p_arbbObj->p_arbbObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbBinIntTieneHermano ( SArbolBinEnteros * p_arbbObj )
{
	int iRes;

	if ( ES_VALIDO ( p_arbbObj ) )
	{
		iRes = SArbBinTieneHermano ( p_arbbObj->p_arbbObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbBinIntEsHijoIzqDelPadre ( SArbolBinEnteros * p_arbbObj )
{
	int iRes;

	if ( ES_VALIDO ( p_arbbObj ) )
	{
		iRes = SArbBinEsHijoIzqDelPadre ( p_arbbObj->p_arbbObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbBinIntEsHijoDerDelPadre ( SArbolBinEnteros * p_arbbObj )
{
	int iRes;

	if ( ES_VALIDO ( p_arbbObj ) )
	{
		iRes = SArbBinEsHijoDerDelPadre ( p_arbbObj->p_arbbObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbBinIntTieneHijoIzq ( SArbolBinEnteros * p_arbbObj )
{
	int iRes;

	if ( ES_VALIDO ( p_arbbObj ) )
	{
		iRes = SArbBinTieneHijoIzq ( p_arbbObj->p_arbbObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbBinIntTieneHijoDer ( SArbolBinEnteros * p_arbbObj )
{
	int iRes;

	if ( ES_VALIDO ( p_arbbObj ) )
	{
		iRes = SArbBinTieneHijoDer ( p_arbbObj->p_arbbObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbBinIntTieneHermanoIzq ( SArbolBinEnteros * p_arbbObj )
{
	int iRes;

	if ( ES_VALIDO ( p_arbbObj ) )
	{
		iRes = SArbBinTieneHermanoIzq ( p_arbbObj->p_arbbObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbBinIntTieneHermanoDer ( SArbolBinEnteros * p_arbbObj )
{
	int iRes;

	if ( ES_VALIDO ( p_arbbObj ) )
	{
		iRes = SArbBinTieneHermanoDer ( p_arbbObj->p_arbbObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbBinIntMoverARaiz ( SArbolBinEnteros * p_arbbObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_arbbObj ) )
	{
		iRes = SArbBinMoverARaiz ( p_arbbObj->p_arbbObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbBinIntMoverAPadre ( SArbolBinEnteros * p_arbbObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_arbbObj ) )
	{
		iRes = SArbBinMoverAPadre ( p_arbbObj->p_arbbObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbBinIntMoverAHijoIzq ( SArbolBinEnteros * p_arbbObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_arbbObj ) )
	{
		iRes = SArbBinMoverAHijoIzq ( p_arbbObj->p_arbbObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbBinIntMoverAHijoDer ( SArbolBinEnteros * p_arbbObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_arbbObj ) )
	{
		iRes = SArbBinMoverAHijoDer ( p_arbbObj->p_arbbObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbBinIntMoverAHermano ( SArbolBinEnteros * p_arbbObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_arbbObj ) )
	{
		iRes = SArbBinMoverAHermano ( p_arbbObj->p_arbbObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbBinIntMoverAPrimPreorden ( SArbolBinEnteros * p_arbbObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_arbbObj ) )
	{
		iRes = SArbBinMoverAPrimPreorden ( p_arbbObj->p_arbbObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbBinIntMoverASigPreorden ( SArbolBinEnteros * p_arbbObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_arbbObj ) )
	{
		iRes = SArbBinMoverASigPreorden ( p_arbbObj->p_arbbObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbBinIntMoverAPrimPostorden ( SArbolBinEnteros * p_arbbObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_arbbObj ) )
	{
		iRes = SArbBinMoverAPrimPostorden ( p_arbbObj->p_arbbObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbBinIntMoverASigPostorden ( SArbolBinEnteros * p_arbbObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_arbbObj ) )
	{
		iRes = SArbBinMoverASigPostorden ( p_arbbObj->p_arbbObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbBinIntMoverAPrimInorden ( SArbolBinEnteros * p_arbbObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_arbbObj ) )
	{
		iRes = SArbBinMoverAPrimInorden ( p_arbbObj->p_arbbObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbBinIntMoverASigInorden ( SArbolBinEnteros * p_arbbObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_arbbObj ) )
	{
		iRes = SArbBinMoverASigInorden ( p_arbbObj->p_arbbObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

void SArbBinIntDesposicionar ( SArbolBinEnteros * p_arbbObj )
{
	if ( ES_VALIDO ( p_arbbObj ) )
	{
		SArbBinDesposicionar ( p_arbbObj->p_arbbObj );
	}
}

int	SArbBinIntEstaPosicionado ( SArbolBinEnteros * p_arbbObj )
{
	int iRes;

	if ( ES_VALIDO ( p_arbbObj ) )
	{
		iRes = SArbBinEstaPosicionado ( p_arbbObj->p_arbbObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbBinIntEnraizar ( SArbolBinEnteros * p_arbbObj, int iValor )
{
	SNodoBin * 	p_nodbObj;
	int 		iRes;

	if ( ES_VALIDO ( p_arbbObj ) )
	{
		p_nodbObj = SNodBinCrearEntero ( iValor );	
		if ( SArbBinEnraizar ( p_arbbObj->p_arbbObj, p_nodbObj ) == 1 )
		{
			iRes = 1;
		}
		else
		{
			SNodBinDestruir ( &p_nodbObj, 0 );
			iRes = 0;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbBinIntVerificar ( SArbolBinEnteros * p_arbbObj, int iCorregir )
{
	int iRes;

	if ( ES_VALIDO ( p_arbbObj ) )
	{
		iRes = SArbBinVerificar ( p_arbbObj->p_arbbObj, iCorregir );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}



