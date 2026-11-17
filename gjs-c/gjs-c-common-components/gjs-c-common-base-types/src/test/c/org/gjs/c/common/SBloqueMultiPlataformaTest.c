#include "Base.h"

#include "SBloqueMultiPlataforma.h"



/* Compara los iTam bytes del bloque desde iPos con los esperados. */
static int BytesSon ( SBloqueMultiPlataforma * p_blqObj, int iPos, const byte * p_byEsperados, int iTam )
{
	int iRes = BOOL_VAL_CIERTO;
	for ( int i = 0; i < iTam; i = i + 1 )
	{
		byte byLeido = SBlqMplLeerByte ( p_blqObj, iPos + i );
		if ( byLeido != p_byEsperados[ i ] )
		{
			printf( "  byte %d: se esperaba 0x%02X: 0x%02X\n", iPos + i, p_byEsperados[ i ], byLeido );
			iRes = BOOL_VAL_FALSO;
		}
	}
	return ( iRes );
}

static int TestSBlqMplCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SBlqMplCrear 01:\n" );

	/* Los mismos tamanos en todas las plataformas: el long tambien mide 8. */
	SBloqueMultiPlataforma * p_blqEnt = SBlqMplCrearEntero ();
	SBloqueMultiPlataforma * p_blqLar = SBlqMplCrearEnteroLargo ();
	SBloqueMultiPlataforma * p_blqSin = SBlqMplCrearEnteroSinSigno ();
	SBloqueMultiPlataforma * p_blqLarSin = SBlqMplCrearEnteroLargoSinSigno ();
	SBloqueMultiPlataforma * p_blqRea = SBlqMplCrearReal ();
	SBloqueMultiPlataforma * p_blqDob = SBlqMplCrearRealDoble ();
	if ( ( SBlqMplTam ( p_blqEnt ) != 4 ) || ( SBlqMplTam ( p_blqLar ) != 8 ) || ( SBlqMplTam ( p_blqSin ) != 4 ) ||
		 ( SBlqMplTam ( p_blqLarSin ) != 8 ) || ( SBlqMplTam ( p_blqRea ) != 4 ) || ( SBlqMplTam ( p_blqDob ) != 8 ) )
	{
		printf( "Error caso 1: se esperaban tamanos 4 8 4 8 4 8: %d %d %d %d %d %d\n", SBlqMplTam ( p_blqEnt ), SBlqMplTam ( p_blqLar ),
				SBlqMplTam ( p_blqSin ), SBlqMplTam ( p_blqLarSin ), SBlqMplTam ( p_blqRea ), SBlqMplTam ( p_blqDob ) );
		iRes = BOOL_VAL_FALSO;
	}
	SBlqMplDestruir ( &p_blqEnt );
	SBlqMplDestruir ( &p_blqLar );
	SBlqMplDestruir ( &p_blqSin );
	SBlqMplDestruir ( &p_blqLarSin );
	SBlqMplDestruir ( &p_blqRea );
	SBlqMplDestruir ( &p_blqDob );
	if ( ES_VALIDO ( p_blqEnt ) )
	{
		printf( "Error caso 2: destruir deberia dejar el puntero a NULL\n" );
		iRes = BOOL_VAL_FALSO;
	}

	/* La cadena: el bloque justo, con el nulo. */
	SBloqueMultiPlataforma * p_blqCad = SBlqMplCrearCadena ( "gjs" );
	const byte byCad[] = { 'g', 'j', 's', 0x00 };
	if ( ( SBlqMplTam ( p_blqCad ) != 4 ) || ( BytesSon ( p_blqCad, 0, byCad, 4 ) == BOOL_VAL_FALSO ) )
	{
		printf( "Error caso 3: \"gjs\" deberia ocupar 4 bytes con el nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	char * p_cLeida = SBlqMplCadena ( p_blqCad );
	if ( CadComparar ( p_cLeida, "gjs" ) != COMP_IGUAL )
	{
		printf( "Error caso 4: se esperaba \"gjs\": %s\n", ES_VALIDO ( p_cLeida ) ? p_cLeida : "(nulo)" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberarCadena ( &p_cLeida );
	if ( SBlqMplEscribirCadena ( p_blqCad, "abcd" ) != 0 )
	{
		printf( "Error caso 5: \"abcd\" con su nulo no cabe en 4 bytes\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SBlqMplEscribirCadena ( p_blqCad, "xy" ) != 1 )
	{
		printf( "Error caso 6: \"xy\" deberia caber\n" );
		iRes = BOOL_VAL_FALSO;
	}
	p_cLeida = SBlqMplCadena ( p_blqCad );
	if ( CadComparar ( p_cLeida, "xy" ) != COMP_IGUAL )
	{
		printf( "Error caso 7: se esperaba \"xy\"\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberarCadena ( &p_cLeida );
	SBlqMplDestruir ( &p_blqCad );

	p_blqCad = SBlqMplCrearCadena ( "" );
	if ( SBlqMplTam ( p_blqCad ) != 1 )
	{
		printf( "Error caso 8: la cadena vacia deberia ocupar 1 byte\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SBlqMplDestruir ( &p_blqCad );
	if ( ES_VALIDO ( SBlqMplCrearCadena ( NULL ) ) )
	{
		printf( "Error caso 9: una cadena nula deberia dar NULL\n" );
		iRes = BOOL_VAL_FALSO;
	}
	ErrLimpiar ();
	return ( iRes );
}

static int TestSBlqMplValor01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SBlqMplValor 01:\n" );

	SBloqueMultiPlataforma * p_blqLar = SBlqMplCrearEnteroLargo ();
	const byte byMenosDos[] = { 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
	if ( ( SBlqMplEscribirEnteroLargo ( p_blqLar, -2L ) != 1 ) || ( BytesSon ( p_blqLar, 0, byMenosDos, 8 ) == BOOL_VAL_FALSO ) ||
		 ( SBlqMplEnteroLargo ( p_blqLar ) != -2L ) )
	{
		printf( "Error caso 1: -2L deberia ocupar FE FF FF FF FF FF FF FF y volver igual\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Un bloque de otro tamano no vale para otro tipo. */
	if ( SBlqMplEscribirEntero ( p_blqLar, 5 ) != 0 )
	{
		printf( "Error caso 2: escribir un int en un bloque de 8 deberia fallar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	ErrLimpiar ();
	if ( ( SBlqMplEntero ( p_blqLar ) != 0 ) || ( ErrCodigo () != ERR_LECTURA_MEMORIA ) )
	{
		printf( "Error caso 3: leer un int de un bloque de 8 deberia dar 0 y ERR_LECTURA_MEMORIA\n" );
		iRes = BOOL_VAL_FALSO;
	}
	ErrLimpiar ();
	SBlqMplDestruir ( &p_blqLar );

	SBloqueMultiPlataforma * p_blqObj = SBlqMplCrearEntero ();
	const byte byInt[] = { 0x00, 0x00, 0x00, 0x80 };
	if ( ( SBlqMplEscribirEntero ( p_blqObj, INT_MIN ) != 1 ) || ( BytesSon ( p_blqObj, 0, byInt, 4 ) == BOOL_VAL_FALSO ) ||
		 ( SBlqMplEntero ( p_blqObj ) != INT_MIN ) )
	{
		printf( "Error caso 4: INT_MIN deberia ocupar 00 00 00 80 y volver igual\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SBlqMplDestruir ( &p_blqObj );

	p_blqObj = SBlqMplCrearEnteroSinSigno ();
	const byte byUInt[] = { 0x78, 0x56, 0x34, 0x12 };
	if ( ( SBlqMplEscribirEnteroSinSigno ( p_blqObj, 0x12345678U ) != 1 ) || ( BytesSon ( p_blqObj, 0, byUInt, 4 ) == BOOL_VAL_FALSO ) ||
		 ( SBlqMplEnteroSinSigno ( p_blqObj ) != 0x12345678U ) )
	{
		printf( "Error caso 5: 0x12345678 deberia ocupar 78 56 34 12 y volver igual\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SBlqMplDestruir ( &p_blqObj );

	/* 4000000000 = 0xEE6B2800 */
	p_blqObj = SBlqMplCrearEnteroLargoSinSigno ();
	const byte byULong[] = { 0x00, 0x28, 0x6B, 0xEE, 0x00, 0x00, 0x00, 0x00 };
	if ( ( SBlqMplEscribirEnteroLargoSinSigno ( p_blqObj, 4000000000UL ) != 1 ) || ( BytesSon ( p_blqObj, 0, byULong, 8 ) == BOOL_VAL_FALSO ) ||
		 ( SBlqMplEnteroLargoSinSigno ( p_blqObj ) != 4000000000UL ) )
	{
		printf( "Error caso 6: 4000000000 deberia ocupar 00 28 6B EE 00 00 00 00 y volver igual\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SBlqMplDestruir ( &p_blqObj );

	/* 1.0f = 0x3F800000 */
	p_blqObj = SBlqMplCrearReal ();
	const byte byReal[] = { 0x00, 0x00, 0x80, 0x3F };
	if ( ( SBlqMplEscribirReal ( p_blqObj, 1.0f ) != 1 ) || ( BytesSon ( p_blqObj, 0, byReal, 4 ) == BOOL_VAL_FALSO ) ||
		 ( SBlqMplReal ( p_blqObj ) != 1.0f ) )
	{
		printf( "Error caso 7: 1.0f deberia ocupar 00 00 80 3F y volver igual\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SBlqMplDestruir ( &p_blqObj );

	/* -2.5 = 0xC004000000000000 */
	p_blqObj = SBlqMplCrearRealDoble ();
	const byte byDoble[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0xC0 };
	if ( ( SBlqMplEscribirRealDoble ( p_blqObj, -2.5 ) != 1 ) || ( BytesSon ( p_blqObj, 0, byDoble, 8 ) == BOOL_VAL_FALSO ) ||
		 ( SBlqMplRealDoble ( p_blqObj ) != -2.5 ) )
	{
		printf( "Error caso 8: -2.5 deberia ocupar 00 00 00 00 00 00 04 C0 y volver igual\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SBlqMplDestruir ( &p_blqObj );

	if ( ( SBlqMplEscribirEntero ( NULL, 1 ) != 0 ) || ( SBlqMplEntero ( NULL ) != 0 ) )
	{
		printf( "Error caso 9: un bloque nulo deberia dar 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	ErrLimpiar ();
	return ( iRes );
}

static int TestSBlqMplEnPos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SBlqMplEnPos 01:\n" );

	/* Posiciones sin alinear: int en 1, long en 5, unsigned int en 13,
	   unsigned long en 17, float en 25 y double en 29: 37 bytes. */
	SBloqueMultiPlataforma * p_blqObj = SBlqMplCrear ( 37 );
	if ( ( SBlqMplEscribirEnteroEnPos ( p_blqObj, 1, -12345 ) != 1 ) ||
		 ( SBlqMplEscribirEnteroLargoEnPos ( p_blqObj, 5, LONG_MIN ) != 1 ) ||
		 ( SBlqMplEscribirEnteroSinSignoEnPos ( p_blqObj, 13, UINT_MAX ) != 1 ) ||
		 ( SBlqMplEscribirEnteroLargoSinSignoEnPos ( p_blqObj, 17, ULONG_MAX ) != 1 ) ||
		 ( SBlqMplEscribirRealEnPos ( p_blqObj, 25, -1.5f ) != 1 ) ||
		 ( SBlqMplEscribirRealDobleEnPos ( p_blqObj, 29, 0.1 ) != 1 ) )
	{
		printf( "Error caso 1: todas las escrituras deberian caber\n" );
		iRes = BOOL_VAL_FALSO;
	}
	const byte byInt[] = { 0xC7, 0xCF, 0xFF, 0xFF };
	if ( BytesSon ( p_blqObj, 1, byInt, 4 ) == BOOL_VAL_FALSO )
	{
		printf( "Error caso 2: -12345 deberia ocupar C7 CF FF FF\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* 0.1 = 0x3FB999999999999A */
	const byte byDoble[] = { 0x9A, 0x99, 0x99, 0x99, 0x99, 0x99, 0xB9, 0x3F };
	if ( BytesSon ( p_blqObj, 29, byDoble, 8 ) == BOOL_VAL_FALSO )
	{
		printf( "Error caso 3: 0.1 deberia ocupar 9A 99 99 99 99 99 B9 3F\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SBlqMplLeerEnteroEnPos ( p_blqObj, 1 ) != -12345 ) ||
		 ( SBlqMplLeerEnteroLargoEnPos ( p_blqObj, 5 ) != LONG_MIN ) ||
		 ( SBlqMplLeerEnteroSinSignoEnPos ( p_blqObj, 13 ) != UINT_MAX ) ||
		 ( SBlqMplLeerEnteroLargoSinSignoEnPos ( p_blqObj, 17 ) != ULONG_MAX ) ||
		 ( SBlqMplLeerRealEnPos ( p_blqObj, 25 ) != -1.5f ) ||
		 ( SBlqMplLeerRealDobleEnPos ( p_blqObj, 29 ) != 0.1 ) )
	{
		printf( "Error caso 4: los valores leidos no coinciden con los escritos\n" );
		iRes = BOOL_VAL_FALSO;
	}

	/* Un 0 leido de verdad no es un error. */
	SBlqMplEscribirEnteroEnPos ( p_blqObj, 33, 0 );
	ErrLimpiar ();
	if ( ( SBlqMplLeerEnteroEnPos ( p_blqObj, 33 ) != 0 ) || ( ErrHayError () == 1 ) )
	{
		printf( "Error caso 5: leer un 0 no deberia anotar error\n" );
		iRes = BOOL_VAL_FALSO;
	}

	/* El ultimo que cabe y el primero que no. */
	if ( SBlqMplEscribirRealDobleEnPos ( p_blqObj, 29, 1.0 ) != 1 )
	{
		printf( "Error caso 6: un double en 29 de 37 deberia caber justo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SBlqMplEscribirRealDobleEnPos ( p_blqObj, 30, 1.0 ) != 0 )
	{
		printf( "Error caso 7: un double en 30 de 37 no deberia caber\n" );
		iRes = BOOL_VAL_FALSO;
	}
	ErrLimpiar ();
	if ( ( SBlqMplLeerEnteroLargoEnPos ( p_blqObj, 30 ) != 0 ) || ( ErrCodigo () != ERR_LECTURA_MEMORIA ) )
	{
		printf( "Error caso 8: leer un long en 30 de 37 deberia dar 0 y ERR_LECTURA_MEMORIA\n" );
		iRes = BOOL_VAL_FALSO;
	}
	ErrLimpiar ();
	if ( ( SBlqMplEscribirEnteroEnPos ( p_blqObj, -1, 7 ) != 0 ) || ( SBlqMplLeerEnteroEnPos ( p_blqObj, -1 ) != 0 ) )
	{
		printf( "Error caso 9: una posicion negativa deberia fallar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SBlqMplEscribirEnteroEnPos ( p_blqObj, INT_MAX, 7 ) != 0 )
	{
		printf( "Error caso 10: la posicion INT_MAX deberia fallar sin desbordar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	ErrLimpiar ();
	SBlqMplDestruir ( &p_blqObj );
	return ( iRes );
}

static int TestSBlqMplSecuencial01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SBlqMplSecuencial 01:\n" );

	/* int 4 + long 8 + float 4 + "gjs" 4 + double 8 + unsigned int 4 + unsigned long 8 = 40 */
	SBloqueMultiPlataforma * p_blqObj = SBlqMplCrear ( 40 );
	int iPos = 0;
	const int iPosiciones[] = { 4, 12, 16, 20, 28, 32, 40 };
	int iEsc[ 7 ];
	iEsc[ 0 ] = SBlqMplEscribirEnteroEnPosExt ( p_blqObj, &iPos, 42 );
	int iTras0 = iPos;
	iEsc[ 1 ] = SBlqMplEscribirEnteroLargoEnPosExt ( p_blqObj, &iPos, -7L );
	int iTras1 = iPos;
	iEsc[ 2 ] = SBlqMplEscribirRealEnPosExt ( p_blqObj, &iPos, 2.5f );
	int iTras2 = iPos;
	iEsc[ 3 ] = SBlqMplEscribirCadenaEnPosExt ( p_blqObj, &iPos, "gjs" );
	int iTras3 = iPos;
	iEsc[ 4 ] = SBlqMplEscribirRealDobleEnPosExt ( p_blqObj, &iPos, -0.25 );
	int iTras4 = iPos;
	iEsc[ 5 ] = SBlqMplEscribirEnteroSinSignoEnPosExt ( p_blqObj, &iPos, 3000000000U );
	int iTras5 = iPos;
	iEsc[ 6 ] = SBlqMplEscribirEnteroLargoSinSignoEnPosExt ( p_blqObj, &iPos, 4000000000UL );
	int iTras[] = { iTras0, iTras1, iTras2, iTras3, iTras4, iTras5, iPos };
	for ( int i = 0; i < 7; i = i + 1 )
	{
		if ( ( iEsc[ i ] != 1 ) || ( iTras[ i ] != iPosiciones[ i ] ) )
		{
			printf( "Error caso 1: escritura %d: se esperaba 1 y posicion %d: %d y %d\n", i, iPosiciones[ i ], iEsc[ i ], iTras[ i ] );
			iRes = BOOL_VAL_FALSO;
		}
	}
	/* Lleno: no cabe nada mas y la posicion no se mueve. */
	if ( ( SBlqMplEscribirEnteroEnPosExt ( p_blqObj, &iPos, 1 ) != 0 ) || ( iPos != 40 ) )
	{
		printf( "Error caso 2: con el bloque lleno deberia fallar sin mover la posicion: %d\n", iPos );
		iRes = BOOL_VAL_FALSO;
	}

	iPos = 0;
	int iLeido = SBlqMplLeerEnteroEnPosExt ( p_blqObj, &iPos );
	long lLeido = SBlqMplLeerEnteroLargoEnPosExt ( p_blqObj, &iPos );
	float fLeido = SBlqMplLeerRealEnPosExt ( p_blqObj, &iPos );
	char * p_cLeida = SBlqMplLeerCadenaEnPosExt ( p_blqObj, &iPos );
	double dLeido = SBlqMplLeerRealDobleEnPosExt ( p_blqObj, &iPos );
	unsigned int uiLeido = SBlqMplLeerEnteroSinSignoEnPosExt ( p_blqObj, &iPos );
	unsigned long ulLeido = SBlqMplLeerEnteroLargoSinSignoEnPosExt ( p_blqObj, &iPos );
	if ( ( iLeido != 42 ) || ( lLeido != -7L ) || ( fLeido != 2.5f ) || ( CadComparar ( p_cLeida, "gjs" ) != COMP_IGUAL ) ||
		 ( dLeido != -0.25 ) || ( uiLeido != 3000000000U ) || ( ulLeido != 4000000000UL ) || ( iPos != 40 ) )
	{
		printf( "Error caso 3: la lectura secuencial no devuelve lo escrito (posicion final %d)\n", iPos );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberarCadena ( &p_cLeida );

	/* Al final: falla, no se mueve y anota el error. */
	ErrLimpiar ();
	if ( ( SBlqMplLeerEnteroEnPosExt ( p_blqObj, &iPos ) != 0 ) || ( iPos != 40 ) || ( ErrCodigo () != ERR_LECTURA_MEMORIA ) )
	{
		printf( "Error caso 4: leer al final deberia fallar sin mover la posicion\n" );
		iRes = BOOL_VAL_FALSO;
	}
	ErrLimpiar ();
	if ( ( SBlqMplLeerEnteroEnPosExt ( p_blqObj, NULL ) != 0 ) || ( SBlqMplEscribirEnteroEnPosExt ( p_blqObj, NULL, 1 ) != 0 ) )
	{
		printf( "Error caso 5: sin posicion deberia fallar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	ErrLimpiar ();
	SBlqMplDestruir ( &p_blqObj );
	return ( iRes );
}

/* Con long de 4 bytes, comparar un long con 2^32 da siempre falso y el
   compilador avisa; como parametro long long no. */
static int EsDosA32 ( long long llValor )
{
	return ( llValor == 4294967296LL );
}

static int TestSBlqMplLong01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SBlqMplLong 01:\n" );

	/* 2^32 seguido de un int 9: lo que escribiria una maquina con long de 8. */
	byte byDatos[] = { 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00 };
	SBloqueMultiPlataforma * p_blqObj = SBlqMplCrear ( 12 );
	SBlqMplEscribirBuffer ( p_blqObj, 0, byDatos, 12 );
	int iPos = 0;
	ErrLimpiar ();
	long lLeido = SBlqMplLeerEnteroLargoEnPosExt ( p_blqObj, &iPos );
	if ( sizeof ( long ) == 8 )
	{
		if ( ( EsDosA32 ( lLeido ) == BOOL_VAL_FALSO ) || ( ErrHayError () == 1 ) )
		{
			printf( "Error caso 1: con long de 8 bytes, 2^32 deberia leerse sin error\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		if ( ( lLeido != 0 ) || ( ErrCodigo () != ERR_CONVERSION_IMPOSIBLE ) )
		{
			printf( "Error caso 2: con long de 4 bytes, 2^32 deberia dar 0 y ERR_CONVERSION_IMPOSIBLE: %d\n", ErrCodigo () );
			iRes = BOOL_VAL_FALSO;
		}
	}
	/* Si no cabe falla como cualquier lectura: la posicion no se mueve. */
	int iPosEsperada = ( sizeof ( long ) == 8 ) ? 8 : 0;
	if ( iPos != iPosEsperada )
	{
		printf( "Error caso 3: tras el long la posicion deberia ser %d: %d\n", iPosEsperada, iPos );
		iRes = BOOL_VAL_FALSO;
	}

	/* Lo mismo sin signo. */
	iPos = 0;
	ErrLimpiar ();
	unsigned long ulLeido = SBlqMplLeerEnteroLargoSinSignoEnPosExt ( p_blqObj, &iPos );
	if ( sizeof ( unsigned long ) == 8 )
	{
		if ( ( EsDosA32 ( (long long) ulLeido ) == BOOL_VAL_FALSO ) || ( iPos != 8 ) || ( ErrHayError () == 1 ) )
		{
			printf( "Error caso 4: con unsigned long de 8 bytes, 2^32 deberia leerse y avanzar a 8\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		if ( ( ulLeido != 0 ) || ( iPos != 0 ) || ( ErrCodigo () != ERR_CONVERSION_IMPOSIBLE ) )
		{
			printf( "Error caso 5: con unsigned long de 4 bytes, 2^32 deberia dar 0, ERR_CONVERSION_IMPOSIBLE y no avanzar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}

	/* Lo de detras sigue en su sitio. */
	iPos = 8;
	ErrLimpiar ();
	if ( ( SBlqMplLeerEnteroEnPosExt ( p_blqObj, &iPos ) != 9 ) || ( iPos != 12 ) )
	{
		printf( "Error caso 6: en 8 deberia leerse el int 9 y quedar en 12\n" );
		iRes = BOOL_VAL_FALSO;
	}
	ErrLimpiar ();
	SBlqMplDestruir ( &p_blqObj );
	return ( iRes );
}

static int TestSBlqMplOtros01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SBlqMplOtros 01:\n" );

	SBloqueMultiPlataforma * p_blqObj = SBlqMplCrearRealDoble ();
	SBlqMplEscribirRealDoble ( p_blqObj, 3.0 );

	SBloqueMultiPlataforma * p_blqDup = SBlqMplDuplicar ( p_blqObj );
	if ( ( SBlqMplEsIgual ( p_blqObj, p_blqDup ) != 1 ) || ( SBlqMplRealDoble ( p_blqDup ) != 3.0 ) )
	{
		printf( "Error caso 1: el duplicado deberia ser igual\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SBlqMplBloque ( p_blqDup ) == SBlqMplBloque ( p_blqObj ) )
	{
		printf( "Error caso 2: el duplicado deberia tener su propio bloque\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SBlqMplHash ( p_blqObj ) != SBlqHash ( SBlqMplBloque ( p_blqObj ) ) )
	{
		printf( "Error caso 3: el hash deberia ser el del bloque envuelto\n" );
		iRes = BOOL_VAL_FALSO;
	}

	/* Extraer la mitad alta del double: 3.0 = 0x4008000000000000. */
	int iPos = 4;
	SBloqueMultiPlataforma * p_blqTrozo = SBlqMplExtraerExt ( p_blqObj, &iPos, 4 );
	const byte byAlta[] = { 0x00, 0x00, 0x08, 0x40 };
	if ( ( SBlqMplTam ( p_blqTrozo ) != 4 ) || ( iPos != 8 ) || ( BytesSon ( p_blqTrozo, 0, byAlta, 4 ) == BOOL_VAL_FALSO ) )
	{
		printf( "Error caso 4: el trozo deberia ser 00 00 08 40 y la posicion 8: %d\n", iPos );
		iRes = BOOL_VAL_FALSO;
	}
	SBlqMplDestruir ( &p_blqTrozo );

	/* Encapsular: el objeto pasa a ser dueno del bloque. */
	SBloque * p_blqDatos = SBlqCrear ( 4 );
	SBloqueMultiPlataforma * p_blqEnc = SBlqMplEncapsular ( p_blqDatos );
	if ( SBlqMplBloque ( p_blqEnc ) != p_blqDatos )
	{
		printf( "Error caso 5: SBlqMplBloque deberia devolver el bloque encapsulado\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SBlqMplEscribirEnteroSinSigno ( p_blqEnc, 1U ) != 1 )
	{
		printf( "Error caso 6: un bloque de 4 deberia admitir un unsigned int\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SBlqMplDestruir ( &p_blqEnc );

	if ( ES_VALIDO ( SBlqMplEncapsular ( NULL ) ) || ES_VALIDO ( SBlqMplDuplicar ( NULL ) ) || ES_VALIDO ( SBlqMplBloque ( NULL ) ) )
	{
		printf( "Error caso 7: con nulos deberia devolver NULL\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SBlqMplDestruir ( NULL );
	SBlqMplDestruir ( &p_blqDup );
	SBlqMplDestruir ( &p_blqObj );
	ErrLimpiar ();
	return ( iRes );
}



int TestSBloqueMultiPlataforma ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SBloqueMultiPlataforma]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSBlqMplCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSBlqMplValor01 () == BOOL_VAL_CIERTO ) &&
			( TestSBlqMplEnPos01 () == BOOL_VAL_CIERTO ) &&
			( TestSBlqMplSecuencial01 () == BOOL_VAL_CIERTO ) &&
			( TestSBlqMplLong01 () == BOOL_VAL_CIERTO ) &&
			( TestSBlqMplOtros01 () == BOOL_VAL_CIERTO ) )
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
