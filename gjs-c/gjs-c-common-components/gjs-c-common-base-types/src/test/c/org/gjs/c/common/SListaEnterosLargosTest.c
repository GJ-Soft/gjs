#include "Base.h"

#include "SListaEnterosLargos.h"



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


int TestSListaEnterosLargos ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SListaEnterosLargos]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSLisIntlOperaciones01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisIntlCursor01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisIntlInvalidos01 () == BOOL_VAL_CIERTO )  &&
			( TestSLisIntlConjunto01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisIntlOrden01 () == BOOL_VAL_CIERTO ) )
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
