/******************************************************************************/
/*                                SToken.cpp                                  */
/*----------------------------------------------------------------------------*/
/* Librería:  GTexto                                                          */
/* Versión:   1.0.0                                                           */
/* Fecha:     30/06/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de código fuente que contiene la implementación de la clase de     */
/* datos SToken.                                                              */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#include "SToken.h"
#include "Cadenas.h"

#include "TextoConfig.h"






int _STokCopiarConFormatoVararg ( SToken * p_tokObj, const char * p_cFormato, va_list valArgumentos );






SToken * STokCrear ( int iLong )
{
	SToken * p_tokObj;
	
	if ( iLong > 0 )
	{
		p_tokObj = (SToken *) MemReservar ( sizeof ( SToken ) );
		if ( ES_VALIDO ( p_tokObj ) )
		{
			p_tokObj->p_cadValor = SCadCrear ( iLong );
			if ( ES_NULO ( p_tokObj->p_cadValor ) )
			{
				MemLiberar ( (void **) &p_tokObj );
			}
		}
	}
	else
	{
		p_tokObj = NULL;
	}
	return ( p_tokObj );
}

SToken * STokGenerar ( SCadena * p_cadValor )
{
	SToken *	p_tokObj;
	int			iLong;
	
	if ( SCadEsValida ( p_cadValor ) == 1 )
	{
		if ( CadEsTokenValido ( SCadValor ( p_cadValor ) ) == 1 )
		{
			iLong = SCadLongitud ( p_cadValor ); 
			p_tokObj = STokCrear ( iLong );
			if ( ES_VALIDO ( p_tokObj ) )
			{
				if ( STokCopiarCadena ( p_tokObj, p_cadValor ) == 0 )
				{
					MemLiberar ( (void **) &p_tokObj );
				}
			}
		}
		else
		{
			p_tokObj = NULL;
		}
	}
	else
	{
		p_tokObj = NULL;
	}
	return ( p_tokObj );
}

SToken * STokGenerarLit ( const char * p_cValor )
{
	SToken *	p_tokObj;
	int			iLong;
	
	if ( ES_VALIDO ( p_cValor ) )
	{
		if ( CadEsTokenValido ( p_cValor ) == 1 )
		{
			iLong = CadLongitud ( p_cValor ); 
			p_tokObj = STokCrear ( iLong );
			if ( ES_VALIDO ( p_tokObj ) )
			{
				if ( STokCopiarLiteral ( p_tokObj, p_cValor ) == 0 )
				{
					MemLiberar ( (void **) &p_tokObj );
				}
			}
		}
		else
		{
			p_tokObj = NULL;
		}
	}
	else
	{
		p_tokObj = NULL;
	}
	return ( p_tokObj );
}

void STokDestruir ( SToken ** p_p_tokObj )
{
	SToken * p_tokObj;
	
	if ( ES_VALIDO ( p_p_tokObj ) )
	{
		p_tokObj = *p_p_tokObj;

		if ( ES_VALIDO ( p_tokObj ) )
		{
			SCadDestruir ( &(p_tokObj->p_cadValor) );
			MemLiberar ( (void **) p_p_tokObj );
		}
	}
}

int STokInicializar ( SToken * p_tokObj, int iLong )
{
	int iRes;

	if ( ES_VALIDO ( p_tokObj ) )
	{
		iRes = SCadInicializar ( p_tokObj->p_cadValor, iLong );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int STokVaciar ( SToken * p_tokObj )
{
	int iRes;

	if ( ES_VALIDO ( p_tokObj ) )
	{
		iRes = SCadVaciar ( p_tokObj->p_cadValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int STokEstaVacio ( SToken * p_tokObj )
{
	int iRes;

	if ( ES_VALIDO ( p_tokObj ) )
	{
		if ( SCadEsValida ( p_tokObj->p_cadValor ) == 1 )
		{
			if ( SCadLongitud ( p_tokObj->p_cadValor ) <= 0 )
			{
				iRes = 1;
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

SCadena * STokValor ( SToken * p_tokObj )
{
	SCadena * p_cadRes;

	if ( ES_VALIDO ( p_tokObj ) )
	{
		p_cadRes = p_tokObj->p_cadValor;
	}
	else
	{
		p_cadRes = NULL;
	}
	return ( p_cadRes );
}

const char * STokValorLit ( SToken * p_tokObj )
{
	const char * p_cRes;

	if ( ES_VALIDO ( p_tokObj ) )
	{
		p_cRes = SCadValorConstante ( p_tokObj->p_cadValor );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

char STokCaracter ( SToken * p_tokObj, int iCar )
{
	char cRes;

	if ( ES_VALIDO ( p_tokObj ) )
	{
		cRes = SCadCaracter  ( p_tokObj->p_cadValor, iCar );
	}
	else
	{
		cRes = ASCII_NUL;
	}
	return ( cRes );
}

int STokEstablecerCaracter ( SToken * p_tokObj, int iCar, char cVal )
{
	int iRes;

	if ( ES_VALIDO ( p_tokObj ) )
	{
		if ( iCar == 0 )
		{
			if ( ASCIIEsValidoInicioToken ( cVal ) == 1 )
			{
				iRes = SCadEstablecerCaracter ( p_tokObj->p_cadValor, iCar, cVal );
			}
			else
			{
				iRes = 0;
			}
		}
		else
		{
			if ( ASCIIEsValidoToken ( cVal ) == 1 )
			{
				iRes = SCadEstablecerCaracter ( p_tokObj->p_cadValor, iCar, cVal );
			}
			else
			{
				iRes = 0;
			}
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int STokCopiarCadena ( SToken * p_tokObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_tokObj ) )
	{
		if ( SCadEsToken ( p_cadValor ) == 1 )
		{
			iRes = SCadCopiar ( p_tokObj->p_cadValor, p_cadValor );
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

int STokCopiarLiteral ( SToken * p_tokObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_tokObj ) )
	{
		if ( CadEsToken ( p_cValor ) == 1 )
		{
			iRes = SCadCopiarLiteral ( p_tokObj->p_cadValor, p_cValor );
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

int STokCopiar ( SToken * p_tokObj, SToken * p_tokValor )
{
	int iRes;

	if ( ES_VALIDO ( p_tokObj ) && ES_VALIDO ( p_tokValor ) )
	{
		iRes = STokCopiarCadena ( p_tokObj, STokValor ( p_tokValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int STokCopiarCaracter ( SToken * p_tokObj, char cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_tokObj ) )
	{
		if ( ASCIIEsValidoInicioToken ( cValor ) == 1 )
		{
			iRes = SCadCopiarCaracter ( p_tokObj->p_cadValor, cValor );
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

int STokCopiarConFormato ( SToken * p_tokObj, const char * p_cFormato, ... )
{
	int		iRes;
	va_list valArgumentos;

	if ( ES_VALIDO ( p_tokObj ) && ES_VALIDO ( p_cFormato ) )
	{
		va_start ( valArgumentos,  p_cFormato );
		iRes = _STokCopiarConFormatoVararg ( p_tokObj, p_cFormato, valArgumentos );
		va_end ( valArgumentos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int _STokCopiarConFormatoVararg ( SToken * p_tokObj, const char * p_cFormato, va_list valArgumentos  )
{
	int		iRes;
	char *	p_cCadena;

	if ( ES_VALIDO ( p_tokObj ) && ES_VALIDO ( p_cFormato ) )
	{
		p_cCadena = CadCrear ( CAD_TAM_DEFECTO );
		if ( ES_VALIDO ( p_cCadena ) )
		{
			if ( FrmCadena ( p_cCadena, p_cFormato, valArgumentos, CAD_TAM_DEFECTO ) == 1 )
			{
				iRes = STokCopiarLiteral ( p_tokObj, p_cCadena );
			}
			else
			{
				iRes = 0;
			}
			MemLiberar ( (void **) &p_cCadena );
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

int STokLongitud ( SToken * p_tokObj )
{
	int iRes;

	if ( ES_VALIDO ( p_tokObj ) )
	{
		iRes = SCadLongitud ( p_tokObj->p_cadValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int STokMaxTam ( SToken * p_tokObj )
{
	int iRes;

	if ( ES_VALIDO ( p_tokObj ) )
	{
		iRes = SCadMaxTam ( p_tokObj->p_cadValor );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int STokAsignar ( SToken * p_tokObj, SToken * p_tokValor )
{
	int iRes;

	if ( ES_VALIDO ( p_tokObj ) )
	{
		if ( SCadVaciar ( p_tokObj->p_cadValor ) == 1 )
		{
			iRes = STokCopiar ( p_tokObj, p_tokValor );
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

int STokEstablecer ( SToken * p_tokObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_tokObj ) )
	{
		if ( SCadVaciar ( p_tokObj->p_cadValor ) == 1 )
		{
			iRes = STokCopiarCadena ( p_tokObj, p_cadValor );
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

int STokEstablecerLit ( SToken * p_tokObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_tokObj ) )
	{
		if ( SCadVaciar ( p_tokObj->p_cadValor ) == 1 )
		{
			iRes = STokCopiarLiteral ( p_tokObj, p_cValor );
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

SToken * STokDuplicar ( SToken * p_tokObj )
{
	SToken * p_tokCopia;

	if ( ES_VALIDO ( p_tokObj ) )
	{
		p_tokCopia = STokGenerar ( p_tokObj->p_cadValor );
	}
	else
	{
		p_tokCopia = NULL;
	}
	return ( p_tokCopia );
}

SCadena * STokDuplicarCadena ( SToken * p_tokObj )
{
	SCadena * p_cadRes;

	if ( ES_VALIDO ( p_tokObj ) )
	{
		p_cadRes = SCadDuplicar ( p_tokObj->p_cadValor );
	}
	else
	{
		p_cadRes = NULL;
	}
	return ( p_cadRes );
}

char * STokDuplicarValor ( SToken * p_tokObj )
{
	char * p_cRes;

	if ( ES_VALIDO ( p_tokObj ) )
	{
		p_cRes = SCadDuplicarValor ( p_tokObj->p_cadValor );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int STokEsIgual ( SToken * p_tokObj, SToken * p_tokValor )
{
	int iRes;

	if ( ES_VALIDO ( p_tokObj ) && ES_VALIDO ( p_tokValor ) )
	{
		iRes = STokEsIgualCad ( p_tokObj, STokValor ( p_tokValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int STokEsMenor ( SToken * p_tokObj, SToken * p_tokValor )
{
	int iRes;

	if ( ES_VALIDO ( p_tokObj ) && ES_VALIDO ( p_tokValor ) )
	{
		iRes = STokEsMenorCad ( p_tokObj, STokValor ( p_tokValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int STokEsMayor ( SToken * p_tokObj, SToken * p_tokValor )
{
	int iRes;

	if ( ES_VALIDO ( p_tokObj ) && ES_VALIDO ( p_tokValor ) )
	{
		iRes = STokEsMayorCad ( p_tokObj, STokValor ( p_tokValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int STokEsDiferente ( SToken * p_tokObj, SToken * p_tokValor )
{
	int iRes;

	if ( ES_VALIDO ( p_tokObj ) && ES_VALIDO ( p_tokValor ) )
	{
		iRes = STokEsDiferenteCad ( p_tokObj, STokValor ( p_tokValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int STokEsIgualCad ( SToken * p_tokObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_tokObj ) && ES_VALIDO ( p_cadValor ) )
	{
		iRes = SCadEsIgual ( p_tokObj->p_cadValor, p_cadValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int STokEsMenorCad ( SToken * p_tokObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_tokObj ) && ES_VALIDO ( p_cadValor ) )
	{
		iRes = SCadEsMenor ( p_tokObj->p_cadValor, p_cadValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int STokEsMayorCad ( SToken * p_tokObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_tokObj ) && ES_VALIDO ( p_cadValor ) )
	{
		iRes = SCadEsMayor ( p_tokObj->p_cadValor, p_cadValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int STokEsDiferenteCad ( SToken * p_tokObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_tokObj ) && ES_VALIDO ( p_cadValor ) )
	{
		iRes = SCadEsDiferente ( p_tokObj->p_cadValor, p_cadValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int STokEsIgualLit ( SToken * p_tokObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_tokObj ) && ES_VALIDO ( p_cValor ) )
	{
		iRes = SCadEsIgualLiteral ( p_tokObj->p_cadValor, p_cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int STokEsMenorLit ( SToken * p_tokObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_tokObj ) && ES_VALIDO ( p_cValor ) )
	{
		iRes = SCadEsMenorLiteral ( p_tokObj->p_cadValor, p_cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int STokEsMayorLit ( SToken * p_tokObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_tokObj ) && ES_VALIDO ( p_cValor ) )
	{
		iRes = SCadEsMayorLiteral ( p_tokObj->p_cadValor, p_cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int STokEsDiferenteLit ( SToken * p_tokObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_tokObj ) && ES_VALIDO ( p_cValor ) )
	{
		iRes = SCadEsDiferenteLiteral ( p_tokObj->p_cadValor, p_cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int STokComparar ( SToken * p_tokObj, SToken * p_tokValor )
{
	int iRes;

	if ( ES_VALIDO ( p_tokObj ) && ES_VALIDO ( p_tokValor ) )
	{
		iRes = STokCompararCad ( p_tokObj, STokValor ( p_tokValor ) );
	}
	else if ( ES_VALIDO ( p_tokObj ) )
	{
		iRes = COMP_MAYOR;
	}
	else if ( ES_VALIDO ( p_tokValor ) )
	{
		iRes = COMP_MENOR;
	}
	else
	{
		iRes = COMP_IGUAL;
	}
	return ( iRes );
}

int STokCompararCad ( SToken * p_tokObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_tokObj ) && ES_VALIDO ( p_cadValor ) )
	{
		iRes = SCadComparar ( p_tokObj->p_cadValor, p_cadValor );
	}
	else if ( ES_VALIDO ( p_tokObj ) )
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

int STokCompararLit ( SToken * p_tokObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_tokObj ) && ES_VALIDO ( p_cValor ) )
	{
		iRes = SCadCompararLiteral ( p_tokObj->p_cadValor, p_cValor );
	}
	else if ( ES_VALIDO ( p_tokObj ) )
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

int STokCumpleExpReg ( SToken * p_tokObj, const char * p_cExpReg )
{
	int iRes;

	if ( ES_VALIDO ( p_tokObj ) )
	{
		iRes = SCadCumpleExpReg ( p_tokObj->p_cadValor, p_cExpReg );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

