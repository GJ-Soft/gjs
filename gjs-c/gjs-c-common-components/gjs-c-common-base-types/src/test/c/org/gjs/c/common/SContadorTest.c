#include "Base.h"

#include "SContador.h"



static int TestSCntCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCntCrear 01:\n" );

	SContador * p_cntObj = SCntCrear ( 0, 3 );
	if ( ES_NULO ( p_cntObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( ( SCntMin ( p_cntObj ) != 0 ) || ( SCntMax ( p_cntObj ) != 3 ) )
		{
			printf( "Error caso 2: se esperaba min 0 y max 3\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* El contador nace en el minimo. */
		if ( SCntValor ( p_cntObj ) != 0 )
		{
			printf( "Error caso 3: el valor inicial deberia ser el minimo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCntEstaEnValorMin ( p_cntObj ) != 1 )
		{
			printf( "Error caso 4: deberia estar en el valor minimo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SCntDestruir ( &p_cntObj );

	if ( ES_VALIDO ( p_cntObj ) )
	{
		printf( "Error caso 5: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Crear con min > max debe fallar. */
	if ( ES_VALIDO ( SCntCrear ( 5, 2 ) ) )
	{
		printf( "Error caso 6: se esperaba nulo al crear con min > max\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSCntIncrementar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCntIncrementar 01:\n" );

	SContador * p_cntObj = SCntCrear ( 0, 2 );
	if ( ES_VALIDO ( p_cntObj ) )
	{
		if ( ( SCntIncrementar ( p_cntObj ) != 1 ) || ( SCntValor ( p_cntObj ) != 1 ) )
		{
			printf( "Error caso 1: incrementar deberia llevar el valor a 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SCntIncrementar ( p_cntObj );
		if ( ( SCntValor ( p_cntObj ) != 2 ) || ( SCntEstaEnValorMax ( p_cntObj ) != 1 ) )
		{
			printf( "Error caso 2: el valor deberia ser 2 y estar en el maximo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* En el maximo, incrementar falla y no pasa del limite. */
		if ( SCntIncrementar ( p_cntObj ) != 0 )
		{
			printf( "Error caso 3: incrementar en el maximo deberia fallar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCntValor ( p_cntObj ) != 2 )
		{
			printf( "Error caso 4: el valor no deberia pasar del maximo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Decrementar hasta el minimo. */
		SCntDecrementar ( p_cntObj );
		SCntDecrementar ( p_cntObj );
		if ( ( SCntValor ( p_cntObj ) != 0 ) || ( SCntDecrementar ( p_cntObj ) != 0 ) )
		{
			printf( "Error caso 5: decrementar en el minimo deberia fallar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Iniciar vuelve al minimo. */
		SCntIncrementar ( p_cntObj );
		SCntIniciar ( p_cntObj );
		if ( SCntValor ( p_cntObj ) != 0 )
		{
			printf( "Error caso 6: iniciar deberia devolver el valor al minimo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el contador\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCntDestruir ( &p_cntObj );
	return ( iRes );
}

static int TestSCntInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCntInvalidos 01:\n" );

	if ( SCntIncrementar ( NULL ) != 0 )
	{
		printf( "Error caso 1: incrementar un contador nulo deberia fallar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SCntValor ( NULL ) != 0 )
	{
		printf( "Error caso 2: el valor de un contador nulo deberia ser 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SContador * p_cntNulo = NULL;
	SCntDestruir ( &p_cntNulo );
	return ( iRes );
}



int TestSContador ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SContador]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSCntCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSCntIncrementar01 () == BOOL_VAL_CIERTO ) &&
			( TestSCntInvalidos01 () == BOOL_VAL_CIERTO ) )
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
