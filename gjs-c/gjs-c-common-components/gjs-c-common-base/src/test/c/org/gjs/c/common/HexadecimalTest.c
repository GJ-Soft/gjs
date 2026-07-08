#include "Base.h"

#include "Hexadecimal.h"



static int TestHexEsValido01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test HexEsValido 01:\n" );
	if ( HexEsValido ( '0' ) != 1 )
	{
		printf( "Error caso 1: se esperaba valido el '0'\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( HexEsValido ( '9' ) != 1 )
	{
		printf( "Error caso 2: se esperaba valido el '9'\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( HexEsValido ( 'A' ) != 1 )
	{
		printf( "Error caso 3: se esperaba valido el 'A'\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( HexEsValido ( 'f' ) != 1 )
	{
		printf( "Error caso 4: se esperaba valido el 'f'\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( HexEsValido ( 'G' ) != 0 )
	{
		printf( "Error caso 5: no se esperaba valido el 'G'\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( HexEsValido ( ' ' ) != 0 )
	{
		printf( "Error caso 6: no se esperaba valido el espacio\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestHexEsNumValido01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test HexEsNumValido 01:\n" );
	if ( HexEsNumValido ( 0 ) != 1 )
	{
		printf( "Error caso 1: se esperaba valido el 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( HexEsNumValido ( 15 ) != 1 )
	{
		printf( "Error caso 2: se esperaba valido el 15\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( HexEsNumValido ( 16 ) != 0 )
	{
		printf( "Error caso 3: no se esperaba valido el 16\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( HexEsNumValido ( -1 ) != 0 )
	{
		printf( "Error caso 4: no se esperaba valido el -1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestHexValor01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test HexValor 01:\n" );
	if ( HexValor ( '0' ) != 0 )
	{
		printf( "Error caso 1: se esperaba 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( HexValor ( '9' ) != 9 )
	{
		printf( "Error caso 2: se esperaba 9\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( HexValor ( 'A' ) != 10 )
	{
		printf( "Error caso 3: se esperaba 10\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( HexValor ( 'f' ) != 15 )
	{
		printf( "Error caso 4: se esperaba 15\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( HexValor ( 'Z' ) != -1 )
	{
		printf( "Error caso 5: se esperaba -1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestHexDigito01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test HexDigito 01:\n" );
	if ( HexDigito ( 0 ) != '0' )
	{
		printf( "Error caso 1: se esperaba '0'\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( HexDigito ( 9 ) != '9' )
	{
		printf( "Error caso 2: se esperaba '9'\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( HexDigito ( 10 ) != 'A' )
	{
		printf( "Error caso 3: se esperaba 'A'\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( HexDigito ( 15 ) != 'F' )
	{
		printf( "Error caso 4: se esperaba 'F'\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( HexDigito ( 16 ) != (char) 0 )
	{
		printf( "Error caso 5: se esperaba caracter nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( HexDigito ( -1 ) != (char) 0 )
	{
		printf( "Error caso 6: se esperaba caracter nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



int TestHexadecimal ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test Hexadecimal]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestHexEsValido01 () == BOOL_VAL_CIERTO ) &&
			( TestHexEsNumValido01 () == BOOL_VAL_CIERTO ) &&
			( TestHexValor01 () == BOOL_VAL_CIERTO ) &&
			( TestHexDigito01 () == BOOL_VAL_CIERTO ) )
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
