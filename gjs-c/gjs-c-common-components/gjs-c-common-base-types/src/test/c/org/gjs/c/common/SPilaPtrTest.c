#include "Base.h"

#include "SPilaPtr.h"



static byte * CrearDatoEntero ( int iValor )
{
	int * p_iDato = (int *) MemReservar ( sizeof ( int ) );
	if ( ES_VALIDO ( p_iDato ) )
	{
		*p_iDato = iValor;
	}
	return ( (byte *) p_iDato );
}



static int TestSPilpCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SPilpCrear 01:\n" );

	SPilaPtr * p_pilObj = SPilpCrear ();
	if ( ES_NULO ( p_pilObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SPilpEsValida ( p_pilObj ) != 1 )
		{
			printf( "Error caso 2: la pila recien creada deberia ser valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SPilpEstaVacia ( p_pilObj ) != 1 )
		{
			printf( "Error caso 3: la pila recien creada deberia estar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SPilpNumElementos ( p_pilObj ) != 0 )
		{
			printf( "Error caso 4: se esperaban 0 elementos\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SPilpDestruir ( &p_pilObj, 0 );

	if ( ES_VALIDO ( p_pilObj ) )
	{
		printf( "Error caso 5: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSPilpApilar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SPilpApilar 01:\n" );

	/* La pila no gestiona la memoria: mantenemos los datos en un array propio
	   y los liberamos al final; la pila se destruye con iLiberar = 0. */
	byte * p_datos [ 3 ];
	p_datos [ 0 ] = CrearDatoEntero ( 10 );
	p_datos [ 1 ] = CrearDatoEntero ( 20 );
	p_datos [ 2 ] = CrearDatoEntero ( 30 );

	SPilaPtr * p_pilObj = SPilpCrear ();
	if ( ES_VALIDO ( p_pilObj ) )
	{
		SPilpApilar ( p_pilObj, p_datos [ 0 ] );
		SPilpApilar ( p_pilObj, p_datos [ 1 ] );
		SPilpApilar ( p_pilObj, p_datos [ 2 ] );

		if ( SPilpNumElementos ( p_pilObj ) != 3 )
		{
			printf( "Error caso 1: se esperaban 3 elementos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Orden LIFO: la cima es el ultimo apilado. */
		if ( *( (int *) SPilpPrimero ( p_pilObj ) ) != 30 )
		{
			printf( "Error caso 2: la cima deberia ser el 30\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SPilpEliminarPrimero ( p_pilObj );
		if ( *( (int *) SPilpPrimero ( p_pilObj ) ) != 20 )
		{
			printf( "Error caso 3: tras eliminar, la cima deberia ser el 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la pila\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SPilpDestruir ( &p_pilObj, 0 );
	MemLiberar ( (void **) &p_datos [ 0 ] );
	MemLiberar ( (void **) &p_datos [ 1 ] );
	MemLiberar ( (void **) &p_datos [ 2 ] );
	return ( iRes );
}

static int TestSPilpDesapilar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SPilpDesapilar 01:\n" );

	byte * p_datos [ 2 ];
	p_datos [ 0 ] = CrearDatoEntero ( 10 );
	p_datos [ 1 ] = CrearDatoEntero ( 20 );

	SPilaPtr * p_pilObj = SPilpCrear ();
	if ( ES_VALIDO ( p_pilObj ) )
	{
		SPilpApilar ( p_pilObj, p_datos [ 0 ] );
		SPilpApilar ( p_pilObj, p_datos [ 1 ] );

		/* Desapilar devuelve la cima ( puntero vivo ) y reduce el tamano. */
		byte * p_byCima = SPilpDesapilar ( p_pilObj );
		if ( ES_NULO ( p_byCima ) || ( *( (int *) p_byCima ) != 20 ) )
		{
			printf( "Error caso 1: desapilar deberia devolver el 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SPilpNumElementos ( p_pilObj ) != 1 )
		{
			printf( "Error caso 2: se esperaba 1 elemento tras desapilar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		byte * p_byFondo = SPilpDesapilar ( p_pilObj );
		if ( ES_NULO ( p_byFondo ) || ( *( (int *) p_byFondo ) != 10 ) )
		{
			printf( "Error caso 3: desapilar deberia devolver el 10\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SPilpEstaVacia ( p_pilObj ) != 1 )
		{
			printf( "Error caso 4: la pila deberia quedar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Desapilar de una pila vacia devuelve nulo. */
		if ( ES_VALIDO ( SPilpDesapilar ( p_pilObj ) ) )
		{
			printf( "Error caso 5: desapilar de una pila vacia deberia dar nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la pila\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SPilpDestruir ( &p_pilObj, 0 );
	MemLiberar ( (void **) &p_datos [ 0 ] );
	MemLiberar ( (void **) &p_datos [ 1 ] );
	return ( iRes );
}

static int TestSPilpInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SPilpInvalidos 01:\n" );

	if ( SPilpEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: una pila nula no deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SPilpEstaVacia ( NULL ) != 1 )
	{
		printf( "Error caso 2: una pila nula deberia considerarse vacia\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SPilpApilar ( NULL, NULL ) != 0 )
	{
		printf( "Error caso 3: apilar en una pila nula deberia fallar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SPilaPtr * p_pilNula = NULL;
	SPilpDestruir ( &p_pilNula, 0 );
	return ( iRes );
}


/* SListaPtr duena de sus datos, en el orden dado. */
static SListaPtr * CrearListaEnteros ( int * p_iValores, int iNum )
{
	SListaPtr * p_lisObj = SLispCrear ();
	int iPos = 0;
	while ( ES_VALIDO ( p_lisObj ) && ( iPos < iNum ) )
	{
		SLispInsertarAlFinal ( p_lisObj, CrearDatoEntero ( p_iValores [ iPos ] ) );
		iPos = iPos + 1;
	}
	return ( p_lisObj );
}

static byte * DuplicarEnteroMas100 ( byte * p_byDato )
{
	return ( CrearDatoEntero ( *( (int *) p_byDato ) + 100 ) );
}

static byte * DuplicarFallaEn20 ( byte * p_byDato )
{
	byte * p_byRes;

	if ( *( (int *) p_byDato ) == 20 )
	{
		p_byRes = NULL;
	}
	else
	{
		p_byRes = CrearDatoEntero ( *( (int *) p_byDato ) );
	}
	return ( p_byRes );
}

static int ValorCima ( SPilaPtr * p_pilObj )
{
	byte * p_byDato = SPilpPrimero ( p_pilObj );
	int iRes = -1;
	if ( ES_VALIDO ( p_byDato ) )
	{
		iRes = *( (int *) p_byDato );
	}
	return ( iRes );
}

/* La cima de una pila vacia es nula y deja ERR_PILA_VACIA. */
static int TestSPilpVacia01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SPilpVacia 01:\n" );

	SPilaPtr * p_pilObj = SPilpCrear ();
	if ( ES_VALIDO ( p_pilObj ) )
	{
		ErrLimpiar ();
		if ( ES_VALIDO ( SPilpPrimero ( p_pilObj ) ) || ( ErrCodigo () != ERR_PILA_VACIA ) )
		{
			printf( "Error caso 1: la cima de una vacia deberia ser nula con ERR_PILA_VACIA\n" );
			iRes = BOOL_VAL_FALSO;
		}
		ErrLimpiar ();
		if ( ES_VALIDO ( SPilpDesapilar ( p_pilObj ) ) || ( ErrCodigo () != ERR_PILA_VACIA ) )
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
	SPilpDestruir ( &p_pilObj, 0 );
	return ( iRes );
}

/* Mueve los nodos: el ultimo de la lista queda en la cima y la lista vacia. */
static int TestSPilpApilarTodos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SPilpApilarTodos 01:\n" );

	int iVal [ 3 ] = { 10, 20, 30 };
	SPilaPtr * p_pilObj = SPilpCrear ();
	SListaPtr * p_lisVal = CrearListaEnteros ( iVal, 3 );
	SListaPtr * p_lisVacia = SLispCrear ();
	if ( ES_VALIDO ( p_pilObj ) && ES_VALIDO ( p_lisVal ) && ES_VALIDO ( p_lisVacia ) )
	{
		byte * p_by30 = SLispElemento ( p_lisVal, 2 );
		if ( SPilpApilarTodos ( p_pilObj, p_lisVal ) != 1 )
		{
			printf( "Error caso 1: se esperaba 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SPilpNumElementos ( p_pilObj ) != 3 ) || ( SLispNumElementos ( p_lisVal ) != 0 ) ||
			 ( SPilpPrimero ( p_pilObj ) != p_by30 ) )
		{
			printf( "Error caso 2: se esperaban 3 apilados, el 30 en la cima y la lista vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		int iEsp [ 3 ] = { 30, 20, 10 };
		int iPos = 0;
		while ( iPos < 3 )
		{
			byte * p_byDato = SPilpDesapilar ( p_pilObj );
			if ( ES_NULO ( p_byDato ) || ( *( (int *) p_byDato ) != iEsp [ iPos ] ) )
			{
				printf( "Error caso 3: en la posicion %d se esperaba desapilar %d\n", iPos, iEsp [ iPos ] );
				iRes = BOOL_VAL_FALSO;
			}
			MemLiberar ( (void **) &p_byDato );
			iPos = iPos + 1;
		}
		if ( ( SPilpApilarTodos ( p_pilObj, p_lisVacia ) != 1 ) || ( SPilpEstaVacia ( p_pilObj ) != 1 ) )
		{
			printf( "Error caso 4: con una lista vacia se esperaba 1 sin cambios\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SPilpApilarTodos ( p_pilObj, NULL ) != 0 ) || ( SPilpApilarTodos ( NULL, p_lisVacia ) != 0 ) )
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
	SPilpDestruir ( &p_pilObj, 1 );
	SLispDestruir ( &p_lisVal );
	SLispDestruir ( &p_lisVacia );
	return ( iRes );
}

/* Apila copias ( iNumBytes o fDuplicar ): la lista y su cursor no cambian. */
static int TestSPilpApilarTodosDup01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SPilpApilarTodosDup 01:\n" );

	int iVal [ 3 ] = { 10, 20, 30 };
	SPilaPtr * p_pilObj = SPilpCrear ();
	SPilaPtr * p_pilExt = SPilpCrear ();
	SPilaPtr * p_pilFalla = SPilpCrear ();
	SListaPtr * p_lisVal = CrearListaEnteros ( iVal, 3 );
	if ( ES_VALIDO ( p_pilObj ) && ES_VALIDO ( p_pilExt ) && ES_VALIDO ( p_pilFalla ) && ES_VALIDO ( p_lisVal ) )
	{
		SLispMoverA ( p_lisVal, 1 );
		if ( SPilpApilarTodosDup ( p_pilObj, p_lisVal, sizeof ( int ) ) != 1 )
		{
			printf( "Error caso 1: se esperaba 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SPilpNumElementos ( p_pilObj ) != 3 ) || ( ValorCima ( p_pilObj ) != 30 ) ||
			 ( SPilpPrimero ( p_pilObj ) == SLispElemento ( p_lisVal, 2 ) ) )
		{
			printf( "Error caso 2: se esperaba una copia del 30 en la cima\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLispNumElementos ( p_lisVal ) != 3 ) || ( SLispPosicion ( p_lisVal ) != 1 ) )
		{
			printf( "Error caso 3: la lista y su cursor no deberian cambiar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SPilpApilarTodosDupExt ( p_pilExt, p_lisVal, DuplicarEnteroMas100 ) != 1 ) ||
			 ( SPilpNumElementos ( p_pilExt ) != 3 ) || ( ValorCima ( p_pilExt ) != 130 ) )
		{
			printf( "Error caso 4: la Ext deberia apilar con 100 mas: cima 130\n" );
			iRes = BOOL_VAL_FALSO;
		}
		ErrLimpiar ();
		if ( ( SPilpApilarTodosDupExt ( p_pilFalla, p_lisVal, DuplicarFallaEn20 ) != 0 ) ||
			 ( ErrCodigo () != ERR_COPIA_OBJETO ) || ( SPilpNumElementos ( p_pilFalla ) != 1 ) )
		{
			printf( "Error caso 5: al fallar en el 20 se esperaba 0, ERR_COPIA_OBJETO y solo el 10\n" );
			iRes = BOOL_VAL_FALSO;
		}
		ErrLimpiar ();
		if ( ( SPilpApilarTodosDup ( p_pilFalla, p_lisVal, 0 ) != 0 ) || ( ErrCodigo () != ERR_COPIA_OBJETO ) ||
			 ( SPilpApilarTodosDupExt ( p_pilFalla, p_lisVal, NULL ) != 0 ) || ( SPilpNumElementos ( p_pilFalla ) != 1 ) )
		{
			printf( "Error caso 6: sin bytes o sin fDuplicar se esperaba 0 sin apilar nada\n" );
			iRes = BOOL_VAL_FALSO;
		}
		ErrLimpiar ();
		if ( ( SPilpApilarTodosDup ( p_pilObj, NULL, sizeof ( int ) ) != 0 ) ||
			 ( SPilpApilarTodosDup ( NULL, p_lisVal, sizeof ( int ) ) != 0 ) ||
			 ( SPilpApilarTodosDupExt ( NULL, p_lisVal, DuplicarEnteroMas100 ) != 0 ) )
		{
			printf( "Error caso 7: con una pila o lista nula se esperaba 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las pilas y la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Las copias son de las pilas. */
	SPilpDestruir ( &p_pilObj, 1 );
	SPilpDestruir ( &p_pilExt, 1 );
	SPilpDestruir ( &p_pilFalla, 1 );
	SLispDestruir ( &p_lisVal );
	return ( iRes );
}


int TestSPilaPtr ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SPilaPtr]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSPilpCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSPilpApilar01 () == BOOL_VAL_CIERTO ) &&
			( TestSPilpDesapilar01 () == BOOL_VAL_CIERTO ) &&
			( TestSPilpInvalidos01 () == BOOL_VAL_CIERTO ) &&
			( TestSPilpVacia01 () == BOOL_VAL_CIERTO ) &&
			( TestSPilpApilarTodos01 () == BOOL_VAL_CIERTO ) &&
			( TestSPilpApilarTodosDup01 () == BOOL_VAL_CIERTO ) )
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
