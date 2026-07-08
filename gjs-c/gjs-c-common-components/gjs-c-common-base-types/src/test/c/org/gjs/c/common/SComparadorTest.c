#include "Base.h"

#include "SComparador.h"



/* Comparador propio de int ( formato -1 / 0 / 1 ). */
static int CompararEnteros ( void * p_vVal1, void * p_vVal2 )
{
	int iVal1 = *( (int *) p_vVal1 );
	int iVal2 = *( (int *) p_vVal2 );
	int iRes = 0;

	if ( iVal1 < iVal2 )
	{
		iRes = -1;
	}
	else if ( iVal1 > iVal2 )
	{
		iRes = 1;
	}
	return ( iRes );
}



static int TestSCmpEnteros01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCmpEnteros 01:\n" );

	/* El comparador de enteros de fabrica opera sobre datos de tipo long. */
	SComparador * p_cmpObj = SCmpEnteros ();
	if ( ES_VALIDO ( p_cmpObj ) )
	{
		long lVal1 = 5;
		long lVal2 = 10;
		long lVal3 = 5;

		if ( SCmpEsValido ( p_cmpObj ) != 1 )
		{
			printf( "Error caso 1: el comparador deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCmpEvaluar ( p_cmpObj, &lVal1, &lVal2 ) != -1 )
		{
			printf( "Error caso 2: 5 deberia ser menor que 10\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCmpEvaluarEsMenor ( p_cmpObj, &lVal1, &lVal2 ) != 1 )
		{
			printf( "Error caso 3: EsMenor deberia ser cierto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCmpEvaluarEsMayor ( p_cmpObj, &lVal2, &lVal1 ) != 1 )
		{
			printf( "Error caso 4: EsMayor deberia ser cierto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCmpEvaluarEsIgual ( p_cmpObj, &lVal1, &lVal3 ) != 1 )
		{
			printf( "Error caso 5: EsIgual deberia ser cierto\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el comparador\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCmpDestruir ( &p_cmpObj );
	return ( iRes );
}

static int TestSCmpLiterales01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCmpLiterales 01:\n" );

	SComparador * p_cmpObj = SCmpLiterales ();
	if ( ES_VALIDO ( p_cmpObj ) )
	{
		if ( SCmpEvaluarEsMenor ( p_cmpObj, "abc", "abd" ) != 1 )
		{
			printf( "Error caso 1: \"abc\" deberia ser menor que \"abd\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCmpEvaluarEsIgual ( p_cmpObj, "hola", "hola" ) != 1 )
		{
			printf( "Error caso 2: dos cadenas iguales deberian ser iguales\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCmpEvaluarEsMayor ( p_cmpObj, "b", "a" ) != 1 )
		{
			printf( "Error caso 3: \"b\" deberia ser mayor que \"a\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el comparador\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCmpDestruir ( &p_cmpObj );
	return ( iRes );
}

static int TestSCmpBloque01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCmpBloque 01:\n" );

	/* Comparador propio de int, para poder usar bloques de tipo int. */
	SComparador * p_cmpObj = SCmpCrear ( CompararEnteros );
	SBloque * p_blqA = SBlqCrearEntero ();
	SBloque * p_blqB = SBlqCrearEntero ();
	if ( ES_VALIDO ( p_cmpObj ) && ES_VALIDO ( p_blqA ) && ES_VALIDO ( p_blqB ) )
	{
		SBlqEscribirEntero ( p_blqA, 5 );
		SBlqEscribirEntero ( p_blqB, 10 );

		if ( SCmpEvaluarBloque ( p_cmpObj, p_blqA, p_blqB ) != -1 )
		{
			printf( "Error caso 1: el bloque 5 deberia ser menor que el 10\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCmpEvaluarBloqueEsMenor ( p_cmpObj, p_blqA, p_blqB ) != 1 )
		{
			printf( "Error caso 2: BloqueEsMenor deberia ser cierto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SBlqEscribirEntero ( p_blqB, 5 );
		if ( SCmpEvaluarBloqueEsIgual ( p_cmpObj, p_blqA, p_blqB ) != 1 )
		{
			printf( "Error caso 3: dos bloques con el mismo valor deberian ser iguales\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear el comparador o los bloques\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCmpDestruir ( &p_cmpObj );
	SBlqDestruir ( &p_blqA );
	SBlqDestruir ( &p_blqB );
	return ( iRes );
}

static int TestSCmpInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCmpInvalidos 01:\n" );

	if ( SCmpEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: un comparador nulo no deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Crear con funcion nula debe fallar. */
	if ( ES_VALIDO ( SCmpCrear ( NULL ) ) )
	{
		printf( "Error caso 2: crear con funcion nula deberia fallar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SComparador * p_cmpNulo = NULL;
	SCmpDestruir ( &p_cmpNulo );
	return ( iRes );
}



int TestSComparador ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SComparador]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSCmpEnteros01 () == BOOL_VAL_CIERTO ) &&
			( TestSCmpLiterales01 () == BOOL_VAL_CIERTO ) &&
			( TestSCmpBloque01 () == BOOL_VAL_CIERTO ) &&
			( TestSCmpInvalidos01 () == BOOL_VAL_CIERTO ) )
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
