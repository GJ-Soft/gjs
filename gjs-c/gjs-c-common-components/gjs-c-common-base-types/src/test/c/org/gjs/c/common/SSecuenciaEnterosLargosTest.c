#include "Base.h"

#include "SSecuenciaEnterosLargos.h"



static int TestSSecIntlOperaciones01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecIntlOperaciones 01:\n" );

	SSecuenciaEnterosLargos * p_secObj = SSecIntlCrear ();
	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ( SSecIntlEsValida ( p_secObj ) != 1 ) || ( SSecIntlNumElementos ( p_secObj ) != 0 ) )
		{
			printf( "Error caso 1: la secuencia recien creada deberia ser valida y vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecIntlInsertar ( p_secObj, 100000L ) != 1 ) ||
			 ( SSecIntlInsertar ( p_secObj, 200000L ) != 1 ) ||
			 ( SSecIntlInsertar ( p_secObj, 300000L ) != 1 ) )
		{
			printf( "Error caso 2: se esperaba poder insertar los tres enteros largos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecIntlNumElementos ( p_secObj ) != 3 ) || ( SSecIntlElemento ( p_secObj, 1 ) != 200000L ) )
		{
			printf( "Error caso 3: deberia haber 3 elementos y el del indice 1 ser 200000\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecIntlExiste ( p_secObj, 300000L ) != 1 ) || ( SSecIntlExiste ( p_secObj, 1L ) != 0 ) )
		{
			printf( "Error caso 4: existe deberia encontrar 300000 y no 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecIntlEliminar ( p_secObj, 0 ) != 1 ) ||
			 ( SSecIntlNumElementos ( p_secObj ) != 2 ) || ( SSecIntlElemento ( p_secObj, 0 ) != 200000L ) )
		{
			printf( "Error caso 5: tras eliminar el primero deberian quedar 200000 y 300000\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SSecIntlVaciar ( p_secObj );
		if ( SSecIntlNumElementos ( p_secObj ) != 0 )
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
	SSecIntlDestruir ( &p_secObj );

	if ( ES_VALIDO ( p_secObj ) )
	{
		printf( "Error caso 7: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSSecIntlInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecIntlInvalidos 01:\n" );

	if ( SSecIntlEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: una secuencia nula no deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SSecIntlNumElementos ( NULL ) != 0 )
	{
		printf( "Error caso 2: una secuencia nula deberia tener 0 elementos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecuenciaEnterosLargos * p_secNula = NULL;
	SSecIntlDestruir ( &p_secNula );
	return ( iRes );
}





/* Funciones de conjunto anadidas en septiembre de 2026. Se comprueban contra
   valores ABSOLUTOS: es lo unico que caza los dos defectos que tuvieron al
   nacer —el indicador de error invertido, que hacia que estas funciones no
   recorrieran nada, y los centinelas de Min/Max cambiados—, porque los dos
   dejaban una funcion que compila, no avisa y siempre contesta lo mismo. */
static int TestSSecIntlConjunto01 ()
{
	int					iRes = BOOL_VAL_CIERTO;
	long			lMin;
	long			lMax;
	double				dMed;
	SSecuenciaEnterosLargos *	p_objObj;
	SSecuenciaEnterosLargos *	p_objUnicos;

	printf( "Test SSecIntlConjunto 01:\n" );

	/* { 5, 2, 9, 5 }: cuatro elementos, con el 5 repetido. */
	p_objObj = SSecIntlCrear ();
	SSecIntlInsertar ( p_objObj, 5L );
	SSecIntlInsertar ( p_objObj, 2L );
	SSecIntlInsertar ( p_objObj, 9L );
	SSecIntlInsertar ( p_objObj, 5L );

	if ( SSecIntlMin ( p_objObj ) != 2L )
	{
		printf( "Error caso 1: el minimo deberia ser 2L: %ld\n", SSecIntlMin ( p_objObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SSecIntlMax ( p_objObj ) != 9L )
	{
		printf( "Error caso 2: el maximo deberia ser 9L: %ld\n", SSecIntlMax ( p_objObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	SSecIntlObtenerParametros ( p_objObj, &lMin, &lMax, &dMed );
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
	if ( SSecIntlTieneRepetidos ( p_objObj ) != 1 )
	{
		printf( "Error caso 5: deberia detectar repetidos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	p_objUnicos = SSecIntlExtraerUnicos ( p_objObj );
	if ( ES_NULO ( p_objUnicos ) )
	{
		printf( "Error caso 6: ExtraerUnicos no deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SSecIntlNumElementos ( p_objUnicos ) != 3 )
		{
			printf( "Error caso 7: deberian quedar 3 unicos: %d\n", SSecIntlNumElementos ( p_objUnicos ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SSecIntlTieneRepetidos ( p_objUnicos ) != 0 )
		{
			printf( "Error caso 8: los unicos no deberian tener repetidos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SSecIntlDestruir ( &p_objUnicos );
	}
	if ( SSecIntlDefinidaPositiva ( p_objObj ) != 1 )
	{
		printf( "Error caso 9: DefinidaPositiva deberia dar 1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SSecIntlSemidefinidaPositiva ( p_objObj ) != 1 )
	{
		printf( "Error caso 10: SemidefinidaPositiva deberia dar 1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecIntlDestruir ( &p_objObj );

	/* Lista vacia: ni division por cero ni valores sin inicializar. */
	p_objObj = SSecIntlCrear ();
	lMin = 7;
	lMax = 7;
	dMed = 7.0;
	SSecIntlObtenerParametros ( p_objObj, &lMin, &lMax, &dMed );
	if ( ( dMed < -0.001 ) || ( dMed > 0.001 ) )
	{
		printf( "Error caso 11: con 0 elementos la media deberia ser 0 y no NaN: %f\n", dMed );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SSecIntlTieneRepetidos ( p_objObj ) != 0 )
	{
		printf( "Error caso 12: una coleccion vacia no tiene repetidos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecIntlDestruir ( &p_objObj );

	/* Objeto invalido: ni cuelga ni inventa. */
	if ( SSecIntlMin ( NULL ) != 0 )
	{
		printf( "Error caso 13: con objeto nulo se esperaba 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SSecIntlExtraerUnicos ( NULL ) ) )
	{
		printf( "Error caso 14: con objeto nulo ExtraerUnicos deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	ErrLimpiar ();
	return ( iRes );
}


/* CrearDesdeLista copia; Secuencia y Lista dan lo de dentro. Repetidos con
   BuscarPrimero / BuscarSiguiente y Repeticiones. */
static int TestSSecIntlBuscarSiguiente01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecIntlBuscarSiguiente 01:\n" );

	long lVal [ 6 ] = { 20, 10, 20, 30, 20, 40 };
	SListaEnterosLargos * p_lisVal = SLisIntlCrear ();
	SSecuenciaEnterosLargos * p_secObj = NULL;
	int iPos = 0;
	while ( ES_VALIDO ( p_lisVal ) && ( iPos < 6 ) )
	{
		SLisIntlInsertar ( p_lisVal, lVal [ iPos ] );
		iPos = iPos + 1;
	}
	if ( ES_VALIDO ( p_lisVal ) )
	{
		p_secObj = SSecIntlCrearDesdeLista ( p_lisVal );
		/* Son copias: vaciar la lista no toca la secuencia. */
		SLisIntlVaciar ( p_lisVal );
		if ( ( SSecIntlNumElementos ( p_secObj ) != 6 ) || ( SSecIntlElemento ( p_secObj, 2 ) != 20 ) )
		{
			printf( "Error caso 1: la secuencia deberia tener sus propias copias de los 6\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_NULO ( SSecIntlSecuencia ( p_secObj ) ) ||
			 ( SSecIntlLista ( p_secObj ) != SSecLista ( SSecIntlSecuencia ( p_secObj ) ) ) ||
			 ( SLisNumElementos ( SSecIntlLista ( p_secObj ) ) != 6 ) )
		{
			printf( "Error caso 2: Secuencia y Lista deberian dar la secuencia interna y su lista\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecIntlBuscarPrimero ( p_secObj, 20 ) != 0 ) ||
			 ( SSecIntlBuscarSiguiente ( p_secObj, 20, 0 ) != 2 ) ||
			 ( SSecIntlBuscarSiguiente ( p_secObj, 20, 2 ) != 4 ) ||
			 ( SSecIntlBuscarSiguiente ( p_secObj, 20, 4 ) != -1 ) ||
			 ( SSecIntlBuscarSiguiente ( p_secObj, 20, 1 ) != 2 ) ||
			 ( SSecIntlBuscarSiguiente ( p_secObj, 20, -2 ) != -1 ) ||
			 ( SSecIntlBuscar ( p_secObj, 40 ) != 5 ) )
		{
			printf( "Error caso 3: el 20 deberia estar en 0, 2 y 4, y el 40 en la 5\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecIntlRepeticiones ( p_secObj, 20 ) != 3 ) ||
			 ( SSecIntlRepeticiones ( p_secObj, 99 ) != 0 ) ||
			 ( SSecIntlBuscar ( p_secObj, 99 ) != -1 ) )
		{
			printf( "Error caso 4: el 20 deberia estar 3 veces y el 99 ninguna\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SSecIntlCrearDesdeLista ( NULL ) ) || ES_VALIDO ( SSecIntlSecuencia ( NULL ) ) ||
			 ES_VALIDO ( SSecIntlLista ( NULL ) ) || ( SSecIntlRepeticiones ( NULL, 20 ) != 0 ) ||
			 ( SSecIntlBuscarSiguiente ( NULL, 20, -1 ) != -1 ) || ( SSecIntlBuscar ( NULL, 20 ) != -1 ) )
		{
			printf( "Error caso 5: con un nulo se esperaba nulo, 0 al contar y -1 al buscar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisIntlDestruir ( &p_lisVal );
	SSecIntlDestruir ( &p_secObj );
	return ( iRes );
}


int TestSSecuenciaEnterosLargos ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SSecuenciaEnterosLargos]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSSecIntlOperaciones01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecIntlInvalidos01 () == BOOL_VAL_CIERTO )  &&
			( TestSSecIntlConjunto01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecIntlBuscarSiguiente01 () == BOOL_VAL_CIERTO ) )
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
