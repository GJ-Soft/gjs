#include "Base.h"

#include "SIndicador2D.h"



static int TestSInd2DCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SInd2DCrear 01:\n" );

	SIndicador2D * p_indObj = SInd2DCrear ( 2, 3 );
	if ( ES_NULO ( p_indObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( ( SInd2DValor1 ( p_indObj ) != 0 ) || ( SInd2DValor2 ( p_indObj ) != 0 ) )
		{
			printf( "Error caso 2: ambas dimensiones deberian empezar en 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SInd2DMax1 ( p_indObj ) != 2 ) || ( SInd2DMax2 ( p_indObj ) != 3 ) )
		{
			printf( "Error caso 3: se esperaban maximos 2 y 3\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SInd2DEsValido ( p_indObj ) != 1 ) || ( SInd2DEstaEnInicio ( p_indObj ) != 1 ) )
		{
			printf( "Error caso 4: deberia ser valido y estar en el inicio\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SInd2DDestruir ( &p_indObj );

	if ( ES_VALIDO ( p_indObj ) )
	{
		printf( "Error caso 5: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Crear con alguna dimension 0 debe fallar. */
	if ( ES_VALIDO ( SInd2DCrear ( 0, 3 ) ) )
	{
		printf( "Error caso 6: se esperaba nulo al crear con una dimension 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSInd2DMover01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SInd2DMover 01:\n" );

	SIndicador2D * p_indObj = SInd2DCrear ( 2, 3 );
	if ( ES_VALIDO ( p_indObj ) )
	{
		if ( ( SInd2DMoverA ( p_indObj, 1, 2 ) != 1 ) ||
			 ( SInd2DValor1 ( p_indObj ) != 1 ) || ( SInd2DValor2 ( p_indObj ) != 2 ) )
		{
			printf( "Error caso 1: mover a ( 1, 2 ) deberia funcionar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Fuera de rango en una dimension: no se mueve. */
		if ( SInd2DMoverA ( p_indObj, 3, 1 ) != 0 )
		{
			printf( "Error caso 2: mover con dimension 1 fuera de rango deberia fallar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SInd2DValor1 ( p_indObj ) != 1 ) || ( SInd2DValor2 ( p_indObj ) != 2 ) )
		{
			printf( "Error caso 3: un movimiento fallido no deberia cambiar el valor\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Incrementar ambas dimensiones hasta el final. */
		if ( SInd2DIncrementar ( p_indObj, 1, 1 ) != 1 )
		{
			printf( "Error caso 4: se esperaba resultado 1 al incrementar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SInd2DEstaEnFinal ( p_indObj ) != 1 )
		{
			printf( "Error caso 5: deberia estar en el final ( 2, 3 )\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* En el final, incrementar falla. */
		if ( SInd2DIncrementar ( p_indObj, 1, 1 ) != 0 )
		{
			printf( "Error caso 6: incrementar en el final deberia fallar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Inicio y final globales. */
		SInd2DInicio ( p_indObj );
		if ( SInd2DEstaEnInicio ( p_indObj ) != 1 )
		{
			printf( "Error caso 7: tras inicio deberia estar en el inicio\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el indicador\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SInd2DDestruir ( &p_indObj );
	return ( iRes );
}

static int TestSInd2DInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SInd2DInvalidos 01:\n" );

	if ( SInd2DEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: un indicador nulo no deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SInd2DValor1 ( NULL ) != 0 )
	{
		printf( "Error caso 2: el valor de un indicador nulo deberia ser 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SIndicador2D * p_indNulo = NULL;
	SInd2DDestruir ( &p_indNulo );
	return ( iRes );
}



int TestSIndicador2D ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SIndicador2D]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSInd2DCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSInd2DMover01 () == BOOL_VAL_CIERTO ) &&
			( TestSInd2DInvalidos01 () == BOOL_VAL_CIERTO ) )
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
