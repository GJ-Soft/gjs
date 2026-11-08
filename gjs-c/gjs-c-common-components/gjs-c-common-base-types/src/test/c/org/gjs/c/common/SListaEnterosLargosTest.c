#include "Base.h"

#include "SListaEnterosLargos.h"



/* Comprueba numero y orden de los valores, sin mover el cursor. */
static int VerificarContenido ( SListaEnterosLargos * p_lisObj, long * p_lEsperados, int iNum )
{
	int iRes = BOOL_VAL_CIERTO;

	if ( SLisIntlNumElementos ( p_lisObj ) != iNum )
	{
		printf( "  Verificacion: se esperaban %d elementos: %d\n", iNum, SLisIntlNumElementos ( p_lisObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	int iPos = 0;
	while ( ( iPos < iNum ) && ( iRes == BOOL_VAL_CIERTO ) )
	{
		if ( SLisIntlElemento ( p_lisObj, iPos ) != p_lEsperados [ iPos ] )
		{
			printf( "  Verificacion: en pos %d se esperaba %ld: %ld\n", iPos, p_lEsperados [ iPos ], SLisIntlElemento ( p_lisObj, iPos ) );
			iRes = BOOL_VAL_FALSO;
		}
		iPos = iPos + 1;
	}
	return ( iRes );
}

static SListaEnterosLargos * CrearListaEnteros ( long * p_lValores, int iNum )
{
	SListaEnterosLargos * p_lisObj = SLisIntlCrear ();
	int iPos = 0;
	while ( ES_VALIDO ( p_lisObj ) && ( iPos < iNum ) )
	{
		SLisIntlInsertarAlFinal ( p_lisObj, p_lValores [ iPos ] );
		iPos = iPos + 1;
	}
	return ( p_lisObj );
}



static int TestSLisIntlOperaciones01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisIntlOperaciones 01:\n" );

	SListaEnterosLargos * p_lisObj = SLisIntlCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( ( SLisIntlEsValida ( p_lisObj ) != 1 ) || ( SLisIntlEstaVacia ( p_lisObj ) != 1 ) )
		{
			printf( "Error caso 1: la lista recien creada deberia ser valida y estar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisIntlInsertarAlFinal ( p_lisObj, 1000000LL ) != 1 ) ||
			 ( SLisIntlInsertarAlFinal ( p_lisObj, 2000000LL ) != 1 ) ||
			 ( SLisIntlInsertarAlFinal ( p_lisObj, 3000000LL ) != 1 ) )
		{
			printf( "Error caso 2: se esperaba poder insertar los tres enteros largos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisIntlNumElementos ( p_lisObj ) != 3 ) || ( SLisIntlElemento ( p_lisObj, 1 ) != 2000000LL ) )
		{
			printf( "Error caso 3: deberia haber 3 elementos y el del indice 1 ser 2000000\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Insertar al inicio desplaza el resto. */
		if ( ( SLisIntlInsertarAlInicio ( p_lisObj, 500000LL ) != 1 ) || ( SLisIntlElemento ( p_lisObj, 0 ) != 500000LL ) )
		{
			printf( "Error caso 4: insertar al inicio deberia dejar 500000 en la cabeza\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Modificar un elemento por posicion. */
		if ( ( SLisIntlEstablecerElem ( p_lisObj, 0, 550000LL ) != 1 ) || ( SLisIntlElemento ( p_lisObj, 0 ) != 550000LL ) )
		{
			printf( "Error caso 5: el elemento 0 deberia poder modificarse a 550000\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisIntlExiste ( p_lisObj, 2000000LL ) != 1 ) || ( SLisIntlExiste ( p_lisObj, 7LL ) != 0 ) )
		{
			printf( "Error caso 6: existe deberia encontrar 2000000 y no 7\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisIntlBuscar ( p_lisObj, 3000000LL ) != 3 )
		{
			printf( "Error caso 7: buscar 3000000 deberia devolver el indice 3\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Eliminar el primero. */
		if ( ( SLisIntlEliminarElem ( p_lisObj, 0 ) != 1 ) ||
			 ( SLisIntlNumElementos ( p_lisObj ) != 3 ) || ( SLisIntlElemento ( p_lisObj, 0 ) != 1000000LL ) )
		{
			printf( "Error caso 8: tras eliminar el primero la cabeza deberia ser 1000000\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisIntlVaciar ( p_lisObj );
		if ( SLisIntlEstaVacia ( p_lisObj ) != 1 )
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
	SLisIntlDestruir ( &p_lisObj );

	if ( ES_VALIDO ( p_lisObj ) )
	{
		printf( "Error caso 10: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSLisIntlCursor01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisIntlCursor 01:\n" );

	SListaEnterosLargos * p_lisObj = SLisIntlCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		SLisIntlInsertarAlFinal ( p_lisObj, 10LL );
		SLisIntlInsertarAlFinal ( p_lisObj, 20LL );
		SLisIntlInsertarAlFinal ( p_lisObj, 30LL );

		SLisIntlInicio ( p_lisObj );
		if ( ( SLisIntlActual ( p_lisObj ) != 10LL ) || ( SLisIntlEstaEnInicio ( p_lisObj ) != 1 ) )
		{
			printf( "Error caso 1: el inicio deberia ser 10\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisIntlSiguiente ( p_lisObj );
		if ( SLisIntlActual ( p_lisObj ) != 20LL )
		{
			printf( "Error caso 2: el siguiente del inicio deberia ser 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisIntlFinal ( p_lisObj );
		if ( ( SLisIntlActual ( p_lisObj ) != 30LL ) || ( SLisIntlEstaEnFinal ( p_lisObj ) != 1 ) )
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
	SLisIntlDestruir ( &p_lisObj );
	return ( iRes );
}

static int TestSLisIntlInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisIntlInvalidos 01:\n" );

	if ( SLisIntlEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: una lista nula no deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLisIntlNumElementos ( NULL ) != 0 )
	{
		printf( "Error caso 2: una lista nula deberia tener 0 elementos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SListaEnterosLargos * p_lisNula = NULL;
	SLisIntlDestruir ( &p_lisNula );
	return ( iRes );
}





/* Funciones de conjunto anadidas en septiembre de 2026. Se comprueban contra
   valores ABSOLUTOS: es lo unico que caza los dos defectos que tuvieron al
   nacer —el indicador de error invertido, que hacia que estas funciones no
   recorrieran nada, y los centinelas de Min/Max cambiados—, porque los dos
   dejaban una funcion que compila, no avisa y siempre contesta lo mismo. */
static int TestSLisIntlConjunto01 ()
{
	int					iRes = BOOL_VAL_CIERTO;
	long			lMin;
	long			lMax;
	double				dMed;
	SListaEnterosLargos *	p_objObj;
	SListaEnterosLargos *	p_objUnicos;

	printf( "Test SLisIntlConjunto 01:\n" );

	/* { 5, 2, 9, 5 }: cuatro elementos, con el 5 repetido. */
	p_objObj = SLisIntlCrear ();
	SLisIntlInsertar ( p_objObj, 5L );
	SLisIntlInsertar ( p_objObj, 2L );
	SLisIntlInsertar ( p_objObj, 9L );
	SLisIntlInsertar ( p_objObj, 5L );

	if ( SLisIntlMin ( p_objObj ) != 2L )
	{
		printf( "Error caso 1: el minimo deberia ser 2L: %ld\n", SLisIntlMin ( p_objObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLisIntlMax ( p_objObj ) != 9L )
	{
		printf( "Error caso 2: el maximo deberia ser 9L: %ld\n", SLisIntlMax ( p_objObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	SLisIntlObtenerParametros ( p_objObj, &lMin, &lMax, &dMed );
	if ( ( lMin != 2L ) || ( lMax != 9L ) )
	{
		printf( "Error caso 3: ObtenerParametros deberia dar 2L y 9L: %ld y %ld\n", lMin, lMax );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( dMed < 5.25 - 0.001 ) || ( dMed > 5.25 + 0.001 ) )
	{
		printf( "Error caso 4: la media deberia ser 5.25: %f\n", dMed );
		iRes = BOOL_VAL_FALSO;
	}
	/* Cuatro elementos y uno repetido: tres unicos. */
	if ( SLisIntlTieneRepetidos ( p_objObj ) != 1 )
	{
		printf( "Error caso 5: deberia detectar repetidos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	p_objUnicos = SLisIntlExtraerUnicos ( p_objObj );
	if ( ES_NULO ( p_objUnicos ) )
	{
		printf( "Error caso 6: ExtraerUnicos no deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SLisIntlNumElementos ( p_objUnicos ) != 3 )
		{
			printf( "Error caso 7: deberian quedar 3 unicos: %d\n", SLisIntlNumElementos ( p_objUnicos ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisIntlTieneRepetidos ( p_objUnicos ) != 0 )
		{
			printf( "Error caso 8: los unicos no deberian tener repetidos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisIntlDestruir ( &p_objUnicos );
	}
	if ( SLisIntlDefinidaPositiva ( p_objObj ) != 1 )
	{
		printf( "Error caso 9: DefinidaPositiva deberia dar 1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLisIntlSemidefinidaPositiva ( p_objObj ) != 1 )
	{
		printf( "Error caso 10: SemidefinidaPositiva deberia dar 1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisIntlDestruir ( &p_objObj );

	/* Lista vacia: ni division por cero ni valores sin inicializar. */
	p_objObj = SLisIntlCrear ();
	lMin = 7;
	lMax = 7;
	dMed = 7.0;
	SLisIntlObtenerParametros ( p_objObj, &lMin, &lMax, &dMed );
	if ( ( dMed < -0.001 ) || ( dMed > 0.001 ) )
	{
		printf( "Error caso 11: con 0 elementos la media deberia ser 0 y no NaN: %f\n", dMed );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLisIntlTieneRepetidos ( p_objObj ) != 0 )
	{
		printf( "Error caso 12: una coleccion vacia no tiene repetidos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisIntlDestruir ( &p_objObj );

	/* Objeto invalido: ni cuelga ni inventa. */
	if ( SLisIntlMin ( NULL ) != 0 )
	{
		printf( "Error caso 13: con objeto nulo se esperaba 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SLisIntlExtraerUnicos ( NULL ) ) )
	{
		printf( "Error caso 14: con objeto nulo ExtraerUnicos deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	ErrLimpiar ();
	return ( iRes );
}


/* Las de orden, que solo tienen las listas. */
static int TestSLisIntlOrden01 ()
{
	int					iRes = BOOL_VAL_CIERTO;
	SListaEnterosLargos *	p_lisObj;
	SListaEnterosLargos *	p_lisOrd;

	printf( "Test SLisIntlOrden 01:\n" );

	p_lisObj = SLisIntlCrear ();
	SLisIntlInsertar ( p_lisObj, 5L );
	SLisIntlInsertar ( p_lisObj, 2L );
	SLisIntlInsertar ( p_lisObj, 9L );
	SLisIntlInsertar ( p_lisObj, 5L );

	/* { 5, 2, 9, 5 } no esta ordenada. */
	if ( SLisIntlEstaOrdenada ( p_lisObj ) != 0 )
	{
		printf( "Error caso 1: esa lista no esta ordenada\n" );
		iRes = BOOL_VAL_FALSO;
	}
	p_lisOrd = SLisIntlOrdenar ( p_lisObj );
	if ( ES_NULO ( p_lisOrd ) )
	{
		printf( "Error caso 2: Ordenar no deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SLisIntlNumElementos ( p_lisOrd ) != 4 )
		{
			printf( "Error caso 3: ordenar no deberia perder elementos: %d\n", SLisIntlNumElementos ( p_lisOrd ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisIntlEstaOrdenada ( p_lisOrd ) != 1 )
		{
			printf( "Error caso 4: el resultado de Ordenar deberia estar ordenado\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisIntlElemento ( p_lisOrd, 0 ) != 2L )
		{
			printf( "Error caso 5: el primero deberia ser 2L: %ld\n", SLisIntlElemento ( p_lisOrd, 0 ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisIntlElemento ( p_lisOrd, 3 ) != 9L )
		{
			printf( "Error caso 6: el ultimo deberia ser 9L: %ld\n", SLisIntlElemento ( p_lisOrd, 3 ) );
			iRes = BOOL_VAL_FALSO;
		}
		SLisIntlDestruir ( &p_lisOrd );
	}
	/* La original no se toca. */
	if ( SLisIntlEstaOrdenada ( p_lisObj ) != 0 )
	{
		printf( "Error caso 7: Ordenar no deberia modificar la lista de entrada\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisIntlDestruir ( &p_lisObj );

	/* ExtraerUnicosExt ( , 1 ) devuelve los unicos YA ordenados. */
	p_lisObj = SLisIntlCrear ();
	SLisIntlInsertar ( p_lisObj, 5L );
	SLisIntlInsertar ( p_lisObj, 2L );
	SLisIntlInsertar ( p_lisObj, 9L );
	SLisIntlInsertar ( p_lisObj, 5L );

	p_lisOrd = SLisIntlExtraerUnicosExt ( p_lisObj, 1 );
	if ( ES_NULO ( p_lisOrd ) )
	{
		printf( "Error caso 8: ExtraerUnicosExt no deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SLisIntlNumElementos ( p_lisOrd ) != 3 )
		{
			printf( "Error caso 9: deberian quedar 3 unicos: %d\n", SLisIntlNumElementos ( p_lisOrd ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisIntlEstaOrdenada ( p_lisOrd ) != 1 )
		{
			printf( "Error caso 10: con iOrdenar = 1 deberian salir ordenados\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisIntlDestruir ( &p_lisOrd );
	}
	SLisIntlDestruir ( &p_lisObj );
	ErrLimpiar ();
	return ( iRes );
}

/* Un valor en la posicion 0 y otro que es el ULTIMO de los valores: los dos
   casos que fallaban en SLista antes del arreglo del 2026-11-01. */
static int TestSLisIntlExisten01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisIntlExisten 01:\n" );

	long lVal [ 3 ] = { 10, 20, 30 };
	long lV1 [ 2 ] = { 10, 30 };
	long lV2 [ 2 ] = { 10, 99 };
	long lV3 [ 2 ] = { 99, 30 };
	long lV4 [ 2 ] = { 98, 99 };
	SListaEnterosLargos * p_lisObj = CrearListaEnteros ( lVal, 3 );
	SListaEnterosLargos * p_lis1 = CrearListaEnteros ( lV1, 2 );
	SListaEnterosLargos * p_lis2 = CrearListaEnteros ( lV2, 2 );
	SListaEnterosLargos * p_lis3 = CrearListaEnteros ( lV3, 2 );
	SListaEnterosLargos * p_lis4 = CrearListaEnteros ( lV4, 2 );
	SListaEnterosLargos * p_lisVacia = SLisIntlCrear ();
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lis1 ) && ES_VALIDO ( p_lis2 ) &&
		 ES_VALIDO ( p_lis3 ) && ES_VALIDO ( p_lis4 ) && ES_VALIDO ( p_lisVacia ) )
	{
		if ( SLisIntlExistenTodos ( p_lisObj, p_lis1 ) != 1 )
		{
			printf( "Error caso 1: { 10, 30 } estan todos en { 10, 20, 30 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisIntlExistenTodos ( p_lisObj, p_lis2 ) != 0 )
		{
			printf( "Error caso 2: en { 10, 99 } falta el 99\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisIntlExisteAlguno ( p_lisObj, p_lis2 ) != 1 )
		{
			printf( "Error caso 3: de { 10, 99 } esta el 10, en la posicion 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisIntlExisteAlguno ( p_lisObj, p_lis3 ) != 1 )
		{
			printf( "Error caso 4: de { 99, 30 } esta el 30, el ultimo de los valores\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisIntlExisteAlguno ( p_lisObj, p_lis4 ) != 0 ) ||
			 ( SLisIntlExistenTodos ( p_lisObj, p_lis4 ) != 0 ) )
		{
			printf( "Error caso 5: de { 98, 99 } no esta ninguno\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisIntlExistenTodos ( p_lisObj, p_lisVacia ) != 1 ) ||
			 ( SLisIntlExisteAlguno ( p_lisObj, p_lisVacia ) != 0 ) )
		{
			printf( "Error caso 6: con valores vacios, Todos da 1 y Alguno 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisIntlExistenTodos ( NULL, p_lis1 ) != 0 ) ||
			 ( SLisIntlExisteAlguno ( p_lisObj, NULL ) != 0 ) )
		{
			printf( "Error caso 7: con listas nulas se esperaba 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisIntlDestruir ( &p_lisObj );
	SLisIntlDestruir ( &p_lis1 );
	SLisIntlDestruir ( &p_lis2 );
	SLisIntlDestruir ( &p_lis3 );
	SLisIntlDestruir ( &p_lis4 );
	SLisIntlDestruir ( &p_lisVacia );
	return ( iRes );
}

static int TestSLisIntlInsertarLista01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisIntlInsertarLista 01:\n" );

	long lDest [ 2 ] = { 1, 2 };
	long lVal [ 3 ] = { 7, 8, 9 };
	SListaEnterosLargos * p_lisObj = CrearListaEnteros ( lDest, 2 );
	SListaEnterosLargos * p_lisVal = CrearListaEnteros ( lVal, 3 );
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisVal ) )
	{
		/* Mueve detras del cursor, en su orden, y deja los valores vacios. */
		SLisIntlMoverA ( p_lisObj, 0 );
		if ( SLisIntlInsertarLista ( p_lisObj, p_lisVal ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al insertar la lista\n" );
			iRes = BOOL_VAL_FALSO;
		}
		long lEsp1 [ 5 ] = { 1, 7, 8, 9, 2 };
		if ( VerificarContenido ( p_lisObj, lEsp1, 5 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 2: se esperaba { 1, 7, 8, 9, 2 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisIntlEstaVacia ( p_lisVal ) != 1 ) || ( SLisIntlEsValida ( p_lisVal ) != 1 ) )
		{
			printf( "Error caso 3: la lista de valores deberia quedar vacia y valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Concatenar va al final, este donde este el cursor. */
		SLisIntlInsertarAlFinal ( p_lisVal, 5 );
		SLisIntlInsertarAlFinal ( p_lisVal, 6 );
		SLisIntlMoverA ( p_lisObj, 1 );
		if ( SLisIntlConcatenarLista ( p_lisObj, p_lisVal ) != 1 )
		{
			printf( "Error caso 4: se esperaba resultado 1 al concatenar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		long lEsp2 [ 7 ] = { 1, 7, 8, 9, 2, 5, 6 };
		if ( ( VerificarContenido ( p_lisObj, lEsp2, 7 ) != BOOL_VAL_CIERTO ) ||
			 ( SLisIntlEstaVacia ( p_lisVal ) != 1 ) )
		{
			printf( "Error caso 5: se esperaba { 1, 7, 8, 9, 2, 5, 6 } y los valores vacios\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisIntlInsertarLista ( p_lisObj, NULL ) != 0 ) ||
			 ( SLisIntlConcatenarLista ( NULL, p_lisVal ) != 0 ) ||
			 ( SLisIntlConcatenarLista ( p_lisObj, p_lisObj ) != 0 ) )
		{
			printf( "Error caso 6: con listas nulas o la misma lista se esperaba 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisIntlDestruir ( &p_lisObj );
	SLisIntlDestruir ( &p_lisVal );
	return ( iRes );
}

static int TestSLisIntlListaDup01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisIntlListaDup 01:\n" );

	long lDest [ 2 ] = { 1, 2 };
	long lVal [ 2 ] = { 7, 8 };
	SListaEnterosLargos * p_lisObj = CrearListaEnteros ( lDest, 2 );
	SListaEnterosLargos * p_lisVal = CrearListaEnteros ( lVal, 2 );
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisVal ) )
	{
		SLisIntlMoverA ( p_lisObj, 0 );
		if ( SLisIntlInsertarListaDup ( p_lisObj, p_lisVal ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al insertar copias\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisIntlConcatenarListaDup ( p_lisObj, p_lisVal ) != 1 )
		{
			printf( "Error caso 2: se esperaba resultado 1 al concatenar copias\n" );
			iRes = BOOL_VAL_FALSO;
		}
		long lEsp [ 6 ] = { 1, 7, 8, 2, 7, 8 };
		if ( VerificarContenido ( p_lisObj, lEsp, 6 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 3: se esperaba { 1, 7, 8, 2, 7, 8 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Los valores quedan intactos, y son copias: cambiar una no toca el original. */
		SLisIntlEstablecerElem ( p_lisObj, 1, 70 );
		if ( VerificarContenido ( p_lisVal, lVal, 2 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 4: los valores deberian seguir { 7, 8 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisIntlInsertarListaDup ( p_lisObj, NULL ) != 0 ) ||
			 ( SLisIntlConcatenarListaDup ( NULL, p_lisVal ) != 0 ) )
		{
			printf( "Error caso 5: con listas nulas se esperaba 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisIntlDestruir ( &p_lisObj );
	SLisIntlDestruir ( &p_lisVal );
	return ( iRes );
}

static int TestSLisIntlExtraerLista01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisIntlExtraerLista 01:\n" );

	long lVal [ 5 ] = { 10, 20, 30, 20, 40 };
	long lBus [ 4 ] = { 20, 40, 99, 20 };
	SListaEnterosLargos * p_lisObj = CrearListaEnteros ( lVal, 5 );
	SListaEnterosLargos * p_lisBus = CrearListaEnteros ( lBus, 4 );
	SListaEnterosLargos * p_lisRes = NULL;
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisBus ) )
	{
		/* Una aparicion por valor buscado, en el orden de los buscados; el 99 no esta. */
		p_lisRes = SLisIntlExtraerLista ( p_lisObj, p_lisBus );
		long lEspRes [ 3 ] = { 20, 40, 20 };
		long lEspObj [ 2 ] = { 10, 30 };
		if ( ES_NULO ( p_lisRes ) || ( SLisIntlEsValida ( p_lisRes ) != 1 ) ||
			 ( VerificarContenido ( p_lisRes, lEspRes, 3 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 1: se esperaba extraer { 20, 40, 20 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( VerificarContenido ( p_lisObj, lEspObj, 2 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 2: en el origen deberia quedar { 10, 30 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Si la de SLista falla no se devuelve una envoltura vacia: se devuelve nulo. */
		if ( ES_VALIDO ( SLisIntlExtraerLista ( p_lisObj, p_lisObj ) ) ||
			 ES_VALIDO ( SLisIntlExtraerLista ( NULL, p_lisBus ) ) )
		{
			printf( "Error caso 3: con la misma lista o una nula se esperaba nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisIntlDestruir ( &p_lisObj );
	SLisIntlDestruir ( &p_lisBus );
	SLisIntlDestruir ( &p_lisRes );
	return ( iRes );
}

/* Destruye una aparicion por valor buscado; los valores no cambian. */
static int TestSLisIntlEliminarLista01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisIntlEliminarLista 01:\n" );

	long lVal [ 5 ] = { 10, 20, 30, 20, 40 };
	long lBus [ 4 ] = { 20, 40, 99, 20 };
	SListaEnterosLargos * p_lisObj = CrearListaEnteros ( lVal, 5 );
	SListaEnterosLargos * p_lisBus = CrearListaEnteros ( lBus, 4 );
	SListaEnterosLargos * p_lisVacia = SLisIntlCrear ();
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisBus ) && ES_VALIDO ( p_lisVacia ) )
	{
		/* El 99 no esta y se ignora; el 20 esta dos veces en los buscados. */
		if ( SLisIntlEliminarLista ( p_lisObj, p_lisBus ) != 1 )
		{
			printf( "Error caso 1: se esperaba 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		long lEspObj [ 2 ] = { 10, 30 };
		if ( ( SLisIntlNumElementos ( p_lisObj ) != 2 ) ||
			 ( VerificarContenido ( p_lisObj, lEspObj, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 2: deberia quedar { 10, 30 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( VerificarContenido ( p_lisBus, lBus, 4 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 3: los valores no deberian cambiar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Ya no queda ninguno: no hay nada que eliminar, y no es un error. */
		if ( ( SLisIntlEliminarLista ( p_lisObj, p_lisBus ) != 1 ) ||
			 ( SLisIntlEliminarLista ( p_lisObj, p_lisVacia ) != 1 ) ||
			 ( VerificarContenido ( p_lisObj, lEspObj, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 4: sin nada que eliminar se esperaba 1 sin cambios\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisIntlEliminarLista ( p_lisObj, p_lisObj ) != 0 ) ||
			 ( VerificarContenido ( p_lisObj, lEspObj, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 5: con la misma lista se esperaba 0 sin cambios\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisIntlEliminarLista ( p_lisObj, NULL ) != 0 ) || ( SLisIntlEliminarLista ( NULL, p_lisBus ) != 0 ) )
		{
			printf( "Error caso 6: con una lista nula se esperaba 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisIntlDestruir ( &p_lisObj );
	SLisIntlDestruir ( &p_lisBus );
	SLisIntlDestruir ( &p_lisVacia );
	return ( iRes );
}

static int TestSLisIntlOperacionesListas01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisIntlOperacionesListas 01:\n" );

	long lV1 [ 4 ] = { 1, 2, 3, 4 };
	long lV2 [ 3 ] = { 4, 2, 5 };
	SListaEnterosLargos * p_lis1 = CrearListaEnteros ( lV1, 4 );
	SListaEnterosLargos * p_lis2 = CrearListaEnteros ( lV2, 3 );
	SListaEnterosLargos * p_lisVacia = SLisIntlCrear ();
	if ( ES_VALIDO ( p_lis1 ) && ES_VALIDO ( p_lis2 ) && ES_VALIDO ( p_lisVacia ) )
	{
		/* La union es concatenacion: el 2 y el 4 salen dos veces. */
		SListaEnterosLargos * p_lisRes = SLisIntlUnion ( p_lis1, p_lis2 );
		long lEspU [ 7 ] = { 1, 2, 3, 4, 4, 2, 5 };
		if ( ES_NULO ( p_lisRes ) || ( SLisIntlEsValida ( p_lisRes ) != 1 ) ||
			 ( VerificarContenido ( p_lisRes, lEspU, 7 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 1: la union deberia ser { 1, 2, 3, 4, 4, 2, 5 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisIntlDestruir ( &p_lisRes );

		/* Interseccion y diferencia, las dos en el orden de V1. */
		p_lisRes = SLisIntlInterseccion ( p_lis1, p_lis2 );
		long lEspI [ 2 ] = { 2, 4 };
		if ( ES_NULO ( p_lisRes ) || ( VerificarContenido ( p_lisRes, lEspI, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 2: la interseccion deberia ser { 2, 4 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisIntlDestruir ( &p_lisRes );

		p_lisRes = SLisIntlDiferencia ( p_lis1, p_lis2 );
		long lEspD [ 2 ] = { 1, 3 };
		if ( ES_NULO ( p_lisRes ) || ( VerificarContenido ( p_lisRes, lEspD, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 3: la diferencia deberia ser { 1, 3 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisIntlDestruir ( &p_lisRes );

		if ( ( VerificarContenido ( p_lis1, lV1, 4 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarContenido ( p_lis2, lV2, 3 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 4: las listas de entrada no deberian cambiar\n" );
			iRes = BOOL_VAL_FALSO;
		}

		/* Con una vacia: lista nueva, valida y vacia; no nulo. */
		p_lisRes = SLisIntlInterseccion ( p_lis1, p_lisVacia );
		if ( ES_NULO ( p_lisRes ) || ( SLisIntlEsValida ( p_lisRes ) != 1 ) || ( SLisIntlEstaVacia ( p_lisRes ) != 1 ) )
		{
			printf( "Error caso 5: la interseccion con una vacia deberia ser una lista vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisIntlDestruir ( &p_lisRes );
		p_lisRes = SLisIntlDiferencia ( p_lis1, p_lisVacia );
		if ( ES_NULO ( p_lisRes ) || ( VerificarContenido ( p_lisRes, lV1, 4 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 6: V1 menos una vacia deberia ser V1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisIntlDestruir ( &p_lisRes );

		if ( ES_VALIDO ( SLisIntlUnion ( p_lis1, NULL ) ) ||
			 ES_VALIDO ( SLisIntlInterseccion ( NULL, p_lis2 ) ) ||
			 ES_VALIDO ( SLisIntlDiferencia ( p_lis1, NULL ) ) )
		{
			printf( "Error caso 7: con listas nulas se esperaba nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisIntlDestruir ( &p_lis1 );
	SLisIntlDestruir ( &p_lis2 );
	SLisIntlDestruir ( &p_lisVacia );
	ErrLimpiar ();
	return ( iRes );
}


/* La copia tiene los mismos valores en el mismo orden, con los extremos del
   tipo; cambiarla no toca el original, ni se mueve su cursor. */
static int TestSLisIntlDuplicar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisIntlDuplicar 01:\n" );

	long lVal [ 4 ] = { 0, LONG_MIN, LONG_MAX, -5 };
	SListaEnterosLargos * p_lisObj = CrearListaEnteros ( lVal, 4 );
	SListaEnterosLargos * p_lisVacia = SLisIntlCrear ();
	SListaEnterosLargos * p_lisDup = NULL;
	SListaEnterosLargos * p_lisDupVacia = NULL;
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisVacia ) )
	{
		SLisIntlMoverA ( p_lisObj, 1 );
		p_lisDup = SLisIntlDuplicar ( p_lisObj );
		if ( SLisIntlPosicion ( p_lisObj ) != 1 )
		{
			printf( "Error caso 1: el cursor del original deberia seguir en 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_NULO ( p_lisDup ) || ( p_lisDup == p_lisObj ) ||
			 ( VerificarContenido ( p_lisDup, lVal, 4 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 2: la copia deberia ser otra lista con { 0, LONG_MIN, LONG_MAX, -5 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisIntlEstablecerElem ( p_lisDup, 2, 99 );
		if ( VerificarContenido ( p_lisObj, lVal, 4 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 3: cambiar la copia no deberia tocar el original\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* La vacia se copia en otra vacia, no en nulo. */
		p_lisDupVacia = SLisIntlDuplicar ( p_lisVacia );
		if ( ES_NULO ( p_lisDupVacia ) || ( SLisIntlEsValida ( p_lisDupVacia ) != 1 ) ||
			 ( SLisIntlNumElementos ( p_lisDupVacia ) != 0 ) )
		{
			printf( "Error caso 4: la copia de una vacia deberia ser otra vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SLisIntlDuplicar ( NULL ) ) )
		{
			printf( "Error caso 5: con una lista nula se esperaba nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisIntlDestruir ( &p_lisObj );
	SLisIntlDestruir ( &p_lisVacia );
	SLisIntlDestruir ( &p_lisDup );
	SLisIntlDestruir ( &p_lisDupVacia );
	return ( iRes );
}


/* 1 solo con el cursor sobre un elemento: no en una vacia, ni deposicionada,
   ni con la lista nula. */
/* Repetidos con BuscarPrimero / BuscarSiguiente y Repeticiones. */
static int TestSLisIntlRepeticiones01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisIntlRepeticiones 01:\n" );

	long lVal [ 6 ] = { 20, 10, 20, 30, 20, 40 };
	SListaEnterosLargos * p_lisObj = CrearListaEnteros ( lVal, 6 );
	SListaEnterosLargos * p_lisVacia = SLisIntlCrear ();
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisVacia ) )
	{
		if ( ( SLisIntlBuscarPrimero ( p_lisObj, 20 ) != 0 ) ||
			 ( SLisIntlBuscarSiguiente ( p_lisObj, 20, 0 ) != 2 ) ||
			 ( SLisIntlBuscarSiguiente ( p_lisObj, 20, 2 ) != 4 ) ||
			 ( SLisIntlBuscarSiguiente ( p_lisObj, 20, 4 ) != -1 ) )
		{
			printf( "Error caso 1: el 20 deberia estar en 0, 2 y 4\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Desde la posicion siguiente, no desde la misma. */
		if ( ( SLisIntlBuscarSiguiente ( p_lisObj, 20, 1 ) != 2 ) ||
			 ( SLisIntlBuscarSiguiente ( p_lisObj, 20, 5 ) != -1 ) ||
			 ( SLisIntlBuscarSiguiente ( p_lisObj, 20, -2 ) != -1 ) ||
			 ( SLisIntlBuscar ( p_lisObj, 20 ) != 0 ) ||
			 ( SLisIntlBuscar ( p_lisObj, 40 ) != 5 ) )
		{
			printf( "Error caso 2: detras de la 1 esta en la 2, y Buscar es BuscarPrimero\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisIntlRepeticiones ( p_lisObj, 20 ) != 3 ) ||
			 ( SLisIntlRepeticiones ( p_lisObj, 40 ) != 1 ) ||
			 ( SLisIntlRepeticiones ( p_lisObj, 99 ) != 0 ) ||
			 ( SLisIntlBuscarPrimero ( p_lisObj, 99 ) != -1 ) )
		{
			printf( "Error caso 3: el 20 deberia estar 3 veces, el 40 una y el 99 ninguna\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisIntlRepeticiones ( p_lisVacia, 20 ) != 0 ) || ( SLisIntlBuscarPrimero ( p_lisVacia, 20 ) != -1 ) ||
			 ( SLisIntlRepeticiones ( NULL, 20 ) != 0 ) || ( SLisIntlBuscarSiguiente ( NULL, 20, -1 ) != -1 ) ||
			 ( SLisIntlBuscar ( NULL, 20 ) != -1 ) )
		{
			printf( "Error caso 4: vacia o nula se esperaba 0 al contar y -1 al buscar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisIntlDestruir ( &p_lisObj );
	SLisIntlDestruir ( &p_lisVacia );
	return ( iRes );
}

static int TestSLisIntlEstaPosicionada01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisIntlEstaPosicionada 01:\n" );

	SListaEnterosLargos * p_lisObj = SLisIntlCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( SLisIntlEstaPosicionada ( p_lisObj ) != 0 )
		{
			printf( "Error caso 1: una lista vacia no deberia estar posicionada\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisIntlInsertarAlFinal ( p_lisObj, 10L );
		SLisIntlInsertarAlFinal ( p_lisObj, 20L );
		SLisIntlInicio ( p_lisObj );
		if ( SLisIntlEstaPosicionada ( p_lisObj ) != 1 )
		{
			printf( "Error caso 2: tras Inicio deberia estar posicionada\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisIntlSiguiente ( p_lisObj );
		SLisIntlSiguiente ( p_lisObj );
		if ( SLisIntlEstaPosicionada ( p_lisObj ) != 0 )
		{
			printf( "Error caso 3: pasado el ultimo no deberia estar posicionada\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisIntlFinal ( p_lisObj );
		SLisIntlDeposicionar ( p_lisObj );
		if ( SLisIntlEstaPosicionada ( p_lisObj ) != 0 )
		{
			printf( "Error caso 4: tras Deposicionar no deberia estar posicionada\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisIntlEstaPosicionada ( NULL ) != 0 )
		{
			printf( "Error caso 5: con una lista nula se esperaba 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisIntlDestruir ( &p_lisObj );
	return ( iRes );
}

int TestSListaEnterosLargos ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SListaEnterosLargos]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSLisIntlOperaciones01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisIntlCursor01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisIntlInvalidos01 () == BOOL_VAL_CIERTO )  &&
			( TestSLisIntlConjunto01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisIntlOrden01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisIntlExisten01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisIntlInsertarLista01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisIntlListaDup01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisIntlExtraerLista01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisIntlEliminarLista01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisIntlOperacionesListas01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisIntlDuplicar01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisIntlRepeticiones01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisIntlEstaPosicionada01 () == BOOL_VAL_CIERTO ) )
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
