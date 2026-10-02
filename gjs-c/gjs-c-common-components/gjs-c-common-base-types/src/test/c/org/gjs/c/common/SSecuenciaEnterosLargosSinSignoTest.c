#include "Base.h"

#include "SSecuenciaEnterosLargosSinSigno.h"



/* Primer valor que un long con signo ya no puede representar: LONG_MAX + 1.
   Vale igual con long de 4 bytes ( Windows ) que de 8 ( Cygwin, Linux ). */
#define ULONG_MITAD		( (unsigned long) LONG_MAX + 1UL )



static int TestSSecEntLssOperaciones01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecEntLssOperaciones 01:\n" );

	SSecuenciaEnterosLargosSinSigno * p_secObj = SSecEntLssCrear ();
	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ( SSecEntLssEsValida ( p_secObj ) != 1 ) || ( SSecEntLssNumElementos ( p_secObj ) != 0 ) )
		{
			printf( "Error caso 1: la secuencia recien creada deberia ser valida y vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecEntLssInsertar ( p_secObj, 100UL ) != 1 ) ||
			 ( SSecEntLssInsertar ( p_secObj, 200UL ) != 1 ) ||
			 ( SSecEntLssInsertar ( p_secObj, 300UL ) != 1 ) )
		{
			printf( "Error caso 2: se esperaba poder insertar los tres valores\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecEntLssNumElementos ( p_secObj ) != 3 ) || ( SSecEntLssElemento ( p_secObj, 1 ) != 200UL ) )
		{
			printf( "Error caso 3: deberia haber 3 elementos y el del indice 1 ser 200\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecEntLssExiste ( p_secObj, 300UL ) != 1 ) || ( SSecEntLssExiste ( p_secObj, 7UL ) != 0 ) )
		{
			printf( "Error caso 4: existe deberia encontrar 300 y no 7\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecEntLssEliminar ( p_secObj, 0 ) != 1 ) ||
			 ( SSecEntLssNumElementos ( p_secObj ) != 2 ) || ( SSecEntLssElemento ( p_secObj, 0 ) != 200UL ) )
		{
			printf( "Error caso 5: tras eliminar el primero deberian quedar 200 y 300\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SSecEntLssVaciar ( p_secObj );
		if ( SSecEntLssNumElementos ( p_secObj ) != 0 )
		{
			printf( "Error caso 6: tras vaciar no deberia quedar ningun elemento\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la secuencia\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecEntLssDestruir ( &p_secObj );

	if ( ES_VALIDO ( p_secObj ) )
	{
		printf( "Error caso 7: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSSecEntLssInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecEntLssInvalidos 01:\n" );

	if ( SSecEntLssEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: una secuencia nula no deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SSecEntLssNumElementos ( NULL ) != 0 )
	{
		printf( "Error caso 2: una secuencia nula deberia tener 0 elementos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecuenciaEnterosLargosSinSigno * p_secNula = NULL;
	SSecEntLssDestruir ( &p_secNula );
	return ( iRes );
}





/* Funciones de conjunto anadidas en septiembre de 2026. Se comprueban contra
   valores ABSOLUTOS: es lo unico que caza los dos defectos que tuvieron al
   nacer —el indicador de error invertido, que hacia que estas funciones no
   recorrieran nada, y los centinelas de Min/Max cambiados—, porque los dos
   dejaban una funcion que compila, no avisa y siempre contesta lo mismo. */
static int TestSSecEntLssConjunto01 ()
{
	int					iRes = BOOL_VAL_CIERTO;
	unsigned long			ulMin;
	unsigned long			ulMax;
	double				dMed;
	SSecuenciaEnterosLargosSinSigno *	p_objObj;
	SSecuenciaEnterosLargosSinSigno *	p_objUnicos;

	printf( "Test SSecEntLssConjunto 01:\n" );

	/* { 5, 2, 9, 5 }: cuatro elementos, con el 5 repetido. */
	p_objObj = SSecEntLssCrear ();
	SSecEntLssInsertar ( p_objObj, 5UL );
	SSecEntLssInsertar ( p_objObj, 2UL );
	SSecEntLssInsertar ( p_objObj, 9UL );
	SSecEntLssInsertar ( p_objObj, 5UL );

	if ( SSecEntLssMin ( p_objObj ) != 2UL )
	{
		printf( "Error caso 1: el minimo deberia ser 2UL: %lu\n", SSecEntLssMin ( p_objObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SSecEntLssMax ( p_objObj ) != 9UL )
	{
		printf( "Error caso 2: el maximo deberia ser 9UL: %lu\n", SSecEntLssMax ( p_objObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	SSecEntLssObtenerParametros ( p_objObj, &ulMin, &ulMax, &dMed );
	if ( ( ulMin != 2UL ) || ( ulMax != 9UL ) )
	{
		printf( "Error caso 3: ObtenerParametros deberia dar 2UL y 9UL: %lu y %lu\n", ulMin, ulMax );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( dMed < 5.25 - 0.001 ) || ( dMed > 5.25 + 0.001 ) )
	{
		printf( "Error caso 4: la media deberia ser 5.25: %f\n", dMed );
		iRes = BOOL_VAL_FALSO;
	}
	/* Cuatro elementos y uno repetido: tres unicos. */
	if ( SSecEntLssTieneRepetidos ( p_objObj ) != 1 )
	{
		printf( "Error caso 5: deberia detectar repetidos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	p_objUnicos = SSecEntLssExtraerUnicos ( p_objObj );
	if ( ES_NULO ( p_objUnicos ) )
	{
		printf( "Error caso 6: ExtraerUnicos no deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SSecEntLssNumElementos ( p_objUnicos ) != 3 )
		{
			printf( "Error caso 7: deberian quedar 3 unicos: %d\n", SSecEntLssNumElementos ( p_objUnicos ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SSecEntLssTieneRepetidos ( p_objUnicos ) != 0 )
		{
			printf( "Error caso 8: los unicos no deberian tener repetidos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SSecEntLssDestruir ( &p_objUnicos );
	}
	if ( SSecEntLssDefinidaPositiva ( p_objObj ) != 1 )
	{
		printf( "Error caso 9: DefinidaPositiva deberia dar 1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecEntLssDestruir ( &p_objObj );

	/* Lista vacia: ni division por cero ni valores sin inicializar. */
	p_objObj = SSecEntLssCrear ();
	ulMin = 7;
	ulMax = 7;
	dMed = 7.0;
	SSecEntLssObtenerParametros ( p_objObj, &ulMin, &ulMax, &dMed );
	if ( ( dMed < -0.001 ) || ( dMed > 0.001 ) )
	{
		printf( "Error caso 11: con 0 elementos la media deberia ser 0 y no NaN: %f\n", dMed );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SSecEntLssTieneRepetidos ( p_objObj ) != 0 )
	{
		printf( "Error caso 12: una coleccion vacia no tiene repetidos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecEntLssDestruir ( &p_objObj );

	/* Objeto invalido: ni cuelga ni inventa. */
	if ( SSecEntLssMin ( NULL ) != 0 )
	{
		printf( "Error caso 13: con objeto nulo se esperaba 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SSecEntLssExtraerUnicos ( NULL ) ) )
	{
		printf( "Error caso 14: con objeto nulo ExtraerUnicos deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	ErrLimpiar ();
	return ( iRes );
}


/* La frontera del tipo: valores que no caben en un long con signo. Con
   DefinidaPositiva guardando el dato en long, LONG_MAX + 1 se veia negativo
   y la secuencia dejaba de ser definida positiva. */
static int TestSSecEntLssConjunto02 ()
{
	int									iRes = BOOL_VAL_CIERTO;
	SSecuenciaEnterosLargosSinSigno *	p_objObj;

	printf( "Test SSecEntLssConjunto 02:\n" );

	/* { ULONG_MAX, LONG_MAX + 1 }: los dos por encima de LONG_MAX. */
	p_objObj = SSecEntLssCrear ();
	SSecEntLssInsertar ( p_objObj, ULONG_MAX );
	SSecEntLssInsertar ( p_objObj, ULONG_MITAD );

	if ( SSecEntLssDefinidaPositiva ( p_objObj ) != 1 )
	{
		printf( "Error caso 1: valores por encima de LONG_MAX siguen siendo positivos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SSecEntLssMin ( p_objObj ) != ULONG_MITAD )
	{
		printf( "Error caso 2: el minimo deberia ser %lu: %lu\n", ULONG_MITAD, SSecEntLssMin ( p_objObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SSecEntLssMax ( p_objObj ) != ULONG_MAX )
	{
		printf( "Error caso 3: el maximo deberia ser %lu: %lu\n", ULONG_MAX, SSecEntLssMax ( p_objObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	/* Con un cero deja de serlo: en sin signo es el unico valor que lo impide. */
	SSecEntLssInsertar ( p_objObj, 0UL );
	if ( SSecEntLssDefinidaPositiva ( p_objObj ) != 0 )
	{
		printf( "Error caso 4: con un 0 DefinidaPositiva deberia dar 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecEntLssDestruir ( &p_objObj );
	ErrLimpiar ();
	return ( iRes );
}



int TestSSecuenciaEnterosLargosSinSigno ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SSecuenciaEnterosLargosSinSigno]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSSecEntLssOperaciones01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecEntLssInvalidos01 () == BOOL_VAL_CIERTO )  &&
			( TestSSecEntLssConjunto01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecEntLssConjunto02 () == BOOL_VAL_CIERTO ) )
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
