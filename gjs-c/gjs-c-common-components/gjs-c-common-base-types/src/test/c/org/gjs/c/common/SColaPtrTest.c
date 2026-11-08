#include "Base.h"

#include "SColaPtr.h"



static byte * CrearDatoEntero ( int iValor )
{
	int * p_iDato = (int *) MemReservar ( sizeof ( int ) );
	if ( ES_VALIDO ( p_iDato ) )
	{
		*p_iDato = iValor;
	}
	return ( (byte *) p_iDato );
}



static int TestSColpCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SColpCrear 01:\n" );

	SColaPtr * p_colObj = SColpCrear ();
	if ( ES_NULO ( p_colObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SColpEsValida ( p_colObj ) != 1 )
		{
			printf( "Error caso 2: la cola recien creada deberia ser valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SColpEstaVacia ( p_colObj ) != 1 )
		{
			printf( "Error caso 3: la cola recien creada deberia estar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SColpNumElementos ( p_colObj ) != 0 )
		{
			printf( "Error caso 4: se esperaban 0 elementos\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SColpDestruir ( &p_colObj, 0 );

	if ( ES_VALIDO ( p_colObj ) )
	{
		printf( "Error caso 5: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSColpEncolar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SColpEncolar 01:\n" );

	byte * p_datos [ 3 ];
	p_datos [ 0 ] = CrearDatoEntero ( 10 );
	p_datos [ 1 ] = CrearDatoEntero ( 20 );
	p_datos [ 2 ] = CrearDatoEntero ( 30 );

	SColaPtr * p_colObj = SColpCrear ();
	if ( ES_VALIDO ( p_colObj ) )
	{
		SColpEncolar ( p_colObj, p_datos [ 0 ] );
		SColpEncolar ( p_colObj, p_datos [ 1 ] );
		SColpEncolar ( p_colObj, p_datos [ 2 ] );

		if ( SColpNumElementos ( p_colObj ) != 3 )
		{
			printf( "Error caso 1: se esperaban 3 elementos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Orden FIFO. */
		if ( *( (int *) SColpPrimero ( p_colObj ) ) != 10 )
		{
			printf( "Error caso 2: el primero deberia ser el 10\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( *( (int *) SColpUltimo ( p_colObj ) ) != 30 )
		{
			printf( "Error caso 3: el ultimo deberia ser el 30\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( *( (int *) SColpElemento ( p_colObj, 1 ) ) != 20 )
		{
			printf( "Error caso 4: el elemento 1 deberia ser el 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Eliminar el ultimo. */
		SColpEliminarUltimo ( p_colObj );
		if ( ( SColpNumElementos ( p_colObj ) != 2 ) || ( *( (int *) SColpUltimo ( p_colObj ) ) != 20 ) )
		{
			printf( "Error caso 5: tras eliminar el ultimo deberia quedar el 20 al final\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la cola\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SColpDestruir ( &p_colObj, 0 );
	MemLiberar ( (void **) &p_datos [ 0 ] );
	MemLiberar ( (void **) &p_datos [ 1 ] );
	MemLiberar ( (void **) &p_datos [ 2 ] );
	return ( iRes );
}

static int TestSColpDesencolar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SColpDesencolar 01:\n" );

	byte * p_datos [ 2 ];
	p_datos [ 0 ] = CrearDatoEntero ( 10 );
	p_datos [ 1 ] = CrearDatoEntero ( 20 );

	SColaPtr * p_colObj = SColpCrear ();
	if ( ES_VALIDO ( p_colObj ) )
	{
		SColpEncolar ( p_colObj, p_datos [ 0 ] );
		SColpEncolar ( p_colObj, p_datos [ 1 ] );

		/* Desencolar devuelve el frente ( puntero vivo ) en orden FIFO. */
		byte * p_byFrente = SColpDesencolar ( p_colObj );
		if ( ES_NULO ( p_byFrente ) || ( *( (int *) p_byFrente ) != 10 ) )
		{
			printf( "Error caso 1: desencolar deberia devolver el 10\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SColpNumElementos ( p_colObj ) != 1 )
		{
			printf( "Error caso 2: se esperaba 1 elemento tras desencolar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		byte * p_bySiguiente = SColpDesencolar ( p_colObj );
		if ( ES_NULO ( p_bySiguiente ) || ( *( (int *) p_bySiguiente ) != 20 ) )
		{
			printf( "Error caso 3: desencolar deberia devolver el 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SColpEstaVacia ( p_colObj ) != 1 )
		{
			printf( "Error caso 4: la cola deberia quedar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Desencolar de una cola vacia devuelve nulo. */
		if ( ES_VALIDO ( SColpDesencolar ( p_colObj ) ) )
		{
			printf( "Error caso 5: desencolar de una cola vacia deberia dar nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la cola\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SColpDestruir ( &p_colObj, 0 );
	MemLiberar ( (void **) &p_datos [ 0 ] );
	MemLiberar ( (void **) &p_datos [ 1 ] );
	return ( iRes );
}

static int TestSColpInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SColpInvalidos 01:\n" );

	if ( SColpEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: una cola nula no deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SColpEstaVacia ( NULL ) != 1 )
	{
		printf( "Error caso 2: una cola nula deberia considerarse vacia\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SColpEncolar ( NULL, NULL ) != 0 )
	{
		printf( "Error caso 3: encolar en una cola nula deberia fallar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SColaPtr * p_colNula = NULL;
	SColpDestruir ( &p_colNula, 0 );
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

static int ValorPrimero ( SColaPtr * p_colObj )
{
	byte * p_byDato = SColpPrimero ( p_colObj );
	int iRes = -1;
	if ( ES_VALIDO ( p_byDato ) )
	{
		iRes = *( (int *) p_byDato );
	}
	return ( iRes );
}

/* Mueve los nodos al final de la cola: salen en el orden de la lista. */
static int TestSColpEncolarTodos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SColpEncolarTodos 01:\n" );

	int iVal [ 3 ] = { 10, 20, 30 };
	SColaPtr * p_colObj = SColpCrear ();
	SListaPtr * p_lisVal = CrearListaEnteros ( iVal, 3 );
	SListaPtr * p_lisVacia = SLispCrear ();
	if ( ES_VALIDO ( p_colObj ) && ES_VALIDO ( p_lisVal ) && ES_VALIDO ( p_lisVacia ) )
	{
		byte * p_by10 = SLispElemento ( p_lisVal, 0 );
		if ( SColpEncolarTodos ( p_colObj, p_lisVal ) != 1 )
		{
			printf( "Error caso 1: se esperaba 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SColpNumElementos ( p_colObj ) != 3 ) || ( SLispNumElementos ( p_lisVal ) != 0 ) ||
			 ( SColpPrimero ( p_colObj ) != p_by10 ) )
		{
			printf( "Error caso 2: se esperaban 3 encolados, el mismo 10 al frente y la lista vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		int iEsp [ 3 ] = { 10, 20, 30 };
		int iPos = 0;
		while ( iPos < 3 )
		{
			byte * p_byDato = SColpDesencolar ( p_colObj );
			if ( ES_NULO ( p_byDato ) || ( *( (int *) p_byDato ) != iEsp [ iPos ] ) )
			{
				printf( "Error caso 3: en la posicion %d se esperaba desencolar %d\n", iPos, iEsp [ iPos ] );
				iRes = BOOL_VAL_FALSO;
			}
			MemLiberar ( (void **) &p_byDato );
			iPos = iPos + 1;
		}
		if ( ( SColpEncolarTodos ( p_colObj, p_lisVacia ) != 1 ) || ( SColpEstaVacia ( p_colObj ) != 1 ) )
		{
			printf( "Error caso 4: con una lista vacia se esperaba 1 sin cambios\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SColpEncolarTodos ( p_colObj, NULL ) != 0 ) || ( SColpEncolarTodos ( NULL, p_lisVacia ) != 0 ) )
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
	SColpDestruir ( &p_colObj, 1 );
	SLispDestruir ( &p_lisVal );
	SLispDestruir ( &p_lisVacia );
	return ( iRes );
}

/* Encola copias ( iNumBytes o fDuplicar ): la lista y su cursor no cambian. */
static int TestSColpEncolarTodosDup01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SColpEncolarTodosDup 01:\n" );

	int iVal [ 3 ] = { 10, 20, 30 };
	SColaPtr * p_colObj = SColpCrear ();
	SColaPtr * p_colExt = SColpCrear ();
	SColaPtr * p_colFalla = SColpCrear ();
	SListaPtr * p_lisVal = CrearListaEnteros ( iVal, 3 );
	if ( ES_VALIDO ( p_colObj ) && ES_VALIDO ( p_colExt ) && ES_VALIDO ( p_colFalla ) && ES_VALIDO ( p_lisVal ) )
	{
		SLispMoverA ( p_lisVal, 1 );
		if ( SColpEncolarTodosDup ( p_colObj, p_lisVal, sizeof ( int ) ) != 1 )
		{
			printf( "Error caso 1: se esperaba 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SColpNumElementos ( p_colObj ) != 3 ) || ( ValorPrimero ( p_colObj ) != 10 ) ||
			 ( SColpPrimero ( p_colObj ) == SLispElemento ( p_lisVal, 0 ) ) )
		{
			printf( "Error caso 2: se esperaba una copia del 10 al frente\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLispNumElementos ( p_lisVal ) != 3 ) || ( SLispPosicion ( p_lisVal ) != 1 ) )
		{
			printf( "Error caso 3: la lista y su cursor no deberian cambiar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SColpEncolarTodosDupExt ( p_colExt, p_lisVal, DuplicarEnteroMas100 ) != 1 ) ||
			 ( SColpNumElementos ( p_colExt ) != 3 ) || ( ValorPrimero ( p_colExt ) != 110 ) )
		{
			printf( "Error caso 4: la Ext deberia encolar con 100 mas: primero 110\n" );
			iRes = BOOL_VAL_FALSO;
		}
		ErrLimpiar ();
		if ( ( SColpEncolarTodosDupExt ( p_colFalla, p_lisVal, DuplicarFallaEn20 ) != 0 ) ||
			 ( ErrCodigo () != ERR_COPIA_OBJETO ) || ( SColpNumElementos ( p_colFalla ) != 1 ) )
		{
			printf( "Error caso 5: al fallar en el 20 se esperaba 0, ERR_COPIA_OBJETO y solo el 10\n" );
			iRes = BOOL_VAL_FALSO;
		}
		ErrLimpiar ();
		if ( ( SColpEncolarTodosDup ( p_colFalla, p_lisVal, 0 ) != 0 ) || ( ErrCodigo () != ERR_COPIA_OBJETO ) ||
			 ( SColpEncolarTodosDupExt ( p_colFalla, p_lisVal, NULL ) != 0 ) || ( SColpNumElementos ( p_colFalla ) != 1 ) )
		{
			printf( "Error caso 6: sin bytes o sin fDuplicar se esperaba 0 sin encolar nada\n" );
			iRes = BOOL_VAL_FALSO;
		}
		ErrLimpiar ();
		if ( ( SColpEncolarTodosDup ( p_colObj, NULL, sizeof ( int ) ) != 0 ) ||
			 ( SColpEncolarTodosDup ( NULL, p_lisVal, sizeof ( int ) ) != 0 ) ||
			 ( SColpEncolarTodosDupExt ( NULL, p_lisVal, DuplicarEnteroMas100 ) != 0 ) )
		{
			printf( "Error caso 7: con una cola o lista nula se esperaba 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las colas y la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Las copias son de las colas. */
	SColpDestruir ( &p_colObj, 1 );
	SColpDestruir ( &p_colExt, 1 );
	SColpDestruir ( &p_colFalla, 1 );
	SLispDestruir ( &p_lisVal );
	return ( iRes );
}


int TestSColaPtr ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SColaPtr]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSColpCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSColpEncolar01 () == BOOL_VAL_CIERTO ) &&
			( TestSColpDesencolar01 () == BOOL_VAL_CIERTO ) &&
			( TestSColpInvalidos01 () == BOOL_VAL_CIERTO ) &&
			( TestSColpEncolarTodos01 () == BOOL_VAL_CIERTO ) &&
			( TestSColpEncolarTodosDup01 () == BOOL_VAL_CIERTO ) )
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
