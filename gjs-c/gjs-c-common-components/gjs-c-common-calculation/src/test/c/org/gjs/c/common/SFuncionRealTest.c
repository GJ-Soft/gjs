#include "Base.h"

#include "SFuncionReal.h"
#include "CalculoOperaciones.h"



/* Funcion de prueba: duplica su argumento. */
static double FunDuplicar ( double dValor )
{
	return ( dValor * 2.0 );
}



static int TestSFunRCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SFunRCrear 01:\n" );

	SFuncionReal * p_funObj = SFunRCrear ( FunDuplicar );
	if ( ES_NULO ( p_funObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SFunREsValida ( p_funObj ) != 1 )
		{
			printf( "Error caso 2: la funcion recien creada deberia ser valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFunREsCompuesta ( p_funObj ) != 0 )
		{
			printf( "Error caso 3: una funcion simple no deberia ser compuesta\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* f( 3 ) = 6. */
		if ( MatEsIgual ( SFunREvaluar ( p_funObj, 3.0 ), 6.0 ) != 1 )
		{
			printf( "Error caso 4: f( 3 ) deberia ser 6: %f\n", SFunREvaluar ( p_funObj, 3.0 ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SFunRDestruir ( &p_funObj );

	if ( ES_VALIDO ( p_funObj ) )
	{
		printf( "Error caso 5: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Crear con una funcion nula devuelve nulo. */
	SFuncionReal * p_funNula = SFunRCrear ( NULL );
	if ( ES_VALIDO ( p_funNula ) )
	{
		printf( "Error caso 6: crear con funcion nula deberia devolver nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SFunRDestruir ( &p_funNula );
	return ( iRes );
}

static int TestSFunRComposicion01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SFunRComposicion 01:\n" );

	SFuncionReal * p_funObj = SFunRCrear ( FunDuplicar );
	/* La negada compone la negacion sobre la funcion original. */
	SFuncionReal * p_funNeg = SFunRNegada ( p_funObj );
	if ( ES_VALIDO ( p_funNeg ) )
	{
		if ( SFunREsCompuesta ( p_funNeg ) != 1 )
		{
			printf( "Error caso 1: la funcion negada deberia ser compuesta\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* -( 3 * 2 ) = -6. */
		if ( MatEsIgual ( SFunREvaluar ( p_funNeg, 3.0 ), -6.0 ) != 1 )
		{
			printf( "Error caso 2: la negada en 3 deberia ser -6: %f\n", SFunREvaluar ( p_funNeg, 3.0 ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* El valor absoluto de la negada: |-6| = 6. */
		SFuncionReal * p_funAbs = SFunRValorAbsoluto ( p_funNeg );
		if ( ES_VALIDO ( p_funAbs ) )
		{
			if ( MatEsIgual ( SFunREvaluar ( p_funAbs, 3.0 ), 6.0 ) != 1 )
			{
				printf( "Error caso 3: el valor absoluto de la negada en 3 deberia ser 6: %f\n", SFunREvaluar ( p_funAbs, 3.0 ) );
				iRes = BOOL_VAL_FALSO;
			}
			/* Destruir la mas externa libera toda la cadena de composicion. */
			SFunRDestruir ( &p_funAbs );
		}
		else
		{
			printf( "Error caso 3: no se pudo componer el valor absoluto\n" );
			iRes = BOOL_VAL_FALSO;
			SFunRDestruir ( &p_funNeg );
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo componer la funcion negada\n" );
		iRes = BOOL_VAL_FALSO;
		SFunRDestruir ( &p_funObj );
	}
	return ( iRes );
}



int TestSFuncionReal ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SFuncionReal]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSFunRCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSFunRComposicion01 () == BOOL_VAL_CIERTO ) )
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
