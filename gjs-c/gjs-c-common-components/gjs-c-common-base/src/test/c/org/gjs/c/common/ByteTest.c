#include "Base.h"

#include "Byte.h"



static int TestByteNibbleInferior01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test ByteNibbleInferior 01:\n" );
	nibble nibVal = ByteNibbleInferior ( 0xAB );
	if ( nibVal != 0x0B )
	{
		printf( "Error caso 1: se esperaba 0x0B: 0x%02X\n", nibVal );
		iRes = BOOL_VAL_FALSO;
	}
	nibVal = ByteNibbleInferior ( 0x00 );
	if ( nibVal != 0x00 )
	{
		printf( "Error caso 2: se esperaba 0x00: 0x%02X\n", nibVal );
		iRes = BOOL_VAL_FALSO;
	}
	nibVal = ByteNibbleInferior ( 0xFF );
	if ( nibVal != 0x0F )
	{
		printf( "Error caso 3: se esperaba 0x0F: 0x%02X\n", nibVal );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestByteNibbleSuperior01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test ByteNibbleSuperior 01:\n" );
	nibble nibVal = ByteNibbleSuperior ( 0xAB );
	if ( nibVal != 0x0A )
	{
		printf( "Error caso 1: se esperaba 0x0A: 0x%02X\n", nibVal );
		iRes = BOOL_VAL_FALSO;
	}
	nibVal = ByteNibbleSuperior ( 0x00 );
	if ( nibVal != 0x00 )
	{
		printf( "Error caso 2: se esperaba 0x00: 0x%02X\n", nibVal );
		iRes = BOOL_VAL_FALSO;
	}
	nibVal = ByteNibbleSuperior ( 0xFF );
	if ( nibVal != 0x0F )
	{
		printf( "Error caso 3: se esperaba 0x0F: 0x%02X\n", nibVal );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestByteComponer01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test ByteComponer 01:\n" );
	byte byVal = ByteComponer ( 0x0A, 0x0B );
	if ( byVal != 0xAB )
	{
		printf( "Error caso 1: se esperaba 0xAB: 0x%02X\n", byVal );
		iRes = BOOL_VAL_FALSO;
	}
	byVal = ByteComponer ( 0x00, 0x00 );
	if ( byVal != 0x00 )
	{
		printf( "Error caso 2: se esperaba 0x00: 0x%02X\n", byVal );
		iRes = BOOL_VAL_FALSO;
	}
	byVal = ByteComponer ( 0x0F, 0x0F );
	if ( byVal != 0xFF )
	{
		printf( "Error caso 3: se esperaba 0xFF: 0x%02X\n", byVal );
		iRes = BOOL_VAL_FALSO;
	}
	/* Solo deben usarse los 4 bits inferiores de cada nibble. */
	byVal = ByteComponer ( 0xFA, 0xFB );
	if ( byVal != 0xAB )
	{
		printf( "Error caso 4: se esperaba 0xAB: 0x%02X\n", byVal );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestByteAHex01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test ByteAHex 01:\n" );
	char * p_cRes = ByteAHex ( 0xAB, NULL );
	if ( p_cRes != NULL )
	{
		if ( strcmp ( p_cRes, "AB" ) != 0 )
		{
			printf( "Error caso 1: se esperaba \"AB\": [%s]\n", p_cRes );
			iRes = BOOL_VAL_FALSO;
		}
		MemLiberar ( (void **) &p_cRes );
	}
	else
	{
		printf( "Error caso 1: no se esperaba nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	char * p_cBuffer = CadCrear ( 2 );
	p_cRes = ByteAHex ( 0x00, p_cBuffer );
	if ( ( p_cRes == p_cBuffer ) && ( strcmp ( p_cRes, "00" ) != 0 ) )
	{
		printf( "Error caso 2: se esperaba \"00\": [%s]\n", p_cRes );
		iRes = BOOL_VAL_FALSO;
	}
	p_cRes = ByteAHex ( 0xFF, p_cBuffer );
	if ( strcmp ( p_cRes, "FF" ) != 0 )
	{
		printf( "Error caso 3: se esperaba \"FF\": [%s]\n", p_cRes );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_cBuffer );
	return ( iRes );
}

static int TestHexAByte01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test HexAByte 01:\n" );
	byte byVal = HexAByte ( "AB" );
	if ( byVal != 0xAB )
	{
		printf( "Error caso 1: se esperaba 0xAB: 0x%02X\n", byVal );
		iRes = BOOL_VAL_FALSO;
	}
	byVal = HexAByte ( "00" );
	if ( byVal != 0x00 )
	{
		printf( "Error caso 2: se esperaba 0x00: 0x%02X\n", byVal );
		iRes = BOOL_VAL_FALSO;
	}
	byVal = HexAByte ( "ff" );
	if ( byVal != 0xFF )
	{
		printf( "Error caso 3: se esperaba 0xFF: 0x%02X\n", byVal );
		iRes = BOOL_VAL_FALSO;
	}
	byVal = HexAByte ( NULL );
	if ( byVal != 0x00 )
	{
		printf( "Error caso 4: se esperaba 0x00: 0x%02X\n", byVal );
		iRes = BOOL_VAL_FALSO;
	}
	byVal = HexAByte ( "ZZ" );
	if ( byVal != 0x00 )
	{
		printf( "Error caso 5: se esperaba 0x00: 0x%02X\n", byVal );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



int TestByte ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test Byte]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestByteNibbleInferior01 () == BOOL_VAL_CIERTO ) &&
			( TestByteNibbleSuperior01 () == BOOL_VAL_CIERTO ) &&
			( TestByteComponer01 () == BOOL_VAL_CIERTO ) &&
			( TestByteAHex01 () == BOOL_VAL_CIERTO ) &&
			( TestHexAByte01 () == BOOL_VAL_CIERTO ) )
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
