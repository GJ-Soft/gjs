/******************************************************************************/
/*                                 SCodigo.cpp                                */
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

#include "SCodigo.h"
#include "ValidacionCadenas.h"

#include "TextoConfig.h"




SCodigo * SCodCrearDef ()
{
	return ( SCodCrear ( COD_MAX_TAM_DEF ) );
}

SCodigo * SCodCrear ( int iMaxTam )
{
	SCodigo * p_codObj;
	
	if ( iMaxTam > 0 )
	{
		p_codObj = (SCodigo *) MemReservar ( sizeof ( SCodigo ) );
		if ( ES_VALIDO ( p_codObj ) )
		{
			p_codObj->p_campValor = SCampCrear ( SCadEsCodigoValido, iMaxTam );
			if ( ES_NULO ( p_codObj->p_campValor ) )
			{
				SCodDestruir ( &p_codObj );
			}
		}
	}
	else
	{
		p_codObj = NULL;
	}
	return ( p_codObj );
}

SCodigo * SCodCrearValor ( SCadena * p_cadValor )
{
	SCodigo * p_codObj;
	
	p_codObj = SCodCrear ( SCadLongitud ( p_cadValor ) );
	if ( SCodEstablecer ( p_codObj, p_cadValor ) == 0 )
	{
		SCodDestruir ( &p_codObj );
	}
	return ( p_codObj );
}

SCodigo * SCodCrearValorLit ( const char * p_cValor )
{
	SCodigo * p_codObj;
	
	p_codObj = SCodCrear ( CadLongitud ( p_cValor ) );
	if ( SCodEstablecerLit ( p_codObj, p_cValor ) == 0 )
	{
		SCodDestruir ( &p_codObj );
	}
	return ( p_codObj );
}

SCodigo * SCodCrearValorExt ( SCadena * p_cadValor, int iMaxTam )
{
	SCodigo * p_codObj;
	
	p_codObj = SCodCrear ( iMaxTam );
	if ( SCodEstablecer ( p_codObj, p_cadValor ) == 0 )
	{
		SCodDestruir ( &p_codObj );
	}
	return ( p_codObj );
}

SCodigo * SCodCrearValorLitExt ( const char * p_cValor, int iMaxTam )
{
	SCodigo * p_codObj;
	
	p_codObj = SCodCrear ( iMaxTam );
	if ( SCodEstablecerLit ( p_codObj, p_cValor ) == 0 )
	{
		SCodDestruir ( &p_codObj );
	}
	return ( p_codObj );
}

void SCodDestruir ( SCodigo ** p_p_codObj )
{
	SCodigo * p_codObj;
	
	if ( ES_VALIDO ( p_p_codObj ) )
	{
		p_codObj = *p_p_codObj;

		if ( ES_VALIDO ( p_codObj ) )
		{
			SCampDestruir ( &(p_codObj->p_campValor) );
			MemLiberar ( (void **) p_p_codObj );
		}
	}
}

int SCodMaxLongitud ( SCodigo * p_codObj )
{
	int iRes;

	if ( ES_VALIDO ( p_codObj ) )
	{
		iRes = SCampMaxLongitud ( p_codObj->p_campValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCodLongitud ( SCodigo * p_codObj )
{
	int iRes;

	if ( ES_VALIDO ( p_codObj ) )
	{
		iRes = SCampLongitud ( p_codObj->p_campValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SCadena * SCodValor ( SCodigo * p_codObj )
{
	SCadena * p_cadRes;

	if ( ES_VALIDO ( p_codObj ) )
	{
		p_cadRes = SCampValor ( p_codObj->p_campValor );
	}
	else
	{
		p_cadRes = NULL;
	}
	return ( p_cadRes );
}

const char * SCodValorLit ( SCodigo * p_codObj )
{
	const char * p_cRes;

	if ( ES_VALIDO ( p_codObj ) )
	{
		p_cRes = SCampValorLit ( p_codObj->p_campValor );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SCodEsValido ( SCodigo * p_codObj )
{
	int iRes;

	if ( ES_VALIDO ( p_codObj ) )
	{
		iRes = SCampEsValido ( p_codObj->p_campValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCodEstablecer ( SCodigo * p_codObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_codObj ) )
	{
		iRes = SCampEstablecer ( p_codObj->p_campValor, p_cadValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCodEstablecerLit ( SCodigo * p_codObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_codObj ) )
	{
		iRes = SCampEstablecerLit ( p_codObj->p_campValor, p_cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCodLimpiar ( SCodigo * p_codObj )
{
	int iRes;

	if ( ES_VALIDO ( p_codObj ) )
	{
		iRes = SCampLimpiar ( p_codObj->p_campValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCodEstaVacio ( SCodigo * p_codObj )
{
	int iRes;

	if ( ES_VALIDO ( p_codObj ) )
	{
		iRes = SCampEstaVacio ( p_codObj->p_campValor );
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

int SCodAsignar ( SCodigo * p_codObj, SCodigo * p_codValor )
{
	int iRes;

	if ( ES_VALIDO ( p_codObj ) )
	{
		iRes = SCodEstablecer ( p_codObj, SCodValor ( p_codValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCodAsignarCampo ( SCodigo * p_codObj, SCampo * p_campValor )
{
	int iRes;

	if ( ES_VALIDO ( p_codObj ) )
	{
		iRes = SCodEstablecer ( p_codObj, SCampValor ( p_campValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SCodigo * SCodDuplicar ( SCodigo * p_codObj )
{
	SCodigo * p_codCopia;

	if ( ES_VALIDO ( p_codObj ) )
	{
		p_codCopia = SCodCrearValorExt ( SCodValor ( p_codObj ), SCodMaxLongitud ( p_codObj ) );
	}
	else
	{
		p_codCopia = NULL;
	}
	return ( p_codCopia );
}

int SCodEsIgual ( SCodigo * p_codObj, SCodigo * p_codValor )
{
	int iRes;

	if ( ES_VALIDO ( p_codObj ) && ES_VALIDO ( p_codValor ) )
	{
		iRes = SCodEsIgualCad ( p_codObj, SCodValor ( p_codValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCodEsMenor ( SCodigo * p_codObj, SCodigo * p_codValor )
{
	int iRes;

	if ( ES_VALIDO ( p_codObj ) && ES_VALIDO ( p_codValor ) )
	{
		iRes = SCodEsMenorCad ( p_codObj, SCodValor ( p_codValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCodEsMayor ( SCodigo * p_codObj, SCodigo * p_codValor )
{
	int iRes;

	if ( ES_VALIDO ( p_codObj ) && ES_VALIDO ( p_codValor ) )
	{
		iRes = SCodEsMayorCad ( p_codObj, SCodValor ( p_codValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCodEsDiferente ( SCodigo * p_codObj, SCodigo * p_codValor )
{
	int iRes;

	if ( ES_VALIDO ( p_codObj ) && ES_VALIDO ( p_codValor ) )
	{
		iRes = SCodEsDiferenteCad ( p_codObj, SCodValor ( p_codValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCodEsMenorIg ( SCodigo * p_codObj, SCodigo * p_codValor )
{
	int iRes;

	if ( ES_VALIDO ( p_codObj ) && ES_VALIDO ( p_codValor ) )
	{
		iRes = SCodEsMenorIgCad ( p_codObj, SCodValor ( p_codValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCodEsMayorIg ( SCodigo * p_codObj, SCodigo * p_codValor )
{
	int iRes;

	if ( ES_VALIDO ( p_codObj ) && ES_VALIDO ( p_codValor ) )
	{
		iRes = SCodEsMayorIgCad ( p_codObj, SCodValor ( p_codValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCodEsIgualCampo ( SCodigo * p_codObj, SCampo * p_campValor )
{
	int iRes;

	if ( ES_VALIDO ( p_codObj ) && ES_VALIDO ( p_campValor ) )
	{
		iRes = SCodEsIgualCad ( p_codObj, SCampValor ( p_campValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCodEsMenorCampo ( SCodigo * p_codObj, SCampo * p_campValor )
{
	int iRes;

	if ( ES_VALIDO ( p_codObj ) && ES_VALIDO ( p_campValor ) )
	{
		iRes = SCodEsMenorCad ( p_codObj, SCampValor ( p_campValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCodEsMayorCampo ( SCodigo * p_codObj, SCampo * p_campValor )
{
	int iRes;

	if ( ES_VALIDO ( p_codObj ) && ES_VALIDO ( p_campValor ) )
	{
		iRes = SCodEsMayorCad ( p_codObj, SCampValor ( p_campValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCodEsDiferenteCampo ( SCodigo * p_codObj, SCampo * p_campValor )
{
	int iRes;

	if ( ES_VALIDO ( p_codObj ) && ES_VALIDO ( p_campValor ) )
	{
		iRes = SCodEsDiferenteCad ( p_codObj, SCampValor ( p_campValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCodEsMenorIgCampo ( SCodigo * p_codObj, SCampo * p_campValor )
{
	int iRes;

	if ( ES_VALIDO ( p_codObj ) && ES_VALIDO ( p_campValor ) )
	{
		iRes = SCodEsMenorIgCad ( p_codObj, SCampValor ( p_campValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCodEsMayorIgCampo ( SCodigo * p_codObj, SCampo * p_campValor )
{
	int iRes;

	if ( ES_VALIDO ( p_codObj ) && ES_VALIDO ( p_campValor ) )
	{
		iRes = SCodEsMayorIgCad ( p_codObj, SCampValor ( p_campValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCodEsIgualCad ( SCodigo * p_codObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_codObj ) && ES_VALIDO ( p_cadValor ) )
	{
		iRes = SCadEsIgual ( SCodValor ( p_codObj ), p_cadValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCodEsMenorCad ( SCodigo * p_codObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_codObj ) && ES_VALIDO ( p_cadValor ) )
	{
		iRes = SCadEsMenor ( SCodValor ( p_codObj ), p_cadValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCodEsMayorCad ( SCodigo * p_codObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_codObj ) && ES_VALIDO ( p_cadValor ) )
	{
		iRes = SCadEsMayor ( SCodValor ( p_codObj ), p_cadValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCodEsDiferenteCad ( SCodigo * p_codObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_codObj ) && ES_VALIDO ( p_cadValor ) )
	{
		iRes = SCadEsDiferente ( SCodValor ( p_codObj ), p_cadValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCodEsMenorIgCad ( SCodigo * p_codObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_codObj ) && ES_VALIDO ( p_cadValor ) )
	{
		iRes = SCadEsMenorIg ( SCodValor ( p_codObj ), p_cadValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCodEsMayorIgCad ( SCodigo * p_codObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_codObj ) && ES_VALIDO ( p_cadValor ) )
	{
		iRes = SCadEsMayorIg ( SCodValor ( p_codObj ), p_cadValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCodEsIgualLit ( SCodigo * p_codObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_codObj ) && ES_VALIDO ( p_cValor ) )
	{
		iRes = SCadEsIgualLiteral ( SCodValor ( p_codObj ), p_cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCodEsMenorLit ( SCodigo * p_codObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_codObj ) && ES_VALIDO ( p_cValor ) )
	{
		iRes = SCadEsMenorLiteral ( SCodValor ( p_codObj ), p_cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCodEsMayorLit ( SCodigo * p_codObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_codObj ) && ES_VALIDO ( p_cValor ) )
	{
		iRes = SCadEsMayorLiteral ( SCodValor ( p_codObj ), p_cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCodEsDiferenteLit ( SCodigo * p_codObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_codObj ) && ES_VALIDO ( p_cValor ) )
	{
		iRes = SCadEsDiferenteLiteral ( SCodValor ( p_codObj ), p_cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCodEsMenorIgLit ( SCodigo * p_codObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_codObj ) && ES_VALIDO ( p_cValor ) )
	{
		iRes = SCadEsMenorIgLiteral ( SCodValor ( p_codObj ), p_cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCodEsMayorIgLit ( SCodigo * p_codObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_codObj ) && ES_VALIDO ( p_cValor ) )
	{
		iRes = SCadEsMayorIgLiteral ( SCodValor ( p_codObj ), p_cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCodComparar ( SCodigo * p_codObj, SCodigo * p_codValor )
{
	int iRes;

	if ( ES_VALIDO ( p_codObj ) && ES_VALIDO ( p_codValor ) )
	{
		iRes = SCodCompararCad ( p_codObj, SCodValor ( p_codValor ) );
	}
	else if ( ES_VALIDO ( p_codObj ) )
	{
		iRes = COMP_MAYOR;
	}
	else if ( ES_VALIDO ( p_codValor ) )
	{
		iRes = COMP_MENOR;
	}
	else
	{
		iRes = COMP_IGUAL;
	}
	return ( iRes );
}

int SCodCompararCampo ( SCodigo * p_codObj, SCampo * p_campValor )
{
	int iRes;

	if ( ES_VALIDO ( p_codObj ) && ES_VALIDO ( p_campValor ) )
	{
		iRes = SCampComparar ( p_codObj->p_campValor, p_campValor );
	}
	else if ( ES_VALIDO ( p_codObj ) )
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

int SCodCompararCad ( SCodigo * p_codObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_codObj ) && ES_VALIDO ( p_cadValor ) )
	{
		iRes = SCadComparar ( SCodValor ( p_codObj ), p_cadValor );
	}
	else if ( ES_VALIDO ( p_codObj ) )
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

int SCodCompararLit ( SCodigo * p_codObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_codObj ) && ES_VALIDO ( p_cValor ) )
	{
		iRes = SCadCompararLiteral ( SCodValor ( p_codObj ), p_cValor );
	}
	else if ( ES_VALIDO ( p_codObj ) )
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

int SCodCumpleExpReg ( SCodigo * p_codObj, const char * p_cExpReg )
{
	int iRes;

	if ( ES_VALIDO ( p_codObj ) )
	{
		iRes = SCadCumpleExpReg ( SCodValor ( p_codObj ), p_cExpReg );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

unsigned int SCodHash ( SCodigo * p_codObj )
{
	unsigned int uiRes = 0;

	if ( ES_VALIDO ( p_codObj ) )
	{
		uiRes = HashCadena ( SCodValorLit ( p_codObj ) );
	}
	return ( uiRes );
}



