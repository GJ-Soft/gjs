#include "Base.h"

#include "SRango.h"



static int TestSRngCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SRngCrear 01:\n" );

	SRango * p_rngObj = SRngCrear ( 5, 10 );
	if ( ES_NULO ( p_rngObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SRngEsValido ( p_rngObj ) != 1 )
		{
			printf( "Error caso 2: el rango recien creado deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SRngMin ( p_rngObj ) != 5 ) || ( SRngMax ( p_rngObj ) != 10 ) )
		{
			printf( "Error caso 3: se esperaba min 5 y max 10\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SRngAmplitud ( p_rngObj ) != 5 )
		{
			printf( "Error caso 4: se esperaba amplitud 5: %d\n", SRngAmplitud ( p_rngObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SRngDestruir ( &p_rngObj );

	if ( ES_VALIDO ( p_rngObj ) )
	{
		printf( "Error caso 5: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Crear con min > max debe fallar. */
	if ( ES_VALIDO ( SRngCrear ( 10, 5 ) ) )
	{
		printf( "Error caso 6: se esperaba nulo al crear con min > max\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSRngEstaIncluido01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SRngEstaIncluido 01:\n" );

	SRango * p_rngObj = SRngCrear ( 5, 10 );
	if ( ES_VALIDO ( p_rngObj ) )
	{
		/* Los extremos estan incluidos. */
		if ( ( SRngEstaIncluido ( p_rngObj, 5 ) != 1 ) || ( SRngEstaIncluido ( p_rngObj, 10 ) != 1 ) )
		{
			printf( "Error caso 1: los extremos deberian estar incluidos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SRngEstaIncluido ( p_rngObj, 7 ) != 1 )
		{
			printf( "Error caso 2: el 7 deberia estar incluido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SRngEstaIncluido ( p_rngObj, 4 ) != 0 ) || ( SRngEstaIncluido ( p_rngObj, 11 ) != 0 ) )
		{
			printf( "Error caso 3: los valores fuera del rango no deberian estar incluidos\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el rango\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SRngDestruir ( &p_rngObj );
	return ( iRes );
}

static int TestSRngEstablecer01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SRngEstablecer 01:\n" );

	SRango * p_rngObj = SRngCrear ( 5, 10 );
	if ( ES_VALIDO ( p_rngObj ) )
	{
		if ( SRngEstablecerMin ( p_rngObj, 3 ) != 1 )
		{
			printf( "Error caso 1: establecer un min valido deberia devolver 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SRngMin ( p_rngObj ) != 3 )
		{
			printf( "Error caso 2: el min deberia ser ahora 3\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SRngEstablecerMax ( p_rngObj, 20 ) != 1 )
		{
			printf( "Error caso 3: establecer un max valido deberia devolver 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SRngMax ( p_rngObj ) != 20 )
		{
			printf( "Error caso 4: el max deberia ser ahora 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Un min mayor que el max deja el rango invalido y devuelve 0. */
		if ( SRngEstablecerMin ( p_rngObj, 25 ) != 0 )
		{
			printf( "Error caso 5: establecer min > max deberia devolver 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el rango\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SRngDestruir ( &p_rngObj );
	return ( iRes );
}

static int TestSRngInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SRngInvalidos 01:\n" );

	if ( SRngEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: un rango nulo no deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SRngEstaIncluido ( NULL, 5 ) != 0 )
	{
		printf( "Error caso 2: nada esta incluido en un rango nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SRango * p_rngNulo = NULL;
	SRngDestruir ( &p_rngNulo );
	return ( iRes );
}



int TestSRango ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SRango]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSRngCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSRngEstaIncluido01 () == BOOL_VAL_CIERTO ) &&
			( TestSRngEstablecer01 () == BOOL_VAL_CIERTO ) &&
			( TestSRngInvalidos01 () == BOOL_VAL_CIERTO ) )
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
