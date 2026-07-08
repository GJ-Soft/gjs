#include "Base.h"

#include "SListaEnterosLargos.h"



static int TestSLisEntlOperaciones01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisEntlOperaciones 01:\n" );

	SListaEnterosLargos * p_lisObj = SLisEntlCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( ( SLisEntlEsValida ( p_lisObj ) != 1 ) || ( SLisEntlEstaVacia ( p_lisObj ) != 1 ) )
		{
			printf( "Error caso 1: la lista recien creada deberia ser valida y estar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisEntlInsertarAlFinal ( p_lisObj, 1000000LL ) != 1 ) ||
			 ( SLisEntlInsertarAlFinal ( p_lisObj, 2000000LL ) != 1 ) ||
			 ( SLisEntlInsertarAlFinal ( p_lisObj, 3000000LL ) != 1 ) )
		{
			printf( "Error caso 2: se esperaba poder insertar los tres enteros largos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisEntlNumElementos ( p_lisObj ) != 3 ) || ( SLisEntlElemento ( p_lisObj, 1 ) != 2000000LL ) )
		{
			printf( "Error caso 3: deberia haber 3 elementos y el del indice 1 ser 2000000\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Insertar al inicio desplaza el resto. */
		if ( ( SLisEntlInsertarAlInicio ( p_lisObj, 500000LL ) != 1 ) || ( SLisEntlElemento ( p_lisObj, 0 ) != 500000LL ) )
		{
			printf( "Error caso 4: insertar al inicio deberia dejar 500000 en la cabeza\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Modificar un elemento por posicion. */
		if ( ( SLisEntlEstablecerElem ( p_lisObj, 0, 550000LL ) != 1 ) || ( SLisEntlElemento ( p_lisObj, 0 ) != 550000LL ) )
		{
			printf( "Error caso 5: el elemento 0 deberia poder modificarse a 550000\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisEntlExiste ( p_lisObj, 2000000LL ) != 1 ) || ( SLisEntlExiste ( p_lisObj, 7LL ) != 0 ) )
		{
			printf( "Error caso 6: existe deberia encontrar 2000000 y no 7\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisEntlBuscar ( p_lisObj, 3000000LL ) != 3 )
		{
			printf( "Error caso 7: buscar 3000000 deberia devolver el indice 3\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Eliminar el primero. */
		if ( ( SLisEntlEliminarElem ( p_lisObj, 0 ) != 1 ) ||
			 ( SLisEntlNumElementos ( p_lisObj ) != 3 ) || ( SLisEntlElemento ( p_lisObj, 0 ) != 1000000LL ) )
		{
			printf( "Error caso 8: tras eliminar el primero la cabeza deberia ser 1000000\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisEntlVaciar ( p_lisObj );
		if ( SLisEntlEstaVacia ( p_lisObj ) != 1 )
		{
			printf( "Error caso 9: tras vaciar la lista deberia estar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisEntlDestruir ( &p_lisObj );

	if ( ES_VALIDO ( p_lisObj ) )
	{
		printf( "Error caso 10: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSLisEntlCursor01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisEntlCursor 01:\n" );

	SListaEnterosLargos * p_lisObj = SLisEntlCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		SLisEntlInsertarAlFinal ( p_lisObj, 10LL );
		SLisEntlInsertarAlFinal ( p_lisObj, 20LL );
		SLisEntlInsertarAlFinal ( p_lisObj, 30LL );

		SLisEntlInicio ( p_lisObj );
		if ( ( SLisEntlActual ( p_lisObj ) != 10LL ) || ( SLisEntlEstaEnInicio ( p_lisObj ) != 1 ) )
		{
			printf( "Error caso 1: el inicio deberia ser 10\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisEntlSiguiente ( p_lisObj );
		if ( SLisEntlActual ( p_lisObj ) != 20LL )
		{
			printf( "Error caso 2: el siguiente del inicio deberia ser 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisEntlFinal ( p_lisObj );
		if ( ( SLisEntlActual ( p_lisObj ) != 30LL ) || ( SLisEntlEstaEnFinal ( p_lisObj ) != 1 ) )
		{
			printf( "Error caso 3: el final deberia ser 30\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisEntlDestruir ( &p_lisObj );
	return ( iRes );
}

static int TestSLisEntlInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisEntlInvalidos 01:\n" );

	if ( SLisEntlEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: una lista nula no deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLisEntlNumElementos ( NULL ) != 0 )
	{
		printf( "Error caso 2: una lista nula deberia tener 0 elementos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SListaEnterosLargos * p_lisNula = NULL;
	SLisEntlDestruir ( &p_lisNula );
	return ( iRes );
}



int TestSListaEnterosLargos ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SListaEnterosLargos]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSLisEntlOperaciones01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisEntlCursor01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisEntlInvalidos01 () == BOOL_VAL_CIERTO ) )
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
