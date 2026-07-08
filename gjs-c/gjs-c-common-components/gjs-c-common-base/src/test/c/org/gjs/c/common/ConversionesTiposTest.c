#include "Base.h"

#include "ConversionesTipos.h"



static int TestConvDigitoACaracter01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test ConvDigitoACaracter 01:\n" );
	if ( ConvDigitoACaracter ( 0 ) != '0' )
	{
		printf( "Error caso 1: se esperaba '0': [%c]\n", ConvDigitoACaracter ( 0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ConvDigitoACaracter ( 5 ) != '5' )
	{
		printf( "Error caso 2: se esperaba '5': [%c]\n", ConvDigitoACaracter ( 5 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ConvDigitoACaracter ( 9 ) != '9' )
	{
		printf( "Error caso 3: se esperaba '9': [%c]\n", ConvDigitoACaracter ( 9 ) );
		iRes = BOOL_VAL_FALSO;
	}
	/* Un digito fuera de rango no debe devolver un caracter numerico. */
	if ( ( ConvDigitoACaracter ( 10 ) >= '0' ) && ( ConvDigitoACaracter ( 10 ) <= '9' ) )
	{
		printf( "Error caso 4: no se esperaba un caracter numerico\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestConvCaracterADigito01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test ConvCaracterADigito 01:\n" );
	if ( ConvCaracterADigito ( '0' ) != 0 )
	{
		printf( "Error caso 1: se esperaba 0: %d\n", ConvCaracterADigito ( '0' ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ConvCaracterADigito ( '7' ) != 7 )
	{
		printf( "Error caso 2: se esperaba 7: %d\n", ConvCaracterADigito ( '7' ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ConvCaracterADigito ( '9' ) != 9 )
	{
		printf( "Error caso 3: se esperaba 9: %d\n", ConvCaracterADigito ( '9' ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ConvCaracterADigito ( 'A' ) != -1 )
	{
		printf( "Error caso 4: se esperaba -1: %d\n", ConvCaracterADigito ( 'A' ) );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestConvRealAEntero01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test ConvRealAEntero 01:\n" );
	/* Truncando. */
	if ( ConvRealAEntero ( 3.7f, 1 ) != 3 )
	{
		printf( "Error caso 1: se esperaba 3: %d\n", ConvRealAEntero ( 3.7f, 1 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ConvRealAEntero ( -3.7f, 1 ) != -3 )
	{
		printf( "Error caso 2: se esperaba -3: %d\n", ConvRealAEntero ( -3.7f, 1 ) );
		iRes = BOOL_VAL_FALSO;
	}
	/* Redondeando. */
	if ( ConvRealAEntero ( 3.7f, 0 ) != 4 )
	{
		printf( "Error caso 3: se esperaba 4: %d\n", ConvRealAEntero ( 3.7f, 0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ConvRealAEntero ( 3.2f, 0 ) != 3 )
	{
		printf( "Error caso 4: se esperaba 3: %d\n", ConvRealAEntero ( 3.2f, 0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ConvRealDobleAEntero ( 12.9, 1 ) != 12 )
	{
		printf( "Error caso 5: se esperaba 12: %d\n", ConvRealDobleAEntero ( 12.9, 1 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ConvRealDobleAEntero ( 12.9, 0 ) != 13 )
	{
		printf( "Error caso 6: se esperaba 13: %d\n", ConvRealDobleAEntero ( 12.9, 0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestConvCadenaAEntero01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test ConvCadenaAEntero 01:\n" );
	if ( ConvCadenaAEntero ( "12345" ) != 12345 )
	{
		printf( "Error caso 1: se esperaba 12345: %d\n", ConvCadenaAEntero ( "12345" ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ConvCadenaAEntero ( "-45" ) != -45 )
	{
		printf( "Error caso 2: se esperaba -45: %d\n", ConvCadenaAEntero ( "-45" ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ConvCadenaAEntero ( NULL ) != 0 )
	{
		printf( "Error caso 3: se esperaba 0 para nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ConvCadenaAEnteroLargo ( "1000000" ) != 1000000L )
	{
		printf( "Error caso 4: se esperaba 1000000: %ld\n", ConvCadenaAEnteroLargo ( "1000000" ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ConvCadenaAEnteroSinSigno ( "100" ) != 100U )
	{
		printf( "Error caso 5: se esperaba 100: %u\n", ConvCadenaAEnteroSinSigno ( "100" ) );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestConvEnteroACadena01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test ConvEnteroACadena 01:\n" );
	char * p_cRes = NULL;

	/* La conversion sin signo esta comprobada como directa. */
	p_cRes = ConvEnteroSinSignoACadena ( 0 );
	if ( ES_NULO ( p_cRes ) || ( strcmp ( p_cRes, "0" ) != 0 ) )
	{
		printf( "Error caso 1: se esperaba \"0\": [%s]\n", ES_VALIDO ( p_cRes ) ? p_cRes : "(nulo)" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_cRes );

	p_cRes = ConvEnteroSinSignoACadena ( 12345 );
	if ( ES_NULO ( p_cRes ) || ( strcmp ( p_cRes, "12345" ) != 0 ) )
	{
		printf( "Error caso 2: se esperaba \"12345\": [%s]\n", ES_VALIDO ( p_cRes ) ? p_cRes : "(nulo)" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_cRes );

	/* Ida y vuelta con enteros con signo. */
	p_cRes = ConvEnteroACadena ( 987 );
	if ( ConvCadenaAEntero ( p_cRes ) != 987 )
	{
		printf( "Error caso 3: ida y vuelta incorrecta para 987: [%s]\n", ES_VALIDO ( p_cRes ) ? p_cRes : "(nulo)" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_cRes );

	p_cRes = ConvEnteroACadena ( -321 );
	if ( ConvCadenaAEntero ( p_cRes ) != -321 )
	{
		printf( "Error caso 4: ida y vuelta incorrecta para -321: [%s]\n", ES_VALIDO ( p_cRes ) ? p_cRes : "(nulo)" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_cRes );

	p_cRes = ConvEnteroLargoACadena ( 1000000L );
	if ( ConvCadenaAEnteroLargo ( p_cRes ) != 1000000L )
	{
		printf( "Error caso 5: ida y vuelta incorrecta para 1000000: [%s]\n", ES_VALIDO ( p_cRes ) ? p_cRes : "(nulo)" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_cRes );

	return ( iRes );
}

static int TestConvRealACadena01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test ConvRealACadena 01:\n" );
	char * p_cRes = NULL;

	p_cRes = ConvRealACadena ( 0.0f );
	if ( ES_NULO ( p_cRes ) || ( strcmp ( p_cRes, "0.0" ) != 0 ) )
	{
		printf( "Error caso 1: se esperaba \"0.0\": [%s]\n", ES_VALIDO ( p_cRes ) ? p_cRes : "(nulo)" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_cRes );

	return ( iRes );
}

static int TestConvEnteroACadenaHex01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test ConvEnteroACadenaHex 01:\n" );
	char * p_cRes = NULL;

	/* Ida y vuelta hexadecimal. */
	p_cRes = ConvEnteroACadenaHex ( 255 );
	if ( ConvCadenaHexAEntero ( p_cRes ) != 255 )
	{
		printf( "Error caso 1: ida y vuelta incorrecta para 255: [%s]\n", ES_VALIDO ( p_cRes ) ? p_cRes : "(nulo)" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_cRes );

	p_cRes = ConvEnteroSinSignoACadenaHex ( 0x1234 );
	if ( ConvCadenaHexAEnteroSinSigno ( p_cRes ) != 0x1234 )
	{
		printf( "Error caso 2: ida y vuelta incorrecta para 0x1234: [%s]\n", ES_VALIDO ( p_cRes ) ? p_cRes : "(nulo)" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_cRes );

	/* Debe admitir tambien cadenas sin el prefijo. */
	if ( ConvCadenaHexAEntero ( "FF" ) != 255 )
	{
		printf( "Error caso 3: se esperaba 255: %d\n", ConvCadenaHexAEntero ( "FF" ) );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



int TestConversionesTipos ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test ConversionesTipos]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestConvDigitoACaracter01 () == BOOL_VAL_CIERTO ) &&
			( TestConvCaracterADigito01 () == BOOL_VAL_CIERTO ) &&
			( TestConvRealAEntero01 () == BOOL_VAL_CIERTO ) &&
			( TestConvCadenaAEntero01 () == BOOL_VAL_CIERTO ) &&
			( TestConvEnteroACadena01 () == BOOL_VAL_CIERTO ) &&
			( TestConvRealACadena01 () == BOOL_VAL_CIERTO ) &&
			( TestConvEnteroACadenaHex01 () == BOOL_VAL_CIERTO ) )
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
