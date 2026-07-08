#include "Base.h"

#include "SPilaEnteros.h"



static int TestSPilEntApilar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SPilEntApilar 01:\n" );

	SPilaEnteros * p_pilObj = SPilEntCrear ();
	if ( ES_VALIDO ( p_pilObj ) )
	{
		if ( ( SPilEntEsValida ( p_pilObj ) != 1 ) || ( SPilEntEstaVacia ( p_pilObj ) != 1 ) )
		{
			printf( "Error caso 1: la pila recien creada deberia ser valida y estar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SPilEntApilar ( p_pilObj, 10 ) != 1 ) ||
			 ( SPilEntApilar ( p_pilObj, 20 ) != 1 ) ||
			 ( SPilEntApilar ( p_pilObj, 30 ) != 1 ) )
		{
			printf( "Error caso 2: se esperaba poder apilar los tres enteros\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SPilEntNumElementos ( p_pilObj ) != 3 ) || ( SPilEntEstaVacia ( p_pilObj ) != 0 ) )
		{
			printf( "Error caso 3: la pila deberia tener 3 elementos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* LIFO: el primero ( cima ) es el ultimo apilado. */
		if ( SPilEntPrimero ( p_pilObj ) != 30 )
		{
			printf( "Error caso 4: la cima deberia ser 30\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Desapilar devuelve la cima y la retira. */
		if ( ( SPilEntDesapilar ( p_pilObj ) != 30 ) || ( SPilEntNumElementos ( p_pilObj ) != 2 ) )
		{
			printf( "Error caso 5: desapilar deberia devolver 30 y dejar 2 elementos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SPilEntPrimero ( p_pilObj ) != 20 )
		{
			printf( "Error caso 6: la nueva cima deberia ser 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Eliminar la cima sin devolverla. */
		if ( ( SPilEntEliminarPrimero ( p_pilObj ) != 1 ) || ( SPilEntPrimero ( p_pilObj ) != 10 ) )
		{
			printf( "Error caso 7: tras eliminar la cima deberia quedar 10\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Vaciar. */
		SPilEntVaciar ( p_pilObj );
		if ( SPilEntEstaVacia ( p_pilObj ) != 1 )
		{
			printf( "Error caso 8: tras vaciar la pila deberia estar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Desapilar en una pila vacia devuelve -1. */
		if ( SPilEntDesapilar ( p_pilObj ) != -1 )
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
	SPilEntDestruir ( &p_pilObj );

	if ( ES_VALIDO ( p_pilObj ) )
	{
		printf( "Error caso 10: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSPilEntInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SPilEntInvalidos 01:\n" );

	if ( SPilEntEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: una pila nula no deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SPilEntEstaVacia ( NULL ) != 1 )
	{
		printf( "Error caso 2: una pila nula deberia considerarse vacia\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SPilEntApilar ( NULL, 5 ) == 1 )
	{
		printf( "Error caso 3: apilar en una pila nula no deberia tener exito\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SPilaEnteros * p_pilNula = NULL;
	SPilEntDestruir ( &p_pilNula );
	return ( iRes );
}



int TestSPilaEnteros ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SPilaEnteros]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSPilEntApilar01 () == BOOL_VAL_CIERTO ) &&
			( TestSPilEntInvalidos01 () == BOOL_VAL_CIERTO ) )
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
