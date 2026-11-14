#include "Base.h"

#include "SSecuenciaEnterosLargos.h"
#include "SListaEnterosLargos.h"



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


static SSecuenciaEnterosLargos * CrearSec ( long * p_lValores, int iNum )
{
	SSecuenciaEnterosLargos * p_secObj = SSecIntlCrear ();
	int iPos = 0;
	while ( ES_VALIDO ( p_secObj ) && ( iPos < iNum ) )
	{
		SSecIntlInsertar ( p_secObj, p_lValores [ iPos ] );
		iPos = iPos + 1;
	}
	return ( p_secObj );
}

static SListaEnterosLargos * CrearLista ( long * p_lValores, int iNum )
{
	SListaEnterosLargos * p_lisObj = SLisIntlCrear ();
	int iPos = 0;
	while ( ES_VALIDO ( p_lisObj ) && ( iPos < iNum ) )
	{
		SLisIntlInsertarAlFinal ( p_lisObj, p_lValores [ iPos ] );
		iPos = iPos + 1;
	}
	return ( p_lisObj );
}

/* Comprueba numero y orden de los valores. */
static int VerificarSec ( SSecuenciaEnterosLargos * p_secObj, long * p_lEsperados, int iNum )
{
	int iRes = BOOL_VAL_CIERTO;

	if ( ( SSecIntlEsValida ( p_secObj ) != 1 ) || ( SSecIntlNumElementos ( p_secObj ) != iNum ) )
	{
		printf( "  Verificacion: se esperaban %d elementos: %d\n", iNum, SSecIntlNumElementos ( p_secObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	int iPos = 0;
	while ( ( iPos < iNum ) && ( iRes == BOOL_VAL_CIERTO ) )
	{
		if ( SSecIntlElemento ( p_secObj, iPos ) != p_lEsperados [ iPos ] )
		{
			printf( "  Verificacion: en pos %d se esperaba %ld: %ld\n", iPos, p_lEsperados [ iPos ], SSecIntlElemento ( p_secObj, iPos ) );
			iRes = BOOL_VAL_FALSO;
		}
		iPos = iPos + 1;
	}
	return ( iRes );
}

/* Igual, para una lista. */
static int VerificarLista ( SListaEnterosLargos * p_lisObj, long * p_lEsperados, int iNum )
{
	int iRes = BOOL_VAL_CIERTO;

	if ( ( SLisIntlEsValida ( p_lisObj ) != 1 ) || ( SLisIntlNumElementos ( p_lisObj ) != iNum ) )
	{
		printf( "  Verificacion: se esperaban %d elementos: %d\n", iNum, SLisIntlNumElementos ( p_lisObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	int iPos = 0;
	while ( ( iPos < iNum ) && ( iRes == BOOL_VAL_CIERTO ) )
	{
		if ( SLisIntlElemento ( p_lisObj, iPos ) != p_lEsperados [ iPos ] )
		{
			printf( "  Verificacion: en pos %d se esperaba %ld: %ld\n", iPos, p_lEsperados [ iPos ], SLisIntlElemento ( p_lisObj, iPos ) );
			iRes = BOOL_VAL_FALSO;
		}
		iPos = iPos + 1;
	}
	return ( iRes );
}

/* ListaIntl da una lista con COPIAS: cambiarla no toca la secuencia. */
static int TestSSecIntlListaIntl01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecIntlListaIntl 01:\n" );

	long lV [ 3 ] = { 5, 1, 5 };
	long lEsp [ 4 ] = { 5, 1, 5, 8 };
	SSecuenciaEnterosLargos * p_secObj = CrearSec ( lV, 3 );
	SListaEnterosLargos * p_lisRes = NULL;
	if ( ES_VALIDO ( p_secObj ) )
	{
		p_lisRes = SSecIntlListaIntl ( p_secObj );
		if ( VerificarLista ( p_lisRes, lV, 3 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 1: la lista deberia ser { 5, 1, 5 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisIntlInsertarAlFinal ( p_lisRes, 8 ) != 1 ) ||
			 ( VerificarLista ( p_lisRes, lEsp, 4 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarSec ( p_secObj, lV, 3 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 2: insertar en la lista no deberia tocar la secuencia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SSecIntlListaIntl ( NULL ) ) )
		{
			printf( "Error caso 3: con una secuencia nula se esperaba nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la secuencia\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisIntlDestruir ( &p_lisRes );
	SSecIntlDestruir ( &p_secObj );
	return ( iRes );
}

/* Pertenencia; Concatenar copia, Eliminar destruye todas las apariciones y
   Extraer mueve. */
static int TestSSecIntlOperacionesListas01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecIntlOperacionesListas 01:\n" );

	long lVal [ 5 ] = { 1, 2, 3, 2, 4 };
	long l29 [ 2 ] = { 2, 9 };
	long l43 [ 2 ] = { 4, 3 };
	long l9 [ 1 ] = { 9 };
	long l1 [ 1 ] = { 1 };
	SSecuenciaEnterosLargos * p_secObj = CrearSec ( lVal, 5 );
	SSecuenciaEnterosLargos * p_sec29 = CrearSec ( l29, 2 );
	SSecuenciaEnterosLargos * p_sec9 = CrearSec ( l9, 1 );
	SListaEnterosLargos * p_lis43 = CrearLista ( l43, 2 );
	SListaEnterosLargos * p_lis9 = CrearLista ( l9, 1 );
	SListaEnterosLargos * p_lis1 = CrearLista ( l1, 1 );
	SSecuenciaEnterosLargos * p_secRes = NULL;
	if ( ES_VALIDO ( p_secObj ) && ES_VALIDO ( p_sec29 ) && ES_VALIDO ( p_sec9 ) && ES_VALIDO ( p_lis43 ) &&
		 ES_VALIDO ( p_lis9 ) && ES_VALIDO ( p_lis1 ) )
	{
		if ( ( SSecIntlExistenTodos ( p_secObj, p_sec29 ) != 0 ) || ( SSecIntlExisteAlguno ( p_secObj, p_sec29 ) != 1 ) ||
			 ( SSecIntlExistenTodosLista ( p_secObj, p_lis43 ) != 1 ) || ( SSecIntlExisteAlgunoLista ( p_secObj, p_lis9 ) != 0 ) )
		{
			printf( "Error caso 1: se esperaba 0, 1, 1 y 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Concatenar copia: la lista y la otra secuencia no cambian. */
		long lEsp2 [ 9 ] = { 1, 2, 3, 2, 4, 4, 3, 2, 9 };
		if ( ( SSecIntlConcatenarLista ( p_secObj, p_lis43 ) != 1 ) ||
			 ( SSecIntlConcatenar ( p_secObj, p_sec29 ) != 1 ) ||
			 ( VerificarSec ( p_secObj, lEsp2, 9 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarLista ( p_lis43, l43, 2 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarSec ( p_sec29, l29, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 2: se esperaban copias al final y los valores sin tocar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Eliminar quita todas las apariciones. */
		long lEsp3 [ 4 ] = { 1, 2, 2, 2 };
		if ( ( SSecIntlEliminarLista ( p_secObj, p_lis43 ) != 1 ) ||
			 ( SSecIntlEliminarSecuencia ( p_secObj, p_sec9 ) != 1 ) ||
			 ( VerificarSec ( p_secObj, lEsp3, 4 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 3: deberia quedar { 1, 2, 2, 2 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Extraer mueve, todas las apariciones de cada valor. */
		long lEsp4 [ 3 ] = { 2, 2, 2 };
		p_secRes = SSecIntlExtraerLista ( p_secObj, p_lis1 );
		if ( ( VerificarSec ( p_secRes, l1, 1 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarSec ( p_secObj, lEsp4, 3 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 4: se esperaba sacar el 1 y dejar { 2, 2, 2 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SSecIntlDestruir ( &p_secRes );
		p_secRes = SSecIntlExtraerSecuencia ( p_secObj, p_sec29 );
		if ( ( VerificarSec ( p_secRes, lEsp4, 3 ) != BOOL_VAL_CIERTO ) ||
			 ( SSecIntlNumElementos ( p_secObj ) != 0 ) )
		{
			printf( "Error caso 5: se esperaba sacar los tres 2 y dejarla vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SSecIntlDestruir ( &p_secRes );
		if ( ( SSecIntlExistenTodos ( NULL, p_sec29 ) != 0 ) || ( SSecIntlExisteAlgunoLista ( p_sec29, NULL ) != 0 ) ||
			 ( SSecIntlConcatenarLista ( p_sec29, NULL ) != 0 ) || ( SSecIntlConcatenar ( NULL, p_sec9 ) != 0 ) ||
			 ( SSecIntlConcatenar ( p_sec29, p_sec29 ) != 0 ) ||
			 ( SSecIntlEliminarSecuencia ( p_sec29, p_sec29 ) != 0 ) || ( SSecIntlEliminarLista ( NULL, p_lis9 ) != 0 ) ||
			 ES_VALIDO ( SSecIntlExtraerSecuencia ( p_sec29, p_sec29 ) ) ||
			 ES_VALIDO ( SSecIntlExtraerLista ( p_sec29, NULL ) ) ||
			 ( VerificarSec ( p_sec29, l29, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 6: con nulos o la misma secuencia se esperaba 0 o nulo sin cambios\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las secuencias o las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecIntlDestruir ( &p_secObj );
	SSecIntlDestruir ( &p_sec29 );
	SSecIntlDestruir ( &p_sec9 );
	SLisIntlDestruir ( &p_lis43 );
	SLisIntlDestruir ( &p_lis9 );
	SLisIntlDestruir ( &p_lis1 );
	ErrLimpiar ();
	return ( iRes );
}

/* Union es concatenacion; Interseccion y Diferencia, en el orden de V1. Las
   tres con copias, sin tocar las de entrada. */
static int TestSSecIntlUnion01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecIntlUnion 01:\n" );

	long lV1 [ 4 ] = { 1, 2, 3, 4 };
	long lV2 [ 3 ] = { 4, 2, 5 };
	long lEspU [ 7 ] = { 1, 2, 3, 4, 4, 2, 5 };
	long lEspI [ 2 ] = { 2, 4 };
	long lEspD [ 2 ] = { 1, 3 };
	SSecuenciaEnterosLargos * p_sec1 = CrearSec ( lV1, 4 );
	SSecuenciaEnterosLargos * p_sec2 = CrearSec ( lV2, 3 );
	SListaEnterosLargos * p_lis2 = CrearLista ( lV2, 3 );
	SSecuenciaEnterosLargos * p_secU = NULL;
	SSecuenciaEnterosLargos * p_secI = NULL;
	SSecuenciaEnterosLargos * p_secD = NULL;
	SSecuenciaEnterosLargos * p_secUL = NULL;
	SSecuenciaEnterosLargos * p_secIL = NULL;
	SSecuenciaEnterosLargos * p_secDL = NULL;
	if ( ES_VALIDO ( p_sec1 ) && ES_VALIDO ( p_sec2 ) && ES_VALIDO ( p_lis2 ) )
	{
		p_secU = SSecIntlUnion ( p_sec1, p_sec2 );
		p_secI = SSecIntlInterseccion ( p_sec1, p_sec2 );
		p_secD = SSecIntlDiferencia ( p_sec1, p_sec2 );
		if ( ( VerificarSec ( p_secU, lEspU, 7 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarSec ( p_secI, lEspI, 2 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarSec ( p_secD, lEspD, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 1: con secuencias se esperaba { 1, 2, 3, 4, 4, 2, 5 }, { 2, 4 } y { 1, 3 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_secUL = SSecIntlUnionLista ( p_sec1, p_lis2 );
		p_secIL = SSecIntlInterseccionLista ( p_sec1, p_lis2 );
		p_secDL = SSecIntlDiferenciaLista ( p_sec1, p_lis2 );
		if ( ( VerificarSec ( p_secUL, lEspU, 7 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarSec ( p_secIL, lEspI, 2 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarSec ( p_secDL, lEspD, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 2: con listas se esperaba { 1, 2, 3, 4, 4, 2, 5 }, { 2, 4 } y { 1, 3 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( VerificarSec ( p_sec1, lV1, 4 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarSec ( p_sec2, lV2, 3 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarLista ( p_lis2, lV2, 3 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 3: las de entrada no deberian cambiar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SSecIntlUnion ( p_sec1, NULL ) ) || ES_VALIDO ( SSecIntlInterseccion ( NULL, p_sec2 ) ) ||
			 ES_VALIDO ( SSecIntlDiferencia ( p_sec1, NULL ) ) || ES_VALIDO ( SSecIntlUnionLista ( NULL, p_lis2 ) ) ||
			 ES_VALIDO ( SSecIntlInterseccionLista ( p_sec1, NULL ) ) || ES_VALIDO ( SSecIntlDiferenciaLista ( NULL, p_lis2 ) ) )
		{
			printf( "Error caso 4: con nulos se esperaba nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las secuencias o la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecIntlDestruir ( &p_secU );
	SSecIntlDestruir ( &p_secI );
	SSecIntlDestruir ( &p_secD );
	SSecIntlDestruir ( &p_secUL );
	SSecIntlDestruir ( &p_secIL );
	SSecIntlDestruir ( &p_secDL );
	SSecIntlDestruir ( &p_sec1 );
	SSecIntlDestruir ( &p_sec2 );
	SLisIntlDestruir ( &p_lis2 );
	ErrLimpiar ();
	return ( iRes );
}

int TestSSecuenciaEnterosLargos ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SSecuenciaEnterosLargos]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSSecIntlOperaciones01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecIntlInvalidos01 () == BOOL_VAL_CIERTO )  &&
			( TestSSecIntlConjunto01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecIntlBuscarSiguiente01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecIntlListaIntl01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecIntlOperacionesListas01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecIntlUnion01 () == BOOL_VAL_CIERTO ) )
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
