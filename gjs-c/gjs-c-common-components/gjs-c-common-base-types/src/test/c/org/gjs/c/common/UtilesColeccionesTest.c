#include "Base.h"

#include "UtilesColecciones.h"



#define TAM_ENTERO		( (int) sizeof ( int ) )



static int iNumDuplicados = 0;

static byte * NuevoEntero ( int iDato )
{
	int * p_iRes = (int *) MemReservar ( sizeof ( int ) );
	if ( ES_VALIDO ( p_iRes ) )
	{
		*p_iRes = iDato;
	}
	return ( (byte *) p_iRes );
}

static int Entero ( byte * p_byDatos )
{
	int iRes = -999;
	if ( ES_VALIDO ( p_byDatos ) )
	{
		iRes = *( (int *) p_byDatos );
	}
	return ( iRes );
}

static byte * DuplicarEntero ( byte * p_byDatos )
{
	iNumDuplicados = iNumDuplicados + 1;
	return ( NuevoEntero ( Entero ( p_byDatos ) ) );
}

static SLista * ListaEnteros ( int iVal1, int iVal2, int iVal3 )
{
	int iValores [ 3 ] = { iVal1, iVal2, iVal3 };
	SLista * p_lisRes = SLisCrear ();
	for ( int i = 0; i < 3; i = i + 1 )
	{
		SElemento * p_elmObj = SElmCrearEntero ();
		SElmEscribirEntero ( p_elmObj, iValores [ i ] );
		SLisInsertarAlFinal ( p_lisRes, p_elmObj );
	}
	return ( p_lisRes );
}

static int CompararEnteros ( void * p_vVal1, void * p_vVal2 )
{
	int iVal1 = *( (int *) p_vVal1 );
	int iVal2 = *( (int *) p_vVal2 );
	int iRes = 0;

	if ( iVal1 < iVal2 )
	{
		iRes = -1;
	}
	else if ( iVal1 > iVal2 )
	{
		iRes = 1;
	}
	return ( iRes );
}

static SListaPtr * ListaPtrEnteros ( int iVal1, int iVal2, int iVal3 )
{
	SListaPtr * p_lisRes = SLispCrear ();
	SLispInsertarAlFinal ( p_lisRes, NuevoEntero ( iVal1 ) );
	SLispInsertarAlFinal ( p_lisRes, NuevoEntero ( iVal2 ) );
	SLispInsertarAlFinal ( p_lisRes, NuevoEntero ( iVal3 ) );
	return ( p_lisRes );
}



static int TestUtlColNodos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test UtlColNodos 01:\n" );

	SElemento * p_elmObj = SElmCrearEntero ();
	SElmEscribirEntero ( p_elmObj, 4321 );

	SContenido * p_conObj = SElmConvertirAContenido ( p_elmObj );
	if ( ES_NULO ( p_conObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al convertir a contenido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SConEntero ( p_conObj ) != 4321 )
		{
			printf( "Error caso 2: el contenido deberia tener 4321: %d\n", SConEntero ( p_conObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SConLiberacionMemoriaActivada ( p_conObj ) != 1 )
		{
			printf( "Error caso 3: el contenido deberia ser duenno de su bloque\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Copia: no comparte el bloque con el elemento. */
		SElmEscribirEntero ( p_elmObj, 1234 );
		if ( SConEntero ( p_conObj ) != 4321 )
		{
			printf( "Error caso 4: el contenido no deberia cambiar con el elemento: %d\n", SConEntero ( p_conObj ) );
			iRes = BOOL_VAL_FALSO;
		}

		SElemento * p_elmVuelta = SConConvertirAElemento ( p_conObj );
		if ( ES_NULO ( p_elmVuelta ) )
		{
			printf( "Error caso 5: no se esperaba nulo al convertir a elemento\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			if ( SElmEntero ( p_elmVuelta ) != 4321 )
			{
				printf( "Error caso 6: el elemento deberia tener 4321: %d\n", SElmEntero ( p_elmVuelta ) );
				iRes = BOOL_VAL_FALSO;
			}
			if ( SElmLiberacionMemoriaActivada ( p_elmVuelta ) != 1 )
			{
				printf( "Error caso 7: el elemento deberia ser duenno de su bloque\n" );
				iRes = BOOL_VAL_FALSO;
			}
			if ( SElmTieneSucesor ( p_elmVuelta ) != 0 )
			{
				printf( "Error caso 8: el elemento nuevo no deberia estar encadenado\n" );
				iRes = BOOL_VAL_FALSO;
			}
			SConEscribirEntero ( p_conObj, 99 );
			if ( SElmEntero ( p_elmVuelta ) != 4321 )
			{
				printf( "Error caso 9: el elemento no deberia cambiar con el contenido: %d\n", SElmEntero ( p_elmVuelta ) );
				iRes = BOOL_VAL_FALSO;
			}
		}
		SElmDestruir ( &p_elmVuelta );
	}
	SConDestruir ( &p_conObj );
	SElmDestruir ( &p_elmObj );

	if ( ES_VALIDO ( SElmConvertirAContenido ( NULL ) ) )
	{
		printf( "Error caso 10: convertir un elemento nulo deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SConConvertirAElemento ( NULL ) ) )
	{
		printf( "Error caso 11: convertir un contenido nulo deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestUtlColLista01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test UtlColLista 01:\n" );

	SLista * p_lisObj = ListaEnteros ( 10, 20, 30 );
	SVector * p_vecObj = SLisConvertirAVector ( p_lisObj );
	if ( ES_NULO ( p_vecObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al convertir la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SVecNumElementos ( p_vecObj ) != 3 )
		{
			printf( "Error caso 2: se esperaban 3 elementos: %d\n", SVecNumElementos ( p_vecObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SConEntero ( SVecElemento ( p_vecObj, 0 ) ) != 10 ) ||
			 ( SConEntero ( SVecElemento ( p_vecObj, 1 ) ) != 20 ) ||
			 ( SConEntero ( SVecElemento ( p_vecObj, 2 ) ) != 30 ) )
		{
			printf( "Error caso 3: se esperaba 10, 20, 30 en el vector\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* La lista sigue intacta y no comparte datos con el vector. */
		SElmEscribirEntero ( SLisElemento ( p_lisObj, 0 ), 11 );
		if ( SConEntero ( SVecElemento ( p_vecObj, 0 ) ) != 10 )
		{
			printf( "Error caso 4: el vector no deberia cambiar con la lista\n" );
			iRes = BOOL_VAL_FALSO;
		}

		SLista * p_lisVuelta = SVecConvertirALista ( p_vecObj );
		if ( ES_NULO ( p_lisVuelta ) )
		{
			printf( "Error caso 5: no se esperaba nulo al convertir el vector\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			if ( SLisNumElementos ( p_lisVuelta ) != 3 )
			{
				printf( "Error caso 6: se esperaban 3 elementos: %d\n", SLisNumElementos ( p_lisVuelta ) );
				iRes = BOOL_VAL_FALSO;
			}
			if ( ( SElmEntero ( SLisElemento ( p_lisVuelta, 0 ) ) != 10 ) ||
				 ( SElmEntero ( SLisElemento ( p_lisVuelta, 1 ) ) != 20 ) ||
				 ( SElmEntero ( SLisElemento ( p_lisVuelta, 2 ) ) != 30 ) )
			{
				printf( "Error caso 7: se esperaba 10, 20, 30 en la lista\n" );
				iRes = BOOL_VAL_FALSO;
			}
		}
		SLisDestruir ( &p_lisVuelta );
	}
	SVecDestruir ( &p_vecObj );
	SLisDestruir ( &p_lisObj );

	/* Un vector no puede estar vacio: la lista vacia no se convierte. */
	SLista * p_lisVacia = SLisCrear ();
	if ( ES_VALIDO ( SLisConvertirAVector ( p_lisVacia ) ) )
	{
		printf( "Error caso 8: la lista vacia deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisDestruir ( &p_lisVacia );

	/* Una posicion vacia del vector es un error. */
	SVector * p_vecHueco = SVecCrear ( 2 );
	SContenido * p_conObj = SConCrearEntero ();
	SConEscribirEntero ( p_conObj, 5 );
	SVecAsignar ( p_vecHueco, 0, p_conObj );
	if ( ES_VALIDO ( SVecConvertirALista ( p_vecHueco ) ) )
	{
		printf( "Error caso 9: un vector con huecos deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SVecDestruir ( &p_vecHueco );

	if ( ES_VALIDO ( SLisConvertirAVector ( NULL ) ) )
	{
		printf( "Error caso 10: convertir una lista nula deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SVecConvertirALista ( NULL ) ) )
	{
		printf( "Error caso 11: convertir un vector nulo deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestUtlColListaPtr01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test UtlColListaPtr 01:\n" );

	SListaPtr * p_lisObj = ListaPtrEnteros ( 7, 8, 9 );
	SVectorPtr * p_vecObj = SLispConvertirAVector ( p_lisObj, TAM_ENTERO );
	if ( ES_NULO ( p_vecObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al convertir la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SVecpNumElementos ( p_vecObj ) != 3 )
		{
			printf( "Error caso 2: se esperaban 3 elementos: %d\n", SVecpNumElementos ( p_vecObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( Entero ( SVecpElemento ( p_vecObj, 0 ) ) != 7 ) ||
			 ( Entero ( SVecpElemento ( p_vecObj, 1 ) ) != 8 ) ||
			 ( Entero ( SVecpElemento ( p_vecObj, 2 ) ) != 9 ) )
		{
			printf( "Error caso 3: se esperaba 7, 8, 9 en el vector\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SVecpElemento ( p_vecObj, 0 ) == SLispElemento ( p_lisObj, 0 ) )
		{
			printf( "Error caso 4: el vector deberia tener copias, no los mismos punteros\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SVecpLiberacionMemoriaActivada ( p_vecObj ) != 1 )
		{
			printf( "Error caso 5: el vector deberia ser duenno de las copias\n" );
			iRes = BOOL_VAL_FALSO;
		}

		SListaPtr * p_lisVuelta = SVecpConvertirALista ( p_vecObj, TAM_ENTERO );
		if ( ES_NULO ( p_lisVuelta ) )
		{
			printf( "Error caso 6: no se esperaba nulo al convertir el vector\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			if ( SLispNumElementos ( p_lisVuelta ) != 3 )
			{
				printf( "Error caso 7: se esperaban 3 elementos: %d\n", SLispNumElementos ( p_lisVuelta ) );
				iRes = BOOL_VAL_FALSO;
			}
			if ( ( Entero ( SLispElemento ( p_lisVuelta, 0 ) ) != 7 ) ||
				 ( Entero ( SLispElemento ( p_lisVuelta, 1 ) ) != 8 ) ||
				 ( Entero ( SLispElemento ( p_lisVuelta, 2 ) ) != 9 ) )
			{
				printf( "Error caso 8: se esperaba 7, 8, 9 en la lista\n" );
				iRes = BOOL_VAL_FALSO;
			}
			if ( SLispElemento ( p_lisVuelta, 0 ) == SVecpElemento ( p_vecObj, 0 ) )
			{
				printf( "Error caso 9: la lista deberia tener copias, no los mismos punteros\n" );
				iRes = BOOL_VAL_FALSO;
			}
			if ( SLispLiberacionMemoriaActivada ( p_lisVuelta ) != 1 )
			{
				printf( "Error caso 10: la lista deberia ser duenna de las copias\n" );
				iRes = BOOL_VAL_FALSO;
			}
		}
		SLispDestruir ( &p_lisVuelta );
	}
	SVecpDestruir ( &p_vecObj );

	if ( ES_VALIDO ( SLispConvertirAVector ( p_lisObj, 0 ) ) )
	{
		printf( "Error caso 11: con 0 bytes deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLispDestruir ( &p_lisObj );

	SListaPtr * p_lisVacia = SLispCrear ();
	if ( ES_VALIDO ( SLispConvertirAVector ( p_lisVacia, TAM_ENTERO ) ) )
	{
		printf( "Error caso 12: la lista vacia deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLispDestruir ( &p_lisVacia );

	SVectorPtr * p_vecHueco = SVecpCrear ( 2 );
	SVecpActivarLiberacionMemoria ( p_vecHueco );
	SVecpAsignar ( p_vecHueco, 1, NuevoEntero ( 5 ) );
	if ( ES_VALIDO ( SVecpConvertirALista ( p_vecHueco, TAM_ENTERO ) ) )
	{
		printf( "Error caso 13: un vector con huecos deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SVecpConvertirALista ( p_vecHueco, 0 ) ) )
	{
		printf( "Error caso 14: con 0 bytes deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SVecpDestruir ( &p_vecHueco );

	if ( ES_VALIDO ( SLispConvertirAVector ( NULL, TAM_ENTERO ) ) )
	{
		printf( "Error caso 15: convertir una lista nula deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SVecpConvertirALista ( NULL, TAM_ENTERO ) ) )
	{
		printf( "Error caso 16: convertir un vector nulo deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestUtlColListaPtrExt01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test UtlColListaPtrExt 01:\n" );

	SListaPtr * p_lisObj = ListaPtrEnteros ( 4, 5, 6 );
	iNumDuplicados = 0;
	SVectorPtr * p_vecObj = SLispConvertirAVectorExt ( p_lisObj, DuplicarEntero );
	if ( ES_NULO ( p_vecObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al convertir la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( iNumDuplicados != 3 )
		{
			printf( "Error caso 2: se esperaban 3 llamadas a la funcion: %d\n", iNumDuplicados );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( Entero ( SVecpElemento ( p_vecObj, 0 ) ) != 4 ) ||
			 ( Entero ( SVecpElemento ( p_vecObj, 1 ) ) != 5 ) ||
			 ( Entero ( SVecpElemento ( p_vecObj, 2 ) ) != 6 ) )
		{
			printf( "Error caso 3: se esperaba 4, 5, 6 en el vector\n" );
			iRes = BOOL_VAL_FALSO;
		}

		iNumDuplicados = 0;
		SListaPtr * p_lisVuelta = SVecpConvertirAListaExt ( p_vecObj, DuplicarEntero );
		if ( ES_NULO ( p_lisVuelta ) )
		{
			printf( "Error caso 4: no se esperaba nulo al convertir el vector\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			if ( iNumDuplicados != 3 )
			{
				printf( "Error caso 5: se esperaban 3 llamadas a la funcion: %d\n", iNumDuplicados );
				iRes = BOOL_VAL_FALSO;
			}
			if ( ( Entero ( SLispElemento ( p_lisVuelta, 0 ) ) != 4 ) ||
				 ( Entero ( SLispElemento ( p_lisVuelta, 1 ) ) != 5 ) ||
				 ( Entero ( SLispElemento ( p_lisVuelta, 2 ) ) != 6 ) )
			{
				printf( "Error caso 6: se esperaba 4, 5, 6 en la lista\n" );
				iRes = BOOL_VAL_FALSO;
			}
		}
		SLispDestruir ( &p_lisVuelta );

		if ( ES_VALIDO ( SVecpConvertirAListaExt ( p_vecObj, NULL ) ) )
		{
			printf( "Error caso 7: sin funcion de duplicado deberia dar nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SVecpDestruir ( &p_vecObj );

	if ( ES_VALIDO ( SLispConvertirAVectorExt ( p_lisObj, NULL ) ) )
	{
		printf( "Error caso 8: sin funcion de duplicado deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLispDestruir ( &p_lisObj );
	return ( iRes );
}


/* { 3, 1, 3 } da el conjunto { 1, 3 }, ordenado y sin repetidos, y vuelve a
   la secuencia { 1, 3 }; siempre con copias, sin tocar el origen. */
static int TestUtlColConjunto01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test UtlColConjunto 01:\n" );

	SLista * p_lisVal = ListaEnteros ( 3, 1, 3 );
	SSecuencia * p_secObj = SSecEncapsularLista ( p_lisVal );
	SConjunto * p_cnjObj = SSecConvertirAConjunto ( p_secObj, CompararEnteros );
	SSecuencia * p_secVuelta = NULL;
	if ( ES_NULO ( p_cnjObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al convertir la secuencia\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( ( SCnjNumElementos ( p_cnjObj ) != 2 ) ||
			 ( SElmEntero ( SCnjElemento ( p_cnjObj, 0 ) ) != 1 ) ||
			 ( SElmEntero ( SCnjElemento ( p_cnjObj, 1 ) ) != 3 ) )
		{
			printf( "Error caso 2: se esperaba el conjunto { 1, 3 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecNumElementos ( p_secObj ) != 3 ) || ( SCnjElemento ( p_cnjObj, 0 ) == SSecElemento ( p_secObj, 1 ) ) )
		{
			printf( "Error caso 3: la secuencia deberia seguir con 3 y el conjunto tener copias\n" );
			iRes = BOOL_VAL_FALSO;
		}

		p_secVuelta = SCnjConvertirASecuencia ( p_cnjObj );
		if ( ES_NULO ( p_secVuelta ) )
		{
			printf( "Error caso 4: no se esperaba nulo al convertir el conjunto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			if ( ( SSecNumElementos ( p_secVuelta ) != 2 ) ||
				 ( SElmEntero ( SSecElemento ( p_secVuelta, 0 ) ) != 1 ) ||
				 ( SElmEntero ( SSecElemento ( p_secVuelta, 1 ) ) != 3 ) )
			{
				printf( "Error caso 5: se esperaba la secuencia { 1, 3 }\n" );
				iRes = BOOL_VAL_FALSO;
			}
			if ( ( SCnjNumElementos ( p_cnjObj ) != 2 ) || ( SSecElemento ( p_secVuelta, 0 ) == SCnjElemento ( p_cnjObj, 0 ) ) )
			{
				printf( "Error caso 6: el conjunto deberia seguir con 2 y la secuencia tener copias\n" );
				iRes = BOOL_VAL_FALSO;
			}
		}
	}

	/* Vacias en los dos sentidos: no son un error. */
	SSecuencia * p_secVacia = SSecCrear ();
	SConjunto * p_cnjVacio = SSecConvertirAConjunto ( p_secVacia, CompararEnteros );
	SSecuencia * p_secDeVacio = SCnjConvertirASecuencia ( p_cnjVacio );
	if ( ES_NULO ( p_cnjVacio ) || ( SCnjNumElementos ( p_cnjVacio ) != 0 ) ||
		 ES_NULO ( p_secDeVacio ) || ( SSecNumElementos ( p_secDeVacio ) != 0 ) )
	{
		printf( "Error caso 7: de vacia se esperaba vacio, y de vacio, vacia\n" );
		iRes = BOOL_VAL_FALSO;
	}

	if ( ES_VALIDO ( SSecConvertirAConjunto ( NULL, CompararEnteros ) ) ||
		 ES_VALIDO ( SSecConvertirAConjunto ( p_secObj, NULL ) ) ||
		 ES_VALIDO ( SCnjConvertirASecuencia ( NULL ) ) )
	{
		printf( "Error caso 8: con argumentos nulos se esperaba nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecDestruir ( &p_secObj );
	SCnjDestruir ( &p_cnjObj );
	SSecDestruir ( &p_secVuelta );
	SSecDestruir ( &p_secVacia );
	SCnjDestruir ( &p_cnjVacio );
	SSecDestruir ( &p_secDeVacio );
	return ( iRes );
}

static int TestUtlColConjuntoPtr01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test UtlColConjuntoPtr 01:\n" );

	SListaPtr * p_lisVal = ListaPtrEnteros ( 3, 1, 3 );
	SSecuenciaPtr * p_secObj = SSecpEncapsularLista ( p_lisVal );
	SConjuntoPtr * p_cnjObj = SSecpConvertirAConjunto ( p_secObj, CompararEnteros, TAM_ENTERO );
	SSecuenciaPtr * p_secVuelta = NULL;
	if ( ES_NULO ( p_cnjObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al convertir la secuencia\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( ( SCnjpNumElementos ( p_cnjObj ) != 2 ) ||
			 ( Entero ( SCnjpElemento ( p_cnjObj, 0 ) ) != 1 ) ||
			 ( Entero ( SCnjpElemento ( p_cnjObj, 1 ) ) != 3 ) )
		{
			printf( "Error caso 2: se esperaba el conjunto { 1, 3 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecpNumElementos ( p_secObj ) != 3 ) || ( SCnjpElemento ( p_cnjObj, 0 ) == SSecpElemento ( p_secObj, 1 ) ) ||
			 ( SCnjpLiberacionMemoriaActivada ( p_cnjObj ) != 1 ) )
		{
			printf( "Error caso 3: la secuencia deberia seguir con 3 y el conjunto ser dueno de sus copias\n" );
			iRes = BOOL_VAL_FALSO;
		}

		p_secVuelta = SCnjpConvertirASecuencia ( p_cnjObj, TAM_ENTERO );
		if ( ES_NULO ( p_secVuelta ) )
		{
			printf( "Error caso 4: no se esperaba nulo al convertir el conjunto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			if ( ( SSecpNumElementos ( p_secVuelta ) != 2 ) ||
				 ( Entero ( SSecpElemento ( p_secVuelta, 0 ) ) != 1 ) ||
				 ( Entero ( SSecpElemento ( p_secVuelta, 1 ) ) != 3 ) )
			{
				printf( "Error caso 5: se esperaba la secuencia { 1, 3 }\n" );
				iRes = BOOL_VAL_FALSO;
			}
			if ( ( SSecpElemento ( p_secVuelta, 0 ) == SCnjpElemento ( p_cnjObj, 0 ) ) ||
				 ( SSecpLiberacionMemoriaActivada ( p_secVuelta ) != 1 ) )
			{
				printf( "Error caso 6: la secuencia deberia ser duena de sus copias\n" );
				iRes = BOOL_VAL_FALSO;
			}
		}
		if ( ES_VALIDO ( SCnjpConvertirASecuencia ( p_cnjObj, 0 ) ) )
		{
			printf( "Error caso 7: con 0 bytes se esperaba nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}

	if ( ES_VALIDO ( SSecpConvertirAConjunto ( p_secObj, CompararEnteros, 0 ) ) ||
		 ES_VALIDO ( SSecpConvertirAConjunto ( NULL, CompararEnteros, TAM_ENTERO ) ) ||
		 ES_VALIDO ( SSecpConvertirAConjunto ( p_secObj, NULL, TAM_ENTERO ) ) ||
		 ES_VALIDO ( SCnjpConvertirASecuencia ( NULL, TAM_ENTERO ) ) )
	{
		printf( "Error caso 8: con 0 bytes o argumentos nulos se esperaba nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecpDestruir ( &p_secObj );
	SCnjpDestruir ( &p_cnjObj );
	SSecpDestruir ( &p_secVuelta );
	return ( iRes );
}

static int TestUtlColConjuntoPtrExt01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test UtlColConjuntoPtrExt 01:\n" );

	SListaPtr * p_lisVal = ListaPtrEnteros ( 3, 1, 3 );
	SSecuenciaPtr * p_secObj = SSecpEncapsularLista ( p_lisVal );
	iNumDuplicados = 0;
	SConjuntoPtr * p_cnjObj = SSecpConvertirAConjuntoExt ( p_secObj, CompararEnteros, DuplicarEntero );
	SSecuenciaPtr * p_secVuelta = NULL;
	if ( ES_NULO ( p_cnjObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al convertir la secuencia\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		/* El 3 repetido no se copia. */
		if ( iNumDuplicados != 2 )
		{
			printf( "Error caso 2: se esperaban 2 llamadas a la funcion: %d\n", iNumDuplicados );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SCnjpNumElementos ( p_cnjObj ) != 2 ) ||
			 ( Entero ( SCnjpElemento ( p_cnjObj, 0 ) ) != 1 ) ||
			 ( Entero ( SCnjpElemento ( p_cnjObj, 1 ) ) != 3 ) )
		{
			printf( "Error caso 3: se esperaba el conjunto { 1, 3 }\n" );
			iRes = BOOL_VAL_FALSO;
		}

		iNumDuplicados = 0;
		p_secVuelta = SCnjpConvertirASecuenciaExt ( p_cnjObj, DuplicarEntero );
		if ( ES_NULO ( p_secVuelta ) )
		{
			printf( "Error caso 4: no se esperaba nulo al convertir el conjunto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			if ( iNumDuplicados != 2 )
			{
				printf( "Error caso 5: se esperaban 2 llamadas a la funcion: %d\n", iNumDuplicados );
				iRes = BOOL_VAL_FALSO;
			}
			if ( ( SSecpNumElementos ( p_secVuelta ) != 2 ) ||
				 ( Entero ( SSecpElemento ( p_secVuelta, 0 ) ) != 1 ) ||
				 ( Entero ( SSecpElemento ( p_secVuelta, 1 ) ) != 3 ) )
			{
				printf( "Error caso 6: se esperaba la secuencia { 1, 3 }\n" );
				iRes = BOOL_VAL_FALSO;
			}
		}
		if ( ES_VALIDO ( SCnjpConvertirASecuenciaExt ( p_cnjObj, NULL ) ) )
		{
			printf( "Error caso 7: sin funcion de duplicado deberia dar nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}

	if ( ES_VALIDO ( SSecpConvertirAConjuntoExt ( p_secObj, CompararEnteros, NULL ) ) ||
		 ES_VALIDO ( SSecpConvertirAConjuntoExt ( NULL, CompararEnteros, DuplicarEntero ) ) ||
		 ES_VALIDO ( SCnjpConvertirASecuenciaExt ( NULL, DuplicarEntero ) ) )
	{
		printf( "Error caso 8: sin funcion de duplicado o con argumentos nulos deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecpDestruir ( &p_secObj );
	SCnjpDestruir ( &p_cnjObj );
	SSecpDestruir ( &p_secVuelta );
	return ( iRes );
}



int TestUtilesColecciones ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test UtilesColecciones]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestUtlColNodos01 () == BOOL_VAL_CIERTO ) &&
			( TestUtlColLista01 () == BOOL_VAL_CIERTO ) &&
			( TestUtlColListaPtr01 () == BOOL_VAL_CIERTO ) &&
			( TestUtlColListaPtrExt01 () == BOOL_VAL_CIERTO ) &&
			( TestUtlColConjunto01 () == BOOL_VAL_CIERTO ) &&
			( TestUtlColConjuntoPtr01 () == BOOL_VAL_CIERTO ) &&
			( TestUtlColConjuntoPtrExt01 () == BOOL_VAL_CIERTO ) )
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
