#include "Base.h"

#include "SPilaLiterales.h"



static int PrimeroEs ( SPilaLiterales * p_pilObj, const char * p_cEsperado )
{
	return ( CadComparar ( SPilLitPrimero ( p_pilObj ), (char *) p_cEsperado ) == COMP_IGUAL );
}



static int TestSPilLitApilar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SPilLitApilar 01:\n" );

	SPilaLiterales * p_pilObj = SPilLitCrear ();
	if ( ES_VALIDO ( p_pilObj ) )
	{
		if ( ( SPilLitEsValida ( p_pilObj ) != 1 ) || ( SPilLitEstaVacia ( p_pilObj ) != 1 ) )
		{
			printf( "Error caso 1: la pila recien creada deberia ser valida y estar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Apilar duplica la cadena; la pila la posee. */
		if ( ( SPilLitApilar ( p_pilObj, "a" ) != 1 ) ||
			 ( SPilLitApilar ( p_pilObj, "b" ) != 1 ) ||
			 ( SPilLitApilar ( p_pilObj, "c" ) != 1 ) )
		{
			printf( "Error caso 2: se esperaba poder apilar las tres cadenas\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SPilLitNumElementos ( p_pilObj ) != 3 ) || ( SPilLitEstaVacia ( p_pilObj ) != 0 ) )
		{
			printf( "Error caso 3: la pila deberia tener 3 elementos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* LIFO: la cima ( peek ) es la ultima apilada. */
		if ( ! PrimeroEs ( p_pilObj, "c" ) )
		{
			printf( "Error caso 4: la cima deberia ser \"c\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Desapilar cede la propiedad de la cadena: el test la libera. */
		char * p_cCima = SPilLitDesapilar ( p_pilObj );
		if ( ( CadComparar ( p_cCima, "c" ) != COMP_IGUAL ) || ( SPilLitNumElementos ( p_pilObj ) != 2 ) )
		{
			printf( "Error caso 5: desapilar deberia devolver \"c\" y dejar 2 elementos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		MemLiberar ( (void **) &p_cCima );
		if ( ! PrimeroEs ( p_pilObj, "b" ) )
		{
			printf( "Error caso 6: la nueva cima deberia ser \"b\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Eliminar la cima sin devolverla ( la pila la libera ). */
		if ( ( SPilLitEliminarPrimero ( p_pilObj ) != 1 ) || ( ! PrimeroEs ( p_pilObj, "a" ) ) )
		{
			printf( "Error caso 7: tras eliminar la cima deberia quedar \"a\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SPilLitVaciar ( p_pilObj );
		if ( SPilLitEstaVacia ( p_pilObj ) != 1 )
		{
			printf( "Error caso 8: tras vaciar la pila deberia estar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la pila\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SPilLitDestruir ( &p_pilObj );

	if ( ES_VALIDO ( p_pilObj ) )
	{
		printf( "Error caso 9: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSPilLitInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SPilLitInvalidos 01:\n" );

	if ( SPilLitEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: una pila nula no deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SPilLitEstaVacia ( NULL ) != 1 )
	{
		printf( "Error caso 2: una pila nula deberia considerarse vacia\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SPilLitPrimero ( NULL ) ) )
	{
		printf( "Error caso 3: la cima de una pila nula deberia ser nula\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Fallan con 0, no con -1, como el resto de la libreria. */
	if ( ( SPilLitApilar ( NULL, "a" ) != 0 ) || ( SPilLitEliminarPrimero ( NULL ) != 0 ) ||
		 ( SPilLitVaciar ( NULL ) != 0 ) )
	{
		printf( "Error caso 4: con una pila nula se esperaba 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SPilaLiterales * p_pilObj = SPilLitCrear ();
	if ( ES_VALIDO ( p_pilObj ) )
	{
		if ( ( SPilLitApilar ( p_pilObj, NULL ) != 0 ) || ( SPilLitEstaVacia ( p_pilObj ) != 1 ) )
		{
			printf( "Error caso 5: apilar una cadena nula deberia dar 0 sin apilar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la pila\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SPilLitDestruir ( &p_pilObj );
	SPilaLiterales * p_pilNula = NULL;
	SPilLitDestruir ( &p_pilNula );
	return ( iRes );
}


/* ApilarTodos mueve y ApilarTodosDup copia: el ultimo de la lista queda en la cima. */
static int TestSPilLitApilarTodos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SPilLitApilarTodos 01:\n" );

	SPilaLiterales * p_pilObj = SPilLitCrear ();
	SListaLiterales * p_lisVal = SLisLitCrear ();
	SListaLiterales * p_lisDup = SLisLitCrear ();
	if ( ES_VALIDO ( p_pilObj ) && ES_VALIDO ( p_lisVal ) && ES_VALIDO ( p_lisDup ) )
	{
		SLisLitInsertarDupAlFinal ( p_lisVal, "a" );
		SLisLitInsertarDupAlFinal ( p_lisVal, "b" );
		SLisLitInsertarDupAlFinal ( p_lisDup, "x" );
		SLisLitInsertarDupAlFinal ( p_lisDup, "y" );
		char * p_cB = SLisLitElemento ( p_lisVal, 1 );
		if ( ( SPilLitApilarTodos ( p_pilObj, p_lisVal ) != 1 ) || ( SPilLitNumElementos ( p_pilObj ) != 2 ) ||
			 ( SPilLitPrimero ( p_pilObj ) != p_cB ) || ( SLisLitNumElementos ( p_lisVal ) != 0 ) )
		{
			printf( "Error caso 1: se esperaban 2 apilados, la misma \"b\" en la cima y la lista vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SPilLitApilarTodosDup ( p_pilObj, p_lisDup ) != 1 ) || ( SPilLitNumElementos ( p_pilObj ) != 4 ) ||
			 ( ! PrimeroEs ( p_pilObj, "y" ) ) || ( SPilLitPrimero ( p_pilObj ) == SLisLitElemento ( p_lisDup, 1 ) ) ||
			 ( SLisLitNumElementos ( p_lisDup ) != 2 ) )
		{
			printf( "Error caso 2: se esperaba una copia de \"y\" en la cima y la lista intacta\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SPilLitApilarTodos ( p_pilObj, NULL ) != 0 ) || ( SPilLitApilarTodos ( NULL, p_lisDup ) != 0 ) ||
			 ( SPilLitApilarTodosDup ( p_pilObj, NULL ) != 0 ) || ( SPilLitApilarTodosDup ( NULL, p_lisDup ) != 0 ) )
		{
			printf( "Error caso 3: con una pila o lista nula se esperaba 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear la pila y las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SPilLitDestruir ( &p_pilObj );
	SLisLitDestruir ( &p_lisVal );
	SLisLitDestruir ( &p_lisDup );
	return ( iRes );
}


int TestSPilaLiterales ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SPilaLiterales]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSPilLitApilar01 () == BOOL_VAL_CIERTO ) &&
			( TestSPilLitInvalidos01 () == BOOL_VAL_CIERTO ) &&
			( TestSPilLitApilarTodos01 () == BOOL_VAL_CIERTO ) )
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
