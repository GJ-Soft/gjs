/******************************************************************************/
/*                                SCadena.cpp                                 */
/*----------------------------------------------------------------------------*/
/* Librería:  GTexto                                                          */
/* Versión:   1.0.0                                                           */
/* Fecha:     30/06/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de código fuente que contiene la implementación de la clase de     */
/* datos SCadena.                                                             */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#include "SCadena.h"


#include "Cadenas.h"


#include "TextoConfig.h"




//extern int HTMLTieneCodificacion ( SCadena * p_cadObj, char cVal );
//extern const char * HTMLCodificar ( SCadena * p_cadObj, char cVal );




SCadena * SCadCrearDef ()
{
	return ( SCadCrear ( CAD_TAM_DEFECTO ) );
}

SCadena * SCadCrear ( int iLong )
{
	SCadena * p_cadObj;
	
	if ( iLong > 0 )
	{
		p_cadObj = (SCadena *) MemReservar ( sizeof ( SCadena ) );
		if ( ES_VALIDO ( p_cadObj ) )
		{
			p_cadObj->p_cValor = NULL;
			p_cadObj->iDistincionTipoLetra = 1;
			if ( SCadInicializar ( p_cadObj, iLong ) == 0 )
			{
				MemLiberar ( (void **) &p_cadObj );
			}
		}
	}
	else
	{
		p_cadObj = NULL;
	}
	return ( p_cadObj );
}

SCadena * SCadCrearLlena ( int iLong, char cRelleno )
{
	SCadena * p_cadObj;

	p_cadObj = SCadCrear ( iLong );
	SCadLlenar ( p_cadObj, cRelleno );
	return ( p_cadObj );
}
	
SCadena * SCadGenerar ( const char * p_cValor )
{
	SCadena *	p_cadObj;
	int			iLong;
	
	if ( ES_VALIDO ( p_cValor ) )
	{
		iLong = CadLongitud ( p_cValor ); 
		p_cadObj = SCadCrear ( iLong );
		if ( ES_VALIDO ( p_cadObj ) )
		{
			if ( SCadCopiarLiteral ( p_cadObj, p_cValor ) == 0 )
			{
				MemLiberar ( (void **) &p_cadObj );
			}
		}
	}
	else
	{
		p_cadObj = NULL;
	}
	return ( p_cadObj );
}

SCadena * SCadGenerarConFormato ( const char * p_cFormato, ... )
{
	SCadena *	p_cadObj;
	va_list		valArgumentos;

	va_start ( valArgumentos,  p_cFormato );
	p_cadObj = SCadGenerarConFormatoExt ( p_cFormato, valArgumentos );
	va_end ( valArgumentos );
	return ( p_cadObj );
}

SCadena * SCadGenerarConFormatoExt ( const char * p_cFormato, va_list valArgumentos )
{
	SCadena *	p_cadObj;
	int			iLong;

	if ( ES_VALIDO ( p_cFormato ) )
	{
		iLong = CAD_MAX_TAM; 
		p_cadObj = SCadCrear ( iLong );
		if ( ES_VALIDO ( p_cadObj ) )
		{
			if ( SCadCopiarConFormato ( p_cadObj, p_cFormato, valArgumentos ) == 1 )
			{
				SCadAjustarMaxTam ( p_cadObj );
			}
			else
			{
				SCadDestruir ( &p_cadObj );
			}
		}
	}
	else
	{
		p_cadObj = NULL;
	}
	return ( p_cadObj );
}

void SCadDestruir ( SCadena ** p_p_cadObj )
{
	SCadena * p_cadObj;
	
	if ( ES_VALIDO ( p_p_cadObj ) )
	{
		p_cadObj = *p_p_cadObj;

		if ( ES_VALIDO ( p_cadObj ) )
		{
			SCadVaciar ( p_cadObj );
			MemLiberar ( (void **) p_p_cadObj );
		}
	}
}

int SCadInicializar ( SCadena * p_cadObj, int iLong )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		SCadVaciar ( p_cadObj );
		if ( iLong > 0 )
		{
			if ( iLong > CAD_MAX_TAM )
			{
				p_cadObj->iMaxTam = CAD_MAX_TAM;
			}
			else
			{
				p_cadObj->iMaxTam = iLong;
			}
			p_cadObj->p_cValor = CadCrear ( p_cadObj->iMaxTam );
			if ( ES_VALIDO ( p_cadObj->p_cValor ) )
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

int SCadVaciar ( SCadena * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		if ( ES_VALIDO ( p_cadObj->p_cValor ) )
		{
			MemLiberar ( (void **) &(p_cadObj->p_cValor) );
		}
		p_cadObj->p_cValor = NULL;
		p_cadObj->iMaxTam = 0;
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadLimpiar ( SCadena * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		CadInicializar ( p_cadObj->p_cValor, p_cadObj->iMaxTam );
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadLlenar ( SCadena * p_cadObj, char cVal )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		CadLimpiarExt ( p_cadObj->p_cValor, cVal, p_cadObj->iMaxTam );
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadLimpiarDesde ( SCadena * p_cadObj, int iPos )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		CadLimpiarDesdeExt ( p_cadObj->p_cValor, iPos, (char) 0, p_cadObj->iMaxTam );
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadLlenarDesde ( SCadena * p_cadObj, int iPos, char cVal )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		CadLimpiarDesdeExt ( p_cadObj->p_cValor, iPos, cVal, p_cadObj->iMaxTam );
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadEsValida ( SCadena * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		if ( ES_VALIDO ( p_cadObj->p_cValor ) )
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
	return ( iRes );
}

int SCadEsNula ( SCadena * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		if ( ES_NULO ( p_cadObj->p_cValor ) )
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
	return ( iRes );
}

int SCadEstaVacia ( SCadena * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		if ( ES_VALIDO ( p_cadObj->p_cValor ) )
		{
			if ( CadLongitud ( p_cadObj->p_cValor ) <= 0 )
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
			iRes = 1;
		}
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

char * SCadValor ( SCadena * p_cadObj )
{
	char * p_cRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		p_cRes = p_cadObj->p_cValor;
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

const char * SCadValorConstante ( SCadena * p_cadObj )
{
	return ( (const char *) SCadValor ( p_cadObj ) );
}

char SCadCaracter ( SCadena * p_cadObj, int iCar )
{
	char cRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		cRes = CadCaracterExt  ( p_cadObj->p_cValor, iCar, p_cadObj->iMaxTam );
	}
	else
	{
		cRes = ASCII_NUL;
	}
	return ( cRes );
}

int SCadEstablecerCaracter ( SCadena * p_cadObj, int iCar, char cVal )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = CadEstablecerCaracterExt ( p_cadObj->p_cValor, iCar, cVal, p_cadObj->iMaxTam );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadCopiarLiteral ( SCadena * p_cadObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		if ( ES_NULO ( p_cadObj->p_cValor ) )
		{
			p_cadObj->iMaxTam = CadLongitud ( p_cValor );
			p_cadObj->p_cValor = CadCrear ( p_cadObj->iMaxTam );
		}
		iRes = CadCopiarExt ( p_cadObj->p_cValor, p_cValor, p_cadObj->iMaxTam, -1 );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadConcatenarLiteral ( SCadena * p_cadObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		if ( ES_NULO ( p_cadObj->p_cValor ) )
		{
			iRes = SCadCopiarLiteral ( p_cadObj, p_cValor );
		}
		else
		{
			iRes = CadConcatenarExt ( p_cadObj->p_cValor, p_cValor, p_cadObj->iMaxTam, -1 );
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadCopiar ( SCadena * p_cadObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) && ES_VALIDO ( p_cadValor ) )
	{
		iRes = SCadCopiarLiteral ( p_cadObj, SCadValorConstante ( p_cadValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadConcatenar ( SCadena * p_cadObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) && ES_VALIDO ( p_cadValor ) )
	{
		iRes = SCadConcatenarLiteral ( p_cadObj, SCadValorConstante ( p_cadValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadCopiarCaracter ( SCadena * p_cadObj, char cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		if ( ES_NULO ( p_cadObj->p_cValor ) )
		{
			p_cadObj->iMaxTam = 1;
			p_cadObj->p_cValor = CadCrear ( p_cadObj->iMaxTam );
		}
		p_cadObj->p_cValor [ 0 ] = cValor;
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadConcatenarCaracter ( SCadena * p_cadObj, char cValor )
{
	int iLong;
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		if ( ES_NULO ( p_cadObj->p_cValor ) )
		{
			SCadCopiarCaracter ( p_cadObj, cValor );
		}
		else
		{
			iLong = SCadLongitud ( p_cadObj );
			if ( iLong < p_cadObj->iMaxTam ) 
			{
				p_cadObj->p_cValor [ iLong ] = cValor;
				p_cadObj->p_cValor [ iLong + 1 ] = (char) 0;
			}
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadCopiarConFormato ( SCadena * p_cadObj, const char * p_cFormato, ... )
{
	int		iRes;
	va_list valArgumentos;

	if ( ES_VALIDO ( p_cadObj ) && ES_VALIDO ( p_cFormato ) )
	{
		va_start ( valArgumentos,  p_cFormato );
		iRes = SCadCopiarConFormatoExt ( p_cadObj, p_cFormato, valArgumentos );
		va_end ( valArgumentos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadCopiarConFormatoExt ( SCadena * p_cadObj, const char * p_cFormato, va_list valArgumentos  )
{
	int		iRes;
	char *	p_cCadena;

	if ( ES_VALIDO ( p_cadObj ) && ES_VALIDO ( p_cFormato ) )
	{
		p_cCadena = CadCrear ( CAD_TAM_DEFECTO );
		if ( ES_VALIDO ( p_cCadena ) )
		{
			if ( FrmCadena ( p_cCadena, p_cFormato, valArgumentos, CAD_TAM_DEFECTO ) == 1 )
			{
				iRes = SCadCopiarLiteral ( p_cadObj, p_cCadena );
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

int SCadConcatenarConFormato ( SCadena * p_cadObj, const char * p_cFormato, ... )
{
	int		iRes;
	va_list valArgumentos;

	if ( ES_VALIDO ( p_cadObj ) && ES_VALIDO ( p_cFormato ) )
	{
		va_start ( valArgumentos,  p_cFormato );
		iRes = SCadConcatenarConFormatoExt ( p_cadObj, p_cFormato, valArgumentos );
		va_end ( valArgumentos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadConcatenarConFormatoExt ( SCadena * p_cadObj, const char * p_cFormato, va_list valArgumentos )
{
	int		iRes;
	char *	p_cCadena;

	if ( ES_VALIDO ( p_cadObj ) && ES_VALIDO ( p_cFormato ) )
	{
		p_cCadena = CadCrear ( CAD_TAM_DEFECTO );
		if ( ES_VALIDO ( p_cCadena ) )
		{
			if ( FrmCadena ( p_cCadena, p_cFormato, valArgumentos, CAD_TAM_DEFECTO ) == 1 )
			{
				if ( ES_NULO ( p_cadObj->p_cValor ) )
				{
					iRes = SCadCopiarLiteral ( p_cadObj, p_cCadena );
				}
				else
				{
					iRes = SCadConcatenarLiteral ( p_cadObj, p_cCadena );
				}
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

int SCadLongitud ( SCadena * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = CadLongitudSeg ( p_cadObj->p_cValor, p_cadObj->iMaxTam );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadMaxTam ( SCadena * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		if ( ES_VALIDO ( p_cadObj->p_cValor ) )
		{
			iRes = p_cadObj->iMaxTam;
		}
		else
		{
			iRes = -1;
		}
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SCadEspacioLibre ( SCadena * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadMaxTam ( p_cadObj ) - SCadLongitud ( p_cadObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadInsertar ( SCadena * p_cadObj, int iPos, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) && ES_VALIDO ( p_cadValor ) && ( iPos >= 0 ) )
	{
		iRes = SCadInsertarLiteral ( p_cadObj, iPos, SCadValorConstante ( p_cadValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadInsertarLiteral ( SCadena * p_cadObj, int iPos, const char * p_cValor )
{
	int iLon;
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) && ( iPos >= 0 ) )
	{
		if ( ES_NULO ( p_cadObj->p_cValor ) )
		{
			iRes = SCadCopiarLiteral ( p_cadObj, p_cValor );
		}
		else 
		{
			iLon = CadLongitud ( p_cadObj->p_cValor );
			if ( iPos >= iLon )
			{
				iRes = SCadConcatenarLiteral ( p_cadObj, p_cValor );
			}
			else
			{
				iRes = CadInsertar ( p_cadObj->p_cValor, iPos, p_cValor );
			}
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadInsertarCaracter ( SCadena * p_cadObj, int iPos, char cValor )
{
	int iLon;
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) && ( iPos >= 0 ) )
	{
		if ( ES_NULO ( p_cadObj->p_cValor ) )
		{
			iRes = SCadCopiarCaracter ( p_cadObj, cValor );
		}
		else 
		{
			iLon = CadLongitud ( p_cadObj->p_cValor );
			if ( iPos >= iLon )
			{
				iRes = SCadConcatenarCaracter ( p_cadObj, cValor );
			}
			else
			{
				iRes = CadInsertarCaracter ( p_cadObj->p_cValor, iPos, cValor );
			}
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadEscribir ( SCadena * p_cadObj, int iPos, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) && ES_VALIDO ( p_cadValor ) && ( iPos >= 0 ) )
	{
		iRes = SCadEscribirLiteral ( p_cadObj, iPos, SCadValorConstante ( p_cadValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadEscribirLiteral ( SCadena * p_cadObj, int iPos, const char * p_cValor )
{
	char *	p_cEspacios;
	int		iLon;
	int		iRes;

	if ( ES_VALIDO ( p_cadObj ) && ( iPos >= 0 ) )
	{
		iLon = CadLongitud ( p_cadObj->p_cValor );
		if ( iPos > iLon )
		{
			p_cEspacios = CadCrear ( iPos - iLon );
			if ( ES_VALIDO ( p_cEspacios ) )
			{
				CadLimpiarExt ( p_cEspacios, ' ', iPos - iLon );
				iRes = SCadConcatenarLiteral ( p_cadObj, p_cEspacios );
				MemLiberar ( (void **) &p_cEspacios );
				iLon = CadLongitud ( p_cadObj->p_cValor );
			}
			else
			{
				iRes = 0;
			}
		}

		if ( ES_NULO ( p_cadObj->p_cValor ) )
		{
			iRes = SCadCopiarLiteral ( p_cadObj, p_cValor );
		}
		else 
		{
			if ( iPos >= iLon )
			{
				iRes = SCadConcatenarLiteral ( p_cadObj, p_cValor );
			}
			else
			{
				iRes = CadEscribir ( p_cadObj->p_cValor, iPos, p_cValor );
			}
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadEscribirCaracter ( SCadena * p_cadObj, int iPos, char cValor )
{
	char *	p_cEspacios;
	int		iLon;
	int		iRes;

	if ( ES_VALIDO ( p_cadObj ) && ( iPos >= 0 ) )
	{
		iLon = CadLongitud ( p_cadObj->p_cValor );
		if ( iPos > iLon )
		{
			p_cEspacios = CadCrear ( iPos - iLon );
			if ( ES_VALIDO ( p_cEspacios ) )
			{
				CadLimpiarExt ( p_cEspacios, ' ', iPos - iLon );
				iRes = SCadConcatenarLiteral ( p_cadObj, p_cEspacios );
				MemLiberar ( (void **) &p_cEspacios );
				iLon = CadLongitud ( p_cadObj->p_cValor );
			}
			else
			{
				iRes = 0;
			}
		}

		if ( ES_NULO ( p_cadObj->p_cValor ) )
		{
			iRes = SCadCopiarCaracter ( p_cadObj, cValor );
		}
		else 
		{
			iLon = CadLongitud ( p_cadObj->p_cValor );
			if ( iPos >= iLon )
			{
				iRes = SCadConcatenarCaracter ( p_cadObj, cValor );
			}
			else
			{
				iRes = CadInsertarCaracter ( p_cadObj->p_cValor, iPos, cValor );
			}
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadAsignar ( SCadena * p_cadObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		if ( SCadVaciar ( p_cadObj ) == 1 )
		{
			iRes = SCadCopiar ( p_cadObj, p_cadValor );
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

int SCadAsignarLiteral ( SCadena * p_cadObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		if ( SCadVaciar ( p_cadObj ) == 1 )
		{
			iRes = SCadCopiarLiteral ( p_cadObj, p_cValor );
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

int SCadEstablecerMaxTam ( SCadena * p_cadObj, int iMaxTam )
{
	char *	p_cValorAux;
	int		iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		if ( iMaxTam > 0 )
		{
			if ( iMaxTam > CAD_MAX_TAM )
			{
				p_cadObj->iMaxTam = CAD_MAX_TAM;
			}
			else
			{
				p_cadObj->iMaxTam = iMaxTam;
			}

			p_cValorAux = CadCrear ( p_cadObj->iMaxTam );
			if ( ES_VALIDO ( p_cValorAux ) )
			{
				iRes = CadCopiarExt ( p_cValorAux, p_cadObj->p_cValor, p_cadObj->iMaxTam, -1 );
			}
			else
			{
				iRes = 0;
			}
			MemLiberar ( (void **) &p_cadObj->p_cValor );

			p_cadObj->p_cValor = p_cValorAux;
		}
		else
		{
			SCadVaciar ( p_cadObj );
			iRes = 0;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadAjustarMaxTam ( SCadena * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadEstablecerMaxTam ( p_cadObj, SCadLongitud ( p_cadObj ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SCadena * SCadDuplicar ( SCadena * p_cadObj )
{
	SCadena * p_cadCopia;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		p_cadCopia = SCadGenerar ( p_cadObj->p_cValor );
		if ( ES_VALIDO ( p_cadCopia ) )
		{
			p_cadCopia->iMaxTam = p_cadObj->iMaxTam;
			p_cadCopia->iDistincionTipoLetra = p_cadObj->iDistincionTipoLetra;
		}
	}
	else
	{
		p_cadCopia = NULL;
	}
	return ( p_cadCopia );
}

char * SCadDuplicarValor ( SCadena * p_cadObj )
{
	char * p_cRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		p_cRes = CadDuplicarSeg ( p_cadObj->p_cValor, SCadLongitud ( p_cadObj ) );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

char * SCadCadenaHexadecimal ( SCadena * p_cadObj )
{
	char *	p_cRes;
	int		iCar;
	int		iLong;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iLong = SCadLongitud ( p_cadObj );
		p_cRes = CadCrear ( iLong * 2 );
		if ( ES_VALIDO ( p_cRes ) )
		{
			for ( iCar = 0; iCar < iLong; iCar = iCar + 1 )
			{
				sprintf ( &(p_cRes [ iCar * 2 ]), "%02X",  (unsigned char) p_cadObj->p_cValor [ iCar ] );
			}
		}
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SCadAsignarCadenaHexadecimal ( SCadena * p_cadObj, const char * p_cValorHex )
{
	char *	p_cValorAux;
	int		iCar;
	int		iLong;
	char	cVal;
	int		iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		if ( ES_VALIDO ( p_cValorHex ) )
		{
			iLong = CadLongitud ( p_cValorHex );
			if ( iLong % 2 == 0 )
			{
				p_cValorAux = CadCrear ( iLong / 2 );
				if ( ES_VALIDO ( p_cValorAux ) )
				{
					for ( iCar = 0; iCar < iLong / 2; iCar = iCar + 1 )
					{
						cVal = (char) ( ((byte) HexValor ( p_cValorHex [ iCar * 2 ] )) * 0x10 + 
										(byte) HexValor ( p_cValorHex [ iCar * 2 + 1 ] ) );
						p_cValorAux [ iCar ] = cVal;
					}
					iRes = SCadAsignarLiteral ( p_cadObj, p_cValorAux );
					MemLiberar ( (void **) &p_cValorAux );
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
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadExpander ( SCadena * p_cadObj )
{
	return ( SCadExpanderCaracter ( p_cadObj, ' ' ) );
}

int SCadExpanderCaracter ( SCadena * p_cadObj, char cVal )
{
	int iLong;
	int iPos;
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		if ( ES_VALIDO ( p_cadObj->p_cValor ) && ( cVal > 0 ) )
		{
			if ( SCadEspacioLibre ( p_cadObj ) > 0 )
			{
				iLong = SCadLongitud ( p_cadObj );
				for ( iPos = 0; iPos < p_cadObj->iMaxTam - iLong; iPos = iPos + 1 ) 
				{	
					p_cadObj->p_cValor [ iLong + iPos ] = (char) cVal; 
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
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadContraer ( SCadena * p_cadObj )
{
	return ( SCadContraerCaracter ( p_cadObj, ' ' ) );
}

int SCadContraerCaracter ( SCadena * p_cadObj, char cVal )
{
	int iPos;
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		if ( ES_VALIDO ( p_cadObj->p_cValor ) && ( cVal > 0 ) )
		{
			iPos = SCadLongitud ( p_cadObj ) - 1;
			while ( ( p_cadObj->p_cValor [ iPos ] == cVal ) && ( iPos > 0 ) )
			{
				p_cadObj->p_cValor [ iPos ] = (char) 0;
				iPos = iPos - 1;
			}
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
	return ( iRes );
}

int SCadEliminarBlancosLaterales ( SCadena * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = CadEliminarBlancosLateralesExt ( p_cadObj->p_cValor, p_cadObj->iMaxTam );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadEliminarBlancosIzq ( SCadena * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = CadEliminarBlancosIzqExt ( p_cadObj->p_cValor, p_cadObj->iMaxTam );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadEliminarBlancosDer ( SCadena * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = CadEliminarBlancosDerExt ( p_cadObj->p_cValor, p_cadObj->iMaxTam );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadFormatearBlancos ( SCadena * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = CadFormatearBlancosExt ( p_cadObj->p_cValor, p_cadObj->iMaxTam );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadContieneBlancos ( SCadena * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = CadContieneBlancosExt ( p_cadObj->p_cValor, p_cadObj->iMaxTam );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadContieneTabuladores ( SCadena * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = CadContieneTabuladoresExt( p_cadObj->p_cValor, p_cadObj->iMaxTam );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadContieneCaracteresNoImprimibles ( SCadena * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = CadContieneCaracteresNoImprimiblesExt ( p_cadObj->p_cValor, p_cadObj->iMaxTam );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadContieneCaracteresNoAlfanumericos ( SCadena * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = CadContieneCaracteresNoAlfanumericosExt ( p_cadObj->p_cValor, p_cadObj->iMaxTam );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadContieneCaracteresNoEstandar ( SCadena * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = CadContieneCaracteresNoEstandarExt ( p_cadObj->p_cValor, p_cadObj->iMaxTam );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadEliminarCaracter ( SCadena * p_cadObj, int iCar )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = CadEliminarCaracterExt ( p_cadObj->p_cValor, iCar, p_cadObj->iMaxTam );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadEliminarCaracteres ( SCadena * p_cadObj, int iPosIni, int iNumCars )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = CadEliminarCaracteresExt ( p_cadObj->p_cValor, iPosIni, iNumCars, p_cadObj->iMaxTam );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadEliminarPrimerosCaracteres ( SCadena * p_cadObj, int iNumCars )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = CadEliminarPrimerosCaracteresExt ( p_cadObj->p_cValor, iNumCars, p_cadObj->iMaxTam );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadEliminarApariciones ( SCadena * p_cadObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) && ES_VALIDO ( p_cadValor ) )
	{
		iRes = SCadEliminarAparicionesLiteral ( p_cadObj, p_cadValor->p_cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadEliminarUltimosCaracteres ( SCadena * p_cadObj, int iNumCars )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = CadEliminarUltimosCaracteresExt ( p_cadObj->p_cValor, iNumCars, p_cadObj->iMaxTam );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadEliminarAparicionesCaracter ( SCadena * p_cadObj, char cCar )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = CadEliminarAparicionesCaracterExt ( p_cadObj->p_cValor, cCar, p_cadObj->iMaxTam );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadEliminarAparicionesLiteral ( SCadena * p_cadObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = CadEliminarAparicionesExt ( p_cadObj->p_cValor, p_cValor, p_cadObj->iMaxTam, -1 );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadEliminarBlancos ( SCadena * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = CadEliminarBlancosExt ( p_cadObj->p_cValor, p_cadObj->iMaxTam );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadEliminarTabuladores ( SCadena * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = CadEliminarTabuladoresExt ( p_cadObj->p_cValor, p_cadObj->iMaxTam );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadAlinearIzq ( SCadena * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadAlinearIzqRellenando ( p_cadObj, ' ' );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadAlinearDer ( SCadena * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadAlinearDerRellenando ( p_cadObj, ' ' );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadAlinearIzqRellenando ( SCadena * p_cadObj, char cVal )
{
	int iPosIni;
	int iPos;
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		SCadExpander ( p_cadObj );
		if ( ES_VALIDO ( p_cadObj->p_cValor ) && ( cVal > 0 ) )
		{
			iPosIni = 0;
			while ( ( p_cadObj->p_cValor [ iPosIni ] == ' ' ) && ( iPosIni < SCadLongitud ( p_cadObj ) ) )
			{
				iPosIni = iPosIni + 1;
			}
			iPos = iPosIni;
			while ( iPos < SCadLongitud ( p_cadObj ) )
			{
				p_cadObj->p_cValor [ iPos - iPosIni ] = p_cadObj->p_cValor [ iPos ];
				p_cadObj->p_cValor [ iPos ] = cVal;
				iPos = iPos + 1;
			}
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
	return ( iRes );
}

int SCadAlinearDerRellenando ( SCadena * p_cadObj, char cVal )
{
	int iPosIni;
	int iPos;
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		SCadExpander ( p_cadObj );
		if ( ES_VALIDO ( p_cadObj->p_cValor ) && ( cVal > 0 ) )
		{
			iPosIni = SCadLongitud ( p_cadObj ) - 1;
			while ( ( p_cadObj->p_cValor [ iPosIni ] == ' ' ) && ( iPosIni < SCadLongitud ( p_cadObj ) ) )
			{
				iPosIni = iPosIni - 1;
			}
			iPos = iPosIni;
			while ( iPos >= 0 )
			{
				p_cadObj->p_cValor [ SCadLongitud ( p_cadObj ) - iPosIni + iPos ] = p_cadObj->p_cValor [ iPos ];
				p_cadObj->p_cValor [ iPos ] = cVal;
				iPos = iPos - 1;
			}
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
	return ( iRes );
}

SCadena * SCadExtraer ( SCadena * p_cadObj, int iPos, int iLong )
{
	SCadena	*	p_cadSubcadena;	
	char *		p_cSubcadena;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		p_cSubcadena = CadExtraerExt ( p_cadObj->p_cValor, iPos, iLong, p_cadObj->iMaxTam );
		if ( ES_VALIDO ( p_cSubcadena ) ) 
		{
			p_cadSubcadena = SCadGenerar ( p_cSubcadena );
			if ( p_cadObj->iDistincionTipoLetra == 0 )
			{
				SCadDesactivarDistincionTipoLetra ( p_cadSubcadena );
			}
			MemLiberar ( (void **) &p_cSubcadena );
		}
		else
		{
			p_cadSubcadena = NULL;
		}
	}
	else
	{
		p_cadSubcadena = NULL;
	}
	return ( p_cadSubcadena );
}

SCadena * SCadExtraerPrimeros ( SCadena * p_cadObj, int iLong )
{
	return ( SCadExtraer ( p_cadObj, 0, iLong ) );
}

SCadena * SCadExtraerUltimos ( SCadena * p_cadObj, int iLong )
{
	return ( SCadExtraer ( p_cadObj, SCadLongitud ( p_cadObj ) - iLong, iLong ) );
}

SCadena * SCadExtraerDesdeCaracter ( SCadena * p_cadObj, char cVal )
{
	return ( SCadExtraerDesdeCaracterExt ( p_cadObj,  cVal, 1 ) );
}

SCadena * SCadExtraerHastaCaracter ( SCadena * p_cadObj, char cVal )
{
	return ( SCadExtraerHastaCaracterExt ( p_cadObj,  cVal, 1 ) );
}

SCadena * SCadExtraerDesdeCaracterExt ( SCadena * p_cadObj, char cVal, int iIncluir )
{
	SCadena	*	p_cadSubcadena;	
	char *		p_cSubcadena;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		p_cSubcadena = CadExtraerDesdeCaracterExt ( p_cadObj->p_cValor, cVal, iIncluir, 0, p_cadObj->iMaxTam );
		if ( ES_VALIDO ( p_cSubcadena ) ) 
		{
			p_cadSubcadena = SCadGenerar ( p_cSubcadena );
			if ( p_cadObj->iDistincionTipoLetra == 0 )
			{
				SCadDesactivarDistincionTipoLetra ( p_cadSubcadena );
			}
			MemLiberar ( (void **) &p_cSubcadena );
		}
		else
		{
			p_cadSubcadena = NULL;
		}
	}
	else
	{
		p_cadSubcadena = NULL;
	}
	return ( p_cadSubcadena );
}

SCadena * SCadExtraerHastaCaracterExt ( SCadena * p_cadObj, char cVal, int iIncluir )
{
	SCadena	*	p_cadSubcadena;	
	char *	p_cSubcadena;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		p_cSubcadena = CadExtraerHastaCaracterExt ( p_cadObj->p_cValor, cVal, iIncluir, 0, p_cadObj->iMaxTam );
		if ( ES_VALIDO ( p_cSubcadena ) ) 
		{
			p_cadSubcadena = SCadGenerar ( p_cSubcadena );
			if ( p_cadObj->iDistincionTipoLetra == 0 )
			{
				SCadDesactivarDistincionTipoLetra ( p_cadSubcadena );
			}
			MemLiberar ( (void **) &p_cSubcadena );
		}
		else
		{
			p_cadSubcadena = NULL;
		}
	}
	else
	{
		p_cadSubcadena = NULL;
	}
	return ( p_cadSubcadena );
}

int SCadExiste ( SCadena * p_cadObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) && ES_VALIDO ( p_cadValor ) )
	{
		iRes = SCadExisteLiteral ( p_cadObj, SCadValor ( p_cadValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadBuscar ( SCadena * p_cadObj, SCadena * p_cadValor, int iPosIni )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) && ES_VALIDO ( p_cadValor ) )
	{
		iRes = SCadBuscarLiteral ( p_cadObj, SCadValor ( p_cadValor ), iPosIni );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadBuscarDesc ( SCadena * p_cadObj, SCadena * p_cadValor, int iPosIni )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) && ES_VALIDO ( p_cadValor ) )
	{
		iRes = SCadBuscarLiteralDesc ( p_cadObj, SCadValor ( p_cadValor ), iPosIni );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadContar ( SCadena * p_cadObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) && ES_VALIDO ( p_cadValor ) )
	{
		iRes = SCadContarLiteral ( p_cadObj, SCadValor ( p_cadValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadReemplazar ( SCadena * p_cadObj, SCadena * p_cadValor, SCadena * p_cadReemp )
{
	return (  SCadReemplazarExt ( p_cadObj, p_cadValor, p_cadReemp, 0 ) );
}

int SCadReemplazarExt ( SCadena * p_cadObj, SCadena * p_cadValor, SCadena * p_cadReemp, int iExpander )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) && ES_VALIDO ( p_cadValor ) && ES_VALIDO ( p_cadReemp ) )
	{
		iRes = SCadReemplazarLiteralExt ( p_cadObj, SCadValor ( p_cadValor ), SCadValor ( p_cadReemp ), iExpander );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int SCadExisteCaracter ( SCadena * p_cadObj, char cVal )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = CadContieneCaracterExt ( p_cadObj->p_cValor, cVal, p_cadObj->iMaxTam );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadBuscarCaracter ( SCadena * p_cadObj, char cVal, int iPosIni )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = CadBuscarCaracterExt ( p_cadObj->p_cValor, cVal, iPosIni, p_cadObj->iMaxTam );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadBuscarCaracterDesc ( SCadena * p_cadObj, char cVal, int iPosIni )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = CadBuscarDescCaracterExt ( p_cadObj->p_cValor, cVal, iPosIni, p_cadObj->iMaxTam );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadBuscarCaracterDiferente ( SCadena * p_cadObj, char cVal, int iPosIni )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = CadBuscarCaracterDiferenteExt( p_cadObj->p_cValor, cVal, iPosIni, p_cadObj->iMaxTam );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadBuscarCaracterDiferenteDesc ( SCadena * p_cadObj, char cVal, int iPosIni )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = CadBuscarDescCaracterDiferenteExt ( p_cadObj->p_cValor, cVal, iPosIni, p_cadObj->iMaxTam );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadContarCaracter ( SCadena * p_cadObj, char cVal )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = CadContarCaracterExt ( p_cadObj->p_cValor, cVal, p_cadObj->iMaxTam );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadReemplazarCaracter ( SCadena * p_cadObj, char cVal, char cReemp )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = CadReemplazarCaracterExt ( p_cadObj->p_cValor, cVal, cReemp, p_cadObj->iMaxTam );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadExisteLiteral ( SCadena * p_cadObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = CadContieneExt ( p_cadObj->p_cValor, p_cValor, p_cadObj->iMaxTam, -1 );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadBuscarLiteral ( SCadena * p_cadObj, const char * p_cValor, int iPosIni )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = CadBuscarExt ( p_cadObj->p_cValor, p_cValor, iPosIni, p_cadObj->iMaxTam, -1 );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadBuscarLiteralDesc ( SCadena * p_cadObj, const char * p_cValor, int iPosIni )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = CadBuscarDescExt ( p_cadObj->p_cValor, p_cValor, iPosIni, p_cadObj->iMaxTam, -1 );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadContarLiteral ( SCadena * p_cadObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = CadContarExt ( p_cadObj->p_cValor, p_cValor, p_cadObj->iMaxTam, -1 );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadReemplazarLiteral ( SCadena * p_cadObj, const char * p_cValor, const char * p_cReemp )
{
	return ( SCadReemplazarLiteralExt ( p_cadObj, p_cValor, p_cReemp, 0 ) );
}

int SCadReemplazarLiteralExt ( SCadena * p_cadObj, const char * p_cValor, const char * p_cReemp, int iExpander )
{
	int	iMaxTamIni;
	int	iMaxTamTrab;
	int	iMaxTamFin;
	int	iAmpliada;
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		if ( iExpander == 1 )
		{
			iMaxTamIni = p_cadObj->iMaxTam;
			iMaxTamTrab = SCadLongitud ( p_cadObj ) * ( 1 + CadLongitud ( p_cReemp ) - CadLongitud ( p_cValor ) );
			if ( iMaxTamTrab > iMaxTamIni )
			{
				SCadEstablecerMaxTam ( p_cadObj, iMaxTamTrab );
				iAmpliada = 1;
			}
			else
			{
				iAmpliada = 0;
			}
			if ( CadReemplazarExt ( p_cadObj->p_cValor, p_cValor, p_cReemp, p_cadObj->iMaxTam, -1, -1 ) == 1 )
			{
				iRes = 1;
				if ( iAmpliada == 1 )
				{
					if ( SCadLongitud ( p_cadObj ) <= iMaxTamIni )
					{
						iMaxTamFin = iMaxTamIni;
					}
					else
					{
						iMaxTamFin = SCadLongitud ( p_cadObj );
					}
					SCadEstablecerMaxTam ( p_cadObj, iMaxTamFin );
				}
			}
			else
			{
				iRes = 0;
				if ( iAmpliada == 1 )
				{
					SCadEstablecerMaxTam ( p_cadObj, iMaxTamIni );
				}
			}
		}
		else
		{
			iRes = CadReemplazarExt ( p_cadObj->p_cValor, p_cValor, p_cReemp, p_cadObj->iMaxTam, -1, -1 );
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadEsIgual ( SCadena * p_cadObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) && ES_VALIDO ( p_cadValor ) )
	{
		iRes = SCadEsIgualLiteral ( p_cadObj, SCadValor ( p_cadValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadEsMenor( SCadena * p_cadObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) && ES_VALIDO ( p_cadValor ) )
	{
		iRes = SCadEsMenorLiteral ( p_cadObj, SCadValor ( p_cadValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadEsMayor ( SCadena * p_cadObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) && ES_VALIDO ( p_cadValor ) )
	{
		iRes = SCadEsMayorLiteral ( p_cadObj, SCadValor ( p_cadValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadEsDiferente ( SCadena * p_cadObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) && ES_VALIDO ( p_cadValor ) )
	{
		iRes = SCadEsDiferenteLiteral ( p_cadObj, SCadValor ( p_cadValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadEsIgualLiteral ( SCadena * p_cadObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) && ES_VALIDO ( p_cValor ) )
	{
		if ( p_cadObj->iDistincionTipoLetra == 1 )
		{
			if ( CadCompararExt ( p_cadObj->p_cValor, p_cValor, p_cadObj->iMaxTam, -1 ) == COMP_IGUAL )
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
			if ( CadCompararSinDistinguirTipoLetraExt ( p_cadObj->p_cValor, p_cValor, p_cadObj->iMaxTam, -1 ) == COMP_IGUAL )
			{
				iRes = 1;
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

int SCadEsMenorLiteral ( SCadena * p_cadObj, const char * p_cValor )
{
	int iRes;
	int iCar;

	if ( ES_VALIDO ( p_cadObj ) && ES_VALIDO ( p_cValor ) )
	{
		if ( SCadLongitud ( p_cadObj ) < CadLongitud ( p_cValor ) )
		{
			iRes = 1;
		}
		else if ( SCadLongitud ( p_cadObj ) == CadLongitud ( p_cValor ) )
		{
			if ( p_cadObj->iDistincionTipoLetra == 1 )
			{
				iCar = 0; 
				while ( ( iCar < SCadLongitud ( p_cadObj ) ) && 
						( p_cadObj->p_cValor [ iCar ] == p_cValor [ iCar ] ) )
				{
					iCar = iCar + 1;
				}
				if ( p_cadObj->p_cValor [ iCar ]  < p_cValor [ iCar ] )
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
				iCar = 0; 
				while ( ( iCar < SCadLongitud ( p_cadObj ) ) && 
						( ASCIILetraMinAMay ( p_cadObj->p_cValor [ iCar ] ) == ASCIILetraMinAMay ( p_cValor [ iCar ] ) ) )
				{
					iCar = iCar + 1;
				}
				if ( ASCIILetraMinAMay ( p_cadObj->p_cValor [ iCar ] ) < ASCIILetraMinAMay ( p_cValor [ iCar ] ) )
				{
					iRes = 1;
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
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadEsMayorLiteral ( SCadena * p_cadObj, const char * p_cValor )
{
	int iRes;
	int iCar;

	if ( ES_VALIDO ( p_cadObj ) && ES_VALIDO ( p_cValor ) )
	{
		if ( SCadLongitud ( p_cadObj ) > CadLongitud ( p_cValor ) )
		{
			iRes = 1;
		}
		else if ( SCadLongitud ( p_cadObj ) == CadLongitud ( p_cValor ) )
		{
			if ( p_cadObj->iDistincionTipoLetra == 1 )
			{
				iCar = 0; 
				while ( ( iCar < SCadLongitud ( p_cadObj ) ) && 
						( p_cadObj->p_cValor [ iCar ] == p_cValor [ iCar ] ) )
				{
					iCar = iCar + 1;
				}
				if ( p_cadObj->p_cValor [ iCar ]  > p_cValor [ iCar ] )
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
				iCar = 0; 
				while ( ( iCar < SCadLongitud ( p_cadObj ) ) && 
						( ASCIILetraMinAMay ( p_cadObj->p_cValor [ iCar ] ) == ASCIILetraMinAMay ( p_cValor [ iCar ] ) ) )
				{
					iCar = iCar + 1;
				}
				if ( ASCIILetraMinAMay ( p_cadObj->p_cValor [ iCar ] ) > ASCIILetraMinAMay ( p_cValor [ iCar ] ) )
				{
					iRes = 1;
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
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadEsDiferenteLiteral ( SCadena * p_cadObj, const char * p_cValor )
{
	int iRes;

	if ( SCadEsIgualLiteral ( p_cadObj, p_cValor ) == 0 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadEmpiezaPor ( SCadena * p_cadObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) && ES_VALIDO ( p_cadValor ) )
	{
		iRes = SCadEmpiezaPorLiteral ( p_cadObj, SCadValorConstante ( p_cadValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadAcabaPor ( SCadena * p_cadObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) && ES_VALIDO ( p_cadValor ) )
	{
		iRes = SCadAcabaPorLiteral  ( p_cadObj, SCadValorConstante ( p_cadValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadEmpiezaPorLiteral ( SCadena * p_cadObj, const char * p_cValor )
{
	int iRes;
	int iCar;
	int iLong;

	if ( ES_VALIDO ( p_cadObj ) && ES_VALIDO ( p_cValor ) )
	{
		iLong = CadLongitud ( p_cValor );
		if ( p_cadObj->iDistincionTipoLetra == 1 )
		{
			iCar = 0; 
			while ( ( iCar < SCadLongitud ( p_cadObj ) ) && ( iCar < iLong ) &&  
					( p_cadObj->p_cValor [ iCar ] == p_cValor [ iCar ] ) )
			{
				iCar = iCar + 1;
			}
			if ( ( iCar == iLong ) && 
				 ( p_cadObj->p_cValor [ iCar - 1 ] == p_cValor [ iCar - 1 ] ) )
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
			iCar = 0; 
			while ( ( iCar < SCadLongitud ( p_cadObj ) ) && ( iCar < iLong ) &&  
					( ASCIILetraMinAMay ( p_cadObj->p_cValor [ iCar ] ) == ASCIILetraMinAMay ( p_cValor [ iCar ] ) ) )
			{
				iCar = iCar + 1;
			}
			if ( ( iCar == iLong ) && 
				 ( ASCIILetraMinAMay ( p_cadObj->p_cValor [ iCar - 1 ] ) == ASCIILetraMinAMay ( p_cValor [ iCar - 1 ] ) ) )
			{
				iRes = 1;
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

int SCadAcabaPorLiteral ( SCadena * p_cadObj, const char * p_cValor )
{
	int iRes;
	int iCar1;
	int iCar2;

	if ( ES_VALIDO ( p_cadObj ) && ES_VALIDO ( p_cValor ) )
	{
		if ( p_cadObj->iDistincionTipoLetra == 1 )
		{
			iCar1 = SCadLongitud ( p_cadObj ) - 1;
			iCar2 = CadLongitud ( p_cValor ) - 1;
			while ( ( iCar1 >= 0 ) && ( iCar2 >= 0 ) &&  
					( p_cadObj->p_cValor [ iCar1 ] == p_cValor [ iCar2 ] ) )
			{
				iCar1 = iCar1 - 1;
				iCar2 = iCar2 - 1;
			}
			if ( iCar2 < 0 )
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
			iCar1 = SCadLongitud ( p_cadObj ) - 1;
			iCar2 = CadLongitud ( p_cValor ) - 1;
			while ( ( iCar1 >= 0 ) && ( iCar2 >= 0 ) &&  
					( ASCIILetraMinAMay ( p_cadObj->p_cValor [ iCar1 ] ) == ASCIILetraMinAMay ( p_cValor [ iCar2 ] ) ) )
			{
				iCar1 = iCar1 - 1;
				iCar2 = iCar2 - 1;
			}
			if ( iCar2 < 0 )
			{
				iRes = 1;
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

int SCadInvertir ( SCadena * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = CadInvertirExt ( p_cadObj->p_cValor, p_cadObj->iMaxTam );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadEliminarCaracteresNoImprimibles ( SCadena * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = CadEliminarCaracteresNoImprimiblesExt ( p_cadObj->p_cValor, p_cadObj->iMaxTam );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadEliminarCaracteresNoAlfanumericos ( SCadena * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = CadEliminarCaracteresNoAlfanumericosExt ( p_cadObj->p_cValor, p_cadObj->iMaxTam );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadEliminarCaracteresNoEstandar ( SCadena * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = CadEliminarCaracteresNoEstandarExt ( p_cadObj->p_cValor, p_cadObj->iMaxTam );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );	
}

int SCadCumpleExpReg ( SCadena * p_cadObj, const char * p_cExpReg )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = CadCumpleExpRegExt ( p_cadObj->p_cValor, p_cExpReg, p_cadObj->iMaxTam );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadConvertirAMayusculas ( SCadena * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = CadConvertirAMayusculasExt ( p_cadObj->p_cValor, p_cadObj->iMaxTam );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadConvertirAMinusculas ( SCadena * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = CadConvertirAMinusculasExt ( p_cadObj->p_cValor, p_cadObj->iMaxTam );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );	
}

int SCadConvertirACapitales ( SCadena * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = CadConvertirACapitalesExt ( p_cadObj->p_cValor, p_cadObj->iMaxTam );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadTraducirLetrasConSigno ( SCadena * p_cadObj )
{
	int iRes;
	int	iCar;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		if ( ES_VALIDO ( p_cadObj->p_cValor ) )
		{
			for ( iCar = 0; iCar < SCadLongitud ( p_cadObj ); iCar = iCar + 1 )
			{
				p_cadObj->p_cValor [ iCar ] = ASCIILetraSinSigno ( p_cadObj->p_cValor [ iCar ] );
			}
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
	return ( iRes );
}

int SCadCorrespondeAValorNulo ( SCadena * p_cadObj )
{
	return ( SCadEsIgualLiteral ( p_cadObj, TXT_VALOR_NULO ) );
}

int SCadContieneValoresNulos ( SCadena * p_cadObj )
{
	return ( SCadExisteLiteral ( p_cadObj, TXT_VALOR_NULO ) );
}

int SCadEliminarValoresNulos ( SCadena * p_cadObj )
{
	return ( SCadEliminarAparicionesLiteral ( p_cadObj, TXT_VALOR_NULO ) );
}

int SCadEsToken ( SCadena * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = CadEsToken ( p_cadObj->p_cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadNumCaracteres ( SCadena * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = CadNumCaracteresExt ( p_cadObj->p_cValor, p_cadObj->iMaxTam );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadNumPalabras ( SCadena * p_cadObj, char cSep, int iSepararSignos )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = CadNumPalabrasSepExt ( p_cadObj->p_cValor, cSep, iSepararSignos, p_cadObj->iMaxTam );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SCadena * SCadPalabra ( SCadena * p_cadObj, int iPalabra, char cSep, int iSepararSignos )
{
	char * p_cPalabra;
	SCadena * p_cadPalabra;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		p_cPalabra = CadPalabraSepExt ( p_cadObj->p_cValor, iPalabra, cSep, iSepararSignos, p_cadObj->iMaxTam );
		if ( ES_VALIDO ( p_cPalabra ) )
		{
			p_cadPalabra = SCadGenerar ( p_cPalabra );
			if ( p_cadObj->iDistincionTipoLetra == 0 )
			{
				SCadDesactivarDistincionTipoLetra ( p_cadPalabra );
			}
			SCadEliminarBlancosLaterales ( p_cadPalabra );
			MemLiberar ( (void **) &p_cPalabra );
		}
		else
		{
			p_cadPalabra = NULL;
		}
	}
	else
	{
		p_cadPalabra = NULL;
	}
	return ( p_cadPalabra );
}

char * SCadPalabraLiteral ( SCadena * p_cadObj, int iPalabra, char cSep, int iSepararSignos )
{
	char * p_cPalabra;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		p_cPalabra = CadPalabraSepExt ( p_cadObj->p_cValor, iPalabra, cSep, iSepararSignos, p_cadObj->iMaxTam );
	}
	else
	{
		p_cPalabra = NULL;
	}
	return ( p_cPalabra );
}

int SCadActivarDistincionTipoLetra ( SCadena * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		p_cadObj->iDistincionTipoLetra = 1;
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadDesactivarDistincionTipoLetra ( SCadena * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		p_cadObj->iDistincionTipoLetra = 0;
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadDistingueTipoLetra ( SCadena * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = p_cadObj->iDistincionTipoLetra;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

void SCadImprimir ( SCadena * p_cadObj )
{
	if ( ES_VALIDO ( p_cadObj ) )
	{
		CadImprimir ( p_cadObj->p_cValor );
	}
	else
	{
		CadImprimir ( NULL );
	}
}

void SCadImprimirExt ( SCadena * p_cadObj, const char * p_cEtiqueta, char cSep, int iEnvolver )
{
	if ( ES_VALIDO ( p_cadObj ) )
	{
		CadImprimirExt ( p_cadObj->p_cValor, p_cEtiqueta, cSep, iEnvolver );
	}
	else
	{
		CadImprimirExt ( NULL, p_cEtiqueta, cSep, iEnvolver );
	}
}

void SCadImprimirXml ( SCadena * p_cadObj, const char * p_cEtiqueta )
{
	if ( ES_VALIDO ( p_cadObj ) )
	{
		CadImprimirXml ( p_cadObj->p_cValor, p_cEtiqueta );
	}
	else
	{
		CadImprimirXml ( NULL, p_cEtiqueta );
	}
}

void SCadImprimirJson ( SCadena * p_cadObj, const char * p_cEtiqueta )
{
	if ( ES_VALIDO ( p_cadObj ) )
	{
		CadImprimirJson ( p_cadObj->p_cValor, p_cEtiqueta );
	}
	else
	{
		CadImprimirJson ( NULL, p_cEtiqueta );
	}
}

