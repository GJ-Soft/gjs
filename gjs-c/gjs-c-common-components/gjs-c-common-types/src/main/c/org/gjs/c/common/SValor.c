#include "SValor.h"

#include "TiposDatosConfig.h"








void _SValInicializar ( SValor * p_valObj, int iTipo, int iMaxTam );



SValor * SValCrearDef ()
{
	SValor * p_valObj;

	p_valObj = (SValor *) MemReservar ( sizeof ( SValor ) );
	if ( ES_VALIDO ( p_valObj ) )
	{
		p_valObj->p_cadValor = NULL;
		_SValInicializar ( p_valObj, TIP_DEFECTO, CAD_TAM_DEFECTO );
	}
	return ( p_valObj );
}

SValor * SValCrear ( int iTipo )
{
    SValor * p_valObj;

    p_valObj = (SValor *) MemReservar ( sizeof ( SValor ) );
    if ( ES_VALIDO ( p_valObj ) )
    {
        p_valObj->p_cadValor = NULL;
		_SValInicializar ( p_valObj, iTipo, CAD_TAM_DEFECTO );
    }
	return ( p_valObj );
}

SValor * SValCrearExt ( int iTipo, int iMaxTam )
{
    SValor * p_valObj;

    p_valObj = (SValor *) MemReservar ( sizeof ( SValor ) );
    if ( ES_VALIDO ( p_valObj ) )
    {
        p_valObj->p_cadValor = NULL;
        _SValInicializar ( p_valObj, iTipo, iMaxTam );
    }
	return ( p_valObj );
}

SValor * SValCrearBooleano ( int iValor )
{
    SValor * p_valObj;

    p_valObj = (SValor *) MemReservar ( sizeof ( SValor ) );
    if ( ES_VALIDO ( p_valObj ) )
    {
		p_valObj->p_cadValor = NULL;
		_SValInicializar ( p_valObj, TIP_BOOLEANO, 0 );
		SValEstablecerValorBooleano ( p_valObj, iValor );
	}
	return ( p_valObj );
}

SValor * SValCrearCaracter ( char cValor )
{
    SValor * p_valObj;

    p_valObj = (SValor *) MemReservar ( sizeof ( SValor ) );
    if ( ES_VALIDO ( p_valObj ) )
    {
		p_valObj->p_cadValor = NULL;
		_SValInicializar ( p_valObj, TIP_CARACTER, 0 );
		SValEstablecerValorCaracter ( p_valObj, cValor );
	}
	return ( p_valObj );
}

SValor * SValCrearEntero ( int iValor )
{
    SValor * p_valObj;

    p_valObj = (SValor *) MemReservar ( sizeof ( SValor ) );
    if ( ES_VALIDO ( p_valObj ) )
    {
		p_valObj->p_cadValor = NULL;
		_SValInicializar ( p_valObj, TIP_NUMERO_ENTERO, 0 );
		SValEstablecerValorEntero ( p_valObj, iValor );
	}
	return ( p_valObj );
}

SValor * SValCrearEnteroLargo ( long lValor )
{
   SValor * p_valObj;

    p_valObj = (SValor *) MemReservar ( sizeof ( SValor ) );
    if ( ES_VALIDO ( p_valObj ) )
    {
		p_valObj->p_cadValor = NULL;
		_SValInicializar ( p_valObj, TIP_NUMERO_ENTERO, 0 );
		SValEstablecerValorEnteroLargo ( p_valObj, lValor );
	}
	return ( p_valObj );
}

SValor * SValCrearEnteroSinSigno ( unsigned int uiValor )
{
   SValor * p_valObj;

    p_valObj = (SValor *) MemReservar ( sizeof ( SValor ) );
    if ( ES_VALIDO ( p_valObj ) )
    {
		p_valObj->p_cadValor = NULL;
		_SValInicializar ( p_valObj, TIP_NUMERO_NATURAL, 0 );
		SValEstablecerValorEnteroSinSigno ( p_valObj, uiValor );
	}
	return ( p_valObj );
}

SValor * SValCrearEnteroLargoSinSigno ( unsigned long ulValor )
{
   SValor * p_valObj;

    p_valObj = (SValor *) MemReservar ( sizeof ( SValor ) );
    if ( ES_VALIDO ( p_valObj ) )
    {
		p_valObj->p_cadValor = NULL;
		_SValInicializar ( p_valObj, TIP_NUMERO_NATURAL, 0 );
		SValEstablecerValorEnteroLargoSinSigno ( p_valObj, ulValor );
	}
	return ( p_valObj );
}

SValor * SValCrearReal ( float fValor )
{
   SValor * p_valObj;

    p_valObj = (SValor *) MemReservar ( sizeof ( SValor ) );
    if ( ES_VALIDO ( p_valObj ) )
    {
		p_valObj->p_cadValor = NULL;
		_SValInicializar ( p_valObj, TIP_NUMERO_REAL, 0 );
		SValEstablecerValorReal ( p_valObj, fValor );
	}
	return ( p_valObj );
}

SValor * SValCrearRealDoble ( double dValor )
{
   SValor * p_valObj;

    p_valObj = (SValor *) MemReservar ( sizeof ( SValor ) );
    if ( ES_VALIDO ( p_valObj ) )
    {
		p_valObj->p_cadValor = NULL;
		_SValInicializar ( p_valObj, TIP_NUMERO_REAL, 0 );
		SValEstablecerValorRealDoble ( p_valObj, dValor );
	}
	return ( p_valObj );
}

SValor * SValCrearCadena ( SCadena * p_cadValor )
{
	return ( SValCrearLiteral ( SCadValorConstante ( p_cadValor ) ) );
}

SValor * SValCrearLiteral ( const char * p_cValor )
{
   SValor * p_valObj;

    p_valObj = (SValor *) MemReservar ( sizeof ( SValor ) );
    if ( ES_VALIDO ( p_valObj ) )
    {
		p_valObj->p_cadValor = NULL;
		_SValInicializar ( p_valObj, TIP_CADENA, 0 );
		SValEstablecerValorLiteral ( p_valObj, p_cValor );
	}
	return ( p_valObj );
}

SValor * SValCrearBinario ( byte * p_byValor, int iTam )
{
   SValor * p_valObj;

    p_valObj = (SValor *) MemReservar ( sizeof ( SValor ) );
    if ( ES_VALIDO ( p_valObj ) )
    {
		p_valObj->p_cadValor = NULL;
		_SValInicializar ( p_valObj, TIP_BINARIO, iTam );
		SValEstablecerValorBinario ( p_valObj, p_byValor, iTam );
	}
	return ( p_valObj );
}

SValor * SValCrearFecha ( SFecha * p_fecValor )
{
	return ( SValCrearFechaNum ( SFecValor ( p_fecValor ) ) );
}

SValor * SValCrearHora ( SHora * p_horValor )
{
	return ( SValCrearHoraNum ( SHorValor ( p_horValor ) ) );
}

SValor * SValCrearFechaHora ( SFechaHora * p_fechValor )
{
	return ( SValCrearFechaNum ( SFecHorValor ( p_fechValor ) ) );
}

SValor * SValCrearFechaNum ( long lValor )
{
   SValor * p_valObj;

    p_valObj = (SValor *) MemReservar ( sizeof ( SValor ) );
    if ( ES_VALIDO ( p_valObj ) )
    {
		p_valObj->p_cadValor = NULL;
		_SValInicializar ( p_valObj, TIP_TIEMPO_FECHA, 4 );
		SValEstablecerValorEnteroLargo ( p_valObj, lValor );
	}
	return ( p_valObj );
}

SValor * SValCrearHoraNum ( long lValor )
{
   SValor * p_valObj;

    p_valObj = (SValor *) MemReservar ( sizeof ( SValor ) );
    if ( ES_VALIDO ( p_valObj ) )
    {
		p_valObj->p_cadValor = NULL;
		_SValInicializar ( p_valObj, TIP_TIEMPO_HORA, 4 );
		SValEstablecerValorEnteroLargo ( p_valObj, lValor );
	}
	return ( p_valObj );
}

SValor * SValCrearFechaHoraNum ( double dValor )
{
   SValor * p_valObj;

    p_valObj = (SValor *) MemReservar ( sizeof ( SValor ) );
    if ( ES_VALIDO ( p_valObj ) )
    {
		p_valObj->p_cadValor = NULL;
		_SValInicializar ( p_valObj, TIP_TIEMPO_FECHA_HORA, 4 );
		SValEstablecerValorRealDoble ( p_valObj, dValor );
	}
	return ( p_valObj );
}

SValor * SValCrearPuntero ( void * p_vValor )
{
   SValor * p_valObj;

    p_valObj = (SValor *) MemReservar ( sizeof ( SValor ) );
    if ( ES_VALIDO ( p_valObj ) )
    {
		p_valObj->p_cadValor = NULL;
		_SValInicializar ( p_valObj, TIP_OBJETO, sizeof( void *) );
		SValEstablecerValorPuntero ( p_valObj, p_vValor );
	}
	return ( p_valObj );
}

void SValDestruir ( SValor ** p_p_valObj )
{
	SValor * p_valObj;
	
	if ( ES_VALIDO ( p_p_valObj ) )
	{
		p_valObj = *p_p_valObj;
		if ( ES_VALIDO ( p_valObj ) )
		{
			SCadcDestruir ( &(p_valObj->p_cadValor) );
		}
		MemLiberar ( (void**) p_p_valObj );
	}
}

int SValTipo ( SValor * p_valObj )
{
	int iRes;

	if ( ES_VALIDO ( p_valObj ) )
	{
		iRes = p_valObj->iTipo;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SValEsValido ( SValor * p_valObj )
{
	int iRes;

	if ( ES_VALIDO ( p_valObj ) )
	{
		if ( ( TipEsValido ( p_valObj->iTipo ) == 1 ) && 
			( SCadcEsValida ( p_valObj->p_cadValor ) == 1 ) )
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

SCadenaConv * SValValor ( SValor * p_valObj )
{
	SCadenaConv * p_cadRes;
	
	if ( ES_VALIDO ( p_valObj ) )
	{
		p_cadRes = p_valObj->p_cadValor;
	}
	else
	{
		p_cadRes = NULL;
	}
	return ( p_cadRes );
}

byte SValValorByte ( SValor * p_valObj )
{
	byte byRes;

	if ( ES_VALIDO ( p_valObj ) )
	{
		if ( ES_VALIDO ( p_valObj->p_cadValor ) )
		{
			if ( TipEsBooleano ( p_valObj->iTipo ) == 1 )
			{
				byRes = ( byte ) SCadcValorEntero ( p_valObj->p_cadValor );
			}
			else
			{
				byRes = 0;
			}
		}
		else
		{
			byRes = 0;
		}
	}
	else
	{
		byRes = 0;
	}
	return ( byRes );
}

int SValValorBooleano ( SValor * p_valObj )
{
	int iRes;

	if ( ES_VALIDO ( p_valObj ) )
	{
		if ( ES_VALIDO ( p_valObj->p_cadValor ) )
		{
			if ( SCadcValorEntero ( p_valObj->p_cadValor ) <= 0 )
			{
				iRes = 0;
			}
			else
			{
				iRes = 1;
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

char SValValorCaracter ( SValor * p_valObj )
{
	char cRes;

	if ( ES_VALIDO ( p_valObj ) )
	{
		if ( ES_VALIDO ( p_valObj->p_cadValor ) )
		{
			cRes = SCadcCaracter ( p_valObj->p_cadValor, 0 );
		}
		else
		{
			cRes = '\0';
		}
	}
	else
	{
		cRes = '\0';
	}
	return ( cRes );
}

unsigned long SValValorNatural ( SValor * p_valObj )
{
	unsigned long ulRes;

	if ( ES_VALIDO ( p_valObj ) )
	{
		if ( ES_VALIDO ( p_valObj->p_cadValor ) )
		{
			if ( TipEsNatural ( p_valObj->iTipo ) == 1 )
			{
				ulRes = (unsigned long) SCadcValorEnteroLargo ( p_valObj->p_cadValor );
			}
			else
			{
				ulRes = 0;
			}
		}
		else
		{
			ulRes = 0;
		}
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

long SValValorEntero ( SValor * p_valObj )
{
	long lRes;

	if ( ES_VALIDO ( p_valObj ) )
	{
		if ( ES_VALIDO ( p_valObj->p_cadValor ) )
		{
			if ( TipEsEntero ( p_valObj->iTipo ) == 1 )
			{
				lRes = SCadcValorEnteroLargo ( p_valObj->p_cadValor );
			}
			else
			{
				lRes = 0;
			}
		}
		else
		{
			lRes = 0;
		}
	}
	else
	{
		lRes = 0;
	}
	return ( lRes );
}

double SValValorReal ( SValor * p_valObj )
{
	double dRes;

	if ( ES_VALIDO ( p_valObj ) )
	{
		if ( ES_VALIDO ( p_valObj->p_cadValor ) )
		{
			if ( TipEsReal ( p_valObj->iTipo ) == 1 )
			{
				dRes = SCadcValorRealDoble ( p_valObj->p_cadValor );
			}
			else
			{
				dRes = 0.0;
			}
		}
		else
		{
			dRes = 0.0;
		}
	}
	else
	{
		dRes = 0.0;
	}
	return ( dRes );
}

SCadena * SValValorCadena ( SValor * p_valObj )
{
	SCadena * p_cadRes;
	
	if ( ES_VALIDO ( p_valObj ) )
	{
		p_cadRes = SCadcCadena  ( p_valObj->p_cadValor );
	}
	else
	{
		p_cadRes = NULL;
	}
	return ( p_cadRes );
}

const char * SValValorLiteral ( SValor * p_valObj )
{
	const char * p_cRes;

	if ( ES_VALIDO ( p_valObj ) )
	{
		if ( ES_VALIDO ( p_valObj->p_cadValor ) )
		{
			p_cRes = SCadValorConstante ( SCadcCadena ( p_valObj->p_cadValor ) );
		}
		else
		{
			p_cRes = NULL;
		}
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

byte * SValValorBinario ( SValor * p_valObj )
{
	byte * p_byRes;

	if ( ES_VALIDO ( p_valObj ) )
	{
		if ( ES_VALIDO ( p_valObj->p_cadValor ) )
		{
			p_byRes = (byte *) SCadValorConstante ( SCadcCadena ( p_valObj->p_cadValor ) );
		}
		else
		{
			p_byRes = NULL;
		}
	}
	else
	{
		p_byRes = NULL;
	}
	return ( p_byRes );
}

void * SValValorPuntero ( SValor * p_valObj )
{
	return ( (void *) SValValorBinario ( p_valObj ) );
}

int SValMaxTam ( SValor * p_valObj )
{
	int iRes;

	if ( ES_VALIDO ( p_valObj ) )
	{
		if ( ES_VALIDO ( p_valObj->p_cadValor ) )
		{
			iRes = SCadMaxTam ( SCadcCadena ( p_valObj->p_cadValor ) );
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

void SValEstablecerValorByte ( SValor * p_valObj, byte byValor )
{
	if ( ES_VALIDO ( p_valObj ) )
	{
		if ( ES_VALIDO ( p_valObj->p_cadValor ) )
		{
			SCadcLimpiar ( p_valObj->p_cadValor );
			if ( TipEsBooleano ( p_valObj->iTipo ) == 1 )
			{
				if ( byValor != 0 )
				{
					byValor = 1;
				}
			}
			SCadcCopiarCaracter ( p_valObj->p_cadValor, byValor );
		}
	}
}

void SValEstablecerValorCaracter ( SValor * p_valObj, char cValor )
{
	if ( ES_VALIDO ( p_valObj ) )
	{
		if ( ES_VALIDO ( p_valObj->p_cadValor ) )
		{
			SCadcLimpiar ( p_valObj->p_cadValor );
			if ( TipEsBooleano ( p_valObj->iTipo ) == 1 )
			{
				if ( ( cValor != '0' ) && ( cValor != '\0') )
				{
					cValor = '1';
				}
				else
				{
					cValor = '0';
				}
			}
			SCadcCopiarCaracter ( p_valObj->p_cadValor, cValor );
		}
	}
}

void SValEstablecerValorBooleano ( SValor * p_valObj, int iValor )
{
	if ( ES_VALIDO ( p_valObj ) )
	{
		if ( ES_VALIDO ( p_valObj->p_cadValor ) )
		{
			SCadcLimpiar ( p_valObj->p_cadValor );
			if ( iValor > 0 )
			{
				iValor = 1;
			}
			else
			{
				iValor = 0;
			}
			SCadcCopiarEntero ( p_valObj->p_cadValor, iValor );
		}
	}
}

void SValEstablecerValorEntero ( SValor * p_valObj, int iValor )
{
	if ( ES_VALIDO ( p_valObj ) )
	{
		if ( ES_VALIDO ( p_valObj->p_cadValor ) )
		{
			SCadcLimpiar ( p_valObj->p_cadValor );
			if ( TipEsBooleano ( p_valObj->iTipo ) == 1 )
			{
				if ( iValor != 0 )
				{
					iValor = 1;
				}
				SCadcCopiarEntero ( p_valObj->p_cadValor, iValor );
			}
			else if ( TipEsNatural ( p_valObj->iTipo ) == 1 )
			{
				if ( iValor < 0 )
				{
					iValor = 0;
				}
				SCadcCopiarEntero ( p_valObj->p_cadValor, iValor );
			}
			else 
			{
				SCadcCopiarEntero ( p_valObj->p_cadValor, iValor );
			}
		}
	}
}

void SValEstablecerValorEnteroLargo ( SValor * p_valObj, long lValor )
{
	if ( ES_VALIDO ( p_valObj ) )
	{
		if ( ES_VALIDO ( p_valObj->p_cadValor ) )
		{
			SCadcLimpiar ( p_valObj->p_cadValor );
			if ( TipEsBooleano ( p_valObj->iTipo ) == 1 )
			{
				if ( lValor != 0 )
				{
					lValor = 1;
				}
				SCadcCopiarEnteroLargo ( p_valObj->p_cadValor, lValor );
			}
			else if ( TipEsNatural ( p_valObj->iTipo ) == 1 )
			{
				if ( lValor < 0 )
				{
					lValor = 0;
				}
				SCadcCopiarEnteroLargo ( p_valObj->p_cadValor, lValor );
			}
			else 
			{
				SCadcCopiarEnteroLargo ( p_valObj->p_cadValor, lValor );
			}
		}
	}
}

void SValEstablecerValorEnteroSinSigno ( SValor * p_valObj, unsigned int uiValor )
{
	if ( ES_VALIDO ( p_valObj ) )
	{
		if ( ES_VALIDO ( p_valObj->p_cadValor ) )
		{
			SCadcLimpiar ( p_valObj->p_cadValor );
			if ( TipEsBooleano ( p_valObj->iTipo ) == 1 )
			{
				if ( uiValor != 0 )
				{
					uiValor = 1;
				}
				SCadcCopiarEnteroSinSigno ( p_valObj->p_cadValor, uiValor );
			}
			else 
			{
				SCadcCopiarEnteroSinSigno ( p_valObj->p_cadValor, uiValor );
			}
		}
	}
}

void SValEstablecerValorEnteroLargoSinSigno ( SValor * p_valObj, unsigned long ulValor )
{
	if ( ES_VALIDO ( p_valObj ) )
	{
		if ( ES_VALIDO ( p_valObj->p_cadValor ) )
		{
			SCadcLimpiar ( p_valObj->p_cadValor );
			if ( TipEsBooleano ( p_valObj->iTipo ) == 1 )
			{
				if ( ulValor != 0 )
				{
					ulValor = 1;
				}
				SCadcCopiarEnteroLargoSinSigno ( p_valObj->p_cadValor, ulValor );
			}
			else 
			{
				SCadcCopiarEnteroLargoSinSigno ( p_valObj->p_cadValor, ulValor );
			}
		}
	}
}

void SValEstablecerValorReal ( SValor * p_valObj, float fValor )
{
	if ( ES_VALIDO ( p_valObj ) )
	{
		if ( ES_VALIDO ( p_valObj->p_cadValor ) )
		{
			SCadcLimpiar ( p_valObj->p_cadValor );
			if ( TipEsBooleano ( p_valObj->iTipo ) == 1 )
			{
				if ( fValor != 0.0 )
				{
					fValor = 1.0;
				}
				SCadcCopiarReal ( p_valObj->p_cadValor, fValor );
			}
			else if ( TipEsNatural ( p_valObj->iTipo ) == 1 )
			{
				if ( fValor < 0.0 )
				{
					fValor = 0.0;
				}
				SCadcCopiarReal ( p_valObj->p_cadValor, fValor );
			}
			else 
			{
				SCadcCopiarReal ( p_valObj->p_cadValor, fValor );
			}
		}
	}
}

void SValEstablecerValorRealDoble ( SValor * p_valObj, double dValor )
{
	if ( ES_VALIDO ( p_valObj ) )
	{
		if ( ES_VALIDO ( p_valObj->p_cadValor ) )
		{
			SCadcLimpiar ( p_valObj->p_cadValor );
			if ( TipEsBooleano ( p_valObj->iTipo ) == 1 )
			{
				if ( dValor != 0.0 )
				{
					dValor = 1.0;
				}
				SCadcCopiarRealDoble ( p_valObj->p_cadValor, dValor );
			}
			else if ( TipEsNatural ( p_valObj->iTipo ) == 1 )
			{
				if ( dValor < 0.0 )
				{
					dValor = 0.0;
				}
				SCadcCopiarRealDoble ( p_valObj->p_cadValor, dValor );
			}
			else 
			{
				SCadcCopiarRealDoble ( p_valObj->p_cadValor, dValor );
			}
		}
	}
}

void SValEstablecerValorBinario ( SValor * p_valObj, byte * p_byValor, int iTam ) 
{
	int iByte;
	
	if ( ES_VALIDO ( p_valObj ) )
	{
		if ( ES_VALIDO ( p_valObj->p_cadValor ) )
		{
			SCadcLimpiar ( p_valObj->p_cadValor );
			if ( ES_VALIDO ( p_byValor ) && ( iTam > 0 ) )
			{
				if ( TipEsBooleano ( p_valObj->iTipo ) == 1 )
				{
					if ( p_byValor [ 0 ] != 0x00 )
					{
						SCadcCopiarEntero ( p_valObj->p_cadValor, 1 );
					}
					else
					{
						SCadcCopiarEntero ( p_valObj->p_cadValor, 0 );
					}
				}
				else 
				{
					if ( iTam > SCadcMaxTam ( p_valObj->p_cadValor ) )
					{
						iTam = SCadcMaxTam ( p_valObj->p_cadValor ); 
					}
					for ( iByte = 0; iByte < iTam; iByte = iByte + 1 )
					{
						SCadcConcatenarCaracter ( p_valObj->p_cadValor, (char) p_byValor [ iByte ] );
					}
				}
			}
		}
	}
}

void SValEstablecerValorLiteral ( SValor * p_valObj, const char * p_cValor )
{
	if ( ES_VALIDO ( p_valObj ) )
	{
		if ( ES_VALIDO ( p_valObj->p_cadValor ) )
		{
			SCadcLimpiar ( p_valObj->p_cadValor );
			if ( ES_VALIDO ( p_cValor ) )
			{
				if ( TipEsBooleano ( p_valObj->iTipo ) == 1 )
				{
					if ( CadEsNumericaExt ( p_cValor, 1 ) == 1 )
					{
						if ( p_cValor [ 0 ] == '1' )
						{
							SCadcCopiarEntero ( p_valObj->p_cadValor, 1 );
						}
						else
						{
							SCadcCopiarEntero ( p_valObj->p_cadValor, 0 );
						}
					}
					else
					{
						SCadcCopiarEntero ( p_valObj->p_cadValor, 0 );
					}
				}
				else if ( TipEsNatural ( p_valObj->iTipo ) == 1 )
				{
					if ( ( CadEsNumerica ( p_cValor ) == 1 ) && ( p_cValor [ 0 ] != '-' ) )
					{
						SCadcCopiarLit ( p_valObj->p_cadValor, p_cValor );
					}
					else
					{
						SCadcCopiarEntero ( p_valObj->p_cadValor, 0 );
					}
				}
				else if ( TipEsNumero ( p_valObj->iTipo ) == 1 )
				{
					if ( CadEsNumerica ( p_cValor ) == 0 )
					{
						SCadcCopiarEntero ( p_valObj->p_cadValor, 0 );
					}
					else
					{
						SCadcCopiarLit ( p_valObj->p_cadValor, p_cValor );
					}
				}
				else
				{
					SCadcCopiarLit ( p_valObj->p_cadValor, p_cValor );
				}
			}
		}
	}
}

void SValEstablecerValorCadena ( SValor * p_valObj, SCadena * p_cadValor )
{
	if ( ES_VALIDO ( p_valObj ) )
	{
		if ( ES_VALIDO ( p_valObj->p_cadValor ) )
		{
			SValEstablecerValorLiteral ( p_valObj, SCadValorConstante ( p_cadValor ) );
		}
	}
}

void SValEstablecerValor ( SValor * p_valObj, SCadenaConv * p_cadValor )
{
	if ( ES_VALIDO ( p_valObj ) )
	{
		if ( ES_VALIDO ( p_valObj->p_cadValor ) )
		{
			SCadcLimpiar ( p_valObj->p_cadValor );
			if ( ES_VALIDO ( p_cadValor ) )
			{
				if ( TipEsBooleano ( p_valObj->iTipo ) == 1 )
				{
					if ( SCadcValorEntero (p_cadValor ) != 0 )
					{
						SCadcCopiarEntero ( p_valObj->p_cadValor, 1 );
					}
					else
					{
						SCadcCopiarEntero ( p_valObj->p_cadValor, 0 );
					}
				}
				else if ( TipEsNatural ( p_valObj->iTipo ) == 1 )
				{
					if ( SCadcValorEnteroLargo ( p_cadValor ) < 0 )
					{
						SCadcCopiarEntero ( p_valObj->p_cadValor, 0 );
					}
					else
					{
						SCadcCopiarEnteroLargo ( p_valObj->p_cadValor, SCadcValorEnteroLargo ( p_cadValor ) );
					}
				}
				else if ( TipEsEntero ( p_valObj->iTipo ) == 1 )
				{
					SCadcCopiarEnteroLargo ( p_valObj->p_cadValor, SCadcValorEnteroLargo ( p_cadValor ) );
				}
				else if ( TipEsReal ( p_valObj->iTipo ) == 1 )
				{
					SCadcCopiarRealDoble ( p_valObj->p_cadValor, SCadcValorRealDoble ( p_cadValor ) );
				}
				else 
				{
					SCadcCopiar ( p_valObj->p_cadValor, p_cadValor );
				}
			}
		}
	}
}

void SValEstablecerValorNumerico ( SValor * p_valObj, SCadenaNumerica * p_cadValor )
{
	if ( ES_VALIDO ( p_valObj ) )
	{
		SValEstablecerValor ( p_valObj, SCadnCadenaConv ( p_cadValor ) );
	}
}

void SValEstablecerValorFecha ( SValor * p_valObj, SFecha * p_fecValor )
{
	if ( ES_VALIDO ( p_valObj ) )
	{
		SValEstablecerValorEnteroLargo ( p_valObj, SFecValor ( p_fecValor ) );
	}
}

void SValEstablecerValorHora ( SValor * p_valObj, SHora * p_horValor )
{
	if ( ES_VALIDO ( p_valObj ) )
	{
		SValEstablecerValorEnteroLargo ( p_valObj, SHorValor ( p_horValor ) );
	}
}

void SValEstablecerValorFechaHora ( SValor * p_valObj, SFechaHora * p_fechValor )
{
	if ( ES_VALIDO ( p_valObj ) )
	{
		SValEstablecerValorRealDoble ( p_valObj, SFecHorValor ( p_fechValor ) );
	}
}

void SValEstablecerValorPuntero ( SValor * p_valObj, void * p_vValor )
{
	if ( ES_VALIDO ( p_valObj ) )
	{
		SValEstablecerValorBinario ( p_valObj, (byte *) p_vValor, sizeof ( void * ) );
	}
}

void SValAsignar ( SValor * p_valObj, SValor * p_valValor )
{
	if ( ES_VALIDO ( p_valObj ) && ES_VALIDO ( p_valValor ) )
	{
		_SValInicializar ( p_valObj, SValTipo ( p_valValor ), SValMaxTam ( p_valValor ) );
		SValEstablecerValor ( p_valObj, SValValor ( p_valValor ) );
	}
}

void SValLimpiar ( SValor * p_valObj )
{
	if ( ES_VALIDO ( p_valObj ) )
	{
		if ( ES_VALIDO ( p_valObj->p_cadValor ) )
		{
			SCadcLimpiar ( p_valObj->p_cadValor );
			if ( ( TipEsBooleano ( p_valObj->iTipo ) == 1 ) || 
				 ( TipEsNumero ( p_valObj->iTipo ) == 1 ) || 
				 ( TipEsByte ( p_valObj->iTipo ) == 1 ) || 
				 ( TipEsTiempo ( p_valObj->iTipo ) == 1 ) )
			{
				SCadcConcatenarCaracter ( p_valObj->p_cadValor, '0' );
			}
			else if ( TipEsCaracter ( p_valObj->iTipo ) == 1 ) 
			{
				SCadcConcatenarCaracter ( p_valObj->p_cadValor, '\0' );
			}
		}
	}
}

int SValTieneValor ( SValor * p_valObj )
{
	int iRes;

	if ( ES_VALIDO ( p_valObj ) )
	{
		if ( ES_VALIDO ( p_valObj->p_cadValor ) )
		{
			if ( SCadLongitud ( SCadcCadena ( p_valObj->p_cadValor ) ) > 0 )
			{
				if ( ( TipEsBooleano ( p_valObj->iTipo ) == 1 ) || 
					 ( TipEsNumero ( p_valObj->iTipo ) == 1 ) )
				{
					if ( SCadcEsNumerica ( p_valObj->p_cadValor ) == 1 )
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

SValor * SValDuplicar ( SValor * p_valObj )
{
    SValor * p_valRes;

	if ( ES_VALIDO ( p_valObj ) )
    {
		  p_valRes = SValCrearExt ( p_valObj->iTipo, SValMaxTam ( p_valObj ) );
		  if ( ES_VALIDO ( p_valRes ) )
		  {
			  SValEstablecerValor ( p_valRes, p_valObj->p_cadValor );
		  }
	}
	else
	{
		p_valRes = NULL;
	}
	return ( p_valRes );
}

int SValEsByte ( SValor * p_valObj )
{
	int iRes;

	if ( ES_VALIDO ( p_valObj ) )
	{
		iRes = TipEsByte ( p_valObj->iTipo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SValEsCaracter ( SValor * p_valObj )
{
	int iRes;

	if ( ES_VALIDO ( p_valObj ) )
	{
		iRes = TipEsCaracter ( p_valObj->iTipo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SValEsNatural ( SValor * p_valObj )
{
	int iRes;

	if ( ES_VALIDO ( p_valObj ) )
	{
		iRes = TipEsNatural ( p_valObj->iTipo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SValEsEntero ( SValor * p_valObj )
{
	int iRes;

	if ( ES_VALIDO ( p_valObj ) )
	{
		iRes = TipEsEntero ( p_valObj->iTipo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SValEsReal ( SValor * p_valObj )
{
	int iRes;

	if ( ES_VALIDO ( p_valObj ) )
	{
		iRes = TipEsReal ( p_valObj->iTipo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SValEsBinario ( SValor * p_valObj )
{
	int iRes;

	if ( ES_VALIDO ( p_valObj ) )
	{
		iRes = TipEsBinario ( p_valObj->iTipo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SValEsCadena ( SValor * p_valObj )
{
	int iRes;

	if ( ES_VALIDO ( p_valObj ) )
	{
		iRes = TipEsCadena ( p_valObj->iTipo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SValEsNumerico ( SValor * p_valObj )
{
	int iRes;

	if ( ES_VALIDO ( p_valObj ) )
	{
		iRes = TipEsNumero ( p_valObj->iTipo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SValEsPuntero ( SValor * p_valObj )
{
	int iRes;

	if ( ES_VALIDO ( p_valObj ) )
	{
		iRes = TipEsObjeto ( p_valObj->iTipo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SValEsFecha ( SValor * p_valObj )
{
	int iRes;

	if ( ES_VALIDO ( p_valObj ) )
	{
		iRes = TipEsFecha ( p_valObj->iTipo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SValEsHora ( SValor * p_valObj )
{
	int iRes;

	if ( ES_VALIDO ( p_valObj ) )
	{
		iRes = TipEsHora ( p_valObj->iTipo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SValEsFechaHora ( SValor * p_valObj )
{
	int iRes;

	if ( ES_VALIDO ( p_valObj ) )
	{
		iRes = TipEsFechaHora ( p_valObj->iTipo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SValEsIgual ( SValor * p_valObj1, SValor * p_valObj2 )
{
	int iRes;

	if ( ES_VALIDO ( p_valObj1 ) && ES_VALIDO ( p_valObj2 ) )
	{
		if ( SValTipo ( p_valObj1 ) == SValTipo ( p_valObj2 ) )
		{
			iRes = SCadcEsIgual ( SValValor ( p_valObj1 ), SValValor ( p_valObj2 ) );
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

int SValEsIgualNoTipado ( SValor * p_valObj1, SValor * p_valObj2 )
{
	int iRes;

	if ( ES_VALIDO ( p_valObj1 ) && ES_VALIDO ( p_valObj2 ) )
	{
		iRes = SCadcEsIgual ( SValValor ( p_valObj1 ), SValValor ( p_valObj2 ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SValEsIgualValorByte ( SValor * p_valObj, byte byValor )
{
	int iRes;

	if ( ES_VALIDO ( p_valObj ) )
	{
		if ( SValValorByte ( p_valObj ) == byValor )
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

int SValEsIgualValorEntero ( SValor * p_valObj, int iValor )
{
	int iRes;

	if ( ES_VALIDO ( p_valObj ) )
	{
		if ( SValValorEntero ( p_valObj ) == (long) iValor )
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

int SValEsIgualValorEnteroLargo ( SValor * p_valObj, long lValor )
{
	int iRes;

	if ( ES_VALIDO ( p_valObj ) )
	{
		if ( SValValorEntero ( p_valObj ) == lValor )
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

int SValEsIgualValorEnteroSinSigno ( SValor * p_valObj, unsigned int uiValor )
{
	int iRes;

	if ( ES_VALIDO ( p_valObj ) )
	{
		if ( SValValorNatural ( p_valObj ) == (unsigned long) uiValor )
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

int SValEsIgualValorEnteroLargoSinSigno ( SValor * p_valObj, unsigned long ulValor )
{
	int iRes;

	if ( ES_VALIDO ( p_valObj ) )
	{
		if ( SValValorNatural ( p_valObj ) == ulValor )
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

int SValEsIgualValorReal ( SValor * p_valObj, float fValor )
{
	int iRes;

	if ( ES_VALIDO ( p_valObj ) )
	{
		if ( SValValorReal ( p_valObj ) == (double) fValor )
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

int SValEsIgualValorRealDoble ( SValor * p_valObj, double dValor )
{
	int iRes;

	if ( ES_VALIDO ( p_valObj ) )
	{
		if ( SValValorReal ( p_valObj ) == dValor )
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

int SValEsIgualValorLiteral ( SValor * p_valObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_valObj ) && ES_VALIDO ( p_cValor ) )
	{
		iRes = SCadEsIgualLiteral ( SValValorCadena ( p_valObj ), p_cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SValEsIgualValorBinario ( SValor * p_valObj, byte * p_byValor, int iTam )
{
	int iRes;

	if ( ES_VALIDO ( p_valObj ) && ES_VALIDO ( p_byValor ) && ( iTam > 0 ) )
	{
		if ( iTam > SValMaxTam ( p_valObj ) )
		{
			iTam = SValMaxTam ( p_valObj );
		}
		iRes = MemEsIgual ( SValValorBinario ( p_valObj ), p_byValor, iTam );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SValEsIgualValorCadena ( SValor * p_valObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_valObj ) && ES_VALIDO ( p_cadValor ) )
	{
		iRes = SCadEsIgual ( SValValorCadena ( p_valObj ), p_cadValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SValEsIgualValor ( SValor * p_valObj, SCadenaConv * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_valObj ) && ES_VALIDO ( p_cadValor ) )
	{
		iRes = SCadcEsIgual ( SValValor ( p_valObj ), p_cadValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SValEsIgualValorNumerico ( SValor * p_valObj, SCadenaNumerica * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_valObj ) && ES_VALIDO ( p_cadValor ) )
	{
		iRes = SCadcEsIgual ( SValValor ( p_valObj ), SCadnCadenaConv ( p_cadValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SValEsIgualValorFecha ( SValor * p_valObj, SFecha * p_fecValor )
{
	int iRes;

	if ( ES_VALIDO ( p_valObj ) && ES_VALIDO ( p_fecValor ) )
	{
		iRes = SValEsIgualValorEnteroLargo ( p_valObj, SFecValor ( p_fecValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SValEsIgualValorHora ( SValor * p_valObj, SHora * p_horValor )
{
	int iRes;

	if ( ES_VALIDO ( p_valObj ) && ES_VALIDO ( p_horValor ) )
	{
		iRes = SValEsIgualValorEnteroLargo ( p_valObj, SHorValor ( p_horValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SValEsIgualValorFechaHora ( SValor * p_valObj, SFechaHora * p_fechValor )
{
	int iRes;

	if ( ES_VALIDO ( p_valObj ) && ES_VALIDO ( p_fechValor ) )
	{
		iRes = SValEsIgualValorRealDoble ( p_valObj, SFecHorValor ( p_fechValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

void _SValInicializar ( SValor * p_valObj, int iTipo, int iMaxTam )
{
	if ( ES_VALIDO ( p_valObj ) )
	{
		if ( TipEsValido ( iTipo ) == 1 )
		{
			p_valObj->iTipo = iTipo;
		}
		else
		{
			p_valObj->iTipo = TIP_DEFECTO;
		}
		SCadcDestruir ( &(p_valObj->p_cadValor) );
		if ( TipEsCadena ( p_valObj->iTipo ) == 1 )
		{
			if ( iMaxTam <= 0 )
			{
				iMaxTam = CAD_TAM_DEFECTO;
			}
			p_valObj->p_cadValor = SCadcCrear ( iMaxTam );
		}
		else if ( TipEsBooleano ( p_valObj->iTipo ) == 1 )
		{
			p_valObj->p_cadValor = SCadcCrear ( 1 );
		}
		else if ( TipEsCaracter ( p_valObj->iTipo ) == 1 )
		{
			p_valObj->p_cadValor = SCadcCrear ( 1 );
		}
		else if ( TipEsByte ( p_valObj->iTipo ) == 1 )
		{
			p_valObj->p_cadValor = SCadcCrear ( 1 );
		}
		else if ( TipEsNatural ( p_valObj->iTipo ) == 1 )
		{
			p_valObj->p_cadValor = SCadcCrear ( TIP_MAX_TAM_CAD_ENTERO_LARGO );
		}
		else if ( TipEsEntero ( p_valObj->iTipo ) == 1 )
		{
			p_valObj->p_cadValor = SCadcCrear ( TIP_MAX_TAM_CAD_ENTERO_LARGO );
		}
		else if ( TipEsReal ( p_valObj->iTipo ) == 1 )
		{
			p_valObj->p_cadValor = SCadcCrear ( TIP_MAX_TAM_CAD_REAL_DOBLE );
		}
		else if ( TipEsTiempo ( p_valObj->iTipo ) == 1 )
		{
			if ( iMaxTam <= 0 )
			{
				iMaxTam = TipTam ( TIP_TIEMPO );
			}
			p_valObj->p_cadValor = SCadcCrear ( iMaxTam );
		}
		else if ( TipEsBinario ( p_valObj->iTipo ) == 1 )
		{
			if ( iMaxTam > 0 )
			{
				p_valObj->p_cadValor = SCadcCrear ( iMaxTam );
			}
			else
			{
				p_valObj->iTipo = TIP_NINGUNO;
				p_valObj->p_cadValor = NULL;
			}
		}
		else if ( TipEsObjeto ( p_valObj->iTipo ) == 1 )
		{
			iMaxTam = sizeof ( void * );
			p_valObj->p_cadValor = SCadcCrear ( iMaxTam );
		}
		else
		{
			p_valObj->iTipo = TIP_NINGUNO;
		}
	}
}

