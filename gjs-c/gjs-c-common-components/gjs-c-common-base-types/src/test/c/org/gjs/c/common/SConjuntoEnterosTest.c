#include "Base.h"

#include "SConjuntoEnteros.h"



/* 1 si el conjunto tiene exactamente esos valores, en ese orden. */
static int EsConjunto ( SConjuntoEnteros * p_cnjObj, const int * p_iEsperados, int iNum )
{
	int iRes = BOOL_VAL_CIERTO;

	if ( SCnjIntNumElementos ( p_cnjObj ) != iNum )
	{
		printf( "  Verificacion: se esperaban %d valores: %d\n", iNum, SCnjIntNumElementos ( p_cnjObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	int iPos = 0;
	while ( ( iPos < iNum ) && ( iRes == BOOL_VAL_CIERTO ) )
	{
		if ( SCnjIntElemento ( p_cnjObj, iPos ) != p_iEsperados [ iPos ] )
		{
			printf( "  Verificacion: en la posicion %d se esperaba %d: %d\n", iPos, p_iEsperados [ iPos ], SCnjIntElemento ( p_cnjObj, iPos ) );
			iRes = BOOL_VAL_FALSO;
		}
		iPos = iPos + 1;
	}
	return ( iRes );
}

static SListaEnteros * CrearLista ( const int * p_iValores, int iNum )
{
	SListaEnteros * p_lisObj = SLisIntCrear ();
	int iPos = 0;
	while ( iPos < iNum )
	{
		SLisIntInsertarAlFinal ( p_lisObj, p_iValores [ iPos ] );
		iPos = iPos + 1;
	}
	return ( p_lisObj );
}

static int TestSCnjIntCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjIntCrear 01:\n" );

	SConjuntoEnteros * p_cnjObj = SCnjIntCrear ();
	if ( ( SCnjIntEsValido ( p_cnjObj ) != 1 ) || ( SCnjIntEstaVacio ( p_cnjObj ) != 1 ) || ( SCnjIntNumElementos ( p_cnjObj ) != 0 ) )
	{
		printf( "Error caso 1: recien creado deberia ser valido y estar vacio\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCnjIntDestruir ( &p_cnjObj );
	if ( ES_VALIDO ( p_cnjObj ) || ( SCnjIntEsValido ( NULL ) != 0 ) || ( SCnjIntEstaVacio ( NULL ) != 1 ) )
	{
		printf( "Error caso 2: tras destruir se esperaba nulo, y el nulo no es valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

/* Se insertan en desorden; salen ordenados y sin repetir. */
static int TestSCnjIntInsertar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjIntInsertar 01:\n" );

	SConjuntoEnteros * p_cnjObj = SCnjIntCrear ();
	if ( ( SCnjIntInsertar ( p_cnjObj, 5 ) != 1 ) || ( SCnjIntInsertar ( p_cnjObj, -3 ) != 1 ) ||
		 ( SCnjIntInsertar ( p_cnjObj, 0 ) != 1 ) || ( SCnjIntInsertar ( p_cnjObj, 300 ) != 1 ) )
	{
		printf( "Error caso 1: se esperaba poder insertar 5, -3, 0 y 300\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SCnjIntInsertar ( p_cnjObj, 5 ) != 0 ) || ( SCnjIntInsertar ( p_cnjObj, 0 ) != 0 ) )
	{
		printf( "Error caso 2: un valor que ya esta no deberia entrar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* El orden es el de los enteros, no el de sus bytes: -3 ( FD FF FF FF )
	   va delante de 0, y 300 ( 2C 01 ) detras de 5. */
	int iOrd [ 4 ] = { -3, 0, 5, 300 };
	if ( EsConjunto ( p_cnjObj, iOrd, 4 ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 3: se esperaba { -3, 0, 5, 300 }\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SCnjIntExiste ( p_cnjObj, 0 ) != 1 ) || ( SCnjIntExiste ( p_cnjObj, 4 ) != 0 ) ||
		 ( SCnjIntBuscar ( p_cnjObj, 5 ) != 2 ) || ( SCnjIntBuscar ( p_cnjObj, 4 ) != -1 ) || ( SCnjIntBuscar ( NULL, 5 ) != -1 ) )
	{
		printf( "Error caso 4: Existe y Buscar encuentran el 0 y el 5 (en la 2) y no el 4\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SCnjIntElemento ( p_cnjObj, 4 ) != 0 ) || ( SCnjIntElemento ( p_cnjObj, -1 ) != 0 ) || ( SCnjIntInsertar ( NULL, 1 ) != 0 ) )
	{
		printf( "Error caso 5: fuera de rango se esperaba 0, y no se inserta en el nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCnjIntDestruir ( &p_cnjObj );
	return ( iRes );
}

static int TestSCnjIntModificarEliminar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjIntModificarEliminar 01:\n" );

	SConjuntoEnteros * p_cnjObj = SCnjIntCrearConValores ( 10, 20, 30 );
	/* El 10 pasa a 25: cambia de sitio. */
	int iMod [ 3 ] = { 20, 25, 30 };
	if ( ( SCnjIntModificar ( p_cnjObj, 0, 25 ) != 1 ) || ( EsConjunto ( p_cnjObj, iMod, 3 ) != BOOL_VAL_CIERTO ) )
	{
		printf( "Error caso 1: cambiar el 10 por 25 deberia dejar { 20, 25, 30 }\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SCnjIntModificar ( p_cnjObj, 0, 30 ) != 0 ) || ( EsConjunto ( p_cnjObj, iMod, 3 ) != BOOL_VAL_CIERTO ) )
	{
		printf( "Error caso 2: cambiar a un valor que ya esta deberia dar 0 sin tocar nada\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SCnjIntModificar ( p_cnjObj, 1, 25 ) != 1 ) || ( SCnjIntModificar ( p_cnjObj, 3, 1 ) != 0 ) )
	{
		printf( "Error caso 3: cambiar un valor por si mismo da 1, y fuera de rango 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	int iElim [ 2 ] = { 20, 30 };
	if ( ( SCnjIntEliminar ( p_cnjObj, 1 ) != 1 ) || ( EsConjunto ( p_cnjObj, iElim, 2 ) != BOOL_VAL_CIERTO ) ||
		 ( SCnjIntEliminar ( p_cnjObj, 2 ) != 0 ) )
	{
		printf( "Error caso 4: eliminar la posicion 1 deja { 20, 30 }; la 2 ya no existe\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SCnjIntVaciar ( p_cnjObj ) != 1 ) || ( SCnjIntEstaVacio ( p_cnjObj ) != 1 ) || ( SCnjIntInsertar ( p_cnjObj, 7 ) != 1 ) )
	{
		printf( "Error caso 5: vaciado queda vacio y se puede seguir usando\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCnjIntDestruir ( &p_cnjObj );
	return ( iRes );
}

static int TestSCnjIntParametros01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjIntParametros 01:\n" );

	SConjuntoEnteros * p_cnjObj = SCnjIntCrearConValores ( 4, -2, 7, 1 );
	SConjuntoEnteros * p_cnjVacio = SCnjIntCrear ();
	SConjuntoEnteros * p_cnjCero = SCnjIntCrearConValores ( 0, 3 );
	SConjuntoEnteros * p_cnjPos = SCnjIntCrearConValores ( 1, 3 );

	int iMin = 0;
	int iMax = 0;
	double dMed = 0.0;
	SCnjIntObtenerParametros ( p_cnjObj, &iMin, &iMax, &dMed );
	if ( ( SCnjIntMin ( p_cnjObj ) != -2 ) || ( SCnjIntMax ( p_cnjObj ) != 7 ) ||
		 ( iMin != -2 ) || ( iMax != 7 ) || ( dMed != 2.5 ) )
	{
		printf( "Error caso 1: minimo -2, maximo 7 y media 2.5: %d, %d, %g\n", iMin, iMax, dMed );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SCnjIntMin ( p_cnjVacio ) != INT_MAX ) || ( SCnjIntMax ( p_cnjVacio ) != INT_MIN ) )
	{
		printf( "Error caso 2: el vacio da INT_MAX e INT_MIN\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SCnjIntDefinidaPositiva ( p_cnjPos ) != 1 ) || ( SCnjIntSemidefinidaPositiva ( p_cnjPos ) != 1 ) ||
		 ( SCnjIntDefinidaPositiva ( p_cnjCero ) != 0 ) || ( SCnjIntSemidefinidaPositiva ( p_cnjCero ) != 1 ) ||
		 ( SCnjIntDefinidaPositiva ( p_cnjObj ) != 0 ) || ( SCnjIntSemidefinidaPositiva ( p_cnjObj ) != 0 ) ||
		 ( SCnjIntDefinidaPositiva ( p_cnjVacio ) != 1 ) || ( SCnjIntSemidefinidaPositiva ( p_cnjVacio ) != 1 ) )
	{
		printf( "Error caso 3: definida es todos > 0 y semidefinida todos >= 0; el vacio cumple las dos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	ErrLimpiar ();
	SCnjIntObtenerParametros ( p_cnjObj, NULL, &iMax, &dMed );
	if ( ErrCodigo () != ERR_PARAMETROS )
	{
		printf( "Error caso 4: sin donde dejar el minimo se esperaba ERR_PARAMETROS\n" );
		iRes = BOOL_VAL_FALSO;
	}
	ErrLimpiar ();
	SCnjIntDestruir ( &p_cnjObj );
	SCnjIntDestruir ( &p_cnjVacio );
	SCnjIntDestruir ( &p_cnjCero );
	SCnjIntDestruir ( &p_cnjPos );
	return ( iRes );
}

static int TestSCnjIntCrearDesde01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjIntCrearDesde 01:\n" );

	int iVal [ 6 ] = { 3, 1, 3, 0, -1, 1 };
	int iOrd [ 4 ] = { -1, 0, 1, 3 };
	SConjuntoEnteros * p_cnjVec = SCnjIntCrearDesdeVector ( iVal, 6 );
	if ( EsConjunto ( p_cnjVec, iOrd, 4 ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 1: desde { 3, 1, 3, 0, -1, 1 } se esperaba { -1, 0, 1, 3 }\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SConjuntoEnteros * p_cnjMacro = SCnjIntCrearConValores ( 3, 1, 3, 0, -1, 1 );
	if ( EsConjunto ( p_cnjMacro, iOrd, 4 ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 2: la macro deberia dar lo mismo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SConjuntoEnteros * p_cnjCero = SCnjIntCrearDesdeVector ( iVal, 0 );
	if ( ( SCnjIntEsValido ( p_cnjCero ) != 1 ) || ( SCnjIntEstaVacio ( p_cnjCero ) != 1 ) ||
		 ES_VALIDO ( SCnjIntCrearDesdeVector ( NULL, 2 ) ) || ES_VALIDO ( SCnjIntCrearDesdeVector ( iVal, -1 ) ) )
	{
		printf( "Error caso 3: con 0 valores, vacio; sin vector o con numero negativo, nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SListaEnteros * p_lisVal = CrearLista ( iVal, 6 );
	SConjuntoEnteros * p_cnjLis = SCnjIntCrearDesdeLista ( p_lisVal );
	if ( ( EsConjunto ( p_cnjLis, iOrd, 4 ) != BOOL_VAL_CIERTO ) || ( SLisIntNumElementos ( p_lisVal ) != 6 ) )
	{
		printf( "Error caso 4: desde la lista, { -1, 0, 1, 3 } y la lista intacta\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SListaEnteros * p_lisCopia = SCnjIntListaInt ( p_cnjLis );
	if ( ( SLisIntNumElementos ( p_lisCopia ) != 4 ) || ( SLisIntElemento ( p_lisCopia, 0 ) != -1 ) || ( SLisIntElemento ( p_lisCopia, 3 ) != 3 ) )
	{
		printf( "Error caso 5: ListaInt da una lista con los valores en orden\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisIntInsertarAlFinal ( p_lisCopia, 99 );
	if ( ( SCnjIntNumElementos ( p_cnjLis ) != 4 ) || ( SLisOrdNumElementos ( SCnjIntLista ( p_cnjLis ) ) != 4 ) ||
		 ( SCnjIntConjunto ( p_cnjLis ) != p_cnjLis->p_cnjDatos ) )
	{
		printf( "Error caso 6: la lista copiada no comparte nada con el conjunto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCnjIntDestruir ( &p_cnjVec );
	SCnjIntDestruir ( &p_cnjMacro );
	SCnjIntDestruir ( &p_cnjCero );
	SCnjIntDestruir ( &p_cnjLis );
	SLisIntDestruir ( &p_lisVal );
	SLisIntDestruir ( &p_lisCopia );
	return ( iRes );
}

static int TestSCnjIntConjuntos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjIntConjuntos 01:\n" );

	SConjuntoEnteros * p_cnjA = SCnjIntCrearConValores ( 1, 2, 3, 4 );
	SConjuntoEnteros * p_cnjB = SCnjIntCrearConValores ( 3, 4, 5 );
	SConjuntoEnteros * p_cnjC = SCnjIntCrearConValores ( 2, 3 );
	SConjuntoEnteros * p_cnjD = SCnjIntCrearConValores ( 8, 9 );

	if ( ( SCnjIntExistenTodos ( p_cnjA, p_cnjC ) != 1 ) || ( SCnjIntExistenTodos ( p_cnjA, p_cnjB ) != 0 ) ||
		 ( SCnjIntExisteAlguno ( p_cnjA, p_cnjB ) != 1 ) || ( SCnjIntExisteAlguno ( p_cnjA, p_cnjD ) != 0 ) )
	{
		printf( "Error caso 1: ExistenTodos y ExisteAlguno\n" );
		iRes = BOOL_VAL_FALSO;
	}
	int iUnion [ 5 ] = { 1, 2, 3, 4, 5 };
	int iInter [ 2 ] = { 3, 4 };
	int iDif [ 2 ] = { 1, 2 };
	SConjuntoEnteros * p_cnjUnion = SCnjIntUnion ( p_cnjA, p_cnjB );
	SConjuntoEnteros * p_cnjInter = SCnjIntInterseccion ( p_cnjA, p_cnjB );
	SConjuntoEnteros * p_cnjDif = SCnjIntDiferencia ( p_cnjA, p_cnjB );
	if ( EsConjunto ( p_cnjUnion, iUnion, 5 ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 2: la union es { 1, 2, 3, 4, 5 }, con lo comun una vez\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( EsConjunto ( p_cnjInter, iInter, 2 ) != BOOL_VAL_CIERTO ) || ( EsConjunto ( p_cnjDif, iDif, 2 ) != BOOL_VAL_CIERTO ) )
	{
		printf( "Error caso 3: interseccion { 3, 4 } y diferencia { 1, 2 }\n" );
		iRes = BOOL_VAL_FALSO;
	}
	int iA [ 4 ] = { 1, 2, 3, 4 };
	if ( EsConjunto ( p_cnjA, iA, 4 ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 4: union, interseccion y diferencia no tocan los de entrada\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Concatenar mete copias de lo que falta. */
	int iConc [ 6 ] = { 1, 2, 3, 4, 8, 9 };
	if ( ( SCnjIntConcatenar ( p_cnjA, p_cnjD ) != 1 ) || ( EsConjunto ( p_cnjA, iConc, 6 ) != BOOL_VAL_CIERTO ) ||
		 ( SCnjIntNumElementos ( p_cnjD ) != 2 ) )
	{
		printf( "Error caso 5: concatenar { 8, 9 } da { 1, 2, 3, 4, 8, 9 } sin tocar { 8, 9 }\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Extraer mueve: { 2, 3 } sale de A. */
	int iExt [ 2 ] = { 2, 3 };
	int iTrasExt [ 4 ] = { 1, 4, 8, 9 };
	SConjuntoEnteros * p_cnjExt = SCnjIntExtraerConjunto ( p_cnjA, p_cnjC );
	if ( ( EsConjunto ( p_cnjExt, iExt, 2 ) != BOOL_VAL_CIERTO ) || ( EsConjunto ( p_cnjA, iTrasExt, 4 ) != BOOL_VAL_CIERTO ) )
	{
		printf( "Error caso 6: extraer { 2, 3 } los saca de A\n" );
		iRes = BOOL_VAL_FALSO;
	}
	int iTrasElim [ 2 ] = { 1, 4 };
	if ( ( SCnjIntEliminarConjunto ( p_cnjA, p_cnjD ) != 1 ) || ( EsConjunto ( p_cnjA, iTrasElim, 2 ) != BOOL_VAL_CIERTO ) )
	{
		printf( "Error caso 7: eliminar { 8, 9 } deja { 1, 4 }\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SCnjIntUnion ( p_cnjA, NULL ) ) || ( SCnjIntExistenTodos ( NULL, p_cnjA ) != 0 ) || ( SCnjIntConcatenar ( p_cnjA, NULL ) != 0 ) )
	{
		printf( "Error caso 8: con un nulo, nulo o 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCnjIntDestruir ( &p_cnjA );
	SCnjIntDestruir ( &p_cnjB );
	SCnjIntDestruir ( &p_cnjC );
	SCnjIntDestruir ( &p_cnjD );
	SCnjIntDestruir ( &p_cnjUnion );
	SCnjIntDestruir ( &p_cnjInter );
	SCnjIntDestruir ( &p_cnjDif );
	SCnjIntDestruir ( &p_cnjExt );
	return ( iRes );
}

/* Las mismas operaciones con una lista, que puede traer repetidos. */
static int TestSCnjIntListas01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjIntListas 01:\n" );

	int iVal [ 4 ] = { 5, 3, 5, 7 };
	SListaEnteros * p_lisVal = CrearLista ( iVal, 4 );
	SConjuntoEnteros * p_cnjObj = SCnjIntCrearConValores ( 1, 3, 5 );

	if ( ( SCnjIntExistenTodosLista ( p_cnjObj, p_lisVal ) != 0 ) || ( SCnjIntExisteAlgunoLista ( p_cnjObj, p_lisVal ) != 1 ) )
	{
		printf( "Error caso 1: no estan todos (falta el 7) pero si alguno\n" );
		iRes = BOOL_VAL_FALSO;
	}
	int iUnion [ 4 ] = { 1, 3, 5, 7 };
	int iInter [ 2 ] = { 3, 5 };
	int iDif [ 1 ] = { 1 };
	SConjuntoEnteros * p_cnjUnion = SCnjIntUnionLista ( p_cnjObj, p_lisVal );
	SConjuntoEnteros * p_cnjInter = SCnjIntInterseccionLista ( p_cnjObj, p_lisVal );
	SConjuntoEnteros * p_cnjDif = SCnjIntDiferenciaLista ( p_cnjObj, p_lisVal );
	if ( ( EsConjunto ( p_cnjUnion, iUnion, 4 ) != BOOL_VAL_CIERTO ) || ( EsConjunto ( p_cnjInter, iInter, 2 ) != BOOL_VAL_CIERTO ) ||
		 ( EsConjunto ( p_cnjDif, iDif, 1 ) != BOOL_VAL_CIERTO ) )
	{
		printf( "Error caso 2: union { 1, 3, 5, 7 }, interseccion { 3, 5 } y diferencia { 1 }\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SCnjIntConcatenarLista ( p_cnjObj, p_lisVal ) != 1 ) || ( EsConjunto ( p_cnjObj, iUnion, 4 ) != BOOL_VAL_CIERTO ) ||
		 ( SLisIntNumElementos ( p_lisVal ) != 4 ) )
	{
		printf( "Error caso 3: concatenar la lista mete el 7 una vez y no la toca\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SConjuntoEnteros * p_cnjExt = SCnjIntExtraerLista ( p_cnjObj, p_lisVal );
	if ( ( SCnjIntNumElementos ( p_cnjExt ) != 3 ) || ( SCnjIntNumElementos ( p_cnjObj ) != 1 ) || ( SCnjIntElemento ( p_cnjObj, 0 ) != 1 ) )
	{
		printf( "Error caso 4: extraer la lista saca 3, 5 y 7 y deja { 1 }\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SCnjIntEliminarLista ( p_cnjExt, p_lisVal ) != 1 ) || ( SCnjIntEstaVacio ( p_cnjExt ) != 1 ) )
	{
		printf( "Error caso 5: eliminar la lista vacia el extraido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCnjIntDestruir ( &p_cnjObj );
	SCnjIntDestruir ( &p_cnjUnion );
	SCnjIntDestruir ( &p_cnjInter );
	SCnjIntDestruir ( &p_cnjDif );
	SCnjIntDestruir ( &p_cnjExt );
	SLisIntDestruir ( &p_lisVal );
	return ( iRes );
}



int TestSConjuntoEnteros ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SConjuntoEnteros]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSCnjIntCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjIntInsertar01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjIntModificarEliminar01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjIntParametros01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjIntCrearDesde01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjIntConjuntos01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjIntListas01 () == BOOL_VAL_CIERTO ) )
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
