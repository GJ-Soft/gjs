#include "Base.h"

#include "Word.h"



static int TestWordByteInferior01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test WordByteInferior 01:\n" );
	byte byVal = WordByteInferior ( 0xABCD );
	if ( byVal != 0xCD )
	{
		printf( "Error caso 1: se esperaba 0xCD: 0x%02X\n", byVal );
		iRes = BOOL_VAL_FALSO;
	}
	byVal = WordByteInferior ( 0x0000 );
	if ( byVal != 0x00 )
	{
		printf( "Error caso 2: se esperaba 0x00: 0x%02X\n", byVal );
		iRes = BOOL_VAL_FALSO;
	}
	byVal = WordByteInferior ( 0xFFFF );
	if ( byVal != 0xFF )
	{
		printf( "Error caso 3: se esperaba 0xFF: 0x%02X\n", byVal );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestWordByteSuperior01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test WordByteSuperior 01:\n" );
	byte byVal = WordByteSuperior ( 0xABCD );
	if ( byVal != 0xAB )
	{
		printf( "Error caso 1: se esperaba 0xAB: 0x%02X\n", byVal );
		iRes = BOOL_VAL_FALSO;
	}
	byVal = WordByteSuperior ( 0x0000 );
	if ( byVal != 0x00 )
	{
		printf( "Error caso 2: se esperaba 0x00: 0x%02X\n", byVal );
		iRes = BOOL_VAL_FALSO;
	}
	byVal = WordByteSuperior ( 0xFFFF );
	if ( byVal != 0xFF )
	{
		printf( "Error caso 3: se esperaba 0xFF: 0x%02X\n", byVal );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestWordComponer01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test WordComponer 01:\n" );
	word wVal = WordComponer ( 0xAB, 0xCD );
	if ( wVal != 0xABCD )
	{
		printf( "Error caso 1: se esperaba 0xABCD: 0x%04X\n", wVal );
		iRes = BOOL_VAL_FALSO;
	}
	wVal = WordComponer ( 0x00, 0x00 );
	if ( wVal != 0x0000 )
	{
		printf( "Error caso 2: se esperaba 0x0000: 0x%04X\n", wVal );
		iRes = BOOL_VAL_FALSO;
	}
	wVal = WordComponer ( 0xFF, 0xFF );
	if ( wVal != 0xFFFF )
	{
		printf( "Error caso 3: se esperaba 0xFFFF: 0x%04X\n", wVal );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



int TestWord ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test Word]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestWordByteInferior01 () == BOOL_VAL_CIERTO ) &&
			( TestWordByteSuperior01 () == BOOL_VAL_CIERTO ) &&
			( TestWordComponer01 () == BOOL_VAL_CIERTO ) )
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
