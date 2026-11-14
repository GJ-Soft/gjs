#include "Base.h"

#include "SSecuenciaLiterales.h"



static int ElementoEs ( SSecuenciaLiterales * p_secObj, int iElem, const char * p_cEsperado )
{
	return ( CadComparar ( SSecLitElemento ( p_secObj, iElem ), (char *) p_cEsperado ) == COMP_IGUAL );
}



static int TestSSecLitOperaciones01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecLitOperaciones 01:\n" );

	SSecuenciaLiterales * p_secObj = SSecLitCrear ();
	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ( SSecLitEsValida ( p_secObj ) != 1 ) || ( SSecLitEstaVacia ( p_secObj ) != 1 ) )
		{
			printf( "Error caso 1: la secuencia recien creada deberia ser valida y estar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Insertar duplica la cadena ( la secuencia la posee ) y conserva el orden de insercion. */
		if ( ( SSecLitInsertar ( p_secObj, "uno" ) != 1 ) ||
			 ( SSecLitInsertar ( p_secObj, "dos" ) != 1 ) ||
			 ( SSecLitInsertar ( p_secObj, "tres" ) != 1 ) )
		{
			printf( "Error caso 2: se esperaba poder insertar las tres cadenas\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecLitNumElementos ( p_secObj ) != 3 ) || ( ! ElementoEs ( p_secObj, 1, "dos" ) ) )
		{
			printf( "Error caso 3: deberia haber 3 elementos y el del indice 1 ser \"dos\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecLitExiste ( p_secObj, "tres" ) != 1 ) || ( SSecLitExiste ( p_secObj, "cuatro" ) != 0 ) )
		{
			printf( "Error caso 4: existe deberia encontrar \"tres\" y no \"cuatro\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SSecLitBuscar ( p_secObj, "uno" ) != 0 )
		{
			printf( "Error caso 5: buscar \"uno\" deberia devolver el indice 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Eliminar el primero: se desplazan los demas. */
		if ( ( SSecLitEliminar ( p_secObj, 0 ) != 1 ) ||
			 ( SSecLitNumElementos ( p_secObj ) != 2 ) || ( ! ElementoEs ( p_secObj, 0, "dos" ) ) )
		{
			printf( "Error caso 6: tras eliminar el primero la cabeza deberia ser \"dos\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SSecLitVaciar ( p_secObj );
		if ( SSecLitEstaVacia ( p_secObj ) != 1 )
		{
			printf( "Error caso 7: tras vaciar la secuencia deberia estar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la secuencia\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecLitDestruir ( &p_secObj );

	if ( ES_VALIDO ( p_secObj ) )
	{
		printf( "Error caso 8: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSSecLitInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecLitInvalidos 01:\n" );

	if ( SSecLitEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: una secuencia nula no deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SSecLitNumElementos ( NULL ) != 0 )
	{
		printf( "Error caso 2: una secuencia nula deberia tener 0 elementos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecuenciaLiterales * p_secNula = NULL;
	SSecLitDestruir ( &p_secNula );
	return ( iRes );
}



/* CrearDesdeLista copia; Secuencia y Lista dan lo de dentro. Repetidos por
   contenido, ExtraerUnicos y TieneRepetidos. */
static int TestSSecLitBuscarSiguiente01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecLitBuscarSiguiente 01:\n" );

	const char * p_cVal [ 6 ] = { "b", "a", "b", "c", "b", "d" };
	char cB [ 2 ] = { 'b', '\0' };
	SListaLiterales * p_lisVal = SLisLitCrear ();
	SSecuenciaLiterales * p_secObj = NULL;
	SSecuenciaLiterales * p_secUni = NULL;
	int iPos = 0;
	while ( ES_VALIDO ( p_lisVal ) && ( iPos < 6 ) )
	{
		SLisLitInsertarDupAlFinal ( p_lisVal, p_cVal [ iPos ] );
		iPos = iPos + 1;
	}
	if ( ES_VALIDO ( p_lisVal ) )
	{
		p_secObj = SSecLitCrearDesdeLista ( p_lisVal );
		if ( ( SSecLitNumElementos ( p_secObj ) != 6 ) || ( ! ElementoEs ( p_secObj, 3, "c" ) ) ||
			 ( SSecLitElemento ( p_secObj, 0 ) == SLisLitElemento ( p_lisVal, 0 ) ) )
		{
			printf( "Error caso 1: la secuencia deberia tener sus propias copias de las 6\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_NULO ( SSecLitSecuencia ( p_secObj ) ) ||
			 ( SSecLitLista ( p_secObj ) != SSecpLista ( SSecLitSecuencia ( p_secObj ) ) ) ||
			 ( SLispNumElementos ( SSecLitLista ( p_secObj ) ) != 6 ) )
		{
			printf( "Error caso 2: Secuencia y Lista deberian dar la secuencia interna y su lista\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecLitBuscarPrimero ( p_secObj, cB ) != 0 ) ||
			 ( SSecLitBuscarSiguiente ( p_secObj, cB, 0 ) != 2 ) ||
			 ( SSecLitBuscarSiguiente ( p_secObj, cB, 2 ) != 4 ) ||
			 ( SSecLitBuscarSiguiente ( p_secObj, cB, 4 ) != -1 ) ||
			 ( SSecLitBuscarSiguiente ( p_secObj, cB, -2 ) != -1 ) ||
			 ( SSecLitBuscar ( p_secObj, "d" ) != 5 ) ||
			 ( SSecLitRepeticiones ( p_secObj, cB ) != 3 ) ||
			 ( SSecLitRepeticiones ( p_secObj, "x" ) != 0 ) )
		{
			printf( "Error caso 3: la b deberia estar en 0, 2 y 4, la d en la 5 y la x en ninguna\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_secUni = SSecLitExtraerUnicos ( p_secObj );
		if ( ( SSecLitNumElementos ( p_secUni ) != 4 ) || ( ! ElementoEs ( p_secUni, 0, "b" ) ) ||
			 ( ! ElementoEs ( p_secUni, 1, "a" ) ) || ( ! ElementoEs ( p_secUni, 2, "c" ) ) ||
			 ( ! ElementoEs ( p_secUni, 3, "d" ) ) ||
			 ( SSecLitElemento ( p_secUni, 0 ) == SSecLitElemento ( p_secObj, 0 ) ) )
		{
			printf( "Error caso 4: se esperaban copias de { b, a, c, d }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecLitTieneRepetidos ( p_secObj ) != 1 ) || ( SSecLitTieneRepetidos ( p_secUni ) != 0 ) ||
			 ( SSecLitTieneRepetidos ( NULL ) != 0 ) || ES_VALIDO ( SSecLitExtraerUnicos ( NULL ) ) )
		{
			printf( "Error caso 5: solo la de partida deberia tener repetidos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SSecLitCrearDesdeLista ( NULL ) ) || ES_VALIDO ( SSecLitSecuencia ( NULL ) ) ||
			 ES_VALIDO ( SSecLitLista ( NULL ) ) || ( SSecLitRepeticiones ( NULL, cB ) != 0 ) ||
			 ( SSecLitBuscarSiguiente ( NULL, cB, -1 ) != -1 ) || ( SSecLitInsertar ( NULL, "a" ) != 0 ) ||
			 ( SSecLitInsertar ( p_secObj, NULL ) != 0 ) )
		{
			printf( "Error caso 6: con un nulo se esperaba nulo, 0 al contar o insertar y -1 al buscar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisLitDestruir ( &p_lisVal );
	SSecLitDestruir ( &p_secObj );
	SSecLitDestruir ( &p_secUni );
	return ( iRes );
}

static SListaLiterales * CrearListaLiterales ( const char ** p_p_cValores, int iNum )
{
	SListaLiterales * p_lisObj = SLisLitCrear ();
	int iPos = 0;
	while ( ES_VALIDO ( p_lisObj ) && ( iPos < iNum ) )
	{
		SLisLitInsertarDupAlFinal ( p_lisObj, p_p_cValores [ iPos ] );
		iPos = iPos + 1;
	}
	return ( p_lisObj );
}

static SSecuenciaLiterales * CrearSecLiterales ( const char ** p_p_cValores, int iNum )
{
	SSecuenciaLiterales * p_secObj = SSecLitCrear ();
	int iPos = 0;
	while ( ES_VALIDO ( p_secObj ) && ( iPos < iNum ) )
	{
		SSecLitInsertar ( p_secObj, p_p_cValores [ iPos ] );
		iPos = iPos + 1;
	}
	return ( p_secObj );
}

static int VerificarSec ( SSecuenciaLiterales * p_secObj, const char ** p_p_cEsperados, int iNum )
{
	int iRes = BOOL_VAL_CIERTO;

	if ( ( SSecLitEsValida ( p_secObj ) != 1 ) || ( SSecLitNumElementos ( p_secObj ) != iNum ) )
	{
		printf( "  Verificacion: se esperaban %d elementos: %d\n", iNum, SSecLitNumElementos ( p_secObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	int iPos = 0;
	while ( ( iPos < iNum ) && ( iRes == BOOL_VAL_CIERTO ) )
	{
		if ( ES_NULO ( SSecLitElemento ( p_secObj, iPos ) ) || ( ! ElementoEs ( p_secObj, iPos, p_p_cEsperados [ iPos ] ) ) )
		{
			printf( "  Verificacion: en pos %d se esperaba \"%s\"\n", iPos, p_p_cEsperados [ iPos ] );
			iRes = BOOL_VAL_FALSO;
		}
		iPos = iPos + 1;
	}
	return ( iRes );
}

/* Comparan el contenido; Concatenar copia, Eliminar destruye todas las
   apariciones y Extraer mueve. */
static int TestSSecLitOperacionesListas01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecLitOperacionesListas 01:\n" );

	const char * p_cVal [ 5 ] = { "a", "b", "c", "b", "d" };
	const char * p_cBX [ 2 ] = { "b", "x" };
	const char * p_cDC [ 2 ] = { "d", "c" };
	const char * p_cX [ 1 ] = { "x" };
	const char * p_cA [ 1 ] = { "a" };
	SSecuenciaLiterales * p_secObj = CrearSecLiterales ( p_cVal, 5 );
	SSecuenciaLiterales * p_secBX = CrearSecLiterales ( p_cBX, 2 );
	SSecuenciaLiterales * p_secX = CrearSecLiterales ( p_cX, 1 );
	SListaLiterales * p_lisDC = CrearListaLiterales ( p_cDC, 2 );
	SListaLiterales * p_lisX = CrearListaLiterales ( p_cX, 1 );
	SListaLiterales * p_lisA = CrearListaLiterales ( p_cA, 1 );
	SSecuenciaLiterales * p_secRes = NULL;
	if ( ES_VALIDO ( p_secObj ) && ES_VALIDO ( p_secBX ) && ES_VALIDO ( p_secX ) && ES_VALIDO ( p_lisDC ) &&
		 ES_VALIDO ( p_lisX ) && ES_VALIDO ( p_lisA ) )
	{
		if ( ( SSecLitExistenTodos ( p_secObj, p_secBX ) != 0 ) || ( SSecLitExisteAlguno ( p_secObj, p_secBX ) != 1 ) ||
			 ( SSecLitExistenTodosLista ( p_secObj, p_lisDC ) != 1 ) || ( SSecLitExisteAlgunoLista ( p_secObj, p_lisX ) != 0 ) )
		{
			printf( "Error caso 1: se esperaba 0, 1, 1 y 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Concatenar copia: la lista y la otra secuencia no cambian. */
		const char * p_cEsp2 [ 9 ] = { "a", "b", "c", "b", "d", "d", "c", "b", "x" };
		if ( ( SSecLitConcatenarLista ( p_secObj, p_lisDC ) != 1 ) ||
			 ( SSecLitConcatenar ( p_secObj, p_secBX ) != 1 ) ||
			 ( VerificarSec ( p_secObj, p_cEsp2, 9 ) != BOOL_VAL_CIERTO ) ||
			 ( SSecLitElemento ( p_secObj, 5 ) == SLisLitElemento ( p_lisDC, 0 ) ) ||
			 ( SLisLitNumElementos ( p_lisDC ) != 2 ) || ( SSecLitNumElementos ( p_secBX ) != 2 ) )
		{
			printf( "Error caso 2: se esperaban copias al final y los valores sin tocar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Eliminar quita todas las apariciones. */
		const char * p_cEsp3 [ 4 ] = { "a", "b", "b", "b" };
		if ( ( SSecLitEliminarLista ( p_secObj, p_lisDC ) != 1 ) ||
			 ( SSecLitEliminarSecuencia ( p_secObj, p_secX ) != 1 ) ||
			 ( VerificarSec ( p_secObj, p_cEsp3, 4 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 3: deberia quedar { a, b, b, b }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Extraer mueve las cadenas, todas las de cada valor. */
		char * p_cMovida = SSecLitElemento ( p_secObj, 0 );
		p_secRes = SSecLitExtraerLista ( p_secObj, p_lisA );
		const char * p_cEsp4 [ 3 ] = { "b", "b", "b" };
		if ( ( VerificarSec ( p_secRes, p_cA, 1 ) != BOOL_VAL_CIERTO ) ||
			 ( SSecLitElemento ( p_secRes, 0 ) != p_cMovida ) ||
			 ( VerificarSec ( p_secObj, p_cEsp4, 3 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 4: se esperaba mover la a y dejar { b, b, b }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SSecLitDestruir ( &p_secRes );
		p_secRes = SSecLitExtraerSecuencia ( p_secObj, p_secBX );
		if ( ( VerificarSec ( p_secRes, p_cEsp4, 3 ) != BOOL_VAL_CIERTO ) ||
			 ( SSecLitEstaVacia ( p_secObj ) != 1 ) )
		{
			printf( "Error caso 5: se esperaba mover las tres b y dejarla vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SSecLitDestruir ( &p_secRes );
		if ( ( SSecLitExistenTodos ( NULL, p_secBX ) != 0 ) || ( SSecLitExisteAlgunoLista ( p_secBX, NULL ) != 0 ) ||
			 ( SSecLitConcatenarLista ( p_secBX, NULL ) != 0 ) || ( SSecLitConcatenar ( NULL, p_secX ) != 0 ) ||
			 ( SSecLitConcatenar ( p_secBX, p_secBX ) != 0 ) ||
			 ( SSecLitEliminarSecuencia ( p_secBX, p_secBX ) != 0 ) || ( SSecLitEliminarLista ( NULL, p_lisX ) != 0 ) ||
			 ES_VALIDO ( SSecLitExtraerSecuencia ( p_secBX, p_secBX ) ) ||
			 ES_VALIDO ( SSecLitExtraerLista ( p_secBX, NULL ) ) ||
			 ( VerificarSec ( p_secBX, p_cBX, 2 ) != BOOL_VAL_CIERTO ) )
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
	SSecLitDestruir ( &p_secObj );
	SSecLitDestruir ( &p_secBX );
	SSecLitDestruir ( &p_secX );
	SLisLitDestruir ( &p_lisDC );
	SLisLitDestruir ( &p_lisX );
	SLisLitDestruir ( &p_lisA );
	return ( iRes );
}

/* ListaLit da una lista con COPIAS de las cadenas: cambiarla no toca la
   secuencia. */
static int TestSSecLitListaLit01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecLitListaLit 01:\n" );

	const char * p_cV [ 3 ] = { "e", "a", "e" };
	SSecuenciaLiterales * p_secObj = CrearSecLiterales ( p_cV, 3 );
	SListaLiterales * p_lisRes = NULL;
	if ( ES_VALIDO ( p_secObj ) )
	{
		p_lisRes = SSecLitListaLit ( p_secObj );
		if ( ES_NULO ( p_lisRes ) || ( SLisLitNumElementos ( p_lisRes ) != 3 ) ||
			 ( CadComparar ( SLisLitElemento ( p_lisRes, 0 ), "e" ) != COMP_IGUAL ) ||
			 ( CadComparar ( SLisLitElemento ( p_lisRes, 1 ), "a" ) != COMP_IGUAL ) ||
			 ( CadComparar ( SLisLitElemento ( p_lisRes, 2 ), "e" ) != COMP_IGUAL ) ||
			 ( SLisLitElemento ( p_lisRes, 0 ) == SSecLitElemento ( p_secObj, 0 ) ) )
		{
			printf( "Error caso 1: la lista deberia ser una copia de { e, a, e }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisLitInsertarDupAlFinal ( p_lisRes, "h" ) != 1 ) || ( SLisLitNumElementos ( p_lisRes ) != 4 ) ||
			 ( VerificarSec ( p_secObj, p_cV, 3 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 2: insertar en la lista no deberia tocar la secuencia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisLitDestruir ( &p_lisRes );
		/* Destruir la copia no deja la secuencia sin sus cadenas. */
		if ( VerificarSec ( p_secObj, p_cV, 3 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 3: la secuencia deberia seguir con { e, a, e }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SSecLitListaLit ( NULL ) ) )
		{
			printf( "Error caso 4: con una secuencia nula se esperaba nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la secuencia\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisLitDestruir ( &p_lisRes );
	SSecLitDestruir ( &p_secObj );
	return ( iRes );
}

/* Union es concatenacion; Interseccion y Diferencia, en el orden de V1,
   comparando el contenido. Las tres con copias, sin tocar las de entrada. */
static int TestSSecLitUnion01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecLitUnion 01:\n" );

	const char * p_cV1 [ 4 ] = { "a", "b", "c", "d" };
	const char * p_cV2 [ 3 ] = { "d", "b", "e" };
	const char * p_cEspU [ 7 ] = { "a", "b", "c", "d", "d", "b", "e" };
	const char * p_cEspI [ 2 ] = { "b", "d" };
	const char * p_cEspD [ 2 ] = { "a", "c" };
	SSecuenciaLiterales * p_sec1 = CrearSecLiterales ( p_cV1, 4 );
	SSecuenciaLiterales * p_sec2 = CrearSecLiterales ( p_cV2, 3 );
	SListaLiterales * p_lis2 = CrearListaLiterales ( p_cV2, 3 );
	SSecuenciaLiterales * p_secU = NULL;
	SSecuenciaLiterales * p_secI = NULL;
	SSecuenciaLiterales * p_secD = NULL;
	SSecuenciaLiterales * p_secUL = NULL;
	SSecuenciaLiterales * p_secIL = NULL;
	SSecuenciaLiterales * p_secDL = NULL;
	if ( ES_VALIDO ( p_sec1 ) && ES_VALIDO ( p_sec2 ) && ES_VALIDO ( p_lis2 ) )
	{
		p_secU = SSecLitUnion ( p_sec1, p_sec2 );
		p_secI = SSecLitInterseccion ( p_sec1, p_sec2 );
		p_secD = SSecLitDiferencia ( p_sec1, p_sec2 );
		if ( ( VerificarSec ( p_secU, p_cEspU, 7 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarSec ( p_secI, p_cEspI, 2 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarSec ( p_secD, p_cEspD, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 1: con secuencias se esperaba { a, b, c, d, d, b, e }, { b, d } y { a, c }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_secUL = SSecLitUnionLista ( p_sec1, p_lis2 );
		p_secIL = SSecLitInterseccionLista ( p_sec1, p_lis2 );
		p_secDL = SSecLitDiferenciaLista ( p_sec1, p_lis2 );
		if ( ( VerificarSec ( p_secUL, p_cEspU, 7 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarSec ( p_secIL, p_cEspI, 2 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarSec ( p_secDL, p_cEspD, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 2: con listas se esperaba { a, b, c, d, d, b, e }, { b, d } y { a, c }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Copias: ninguna cadena del resultado es la de la entrada. */
		if ( ES_NULO ( p_secU ) || ES_NULO ( p_secI ) ||
			 ( SSecLitElemento ( p_secU, 0 ) == SSecLitElemento ( p_sec1, 0 ) ) ||
			 ( SSecLitElemento ( p_secU, 6 ) == SSecLitElemento ( p_sec2, 2 ) ) ||
			 ( SSecLitElemento ( p_secI, 0 ) == SSecLitElemento ( p_sec1, 1 ) ) )
		{
			printf( "Error caso 3: el resultado deberia tener copias de las cadenas\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( VerificarSec ( p_sec1, p_cV1, 4 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarSec ( p_sec2, p_cV2, 3 ) != BOOL_VAL_CIERTO ) ||
			 ( SLisLitNumElementos ( p_lis2 ) != 3 ) )
		{
			printf( "Error caso 4: las de entrada no deberian cambiar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SSecLitUnion ( p_sec1, NULL ) ) || ES_VALIDO ( SSecLitInterseccion ( NULL, p_sec2 ) ) ||
			 ES_VALIDO ( SSecLitDiferencia ( p_sec1, NULL ) ) || ES_VALIDO ( SSecLitUnionLista ( NULL, p_lis2 ) ) ||
			 ES_VALIDO ( SSecLitInterseccionLista ( p_sec1, NULL ) ) || ES_VALIDO ( SSecLitDiferenciaLista ( NULL, p_lis2 ) ) )
		{
			printf( "Error caso 5: con nulos se esperaba nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las secuencias o la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecLitDestruir ( &p_secU );
	SSecLitDestruir ( &p_secI );
	SSecLitDestruir ( &p_secD );
	SSecLitDestruir ( &p_secUL );
	SSecLitDestruir ( &p_secIL );
	SSecLitDestruir ( &p_secDL );
	SSecLitDestruir ( &p_sec1 );
	SSecLitDestruir ( &p_sec2 );
	SLisLitDestruir ( &p_lis2 );
	ErrLimpiar ();
	return ( iRes );
}

int TestSSecuenciaLiterales ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SSecuenciaLiterales]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSSecLitOperaciones01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecLitInvalidos01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecLitBuscarSiguiente01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecLitOperacionesListas01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecLitListaLit01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecLitUnion01 () == BOOL_VAL_CIERTO ) )
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
