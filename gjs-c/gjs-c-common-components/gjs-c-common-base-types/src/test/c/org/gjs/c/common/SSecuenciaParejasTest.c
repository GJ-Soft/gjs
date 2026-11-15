#include "Base.h"

#include "SSecuenciaParejas.h"



static int TestSSecPrjOperaciones01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecPrjOperaciones 01:\n" );

	/* La pareja guarda los punteros sin poseerlos; los datos viven en la pila del test. */
	int iA = 1;
	int iB = 2;
	int iC = 3;
	int iD = 4;
	SSecuenciaParejas * p_secObj = SSecPrjCrear ();
	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ( SSecPrjEsValida ( p_secObj ) != 1 ) || ( SSecPrjEstaVacia ( p_secObj ) != 1 ) )
		{
			printf( "Error caso 1: la secuencia recien creada deberia ser valida y estar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* InsertarExt crea la pareja a partir de dos punteros. */
		if ( SSecPrjInsertarExt ( p_secObj, &iA, &iB ) != 1 )
		{
			printf( "Error caso 2: se esperaba resultado 1 al insertar la pareja\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SSecPrjNumElementos ( p_secObj ) != 1 )
		{
			printf( "Error caso 3: la secuencia deberia tener 1 elemento\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SPrjObtenerPrimero ( SSecPrjElemento ( p_secObj, 0 ) ) != (void *) &iA ) ||
			 ( SPrjObtenerSegundo ( SSecPrjElemento ( p_secObj, 0 ) ) != (void *) &iB ) )
		{
			printf( "Error caso 4: la pareja deberia guardar los punteros a iA e iB\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Insertar una pareja ya creada ( la secuencia pasa a poseerla ). */
		if ( SSecPrjInsertar ( p_secObj, SPrjCrearSoloPtr ( &iC, &iD ) ) != 1 )
		{
			printf( "Error caso 5: se esperaba poder insertar una pareja creada aparte\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecPrjNumElementos ( p_secObj ) != 2 ) ||
			 ( SPrjObtenerPrimero ( SSecPrjElemento ( p_secObj, 1 ) ) != (void *) &iC ) )
		{
			printf( "Error caso 6: la segunda pareja deberia guardar el puntero a iC\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Eliminar el primero. */
		if ( ( SSecPrjEliminarElem ( p_secObj, 0 ) != 1 ) || ( SSecPrjNumElementos ( p_secObj ) != 1 ) )
		{
			printf( "Error caso 7: tras eliminar deberia quedar 1 elemento\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SSecPrjVaciar ( p_secObj );
		if ( SSecPrjEstaVacia ( p_secObj ) != 1 )
		{
			printf( "Error caso 8: tras vaciar la secuencia deberia estar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la secuencia\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecPrjDestruir ( &p_secObj );

	if ( ES_VALIDO ( p_secObj ) )
	{
		printf( "Error caso 9: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

/* Las parejas quedan en el orden de insercion; EliminarElem fuera de rango da
   0 sin tocar nada. */
static int TestSSecPrjOrden01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecPrjOrden 01:\n" );

	int iV [ 3 ] = { 30, 10, 20 };
	SSecuenciaParejas * p_secObj = SSecPrjCrear ();
	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ( SSecPrjInsertarExt ( p_secObj, &iV [ 0 ], &iV [ 0 ] ) != 1 ) ||
			 ( SSecPrjInsertarExt ( p_secObj, &iV [ 1 ], &iV [ 1 ] ) != 1 ) ||
			 ( SSecPrjInsertarExt ( p_secObj, &iV [ 2 ], &iV [ 2 ] ) != 1 ) )
		{
			printf( "Error caso 1: se esperaba poder insertar las tres parejas\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SPrjObtenerPrimero ( SSecPrjElemento ( p_secObj, 0 ) ) != (void *) &iV [ 0 ] ) ||
			 ( SPrjObtenerPrimero ( SSecPrjElemento ( p_secObj, 1 ) ) != (void *) &iV [ 1 ] ) ||
			 ( SPrjObtenerPrimero ( SSecPrjElemento ( p_secObj, 2 ) ) != (void *) &iV [ 2 ] ) )
		{
			printf( "Error caso 2: deberian quedar en el orden de insercion\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecPrjEliminarElem ( p_secObj, 3 ) != 0 ) || ( SSecPrjEliminarElem ( p_secObj, -1 ) != 0 ) ||
			 ( SSecPrjNumElementos ( p_secObj ) != 3 ) )
		{
			printf( "Error caso 3: eliminar fuera de rango deberia dar 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecPrjEliminarElem ( p_secObj, 1 ) != 1 ) ||
			 ( SPrjObtenerPrimero ( SSecPrjElemento ( p_secObj, 1 ) ) != (void *) &iV [ 2 ] ) )
		{
			printf( "Error caso 4: tras eliminar la del medio la segunda deberia ser la de 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecPrjInsertar ( p_secObj, NULL ) != 0 ) || ( SSecPrjInsertarExt ( NULL, &iV [ 0 ], &iV [ 1 ] ) != 0 ) ||
			 ( SSecPrjNumElementos ( p_secObj ) != 2 ) )
		{
			printf( "Error caso 5: con una pareja o una secuencia nula se esperaba 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la secuencia\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecPrjDestruir ( &p_secObj );
	return ( iRes );
}

static int TestSSecPrjInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecPrjInvalidos 01:\n" );

	if ( SSecPrjEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: una secuencia nula no deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SSecPrjNumElementos ( NULL ) != 0 )
	{
		printf( "Error caso 2: una secuencia nula deberia tener 0 elementos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecuenciaParejas * p_secNula = NULL;
	SSecPrjDestruir ( &p_secNula );
	return ( iRes );
}



int TestSSecuenciaParejas ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SSecuenciaParejas]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSSecPrjOperaciones01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecPrjOrden01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecPrjInvalidos01 () == BOOL_VAL_CIERTO ) )
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
