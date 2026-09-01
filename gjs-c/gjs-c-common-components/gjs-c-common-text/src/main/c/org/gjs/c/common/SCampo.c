/******************************************************************************/
/*                                 SCampo.c                                   */
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

#include "SCampo.h"
#include "Cadenas.h"

#include "TextoConfig.h"


SCampo * SCampCrearDef ( PFUNINTPCAD fValidacion )
{
	return ( SCampCrear ( fValidacion, NOM_MAX_TAM_DEF ) );
}

SCampo * SCampCrear ( PFUNINTPCAD fValidacion, int iMaxTam )
{
	SCampo * p_campObj;
	
	if ( ES_VALIDO ( fValidacion ) && ( iMaxTam > 0 ) )
	{
		p_campObj = (SCampo *) MemReservar ( sizeof ( SCampo ) );
		if ( ES_VALIDO ( p_campObj ) )
		{
			p_campObj->fValidacion = fValidacion;
			p_campObj->p_cadValor = SCadCrear ( iMaxTam );
			if ( ES_NULO ( p_campObj->p_cadValor ) )
			{
				SCampDestruir ( &p_campObj );
			}
		}
	}
	else
	{
		p_campObj = NULL;
	}
	return ( p_campObj );
}

void SCampDestruir ( SCampo ** p_p_campObj )
{
	SCampo * p_campObj;
	
	if ( ES_VALIDO ( p_p_campObj ) )
	{
		p_campObj = *p_p_campObj;

		if ( ES_VALIDO ( p_campObj ) )
		{
			SCadDestruir ( &(p_campObj->p_cadValor) );
			MemLiberar ( (void **) p_p_campObj );
		}
	}
}

int SCampMaxLongitud ( SCampo * p_campObj )
{
	int iRes;

	if ( ES_VALIDO ( p_campObj ) )
	{
		iRes = SCadMaxTam ( p_campObj->p_cadValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCampLongitud ( SCampo * p_campObj )
{
	int iRes;

	if ( ES_VALIDO ( p_campObj ) )
	{
		iRes = SCadLongitud ( p_campObj->p_cadValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCampEsValido ( SCampo * p_campObj )
{
	int iRes;

	if ( ES_VALIDO ( p_campObj ) )
	{
		if ( ES_VALIDO ( p_campObj->fValidacion ) )
		{
			iRes = p_campObj->fValidacion ( p_campObj->p_cadValor );
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

SCadena * SCampValor ( SCampo * p_campObj )
{
	SCadena * p_cadRes;

	if ( ES_VALIDO ( p_campObj ) )
	{
		p_cadRes = p_campObj->p_cadValor;
	}
	else
	{
		p_cadRes = NULL;
	}
	return ( p_cadRes );
}

const char * SCampValorLit ( SCampo * p_campObj )
{
	const char * p_cRes;

	if ( ES_VALIDO ( p_campObj ) )
	{
		p_cRes = SCadValorConstante ( p_campObj->p_cadValor );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SCampEstablecer ( SCampo * p_campObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_campObj ) && ES_VALIDO ( p_cadValor ) )
	{
		if ( SCadLongitud ( p_cadValor ) <= SCadMaxTam ( p_campObj->p_cadValor ) )
		{
			if ( SCadCopiar ( p_campObj->p_cadValor, p_cadValor ) == 1 )
			{
				iRes = SCampEsValido ( p_campObj );
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

int SCampEstablecerLit ( SCampo * p_campObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_campObj ) && ES_VALIDO ( p_cValor ) )
	{
		if ( CadLongitud ( p_cValor ) <= SCadMaxTam ( p_campObj->p_cadValor ) )
		{
			if ( SCadCopiarLiteral ( p_campObj->p_cadValor, p_cValor ) == 1 )
			{
				iRes = SCampEsValido ( p_campObj );
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

int SCampLimpiar ( SCampo * p_campObj )
{
	int iRes;

	if ( ES_VALIDO ( p_campObj ) )
	{
		iRes = SCadLimpiar ( p_campObj->p_cadValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCampEstaVacio ( SCampo * p_campObj )
{
	int iRes;

	if ( ES_VALIDO ( p_campObj ) )
	{
		iRes = SCadEstaVacia ( p_campObj->p_cadValor );
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

int SCampAsignar ( SCampo * p_campObj, SCampo * p_campValor )
{
	int iRes;

	if ( ES_VALIDO ( p_campObj ) )
	{
		iRes = SCampEstablecer ( p_campObj, SCampValor ( p_campValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SCampo * SCampDuplicar ( SCampo * p_campObj )
{
	SCampo * p_campCopia;

	if ( ES_VALIDO ( p_campObj ) )
	{
		p_campCopia = SCampCrear ( p_campObj->fValidacion, SCampMaxLongitud ( p_campObj ) );
		if ( ES_VALIDO ( p_campCopia ) )
		{
			SCampEstablecer ( p_campCopia, p_campObj->p_cadValor );
		}
	}
	else
	{
		p_campCopia = NULL;
	}
	return ( p_campCopia );
}

int SCampEsIgual ( SCampo * p_campObj, SCampo * p_campValor )
{
	int iRes;

	if ( ES_VALIDO ( p_campObj ) && ES_VALIDO ( p_campValor ) )
	{
		iRes = SCampEsIgualCad ( p_campObj, SCampValor ( p_campValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCampEsMenor ( SCampo * p_campObj, SCampo * p_campValor )
{
	int iRes;

	if ( ES_VALIDO ( p_campObj ) && ES_VALIDO ( p_campValor ) )
	{
		iRes = SCampEsMenorCad ( p_campObj, SCampValor ( p_campValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCampEsMayor ( SCampo * p_campObj, SCampo * p_campValor )
{
	int iRes;

	if ( ES_VALIDO ( p_campObj ) && ES_VALIDO ( p_campValor ) )
	{
		iRes = SCampEsMayorCad ( p_campObj, SCampValor ( p_campValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCampEsDiferente ( SCampo * p_campObj, SCampo * p_campValor )
{
	int iRes;

	if ( ES_VALIDO ( p_campObj ) && ES_VALIDO ( p_campValor ) )
	{
		iRes = SCampEsDiferenteCad ( p_campObj, SCampValor ( p_campValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int SCampEsMenorIg ( SCampo * p_campObj, SCampo * p_campValor )
{
	int iRes;

	if ( ES_VALIDO ( p_campObj ) && ES_VALIDO ( p_campValor ) )
	{
		iRes = SCampEsMenorIgCad ( p_campObj, SCampValor ( p_campValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCampEsMayorIg ( SCampo * p_campObj, SCampo * p_campValor )
{
	int iRes;

	if ( ES_VALIDO ( p_campObj ) && ES_VALIDO ( p_campValor ) )
	{
		iRes = SCampEsMayorIgCad ( p_campObj, SCampValor ( p_campValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCampEsIgualCad ( SCampo * p_campObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_campObj ) && ES_VALIDO ( p_cadValor ) )
	{
		iRes = SCadEsIgual ( p_campObj->p_cadValor, p_cadValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCampEsMenorCad ( SCampo * p_campObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_campObj ) && ES_VALIDO ( p_cadValor ) )
	{
		iRes = SCadEsMenor ( p_campObj->p_cadValor, p_cadValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCampEsMayorCad ( SCampo * p_campObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_campObj ) && ES_VALIDO ( p_cadValor ) )
	{
		iRes = SCadEsMayor ( p_campObj->p_cadValor, p_cadValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCampEsDiferenteCad ( SCampo * p_campObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_campObj ) && ES_VALIDO ( p_cadValor ) )
	{
		iRes = SCadEsDiferente ( p_campObj->p_cadValor, p_cadValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCampEsMenorIgCad ( SCampo * p_campObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_campObj ) && ES_VALIDO ( p_cadValor ) )
	{
		iRes = SCadEsMenorIg ( p_campObj->p_cadValor, p_cadValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCampEsMayorIgCad ( SCampo * p_campObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_campObj ) && ES_VALIDO ( p_cadValor ) )
	{
		iRes = SCadEsMayorIg ( p_campObj->p_cadValor, p_cadValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCampEsIgualLit ( SCampo * p_campObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_campObj ) && ES_VALIDO ( p_cValor ) )
	{
		iRes = SCadEsIgualLiteral ( p_campObj->p_cadValor, p_cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCampEsMenorLit ( SCampo * p_campObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_campObj ) && ES_VALIDO ( p_cValor ) )
	{
		iRes = SCadEsMenorLiteral ( p_campObj->p_cadValor, p_cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCampEsMayorLit ( SCampo * p_campObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_campObj ) && ES_VALIDO ( p_cValor ) )
	{
		iRes = SCadEsMayorLiteral ( p_campObj->p_cadValor, p_cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCampEsDiferenteLit ( SCampo * p_campObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_campObj ) && ES_VALIDO ( p_cValor ) )
	{
		iRes = SCadEsDiferenteLiteral ( p_campObj->p_cadValor, p_cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCampEsMenorIgLit ( SCampo * p_campObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_campObj ) && ES_VALIDO ( p_cValor ) )
	{
		iRes = SCadEsMenorIgLiteral ( p_campObj->p_cadValor, p_cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCampEsMayorIgLit ( SCampo * p_campObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_campObj ) && ES_VALIDO ( p_cValor ) )
	{
		iRes = SCadEsMayorIgLiteral ( p_campObj->p_cadValor, p_cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCampComparar ( SCampo * p_campObj, SCampo * p_campValor )
{
	int iRes;

	if ( ES_VALIDO ( p_campObj ) && ES_VALIDO ( p_campValor ) )
	{
		iRes = SCampCompararCad ( p_campObj, SCampValor ( p_campValor ) );
	}
	else if ( ES_VALIDO ( p_campObj ) )
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

int SCampCompararCad ( SCampo * p_campObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_campObj ) && ES_VALIDO ( p_cadValor ) )
	{
		iRes = SCadComparar ( p_campObj->p_cadValor, p_cadValor );
	}
	else if ( ES_VALIDO ( p_campObj ) )
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

int SCampCompararLit ( SCampo * p_campObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_campObj ) && ES_VALIDO ( p_cValor ) )
	{
		iRes = SCadCompararLiteral ( p_campObj->p_cadValor, p_cValor );
	}
	else if ( ES_VALIDO ( p_campObj ) )
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

int SCampCumpleExpReg ( SCampo * p_campObj, const char * p_cExpReg )
{
	int iRes;

	if ( ES_VALIDO ( p_campObj ) )
	{
		iRes = SCadCumpleExpReg ( p_campObj->p_cadValor, p_cExpReg );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}




