#include "Base.h"

#include "SSecuenciaEnteros.h"
#include "SListaEnteros.h"



static int TestSSecIntOperaciones01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecIntOperaciones 01:\n" );

	SSecuenciaEnteros * p_secObj = SSecIntCrear ();
	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ( SSecIntEsValida ( p_secObj ) != 1 ) || ( SSecIntNumElementos ( p_secObj ) != 0 ) )
		{
			printf( "Error caso 1: la secuencia recien creada deberia ser valida y vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecIntInsertar ( p_secObj, 10 ) != 1 ) ||
			 ( SSecIntInsertar ( p_secObj, 20 ) != 1 ) ||
			 ( SSecIntInsertar ( p_secObj, 30 ) != 1 ) )
		{
			printf( "Error caso 2: se esperaba poder insertar los tres enteros\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecIntNumElementos ( p_secObj ) != 3 ) || ( SSecIntElemento ( p_secObj, 1 ) != 20 ) )
		{
			printf( "Error caso 3: deberia haber 3 elementos y el del indice 1 ser 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecIntExiste ( p_secObj, 30 ) != 1 ) || ( SSecIntExiste ( p_secObj, 99 ) != 0 ) )
		{
			printf( "Error caso 4: existe deberia encontrar 30 y no 99\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Modificar el elemento del indice 1. */
		if ( ( SSecIntModificar ( p_secObj, 1, 25 ) != 1 ) || ( SSecIntElemento ( p_secObj, 1 ) != 25 ) )
		{
			printf( "Error caso 5: el elemento 1 deberia poder modificarse a 25\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Eliminar el primero: se desplazan los demas. */
		if ( ( SSecIntEliminar ( p_secObj, 0 ) != 1 ) ||
			 ( SSecIntNumElementos ( p_secObj ) != 2 ) || ( SSecIntElemento ( p_secObj, 0 ) != 25 ) )
		{
			printf( "Error caso 6: tras eliminar el primero deberian quedar 25 y 30\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Vaciar. */
		SSecIntVaciar ( p_secObj );
		if ( SSecIntNumElementos ( p_secObj ) != 0 )
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
	SSecIntDestruir ( &p_secObj );

	if ( ES_VALIDO ( p_secObj ) )
	{
		printf( "Error caso 8: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSSecIntInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecIntInvalidos 01:\n" );

	if ( SSecIntEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: una secuencia nula no deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SSecIntNumElementos ( NULL ) != 0 )
	{
		printf( "Error caso 2: una secuencia nula deberia tener 0 elementos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SSecIntInsertar ( NULL, 5 ) == 1 )
	{
		printf( "Error caso 3: insertar en una secuencia nula no deberia devolver exito\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecuenciaEnteros * p_secNula = NULL;
	SSecIntDestruir ( &p_secNula );
	return ( iRes );
}





/* Funciones de conjunto anadidas en septiembre de 2026. Se comprueban contra
   valores ABSOLUTOS: es lo unico que caza los dos defectos que tuvieron al
   nacer —el indicador de error invertido, que hacia que estas funciones no
   recorrieran nada, y los centinelas de Min/Max cambiados—, porque los dos
   dejaban una funcion que compila, no avisa y siempre contesta lo mismo. */
static int TestSSecIntConjunto01 ()
{
	int					iRes = BOOL_VAL_CIERTO;
	int			iMin;
	int			iMax;
	double				dMed;
	SSecuenciaEnteros *	p_objObj;
	SSecuenciaEnteros *	p_objUnicos;

	printf( "Test SSecIntConjunto 01:\n" );

	/* { 5, 2, 9, 5 }: cuatro elementos, con el 5 repetido. */
	p_objObj = SSecIntCrear ();
	SSecIntInsertar ( p_objObj, 5 );
	SSecIntInsertar ( p_objObj, 2 );
	SSecIntInsertar ( p_objObj, 9 );
	SSecIntInsertar ( p_objObj, 5 );

	if ( SSecIntMin ( p_objObj ) != 2 )
	{
		printf( "Error caso 1: el minimo deberia ser 2: %d\n", SSecIntMin ( p_objObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SSecIntMax ( p_objObj ) != 9 )
	{
		printf( "Error caso 2: el maximo deberia ser 9: %d\n", SSecIntMax ( p_objObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	SSecIntObtenerParametros ( p_objObj, &iMin, &iMax, &dMed );
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
	if ( SSecIntTieneRepetidos ( p_objObj ) != 1 )
	{
		printf( "Error caso 5: deberia detectar repetidos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	p_objUnicos = SSecIntExtraerUnicos ( p_objObj );
	if ( ES_NULO ( p_objUnicos ) )
	{
		printf( "Error caso 6: ExtraerUnicos no deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SSecIntNumElementos ( p_objUnicos ) != 3 )
		{
			printf( "Error caso 7: deberian quedar 3 unicos: %d\n", SSecIntNumElementos ( p_objUnicos ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SSecIntTieneRepetidos ( p_objUnicos ) != 0 )
		{
			printf( "Error caso 8: los unicos no deberian tener repetidos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SSecIntDestruir ( &p_objUnicos );
	}
	if ( SSecIntDefinidaPositiva ( p_objObj ) != 1 )
	{
		printf( "Error caso 9: DefinidaPositiva deberia dar 1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SSecIntSemidefinidaPositiva ( p_objObj ) != 1 )
	{
		printf( "Error caso 10: SemidefinidaPositiva deberia dar 1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecIntDestruir ( &p_objObj );

	/* Lista vacia: ni division por cero ni valores sin inicializar. */
	p_objObj = SSecIntCrear ();
	iMin = 7;
	iMax = 7;
	dMed = 7.0;
	SSecIntObtenerParametros ( p_objObj, &iMin, &iMax, &dMed );
	if ( ( dMed < -0.001 ) || ( dMed > 0.001 ) )
	{
		printf( "Error caso 11: con 0 elementos la media deberia ser 0 y no NaN: %f\n", dMed );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SSecIntTieneRepetidos ( p_objObj ) != 0 )
	{
		printf( "Error caso 12: una coleccion vacia no tiene repetidos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecIntDestruir ( &p_objObj );

	/* Objeto invalido: ni cuelga ni inventa. */
	if ( SSecIntMin ( NULL ) != 0 )
	{
		printf( "Error caso 13: con objeto nulo se esperaba 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SSecIntExtraerUnicos ( NULL ) ) )
	{
		printf( "Error caso 14: con objeto nulo ExtraerUnicos deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	ErrLimpiar ();
	return ( iRes );
}


/* CrearDesdeLista copia; Secuencia y Lista dan lo de dentro. Repetidos con
   BuscarPrimero / BuscarSiguiente y Repeticiones. */
static int TestSSecIntBuscarSiguiente01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecIntBuscarSiguiente 01:\n" );

	int iVal [ 6 ] = { 20, 10, 20, 30, 20, 40 };
	SListaEnteros * p_lisVal = SLisIntCrear ();
	SSecuenciaEnteros * p_secObj = NULL;
	int iPos = 0;
	while ( ES_VALIDO ( p_lisVal ) && ( iPos < 6 ) )
	{
		SLisIntInsertar ( p_lisVal, iVal [ iPos ] );
		iPos = iPos + 1;
	}
	if ( ES_VALIDO ( p_lisVal ) )
	{
		p_secObj = SSecIntCrearDesdeLista ( p_lisVal );
		/* Son copias: vaciar la lista no toca la secuencia. */
		SLisIntVaciar ( p_lisVal );
		if ( ( SSecIntNumElementos ( p_secObj ) != 6 ) || ( SSecIntElemento ( p_secObj, 2 ) != 20 ) )
		{
			printf( "Error caso 1: la secuencia deberia tener sus propias copias de los 6\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_NULO ( SSecIntSecuencia ( p_secObj ) ) ||
			 ( SSecIntLista ( p_secObj ) != SSecLista ( SSecIntSecuencia ( p_secObj ) ) ) ||
			 ( SLisNumElementos ( SSecIntLista ( p_secObj ) ) != 6 ) )
		{
			printf( "Error caso 2: Secuencia y Lista deberian dar la secuencia interna y su lista\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecIntBuscarPrimero ( p_secObj, 20 ) != 0 ) ||
			 ( SSecIntBuscarSiguiente ( p_secObj, 20, 0 ) != 2 ) ||
			 ( SSecIntBuscarSiguiente ( p_secObj, 20, 2 ) != 4 ) ||
			 ( SSecIntBuscarSiguiente ( p_secObj, 20, 4 ) != -1 ) ||
			 ( SSecIntBuscarSiguiente ( p_secObj, 20, 1 ) != 2 ) ||
			 ( SSecIntBuscarSiguiente ( p_secObj, 20, -2 ) != -1 ) ||
			 ( SSecIntBuscar ( p_secObj, 40 ) != 5 ) )
		{
			printf( "Error caso 3: el 20 deberia estar en 0, 2 y 4, y el 40 en la 5\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecIntRepeticiones ( p_secObj, 20 ) != 3 ) ||
			 ( SSecIntRepeticiones ( p_secObj, 99 ) != 0 ) ||
			 ( SSecIntBuscar ( p_secObj, 99 ) != -1 ) )
		{
			printf( "Error caso 4: el 20 deberia estar 3 veces y el 99 ninguna\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SSecIntCrearDesdeLista ( NULL ) ) || ES_VALIDO ( SSecIntSecuencia ( NULL ) ) ||
			 ES_VALIDO ( SSecIntLista ( NULL ) ) || ( SSecIntRepeticiones ( NULL, 20 ) != 0 ) ||
			 ( SSecIntBuscarSiguiente ( NULL, 20, -1 ) != -1 ) || ( SSecIntBuscar ( NULL, 20 ) != -1 ) )
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
	SLisIntDestruir ( &p_lisVal );
	SSecIntDestruir ( &p_secObj );
	return ( iRes );
}


static SSecuenciaEnteros * CrearSec ( int * p_iValores, int iNum )
{
	SSecuenciaEnteros * p_secObj = SSecIntCrear ();
	int iPos = 0;
	while ( ES_VALIDO ( p_secObj ) && ( iPos < iNum ) )
	{
		SSecIntInsertar ( p_secObj, p_iValores [ iPos ] );
		iPos = iPos + 1;
	}
	return ( p_secObj );
}

static SListaEnteros * CrearLista ( int * p_iValores, int iNum )
{
	SListaEnteros * p_lisObj = SLisIntCrear ();
	int iPos = 0;
	while ( ES_VALIDO ( p_lisObj ) && ( iPos < iNum ) )
	{
		SLisIntInsertarAlFinal ( p_lisObj, p_iValores [ iPos ] );
		iPos = iPos + 1;
	}
	return ( p_lisObj );
}

/* Comprueba numero y orden de los valores. */
static int VerificarSec ( SSecuenciaEnteros * p_secObj, int * p_iEsperados, int iNum )
{
	int iRes = BOOL_VAL_CIERTO;

	if ( ( SSecIntEsValida ( p_secObj ) != 1 ) || ( SSecIntNumElementos ( p_secObj ) != iNum ) )
	{
		printf( "  Verificacion: se esperaban %d elementos: %d\n", iNum, SSecIntNumElementos ( p_secObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	int iPos = 0;
	while ( ( iPos < iNum ) && ( iRes == BOOL_VAL_CIERTO ) )
	{
		if ( SSecIntElemento ( p_secObj, iPos ) != p_iEsperados [ iPos ] )
		{
			printf( "  Verificacion: en pos %d se esperaba %d: %d\n", iPos, p_iEsperados [ iPos ], SSecIntElemento ( p_secObj, iPos ) );
			iRes = BOOL_VAL_FALSO;
		}
		iPos = iPos + 1;
	}
	return ( iRes );
}

/* Igual, para una lista. */
static int VerificarLista ( SListaEnteros * p_lisObj, int * p_iEsperados, int iNum )
{
	int iRes = BOOL_VAL_CIERTO;

	if ( ( SLisIntEsValida ( p_lisObj ) != 1 ) || ( SLisIntNumElementos ( p_lisObj ) != iNum ) )
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

/* ListaInt da una lista con COPIAS: cambiarla no toca la secuencia. */
static int TestSSecIntListaInt01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecIntListaInt 01:\n" );

	int iV [ 3 ] = { 5, 1, 5 };
	int iEsp [ 4 ] = { 5, 1, 5, 8 };
	SSecuenciaEnteros * p_secObj = CrearSec ( iV, 3 );
	SListaEnteros * p_lisRes = NULL;
	if ( ES_VALIDO ( p_secObj ) )
	{
		p_lisRes = SSecIntListaInt ( p_secObj );
		if ( VerificarLista ( p_lisRes, iV, 3 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 1: la lista deberia ser { 5, 1, 5 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisIntInsertarAlFinal ( p_lisRes, 8 ) != 1 ) ||
			 ( VerificarLista ( p_lisRes, iEsp, 4 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarSec ( p_secObj, iV, 3 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 2: insertar en la lista no deberia tocar la secuencia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SSecIntListaInt ( NULL ) ) )
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
	SLisIntDestruir ( &p_lisRes );
	SSecIntDestruir ( &p_secObj );
	return ( iRes );
}

/* Pertenencia; Concatenar copia, Eliminar destruye todas las apariciones y
   Extraer mueve. */
static int TestSSecIntOperacionesListas01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecIntOperacionesListas 01:\n" );

	int iVal [ 5 ] = { 1, 2, 3, 2, 4 };
	int i29 [ 2 ] = { 2, 9 };
	int i43 [ 2 ] = { 4, 3 };
	int i9 [ 1 ] = { 9 };
	int i1 [ 1 ] = { 1 };
	SSecuenciaEnteros * p_secObj = CrearSec ( iVal, 5 );
	SSecuenciaEnteros * p_sec29 = CrearSec ( i29, 2 );
	SSecuenciaEnteros * p_sec9 = CrearSec ( i9, 1 );
	SListaEnteros * p_lis43 = CrearLista ( i43, 2 );
	SListaEnteros * p_lis9 = CrearLista ( i9, 1 );
	SListaEnteros * p_lis1 = CrearLista ( i1, 1 );
	SSecuenciaEnteros * p_secRes = NULL;
	if ( ES_VALIDO ( p_secObj ) && ES_VALIDO ( p_sec29 ) && ES_VALIDO ( p_sec9 ) && ES_VALIDO ( p_lis43 ) &&
		 ES_VALIDO ( p_lis9 ) && ES_VALIDO ( p_lis1 ) )
	{
		if ( ( SSecIntExistenTodos ( p_secObj, p_sec29 ) != 0 ) || ( SSecIntExisteAlguno ( p_secObj, p_sec29 ) != 1 ) ||
			 ( SSecIntExistenTodosLista ( p_secObj, p_lis43 ) != 1 ) || ( SSecIntExisteAlgunoLista ( p_secObj, p_lis9 ) != 0 ) )
		{
			printf( "Error caso 1: se esperaba 0, 1, 1 y 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Concatenar copia: la lista y la otra secuencia no cambian. */
		int iEsp2 [ 9 ] = { 1, 2, 3, 2, 4, 4, 3, 2, 9 };
		if ( ( SSecIntConcatenarLista ( p_secObj, p_lis43 ) != 1 ) ||
			 ( SSecIntConcatenar ( p_secObj, p_sec29 ) != 1 ) ||
			 ( VerificarSec ( p_secObj, iEsp2, 9 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarLista ( p_lis43, i43, 2 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarSec ( p_sec29, i29, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 2: se esperaban copias al final y los valores sin tocar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Eliminar quita todas las apariciones. */
		int iEsp3 [ 4 ] = { 1, 2, 2, 2 };
		if ( ( SSecIntEliminarLista ( p_secObj, p_lis43 ) != 1 ) ||
			 ( SSecIntEliminarSecuencia ( p_secObj, p_sec9 ) != 1 ) ||
			 ( VerificarSec ( p_secObj, iEsp3, 4 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 3: deberia quedar { 1, 2, 2, 2 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Extraer mueve, todas las apariciones de cada valor. */
		int iEsp4 [ 3 ] = { 2, 2, 2 };
		p_secRes = SSecIntExtraerLista ( p_secObj, p_lis1 );
		if ( ( VerificarSec ( p_secRes, i1, 1 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarSec ( p_secObj, iEsp4, 3 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 4: se esperaba sacar el 1 y dejar { 2, 2, 2 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SSecIntDestruir ( &p_secRes );
		p_secRes = SSecIntExtraerSecuencia ( p_secObj, p_sec29 );
		if ( ( VerificarSec ( p_secRes, iEsp4, 3 ) != BOOL_VAL_CIERTO ) ||
			 ( SSecIntNumElementos ( p_secObj ) != 0 ) )
		{
			printf( "Error caso 5: se esperaba sacar los tres 2 y dejarla vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SSecIntDestruir ( &p_secRes );
		if ( ( SSecIntExistenTodos ( NULL, p_sec29 ) != 0 ) || ( SSecIntExisteAlgunoLista ( p_sec29, NULL ) != 0 ) ||
			 ( SSecIntConcatenarLista ( p_sec29, NULL ) != 0 ) || ( SSecIntConcatenar ( NULL, p_sec9 ) != 0 ) ||
			 ( SSecIntConcatenar ( p_sec29, p_sec29 ) != 0 ) ||
			 ( SSecIntEliminarSecuencia ( p_sec29, p_sec29 ) != 0 ) || ( SSecIntEliminarLista ( NULL, p_lis9 ) != 0 ) ||
			 ES_VALIDO ( SSecIntExtraerSecuencia ( p_sec29, p_sec29 ) ) ||
			 ES_VALIDO ( SSecIntExtraerLista ( p_sec29, NULL ) ) ||
			 ( VerificarSec ( p_sec29, i29, 2 ) != BOOL_VAL_CIERTO ) )
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
	SSecIntDestruir ( &p_secObj );
	SSecIntDestruir ( &p_sec29 );
	SSecIntDestruir ( &p_sec9 );
	SLisIntDestruir ( &p_lis43 );
	SLisIntDestruir ( &p_lis9 );
	SLisIntDestruir ( &p_lis1 );
	ErrLimpiar ();
	return ( iRes );
}

/* Union es concatenacion; Interseccion y Diferencia, en el orden de V1. Las
   tres con copias, sin tocar las de entrada. */
static int TestSSecIntUnion01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecIntUnion 01:\n" );

	int iV1 [ 4 ] = { 1, 2, 3, 4 };
	int iV2 [ 3 ] = { 4, 2, 5 };
	int iEspU [ 7 ] = { 1, 2, 3, 4, 4, 2, 5 };
	int iEspI [ 2 ] = { 2, 4 };
	int iEspD [ 2 ] = { 1, 3 };
	SSecuenciaEnteros * p_sec1 = CrearSec ( iV1, 4 );
	SSecuenciaEnteros * p_sec2 = CrearSec ( iV2, 3 );
	SListaEnteros * p_lis2 = CrearLista ( iV2, 3 );
	SSecuenciaEnteros * p_secU = NULL;
	SSecuenciaEnteros * p_secI = NULL;
	SSecuenciaEnteros * p_secD = NULL;
	SSecuenciaEnteros * p_secUL = NULL;
	SSecuenciaEnteros * p_secIL = NULL;
	SSecuenciaEnteros * p_secDL = NULL;
	if ( ES_VALIDO ( p_sec1 ) && ES_VALIDO ( p_sec2 ) && ES_VALIDO ( p_lis2 ) )
	{
		p_secU = SSecIntUnion ( p_sec1, p_sec2 );
		p_secI = SSecIntInterseccion ( p_sec1, p_sec2 );
		p_secD = SSecIntDiferencia ( p_sec1, p_sec2 );
		if ( ( VerificarSec ( p_secU, iEspU, 7 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarSec ( p_secI, iEspI, 2 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarSec ( p_secD, iEspD, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 1: con secuencias se esperaba { 1, 2, 3, 4, 4, 2, 5 }, { 2, 4 } y { 1, 3 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_secUL = SSecIntUnionLista ( p_sec1, p_lis2 );
		p_secIL = SSecIntInterseccionLista ( p_sec1, p_lis2 );
		p_secDL = SSecIntDiferenciaLista ( p_sec1, p_lis2 );
		if ( ( VerificarSec ( p_secUL, iEspU, 7 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarSec ( p_secIL, iEspI, 2 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarSec ( p_secDL, iEspD, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 2: con listas se esperaba { 1, 2, 3, 4, 4, 2, 5 }, { 2, 4 } y { 1, 3 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( VerificarSec ( p_sec1, iV1, 4 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarSec ( p_sec2, iV2, 3 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarLista ( p_lis2, iV2, 3 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 3: las de entrada no deberian cambiar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SSecIntUnion ( p_sec1, NULL ) ) || ES_VALIDO ( SSecIntInterseccion ( NULL, p_sec2 ) ) ||
			 ES_VALIDO ( SSecIntDiferencia ( p_sec1, NULL ) ) || ES_VALIDO ( SSecIntUnionLista ( NULL, p_lis2 ) ) ||
			 ES_VALIDO ( SSecIntInterseccionLista ( p_sec1, NULL ) ) || ES_VALIDO ( SSecIntDiferenciaLista ( NULL, p_lis2 ) ) )
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
	SSecIntDestruir ( &p_secU );
	SSecIntDestruir ( &p_secI );
	SSecIntDestruir ( &p_secD );
	SSecIntDestruir ( &p_secUL );
	SSecIntDestruir ( &p_secIL );
	SSecIntDestruir ( &p_secDL );
	SSecIntDestruir ( &p_sec1 );
	SSecIntDestruir ( &p_sec2 );
	SLisIntDestruir ( &p_lis2 );
	ErrLimpiar ();
	return ( iRes );
}

int TestSSecuenciaEnteros ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SSecuenciaEnteros]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSSecIntOperaciones01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecIntInvalidos01 () == BOOL_VAL_CIERTO )  &&
			( TestSSecIntConjunto01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecIntBuscarSiguiente01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecIntListaInt01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecIntOperacionesListas01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecIntUnion01 () == BOOL_VAL_CIERTO ) )
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
