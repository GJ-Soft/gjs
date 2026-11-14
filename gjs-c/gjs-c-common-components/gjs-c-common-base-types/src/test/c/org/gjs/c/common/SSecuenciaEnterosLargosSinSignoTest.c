#include "Base.h"

#include "SSecuenciaEnterosLargosSinSigno.h"
#include "SListaEnterosLargosSinSigno.h"



/* Primer valor que un long con signo ya no puede representar: LONG_MAX + 1.
   Vale igual con long de 4 bytes ( Windows ) que de 8 ( Cygwin, Linux ). */
#define ULONG_MITAD		( (unsigned long) LONG_MAX + 1UL )



static int TestSSecIntLssOperaciones01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecIntLssOperaciones 01:\n" );

	SSecuenciaEnterosLargosSinSigno * p_secObj = SSecIntLssCrear ();
	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ( SSecIntLssEsValida ( p_secObj ) != 1 ) || ( SSecIntLssNumElementos ( p_secObj ) != 0 ) )
		{
			printf( "Error caso 1: la secuencia recien creada deberia ser valida y vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecIntLssInsertar ( p_secObj, 100UL ) != 1 ) ||
			 ( SSecIntLssInsertar ( p_secObj, 200UL ) != 1 ) ||
			 ( SSecIntLssInsertar ( p_secObj, 300UL ) != 1 ) )
		{
			printf( "Error caso 2: se esperaba poder insertar los tres valores\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecIntLssNumElementos ( p_secObj ) != 3 ) || ( SSecIntLssElemento ( p_secObj, 1 ) != 200UL ) )
		{
			printf( "Error caso 3: deberia haber 3 elementos y el del indice 1 ser 200\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecIntLssExiste ( p_secObj, 300UL ) != 1 ) || ( SSecIntLssExiste ( p_secObj, 7UL ) != 0 ) )
		{
			printf( "Error caso 4: existe deberia encontrar 300 y no 7\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecIntLssEliminar ( p_secObj, 0 ) != 1 ) ||
			 ( SSecIntLssNumElementos ( p_secObj ) != 2 ) || ( SSecIntLssElemento ( p_secObj, 0 ) != 200UL ) )
		{
			printf( "Error caso 5: tras eliminar el primero deberian quedar 200 y 300\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SSecIntLssVaciar ( p_secObj );
		if ( SSecIntLssNumElementos ( p_secObj ) != 0 )
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
	SSecIntLssDestruir ( &p_secObj );

	if ( ES_VALIDO ( p_secObj ) )
	{
		printf( "Error caso 7: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSSecIntLssInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecIntLssInvalidos 01:\n" );

	if ( SSecIntLssEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: una secuencia nula no deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SSecIntLssNumElementos ( NULL ) != 0 )
	{
		printf( "Error caso 2: una secuencia nula deberia tener 0 elementos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecuenciaEnterosLargosSinSigno * p_secNula = NULL;
	SSecIntLssDestruir ( &p_secNula );
	return ( iRes );
}





/* Funciones de conjunto anadidas en septiembre de 2026. Se comprueban contra
   valores ABSOLUTOS: es lo unico que caza los dos defectos que tuvieron al
   nacer —el indicador de error invertido, que hacia que estas funciones no
   recorrieran nada, y los centinelas de Min/Max cambiados—, porque los dos
   dejaban una funcion que compila, no avisa y siempre contesta lo mismo. */
static int TestSSecIntLssConjunto01 ()
{
	int					iRes = BOOL_VAL_CIERTO;
	unsigned long			ulMin;
	unsigned long			ulMax;
	double				dMed;
	SSecuenciaEnterosLargosSinSigno *	p_objObj;
	SSecuenciaEnterosLargosSinSigno *	p_objUnicos;

	printf( "Test SSecIntLssConjunto 01:\n" );

	/* { 5, 2, 9, 5 }: cuatro elementos, con el 5 repetido. */
	p_objObj = SSecIntLssCrear ();
	SSecIntLssInsertar ( p_objObj, 5UL );
	SSecIntLssInsertar ( p_objObj, 2UL );
	SSecIntLssInsertar ( p_objObj, 9UL );
	SSecIntLssInsertar ( p_objObj, 5UL );

	if ( SSecIntLssMin ( p_objObj ) != 2UL )
	{
		printf( "Error caso 1: el minimo deberia ser 2UL: %lu\n", SSecIntLssMin ( p_objObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SSecIntLssMax ( p_objObj ) != 9UL )
	{
		printf( "Error caso 2: el maximo deberia ser 9UL: %lu\n", SSecIntLssMax ( p_objObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	SSecIntLssObtenerParametros ( p_objObj, &ulMin, &ulMax, &dMed );
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
	if ( SSecIntLssTieneRepetidos ( p_objObj ) != 1 )
	{
		printf( "Error caso 5: deberia detectar repetidos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	p_objUnicos = SSecIntLssExtraerUnicos ( p_objObj );
	if ( ES_NULO ( p_objUnicos ) )
	{
		printf( "Error caso 6: ExtraerUnicos no deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SSecIntLssNumElementos ( p_objUnicos ) != 3 )
		{
			printf( "Error caso 7: deberian quedar 3 unicos: %d\n", SSecIntLssNumElementos ( p_objUnicos ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SSecIntLssTieneRepetidos ( p_objUnicos ) != 0 )
		{
			printf( "Error caso 8: los unicos no deberian tener repetidos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SSecIntLssDestruir ( &p_objUnicos );
	}
	if ( SSecIntLssDefinidaPositiva ( p_objObj ) != 1 )
	{
		printf( "Error caso 9: DefinidaPositiva deberia dar 1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecIntLssDestruir ( &p_objObj );

	/* Lista vacia: ni division por cero ni valores sin inicializar. */
	p_objObj = SSecIntLssCrear ();
	ulMin = 7;
	ulMax = 7;
	dMed = 7.0;
	SSecIntLssObtenerParametros ( p_objObj, &ulMin, &ulMax, &dMed );
	if ( ( dMed < -0.001 ) || ( dMed > 0.001 ) )
	{
		printf( "Error caso 11: con 0 elementos la media deberia ser 0 y no NaN: %f\n", dMed );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SSecIntLssTieneRepetidos ( p_objObj ) != 0 )
	{
		printf( "Error caso 12: una coleccion vacia no tiene repetidos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecIntLssDestruir ( &p_objObj );

	/* Objeto invalido: ni cuelga ni inventa. */
	if ( SSecIntLssMin ( NULL ) != 0 )
	{
		printf( "Error caso 13: con objeto nulo se esperaba 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SSecIntLssExtraerUnicos ( NULL ) ) )
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
static int TestSSecIntLssConjunto02 ()
{
	int									iRes = BOOL_VAL_CIERTO;
	SSecuenciaEnterosLargosSinSigno *	p_objObj;

	printf( "Test SSecIntLssConjunto 02:\n" );

	/* { ULONG_MAX, LONG_MAX + 1 }: los dos por encima de LONG_MAX. */
	p_objObj = SSecIntLssCrear ();
	SSecIntLssInsertar ( p_objObj, ULONG_MAX );
	SSecIntLssInsertar ( p_objObj, ULONG_MITAD );

	if ( SSecIntLssDefinidaPositiva ( p_objObj ) != 1 )
	{
		printf( "Error caso 1: valores por encima de LONG_MAX siguen siendo positivos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SSecIntLssMin ( p_objObj ) != ULONG_MITAD )
	{
		printf( "Error caso 2: el minimo deberia ser %lu: %lu\n", ULONG_MITAD, SSecIntLssMin ( p_objObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SSecIntLssMax ( p_objObj ) != ULONG_MAX )
	{
		printf( "Error caso 3: el maximo deberia ser %lu: %lu\n", ULONG_MAX, SSecIntLssMax ( p_objObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	/* Con un cero deja de serlo: en sin signo es el unico valor que lo impide. */
	SSecIntLssInsertar ( p_objObj, 0UL );
	if ( SSecIntLssDefinidaPositiva ( p_objObj ) != 0 )
	{
		printf( "Error caso 4: con un 0 DefinidaPositiva deberia dar 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecIntLssDestruir ( &p_objObj );
	ErrLimpiar ();
	return ( iRes );
}



/* CrearDesdeLista copia; Secuencia y Lista dan lo de dentro. Repetidos con
   BuscarPrimero / BuscarSiguiente y Repeticiones. */
static int TestSSecIntLssBuscarSiguiente01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecIntLssBuscarSiguiente 01:\n" );

	unsigned long ulVal [ 6 ] = { ULONG_MAX, 10, ULONG_MAX, 30, ULONG_MAX, 40 };
	SListaEnterosLargosSinSigno * p_lisVal = SLisIntLssCrear ();
	SSecuenciaEnterosLargosSinSigno * p_secObj = NULL;
	int iPos = 0;
	while ( ES_VALIDO ( p_lisVal ) && ( iPos < 6 ) )
	{
		SLisIntLssInsertar ( p_lisVal, ulVal [ iPos ] );
		iPos = iPos + 1;
	}
	if ( ES_VALIDO ( p_lisVal ) )
	{
		p_secObj = SSecIntLssCrearDesdeLista ( p_lisVal );
		/* Son copias: vaciar la lista no toca la secuencia. */
		SLisIntLssVaciar ( p_lisVal );
		if ( ( SSecIntLssNumElementos ( p_secObj ) != 6 ) || ( SSecIntLssElemento ( p_secObj, 2 ) != ULONG_MAX ) )
		{
			printf( "Error caso 1: la secuencia deberia tener sus propias copias de los 6\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_NULO ( SSecIntLssSecuencia ( p_secObj ) ) ||
			 ( SSecIntLssLista ( p_secObj ) != SSecLista ( SSecIntLssSecuencia ( p_secObj ) ) ) ||
			 ( SLisNumElementos ( SSecIntLssLista ( p_secObj ) ) != 6 ) )
		{
			printf( "Error caso 2: Secuencia y Lista deberian dar la secuencia interna y su lista\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecIntLssBuscarPrimero ( p_secObj, ULONG_MAX ) != 0 ) ||
			 ( SSecIntLssBuscarSiguiente ( p_secObj, ULONG_MAX, 0 ) != 2 ) ||
			 ( SSecIntLssBuscarSiguiente ( p_secObj, ULONG_MAX, 2 ) != 4 ) ||
			 ( SSecIntLssBuscarSiguiente ( p_secObj, ULONG_MAX, 4 ) != -1 ) ||
			 ( SSecIntLssBuscarSiguiente ( p_secObj, ULONG_MAX, 1 ) != 2 ) ||
			 ( SSecIntLssBuscarSiguiente ( p_secObj, ULONG_MAX, -2 ) != -1 ) ||
			 ( SSecIntLssBuscar ( p_secObj, 40 ) != 5 ) )
		{
			printf( "Error caso 3: el ULONG_MAX deberia estar en 0, 2 y 4, y el 40 en la 5\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecIntLssRepeticiones ( p_secObj, ULONG_MAX ) != 3 ) ||
			 ( SSecIntLssRepeticiones ( p_secObj, 99 ) != 0 ) ||
			 ( SSecIntLssBuscar ( p_secObj, 99 ) != -1 ) )
		{
			printf( "Error caso 4: el ULONG_MAX deberia estar 3 veces y el 99 ninguna\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SSecIntLssCrearDesdeLista ( NULL ) ) || ES_VALIDO ( SSecIntLssSecuencia ( NULL ) ) ||
			 ES_VALIDO ( SSecIntLssLista ( NULL ) ) || ( SSecIntLssRepeticiones ( NULL, ULONG_MAX ) != 0 ) ||
			 ( SSecIntLssBuscarSiguiente ( NULL, ULONG_MAX, -1 ) != -1 ) || ( SSecIntLssBuscar ( NULL, ULONG_MAX ) != -1 ) )
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
	SLisIntLssDestruir ( &p_lisVal );
	SSecIntLssDestruir ( &p_secObj );
	return ( iRes );
}


static SSecuenciaEnterosLargosSinSigno * CrearSec ( unsigned long * p_ulValores, int iNum )
{
	SSecuenciaEnterosLargosSinSigno * p_secObj = SSecIntLssCrear ();
	int iPos = 0;
	while ( ES_VALIDO ( p_secObj ) && ( iPos < iNum ) )
	{
		SSecIntLssInsertar ( p_secObj, p_ulValores [ iPos ] );
		iPos = iPos + 1;
	}
	return ( p_secObj );
}

static SListaEnterosLargosSinSigno * CrearLista ( unsigned long * p_ulValores, int iNum )
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

/* Comprueba numero y orden de los valores. */
static int VerificarSec ( SSecuenciaEnterosLargosSinSigno * p_secObj, unsigned long * p_ulEsperados, int iNum )
{
	int iRes = BOOL_VAL_CIERTO;

	if ( ( SSecIntLssEsValida ( p_secObj ) != 1 ) || ( SSecIntLssNumElementos ( p_secObj ) != iNum ) )
	{
		printf( "  Verificacion: se esperaban %d elementos: %d\n", iNum, SSecIntLssNumElementos ( p_secObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	int iPos = 0;
	while ( ( iPos < iNum ) && ( iRes == BOOL_VAL_CIERTO ) )
	{
		if ( SSecIntLssElemento ( p_secObj, iPos ) != p_ulEsperados [ iPos ] )
		{
			printf( "  Verificacion: en pos %d se esperaba %lu: %lu\n", iPos, p_ulEsperados [ iPos ], SSecIntLssElemento ( p_secObj, iPos ) );
			iRes = BOOL_VAL_FALSO;
		}
		iPos = iPos + 1;
	}
	return ( iRes );
}

/* Igual, para una lista. */
static int VerificarLista ( SListaEnterosLargosSinSigno * p_lisObj, unsigned long * p_ulEsperados, int iNum )
{
	int iRes = BOOL_VAL_CIERTO;

	if ( ( SLisIntLssEsValida ( p_lisObj ) != 1 ) || ( SLisIntLssNumElementos ( p_lisObj ) != iNum ) )
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

/* ListaIntLss da una lista con COPIAS: cambiarla no toca la secuencia. */
static int TestSSecIntLssListaIntLss01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecIntLssListaIntLss 01:\n" );

	unsigned long ulV [ 3 ] = { 5, 1, 5 };
	unsigned long ulEsp [ 4 ] = { 5, 1, 5, 8 };
	SSecuenciaEnterosLargosSinSigno * p_secObj = CrearSec ( ulV, 3 );
	SListaEnterosLargosSinSigno * p_lisRes = NULL;
	if ( ES_VALIDO ( p_secObj ) )
	{
		p_lisRes = SSecIntLssListaIntLss ( p_secObj );
		if ( VerificarLista ( p_lisRes, ulV, 3 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 1: la lista deberia ser { 5, 1, 5 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisIntLssInsertarAlFinal ( p_lisRes, 8 ) != 1 ) ||
			 ( VerificarLista ( p_lisRes, ulEsp, 4 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarSec ( p_secObj, ulV, 3 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 2: insertar en la lista no deberia tocar la secuencia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SSecIntLssListaIntLss ( NULL ) ) )
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
	SLisIntLssDestruir ( &p_lisRes );
	SSecIntLssDestruir ( &p_secObj );
	return ( iRes );
}

/* Pertenencia; Concatenar copia, Eliminar destruye todas las apariciones y
   Extraer mueve. */
static int TestSSecIntLssOperacionesListas01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecIntLssOperacionesListas 01:\n" );

	unsigned long ulVal [ 5 ] = { 1, 2, 3, 2, 4 };
	unsigned long ul29 [ 2 ] = { 2, 9 };
	unsigned long ul43 [ 2 ] = { 4, 3 };
	unsigned long ul9 [ 1 ] = { 9 };
	unsigned long ul1 [ 1 ] = { 1 };
	SSecuenciaEnterosLargosSinSigno * p_secObj = CrearSec ( ulVal, 5 );
	SSecuenciaEnterosLargosSinSigno * p_sec29 = CrearSec ( ul29, 2 );
	SSecuenciaEnterosLargosSinSigno * p_sec9 = CrearSec ( ul9, 1 );
	SListaEnterosLargosSinSigno * p_lis43 = CrearLista ( ul43, 2 );
	SListaEnterosLargosSinSigno * p_lis9 = CrearLista ( ul9, 1 );
	SListaEnterosLargosSinSigno * p_lis1 = CrearLista ( ul1, 1 );
	SSecuenciaEnterosLargosSinSigno * p_secRes = NULL;
	if ( ES_VALIDO ( p_secObj ) && ES_VALIDO ( p_sec29 ) && ES_VALIDO ( p_sec9 ) && ES_VALIDO ( p_lis43 ) &&
		 ES_VALIDO ( p_lis9 ) && ES_VALIDO ( p_lis1 ) )
	{
		if ( ( SSecIntLssExistenTodos ( p_secObj, p_sec29 ) != 0 ) || ( SSecIntLssExisteAlguno ( p_secObj, p_sec29 ) != 1 ) ||
			 ( SSecIntLssExistenTodosLista ( p_secObj, p_lis43 ) != 1 ) || ( SSecIntLssExisteAlgunoLista ( p_secObj, p_lis9 ) != 0 ) )
		{
			printf( "Error caso 1: se esperaba 0, 1, 1 y 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Concatenar copia: la lista y la otra secuencia no cambian. */
		unsigned long ulEsp2 [ 9 ] = { 1, 2, 3, 2, 4, 4, 3, 2, 9 };
		if ( ( SSecIntLssConcatenarLista ( p_secObj, p_lis43 ) != 1 ) ||
			 ( SSecIntLssConcatenar ( p_secObj, p_sec29 ) != 1 ) ||
			 ( VerificarSec ( p_secObj, ulEsp2, 9 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarLista ( p_lis43, ul43, 2 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarSec ( p_sec29, ul29, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 2: se esperaban copias al final y los valores sin tocar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Eliminar quita todas las apariciones. */
		unsigned long ulEsp3 [ 4 ] = { 1, 2, 2, 2 };
		if ( ( SSecIntLssEliminarLista ( p_secObj, p_lis43 ) != 1 ) ||
			 ( SSecIntLssEliminarSecuencia ( p_secObj, p_sec9 ) != 1 ) ||
			 ( VerificarSec ( p_secObj, ulEsp3, 4 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 3: deberia quedar { 1, 2, 2, 2 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Extraer mueve, todas las apariciones de cada valor. */
		unsigned long ulEsp4 [ 3 ] = { 2, 2, 2 };
		p_secRes = SSecIntLssExtraerLista ( p_secObj, p_lis1 );
		if ( ( VerificarSec ( p_secRes, ul1, 1 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarSec ( p_secObj, ulEsp4, 3 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 4: se esperaba sacar el 1 y dejar { 2, 2, 2 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SSecIntLssDestruir ( &p_secRes );
		p_secRes = SSecIntLssExtraerSecuencia ( p_secObj, p_sec29 );
		if ( ( VerificarSec ( p_secRes, ulEsp4, 3 ) != BOOL_VAL_CIERTO ) ||
			 ( SSecIntLssNumElementos ( p_secObj ) != 0 ) )
		{
			printf( "Error caso 5: se esperaba sacar los tres 2 y dejarla vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SSecIntLssDestruir ( &p_secRes );
		if ( ( SSecIntLssExistenTodos ( NULL, p_sec29 ) != 0 ) || ( SSecIntLssExisteAlgunoLista ( p_sec29, NULL ) != 0 ) ||
			 ( SSecIntLssConcatenarLista ( p_sec29, NULL ) != 0 ) || ( SSecIntLssConcatenar ( NULL, p_sec9 ) != 0 ) ||
			 ( SSecIntLssConcatenar ( p_sec29, p_sec29 ) != 0 ) ||
			 ( SSecIntLssEliminarSecuencia ( p_sec29, p_sec29 ) != 0 ) || ( SSecIntLssEliminarLista ( NULL, p_lis9 ) != 0 ) ||
			 ES_VALIDO ( SSecIntLssExtraerSecuencia ( p_sec29, p_sec29 ) ) ||
			 ES_VALIDO ( SSecIntLssExtraerLista ( p_sec29, NULL ) ) ||
			 ( VerificarSec ( p_sec29, ul29, 2 ) != BOOL_VAL_CIERTO ) )
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
	SSecIntLssDestruir ( &p_secObj );
	SSecIntLssDestruir ( &p_sec29 );
	SSecIntLssDestruir ( &p_sec9 );
	SLisIntLssDestruir ( &p_lis43 );
	SLisIntLssDestruir ( &p_lis9 );
	SLisIntLssDestruir ( &p_lis1 );
	ErrLimpiar ();
	return ( iRes );
}

/* Union es concatenacion; Interseccion y Diferencia, en el orden de V1. Las
   tres con copias, sin tocar las de entrada. */
static int TestSSecIntLssUnion01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecIntLssUnion 01:\n" );

	unsigned long ulV1 [ 4 ] = { 1, 2, 3, 4 };
	unsigned long ulV2 [ 3 ] = { 4, 2, 5 };
	unsigned long ulEspU [ 7 ] = { 1, 2, 3, 4, 4, 2, 5 };
	unsigned long ulEspI [ 2 ] = { 2, 4 };
	unsigned long ulEspD [ 2 ] = { 1, 3 };
	SSecuenciaEnterosLargosSinSigno * p_sec1 = CrearSec ( ulV1, 4 );
	SSecuenciaEnterosLargosSinSigno * p_sec2 = CrearSec ( ulV2, 3 );
	SListaEnterosLargosSinSigno * p_lis2 = CrearLista ( ulV2, 3 );
	SSecuenciaEnterosLargosSinSigno * p_secU = NULL;
	SSecuenciaEnterosLargosSinSigno * p_secI = NULL;
	SSecuenciaEnterosLargosSinSigno * p_secD = NULL;
	SSecuenciaEnterosLargosSinSigno * p_secUL = NULL;
	SSecuenciaEnterosLargosSinSigno * p_secIL = NULL;
	SSecuenciaEnterosLargosSinSigno * p_secDL = NULL;
	if ( ES_VALIDO ( p_sec1 ) && ES_VALIDO ( p_sec2 ) && ES_VALIDO ( p_lis2 ) )
	{
		p_secU = SSecIntLssUnion ( p_sec1, p_sec2 );
		p_secI = SSecIntLssInterseccion ( p_sec1, p_sec2 );
		p_secD = SSecIntLssDiferencia ( p_sec1, p_sec2 );
		if ( ( VerificarSec ( p_secU, ulEspU, 7 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarSec ( p_secI, ulEspI, 2 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarSec ( p_secD, ulEspD, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 1: con secuencias se esperaba { 1, 2, 3, 4, 4, 2, 5 }, { 2, 4 } y { 1, 3 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_secUL = SSecIntLssUnionLista ( p_sec1, p_lis2 );
		p_secIL = SSecIntLssInterseccionLista ( p_sec1, p_lis2 );
		p_secDL = SSecIntLssDiferenciaLista ( p_sec1, p_lis2 );
		if ( ( VerificarSec ( p_secUL, ulEspU, 7 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarSec ( p_secIL, ulEspI, 2 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarSec ( p_secDL, ulEspD, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 2: con listas se esperaba { 1, 2, 3, 4, 4, 2, 5 }, { 2, 4 } y { 1, 3 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( VerificarSec ( p_sec1, ulV1, 4 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarSec ( p_sec2, ulV2, 3 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarLista ( p_lis2, ulV2, 3 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 3: las de entrada no deberian cambiar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SSecIntLssUnion ( p_sec1, NULL ) ) || ES_VALIDO ( SSecIntLssInterseccion ( NULL, p_sec2 ) ) ||
			 ES_VALIDO ( SSecIntLssDiferencia ( p_sec1, NULL ) ) || ES_VALIDO ( SSecIntLssUnionLista ( NULL, p_lis2 ) ) ||
			 ES_VALIDO ( SSecIntLssInterseccionLista ( p_sec1, NULL ) ) || ES_VALIDO ( SSecIntLssDiferenciaLista ( NULL, p_lis2 ) ) )
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
	SSecIntLssDestruir ( &p_secU );
	SSecIntLssDestruir ( &p_secI );
	SSecIntLssDestruir ( &p_secD );
	SSecIntLssDestruir ( &p_secUL );
	SSecIntLssDestruir ( &p_secIL );
	SSecIntLssDestruir ( &p_secDL );
	SSecIntLssDestruir ( &p_sec1 );
	SSecIntLssDestruir ( &p_sec2 );
	SLisIntLssDestruir ( &p_lis2 );
	ErrLimpiar ();
	return ( iRes );
}

int TestSSecuenciaEnterosLargosSinSigno ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SSecuenciaEnterosLargosSinSigno]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSSecIntLssOperaciones01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecIntLssInvalidos01 () == BOOL_VAL_CIERTO )  &&
			( TestSSecIntLssConjunto01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecIntLssConjunto02 () == BOOL_VAL_CIERTO ) &&
			( TestSSecIntLssBuscarSiguiente01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecIntLssListaIntLss01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecIntLssOperacionesListas01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecIntLssUnion01 () == BOOL_VAL_CIERTO ) )
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
