#include "Base.h"

#include "SListaEnteros.h"



/* Recorre la lista comprobando numero y orden de los valores. */
static int VerificarContenido ( SListaEnteros * p_lisObj, int * p_iEsperados, int iNum )
{
	int iRes = BOOL_VAL_CIERTO;

	if ( SLisIntNumElementos ( p_lisObj ) != iNum )
	{
		printf( "  Verificacion: se esperaban %d elementos: %d\n", iNum, SLisIntNumElementos ( p_lisObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	int iPos = 0;
	while ( ( iPos < iNum ) && ( iRes == BOOL_VAL_CIERTO ) )
	{
		if ( SLisIntElemento ( p_lisObj, iPos ) != p_iEsperados [ iPos ] )
		{
			printf( "  Verificacion: en pos %d se esperaba %d: %d\n", iPos, p_iEsperados [ iPos ], SLisIntElemento ( p_lisObj, iPos ) );
			iRes = BOOL_VAL_FALSO;
		}
		iPos = iPos + 1;
	}
	return ( iRes );
}

static SListaEnteros * CrearListaEnteros ( int * p_iValores, int iNum )
{
	SListaEnteros * p_lisObj = SLisIntCrear ();
	int iPos = 0;
	while ( ES_VALIDO ( p_lisObj ) && ( iPos < iNum ) )
	{
		SLisIntInsertarAlFinal ( p_lisObj, p_iValores [ iPos ] );
		iPos = iPos + 1;
	}
	return ( p_lisObj );
}



static int TestSLisIntCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisIntCrear 01:\n" );

	SListaEnteros * p_lisObj = SLisIntCrear ();
	if ( ES_NULO ( p_lisObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SLisIntEsValida ( p_lisObj ) != 1 )
		{
			printf( "Error caso 2: la lista recien creada deberia ser valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisIntEstaVacia ( p_lisObj ) != 1 )
		{
			printf( "Error caso 3: la lista recien creada deberia estar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisIntNumElementos ( p_lisObj ) != 0 )
		{
			printf( "Error caso 4: se esperaban 0 elementos\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SLisIntDestruir ( &p_lisObj );

	if ( ES_VALIDO ( p_lisObj ) )
	{
		printf( "Error caso 5: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSLisIntInsertar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisIntInsertar 01:\n" );

	SListaEnteros * p_lisObj = SLisIntCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		SLisIntInsertarAlFinal ( p_lisObj, 10 );
		SLisIntInsertarAlFinal ( p_lisObj, 20 );
		SLisIntInsertarAlFinal ( p_lisObj, 30 );

		int iEsp1 [ 3 ] = { 10, 20, 30 };
		if ( VerificarContenido ( p_lisObj, iEsp1, 3 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 1: contenido incorrecto tras insertar al final\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Fuera de rango devuelve -1. */
		if ( SLisIntElemento ( p_lisObj, 5 ) != -1 )
		{
			printf( "Error caso 2: un indice fuera de rango deberia devolver -1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Insertar en medio ( detras del indice 0 ). */
		if ( SLisIntInsertarElem ( p_lisObj, 0, 15 ) != 1 )
		{
			printf( "Error caso 3: se esperaba resultado 1 al insertar en medio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		int iEsp2 [ 4 ] = { 10, 15, 20, 30 };
		if ( VerificarContenido ( p_lisObj, iEsp2, 4 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 4: contenido incorrecto tras insertar en medio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Insertar al inicio. */
		SLisIntInsertarAlInicio ( p_lisObj, 5 );
		if ( SLisIntElemento ( p_lisObj, 0 ) != 5 )
		{
			printf( "Error caso 5: el primer elemento deberia ser el 5\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisIntDestruir ( &p_lisObj );
	return ( iRes );
}

static int TestSLisIntCursor01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisIntCursor 01:\n" );

	SListaEnteros * p_lisObj = SLisIntCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		SLisIntInsertarAlFinal ( p_lisObj, 10 );
		SLisIntInsertarAlFinal ( p_lisObj, 20 );
		SLisIntInsertarAlFinal ( p_lisObj, 30 );

		SLisIntInicio ( p_lisObj );
		if ( ( SLisIntPosicion ( p_lisObj ) != 0 ) || ( SLisIntActual ( p_lisObj ) != 10 ) )
		{
			printf( "Error caso 1: el inicio deberia situar el cursor en el 10\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisIntSiguiente ( p_lisObj );
		if ( SLisIntActual ( p_lisObj ) != 20 )
		{
			printf( "Error caso 2: el siguiente deberia situar el cursor en el 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisIntFinal ( p_lisObj );
		if ( ( SLisIntActual ( p_lisObj ) != 30 ) || ( SLisIntEstaEnFinal ( p_lisObj ) != 1 ) )
		{
			printf( "Error caso 3: el final deberia situar el cursor en el 30\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisIntAnterior ( p_lisObj );
		if ( SLisIntActual ( p_lisObj ) != 20 )
		{
			printf( "Error caso 4: el anterior deberia situar el cursor en el 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisIntDestruir ( &p_lisObj );
	return ( iRes );
}

static int TestSLisIntBuscar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisIntBuscar 01:\n" );

	SListaEnteros * p_lisObj = SLisIntCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		SLisIntInsertarAlFinal ( p_lisObj, 10 );
		SLisIntInsertarAlFinal ( p_lisObj, 20 );
		SLisIntInsertarAlFinal ( p_lisObj, 30 );

		if ( SLisIntBuscar ( p_lisObj, 20 ) != 1 )
		{
			printf( "Error caso 1: el 20 deberia estar en la posicion 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisIntBuscar ( p_lisObj, 99 ) != -1 )
		{
			printf( "Error caso 2: el 99 no deberia encontrarse\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisIntExiste ( p_lisObj, 30 ) != 1 )
		{
			printf( "Error caso 3: el 30 deberia existir\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisIntExiste ( p_lisObj, 99 ) != 0 )
		{
			printf( "Error caso 4: el 99 no deberia existir\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisIntDestruir ( &p_lisObj );
	return ( iRes );
}

static int TestSLisIntEliminar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisIntEliminar 01:\n" );

	SListaEnteros * p_lisObj = SLisIntCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		SLisIntInsertarAlFinal ( p_lisObj, 10 );
		SLisIntInsertarAlFinal ( p_lisObj, 20 );
		SLisIntInsertarAlFinal ( p_lisObj, 30 );

		SLisIntEliminarElem ( p_lisObj, 1 );
		int iEsp [ 2 ] = { 10, 30 };
		if ( VerificarContenido ( p_lisObj, iEsp, 2 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 1: contenido incorrecto tras eliminar el elemento 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisIntVaciar ( p_lisObj ) != 1 )
		{
			printf( "Error caso 2: se esperaba resultado 1 al vaciar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisIntEstaVacia ( p_lisObj ) != 1 )
		{
			printf( "Error caso 3: la lista deberia quedar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisIntDestruir ( &p_lisObj );
	return ( iRes );
}

static int TestSLisIntInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisIntInvalidos 01:\n" );

	if ( SLisIntEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: una lista nula no deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLisIntNumElementos ( NULL ) != 0 )
	{
		printf( "Error caso 2: el numero de elementos de una lista nula deberia ser 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLisIntEstaVacia ( NULL ) != 1 )
	{
		printf( "Error caso 3: una lista nula deberia considerarse vacia\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SListaEnteros * p_lisNula = NULL;
	SLisIntDestruir ( &p_lisNula );
	return ( iRes );
}





/* Funciones de conjunto anadidas en septiembre de 2026. Se comprueban contra
   valores ABSOLUTOS: es lo unico que caza los dos defectos que tuvieron al
   nacer —el indicador de error invertido, que hacia que estas funciones no
   recorrieran nada, y los centinelas de Min/Max cambiados—, porque los dos
   dejaban una funcion que compila, no avisa y siempre contesta lo mismo. */
static int TestSLisIntConjunto01 ()
{
	int					iRes = BOOL_VAL_CIERTO;
	int			iMin;
	int			iMax;
	double				dMed;
	SListaEnteros *	p_objObj;
	SListaEnteros *	p_objUnicos;

	printf( "Test SLisIntConjunto 01:\n" );

	/* { 5, 2, 9, 5 }: cuatro elementos, con el 5 repetido. */
	p_objObj = SLisIntCrear ();
	SLisIntInsertar ( p_objObj, 5 );
	SLisIntInsertar ( p_objObj, 2 );
	SLisIntInsertar ( p_objObj, 9 );
	SLisIntInsertar ( p_objObj, 5 );

	if ( SLisIntMin ( p_objObj ) != 2 )
	{
		printf( "Error caso 1: el minimo deberia ser 2: %d\n", SLisIntMin ( p_objObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLisIntMax ( p_objObj ) != 9 )
	{
		printf( "Error caso 2: el maximo deberia ser 9: %d\n", SLisIntMax ( p_objObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	SLisIntObtenerParametros ( p_objObj, &iMin, &iMax, &dMed );
	if ( ( iMin != 2 ) || ( iMax != 9 ) )
	{
		printf( "Error caso 3: ObtenerParametros deberia dar 2 y 9: %d y %d\n", iMin, iMax );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( dMed < 5.25 - 0.001 ) || ( dMed > 5.25 + 0.001 ) )
	{
		printf( "Error caso 4: la media deberia ser 5.25: %f\n", dMed );
		iRes = BOOL_VAL_FALSO;
	}
	/* Cuatro elementos y uno repetido: tres unicos. */
	if ( SLisIntTieneRepetidos ( p_objObj ) != 1 )
	{
		printf( "Error caso 5: deberia detectar repetidos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	p_objUnicos = SLisIntExtraerUnicos ( p_objObj );
	if ( ES_NULO ( p_objUnicos ) )
	{
		printf( "Error caso 6: ExtraerUnicos no deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SLisIntNumElementos ( p_objUnicos ) != 3 )
		{
			printf( "Error caso 7: deberian quedar 3 unicos: %d\n", SLisIntNumElementos ( p_objUnicos ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisIntTieneRepetidos ( p_objUnicos ) != 0 )
		{
			printf( "Error caso 8: los unicos no deberian tener repetidos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisIntDestruir ( &p_objUnicos );
	}
	if ( SLisIntDefinidaPositiva ( p_objObj ) != 1 )
	{
		printf( "Error caso 9: DefinidaPositiva deberia dar 1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLisIntSemidefinidaPositiva ( p_objObj ) != 1 )
	{
		printf( "Error caso 10: SemidefinidaPositiva deberia dar 1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisIntDestruir ( &p_objObj );

	/* Lista vacia: ni division por cero ni valores sin inicializar. */
	p_objObj = SLisIntCrear ();
	iMin = 7;
	iMax = 7;
	dMed = 7.0;
	SLisIntObtenerParametros ( p_objObj, &iMin, &iMax, &dMed );
	if ( ( dMed < -0.001 ) || ( dMed > 0.001 ) )
	{
		printf( "Error caso 11: con 0 elementos la media deberia ser 0 y no NaN: %f\n", dMed );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLisIntTieneRepetidos ( p_objObj ) != 0 )
	{
		printf( "Error caso 12: una coleccion vacia no tiene repetidos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisIntDestruir ( &p_objObj );

	/* Objeto invalido: ni cuelga ni inventa. */
	if ( SLisIntMin ( NULL ) != 0 )
	{
		printf( "Error caso 13: con objeto nulo se esperaba 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SLisIntExtraerUnicos ( NULL ) ) )
	{
		printf( "Error caso 14: con objeto nulo ExtraerUnicos deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	ErrLimpiar ();
	return ( iRes );
}


/* Las de orden, que solo tienen las listas. */
static int TestSLisIntOrden01 ()
{
	int					iRes = BOOL_VAL_CIERTO;
	SListaEnteros *	p_lisObj;
	SListaEnteros *	p_lisOrd;

	printf( "Test SLisIntOrden 01:\n" );

	p_lisObj = SLisIntCrear ();
	SLisIntInsertar ( p_lisObj, 5 );
	SLisIntInsertar ( p_lisObj, 2 );
	SLisIntInsertar ( p_lisObj, 9 );
	SLisIntInsertar ( p_lisObj, 5 );

	/* { 5, 2, 9, 5 } no esta ordenada. */
	if ( SLisIntEstaOrdenada ( p_lisObj ) != 0 )
	{
		printf( "Error caso 1: esa lista no esta ordenada\n" );
		iRes = BOOL_VAL_FALSO;
	}
	p_lisOrd = SLisIntOrdenar ( p_lisObj );
	if ( ES_NULO ( p_lisOrd ) )
	{
		printf( "Error caso 2: Ordenar no deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SLisIntNumElementos ( p_lisOrd ) != 4 )
		{
			printf( "Error caso 3: ordenar no deberia perder elementos: %d\n", SLisIntNumElementos ( p_lisOrd ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisIntEstaOrdenada ( p_lisOrd ) != 1 )
		{
			printf( "Error caso 4: el resultado de Ordenar deberia estar ordenado\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisIntElemento ( p_lisOrd, 0 ) != 2 )
		{
			printf( "Error caso 5: el primero deberia ser 2: %d\n", SLisIntElemento ( p_lisOrd, 0 ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisIntElemento ( p_lisOrd, 3 ) != 9 )
		{
			printf( "Error caso 6: el ultimo deberia ser 9: %d\n", SLisIntElemento ( p_lisOrd, 3 ) );
			iRes = BOOL_VAL_FALSO;
		}
		SLisIntDestruir ( &p_lisOrd );
	}
	/* La original no se toca. */
	if ( SLisIntEstaOrdenada ( p_lisObj ) != 0 )
	{
		printf( "Error caso 7: Ordenar no deberia modificar la lista de entrada\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisIntDestruir ( &p_lisObj );

	/* ExtraerUnicosExt ( , 1 ) devuelve los unicos YA ordenados. */
	p_lisObj = SLisIntCrear ();
	SLisIntInsertar ( p_lisObj, 5 );
	SLisIntInsertar ( p_lisObj, 2 );
	SLisIntInsertar ( p_lisObj, 9 );
	SLisIntInsertar ( p_lisObj, 5 );

	p_lisOrd = SLisIntExtraerUnicosExt ( p_lisObj, 1 );
	if ( ES_NULO ( p_lisOrd ) )
	{
		printf( "Error caso 8: ExtraerUnicosExt no deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SLisIntNumElementos ( p_lisOrd ) != 3 )
		{
			printf( "Error caso 9: deberian quedar 3 unicos: %d\n", SLisIntNumElementos ( p_lisOrd ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisIntEstaOrdenada ( p_lisOrd ) != 1 )
		{
			printf( "Error caso 10: con iOrdenar = 1 deberian salir ordenados\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisIntDestruir ( &p_lisOrd );
	}
	SLisIntDestruir ( &p_lisObj );
	ErrLimpiar ();
	return ( iRes );
}

/* Un valor en la posicion 0 y otro que es el ULTIMO de los valores: los dos
   casos que fallaban en SLista antes del arreglo del 2026-11-01. */
static int TestSLisIntExisten01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisIntExisten 01:\n" );

	int iVal [ 3 ] = { 10, 20, 30 };
	int iV1 [ 2 ] = { 10, 30 };
	int iV2 [ 2 ] = { 10, 99 };
	int iV3 [ 2 ] = { 99, 30 };
	int iV4 [ 2 ] = { 98, 99 };
	SListaEnteros * p_lisObj = CrearListaEnteros ( iVal, 3 );
	SListaEnteros * p_lis1 = CrearListaEnteros ( iV1, 2 );
	SListaEnteros * p_lis2 = CrearListaEnteros ( iV2, 2 );
	SListaEnteros * p_lis3 = CrearListaEnteros ( iV3, 2 );
	SListaEnteros * p_lis4 = CrearListaEnteros ( iV4, 2 );
	SListaEnteros * p_lisVacia = SLisIntCrear ();
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lis1 ) && ES_VALIDO ( p_lis2 ) &&
		 ES_VALIDO ( p_lis3 ) && ES_VALIDO ( p_lis4 ) && ES_VALIDO ( p_lisVacia ) )
	{
		if ( SLisIntExistenTodos ( p_lisObj, p_lis1 ) != 1 )
		{
			printf( "Error caso 1: { 10, 30 } estan todos en { 10, 20, 30 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisIntExistenTodos ( p_lisObj, p_lis2 ) != 0 )
		{
			printf( "Error caso 2: en { 10, 99 } falta el 99\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisIntExisteAlguno ( p_lisObj, p_lis2 ) != 1 )
		{
			printf( "Error caso 3: de { 10, 99 } esta el 10, en la posicion 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisIntExisteAlguno ( p_lisObj, p_lis3 ) != 1 )
		{
			printf( "Error caso 4: de { 99, 30 } esta el 30, el ultimo de los valores\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisIntExisteAlguno ( p_lisObj, p_lis4 ) != 0 ) ||
			 ( SLisIntExistenTodos ( p_lisObj, p_lis4 ) != 0 ) )
		{
			printf( "Error caso 5: de { 98, 99 } no esta ninguno\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisIntExistenTodos ( p_lisObj, p_lisVacia ) != 1 ) ||
			 ( SLisIntExisteAlguno ( p_lisObj, p_lisVacia ) != 0 ) )
		{
			printf( "Error caso 6: con valores vacios, Todos da 1 y Alguno 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisIntExistenTodos ( NULL, p_lis1 ) != 0 ) ||
			 ( SLisIntExisteAlguno ( p_lisObj, NULL ) != 0 ) )
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
	SLisIntDestruir ( &p_lisObj );
	SLisIntDestruir ( &p_lis1 );
	SLisIntDestruir ( &p_lis2 );
	SLisIntDestruir ( &p_lis3 );
	SLisIntDestruir ( &p_lis4 );
	SLisIntDestruir ( &p_lisVacia );
	return ( iRes );
}

static int TestSLisIntInsertarLista01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisIntInsertarLista 01:\n" );

	int iDest [ 2 ] = { 1, 2 };
	int iVal [ 3 ] = { 7, 8, 9 };
	SListaEnteros * p_lisObj = CrearListaEnteros ( iDest, 2 );
	SListaEnteros * p_lisVal = CrearListaEnteros ( iVal, 3 );
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisVal ) )
	{
		/* Mueve detras del cursor, en su orden, y deja los valores vacios. */
		SLisIntMoverA ( p_lisObj, 0 );
		if ( SLisIntInsertarLista ( p_lisObj, p_lisVal ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al insertar la lista\n" );
			iRes = BOOL_VAL_FALSO;
		}
		int iEsp1 [ 5 ] = { 1, 7, 8, 9, 2 };
		if ( VerificarContenido ( p_lisObj, iEsp1, 5 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 2: se esperaba { 1, 7, 8, 9, 2 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisIntEstaVacia ( p_lisVal ) != 1 ) || ( SLisIntEsValida ( p_lisVal ) != 1 ) )
		{
			printf( "Error caso 3: la lista de valores deberia quedar vacia y valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Concatenar va al final, este donde este el cursor. */
		SLisIntInsertarAlFinal ( p_lisVal, 5 );
		SLisIntInsertarAlFinal ( p_lisVal, 6 );
		SLisIntMoverA ( p_lisObj, 1 );
		if ( SLisIntConcatenarLista ( p_lisObj, p_lisVal ) != 1 )
		{
			printf( "Error caso 4: se esperaba resultado 1 al concatenar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		int iEsp2 [ 7 ] = { 1, 7, 8, 9, 2, 5, 6 };
		if ( ( VerificarContenido ( p_lisObj, iEsp2, 7 ) != BOOL_VAL_CIERTO ) ||
			 ( SLisIntEstaVacia ( p_lisVal ) != 1 ) )
		{
			printf( "Error caso 5: se esperaba { 1, 7, 8, 9, 2, 5, 6 } y los valores vacios\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisIntInsertarLista ( p_lisObj, NULL ) != 0 ) ||
			 ( SLisIntConcatenarLista ( NULL, p_lisVal ) != 0 ) ||
			 ( SLisIntConcatenarLista ( p_lisObj, p_lisObj ) != 0 ) )
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
	SLisIntDestruir ( &p_lisObj );
	SLisIntDestruir ( &p_lisVal );
	return ( iRes );
}

static int TestSLisIntListaDup01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisIntListaDup 01:\n" );

	int iDest [ 2 ] = { 1, 2 };
	int iVal [ 2 ] = { 7, 8 };
	SListaEnteros * p_lisObj = CrearListaEnteros ( iDest, 2 );
	SListaEnteros * p_lisVal = CrearListaEnteros ( iVal, 2 );
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisVal ) )
	{
		SLisIntMoverA ( p_lisObj, 0 );
		if ( SLisIntInsertarListaDup ( p_lisObj, p_lisVal ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al insertar copias\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisIntConcatenarListaDup ( p_lisObj, p_lisVal ) != 1 )
		{
			printf( "Error caso 2: se esperaba resultado 1 al concatenar copias\n" );
			iRes = BOOL_VAL_FALSO;
		}
		int iEsp [ 6 ] = { 1, 7, 8, 2, 7, 8 };
		if ( VerificarContenido ( p_lisObj, iEsp, 6 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 3: se esperaba { 1, 7, 8, 2, 7, 8 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Los valores quedan intactos, y son copias: cambiar una no toca el original. */
		SLisIntEstablecerElem ( p_lisObj, 1, 70 );
		if ( VerificarContenido ( p_lisVal, iVal, 2 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 4: los valores deberian seguir { 7, 8 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisIntInsertarListaDup ( p_lisObj, NULL ) != 0 ) ||
			 ( SLisIntConcatenarListaDup ( NULL, p_lisVal ) != 0 ) )
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
	SLisIntDestruir ( &p_lisObj );
	SLisIntDestruir ( &p_lisVal );
	return ( iRes );
}

static int TestSLisIntExtraerLista01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisIntExtraerLista 01:\n" );

	int iVal [ 5 ] = { 10, 20, 30, 20, 40 };
	int iBus [ 4 ] = { 20, 40, 99, 20 };
	SListaEnteros * p_lisObj = CrearListaEnteros ( iVal, 5 );
	SListaEnteros * p_lisBus = CrearListaEnteros ( iBus, 4 );
	SListaEnteros * p_lisRes = NULL;
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisBus ) )
	{
		/* Una aparicion por valor buscado, en el orden de los buscados; el 99 no esta. */
		p_lisRes = SLisIntExtraerLista ( p_lisObj, p_lisBus );
		int iEspRes [ 3 ] = { 20, 40, 20 };
		int iEspObj [ 2 ] = { 10, 30 };
		if ( ES_NULO ( p_lisRes ) || ( SLisIntEsValida ( p_lisRes ) != 1 ) ||
			 ( VerificarContenido ( p_lisRes, iEspRes, 3 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 1: se esperaba extraer { 20, 40, 20 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( VerificarContenido ( p_lisObj, iEspObj, 2 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 2: en el origen deberia quedar { 10, 30 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Si la de SLista falla no se devuelve una envoltura vacia: se devuelve nulo. */
		if ( ES_VALIDO ( SLisIntExtraerLista ( p_lisObj, p_lisObj ) ) ||
			 ES_VALIDO ( SLisIntExtraerLista ( NULL, p_lisBus ) ) )
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
	SLisIntDestruir ( &p_lisObj );
	SLisIntDestruir ( &p_lisBus );
	SLisIntDestruir ( &p_lisRes );
	return ( iRes );
}

/* Destruye una aparicion por valor buscado; los valores no cambian. */
static int TestSLisIntEliminarLista01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisIntEliminarLista 01:\n" );

	int iVal [ 5 ] = { 10, 20, 30, 20, 40 };
	int iBus [ 4 ] = { 20, 40, 99, 20 };
	SListaEnteros * p_lisObj = CrearListaEnteros ( iVal, 5 );
	SListaEnteros * p_lisBus = CrearListaEnteros ( iBus, 4 );
	SListaEnteros * p_lisVacia = SLisIntCrear ();
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisBus ) && ES_VALIDO ( p_lisVacia ) )
	{
		/* El 99 no esta y se ignora; el 20 esta dos veces en los buscados. */
		if ( SLisIntEliminarLista ( p_lisObj, p_lisBus ) != 1 )
		{
			printf( "Error caso 1: se esperaba 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		int iEspObj [ 2 ] = { 10, 30 };
		if ( ( SLisIntNumElementos ( p_lisObj ) != 2 ) ||
			 ( VerificarContenido ( p_lisObj, iEspObj, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 2: deberia quedar { 10, 30 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( VerificarContenido ( p_lisBus, iBus, 4 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 3: los valores no deberian cambiar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Ya no queda ninguno: no hay nada que eliminar, y no es un error. */
		if ( ( SLisIntEliminarLista ( p_lisObj, p_lisBus ) != 1 ) ||
			 ( SLisIntEliminarLista ( p_lisObj, p_lisVacia ) != 1 ) ||
			 ( VerificarContenido ( p_lisObj, iEspObj, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 4: sin nada que eliminar se esperaba 1 sin cambios\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisIntEliminarLista ( p_lisObj, p_lisObj ) != 0 ) ||
			 ( VerificarContenido ( p_lisObj, iEspObj, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 5: con la misma lista se esperaba 0 sin cambios\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisIntEliminarLista ( p_lisObj, NULL ) != 0 ) || ( SLisIntEliminarLista ( NULL, p_lisBus ) != 0 ) )
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
	SLisIntDestruir ( &p_lisObj );
	SLisIntDestruir ( &p_lisBus );
	SLisIntDestruir ( &p_lisVacia );
	return ( iRes );
}

static int TestSLisIntOperacionesListas01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisIntOperacionesListas 01:\n" );

	int iV1 [ 4 ] = { 1, 2, 3, 4 };
	int iV2 [ 3 ] = { 4, 2, 5 };
	SListaEnteros * p_lis1 = CrearListaEnteros ( iV1, 4 );
	SListaEnteros * p_lis2 = CrearListaEnteros ( iV2, 3 );
	SListaEnteros * p_lisVacia = SLisIntCrear ();
	if ( ES_VALIDO ( p_lis1 ) && ES_VALIDO ( p_lis2 ) && ES_VALIDO ( p_lisVacia ) )
	{
		/* La union es concatenacion: el 2 y el 4 salen dos veces. */
		SListaEnteros * p_lisRes = SLisIntUnion ( p_lis1, p_lis2 );
		int iEspU [ 7 ] = { 1, 2, 3, 4, 4, 2, 5 };
		if ( ES_NULO ( p_lisRes ) || ( SLisIntEsValida ( p_lisRes ) != 1 ) ||
			 ( VerificarContenido ( p_lisRes, iEspU, 7 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 1: la union deberia ser { 1, 2, 3, 4, 4, 2, 5 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisIntDestruir ( &p_lisRes );

		/* Interseccion y diferencia, las dos en el orden de V1. */
		p_lisRes = SLisIntInterseccion ( p_lis1, p_lis2 );
		int iEspI [ 2 ] = { 2, 4 };
		if ( ES_NULO ( p_lisRes ) || ( VerificarContenido ( p_lisRes, iEspI, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 2: la interseccion deberia ser { 2, 4 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisIntDestruir ( &p_lisRes );

		p_lisRes = SLisIntDiferencia ( p_lis1, p_lis2 );
		int iEspD [ 2 ] = { 1, 3 };
		if ( ES_NULO ( p_lisRes ) || ( VerificarContenido ( p_lisRes, iEspD, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 3: la diferencia deberia ser { 1, 3 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisIntDestruir ( &p_lisRes );

		if ( ( VerificarContenido ( p_lis1, iV1, 4 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarContenido ( p_lis2, iV2, 3 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 4: las listas de entrada no deberian cambiar\n" );
			iRes = BOOL_VAL_FALSO;
		}

		/* Con una vacia: lista nueva, valida y vacia; no nulo. */
		p_lisRes = SLisIntInterseccion ( p_lis1, p_lisVacia );
		if ( ES_NULO ( p_lisRes ) || ( SLisIntEsValida ( p_lisRes ) != 1 ) || ( SLisIntEstaVacia ( p_lisRes ) != 1 ) )
		{
			printf( "Error caso 5: la interseccion con una vacia deberia ser una lista vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisIntDestruir ( &p_lisRes );
		p_lisRes = SLisIntDiferencia ( p_lis1, p_lisVacia );
		if ( ES_NULO ( p_lisRes ) || ( VerificarContenido ( p_lisRes, iV1, 4 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 6: V1 menos una vacia deberia ser V1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisIntDestruir ( &p_lisRes );

		if ( ES_VALIDO ( SLisIntUnion ( p_lis1, NULL ) ) ||
			 ES_VALIDO ( SLisIntInterseccion ( NULL, p_lis2 ) ) ||
			 ES_VALIDO ( SLisIntDiferencia ( p_lis1, NULL ) ) )
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
	SLisIntDestruir ( &p_lis1 );
	SLisIntDestruir ( &p_lis2 );
	SLisIntDestruir ( &p_lisVacia );
	ErrLimpiar ();
	return ( iRes );
}

/* La copia tiene los mismos valores en el mismo orden, con los extremos del
   tipo; cambiarla no toca el original, ni se mueve su cursor. */
static int TestSLisIntDuplicar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisIntDuplicar 01:\n" );

	int iVal [ 4 ] = { 0, INT_MIN, INT_MAX, -5 };
	SListaEnteros * p_lisObj = CrearListaEnteros ( iVal, 4 );
	SListaEnteros * p_lisVacia = SLisIntCrear ();
	SListaEnteros * p_lisDup = NULL;
	SListaEnteros * p_lisDupVacia = NULL;
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisVacia ) )
	{
		SLisIntMoverA ( p_lisObj, 1 );
		p_lisDup = SLisIntDuplicar ( p_lisObj );
		if ( SLisIntPosicion ( p_lisObj ) != 1 )
		{
			printf( "Error caso 1: el cursor del original deberia seguir en 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_NULO ( p_lisDup ) || ( p_lisDup == p_lisObj ) ||
			 ( VerificarContenido ( p_lisDup, iVal, 4 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 2: la copia deberia ser otra lista con { 0, INT_MIN, INT_MAX, -5 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisIntEstablecerElem ( p_lisDup, 2, 99 );
		if ( VerificarContenido ( p_lisObj, iVal, 4 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 3: cambiar la copia no deberia tocar el original\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* La vacia se copia en otra vacia, no en nulo. */
		p_lisDupVacia = SLisIntDuplicar ( p_lisVacia );
		if ( ES_NULO ( p_lisDupVacia ) || ( SLisIntEsValida ( p_lisDupVacia ) != 1 ) ||
			 ( SLisIntNumElementos ( p_lisDupVacia ) != 0 ) )
		{
			printf( "Error caso 4: la copia de una vacia deberia ser otra vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SLisIntDuplicar ( NULL ) ) )
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
	SLisIntDestruir ( &p_lisObj );
	SLisIntDestruir ( &p_lisVacia );
	SLisIntDestruir ( &p_lisDup );
	SLisIntDestruir ( &p_lisDupVacia );
	return ( iRes );
}


/* 1 solo con el cursor sobre un elemento: no en una vacia, ni deposicionada,
   ni con la lista nula. */
/* Repetidos con BuscarPrimero / BuscarSiguiente y Repeticiones. */
static int TestSLisIntRepeticiones01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisIntRepeticiones 01:\n" );

	int iVal [ 6 ] = { 20, 10, 20, 30, 20, 40 };
	SListaEnteros * p_lisObj = CrearListaEnteros ( iVal, 6 );
	SListaEnteros * p_lisVacia = SLisIntCrear ();
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisVacia ) )
	{
		if ( ( SLisIntBuscarPrimero ( p_lisObj, 20 ) != 0 ) ||
			 ( SLisIntBuscarSiguiente ( p_lisObj, 20, 0 ) != 2 ) ||
			 ( SLisIntBuscarSiguiente ( p_lisObj, 20, 2 ) != 4 ) ||
			 ( SLisIntBuscarSiguiente ( p_lisObj, 20, 4 ) != -1 ) )
		{
			printf( "Error caso 1: el 20 deberia estar en 0, 2 y 4\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Desde la posicion siguiente, no desde la misma. */
		if ( ( SLisIntBuscarSiguiente ( p_lisObj, 20, 1 ) != 2 ) ||
			 ( SLisIntBuscarSiguiente ( p_lisObj, 20, 5 ) != -1 ) ||
			 ( SLisIntBuscarSiguiente ( p_lisObj, 20, -2 ) != -1 ) ||
			 ( SLisIntBuscar ( p_lisObj, 20 ) != 0 ) ||
			 ( SLisIntBuscar ( p_lisObj, 40 ) != 5 ) )
		{
			printf( "Error caso 2: detras de la 1 esta en la 2, y Buscar es BuscarPrimero\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisIntRepeticiones ( p_lisObj, 20 ) != 3 ) ||
			 ( SLisIntRepeticiones ( p_lisObj, 40 ) != 1 ) ||
			 ( SLisIntRepeticiones ( p_lisObj, 99 ) != 0 ) ||
			 ( SLisIntBuscarPrimero ( p_lisObj, 99 ) != -1 ) )
		{
			printf( "Error caso 3: el 20 deberia estar 3 veces, el 40 una y el 99 ninguna\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisIntRepeticiones ( p_lisVacia, 20 ) != 0 ) || ( SLisIntBuscarPrimero ( p_lisVacia, 20 ) != -1 ) ||
			 ( SLisIntRepeticiones ( NULL, 20 ) != 0 ) || ( SLisIntBuscarSiguiente ( NULL, 20, -1 ) != -1 ) ||
			 ( SLisIntBuscar ( NULL, 20 ) != -1 ) )
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
	SLisIntDestruir ( &p_lisObj );
	SLisIntDestruir ( &p_lisVacia );
	return ( iRes );
}

static int TestSLisIntEstaPosicionada01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisIntEstaPosicionada 01:\n" );

	SListaEnteros * p_lisObj = SLisIntCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( SLisIntEstaPosicionada ( p_lisObj ) != 0 )
		{
			printf( "Error caso 1: una lista vacia no deberia estar posicionada\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisIntInsertarAlFinal ( p_lisObj, 10 );
		SLisIntInsertarAlFinal ( p_lisObj, 20 );
		SLisIntInicio ( p_lisObj );
		if ( SLisIntEstaPosicionada ( p_lisObj ) != 1 )
		{
			printf( "Error caso 2: tras Inicio deberia estar posicionada\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisIntSiguiente ( p_lisObj );
		SLisIntSiguiente ( p_lisObj );
		if ( SLisIntEstaPosicionada ( p_lisObj ) != 0 )
		{
			printf( "Error caso 3: pasado el ultimo no deberia estar posicionada\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisIntFinal ( p_lisObj );
		SLisIntDeposicionar ( p_lisObj );
		if ( SLisIntEstaPosicionada ( p_lisObj ) != 0 )
		{
			printf( "Error caso 4: tras Deposicionar no deberia estar posicionada\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisIntEstaPosicionada ( NULL ) != 0 )
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
	SLisIntDestruir ( &p_lisObj );
	return ( iRes );
}

int TestSListaEnteros ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SListaEnteros]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSLisIntCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisIntInsertar01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisIntCursor01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisIntBuscar01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisIntEliminar01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisIntInvalidos01 () == BOOL_VAL_CIERTO )  &&
			( TestSLisIntConjunto01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisIntOrden01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisIntExisten01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisIntInsertarLista01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisIntListaDup01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisIntExtraerLista01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisIntEliminarLista01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisIntOperacionesListas01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisIntDuplicar01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisIntRepeticiones01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisIntEstaPosicionada01 () == BOOL_VAL_CIERTO ) )
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
