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
			( TestSLisEliminar01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisExtraer01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisVaciar01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisInvalidos01 () == BOOL_VAL_CIERTO )  &&
			( TestSLisElementoIndice01 () == BOOL_VAL_CIERTO ) )
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
