#include "Base.h"

#include "SContadorCiclos.h"



static int TestSConCicCicloVida01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SConCicCicloVida 01:\n" );
	SContadorCiclos * p_concicObj = SConCicCrear ();
	if ( ES_NULO ( p_concicObj ) )
	{
		printf( "Error caso 0: no se pudo crear el contador\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SConCicEstaContando ( p_concicObj ) != 0 )
		{
			printf( "Error caso 1: un contador recien creado no debe estar contando\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SConCicIniciar ( p_concicObj );
		if ( SConCicEstaContando ( p_concicObj ) != 1 )
		{
			printf( "Error caso 2: tras iniciar debe estar contando\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Se queman algunos ciclos para que el contador avance. */
		volatile unsigned long ulSuma = 0;
		for ( unsigned long ul = 0; ul < 1000000; ul = ul + 1 )
		{
			ulSuma = ulSuma + ul;
		}
		uint64_t ui64Valor = SConCicValor ( p_concicObj );
		if ( ui64Valor == 0 )
		{
			printf( "Error caso 3: se esperaba un valor de ciclos > 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		uint64_t ui64Parada = SConCicParar ( p_concicObj );
		if ( ui64Parada < ui64Valor )
		{
			printf( "Error caso 4: el valor al parar no debe ser menor que el intermedio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SConCicEstaContando ( p_concicObj ) != 0 )
		{
			printf( "Error caso 5: tras parar no debe estar contando\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SConCicDestruir ( &p_concicObj );
	return ( iRes );
}

static int TestSConCicNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SConCicNulo 01:\n" );
	if ( SConCicValor ( NULL ) != 0 )
	{
		printf( "Error caso 1: se esperaba 0 en el valor de un contador nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SConCicEstaContando ( NULL ) != 0 )
	{
		printf( "Error caso 2: un contador nulo no debe estar contando\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SConCicParar ( NULL ) != 0 )
	{
		printf( "Error caso 3: se esperaba 0 al parar un contador nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



int TestSContadorCiclos ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SContadorCiclos]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSConCicCicloVida01 () == BOOL_VAL_CIERTO ) &&
			( TestSConCicNulo01 () == BOOL_VAL_CIERTO ) )
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
