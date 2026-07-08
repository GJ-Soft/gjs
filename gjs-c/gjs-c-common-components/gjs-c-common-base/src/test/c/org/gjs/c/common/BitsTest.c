#include "Base.h"

#include "Bits.h"



static int TestByMascaraBitsSuperiores01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test ByMascaraBitsSuperiores 01:\n" );
	byte byMasc = ByMascaraBitsSuperiores ( 4 );
	if ( byMasc != 0xF0 )
	{
		printf( "Error caso 1: se esperaba 0xF0: 0x%02X\n", byMasc );
		iRes = BOOL_VAL_FALSO;
	}
	byMasc = ByMascaraBitsSuperiores ( 1 );
	if ( byMasc != 0xFE )
	{
		printf( "Error caso 2: se esperaba 0xFE: 0x%02X\n", byMasc );
		iRes = BOOL_VAL_FALSO;
	}
	byMasc = ByMascaraBitsSuperiores ( 0 );
	if ( byMasc != 0x00 )
	{
		printf( "Error caso 3: se esperaba 0x00: 0x%02X\n", byMasc );
		iRes = BOOL_VAL_FALSO;
	}
	byMasc = ByMascaraBitsSuperiores ( 8 );
	if ( byMasc != 0x00 )
	{
		printf( "Error caso 4: se esperaba 0x00: 0x%02X\n", byMasc );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestByMascaraBitsInferiores01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test ByMascaraBitsInferiores 01:\n" );
	byte byMasc = ByMascaraBitsInferiores ( 4 );
	if ( byMasc != 0x0F )
	{
		printf( "Error caso 1: se esperaba 0x0F: 0x%02X\n", byMasc );
		iRes = BOOL_VAL_FALSO;
	}
	byMasc = ByMascaraBitsInferiores ( 1 );
	if ( byMasc != 0x01 )
	{
		printf( "Error caso 2: se esperaba 0x01: 0x%02X\n", byMasc );
		iRes = BOOL_VAL_FALSO;
	}
	byMasc = ByMascaraBitsInferiores ( 0 );
	if ( byMasc != 0x00 )
	{
		printf( "Error caso 3: se esperaba 0x00: 0x%02X\n", byMasc );
		iRes = BOOL_VAL_FALSO;
	}
	byMasc = ByMascaraBitsInferiores ( 8 );
	if ( byMasc != 0x00 )
	{
		printf( "Error caso 4: se esperaba 0x00: 0x%02X\n", byMasc );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestBy2MascaraBits01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test By2MascaraBits 01:\n" );
	byte2 by2Masc = By2MascaraBitsSuperiores ( 8 );
	if ( by2Masc != 0xFF00 )
	{
		printf( "Error caso 1: se esperaba 0xFF00: 0x%04X\n", by2Masc );
		iRes = BOOL_VAL_FALSO;
	}
	by2Masc = By2MascaraBitsInferiores ( 8 );
	if ( by2Masc != 0x00FF )
	{
		printf( "Error caso 2: se esperaba 0x00FF: 0x%04X\n", by2Masc );
		iRes = BOOL_VAL_FALSO;
	}
	by2Masc = By2MascaraBitsSuperiores ( 16 );
	if ( by2Masc != 0x0000 )
	{
		printf( "Error caso 3: se esperaba 0x0000: 0x%04X\n", by2Masc );
		iRes = BOOL_VAL_FALSO;
	}
	by2Masc = By2MascaraBitsInferiores ( 0 );
	if ( by2Masc != 0x0000 )
	{
		printf( "Error caso 4: se esperaba 0x0000: 0x%04X\n", by2Masc );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestBy4MascaraBits01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test By4MascaraBits 01:\n" );
	byte4 by4Masc = By4MascaraBitsSuperiores ( 16 );
	if ( by4Masc != 0xFFFF0000 )
	{
		printf( "Error caso 1: se esperaba 0xFFFF0000: 0x%08X\n", (unsigned int) by4Masc );
		iRes = BOOL_VAL_FALSO;
	}
	by4Masc = By4MascaraBitsInferiores ( 16 );
	if ( by4Masc != 0x0000FFFF )
	{
		printf( "Error caso 2: se esperaba 0x0000FFFF: 0x%08X\n", (unsigned int) by4Masc );
		iRes = BOOL_VAL_FALSO;
	}
	by4Masc = By4MascaraBitsSuperiores ( 32 );
	if ( by4Masc != 0x00000000 )
	{
		printf( "Error caso 3: se esperaba 0x00000000: 0x%08X\n", (unsigned int) by4Masc );
		iRes = BOOL_VAL_FALSO;
	}
	by4Masc = By4MascaraBitsInferiores ( 0 );
	if ( by4Masc != 0x00000000 )
	{
		printf( "Error caso 4: se esperaba 0x00000000: 0x%08X\n", (unsigned int) by4Masc );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



int TestBits ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test Bits]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestByMascaraBitsSuperiores01 () == BOOL_VAL_CIERTO ) &&
			( TestByMascaraBitsInferiores01 () == BOOL_VAL_CIERTO ) &&
			( TestBy2MascaraBits01 () == BOOL_VAL_CIERTO ) &&
			( TestBy4MascaraBits01 () == BOOL_VAL_CIERTO ) )
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
