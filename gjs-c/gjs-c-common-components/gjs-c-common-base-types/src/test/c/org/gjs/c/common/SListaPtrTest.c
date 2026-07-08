#include "Base.h"

#include "SListaPtr.h"



/* Reserva un entero en memoria dinamica y devuelve su direccion como byte *.
   Como la SListaPtr tiene la liberacion activada por defecto, la lista pasa a
   ser la duena de estos datos y los libera ella al eliminar o destruir. */
static byte * CrearDatoEntero ( int iValor )
{
	int * p_iDato = (int *) MemReservar ( sizeof ( int ) );
	if ( ES_VALIDO ( p_iDato ) )
	{
		*p_iDato = iValor;
	}
	return ( (byte *) p_iDato );
}

static int VerificarContenido ( SListaPtr * p_lisObj, int * p_iEsperados, int iNum )
{
	int iRes = BOOL_VAL_CIERTO;

	if ( SLispNumElementos ( p_lisObj ) != iNum )
	{
		printf( "  Verificacion: se esperaban %d elementos: %d\n", iNum, SLispNumElementos ( p_lisObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	int iPos = 0;
	while ( ( iPos < iNum ) && ( iRes == BOOL_VAL_CIERTO ) )
	{
		byte * p_byDato = SLispElemento ( p_lisObj, iPos );
		if ( ES_NULO ( p_byDato ) )
		{
			printf( "  Verificacion: elemento nulo en la posicion %d\n", iPos );
			iRes = BOOL_VAL_FALSO;
		}
		else if ( *( (int *) p_byDato ) != p_iEsperados [ iPos ] )
		{
			printf( "  Verificacion: en pos %d se esperaba %d: %d\n", iPos, p_iEsperados [ iPos ], *( (int *) p_byDato ) );
			iRes = BOOL_VAL_FALSO;
		}
		iPos = iPos + 1;
	}
	return ( iRes );
}



static int TestSLispCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLispCrear 01:\n" );

	SListaPtr * p_lisObj = SLispCrear ();
	if ( ES_NULO ( p_lisObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SLispEsValida ( p_lisObj ) != 1 )
		{
			printf( "Error caso 2: la lista recien creada deberia ser valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLispEstaVacia ( p_lisObj ) != 1 )
		{
			printf( "Error caso 3: la lista recien creada deberia estar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Por defecto la lista gestiona la memoria de sus datos. */
		if ( SLispLiberacionMemoriaActivada ( p_lisObj ) != 1 )
		{
			printf( "Error caso 4: la liberacion de memoria deberia estar activada por defecto\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SLispDestruir ( &p_lisObj );

	if ( ES_VALIDO ( p_lisObj ) )
	{
		printf( "Error caso 5: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSLispInsertar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLispInsertar 01:\n" );

	SListaPtr * p_lisObj = SLispCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		SLispInsertarAlFinal ( p_lisObj, CrearDatoEntero ( 10 ) );
		SLispInsertarAlFinal ( p_lisObj, CrearDatoEntero ( 20 ) );
		SLispInsertarAlFinal ( p_lisObj, CrearDatoEntero ( 30 ) );

		int iEsp1 [ 3 ] = { 10, 20, 30 };
		if ( VerificarContenido ( p_lisObj, iEsp1, 3 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 1: contenido incorrecto tras insertar al final\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Insertar en medio ( detras del indice 0 ). */
		if ( SLispInsertarElem ( p_lisObj, 0, CrearDatoEntero ( 15 ) ) != 1 )
		{
			printf( "Error caso 2: se esperaba resultado 1 al insertar en medio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		int iEsp2 [ 4 ] = { 10, 15, 20, 30 };
		if ( VerificarContenido ( p_lisObj, iEsp2, 4 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 3: contenido incorrecto tras insertar en medio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Insertar al inicio. */
		SLispInsertarAlInicio ( p_lisObj, CrearDatoEntero ( 5 ) );
		if ( *( (int *) SLispElemento ( p_lisObj, 0 ) ) != 5 )
		{
			printf( "Error caso 4: el primer elemento deberia ser el 5\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLispDestruir ( &p_lisObj );
	return ( iRes );
}

static int TestSLispCursor01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLispCursor 01:\n" );

	SListaPtr * p_lisObj = SLispCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		SLispInsertarAlFinal ( p_lisObj, CrearDatoEntero ( 10 ) );
		SLispInsertarAlFinal ( p_lisObj, CrearDatoEntero ( 20 ) );
		SLispInsertarAlFinal ( p_lisObj, CrearDatoEntero ( 30 ) );

		SLispInicio ( p_lisObj );
		if ( ( SLispPosicion ( p_lisObj ) != 0 ) || ( *( (int *) SLispActual ( p_lisObj ) ) != 10 ) )
		{
			printf( "Error caso 1: el inicio deberia situar el cursor en el 10\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLispSiguiente ( p_lisObj );
		if ( *( (int *) SLispActual ( p_lisObj ) ) != 20 )
		{
			printf( "Error caso 2: el siguiente deberia situar el cursor en el 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLispFinal ( p_lisObj );
		if ( ( *( (int *) SLispActual ( p_lisObj ) ) != 30 ) || ( SLispEstaEnFinal ( p_lisObj ) != 1 ) )
		{
			printf( "Error caso 3: el final deberia situar el cursor en el 30\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLispAnterior ( p_lisObj );
		if ( *( (int *) SLispActual ( p_lisObj ) ) != 20 )
		{
			printf( "Error caso 4: el anterior deberia situar el cursor en el 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLispDestruir ( &p_lisObj );
	return ( iRes );
}

static int TestSLispBuscar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLispBuscar 01:\n" );

	SListaPtr * p_lisObj = SLispCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		SLispInsertarAlFinal ( p_lisObj, CrearDatoEntero ( 10 ) );
		SLispInsertarAlFinal ( p_lisObj, CrearDatoEntero ( 20 ) );
		SLispInsertarAlFinal ( p_lisObj, CrearDatoEntero ( 30 ) );

		int iBuscar = 20;
		if ( SLispBuscar ( p_lisObj, (byte *) &iBuscar, sizeof ( int ) ) != 1 )
		{
			printf( "Error caso 1: el 20 deberia estar en la posicion 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		iBuscar = 99;
		if ( SLispBuscar ( p_lisObj, (byte *) &iBuscar, sizeof ( int ) ) != -1 )
		{
			printf( "Error caso 2: el 99 no deberia encontrarse\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLispDestruir ( &p_lisObj );
	return ( iRes );
}

static int TestSLispEliminar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLispEliminar 01:\n" );

	SListaPtr * p_lisObj = SLispCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		SLispInsertarAlFinal ( p_lisObj, CrearDatoEntero ( 10 ) );
		SLispInsertarAlFinal ( p_lisObj, CrearDatoEntero ( 20 ) );
		SLispInsertarAlFinal ( p_lisObj, CrearDatoEntero ( 30 ) );

		/* Al eliminar, la lista libera el dato ( liberacion activada ). */
		SLispEliminarElem ( p_lisObj, 1 );
		int iEsp [ 2 ] = { 10, 30 };
		if ( VerificarContenido ( p_lisObj, iEsp, 2 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 1: contenido incorrecto tras eliminar el elemento 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLispVaciar ( p_lisObj ) != 1 )
		{
			printf( "Error caso 2: se esperaba resultado 1 al vaciar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLispEstaVacia ( p_lisObj ) != 1 )
		{
			printf( "Error caso 3: la lista deberia quedar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLispDestruir ( &p_lisObj );
	return ( iRes );
}

static int TestSLispInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLispInvalidos 01:\n" );

	if ( SLispEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: una lista nula no deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLispNumElementos ( NULL ) != 0 )
	{
		printf( "Error caso 2: el numero de elementos de una lista nula deberia ser 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLispEstaVacia ( NULL ) != 1 )
	{
		printf( "Error caso 3: una lista nula deberia considerarse vacia\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SListaPtr * p_lisNula = NULL;
	SLispDestruir ( &p_lisNula );
	return ( iRes );
}



int TestSListaPtr ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SListaPtr]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSLispCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSLispInsertar01 () == BOOL_VAL_CIERTO ) &&
			( TestSLispCursor01 () == BOOL_VAL_CIERTO ) &&
			( TestSLispBuscar01 () == BOOL_VAL_CIERTO ) &&
			( TestSLispEliminar01 () == BOOL_VAL_CIERTO ) &&
			( TestSLispInvalidos01 () == BOOL_VAL_CIERTO ) )
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
