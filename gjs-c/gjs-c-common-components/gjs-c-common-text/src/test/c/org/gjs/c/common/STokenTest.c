#include "Base.h"

#include "SToken.h"



static int TestSTokCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test STokCrear 01:\n" );

	SToken * p_tokObj = STokCrear ( 20 );
	if ( ES_NULO ( p_tokObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		/* Un token recien creado esta vacio. */
		if ( STokEstaVacio ( p_tokObj ) != 1 )
		{
			printf( "Error caso 2: el token recien creado deberia estar vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( STokLongitud ( p_tokObj ) != 0 )
		{
			printf( "Error caso 3: la longitud inicial deberia ser 0: %d\n", STokLongitud ( p_tokObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	STokDestruir ( &p_tokObj );

	if ( ES_VALIDO ( p_tokObj ) )
	{
		printf( "Error caso 4: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSTokGenerar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test STokGenerar 01:\n" );

	SToken * p_tokObj = STokGenerarLit ( "hola" );
	if ( ES_VALIDO ( p_tokObj ) )
	{
		if ( STokEstaVacio ( p_tokObj ) != 0 )
		{
			printf( "Error caso 1: el token generado no deberia estar vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( STokLongitud ( p_tokObj ) != 4 )
		{
			printf( "Error caso 2: la longitud deberia ser 4: %d\n", STokLongitud ( p_tokObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( STokEsIgualLit ( p_tokObj, "hola" ) != 1 )
		{
			printf( "Error caso 3: el valor deberia ser \"hola\": [%s]\n", STokValorLit ( p_tokObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo generar el token\n" );
		iRes = BOOL_VAL_FALSO;
	}
	STokDestruir ( &p_tokObj );

	/* Generar con un literal que no es un token valido devuelve nulo. */
	SToken * p_tokMal = STokGenerarLit ( "no valido" );
	if ( ES_VALIDO ( p_tokMal ) )
	{
		printf( "Error caso 4: un literal con espacios no deberia generar un token\n" );
		iRes = BOOL_VAL_FALSO;
	}
	STokDestruir ( &p_tokMal );
	return ( iRes );
}

static int TestSTokCopiar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test STokCopiar 01:\n" );

	SToken * p_tokObj = STokCrear ( 20 );
	if ( ES_VALIDO ( p_tokObj ) )
	{
		if ( STokCopiarLiteral ( p_tokObj, "identificador" ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al copiar un token valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( STokEsIgualLit ( p_tokObj, "identificador" ) != 1 )
		{
			printf( "Error caso 2: se esperaba \"identificador\": [%s]\n", STokValorLit ( p_tokObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el token\n" );
		iRes = BOOL_VAL_FALSO;
	}
	STokDestruir ( &p_tokObj );
	return ( iRes );
}

static int TestSTokComparaciones01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test STokComparaciones 01:\n" );

	SToken * p_tokA = STokGenerarLit ( "abc" );
	SToken * p_tokB = STokGenerarLit ( "abd" );
	if ( ES_VALIDO ( p_tokA ) && ES_VALIDO ( p_tokB ) )
	{
		if ( STokEsMenor ( p_tokA, p_tokB ) != 1 )
		{
			printf( "Error caso 1: \"abc\" deberia ser menor que \"abd\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( STokEsMayor ( p_tokB, p_tokA ) != 1 )
		{
			printf( "Error caso 2: \"abd\" deberia ser mayor que \"abc\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( STokEsIgual ( p_tokA, p_tokB ) != 0 )
		{
			printf( "Error caso 3: \"abc\" y \"abd\" no deberian ser iguales\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( STokEsDiferente ( p_tokA, p_tokB ) != 1 )
		{
			printf( "Error caso 4: \"abc\" y \"abd\" deberian ser diferentes\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron generar los tokens\n" );
		iRes = BOOL_VAL_FALSO;
	}
	STokDestruir ( &p_tokA );
	STokDestruir ( &p_tokB );
	return ( iRes );
}

static int TestSTokValorEstablecer01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test STokValorEstablecer 01:\n" );

	SToken * p_tokObj = STokCrear ( 20 );
	SCadena * p_cadValor = SCadGenerar ( "primero" );
	if ( ES_VALIDO ( p_tokObj ) && ES_VALIDO ( p_cadValor ) )
	{
		/* STokEstablecer sustituye el valor por el de una SCadena. */
		if ( STokEstablecer ( p_tokObj, p_cadValor ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al establecer desde una SCadena\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( STokEsIgualCad ( p_tokObj, p_cadValor ) != 1 )
		{
			printf( "Error caso 2: el token deberia ser igual a la cadena establecida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* STokValor devuelve la cadena interna, no una copia. */
		if ( SCadEsIgual ( STokValor ( p_tokObj ), p_cadValor ) != 1 )
		{
			printf( "Error caso 3: STokValor deberia devolver la cadena con el mismo contenido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Y STokValorLit el contenido de solo lectura. */
		if ( CadComparar ( (char *) STokValorLit ( p_tokObj ), "primero" ) != COMP_IGUAL )
		{
			printf( "Error caso 4: se esperaba \"primero\": [%s]\n", STokValorLit ( p_tokObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* STokEstablecerLit sustituye, no concatena. */
		if ( STokEstablecerLit ( p_tokObj, "segundo" ) != 1 )
		{
			printf( "Error caso 5: se esperaba resultado 1 al establecer desde un literal\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( STokEsIgualLit ( p_tokObj, "segundo" ) != 1 )
		{
			printf( "Error caso 6: se esperaba \"segundo\": [%s]\n", STokValorLit ( p_tokObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( STokLongitud ( p_tokObj ) != 7 )
		{
			printf( "Error caso 7: la longitud deberia ser 7: %d\n", STokLongitud ( p_tokObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* STokEstablecer vacia antes de copiar, y vaciar libera el buffer: el */
		/* token queda redimensionado al ultimo valor, no conserva el tope.   */
		if ( STokMaxTam ( p_tokObj ) != 7 )
		{
			printf( "Error caso 8: la longitud maxima deberia haber quedado en 7: %d\n", STokMaxTam ( p_tokObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* STokCopiarLiteral, en cambio, no vacia y respeta el tope vigente. */
		if ( STokCopiarLiteral ( p_tokObj, "octavos" ) != 1 )
		{
			printf( "Error caso 9: se esperaba resultado 1 al copiar un valor que cabe\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( STokMaxTam ( p_tokObj ) != 7 )
		{
			printf( "Error caso 10: copiar no deberia cambiar la longitud maxima: %d\n", STokMaxTam ( p_tokObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron preparar el token y la cadena\n" );
		iRes = BOOL_VAL_FALSO;
	}
	STokDestruir ( &p_tokObj );
	SCadDestruir ( &p_cadValor );
	return ( iRes );
}

static int TestSTokComparar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test STokComparar 01:\n" );

	SToken * p_tokA = STokGenerarLit ( "abc" );
	SToken * p_tokB = STokGenerarLit ( "abd" );
	if ( ES_VALIDO ( p_tokA ) && ES_VALIDO ( p_tokB ) )
	{
		if ( STokComparar ( p_tokA, p_tokB ) != COMP_MENOR )
		{
			printf( "Error caso 1: se esperaba COMP_MENOR: %d\n", STokComparar ( p_tokA, p_tokB ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( STokComparar ( p_tokB, p_tokA ) != COMP_MAYOR )
		{
			printf( "Error caso 2: se esperaba COMP_MAYOR: %d\n", STokComparar ( p_tokB, p_tokA ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( STokComparar ( p_tokA, p_tokA ) != COMP_IGUAL )
		{
			printf( "Error caso 3: se esperaba COMP_IGUAL: %d\n", STokComparar ( p_tokA, p_tokA ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( STokCompararCad ( p_tokA, STokValor ( p_tokB ) ) != COMP_MENOR )
		{
			printf( "Error caso 4: se esperaba COMP_MENOR contra la cadena\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( STokCompararLit ( p_tokA, "abc" ) != COMP_IGUAL )
		{
			printf( "Error caso 5: se esperaba COMP_IGUAL contra el literal\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( STokCompararLit ( p_tokB, "abc" ) != COMP_MAYOR )
		{
			printf( "Error caso 6: se esperaba COMP_MAYOR contra el literal\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Un token valido es mayor que uno nulo, y dos nulos son iguales. */
		if ( STokComparar ( p_tokA, NULL ) != COMP_MAYOR )
		{
			printf( "Error caso 7: un token valido deberia ser mayor que uno nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( STokComparar ( NULL, p_tokB ) != COMP_MENOR )
		{
			printf( "Error caso 8: un token nulo deberia ser menor que uno valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( STokComparar ( NULL, NULL ) != COMP_IGUAL )
		{
			printf( "Error caso 9: dos tokens nulos deberian ser iguales\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron generar los tokens\n" );
		iRes = BOOL_VAL_FALSO;
	}
	STokDestruir ( &p_tokA );
	STokDestruir ( &p_tokB );
	return ( iRes );
}



int TestSToken ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SToken]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSTokCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSTokGenerar01 () == BOOL_VAL_CIERTO ) &&
			( TestSTokCopiar01 () == BOOL_VAL_CIERTO ) &&
			( TestSTokComparaciones01 () == BOOL_VAL_CIERTO ) &&
			( TestSTokValorEstablecer01 () == BOOL_VAL_CIERTO ) &&
			( TestSTokComparar01 () == BOOL_VAL_CIERTO ) )
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
