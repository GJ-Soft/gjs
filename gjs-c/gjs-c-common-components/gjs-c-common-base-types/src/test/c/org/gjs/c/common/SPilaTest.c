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



int TestSPila ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SPila]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSPilCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSPilApilar01 () == BOOL_VAL_CIERTO ) &&
			( TestSPilDesapilar01 () == BOOL_VAL_CIERTO ) &&
			( TestSPilVaciar01 () == BOOL_VAL_CIERTO ) &&
			( TestSPilInvalidos01 () == BOOL_VAL_CIERTO ) )
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
