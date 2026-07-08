#include "Base.h"

#include "SListaParejas.h"



static int TestSLisPrjOperaciones01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisPrjOperaciones 01:\n" );

	/* La pareja guarda los punteros sin poseerlos; los datos viven en la pila del test. */
	int iA = 1;
	int iB = 2;
	int iC = 3;
	int iD = 4;
	SListaParejas * p_lisObj = SLisPrjCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( ( SLisPrjEsValida ( p_lisObj ) != 1 ) || ( SLisPrjEstaVacia ( p_lisObj ) != 1 ) )
		{
			printf( "Error caso 1: la lista recien creada deberia ser valida y estar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* InsertarExt crea la pareja a partir de dos punteros. */
		if ( SLisPrjInsertarExt ( p_lisObj, &iA, &iB ) != 1 )
		{
			printf( "Error caso 2: se esperaba resultado 1 al insertar la pareja\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisPrjNumElementos ( p_lisObj ) != 1 )
		{
			printf( "Error caso 3: la lista deberia tener 1 elemento\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SPrjObtenerPrimero ( SLisPrjElemento ( p_lisObj, 0 ) ) != (void *) &iA ) ||
			 ( SPrjObtenerSegundo ( SLisPrjElemento ( p_lisObj, 0 ) ) != (void *) &iB ) )
		{
			printf( "Error caso 4: la pareja deberia guardar los punteros a iA e iB\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Insertar una pareja ya creada ( la lista pasa a poseerla ). */
		if ( SLisPrjInsertar ( p_lisObj, SPrjCrearSoloPtr ( &iC, &iD ) ) != 1 )
		{
			printf( "Error caso 5: se esperaba poder insertar una pareja creada aparte\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisPrjNumElementos ( p_lisObj ) != 2 ) ||
			 ( SPrjObtenerPrimero ( SLisPrjElemento ( p_lisObj, 1 ) ) != (void *) &iC ) )
		{
			printf( "Error caso 6: la segunda pareja deberia guardar el puntero a iC\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Eliminar el primero. */
		if ( ( SLisPrjEliminarElem ( p_lisObj, 0 ) != 1 ) || ( SLisPrjNumElementos ( p_lisObj ) != 1 ) )
		{
			printf( "Error caso 7: tras eliminar deberia quedar 1 elemento\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisPrjVaciar ( p_lisObj );
		if ( SLisPrjEstaVacia ( p_lisObj ) != 1 )
		{
			printf( "Error caso 8: tras vaciar la lista deberia estar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisPrjDestruir ( &p_lisObj );

	if ( ES_VALIDO ( p_lisObj ) )
	{
		printf( "Error caso 9: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSLisPrjInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisPrjInvalidos 01:\n" );

	if ( SLisPrjEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: una lista nula no deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLisPrjNumElementos ( NULL ) != 0 )
	{
		printf( "Error caso 2: una lista nula deberia tener 0 elementos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SListaParejas * p_lisNula = NULL;
	SLisPrjDestruir ( &p_lisNula );
	return ( iRes );
}



int TestSListaParejas ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SListaParejas]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSLisPrjOperaciones01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisPrjInvalidos01 () == BOOL_VAL_CIERTO ) )
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
