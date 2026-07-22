#include "Base.h"

#include "STemporizador.h"



static int TestSTmpIntervalo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test STmpIntervalo 01:\n" );
	STemporizador * p_tmpObj = STmpCrear ( 100 );
	if ( ES_NULO ( p_tmpObj ) )
	{
		printf( "Error caso 0: no se pudo crear el temporizador\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( STmpIntervalo ( p_tmpObj ) != 100 )
		{
			printf( "Error caso 1: se esperaba intervalo 100: %d\n", STmpIntervalo ( p_tmpObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		STmpEstablecerIntervalo ( p_tmpObj, 50 );
		if ( STmpIntervalo ( p_tmpObj ) != 50 )
		{
			printf( "Error caso 2: se esperaba intervalo 50: %d\n", STmpIntervalo ( p_tmpObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* Un intervalo no positivo se normaliza a 0. */
		STmpEstablecerIntervalo ( p_tmpObj, -7 );
		if ( STmpIntervalo ( p_tmpObj ) != 0 )
		{
			printf( "Error caso 3: se esperaba intervalo 0 tras valor negativo: %d\n", STmpIntervalo ( p_tmpObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* Una espera breve no debe fallar. */
		STmpEsperar ( p_tmpObj, 1 );
		if ( STmpIntervalo ( p_tmpObj ) != 1 )
		{
			printf( "Error caso 4: STmpEsperar debe fijar el intervalo a 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	STmpDestruir ( &p_tmpObj );
	return ( iRes );
}

static int TestSTmpNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test STmpNulo 01:\n" );
	if ( STmpIntervalo ( NULL ) != 0 )
	{
		printf( "Error caso 1: se esperaba 0 en el intervalo de un temporizador nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



int TestSTemporizador ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test STemporizador]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSTmpIntervalo01 () == BOOL_VAL_CIERTO ) &&
			( TestSTmpNulo01 () == BOOL_VAL_CIERTO ) )
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
