#include "Base.h"

#include "SSecuenciaEnteros.h"



static int TestSSecEntOperaciones01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecEntOperaciones 01:\n" );

	SSecuenciaEnteros * p_secObj = SSecEntCrear ();
	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ( SSecEntEsValida ( p_secObj ) != 1 ) || ( SSecEntNumElementos ( p_secObj ) != 0 ) )
		{
			printf( "Error caso 1: la secuencia recien creada deberia ser valida y vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecEntInsertar ( p_secObj, 10 ) != 1 ) ||
			 ( SSecEntInsertar ( p_secObj, 20 ) != 1 ) ||
			 ( SSecEntInsertar ( p_secObj, 30 ) != 1 ) )
		{
			printf( "Error caso 2: se esperaba poder insertar los tres enteros\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecEntNumElementos ( p_secObj ) != 3 ) || ( SSecEntElemento ( p_secObj, 1 ) != 20 ) )
		{
			printf( "Error caso 3: deberia haber 3 elementos y el del indice 1 ser 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecEntExiste ( p_secObj, 30 ) != 1 ) || ( SSecEntExiste ( p_secObj, 99 ) != 0 ) )
		{
			printf( "Error caso 4: existe deberia encontrar 30 y no 99\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Modificar el elemento del indice 1. */
		if ( ( SSecEntModificar ( p_secObj, 1, 25 ) != 1 ) || ( SSecEntElemento ( p_secObj, 1 ) != 25 ) )
		{
			printf( "Error caso 5: el elemento 1 deberia poder modificarse a 25\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Eliminar el primero: se desplazan los demas. */
		if ( ( SSecEntEliminar ( p_secObj, 0 ) != 1 ) ||
			 ( SSecEntNumElementos ( p_secObj ) != 2 ) || ( SSecEntElemento ( p_secObj, 0 ) != 25 ) )
		{
			printf( "Error caso 6: tras eliminar el primero deberian quedar 25 y 30\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Vaciar. */
		SSecEntVaciar ( p_secObj );
		if ( SSecEntNumElementos ( p_secObj ) != 0 )
		{
			printf( "Error caso 7: tras vaciar no deberia quedar ningun elemento\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la secuencia\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecEntDestruir ( &p_secObj );

	if ( ES_VALIDO ( p_secObj ) )
	{
		printf( "Error caso 8: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSSecEntInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecEntInvalidos 01:\n" );

	if ( SSecEntEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: una secuencia nula no deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SSecEntNumElementos ( NULL ) != 0 )
	{
		printf( "Error caso 2: una secuencia nula deberia tener 0 elementos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SSecEntInsertar ( NULL, 5 ) == 1 )
	{
		printf( "Error caso 3: insertar en una secuencia nula no deberia devolver exito\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecuenciaEnteros * p_secNula = NULL;
	SSecEntDestruir ( &p_secNula );
	return ( iRes );
}





/* Funciones de conjunto anadidas en septiembre de 2026. Se comprueban contra
   valores ABSOLUTOS: es lo unico que caza los dos defectos que tuvieron al
   nacer —el indicador de error invertido, que hacia que estas funciones no
   recorrieran nada, y los centinelas de Min/Max cambiados—, porque los dos
   dejaban una funcion que compila, no avisa y siempre contesta lo mismo. */
static int TestSSecEntConjunto01 ()
{
	int					iRes = BOOL_VAL_CIERTO;
	int			iMin;
	int			iMax;
	double				dMed;
	SSecuenciaEnteros *	p_objObj;
	SSecuenciaEnteros *	p_objUnicos;

	printf( "Test SSecEntConjunto 01:\n" );

	/* { 5, 2, 9, 5 }: cuatro elementos, con el 5 repetido. */
	p_objObj = SSecEntCrear ();
	SSecEntInsertar ( p_objObj, 5 );
	SSecEntInsertar ( p_objObj, 2 );
	SSecEntInsertar ( p_objObj, 9 );
	SSecEntInsertar ( p_objObj, 5 );

	if ( SSecEntMin ( p_objObj ) != 2 )
	{
		printf( "Error caso 1: el minimo deberia ser 2: %d\n", SSecEntMin ( p_objObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SSecEntMax ( p_objObj ) != 9 )
	{
		printf( "Error caso 2: el maximo deberia ser 9: %d\n", SSecEntMax ( p_objObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	SSecEntObtenerParametros ( p_objObj, &iMin, &iMax, &dMed );
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
	if ( SSecEntTieneRepetidos ( p_objObj ) != 1 )
	{
		printf( "Error caso 5: deberia detectar repetidos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	p_objUnicos = SSecEntExtraerUnicos ( p_objObj );
	if ( ES_NULO ( p_objUnicos ) )
	{
		printf( "Error caso 6: ExtraerUnicos no deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SSecEntNumElementos ( p_objUnicos ) != 3 )
		{
			printf( "Error caso 7: deberian quedar 3 unicos: %d\n", SSecEntNumElementos ( p_objUnicos ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SSecEntTieneRepetidos ( p_objUnicos ) != 0 )
		{
			printf( "Error caso 8: los unicos no deberian tener repetidos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SSecEntDestruir ( &p_objUnicos );
	}
	if ( SSecEntDefinidaPositiva ( p_objObj ) != 1 )
	{
		printf( "Error caso 9: DefinidaPositiva deberia dar 1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SSecEntSemidefinidaPositiva ( p_objObj ) != 1 )
	{
		printf( "Error caso 10: SemidefinidaPositiva deberia dar 1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecEntDestruir ( &p_objObj );

	/* Lista vacia: ni division por cero ni valores sin inicializar. */
	p_objObj = SSecEntCrear ();
	iMin = 7;
	iMax = 7;
	dMed = 7.0;
	SSecEntObtenerParametros ( p_objObj, &iMin, &iMax, &dMed );
	if ( ( dMed < -0.001 ) || ( dMed > 0.001 ) )
	{
		printf( "Error caso 11: con 0 elementos la media deberia ser 0 y no NaN: %f\n", dMed );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SSecEntTieneRepetidos ( p_objObj ) != 0 )
	{
		printf( "Error caso 12: una coleccion vacia no tiene repetidos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecEntDestruir ( &p_objObj );

	/* Objeto invalido: ni cuelga ni inventa. */
	if ( SSecEntMin ( NULL ) != 0 )
	{
		printf( "Error caso 13: con objeto nulo se esperaba 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SSecEntExtraerUnicos ( NULL ) ) )
	{
		printf( "Error caso 14: con objeto nulo ExtraerUnicos deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	ErrLimpiar ();
	return ( iRes );
}


int TestSSecuenciaEnteros ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SSecuenciaEnteros]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSSecEntOperaciones01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecEntInvalidos01 () == BOOL_VAL_CIERTO )  &&
			( TestSSecEntConjunto01 () == BOOL_VAL_CIERTO ) )
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
