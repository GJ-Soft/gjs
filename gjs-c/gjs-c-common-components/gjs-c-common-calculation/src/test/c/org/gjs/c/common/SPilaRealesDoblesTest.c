#include "Base.h"

#include "SPilaRealesDobles.h"
#include "CalculoOperaciones.h"



static int TestSPilRealdCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SPilRealdCrear 01:\n" );

	SPilaRealesDobles * p_pilObj = SPilRealdCrear ();
	if ( ES_NULO ( p_pilObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SPilRealdEsValida ( p_pilObj ) != 1 )
		{
			printf( "Error caso 2: la pila recien creada deberia ser valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SPilRealdEstaVacia ( p_pilObj ) != 1 )
		{
			printf( "Error caso 3: la pila recien creada deberia estar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SPilRealdDestruir ( &p_pilObj );

	if ( ES_VALIDO ( p_pilObj ) )
	{
		printf( "Error caso 4: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSPilRealdApilar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SPilRealdApilar 01:\n" );

	SPilaRealesDobles * p_pilObj = SPilRealdCrear ();
	if ( ES_VALIDO ( p_pilObj ) )
	{
		SPilRealdApilar ( p_pilObj, 1.0 );
		SPilRealdApilar ( p_pilObj, 2.0 );
		SPilRealdApilar ( p_pilObj, 3.0 );

		if ( SPilRealdNumElementos ( p_pilObj ) != 3 )
		{
			printf( "Error caso 1: se esperaban 3 elementos: %d\n", SPilRealdNumElementos ( p_pilObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* La pila es LIFO: el primero es el ultimo apilado. */
		if ( MatEsIgual ( SPilRealdPrimero ( p_pilObj ), 3.0 ) != 1 )
		{
			printf( "Error caso 2: el primero deberia ser 3: %f\n", SPilRealdPrimero ( p_pilObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( MatEsIgual ( SPilRealdDesapilar ( p_pilObj ), 3.0 ) != 1 )
		{
			printf( "Error caso 3: al desapilar deberia devolver 3\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SPilRealdNumElementos ( p_pilObj ) != 2 )
		{
			printf( "Error caso 4: deberian quedar 2 elementos: %d\n", SPilRealdNumElementos ( p_pilObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( MatEsIgual ( SPilRealdPrimero ( p_pilObj ), 2.0 ) != 1 )
		{
			printf( "Error caso 5: el primero deberia ser ahora 2: %f\n", SPilRealdPrimero ( p_pilObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		SPilRealdVaciar ( p_pilObj );
		if ( SPilRealdEstaVacia ( p_pilObj ) != 1 )
		{
			printf( "Error caso 6: la pila deberia quedar vacia tras vaciarla\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la pila\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SPilRealdDestruir ( &p_pilObj );
	return ( iRes );
}

/* ApilarTodos mueve y ApilarTodosDup copia: el ultimo de la lista queda en la cima. */
static int TestSPilRealdApilarTodos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SPilRealdApilarTodos 01:\n" );

	SPilaRealesDobles * p_pilObj = SPilRealdCrear ();
	SListaRealesDobles * p_lisVal = SLisRealdCrear ();
	SListaRealesDobles * p_lisDup = SLisRealdCrear ();
	if ( ES_VALIDO ( p_pilObj ) && ES_VALIDO ( p_lisVal ) && ES_VALIDO ( p_lisDup ) )
	{
		SLisRealdInsertarAlFinal ( p_lisVal, 10.5 );
		SLisRealdInsertarAlFinal ( p_lisVal, 20.5 );
		SLisRealdInsertarAlFinal ( p_lisDup, 1.25 );
		SLisRealdInsertarAlFinal ( p_lisDup, 2.25 );
		if ( ( SPilRealdApilarTodos ( p_pilObj, p_lisVal ) != 1 ) || ( SPilRealdNumElementos ( p_pilObj ) != 2 ) ||
			 ( MatEsIgual ( SPilRealdPrimero ( p_pilObj ), 20.5 ) != 1 ) || ( SLisRealdNumElementos ( p_lisVal ) != 0 ) )
		{
			printf( "Error caso 1: se esperaban 2 apilados, el 20.5 en la cima y la lista vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SPilRealdApilarTodosDup ( p_pilObj, p_lisDup ) != 1 ) || ( SPilRealdNumElementos ( p_pilObj ) != 4 ) ||
			 ( MatEsIgual ( SPilRealdPrimero ( p_pilObj ), 2.25 ) != 1 ) || ( SLisRealdNumElementos ( p_lisDup ) != 2 ) )
		{
			printf( "Error caso 2: se esperaban 4 apilados, el 2.25 en la cima y la lista intacta\n" );
			iRes = BOOL_VAL_FALSO;
		}
		double dEsp [ 4 ] = { 2.25, 1.25, 20.5, 10.5 };
		int iPos = 0;
		while ( iPos < 4 )
		{
			if ( MatEsIgual ( SPilRealdDesapilar ( p_pilObj ), dEsp [ iPos ] ) != 1 )
			{
				printf( "Error caso 3: en la posicion %d se esperaba desapilar %g\n", iPos, dEsp [ iPos ] );
				iRes = BOOL_VAL_FALSO;
			}
			iPos = iPos + 1;
		}
		if ( ( SPilRealdApilarTodos ( p_pilObj, NULL ) != 0 ) || ( SPilRealdApilarTodos ( NULL, p_lisDup ) != 0 ) ||
			 ( SPilRealdApilarTodosDup ( p_pilObj, NULL ) != 0 ) || ( SPilRealdApilarTodosDup ( NULL, p_lisDup ) != 0 ) )
		{
			printf( "Error caso 4: con una pila o lista nula se esperaba 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear la pila y las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SPilRealdDestruir ( &p_pilObj );
	SLisRealdDestruir ( &p_lisVal );
	SLisRealdDestruir ( &p_lisDup );
	return ( iRes );
}



int TestSPilaRealesDobles ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SPilaRealesDobles]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSPilRealdCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSPilRealdApilar01 () == BOOL_VAL_CIERTO ) &&
			( TestSPilRealdApilarTodos01 () == BOOL_VAL_CIERTO ) )
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
