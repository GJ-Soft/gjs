#include "Base.h"

#include "SIndicador.h"



static int TestSIndCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SIndCrear 01:\n" );

	SIndicador * p_indObj = SIndCrear ( 3 );
	if ( ES_NULO ( p_indObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( ( SIndValor ( p_indObj ) != 0 ) || ( SIndMax ( p_indObj ) != 3 ) )
		{
			printf( "Error caso 2: se esperaba valor 0 y max 3\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SIndEstaEnInicio ( p_indObj ) != 1 )
		{
			printf( "Error caso 3: el indicador deberia estar en el inicio\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SIndDestruir ( &p_indObj );

	if ( ES_VALIDO ( p_indObj ) )
	{
		printf( "Error caso 4: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Crear con max 0 debe fallar. */
	if ( ES_VALIDO ( SIndCrear ( 0 ) ) )
	{
		printf( "Error caso 5: se esperaba nulo al crear con max 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSIndMover01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SIndMover 01:\n" );

	SIndicador * p_indObj = SIndCrear ( 2 );
	if ( ES_VALIDO ( p_indObj ) )
	{
		if ( ( SIndIncrementar ( p_indObj ) != 1 ) || ( SIndValor ( p_indObj ) != 1 ) )
		{
			printf( "Error caso 1: incrementar deberia llevar el valor a 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SIndIncrementar ( p_indObj );
		if ( ( SIndValor ( p_indObj ) != 2 ) || ( SIndEstaEnFinal ( p_indObj ) != 1 ) )
		{
			printf( "Error caso 2: el valor deberia ser 2 y estar en el final\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* En el maximo, incrementar falla. */
		if ( SIndIncrementar ( p_indObj ) != 0 )
		{
			printf( "Error caso 3: incrementar en el maximo deberia fallar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* MoverA dentro y fuera de rango. */
		if ( ( SIndMoverA ( p_indObj, 1 ) != 1 ) || ( SIndValor ( p_indObj ) != 1 ) )
		{
			printf( "Error caso 4: mover a 1 deberia funcionar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SIndMoverA ( p_indObj, 5 ) != 0 )
		{
			printf( "Error caso 5: mover fuera del maximo deberia fallar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Inicio y final. */
		SIndInicio ( p_indObj );
		if ( SIndValor ( p_indObj ) != 0 )
		{
			printf( "Error caso 6: inicio deberia dejar el valor en 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SIndDecrementar ( p_indObj ) != 0 )
		{
			printf( "Error caso 7: decrementar en el inicio deberia fallar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el indicador\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SIndDestruir ( &p_indObj );
	return ( iRes );
}

static int TestSIndInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SIndInvalidos 01:\n" );

	if ( SIndIncrementar ( NULL ) != 0 )
	{
		printf( "Error caso 1: incrementar un indicador nulo deberia fallar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SIndValor ( NULL ) != 0 )
	{
		printf( "Error caso 2: el valor de un indicador nulo deberia ser 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SIndicador * p_indNulo = NULL;
	SIndDestruir ( &p_indNulo );
	return ( iRes );
}



int TestSIndicador ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SIndicador]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSIndCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSIndMover01 () == BOOL_VAL_CIERTO ) &&
			( TestSIndInvalidos01 () == BOOL_VAL_CIERTO ) )
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
