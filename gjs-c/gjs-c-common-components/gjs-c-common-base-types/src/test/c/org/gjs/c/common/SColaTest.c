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


/* Mueve los elementos al final de la cola: salen en el orden de la lista. */
static int TestSColEncolarTodos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SColEncolarTodos 01:\n" );

	SCola * p_colObj = SColCrear ();
	SLista * p_lisVal = SLisCrear ();
	SLista * p_lisVacia = SLisCrear ();
	if ( ES_VALIDO ( p_colObj ) && ES_VALIDO ( p_lisVal ) && ES_VALIDO ( p_lisVacia ) )
	{
		SColEncolar ( p_colObj, CrearElementoEntero ( 5 ) );
		SLisInsertarAlFinal ( p_lisVal, CrearElementoEntero ( 10 ) );
		SLisInsertarAlFinal ( p_lisVal, CrearElementoEntero ( 20 ) );
		SLisInsertarAlFinal ( p_lisVal, CrearElementoEntero ( 30 ) );
		SElemento * p_elm10 = SLisElemento ( p_lisVal, 0 );
		if ( SColEncolarTodos ( p_colObj, p_lisVal ) != 1 )
		{
			printf( "Error caso 1: se esperaba 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SColNumElementos ( p_colObj ) != 4 ) || ( SLisNumElementos ( p_lisVal ) != 0 ) ||
			 ( SColElemento ( p_colObj, 1 ) != p_elm10 ) )
		{
			printf( "Error caso 2: se esperaban 4 encolados, el mismo 10 detras del 5 y la lista vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		int iEsp [ 4 ] = { 5, 10, 20, 30 };
		int iPos = 0;
		while ( iPos < 4 )
		{
			SElemento * p_elmObj = SColDesencolar ( p_colObj );
			if ( ES_NULO ( p_elmObj ) || ( SElmEntero ( p_elmObj ) != iEsp [ iPos ] ) )
			{
				printf( "Error caso 3: en la posicion %d se esperaba desencolar %d\n", iPos, iEsp [ iPos ] );
				iRes = BOOL_VAL_FALSO;
			}
			SElmDestruir ( &p_elmObj );
			iPos = iPos + 1;
		}
		if ( ( SColEncolarTodos ( p_colObj, p_lisVacia ) != 1 ) || ( SColEstaVacia ( p_colObj ) != 1 ) )
		{
			printf( "Error caso 4: con una lista vacia se esperaba 1 sin cambios\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SColEncolarTodos ( p_colObj, NULL ) != 0 ) || ( SColEncolarTodos ( NULL, p_lisVacia ) != 0 ) )
		{
			printf( "Error caso 5: con una cola o lista nula se esperaba 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear la cola y las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SColDestruir ( &p_colObj );
	SLisDestruir ( &p_lisVal );
	SLisDestruir ( &p_lisVacia );
	return ( iRes );
}

/* Encola copias: la lista y su cursor no cambian. Con tamano 0 un elemento no
   es valido y SElmDuplicar falla: se para con ERR_COPIA_OBJETO. */
static int TestSColEncolarTodosDup01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SColEncolarTodosDup 01:\n" );

	SCola * p_colObj = SColCrear ();
	SCola * p_colFalla = SColCrear ();
	SLista * p_lisVal = SLisCrear ();
	SLista * p_lisFalla = SLisCrear ();
	SElemento * p_elmMalo = CrearElementoEntero ( 20 );
	if ( ES_VALIDO ( p_colObj ) && ES_VALIDO ( p_colFalla ) && ES_VALIDO ( p_lisVal ) &&
		 ES_VALIDO ( p_lisFalla ) && ES_VALIDO ( p_elmMalo ) )
	{
		SLisInsertarAlFinal ( p_lisVal, CrearElementoEntero ( 10 ) );
		SLisInsertarAlFinal ( p_lisVal, CrearElementoEntero ( 20 ) );
		SLisMoverA ( p_lisVal, 1 );
		if ( SColEncolarTodosDup ( p_colObj, p_lisVal ) != 1 )
		{
			printf( "Error caso 1: se esperaba 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SElemento * p_elmPrimero = SColPrimero ( p_colObj );
		if ( ( SColNumElementos ( p_colObj ) != 2 ) || ES_NULO ( p_elmPrimero ) ||
			 ( SElmEntero ( p_elmPrimero ) != 10 ) || ( p_elmPrimero == SLisElemento ( p_lisVal, 0 ) ) )
		{
			printf( "Error caso 2: se esperaba una copia del 10 al frente\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisNumElementos ( p_lisVal ) != 2 ) || ( SLisPosicion ( p_lisVal ) != 1 ) )
		{
			printf( "Error caso 3: la lista y su cursor no deberian cambiar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_elmMalo->p_blqDatos->iTam = 0;
		SLisInsertarAlFinal ( p_lisFalla, CrearElementoEntero ( 10 ) );
		SLisInsertarAlFinal ( p_lisFalla, p_elmMalo );
		ErrLimpiar ();
		if ( ( SColEncolarTodosDup ( p_colFalla, p_lisFalla ) != 0 ) || ( ErrCodigo () != ERR_COPIA_OBJETO ) ||
			 ( SColNumElementos ( p_colFalla ) != 1 ) )
		{
			printf( "Error caso 4: se esperaba 0 con ERR_COPIA_OBJETO y solo el 10 encolado\n" );
			iRes = BOOL_VAL_FALSO;
		}
		ErrLimpiar ();
		/* Se repara para poder destruirlo. */
		p_elmMalo->p_blqDatos->iTam = sizeof ( int );
		if ( ( SColEncolarTodosDup ( p_colObj, NULL ) != 0 ) || ( SColEncolarTodosDup ( NULL, p_lisVal ) != 0 ) )
		{
			printf( "Error caso 5: con una cola o lista nula se esperaba 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las colas y las listas\n" );
		iRes = BOOL_VAL_FALSO;
		SElmDestruir ( &p_elmMalo );
	}
	SColDestruir ( &p_colObj );
	SColDestruir ( &p_colFalla );
	SLisDestruir ( &p_lisVal );
	SLisDestruir ( &p_lisFalla );
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
			( TestSColInvalidos01 () == BOOL_VAL_CIERTO ) &&
			( TestSColEncolarTodos01 () == BOOL_VAL_CIERTO ) &&
			( TestSColEncolarTodosDup01 () == BOOL_VAL_CIERTO ) )
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
