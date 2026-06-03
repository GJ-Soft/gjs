/******************************************************************************/
/*                                 SDescripcion.cpp                                */
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

#include "SDescripcion.h"
#include "Cadenas.h"

#include "TextoConfig.h"



SDescripcion * SDescCrearDef ()
{
	return ( SDescCrear ( DESC_MAX_TAM_DEF ) );
}

SDescripcion * SDescCrear ( int iMaxTam )
{
	SDescripcion * p_descObj;
	
	if ( iMaxTam > 0 )
	{
		p_descObj = (SDescripcion *) MemReservar ( sizeof ( SDescripcion ) );
		if ( ES_VALIDO ( p_descObj ) )
		{
			p_descObj->p_cadValor = SCadCrear ( iMaxTam );
		}
	}
	else
	{
		p_descObj = NULL;
	}
	return ( p_descObj );
}


void SDescDestruir ( SDescripcion ** p_p_descObj )
{
	SDescripcion * p_descObj;
	
	if ( ES_VALIDO ( p_p_descObj ) )
	{
		p_descObj = *p_p_descObj;

		if ( ES_VALIDO ( p_descObj ) )
		{
			SCadDestruir ( &(p_descObj->p_cadValor) );
			MemLiberar ( (void **) p_p_descObj );
		}
	}
}

int SDescMaxLongitud ( SDescripcion * p_descObj )
{
	int iRes;

	if ( ES_VALIDO ( p_descObj ) )
	{
		iRes = SCadMaxTam ( p_descObj->p_cadValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SDescLongitud ( SDescripcion * p_descObj )
{
	int iRes;

	if ( ES_VALIDO ( p_descObj ) )
	{
		iRes = SCadLongitud ( p_descObj->p_cadValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


SCadena * SDescValor ( SDescripcion * p_descObj )
{
	SCadena * p_cadRes;

	if ( ES_VALIDO ( p_descObj ) )
	{
		p_cadRes = p_descObj->p_cadValor;
	}
	else
	{
		p_cadRes = NULL;
	}
	return ( p_cadRes );
}

const char * SDescValorConstante ( SDescripcion * p_descObj )
{
	const char * p_cRes;

	if ( ES_VALIDO ( p_descObj ) )
	{
		p_cRes = SCadValorConstante ( p_descObj->p_cadValor );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SDescEstablecerCad ( SDescripcion * p_descObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_descObj ) && ES_VALIDO ( p_cadValor ) )
	{
		if ( SCadLongitud ( p_cadValor ) <= SCadMaxTam ( p_descObj->p_cadValor ) )
		{
			if ( SCadContieneCaracteresNoImprimibles ( p_cadValor ) == 0 ) 
			{
				iRes = SCadCopiar ( p_descObj->p_cadValor, p_cadValor );
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

int SDescEstablecer ( SDescripcion * p_descObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_descObj ) && ES_VALIDO ( p_cValor ) )
	{
		if ( CadLongitud ( p_cValor ) <= SCadMaxTam ( p_descObj->p_cadValor ) )
		{
			if ( CadContieneCaracteresNoImprimibles ( p_cValor ) == 0 )
			{
				iRes = SCadCopiarLiteral ( p_descObj->p_cadValor, p_cValor );
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

int SDescLimpiar ( SDescripcion * p_descObj )
{
	int iRes;

	if ( ES_VALIDO ( p_descObj ) )
	{
		iRes = SCadVaciar ( p_descObj->p_cadValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SDescEstaVacio ( SDescripcion * p_descObj )
{
	int iRes;

	if ( ES_VALIDO ( p_descObj ) )
	{
		iRes = SCadEstaVacia ( p_descObj->p_cadValor );
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}





