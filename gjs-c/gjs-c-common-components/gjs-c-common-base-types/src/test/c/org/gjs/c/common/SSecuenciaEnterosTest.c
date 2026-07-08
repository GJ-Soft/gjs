#include "Base.h"

#include "SSecuenciaEnteros.h"



static int TestSSecEntOperaciones01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecEntOperaciones 01:\n" );

	SSecuenciaEnteros * p_secObj = SSecEntCrear ();
	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ( SSecEntEsValida ( p_secObj ) != 1 ) || ( SSecEntNumElementos ( p_secObj ) != 0 ) )
		{
			printf( "Error caso 1: la secuencia recien creada deberia ser valida y vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecEntInsertar ( p_secObj, 10 ) != 1 ) ||
			 ( SSecEntInsertar ( p_secObj, 20 ) != 1 ) ||
			 ( SSecEntInsertar ( p_secObj, 30 ) != 1 ) )
		{
			printf( "Error caso 2: se esperaba poder insertar los tres enteros\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecEntNumElementos ( p_secObj ) != 3 ) || ( SSecEntElemento ( p_secObj, 1 ) != 20 ) )
		{
			printf( "Error caso 3: deberia haber 3 elementos y el del indice 1 ser 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecEntExiste ( p_secObj, 30 ) != 1 ) || ( SSecEntExiste ( p_secObj, 99 ) != 0 ) )
		{
			printf( "Error caso 4: existe deberia encontrar 30 y no 99\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Modificar el elemento del indice 1. */
		if ( ( SSecEntModificar ( p_secObj, 1, 25 ) != 1 ) || ( SSecEntElemento ( p_secObj, 1 ) != 25 ) )
		{
			printf( "Error caso 5: el elemento 1 deberia poder modificarse a 25\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Eliminar el primero: se desplazan los demas. */
		if ( ( SSecEntEliminar ( p_secObj, 0 ) != 1 ) ||
			 ( SSecEntNumElementos ( p_secObj ) != 2 ) || ( SSecEntElemento ( p_secObj, 0 ) != 25 ) )
		{
			printf( "Error caso 6: tras eliminar el primero deberian quedar 25 y 30\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Vaciar. */
		SSecEntVaciar ( p_secObj );
		if ( SSecEntNumElementos ( p_secObj ) != 0 )
		{
			printf( "Error caso 7: tras vaciar no deberia quedar ningun elemento\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la secuencia\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecEntDestruir ( &p_secObj );

	if ( ES_VALIDO ( p_secObj ) )
	{
		printf( "Error caso 8: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSSecEntInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecEntInvalidos 01:\n" );

	if ( SSecEntEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: una secuencia nula no deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SSecEntNumElementos ( NULL ) != 0 )
	{
		printf( "Error caso 2: una secuencia nula deberia tener 0 elementos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SSecEntInsertar ( NULL, 5 ) == 1 )
	{
		printf( "Error caso 3: insertar en una secuencia nula no deberia devolver exito\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecuenciaEnteros * p_secNula = NULL;
	SSecEntDestruir ( &p_secNula );
	return ( iRes );
}



int TestSSecuenciaEnteros ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SSecuenciaEnteros]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSSecEntOperaciones01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecEntInvalidos01 () == BOOL_VAL_CIERTO ) )
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
