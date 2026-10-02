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



/* Lo que el paso de sscanf a strtol arregla. Ninguno de estos casos pasaba
   antes del 2026-09-19: con sscanf el desbordamiento era comportamiento
   indefinido y la basura del final se ignoraba. */
static int TestConvCadenaAEntero02 ()
{
	int iRes = BOOL_VAL_CIERTO;

	printf ( "Test ConvCadenaAEntero 02 ( casos limite ):\n" );

	/* El limite justo si entra. */
	if ( ConvCadenaAEntero ( "2147483647" ) != 2147483647 )
	{
		printf ( "Error caso 1: INT_MAX deberia convertirse: %d\n",
				 ConvCadenaAEntero ( "2147483647" ) );
		iRes = BOOL_VAL_FALSO;
	}
	/* Uno mas, no. Y tiene los mismos diez digitos que INT_MAX, que es por lo
	   que la comprobacion de longitud que habia antes no bastaba. */
	if ( ConvCadenaAEntero ( "2147483648" ) != 0 )
	{
		printf ( "Error caso 2: INT_MAX+1 deberia dar 0: %d\n",
				 ConvCadenaAEntero ( "2147483648" ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ConvCadenaAEntero ( "9999999999" ) != 0 )
	{
		printf ( "Error caso 3: un numero de 10 digitos que no cabe deberia dar 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Basura al final: sscanf devolvia 12. */
	if ( ConvCadenaAEntero ( "12abc" ) != 0 )
	{
		printf ( "Error caso 4: \"12abc\" no es un entero: %d\n", ConvCadenaAEntero ( "12abc" ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ConvCadenaAEntero ( "abc" ) != 0 )
	{
		printf ( "Error caso 5: \"abc\" deberia dar 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ConvCadenaAEntero ( "" ) != 0 )
	{
		printf ( "Error caso 6: la cadena vacia deberia dar 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ConvCadenaAEntero ( NULL ) != 0 )
	{
		printf ( "Error caso 7: el puntero nulo deberia dar 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Un long de mas digitos que un int. Esto es lo que rompia la comprobacion
	   de longitud: usaba los digitos del int, no los del long.
	   Solo aplica donde long es mas ancho que int: en Windows ( LLP64 ) mide
	   lo mismo, y ahi 13 digitos NO caben, asi que lo correcto es 0. */
#if ( LONG_MAX >= 1234567890123 )
	if ( ConvCadenaAEnteroLargo ( "1234567890123" ) != 1234567890123L )
	{
		printf ( "Error caso 8: un long de 13 digitos deberia convertirse: %ld\n",
				 ConvCadenaAEnteroLargo ( "1234567890123" ) );
		iRes = BOOL_VAL_FALSO;
	}
#else
	if ( ConvCadenaAEnteroLargo ( "1234567890123" ) != 0 )
	{
		printf ( "Error caso 8: con long de 32 bits, 13 digitos no caben: deberia dar 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
#endif
	/* Y el menos en una conversion SIN SIGNO. strtoul lo acepta y devuelve el
	   complemento —4294967295 para "-1"— sin senalar error, asi que hay que
	   rechazarlo a mano. */
	if ( ConvCadenaAEnteroSinSigno ( "-1" ) != 0 )
	{
		printf ( "Error caso 9: \"-1\" sin signo deberia dar 0: %u\n",
				 ConvCadenaAEnteroSinSigno ( "-1" ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ConvCadenaAEnteroSinSigno ( "  -1" ) != 0 )
	{
		printf ( "Error caso 10: \"  -1\" con blancos delante tambien deberia dar 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

/* Las dos de real. */
static int TestConvCadenaAReal01 ()
{
	int iRes = BOOL_VAL_CIERTO;

	printf ( "Test ConvCadenaAReal 01:\n" );

	/* 3.25 es exacto en binario, asi que se puede comparar con igualdad. */
	if ( ConvCadenaAReal ( "3.25" ) != 3.25f )
	{
		printf ( "Error caso 1: se esperaba 3.25\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ConvCadenaARealDoble ( "-2.5" ) != -2.5 )
	{
		printf ( "Error caso 2: se esperaba -2.5\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ConvCadenaARealDoble ( "1e10" ) != 1e10 )
	{
		printf ( "Error caso 3: se esperaba 1e10\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Desbordamiento y basura, como en los enteros. */
	if ( ConvCadenaARealDoble ( "1e400" ) != 0.0 )
	{
		printf ( "Error caso 4: 1e400 no es representable, deberia dar 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ConvCadenaARealDoble ( "3.5xyz" ) != 0.0 )
	{
		printf ( "Error caso 5: \"3.5xyz\" no es un real, deberia dar 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ConvCadenaAReal ( NULL ) != 0.0f )
	{
		printf ( "Error caso 6: el puntero nulo deberia dar 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ConvCadenaAReal ( "" ) != 0.0f )
	{
		printf ( "Error caso 7: la cadena vacia deberia dar 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

/* Que las conversiones dejen el codigo de error correcto, y que distingan el
   puntero invalido de la cadena que no se puede convertir. El patron del repo
   es limpiar antes y comprobar despues: el acierto NO limpia el error. */
static int TestConvCadenaAError01 ()
{
	int iRes = BOOL_VAL_CIERTO;

	printf ( "Test ConvCadenaA errores 01:\n" );

	/* Un puntero nulo es un problema de parametros, no de conversion. */
	ErrLimpiar ();
	ConvCadenaAEntero ( NULL );
	if ( ErrCodigo () != ERR_PARAMETROS )
	{
		printf( "Error caso 1: con NULL se esperaba ERR_PARAMETROS ( %d ): %d\n",
				ERR_PARAMETROS, ErrCodigo () );
		iRes = BOOL_VAL_FALSO;
	}
	/* Lo demas es conversion imposible. */
	ErrLimpiar ();
	ConvCadenaAEntero ( "abc" );
	if ( ErrCodigo () != ERR_CONVERSION_IMPOSIBLE )
	{
		printf( "Error caso 2: con \"abc\" se esperaba ERR_CONVERSION_IMPOSIBLE ( %d ): %d\n",
				ERR_CONVERSION_IMPOSIBLE, ErrCodigo () );
		iRes = BOOL_VAL_FALSO;
	}
	ErrLimpiar ();
	ConvCadenaAEntero ( "2147483648" );
	if ( ErrCodigo () != ERR_CONVERSION_IMPOSIBLE )
	{
		printf( "Error caso 3: el desbordamiento deberia dar ERR_CONVERSION_IMPOSIBLE: %d\n",
				ErrCodigo () );
		iRes = BOOL_VAL_FALSO;
	}
	ErrLimpiar ();
	ConvCadenaAEnteroSinSigno ( "-1" );
	if ( ErrCodigo () != ERR_CONVERSION_IMPOSIBLE )
	{
		printf( "Error caso 4: el menos en una sin signo deberia dar ERR_CONVERSION_IMPOSIBLE: %d\n",
				ErrCodigo () );
		iRes = BOOL_VAL_FALSO;
	}
	ErrLimpiar ();
	ConvCadenaARealDoble ( "1e400" );
	if ( ErrCodigo () != ERR_CONVERSION_IMPOSIBLE )
	{
		printf( "Error caso 5: 1e400 deberia dar ERR_CONVERSION_IMPOSIBLE: %d\n", ErrCodigo () );
		iRes = BOOL_VAL_FALSO;
	}
	/* Y que una conversion buena NO ponga error. Ojo: tampoco lo limpia, por
	   eso hay que limpiar antes. */
	ErrLimpiar ();
	if ( ConvCadenaAEntero ( "42" ) != 42 )
	{
		printf( "Error caso 6: \"42\" deberia convertirse\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ErrHayError () != 0 )
	{
		printf( "Error caso 7: una conversion correcta no deberia dejar error: %d\n",
				ErrCodigo () );
		iRes = BOOL_VAL_FALSO;
	}
	ErrLimpiar ();
	return ( iRes );
}

/* Las hexadecimales, tras pasar de sscanf a strtoul en base 16. Lo que antes
   pasaba: "FFzz" daba 255, "-1" daba 4294967295 y el desbordamiento era
   comportamiento indefinido. */
static int TestConvCadenaHexA01 ()
{
	int iRes = BOOL_VAL_CIERTO;

	printf ( "Test ConvCadenaHexA 01:\n" );

	/* Lo que tiene que seguir funcionando. */
	if ( ConvCadenaHexAEnteroSinSigno ( "FF" ) != 255 )
	{
		printf ( "Error caso 1: \"FF\" deberia dar 255: %u\n",
				 ConvCadenaHexAEnteroSinSigno ( "FF" ) );
		iRes = BOOL_VAL_FALSO;
	}
	/* El '&' de Basic, que es el motivo de que estas funciones existan. */
	if ( ConvCadenaHexAEnteroSinSigno ( "&FF" ) != 255 )
	{
		printf ( "Error caso 2: \"&FF\" deberia dar 255: %u\n",
				 ConvCadenaHexAEnteroSinSigno ( "&FF" ) );
		iRes = BOOL_VAL_FALSO;
	}
	/* El prefijo 0x lo admitia sscanf y lo admite strtoul: no cambia. */
	if ( ConvCadenaHexAEnteroSinSigno ( "0xFF" ) != 255 )
	{
		printf ( "Error caso 3: \"0xFF\" deberia dar 255: %u\n",
				 ConvCadenaHexAEnteroSinSigno ( "0xFF" ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ConvCadenaHexAEnteroSinSigno ( "ffffffff" ) != 4294967295u )
	{
		printf ( "Error caso 4: \"ffffffff\" deberia dar 4294967295\n" );
		iRes = BOOL_VAL_FALSO;
	}

	/* Y lo que ahora se rechaza. */
	if ( ConvCadenaHexAEnteroSinSigno ( "FFzz" ) != 0 )
	{
		printf ( "Error caso 5: \"FFzz\" no es hexadecimal, sscanf daba 255: %u\n",
				 ConvCadenaHexAEnteroSinSigno ( "FFzz" ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ConvCadenaHexAEnteroSinSigno ( "-1" ) != 0 )
	{
		printf ( "Error caso 6: \"-1\" en una sin signo, sscanf daba 4294967295: %u\n",
				 ConvCadenaHexAEnteroSinSigno ( "-1" ) );
		iRes = BOOL_VAL_FALSO;
	}
	/* Diez digitos hexadecimales no caben en un unsigned int. */
	if ( ConvCadenaHexAEnteroSinSigno ( "FFFFFFFFFF" ) != 0 )
	{
		printf ( "Error caso 7: el desbordamiento deberia dar 0: %u\n",
				 ConvCadenaHexAEnteroSinSigno ( "FFFFFFFFFF" ) );
		iRes = BOOL_VAL_FALSO;
	}
	/* Un '&' suelto no es un numero. Antes daba 0 en silencio. */
	if ( ConvCadenaHexAEnteroSinSigno ( "&" ) != 0 )
	{
		printf ( "Error caso 8: \"&\" solo deberia dar 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ConvCadenaHexAEnteroSinSigno ( "GG" ) != 0 )
	{
		printf ( "Error caso 9: \"GG\" no es hexadecimal\n" );
		iRes = BOOL_VAL_FALSO;
	}

	/* Los codigos de error, igual que en las decimales. */
	ErrLimpiar ();
	ConvCadenaHexAEnteroSinSigno ( NULL );
	if ( ErrCodigo () != ERR_PARAMETROS )
	{
		printf ( "Error caso 10: con NULL se esperaba ERR_PARAMETROS: %d\n", ErrCodigo () );
		iRes = BOOL_VAL_FALSO;
	}
	ErrLimpiar ();
	ConvCadenaHexAEnteroSinSigno ( "FFzz" );
	if ( ErrCodigo () != ERR_CONVERSION_IMPOSIBLE )
	{
		printf ( "Error caso 11: se esperaba ERR_CONVERSION_IMPOSIBLE: %d\n", ErrCodigo () );
		iRes = BOOL_VAL_FALSO;
	}
	ErrLimpiar ();

	/* Las tres con signo son un reinterpretado de las sin signo, y eso es a
	   proposito: en hexadecimal se escriben los bits, no el valor con signo.
	   Este caso lo deja fijado. */
	if ( ConvCadenaHexAEntero ( "&FFFFFFFF" ) != -1 )
	{
		printf ( "Error caso 12: \"&FFFFFFFF\" deberia reinterpretarse como -1: %d\n",
				 ConvCadenaHexAEntero ( "&FFFFFFFF" ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ConvCadenaHexAEnteroDobleLargoSinSigno ( "FFFFFFFFFFFFFFFF" ) != 18446744073709551615ULL )
	{
		printf ( "Error caso 13: los 64 bits a uno deberian convertirse\n" );
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
			( TestConvEnteroACadenaHex01 () == BOOL_VAL_CIERTO ) &&
			( TestConvCadenaAEntero02 () == BOOL_VAL_CIERTO ) &&
			( TestConvCadenaAReal01 () == BOOL_VAL_CIERTO ) &&
			( TestConvCadenaAError01 () == BOOL_VAL_CIERTO ) &&
			( TestConvCadenaHexA01 () == BOOL_VAL_CIERTO ) )
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
