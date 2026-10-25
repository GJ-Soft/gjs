#include "Base.h"

#include "SListaEnterosLargosSinSigno.h"



/* Primer valor que un long con signo ya no puede representar: LONG_MAX + 1.
   Vale igual con long de 4 bytes ( Windows ) que de 8 ( Cygwin, Linux ). */
#define ULONG_MITAD		( (unsigned long) LONG_MAX + 1UL )



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
			( TestSLisIntLssOrden02 () == BOOL_VAL_CIERTO ) )
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
