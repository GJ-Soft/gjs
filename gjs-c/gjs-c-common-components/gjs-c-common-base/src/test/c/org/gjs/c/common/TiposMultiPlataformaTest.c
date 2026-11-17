#include "Base.h"

#include "TiposMultiPlataforma.h"



/* Compara los iTam primeros bytes de p_byBuf con los esperados. */
static int BytesSon ( byte * p_byBuf, const byte * p_byEsperados, int iTam )
{
	int iRes = BOOL_VAL_CIERTO;
	for ( int i = 0; i < iTam; i = i + 1 )
	{
		if ( p_byBuf[ i ] != p_byEsperados[ i ] )
		{
			printf( "  byte %d: se esperaba 0x%02X: 0x%02X\n", i, p_byEsperados[ i ], p_byBuf[ i ] );
			iRes = BOOL_VAL_FALSO;
		}
	}
	return ( iRes );
}

static int TestMplEscribirEnteros01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test MplEscribirEnteros 01:\n" );
	byte byBuf[ 10 ];

	const byte byU16[] = { 0x34, 0x12 };
	if ( ( MplEscribirU16 ( byBuf, 0x1234 ) != 2 ) || ( BytesSon ( byBuf, byU16, 2 ) == BOOL_VAL_FALSO ) )
	{
		printf( "Error caso 1: 0x1234 deberia ocupar 34 12\n" );
		iRes = BOOL_VAL_FALSO;
	}
	const byte byU32[] = { 0x78, 0x56, 0x34, 0x12 };
	if ( ( MplEscribirU32 ( byBuf, 0x12345678 ) != 4 ) || ( BytesSon ( byBuf, byU32, 4 ) == BOOL_VAL_FALSO ) )
	{
		printf( "Error caso 2: 0x12345678 deberia ocupar 78 56 34 12\n" );
		iRes = BOOL_VAL_FALSO;
	}
	const byte byU64[] = { 0xEF, 0xCD, 0xAB, 0x89, 0x67, 0x45, 0x23, 0x01 };
	if ( ( MplEscribirU64 ( byBuf, 0x0123456789ABCDEFULL ) != 8 ) || ( BytesSon ( byBuf, byU64, 8 ) == BOOL_VAL_FALSO ) )
	{
		printf( "Error caso 3: 0x0123456789ABCDEF deberia ocupar EF CD AB 89 67 45 23 01\n" );
		iRes = BOOL_VAL_FALSO;
	}
	const byte byI8[] = { 0x80 };
	if ( ( MplEscribirI8 ( byBuf, -128 ) != 1 ) || ( BytesSon ( byBuf, byI8, 1 ) == BOOL_VAL_FALSO ) )
	{
		printf( "Error caso 4: -128 deberia ocupar 80\n" );
		iRes = BOOL_VAL_FALSO;
	}
	const byte byI16[] = { 0xC7, 0xCF };
	if ( ( MplEscribirI16 ( byBuf, -12345 ) != 2 ) || ( BytesSon ( byBuf, byI16, 2 ) == BOOL_VAL_FALSO ) )
	{
		printf( "Error caso 5: -12345 deberia ocupar C7 CF\n" );
		iRes = BOOL_VAL_FALSO;
	}
	const byte byI32[] = { 0xFE, 0xFF, 0xFF, 0xFF };
	if ( ( MplEscribirI32 ( byBuf, -2 ) != 4 ) || ( BytesSon ( byBuf, byI32, 4 ) == BOOL_VAL_FALSO ) )
	{
		printf( "Error caso 6: -2 deberia ocupar FE FF FF FF\n" );
		iRes = BOOL_VAL_FALSO;
	}
	const byte byI64[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80 };
	if ( ( MplEscribirI64 ( byBuf, INT64_MIN ) != 8 ) || ( BytesSon ( byBuf, byI64, 8 ) == BOOL_VAL_FALSO ) )
	{
		printf( "Error caso 7: INT64_MIN deberia ocupar 00 00 00 00 00 00 00 80\n" );
		iRes = BOOL_VAL_FALSO;
	}
	const byte byU8[] = { 0xFF };
	if ( ( MplEscribirU8 ( byBuf, 255 ) != 1 ) || ( BytesSon ( byBuf, byU8, 1 ) == BOOL_VAL_FALSO ) )
	{
		printf( "Error caso 8: 255 deberia ocupar FF\n" );
		iRes = BOOL_VAL_FALSO;
	}

	/* No escribe mas alla de su tamano. */
	for ( int i = 0; i < 10; i = i + 1 )
	{
		byBuf[ i ] = 0xAA;
	}
	MplEscribirU16 ( byBuf + 1, 0 );
	const byte byVecinos[] = { 0xAA, 0x00, 0x00, 0xAA };
	if ( BytesSon ( byBuf, byVecinos, 4 ) == BOOL_VAL_FALSO )
	{
		printf( "Error caso 9: solo deberia escribir los dos bytes del valor\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestMplLeerEnteros01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test MplLeerEnteros 01:\n" );

	/* Bytes fijos, no escritos por el propio modulo. */
	const byte byDatos[] = { 0x00, 0x00, 0x00, 0x80, 0xFF, 0xFF, 0xFF, 0x7F };
	if ( MplLeerI32 ( byDatos ) != INT32_MIN )
	{
		printf( "Error caso 1: 00 00 00 80 deberia ser INT32_MIN: %ld\n", (long) MplLeerI32 ( byDatos ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MplLeerU32 ( byDatos ) != 2147483648UL )
	{
		printf( "Error caso 2: 00 00 00 80 deberia ser 2147483648: %lu\n", (unsigned long) MplLeerU32 ( byDatos ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MplLeerI32 ( byDatos + 4 ) != INT32_MAX )
	{
		printf( "Error caso 3: FF FF FF 7F deberia ser INT32_MAX: %ld\n", (long) MplLeerI32 ( byDatos + 4 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MplLeerI64 ( byDatos ) != 0x7FFFFFFF80000000LL )
	{
		printf( "Error caso 4: se esperaba 0x7FFFFFFF80000000\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MplLeerI16 ( byDatos + 2 ) != INT16_MIN )
	{
		printf( "Error caso 5: 00 80 deberia ser INT16_MIN: %d\n", MplLeerI16 ( byDatos + 2 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MplLeerU16 ( byDatos + 2 ) != 0x8000 )
	{
		printf( "Error caso 6: 00 80 deberia ser 0x8000: %u\n", MplLeerU16 ( byDatos + 2 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MplLeerI8 ( byDatos + 4 ) != -1 )
	{
		printf( "Error caso 7: FF deberia ser -1: %d\n", MplLeerI8 ( byDatos + 4 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MplLeerU8 ( byDatos + 4 ) != 255 )
	{
		printf( "Error caso 8: FF deberia ser 255: %u\n", MplLeerU8 ( byDatos + 4 ) );
		iRes = BOOL_VAL_FALSO;
	}

	/* Ida y vuelta en los extremos. */
	byte byBuf[ 8 ];
	MplEscribirI64 ( byBuf, INT64_MIN );
	if ( MplLeerI64 ( byBuf ) != INT64_MIN )
	{
		printf( "Error caso 9: ida y vuelta de INT64_MIN\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MplEscribirI64 ( byBuf, INT64_MAX );
	if ( MplLeerI64 ( byBuf ) != INT64_MAX )
	{
		printf( "Error caso 10: ida y vuelta de INT64_MAX\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MplEscribirU64 ( byBuf, UINT64_MAX );
	if ( MplLeerU64 ( byBuf ) != UINT64_MAX )
	{
		printf( "Error caso 11: ida y vuelta de UINT64_MAX\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MplLeerI64 ( byBuf ) != -1 )
	{
		printf( "Error caso 12: FF x 8 como con signo deberia ser -1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MplEscribirI16 ( byBuf, -12345 );
	if ( MplLeerI16 ( byBuf ) != -12345 )
	{
		printf( "Error caso 13: ida y vuelta de -12345: %d\n", MplLeerI16 ( byBuf ) );
		iRes = BOOL_VAL_FALSO;
	}
	MplEscribirI8 ( byBuf, INT8_MIN );
	if ( MplLeerI8 ( byBuf ) != INT8_MIN )
	{
		printf( "Error caso 14: ida y vuelta de INT8_MIN: %d\n", MplLeerI8 ( byBuf ) );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestMplReales01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test MplReales 01:\n" );
	byte byBuf[ 8 ];

	/* 1.0f = 0x3F800000 */
	const byte byUno[] = { 0x00, 0x00, 0x80, 0x3F };
	if ( ( MplEscribirReal ( byBuf, 1.0f ) != 4 ) || ( BytesSon ( byBuf, byUno, 4 ) == BOOL_VAL_FALSO ) )
	{
		printf( "Error caso 1: 1.0f deberia ocupar 00 00 80 3F\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* -2.5 = 0xC004000000000000 */
	const byte byMenos[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0xC0 };
	if ( ( MplEscribirRealDoble ( byBuf, -2.5 ) != 8 ) || ( BytesSon ( byBuf, byMenos, 8 ) == BOOL_VAL_FALSO ) )
	{
		printf( "Error caso 2: -2.5 deberia ocupar 00 00 00 00 00 00 04 C0\n" );
		iRes = BOOL_VAL_FALSO;
	}

	/* Bytes fijos: 0x40490FDB es 3.14159274f y 0x3FB999999999999A es 0.1. */
	const byte byPi[] = { 0xDB, 0x0F, 0x49, 0x40 };
	if ( MplLeerReal ( byPi ) != 3.14159274f )
	{
		printf( "Error caso 3: DB 0F 49 40 deberia ser 3.14159274f: %.9g\n", MplLeerReal ( byPi ) );
		iRes = BOOL_VAL_FALSO;
	}
	const byte byDecima[] = { 0x9A, 0x99, 0x99, 0x99, 0x99, 0x99, 0xB9, 0x3F };
	if ( MplLeerRealDoble ( byDecima ) != 0.1 )
	{
		printf( "Error caso 4: 9A 99 99 99 99 99 B9 3F deberia ser 0.1: %.17g\n", MplLeerRealDoble ( byDecima ) );
		iRes = BOOL_VAL_FALSO;
	}

	MplEscribirRealDoble ( byBuf, DBL_MAX );
	if ( MplLeerRealDoble ( byBuf ) != DBL_MAX )
	{
		printf( "Error caso 5: ida y vuelta de DBL_MAX\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MplEscribirReal ( byBuf, -FLT_MIN );
	if ( MplLeerReal ( byBuf ) != -FLT_MIN )
	{
		printf( "Error caso 6: ida y vuelta de -FLT_MIN\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestMplNulos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test MplNulos 01:\n" );

	ErrLimpiar ();
	if ( MplEscribirU32 ( NULL, 1 ) != 0 )
	{
		printf( "Error caso 1: escribir en un destino nulo deberia devolver 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ErrCodigo () != ERR_MEMORIA_INVALIDA )
	{
		printf( "Error caso 2: se esperaba ERR_MEMORIA_INVALIDA: %d\n", ErrCodigo () );
		iRes = BOOL_VAL_FALSO;
	}
	ErrLimpiar ();
	if ( MplLeerI64 ( NULL ) != 0 )
	{
		printf( "Error caso 3: leer de un origen nulo deberia devolver 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ErrCodigo () != ERR_MEMORIA_INVALIDA )
	{
		printf( "Error caso 4: se esperaba ERR_MEMORIA_INVALIDA: %d\n", ErrCodigo () );
		iRes = BOOL_VAL_FALSO;
	}
	ErrLimpiar ();
	if ( MplLeerRealDoble ( NULL ) != 0.0 )
	{
		printf( "Error caso 5: leer un real de un origen nulo deberia devolver 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	ErrLimpiar ();
	return ( iRes );
}



static int TestMplTiposC01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test MplTiposC 01:\n" );
	byte byBuf[ 8 ];

	const byte byShort[] = { 0xC7, 0xCF };
	if ( ( MplEscribirShort ( byBuf, -12345 ) != MPL_TAM_SHORT ) || ( BytesSon ( byBuf, byShort, 2 ) == BOOL_VAL_FALSO ) ||
		 ( MplLeerShort ( byBuf ) != -12345 ) )
	{
		printf( "Error caso 1: short -12345 deberia ocupar C7 CF y volver igual\n" );
		iRes = BOOL_VAL_FALSO;
	}
	const byte byUShort[] = { 0xFF, 0xFF };
	if ( ( MplEscribirUShort ( byBuf, USHRT_MAX ) != 2 ) || ( BytesSon ( byBuf, byUShort, 2 ) == BOOL_VAL_FALSO ) ||
		 ( MplLeerUShort ( byBuf ) != USHRT_MAX ) )
	{
		printf( "Error caso 2: USHRT_MAX deberia ocupar FF FF y volver igual\n" );
		iRes = BOOL_VAL_FALSO;
	}
	const byte byInt[] = { 0x00, 0x00, 0x00, 0x80 };
	if ( ( MplEscribirInt ( byBuf, INT_MIN ) != MPL_TAM_INT ) || ( BytesSon ( byBuf, byInt, 4 ) == BOOL_VAL_FALSO ) ||
		 ( MplLeerInt ( byBuf ) != INT_MIN ) )
	{
		printf( "Error caso 3: INT_MIN deberia ocupar 00 00 00 80 y volver igual\n" );
		iRes = BOOL_VAL_FALSO;
	}
	const byte byUInt[] = { 0x78, 0x56, 0x34, 0x12 };
	if ( ( MplEscribirUInt ( byBuf, 0x12345678U ) != 4 ) || ( BytesSon ( byBuf, byUInt, 4 ) == BOOL_VAL_FALSO ) ||
		 ( MplLeerUInt ( byBuf ) != 0x12345678U ) )
	{
		printf( "Error caso 4: 0x12345678 deberia ocupar 78 56 34 12 y volver igual\n" );
		iRes = BOOL_VAL_FALSO;
	}
	const byte byLLong[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80 };
	if ( ( MplEscribirLLong ( byBuf, LLONG_MIN ) != MPL_TAM_LLONG ) || ( BytesSon ( byBuf, byLLong, 8 ) == BOOL_VAL_FALSO ) ||
		 ( MplLeerLLong ( byBuf ) != LLONG_MIN ) )
	{
		printf( "Error caso 5: LLONG_MIN deberia ocupar 00 x 7 80 y volver igual\n" );
		iRes = BOOL_VAL_FALSO;
	}
	const byte byULLong[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
	if ( ( MplEscribirULLong ( byBuf, ULLONG_MAX ) != 8 ) || ( BytesSon ( byBuf, byULLong, 8 ) == BOOL_VAL_FALSO ) ||
		 ( MplLeerULLong ( byBuf ) != ULLONG_MAX ) )
	{
		printf( "Error caso 6: ULLONG_MAX deberia ocupar FF x 8 y volver igual\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

/* Con long de 4 bytes, comparar un long con 2^32 da siempre falso y el
   compilador avisa; como parametro long long no. */
static int EsDosA32 ( long long llValor )
{
	return ( llValor == 4294967296LL );
}

static int TestMplLong01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test MplLong 01:\n" );
	byte byBuf[ 8 ];

	/* Los mismos 8 bytes en Windows (long de 4) que en Cygwin (long de 8). */
	const byte byMenosDos[] = { 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
	if ( ( MplEscribirLong ( byBuf, -2L ) != MPL_TAM_LONG ) || ( BytesSon ( byBuf, byMenosDos, 8 ) == BOOL_VAL_FALSO ) )
	{
		printf( "Error caso 1: -2L deberia ocupar FE FF FF FF FF FF FF FF\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* 4000000000 = 0xEE6B2800, cabe en un unsigned long de 4 bytes. */
	const byte byCuatroMil[] = { 0x00, 0x28, 0x6B, 0xEE, 0x00, 0x00, 0x00, 0x00 };
	if ( ( MplEscribirULong ( byBuf, 4000000000UL ) != 8 ) || ( BytesSon ( byBuf, byCuatroMil, 8 ) == BOOL_VAL_FALSO ) ||
		 ( MplLeerULong ( byBuf ) != 4000000000UL ) )
	{
		printf( "Error caso 2: 4000000000 deberia ocupar 00 28 6B EE 00 00 00 00 y volver igual\n" );
		iRes = BOOL_VAL_FALSO;
	}

	/* Ida y vuelta en los extremos de esta maquina. */
	MplEscribirLong ( byBuf, LONG_MIN );
	if ( MplLeerLong ( byBuf ) != LONG_MIN )
	{
		printf( "Error caso 3: ida y vuelta de LONG_MIN\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MplEscribirLong ( byBuf, LONG_MAX );
	if ( MplLeerLong ( byBuf ) != LONG_MAX )
	{
		printf( "Error caso 4: ida y vuelta de LONG_MAX\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MplEscribirULong ( byBuf, ULONG_MAX );
	if ( MplLeerULong ( byBuf ) != ULONG_MAX )
	{
		printf( "Error caso 5: ida y vuelta de ULONG_MAX\n" );
		iRes = BOOL_VAL_FALSO;
	}

	/* 2^32, escrito en una maquina con long de 8: en una de 4 no cabe. */
	const byte byDosA32[] = { 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00 };
	ErrLimpiar ();
	long lLeido = MplLeerLong ( byDosA32 );
	unsigned long ulLeido = MplLeerULong ( byDosA32 );
	if ( sizeof ( long ) == MPL_TAM_LONG )
	{
		if ( ( EsDosA32 ( lLeido ) == BOOL_VAL_FALSO ) || ( EsDosA32 ( (long long) ulLeido ) == BOOL_VAL_FALSO ) || ( ErrHayError () == 1 ) )
		{
			printf( "Error caso 6: con long de 8 bytes, 2^32 deberia leerse sin error\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		if ( ( lLeido != 0 ) || ( ulLeido != 0 ) || ( ErrCodigo () != ERR_CONVERSION_IMPOSIBLE ) )
		{
			printf( "Error caso 7: con long de 4 bytes, 2^32 deberia dar 0 y ERR_CONVERSION_IMPOSIBLE: %d\n", ErrCodigo () );
			iRes = BOOL_VAL_FALSO;
		}
	}

	/* INT64_MIN: en una de 4 tampoco cabe, por abajo. */
	const byte byMinimo[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80 };
	ErrLimpiar ();
	lLeido = MplLeerLong ( byMinimo );
	if ( sizeof ( long ) == MPL_TAM_LONG )
	{
		if ( ( lLeido != LONG_MIN ) || ( ErrHayError () == 1 ) )
		{
			printf( "Error caso 8: con long de 8 bytes deberia leerse LONG_MIN\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		if ( ( lLeido != 0 ) || ( ErrCodigo () != ERR_CONVERSION_IMPOSIBLE ) )
		{
			printf( "Error caso 9: con long de 4 bytes, INT64_MIN deberia dar 0 y ERR_CONVERSION_IMPOSIBLE\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}

	/* Un origen nulo da su propio error, no el de conversion. */
	ErrLimpiar ();
	if ( ( MplLeerLong ( NULL ) != 0 ) || ( ErrCodigo () != ERR_MEMORIA_INVALIDA ) )
	{
		printf( "Error caso 10: un origen nulo deberia dar 0 y ERR_MEMORIA_INVALIDA: %d\n", ErrCodigo () );
		iRes = BOOL_VAL_FALSO;
	}
	ErrLimpiar ();
	return ( iRes );
}

static int TestMplCabeLong01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test MplCabeLong 01:\n" );

	const byte byDosA32[] = { 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00 };
	const byte byMenosDos[] = { 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
	const byte byUIntMax[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00 };
	int iCabeEsperado = ( sizeof ( long ) == 8 ) ? 1 : 0;

	ErrLimpiar ();
	if ( ( MplCabeLong ( byDosA32 ) != iCabeEsperado ) || ( MplCabeULong ( byDosA32 ) != iCabeEsperado ) )
	{
		printf( "Error caso 1: 2^32 deberia caber solo con long de 8 bytes: %d %d\n", MplCabeLong ( byDosA32 ), MplCabeULong ( byDosA32 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ErrHayError () == 1 )
	{
		printf( "Error caso 2: preguntar si cabe no deberia anotar error: %d\n", ErrCodigo () );
		iRes = BOOL_VAL_FALSO;
	}
	/* -2 cabe siempre como long; como unsigned long es 2^64 - 2, que no cabe en 4 bytes. */
	if ( ( MplCabeLong ( byMenosDos ) != 1 ) || ( MplCabeULong ( byMenosDos ) != iCabeEsperado ) )
	{
		printf( "Error caso 3: FE FF x 7: long siempre, unsigned long solo con 8 bytes\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* UINT_MAX cabe en un unsigned long de 4, pero no en un long de 4. */
	if ( ( MplCabeULong ( byUIntMax ) != 1 ) || ( MplCabeLong ( byUIntMax ) != iCabeEsperado ) )
	{
		printf( "Error caso 4: FF FF FF FF 00 x 4: unsigned long siempre, long solo con 8 bytes\n" );
		iRes = BOOL_VAL_FALSO;
	}
	ErrLimpiar ();
	return ( iRes );
}

static int TestMplTam01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test MplTam 01:\n" );

	if ( MplTamShort () != 2 )
	{
		printf( "Error caso 1: MplTamShort deberia ser 2: %d\n", MplTamShort () );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MplTamUShort () != 2 )
	{
		printf( "Error caso 2: MplTamUShort deberia ser 2: %d\n", MplTamUShort () );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MplTamInt () != 4 )
	{
		printf( "Error caso 3: MplTamInt deberia ser 4: %d\n", MplTamInt () );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MplTamUInt () != 4 )
	{
		printf( "Error caso 4: MplTamUInt deberia ser 4: %d\n", MplTamUInt () );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MplTamLong () != 8 )
	{
		printf( "Error caso 5: MplTamLong deberia ser 8: %d\n", MplTamLong () );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MplTamULong () != 8 )
	{
		printf( "Error caso 6: MplTamULong deberia ser 8: %d\n", MplTamULong () );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MplTamLLong () != 8 )
	{
		printf( "Error caso 7: MplTamLLong deberia ser 8: %d\n", MplTamLLong () );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MplTamULLong () != 8 )
	{
		printf( "Error caso 8: MplTamULLong deberia ser 8: %d\n", MplTamULLong () );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MplTamReal () != 4 )
	{
		printf( "Error caso 9: MplTamReal deberia ser 4: %d\n", MplTamReal () );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MplTamRealDoble () != 8 )
	{
		printf( "Error caso 10: MplTamRealDoble deberia ser 8: %d\n", MplTamRealDoble () );
		iRes = BOOL_VAL_FALSO;
	}

	/* Lo que dicen es lo que ocupa de verdad lo escrito. */
	byte byBuf[ 8 ];
	if ( MplEscribirLong ( byBuf, 1L ) != MplTamLong () )
	{
		printf( "Error caso 11: MplEscribirLong deberia escribir MplTamLong bytes\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MplEscribirInt ( byBuf, 1 ) != MplTamInt () )
	{
		printf( "Error caso 12: MplEscribirInt deberia escribir MplTamInt bytes\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MplEscribirRealDoble ( byBuf, 1.0 ) != MplTamRealDoble () )
	{
		printf( "Error caso 13: MplEscribirRealDoble deberia escribir MplTamRealDoble bytes\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



int TestTiposMultiPlataforma ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test TiposMultiPlataforma]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestMplEscribirEnteros01 () == BOOL_VAL_CIERTO ) &&
			( TestMplLeerEnteros01 () == BOOL_VAL_CIERTO ) &&
			( TestMplReales01 () == BOOL_VAL_CIERTO ) &&
			( TestMplNulos01 () == BOOL_VAL_CIERTO ) &&
			( TestMplTiposC01 () == BOOL_VAL_CIERTO ) &&
			( TestMplLong01 () == BOOL_VAL_CIERTO ) &&
			( TestMplTam01 () == BOOL_VAL_CIERTO ) &&
			( TestMplCabeLong01 () == BOOL_VAL_CIERTO ) )
	{
		printf ( "%sResultado: OK%s\n", ANSI_VERDE, ANSI_RESETEAR );
	}
	else
	{
		printf ( "%sResultado: KO%s\n", ANSI_ROJO, ANSI_RESETEAR );
		iRes = BOOL_VAL_FALSO;
	}
	printf ( "%s[Fin]%s\n", ANSI_AMARILLO, ANSI_RESETEAR );
	return ( iRes );
}
