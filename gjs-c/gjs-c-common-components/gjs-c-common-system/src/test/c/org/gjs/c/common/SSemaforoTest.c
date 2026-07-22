#include "Base.h"

#include "SSemaforo.h"



static int TestSSemCicloVida01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSemCicloVida 01:\n" );
	/* Se usa un semaforo anonimo (sin nombre), que se crea de inmediato con el
	   valor maximo indicado. */
	SSemaforo * p_semObj = SSemCrearExt ( "", 2 );
	if ( ES_NULO ( p_semObj ) )
	{
		printf( "Error caso 0: no se pudo crear el semaforo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SSemEsValido ( p_semObj ) != 1 )
		{
			printf( "Error caso 1: se esperaba un semaforo valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SSemEstaCreado ( p_semObj ) != 1 )
		{
			printf( "Error caso 2: el semaforo anonimo deberia estar creado\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SSemValorMaximo ( p_semObj ) != 2 )
		{
			printf( "Error caso 3: se esperaba valor maximo 2: %ld\n", SSemValorMaximo ( p_semObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SSemDadoDeAlta ( p_semObj ) != 0 )
		{
			printf( "Error caso 4: un semaforo recien creado no debe estar dado de alta\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SSemAlta ( p_semObj, 0 ) != 1 )
		{
			printf( "Error caso 5: se esperaba dar de alta el semaforo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SSemDadoDeAlta ( p_semObj ) != 1 )
		{
			printf( "Error caso 6: tras el alta debe constar dado de alta\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SSemBaja ( p_semObj ) != 1 )
		{
			printf( "Error caso 7: se esperaba dar de baja el semaforo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SSemDadoDeAlta ( p_semObj ) != 0 )
		{
			printf( "Error caso 8: tras la baja no debe constar dado de alta\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SSemDestruir ( &p_semObj );
	return ( iRes );
}

static int TestSSemCicloVida02 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSemCicloVida 02:\n" );
	SSemaforo * p_semObj = SSemCrear ( "gjs_test_sem" );
	if ( ES_NULO ( p_semObj ) )
	{
		printf( "Error caso 0: no se pudo crear el semaforo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SSemInicializar ( p_semObj ) != 1 )
		{
			printf( "Error caso 1: no se pudo inicializar el semaforo con nombre\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SSemEsValido ( p_semObj ) != 1 )
		{
			printf( "Error caso 2: se esperaba un semaforo valido tras inicializar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SSemEstaCreado ( p_semObj ) != 1 )
		{
			printf( "Error caso 3: el semaforo deberia constar creado\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_NULO ( SSemNombre ( p_semObj ) ) )
		{
			printf( "Error caso 4: se esperaba nombre de semaforo no nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SSemDestruir ( &p_semObj );
	return ( iRes );
}


static int TestSSemNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSemNulo 01:\n" );
	if ( SSemEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: un semaforo nulo no debe ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SSemAlta ( NULL, 0 ) != 0 )
	{
		printf( "Error caso 2: se esperaba 0 al dar de alta un semaforo nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SSemDadoDeAlta ( NULL ) != 0 )
	{
		printf( "Error caso 3: un semaforo nulo no debe estar dado de alta\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



int TestSSemaforo ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SSemaforo]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSSemCicloVida01 () == BOOL_VAL_CIERTO ) &&
			( TestSSemCicloVida02 () == BOOL_VAL_CIERTO ) &&
			( TestSSemNulo01 () == BOOL_VAL_CIERTO ) )
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
