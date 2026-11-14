#include "Base.h"

#include "SLista.h"



/* Crea un elemento entero listo para insertar en la lista. */
static SElemento * CrearElementoEntero ( int iValor )
{
	SElemento * p_elmObj = SElmCrearEntero ();
	if ( ES_VALIDO ( p_elmObj ) )
	{
		SElmEscribirEntero ( p_elmObj, iValor );
	}
	return ( p_elmObj );
}

/* Recorre la lista de principio a fin comprobando numero y orden de los valores. */
static int VerificarContenido ( SLista * p_lisObj, int * p_iEsperados, int iNum )
{
	int iRes = BOOL_VAL_CIERTO;

	if ( SLisNumElementos ( p_lisObj ) != iNum )
	{
		printf( "  Verificacion: se esperaban %d elementos: %d\n", iNum, SLisNumElementos ( p_lisObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	int iPos = 0;
	SLisInicio ( p_lisObj );
	while ( ( iPos < iNum ) && ( iRes == BOOL_VAL_CIERTO ) )
	{
		SElemento * p_elmObj = SLisActual ( p_lisObj );
		if ( ES_NULO ( p_elmObj ) )
		{
			printf( "  Verificacion: elemento nulo en la posicion %d\n", iPos );
			iRes = BOOL_VAL_FALSO;
		}
		else if ( SElmEntero ( p_elmObj ) != p_iEsperados [ iPos ] )
		{
			printf( "  Verificacion: en pos %d se esperaba %d: %d\n", iPos, p_iEsperados [ iPos ], SElmEntero ( p_elmObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		SLisSiguiente ( p_lisObj );
		iPos = iPos + 1;
	}
	return ( iRes );
}

/* Comprueba la cadena por dentro: de p_elmPrimero a p_elmUltimo en exactamente
   NumElementos pasos, con cada enlace hacia atras casando con el de delante. */
static int VerificarCadena ( SLista * p_lisObj )
{
	int iRes = BOOL_VAL_CIERTO;
	int iNum = 0;
	SElemento * p_elmAnt = NULL;
	SElemento * p_elmObj = p_lisObj->p_elmPrimero;

	while ( ES_VALIDO ( p_elmObj ) && ( iRes == BOOL_VAL_CIERTO ) )
	{
		if ( SElmAntecesor ( p_elmObj ) != p_elmAnt )
		{
			printf( "  Cadena: el enlace hacia atras del elemento %d no casa\n", iNum );
			iRes = BOOL_VAL_FALSO;
		}
		p_elmAnt = p_elmObj;
		p_elmObj = SElmSucesor ( p_elmObj );
		iNum = iNum + 1;
	}
	if ( iNum != SLisNumElementos ( p_lisObj ) )
	{
		printf( "  Cadena: se recorren %d elementos y la lista dice %d\n", iNum, SLisNumElementos ( p_lisObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( p_lisObj->p_elmUltimo != p_elmAnt )
	{
		printf( "  Cadena: el ultimo de la lista no es el final de la cadena\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static SLista * CrearListaEnteros ( int * p_iValores, int iNum )
{
	SLista * p_lisObj = SLisCrear ();
	int iPos = 0;
	while ( ES_VALIDO ( p_lisObj ) && ( iPos < iNum ) )
	{
		SLisInsertarAlFinal ( p_lisObj, CrearElementoEntero ( p_iValores [ iPos ] ) );
		iPos = iPos + 1;
	}
	return ( p_lisObj );
}



static int TestSLisCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisCrear 01:\n" );

	SLista * p_lisObj = SLisCrear ();
	if ( ES_NULO ( p_lisObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SLisEsValida ( p_lisObj ) != 1 )
		{
			printf( "Error caso 2: la lista recien creada deberia ser valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisEstaVacia ( p_lisObj ) != 1 )
		{
			printf( "Error caso 3: la lista recien creada deberia estar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisNumElementos ( p_lisObj ) != 0 )
		{
			printf( "Error caso 4: se esperaban 0 elementos\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SLisDestruir ( &p_lisObj );

	if ( ES_VALIDO ( p_lisObj ) )
	{
		printf( "Error caso 5: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSLisInsertarAlFinal01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisInsertarAlFinal 01:\n" );

	SLista * p_lisObj = SLisCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		SLisInsertarAlFinal ( p_lisObj, CrearElementoEntero ( 10 ) );
		SLisInsertarAlFinal ( p_lisObj, CrearElementoEntero ( 20 ) );
		SLisInsertarAlFinal ( p_lisObj, CrearElementoEntero ( 30 ) );

		if ( SLisEstaVacia ( p_lisObj ) != 0 )
		{
			printf( "Error caso 1: la lista no deberia estar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		int iEsperados [ 3 ] = { 10, 20, 30 };
		if ( VerificarContenido ( p_lisObj, iEsperados, 3 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 2: el contenido tras insertar al final no es el esperado\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisDestruir ( &p_lisObj );
	return ( iRes );
}

static int TestSLisInsertarAlInicio01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisInsertarAlInicio 01:\n" );

	SLista * p_lisObj = SLisCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		SLisInsertarAlInicio ( p_lisObj, CrearElementoEntero ( 10 ) );
		SLisInsertarAlInicio ( p_lisObj, CrearElementoEntero ( 20 ) );
		SLisInsertarAlInicio ( p_lisObj, CrearElementoEntero ( 30 ) );

		/* Al insertar siempre al inicio, el orden queda invertido. */
		int iEsperados [ 3 ] = { 30, 20, 10 };
		if ( VerificarContenido ( p_lisObj, iEsperados, 3 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 1: el contenido tras insertar al inicio no es el esperado\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisDestruir ( &p_lisObj );
	return ( iRes );
}

static int TestSLisInsertarElem01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisInsertarElem 01:\n" );

	SLista * p_lisObj = SLisCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		SLisInsertarAlFinal ( p_lisObj, CrearElementoEntero ( 10 ) );
		SLisInsertarAlFinal ( p_lisObj, CrearElementoEntero ( 30 ) );

		/* Insertar 20 detras del elemento en la posicion 0. */
		if ( SLisInsertarElem ( p_lisObj, 0, CrearElementoEntero ( 20 ) ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al insertar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		int iEsperados [ 3 ] = { 10, 20, 30 };
		if ( VerificarContenido ( p_lisObj, iEsperados, 3 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 2: el contenido tras insertar en medio no es el esperado\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisDestruir ( &p_lisObj );
	return ( iRes );
}

static int TestSLisCursor01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisCursor 01:\n" );

	SLista * p_lisObj = SLisCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		SLisInsertarAlFinal ( p_lisObj, CrearElementoEntero ( 10 ) );
		SLisInsertarAlFinal ( p_lisObj, CrearElementoEntero ( 20 ) );
		SLisInsertarAlFinal ( p_lisObj, CrearElementoEntero ( 30 ) );

		SLisInicio ( p_lisObj );
		if ( ( SLisPosicion ( p_lisObj ) != 0 ) || ( SElmEntero ( SLisActual ( p_lisObj ) ) != 10 ) )
		{
			printf( "Error caso 1: el inicio deberia situar el cursor en el 10\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisEstaEnInicio ( p_lisObj ) != 1 )
		{
			printf( "Error caso 2: el cursor deberia estar en el inicio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisSiguiente ( p_lisObj );
		if ( ( SLisPosicion ( p_lisObj ) != 1 ) || ( SElmEntero ( SLisActual ( p_lisObj ) ) != 20 ) )
		{
			printf( "Error caso 3: el siguiente deberia situar el cursor en el 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisFinal ( p_lisObj );
		if ( ( SElmEntero ( SLisActual ( p_lisObj ) ) != 30 ) || ( SLisEstaEnFinal ( p_lisObj ) != 1 ) )
		{
			printf( "Error caso 4: el final deberia situar el cursor en el 30\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisAnterior ( p_lisObj );
		if ( SElmEntero ( SLisActual ( p_lisObj ) ) != 20 )
		{
			printf( "Error caso 5: el anterior deberia situar el cursor en el 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisMoverA ( p_lisObj, 0 );
		if ( SElmEntero ( SLisActual ( p_lisObj ) ) != 10 )
		{
			printf( "Error caso 6: mover a 0 deberia situar el cursor en el 10\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisDestruir ( &p_lisObj );
	return ( iRes );
}

static int TestSLisBuscar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisBuscar 01:\n" );

	SLista * p_lisObj = SLisCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		SLisInsertarAlFinal ( p_lisObj, CrearElementoEntero ( 10 ) );
		SLisInsertarAlFinal ( p_lisObj, CrearElementoEntero ( 20 ) );
		SLisInsertarAlFinal ( p_lisObj, CrearElementoEntero ( 30 ) );

		SBloque * p_blqBuscar = SBlqCrearEntero ();
		if ( ES_VALIDO ( p_blqBuscar ) )
		{
			SBlqEscribirEntero ( p_blqBuscar, 20 );
			if ( SLisBuscar ( p_lisObj, p_blqBuscar ) != 1 )
			{
				printf( "Error caso 1: el 20 deberia estar en la posicion 1\n" );
				iRes = BOOL_VAL_FALSO;
			}
			SBlqEscribirEntero ( p_blqBuscar, 99 );
			if ( SLisBuscar ( p_lisObj, p_blqBuscar ) != -1 )
			{
				printf( "Error caso 2: el 99 no deberia encontrarse\n" );
				iRes = BOOL_VAL_FALSO;
			}
		}
		SBlqDestruir ( &p_blqBuscar );
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisDestruir ( &p_lisObj );
	return ( iRes );
}

/* Busca por contenido: vale un elemento que no esta en la lista. */
static int TestSLisBuscarElem01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisBuscarElem 01:\n" );

	int iVal [ 4 ] = { 10, 20, 30, 20 };
	SLista * p_lisObj = CrearListaEnteros ( iVal, 4 );
	SElemento * p_elm20 = CrearElementoEntero ( 20 );
	SElemento * p_elm99 = CrearElementoEntero ( 99 );
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_elm20 ) && ES_VALIDO ( p_elm99 ) )
	{
		/* El primero igual, aunque el 20 este dos veces. */
		if ( SLisBuscarElem ( p_lisObj, p_elm20 ) != 1 )
		{
			printf( "Error caso 1: el 20 deberia estar en la posicion 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisBuscarElem ( p_lisObj, p_elm99 ) != -1 )
		{
			printf( "Error caso 2: el 99 no deberia encontrarse\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Un elemento de la propia lista se encuentra por su contenido. */
		if ( SLisBuscarElem ( p_lisObj, SLisElemento ( p_lisObj, 2 ) ) != 2 )
		{
			printf( "Error caso 3: el elemento 2 de la lista deberia estar en la posicion 2\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisBuscarElem ( p_lisObj, NULL ) != -1 ) || ( SLisBuscarElem ( NULL, p_elm20 ) != -1 ) )
		{
			printf( "Error caso 4: con un nulo se esperaba -1\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear la lista o los elementos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SElmDestruir ( &p_elm20 );
	SElmDestruir ( &p_elm99 );
	SLisDestruir ( &p_lisObj );
	return ( iRes );
}

/* Recorre los repetidos con BuscarPrimero / BuscarSiguiente, con el cursor
   quieto y sin el: sin cursor, a partir de la mitad se entra por el final. */
static int TestSLisBuscarSiguiente01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisBuscarSiguiente 01:\n" );

	int iVal [ 6 ] = { 20, 10, 20, 30, 20, 40 };
	int iVeinte = 20;
	SLista * p_lisObj = CrearListaEnteros ( iVal, 6 );
	SElemento * p_elm20 = CrearElementoEntero ( 20 );
	SBloque * p_blq20 = SBlqCrearEntero ();
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_elm20 ) && ES_VALIDO ( p_blq20 ) )
	{
		SBlqEscribirEntero ( p_blq20, 20 );
		SLisDeposicionar ( p_lisObj );
		if ( ( SLisBuscarPrimero ( p_lisObj, p_blq20 ) != 0 ) ||
			 ( SLisBuscarSiguiente ( p_lisObj, p_blq20, 0 ) != 2 ) ||
			 ( SLisBuscarSiguiente ( p_lisObj, p_blq20, 2 ) != 4 ) ||
			 ( SLisBuscarSiguiente ( p_lisObj, p_blq20, 4 ) != -1 ) )
		{
			printf( "Error caso 1: sin cursor el 20 deberia estar en 0, 2 y 4\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisBuscarPrimeroExt ( p_lisObj, (byte *) &iVeinte ) != 0 ) ||
			 ( SLisBuscarSiguienteExt ( p_lisObj, (byte *) &iVeinte, 0 ) != 2 ) ||
			 ( SLisBuscarSiguienteExt ( p_lisObj, (byte *) &iVeinte, 2 ) != 4 ) ||
			 ( SLisBuscarSiguienteExt ( p_lisObj, (byte *) &iVeinte, 4 ) != -1 ) )
		{
			printf( "Error caso 2: con memoria cruda el 20 deberia estar en 0, 2 y 4\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisBuscarPrimeroElem ( p_lisObj, p_elm20 ) != 0 ) ||
			 ( SLisBuscarSiguienteElem ( p_lisObj, p_elm20, 0 ) != 2 ) ||
			 ( SLisBuscarSiguienteElem ( p_lisObj, p_elm20, 2 ) != 4 ) ||
			 ( SLisBuscarSiguienteElem ( p_lisObj, p_elm20, 4 ) != -1 ) )
		{
			printf( "Error caso 3: por elemento el 20 deberia estar en 0, 2 y 4\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Desde la posicion siguiente, no desde la misma: el 20 de la 2 no cuenta. */
		if ( ( SLisBuscarSiguiente ( p_lisObj, p_blq20, 1 ) != 2 ) ||
			 ( SLisBuscarSiguiente ( p_lisObj, p_blq20, 3 ) != 4 ) )
		{
			printf( "Error caso 4: detras de la 1 el 20 esta en la 2, y detras de la 3 en la 4\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Con el cursor en la 4 se parte de el, hacia atras y hacia delante, y no se mueve. */
		SLisMoverA ( p_lisObj, 4 );
		if ( ( SLisBuscarPrimero ( p_lisObj, p_blq20 ) != 0 ) ||
			 ( SLisBuscarSiguiente ( p_lisObj, p_blq20, 0 ) != 2 ) ||
			 ( SLisBuscarSiguiente ( p_lisObj, p_blq20, 2 ) != 4 ) ||
			 ( SLisBuscarSiguiente ( p_lisObj, p_blq20, 4 ) != -1 ) ||
			 ( SLisPosicion ( p_lisObj ) != 4 ) )
		{
			printf( "Error caso 5: con el cursor en la 4 se esperaba lo mismo y el cursor quieto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisBuscar ( p_lisObj, p_blq20 ) != 0 ) || ( SLisBuscarExt ( p_lisObj, (byte *) &iVeinte ) != 0 ) ||
			 ( SLisBuscarElem ( p_lisObj, p_elm20 ) != 0 ) )
		{
			printf( "Error caso 6: Buscar deberia ser BuscarPrimero\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisBuscarSiguiente ( p_lisObj, p_blq20, 5 ) != -1 ) ||
			 ( SLisBuscarSiguiente ( p_lisObj, p_blq20, 6 ) != -1 ) ||
			 ( SLisBuscarSiguiente ( p_lisObj, p_blq20, -2 ) != -1 ) )
		{
			printf( "Error caso 7: desde el final o con una posicion menor que -1 se esperaba -1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisBuscarSiguiente ( NULL, p_blq20, -1 ) != -1 ) ||
			 ( SLisBuscarSiguiente ( p_lisObj, NULL, -1 ) != -1 ) ||
			 ( SLisBuscarSiguienteExt ( p_lisObj, NULL, -1 ) != -1 ) ||
			 ( SLisBuscarSiguienteElem ( p_lisObj, NULL, -1 ) != -1 ) ||
			 ( SLisBuscarPrimeroElem ( NULL, p_elm20 ) != -1 ) )
		{
			printf( "Error caso 8: con un nulo se esperaba -1\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear la lista o los datos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SElmDestruir ( &p_elm20 );
	SBlqDestruir ( &p_blq20 );
	SLisDestruir ( &p_lisObj );
	return ( iRes );
}

/* Existe y Repeticiones, por bloque, por memoria cruda y por elemento. */
static int TestSLisRepeticiones01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisRepeticiones 01:\n" );

	int iVal [ 6 ] = { 20, 10, 20, 30, 20, 40 };
	int iVeinte = 20;
	int iNoventa = 99;
	SLista * p_lisObj = CrearListaEnteros ( iVal, 6 );
	SLista * p_lisVacia = SLisCrear ();
	SElemento * p_elm20 = CrearElementoEntero ( 20 );
	SElemento * p_elm99 = CrearElementoEntero ( 99 );
	SBloque * p_blqDato = SBlqCrearEntero ();
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisVacia ) && ES_VALIDO ( p_elm20 ) &&
		 ES_VALIDO ( p_elm99 ) && ES_VALIDO ( p_blqDato ) )
	{
		SBlqEscribirEntero ( p_blqDato, 20 );
		if ( ( SLisRepeticiones ( p_lisObj, p_blqDato ) != 3 ) ||
			 ( SLisRepeticionesExt ( p_lisObj, (byte *) &iVeinte ) != 3 ) ||
			 ( SLisRepeticionesElem ( p_lisObj, p_elm20 ) != 3 ) )
		{
			printf( "Error caso 1: el 20 deberia estar 3 veces\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisExiste ( p_lisObj, p_blqDato ) != 1 ) ||
			 ( SLisExisteExt ( p_lisObj, (byte *) &iVeinte ) != 1 ) ||
			 ( SLisExisteElem ( p_lisObj, p_elm20 ) != 1 ) )
		{
			printf( "Error caso 2: el 20 deberia existir\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SBlqEscribirEntero ( p_blqDato, 40 );
		if ( ( SLisRepeticiones ( p_lisObj, p_blqDato ) != 1 ) || ( SLisExiste ( p_lisObj, p_blqDato ) != 1 ) )
		{
			printf( "Error caso 3: el 40, el ultimo, deberia estar una vez\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SBlqEscribirEntero ( p_blqDato, 99 );
		if ( ( SLisRepeticiones ( p_lisObj, p_blqDato ) != 0 ) ||
			 ( SLisRepeticionesExt ( p_lisObj, (byte *) &iNoventa ) != 0 ) ||
			 ( SLisRepeticionesElem ( p_lisObj, p_elm99 ) != 0 ) ||
			 ( SLisExiste ( p_lisObj, p_blqDato ) != 0 ) ||
			 ( SLisExisteExt ( p_lisObj, (byte *) &iNoventa ) != 0 ) ||
			 ( SLisExisteElem ( p_lisObj, p_elm99 ) != 0 ) )
		{
			printf( "Error caso 4: el 99 no deberia estar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisRepeticionesElem ( p_lisVacia, p_elm20 ) != 0 ) || ( SLisExisteElem ( p_lisVacia, p_elm20 ) != 0 ) )
		{
			printf( "Error caso 5: en una lista vacia no deberia estar nada\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisRepeticiones ( NULL, p_blqDato ) != 0 ) || ( SLisRepeticiones ( p_lisObj, NULL ) != 0 ) ||
			 ( SLisRepeticionesExt ( p_lisObj, NULL ) != 0 ) || ( SLisRepeticionesElem ( p_lisObj, NULL ) != 0 ) ||
			 ( SLisExiste ( NULL, p_blqDato ) != 0 ) || ( SLisExisteElem ( p_lisObj, NULL ) != 0 ) ||
			 ( SLisExisteExt ( p_lisObj, NULL ) != 0 ) )
		{
			printf( "Error caso 6: con un nulo se esperaba 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas o los datos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SElmDestruir ( &p_elm20 );
	SElmDestruir ( &p_elm99 );
	SBlqDestruir ( &p_blqDato );
	SLisDestruir ( &p_lisObj );
	SLisDestruir ( &p_lisVacia );
	return ( iRes );
}

static int TestSLisEliminar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisEliminar 01:\n" );

	SLista * p_lisObj = SLisCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		SLisInsertarAlFinal ( p_lisObj, CrearElementoEntero ( 10 ) );
		SLisInsertarAlFinal ( p_lisObj, CrearElementoEntero ( 20 ) );
		SLisInsertarAlFinal ( p_lisObj, CrearElementoEntero ( 30 ) );

		/* Borrar el primero: el nuevo primero no debe conservar enlace colgante. */
		SLisInicio ( p_lisObj );
		SLisEliminar ( p_lisObj );
		int iEsp1 [ 2 ] = { 20, 30 };
		if ( VerificarContenido ( p_lisObj, iEsp1, 2 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 1: contenido incorrecto tras borrar el primero\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Recorrido hacia atras: al retroceder desde el nuevo primero se sale a nulo. */
		SLisFinal ( p_lisObj );
		SLisAnterior ( p_lisObj );
		if ( SElmEntero ( SLisActual ( p_lisObj ) ) != 20 )
		{
			printf( "Error caso 2: el anterior al 30 deberia ser el 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisAnterior ( p_lisObj );
		if ( ES_VALIDO ( SLisActual ( p_lisObj ) ) )
		{
			printf( "Error caso 3: retroceder mas alla del primero deberia dar nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}

		/* Borrar el ultimo: el nuevo ultimo no debe conservar sucesor colgante. */
		SLisFinal ( p_lisObj );
		SLisEliminar ( p_lisObj );
		int iEsp2 [ 1 ] = { 20 };
		if ( VerificarContenido ( p_lisObj, iEsp2, 1 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 4: contenido incorrecto tras borrar el ultimo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisInicio ( p_lisObj );
		if ( SLisEstaEnFinal ( p_lisObj ) != 1 )
		{
			printf( "Error caso 5: el unico elemento deberia estar tambien en el final\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisSiguiente ( p_lisObj );
		if ( ES_VALIDO ( SLisActual ( p_lisObj ) ) )
		{
			printf( "Error caso 6: avanzar desde el ultimo deberia dar nulo ( sin puntero colgante )\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisDestruir ( &p_lisObj );

	/* Borrar en medio: los vecinos quedan correctamente enlazados en ambos sentidos. */
	SLista * p_lisMedio = SLisCrear ();
	if ( ES_VALIDO ( p_lisMedio ) )
	{
		SLisInsertarAlFinal ( p_lisMedio, CrearElementoEntero ( 10 ) );
		SLisInsertarAlFinal ( p_lisMedio, CrearElementoEntero ( 20 ) );
		SLisInsertarAlFinal ( p_lisMedio, CrearElementoEntero ( 30 ) );

		SLisMoverA ( p_lisMedio, 1 );
		SLisEliminar ( p_lisMedio );
		int iEsp3 [ 2 ] = { 10, 30 };
		if ( VerificarContenido ( p_lisMedio, iEsp3, 2 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 7: contenido incorrecto tras borrar en medio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Recorrido hacia atras desde el final. */
		SLisFinal ( p_lisMedio );
		SLisAnterior ( p_lisMedio );
		if ( SElmEntero ( SLisActual ( p_lisMedio ) ) != 10 )
		{
			printf( "Error caso 8: el anterior al 30 deberia ser ahora el 10\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SLisDestruir ( &p_lisMedio );
	return ( iRes );
}

static int TestSLisVaciar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisVaciar 01:\n" );

	SLista * p_lisObj = SLisCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		SLisInsertarAlFinal ( p_lisObj, CrearElementoEntero ( 10 ) );
		SLisInsertarAlFinal ( p_lisObj, CrearElementoEntero ( 20 ) );

		if ( SLisVaciar ( p_lisObj ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al vaciar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisNumElementos ( p_lisObj ) != 0 )
		{
			printf( "Error caso 2: se esperaban 0 elementos tras vaciar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Tras vaciar debe seguir siendo una lista valida y reutilizable. */
		if ( SLisEsValida ( p_lisObj ) != 1 )
		{
			printf( "Error caso 3: la lista deberia seguir siendo valida tras vaciar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisInsertarAlFinal ( p_lisObj, CrearElementoEntero ( 99 ) ) != 1 )
		{
			printf( "Error caso 4: deberia poder reinsertarse tras vaciar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisDestruir ( &p_lisObj );
	return ( iRes );
}

static int TestSLisInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisInvalidos 01:\n" );

	if ( SLisEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: una lista nula no deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLisNumElementos ( NULL ) != 0 )
	{
		printf( "Error caso 2: el numero de elementos de una lista nula deberia ser 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLisEstaVacia ( NULL ) != 1 )
	{
		printf( "Error caso 3: una lista nula deberia considerarse vacia\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLista * p_lisNula = NULL;
	SLisDestruir ( &p_lisNula );
	return ( iRes );
}

static int TestSLisExtraer01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisExtraer 01:\n" );

	SLista * p_lisObj = SLisCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		SLisInsertarAlFinal ( p_lisObj, CrearElementoEntero ( 10 ) );
		SLisInsertarAlFinal ( p_lisObj, CrearElementoEntero ( 20 ) );
		SLisInsertarAlFinal ( p_lisObj, CrearElementoEntero ( 30 ) );

		/* SLisExtraerElem: saca el elemento del indice indicado SIN destruirlo. */
		SElemento * p_elmExt = SLisExtraerElem ( p_lisObj, 1 );
		if ( ES_NULO ( p_elmExt ) )
		{
			printf( "Error caso 1: no se esperaba nulo al extraer\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			/* El extraido sigue vivo y conserva su valor. */
			if ( SElmEntero ( p_elmExt ) != 20 )
			{
				printf( "Error caso 2: el elemento extraido deberia valer 20: %d\n", SElmEntero ( p_elmExt ) );
				iRes = BOOL_VAL_FALSO;
			}
			/* Y queda desligado de la lista: sin antecesor ni sucesor. */
			if ( ( SElmTieneAntecesor ( p_elmExt ) != 0 ) || ( SElmTieneSucesor ( p_elmExt ) != 0 ) )
			{
				printf( "Error caso 3: el elemento extraido deberia quedar desencadenado\n" );
				iRes = BOOL_VAL_FALSO;
			}
			/* El llamante es el dueno del elemento extraido y debe destruirlo. */
			SElmDestruir ( &p_elmExt );
		}
		/* La lista queda sin ese elemento y consistente. */
		int iEsp1 [ 2 ] = { 10, 30 };
		if ( VerificarContenido ( p_lisObj, iEsp1, 2 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 4: contenido incorrecto tras extraer el elemento 1\n" );
			iRes = BOOL_VAL_FALSO;
		}

		/* SLisExtraer: saca el elemento situado en el cursor. */
		SLisInicio ( p_lisObj );
		SElemento * p_elmPrim = SLisExtraer ( p_lisObj );
		if ( ES_NULO ( p_elmPrim ) )
		{
			printf( "Error caso 5: no se esperaba nulo al extraer el actual\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			if ( SElmEntero ( p_elmPrim ) != 10 )
			{
				printf( "Error caso 6: el elemento extraido deberia valer 10: %d\n", SElmEntero ( p_elmPrim ) );
				iRes = BOOL_VAL_FALSO;
			}
			SElmDestruir ( &p_elmPrim );
		}
		int iEsp2 [ 1 ] = { 30 };
		if ( VerificarContenido ( p_lisObj, iEsp2, 1 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 7: contenido incorrecto tras extraer el actual\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Extraer de una posicion invalida devuelve nulo. */
		if ( ES_VALIDO ( SLisExtraerElem ( p_lisObj, 5 ) ) )
		{
			printf( "Error caso 8: extraer una posicion invalida deberia dar nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisDestruir ( &p_lisObj );
	return ( iRes );
}





/* SLisElemento entra por el extremo mas cercano al indice, asi que hay que
   probar TODOS los indices, no solo los primeros: el off-by-one que tuvo la
   rama de entrada por el final solo se veia pidiendo un indice de la segunda
   mitad. Y con el cursor FRIO, porque mientras estuviera caliente la funcion
   tomaba el otro camino.

   Se comprueba ademas el contrato nuevo: consultar por indice NO mueve el
   cursor. Antes lo movia, y de ahi salio que InsertarOrdenado dejara de
   ordenar en cuanto se quito ese efecto. */
static int TestSLisElementoIndice01 ()
{
	int			iRes = BOOL_VAL_CIERTO;
	int			iPos;
	SLista *	p_lisObj;
	SElemento *	p_elmObj;

	printf( "Test SLisElementoIndice 01:\n" );

	/* Siete elementos: 100, 101 … 106. Impar a proposito, para que el reparto
	   entre las dos mitades no sea simetrico. */
	p_lisObj = SLisCrear ();
	for ( iPos = 0; iPos < 7; iPos = iPos + 1 )
	{
		SLisInsertarAlFinal ( p_lisObj, CrearElementoEntero ( 100 + iPos ) );
	}

	/* De atras hacia delante y con el cursor recien puesto al principio cada
	   vez, para forzar la entrada por el final. */
	for ( iPos = 6; iPos >= 0; iPos = iPos - 1 )
	{
		SLisInicio ( p_lisObj );
		p_elmObj = SLisElemento ( p_lisObj, iPos );
		if ( ES_NULO ( p_elmObj ) )
		{
			printf( "Error caso 1: el indice %d no deberia dar nulo\n", iPos );
			iRes = BOOL_VAL_FALSO;
		}
		else if ( SElmEntero ( p_elmObj ) != 100 + iPos )
		{
			printf( "Error caso 2: en el indice %d se esperaba %d: %d\n",
					iPos, 100 + iPos, SElmEntero ( p_elmObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	/* Y de delante hacia atras. */
	for ( iPos = 0; iPos < 7; iPos = iPos + 1 )
	{
		p_elmObj = SLisElemento ( p_lisObj, iPos );
		if ( ES_VALIDO ( p_elmObj ) && ( SElmEntero ( p_elmObj ) != 100 + iPos ) )
		{
			printf( "Error caso 3: en el indice %d se esperaba %d: %d\n",
					iPos, 100 + iPos, SElmEntero ( p_elmObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	/* Fuera de rango, nulo. */
	if ( ES_VALIDO ( SLisElemento ( p_lisObj, 7 ) ) )
	{
		printf( "Error caso 4: el indice 7 no existe\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SLisElemento ( p_lisObj, -1 ) ) )
	{
		printf( "Error caso 5: el indice -1 no existe\n" );
		iRes = BOOL_VAL_FALSO;
	}

	/* El contrato nuevo: consultar por indice no mueve el cursor. */
	SLisInicio ( p_lisObj );
	SLisSiguiente ( p_lisObj );
	SLisSiguiente ( p_lisObj );
	if ( SLisPosicion ( p_lisObj ) != 2 )
	{
		printf( "Error caso 6: el cursor deberia estar en 2: %d\n", SLisPosicion ( p_lisObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	SLisElemento ( p_lisObj, 6 );
	SLisElemento ( p_lisObj, 0 );
	if ( SLisPosicion ( p_lisObj ) != 2 )
	{
		printf( "Error caso 7: consultar por indice no deberia mover el cursor, y esta en %d\n",
				SLisPosicion ( p_lisObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	SLisDestruir ( &p_lisObj );
	ErrLimpiar ();
	return ( iRes );
}

/* Contra los dos defectos que tuvo: tomar el resultado de SLisBuscar ( posicion
   o -1 ) como booleano, que fallaba con un valor en la posicion 0, y parar el
   recorrido antes del ULTIMO valor. */
static int TestSLisExisten01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisExisten 01:\n" );

	int iVal [ 3 ] = { 10, 20, 30 };
	int iV1 [ 2 ] = { 10, 30 };
	int iV2 [ 2 ] = { 10, 99 };
	int iV3 [ 2 ] = { 99, 30 };
	int iV4 [ 2 ] = { 98, 99 };
	SLista * p_lisObj = CrearListaEnteros ( iVal, 3 );
	SLista * p_lis1 = CrearListaEnteros ( iV1, 2 );
	SLista * p_lis2 = CrearListaEnteros ( iV2, 2 );
	SLista * p_lis3 = CrearListaEnteros ( iV3, 2 );
	SLista * p_lis4 = CrearListaEnteros ( iV4, 2 );
	SLista * p_lisVacia = SLisCrear ();
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lis1 ) && ES_VALIDO ( p_lis2 ) &&
		 ES_VALIDO ( p_lis3 ) && ES_VALIDO ( p_lis4 ) && ES_VALIDO ( p_lisVacia ) )
	{
		if ( SLisExistenTodos ( p_lisObj, p_lis1 ) != 1 )
		{
			printf( "Error caso 1: { 10, 30 } estan todos en { 10, 20, 30 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisExistenTodos ( p_lisObj, p_lis2 ) != 0 )
		{
			printf( "Error caso 2: en { 10, 99 } falta el 99\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisExisteAlguno ( p_lisObj, p_lis2 ) != 1 )
		{
			printf( "Error caso 3: de { 10, 99 } esta el 10, en la posicion 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisExisteAlguno ( p_lisObj, p_lis3 ) != 1 )
		{
			printf( "Error caso 4: de { 99, 30 } esta el 30, el ultimo de los valores\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisExisteAlguno ( p_lisObj, p_lis4 ) != 0 ) ||
			 ( SLisExistenTodos ( p_lisObj, p_lis4 ) != 0 ) )
		{
			printf( "Error caso 5: de { 98, 99 } no esta ninguno\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisExistenTodos ( p_lisObj, p_lisVacia ) != 1 ) ||
			 ( SLisExisteAlguno ( p_lisObj, p_lisVacia ) != 0 ) )
		{
			printf( "Error caso 6: con valores vacios, Todos da 1 y Alguno 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisExistenTodos ( NULL, p_lis1 ) != 0 ) ||
			 ( SLisExisteAlguno ( p_lisObj, NULL ) != 0 ) )
		{
			printf( "Error caso 7: con listas nulas se esperaba 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisDestruir ( &p_lisObj );
	SLisDestruir ( &p_lis1 );
	SLisDestruir ( &p_lis2 );
	SLisDestruir ( &p_lis3 );
	SLisDestruir ( &p_lis4 );
	SLisDestruir ( &p_lisVacia );
	return ( iRes );
}

static int TestSLisInsertarLista01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisInsertarLista 01:\n" );

	int iDest [ 2 ] = { 1, 2 };
	int iVal [ 3 ] = { 7, 8, 9 };
	SLista * p_lisObj = CrearListaEnteros ( iDest, 2 );
	SLista * p_lisVal = CrearListaEnteros ( iVal, 3 );
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisVal ) )
	{
		/* Detras del cursor, en su orden. */
		SLisMoverA ( p_lisObj, 0 );
		if ( SLisInsertarLista ( p_lisObj, p_lisVal ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al insertar la lista\n" );
			iRes = BOOL_VAL_FALSO;
		}
		int iEsp1 [ 5 ] = { 1, 7, 8, 9, 2 };
		if ( ( VerificarCadena ( p_lisObj ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarContenido ( p_lisObj, iEsp1, 5 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 2: se esperaba { 1, 7, 8, 9, 2 } y la cadena entera\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisEstaVacia ( p_lisVal ) != 1 ) || ( SLisEsValida ( p_lisVal ) != 1 ) )
		{
			printf( "Error caso 3: la lista de valores deberia quedar vacia y valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Concatenar va al final, este donde este el cursor. */
		SLisInsertarAlFinal ( p_lisVal, CrearElementoEntero ( 5 ) );
		SLisInsertarAlFinal ( p_lisVal, CrearElementoEntero ( 6 ) );
		SLisMoverA ( p_lisObj, 1 );
		if ( SLisConcatenarLista ( p_lisObj, p_lisVal ) != 1 )
		{
			printf( "Error caso 4: se esperaba resultado 1 al concatenar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		int iEsp2 [ 7 ] = { 1, 7, 8, 9, 2, 5, 6 };
		if ( ( VerificarCadena ( p_lisObj ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarContenido ( p_lisObj, iEsp2, 7 ) != BOOL_VAL_CIERTO ) ||
			 ( SLisEstaVacia ( p_lisVal ) != 1 ) )
		{
			printf( "Error caso 5: se esperaba { 1, 7, 8, 9, 2, 5, 6 } y los valores vacios\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Sin cursor en un destino no vacio no se puede insertar: no se pierde nada. */
		SLisInsertarAlFinal ( p_lisVal, CrearElementoEntero ( 3 ) );
		SLisInsertarAlFinal ( p_lisVal, CrearElementoEntero ( 4 ) );
		SLisDeposicionar ( p_lisObj );
		if ( SLisInsertarLista ( p_lisObj, p_lisVal ) != 0 )
		{
			printf( "Error caso 6: sin cursor se esperaba resultado 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		int iEsp3 [ 2 ] = { 3, 4 };
		if ( ( VerificarCadena ( p_lisVal ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarContenido ( p_lisVal, iEsp3, 2 ) != BOOL_VAL_CIERTO ) ||
			 ( SLisNumElementos ( p_lisObj ) != 7 ) )
		{
			printf( "Error caso 7: al fallar, los valores deberian seguir { 3, 4 } y el destino con 7\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisConcatenarLista ( p_lisObj, p_lisObj ) != 0 ) ||
			 ( SLisInsertarLista ( p_lisObj, p_lisObj ) != 0 ) ||
			 ( SLisNumElementos ( p_lisObj ) != 7 ) )
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
	SLisDestruir ( &p_lisObj );
	SLisDestruir ( &p_lisVal );
	return ( iRes );
}

static int TestSLisListaDup01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisListaDup 01:\n" );

	int iDest [ 2 ] = { 1, 2 };
	int iVal [ 2 ] = { 7, 8 };
	SLista * p_lisObj = CrearListaEnteros ( iDest, 2 );
	SLista * p_lisVal = CrearListaEnteros ( iVal, 2 );
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisVal ) )
	{
		SLisMoverA ( p_lisObj, 0 );
		if ( SLisInsertarListaDup ( p_lisObj, p_lisVal ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al insertar copias\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisConcatenarListaDup ( p_lisObj, p_lisVal ) != 1 )
		{
			printf( "Error caso 2: se esperaba resultado 1 al concatenar copias\n" );
			iRes = BOOL_VAL_FALSO;
		}
		int iEsp [ 6 ] = { 1, 7, 8, 2, 7, 8 };
		if ( ( VerificarCadena ( p_lisObj ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarContenido ( p_lisObj, iEsp, 6 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 3: se esperaba { 1, 7, 8, 2, 7, 8 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Los valores no se tocan, y las copias son elementos propios. */
		if ( ( VerificarContenido ( p_lisVal, iVal, 2 ) != BOOL_VAL_CIERTO ) ||
			 ( SLisElemento ( p_lisObj, 1 ) == SLisElemento ( p_lisVal, 0 ) ) ||
			 ( SElmDatos ( SLisElemento ( p_lisObj, 1 ) ) == SElmDatos ( SLisElemento ( p_lisVal, 0 ) ) ) )
		{
			printf( "Error caso 4: los valores deberian quedar intactos y sin compartir datos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisConcatenarListaDup ( p_lisVal, p_lisVal ) != 0 ) ||
			 ( SLisInsertarListaDup ( p_lisVal, p_lisVal ) != 0 ) )
		{
			printf( "Error caso 5: con la misma lista se esperaba 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisDestruir ( &p_lisObj );
	SLisDestruir ( &p_lisVal );
	return ( iRes );
}

static int TestSLisExtraerLista01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisExtraerLista 01:\n" );

	int iVal [ 6 ] = { 20, 10, 20, 30, 40, 20 };
	int iBus [ 4 ] = { 20, 40, 99, 20 };
	SLista * p_lisObj = CrearListaEnteros ( iVal, 6 );
	SLista * p_lisBus = CrearListaEnteros ( iBus, 4 );
	SLista * p_lisRes = NULL;
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisBus ) )
	{
		/* Todas las apariciones de cada valor buscado, en el orden de los buscados: el
		   20 esta tres veces y sale entero con el primero; el 99 no esta. */
		p_lisRes = SLisExtraerLista ( p_lisObj, p_lisBus );
		int iEspRes [ 4 ] = { 20, 20, 20, 40 };
		int iEspObj [ 2 ] = { 10, 30 };
		if ( ES_NULO ( p_lisRes ) ||
			 ( VerificarCadena ( p_lisRes ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarContenido ( p_lisRes, iEspRes, 4 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 1: se esperaba extraer { 20, 20, 20, 40 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( VerificarCadena ( p_lisObj ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarContenido ( p_lisObj, iEspObj, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 2: en el origen deberia quedar { 10, 30 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SLisExtraerLista ( p_lisObj, p_lisObj ) ) )
		{
			printf( "Error caso 3: con la misma lista se esperaba nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisDestruir ( &p_lisObj );
	SLisDestruir ( &p_lisBus );
	SLisDestruir ( &p_lisRes );
	return ( iRes );
}

/* Destruye todas las apariciones de cada valor buscado; los valores no cambian. */
static int TestSLisEliminarLista01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisEliminarLista 01:\n" );

	int iVal [ 6 ] = { 20, 10, 20, 30, 40, 20 };
	int iBus [ 4 ] = { 20, 40, 99, 20 };
	SLista * p_lisObj = CrearListaEnteros ( iVal, 6 );
	SLista * p_lisBus = CrearListaEnteros ( iBus, 4 );
	SLista * p_lisVacia = SLisCrear ();
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisBus ) && ES_VALIDO ( p_lisVacia ) )
	{
		/* El 99 no esta y se ignora; el 20 esta tres veces y se van todas, aunque
		   tambien este dos veces en los buscados. */
		if ( SLisEliminarLista ( p_lisObj, p_lisBus ) != 1 )
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
		if ( ( SLisEliminarLista ( p_lisObj, p_lisBus ) != 1 ) ||
			 ( SLisEliminarLista ( p_lisObj, p_lisVacia ) != 1 ) ||
			 ( VerificarContenido ( p_lisObj, iEspObj, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 4: sin nada que eliminar se esperaba 1 sin cambios\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisEliminarLista ( p_lisObj, p_lisObj ) != 0 ) ||
			 ( VerificarContenido ( p_lisObj, iEspObj, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 5: con la misma lista se esperaba 0 sin cambios\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisEliminarLista ( p_lisObj, NULL ) != 0 ) || ( SLisEliminarLista ( NULL, p_lisBus ) != 0 ) )
		{
			printf( "Error caso 6: con una lista nula se esperaba 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisDestruir ( &p_lisObj );
	SLisDestruir ( &p_lisBus );
	SLisDestruir ( &p_lisVacia );
	return ( iRes );
}

static int TestSLisConjuntos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisConjuntos 01:\n" );

	int iV1 [ 4 ] = { 1, 2, 3, 4 };
	int iV2 [ 3 ] = { 4, 2, 5 };
	SLista * p_lis1 = CrearListaEnteros ( iV1, 4 );
	SLista * p_lis2 = CrearListaEnteros ( iV2, 3 );
	SLista * p_lisVacia = SLisCrear ();
	if ( ES_VALIDO ( p_lis1 ) && ES_VALIDO ( p_lis2 ) && ES_VALIDO ( p_lisVacia ) )
	{
		/* La union es concatenacion: el 2 y el 4 salen dos veces. */
		SLista * p_lisRes = SLisUnion ( p_lis1, p_lis2 );
		int iEspU [ 7 ] = { 1, 2, 3, 4, 4, 2, 5 };
		if ( ES_NULO ( p_lisRes ) || ( VerificarContenido ( p_lisRes, iEspU, 7 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 1: la union deberia ser { 1, 2, 3, 4, 4, 2, 5 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisDestruir ( &p_lisRes );

		/* Interseccion en el orden de V1. */
		p_lisRes = SLisInterseccion ( p_lis1, p_lis2 );
		int iEspI [ 2 ] = { 2, 4 };
		if ( ES_NULO ( p_lisRes ) || ( VerificarContenido ( p_lisRes, iEspI, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 2: la interseccion deberia ser { 2, 4 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisDestruir ( &p_lisRes );

		/* Diferencia V1 - V2, en el orden de V1. */
		p_lisRes = SLisDiferencia ( p_lis1, p_lis2 );
		int iEspD [ 2 ] = { 1, 3 };
		if ( ES_NULO ( p_lisRes ) || ( VerificarContenido ( p_lisRes, iEspD, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 3: la diferencia deberia ser { 1, 3 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisDestruir ( &p_lisRes );

		if ( ( VerificarContenido ( p_lis1, iV1, 4 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarContenido ( p_lis2, iV2, 3 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 4: las listas de entrada no deberian cambiar\n" );
			iRes = BOOL_VAL_FALSO;
		}

		/* Con una vacia: lista nueva vacia, no nulo. */
		p_lisRes = SLisInterseccion ( p_lis1, p_lisVacia );
		if ( ES_NULO ( p_lisRes ) || ( SLisEstaVacia ( p_lisRes ) != 1 ) )
		{
			printf( "Error caso 5: la interseccion con una vacia deberia ser una lista vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisDestruir ( &p_lisRes );
		p_lisRes = SLisDiferencia ( p_lis1, p_lisVacia );
		if ( ES_NULO ( p_lisRes ) || ( VerificarContenido ( p_lisRes, iV1, 4 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 6: V1 menos una vacia deberia ser V1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisDestruir ( &p_lisRes );

		if ( ES_VALIDO ( SLisUnion ( p_lis1, NULL ) ) ||
			 ES_VALIDO ( SLisInterseccion ( NULL, p_lis2 ) ) ||
			 ES_VALIDO ( SLisDiferencia ( p_lis1, NULL ) ) )
		{
			printf( "Error caso 7: con listas nulas se esperaba nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisDestruir ( &p_lis1 );
	SLisDestruir ( &p_lis2 );
	SLisDestruir ( &p_lisVacia );
	ErrLimpiar ();
	return ( iRes );
}

/* La copia es otra lista, con otros nodos y otros bloques, y los mismos valores
   en el mismo orden; el original no cambia, ni su cursor. */
static int TestSLisDuplicar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisDuplicar 01:\n" );

	int iVal [ 3 ] = { 10, 20, 30 };
	SLista * p_lisObj = CrearListaEnteros ( iVal, 3 );
	SLista * p_lisVacia = SLisCrear ();
	SLista * p_lisDup = NULL;
	SLista * p_lisDupVacia = NULL;
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisVacia ) )
	{
		SLisMoverA ( p_lisObj, 1 );
		SElemento * p_elmActual = SLisActual ( p_lisObj );
		p_lisDup = SLisDuplicar ( p_lisObj );
		/* Antes de VerificarContenido, que mueve el cursor al inicio. */
		if ( ( SLisPosicion ( p_lisObj ) != 1 ) || ( SLisActual ( p_lisObj ) != p_elmActual ) )
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
			if ( ( SLisElemento ( p_lisDup, 0 ) == SLisElemento ( p_lisObj, 0 ) ) ||
				 ( SElmDatos ( SLisElemento ( p_lisDup, 0 ) ) == SElmDatos ( SLisElemento ( p_lisObj, 0 ) ) ) )
			{
				printf( "Error caso 4: la copia no deberia compartir nodos ni bloques\n" );
				iRes = BOOL_VAL_FALSO;
			}
			SElmEscribirEntero ( SLisElemento ( p_lisDup, 2 ), 99 );
			if ( VerificarContenido ( p_lisObj, iVal, 3 ) != BOOL_VAL_CIERTO )
			{
				printf( "Error caso 5: cambiar la copia no deberia tocar el original\n" );
				iRes = BOOL_VAL_FALSO;
			}
		}
		/* La vacia se copia en otra vacia, no en nulo. */
		p_lisDupVacia = SLisDuplicar ( p_lisVacia );
		if ( ES_NULO ( p_lisDupVacia ) || ( SLisEsValida ( p_lisDupVacia ) != 1 ) ||
			 ( SLisNumElementos ( p_lisDupVacia ) != 0 ) )
		{
			printf( "Error caso 6: la copia de una vacia deberia ser otra vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SLisDuplicar ( NULL ) ) )
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
	SLisDestruir ( &p_lisObj );
	SLisDestruir ( &p_lisVacia );
	SLisDestruir ( &p_lisDup );
	SLisDestruir ( &p_lisDupVacia );
	return ( iRes );
}


/* 1 solo con el cursor sobre un elemento: no en una vacia, ni deposicionada,
   ni con la lista nula. */
static int TestSLisEstaPosicionada01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisEstaPosicionada 01:\n" );

	SLista * p_lisObj = SLisCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( SLisEstaPosicionada ( p_lisObj ) != 0 )
		{
			printf( "Error caso 1: una lista vacia no deberia estar posicionada\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisInsertarAlFinal ( p_lisObj, SElmCrearEntero () );
		SLisInsertarAlFinal ( p_lisObj, SElmCrearEntero () );
		SLisInicio ( p_lisObj );
		if ( SLisEstaPosicionada ( p_lisObj ) != 1 )
		{
			printf( "Error caso 2: tras Inicio deberia estar posicionada\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisSiguiente ( p_lisObj );
		SLisSiguiente ( p_lisObj );
		if ( SLisEstaPosicionada ( p_lisObj ) != 0 )
		{
			printf( "Error caso 3: pasado el ultimo no deberia estar posicionada\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisFinal ( p_lisObj );
		SLisDeposicionar ( p_lisObj );
		if ( SLisEstaPosicionada ( p_lisObj ) != 0 )
		{
			printf( "Error caso 4: tras Deposicionar no deberia estar posicionada\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisEstaPosicionada ( NULL ) != 0 )
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
	SLisDestruir ( &p_lisObj );
	return ( iRes );
}

int TestSLista ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SLista]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSLisCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisInsertarAlFinal01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisInsertarAlInicio01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisInsertarElem01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisCursor01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisBuscar01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisBuscarElem01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisBuscarSiguiente01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisRepeticiones01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisEliminar01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisExtraer01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisVaciar01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisInvalidos01 () == BOOL_VAL_CIERTO )  &&
			( TestSLisElementoIndice01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisExisten01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisInsertarLista01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisListaDup01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisExtraerLista01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisEliminarLista01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisConjuntos01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisDuplicar01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisEstaPosicionada01 () == BOOL_VAL_CIERTO ) )
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
