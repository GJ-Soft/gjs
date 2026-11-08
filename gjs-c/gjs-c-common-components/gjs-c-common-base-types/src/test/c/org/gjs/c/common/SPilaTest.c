#include "Base.h"

#include "SPila.h"



static SElemento * CrearElementoEntero ( int iValor )
{
	SElemento * p_elmObj = SElmCrearEntero ();
	if ( ES_VALIDO ( p_elmObj ) )
	{
		SElmEscribirEntero ( p_elmObj, iValor );
	}
	return ( p_elmObj );
}



static int TestSPilCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SPilCrear 01:\n" );

	SPila * p_pilObj = SPilCrear ();
	if ( ES_NULO ( p_pilObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SPilEsValida ( p_pilObj ) != 1 )
		{
			printf( "Error caso 2: la pila recien creada deberia ser valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SPilEstaVacia ( p_pilObj ) != 1 )
		{
			printf( "Error caso 3: la pila recien creada deberia estar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SPilNumElementos ( p_pilObj ) != 0 )
		{
			printf( "Error caso 4: se esperaban 0 elementos\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SPilDestruir ( &p_pilObj );

	if ( ES_VALIDO ( p_pilObj ) )
	{
		printf( "Error caso 5: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSPilApilar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SPilApilar 01:\n" );

	SPila * p_pilObj = SPilCrear ();
	if ( ES_VALIDO ( p_pilObj ) )
	{
		SPilApilar ( p_pilObj, CrearElementoEntero ( 10 ) );
		SPilApilar ( p_pilObj, CrearElementoEntero ( 20 ) );
		SPilApilar ( p_pilObj, CrearElementoEntero ( 30 ) );

		if ( SPilNumElementos ( p_pilObj ) != 3 )
		{
			printf( "Error caso 1: se esperaban 3 elementos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Orden LIFO: la cima es el ultimo apilado. */
		if ( SElmEntero ( SPilPrimero ( p_pilObj ) ) != 30 )
		{
			printf( "Error caso 2: la cima deberia ser el 30\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SPilEliminarPrimero ( p_pilObj );
		if ( SElmEntero ( SPilPrimero ( p_pilObj ) ) != 20 )
		{
			printf( "Error caso 3: tras eliminar, la cima deberia ser el 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SPilEliminarPrimero ( p_pilObj );
		if ( SElmEntero ( SPilPrimero ( p_pilObj ) ) != 10 )
		{
			printf( "Error caso 4: tras eliminar, la cima deberia ser el 10\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la pila\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SPilDestruir ( &p_pilObj );
	return ( iRes );
}

static int TestSPilDesapilar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SPilDesapilar 01:\n" );

	SPila * p_pilObj = SPilCrear ();
	if ( ES_VALIDO ( p_pilObj ) )
	{
		SPilApilar ( p_pilObj, CrearElementoEntero ( 10 ) );
		SPilApilar ( p_pilObj, CrearElementoEntero ( 20 ) );

		/* Desapilar reduce el numero de elementos. */
		SPilDesapilar ( p_pilObj );
		if ( SPilNumElementos ( p_pilObj ) != 1 )
		{
			printf( "Error caso 1: se esperaba 1 elemento tras desapilar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SPilDesapilar ( p_pilObj );
		if ( SPilEstaVacia ( p_pilObj ) != 1 )
		{
			printf( "Error caso 2: la pila deberia quedar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Desapilar de una pila vacia devuelve nulo. */
		if ( ES_VALIDO ( SPilDesapilar ( p_pilObj ) ) )
		{
			printf( "Error caso 3: desapilar de una pila vacia deberia dar nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la pila\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SPilDestruir ( &p_pilObj );
	return ( iRes );
}

static int TestSPilVaciar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SPilVaciar 01:\n" );

	SPila * p_pilObj = SPilCrear ();
	if ( ES_VALIDO ( p_pilObj ) )
	{
		SPilApilar ( p_pilObj, CrearElementoEntero ( 10 ) );
		SPilApilar ( p_pilObj, CrearElementoEntero ( 20 ) );

		if ( SPilVaciar ( p_pilObj ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al vaciar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SPilNumElementos ( p_pilObj ) != 0 )
		{
			printf( "Error caso 2: se esperaban 0 elementos tras vaciar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Debe seguir siendo reutilizable. */
		if ( SPilApilar ( p_pilObj, CrearElementoEntero ( 99 ) ) != 1 )
		{
			printf( "Error caso 3: deberia poder apilarse tras vaciar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la pila\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SPilDestruir ( &p_pilObj );
	return ( iRes );
}

static int TestSPilInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SPilInvalidos 01:\n" );

	if ( SPilEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: una pila nula no deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SPilEstaVacia ( NULL ) != 1 )
	{
		printf( "Error caso 2: una pila nula deberia considerarse vacia\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SPilApilar ( NULL, NULL ) != 0 )
	{
		printf( "Error caso 3: apilar en una pila nula deberia fallar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SPila * p_pilNula = NULL;
	SPilDestruir ( &p_pilNula );
	return ( iRes );
}


/* La cima de una pila vacia es nula y deja ERR_PILA_VACIA. */
static int TestSPilVacia01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SPilVacia 01:\n" );

	SPila * p_pilObj = SPilCrear ();
	if ( ES_VALIDO ( p_pilObj ) )
	{
		ErrLimpiar ();
		if ( ES_VALIDO ( SPilPrimero ( p_pilObj ) ) || ( ErrCodigo () != ERR_PILA_VACIA ) )
		{
			printf( "Error caso 1: la cima de una vacia deberia ser nula con ERR_PILA_VACIA\n" );
			iRes = BOOL_VAL_FALSO;
		}
		ErrLimpiar ();
		if ( ES_VALIDO ( SPilDesapilar ( p_pilObj ) ) || ( ErrCodigo () != ERR_PILA_VACIA ) )
		{
			printf( "Error caso 2: desapilar una vacia deberia dar nulo con ERR_PILA_VACIA\n" );
			iRes = BOOL_VAL_FALSO;
		}
		ErrLimpiar ();
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la pila\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SPilDestruir ( &p_pilObj );
	return ( iRes );
}

/* Mueve los elementos: el ultimo de la lista queda en la cima. */
static int TestSPilApilarTodos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SPilApilarTodos 01:\n" );

	SPila * p_pilObj = SPilCrear ();
	SLista * p_lisVal = SLisCrear ();
	SLista * p_lisVacia = SLisCrear ();
	if ( ES_VALIDO ( p_pilObj ) && ES_VALIDO ( p_lisVal ) && ES_VALIDO ( p_lisVacia ) )
	{
		SLisInsertarAlFinal ( p_lisVal, CrearElementoEntero ( 10 ) );
		SLisInsertarAlFinal ( p_lisVal, CrearElementoEntero ( 20 ) );
		SLisInsertarAlFinal ( p_lisVal, CrearElementoEntero ( 30 ) );
		SElemento * p_elm30 = SLisElemento ( p_lisVal, 2 );
		if ( SPilApilarTodos ( p_pilObj, p_lisVal ) != 1 )
		{
			printf( "Error caso 1: se esperaba 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SPilNumElementos ( p_pilObj ) != 3 ) || ( SLisNumElementos ( p_lisVal ) != 0 ) ||
			 ( SPilPrimero ( p_pilObj ) != p_elm30 ) )
		{
			printf( "Error caso 2: se esperaban 3 apilados, el 30 en la cima y la lista vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		int iEsp [ 3 ] = { 30, 20, 10 };
		int iPos = 0;
		while ( iPos < 3 )
		{
			SElemento * p_elmObj = SPilDesapilar ( p_pilObj );
			if ( ES_NULO ( p_elmObj ) || ( SElmEntero ( p_elmObj ) != iEsp [ iPos ] ) )
			{
				printf( "Error caso 3: en la posicion %d se esperaba desapilar %d\n", iPos, iEsp [ iPos ] );
				iRes = BOOL_VAL_FALSO;
			}
			SElmDestruir ( &p_elmObj );
			iPos = iPos + 1;
		}
		if ( ( SPilApilarTodos ( p_pilObj, p_lisVacia ) != 1 ) || ( SPilEstaVacia ( p_pilObj ) != 1 ) )
		{
			printf( "Error caso 4: con una lista vacia se esperaba 1 sin cambios\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SPilApilarTodos ( p_pilObj, NULL ) != 0 ) || ( SPilApilarTodos ( NULL, p_lisVacia ) != 0 ) )
		{
			printf( "Error caso 5: con una pila o lista nula se esperaba 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear la pila y las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SPilDestruir ( &p_pilObj );
	SLisDestruir ( &p_lisVal );
	SLisDestruir ( &p_lisVacia );
	return ( iRes );
}

/* Apila copias: la lista y su cursor no cambian. Con tamano 0 un elemento no
   es valido y SElmDuplicar falla: se para con ERR_COPIA_OBJETO. */
static int TestSPilApilarTodosDup01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SPilApilarTodosDup 01:\n" );

	SPila * p_pilObj = SPilCrear ();
	SPila * p_pilFalla = SPilCrear ();
	SLista * p_lisVal = SLisCrear ();
	SLista * p_lisFalla = SLisCrear ();
	SElemento * p_elmMalo = CrearElementoEntero ( 20 );
	if ( ES_VALIDO ( p_pilObj ) && ES_VALIDO ( p_pilFalla ) && ES_VALIDO ( p_lisVal ) &&
		 ES_VALIDO ( p_lisFalla ) && ES_VALIDO ( p_elmMalo ) )
	{
		SLisInsertarAlFinal ( p_lisVal, CrearElementoEntero ( 10 ) );
		SLisInsertarAlFinal ( p_lisVal, CrearElementoEntero ( 20 ) );
		SLisMoverA ( p_lisVal, 1 );
		if ( SPilApilarTodosDup ( p_pilObj, p_lisVal ) != 1 )
		{
			printf( "Error caso 1: se esperaba 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SElemento * p_elmCima = SPilPrimero ( p_pilObj );
		if ( ( SPilNumElementos ( p_pilObj ) != 2 ) || ES_NULO ( p_elmCima ) ||
			 ( SElmEntero ( p_elmCima ) != 20 ) || ( p_elmCima == SLisElemento ( p_lisVal, 1 ) ) )
		{
			printf( "Error caso 2: se esperaba una copia del 20 en la cima\n" );
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
		if ( ( SPilApilarTodosDup ( p_pilFalla, p_lisFalla ) != 0 ) || ( ErrCodigo () != ERR_COPIA_OBJETO ) ||
			 ( SPilNumElementos ( p_pilFalla ) != 1 ) )
		{
			printf( "Error caso 4: se esperaba 0 con ERR_COPIA_OBJETO y solo el 10 apilado\n" );
			iRes = BOOL_VAL_FALSO;
		}
		ErrLimpiar ();
		/* Se repara para poder destruirlo. */
		p_elmMalo->p_blqDatos->iTam = sizeof ( int );
		if ( ( SPilApilarTodosDup ( p_pilObj, NULL ) != 0 ) || ( SPilApilarTodosDup ( NULL, p_lisVal ) != 0 ) )
		{
			printf( "Error caso 5: con una pila o lista nula se esperaba 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las pilas y las listas\n" );
		iRes = BOOL_VAL_FALSO;
		SElmDestruir ( &p_elmMalo );
	}
	SPilDestruir ( &p_pilObj );
	SPilDestruir ( &p_pilFalla );
	SLisDestruir ( &p_lisVal );
	SLisDestruir ( &p_lisFalla );
	return ( iRes );
}


int TestSPila ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SPila]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSPilCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSPilApilar01 () == BOOL_VAL_CIERTO ) &&
			( TestSPilDesapilar01 () == BOOL_VAL_CIERTO ) &&
			( TestSPilVaciar01 () == BOOL_VAL_CIERTO ) &&
			( TestSPilInvalidos01 () == BOOL_VAL_CIERTO ) &&
			( TestSPilVacia01 () == BOOL_VAL_CIERTO ) &&
			( TestSPilApilarTodos01 () == BOOL_VAL_CIERTO ) &&
			( TestSPilApilarTodosDup01 () == BOOL_VAL_CIERTO ) )
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
