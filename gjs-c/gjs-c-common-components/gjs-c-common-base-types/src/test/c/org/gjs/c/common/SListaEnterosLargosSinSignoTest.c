#include "Base.h"

#include "SListaEnterosLargosSinSigno.h"



/* Primer valor que un long con signo ya no puede representar: LONG_MAX + 1.
   Vale igual con long de 4 bytes ( Windows ) que de 8 ( Cygwin, Linux ). */
#define ULONG_MITAD		( (unsigned long) LONG_MAX + 1UL )



static int TestSLisEntLssOperaciones01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisEntLssOperaciones 01:\n" );

	SListaEnterosLargosSinSigno * p_lisObj = SLisEntLssCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( ( SLisEntLssEsValida ( p_lisObj ) != 1 ) || ( SLisEntLssEstaVacia ( p_lisObj ) != 1 ) )
		{
			printf( "Error caso 1: la lista recien creada deberia ser valida y estar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisEntLssInsertarAlFinal ( p_lisObj, 1000000UL ) != 1 ) ||
			 ( SLisEntLssInsertarAlFinal ( p_lisObj, 2000000UL ) != 1 ) ||
			 ( SLisEntLssInsertarAlFinal ( p_lisObj, 3000000UL ) != 1 ) )
		{
			printf( "Error caso 2: se esperaba poder insertar los tres enteros largos sin signo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisEntLssNumElementos ( p_lisObj ) != 3 ) || ( SLisEntLssElemento ( p_lisObj, 1 ) != 2000000UL ) )
		{
			printf( "Error caso 3: deberia haber 3 elementos y el del indice 1 ser 2000000\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Insertar al inicio desplaza el resto. */
		if ( ( SLisEntLssInsertarAlInicio ( p_lisObj, 500000UL ) != 1 ) || ( SLisEntLssElemento ( p_lisObj, 0 ) != 500000UL ) )
		{
			printf( "Error caso 4: insertar al inicio deberia dejar 500000 en la cabeza\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Modificar un elemento por posicion, con el mayor valor del tipo. */
		if ( ( SLisEntLssEstablecerElem ( p_lisObj, 0, ULONG_MAX ) != 1 ) || ( SLisEntLssElemento ( p_lisObj, 0 ) != ULONG_MAX ) )
		{
			printf( "Error caso 5: el elemento 0 deberia poder modificarse a ULONG_MAX: %lu\n", SLisEntLssElemento ( p_lisObj, 0 ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisEntLssExiste ( p_lisObj, 2000000UL ) != 1 ) || ( SLisEntLssExiste ( p_lisObj, 7UL ) != 0 ) )
		{
			printf( "Error caso 6: existe deberia encontrar 2000000 y no 7\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisEntLssBuscar ( p_lisObj, 3000000UL ) != 3 ) || ( SLisEntLssBuscar ( p_lisObj, ULONG_MAX ) != 0 ) )
		{
			printf( "Error caso 7: buscar 3000000 deberia dar el indice 3 y ULONG_MAX el 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Fuera de rango devuelve 0, igual que SSecEntLssElemento. */
		if ( SLisEntLssElemento ( p_lisObj, 4 ) != 0UL )
		{
			printf( "Error caso 8: un indice fuera de rango deberia dar 0: %lu\n", SLisEntLssElemento ( p_lisObj, 4 ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* Eliminar el primero. */
		if ( ( SLisEntLssEliminarElem ( p_lisObj, 0 ) != 1 ) ||
			 ( SLisEntLssNumElementos ( p_lisObj ) != 3 ) || ( SLisEntLssElemento ( p_lisObj, 0 ) != 1000000UL ) )
		{
			printf( "Error caso 9: tras eliminar el primero la cabeza deberia ser 1000000\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisEntLssVaciar ( p_lisObj );
		if ( SLisEntLssEstaVacia ( p_lisObj ) != 1 )
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
	SLisEntLssDestruir ( &p_lisObj );

	if ( ES_VALIDO ( p_lisObj ) )
	{
		printf( "Error caso 11: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSLisEntLssCursor01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisEntLssCursor 01:\n" );

	SListaEnterosLargosSinSigno * p_lisObj = SLisEntLssCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		SLisEntLssInsertarAlFinal ( p_lisObj, 10UL );
		SLisEntLssInsertarAlFinal ( p_lisObj, 20UL );
		SLisEntLssInsertarAlFinal ( p_lisObj, ULONG_MAX );

		SLisEntLssInicio ( p_lisObj );
		if ( ( SLisEntLssActual ( p_lisObj ) != 10UL ) || ( SLisEntLssEstaEnInicio ( p_lisObj ) != 1 ) )
		{
			printf( "Error caso 1: el inicio deberia ser 10\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisEntLssSiguiente ( p_lisObj );
		if ( SLisEntLssActual ( p_lisObj ) != 20UL )
		{
			printf( "Error caso 2: el siguiente del inicio deberia ser 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisEntLssFinal ( p_lisObj );
		if ( ( SLisEntLssActual ( p_lisObj ) != ULONG_MAX ) || ( SLisEntLssEstaEnFinal ( p_lisObj ) != 1 ) )
		{
			printf( "Error caso 3: el final deberia ser ULONG_MAX: %lu\n", SLisEntLssActual ( p_lisObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisEntLssDestruir ( &p_lisObj );
	return ( iRes );
}

static int TestSLisEntLssInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisEntLssInvalidos 01:\n" );

	if ( SLisEntLssEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: una lista nula no deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLisEntLssNumElementos ( NULL ) != 0 )
	{
		printf( "Error caso 2: una lista nula deberia tener 0 elementos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLisEntLssElemento ( NULL, 0 ) != 0UL )
	{
		printf( "Error caso 3: una lista nula deberia dar 0 como elemento\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SListaEnterosLargosSinSigno * p_lisNula = NULL;
	SLisEntLssDestruir ( &p_lisNula );
	ErrLimpiar ();
	return ( iRes );
}





/* Funciones de conjunto, contra valores ABSOLUTOS. Con valores pequenos
   ya se ve el centinela de Max: si arranca en LONG_MIN, en sin signo eso es
   LONG_MAX + 1 y ningun elemento lo supera. */
static int TestSLisEntLssConjunto01 ()
{
	int								iRes = BOOL_VAL_CIERTO;
	unsigned long					ulMin;
	unsigned long					ulMax;
	double							dMed;
	SListaEnterosLargosSinSigno *	p_objObj;
	SListaEnterosLargosSinSigno *	p_objUnicos;

	printf( "Test SLisEntLssConjunto 01:\n" );

	/* { 5, 2, 9, 5 }: cuatro elementos, con el 5 repetido. */
	p_objObj = SLisEntLssCrear ();
	SLisEntLssInsertar ( p_objObj, 5UL );
	SLisEntLssInsertar ( p_objObj, 2UL );
	SLisEntLssInsertar ( p_objObj, 9UL );
	SLisEntLssInsertar ( p_objObj, 5UL );

	if ( SLisEntLssMin ( p_objObj ) != 2UL )
	{
		printf( "Error caso 1: el minimo deberia ser 2: %lu\n", SLisEntLssMin ( p_objObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLisEntLssMax ( p_objObj ) != 9UL )
	{
		printf( "Error caso 2: el maximo deberia ser 9: %lu\n", SLisEntLssMax ( p_objObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	SLisEntLssObtenerParametros ( p_objObj, &ulMin, &ulMax, &dMed );
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
	if ( SLisEntLssTieneRepetidos ( p_objObj ) != 1 )
	{
		printf( "Error caso 5: deberia detectar repetidos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	p_objUnicos = SLisEntLssExtraerUnicos ( p_objObj );
	if ( ES_NULO ( p_objUnicos ) )
	{
		printf( "Error caso 6: ExtraerUnicos no deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SLisEntLssNumElementos ( p_objUnicos ) != 3 )
		{
			printf( "Error caso 7: deberian quedar 3 unicos: %d\n", SLisEntLssNumElementos ( p_objUnicos ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisEntLssTieneRepetidos ( p_objUnicos ) != 0 )
		{
			printf( "Error caso 8: los unicos no deberian tener repetidos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisEntLssDestruir ( &p_objUnicos );
	}
	if ( SLisEntLssDefinidaPositiva ( p_objObj ) != 1 )
	{
		printf( "Error caso 9: DefinidaPositiva deberia dar 1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Con un cero deja de serlo: en sin signo es el unico valor que lo impide. */
	SLisEntLssInsertar ( p_objObj, 0UL );
	if ( SLisEntLssDefinidaPositiva ( p_objObj ) != 0 )
	{
		printf( "Error caso 10: con un 0 DefinidaPositiva deberia dar 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisEntLssDestruir ( &p_objObj );

	/* Lista vacia: ni division por cero ni valores sin inicializar. Los
	   extremos quedan en sus centinelas. */
	p_objObj = SLisEntLssCrear ();
	ulMin = 7;
	ulMax = 7;
	dMed = 7.0;
	SLisEntLssObtenerParametros ( p_objObj, &ulMin, &ulMax, &dMed );
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
	if ( SLisEntLssTieneRepetidos ( p_objObj ) != 0 )
	{
		printf( "Error caso 13: una coleccion vacia no tiene repetidos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisEntLssDestruir ( &p_objObj );

	/* Objeto invalido: ni cuelga ni inventa. */
	if ( SLisEntLssMin ( NULL ) != 0UL )
	{
		printf( "Error caso 14: con objeto nulo se esperaba 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLisEntLssMax ( NULL ) != 0UL )
	{
		printf( "Error caso 15: con objeto nulo se esperaba 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SLisEntLssExtraerUnicos ( NULL ) ) )
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
static int TestSLisEntLssConjunto02 ()
{
	int								iRes = BOOL_VAL_CIERTO;
	unsigned long					ulMin;
	unsigned long					ulMax;
	double							dMed;
	SListaEnterosLargosSinSigno *	p_objObj;

	printf( "Test SLisEntLssConjunto 02:\n" );

	/* { ULONG_MAX, LONG_MAX + 1 }: los dos por encima de LONG_MAX. */
	p_objObj = SLisEntLssCrear ();
	SLisEntLssInsertar ( p_objObj, ULONG_MAX );
	SLisEntLssInsertar ( p_objObj, ULONG_MITAD );

	if ( SLisEntLssMin ( p_objObj ) != ULONG_MITAD )
	{
		printf( "Error caso 1: el minimo deberia ser %lu: %lu\n", ULONG_MITAD, SLisEntLssMin ( p_objObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLisEntLssMax ( p_objObj ) != ULONG_MAX )
	{
		printf( "Error caso 2: el maximo deberia ser %lu: %lu\n", ULONG_MAX, SLisEntLssMax ( p_objObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	SLisEntLssObtenerParametros ( p_objObj, &ulMin, &ulMax, &dMed );
	if ( ( ulMin != ULONG_MITAD ) || ( ulMax != ULONG_MAX ) )
	{
		printf( "Error caso 3: ObtenerParametros deberia dar %lu y %lu: %lu y %lu\n", ULONG_MITAD, ULONG_MAX, ulMin, ulMax );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLisEntLssDefinidaPositiva ( p_objObj ) != 1 )
	{
		printf( "Error caso 4: valores por encima de LONG_MAX siguen siendo positivos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLisEntLssExiste ( p_objObj, ULONG_MITAD ) != 1 )
	{
		printf( "Error caso 5: deberia existir LONG_MAX + 1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* LONG_MAX, justo por debajo, pasa a ser el minimo. */
	SLisEntLssInsertar ( p_objObj, (unsigned long) LONG_MAX );
	if ( SLisEntLssMin ( p_objObj ) != (unsigned long) LONG_MAX )
	{
		printf( "Error caso 6: el minimo deberia ser %ld: %lu\n", LONG_MAX, SLisEntLssMin ( p_objObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	SLisEntLssDestruir ( &p_objObj );
	ErrLimpiar ();
	return ( iRes );
}


/* Las de orden, que solo tienen las listas. */
static int TestSLisEntLssOrden01 ()
{
	int								iRes = BOOL_VAL_CIERTO;
	SListaEnterosLargosSinSigno *	p_lisObj;
	SListaEnterosLargosSinSigno *	p_lisOrd;

	printf( "Test SLisEntLssOrden 01:\n" );

	p_lisObj = SLisEntLssCrear ();
	SLisEntLssInsertar ( p_lisObj, 5UL );
	SLisEntLssInsertar ( p_lisObj, 2UL );
	SLisEntLssInsertar ( p_lisObj, 9UL );
	SLisEntLssInsertar ( p_lisObj, 5UL );

	/* { 5, 2, 9, 5 } no esta ordenada. */
	if ( SLisEntLssEstaOrdenada ( p_lisObj ) != 0 )
	{
		printf( "Error caso 1: esa lista no esta ordenada\n" );
		iRes = BOOL_VAL_FALSO;
	}
	p_lisOrd = SLisEntLssOrdenar ( p_lisObj );
	if ( ES_NULO ( p_lisOrd ) )
	{
		printf( "Error caso 2: Ordenar no deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SLisEntLssNumElementos ( p_lisOrd ) != 4 )
		{
			printf( "Error caso 3: ordenar no deberia perder elementos: %d\n", SLisEntLssNumElementos ( p_lisOrd ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisEntLssEstaOrdenada ( p_lisOrd ) != 1 )
		{
			printf( "Error caso 4: el resultado de Ordenar deberia estar ordenado\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisEntLssElemento ( p_lisOrd, 0 ) != 2UL )
		{
			printf( "Error caso 5: el primero deberia ser 2: %lu\n", SLisEntLssElemento ( p_lisOrd, 0 ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisEntLssElemento ( p_lisOrd, 3 ) != 9UL )
		{
			printf( "Error caso 6: el ultimo deberia ser 9: %lu\n", SLisEntLssElemento ( p_lisOrd, 3 ) );
			iRes = BOOL_VAL_FALSO;
		}
		SLisEntLssDestruir ( &p_lisOrd );
	}
	/* La original no se toca. */
	if ( SLisEntLssEstaOrdenada ( p_lisObj ) != 0 )
	{
		printf( "Error caso 7: Ordenar no deberia modificar la lista de entrada\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisEntLssDestruir ( &p_lisObj );

	/* ExtraerUnicosExt ( , 1 ) devuelve los unicos YA ordenados. */
	p_lisObj = SLisEntLssCrear ();
	SLisEntLssInsertar ( p_lisObj, 5UL );
	SLisEntLssInsertar ( p_lisObj, 2UL );
	SLisEntLssInsertar ( p_lisObj, 9UL );
	SLisEntLssInsertar ( p_lisObj, 5UL );

	p_lisOrd = SLisEntLssExtraerUnicosExt ( p_lisObj, 1 );
	if ( ES_NULO ( p_lisOrd ) )
	{
		printf( "Error caso 8: ExtraerUnicosExt no deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SLisEntLssNumElementos ( p_lisOrd ) != 3 )
		{
			printf( "Error caso 9: deberian quedar 3 unicos: %d\n", SLisEntLssNumElementos ( p_lisOrd ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisEntLssEstaOrdenada ( p_lisOrd ) != 1 )
		{
			printf( "Error caso 10: con iOrdenar = 1 deberian salir ordenados\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisEntLssDestruir ( &p_lisOrd );
	}
	SLisEntLssDestruir ( &p_lisObj );
	ErrLimpiar ();
	return ( iRes );
}


/* Orden en la frontera: comparando en long con signo, LONG_MAX + 1 se ve
   negativo y queda por delante del 0. */
static int TestSLisEntLssOrden02 ()
{
	int								iRes = BOOL_VAL_CIERTO;
	SListaEnterosLargosSinSigno *	p_lisObj;
	SListaEnterosLargosSinSigno *	p_lisOrd;

	printf( "Test SLisEntLssOrden 02:\n" );

	/* { 1, LONG_MAX + 1, ULONG_MAX } esta ordenada. */
	p_lisObj = SLisEntLssCrear ();
	SLisEntLssInsertar ( p_lisObj, 1UL );
	SLisEntLssInsertar ( p_lisObj, ULONG_MITAD );
	SLisEntLssInsertar ( p_lisObj, ULONG_MAX );
	if ( SLisEntLssEstaOrdenada ( p_lisObj ) != 1 )
	{
		printf( "Error caso 1: { 1, LONG_MAX + 1, ULONG_MAX } esta ordenada\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisEntLssDestruir ( &p_lisObj );

	/* { LONG_MAX + 1, 1 } no lo esta. */
	p_lisObj = SLisEntLssCrear ();
	SLisEntLssInsertar ( p_lisObj, ULONG_MITAD );
	SLisEntLssInsertar ( p_lisObj, 1UL );
	if ( SLisEntLssEstaOrdenada ( p_lisObj ) != 0 )
	{
		printf( "Error caso 2: { LONG_MAX + 1, 1 } no esta ordenada\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisEntLssDestruir ( &p_lisObj );

	/* Ordenar { ULONG_MAX, 0, LONG_MAX + 1, 5 } da { 0, 5, LONG_MAX + 1, ULONG_MAX }. */
	p_lisObj = SLisEntLssCrear ();
	SLisEntLssInsertar ( p_lisObj, ULONG_MAX );
	SLisEntLssInsertar ( p_lisObj, 0UL );
	SLisEntLssInsertar ( p_lisObj, ULONG_MITAD );
	SLisEntLssInsertar ( p_lisObj, 5UL );
	p_lisOrd = SLisEntLssOrdenar ( p_lisObj );
	if ( ES_NULO ( p_lisOrd ) )
	{
		printf( "Error caso 3: Ordenar no deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( ( SLisEntLssElemento ( p_lisOrd, 0 ) != 0UL ) ||
			 ( SLisEntLssElemento ( p_lisOrd, 1 ) != 5UL ) ||
			 ( SLisEntLssElemento ( p_lisOrd, 2 ) != ULONG_MITAD ) ||
			 ( SLisEntLssElemento ( p_lisOrd, 3 ) != ULONG_MAX ) )
		{
			printf( "Error caso 4: se esperaba { 0, 5, %lu, %lu }: { %lu, %lu, %lu, %lu }\n",
					ULONG_MITAD, ULONG_MAX,
					SLisEntLssElemento ( p_lisOrd, 0 ), SLisEntLssElemento ( p_lisOrd, 1 ),
					SLisEntLssElemento ( p_lisOrd, 2 ), SLisEntLssElemento ( p_lisOrd, 3 ) );
			iRes = BOOL_VAL_FALSO;
		}
		SLisEntLssDestruir ( &p_lisOrd );
	}
	SLisEntLssDestruir ( &p_lisObj );
	ErrLimpiar ();
	return ( iRes );
}


int TestSListaEnterosLargosSinSigno ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SListaEnterosLargosSinSigno]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSLisEntLssOperaciones01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisEntLssCursor01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisEntLssInvalidos01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisEntLssConjunto01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisEntLssConjunto02 () == BOOL_VAL_CIERTO ) &&
			( TestSLisEntLssOrden01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisEntLssOrden02 () == BOOL_VAL_CIERTO ) )
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
