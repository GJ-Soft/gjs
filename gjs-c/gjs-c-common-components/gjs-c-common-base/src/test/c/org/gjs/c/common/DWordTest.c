#include "Base.h"

#include "DWord.h"



static int TestDWordWordInferior01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test DWordWordInferior 01:\n" );
	word wVal = DWordWordInferior ( 0x12345678 );
	if ( wVal != 0x5678 )
	{
		printf( "Error caso 1: se esperaba 0x5678: 0x%04X\n", wVal );
		iRes = BOOL_VAL_FALSO;
	}
	wVal = DWordWordInferior ( 0x00000000 );
	if ( wVal != 0x0000 )
	{
		printf( "Error caso 2: se esperaba 0x0000: 0x%04X\n", wVal );
		iRes = BOOL_VAL_FALSO;
	}
	wVal = DWordWordInferior ( 0xFFFFFFFF );
	if ( wVal != 0xFFFF )
	{
		printf( "Error caso 3: se esperaba 0xFFFF: 0x%04X\n", wVal );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestDWordWordSuperior01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test DWordWordSuperior 01:\n" );
	word wVal = DWordWordSuperior ( 0x12345678 );
	if ( wVal != 0x1234 )
	{
		printf( "Error caso 1: se esperaba 0x1234: 0x%04X\n", wVal );
		iRes = BOOL_VAL_FALSO;
	}
	wVal = DWordWordSuperior ( 0x00000000 );
	if ( wVal != 0x0000 )
	{
		printf( "Error caso 2: se esperaba 0x0000: 0x%04X\n", wVal );
		iRes = BOOL_VAL_FALSO;
	}
	wVal = DWordWordSuperior ( 0xFFFFFFFF );
	if ( wVal != 0xFFFF )
	{
		printf( "Error caso 3: se esperaba 0xFFFF: 0x%04X\n", wVal );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestDWordComponer01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test DWordComponer 01:\n" );
	/* Se espera que DWordComponer sea la operacion inversa a la descomposicion. */
	dword dwVal = DWordComponer ( 0x1234, 0x5678 );
	if ( dwVal != 0x12345678 )
	{
		printf( "Error caso 1: se esperaba 0x12345678: 0x%08X\n", (unsigned int) dwVal );
		iRes = BOOL_VAL_FALSO;
	}
	dwVal = DWordComponer ( 0x0000, 0x0000 );
	if ( dwVal != 0x00000000 )
	{
		printf( "Error caso 2: se esperaba 0x00000000: 0x%08X\n", (unsigned int) dwVal );
		iRes = BOOL_VAL_FALSO;
	}
	dwVal = DWordComponer ( 0xFFFF, 0xFFFF );
	if ( dwVal != 0xFFFFFFFF )
	{
		printf( "Error caso 3: se esperaba 0xFFFFFFFF: 0x%08X\n", (unsigned int) dwVal );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



int TestDWord ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test DWord]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestDWordWordInferior01 () == BOOL_VAL_CIERTO ) &&
			( TestDWordWordSuperior01 () == BOOL_VAL_CIERTO ) &&
			( TestDWordComponer01 () == BOOL_VAL_CIERTO ) )
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
