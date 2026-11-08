#include "Base.h"

#include "SListaLiterales.h"



static int ElementoEs ( SListaLiterales * p_lisObj, int iElem, const char * p_cEsperado )
{
	return ( CadComparar ( SLisLitElemento ( p_lisObj, iElem ), (char *) p_cEsperado ) == COMP_IGUAL );
}

static int ActualEs ( SListaLiterales * p_lisObj, const char * p_cEsperado )
{
	return ( CadComparar ( SLisLitActual ( p_lisObj ), (char *) p_cEsperado ) == COMP_IGUAL );
}

static int VerificarContenido ( SListaLiterales * p_lisObj, const char ** p_p_cEsperados, int iNum )
{
	int iRes = BOOL_VAL_CIERTO;

	if ( SLisLitNumElementos ( p_lisObj ) != iNum )
	{
		printf( "  Verificacion: se esperaban %d elementos: %d\n", iNum, SLisLitNumElementos ( p_lisObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	int iPos = 0;
	while ( ( iPos < iNum ) && ( iRes == BOOL_VAL_CIERTO ) )
	{
		if ( ! ElementoEs ( p_lisObj, iPos, p_p_cEsperados [ iPos ] ) )
		{
			printf( "  Verificacion: en pos %d se esperaba \"%s\"\n", iPos, p_p_cEsperados [ iPos ] );
			iRes = BOOL_VAL_FALSO;
		}
		iPos = iPos + 1;
	}
	return ( iRes );
}

/* Con copias propias de cada cadena: asi ningun valor comparte puntero con los
   literales del test ni con otra lista, y las comparaciones son por contenido. */
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



static int TestSLisLitOperaciones01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisLitOperaciones 01:\n" );

	SListaLiterales * p_lisObj = SLisLitCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( ( SLisLitEsValida ( p_lisObj ) != 1 ) || ( SLisLitEstaVacia ( p_lisObj ) != 1 ) )
		{
			printf( "Error caso 1: la lista recien creada deberia ser valida y estar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Las variantes Dup duplican; la lista posee las cadenas. */
		if ( ( SLisLitInsertarDupAlFinal ( p_lisObj, "a" ) != 1 ) ||
			 ( SLisLitInsertarDupAlFinal ( p_lisObj, "b" ) != 1 ) ||
			 ( SLisLitInsertarDupAlFinal ( p_lisObj, "c" ) != 1 ) )
		{
			printf( "Error caso 2: se esperaba poder insertar las tres cadenas\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisLitNumElementos ( p_lisObj ) != 3 ) || ( ! ElementoEs ( p_lisObj, 1, "b" ) ) )
		{
			printf( "Error caso 3: deberia haber 3 elementos y el del indice 1 ser \"b\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Insertar al inicio. */
		if ( ( SLisLitInsertarDupAlInicio ( p_lisObj, "z" ) != 1 ) || ( ! ElementoEs ( p_lisObj, 0, "z" ) ) )
		{
			printf( "Error caso 4: insertar al inicio deberia dejar \"z\" en la cabeza\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisLitExiste ( p_lisObj, "b" ) != 1 ) || ( SLisLitExiste ( p_lisObj, "x" ) != 0 ) )
		{
			printf( "Error caso 5: existe deberia encontrar \"b\" y no \"x\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisLitBuscar ( p_lisObj, "c" ) != 3 )
		{
			printf( "Error caso 6: buscar \"c\" deberia devolver el indice 3\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Sustituir el elemento 0 ( libera la cadena anterior ). */
		if ( ( SLisLitEstablecerElemDup ( p_lisObj, 0, "Z" ) != 1 ) || ( ! ElementoEs ( p_lisObj, 0, "Z" ) ) )
		{
			printf( "Error caso 7: el elemento 0 deberia poder sustituirse por \"Z\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Eliminar el primero. */
		if ( ( SLisLitEliminarElem ( p_lisObj, 0 ) != 1 ) ||
			 ( SLisLitNumElementos ( p_lisObj ) != 3 ) || ( ! ElementoEs ( p_lisObj, 0, "a" ) ) )
		{
			printf( "Error caso 8: tras eliminar el primero la cabeza deberia ser \"a\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisLitVaciar ( p_lisObj );
		if ( SLisLitEstaVacia ( p_lisObj ) != 1 )
		{
			printf( "Error caso 9: tras vaciar la lista deberia estar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisLitDestruir ( &p_lisObj );

	if ( ES_VALIDO ( p_lisObj ) )
	{
		printf( "Error caso 10: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSLisLitCursor01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisLitCursor 01:\n" );

	SListaLiterales * p_lisObj = SLisLitCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		SLisLitInsertarDupAlFinal ( p_lisObj, "uno" );
		SLisLitInsertarDupAlFinal ( p_lisObj, "dos" );
		SLisLitInsertarDupAlFinal ( p_lisObj, "tres" );

		SLisLitInicio ( p_lisObj );
		if ( ( ! ActualEs ( p_lisObj, "uno" ) ) || ( SLisLitEstaEnInicio ( p_lisObj ) != 1 ) )
		{
			printf( "Error caso 1: el inicio deberia ser \"uno\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisLitSiguiente ( p_lisObj );
		if ( ! ActualEs ( p_lisObj, "dos" ) )
		{
			printf( "Error caso 2: el siguiente del inicio deberia ser \"dos\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisLitFinal ( p_lisObj );
		if ( ( ! ActualEs ( p_lisObj, "tres" ) ) || ( SLisLitEstaEnFinal ( p_lisObj ) != 1 ) )
		{
			printf( "Error caso 3: el final deberia ser \"tres\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisLitDestruir ( &p_lisObj );
	return ( iRes );
}

static int TestSLisLitInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisLitInvalidos 01:\n" );

	if ( SLisLitEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: una lista nula no deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLisLitNumElementos ( NULL ) != 0 )
	{
		printf( "Error caso 2: una lista nula deberia tener 0 elementos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SListaLiterales * p_lisNula = NULL;
	SLisLitDestruir ( &p_lisNula );
	return ( iRes );
}

/* Buscar compara el CONTENIDO: la cadena buscada es otro bloque con el mismo
   texto. Casos en la primera y en la ultima posicion. */
static int TestSLisLitBuscarExiste01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisLitBuscarExiste 01:\n" );

	const char * p_cVal [ 3 ] = { "alfa", "beta", "gamma" };
	SListaLiterales * p_lisObj = CrearListaLiterales ( p_cVal, 3 );
	char cBeta [ 5 ] = { 'b', 'e', 't', 'a', 0 };
	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( ( SLisLitBuscar ( p_lisObj, "alfa" ) != 0 ) || ( SLisLitBuscar ( p_lisObj, "gamma" ) != 2 ) )
		{
			printf( "Error caso 1: \"alfa\" esta en la 0 y \"gamma\" en la 2\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisLitBuscar ( p_lisObj, cBeta ) != 1 ) || ( SLisLitExiste ( p_lisObj, cBeta ) != 1 ) )
		{
			printf( "Error caso 2: \"beta\" en otro bloque deberia encontrarse en la 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisLitBuscar ( p_lisObj, "delta" ) != -1 ) || ( SLisLitExiste ( p_lisObj, "delta" ) != 0 ) ||
			 ( SLisLitBuscar ( p_lisObj, "alf" ) != -1 ) )
		{
			printf( "Error caso 3: ni \"delta\" ni el prefijo \"alf\" estan\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisLitBuscar ( p_lisObj, NULL ) != -1 ) || ( SLisLitBuscar ( NULL, "alfa" ) != -1 ) ||
			 ( SLisLitExiste ( p_lisObj, NULL ) != 0 ) || ( SLisLitExiste ( NULL, "alfa" ) != 0 ) )
		{
			printf( "Error caso 4: con parametros nulos se esperaba -1 y 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisLitDestruir ( &p_lisObj );
	return ( iRes );
}

/* Un valor en la posicion 0 y otro que es el ULTIMO de los valores. */
static int TestSLisLitExisten01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisLitExisten 01:\n" );

	const char * p_cVal [ 3 ] = { "a", "b", "c" };
	const char * p_cV1 [ 2 ] = { "a", "c" };
	const char * p_cV2 [ 2 ] = { "a", "x" };
	const char * p_cV3 [ 2 ] = { "x", "c" };
	const char * p_cV4 [ 2 ] = { "x", "y" };
	SListaLiterales * p_lisObj = CrearListaLiterales ( p_cVal, 3 );
	SListaLiterales * p_lis1 = CrearListaLiterales ( p_cV1, 2 );
	SListaLiterales * p_lis2 = CrearListaLiterales ( p_cV2, 2 );
	SListaLiterales * p_lis3 = CrearListaLiterales ( p_cV3, 2 );
	SListaLiterales * p_lis4 = CrearListaLiterales ( p_cV4, 2 );
	SListaLiterales * p_lisVacia = SLisLitCrear ();
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lis1 ) && ES_VALIDO ( p_lis2 ) &&
		 ES_VALIDO ( p_lis3 ) && ES_VALIDO ( p_lis4 ) && ES_VALIDO ( p_lisVacia ) )
	{
		if ( SLisLitExistenTodos ( p_lisObj, p_lis1 ) != 1 )
		{
			printf( "Error caso 1: { a, c } estan todos en { a, b, c }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisLitExistenTodos ( p_lisObj, p_lis2 ) != 0 ) || ( SLisLitExisteAlguno ( p_lisObj, p_lis2 ) != 1 ) )
		{
			printf( "Error caso 2: de { a, x } falta la x pero esta la a, en la posicion 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisLitExisteAlguno ( p_lisObj, p_lis3 ) != 1 )
		{
			printf( "Error caso 3: de { x, c } esta la c, la ultima de los valores\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisLitExisteAlguno ( p_lisObj, p_lis4 ) != 0 ) || ( SLisLitExistenTodos ( p_lisObj, p_lis4 ) != 0 ) )
		{
			printf( "Error caso 4: de { x, y } no esta ninguna\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisLitExistenTodos ( p_lisObj, p_lisVacia ) != 1 ) || ( SLisLitExisteAlguno ( p_lisObj, p_lisVacia ) != 0 ) )
		{
			printf( "Error caso 5: con valores vacios, Todos da 1 y Alguno 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisLitExistenTodos ( NULL, p_lis1 ) != 0 ) || ( SLisLitExisteAlguno ( p_lisObj, NULL ) != 0 ) )
		{
			printf( "Error caso 6: con listas nulas se esperaba 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisLitDestruir ( &p_lisObj );
	SLisLitDestruir ( &p_lis1 );
	SLisLitDestruir ( &p_lis2 );
	SLisLitDestruir ( &p_lis3 );
	SLisLitDestruir ( &p_lis4 );
	SLisLitDestruir ( &p_lisVacia );
	return ( iRes );
}

static int TestSLisLitInsertarLista01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisLitInsertarLista 01:\n" );

	const char * p_cDest [ 2 ] = { "uno", "dos" };
	const char * p_cVal [ 2 ] = { "siete", "ocho" };
	SListaLiterales * p_lisObj = CrearListaLiterales ( p_cDest, 2 );
	SListaLiterales * p_lisVal = CrearListaLiterales ( p_cVal, 2 );
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisVal ) )
	{
		/* Mover: la cadena que llega es la MISMA, no una copia. */
		char * p_cSiete = SLisLitElemento ( p_lisVal, 0 );
		SLisLitMoverA ( p_lisObj, 0 );
		if ( SLisLitInsertarLista ( p_lisObj, p_lisVal ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al insertar la lista\n" );
			iRes = BOOL_VAL_FALSO;
		}
		const char * p_cEsp1 [ 4 ] = { "uno", "siete", "ocho", "dos" };
		if ( ( VerificarContenido ( p_lisObj, p_cEsp1, 4 ) != BOOL_VAL_CIERTO ) ||
			 ( SLisLitElemento ( p_lisObj, 1 ) != p_cSiete ) )
		{
			printf( "Error caso 2: se esperaba { uno, siete, ocho, dos } con las cadenas movidas\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisLitEstaVacia ( p_lisVal ) != 1 ) || ( SLisLitEsValida ( p_lisVal ) != 1 ) )
		{
			printf( "Error caso 3: la lista de valores deberia quedar vacia y valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisLitInsertarDupAlFinal ( p_lisVal, "cinco" );
		if ( SLisLitConcatenarLista ( p_lisObj, p_lisVal ) != 1 )
		{
			printf( "Error caso 4: se esperaba resultado 1 al concatenar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		const char * p_cEsp2 [ 5 ] = { "uno", "siete", "ocho", "dos", "cinco" };
		if ( ( VerificarContenido ( p_lisObj, p_cEsp2, 5 ) != BOOL_VAL_CIERTO ) || ( SLisLitEstaVacia ( p_lisVal ) != 1 ) )
		{
			printf( "Error caso 5: se esperaba { uno, siete, ocho, dos, cinco } y los valores vacios\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisLitInsertarLista ( p_lisObj, NULL ) != 0 ) || ( SLisLitConcatenarLista ( p_lisObj, p_lisObj ) != 0 ) )
		{
			printf( "Error caso 6: con una lista nula o la misma lista se esperaba 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisLitDestruir ( &p_lisObj );
	SLisLitDestruir ( &p_lisVal );
	return ( iRes );
}

static int TestSLisLitListaDup01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisLitListaDup 01:\n" );

	const char * p_cDest [ 2 ] = { "uno", "dos" };
	const char * p_cVal [ 2 ] = { "siete", "ocho" };
	SListaLiterales * p_lisObj = CrearListaLiterales ( p_cDest, 2 );
	SListaLiterales * p_lisVal = CrearListaLiterales ( p_cVal, 2 );
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisVal ) )
	{
		SLisLitMoverA ( p_lisObj, 0 );
		if ( ( SLisLitInsertarListaDup ( p_lisObj, p_lisVal ) != 1 ) ||
			 ( SLisLitConcatenarListaDup ( p_lisObj, p_lisVal ) != 1 ) )
		{
			printf( "Error caso 1: se esperaba resultado 1 al insertar y concatenar copias\n" );
			iRes = BOOL_VAL_FALSO;
		}
		const char * p_cEsp [ 6 ] = { "uno", "siete", "ocho", "dos", "siete", "ocho" };
		if ( VerificarContenido ( p_lisObj, p_cEsp, 6 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 2: se esperaba { uno, siete, ocho, dos, siete, ocho }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Copias: otro bloque, y los valores quedan intactos. */
		if ( ( SLisLitElemento ( p_lisObj, 1 ) == SLisLitElemento ( p_lisVal, 0 ) ) ||
			 ( VerificarContenido ( p_lisVal, p_cVal, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 3: las copias no deberian compartir cadena y los valores seguir { siete, ocho }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisLitInsertarListaDup ( NULL, p_lisVal ) != 0 ) || ( SLisLitConcatenarListaDup ( p_lisVal, p_lisVal ) != 0 ) )
		{
			printf( "Error caso 4: con una lista nula o la misma lista se esperaba 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisLitDestruir ( &p_lisObj );
	SLisLitDestruir ( &p_lisVal );
	return ( iRes );
}

static int TestSLisLitExtraerLista01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisLitExtraerLista 01:\n" );

	const char * p_cVal [ 5 ] = { "a", "b", "c", "b", "d" };
	const char * p_cBus [ 4 ] = { "b", "d", "x", "b" };
	SListaLiterales * p_lisObj = CrearListaLiterales ( p_cVal, 5 );
	SListaLiterales * p_lisBus = CrearListaLiterales ( p_cBus, 4 );
	SListaLiterales * p_lisRes = NULL;
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisBus ) )
	{
		/* Una aparicion por valor buscado, en el orden de los buscados; la x no esta. */
		p_lisRes = SLisLitExtraerLista ( p_lisObj, p_lisBus );
		const char * p_cEspRes [ 3 ] = { "b", "d", "b" };
		const char * p_cEspObj [ 2 ] = { "a", "c" };
		if ( ES_NULO ( p_lisRes ) || ( VerificarContenido ( p_lisRes, p_cEspRes, 3 ) != BOOL_VAL_CIERTO ) ||
			 ( SLisLitLiberacionMemoriaActivada ( p_lisRes ) != 1 ) )
		{
			printf( "Error caso 1: se esperaba extraer { b, d, b } con la liberacion del origen\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( VerificarContenido ( p_lisObj, p_cEspObj, 2 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 2: en el origen deberia quedar { a, c }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SLisLitExtraerLista ( p_lisObj, p_lisObj ) ) || ES_VALIDO ( SLisLitExtraerLista ( NULL, p_lisBus ) ) )
		{
			printf( "Error caso 3: con la misma lista o una nula se esperaba nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisLitDestruir ( &p_lisObj );
	SLisLitDestruir ( &p_lisBus );
	SLisLitDestruir ( &p_lisRes );
	return ( iRes );
}

/* Destruye una aparicion por valor buscado comparando el contenido; los valores
   no cambian, y sin liberacion no se liberan las cadenas. */
static int TestSLisLitEliminarLista01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisLitEliminarLista 01:\n" );

	const char * p_cVal [ 5 ] = { "a", "b", "c", "b", "d" };
	const char * p_cBus [ 4 ] = { "b", "d", "x", "b" };
	SListaLiterales * p_lisObj = CrearListaLiterales ( p_cVal, 5 );
	SListaLiterales * p_lisBus = CrearListaLiterales ( p_cBus, 4 );
	SListaLiterales * p_lisVacia = SLisLitCrear ();
	SListaLiterales * p_lisSinLib = SLisLitCrear ();
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisBus ) && ES_VALIDO ( p_lisVacia ) && ES_VALIDO ( p_lisSinLib ) )
	{
		/* La x no esta y se ignora; la b esta dos veces en los buscados. */
		if ( SLisLitEliminarLista ( p_lisObj, p_lisBus ) != 1 )
		{
			printf( "Error caso 1: se esperaba 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		const char * p_cEspObj [ 2 ] = { "a", "c" };
		if ( VerificarContenido ( p_lisObj, p_cEspObj, 2 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 2: deberia quedar { a, c }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( VerificarContenido ( p_lisBus, p_cBus, 4 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 3: los valores no deberian cambiar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Ya no queda ninguno: no hay nada que eliminar, y no es un error. */
		if ( ( SLisLitEliminarLista ( p_lisObj, p_lisBus ) != 1 ) ||
			 ( SLisLitEliminarLista ( p_lisObj, p_lisVacia ) != 1 ) ||
			 ( VerificarContenido ( p_lisObj, p_cEspObj, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 4: sin nada que eliminar se esperaba 1 sin cambios\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisLitEliminarLista ( p_lisObj, p_lisObj ) != 0 ) ||
			 ( VerificarContenido ( p_lisObj, p_cEspObj, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 5: con la misma lista se esperaba 0 sin cambios\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisLitEliminarLista ( p_lisObj, NULL ) != 0 ) || ( SLisLitEliminarLista ( NULL, p_lisBus ) != 0 ) )
		{
			printf( "Error caso 6: con una lista nula se esperaba 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Sin liberacion las cadenas no son de la lista: aqui son literales del
		   programa, y liberarlas romperia el heap. */
		const char * p_cEspSinLib [ 2 ] = { "a", "c" };
		SLisLitDesactivarLiberacionMemoria ( p_lisSinLib );
		SLisLitInsertarAlFinal ( p_lisSinLib, (char *) "a" );
		SLisLitInsertarAlFinal ( p_lisSinLib, (char *) "b" );
		SLisLitInsertarAlFinal ( p_lisSinLib, (char *) "c" );
		if ( ( SLisLitEliminarLista ( p_lisSinLib, p_lisBus ) != 1 ) ||
			 ( VerificarContenido ( p_lisSinLib, p_cEspSinLib, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 7: sin liberacion se esperaba quitar la b sin liberarla\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisLitDestruir ( &p_lisObj );
	SLisLitDestruir ( &p_lisBus );
	SLisLitDestruir ( &p_lisVacia );
	SLisLitDestruir ( &p_lisSinLib );
	return ( iRes );
}

static int TestSLisLitOperacionesListas01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisLitOperacionesListas 01:\n" );

	const char * p_cV1 [ 4 ] = { "uno", "dos", "tres", "cuatro" };
	const char * p_cV2 [ 3 ] = { "cuatro", "dos", "cinco" };
	SListaLiterales * p_lis1 = CrearListaLiterales ( p_cV1, 4 );
	SListaLiterales * p_lis2 = CrearListaLiterales ( p_cV2, 3 );
	if ( ES_VALIDO ( p_lis1 ) && ES_VALIDO ( p_lis2 ) )
	{
		/* La union es concatenacion: "dos" y "cuatro" salen dos veces. */
		SListaLiterales * p_lisRes = SLisLitUnion ( p_lis1, p_lis2 );
		const char * p_cEspU [ 7 ] = { "uno", "dos", "tres", "cuatro", "cuatro", "dos", "cinco" };
		if ( ES_NULO ( p_lisRes ) || ( VerificarContenido ( p_lisRes, p_cEspU, 7 ) != BOOL_VAL_CIERTO ) ||
			 ( SLisLitElemento ( p_lisRes, 0 ) == SLisLitElemento ( p_lis1, 0 ) ) ||
			 ( SLisLitLiberacionMemoriaActivada ( p_lisRes ) != 1 ) )
		{
			printf( "Error caso 1: la union deberia ser { uno, dos, tres, cuatro, cuatro, dos, cinco } con copias propias\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisLitDestruir ( &p_lisRes );

		/* Interseccion y diferencia, las dos en el orden de V1. */
		p_lisRes = SLisLitInterseccion ( p_lis1, p_lis2 );
		const char * p_cEspI [ 2 ] = { "dos", "cuatro" };
		if ( ES_NULO ( p_lisRes ) || ( VerificarContenido ( p_lisRes, p_cEspI, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 2: la interseccion deberia ser { dos, cuatro }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisLitDestruir ( &p_lisRes );

		p_lisRes = SLisLitDiferencia ( p_lis1, p_lis2 );
		const char * p_cEspD [ 2 ] = { "uno", "tres" };
		if ( ES_NULO ( p_lisRes ) || ( VerificarContenido ( p_lisRes, p_cEspD, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 3: la diferencia deberia ser { uno, tres }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisLitDestruir ( &p_lisRes );

		if ( ( VerificarContenido ( p_lis1, p_cV1, 4 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarContenido ( p_lis2, p_cV2, 3 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 4: las listas de entrada no deberian cambiar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SLisLitUnion ( p_lis1, NULL ) ) ||
			 ES_VALIDO ( SLisLitInterseccion ( NULL, p_lis2 ) ) ||
			 ES_VALIDO ( SLisLitDiferencia ( p_lis1, NULL ) ) )
		{
			printf( "Error caso 5: con listas nulas se esperaba nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisLitDestruir ( &p_lis1 );
	SLisLitDestruir ( &p_lis2 );
	ErrLimpiar ();
	return ( iRes );
}

/* La copia tiene sus propias cadenas, con el mismo texto y en el mismo orden;
   el original no cambia, ni su cursor. */
static int TestSLisLitDuplicar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisLitDuplicar 01:\n" );

	const char * p_cVal [ 3 ] = { "uno", "dos", "tres" };
	SListaLiterales * p_lisObj = CrearListaLiterales ( p_cVal, 3 );
	SListaLiterales * p_lisVacia = SLisLitCrear ();
	SListaLiterales * p_lisDup = NULL;
	SListaLiterales * p_lisDupVacia = NULL;
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisVacia ) )
	{
		SLisLitMoverA ( p_lisObj, 1 );
		p_lisDup = SLisLitDuplicar ( p_lisObj );
		if ( SLisLitPosicion ( p_lisObj ) != 1 )
		{
			printf( "Error caso 1: el cursor del original deberia seguir en 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_NULO ( p_lisDup ) || ( p_lisDup == p_lisObj ) )
		{
			printf( "Error caso 2: se esperaba una lista nueva\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			if ( VerificarContenido ( p_lisDup, p_cVal, 3 ) != BOOL_VAL_CIERTO )
			{
				printf( "Error caso 3: la copia deberia tener { uno, dos, tres }\n" );
				iRes = BOOL_VAL_FALSO;
			}
			if ( SLisLitElemento ( p_lisDup, 0 ) == SLisLitElemento ( p_lisObj, 0 ) )
			{
				printf( "Error caso 4: la copia no deberia compartir las cadenas\n" );
				iRes = BOOL_VAL_FALSO;
			}
			SLisLitEstablecerElemDup ( p_lisDup, 2, "otro" );
			if ( VerificarContenido ( p_lisObj, p_cVal, 3 ) != BOOL_VAL_CIERTO )
			{
				printf( "Error caso 5: cambiar la copia no deberia tocar el original\n" );
				iRes = BOOL_VAL_FALSO;
			}
		}
		/* La vacia se copia en otra vacia, no en nulo. */
		p_lisDupVacia = SLisLitDuplicar ( p_lisVacia );
		if ( ES_NULO ( p_lisDupVacia ) || ( SLisLitEsValida ( p_lisDupVacia ) != 1 ) ||
			 ( SLisLitNumElementos ( p_lisDupVacia ) != 0 ) )
		{
			printf( "Error caso 6: la copia de una vacia deberia ser otra vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SLisLitDuplicar ( NULL ) ) )
		{
			printf( "Error caso 7: con una lista nula se esperaba nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisLitDestruir ( &p_lisObj );
	SLisLitDestruir ( &p_lisVacia );
	SLisLitDestruir ( &p_lisDup );
	SLisLitDestruir ( &p_lisDupVacia );
	return ( iRes );
}


/* 1 solo con el cursor sobre un elemento: no en una vacia, ni deposicionada,
   ni con la lista nula. */
/* Repetidos comparando el contenido, y ExtraerUnicos / TieneRepetidos. */
static int TestSLisLitRepeticiones01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisLitRepeticiones 01:\n" );

	const char * p_cVal [ 6 ] = { "b", "a", "b", "c", "b", "d" };
	const char * p_cDes [ 5 ] = { "c", "a", "c", "b", "a" };
	/* Otro bloque con el mismo texto: se busca por contenido. */
	char cB [ 2 ] = { 'b', '\0' };
	SListaLiterales * p_lisObj = CrearListaLiterales ( p_cVal, 6 );
	SListaLiterales * p_lisDes = CrearListaLiterales ( p_cDes, 5 );
	SListaLiterales * p_lisVacia = SLisLitCrear ();
	SListaLiterales * p_lisUni = NULL;
	SListaLiterales * p_lisOrd = NULL;
	SListaLiterales * p_lisUniVacia = NULL;
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisDes ) && ES_VALIDO ( p_lisVacia ) )
	{
		if ( ( SLisLitBuscarPrimero ( p_lisObj, cB ) != 0 ) ||
			 ( SLisLitBuscarSiguiente ( p_lisObj, cB, 0 ) != 2 ) ||
			 ( SLisLitBuscarSiguiente ( p_lisObj, cB, 2 ) != 4 ) ||
			 ( SLisLitBuscarSiguiente ( p_lisObj, cB, 4 ) != -1 ) ||
			 ( SLisLitBuscarSiguiente ( p_lisObj, cB, 1 ) != 2 ) ||
			 ( SLisLitBuscar ( p_lisObj, "d" ) != 5 ) )
		{
			printf( "Error caso 1: la b deberia estar en 0, 2 y 4, y la d en la 5\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisLitRepeticiones ( p_lisObj, cB ) != 3 ) || ( SLisLitRepeticiones ( p_lisObj, "a" ) != 1 ) ||
			 ( SLisLitRepeticiones ( p_lisObj, "x" ) != 0 ) || ( SLisLitBuscar ( p_lisObj, "x" ) != -1 ) )
		{
			printf( "Error caso 2: la b deberia estar 3 veces, la a una y la x ninguna\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Unicos en el orden de su primera aparicion, u ordenados; copias propias. */
		p_lisUni = SLisLitExtraerUnicos ( p_lisDes );
		p_lisOrd = SLisLitExtraerUnicosExt ( p_lisDes, 1 );
		const char * p_cUni [ 3 ] = { "c", "a", "b" };
		const char * p_cOrd [ 3 ] = { "a", "b", "c" };
		if ( ( VerificarContenido ( p_lisUni, p_cUni, 3 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarContenido ( p_lisOrd, p_cOrd, 3 ) != BOOL_VAL_CIERTO ) ||
			 ( SLisLitLiberacionMemoriaActivada ( p_lisUni ) != 1 ) ||
			 ( SLisLitElemento ( p_lisUni, 0 ) == SLisLitElemento ( p_lisDes, 0 ) ) ||
			 ( VerificarContenido ( p_lisDes, p_cDes, 5 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 3: se esperaban copias de { c, a, b } y, ordenadas, { a, b, c }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisLitTieneRepetidos ( p_lisDes ) != 1 ) || ( SLisLitTieneRepetidos ( p_lisUni ) != 0 ) ||
			 ( SLisLitTieneRepetidos ( p_lisVacia ) != 0 ) || ( SLisLitTieneRepetidos ( NULL ) != 0 ) )
		{
			printf( "Error caso 4: solo la de partida deberia tener repetidos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_lisUniVacia = SLisLitExtraerUnicos ( p_lisVacia );
		if ( ( SLisLitEsValida ( p_lisUniVacia ) != 1 ) || ( SLisLitNumElementos ( p_lisUniVacia ) != 0 ) ||
			 ES_VALIDO ( SLisLitExtraerUnicos ( NULL ) ) )
		{
			printf( "Error caso 5: de una vacia se esperaba otra vacia, y de una nula nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisLitRepeticiones ( NULL, cB ) != 0 ) || ( SLisLitRepeticiones ( p_lisObj, NULL ) != 0 ) ||
			 ( SLisLitBuscarSiguiente ( NULL, cB, -1 ) != -1 ) || ( SLisLitBuscarSiguiente ( p_lisObj, NULL, -1 ) != -1 ) ||
			 ( SLisLitBuscarSiguiente ( p_lisObj, cB, -2 ) != -1 ) )
		{
			printf( "Error caso 6: con un nulo se esperaba 0 al contar y -1 al buscar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisLitDestruir ( &p_lisObj );
	SLisLitDestruir ( &p_lisDes );
	SLisLitDestruir ( &p_lisVacia );
	SLisLitDestruir ( &p_lisUni );
	SLisLitDestruir ( &p_lisOrd );
	SLisLitDestruir ( &p_lisUniVacia );
	return ( iRes );
}

static int TestSLisLitEstaPosicionada01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisLitEstaPosicionada 01:\n" );

	SListaLiterales * p_lisObj = SLisLitCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( SLisLitEstaPosicionada ( p_lisObj ) != 0 )
		{
			printf( "Error caso 1: una lista vacia no deberia estar posicionada\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisLitInsertarDupAlFinal ( p_lisObj, "v10" );
		SLisLitInsertarDupAlFinal ( p_lisObj, "v20" );
		SLisLitInicio ( p_lisObj );
		if ( SLisLitEstaPosicionada ( p_lisObj ) != 1 )
		{
			printf( "Error caso 2: tras Inicio deberia estar posicionada\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisLitSiguiente ( p_lisObj );
		SLisLitSiguiente ( p_lisObj );
		if ( SLisLitEstaPosicionada ( p_lisObj ) != 0 )
		{
			printf( "Error caso 3: pasado el ultimo no deberia estar posicionada\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisLitFinal ( p_lisObj );
		SLisLitDeposicionar ( p_lisObj );
		if ( SLisLitEstaPosicionada ( p_lisObj ) != 0 )
		{
			printf( "Error caso 4: tras Deposicionar no deberia estar posicionada\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisLitEstaPosicionada ( NULL ) != 0 )
		{
			printf( "Error caso 5: con una lista nula se esperaba 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisLitDestruir ( &p_lisObj );
	return ( iRes );
}

int TestSListaLiterales ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SListaLiterales]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSLisLitOperaciones01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisLitCursor01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisLitInvalidos01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisLitBuscarExiste01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisLitExisten01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisLitInsertarLista01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisLitListaDup01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisLitExtraerLista01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisLitEliminarLista01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisLitOperacionesListas01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisLitDuplicar01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisLitRepeticiones01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisLitEstaPosicionada01 () == BOOL_VAL_CIERTO ) )
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
