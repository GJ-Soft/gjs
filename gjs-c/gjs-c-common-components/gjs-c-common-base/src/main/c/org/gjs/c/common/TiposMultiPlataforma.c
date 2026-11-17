#include "TiposMultiPlataforma.h"

#include "Memoria.h"
#include "Errores.h"


/* Los reales se guardan con sus bits, así que tienen que ser IEEE 754:
   float binary32 (base 2, 24 bits de mantisa, exponente hasta 128) y double
   binary64 (53 bits de mantisa, exponente hasta 1024). Una plataforma con
   otro formato no compila, en vez de escribir bits que signifiquen otra cosa: */
_Static_assert ( FLT_RADIX == 2, "los reales tienen que ser binarios (IEEE 754)" );
_Static_assert ( sizeof ( float ) == MPL_TAM_REAL, "float tiene que medir 4 bytes" );
_Static_assert ( FLT_MANT_DIG == 24, "float tiene que ser IEEE 754 binary32" );
_Static_assert ( FLT_MAX_EXP == 128, "float tiene que ser IEEE 754 binary32" );
_Static_assert ( sizeof ( double ) == MPL_TAM_REAL_DOBLE, "double tiene que medir 8 bytes" );
_Static_assert ( DBL_MANT_DIG == 53, "double tiene que ser IEEE 754 binary64" );
_Static_assert ( DBL_MAX_EXP == 1024, "double tiene que ser IEEE 754 binary64" );

/* Los tipos de C tienen que caber en el tamaño con que se guardan. Sólo long
   puede ser más pequeño (4 bytes en Windows), y al leerlo se comprueba que el
   valor quepa: */
_Static_assert ( sizeof ( short ) == MPL_TAM_SHORT, "short tiene que medir 2 bytes" );
_Static_assert ( sizeof ( int ) == MPL_TAM_INT, "int tiene que medir 4 bytes" );
_Static_assert ( sizeof ( long ) <= MPL_TAM_LONG, "long no puede medir mas de 8 bytes" );
_Static_assert ( sizeof ( long long ) == MPL_TAM_LLONG, "long long tiene que medir 8 bytes" );


/* Escribe los iTam bytes de menor peso de ullValor, empezando por el de menor
   peso. Los desplazamientos operan sobre el valor, así que el resultado no
   depende del orden de bytes de la máquina. */
static int _MplEscribir ( byte * p_byDest, uint64_t ullValor, int iTam )
{
	int iRes;

	if ( ES_VALIDO ( p_byDest ) )
	{
		for ( int i = 0; i < iTam; i = i + 1 )
		{
			p_byDest[ i ] = (byte) ( ullValor & 0xFF );
			ullValor = ullValor >> 8;
		}
		iRes = iTam;
	}
	else
	{
		ERROR_ESTABLECER ( ERR_MEMORIA_INVALIDA );
		iRes = 0;
	}
	return ( iRes );
}

/* Compone el valor de iTam bytes guardados con el de menor peso primero. */
static uint64_t _MplLeer ( const byte * p_byOrig, int iTam )
{
	uint64_t ullRes = 0;

	if ( ES_VALIDO ( p_byOrig ) )
	{
		for ( int i = iTam - 1; i >= 0; i = i - 1 )
		{
			ullRes = ( ullRes << 8 ) | p_byOrig[ i ];
		}
	}
	else
	{
		ERROR_ESTABLECER ( ERR_MEMORIA_INVALIDA );
	}
	return ( ullRes );
}

/* 1 si llValor está entre llMin y llMax. */
static int _MplEnRango ( int64_t llValor, int64_t llMin, int64_t llMax )
{
	int iRes;

	if ( llValor >= llMin )
	{
		if ( llValor <= llMax )
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

/* 1 si ullValor no pasa de ullMax. */
static int _MplEnRangoSinSigno ( uint64_t ullValor, uint64_t ullMax )
{
	int iRes;

	if ( ullValor <= ullMax )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

/* Interpreta los iTam bytes bajos de ullValor en complemento a dos. Se hace a
   mano porque pasar a con signo un valor que no cabe depende del compilador. */
static int64_t _MplConSigno ( uint64_t ullValor, int iTam )
{
	int64_t llRes;
	uint64_t ullMascara;

	if ( iTam < MPL_TAM_64 )
	{
		ullMascara = ( ( (uint64_t) 1 ) << ( iTam * 8 ) ) - 1;
	}
	else
	{
		ullMascara = UINT64_MAX;
	}
	if ( ( ullValor & ( ( ullMascara >> 1 ) + 1 ) ) == 0 )
	{
		llRes = (int64_t) ullValor;
	}
	else
	{
		llRes = - (int64_t) ( ~ullValor & ullMascara ) - 1;
	}
	return ( llRes );
}




/* Rutinas: */
int MplEscribirI8 ( byte * p_byDest, int8_t iValor )
{
	return ( _MplEscribir ( p_byDest, (uint8_t) iValor, MPL_TAM_8 ) );
}

int MplEscribirU8 ( byte * p_byDest, uint8_t uiValor )
{
	return ( _MplEscribir ( p_byDest, uiValor, MPL_TAM_8 ) );
}

int MplEscribirI16 ( byte * p_byDest, int16_t iValor )
{
	return ( _MplEscribir ( p_byDest, (uint16_t) iValor, MPL_TAM_16 ) );
}

int MplEscribirU16 ( byte * p_byDest, uint16_t uiValor )
{
	return ( _MplEscribir ( p_byDest, uiValor, MPL_TAM_16 ) );
}

int MplEscribirI32 ( byte * p_byDest, int32_t iValor )
{
	return ( _MplEscribir ( p_byDest, (uint32_t) iValor, MPL_TAM_32 ) );
}

int MplEscribirU32 ( byte * p_byDest, uint32_t uiValor )
{
	return ( _MplEscribir ( p_byDest, uiValor, MPL_TAM_32 ) );
}

int MplEscribirI64 ( byte * p_byDest, int64_t llValor )
{
	return ( _MplEscribir ( p_byDest, (uint64_t) llValor, MPL_TAM_64 ) );
}

int MplEscribirU64 ( byte * p_byDest, uint64_t ullValor )
{
	return ( _MplEscribir ( p_byDest, ullValor, MPL_TAM_64 ) );
}

int MplEscribirReal ( byte * p_byDest, float fValor )
{
	union { float fValor; uint32_t uiBits; } uniValor;

	uniValor.fValor = fValor;
	return ( _MplEscribir ( p_byDest, uniValor.uiBits, MPL_TAM_REAL ) );
}

int MplEscribirRealDoble ( byte * p_byDest, double dValor )
{
	union { double dValor; uint64_t ullBits; } uniValor;

	uniValor.dValor = dValor;
	return ( _MplEscribir ( p_byDest, uniValor.ullBits, MPL_TAM_REAL_DOBLE ) );
}


int8_t MplLeerI8 ( const byte * p_byOrig )
{
	return ( (int8_t) _MplConSigno ( _MplLeer ( p_byOrig, MPL_TAM_8 ), MPL_TAM_8 ) );
}

uint8_t MplLeerU8 ( const byte * p_byOrig )
{
	return ( (uint8_t) _MplLeer ( p_byOrig, MPL_TAM_8 ) );
}

int16_t MplLeerI16 ( const byte * p_byOrig )
{
	return ( (int16_t) _MplConSigno ( _MplLeer ( p_byOrig, MPL_TAM_16 ), MPL_TAM_16 ) );
}

uint16_t MplLeerU16 ( const byte * p_byOrig )
{
	return ( (uint16_t) _MplLeer ( p_byOrig, MPL_TAM_16 ) );
}

int32_t MplLeerI32 ( const byte * p_byOrig )
{
	return ( (int32_t) _MplConSigno ( _MplLeer ( p_byOrig, MPL_TAM_32 ), MPL_TAM_32 ) );
}

uint32_t MplLeerU32 ( const byte * p_byOrig )
{
	return ( (uint32_t) _MplLeer ( p_byOrig, MPL_TAM_32 ) );
}

int64_t MplLeerI64 ( const byte * p_byOrig )
{
	return ( _MplConSigno ( _MplLeer ( p_byOrig, MPL_TAM_64 ), MPL_TAM_64 ) );
}

uint64_t MplLeerU64 ( const byte * p_byOrig )
{
	return ( _MplLeer ( p_byOrig, MPL_TAM_64 ) );
}

float MplLeerReal ( const byte * p_byOrig )
{
	union { float fValor; uint32_t uiBits; } uniValor;

	uniValor.uiBits = (uint32_t) _MplLeer ( p_byOrig, MPL_TAM_REAL );
	return ( uniValor.fValor );
}

double MplLeerRealDoble ( const byte * p_byOrig )
{
	union { double dValor; uint64_t ullBits; } uniValor;

	uniValor.ullBits = _MplLeer ( p_byOrig, MPL_TAM_REAL_DOBLE );
	return ( uniValor.dValor );
}


int MplEscribirShort ( byte * p_byDest, short sValor )
{
	return ( MplEscribirI16 ( p_byDest, sValor ) );
}

int MplEscribirUShort ( byte * p_byDest, unsigned short usValor )
{
	return ( MplEscribirU16 ( p_byDest, usValor ) );
}

int MplEscribirInt ( byte * p_byDest, int iValor )
{
	return ( MplEscribirI32 ( p_byDest, iValor ) );
}

int MplEscribirUInt ( byte * p_byDest, unsigned int uiValor )
{
	return ( MplEscribirU32 ( p_byDest, uiValor ) );
}

int MplEscribirLong ( byte * p_byDest, long lValor )
{
	return ( MplEscribirI64 ( p_byDest, lValor ) );
}

int MplEscribirULong ( byte * p_byDest, unsigned long ulValor )
{
	return ( MplEscribirU64 ( p_byDest, ulValor ) );
}

int MplEscribirLLong ( byte * p_byDest, long long llValor )
{
	return ( MplEscribirI64 ( p_byDest, llValor ) );
}

int MplEscribirULLong ( byte * p_byDest, unsigned long long ullValor )
{
	return ( MplEscribirU64 ( p_byDest, ullValor ) );
}


short MplLeerShort ( const byte * p_byOrig )
{
	return ( MplLeerI16 ( p_byOrig ) );
}

unsigned short MplLeerUShort ( const byte * p_byOrig )
{
	return ( MplLeerU16 ( p_byOrig ) );
}

int MplLeerInt ( const byte * p_byOrig )
{
	return ( MplLeerI32 ( p_byOrig ) );
}

unsigned int MplLeerUInt ( const byte * p_byOrig )
{
	return ( MplLeerU32 ( p_byOrig ) );
}

long MplLeerLong ( const byte * p_byOrig )
{
	long lRes;

	if ( MplCabeLong ( p_byOrig ) == 1 )
	{
		lRes = (long) MplLeerI64 ( p_byOrig );
	}
	else
	{
		ERROR_ESTABLECER ( ERR_CONVERSION_IMPOSIBLE );
		lRes = 0;
	}
	return ( lRes );
}

unsigned long MplLeerULong ( const byte * p_byOrig )
{
	unsigned long ulRes;

	if ( MplCabeULong ( p_byOrig ) == 1 )
	{
		ulRes = (unsigned long) MplLeerU64 ( p_byOrig );
	}
	else
	{
		ERROR_ESTABLECER ( ERR_CONVERSION_IMPOSIBLE );
		ulRes = 0;
	}
	return ( ulRes );
}

/* Si el valor guardado cabe en el long de esta máquina. No anota error si no
   cabe: es una pregunta. */
int MplCabeLong ( const byte * p_byOrig )
{
	return ( _MplEnRango ( MplLeerI64 ( p_byOrig ), LONG_MIN, LONG_MAX ) );
}

int MplCabeULong ( const byte * p_byOrig )
{
	return ( _MplEnRangoSinSigno ( MplLeerU64 ( p_byOrig ), ULONG_MAX ) );
}

long long MplLeerLLong ( const byte * p_byOrig )
{
	return ( MplLeerI64 ( p_byOrig ) );
}

unsigned long long MplLeerULLong ( const byte * p_byOrig )
{
	return ( MplLeerU64 ( p_byOrig ) );
}


int MplTamShort ()
{
	return ( MPL_TAM_SHORT );
}

int MplTamUShort ()
{
	return ( MPL_TAM_SHORT );
}

int MplTamInt ()
{
	return ( MPL_TAM_INT );
}

int MplTamUInt ()
{
	return ( MPL_TAM_INT );
}

int MplTamLong ()
{
	return ( MPL_TAM_LONG );
}

int MplTamULong ()
{
	return ( MPL_TAM_LONG );
}

int MplTamLLong ()
{
	return ( MPL_TAM_LLONG );
}

int MplTamULLong ()
{
	return ( MPL_TAM_LLONG );
}

int MplTamReal ()
{
	return ( MPL_TAM_REAL );
}

int MplTamRealDoble ()
{
	return ( MPL_TAM_REAL_DOBLE );
}
