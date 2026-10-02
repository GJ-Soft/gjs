#include "Base.h"

#include "SSecuenciaEnterosLargos.h"



static int TestSSecEntlOperaciones01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecEntlOperaciones 01:\n" );

	SSecuenciaEnterosLargos * p_secObj = SSecEntlCrear ();
	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ( SSecEntlEsValida ( p_secObj ) != 1 ) || ( SSecEntlNumElementos ( p_secObj ) != 0 ) )
		{
			printf( "Error caso 1: la secuencia recien creada deberia ser valida y vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecEntlInsertar ( p_secObj, 100000L ) != 1 ) ||
			 ( SSecEntlInsertar ( p_secObj, 200000L ) != 1 ) ||
			 ( SSecEntlInsertar ( p_secObj, 300000L ) != 1 ) )
		{
			printf( "Error caso 2: se esperaba poder insertar los tres enteros largos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecEntlNumElementos ( p_secObj ) != 3 ) || ( SSecEntlElemento ( p_secObj, 1 ) != 200000L ) )
		{
			printf( "Error caso 3: deberia haber 3 elementos y el del indice 1 ser 200000\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecEntlExiste ( p_secObj, 300000L ) != 1 ) || ( SSecEntlExiste ( p_secObj, 1L ) != 0 ) )
		{
			printf( "Error caso 4: existe deberia encontrar 300000 y no 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecEntlEliminar ( p_secObj, 0 ) != 1 ) ||
			 ( SSecEntlNumElementos ( p_secObj ) != 2 ) || ( SSecEntlElemento ( p_secObj, 0 ) != 200000L ) )
		{
			printf( "Error caso 5: tras eliminar el primero deberian quedar 200000 y 300000\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SSecEntlVaciar ( p_secObj );
		if ( SSecEntlNumElementos ( p_secObj ) != 0 )
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
	SSecEntlDestruir ( &p_secObj );

	if ( ES_VALIDO ( p_secObj ) )
	{
		printf( "Error caso 7: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSSecEntlInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecEntlInvalidos 01:\n" );

	if ( SSecEntlEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: una secuencia nula no deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SSecEntlNumElementos ( NULL ) != 0 )
	{
		printf( "Error caso 2: una secuencia nula deberia tener 0 elementos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecuenciaEnterosLargos * p_secNula = NULL;
	SSecEntlDestruir ( &p_secNula );
	return ( iRes );
}





/* Funciones de conjunto anadidas en septiembre de 2026. Se comprueban contra
   valores ABSOLUTOS: es lo unico que caza los dos defectos que tuvieron al
   nacer —el indicador de error invertido, que hacia que estas funciones no
   recorrieran nada, y los centinelas de Min/Max cambiados—, porque los dos
   dejaban una funcion que compila, no avisa y siempre contesta lo mismo. */
static int TestSSecEntlConjunto01 ()
{
	int					iRes = BOOL_VAL_CIERTO;
	long			lMin;
	long			lMax;
	double				dMed;
	SSecuenciaEnterosLargos *	p_objObj;
	SSecuenciaEnterosLargos *	p_objUnicos;

	printf( "Test SSecEntlConjunto 01:\n" );

	/* { 5, 2, 9, 5 }: cuatro elementos, con el 5 repetido. */
	p_objObj = SSecEntlCrear ();
	SSecEntlInsertar ( p_objObj, 5L );
	SSecEntlInsertar ( p_objObj, 2L );
	SSecEntlInsertar ( p_objObj, 9L );
	SSecEntlInsertar ( p_objObj, 5L );

	if ( SSecEntlMin ( p_objObj ) != 2L )
	{
		printf( "Error caso 1: el minimo deberia ser 2L: %ld\n", SSecEntlMin ( p_objObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SSecEntlMax ( p_objObj ) != 9L )
	{
		printf( "Error caso 2: el maximo deberia ser 9L: %ld\n", SSecEntlMax ( p_objObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	SSecEntlObtenerParametros ( p_objObj, &lMin, &lMax, &dMed );
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
	if ( SSecEntlTieneRepetidos ( p_objObj ) != 1 )
	{
		printf( "Error caso 5: deberia detectar repetidos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	p_objUnicos = SSecEntlExtraerUnicos ( p_objObj );
	if ( ES_NULO ( p_objUnicos ) )
	{
		printf( "Error caso 6: ExtraerUnicos no deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SSecEntlNumElementos ( p_objUnicos ) != 3 )
		{
			printf( "Error caso 7: deberian quedar 3 unicos: %d\n", SSecEntlNumElementos ( p_objUnicos ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SSecEntlTieneRepetidos ( p_objUnicos ) != 0 )
		{
			printf( "Error caso 8: los unicos no deberian tener repetidos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SSecEntlDestruir ( &p_objUnicos );
	}
	if ( SSecEntlDefinidaPositiva ( p_objObj ) != 1 )
	{
		printf( "Error caso 9: DefinidaPositiva deberia dar 1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SSecEntlSemidefinidaPositiva ( p_objObj ) != 1 )
	{
		printf( "Error caso 10: SemidefinidaPositiva deberia dar 1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecEntlDestruir ( &p_objObj );

	/* Lista vacia: ni division por cero ni valores sin inicializar. */
	p_objObj = SSecEntlCrear ();
	lMin = 7;
	lMax = 7;
	dMed = 7.0;
	SSecEntlObtenerParametros ( p_objObj, &lMin, &lMax, &dMed );
	if ( ( dMed < -0.001 ) || ( dMed > 0.001 ) )
	{
		printf( "Error caso 11: con 0 elementos la media deberia ser 0 y no NaN: %f\n", dMed );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SSecEntlTieneRepetidos ( p_objObj ) != 0 )
	{
		printf( "Error caso 12: una coleccion vacia no tiene repetidos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecEntlDestruir ( &p_objObj );

	/* Objeto invalido: ni cuelga ni inventa. */
	if ( SSecEntlMin ( NULL ) != 0 )
	{
		printf( "Error caso 13: con objeto nulo se esperaba 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SSecEntlExtraerUnicos ( NULL ) ) )
	{
		printf( "Error caso 14: con objeto nulo ExtraerUnicos deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	ErrLimpiar ();
	return ( iRes );
}


int TestSSecuenciaEnterosLargos ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SSecuenciaEnterosLargos]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSSecEntlOperaciones01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecEntlInvalidos01 () == BOOL_VAL_CIERTO )  &&
			( TestSSecEntlConjunto01 () == BOOL_VAL_CIERTO ) )
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
