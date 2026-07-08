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

	SToken * p_tokObj = STokGenerarExt ( "hola" );
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
		if ( STokLiteralEsIgual ( p_tokObj, "hola" ) != 1 )
		{
			printf( "Error caso 3: el valor deberia ser \"hola\": [%s]\n", STokValor ( p_tokObj ) );
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
	SToken * p_tokMal = STokGenerarExt ( "no valido" );
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
		if ( STokLiteralEsIgual ( p_tokObj, "identificador" ) != 1 )
		{
			printf( "Error caso 2: se esperaba \"identificador\": [%s]\n", STokValor ( p_tokObj ) );
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

	SToken * p_tokA = STokGenerarExt ( "abc" );
	SToken * p_tokB = STokGenerarExt ( "abd" );
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



int TestSToken ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SToken]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSTokCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSTokGenerar01 () == BOOL_VAL_CIERTO ) &&
			( TestSTokCopiar01 () == BOOL_VAL_CIERTO ) &&
			( TestSTokComparaciones01 () == BOOL_VAL_CIERTO ) )
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
