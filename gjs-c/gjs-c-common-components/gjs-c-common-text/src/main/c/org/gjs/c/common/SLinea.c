#include "SLinea.h"
#include "Cadenas.h"

#include "TextoConfig.h"




SLinea * SLinCrear ( int iMaxLong )
{
	SLinea * p_linObj;
	
	if ( iMaxLong > 0 )
	{
		p_linObj = (SLinea *) MemReservar ( sizeof ( SLinea ) );
		if ( ES_VALIDO ( p_linObj ) )
		{
			p_linObj->p_cadTexto = SCadCrear ( iMaxLong );
			p_linObj->p_indPosicion = SIndCrear ( iMaxLong );
		}
	}
	else
	{
		p_linObj = NULL;
	}
	return ( p_linObj );
}

SLinea * SLinGenerar ( SCadena * p_cadValor )
{
	SLinea *	p_linObj;
	int			iLong;
	
	if ( SCadEsValida ( p_cadValor ) == 1 )
	{
		iLong = SCadLongitud ( p_cadValor ); 
		p_linObj = SLinCrear ( iLong );
		if ( ES_VALIDO ( p_linObj ) )
		{
			if ( SLinInsertar ( p_linObj, p_cadValor ) == 1 )
			{
				SLinIni ( p_linObj );
			}
			else
			{
				SLinDestruir ( &p_linObj );
			}
		}
	}
	else
	{
		p_linObj = NULL;
	}
	return ( p_linObj );
}

SLinea * SLinGenerarLiteral ( const char * p_cValor )
{
	SLinea *	p_linObj;
	int			iLong;
	
	if ( ES_VALIDO ( p_cValor ) )
	{
		iLong = CadLongitud ( p_cValor ); 
		p_linObj = SLinCrear ( iLong );
		if ( ES_VALIDO ( p_linObj ) )
		{
			if ( SLinInsertarLiteral ( p_linObj, p_cValor ) == 1 )
			{
				SLinIni ( p_linObj );
			}
			else
			{
				SLinDestruir ( &p_linObj );
			}
		}
	}
	else
	{
		p_linObj = NULL;
	}
	return ( p_linObj );
}

void SLinDestruir ( SLinea ** p_p_linObj )
{
	SLinea * p_linObj;
	
	if ( ES_VALIDO ( p_p_linObj ) )
	{
		p_linObj = *p_p_linObj;

		if ( ES_VALIDO ( p_linObj ) )
		{
			SCadDestruir ( &(p_linObj->p_cadTexto) );
			SIndDestruir ( &(p_linObj->p_indPosicion) );
			MemLiberar ( (void **) p_p_linObj );
		}
	}
}

int SLinEsValida ( SLinea * p_linObj )
{
	int iRes;

	if ( ES_VALIDO ( p_linObj ) )
	{
		if ( ( SCadEsValida ( p_linObj->p_cadTexto ) == 1 ) &&
			 ( SIndEsValido ( p_linObj->p_indPosicion ) == 1 ) )
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

SCadena * SLinValorCadena ( SLinea * p_linObj )
{
	SCadena *	p_cadRes;
	
	if ( ES_VALIDO ( p_linObj ) )
	{
		p_cadRes = p_linObj->p_cadTexto;
	}
	else
	{
		p_cadRes = NULL;
	}
	return ( p_cadRes );
}

char * SLinValorLiteral ( SLinea * p_linObj )
{
	char *	p_cRes;
	
	if ( ES_VALIDO ( p_linObj ) )
	{
		p_cRes = SCadValor ( p_linObj->p_cadTexto );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SLinPosicion ( SLinea * p_linObj )
{
	int iRes;

	if ( ES_VALIDO ( p_linObj ) )
	{
		iRes = (int) SIndValor ( p_linObj->p_indPosicion );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SLinLongitud ( SLinea * p_linObj )
{
	int iRes;

	if ( ES_VALIDO ( p_linObj ) )
	{
		iRes = SCadLongitud ( p_linObj->p_cadTexto );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SLinLongitudMax ( SLinea * p_linObj )
{
	int iRes;

	if ( ES_VALIDO ( p_linObj ) )
	{
		iRes = (int) SIndMax ( p_linObj->p_indPosicion );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SLinEstaVacia ( SLinea * p_linObj )
{
	int iRes;

	if ( ES_VALIDO ( p_linObj ) )
	{
		iRes = SCadEstaVacia ( p_linObj->p_cadTexto );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SLinEstaEnFinal ( SLinea * p_linObj )
{
	int iRes;

	if ( ES_VALIDO ( p_linObj ) )
	{
		if ( ((int) SIndValor ( p_linObj->p_indPosicion )) >= SCadLongitud ( p_linObj->p_cadTexto ) )
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
		iRes = -1;
	}
	return ( iRes );
}

int SLinEstaEnInicio ( SLinea * p_linObj )
{
	int iRes;

	if ( ES_VALIDO ( p_linObj ) )
	{
		iRes = SIndEstaEnInicio ( p_linObj->p_indPosicion );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SLinEspacioLibre ( SLinea * p_linObj )
{
	int iRes;

	if ( ES_VALIDO ( p_linObj ) )
	{
		iRes = SIndMax ( p_linObj->p_indPosicion ) - SCadLongitud ( p_linObj->p_cadTexto );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SLinQuedaEspacioLibre ( SLinea * p_linObj )
{
	int iRes;

	if ( ES_VALIDO ( p_linObj ) )
	{
		if ( ((int) SIndMax ( p_linObj->p_indPosicion )) > SCadLongitud ( p_linObj->p_cadTexto ) )
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
		iRes = -1;
	}
	return ( iRes );
}

void SLinIni ( SLinea * p_linObj )
{
	if ( SLinEsValida ( p_linObj ) == 1 )
	{
		SIndInicio ( p_linObj->p_indPosicion );
	}
}

void SLinFin ( SLinea * p_linObj )
{
	if ( SLinEsValida ( p_linObj ) == 1 )
	{
		SIndFinal ( p_linObj->p_indPosicion );
	}
}

void SLinSig ( SLinea * p_linObj )
{
	if ( SLinEsValida ( p_linObj ) == 1 )
	{
		SIndIncrementar ( p_linObj->p_indPosicion );
	}
}

void SLinAnt ( SLinea * p_linObj )
{
	if ( SLinEsValida ( p_linObj ) == 1 )
	{
		SIndDecrementar ( p_linObj->p_indPosicion );
	}
}

void SLinMover ( SLinea * p_linObj, int iPos )
{
	if ( SLinEsValida ( p_linObj ) == 1 )
	{
		SIndMoverA ( p_linObj->p_indPosicion, iPos );
	}
}

int SLinVaciar ( SLinea * p_linObj )
{
	int iRes;

	if ( SLinEsValida ( p_linObj ) == 1 )
	{
		if ( SCadVaciar ( p_linObj->p_cadTexto ) == 1 )
		{
			SIndInicio ( p_linObj->p_indPosicion );
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

int SLinPuedeInsertar ( SLinea * p_linObj, SCadena * p_cadValor )
{
	int	iRes;
	int iLon;
	int iLonIns;
	int iMax;

	if ( ( SLinEsValida ( p_linObj ) == 1 ) && ( SCadEsValida ( p_cadValor ) == 1 ) )
	{
		iLon = SCadLongitud ( p_linObj->p_cadTexto );
		iLonIns = SCadLongitud ( p_cadValor );
		iMax = (int) SIndMax ( p_linObj->p_indPosicion );

		if ( iLon + iLonIns <= iMax )
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

int SLinPuedeInsertarLiteral ( SLinea * p_linObj, const char * p_cValor )
{
	int	iRes;
	int iLon;
	int iLonIns;
	int iMax;

	if ( ( SLinEsValida ( p_linObj ) == 1 ) && ES_VALIDO ( p_cValor ) )
	{
		iLon = SCadLongitud ( p_linObj->p_cadTexto );
		iLonIns = CadLongitud ( p_cValor );
		iMax = (int) SIndMax ( p_linObj->p_indPosicion );

		if ( iLon + iLonIns <= iMax )
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

int SLinPuedeInsertarCaracter ( SLinea * p_linObj, char cValor )
{
	int	iRes;
	int iLon;
	int iMax;

	if ( SLinEsValida ( p_linObj ) == 1 )
	{
		iLon = SCadLongitud ( p_linObj->p_cadTexto );
		iMax = (int) SIndMax ( p_linObj->p_indPosicion );

		if ( iLon < iMax )
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

int SLinPuedeEscribir ( SLinea * p_linObj, SCadena * p_cadValor )
{
	int	iRes;
	int iPos;
	int iLonIns;
	int iMax;

	if ( ( SLinEsValida ( p_linObj ) == 1 ) && ( SCadEsValida ( p_cadValor ) == 1 ) )
	{
		iPos = (int) SIndValor ( p_linObj->p_indPosicion );
		iLonIns = SCadLongitud ( p_cadValor );
		iMax = (int) SIndMax ( p_linObj->p_indPosicion );

		if ( iPos + iLonIns <= iMax )
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

int SLinPuedeEscribirLiteral ( SLinea * p_linObj, const char * p_cValor )
{
	int	iRes;
	int iPos;
	int iLonIns;
	int iMax;

	if ( ( SLinEsValida ( p_linObj ) == 1 ) && ES_VALIDO ( p_cValor ) )
	{
		iPos = (int) SIndValor ( p_linObj->p_indPosicion );
		iLonIns = CadLongitud ( p_cValor );
		iMax = (int) SIndMax ( p_linObj->p_indPosicion );

		if ( iPos + iLonIns <= iMax )
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

int SLinPuedeEscribirCaracter ( SLinea * p_linObj, char cValor )
{
	int	iRes;
	int iPos;
	int iMax;

	if ( SLinEsValida ( p_linObj ) == 1 )
	{
		iPos = (int) SIndValor ( p_linObj->p_indPosicion );
		iMax = (int) SIndMax ( p_linObj->p_indPosicion );

		if ( iPos < iMax )
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

int SLinInsertar ( SLinea * p_linObj, SCadena * p_cadValor )
{
	return ( SLinInsertarExt ( p_linObj, p_cadValor, NULL ) );
}

int SLinInsertarExt ( SLinea * p_linObj, SCadena * p_cadValor, SCadena ** p_p_cadResto )
{
	int			iRes;
	SCadena *	p_cadResto;
	int			iPos;
	int			iLon;
	int			iLonIns;
	int			iMax;
	int			iLonRes;

	if ( ( SLinEsValida ( p_linObj ) == 1 ) && ( SCadEsValida ( p_cadValor ) == 1 ) )
	{
		iLon = SCadLongitud ( p_linObj->p_cadTexto );
		iLonIns = SCadLongitud ( p_cadValor );
		iMax = (int) SIndMax ( p_linObj->p_indPosicion );
		iPos = (int) SIndValor ( p_linObj->p_indPosicion );

		iLonRes = iLon + iLonIns - iMax; 
		if ( ( iLonRes > 0 ) && ES_VALIDO ( p_p_cadResto ) )
		{
			p_cadResto = SCadExtraerUltimos ( p_linObj->p_cadTexto, iLonRes );
			*p_p_cadResto = p_cadResto;
		}

		iRes = SCadInsertar ( p_linObj->p_cadTexto, iPos, p_cadValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLinInsertarLiteral ( SLinea * p_linObj, const char * p_cValor )
{
	return ( SLinInsertarLiteralExt ( p_linObj, p_cValor, NULL ) );
}

int SLinInsertarLiteralExt ( SLinea * p_linObj, const char * p_cValor, char ** p_p_cResto )
{
	int			iRes;
	char *		p_cResto;
	int			iPos;
	int			iLon;
	int			iLonIns;
	int			iMax;
	int			iLonRes;

	if ( ( SLinEsValida ( p_linObj ) == 1 ) && ( CadLongitud ( p_cValor ) > 0 ) )
	{
		iLon = SCadLongitud ( p_linObj->p_cadTexto );
		iLonIns = CadLongitud ( p_cValor );
		iMax = (int) SIndMax ( p_linObj->p_indPosicion );
		iPos = (int) SIndValor ( p_linObj->p_indPosicion );

		iLonRes = iLon + iLonIns - iMax; 
		if ( ( iLonRes > 0 ) && ES_VALIDO ( p_p_cResto ) )
		{
			p_cResto = CadExtraerUltimos ( SCadValor ( p_linObj->p_cadTexto ), iLonRes );
			*p_p_cResto = p_cResto;
		}

		iRes = SCadInsertarLiteral ( p_linObj->p_cadTexto, iPos, p_cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLinInsertarCaracter ( SLinea * p_linObj, char cValor)
{
	return ( SLinInsertarCaracterExt ( p_linObj, cValor, NULL ) );
}

int SLinInsertarCaracterExt ( SLinea * p_linObj, char cValor, char * p_cResto )
{
	int			iRes;
	char 		cResto;
	int			iPos;
	int			iLon;
	int			iMax;

	if ( SLinEsValida ( p_linObj ) == 1 )
	{
		iLon = SCadLongitud ( p_linObj->p_cadTexto );
		iMax = (int) SIndMax ( p_linObj->p_indPosicion );
		iPos = (int) SIndValor ( p_linObj->p_indPosicion );

		if ( ( iLon == iMax ) && ES_VALIDO ( p_cResto ) )
		{
			cResto = SCadCaracter ( p_linObj->p_cadTexto, iLon - 1 );
			p_cResto = &cResto;
		}

		iRes = SCadInsertarCaracter ( p_linObj->p_cadTexto, iPos, cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLinEscribir ( SLinea * p_linObj, SCadena * p_cadValor )
{
	int	iRes;
	int	iPos;

	if ( ( SLinEsValida ( p_linObj ) == 1 ) && ( SCadEsValida ( p_cadValor ) == 1 ) )
	{
		iPos = (int) SIndValor ( p_linObj->p_indPosicion );
		iRes = SCadEscribir ( p_linObj->p_cadTexto, iPos, p_cadValor );
		if ( iRes == 1 )
		{
			SIndIncrementarExt ( p_linObj->p_indPosicion, SCadLongitud ( p_cadValor ) ); 
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLinEscribirLiteral ( SLinea * p_linObj, const char * p_cValor )
{
	int	iRes;
	int	iPos;

	if ( ( SLinEsValida ( p_linObj ) == 1 ) && ES_VALIDO ( p_cValor ) )
	{
		iPos = (int) SIndValor ( p_linObj->p_indPosicion );
		iRes = SCadEscribirLiteral ( p_linObj->p_cadTexto, iPos, p_cValor );
		if ( iRes == 1 )
		{
			SIndIncrementarExt ( p_linObj->p_indPosicion, CadLongitud ( p_cValor ) ); 
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLinEscribirCaracter ( SLinea * p_linObj, char cValor )
{
	int	iRes;
	int	iPos;

	if ( SLinEsValida ( p_linObj ) == 1 ) 
	{
		iPos = (int) SIndValor ( p_linObj->p_indPosicion );
		iRes = SCadEscribirCaracter ( p_linObj->p_cadTexto, iPos, cValor );
		if ( iRes == 1 )
		{
			SIndIncrementar ( p_linObj->p_indPosicion ); 
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLinEliminarCaracter ( SLinea * p_linObj )
{
	return ( SLinEliminarCaracteres ( p_linObj, 1 ) );
}

int SLinEliminarCaracteres ( SLinea * p_linObj, int iNum )
{
	int	iRes;
	int	iPos;

	if ( ( SLinEsValida ( p_linObj ) == 1 ) && ( iNum > 0 ) )
	{
		iPos = (int) SIndValor ( p_linObj->p_indPosicion );
		iRes = SCadEliminarCaracteres ( p_linObj->p_cadTexto, iPos, iNum );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SLinea * SLinDuplicar ( SLinea * p_linObj )
{
	SLinea * p_linCopia;

	if ( ES_VALIDO ( p_linObj ) )
	{
		p_linCopia = SLinCrear ( SIndMax ( p_linObj->p_indPosicion ) );
		if ( ES_VALIDO ( p_linCopia ) )
		{
			SLinEscribir ( p_linCopia, p_linObj->p_cadTexto );
		}
	}
	else
	{
		p_linCopia = NULL;
	}
	return ( p_linCopia );
}

SLinea * SLinDuplicarVacia ( SLinea * p_linObj )
{
	SLinea * p_linCopia;

	if ( ES_VALIDO ( p_linObj ) )
	{
		p_linCopia = SLinCrear ( SIndMax ( p_linObj->p_indPosicion ) );
	}
	else
	{
		p_linCopia = NULL;
	}
	return ( p_linCopia );
}

int SLinSonCompatibles ( SLinea * p_linObj, SLinea * p_linValor )
{
	int	iRes;

	if ( ( SLinEsValida ( p_linObj ) == 1 ) && ( SLinEsValida ( p_linValor ) == 1 ) )
	{
		if ( ((int) SIndMax ( p_linObj->p_indPosicion )) == SLinLongitudMax ( p_linValor ) )
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

int SLinAsignar ( SLinea * p_linObj, SLinea * p_linValor )
{
	int	iRes;
	int iMax;

	if ( ES_VALIDO ( p_linObj ) && ES_VALIDO ( p_linValor ) )
	{
		SCadDestruir ( &(p_linObj->p_cadTexto) );
		SIndDestruir ( &(p_linObj->p_indPosicion) );

		iMax = SLinLongitudMax ( p_linValor );

		p_linObj->p_cadTexto = SCadCrear ( iMax );
		p_linObj->p_indPosicion = SIndCrear ( iMax );

		if ( ( SCadCopiar ( p_linObj->p_cadTexto, SLinValorCadena ( p_linValor ) ) == 1 ) &&
			 ( SIndMoverA ( p_linObj->p_indPosicion, SLinPosicion ( p_linValor ) ) == 1 ) )
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

int SLinNumPalabras ( SLinea * p_linObj )
{
	int iRes;

	if ( SLinEsValida ( p_linObj ) == 1 )
	{
		iRes = SCadNumPalabras ( p_linObj->p_cadTexto, ' ', 0 );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLinNumCaracteres ( SLinea * p_linObj )
{
	int iRes;

	if ( SLinEsValida ( p_linObj ) == 1 )
	{
		iRes = SCadNumCaracteres ( p_linObj->p_cadTexto );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

void SLinImprimir ( SLinea * p_linObj )
{
	if ( SLinEsValida ( p_linObj ) == 1 )
	{
		SCadImprimir ( p_linObj->p_cadTexto );
	}
}