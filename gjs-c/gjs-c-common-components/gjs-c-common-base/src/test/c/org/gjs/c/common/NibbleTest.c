#include "Base.h"

#include "Nibble.h"



static int TestNibValor01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test NibValor 01:\n" );
	unsigned int uiValor = NibValor ( 0x0 );
	if ( uiValor != 0 )
	{
		printf( "Error caso 1: se esperaba 0: %u\n", uiValor );
		iRes = BOOL_VAL_FALSO;
	}
	uiValor = NibValor ( 0x5 );
	if ( uiValor != 5 )
	{
		printf( "Error caso 2: se esperaba 5: %u\n", uiValor );
		iRes = BOOL_VAL_FALSO;
	}
	uiValor = NibValor ( 0xF );
	if ( uiValor != 15 )
	{
		printf( "Error caso 3: se esperaba 15: %u\n", uiValor );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



int TestNibble ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test Nibble]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestNibValor01 () == BOOL_VAL_CIERTO ) )
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
