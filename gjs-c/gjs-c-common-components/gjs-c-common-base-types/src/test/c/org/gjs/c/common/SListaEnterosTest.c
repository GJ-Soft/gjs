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
			( TestSLisIntOrden01 () == BOOL_VAL_CIERTO ) )
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
