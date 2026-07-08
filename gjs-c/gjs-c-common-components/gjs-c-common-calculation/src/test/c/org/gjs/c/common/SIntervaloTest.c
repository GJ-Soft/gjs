#include "Base.h"

#include "SIntervalo.h"
#include "CalculoOperaciones.h"



static int TestSIntvCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SIntvCrear 01:\n" );

	SIntervalo * p_intvObj = SIntvCrear ( 0.0, 10.0 );
	if ( ES_NULO ( p_intvObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SIntvEsValido ( p_intvObj ) != 1 )
		{
			printf( "Error caso 2: el intervalo recien creado deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( MatEsIgual ( SIntvMin ( p_intvObj ), 0.0 ) != 1 )
		{
			printf( "Error caso 3: el minimo deberia ser 0: %f\n", SIntvMin ( p_intvObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( MatEsIgual ( SIntvMax ( p_intvObj ), 10.0 ) != 1 )
		{
			printf( "Error caso 4: el maximo deberia ser 10: %f\n", SIntvMax ( p_intvObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( MatEsIgual ( SIntvLongitud ( p_intvObj ), 10.0 ) != 1 )
		{
			printf( "Error caso 5: la longitud deberia ser 10: %f\n", SIntvLongitud ( p_intvObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* Sin divisiones hay un unico subintervalo. */
		if ( SIntvNumSubintervalos ( p_intvObj ) != 1 )
		{
			printf( "Error caso 6: deberia haber 1 subintervalo: %d\n", SIntvNumSubintervalos ( p_intvObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SIntvDestruir ( &p_intvObj );

	if ( ES_VALIDO ( p_intvObj ) )
	{
		printf( "Error caso 7: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Un intervalo con minimo mayor que el maximo no puede crearse. */
	SIntervalo * p_intvMal = SIntvCrear ( 10.0, 0.0 );
	if ( ES_VALIDO ( p_intvMal ) )
	{
		printf( "Error caso 8: no deberia crearse un intervalo con min > max\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SIntvDestruir ( &p_intvMal );
	return ( iRes );
}

static int TestSIntvDividir01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SIntvDividir 01:\n" );

	SIntervalo * p_intvObj = SIntvCrear ( 0.0, 10.0 );
	if ( ES_VALIDO ( p_intvObj ) )
	{
		if ( SIntvDividirEquidistantemente ( p_intvObj, 3 ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al dividir\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SIntvNumSubintervalos ( p_intvObj ) != 3 )
		{
			printf( "Error caso 2: deberia haber 3 subintervalos: %d\n", SIntvNumSubintervalos ( p_intvObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SIntvNumDivisiones ( p_intvObj ) != 2 )
		{
			printf( "Error caso 3: deberia haber 2 divisiones: %d\n", SIntvNumDivisiones ( p_intvObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* El primer subintervalo empieza en el minimo y el ultimo acaba en el maximo. */
		if ( MatEsIgual ( SIntvSubintervaloMin ( p_intvObj, 0 ), 0.0 ) != 1 )
		{
			printf( "Error caso 4: el primer subintervalo deberia empezar en 0: %f\n", SIntvSubintervaloMin ( p_intvObj, 0 ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( MatEsIgual ( SIntvSubintervaloMax ( p_intvObj, 2 ), 10.0 ) != 1 )
		{
			printf( "Error caso 5: el ultimo subintervalo deberia acabar en 10: %f\n", SIntvSubintervaloMax ( p_intvObj, 2 ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el intervalo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SIntvDestruir ( &p_intvObj );
	return ( iRes );
}

static int TestSIntvEstablecer01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SIntvEstablecer 01:\n" );

	SIntervalo * p_intvObj = SIntvCrear ( 0.0, 10.0 );
	if ( ES_VALIDO ( p_intvObj ) )
	{
		SIntvEstablecerMin ( p_intvObj, 2.0 );
		SIntvEstablecerMax ( p_intvObj, 8.0 );
		if ( MatEsIgual ( SIntvLongitud ( p_intvObj ), 6.0 ) != 1 )
		{
			printf( "Error caso 1: la longitud deberia ser 6: %f\n", SIntvLongitud ( p_intvObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el intervalo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SIntvDestruir ( &p_intvObj );
	return ( iRes );
}



int TestSIntervalo ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SIntervalo]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSIntvCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSIntvDividir01 () == BOOL_VAL_CIERTO ) &&
			( TestSIntvEstablecer01 () == BOOL_VAL_CIERTO ) )
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
