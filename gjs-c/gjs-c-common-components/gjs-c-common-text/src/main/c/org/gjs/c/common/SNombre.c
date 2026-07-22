/******************************************************************************/
/*                                 SNombre.cpp                                */
/*----------------------------------------------------------------------------*/
/* Librería:  Texto                                                           */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#include "SNombre.h"
#include "Cadenas.h"

#include "TextoConfig.h"


SNombre * SNomCrearDef ()
{
	return ( SNomCrear ( NOM_MAX_TAM_DEF ) );
}

SNombre * SNomCrear ( int iMaxTam )
{
	SNombre * p_nomObj;
	
	if ( iMaxTam > 0 )
	{
		p_nomObj = (SNombre *) MemReservar ( sizeof ( SNombre ) );
		if ( ES_VALIDO ( p_nomObj ) )
		{
			p_nomObj->p_cadValor = SCadCrear ( iMaxTam );
		}
	}
	else
	{
		p_nomObj = NULL;
	}
	return ( p_nomObj );
}


void SNomDestruir ( SNombre ** p_p_nomObj )
{
	SNombre * p_nomObj;
	
	if ( ES_VALIDO ( p_p_nomObj ) )
	{
		p_nomObj = *p_p_nomObj;

		if ( ES_VALIDO ( p_nomObj ) )
		{
			SCadDestruir ( &(p_nomObj->p_cadValor) );
			MemLiberar ( (void **) p_p_nomObj );
		}
	}
}

int SNomMaxLongitud ( SNombre * p_nomObj )
{
	int iRes;

	if ( ES_VALIDO ( p_nomObj ) )
	{
		iRes = SCadMaxTam ( p_nomObj->p_cadValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNomLongitud ( SNombre * p_nomObj )
{
	int iRes;

	if ( ES_VALIDO ( p_nomObj ) )
	{
		iRes = SCadLongitud ( p_nomObj->p_cadValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


SCadena * SNomValor ( SNombre * p_nomObj )
{
	SCadena * p_cadRes;

	if ( ES_VALIDO ( p_nomObj ) )
	{
		p_cadRes = p_nomObj->p_cadValor;
	}
	else
	{
		p_cadRes = NULL;
	}
	return ( p_cadRes );
}

const char * SNomValorConstante ( SNombre * p_nomObj )
{
	const char * p_cRes;

	if ( ES_VALIDO ( p_nomObj ) )
	{
		p_cRes = SCadValorConstante ( p_nomObj->p_cadValor );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SNomEstablecerCad ( SNombre * p_nomObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_nomObj ) && ES_VALIDO ( p_cadValor ) )
	{
		if ( SCadLongitud ( p_cadValor ) <= SCadMaxTam ( p_nomObj->p_cadValor ) )
		{
			if ( ( SCadContieneBlancos ( p_cadValor ) == 0 ) &&
				 ( SCadContieneCaracteresNoImprimibles ( p_cadValor ) == 0 ) &&
				 ( SCadContieneCaracteresNoEstandar ( p_cadValor ) == 0 ) &&
				 ( ASCIIEsLetra ( SCadCaracter ( p_cadValor, 0 ) ) == 1 ) )
			{
				iRes = SCadCopiar ( p_nomObj->p_cadValor, p_cadValor );
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
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNomEstablecer ( SNombre * p_nomObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_nomObj ) && ES_VALIDO ( p_cValor ) )
	{
		if ( CadLongitud ( p_cValor ) <= SCadMaxTam ( p_nomObj->p_cadValor ) )
		{
			if ( ( CadContieneBlancos ( p_cValor ) == 0 ) &&
				 ( CadContieneCaracteresNoImprimibles ( p_cValor ) == 0 ) &&
				 ( CadContieneCaracteresNoEstandar ( p_cValor ) == 0 ) &&
				 ( ASCIIEsLetra ( p_cValor [ 0 ] ) == 1 ) )
			{
				iRes = SCadCopiarLiteral ( p_nomObj->p_cadValor, p_cValor );
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
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNomLimpiar ( SNombre * p_nomObj )
{
	int iRes;

	if ( ES_VALIDO ( p_nomObj ) )
	{
		iRes = SCadVaciar ( p_nomObj->p_cadValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNomEstaVacio ( SNombre * p_nomObj )
{
	int iRes;

	if ( ES_VALIDO ( p_nomObj ) )
	{
		iRes = SCadEstaVacia ( p_nomObj->p_cadValor );
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}



