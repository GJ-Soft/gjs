#include "Base.h"

#include "SCola.h"



static SElemento * CrearElementoEntero ( int iValor )
{
	SElemento * p_elmObj = SElmCrearEntero ();
	if ( ES_VALIDO ( p_elmObj ) )
	{
		SElmEscribirEntero ( p_elmObj, iValor );
	}
	return ( p_elmObj );
}



static int TestSColCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SColCrear 01:\n" );

	SCola * p_colObj = SColCrear ();
	if ( ES_NULO ( p_colObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SColEsValida ( p_colObj ) != 1 )
		{
			printf( "Error caso 2: la cola recien creada deberia ser valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SColEstaVacia ( p_colObj ) != 1 )
		{
			printf( "Error caso 3: la cola recien creada deberia estar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SColNumElementos ( p_colObj ) != 0 )
		{
			printf( "Error caso 4: se esperaban 0 elementos\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SColDestruir ( &p_colObj );

	if ( ES_VALIDO ( p_colObj ) )
	{
		printf( "Error caso 5: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSColEncolar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SColEncolar 01:\n" );

	SCola * p_colObj = SColCrear ();
	if ( ES_VALIDO ( p_colObj ) )
	{
		SColEncolar ( p_colObj, CrearElementoEntero ( 10 ) );
		SColEncolar ( p_colObj, CrearElementoEntero ( 20 ) );
		SColEncolar ( p_colObj, CrearElementoEntero ( 30 ) );

		if ( SColNumElementos ( p_colObj ) != 3 )
		{
			printf( "Error caso 1: se esperaban 3 elementos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Orden FIFO: el primero es el mas antiguo, el ultimo el mas reciente. */
		if ( SElmEntero ( SColPrimero ( p_colObj ) ) != 10 )
		{
			printf( "Error caso 2: el primero deberia ser el 10\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SElmEntero ( SColUltimo ( p_colObj ) ) != 30 )
		{
			printf( "Error caso 3: el ultimo deberia ser el 30\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SElmEntero ( SColElemento ( p_colObj, 1 ) ) != 20 )
		{
			printf( "Error caso 4: el elemento 1 deberia ser el 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Al eliminar el primero, sale el mas antiguo. */
		SColEliminarPrimero ( p_colObj );
		if ( SElmEntero ( SColPrimero ( p_colObj ) ) != 20 )
		{
			printf( "Error caso 5: tras eliminar el primero, deberia quedar el 20 al frente\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la cola\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SColDestruir ( &p_colObj );
	return ( iRes );
}

static int TestSColEliminarUltimo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SColEliminarUltimo 01:\n" );

	SCola * p_colObj = SColCrear ();
	if ( ES_VALIDO ( p_colObj ) )
	{
		SColEncolar ( p_colObj, CrearElementoEntero ( 10 ) );
		SColEncolar ( p_colObj, CrearElementoEntero ( 20 ) );
		SColEncolar ( p_colObj, CrearElementoEntero ( 30 ) );

		if ( SColEliminarUltimo ( p_colObj ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al eliminar el ultimo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SColNumElementos ( p_colObj ) != 2 )
		{
			printf( "Error caso 2: se esperaban 2 elementos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SElmEntero ( SColUltimo ( p_colObj ) ) != 20 )
		{
			printf( "Error caso 3: el nuevo ultimo deberia ser el 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la cola\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SColDestruir ( &p_colObj );
	return ( iRes );
}

static int TestSColDesencolar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SColDesencolar 01:\n" );

	SCola * p_colObj = SColCrear ();
	if ( ES_VALIDO ( p_colObj ) )
	{
		SColEncolar ( p_colObj, CrearElementoEntero ( 10 ) );
		SColEncolar ( p_colObj, CrearElementoEntero ( 20 ) );

		/* Desencolar reduce el numero de elementos. */
		SColDesencolar ( p_colObj );
		if ( SColNumElementos ( p_colObj ) != 1 )
		{
			printf( "Error caso 1: se esperaba 1 elemento tras desencolar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SColDesencolar ( p_colObj );
		if ( SColEstaVacia ( p_colObj ) != 1 )
		{
			printf( "Error caso 2: la cola deberia quedar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Desencolar de una cola vacia devuelve nulo. */
		if ( ES_VALIDO ( SColDesencolar ( p_colObj ) ) )
		{
			printf( "Error caso 3: desencolar de una cola vacia deberia dar nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la cola\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SColDestruir ( &p_colObj );
	return ( iRes );
}

static int TestSColVaciar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SColVaciar 01:\n" );

	SCola * p_colObj = SColCrear ();
	if ( ES_VALIDO ( p_colObj ) )
	{
		SColEncolar ( p_colObj, CrearElementoEntero ( 10 ) );
		SColEncolar ( p_colObj, CrearElementoEntero ( 20 ) );

		if ( SColVaciar ( p_colObj ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al vaciar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SColNumElementos ( p_colObj ) != 0 )
		{
			printf( "Error caso 2: se esperaban 0 elementos tras vaciar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SColEncolar ( p_colObj, CrearElementoEntero ( 99 ) ) != 1 )
		{
			printf( "Error caso 3: deberia poder encolarse tras vaciar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la cola\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SColDestruir ( &p_colObj );
	return ( iRes );
}

static int TestSColInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SColInvalidos 01:\n" );

	if ( SColEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: una cola nula no deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SColEstaVacia ( NULL ) != 1 )
	{
		printf( "Error caso 2: una cola nula deberia considerarse vacia\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SColEncolar ( NULL, NULL ) != 0 )
	{
		printf( "Error caso 3: encolar en una cola nula deberia fallar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCola * p_colNula = NULL;
	SColDestruir ( &p_colNula );
	return ( iRes );
}



int TestSCola ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SCola]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSColCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSColEncolar01 () == BOOL_VAL_CIERTO ) &&
			( TestSColEliminarUltimo01 () == BOOL_VAL_CIERTO ) &&
			( TestSColDesencolar01 () == BOOL_VAL_CIERTO ) &&
			( TestSColVaciar01 () == BOOL_VAL_CIERTO ) &&
			( TestSColInvalidos01 () == BOOL_VAL_CIERTO ) )
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
