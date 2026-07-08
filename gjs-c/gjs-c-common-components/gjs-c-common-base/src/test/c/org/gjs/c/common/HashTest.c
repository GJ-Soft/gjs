#include "Base.h"

#include "Hash.h"



static int TestHashByte01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test HashByte 01:\n" );
	/* Valores tomados directamente de la tabla de sustitucion. */
	if ( HashByte ( 0x00 ) != 0x7C )
	{
		printf( "Error caso 1: se esperaba 0x7C: 0x%X\n", HashByte ( 0x00 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( HashByte ( 0x01 ) != 0x22 )
	{
		printf( "Error caso 2: se esperaba 0x22: 0x%X\n", HashByte ( 0x01 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( HashByte ( 0xFF ) != 0x81 )
	{
		printf( "Error caso 3: se esperaba 0x81: 0x%X\n", HashByte ( 0xFF ) );
		iRes = BOOL_VAL_FALSO;
	}
	/* HashCaracter delega en HashByte. */
	if ( HashCaracter ( 'A' ) != HashByte ( (byte) 'A' ) )
	{
		printf( "Error caso 4: HashCaracter deberia coincidir con HashByte\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestHashBinario01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test HashBinario 01:\n" );
	byte byDatos [ 4 ] = { 0x01, 0x02, 0x03, 0x04 };
	/* Con puntero nulo o tamano no positivo debe devolver 0. */
	if ( HashBinario ( NULL, 4 ) != 0 )
	{
		printf( "Error caso 1: se esperaba 0 para puntero nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( HashBinario ( byDatos, 0 ) != 0 )
	{
		printf( "Error caso 2: se esperaba 0 para tamano 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Debe ser determinista. */
	if ( HashBinario ( byDatos, 4 ) != HashBinario ( byDatos, 4 ) )
	{
		printf( "Error caso 3: el hash deberia ser determinista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestHashCadena01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test HashCadena 01:\n" );
	/* Determinista para la misma cadena. */
	if ( HashCadena ( "hola mundo" ) != HashCadena ( "hola mundo" ) )
	{
		printf( "Error caso 1: el hash de la misma cadena deberia coincidir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Cadenas distintas deberian dar (con alta probabilidad) hash distinto. */
	if ( HashCadena ( "hola mundo" ) == HashCadena ( "adios mundo" ) )
	{
		printf( "Error caso 2: se esperaban hash distintos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* El hash entero tambien debe ser determinista. */
	if ( HashEntero ( 123456 ) != HashEntero ( 123456 ) )
	{
		printf( "Error caso 3: el hash entero deberia ser determinista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



int TestHash ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test Hash]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestHashByte01 () == BOOL_VAL_CIERTO ) &&
			( TestHashBinario01 () == BOOL_VAL_CIERTO ) &&
			( TestHashCadena01 () == BOOL_VAL_CIERTO ) )
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
