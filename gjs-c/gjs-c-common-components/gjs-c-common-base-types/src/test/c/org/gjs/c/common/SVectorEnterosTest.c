#include "Base.h"

#include "SVectorEnteros.h"



static int TestSVecEntCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SVecEntCrear 01:\n" );

	SVectorEnteros * p_vecObj = SVecEntCrear ( 4 );
	if ( ES_NULO ( p_vecObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SVecEntEsValido ( p_vecObj ) != 1 )
		{
			printf( "Error caso 2: el vector recien creado deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SVecEntNumElementos ( p_vecObj ) != 4 )
		{
			printf( "Error caso 3: se esperaban 4 elementos: %d\n", SVecEntNumElementos ( p_vecObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* Las posiciones sin asignar se leen como 0. */
		if ( SVecEntElemento ( p_vecObj, 0 ) != 0 )
		{
			printf( "Error caso 4: una posicion sin asignar deberia leerse como 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SVecEntDestruir ( &p_vecObj );

	if ( ES_VALIDO ( p_vecObj ) )
	{
		printf( "Error caso 5: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Crear con 0 elementos debe fallar. */
	if ( ES_VALIDO ( SVecEntCrear ( 0 ) ) )
	{
		printf( "Error caso 6: se esperaba nulo al crear con 0 elementos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSVecEntAsignar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SVecEntAsignar 01:\n" );

	SVectorEnteros * p_vecObj = SVecEntCrear ( 3 );
	if ( ES_VALIDO ( p_vecObj ) )
	{
		if ( SVecEntAsignar ( p_vecObj, 1, 42 ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al asignar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SVecEntElemento ( p_vecObj, 1 ) != 42 )
		{
			printf( "Error caso 2: se esperaba 42 en la posicion 1: %d\n", SVecEntElemento ( p_vecObj, 1 ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* Reasignar sobre una posicion ya usada. */
		if ( SVecEntAsignar ( p_vecObj, 1, 99 ) != 1 )
		{
			printf( "Error caso 3: se esperaba resultado 1 al reasignar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SVecEntElemento ( p_vecObj, 1 ) != 99 )
		{
			printf( "Error caso 4: se esperaba 99 tras reasignar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Asignar fuera de rango debe fallar. */
		if ( SVecEntAsignar ( p_vecObj, 3, 1 ) != 0 )
		{
			printf( "Error caso 5: asignar fuera de rango deberia fallar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el vector\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SVecEntDestruir ( &p_vecObj );
	return ( iRes );
}

static int TestSVecEntExiste01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SVecEntExiste 01:\n" );

	SVectorEnteros * p_vecObj = SVecEntCrear ( 3 );
	if ( ES_VALIDO ( p_vecObj ) )
	{
		/* Inicializar deja todas las posiciones a 0. */
		if ( SVecEntInicializar ( p_vecObj ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al inicializar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SVecEntAsignar ( p_vecObj, 0, 7 );
		SVecEntAsignar ( p_vecObj, 2, 9 );

		if ( SVecEntExiste ( p_vecObj, 9 ) != 1 )
		{
			printf( "Error caso 2: el 9 deberia existir\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SVecEntExiste ( p_vecObj, 100 ) != 0 )
		{
			printf( "Error caso 3: el 100 no deberia existir\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* La posicion 1 sigue a 0 tras inicializar. */
		if ( SVecEntExiste ( p_vecObj, 0 ) != 1 )
		{
			printf( "Error caso 4: el 0 deberia existir ( posicion 1 sin reasignar )\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el vector\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SVecEntDestruir ( &p_vecObj );
	return ( iRes );
}

static int TestSVecEntInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SVecEntInvalidos 01:\n" );

	if ( SVecEntEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: un vector nulo no deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SVecEntNumElementos ( NULL ) != 0 )
	{
		printf( "Error caso 2: el numero de elementos de un vector nulo deberia ser 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SVecEntAsignar ( NULL, 0, 1 ) != 0 )
	{
		printf( "Error caso 3: asignar en un vector nulo deberia fallar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SVectorEnteros * p_vecNulo = NULL;
	SVecEntDestruir ( &p_vecNulo );
	return ( iRes );
}



int TestSVectorEnteros ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SVectorEnteros]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSVecEntCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSVecEntAsignar01 () == BOOL_VAL_CIERTO ) &&
			( TestSVecEntExiste01 () == BOOL_VAL_CIERTO ) &&
			( TestSVecEntInvalidos01 () == BOOL_VAL_CIERTO ) )
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
