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
#include "ValidacionCadenas.h"

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
			p_nomObj->p_campValor = SCampCrear ( SCadEsNombreValido, iMaxTam );
			if ( ES_NULO ( p_nomObj->p_campValor ) )
			{
				SNomDestruir ( &p_nomObj );
			}
		}
	}
	else
	{
		p_nomObj = NULL;
	}
	return ( p_nomObj );
}

SNombre * SNomCrearValor ( SCadena * p_cadValor )
{
	SNombre * p_nomObj;
	
	p_nomObj = SNomCrear ( SCadLongitud ( p_cadValor ) );
	if ( SNomEstablecer ( p_nomObj, p_cadValor ) == 0 )
	{
		SNomDestruir ( &p_nomObj );
	}
	return ( p_nomObj );
}

SNombre * SNomCrearValorLit ( const char * p_cValor )
{
	SNombre * p_nomObj;
	
	p_nomObj = SNomCrear ( CadLongitud ( p_cValor ) );
	if ( SNomEstablecerLit ( p_nomObj, p_cValor ) == 0 )
	{
		SNomDestruir ( &p_nomObj );
	}
	return ( p_nomObj );
}

SNombre * SNomCrearValorExt ( SCadena * p_cadValor, int iMaxTam )
{
	SNombre * p_nomObj;
	
	p_nomObj = SNomCrear ( iMaxTam );
	if ( SNomEstablecer ( p_nomObj, p_cadValor ) == 0 )
	{
		SNomDestruir ( &p_nomObj );
	}
	return ( p_nomObj );
}

SNombre * SNomCrearValorLitExt ( const char * p_cValor, int iMaxTam )
{
	SNombre * p_nomObj;
	
	p_nomObj = SNomCrear ( iMaxTam );
	if ( SNomEstablecerLit ( p_nomObj, p_cValor ) == 0 )
	{
		SNomDestruir ( &p_nomObj );
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
			SCampDestruir ( &(p_nomObj->p_campValor) );
			MemLiberar ( (void **) p_p_nomObj );
		}
	}
}

int SNomMaxLongitud ( SNombre * p_nomObj )
{
	int iRes;

	if ( ES_VALIDO ( p_nomObj ) )
	{
		iRes = SCampMaxLongitud ( p_nomObj->p_campValor );
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
		iRes = SCampLongitud ( p_nomObj->p_campValor );
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
		p_cadRes = SCampValor ( p_nomObj->p_campValor );
	}
	else
	{
		p_cadRes = NULL;
	}
	return ( p_cadRes );
}

const char * SNomValorLit ( SNombre * p_nomObj )
{
	const char * p_cRes;

	if ( ES_VALIDO ( p_nomObj ) )
	{
		p_cRes = SCampValorLit ( p_nomObj->p_campValor );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SNomEsValido ( SNombre * p_nomObj )
{
	int iRes;

	if ( ES_VALIDO ( p_nomObj ) )
	{
		iRes = SCampEsValido ( p_nomObj->p_campValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNomEstablecer ( SNombre * p_nomObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_nomObj ) )
	{
		iRes = SCampEstablecer ( p_nomObj->p_campValor, p_cadValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNomEstablecerLit ( SNombre * p_nomObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_nomObj ) )
	{
		iRes = SCampEstablecerLit ( p_nomObj->p_campValor, p_cValor );
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
		iRes = SCampLimpiar ( p_nomObj->p_campValor );
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
		iRes = SCampEstaVacio ( p_nomObj->p_campValor );
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

int SNomAsignar ( SNombre * p_nomObj, SNombre * p_nomValor )
{
	int iRes;

	if ( ES_VALIDO ( p_nomObj ) )
	{
		iRes = SNomEstablecer ( p_nomObj, SNomValor ( p_nomValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNomAsignarCampo ( SNombre * p_nomObj, SCampo * p_campValor )
{
	int iRes;

	if ( ES_VALIDO ( p_nomObj ) )
	{
		iRes = SNomEstablecer ( p_nomObj, SCampValor ( p_campValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SNombre * SNomDuplicar ( SNombre * p_nomObj )
{
	SNombre * p_nomCopia;

	if ( ES_VALIDO ( p_nomObj ) )
	{
		p_nomCopia = SNomCrearValorExt ( SNomValor ( p_nomObj ), SNomMaxLongitud ( p_nomObj ) );
	}
	else
	{
		p_nomCopia = NULL;
	}
	return ( p_nomCopia );
}

int SNomEsIgual ( SNombre * p_nomObj, SNombre * p_nomValor )
{
	int iRes;

	if ( ES_VALIDO ( p_nomObj ) && ES_VALIDO ( p_nomValor ) )
	{
		iRes = SNomEsIgualCad ( p_nomObj, SNomValor ( p_nomValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNomEsMenor ( SNombre * p_nomObj, SNombre * p_nomValor )
{
	int iRes;

	if ( ES_VALIDO ( p_nomObj ) && ES_VALIDO ( p_nomValor ) )
	{
		iRes = SNomEsMenorCad ( p_nomObj, SNomValor ( p_nomValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNomEsMayor ( SNombre * p_nomObj, SNombre * p_nomValor )
{
	int iRes;

	if ( ES_VALIDO ( p_nomObj ) && ES_VALIDO ( p_nomValor ) )
	{
		iRes = SNomEsMayorCad ( p_nomObj, SNomValor ( p_nomValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNomEsDiferente ( SNombre * p_nomObj, SNombre * p_nomValor )
{
	int iRes;

	if ( ES_VALIDO ( p_nomObj ) && ES_VALIDO ( p_nomValor ) )
	{
		iRes = SNomEsDiferenteCad ( p_nomObj, SNomValor ( p_nomValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNomEsMenorIg ( SNombre * p_nomObj, SNombre * p_nomValor )
{
	int iRes;

	if ( ES_VALIDO ( p_nomObj ) && ES_VALIDO ( p_nomValor ) )
	{
		iRes = SNomEsMenorIgCad ( p_nomObj, SNomValor ( p_nomValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNomEsMayorIg ( SNombre * p_nomObj, SNombre * p_nomValor )
{
	int iRes;

	if ( ES_VALIDO ( p_nomObj ) && ES_VALIDO ( p_nomValor ) )
	{
		iRes = SNomEsMayorIgCad ( p_nomObj, SNomValor ( p_nomValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNomEsIgualCampo ( SNombre * p_nomObj, SCampo * p_campValor )
{
	int iRes;

	if ( ES_VALIDO ( p_nomObj ) && ES_VALIDO ( p_campValor ) )
	{
		iRes = SNomEsIgualCad ( p_nomObj, SCampValor ( p_campValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNomEsMenorCampo ( SNombre * p_nomObj, SCampo * p_campValor )
{
	int iRes;

	if ( ES_VALIDO ( p_nomObj ) && ES_VALIDO ( p_campValor ) )
	{
		iRes = SNomEsMenorCad ( p_nomObj, SCampValor ( p_campValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNomEsMayorCampo ( SNombre * p_nomObj, SCampo * p_campValor )
{
	int iRes;

	if ( ES_VALIDO ( p_nomObj ) && ES_VALIDO ( p_campValor ) )
	{
		iRes = SNomEsMayorCad ( p_nomObj, SCampValor ( p_campValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNomEsDiferenteCampo ( SNombre * p_nomObj, SCampo * p_campValor )
{
	int iRes;

	if ( ES_VALIDO ( p_nomObj ) && ES_VALIDO ( p_campValor ) )
	{
		iRes = SNomEsDiferenteCad ( p_nomObj, SCampValor ( p_campValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNomEsMenorIgCampo ( SNombre * p_nomObj, SCampo * p_campValor )
{
	int iRes;

	if ( ES_VALIDO ( p_nomObj ) && ES_VALIDO ( p_campValor ) )
	{
		iRes = SNomEsMenorIgCad ( p_nomObj, SCampValor ( p_campValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNomEsMayorIgCampo ( SNombre * p_nomObj, SCampo * p_campValor )
{
	int iRes;

	if ( ES_VALIDO ( p_nomObj ) && ES_VALIDO ( p_campValor ) )
	{
		iRes = SNomEsMayorIgCad ( p_nomObj, SCampValor ( p_campValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNomEsIgualCad ( SNombre * p_nomObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_nomObj ) && ES_VALIDO ( p_cadValor ) )
	{
		iRes = SCadEsIgual ( SNomValor ( p_nomObj ), p_cadValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNomEsMenorCad ( SNombre * p_nomObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_nomObj ) && ES_VALIDO ( p_cadValor ) )
	{
		iRes = SCadEsMenor ( SNomValor ( p_nomObj ), p_cadValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNomEsMayorCad ( SNombre * p_nomObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_nomObj ) && ES_VALIDO ( p_cadValor ) )
	{
		iRes = SCadEsMayor ( SNomValor ( p_nomObj ), p_cadValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNomEsDiferenteCad ( SNombre * p_nomObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_nomObj ) && ES_VALIDO ( p_cadValor ) )
	{
		iRes = SCadEsDiferente ( SNomValor ( p_nomObj ), p_cadValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNomEsMenorIgCad ( SNombre * p_nomObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_nomObj ) && ES_VALIDO ( p_cadValor ) )
	{
		iRes = SCadEsMenorIg ( SNomValor ( p_nomObj ), p_cadValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNomEsMayorIgCad ( SNombre * p_nomObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_nomObj ) && ES_VALIDO ( p_cadValor ) )
	{
		iRes = SCadEsMayorIg ( SNomValor ( p_nomObj ), p_cadValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNomEsIgualLit ( SNombre * p_nomObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_nomObj ) && ES_VALIDO ( p_cValor ) )
	{
		iRes = SCadEsIgualLiteral ( SNomValor ( p_nomObj ), p_cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNomEsMenorLit ( SNombre * p_nomObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_nomObj ) && ES_VALIDO ( p_cValor ) )
	{
		iRes = SCadEsMenorLiteral ( SNomValor ( p_nomObj ), p_cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNomEsMayorLit ( SNombre * p_nomObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_nomObj ) && ES_VALIDO ( p_cValor ) )
	{
		iRes = SCadEsMayorLiteral ( SNomValor ( p_nomObj ), p_cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNomEsDiferenteLit ( SNombre * p_nomObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_nomObj ) && ES_VALIDO ( p_cValor ) )
	{
		iRes = SCadEsDiferenteLiteral ( SNomValor ( p_nomObj ), p_cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNomEsMenorIgLit ( SNombre * p_nomObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_nomObj ) && ES_VALIDO ( p_cValor ) )
	{
		iRes = SCadEsMenorIgLiteral ( SNomValor ( p_nomObj ), p_cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNomEsMayorIgLit ( SNombre * p_nomObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_nomObj ) && ES_VALIDO ( p_cValor ) )
	{
		iRes = SCadEsMayorIgLiteral ( SNomValor ( p_nomObj ), p_cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNomComparar ( SNombre * p_nomObj, SNombre * p_nomValor )
{
	int iRes;

	if ( ES_VALIDO ( p_nomObj ) && ES_VALIDO ( p_nomValor ) )
	{
		iRes = SNomCompararCad ( p_nomObj, SNomValor ( p_nomValor ) );
	}
	else if ( ES_VALIDO ( p_nomObj ) )
	{
		iRes = COMP_MAYOR;
	}
	else if ( ES_VALIDO ( p_nomValor ) )
	{
		iRes = COMP_MENOR;
	}
	else
	{
		iRes = COMP_IGUAL;
	}
	return ( iRes );
}

int SNomCompararCampo ( SNombre * p_nomObj, SCampo * p_campValor )
{
	int iRes;

	if ( ES_VALIDO ( p_nomObj ) && ES_VALIDO ( p_campValor ) )
	{
		iRes = SCampComparar ( p_nomObj->p_campValor, p_campValor );
	}
	else if ( ES_VALIDO ( p_nomObj ) )
	{
		iRes = COMP_MAYOR;
	}
	else if ( ES_VALIDO ( p_campValor ) )
	{
		iRes = COMP_MENOR;
	}
	else
	{
		iRes = COMP_IGUAL;
	}
	return ( iRes );
}

int SNomCompararCad ( SNombre * p_nomObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_nomObj ) && ES_VALIDO ( p_cadValor ) )
	{
		iRes = SCadComparar ( SNomValor ( p_nomObj ), p_cadValor );
	}
	else if ( ES_VALIDO ( p_nomObj ) )
	{
		iRes = COMP_MAYOR;
	}
	else if ( ES_VALIDO ( p_cadValor ) )
	{
		iRes = COMP_MENOR;
	}
	else
	{
		iRes = COMP_IGUAL;
	}
	return ( iRes );
}

int SNomCompararLit ( SNombre * p_nomObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_nomObj ) && ES_VALIDO ( p_cValor ) )
	{
		iRes = SCadCompararLiteral ( SNomValor ( p_nomObj ), p_cValor );
	}
	else if ( ES_VALIDO ( p_nomObj ) )
	{
		iRes = COMP_MAYOR;
	}
	else if ( ES_VALIDO ( p_cValor ) )
	{
		iRes = COMP_MENOR;
	}
	else
	{
		iRes = COMP_IGUAL;
	}
	return ( iRes );
}

int SNomCumpleExpReg ( SNombre * p_nomObj, const char * p_cExpReg )
{
	int iRes;

	if ( ES_VALIDO ( p_nomObj ) )
	{
		iRes = SCadCumpleExpReg ( SNomValor ( p_nomObj ), p_cExpReg );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

unsigned int SNomHash ( SNombre * p_nomObj )
{
	unsigned int uiRes = 0;

	if ( ES_VALIDO ( p_nomObj ) )
	{
		uiRes = HashCadena ( SNomValorLit ( p_nomObj ) );
	}
	return ( uiRes );
}




