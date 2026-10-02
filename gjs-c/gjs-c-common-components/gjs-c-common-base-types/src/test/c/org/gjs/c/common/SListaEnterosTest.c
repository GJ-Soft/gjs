#include "Base.h"

#include "SListaEnteros.h"



/* Recorre la lista comprobando numero y orden de los valores. */
static int VerificarContenido ( SListaEnteros * p_lisObj, int * p_iEsperados, int iNum )
{
	int iRes = BOOL_VAL_CIERTO;

	if ( SLisEntNumElementos ( p_lisObj ) != iNum )
	{
		printf( "  Verificacion: se esperaban %d elementos: %d\n", iNum, SLisEntNumElementos ( p_lisObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	int iPos = 0;
	while ( ( iPos < iNum ) && ( iRes == BOOL_VAL_CIERTO ) )
	{
		if ( SLisEntElemento ( p_lisObj, iPos ) != p_iEsperados [ iPos ] )
		{
			printf( "  Verificacion: en pos %d se esperaba %d: %d\n", iPos, p_iEsperados [ iPos ], SLisEntElemento ( p_lisObj, iPos ) );
			iRes = BOOL_VAL_FALSO;
		}
		iPos = iPos + 1;
	}
	return ( iRes );
}



static int TestSLisEntCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisEntCrear 01:\n" );

	SListaEnteros * p_lisObj = SLisEntCrear ();
	if ( ES_NULO ( p_lisObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SLisEntEsValida ( p_lisObj ) != 1 )
		{
			printf( "Error caso 2: la lista recien creada deberia ser valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisEntEstaVacia ( p_lisObj ) != 1 )
		{
			printf( "Error caso 3: la lista recien creada deberia estar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisEntNumElementos ( p_lisObj ) != 0 )
		{
			printf( "Error caso 4: se esperaban 0 elementos\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SLisEntDestruir ( &p_lisObj );

	if ( ES_VALIDO ( p_lisObj ) )
	{
		printf( "Error caso 5: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSLisEntInsertar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisEntInsertar 01:\n" );

	SListaEnteros * p_lisObj = SLisEntCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		SLisEntInsertarAlFinal ( p_lisObj, 10 );
		SLisEntInsertarAlFinal ( p_lisObj, 20 );
		SLisEntInsertarAlFinal ( p_lisObj, 30 );

		int iEsp1 [ 3 ] = { 10, 20, 30 };
		if ( VerificarContenido ( p_lisObj, iEsp1, 3 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 1: contenido incorrecto tras insertar al final\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Fuera de rango devuelve -1. */
		if ( SLisEntElemento ( p_lisObj, 5 ) != -1 )
		{
			printf( "Error caso 2: un indice fuera de rango deberia devolver -1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Insertar en medio ( detras del indice 0 ). */
		if ( SLisEntInsertarElem ( p_lisObj, 0, 15 ) != 1 )
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
		SLisEntInsertarAlInicio ( p_lisObj, 5 );
		if ( SLisEntElemento ( p_lisObj, 0 ) != 5 )
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
	SLisEntDestruir ( &p_lisObj );
	return ( iRes );
}

static int TestSLisEntCursor01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisEntCursor 01:\n" );

	SListaEnteros * p_lisObj = SLisEntCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		SLisEntInsertarAlFinal ( p_lisObj, 10 );
		SLisEntInsertarAlFinal ( p_lisObj, 20 );
		SLisEntInsertarAlFinal ( p_lisObj, 30 );

		SLisEntInicio ( p_lisObj );
		if ( ( SLisEntPosicion ( p_lisObj ) != 0 ) || ( SLisEntActual ( p_lisObj ) != 10 ) )
		{
			printf( "Error caso 1: el inicio deberia situar el cursor en el 10\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisEntSiguiente ( p_lisObj );
		if ( SLisEntActual ( p_lisObj ) != 20 )
		{
			printf( "Error caso 2: el siguiente deberia situar el cursor en el 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisEntFinal ( p_lisObj );
		if ( ( SLisEntActual ( p_lisObj ) != 30 ) || ( SLisEntEstaEnFinal ( p_lisObj ) != 1 ) )
		{
			printf( "Error caso 3: el final deberia situar el cursor en el 30\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisEntAnterior ( p_lisObj );
		if ( SLisEntActual ( p_lisObj ) != 20 )
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
	SLisEntDestruir ( &p_lisObj );
	return ( iRes );
}

static int TestSLisEntBuscar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisEntBuscar 01:\n" );

	SListaEnteros * p_lisObj = SLisEntCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		SLisEntInsertarAlFinal ( p_lisObj, 10 );
		SLisEntInsertarAlFinal ( p_lisObj, 20 );
		SLisEntInsertarAlFinal ( p_lisObj, 30 );

		if ( SLisEntBuscar ( p_lisObj, 20 ) != 1 )
		{
			printf( "Error caso 1: el 20 deberia estar en la posicion 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisEntBuscar ( p_lisObj, 99 ) != -1 )
		{
			printf( "Error caso 2: el 99 no deberia encontrarse\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisEntExiste ( p_lisObj, 30 ) != 1 )
		{
			printf( "Error caso 3: el 30 deberia existir\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisEntExiste ( p_lisObj, 99 ) != 0 )
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
	SLisEntDestruir ( &p_lisObj );
	return ( iRes );
}

static int TestSLisEntEliminar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisEntEliminar 01:\n" );

	SListaEnteros * p_lisObj = SLisEntCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		SLisEntInsertarAlFinal ( p_lisObj, 10 );
		SLisEntInsertarAlFinal ( p_lisObj, 20 );
		SLisEntInsertarAlFinal ( p_lisObj, 30 );

		SLisEntEliminarElem ( p_lisObj, 1 );
		int iEsp [ 2 ] = { 10, 30 };
		if ( VerificarContenido ( p_lisObj, iEsp, 2 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 1: contenido incorrecto tras eliminar el elemento 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisEntVaciar ( p_lisObj ) != 1 )
		{
			printf( "Error caso 2: se esperaba resultado 1 al vaciar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisEntEstaVacia ( p_lisObj ) != 1 )
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
	SLisEntDestruir ( &p_lisObj );
	return ( iRes );
}

static int TestSLisEntInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisEntInvalidos 01:\n" );

	if ( SLisEntEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: una lista nula no deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLisEntNumElementos ( NULL ) != 0 )
	{
		printf( "Error caso 2: el numero de elementos de una lista nula deberia ser 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLisEntEstaVacia ( NULL ) != 1 )
	{
		printf( "Error caso 3: una lista nula deberia considerarse vacia\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SListaEnteros * p_lisNula = NULL;
	SLisEntDestruir ( &p_lisNula );
	return ( iRes );
}





/* Funciones de conjunto anadidas en septiembre de 2026. Se comprueban contra
   valores ABSOLUTOS: es lo unico que caza los dos defectos que tuvieron al
   nacer —el indicador de error invertido, que hacia que estas funciones no
   recorrieran nada, y los centinelas de Min/Max cambiados—, porque los dos
   dejaban una funcion que compila, no avisa y siempre contesta lo mismo. */
static int TestSLisEntConjunto01 ()
{
	int					iRes = BOOL_VAL_CIERTO;
	int			iMin;
	int			iMax;
	double				dMed;
	SListaEnteros *	p_objObj;
	SListaEnteros *	p_objUnicos;

	printf( "Test SLisEntConjunto 01:\n" );

	/* { 5, 2, 9, 5 }: cuatro elementos, con el 5 repetido. */
	p_objObj = SLisEntCrear ();
	SLisEntInsertar ( p_objObj, 5 );
	SLisEntInsertar ( p_objObj, 2 );
	SLisEntInsertar ( p_objObj, 9 );
	SLisEntInsertar ( p_objObj, 5 );

	if ( SLisEntMin ( p_objObj ) != 2 )
	{
		printf( "Error caso 1: el minimo deberia ser 2: %d\n", SLisEntMin ( p_objObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLisEntMax ( p_objObj ) != 9 )
	{
		printf( "Error caso 2: el maximo deberia ser 9: %d\n", SLisEntMax ( p_objObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	SLisEntObtenerParametros ( p_objObj, &iMin, &iMax, &dMed );
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
	if ( SLisEntTieneRepetidos ( p_objObj ) != 1 )
	{
		printf( "Error caso 5: deberia detectar repetidos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	p_objUnicos = SLisEntExtraerUnicos ( p_objObj );
	if ( ES_NULO ( p_objUnicos ) )
	{
		printf( "Error caso 6: ExtraerUnicos no deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SLisEntNumElementos ( p_objUnicos ) != 3 )
		{
			printf( "Error caso 7: deberian quedar 3 unicos: %d\n", SLisEntNumElementos ( p_objUnicos ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisEntTieneRepetidos ( p_objUnicos ) != 0 )
		{
			printf( "Error caso 8: los unicos no deberian tener repetidos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisEntDestruir ( &p_objUnicos );
	}
	if ( SLisEntDefinidaPositiva ( p_objObj ) != 1 )
	{
		printf( "Error caso 9: DefinidaPositiva deberia dar 1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLisEntSemidefinidaPositiva ( p_objObj ) != 1 )
	{
		printf( "Error caso 10: SemidefinidaPositiva deberia dar 1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisEntDestruir ( &p_objObj );

	/* Lista vacia: ni division por cero ni valores sin inicializar. */
	p_objObj = SLisEntCrear ();
	iMin = 7;
	iMax = 7;
	dMed = 7.0;
	SLisEntObtenerParametros ( p_objObj, &iMin, &iMax, &dMed );
	if ( ( dMed < -0.001 ) || ( dMed > 0.001 ) )
	{
		printf( "Error caso 11: con 0 elementos la media deberia ser 0 y no NaN: %f\n", dMed );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLisEntTieneRepetidos ( p_objObj ) != 0 )
	{
		printf( "Error caso 12: una coleccion vacia no tiene repetidos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisEntDestruir ( &p_objObj );

	/* Objeto invalido: ni cuelga ni inventa. */
	if ( SLisEntMin ( NULL ) != 0 )
	{
		printf( "Error caso 13: con objeto nulo se esperaba 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SLisEntExtraerUnicos ( NULL ) ) )
	{
		printf( "Error caso 14: con objeto nulo ExtraerUnicos deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	ErrLimpiar ();
	return ( iRes );
}


/* Las de orden, que solo tienen las listas. */
static int TestSLisEntOrden01 ()
{
	int					iRes = BOOL_VAL_CIERTO;
	SListaEnteros *	p_lisObj;
	SListaEnteros *	p_lisOrd;

	printf( "Test SLisEntOrden 01:\n" );

	p_lisObj = SLisEntCrear ();
	SLisEntInsertar ( p_lisObj, 5 );
	SLisEntInsertar ( p_lisObj, 2 );
	SLisEntInsertar ( p_lisObj, 9 );
	SLisEntInsertar ( p_lisObj, 5 );

	/* { 5, 2, 9, 5 } no esta ordenada. */
	if ( SLisEntEstaOrdenada ( p_lisObj ) != 0 )
	{
		printf( "Error caso 1: esa lista no esta ordenada\n" );
		iRes = BOOL_VAL_FALSO;
	}
	p_lisOrd = SLisEntOrdenar ( p_lisObj );
	if ( ES_NULO ( p_lisOrd ) )
	{
		printf( "Error caso 2: Ordenar no deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SLisEntNumElementos ( p_lisOrd ) != 4 )
		{
			printf( "Error caso 3: ordenar no deberia perder elementos: %d\n", SLisEntNumElementos ( p_lisOrd ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisEntEstaOrdenada ( p_lisOrd ) != 1 )
		{
			printf( "Error caso 4: el resultado de Ordenar deberia estar ordenado\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisEntElemento ( p_lisOrd, 0 ) != 2 )
		{
			printf( "Error caso 5: el primero deberia ser 2: %d\n", SLisEntElemento ( p_lisOrd, 0 ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisEntElemento ( p_lisOrd, 3 ) != 9 )
		{
			printf( "Error caso 6: el ultimo deberia ser 9: %d\n", SLisEntElemento ( p_lisOrd, 3 ) );
			iRes = BOOL_VAL_FALSO;
		}
		SLisEntDestruir ( &p_lisOrd );
	}
	/* La original no se toca. */
	if ( SLisEntEstaOrdenada ( p_lisObj ) != 0 )
	{
		printf( "Error caso 7: Ordenar no deberia modificar la lista de entrada\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisEntDestruir ( &p_lisObj );

	/* ExtraerUnicosExt ( , 1 ) devuelve los unicos YA ordenados. */
	p_lisObj = SLisEntCrear ();
	SLisEntInsertar ( p_lisObj, 5 );
	SLisEntInsertar ( p_lisObj, 2 );
	SLisEntInsertar ( p_lisObj, 9 );
	SLisEntInsertar ( p_lisObj, 5 );

	p_lisOrd = SLisEntExtraerUnicosExt ( p_lisObj, 1 );
	if ( ES_NULO ( p_lisOrd ) )
	{
		printf( "Error caso 8: ExtraerUnicosExt no deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SLisEntNumElementos ( p_lisOrd ) != 3 )
		{
			printf( "Error caso 9: deberian quedar 3 unicos: %d\n", SLisEntNumElementos ( p_lisOrd ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisEntEstaOrdenada ( p_lisOrd ) != 1 )
		{
			printf( "Error caso 10: con iOrdenar = 1 deberian salir ordenados\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisEntDestruir ( &p_lisOrd );
	}
	SLisEntDestruir ( &p_lisObj );
	ErrLimpiar ();
	return ( iRes );
}


int TestSListaEnteros ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SListaEnteros]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSLisEntCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisEntInsertar01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisEntCursor01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisEntBuscar01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisEntEliminar01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisEntInvalidos01 () == BOOL_VAL_CIERTO )  &&
			( TestSLisEntConjunto01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisEntOrden01 () == BOOL_VAL_CIERTO ) )
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
