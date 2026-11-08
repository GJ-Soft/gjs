#include "Base.h"

#include "SListaPtr.h"



/* Reserva un entero en memoria dinamica y devuelve su direccion como byte *.
   Como la SListaPtr tiene la liberacion activada por defecto, la lista pasa a
   ser la duena de estos datos y los libera ella al eliminar o destruir. */
static byte * CrearDatoEntero ( int iValor )
{
	int * p_iDato = (int *) MemReservar ( sizeof ( int ) );
	if ( ES_VALIDO ( p_iDato ) )
	{
		*p_iDato = iValor;
	}
	return ( (byte *) p_iDato );
}

static int VerificarContenido ( SListaPtr * p_lisObj, int * p_iEsperados, int iNum )
{
	int iRes = BOOL_VAL_CIERTO;

	if ( SLispNumElementos ( p_lisObj ) != iNum )
	{
		printf( "  Verificacion: se esperaban %d elementos: %d\n", iNum, SLispNumElementos ( p_lisObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	int iPos = 0;
	while ( ( iPos < iNum ) && ( iRes == BOOL_VAL_CIERTO ) )
	{
		byte * p_byDato = SLispElemento ( p_lisObj, iPos );
		if ( ES_NULO ( p_byDato ) )
		{
			printf( "  Verificacion: elemento nulo en la posicion %d\n", iPos );
			iRes = BOOL_VAL_FALSO;
		}
		else if ( *( (int *) p_byDato ) != p_iEsperados [ iPos ] )
		{
			printf( "  Verificacion: en pos %d se esperaba %d: %d\n", iPos, p_iEsperados [ iPos ], *( (int *) p_byDato ) );
			iRes = BOOL_VAL_FALSO;
		}
		iPos = iPos + 1;
	}
	return ( iRes );
}

/* Comprueba la cadena por dentro: que de p_elpPrimero se llega a p_elpUltimo en
   exactamente NumElementos pasos y que cada enlace hacia atras casa con el de
   hacia delante. VerificarContenido no basta: entra por el extremo mas cercano
   y una cadena partida por la mitad puede pasarla. */
static int VerificarCadena ( SListaPtr * p_lisObj )
{
	int iRes = BOOL_VAL_CIERTO;
	int iNum = 0;
	SElementoPtr * p_elpAnt = NULL;
	SElementoPtr * p_elpObj = p_lisObj->p_elpPrimero;

	while ( ES_VALIDO ( p_elpObj ) && ( iRes == BOOL_VAL_CIERTO ) )
	{
		if ( SElpAntecesor ( p_elpObj ) != p_elpAnt )
		{
			printf( "  Cadena: el enlace hacia atras del elemento %d no casa\n", iNum );
			iRes = BOOL_VAL_FALSO;
		}
		p_elpAnt = p_elpObj;
		p_elpObj = SElpSucesor ( p_elpObj );
		iNum = iNum + 1;
	}
	if ( iNum != SLispNumElementos ( p_lisObj ) )
	{
		printf( "  Cadena: se recorren %d elementos y la lista dice %d\n", iNum, SLispNumElementos ( p_lisObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( p_lisObj->p_elpUltimo != p_elpAnt )
	{
		printf( "  Cadena: el ultimo de la lista no es el final de la cadena\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static SListaPtr * CrearListaEnteros ( int * p_iValores, int iNum )
{
	SListaPtr * p_lisObj = SLispCrear ();
	int iPos = 0;
	while ( ES_VALIDO ( p_lisObj ) && ( iPos < iNum ) )
	{
		SLispInsertarAlFinal ( p_lisObj, CrearDatoEntero ( p_iValores [ iPos ] ) );
		iPos = iPos + 1;
	}
	return ( p_lisObj );
}

static int SonIgualesEnteros ( byte * p_byDato1, byte * p_byDato2 )
{
	return ( ( *( (int *) p_byDato1 ) == *( (int *) p_byDato2 ) ) ? 1 : 0 );
}

/* Igualdad "modulo 10": con ella 12 y 2 son iguales y por bytes no, asi que
   distingue de verdad las Ext de las que comparan memoria. */
static int SonIgualesMod10 ( byte * p_byDato1, byte * p_byDato2 )
{
	return ( ( ( *( (int *) p_byDato1 ) % 10 ) == ( *( (int *) p_byDato2 ) % 10 ) ) ? 1 : 0 );
}

/* Duplica sumando 100, para ver en el resultado que la copia la hizo ella. */
static byte * DuplicarEnteroMas100 ( byte * p_byDato )
{
	return ( CrearDatoEntero ( *( (int *) p_byDato ) + 100 ) );
}



static int TestSLispCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLispCrear 01:\n" );

	SListaPtr * p_lisObj = SLispCrear ();
	if ( ES_NULO ( p_lisObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SLispEsValida ( p_lisObj ) != 1 )
		{
			printf( "Error caso 2: la lista recien creada deberia ser valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLispEstaVacia ( p_lisObj ) != 1 )
		{
			printf( "Error caso 3: la lista recien creada deberia estar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Por defecto la lista gestiona la memoria de sus datos. */
		if ( SLispLiberacionMemoriaActivada ( p_lisObj ) != 1 )
		{
			printf( "Error caso 4: la liberacion de memoria deberia estar activada por defecto\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SLispDestruir ( &p_lisObj );

	if ( ES_VALIDO ( p_lisObj ) )
	{
		printf( "Error caso 5: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSLispInsertar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLispInsertar 01:\n" );

	SListaPtr * p_lisObj = SLispCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		SLispInsertarAlFinal ( p_lisObj, CrearDatoEntero ( 10 ) );
		SLispInsertarAlFinal ( p_lisObj, CrearDatoEntero ( 20 ) );
		SLispInsertarAlFinal ( p_lisObj, CrearDatoEntero ( 30 ) );

		int iEsp1 [ 3 ] = { 10, 20, 30 };
		if ( VerificarContenido ( p_lisObj, iEsp1, 3 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 1: contenido incorrecto tras insertar al final\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Insertar en medio ( detras del indice 0 ). */
		if ( SLispInsertarElem ( p_lisObj, 0, CrearDatoEntero ( 15 ) ) != 1 )
		{
			printf( "Error caso 2: se esperaba resultado 1 al insertar en medio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		int iEsp2 [ 4 ] = { 10, 15, 20, 30 };
		if ( VerificarContenido ( p_lisObj, iEsp2, 4 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 3: contenido incorrecto tras insertar en medio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Insertar al inicio. */
		SLispInsertarAlInicio ( p_lisObj, CrearDatoEntero ( 5 ) );
		if ( *( (int *) SLispElemento ( p_lisObj, 0 ) ) != 5 )
		{
			printf( "Error caso 4: el primer elemento deberia ser el 5\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLispDestruir ( &p_lisObj );
	return ( iRes );
}

static int TestSLispCursor01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLispCursor 01:\n" );

	SListaPtr * p_lisObj = SLispCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		SLispInsertarAlFinal ( p_lisObj, CrearDatoEntero ( 10 ) );
		SLispInsertarAlFinal ( p_lisObj, CrearDatoEntero ( 20 ) );
		SLispInsertarAlFinal ( p_lisObj, CrearDatoEntero ( 30 ) );

		SLispInicio ( p_lisObj );
		if ( ( SLispPosicion ( p_lisObj ) != 0 ) || ( *( (int *) SLispActual ( p_lisObj ) ) != 10 ) )
		{
			printf( "Error caso 1: el inicio deberia situar el cursor en el 10\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLispSiguiente ( p_lisObj );
		if ( *( (int *) SLispActual ( p_lisObj ) ) != 20 )
		{
			printf( "Error caso 2: el siguiente deberia situar el cursor en el 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLispFinal ( p_lisObj );
		if ( ( *( (int *) SLispActual ( p_lisObj ) ) != 30 ) || ( SLispEstaEnFinal ( p_lisObj ) != 1 ) )
		{
			printf( "Error caso 3: el final deberia situar el cursor en el 30\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLispAnterior ( p_lisObj );
		if ( *( (int *) SLispActual ( p_lisObj ) ) != 20 )
		{
			printf( "Error caso 4: el anterior deberia situar el cursor en el 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLispDestruir ( &p_lisObj );
	return ( iRes );
}

static int TestSLispBuscar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLispBuscar 01:\n" );

	SListaPtr * p_lisObj = SLispCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		SLispInsertarAlFinal ( p_lisObj, CrearDatoEntero ( 10 ) );
		SLispInsertarAlFinal ( p_lisObj, CrearDatoEntero ( 20 ) );
		SLispInsertarAlFinal ( p_lisObj, CrearDatoEntero ( 30 ) );

		int iBuscar = 20;
		if ( SLispBuscar ( p_lisObj, (byte *) &iBuscar, sizeof ( int ) ) != 1 )
		{
			printf( "Error caso 1: el 20 deberia estar en la posicion 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		iBuscar = 99;
		if ( SLispBuscar ( p_lisObj, (byte *) &iBuscar, sizeof ( int ) ) != -1 )
		{
			printf( "Error caso 2: el 99 no deberia encontrarse\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLispDestruir ( &p_lisObj );
	return ( iRes );
}

/* Recorre los repetidos con BuscarPrimero / BuscarSiguiente, por bytes, con
   fSonIguales y con un elemento, con el cursor quieto y sin el: sin cursor, a
   partir de la mitad se entra por el final. */
static int TestSLispBuscarSiguiente01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLispBuscarSiguiente 01:\n" );

	int iVal [ 6 ] = { 20, 11, 20, 30, 20, 41 };
	int iVeinte = 20;
	int iUno = 1;
	SListaPtr * p_lisObj = CrearListaEnteros ( iVal, 6 );
	SElementoPtr * p_elp20 = SElpCrear ( CrearDatoEntero ( 20 ), 1 );
	SElementoPtr * p_elp1 = SElpCrear ( CrearDatoEntero ( 1 ), 1 );
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_elp20 ) && ES_VALIDO ( p_elp1 ) )
	{
		SLispDeposicionar ( p_lisObj );
		if ( ( SLispBuscarPrimero ( p_lisObj, (byte *) &iVeinte, sizeof ( int ) ) != 0 ) ||
			 ( SLispBuscarSiguiente ( p_lisObj, (byte *) &iVeinte, 0, sizeof ( int ) ) != 2 ) ||
			 ( SLispBuscarSiguiente ( p_lisObj, (byte *) &iVeinte, 2, sizeof ( int ) ) != 4 ) ||
			 ( SLispBuscarSiguiente ( p_lisObj, (byte *) &iVeinte, 4, sizeof ( int ) ) != -1 ) )
		{
			printf( "Error caso 1: sin cursor el 20 deberia estar en 0, 2 y 4\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLispBuscarPrimeroPtr ( p_lisObj, p_elp20, sizeof ( int ) ) != 0 ) ||
			 ( SLispBuscarSiguientePtr ( p_lisObj, p_elp20, 0, sizeof ( int ) ) != 2 ) ||
			 ( SLispBuscarSiguientePtr ( p_lisObj, p_elp20, 2, sizeof ( int ) ) != 4 ) ||
			 ( SLispBuscarSiguientePtr ( p_lisObj, p_elp20, 4, sizeof ( int ) ) != -1 ) )
		{
			printf( "Error caso 2: por elemento el 20 deberia estar en 0, 2 y 4\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Modulo 10 el 1 casa con el 11 y con el 41; por bytes no esta. */
		if ( ( SLispBuscarPrimeroExt ( p_lisObj, (byte *) &iUno, SonIgualesMod10 ) != 1 ) ||
			 ( SLispBuscarSiguienteExt ( p_lisObj, (byte *) &iUno, 1, SonIgualesMod10 ) != 5 ) ||
			 ( SLispBuscarSiguienteExt ( p_lisObj, (byte *) &iUno, 3, SonIgualesMod10 ) != 5 ) ||
			 ( SLispBuscarSiguienteExt ( p_lisObj, (byte *) &iUno, 5, SonIgualesMod10 ) != -1 ) ||
			 ( SLispBuscarPrimero ( p_lisObj, (byte *) &iUno, sizeof ( int ) ) != -1 ) )
		{
			printf( "Error caso 3: modulo 10 el 1 deberia estar en 1 y 5\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLispBuscarPrimeroExtPtr ( p_lisObj, p_elp1, SonIgualesMod10 ) != 1 ) ||
			 ( SLispBuscarSiguienteExtPtr ( p_lisObj, p_elp1, 1, SonIgualesMod10 ) != 5 ) ||
			 ( SLispBuscarSiguienteExtPtr ( p_lisObj, p_elp1, 5, SonIgualesMod10 ) != -1 ) )
		{
			printf( "Error caso 4: modulo 10 por elemento el 1 deberia estar en 1 y 5\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Desde la posicion siguiente, no desde la misma. */
		if ( ( SLispBuscarSiguiente ( p_lisObj, (byte *) &iVeinte, 1, sizeof ( int ) ) != 2 ) ||
			 ( SLispBuscarSiguiente ( p_lisObj, (byte *) &iVeinte, 3, sizeof ( int ) ) != 4 ) )
		{
			printf( "Error caso 5: detras de la 1 el 20 esta en la 2, y detras de la 3 en la 4\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Con el cursor en la 4 se parte de el, hacia atras y hacia delante, y no se mueve. */
		SLispMoverA ( p_lisObj, 4 );
		if ( ( SLispBuscarPrimero ( p_lisObj, (byte *) &iVeinte, sizeof ( int ) ) != 0 ) ||
			 ( SLispBuscarSiguiente ( p_lisObj, (byte *) &iVeinte, 0, sizeof ( int ) ) != 2 ) ||
			 ( SLispBuscarSiguiente ( p_lisObj, (byte *) &iVeinte, 2, sizeof ( int ) ) != 4 ) ||
			 ( SLispBuscarSiguienteExt ( p_lisObj, (byte *) &iUno, 1, SonIgualesMod10 ) != 5 ) ||
			 ( SLispPosicion ( p_lisObj ) != 4 ) )
		{
			printf( "Error caso 6: con el cursor en la 4 se esperaba lo mismo y el cursor quieto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLispBuscar ( p_lisObj, (byte *) &iVeinte, sizeof ( int ) ) != 0 ) ||
			 ( SLispBuscarPtr ( p_lisObj, p_elp20, sizeof ( int ) ) != 0 ) ||
			 ( SLispBuscarExt ( p_lisObj, (byte *) &iUno, SonIgualesMod10 ) != 1 ) ||
			 ( SLispBuscarExtPtr ( p_lisObj, p_elp1, SonIgualesMod10 ) != 1 ) )
		{
			printf( "Error caso 7: Buscar deberia ser BuscarPrimero\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLispBuscarSiguiente ( p_lisObj, (byte *) &iVeinte, 5, sizeof ( int ) ) != -1 ) ||
			 ( SLispBuscarSiguiente ( p_lisObj, (byte *) &iVeinte, 6, sizeof ( int ) ) != -1 ) ||
			 ( SLispBuscarSiguiente ( p_lisObj, (byte *) &iVeinte, -2, sizeof ( int ) ) != -1 ) )
		{
			printf( "Error caso 8: desde el final o con una posicion menor que -1 se esperaba -1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLispBuscarSiguiente ( NULL, (byte *) &iVeinte, -1, sizeof ( int ) ) != -1 ) ||
			 ( SLispBuscarSiguiente ( p_lisObj, NULL, -1, sizeof ( int ) ) != -1 ) ||
			 ( SLispBuscarSiguientePtr ( p_lisObj, NULL, -1, sizeof ( int ) ) != -1 ) ||
			 ( SLispBuscarSiguienteExt ( p_lisObj, (byte *) &iUno, -1, NULL ) != -1 ) ||
			 ( SLispBuscarSiguienteExtPtr ( p_lisObj, NULL, -1, SonIgualesMod10 ) != -1 ) ||
			 ( SLispBuscarPrimeroExtPtr ( p_lisObj, p_elp1, NULL ) != -1 ) )
		{
			printf( "Error caso 9: con un nulo se esperaba -1\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear la lista o los elementos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SElpDestruir ( &p_elp20 );
	SElpDestruir ( &p_elp1 );
	SLispDestruir ( &p_lisObj );
	return ( iRes );
}

/* Existe y Repeticiones, por bytes y con fSonIguales, con un dato y con un
   elemento. */
static int TestSLispRepeticiones01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLispRepeticiones 01:\n" );

	int iVal [ 6 ] = { 20, 11, 20, 30, 20, 41 };
	int iVeinte = 20;
	int iCero = 0;
	int iNueve = 9;
	SListaPtr * p_lisObj = CrearListaEnteros ( iVal, 6 );
	SListaPtr * p_lisVacia = SLispCrear ();
	SElementoPtr * p_elp20 = SElpCrear ( CrearDatoEntero ( 20 ), 1 );
	SElementoPtr * p_elp0 = SElpCrear ( CrearDatoEntero ( 0 ), 1 );
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisVacia ) && ES_VALIDO ( p_elp20 ) && ES_VALIDO ( p_elp0 ) )
	{
		if ( ( SLispRepeticiones ( p_lisObj, (byte *) &iVeinte, sizeof ( int ) ) != 3 ) ||
			 ( SLispRepeticionesPtr ( p_lisObj, p_elp20, sizeof ( int ) ) != 3 ) ||
			 ( SLispExiste ( p_lisObj, (byte *) &iVeinte, sizeof ( int ) ) != 1 ) ||
			 ( SLispExistePtr ( p_lisObj, p_elp20, sizeof ( int ) ) != 1 ) )
		{
			printf( "Error caso 1: por bytes el 20 deberia estar 3 veces\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Modulo 10 el 0 casa con los tres 20 y con el 30; por bytes no esta. */
		if ( ( SLispRepeticionesExt ( p_lisObj, (byte *) &iCero, SonIgualesMod10 ) != 4 ) ||
			 ( SLispRepeticionesExtPtr ( p_lisObj, p_elp0, SonIgualesMod10 ) != 4 ) ||
			 ( SLispExisteExt ( p_lisObj, (byte *) &iCero, SonIgualesMod10 ) != 1 ) ||
			 ( SLispExisteExtPtr ( p_lisObj, p_elp0, SonIgualesMod10 ) != 1 ) ||
			 ( SLispRepeticiones ( p_lisObj, (byte *) &iCero, sizeof ( int ) ) != 0 ) ||
			 ( SLispExistePtr ( p_lisObj, p_elp0, sizeof ( int ) ) != 0 ) )
		{
			printf( "Error caso 2: modulo 10 el 0 deberia estar 4 veces, y por bytes ninguna\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLispRepeticionesExt ( p_lisObj, (byte *) &iNueve, SonIgualesMod10 ) != 0 ) ||
			 ( SLispExisteExt ( p_lisObj, (byte *) &iNueve, SonIgualesMod10 ) != 0 ) )
		{
			printf( "Error caso 3: el 9 no deberia estar ni modulo 10\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLispRepeticionesPtr ( p_lisVacia, p_elp20, sizeof ( int ) ) != 0 ) ||
			 ( SLispExisteExtPtr ( p_lisVacia, p_elp0, SonIgualesMod10 ) != 0 ) )
		{
			printf( "Error caso 4: en una lista vacia no deberia estar nada\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLispRepeticiones ( NULL, (byte *) &iVeinte, sizeof ( int ) ) != 0 ) ||
			 ( SLispRepeticiones ( p_lisObj, NULL, sizeof ( int ) ) != 0 ) ||
			 ( SLispRepeticionesPtr ( p_lisObj, NULL, sizeof ( int ) ) != 0 ) ||
			 ( SLispRepeticionesExt ( p_lisObj, (byte *) &iCero, NULL ) != 0 ) ||
			 ( SLispRepeticionesExtPtr ( p_lisObj, NULL, SonIgualesMod10 ) != 0 ) ||
			 ( SLispExiste ( NULL, (byte *) &iVeinte, sizeof ( int ) ) != 0 ) ||
			 ( SLispExistePtr ( p_lisObj, NULL, sizeof ( int ) ) != 0 ) ||
			 ( SLispExisteExt ( p_lisObj, (byte *) &iCero, NULL ) != 0 ) ||
			 ( SLispExisteExtPtr ( p_lisObj, NULL, SonIgualesMod10 ) != 0 ) )
		{
			printf( "Error caso 5: con un nulo se esperaba 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas o los elementos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SElpDestruir ( &p_elp20 );
	SElpDestruir ( &p_elp0 );
	SLispDestruir ( &p_lisObj );
	SLispDestruir ( &p_lisVacia );
	return ( iRes );
}

static int TestSLispEliminar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLispEliminar 01:\n" );

	SListaPtr * p_lisObj = SLispCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		SLispInsertarAlFinal ( p_lisObj, CrearDatoEntero ( 10 ) );
		SLispInsertarAlFinal ( p_lisObj, CrearDatoEntero ( 20 ) );
		SLispInsertarAlFinal ( p_lisObj, CrearDatoEntero ( 30 ) );

		/* Al eliminar, la lista libera el dato ( liberacion activada ). */
		SLispEliminarElem ( p_lisObj, 1 );
		int iEsp [ 2 ] = { 10, 30 };
		if ( VerificarContenido ( p_lisObj, iEsp, 2 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 1: contenido incorrecto tras eliminar el elemento 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLispVaciar ( p_lisObj ) != 1 )
		{
			printf( "Error caso 2: se esperaba resultado 1 al vaciar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLispEstaVacia ( p_lisObj ) != 1 )
		{
			printf( "Error caso 3: la lista deberia quedar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLispDestruir ( &p_lisObj );
	return ( iRes );
}

static int TestSLispInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLispInvalidos 01:\n" );

	if ( SLispEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: una lista nula no deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLispNumElementos ( NULL ) != 0 )
	{
		printf( "Error caso 2: el numero de elementos de una lista nula deberia ser 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLispEstaVacia ( NULL ) != 1 )
	{
		printf( "Error caso 3: una lista nula deberia considerarse vacia\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SListaPtr * p_lisNula = NULL;
	SLispDestruir ( &p_lisNula );
	return ( iRes );
}

/* El cursor sobre una lista nula: antes escribia en p_lisObj->iPos y reventaba. */
static int TestSLispCursorNulo01 ()
{
	printf( "Test SLispCursorNulo 01:\n" );
	SLispInicio ( NULL );
	SLispFinal ( NULL );
	SLispSiguiente ( NULL );
	SLispAnterior ( NULL );
	SLispMoverA ( NULL, 0 );
	return ( BOOL_VAL_CIERTO );
}

static int TestSLispExtraer01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLispExtraer 01:\n" );

	int iVal [ 4 ] = { 10, 20, 30, 40 };
	SListaPtr * p_lisObj = CrearListaEnteros ( iVal, 4 );
	if ( ES_VALIDO ( p_lisObj ) )
	{
		/* Del medio: era el caso que partia la cadena en dos. */
		byte * p_byDato = SLispExtraerElem ( p_lisObj, 1 );
		if ( ES_NULO ( p_byDato ) || ( *( (int *) p_byDato ) != 20 ) )
		{
			printf( "Error caso 1: se esperaba extraer el 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
		MemLiberar ( (void **) &p_byDato );
		int iEsp1 [ 3 ] = { 10, 30, 40 };
		if ( ( VerificarContenido ( p_lisObj, iEsp1, 3 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarCadena ( p_lisObj ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 2: la lista deberia quedar { 10, 30, 40 } y entera\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Por el cursor: queda en el sucesor del extraido. */
		SLispMoverA ( p_lisObj, 1 );
		p_byDato = SLispExtraer ( p_lisObj );
		if ( ES_NULO ( p_byDato ) || ( *( (int *) p_byDato ) != 30 ) )
		{
			printf( "Error caso 3: se esperaba extraer el 30\n" );
			iRes = BOOL_VAL_FALSO;
		}
		MemLiberar ( (void **) &p_byDato );
		if ( ( SLispPosicion ( p_lisObj ) != 1 ) || ( ES_NULO ( SLispActual ( p_lisObj ) ) ) ||
			 ( *( (int *) SLispActual ( p_lisObj ) ) != 40 ) )
		{
			printf( "Error caso 4: el cursor deberia quedar en el 40, posicion 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		int iEsp2 [ 2 ] = { 10, 40 };
		if ( ( VerificarContenido ( p_lisObj, iEsp2, 2 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarCadena ( p_lisObj ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 5: la lista deberia quedar { 10, 40 } y entera\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Fuera de rango no se extrae nada. */
		if ( ES_VALIDO ( SLispExtraerElem ( p_lisObj, 5 ) ) )
		{
			printf( "Error caso 6: fuera de rango se esperaba nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* El ultimo y luego el unico: la lista vacia tiene que seguir siendo valida. */
		p_byDato = SLispExtraerElem ( p_lisObj, 1 );
		MemLiberar ( (void **) &p_byDato );
		p_byDato = SLispExtraerElem ( p_lisObj, 0 );
		if ( ES_NULO ( p_byDato ) || ( *( (int *) p_byDato ) != 10 ) )
		{
			printf( "Error caso 7: se esperaba extraer el 10\n" );
			iRes = BOOL_VAL_FALSO;
		}
		MemLiberar ( (void **) &p_byDato );
		if ( ( SLispEstaVacia ( p_lisObj ) != 1 ) || ( SLispEsValida ( p_lisObj ) != 1 ) )
		{
			printf( "Error caso 8: la lista deberia quedar vacia y valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLispDestruir ( &p_lisObj );
	return ( iRes );
}

static int TestSLispBuscarExt01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLispBuscarExt 01:\n" );

	int iVal [ 3 ] = { 12, 25, 33 };
	SListaPtr * p_lisObj = CrearListaEnteros ( iVal, 3 );
	SElementoPtr * p_elp33 = SElpCrear ( CrearDatoEntero ( 33 ), 1 );
	SElementoPtr * p_elp3 = SElpCrear ( CrearDatoEntero ( 3 ), 1 );
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_elp33 ) && ES_VALIDO ( p_elp3 ) )
	{
		int iBuscar = 22;
		if ( SLispBuscarExt ( p_lisObj, (byte *) &iBuscar, SonIgualesMod10 ) != 0 )
		{
			printf( "Error caso 1: modulo 10, el 22 casa con el 12 de la posicion 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		iBuscar = 5;
		if ( SLispBuscarExt ( p_lisObj, (byte *) &iBuscar, SonIgualesMod10 ) != 1 )
		{
			printf( "Error caso 2: modulo 10, el 5 casa con el 25 de la posicion 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		iBuscar = 9;
		if ( SLispBuscarExt ( p_lisObj, (byte *) &iBuscar, SonIgualesMod10 ) != -1 )
		{
			printf( "Error caso 3: el 9 no deberia encontrarse\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLispBuscarPtr ( p_lisObj, p_elp33, sizeof ( int ) ) != 2 )
		{
			printf( "Error caso 4: el elemento 33 deberia estar en la posicion 2\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLispBuscarPtr ( p_lisObj, p_elp3, sizeof ( int ) ) != -1 )
		{
			printf( "Error caso 5: por bytes, el 3 no esta\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLispBuscarExtPtr ( p_lisObj, p_elp3, SonIgualesMod10 ) != 2 )
		{
			printf( "Error caso 6: modulo 10, el elemento 3 casa con el 33 de la posicion 2\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLispBuscarExt ( p_lisObj, (byte *) &iBuscar, NULL ) != -1 )
		{
			printf( "Error caso 7: sin funcion de comparacion se esperaba -1\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear la lista o los elementos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SElpDestruir ( &p_elp33 );
	SElpDestruir ( &p_elp3 );
	SLispDestruir ( &p_lisObj );
	return ( iRes );
}

/* Los casos estan elegidos contra los dos defectos que tuvo: tomar el
   resultado de SLispBuscar ( posicion o -1 ) como booleano, que fallaba con un
   valor en la posicion 0, y parar el recorrido antes del ULTIMO valor. */
static int TestSLispExisten01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLispExisten 01:\n" );

	int iVal [ 3 ] = { 10, 20, 30 };
	int iV1 [ 2 ] = { 10, 30 };
	int iV2 [ 2 ] = { 10, 99 };
	int iV3 [ 2 ] = { 99, 30 };
	int iV4 [ 2 ] = { 98, 99 };
	SListaPtr * p_lisObj = CrearListaEnteros ( iVal, 3 );
	SListaPtr * p_lis1 = CrearListaEnteros ( iV1, 2 );
	SListaPtr * p_lis2 = CrearListaEnteros ( iV2, 2 );
	SListaPtr * p_lis3 = CrearListaEnteros ( iV3, 2 );
	SListaPtr * p_lis4 = CrearListaEnteros ( iV4, 2 );
	SListaPtr * p_lisVacia = SLispCrear ();
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lis1 ) && ES_VALIDO ( p_lis2 ) &&
		 ES_VALIDO ( p_lis3 ) && ES_VALIDO ( p_lis4 ) && ES_VALIDO ( p_lisVacia ) )
	{
		if ( SLispExistenTodos ( p_lisObj, p_lis1, sizeof ( int ) ) != 1 )
		{
			printf( "Error caso 1: { 10, 30 } estan todos en { 10, 20, 30 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLispExistenTodos ( p_lisObj, p_lis2, sizeof ( int ) ) != 0 )
		{
			printf( "Error caso 2: en { 10, 99 } falta el 99\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLispExisteAlguno ( p_lisObj, p_lis2, sizeof ( int ) ) != 1 )
		{
			printf( "Error caso 3: de { 10, 99 } esta el 10, en la posicion 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLispExisteAlguno ( p_lisObj, p_lis3, sizeof ( int ) ) != 1 )
		{
			printf( "Error caso 4: de { 99, 30 } esta el 30, el ultimo de los valores\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLispExisteAlguno ( p_lisObj, p_lis4, sizeof ( int ) ) != 0 ) ||
			 ( SLispExistenTodos ( p_lisObj, p_lis4, sizeof ( int ) ) != 0 ) )
		{
			printf( "Error caso 5: de { 98, 99 } no esta ninguno\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLispExistenTodos ( p_lisObj, p_lisVacia, sizeof ( int ) ) != 1 ) ||
			 ( SLispExisteAlguno ( p_lisObj, p_lisVacia, sizeof ( int ) ) != 0 ) )
		{
			printf( "Error caso 6: con valores vacios, Todos da 1 y Alguno 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLispExistenTodos ( NULL, p_lis1, sizeof ( int ) ) != 0 ) ||
			 ( SLispExisteAlguno ( p_lisObj, NULL, sizeof ( int ) ) != 0 ) )
		{
			printf( "Error caso 7: con listas nulas se esperaba 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Las consultas no mueven el cursor de los valores. */
		SLispMoverA ( p_lis1, 1 );
		SLispExistenTodos ( p_lisObj, p_lis1, sizeof ( int ) );
		if ( SLispPosicion ( p_lis1 ) != 1 )
		{
			printf( "Error caso 8: el cursor de los valores deberia seguir en 1: %d\n", SLispPosicion ( p_lis1 ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLispDestruir ( &p_lisObj );
	SLispDestruir ( &p_lis1 );
	SLispDestruir ( &p_lis2 );
	SLispDestruir ( &p_lis3 );
	SLispDestruir ( &p_lis4 );
	SLispDestruir ( &p_lisVacia );
	return ( iRes );
}

static int TestSLispExistenExt01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLispExistenExt 01:\n" );

	int iVal [ 2 ] = { 12, 25 };
	int iV1 [ 2 ] = { 2, 5 };
	int iV2 [ 2 ] = { 7, 15 };
	SListaPtr * p_lisObj = CrearListaEnteros ( iVal, 2 );
	SListaPtr * p_lis1 = CrearListaEnteros ( iV1, 2 );
	SListaPtr * p_lis2 = CrearListaEnteros ( iV2, 2 );
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lis1 ) && ES_VALIDO ( p_lis2 ) )
	{
		if ( SLispExistenTodos ( p_lisObj, p_lis1, sizeof ( int ) ) != 0 )
		{
			printf( "Error caso 1: por bytes, { 2, 5 } no estan en { 12, 25 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLispExistenTodosExt ( p_lisObj, p_lis1, SonIgualesMod10 ) != 1 )
		{
			printf( "Error caso 2: modulo 10, { 2, 5 } estan todos en { 12, 25 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLispExistenTodosExt ( p_lisObj, p_lis2, SonIgualesMod10 ) != 0 )
		{
			printf( "Error caso 3: modulo 10, en { 7, 15 } falta el 7\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLispExisteAlgunoExt ( p_lisObj, p_lis2, SonIgualesMod10 ) != 1 )
		{
			printf( "Error caso 4: modulo 10, de { 7, 15 } esta el 15\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLispExistenTodosExt ( p_lisObj, p_lis1, NULL ) != 0 ) ||
			 ( SLispExisteAlgunoExt ( p_lisObj, p_lis1, NULL ) != 0 ) )
		{
			printf( "Error caso 5: sin funcion de comparacion se esperaba 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLispDestruir ( &p_lisObj );
	SLispDestruir ( &p_lis1 );
	SLispDestruir ( &p_lis2 );
	return ( iRes );
}

static int TestSLispInsertarLista01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLispInsertarLista 01:\n" );

	int iDest [ 2 ] = { 1, 2 };
	int iVal [ 3 ] = { 7, 8, 9 };
	SListaPtr * p_lisObj = CrearListaEnteros ( iDest, 2 );
	SListaPtr * p_lisVal = CrearListaEnteros ( iVal, 3 );
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisVal ) )
	{
		/* Detras del cursor, en su orden. */
		SLispMoverA ( p_lisObj, 0 );
		if ( SLispInsertarLista ( p_lisObj, p_lisVal ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al insertar la lista\n" );
			iRes = BOOL_VAL_FALSO;
		}
		int iEsp1 [ 5 ] = { 1, 7, 8, 9, 2 };
		if ( ( VerificarContenido ( p_lisObj, iEsp1, 5 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarCadena ( p_lisObj ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 2: se esperaba { 1, 7, 8, 9, 2 } y la cadena entera\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Mover deja la de valores vacia, pero valida y reutilizable. */
		if ( ( SLispEstaVacia ( p_lisVal ) != 1 ) || ( SLispEsValida ( p_lisVal ) != 1 ) )
		{
			printf( "Error caso 3: la lista de valores deberia quedar vacia y valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Concatenar va al final, este donde este el cursor. */
		SLispInsertarAlFinal ( p_lisVal, CrearDatoEntero ( 5 ) );
		SLispInsertarAlFinal ( p_lisVal, CrearDatoEntero ( 6 ) );
		SLispMoverA ( p_lisObj, 1 );
		if ( SLispConcatenarLista ( p_lisObj, p_lisVal ) != 1 )
		{
			printf( "Error caso 4: se esperaba resultado 1 al concatenar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		int iEsp2 [ 7 ] = { 1, 7, 8, 9, 2, 5, 6 };
		if ( ( VerificarContenido ( p_lisObj, iEsp2, 7 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarCadena ( p_lisObj ) != BOOL_VAL_CIERTO ) ||
			 ( SLispEstaVacia ( p_lisVal ) != 1 ) )
		{
			printf( "Error caso 5: se esperaba { 1, 7, 8, 9, 2, 5, 6 } y los valores vacios\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Sin cursor en un destino no vacio no se puede insertar: no se pierde nada. */
		SLispInsertarAlFinal ( p_lisVal, CrearDatoEntero ( 3 ) );
		SLispInsertarAlFinal ( p_lisVal, CrearDatoEntero ( 4 ) );
		SLispDeposicionar ( p_lisObj );
		if ( SLispInsertarLista ( p_lisObj, p_lisVal ) != 0 )
		{
			printf( "Error caso 6: sin cursor se esperaba resultado 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		int iEsp3 [ 2 ] = { 3, 4 };
		if ( ( VerificarContenido ( p_lisVal, iEsp3, 2 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarCadena ( p_lisVal ) != BOOL_VAL_CIERTO ) ||
			 ( SLispNumElementos ( p_lisObj ) != 7 ) )
		{
			printf( "Error caso 7: al fallar, los valores deberian seguir { 3, 4 } y el destino con 7\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* La misma lista en los dos lados se rechaza sin tocarla. */
		if ( ( SLispConcatenarLista ( p_lisObj, p_lisObj ) != 0 ) ||
			 ( SLispInsertarLista ( p_lisObj, p_lisObj ) != 0 ) ||
			 ( SLispNumElementos ( p_lisObj ) != 7 ) )
		{
			printf( "Error caso 8: con la misma lista se esperaba 0 y la lista intacta\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLispDestruir ( &p_lisObj );
	SLispDestruir ( &p_lisVal );
	return ( iRes );
}

static int TestSLispListaDup01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLispListaDup 01:\n" );

	int iDest [ 2 ] = { 1, 2 };
	int iVal [ 2 ] = { 7, 8 };
	SListaPtr * p_lisObj = CrearListaEnteros ( iDest, 2 );
	SListaPtr * p_lisVal = CrearListaEnteros ( iVal, 2 );
	SListaPtr * p_lisExt = SLispCrear ();
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisVal ) && ES_VALIDO ( p_lisExt ) )
	{
		SLispMoverA ( p_lisObj, 0 );
		if ( SLispInsertarListaDup ( p_lisObj, p_lisVal, sizeof ( int ) ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al insertar copias\n" );
			iRes = BOOL_VAL_FALSO;
		}
		int iEsp1 [ 4 ] = { 1, 7, 8, 2 };
		if ( ( VerificarContenido ( p_lisObj, iEsp1, 4 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarCadena ( p_lisObj ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 2: se esperaba { 1, 7, 8, 2 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLispConcatenarListaDup ( p_lisObj, p_lisVal, sizeof ( int ) ) != 1 )
		{
			printf( "Error caso 3: se esperaba resultado 1 al concatenar copias\n" );
			iRes = BOOL_VAL_FALSO;
		}
		int iEsp2 [ 6 ] = { 1, 7, 8, 2, 7, 8 };
		if ( VerificarContenido ( p_lisObj, iEsp2, 6 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 4: se esperaba { 1, 7, 8, 2, 7, 8 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Las de valores no se tocan, y las copias son bloques propios. */
		if ( ( VerificarContenido ( p_lisVal, iVal, 2 ) != BOOL_VAL_CIERTO ) ||
			 ( SLispElemento ( p_lisObj, 1 ) == SLispElemento ( p_lisVal, 0 ) ) )
		{
			printf( "Error caso 5: los valores deberian quedar intactos y sin compartir datos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLispConcatenarListaDupExt ( p_lisExt, p_lisVal, DuplicarEnteroMas100 ) != 1 )
		{
			printf( "Error caso 6: se esperaba resultado 1 al concatenar con fDuplicar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLispMoverA ( p_lisExt, 0 );
		if ( SLispInsertarListaDupExt ( p_lisExt, p_lisVal, DuplicarEnteroMas100 ) != 1 )
		{
			printf( "Error caso 7: se esperaba resultado 1 al insertar con fDuplicar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		int iEsp3 [ 4 ] = { 107, 107, 108, 108 };
		if ( ( VerificarContenido ( p_lisExt, iEsp3, 4 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarCadena ( p_lisExt ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 8: se esperaba { 107, 107, 108, 108 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLispInsertarListaDupExt ( p_lisExt, p_lisVal, NULL ) != 0 ) ||
			 ( SLispConcatenarListaDupExt ( p_lisExt, p_lisVal, NULL ) != 0 ) ||
			 ( SLispConcatenarListaDup ( p_lisVal, p_lisVal, sizeof ( int ) ) != 0 ) ||
			 ( SLispInsertarListaDup ( p_lisVal, p_lisVal, sizeof ( int ) ) != 0 ) )
		{
			printf( "Error caso 9: sin fDuplicar o con la misma lista se esperaba 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLispDestruir ( &p_lisObj );
	SLispDestruir ( &p_lisVal );
	SLispDestruir ( &p_lisExt );
	ErrLimpiar ();
	return ( iRes );
}

static int TestSLispExtraerLista01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLispExtraerLista 01:\n" );

	int iVal [ 5 ] = { 10, 20, 30, 20, 40 };
	int iBus [ 4 ] = { 20, 40, 99, 20 };
	int iValExt [ 3 ] = { 12, 25, 33 };
	int iBusExt [ 2 ] = { 3, 2 };
	SListaPtr * p_lisObj = CrearListaEnteros ( iVal, 5 );
	SListaPtr * p_lisBus = CrearListaEnteros ( iBus, 4 );
	SListaPtr * p_lisObjExt = CrearListaEnteros ( iValExt, 3 );
	SListaPtr * p_lisBusExt = CrearListaEnteros ( iBusExt, 2 );
	SListaPtr * p_lisRes = NULL;
	SListaPtr * p_lisResExt = NULL;
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisBus ) && ES_VALIDO ( p_lisObjExt ) && ES_VALIDO ( p_lisBusExt ) )
	{
		/* Una aparicion por valor buscado, en el orden de los buscados; el 99 no esta. */
		p_lisRes = SLispExtraerLista ( p_lisObj, p_lisBus, sizeof ( int ) );
		int iEspRes [ 3 ] = { 20, 40, 20 };
		int iEspObj [ 2 ] = { 10, 30 };
		if ( ES_NULO ( p_lisRes ) ||
			 ( VerificarContenido ( p_lisRes, iEspRes, 3 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarCadena ( p_lisRes ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 1: se esperaba extraer { 20, 40, 20 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( VerificarContenido ( p_lisObj, iEspObj, 2 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarCadena ( p_lisObj ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 2: en el origen deberia quedar { 10, 30 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLispLiberacionMemoriaActivada ( p_lisRes ) != 1 )
		{
			printf( "Error caso 3: la extraida hereda la liberacion activada del origen\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Con el origen sin liberacion, la extraida tampoco libera: los datos no son suyos. */
		SListaPtr * p_lisSinLib = SLispExtraerLista ( p_lisObj, p_lisObj, sizeof ( int ) );
		if ( ES_VALIDO ( p_lisSinLib ) )
		{
			printf( "Error caso 4: con la misma lista se esperaba nulo\n" );
			iRes = BOOL_VAL_FALSO;
			SLispDestruir ( &p_lisSinLib );
		}
		SLispDesactivarLiberacionMemoria ( p_lisObj );
		int iBus10 = 10;
		SListaPtr * p_lisBus10 = SLispCrear ();
		SLispDesactivarLiberacionMemoria ( p_lisBus10 );
		SLispInsertarAlFinal ( p_lisBus10, (byte *) &iBus10 );
		p_lisSinLib = SLispExtraerLista ( p_lisObj, p_lisBus10, sizeof ( int ) );
		if ( ES_NULO ( p_lisSinLib ) || ( SLispLiberacionMemoriaActivada ( p_lisSinLib ) != 0 ) ||
			 ( SLispNumElementos ( p_lisSinLib ) != 1 ) )
		{
			printf( "Error caso 5: la extraida de un origen sin liberacion no deberia liberar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Se devuelve la propiedad a mano para que no quede nada sin liberar. */
		SLispActivarLiberacionMemoria ( p_lisSinLib );
		SLispActivarLiberacionMemoria ( p_lisObj );
		SLispDestruir ( &p_lisSinLib );
		SLispDestruir ( &p_lisBus10 );

		p_lisResExt = SLispExtraerListaExt ( p_lisObjExt, p_lisBusExt, SonIgualesMod10 );
		int iEspResExt [ 2 ] = { 33, 12 };
		int iEspObjExt [ 1 ] = { 25 };
		if ( ES_NULO ( p_lisResExt ) ||
			 ( VerificarContenido ( p_lisResExt, iEspResExt, 2 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarContenido ( p_lisObjExt, iEspObjExt, 1 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 6: modulo 10 se esperaba extraer { 33, 12 } y dejar { 25 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SLispExtraerListaExt ( p_lisObjExt, p_lisBusExt, NULL ) ) )
		{
			printf( "Error caso 7: sin funcion de comparacion se esperaba nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLispDestruir ( &p_lisObj );
	SLispDestruir ( &p_lisBus );
	SLispDestruir ( &p_lisObjExt );
	SLispDestruir ( &p_lisBusExt );
	SLispDestruir ( &p_lisRes );
	SLispDestruir ( &p_lisResExt );
	return ( iRes );
}

/* Destruye una aparicion por valor buscado; los valores no cambian, y sin
   liberacion en la lista no se liberan los datos. */
static int TestSLispEliminarLista01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLispEliminarLista 01:\n" );

	int iVal [ 5 ] = { 10, 20, 30, 20, 40 };
	int iBus [ 4 ] = { 20, 40, 99, 20 };
	int iValExt [ 3 ] = { 12, 25, 33 };
	int iBusExt [ 2 ] = { 3, 2 };
	SListaPtr * p_lisObj = CrearListaEnteros ( iVal, 5 );
	SListaPtr * p_lisBus = CrearListaEnteros ( iBus, 4 );
	SListaPtr * p_lisObjExt = CrearListaEnteros ( iValExt, 3 );
	SListaPtr * p_lisBusExt = CrearListaEnteros ( iBusExt, 2 );
	SListaPtr * p_lisVacia = SLispCrear ();
	SListaPtr * p_lisSinLib = SLispCrear ();
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisBus ) && ES_VALIDO ( p_lisObjExt ) &&
		 ES_VALIDO ( p_lisBusExt ) && ES_VALIDO ( p_lisVacia ) && ES_VALIDO ( p_lisSinLib ) )
	{
		/* El 99 no esta y se ignora; el 20 esta dos veces en los buscados. */
		if ( SLispEliminarLista ( p_lisObj, p_lisBus, sizeof ( int ) ) != 1 )
		{
			printf( "Error caso 1: se esperaba 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		int iEspObj [ 2 ] = { 10, 30 };
		if ( ( VerificarCadena ( p_lisObj ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarContenido ( p_lisObj, iEspObj, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 2: deberia quedar { 10, 30 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( VerificarContenido ( p_lisBus, iBus, 4 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 3: los valores no deberian cambiar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Ya no queda ninguno: no hay nada que eliminar, y no es un error. */
		if ( ( SLispEliminarLista ( p_lisObj, p_lisBus, sizeof ( int ) ) != 1 ) ||
			 ( SLispEliminarLista ( p_lisObj, p_lisVacia, sizeof ( int ) ) != 1 ) ||
			 ( VerificarContenido ( p_lisObj, iEspObj, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 4: sin nada que eliminar se esperaba 1 sin cambios\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLispEliminarLista ( p_lisObj, p_lisObj, sizeof ( int ) ) != 0 ) ||
			 ( VerificarContenido ( p_lisObj, iEspObj, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 5: con la misma lista se esperaba 0 sin cambios\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLispEliminarLista ( p_lisObj, NULL, sizeof ( int ) ) != 0 ) ||
			 ( SLispEliminarLista ( NULL, p_lisBus, sizeof ( int ) ) != 0 ) )
		{
			printf( "Error caso 6: con una lista nula se esperaba 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Sin liberacion los datos no son de la lista: aqui son de la pila, y
		   liberarlos romperia el heap. */
		int iLoc [ 3 ] = { 5, 6, 7 };
		int iBusLoc [ 1 ] = { 6 };
		int iEspLoc [ 2 ] = { 5, 7 };
		SLispDesactivarLiberacionMemoria ( p_lisSinLib );
		SLispInsertarAlFinal ( p_lisSinLib, (byte *) &iLoc [ 0 ] );
		SLispInsertarAlFinal ( p_lisSinLib, (byte *) &iLoc [ 1 ] );
		SLispInsertarAlFinal ( p_lisSinLib, (byte *) &iLoc [ 2 ] );
		SListaPtr * p_lisBusLoc = CrearListaEnteros ( iBusLoc, 1 );
		if ( ( SLispEliminarLista ( p_lisSinLib, p_lisBusLoc, sizeof ( int ) ) != 1 ) ||
			 ( VerificarContenido ( p_lisSinLib, iEspLoc, 2 ) != BOOL_VAL_CIERTO ) ||
			 ( iLoc [ 1 ] != 6 ) )
		{
			printf( "Error caso 7: sin liberacion se esperaba quitar el 6 sin liberarlo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLispDestruir ( &p_lisBusLoc );

		/* Modulo 10: el 3 elimina el 33 y el 2 el 12. */
		int iEspObjExt [ 1 ] = { 25 };
		if ( ( SLispEliminarListaExt ( p_lisObjExt, p_lisBusExt, SonIgualesMod10 ) != 1 ) ||
			 ( VerificarCadena ( p_lisObjExt ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarContenido ( p_lisObjExt, iEspObjExt, 1 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 8: modulo 10 deberia quedar { 25 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLispEliminarListaExt ( p_lisObjExt, p_lisBusExt, NULL ) != 0 ) ||
			 ( VerificarContenido ( p_lisObjExt, iEspObjExt, 1 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 9: sin funcion de comparacion se esperaba 0 sin cambios\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLispEliminarListaExt ( p_lisObjExt, p_lisObjExt, SonIgualesMod10 ) != 0 ) ||
			 ( SLispEliminarListaExt ( NULL, p_lisBusExt, SonIgualesMod10 ) != 0 ) ||
			 ( SLispEliminarListaExt ( p_lisObjExt, NULL, SonIgualesMod10 ) != 0 ) ||
			 ( VerificarContenido ( p_lisObjExt, iEspObjExt, 1 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 10: con la misma lista o una nula se esperaba 0 sin cambios\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLispDestruir ( &p_lisObj );
	SLispDestruir ( &p_lisBus );
	SLispDestruir ( &p_lisObjExt );
	SLispDestruir ( &p_lisBusExt );
	SLispDestruir ( &p_lisVacia );
	SLispDestruir ( &p_lisSinLib );
	return ( iRes );
}

static int TestSLispConjuntos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLispConjuntos 01:\n" );

	int iV1 [ 4 ] = { 1, 2, 3, 4 };
	int iV2 [ 3 ] = { 4, 2, 5 };
	int iV3 [ 3 ] = { 14, 22, 7 };
	SListaPtr * p_lis1 = CrearListaEnteros ( iV1, 4 );
	SListaPtr * p_lis2 = CrearListaEnteros ( iV2, 3 );
	SListaPtr * p_lis3 = CrearListaEnteros ( iV3, 3 );
	SListaPtr * p_lisVacia = SLispCrear ();
	if ( ES_VALIDO ( p_lis1 ) && ES_VALIDO ( p_lis2 ) && ES_VALIDO ( p_lis3 ) && ES_VALIDO ( p_lisVacia ) )
	{
		/* La union es concatenacion: el 2 y el 4 salen dos veces. */
		SListaPtr * p_lisRes = SLispUnion ( p_lis1, p_lis2, sizeof ( int ) );
		int iEspU [ 7 ] = { 1, 2, 3, 4, 4, 2, 5 };
		if ( ES_NULO ( p_lisRes ) || ( VerificarContenido ( p_lisRes, iEspU, 7 ) != BOOL_VAL_CIERTO ) ||
			 ( SLispLiberacionMemoriaActivada ( p_lisRes ) != 1 ) )
		{
			printf( "Error caso 1: la union deberia ser { 1, 2, 3, 4, 4, 2, 5 } y liberar sus copias\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLispDestruir ( &p_lisRes );

		/* Interseccion en el orden de V1. */
		p_lisRes = SLispInterseccion ( p_lis1, p_lis2, sizeof ( int ) );
		int iEspI [ 2 ] = { 2, 4 };
		if ( ES_NULO ( p_lisRes ) || ( VerificarContenido ( p_lisRes, iEspI, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 2: la interseccion deberia ser { 2, 4 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLispDestruir ( &p_lisRes );

		/* Diferencia V1 - V2, en el orden de V1. */
		p_lisRes = SLispDiferencia ( p_lis1, p_lis2, sizeof ( int ) );
		int iEspD [ 2 ] = { 1, 3 };
		if ( ES_NULO ( p_lisRes ) || ( VerificarContenido ( p_lisRes, iEspD, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 3: la diferencia deberia ser { 1, 3 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLispDestruir ( &p_lisRes );

		/* Las de entrada quedan como estaban. */
		if ( ( VerificarContenido ( p_lis1, iV1, 4 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarContenido ( p_lis2, iV2, 3 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 4: las listas de entrada no deberian cambiar\n" );
			iRes = BOOL_VAL_FALSO;
		}

		p_lisRes = SLispUnionExt ( p_lis1, p_lis2, DuplicarEnteroMas100 );
		int iEspUE [ 7 ] = { 101, 102, 103, 104, 104, 102, 105 };
		if ( ES_NULO ( p_lisRes ) || ( VerificarContenido ( p_lisRes, iEspUE, 7 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 5: la union con fDuplicar deberia ser { 101, 102, 103, 104, 104, 102, 105 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLispDestruir ( &p_lisRes );

		/* Modulo 10: el 2 casa con el 22 y el 4 con el 14; se copian los de V1. */
		p_lisRes = SLispInterseccionExt ( p_lis1, p_lis3, SonIgualesMod10, DuplicarEnteroMas100 );
		int iEspIE [ 2 ] = { 102, 104 };
		if ( ES_NULO ( p_lisRes ) || ( VerificarContenido ( p_lisRes, iEspIE, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 6: la interseccion modulo 10 deberia ser { 102, 104 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLispDestruir ( &p_lisRes );

		p_lisRes = SLispDiferenciaExt ( p_lis1, p_lis3, SonIgualesMod10, DuplicarEnteroMas100 );
		int iEspDE [ 2 ] = { 101, 103 };
		if ( ES_NULO ( p_lisRes ) || ( VerificarContenido ( p_lisRes, iEspDE, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 7: la diferencia modulo 10 deberia ser { 101, 103 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLispDestruir ( &p_lisRes );

		/* Con una vacia: lista nueva vacia, no nulo. */
		p_lisRes = SLispInterseccion ( p_lis1, p_lisVacia, sizeof ( int ) );
		if ( ES_NULO ( p_lisRes ) || ( SLispEstaVacia ( p_lisRes ) != 1 ) )
		{
			printf( "Error caso 8: la interseccion con una vacia deberia ser una lista vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLispDestruir ( &p_lisRes );
		p_lisRes = SLispDiferencia ( p_lis1, p_lisVacia, sizeof ( int ) );
		if ( ES_NULO ( p_lisRes ) || ( VerificarContenido ( p_lisRes, iV1, 4 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 9: V1 menos una vacia deberia ser V1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLispDestruir ( &p_lisRes );

		if ( ES_VALIDO ( SLispUnion ( p_lis1, NULL, sizeof ( int ) ) ) ||
			 ES_VALIDO ( SLispUnionExt ( p_lis1, p_lis2, NULL ) ) ||
			 ES_VALIDO ( SLispInterseccionExt ( p_lis1, p_lis3, NULL, DuplicarEnteroMas100 ) ) ||
			 ES_VALIDO ( SLispDiferenciaExt ( p_lis1, p_lis3, SonIgualesMod10, NULL ) ) )
		{
			printf( "Error caso 10: con parametros nulos se esperaba nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLispDestruir ( &p_lis1 );
	SLispDestruir ( &p_lis2 );
	SLispDestruir ( &p_lis3 );
	SLispDestruir ( &p_lisVacia );
	return ( iRes );
}


/* La copia tiene datos propios y es duena de ellos; la Ext copia con fDuplicar.
   El original no cambia, ni su cursor. */
static int TestSLispDuplicar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLispDuplicar 01:\n" );

	int iVal [ 3 ] = { 10, 20, 30 };
	SListaPtr * p_lisObj = CrearListaEnteros ( iVal, 3 );
	SListaPtr * p_lisVacia = SLispCrear ();
	SListaPtr * p_lisDup = NULL;
	SListaPtr * p_lisExt = NULL;
	SListaPtr * p_lisDupVacia = NULL;
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisVacia ) )
	{
		SLispMoverA ( p_lisObj, 1 );
		p_lisDup = SLispDuplicar ( p_lisObj, sizeof ( int ) );
		p_lisExt = SLispDuplicarExt ( p_lisObj, DuplicarEnteroMas100 );
		if ( SLispPosicion ( p_lisObj ) != 1 )
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
			if ( ( VerificarContenido ( p_lisDup, iVal, 3 ) != BOOL_VAL_CIERTO ) ||
				 ( VerificarCadena ( p_lisDup ) != BOOL_VAL_CIERTO ) )
			{
				printf( "Error caso 3: la copia deberia tener { 10, 20, 30 }\n" );
				iRes = BOOL_VAL_FALSO;
			}
			if ( ( SLispElemento ( p_lisDup, 0 ) == SLispElemento ( p_lisObj, 0 ) ) ||
				 ( SLispLiberacionMemoriaActivada ( p_lisDup ) != 1 ) )
			{
				printf( "Error caso 4: la copia deberia tener datos propios y liberarlos\n" );
				iRes = BOOL_VAL_FALSO;
			}
			*( (int *) SLispElemento ( p_lisDup, 2 ) ) = 99;
			if ( VerificarContenido ( p_lisObj, iVal, 3 ) != BOOL_VAL_CIERTO )
			{
				printf( "Error caso 5: cambiar la copia no deberia tocar el original\n" );
				iRes = BOOL_VAL_FALSO;
			}
		}
		int iEspExt [ 3 ] = { 110, 120, 130 };
		if ( ES_NULO ( p_lisExt ) ||
			 ( VerificarContenido ( p_lisExt, iEspExt, 3 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarCadena ( p_lisExt ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 6: con fDuplicar se esperaba { 110, 120, 130 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* La vacia se copia en otra vacia, no en nulo. */
		p_lisDupVacia = SLispDuplicar ( p_lisVacia, sizeof ( int ) );
		if ( ES_NULO ( p_lisDupVacia ) || ( SLispEsValida ( p_lisDupVacia ) != 1 ) ||
			 ( SLispNumElementos ( p_lisDupVacia ) != 0 ) )
		{
			printf( "Error caso 7: la copia de una vacia deberia ser otra vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SLispDuplicar ( NULL, sizeof ( int ) ) ) ||
			 ES_VALIDO ( SLispDuplicarExt ( NULL, DuplicarEnteroMas100 ) ) ||
			 ES_VALIDO ( SLispDuplicarExt ( p_lisObj, NULL ) ) )
		{
			printf( "Error caso 8: con una lista nula o sin fDuplicar se esperaba nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLispDestruir ( &p_lisObj );
	SLispDestruir ( &p_lisVacia );
	SLispDestruir ( &p_lisDup );
	SLispDestruir ( &p_lisExt );
	SLispDestruir ( &p_lisDupVacia );
	ErrLimpiar ();
	return ( iRes );
}


/* 1 solo con el cursor sobre un elemento: no en una vacia, ni deposicionada,
   ni con la lista nula. */
static int TestSLispEstaPosicionada01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLispEstaPosicionada 01:\n" );

	SListaPtr * p_lisObj = SLispCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( SLispEstaPosicionada ( p_lisObj ) != 0 )
		{
			printf( "Error caso 1: una lista vacia no deberia estar posicionada\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLispInsertarAlFinal ( p_lisObj, CrearDatoEntero ( 10 ) );
		SLispInsertarAlFinal ( p_lisObj, CrearDatoEntero ( 20 ) );
		SLispInicio ( p_lisObj );
		if ( SLispEstaPosicionada ( p_lisObj ) != 1 )
		{
			printf( "Error caso 2: tras Inicio deberia estar posicionada\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLispSiguiente ( p_lisObj );
		SLispSiguiente ( p_lisObj );
		if ( SLispEstaPosicionada ( p_lisObj ) != 0 )
		{
			printf( "Error caso 3: pasado el ultimo no deberia estar posicionada\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLispFinal ( p_lisObj );
		SLispDeposicionar ( p_lisObj );
		if ( SLispEstaPosicionada ( p_lisObj ) != 0 )
		{
			printf( "Error caso 4: tras Deposicionar no deberia estar posicionada\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLispEstaPosicionada ( NULL ) != 0 )
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
	SLispDestruir ( &p_lisObj );
	return ( iRes );
}

int TestSListaPtr ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SListaPtr]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSLispCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSLispInsertar01 () == BOOL_VAL_CIERTO ) &&
			( TestSLispCursor01 () == BOOL_VAL_CIERTO ) &&
			( TestSLispBuscar01 () == BOOL_VAL_CIERTO ) &&
			( TestSLispEliminar01 () == BOOL_VAL_CIERTO ) &&
			( TestSLispInvalidos01 () == BOOL_VAL_CIERTO ) &&
			( TestSLispCursorNulo01 () == BOOL_VAL_CIERTO ) &&
			( TestSLispExtraer01 () == BOOL_VAL_CIERTO ) &&
			( TestSLispBuscarExt01 () == BOOL_VAL_CIERTO ) &&
			( TestSLispBuscarSiguiente01 () == BOOL_VAL_CIERTO ) &&
			( TestSLispRepeticiones01 () == BOOL_VAL_CIERTO ) &&
			( TestSLispExisten01 () == BOOL_VAL_CIERTO ) &&
			( TestSLispExistenExt01 () == BOOL_VAL_CIERTO ) &&
			( TestSLispInsertarLista01 () == BOOL_VAL_CIERTO ) &&
			( TestSLispListaDup01 () == BOOL_VAL_CIERTO ) &&
			( TestSLispExtraerLista01 () == BOOL_VAL_CIERTO ) &&
			( TestSLispEliminarLista01 () == BOOL_VAL_CIERTO ) &&
			( TestSLispConjuntos01 () == BOOL_VAL_CIERTO ) &&
			( TestSLispDuplicar01 () == BOOL_VAL_CIERTO ) &&
			( TestSLispEstaPosicionada01 () == BOOL_VAL_CIERTO ) )
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
