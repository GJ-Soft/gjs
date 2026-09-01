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
#include "ValidacionCadenas.h"

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
			p_descObj->p_campValor = SCampCrear ( SCadEsDescripcionValida, iMaxTam );
			if ( ES_NULO ( p_descObj->p_campValor ) )
			{
				SDescDestruir ( &p_descObj );
			}
		}
	}
	else
	{
		p_descObj = NULL;
	}
	return ( p_descObj );
}

SDescripcion * SDescCrearValor ( SCadena * p_cadValor )
{
	SDescripcion * p_descObj;
	
	p_descObj = SDescCrear ( SCadLongitud ( p_cadValor ) );
	if ( SDescEstablecer ( p_descObj, p_cadValor ) == 0 )
	{
		SDescDestruir ( &p_descObj );
	}
	return ( p_descObj );
}

SDescripcion * SDescCrearValorLit ( const char * p_cValor )
{
	SDescripcion * p_descObj;
	
	p_descObj = SDescCrear ( CadLongitud ( p_cValor ) );
	if ( SDescEstablecerLit ( p_descObj, p_cValor ) == 0 )
	{
		SDescDestruir ( &p_descObj );
	}
	return ( p_descObj );
}

SDescripcion * SDescCrearValorExt ( SCadena * p_cadValor, int iMaxTam )
{
	SDescripcion * p_descObj;
	
	p_descObj = SDescCrear ( iMaxTam );
	if ( SDescEstablecer ( p_descObj, p_cadValor ) == 0 )
	{
		SDescDestruir ( &p_descObj );
	}
	return ( p_descObj );
}

SDescripcion * SDescCrearValorLitExt ( const char * p_cValor, int iMaxTam )
{
	SDescripcion * p_descObj;
	
	p_descObj = SDescCrear ( iMaxTam );
	if ( SDescEstablecerLit ( p_descObj, p_cValor ) == 0 )
	{
		SDescDestruir ( &p_descObj );
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
			SCampDestruir ( &(p_descObj->p_campValor) );
			MemLiberar ( (void **) p_p_descObj );
		}
	}
}

int SDescMaxLongitud ( SDescripcion * p_descObj )
{
	int iRes;

	if ( ES_VALIDO ( p_descObj ) )
	{
		iRes = SCampMaxLongitud ( p_descObj->p_campValor );
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
		iRes = SCampLongitud ( p_descObj->p_campValor );
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
		p_cadRes = SCampValor ( p_descObj->p_campValor );
	}
	else
	{
		p_cadRes = NULL;
	}
	return ( p_cadRes );
}

const char * SDescValorLit ( SDescripcion * p_descObj )
{
	const char * p_cRes;

	if ( ES_VALIDO ( p_descObj ) )
	{
		p_cRes = SCampValorLit ( p_descObj->p_campValor );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SDescEsValida ( SDescripcion * p_descObj )
{
	int iRes;

	if ( ES_VALIDO ( p_descObj ) )
	{
		iRes = SCampEsValido ( p_descObj->p_campValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SDescEstablecer ( SDescripcion * p_descObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_descObj ) )
	{
		iRes = SCampEstablecer ( p_descObj->p_campValor, p_cadValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SDescEstablecerLit ( SDescripcion * p_descObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_descObj ) )
	{
		iRes = SCampEstablecerLit ( p_descObj->p_campValor, p_cValor );
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
		iRes = SCampLimpiar ( p_descObj->p_campValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SDescEstaVacia ( SDescripcion * p_descObj )
{
	int iRes;

	if ( ES_VALIDO ( p_descObj ) )
	{
		iRes = SCampEstaVacio ( p_descObj->p_campValor );
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

int SDescAsignar ( SDescripcion * p_descObj, SDescripcion * p_descValor )
{
	int iRes;

	if ( ES_VALIDO ( p_descObj ) )
	{
		iRes = SDescEstablecer ( p_descObj, SDescValor ( p_descValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SDescAsignarCampo ( SDescripcion * p_descObj, SCampo * p_campValor )
{
	int iRes;

	if ( ES_VALIDO ( p_descObj ) )
	{
		iRes = SDescEstablecer ( p_descObj, SCampValor ( p_campValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SDescripcion * SDescDuplicar ( SDescripcion * p_descObj )
{
	SDescripcion * p_descCopia;

	if ( ES_VALIDO ( p_descObj ) )
	{
		p_descCopia = SDescCrearValorExt ( SDescValor ( p_descObj ), SDescMaxLongitud ( p_descObj ) );
	}
	else
	{
		p_descCopia = NULL;
	}
	return ( p_descCopia );
}

int SDescEsIgual ( SDescripcion * p_descObj, SDescripcion * p_descValor )
{
	int iRes;

	if ( ES_VALIDO ( p_descObj ) && ES_VALIDO ( p_descValor ) )
	{
		iRes = SDescEsIgualCad ( p_descObj, SDescValor ( p_descValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SDescEsMenor ( SDescripcion * p_descObj, SDescripcion * p_descValor )
{
	int iRes;

	if ( ES_VALIDO ( p_descObj ) && ES_VALIDO ( p_descValor ) )
	{
		iRes = SDescEsMenorCad ( p_descObj, SDescValor ( p_descValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SDescEsMayor ( SDescripcion * p_descObj, SDescripcion * p_descValor )
{
	int iRes;

	if ( ES_VALIDO ( p_descObj ) && ES_VALIDO ( p_descValor ) )
	{
		iRes = SDescEsMayorCad ( p_descObj, SDescValor ( p_descValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SDescEsDiferente ( SDescripcion * p_descObj, SDescripcion * p_descValor )
{
	int iRes;

	if ( ES_VALIDO ( p_descObj ) && ES_VALIDO ( p_descValor ) )
	{
		iRes = SDescEsDiferenteCad ( p_descObj, SDescValor ( p_descValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SDescEsMenorIg ( SDescripcion * p_descObj, SDescripcion * p_descValor )
{
	int iRes;

	if ( ES_VALIDO ( p_descObj ) && ES_VALIDO ( p_descValor ) )
	{
		iRes = SDescEsMenorIgCad ( p_descObj, SDescValor ( p_descValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SDescEsMayorIg ( SDescripcion * p_descObj, SDescripcion * p_descValor )
{
	int iRes;

	if ( ES_VALIDO ( p_descObj ) && ES_VALIDO ( p_descValor ) )
	{
		iRes = SDescEsMayorIgCad ( p_descObj, SDescValor ( p_descValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SDescEsIgualCampo ( SDescripcion * p_descObj, SCampo * p_campValor )
{
	int iRes;

	if ( ES_VALIDO ( p_descObj ) && ES_VALIDO ( p_campValor ) )
	{
		iRes = SDescEsIgualCad ( p_descObj, SCampValor ( p_campValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SDescEsMenorCampo ( SDescripcion * p_descObj, SCampo * p_campValor )
{
	int iRes;

	if ( ES_VALIDO ( p_descObj ) && ES_VALIDO ( p_campValor ) )
	{
		iRes = SDescEsMenorCad ( p_descObj, SCampValor ( p_campValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SDescEsMayorCampo ( SDescripcion * p_descObj, SCampo * p_campValor )
{
	int iRes;

	if ( ES_VALIDO ( p_descObj ) && ES_VALIDO ( p_campValor ) )
	{
		iRes = SDescEsMayorCad ( p_descObj, SCampValor ( p_campValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SDescEsDiferenteCampo ( SDescripcion * p_descObj, SCampo * p_campValor )
{
	int iRes;

	if ( ES_VALIDO ( p_descObj ) && ES_VALIDO ( p_campValor ) )
	{
		iRes = SDescEsDiferenteCad ( p_descObj, SCampValor ( p_campValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SDescEsMenorIgCampo ( SDescripcion * p_descObj, SCampo * p_campValor )
{
	int iRes;

	if ( ES_VALIDO ( p_descObj ) && ES_VALIDO ( p_campValor ) )
	{
		iRes = SDescEsMenorIgCad ( p_descObj, SCampValor ( p_campValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SDescEsMayorIgCampo ( SDescripcion * p_descObj, SCampo * p_campValor )
{
	int iRes;

	if ( ES_VALIDO ( p_descObj ) && ES_VALIDO ( p_campValor ) )
	{
		iRes = SDescEsMayorIgCad ( p_descObj, SCampValor ( p_campValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SDescEsIgualCad ( SDescripcion * p_descObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_descObj ) && ES_VALIDO ( p_cadValor ) )
	{
		iRes = SCadEsIgual ( SDescValor ( p_descObj ), p_cadValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SDescEsMenorCad ( SDescripcion * p_descObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_descObj ) && ES_VALIDO ( p_cadValor ) )
	{
		iRes = SCadEsMenor ( SDescValor ( p_descObj ), p_cadValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SDescEsMayorCad ( SDescripcion * p_descObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_descObj ) && ES_VALIDO ( p_cadValor ) )
	{
		iRes = SCadEsMayor ( SDescValor ( p_descObj ), p_cadValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SDescEsDiferenteCad ( SDescripcion * p_descObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_descObj ) && ES_VALIDO ( p_cadValor ) )
	{
		iRes = SCadEsDiferente ( SDescValor ( p_descObj ), p_cadValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SDescEsMenorIgCad ( SDescripcion * p_descObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_descObj ) && ES_VALIDO ( p_cadValor ) )
	{
		iRes = SCadEsMenorIg ( SDescValor ( p_descObj ), p_cadValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SDescEsMayorIgCad ( SDescripcion * p_descObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_descObj ) && ES_VALIDO ( p_cadValor ) )
	{
		iRes = SCadEsMayorIg ( SDescValor ( p_descObj ), p_cadValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SDescEsIgualLit ( SDescripcion * p_descObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_descObj ) && ES_VALIDO ( p_cValor ) )
	{
		iRes = SCadEsIgualLiteral ( SDescValor ( p_descObj ), p_cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SDescEsMenorLit ( SDescripcion * p_descObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_descObj ) && ES_VALIDO ( p_cValor ) )
	{
		iRes = SCadEsMenorLiteral ( SDescValor ( p_descObj ), p_cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SDescEsMayorLit ( SDescripcion * p_descObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_descObj ) && ES_VALIDO ( p_cValor ) )
	{
		iRes = SCadEsMayorLiteral ( SDescValor ( p_descObj ), p_cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SDescEsDiferenteLit ( SDescripcion * p_descObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_descObj ) && ES_VALIDO ( p_cValor ) )
	{
		iRes = SCadEsDiferenteLiteral ( SDescValor ( p_descObj ), p_cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SDescEsMenorIgLit ( SDescripcion * p_descObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_descObj ) && ES_VALIDO ( p_cValor ) )
	{
		iRes = SCadEsMenorIgLiteral ( SDescValor ( p_descObj ), p_cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SDescEsMayorIgLit ( SDescripcion * p_descObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_descObj ) && ES_VALIDO ( p_cValor ) )
	{
		iRes = SCadEsMayorIgLiteral ( SDescValor ( p_descObj ), p_cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SDescComparar ( SDescripcion * p_descObj, SDescripcion * p_descValor )
{
	int iRes;

	if ( ES_VALIDO ( p_descObj ) && ES_VALIDO ( p_descValor ) )
	{
		iRes = SDescCompararCad ( p_descObj, SDescValor ( p_descValor ) );
	}
	else if ( ES_VALIDO ( p_descObj ) )
	{
		iRes = COMP_MAYOR;
	}
	else if ( ES_VALIDO ( p_descValor ) )
	{
		iRes = COMP_MENOR;
	}
	else
	{
		iRes = COMP_IGUAL;
	}
	return ( iRes );
}

int SDescCompararCampo ( SDescripcion * p_descObj, SCampo * p_campValor )
{
	int iRes;

	if ( ES_VALIDO ( p_descObj ) && ES_VALIDO ( p_campValor ) )
	{
		iRes = SCampComparar ( p_descObj->p_campValor, p_campValor );
	}
	else if ( ES_VALIDO ( p_descObj ) )
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

int SDescCompararCad ( SDescripcion * p_descObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_descObj ) && ES_VALIDO ( p_cadValor ) )
	{
		iRes = SCadComparar ( SDescValor ( p_descObj ), p_cadValor );
	}
	else if ( ES_VALIDO ( p_descObj ) )
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

int SDescCompararLit ( SDescripcion * p_descObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_descObj ) && ES_VALIDO ( p_cValor ) )
	{
		iRes = SCadCompararLiteral ( SDescValor ( p_descObj ), p_cValor );
	}
	else if ( ES_VALIDO ( p_descObj ) )
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

int SDescCumpleExpReg ( SDescripcion * p_descObj, const char * p_cExpReg )
{
	int iRes;

	if ( ES_VALIDO ( p_descObj ) )
	{
		iRes = SCadCumpleExpReg ( SDescValor ( p_descObj ), p_cExpReg );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}



