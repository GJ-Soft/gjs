#include "Base.h"

#include "SListaEnterosLargosSinSigno.h"



/* Primer valor que un long con signo ya no puede representar: LONG_MAX + 1.
   Vale igual con long de 4 bytes ( Windows ) que de 8 ( Cygwin, Linux ). */
#define ULONG_MITAD		( (unsigned long) LONG_MAX + 1UL )



/* Comprueba numero y orden de los valores, sin mover el cursor. */
static int VerificarContenido ( SListaEnterosLargosSinSigno * p_lisObj, unsigned long * p_ulEsperados, int iNum )
{
	int iRes = BOOL_VAL_CIERTO;

	if ( SLisIntLssNumElementos ( p_lisObj ) != iNum )
	{
		printf( "  Verificacion: se esperaban %d elementos: %d\n", iNum, SLisIntLssNumElementos ( p_lisObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	int iPos = 0;
	while ( ( iPos < iNum ) && ( iRes == BOOL_VAL_CIERTO ) )
	{
		if ( SLisIntLssElemento ( p_lisObj, iPos ) != p_ulEsperados [ iPos ] )
		{
			printf( "  Verificacion: en pos %d se esperaba %lu: %lu\n", iPos, p_ulEsperados [ iPos ], SLisIntLssElemento ( p_lisObj, iPos ) );
			iRes = BOOL_VAL_FALSO;
		}
		iPos = iPos + 1;
	}
	return ( iRes );
}

static SListaEnterosLargosSinSigno * CrearListaEnteros ( unsigned long * p_ulValores, int iNum )
{
	SListaEnterosLargosSinSigno * p_lisObj = SLisIntLssCrear ();
	int iPos = 0;
	while ( ES_VALIDO ( p_lisObj ) && ( iPos < iNum ) )
	{
		SLisIntLssInsertarAlFinal ( p_lisObj, p_ulValores [ iPos ] );
		iPos = iPos + 1;
	}
	return ( p_lisObj );
}



static int TestSLisIntLssOperaciones01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisIntLssOperaciones 01:\n" );

	SListaEnterosLargosSinSigno * p_lisObj = SLisIntLssCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( ( SLisIntLssEsValida ( p_lisObj ) != 1 ) || ( SLisIntLssEstaVacia ( p_lisObj ) != 1 ) )
		{
			printf( "Error caso 1: la lista recien creada deberia ser valida y estar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisIntLssInsertarAlFinal ( p_lisObj, 1000000UL ) != 1 ) ||
			 ( SLisIntLssInsertarAlFinal ( p_lisObj, 2000000UL ) != 1 ) ||
			 ( SLisIntLssInsertarAlFinal ( p_lisObj, 3000000UL ) != 1 ) )
		{
			printf( "Error caso 2: se esperaba poder insertar los tres enteros largos sin signo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisIntLssNumElementos ( p_lisObj ) != 3 ) || ( SLisIntLssElemento ( p_lisObj, 1 ) != 2000000UL ) )
		{
			printf( "Error caso 3: deberia haber 3 elementos y el del indice 1 ser 2000000\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Insertar al inicio desplaza el resto. */
		if ( ( SLisIntLssInsertarAlInicio ( p_lisObj, 500000UL ) != 1 ) || ( SLisIntLssElemento ( p_lisObj, 0 ) != 500000UL ) )
		{
			printf( "Error caso 4: insertar al inicio deberia dejar 500000 en la cabeza\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Modificar un elemento por posicion, con el mayor valor del tipo. */
		if ( ( SLisIntLssEstablecerElem ( p_lisObj, 0, ULONG_MAX ) != 1 ) || ( SLisIntLssElemento ( p_lisObj, 0 ) != ULONG_MAX ) )
		{
			printf( "Error caso 5: el elemento 0 deberia poder modificarse a ULONG_MAX: %lu\n", SLisIntLssElemento ( p_lisObj, 0 ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisIntLssExiste ( p_lisObj, 2000000UL ) != 1 ) || ( SLisIntLssExiste ( p_lisObj, 7UL ) != 0 ) )
		{
			printf( "Error caso 6: existe deberia encontrar 2000000 y no 7\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisIntLssBuscar ( p_lisObj, 3000000UL ) != 3 ) || ( SLisIntLssBuscar ( p_lisObj, ULONG_MAX ) != 0 ) )
		{
			printf( "Error caso 7: buscar 3000000 deberia dar el indice 3 y ULONG_MAX el 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Fuera de rango devuelve 0, igual que SSecIntLssElemento. */
		if ( SLisIntLssElemento ( p_lisObj, 4 ) != 0UL )
		{
			printf( "Error caso 8: un indice fuera de rango deberia dar 0: %lu\n", SLisIntLssElemento ( p_lisObj, 4 ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* Eliminar el primero. */
		if ( ( SLisIntLssEliminarElem ( p_lisObj, 0 ) != 1 ) ||
			 ( SLisIntLssNumElementos ( p_lisObj ) != 3 ) || ( SLisIntLssElemento ( p_lisObj, 0 ) != 1000000UL ) )
		{
			printf( "Error caso 9: tras eliminar el primero la cabeza deberia ser 1000000\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisIntLssVaciar ( p_lisObj );
		if ( SLisIntLssEstaVacia ( p_lisObj ) != 1 )
		{
			printf( "Error caso 10: tras vaciar la lista deberia estar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisIntLssDestruir ( &p_lisObj );

	if ( ES_VALIDO ( p_lisObj ) )
	{
		printf( "Error caso 11: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSLisIntLssCursor01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisIntLssCursor 01:\n" );

	SListaEnterosLargosSinSigno * p_lisObj = SLisIntLssCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		SLisIntLssInsertarAlFinal ( p_lisObj, 10UL );
		SLisIntLssInsertarAlFinal ( p_lisObj, 20UL );
		SLisIntLssInsertarAlFinal ( p_lisObj, ULONG_MAX );

		SLisIntLssInicio ( p_lisObj );
		if ( ( SLisIntLssActual ( p_lisObj ) != 10UL ) || ( SLisIntLssEstaEnInicio ( p_lisObj ) != 1 ) )
		{
			printf( "Error caso 1: el inicio deberia ser 10\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisIntLssSiguiente ( p_lisObj );
		if ( SLisIntLssActual ( p_lisObj ) != 20UL )
		{
			printf( "Error caso 2: el siguiente del inicio deberia ser 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisIntLssFinal ( p_lisObj );
		if ( ( SLisIntLssActual ( p_lisObj ) != ULONG_MAX ) || ( SLisIntLssEstaEnFinal ( p_lisObj ) != 1 ) )
		{
			printf( "Error caso 3: el final deberia ser ULONG_MAX: %lu\n", SLisIntLssActual ( p_lisObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisIntLssDestruir ( &p_lisObj );
	return ( iRes );
}

static int TestSLisIntLssInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisIntLssInvalidos 01:\n" );

	if ( SLisIntLssEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: una lista nula no deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLisIntLssNumElementos ( NULL ) != 0 )
	{
		printf( "Error caso 2: una lista nula deberia tener 0 elementos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLisIntLssElemento ( NULL, 0 ) != 0UL )
	{
		printf( "Error caso 3: una lista nula deberia dar 0 como elemento\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SListaEnterosLargosSinSigno * p_lisNula = NULL;
	SLisIntLssDestruir ( &p_lisNula );
	ErrLimpiar ();
	return ( iRes );
}





/* Funciones de conjunto, contra valores ABSOLUTOS. Con valores pequenos
   ya se ve el centinela de Max: si arranca en LONG_MIN, en sin signo eso es
   LONG_MAX + 1 y ningun elemento lo supera. */
static int TestSLisIntLssConjunto01 ()
{
	int								iRes = BOOL_VAL_CIERTO;
	unsigned long					ulMin;
	unsigned long					ulMax;
	double							dMed;
	SListaEnterosLargosSinSigno *	p_objObj;
	SListaEnterosLargosSinSigno *	p_objUnicos;

	printf( "Test SLisIntLssConjunto 01:\n" );

	/* { 5, 2, 9, 5 }: cuatro elementos, con el 5 repetido. */
	p_objObj = SLisIntLssCrear ();
	SLisIntLssInsertar ( p_objObj, 5UL );
	SLisIntLssInsertar ( p_objObj, 2UL );
	SLisIntLssInsertar ( p_objObj, 9UL );
	SLisIntLssInsertar ( p_objObj, 5UL );

	if ( SLisIntLssMin ( p_objObj ) != 2UL )
	{
		printf( "Error caso 1: el minimo deberia ser 2: %lu\n", SLisIntLssMin ( p_objObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLisIntLssMax ( p_objObj ) != 9UL )
	{
		printf( "Error caso 2: el maximo deberia ser 9: %lu\n", SLisIntLssMax ( p_objObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	SLisIntLssObtenerParametros ( p_objObj, &ulMin, &ulMax, &dMed );
	if ( ( ulMin != 2UL ) || ( ulMax != 9UL ) )
	{
		printf( "Error caso 3: ObtenerParametros deberia dar 2 y 9: %lu y %lu\n", ulMin, ulMax );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( dMed < 5.25 - 0.001 ) || ( dMed > 5.25 + 0.001 ) )
	{
		printf( "Error caso 4: la media deberia ser 5.25: %f\n", dMed );
		iRes = BOOL_VAL_FALSO;
	}
	/* Cuatro elementos y uno repetido: tres unicos. */
	if ( SLisIntLssTieneRepetidos ( p_objObj ) != 1 )
	{
		printf( "Error caso 5: deberia detectar repetidos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	p_objUnicos = SLisIntLssExtraerUnicos ( p_objObj );
	if ( ES_NULO ( p_objUnicos ) )
	{
		printf( "Error caso 6: ExtraerUnicos no deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SLisIntLssNumElementos ( p_objUnicos ) != 3 )
		{
			printf( "Error caso 7: deberian quedar 3 unicos: %d\n", SLisIntLssNumElementos ( p_objUnicos ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisIntLssTieneRepetidos ( p_objUnicos ) != 0 )
		{
			printf( "Error caso 8: los unicos no deberian tener repetidos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisIntLssDestruir ( &p_objUnicos );
	}
	if ( SLisIntLssDefinidaPositiva ( p_objObj ) != 1 )
	{
		printf( "Error caso 9: DefinidaPositiva deberia dar 1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Con un cero deja de serlo: en sin signo es el unico valor que lo impide. */
	SLisIntLssInsertar ( p_objObj, 0UL );
	if ( SLisIntLssDefinidaPositiva ( p_objObj ) != 0 )
	{
		printf( "Error caso 10: con un 0 DefinidaPositiva deberia dar 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisIntLssDestruir ( &p_objObj );

	/* Lista vacia: ni division por cero ni valores sin inicializar. Los
	   extremos quedan en sus centinelas. */
	p_objObj = SLisIntLssCrear ();
	ulMin = 7;
	ulMax = 7;
	dMed = 7.0;
	SLisIntLssObtenerParametros ( p_objObj, &ulMin, &ulMax, &dMed );
	if ( ( dMed < -0.001 ) || ( dMed > 0.001 ) )
	{
		printf( "Error caso 11: con 0 elementos la media deberia ser 0 y no NaN: %f\n", dMed );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( ulMin != ULONG_MAX ) || ( ulMax != 0UL ) )
	{
		printf( "Error caso 12: con 0 elementos deberia dar ULONG_MAX y 0: %lu y %lu\n", ulMin, ulMax );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLisIntLssTieneRepetidos ( p_objObj ) != 0 )
	{
		printf( "Error caso 13: una coleccion vacia no tiene repetidos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisIntLssDestruir ( &p_objObj );

	/* Objeto invalido: ni cuelga ni inventa. */
	if ( SLisIntLssMin ( NULL ) != 0UL )
	{
		printf( "Error caso 14: con objeto nulo se esperaba 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLisIntLssMax ( NULL ) != 0UL )
	{
		printf( "Error caso 15: con objeto nulo se esperaba 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SLisIntLssExtraerUnicos ( NULL ) ) )
	{
		printf( "Error caso 16: con objeto nulo ExtraerUnicos deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	ErrLimpiar ();
	return ( iRes );
}


/* La frontera del tipo: valores que no caben en un long con signo. Aqui se
   ven los centinelas de Min ( LONG_MAX en vez de ULONG_MAX ) y cualquier
   variable intermedia que se quede en long. */
static int TestSLisIntLssConjunto02 ()
{
	int								iRes = BOOL_VAL_CIERTO;
	unsigned long					ulMin;
	unsigned long					ulMax;
	double							dMed;
	SListaEnterosLargosSinSigno *	p_objObj;

	printf( "Test SLisIntLssConjunto 02:\n" );

	/* { ULONG_MAX, LONG_MAX + 1 }: los dos por encima de LONG_MAX. */
	p_objObj = SLisIntLssCrear ();
	SLisIntLssInsertar ( p_objObj, ULONG_MAX );
	SLisIntLssInsertar ( p_objObj, ULONG_MITAD );

	if ( SLisIntLssMin ( p_objObj ) != ULONG_MITAD )
	{
		printf( "Error caso 1: el minimo deberia ser %lu: %lu\n", ULONG_MITAD, SLisIntLssMin ( p_objObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLisIntLssMax ( p_objObj ) != ULONG_MAX )
	{
		printf( "Error caso 2: el maximo deberia ser %lu: %lu\n", ULONG_MAX, SLisIntLssMax ( p_objObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	SLisIntLssObtenerParametros ( p_objObj, &ulMin, &ulMax, &dMed );
	if ( ( ulMin != ULONG_MITAD ) || ( ulMax != ULONG_MAX ) )
	{
		printf( "Error caso 3: ObtenerParametros deberia dar %lu y %lu: %lu y %lu\n", ULONG_MITAD, ULONG_MAX, ulMin, ulMax );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLisIntLssDefinidaPositiva ( p_objObj ) != 1 )
	{
		printf( "Error caso 4: valores por encima de LONG_MAX siguen siendo positivos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLisIntLssExiste ( p_objObj, ULONG_MITAD ) != 1 )
	{
		printf( "Error caso 5: deberia existir LONG_MAX + 1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* LONG_MAX, justo por debajo, pasa a ser el minimo. */
	SLisIntLssInsertar ( p_objObj, (unsigned long) LONG_MAX );
	if ( SLisIntLssMin ( p_objObj ) != (unsigned long) LONG_MAX )
	{
		printf( "Error caso 6: el minimo deberia ser %ld: %lu\n", LONG_MAX, SLisIntLssMin ( p_objObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	SLisIntLssDestruir ( &p_objObj );
	ErrLimpiar ();
	return ( iRes );
}


/* Las de orden, que solo tienen las listas. */
static int TestSLisIntLssOrden01 ()
{
	int								iRes = BOOL_VAL_CIERTO;
	SListaEnterosLargosSinSigno *	p_lisObj;
	SListaEnterosLargosSinSigno *	p_lisOrd;

	printf( "Test SLisIntLssOrden 01:\n" );

	p_lisObj = SLisIntLssCrear ();
	SLisIntLssInsertar ( p_lisObj, 5UL );
	SLisIntLssInsertar ( p_lisObj, 2UL );
	SLisIntLssInsertar ( p_lisObj, 9UL );
	SLisIntLssInsertar ( p_lisObj, 5UL );

	/* { 5, 2, 9, 5 } no esta ordenada. */
	if ( SLisIntLssEstaOrdenada ( p_lisObj ) != 0 )
	{
		printf( "Error caso 1: esa lista no esta ordenada\n" );
		iRes = BOOL_VAL_FALSO;
	}
	p_lisOrd = SLisIntLssOrdenar ( p_lisObj );
	if ( ES_NULO ( p_lisOrd ) )
	{
		printf( "Error caso 2: Ordenar no deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SLisIntLssNumElementos ( p_lisOrd ) != 4 )
		{
			printf( "Error caso 3: ordenar no deberia perder elementos: %d\n", SLisIntLssNumElementos ( p_lisOrd ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisIntLssEstaOrdenada ( p_lisOrd ) != 1 )
		{
			printf( "Error caso 4: el resultado de Ordenar deberia estar ordenado\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisIntLssElemento ( p_lisOrd, 0 ) != 2UL )
		{
			printf( "Error caso 5: el primero deberia ser 2: %lu\n", SLisIntLssElemento ( p_lisOrd, 0 ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisIntLssElemento ( p_lisOrd, 3 ) != 9UL )
		{
			printf( "Error caso 6: el ultimo deberia ser 9: %lu\n", SLisIntLssElemento ( p_lisOrd, 3 ) );
			iRes = BOOL_VAL_FALSO;
		}
		SLisIntLssDestruir ( &p_lisOrd );
	}
	/* La original no se toca. */
	if ( SLisIntLssEstaOrdenada ( p_lisObj ) != 0 )
	{
		printf( "Error caso 7: Ordenar no deberia modificar la lista de entrada\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisIntLssDestruir ( &p_lisObj );

	/* ExtraerUnicosExt ( , 1 ) devuelve los unicos YA ordenados. */
	p_lisObj = SLisIntLssCrear ();
	SLisIntLssInsertar ( p_lisObj, 5UL );
	SLisIntLssInsertar ( p_lisObj, 2UL );
	SLisIntLssInsertar ( p_lisObj, 9UL );
	SLisIntLssInsertar ( p_lisObj, 5UL );

	p_lisOrd = SLisIntLssExtraerUnicosExt ( p_lisObj, 1 );
	if ( ES_NULO ( p_lisOrd ) )
	{
		printf( "Error caso 8: ExtraerUnicosExt no deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SLisIntLssNumElementos ( p_lisOrd ) != 3 )
		{
			printf( "Error caso 9: deberian quedar 3 unicos: %d\n", SLisIntLssNumElementos ( p_lisOrd ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisIntLssEstaOrdenada ( p_lisOrd ) != 1 )
		{
			printf( "Error caso 10: con iOrdenar = 1 deberian salir ordenados\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisIntLssDestruir ( &p_lisOrd );
	}
	SLisIntLssDestruir ( &p_lisObj );
	ErrLimpiar ();
	return ( iRes );
}


/* Orden en la frontera: comparando en long con signo, LONG_MAX + 1 se ve
   negativo y queda por delante del 0. */
static int TestSLisIntLssOrden02 ()
{
	int								iRes = BOOL_VAL_CIERTO;
	SListaEnterosLargosSinSigno *	p_lisObj;
	SListaEnterosLargosSinSigno *	p_lisOrd;

	printf( "Test SLisIntLssOrden 02:\n" );

	/* { 1, LONG_MAX + 1, ULONG_MAX } esta ordenada. */
	p_lisObj = SLisIntLssCrear ();
	SLisIntLssInsertar ( p_lisObj, 1UL );
	SLisIntLssInsertar ( p_lisObj, ULONG_MITAD );
	SLisIntLssInsertar ( p_lisObj, ULONG_MAX );
	if ( SLisIntLssEstaOrdenada ( p_lisObj ) != 1 )
	{
		printf( "Error caso 1: { 1, LONG_MAX + 1, ULONG_MAX } esta ordenada\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisIntLssDestruir ( &p_lisObj );

	/* { LONG_MAX + 1, 1 } no lo esta. */
	p_lisObj = SLisIntLssCrear ();
	SLisIntLssInsertar ( p_lisObj, ULONG_MITAD );
	SLisIntLssInsertar ( p_lisObj, 1UL );
	if ( SLisIntLssEstaOrdenada ( p_lisObj ) != 0 )
	{
		printf( "Error caso 2: { LONG_MAX + 1, 1 } no esta ordenada\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisIntLssDestruir ( &p_lisObj );

	/* Ordenar { ULONG_MAX, 0, LONG_MAX + 1, 5 } da { 0, 5, LONG_MAX + 1, ULONG_MAX }. */
	p_lisObj = SLisIntLssCrear ();
	SLisIntLssInsertar ( p_lisObj, ULONG_MAX );
	SLisIntLssInsertar ( p_lisObj, 0UL );
	SLisIntLssInsertar ( p_lisObj, ULONG_MITAD );
	SLisIntLssInsertar ( p_lisObj, 5UL );
	p_lisOrd = SLisIntLssOrdenar ( p_lisObj );
	if ( ES_NULO ( p_lisOrd ) )
	{
		printf( "Error caso 3: Ordenar no deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( ( SLisIntLssElemento ( p_lisOrd, 0 ) != 0UL ) ||
			 ( SLisIntLssElemento ( p_lisOrd, 1 ) != 5UL ) ||
			 ( SLisIntLssElemento ( p_lisOrd, 2 ) != ULONG_MITAD ) ||
			 ( SLisIntLssElemento ( p_lisOrd, 3 ) != ULONG_MAX ) )
		{
			printf( "Error caso 4: se esperaba { 0, 5, %lu, %lu }: { %lu, %lu, %lu, %lu }\n",
					ULONG_MITAD, ULONG_MAX,
					SLisIntLssElemento ( p_lisOrd, 0 ), SLisIntLssElemento ( p_lisOrd, 1 ),
					SLisIntLssElemento ( p_lisOrd, 2 ), SLisIntLssElemento ( p_lisOrd, 3 ) );
			iRes = BOOL_VAL_FALSO;
		}
		SLisIntLssDestruir ( &p_lisOrd );
	}
	SLisIntLssDestruir ( &p_lisObj );
	ErrLimpiar ();
	return ( iRes );
}

/* Un valor en la posicion 0 y otro que es el ULTIMO de los valores: los dos
   casos que fallaban en SLista antes del arreglo del 2026-11-01. */
static int TestSLisIntLssExisten01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisIntLssExisten 01:\n" );

	unsigned long ulVal [ 3 ] = { 10, 20, 30 };
	unsigned long ulV1 [ 2 ] = { 10, 30 };
	unsigned long ulV2 [ 2 ] = { 10, 99 };
	unsigned long ulV3 [ 2 ] = { 99, 30 };
	unsigned long ulV4 [ 2 ] = { 98, 99 };
	SListaEnterosLargosSinSigno * p_lisObj = CrearListaEnteros ( ulVal, 3 );
	SListaEnterosLargosSinSigno * p_lis1 = CrearListaEnteros ( ulV1, 2 );
	SListaEnterosLargosSinSigno * p_lis2 = CrearListaEnteros ( ulV2, 2 );
	SListaEnterosLargosSinSigno * p_lis3 = CrearListaEnteros ( ulV3, 2 );
	SListaEnterosLargosSinSigno * p_lis4 = CrearListaEnteros ( ulV4, 2 );
	SListaEnterosLargosSinSigno * p_lisVacia = SLisIntLssCrear ();
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lis1 ) && ES_VALIDO ( p_lis2 ) &&
		 ES_VALIDO ( p_lis3 ) && ES_VALIDO ( p_lis4 ) && ES_VALIDO ( p_lisVacia ) )
	{
		if ( SLisIntLssExistenTodos ( p_lisObj, p_lis1 ) != 1 )
		{
			printf( "Error caso 1: { 10, 30 } estan todos en { 10, 20, 30 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisIntLssExistenTodos ( p_lisObj, p_lis2 ) != 0 )
		{
			printf( "Error caso 2: en { 10, 99 } falta el 99\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisIntLssExisteAlguno ( p_lisObj, p_lis2 ) != 1 )
		{
			printf( "Error caso 3: de { 10, 99 } esta el 10, en la posicion 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisIntLssExisteAlguno ( p_lisObj, p_lis3 ) != 1 )
		{
			printf( "Error caso 4: de { 99, 30 } esta el 30, el ultimo de los valores\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisIntLssExisteAlguno ( p_lisObj, p_lis4 ) != 0 ) ||
			 ( SLisIntLssExistenTodos ( p_lisObj, p_lis4 ) != 0 ) )
		{
			printf( "Error caso 5: de { 98, 99 } no esta ninguno\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisIntLssExistenTodos ( p_lisObj, p_lisVacia ) != 1 ) ||
			 ( SLisIntLssExisteAlguno ( p_lisObj, p_lisVacia ) != 0 ) )
		{
			printf( "Error caso 6: con valores vacios, Todos da 1 y Alguno 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisIntLssExistenTodos ( NULL, p_lis1 ) != 0 ) ||
			 ( SLisIntLssExisteAlguno ( p_lisObj, NULL ) != 0 ) )
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
	SLisIntLssDestruir ( &p_lisObj );
	SLisIntLssDestruir ( &p_lis1 );
	SLisIntLssDestruir ( &p_lis2 );
	SLisIntLssDestruir ( &p_lis3 );
	SLisIntLssDestruir ( &p_lis4 );
	SLisIntLssDestruir ( &p_lisVacia );
	return ( iRes );
}

static int TestSLisIntLssInsertarLista01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisIntLssInsertarLista 01:\n" );

	unsigned long ulDest [ 2 ] = { 1, 2 };
	unsigned long ulVal [ 3 ] = { 7, 8, 9 };
	SListaEnterosLargosSinSigno * p_lisObj = CrearListaEnteros ( ulDest, 2 );
	SListaEnterosLargosSinSigno * p_lisVal = CrearListaEnteros ( ulVal, 3 );
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisVal ) )
	{
		/* Mueve detras del cursor, en su orden, y deja los valores vacios. */
		SLisIntLssMoverA ( p_lisObj, 0 );
		if ( SLisIntLssInsertarLista ( p_lisObj, p_lisVal ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al insertar la lista\n" );
			iRes = BOOL_VAL_FALSO;
		}
		unsigned long ulEsp1 [ 5 ] = { 1, 7, 8, 9, 2 };
		if ( VerificarContenido ( p_lisObj, ulEsp1, 5 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 2: se esperaba { 1, 7, 8, 9, 2 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisIntLssEstaVacia ( p_lisVal ) != 1 ) || ( SLisIntLssEsValida ( p_lisVal ) != 1 ) )
		{
			printf( "Error caso 3: la lista de valores deberia quedar vacia y valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Concatenar va al final, este donde este el cursor. */
		SLisIntLssInsertarAlFinal ( p_lisVal, 5 );
		SLisIntLssInsertarAlFinal ( p_lisVal, 6 );
		SLisIntLssMoverA ( p_lisObj, 1 );
		if ( SLisIntLssConcatenarLista ( p_lisObj, p_lisVal ) != 1 )
		{
			printf( "Error caso 4: se esperaba resultado 1 al concatenar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		unsigned long ulEsp2 [ 7 ] = { 1, 7, 8, 9, 2, 5, 6 };
		if ( ( VerificarContenido ( p_lisObj, ulEsp2, 7 ) != BOOL_VAL_CIERTO ) ||
			 ( SLisIntLssEstaVacia ( p_lisVal ) != 1 ) )
		{
			printf( "Error caso 5: se esperaba { 1, 7, 8, 9, 2, 5, 6 } y los valores vacios\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisIntLssInsertarLista ( p_lisObj, NULL ) != 0 ) ||
			 ( SLisIntLssConcatenarLista ( NULL, p_lisVal ) != 0 ) ||
			 ( SLisIntLssConcatenarLista ( p_lisObj, p_lisObj ) != 0 ) )
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
	SLisIntLssDestruir ( &p_lisObj );
	SLisIntLssDestruir ( &p_lisVal );
	return ( iRes );
}

static int TestSLisIntLssListaDup01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisIntLssListaDup 01:\n" );

	unsigned long ulDest [ 2 ] = { 1, 2 };
	unsigned long ulVal [ 2 ] = { 7, 8 };
	SListaEnterosLargosSinSigno * p_lisObj = CrearListaEnteros ( ulDest, 2 );
	SListaEnterosLargosSinSigno * p_lisVal = CrearListaEnteros ( ulVal, 2 );
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisVal ) )
	{
		SLisIntLssMoverA ( p_lisObj, 0 );
		if ( SLisIntLssInsertarListaDup ( p_lisObj, p_lisVal ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al insertar copias\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisIntLssConcatenarListaDup ( p_lisObj, p_lisVal ) != 1 )
		{
			printf( "Error caso 2: se esperaba resultado 1 al concatenar copias\n" );
			iRes = BOOL_VAL_FALSO;
		}
		unsigned long ulEsp [ 6 ] = { 1, 7, 8, 2, 7, 8 };
		if ( VerificarContenido ( p_lisObj, ulEsp, 6 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 3: se esperaba { 1, 7, 8, 2, 7, 8 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Los valores quedan intactos, y son copias: cambiar una no toca el original. */
		SLisIntLssEstablecerElem ( p_lisObj, 1, 70 );
		if ( VerificarContenido ( p_lisVal, ulVal, 2 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 4: los valores deberian seguir { 7, 8 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisIntLssInsertarListaDup ( p_lisObj, NULL ) != 0 ) ||
			 ( SLisIntLssConcatenarListaDup ( NULL, p_lisVal ) != 0 ) )
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
	SLisIntLssDestruir ( &p_lisObj );
	SLisIntLssDestruir ( &p_lisVal );
	return ( iRes );
}

static int TestSLisIntLssExtraerLista01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisIntLssExtraerLista 01:\n" );

	unsigned long ulVal [ 6 ] = { 20, 10, 20, 30, 40, 20 };
	unsigned long ulBus [ 4 ] = { 20, 40, 99, 20 };
	SListaEnterosLargosSinSigno * p_lisObj = CrearListaEnteros ( ulVal, 6 );
	SListaEnterosLargosSinSigno * p_lisBus = CrearListaEnteros ( ulBus, 4 );
	SListaEnterosLargosSinSigno * p_lisRes = NULL;
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisBus ) )
	{
		/* Todas las apariciones de cada valor buscado, en el orden de los buscados: el
		   20 esta tres veces y sale entero con el primero; el 99 no esta. */
		p_lisRes = SLisIntLssExtraerLista ( p_lisObj, p_lisBus );
		unsigned long ulEspRes [ 4 ] = { 20, 20, 20, 40 };
		unsigned long ulEspObj [ 2 ] = { 10, 30 };
		if ( ES_NULO ( p_lisRes ) || ( SLisIntLssEsValida ( p_lisRes ) != 1 ) ||
			 ( VerificarContenido ( p_lisRes, ulEspRes, 4 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 1: se esperaba extraer { 20, 20, 20, 40 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( VerificarContenido ( p_lisObj, ulEspObj, 2 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 2: en el origen deberia quedar { 10, 30 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Si la de SLista falla no se devuelve una envoltura vacia: se devuelve nulo. */
		if ( ES_VALIDO ( SLisIntLssExtraerLista ( p_lisObj, p_lisObj ) ) ||
			 ES_VALIDO ( SLisIntLssExtraerLista ( NULL, p_lisBus ) ) )
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
	SLisIntLssDestruir ( &p_lisObj );
	SLisIntLssDestruir ( &p_lisBus );
	SLisIntLssDestruir ( &p_lisRes );
	return ( iRes );
}

/* Destruye todas las apariciones de cada valor buscado; los valores no cambian. */
static int TestSLisIntLssEliminarLista01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisIntLssEliminarLista 01:\n" );

	unsigned long ulVal [ 6 ] = { ULONG_MAX, 10, ULONG_MAX, 30, 40, ULONG_MAX };
	unsigned long ulBus [ 4 ] = { ULONG_MAX, 40, 99, ULONG_MAX };
	SListaEnterosLargosSinSigno * p_lisObj = CrearListaEnteros ( ulVal, 6 );
	SListaEnterosLargosSinSigno * p_lisBus = CrearListaEnteros ( ulBus, 4 );
	SListaEnterosLargosSinSigno * p_lisVacia = SLisIntLssCrear ();
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisBus ) && ES_VALIDO ( p_lisVacia ) )
	{
		/* El 99 no esta y se ignora; el ULONG_MAX esta tres veces y se van todas, aunque
		   tambien este dos veces en los buscados. */
		if ( SLisIntLssEliminarLista ( p_lisObj, p_lisBus ) != 1 )
		{
			printf( "Error caso 1: se esperaba 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		unsigned long ulEspObj [ 2 ] = { 10, 30 };
		if ( ( SLisIntLssNumElementos ( p_lisObj ) != 2 ) ||
			 ( VerificarContenido ( p_lisObj, ulEspObj, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 2: deberia quedar { 10, 30 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( VerificarContenido ( p_lisBus, ulBus, 4 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 3: los valores no deberian cambiar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Ya no queda ninguno: no hay nada que eliminar, y no es un error. */
		if ( ( SLisIntLssEliminarLista ( p_lisObj, p_lisBus ) != 1 ) ||
			 ( SLisIntLssEliminarLista ( p_lisObj, p_lisVacia ) != 1 ) ||
			 ( VerificarContenido ( p_lisObj, ulEspObj, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 4: sin nada que eliminar se esperaba 1 sin cambios\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisIntLssEliminarLista ( p_lisObj, p_lisObj ) != 0 ) ||
			 ( VerificarContenido ( p_lisObj, ulEspObj, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 5: con la misma lista se esperaba 0 sin cambios\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisIntLssEliminarLista ( p_lisObj, NULL ) != 0 ) || ( SLisIntLssEliminarLista ( NULL, p_lisBus ) != 0 ) )
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
	SLisIntLssDestruir ( &p_lisObj );
	SLisIntLssDestruir ( &p_lisBus );
	SLisIntLssDestruir ( &p_lisVacia );
	return ( iRes );
}

static int TestSLisIntLssOperacionesListas01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisIntLssOperacionesListas 01:\n" );

	unsigned long ulV1 [ 4 ] = { 1, 2, 3, 4 };
	unsigned long ulV2 [ 3 ] = { 4, 2, 5 };
	SListaEnterosLargosSinSigno * p_lis1 = CrearListaEnteros ( ulV1, 4 );
	SListaEnterosLargosSinSigno * p_lis2 = CrearListaEnteros ( ulV2, 3 );
	SListaEnterosLargosSinSigno * p_lisVacia = SLisIntLssCrear ();
	if ( ES_VALIDO ( p_lis1 ) && ES_VALIDO ( p_lis2 ) && ES_VALIDO ( p_lisVacia ) )
	{
		/* La union es concatenacion: el 2 y el 4 salen dos veces. */
		SListaEnterosLargosSinSigno * p_lisRes = SLisIntLssUnion ( p_lis1, p_lis2 );
		unsigned long ulEspU [ 7 ] = { 1, 2, 3, 4, 4, 2, 5 };
		if ( ES_NULO ( p_lisRes ) || ( SLisIntLssEsValida ( p_lisRes ) != 1 ) ||
			 ( VerificarContenido ( p_lisRes, ulEspU, 7 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 1: la union deberia ser { 1, 2, 3, 4, 4, 2, 5 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisIntLssDestruir ( &p_lisRes );

		/* Interseccion y diferencia, las dos en el orden de V1. */
		p_lisRes = SLisIntLssInterseccion ( p_lis1, p_lis2 );
		unsigned long ulEspI [ 2 ] = { 2, 4 };
		if ( ES_NULO ( p_lisRes ) || ( VerificarContenido ( p_lisRes, ulEspI, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 2: la interseccion deberia ser { 2, 4 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisIntLssDestruir ( &p_lisRes );

		p_lisRes = SLisIntLssDiferencia ( p_lis1, p_lis2 );
		unsigned long ulEspD [ 2 ] = { 1, 3 };
		if ( ES_NULO ( p_lisRes ) || ( VerificarContenido ( p_lisRes, ulEspD, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 3: la diferencia deberia ser { 1, 3 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisIntLssDestruir ( &p_lisRes );

		if ( ( VerificarContenido ( p_lis1, ulV1, 4 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarContenido ( p_lis2, ulV2, 3 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 4: las listas de entrada no deberian cambiar\n" );
			iRes = BOOL_VAL_FALSO;
		}

		/* Con una vacia: lista nueva, valida y vacia; no nulo. */
		p_lisRes = SLisIntLssInterseccion ( p_lis1, p_lisVacia );
		if ( ES_NULO ( p_lisRes ) || ( SLisIntLssEsValida ( p_lisRes ) != 1 ) || ( SLisIntLssEstaVacia ( p_lisRes ) != 1 ) )
		{
			printf( "Error caso 5: la interseccion con una vacia deberia ser una lista vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisIntLssDestruir ( &p_lisRes );
		p_lisRes = SLisIntLssDiferencia ( p_lis1, p_lisVacia );
		if ( ES_NULO ( p_lisRes ) || ( VerificarContenido ( p_lisRes, ulV1, 4 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 6: V1 menos una vacia deberia ser V1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisIntLssDestruir ( &p_lisRes );

		if ( ES_VALIDO ( SLisIntLssUnion ( p_lis1, NULL ) ) ||
			 ES_VALIDO ( SLisIntLssInterseccion ( NULL, p_lis2 ) ) ||
			 ES_VALIDO ( SLisIntLssDiferencia ( p_lis1, NULL ) ) )
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
	SLisIntLssDestruir ( &p_lis1 );
	SLisIntLssDestruir ( &p_lis2 );
	SLisIntLssDestruir ( &p_lisVacia );
	ErrLimpiar ();
	return ( iRes );
}


/* Los valores por encima de LONG_MAX, que como long con signo serian negativos,
   tienen que encontrarse y distinguirse igual que los demas. */
static int TestSLisIntLssOperacionesListas02 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisIntLssOperacionesListas 02:\n" );

	unsigned long ulV1 [ 4 ] = { 0UL, (unsigned long) LONG_MAX, ULONG_MITAD, ULONG_MAX };
	unsigned long ulV2 [ 2 ] = { ULONG_MAX, ULONG_MITAD };
	SListaEnterosLargosSinSigno * p_lis1 = CrearListaEnteros ( ulV1, 4 );
	SListaEnterosLargosSinSigno * p_lis2 = CrearListaEnteros ( ulV2, 2 );
	if ( ES_VALIDO ( p_lis1 ) && ES_VALIDO ( p_lis2 ) )
	{
		if ( SLisIntLssExistenTodos ( p_lis1, p_lis2 ) != 1 )
		{
			printf( "Error caso 1: LONG_MAX + 1 y ULONG_MAX estan en V1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SListaEnterosLargosSinSigno * p_lisRes = SLisIntLssInterseccion ( p_lis1, p_lis2 );
		unsigned long ulEspI [ 2 ] = { ULONG_MITAD, ULONG_MAX };
		if ( ES_NULO ( p_lisRes ) || ( VerificarContenido ( p_lisRes, ulEspI, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 2: la interseccion deberia ser { LONG_MAX + 1, ULONG_MAX }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisIntLssDestruir ( &p_lisRes );
		p_lisRes = SLisIntLssDiferencia ( p_lis1, p_lis2 );
		unsigned long ulEspD [ 2 ] = { 0UL, (unsigned long) LONG_MAX };
		if ( ES_NULO ( p_lisRes ) || ( VerificarContenido ( p_lisRes, ulEspD, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 3: la diferencia deberia ser { 0, LONG_MAX }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisIntLssDestruir ( &p_lisRes );
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisIntLssDestruir ( &p_lis1 );
	SLisIntLssDestruir ( &p_lis2 );
	return ( iRes );
}

/* La copia tiene los mismos valores en el mismo orden, con los extremos del
   tipo; cambiarla no toca el original, ni se mueve su cursor. */
static int TestSLisIntLssDuplicar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisIntLssDuplicar 01:\n" );

	unsigned long ulVal [ 4 ] = { 0, ULONG_MAX, ULONG_MITAD, 5 };
	SListaEnterosLargosSinSigno * p_lisObj = CrearListaEnteros ( ulVal, 4 );
	SListaEnterosLargosSinSigno * p_lisVacia = SLisIntLssCrear ();
	SListaEnterosLargosSinSigno * p_lisDup = NULL;
	SListaEnterosLargosSinSigno * p_lisDupVacia = NULL;
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisVacia ) )
	{
		SLisIntLssMoverA ( p_lisObj, 1 );
		p_lisDup = SLisIntLssDuplicar ( p_lisObj );
		if ( SLisIntLssPosicion ( p_lisObj ) != 1 )
		{
			printf( "Error caso 1: el cursor del original deberia seguir en 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_NULO ( p_lisDup ) || ( p_lisDup == p_lisObj ) ||
			 ( VerificarContenido ( p_lisDup, ulVal, 4 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 2: la copia deberia ser otra lista con { 0, ULONG_MAX, ULONG_MITAD, 5 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisIntLssEstablecerElem ( p_lisDup, 2, 99 );
		if ( VerificarContenido ( p_lisObj, ulVal, 4 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 3: cambiar la copia no deberia tocar el original\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* La vacia se copia en otra vacia, no en nulo. */
		p_lisDupVacia = SLisIntLssDuplicar ( p_lisVacia );
		if ( ES_NULO ( p_lisDupVacia ) || ( SLisIntLssEsValida ( p_lisDupVacia ) != 1 ) ||
			 ( SLisIntLssNumElementos ( p_lisDupVacia ) != 0 ) )
		{
			printf( "Error caso 4: la copia de una vacia deberia ser otra vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SLisIntLssDuplicar ( NULL ) ) )
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
	SLisIntLssDestruir ( &p_lisObj );
	SLisIntLssDestruir ( &p_lisVacia );
	SLisIntLssDestruir ( &p_lisDup );
	SLisIntLssDestruir ( &p_lisDupVacia );
	return ( iRes );
}


/* 1 solo con el cursor sobre un elemento: no en una vacia, ni deposicionada,
   ni con la lista nula. */
/* Repetidos con BuscarPrimero / BuscarSiguiente y Repeticiones. */
static int TestSLisIntLssRepeticiones01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisIntLssRepeticiones 01:\n" );

	unsigned long ulVal [ 6 ] = { ULONG_MAX, 10, ULONG_MAX, 30, ULONG_MAX, 40 };
	SListaEnterosLargosSinSigno * p_lisObj = CrearListaEnteros ( ulVal, 6 );
	SListaEnterosLargosSinSigno * p_lisVacia = SLisIntLssCrear ();
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisVacia ) )
	{
		if ( ( SLisIntLssBuscarPrimero ( p_lisObj, ULONG_MAX ) != 0 ) ||
			 ( SLisIntLssBuscarSiguiente ( p_lisObj, ULONG_MAX, 0 ) != 2 ) ||
			 ( SLisIntLssBuscarSiguiente ( p_lisObj, ULONG_MAX, 2 ) != 4 ) ||
			 ( SLisIntLssBuscarSiguiente ( p_lisObj, ULONG_MAX, 4 ) != -1 ) )
		{
			printf( "Error caso 1: el ULONG_MAX deberia estar en 0, 2 y 4\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Desde la posicion siguiente, no desde la misma. */
		if ( ( SLisIntLssBuscarSiguiente ( p_lisObj, ULONG_MAX, 1 ) != 2 ) ||
			 ( SLisIntLssBuscarSiguiente ( p_lisObj, ULONG_MAX, 5 ) != -1 ) ||
			 ( SLisIntLssBuscarSiguiente ( p_lisObj, ULONG_MAX, -2 ) != -1 ) ||
			 ( SLisIntLssBuscar ( p_lisObj, ULONG_MAX ) != 0 ) ||
			 ( SLisIntLssBuscar ( p_lisObj, 40 ) != 5 ) )
		{
			printf( "Error caso 2: detras de la 1 esta en la 2, y Buscar es BuscarPrimero\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisIntLssRepeticiones ( p_lisObj, ULONG_MAX ) != 3 ) ||
			 ( SLisIntLssRepeticiones ( p_lisObj, 40 ) != 1 ) ||
			 ( SLisIntLssRepeticiones ( p_lisObj, 99 ) != 0 ) ||
			 ( SLisIntLssBuscarPrimero ( p_lisObj, 99 ) != -1 ) )
		{
			printf( "Error caso 3: el ULONG_MAX deberia estar 3 veces, el 40 una y el 99 ninguna\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisIntLssRepeticiones ( p_lisVacia, ULONG_MAX ) != 0 ) || ( SLisIntLssBuscarPrimero ( p_lisVacia, ULONG_MAX ) != -1 ) ||
			 ( SLisIntLssRepeticiones ( NULL, ULONG_MAX ) != 0 ) || ( SLisIntLssBuscarSiguiente ( NULL, ULONG_MAX, -1 ) != -1 ) ||
			 ( SLisIntLssBuscar ( NULL, ULONG_MAX ) != -1 ) )
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
	SLisIntLssDestruir ( &p_lisObj );
	SLisIntLssDestruir ( &p_lisVacia );
	return ( iRes );
}

static int TestSLisIntLssEstaPosicionada01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisIntLssEstaPosicionada 01:\n" );

	SListaEnterosLargosSinSigno * p_lisObj = SLisIntLssCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( SLisIntLssEstaPosicionada ( p_lisObj ) != 0 )
		{
			printf( "Error caso 1: una lista vacia no deberia estar posicionada\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisIntLssInsertarAlFinal ( p_lisObj, 10UL );
		SLisIntLssInsertarAlFinal ( p_lisObj, 20UL );
		SLisIntLssInicio ( p_lisObj );
		if ( SLisIntLssEstaPosicionada ( p_lisObj ) != 1 )
		{
			printf( "Error caso 2: tras Inicio deberia estar posicionada\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisIntLssSiguiente ( p_lisObj );
		SLisIntLssSiguiente ( p_lisObj );
		if ( SLisIntLssEstaPosicionada ( p_lisObj ) != 0 )
		{
			printf( "Error caso 3: pasado el ultimo no deberia estar posicionada\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisIntLssFinal ( p_lisObj );
		SLisIntLssDeposicionar ( p_lisObj );
		if ( SLisIntLssEstaPosicionada ( p_lisObj ) != 0 )
		{
			printf( "Error caso 4: tras Deposicionar no deberia estar posicionada\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisIntLssEstaPosicionada ( NULL ) != 0 )
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
	SLisIntLssDestruir ( &p_lisObj );
	return ( iRes );
}

/* Encapsular se queda con la SLista que se le da, sin copiarla, y la
   destruye con ella; con una nula devuelve NULL. */
static int TestSLisIntLssEncapsular01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisIntLssEncapsular 01:\n" );

	unsigned long ulV [ 3 ] = { 7, 2, 7 };
	SListaEnterosLargosSinSigno * p_lisCopia = CrearListaEnteros ( ulV, 3 );
	SListaEnterosLargosSinSigno * p_lisRes = NULL;
	if ( ES_VALIDO ( p_lisCopia ) )
	{
		/* Se le quita la SLista a p_lisCopia para encapsularla. */
		SLista * p_lisDatos = p_lisCopia->p_lisDatos;
		p_lisCopia->p_lisDatos = NULL;
		p_lisRes = SLisIntLssEncapsular ( p_lisDatos );
		if ( ES_NULO ( p_lisRes ) || ( p_lisRes->p_lisDatos != p_lisDatos ) ||
			 ( VerificarContenido ( p_lisRes, ulV, 3 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 1: deberia envolver esa misma lista, con { 7, 2, 7 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SLisIntLssEncapsular ( NULL ) ) )
		{
			printf( "Error caso 2: con una lista nula se esperaba nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisIntLssDestruir ( &p_lisRes );
	SLisIntLssDestruir ( &p_lisCopia );
	return ( iRes );
}

int TestSListaEnterosLargosSinSigno ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SListaEnterosLargosSinSigno]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSLisIntLssOperaciones01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisIntLssCursor01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisIntLssInvalidos01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisIntLssConjunto01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisIntLssConjunto02 () == BOOL_VAL_CIERTO ) &&
			( TestSLisIntLssOrden01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisIntLssOrden02 () == BOOL_VAL_CIERTO ) &&
			( TestSLisIntLssExisten01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisIntLssInsertarLista01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisIntLssListaDup01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisIntLssExtraerLista01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisIntLssEliminarLista01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisIntLssOperacionesListas01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisIntLssOperacionesListas02 () == BOOL_VAL_CIERTO ) &&
			( TestSLisIntLssDuplicar01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisIntLssRepeticiones01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisIntLssEstaPosicionada01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisIntLssEncapsular01 () == BOOL_VAL_CIERTO ) )
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
