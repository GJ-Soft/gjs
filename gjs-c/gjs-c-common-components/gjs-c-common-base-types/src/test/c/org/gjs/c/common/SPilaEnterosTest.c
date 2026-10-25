#include "Base.h"

#include "SPilaEnteros.h"



static int TestSPilIntApilar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SPilIntApilar 01:\n" );

	SPilaEnteros * p_pilObj = SPilIntCrear ();
	if ( ES_VALIDO ( p_pilObj ) )
	{
		if ( ( SPilIntEsValida ( p_pilObj ) != 1 ) || ( SPilIntEstaVacia ( p_pilObj ) != 1 ) )
		{
			printf( "Error caso 1: la pila recien creada deberia ser valida y estar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SPilIntApilar ( p_pilObj, 10 ) != 1 ) ||
			 ( SPilIntApilar ( p_pilObj, 20 ) != 1 ) ||
			 ( SPilIntApilar ( p_pilObj, 30 ) != 1 ) )
		{
			printf( "Error caso 2: se esperaba poder apilar los tres enteros\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SPilIntNumElementos ( p_pilObj ) != 3 ) || ( SPilIntEstaVacia ( p_pilObj ) != 0 ) )
		{
			printf( "Error caso 3: la pila deberia tener 3 elementos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* LIFO: el primero ( cima ) es el ultimo apilado. */
		if ( SPilIntPrimero ( p_pilObj ) != 30 )
		{
			printf( "Error caso 4: la cima deberia ser 30\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Desapilar devuelve la cima y la retira. */
		if ( ( SPilIntDesapilar ( p_pilObj ) != 30 ) || ( SPilIntNumElementos ( p_pilObj ) != 2 ) )
		{
			printf( "Error caso 5: desapilar deberia devolver 30 y dejar 2 elementos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SPilIntPrimero ( p_pilObj ) != 20 )
		{
			printf( "Error caso 6: la nueva cima deberia ser 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Eliminar la cima sin devolverla. */
		if ( ( SPilIntEliminarPrimero ( p_pilObj ) != 1 ) || ( SPilIntPrimero ( p_pilObj ) != 10 ) )
		{
			printf( "Error caso 7: tras eliminar la cima deberia quedar 10\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Vaciar. */
		SPilIntVaciar ( p_pilObj );
		if ( SPilIntEstaVacia ( p_pilObj ) != 1 )
		{
			printf( "Error caso 8: tras vaciar la pila deberia estar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Desapilar en una pila vacia devuelve -1. */
		if ( SPilIntDesapilar ( p_pilObj ) != -1 )
		{
			printf( "Error caso 9: desapilar en una pila vacia deberia devolver -1\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la pila\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SPilIntDestruir ( &p_pilObj );

	if ( ES_VALIDO ( p_pilObj ) )
	{
		printf( "Error caso 10: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSPilIntInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SPilIntInvalidos 01:\n" );

	if ( SPilIntEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: una pila nula no deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SPilIntEstaVacia ( NULL ) != 1 )
	{
		printf( "Error caso 2: una pila nula deberia considerarse vacia\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SPilIntApilar ( NULL, 5 ) == 1 )
	{
		printf( "Error caso 3: apilar en una pila nula no deberia tener exito\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SPilaEnteros * p_pilNula = NULL;
	SPilIntDestruir ( &p_pilNula );
	return ( iRes );
}



int TestSPilaEnteros ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SPilaEnteros]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSPilIntApilar01 () == BOOL_VAL_CIERTO ) &&
			( TestSPilIntInvalidos01 () == BOOL_VAL_CIERTO ) )
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
