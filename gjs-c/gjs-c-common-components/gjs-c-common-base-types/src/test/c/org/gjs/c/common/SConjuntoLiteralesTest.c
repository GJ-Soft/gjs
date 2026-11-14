#include "Base.h"

#include "SConjuntoLiterales.h"



static int ElementoEs ( SConjuntoLiterales * p_cnjObj, int iElem, const char * p_cEsperado )
{
	return ( CadComparar ( SCnjLitElemento ( p_cnjObj, iElem ), (char *) p_cEsperado ) == COMP_IGUAL );
}



static int TestSCnjLitOperaciones01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjLitOperaciones 01:\n" );

	SConjuntoLiterales * p_cnjObj = SCnjLitCrear ();
	if ( ES_VALIDO ( p_cnjObj ) )
	{
		if ( ( SCnjLitEsValido ( p_cnjObj ) != 1 ) || ( SCnjLitEstaVacio ( p_cnjObj ) != 1 ) )
		{
			printf( "Error caso 1: el conjunto recien creado deberia ser valido y estar vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Se insertan en desorden; el conjunto los mantiene ordenados. */
		if ( ( SCnjLitInsertar ( p_cnjObj, "banana" ) != 1 ) ||
			 ( SCnjLitInsertar ( p_cnjObj, "apple" ) != 1 ) ||
			 ( SCnjLitInsertar ( p_cnjObj, "cherry" ) != 1 ) )
		{
			printf( "Error caso 2: se esperaba poder insertar las tres cadenas\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Un valor ya presente se rechaza. */
		if ( SCnjLitInsertar ( p_cnjObj, "apple" ) == 1 )
		{
			printf( "Error caso 3: insertar un valor duplicado no deberia tener exito\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnjLitNumElementos ( p_cnjObj ) != 3 )
		{
			printf( "Error caso 4: el conjunto deberia tener 3 elementos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Orden alfabetico. */
		if ( ( ! ElementoEs ( p_cnjObj, 0, "apple" ) ) ||
			 ( ! ElementoEs ( p_cnjObj, 1, "banana" ) ) ||
			 ( ! ElementoEs ( p_cnjObj, 2, "cherry" ) ) )
		{
			printf( "Error caso 5: los elementos deberian estar en orden alfabetico\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SCnjLitExiste ( p_cnjObj, "banana" ) != 1 ) || ( SCnjLitExiste ( p_cnjObj, "grape" ) != 0 ) )
		{
			printf( "Error caso 6: existe deberia encontrar \"banana\" y no \"grape\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnjLitBuscar ( p_cnjObj, "cherry" ) != 2 )
		{
			printf( "Error caso 7: buscar \"cherry\" deberia devolver el indice 2\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Eliminar el primero ( "apple" ). */
		SCnjLitEliminar ( p_cnjObj, 0 );
		if ( ( SCnjLitNumElementos ( p_cnjObj ) != 2 ) || ( ! ElementoEs ( p_cnjObj, 0, "banana" ) ) )
		{
			printf( "Error caso 8: tras eliminar deberia quedar \"banana\" primero\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SCnjLitVaciar ( p_cnjObj );
		if ( SCnjLitEstaVacio ( p_cnjObj ) != 1 )
		{
			printf( "Error caso 9: tras vaciar el conjunto deberia estar vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el conjunto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCnjLitDestruir ( &p_cnjObj );

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		printf( "Error caso 10: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int CadenaEs ( const char * p_cCad, const char * p_cEsperado )
{
	return ( ES_VALIDO ( p_cCad ) && ( CadComparar ( (char *) p_cCad, (char *) p_cEsperado ) == COMP_IGUAL ) );
}

static int TestSCnjLitPrimeroUltimo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjLitPrimeroUltimo 01:\n" );

	SConjuntoLiterales * p_cnjObj = SCnjLitCrear ();
	if ( ES_VALIDO ( p_cnjObj ) )
	{
		/* Vacio: no hay ni primero ni ultimo. */
		if ( ES_VALIDO ( SCnjLitPrimero ( p_cnjObj ) ) )
		{
			printf( "Error caso 1: el primero de un conjunto vacio deberia ser nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SCnjLitUltimo ( p_cnjObj ) ) )
		{
			printf( "Error caso 2: el ultimo de un conjunto vacio deberia ser nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Con un solo elemento, primero y ultimo son la misma cadena. */
		SCnjLitInsertar ( p_cnjObj, "banana" );
		if ( ! CadenaEs ( SCnjLitPrimero ( p_cnjObj ), "banana" ) )
		{
			printf( "Error caso 3: con un elemento, el primero deberia ser \"banana\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnjLitUltimo ( p_cnjObj ) != SCnjLitPrimero ( p_cnjObj ) )
		{
			printf( "Error caso 4: con un elemento, el ultimo deberia ser el mismo que el primero\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Se insertan por fuera de los extremos: primero y ultimo siguen el orden alfabetico. */
		SCnjLitInsertar ( p_cnjObj, "cherry" );
		SCnjLitInsertar ( p_cnjObj, "apple" );
		if ( ! CadenaEs ( SCnjLitPrimero ( p_cnjObj ), "apple" ) )
		{
			printf( "Error caso 5: el primero deberia ser \"apple\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ! CadenaEs ( SCnjLitUltimo ( p_cnjObj ), "cherry" ) )
		{
			printf( "Error caso 6: el ultimo deberia ser \"cherry\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Tras eliminar el ultimo, el nuevo ultimo es "banana". */
		SCnjLitEliminar ( p_cnjObj, 2 );
		if ( ! CadenaEs ( SCnjLitUltimo ( p_cnjObj ), "banana" ) )
		{
			printf( "Error caso 7: tras eliminar \"cherry\", el ultimo deberia ser \"banana\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SCnjLitPrimero ( NULL ) ) || ES_VALIDO ( SCnjLitUltimo ( NULL ) ) )
		{
			printf( "Error caso 8: primero y ultimo de un conjunto nulo deberian ser nulos\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el conjunto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCnjLitDestruir ( &p_cnjObj );
	return ( iRes );
}

static int TestSCnjLitPosicion01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjLitPosicion 01:\n" );

	SConjuntoLiterales * p_cnjObj = SCnjLitCrear ();
	if ( ES_VALIDO ( p_cnjObj ) )
	{
		/* Vacio: nada tiene posicion. */
		if ( SCnjLitPosicion ( p_cnjObj, "banana" ) != -1 )
		{
			printf( "Error caso 1: en un conjunto vacio la posicion deberia ser -1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SCnjLitInsertar ( p_cnjObj, "cherry" );
		SCnjLitInsertar ( p_cnjObj, "apple" );
		SCnjLitInsertar ( p_cnjObj, "banana" );

		/* Posicion por valor: el conjunto guarda copias, asi que se busca con literales ajenos. */
		if ( ( SCnjLitPosicion ( p_cnjObj, "apple" ) != 0 ) ||
			 ( SCnjLitPosicion ( p_cnjObj, "banana" ) != 1 ) ||
			 ( SCnjLitPosicion ( p_cnjObj, "cherry" ) != 2 ) )
		{
			printf( "Error caso 2: \"apple\", \"banana\" y \"cherry\" deberian estar en las posiciones 0, 1 y 2\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SCnjLitPosicion ( p_cnjObj, SCnjLitPrimero ( p_cnjObj ) ) != 0 ) ||
			 ( SCnjLitPosicion ( p_cnjObj, SCnjLitUltimo ( p_cnjObj ) ) != 2 ) )
		{
			printf( "Error caso 3: el primero y el ultimo deberian estar en las posiciones 0 y 2\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Valores que no estan: menor que el minimo, intermedio y mayor que el maximo. */
		if ( SCnjLitPosicion ( p_cnjObj, "aaa" ) != -1 )
		{
			printf( "Error caso 4: \"aaa\" no deberia tener posicion\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnjLitPosicion ( p_cnjObj, "blueberry" ) != -1 )
		{
			printf( "Error caso 5: \"blueberry\" no deberia tener posicion\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnjLitPosicion ( p_cnjObj, "grape" ) != -1 )
		{
			printf( "Error caso 6: \"grape\" no deberia tener posicion\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Un prefijo de un elemento no es ese elemento. */
		if ( SCnjLitPosicion ( p_cnjObj, "ban" ) != -1 )
		{
			printf( "Error caso 7: \"ban\" no deberia tener posicion\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnjLitPosicion ( p_cnjObj, NULL ) != -1 )
		{
			printf( "Error caso 8: una cadena nula no deberia tener posicion\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnjLitPosicion ( NULL, "banana" ) != -1 )
		{
			printf( "Error caso 9: en un conjunto nulo la posicion deberia ser -1\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el conjunto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCnjLitDestruir ( &p_cnjObj );
	return ( iRes );
}

static int TestSCnjLitInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjLitInvalidos 01:\n" );

	if ( SCnjLitEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: un conjunto nulo no deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SCnjLitNumElementos ( NULL ) != 0 )
	{
		printf( "Error caso 2: un conjunto nulo deberia tener 0 elementos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SConjuntoLiterales * p_cnjNulo = NULL;
	SCnjLitDestruir ( &p_cnjNulo );
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

static SConjuntoLiterales * CrearCnjLiterales ( const char ** p_p_cValores, int iNum )
{
	SConjuntoLiterales * p_cnjObj = SCnjLitCrear ();
	int iPos = 0;
	while ( ES_VALIDO ( p_cnjObj ) && ( iPos < iNum ) )
	{
		SCnjLitInsertar ( p_cnjObj, p_p_cValores [ iPos ] );
		iPos = iPos + 1;
	}
	return ( p_cnjObj );
}

static int VerificarCnj ( SConjuntoLiterales * p_cnjObj, const char ** p_p_cEsperados, int iNum )
{
	int iRes = BOOL_VAL_CIERTO;

	if ( ( SCnjLitEsValido ( p_cnjObj ) != 1 ) || ( SCnjLitNumElementos ( p_cnjObj ) != iNum ) )
	{
		printf( "  Verificacion: se esperaban %d elementos: %d\n", iNum, SCnjLitNumElementos ( p_cnjObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	int iPos = 0;
	while ( ( iPos < iNum ) && ( iRes == BOOL_VAL_CIERTO ) )
	{
		if ( ES_NULO ( SCnjLitElemento ( p_cnjObj, iPos ) ) || ( ! ElementoEs ( p_cnjObj, iPos, p_p_cEsperados [ iPos ] ) ) )
		{
			printf( "  Verificacion: en pos %d se esperaba \"%s\"\n", iPos, p_p_cEsperados [ iPos ] );
			iRes = BOOL_VAL_FALSO;
		}
		iPos = iPos + 1;
	}
	return ( iRes );
}

static int VerificarYDestruir ( SConjuntoLiterales ** p_p_cnjObj, const char ** p_p_cEsperados, int iNum )
{
	int iRes = VerificarCnj ( *p_p_cnjObj, p_p_cEsperados, iNum );
	SCnjLitDestruir ( p_p_cnjObj );
	return ( iRes );
}

/* Conjunto y lista internos, pertenencia, Concatenar ( copias de lo que
   falta ), Eliminar y Extraer. */
static int TestSCnjLitOperacionesListas01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjLitOperacionesListas 01:\n" );

	const char * p_cA [ 3 ] = { "b", "d", "a" };
	const char * p_cB [ 2 ] = { "d", "e" };
	const char * p_cL [ 3 ] = { "c", "a", "c" };
	const char * p_cAB [ 2 ] = { "a", "b" };
	const char * p_cX [ 1 ] = { "x" };
	const char * p_cSoloA [ 1 ] = { "a" };
	const char * p_cC [ 1 ] = { "c" };
	SConjuntoLiterales * p_cnjA = CrearCnjLiterales ( p_cA, 3 );
	SConjuntoLiterales * p_cnjB = CrearCnjLiterales ( p_cB, 2 );
	SConjuntoLiterales * p_cnjSoloA = CrearCnjLiterales ( p_cSoloA, 1 );
	SListaLiterales * p_lisL = CrearListaLiterales ( p_cL, 3 );
	SListaLiterales * p_lisAB = CrearListaLiterales ( p_cAB, 2 );
	SListaLiterales * p_lisX = CrearListaLiterales ( p_cX, 1 );
	SListaLiterales * p_lisC = CrearListaLiterales ( p_cC, 1 );
	SConjuntoLiterales * p_cnjRes = NULL;
	if ( ES_VALIDO ( p_cnjA ) && ES_VALIDO ( p_cnjB ) && ES_VALIDO ( p_cnjSoloA ) && ES_VALIDO ( p_lisL ) &&
		 ES_VALIDO ( p_lisAB ) && ES_VALIDO ( p_lisX ) && ES_VALIDO ( p_lisC ) )
	{
		if ( ( SCnjLitConjunto ( p_cnjA ) != p_cnjA->p_cnjDatos ) ||
			 ( SCnjLitLista ( p_cnjA ) != SCnjpLista ( p_cnjA->p_cnjDatos ) ) ||
			 ES_VALIDO ( SCnjLitConjunto ( NULL ) ) || ES_VALIDO ( SCnjLitLista ( NULL ) ) )
		{
			printf( "Error caso 1: Conjunto y Lista deberian devolver los internos, o nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SCnjLitExistenTodos ( p_cnjA, p_cnjB ) != 0 ) || ( SCnjLitExisteAlguno ( p_cnjA, p_cnjB ) != 1 ) ||
			 ( SCnjLitExistenTodosLista ( p_cnjA, p_lisAB ) != 1 ) || ( SCnjLitExisteAlgunoLista ( p_cnjA, p_lisX ) != 0 ) )
		{
			printf( "Error caso 2: se esperaba 0, 1, 1 y 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Concatenar copia lo que falta: la c una vez, y luego la e. */
		const char * p_cEsp3 [ 5 ] = { "a", "b", "c", "d", "e" };
		if ( ( SCnjLitConcatenarLista ( p_cnjA, p_lisL ) != 1 ) ||
			 ( SCnjLitConcatenarConjunto ( p_cnjA, p_cnjB ) != 1 ) ||
			 ( VerificarCnj ( p_cnjA, p_cEsp3, 5 ) != BOOL_VAL_CIERTO ) ||
			 ( SCnjLitElemento ( p_cnjA, 2 ) == SLisLitElemento ( p_lisL, 0 ) ) ||
			 ( SLisLitNumElementos ( p_lisL ) != 3 ) || ( SCnjLitNumElementos ( p_cnjB ) != 2 ) )
		{
			printf( "Error caso 3: deberia quedar { a, b, c, d, e } con copias y los valores sin tocar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		const char * p_cEsp4 [ 2 ] = { "a", "b" };
		if ( ( SCnjLitEliminarLista ( p_cnjA, p_lisC ) != 1 ) ||
			 ( SCnjLitEliminarConjunto ( p_cnjA, p_cnjB ) != 1 ) ||
			 ( VerificarCnj ( p_cnjA, p_cEsp4, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 4: deberia quedar { a, b }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		char * p_cMovida = SCnjLitElemento ( p_cnjA, 0 );
		p_cnjRes = SCnjLitExtraerConjunto ( p_cnjA, p_cnjSoloA );
		const char * p_cSoloB [ 1 ] = { "b" };
		if ( ( SCnjLitElemento ( p_cnjRes, 0 ) != p_cMovida ) ||
			 ( VerificarYDestruir ( &p_cnjRes, p_cSoloA, 1 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarCnj ( p_cnjA, p_cSoloB, 1 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 5: se esperaba mover la a y dejar { b }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_cnjRes = SCnjLitExtraerLista ( p_cnjA, p_lisAB );
		if ( ( VerificarYDestruir ( &p_cnjRes, p_cSoloB, 1 ) != BOOL_VAL_CIERTO ) ||
			 ( SCnjLitEstaVacio ( p_cnjA ) != 1 ) )
		{
			printf( "Error caso 6: se esperaba mover la b y dejarlo vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SCnjLitExistenTodos ( NULL, p_cnjB ) != 0 ) || ( SCnjLitExisteAlgunoLista ( p_cnjB, NULL ) != 0 ) ||
			 ( SCnjLitConcatenarLista ( p_cnjB, NULL ) != 0 ) || ( SCnjLitConcatenarConjunto ( NULL, p_cnjB ) != 0 ) ||
			 ( SCnjLitEliminarConjunto ( p_cnjB, p_cnjB ) != 0 ) || ( SCnjLitEliminarLista ( NULL, p_lisX ) != 0 ) ||
			 ES_VALIDO ( SCnjLitExtraerConjunto ( p_cnjB, p_cnjB ) ) ||
			 ES_VALIDO ( SCnjLitExtraerLista ( p_cnjB, NULL ) ) ||
			 ( VerificarCnj ( p_cnjB, p_cB, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 7: con nulos o el mismo conjunto se esperaba 0 o nulo sin cambios\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear los conjuntos o las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCnjLitDestruir ( &p_cnjA );
	SCnjLitDestruir ( &p_cnjB );
	SCnjLitDestruir ( &p_cnjSoloA );
	SLisLitDestruir ( &p_lisL );
	SLisLitDestruir ( &p_lisAB );
	SLisLitDestruir ( &p_lisX );
	SLisLitDestruir ( &p_lisC );
	return ( iRes );
}

/* Union, Interseccion y Diferencia: copias, sin repetidos, y los de entrada
   sin tocar. */
static int TestSCnjLitUnion01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjLitUnion 01:\n" );

	const char * p_cA [ 3 ] = { "b", "d", "a" };
	const char * p_cB [ 2 ] = { "d", "e" };
	const char * p_cL [ 3 ] = { "c", "a", "c" };
	SConjuntoLiterales * p_cnjA = CrearCnjLiterales ( p_cA, 3 );
	SConjuntoLiterales * p_cnjB = CrearCnjLiterales ( p_cB, 2 );
	SListaLiterales * p_lisL = CrearListaLiterales ( p_cL, 3 );
	SConjuntoLiterales * p_cnjRes = NULL;
	if ( ES_VALIDO ( p_cnjA ) && ES_VALIDO ( p_cnjB ) && ES_VALIDO ( p_lisL ) )
	{
		const char * p_cUni [ 4 ] = { "a", "b", "d", "e" };
		const char * p_cInt [ 1 ] = { "d" };
		const char * p_cDif [ 2 ] = { "a", "b" };
		p_cnjRes = SCnjLitUnion ( p_cnjA, p_cnjB );
		if ( ( SCnjLitElemento ( p_cnjRes, 0 ) == SCnjLitElemento ( p_cnjA, 0 ) ) ||
			 ( VerificarYDestruir ( &p_cnjRes, p_cUni, 4 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 1: la union deberia ser { a, b, d, e }, con copias\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_cnjRes = SCnjLitInterseccion ( p_cnjA, p_cnjB );
		if ( VerificarYDestruir ( &p_cnjRes, p_cInt, 1 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 2: la interseccion deberia ser { d }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_cnjRes = SCnjLitDiferencia ( p_cnjA, p_cnjB );
		if ( VerificarYDestruir ( &p_cnjRes, p_cDif, 2 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 3: la diferencia deberia ser { a, b }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		const char * p_cUniL [ 4 ] = { "a", "b", "c", "d" };
		const char * p_cIntL [ 1 ] = { "a" };
		const char * p_cDifL [ 2 ] = { "b", "d" };
		p_cnjRes = SCnjLitUnionLista ( p_cnjA, p_lisL );
		if ( VerificarYDestruir ( &p_cnjRes, p_cUniL, 4 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 4: la union con la lista deberia ser { a, b, c, d }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_cnjRes = SCnjLitInterseccionLista ( p_cnjA, p_lisL );
		if ( VerificarYDestruir ( &p_cnjRes, p_cIntL, 1 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 5: la interseccion con la lista deberia ser { a }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_cnjRes = SCnjLitDiferenciaLista ( p_cnjA, p_lisL );
		if ( VerificarYDestruir ( &p_cnjRes, p_cDifL, 2 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 6: la diferencia con la lista deberia ser { b, d }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		const char * p_cOrdA [ 3 ] = { "a", "b", "d" };
		if ( ( VerificarCnj ( p_cnjA, p_cOrdA, 3 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarCnj ( p_cnjB, p_cB, 2 ) != BOOL_VAL_CIERTO ) || ( SLisLitNumElementos ( p_lisL ) != 3 ) )
		{
			printf( "Error caso 7: los de entrada no deberian cambiar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SCnjLitUnion ( NULL, p_cnjB ) ) || ES_VALIDO ( SCnjLitInterseccion ( p_cnjA, NULL ) ) ||
			 ES_VALIDO ( SCnjLitDiferencia ( NULL, NULL ) ) || ES_VALIDO ( SCnjLitUnionLista ( p_cnjA, NULL ) ) ||
			 ES_VALIDO ( SCnjLitInterseccionLista ( NULL, p_lisL ) ) || ES_VALIDO ( SCnjLitDiferenciaLista ( NULL, p_lisL ) ) )
		{
			printf( "Error caso 8: con nulos se esperaba nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear los conjuntos o la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCnjLitDestruir ( &p_cnjA );
	SCnjLitDestruir ( &p_cnjB );
	SLisLitDestruir ( &p_lisL );
	return ( iRes );
}

int TestSConjuntoLiterales ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SConjuntoLiterales]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSCnjLitOperaciones01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjLitPrimeroUltimo01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjLitPosicion01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjLitInvalidos01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjLitOperacionesListas01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjLitUnion01 () == BOOL_VAL_CIERTO ) )
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
