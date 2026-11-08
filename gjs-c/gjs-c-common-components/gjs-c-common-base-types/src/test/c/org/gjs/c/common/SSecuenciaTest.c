#include "Base.h"

#include "SSecuencia.h"
#include "SElemento.h"



static SElemento * CrearElemEntero ( int iValor )
{
	SElemento * p_elmObj = SElmCrearEntero ();
	if ( ES_VALIDO ( p_elmObj ) )
	{
		SElmEscribirEntero ( p_elmObj, iValor );
	}
	return ( p_elmObj );
}

static int ValorElem ( SSecuencia * p_secObj, int iElem )
{
	return ( SElmEntero ( SSecElemento ( p_secObj, iElem ) ) );
}



static SSecuencia * CrearSecEnteros ( int * p_iValores, int iNum )
{
	SSecuencia * p_secObj = SSecCrear ();
	int iPos = 0;
	while ( ES_VALIDO ( p_secObj ) && ( iPos < iNum ) )
	{
		SSecInsertar ( p_secObj, CrearElemEntero ( p_iValores [ iPos ] ) );
		iPos = iPos + 1;
	}
	return ( p_secObj );
}

static SLista * CrearListaEnteros ( int * p_iValores, int iNum )
{
	SLista * p_lisObj = SLisCrear ();
	int iPos = 0;
	while ( ES_VALIDO ( p_lisObj ) && ( iPos < iNum ) )
	{
		SLisInsertarAlFinal ( p_lisObj, CrearElemEntero ( p_iValores [ iPos ] ) );
		iPos = iPos + 1;
	}
	return ( p_lisObj );
}

/* Recorre la lista por la cadena comprobando numero y orden de los valores. */
static int VerificarLista ( SLista * p_lisObj, int * p_iEsperados, int iNum )
{
	int iRes = BOOL_VAL_CIERTO;
	if ( SLisNumElementos ( p_lisObj ) != iNum )
	{
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		SElemento * p_elmObj = SLisElemento ( p_lisObj, 0 );
		int iPos = 0;
		while ( ( iRes == BOOL_VAL_CIERTO ) && ( iPos < iNum ) )
		{
			if ( ES_NULO ( p_elmObj ) )
			{
				iRes = BOOL_VAL_FALSO;
			}
			else
			{
				if ( SElmEntero ( p_elmObj ) != p_iEsperados [ iPos ] )
				{
					iRes = BOOL_VAL_FALSO;
				}
				p_elmObj = SElmSucesor ( p_elmObj );
			}
			iPos = iPos + 1;
		}
	}
	return ( iRes );
}

static int VerificarSec ( SSecuencia * p_secObj, int * p_iEsperados, int iNum )
{
	int iRes;
	if ( SSecEsValida ( p_secObj ) == 1 )
	{
		iRes = VerificarLista ( SSecLista ( p_secObj ), p_iEsperados, iNum );
	}
	else
	{
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

/* Comprueba una secuencia devuelta por una operacion y la destruye. */
static int VerificarYDestruir ( SSecuencia ** p_p_secObj, int * p_iEsperados, int iNum )
{
	int iRes = VerificarSec ( *p_p_secObj, p_iEsperados, iNum );
	SSecDestruir ( p_p_secObj );
	return ( iRes );
}

static int TestSSecOperaciones01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecOperaciones 01:\n" );

	/* La secuencia posee los elementos insertados ( se liberan al destruir/vaciar ). */
	SSecuencia * p_secObj = SSecCrear ();
	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ( SSecEsValida ( p_secObj ) != 1 ) || ( SSecEstaVacia ( p_secObj ) != 1 ) )
		{
			printf( "Error caso 1: la secuencia recien creada deberia ser valida y vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecInsertar ( p_secObj, CrearElemEntero ( 11 ) ) != 1 ) ||
			 ( SSecInsertar ( p_secObj, CrearElemEntero ( 22 ) ) != 1 ) )
		{
			printf( "Error caso 2: se esperaba poder insertar los dos elementos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecNumElementos ( p_secObj ) != 2 ) || ( ValorElem ( p_secObj, 0 ) != 11 ) )
		{
			printf( "Error caso 3: deberia haber 2 elementos y el primero valer 11\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Eliminar el primero: la secuencia libera ese elemento y se desplaza el resto. */
		if ( ( SSecEliminar ( p_secObj, 0 ) != 1 ) ||
			 ( SSecNumElementos ( p_secObj ) != 1 ) || ( ValorElem ( p_secObj, 0 ) != 22 ) )
		{
			printf( "Error caso 4: tras eliminar el primero deberia quedar el 22\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SSecVaciar ( p_secObj );
		if ( SSecNumElementos ( p_secObj ) != 0 )
		{
			printf( "Error caso 5: tras vaciar no deberia quedar ningun elemento\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la secuencia\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecDestruir ( &p_secObj );

	if ( ES_VALIDO ( p_secObj ) )
	{
		printf( "Error caso 6: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSSecExtraer01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecExtraer 01:\n" );

	SSecuencia * p_secObj = SSecCrear ();
	if ( ES_VALIDO ( p_secObj ) )
	{
		/* Secuencia vacia: no hay nada que extraer. */
		if ( ES_VALIDO ( SSecExtraer ( p_secObj, 0 ) ) )
		{
			printf( "Error caso 1: extraer de una secuencia vacia deberia devolver nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SSecInsertar ( p_secObj, CrearElemEntero ( 10 ) );
		SSecInsertar ( p_secObj, CrearElemEntero ( 20 ) );
		SSecInsertar ( p_secObj, CrearElemEntero ( 30 ) );
		SSecInsertar ( p_secObj, CrearElemEntero ( 40 ) );

		/* Se extrae el mismo elemento que habia, vivo y desenganchado de la secuencia. */
		SElemento * p_elmEsp = SSecElemento ( p_secObj, 1 );
		SElemento * p_elmExt = SSecExtraer ( p_secObj, 1 );
		if ( ES_NULO ( p_elmExt ) || ( p_elmExt != p_elmEsp ) || ( SElmEntero ( p_elmExt ) != 20 ) )
		{
			printf( "Error caso 2: se esperaba extraer el 20 de la posicion 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else if ( ES_VALIDO ( SElmSucesor ( p_elmExt ) ) || ES_VALIDO ( SElmAntecesor ( p_elmExt ) ) )
		{
			printf( "Error caso 3: el elemento extraido no deberia conservar enlaces\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecNumElementos ( p_secObj ) != 3 ) ||
			 ( ValorElem ( p_secObj, 0 ) != 10 ) ||
			 ( ValorElem ( p_secObj, 1 ) != 30 ) ||
			 ( ValorElem ( p_secObj, 2 ) != 40 ) )
		{
			printf( "Error caso 4: tras extraer deberian quedar 10, 30 y 40\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Posiciones fuera de rango: nulo, y la secuencia no cambia. */
		if ( ES_VALIDO ( SSecExtraer ( p_secObj, -1 ) ) || ES_VALIDO ( SSecExtraer ( p_secObj, 3 ) ) )
		{
			printf( "Error caso 5: extraer fuera de rango deberia devolver nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SSecNumElementos ( p_secObj ) != 3 )
		{
			printf( "Error caso 6: extraer fuera de rango no deberia cambiar la secuencia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* El extraido se puede volver a insertar: la secuencia lo pone al final. */
		if ( ES_VALIDO ( p_elmExt ) )
		{
			if ( SSecInsertar ( p_secObj, p_elmExt ) != 1 )
			{
				printf( "Error caso 7: el elemento extraido deberia poder volver a insertarse\n" );
				iRes = BOOL_VAL_FALSO;
				SElmDestruir ( &p_elmExt );
			}
			else if ( SSecElemento ( p_secObj, 3 ) != p_elmExt )
			{
				printf( "Error caso 8: al reinsertarlo deberia quedar al final\n" );
				iRes = BOOL_VAL_FALSO;
			}
		}
		/* Los extremos; los extraidos son ya del llamador. */
		p_elmExt = SSecExtraer ( p_secObj, 0 );
		if ( ES_NULO ( p_elmExt ) || ( SElmEntero ( p_elmExt ) != 10 ) )
		{
			printf( "Error caso 9: extraer la posicion 0 deberia dar el 10\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SElmDestruir ( &p_elmExt );
		p_elmExt = SSecExtraer ( p_secObj, SSecNumElementos ( p_secObj ) - 1 );
		if ( ES_NULO ( p_elmExt ) || ( SElmEntero ( p_elmExt ) != 20 ) )
		{
			printf( "Error caso 10: extraer la ultima posicion deberia dar el 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SElmDestruir ( &p_elmExt );
		if ( ( SSecNumElementos ( p_secObj ) != 2 ) ||
			 ( ValorElem ( p_secObj, 0 ) != 30 ) ||
			 ( ValorElem ( p_secObj, 1 ) != 40 ) )
		{
			printf( "Error caso 11: deberian quedar el 30 y el 40\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SSecExtraer ( NULL, 0 ) ) )
		{
			printf( "Error caso 12: extraer de una secuencia nula deberia devolver nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la secuencia\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecDestruir ( &p_secObj );
	return ( iRes );
}

/* CrearDesdeLista y Duplicar copian; EncapsularLista se queda con la lista. */
static int TestSSecCrearDesdeLista01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecCrearDesdeLista 01:\n" );

	int iVal [ 3 ] = { 10, 20, 30 };
	SLista * p_lisObj = CrearListaEnteros ( iVal, 3 );
	SLista * p_lisEnc = CrearListaEnteros ( iVal, 3 );
	SLista * p_lisVacia = SLisCrear ();
	SSecuencia * p_secObj = NULL;
	SSecuencia * p_secDup = NULL;
	SSecuencia * p_secEnc = NULL;
	SSecuencia * p_secVacia = NULL;
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisEnc ) && ES_VALIDO ( p_lisVacia ) )
	{
		p_secObj = SSecCrearDesdeLista ( p_lisObj );
		if ( ( VerificarSec ( p_secObj, iVal, 3 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarLista ( p_lisObj, iVal, 3 ) != BOOL_VAL_CIERTO ) ||
			 ( SSecElemento ( p_secObj, 0 ) == SLisElemento ( p_lisObj, 0 ) ) )
		{
			printf( "Error caso 1: se esperaban copias de { 10, 20, 30 } y la lista intacta\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_secDup = SSecDuplicar ( p_secObj );
		if ( ( VerificarSec ( p_secDup, iVal, 3 ) != BOOL_VAL_CIERTO ) ||
			 ( SSecElemento ( p_secDup, 0 ) == SSecElemento ( p_secObj, 0 ) ) )
		{
			printf( "Error caso 2: el duplicado deberia tener copias de { 10, 20, 30 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Encapsulada, la lista es de la secuencia: se destruye con ella. */
		p_secEnc = SSecEncapsularLista ( p_lisEnc );
		if ( ES_NULO ( p_secEnc ) || ( SSecLista ( p_secEnc ) != p_lisEnc ) )
		{
			printf( "Error caso 3: la secuencia deberia envolver la misma lista\n" );
			iRes = BOOL_VAL_FALSO;
			SLisDestruir ( &p_lisEnc );
		}
		p_secVacia = SSecCrearDesdeLista ( p_lisVacia );
		if ( ( SSecEsValida ( p_secVacia ) != 1 ) || ( SSecEstaVacia ( p_secVacia ) != 1 ) )
		{
			printf( "Error caso 4: de una lista vacia se esperaba una secuencia vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SSecCrearDesdeLista ( NULL ) ) || ES_VALIDO ( SSecEncapsularLista ( NULL ) ) ||
			 ES_VALIDO ( SSecDuplicar ( NULL ) ) )
		{
			printf( "Error caso 5: con una lista o secuencia nula se esperaba nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
		SLisDestruir ( &p_lisEnc );
	}
	SLisDestruir ( &p_lisObj );
	SLisDestruir ( &p_lisVacia );
	SSecDestruir ( &p_secObj );
	SSecDestruir ( &p_secDup );
	SSecDestruir ( &p_secEnc );
	SSecDestruir ( &p_secVacia );
	return ( iRes );
}

/* Busca por contenido: vale un elemento que no esta en la secuencia. */
static int TestSSecBuscar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecBuscar 01:\n" );

	int iVal [ 4 ] = { 10, 20, 30, 20 };
	SSecuencia * p_secObj = CrearSecEnteros ( iVal, 4 );
	SElemento * p_elm20 = CrearElemEntero ( 20 );
	SElemento * p_elm99 = CrearElemEntero ( 99 );
	if ( ES_VALIDO ( p_secObj ) && ES_VALIDO ( p_elm20 ) && ES_VALIDO ( p_elm99 ) )
	{
		if ( SSecBuscar ( p_secObj, p_elm20 ) != 1 )
		{
			printf( "Error caso 1: el 20 deberia estar en la posicion 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SSecBuscar ( p_secObj, p_elm99 ) != -1 )
		{
			printf( "Error caso 2: el 99 no deberia encontrarse\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecBuscar ( p_secObj, NULL ) != -1 ) || ( SSecBuscar ( NULL, p_elm20 ) != -1 ) )
		{
			printf( "Error caso 3: con un nulo se esperaba -1\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear la secuencia o los elementos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SElmDestruir ( &p_elm20 );
	SElmDestruir ( &p_elm99 );
	SSecDestruir ( &p_secObj );
	return ( iRes );
}

/* Existen, Concatenar y Eliminar, con secuencias y con listas. */
/* Recorre los repetidos con BuscarPrimero / BuscarSiguiente; Existe y
   Repeticiones. */
static int TestSSecBuscarSiguiente01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecBuscarSiguiente 01:\n" );

	int iVal [ 6 ] = { 20, 10, 20, 30, 20, 40 };
	SSecuencia * p_secObj = CrearSecEnteros ( iVal, 6 );
	SSecuencia * p_secVacia = SSecCrear ();
	SElemento * p_elm20 = CrearElemEntero ( 20 );
	SElemento * p_elm99 = CrearElemEntero ( 99 );
	if ( ES_VALIDO ( p_secObj ) && ES_VALIDO ( p_secVacia ) && ES_VALIDO ( p_elm20 ) && ES_VALIDO ( p_elm99 ) )
	{
		if ( ( SSecBuscarPrimero ( p_secObj, p_elm20 ) != 0 ) ||
			 ( SSecBuscarSiguiente ( p_secObj, p_elm20, 0 ) != 2 ) ||
			 ( SSecBuscarSiguiente ( p_secObj, p_elm20, 2 ) != 4 ) ||
			 ( SSecBuscarSiguiente ( p_secObj, p_elm20, 4 ) != -1 ) )
		{
			printf( "Error caso 1: el 20 deberia estar en 0, 2 y 4\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Desde la posicion siguiente, no desde la misma. */
		if ( ( SSecBuscarSiguiente ( p_secObj, p_elm20, 1 ) != 2 ) ||
			 ( SSecBuscarSiguiente ( p_secObj, p_elm20, 3 ) != 4 ) ||
			 ( SSecBuscar ( p_secObj, p_elm20 ) != 0 ) )
		{
			printf( "Error caso 2: detras de la 1 el 20 esta en la 2, y Buscar es BuscarPrimero\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecRepeticiones ( p_secObj, p_elm20 ) != 3 ) || ( SSecExiste ( p_secObj, p_elm20 ) != 1 ) ||
			 ( SSecRepeticiones ( p_secObj, p_elm99 ) != 0 ) || ( SSecExiste ( p_secObj, p_elm99 ) != 0 ) ||
			 ( SSecBuscarPrimero ( p_secObj, p_elm99 ) != -1 ) )
		{
			printf( "Error caso 3: el 20 deberia estar 3 veces y el 99 ninguna\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecRepeticiones ( p_secVacia, p_elm20 ) != 0 ) || ( SSecExiste ( p_secVacia, p_elm20 ) != 0 ) ||
			 ( SSecBuscarPrimero ( p_secVacia, p_elm20 ) != -1 ) )
		{
			printf( "Error caso 4: en una secuencia vacia no deberia estar nada\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecBuscarSiguiente ( p_secObj, p_elm20, 5 ) != -1 ) ||
			 ( SSecBuscarSiguiente ( p_secObj, p_elm20, -2 ) != -1 ) )
		{
			printf( "Error caso 5: desde el final o con una posicion menor que -1 se esperaba -1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecBuscarSiguiente ( NULL, p_elm20, -1 ) != -1 ) || ( SSecBuscarSiguiente ( p_secObj, NULL, -1 ) != -1 ) ||
			 ( SSecBuscarPrimero ( NULL, p_elm20 ) != -1 ) ||
			 ( SSecRepeticiones ( NULL, p_elm20 ) != 0 ) || ( SSecRepeticiones ( p_secObj, NULL ) != 0 ) ||
			 ( SSecExiste ( NULL, p_elm20 ) != 0 ) || ( SSecExiste ( p_secObj, NULL ) != 0 ) )
		{
			printf( "Error caso 6: con un nulo se esperaba -1 al buscar y 0 al contar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las secuencias o los elementos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SElmDestruir ( &p_elm20 );
	SElmDestruir ( &p_elm99 );
	SSecDestruir ( &p_secObj );
	SSecDestruir ( &p_secVacia );
	return ( iRes );
}

static int TestSSecOperacionesListas01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecOperacionesListas 01:\n" );

	int iVal [ 4 ] = { 1, 2, 3, 4 };
	int iSec [ 2 ] = { 4, 2 };
	int iLis [ 2 ] = { 2, 5 };
	int iUno [ 1 ] = { 1 };
	int iDos [ 1 ] = { 2 };
	int iTres [ 1 ] = { 3 };
	int iCuatro [ 1 ] = { 4 };
	int iCinco [ 1 ] = { 5 };
	int iEli [ 3 ] = { 2, 4, 99 };
	SSecuencia * p_secObj = CrearSecEnteros ( iVal, 4 );
	SSecuencia * p_secVal = CrearSecEnteros ( iSec, 2 );
	SLista * p_lisVal = CrearListaEnteros ( iLis, 2 );
	SSecuencia * p_secA = CrearSecEnteros ( iUno, 1 );
	SSecuencia * p_secMov = CrearSecEnteros ( iDos, 1 );
	SLista * p_lisMov = CrearListaEnteros ( iTres, 1 );
	SSecuencia * p_secDup = CrearSecEnteros ( iCuatro, 1 );
	SLista * p_lisDup = CrearListaEnteros ( iCinco, 1 );
	SSecuencia * p_secEli = CrearSecEnteros ( iEli, 3 );
	SLista * p_lisEli = CrearListaEnteros ( iCinco, 1 );
	if ( ES_VALIDO ( p_secObj ) && ES_VALIDO ( p_secVal ) && ES_VALIDO ( p_lisVal ) && ES_VALIDO ( p_secA ) &&
		 ES_VALIDO ( p_secMov ) && ES_VALIDO ( p_lisMov ) && ES_VALIDO ( p_secDup ) && ES_VALIDO ( p_lisDup ) &&
		 ES_VALIDO ( p_secEli ) && ES_VALIDO ( p_lisEli ) )
	{
		if ( ( SSecExistenTodos ( p_secObj, p_secVal ) != 1 ) || ( SSecExisteAlguno ( p_secObj, p_secVal ) != 1 ) ||
			 ( SSecExistenTodosLista ( p_secObj, p_lisVal ) != 0 ) || ( SSecExisteAlgunoLista ( p_secObj, p_lisVal ) != 1 ) )
		{
			printf( "Error caso 1: { 4, 2 } estan todos; de { 2, 5 } solo alguno\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecExistenTodos ( p_secObj, NULL ) != 0 ) || ( SSecExistenTodos ( NULL, p_secVal ) != 0 ) ||
			 ( SSecExisteAlgunoLista ( NULL, p_lisVal ) != 0 ) )
		{
			printf( "Error caso 2: con un nulo se esperaba 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Sin Dup se mueven: el origen queda vacio. Con Dup se copian. */
		int iEsp [ 5 ] = { 1, 2, 3, 4, 5 };
		if ( ( SSecConcatenar ( p_secA, p_secMov ) != 1 ) || ( SSecConcatenarLista ( p_secA, p_lisMov ) != 1 ) ||
			 ( SSecConcatenarDup ( p_secA, p_secDup ) != 1 ) || ( SSecConcatenarListaDup ( p_secA, p_lisDup ) != 1 ) ||
			 ( VerificarSec ( p_secA, iEsp, 5 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 3: tras concatenar deberia quedar { 1, 2, 3, 4, 5 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecEstaVacia ( p_secMov ) != 1 ) || ( SSecEsValida ( p_secMov ) != 1 ) ||
			 ( SLisEstaVacia ( p_lisMov ) != 1 ) ||
			 ( VerificarSec ( p_secDup, iCuatro, 1 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarLista ( p_lisDup, iCinco, 1 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 4: las movidas deberian quedar vacias y las copiadas intactas\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecConcatenar ( p_secA, p_secA ) != 0 ) || ( SSecConcatenarLista ( p_secA, NULL ) != 0 ) ||
			 ( SSecConcatenarDup ( NULL, p_secDup ) != 0 ) || ( VerificarSec ( p_secA, iEsp, 5 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 5: con la misma secuencia o una nula se esperaba 0 sin cambios\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* El 99 no esta y se ignora. */
		int iQueda [ 2 ] = { 1, 3 };
		if ( ( SSecEliminarSecuencia ( p_secA, p_secEli ) != 1 ) || ( SSecEliminarLista ( p_secA, p_lisEli ) != 1 ) ||
			 ( VerificarSec ( p_secA, iQueda, 2 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarSec ( p_secEli, iEli, 3 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 6: tras eliminar deberia quedar { 1, 3 } y los valores intactos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecEliminarSecuencia ( p_secA, p_secA ) != 0 ) || ( SSecEliminarLista ( p_secA, NULL ) != 0 ) ||
			 ( SSecEliminarLista ( NULL, p_lisEli ) != 0 ) || ( VerificarSec ( p_secA, iQueda, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 7: con la misma secuencia o una nula se esperaba 0 sin cambios\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las secuencias\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecDestruir ( &p_secObj );
	SSecDestruir ( &p_secVal );
	SLisDestruir ( &p_lisVal );
	SSecDestruir ( &p_secA );
	SSecDestruir ( &p_secMov );
	SLisDestruir ( &p_lisMov );
	SSecDestruir ( &p_secDup );
	SLisDestruir ( &p_lisDup );
	SSecDestruir ( &p_secEli );
	SLisDestruir ( &p_lisEli );
	return ( iRes );
}

/* Saca una aparicion por valor; si la de SLista falla, nulo y no una secuencia
   sin lista. */
static int TestSSecExtraerSecuencia01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecExtraerSecuencia 01:\n" );

	int iVal [ 5 ] = { 10, 20, 30, 20, 40 };
	int iBus [ 4 ] = { 20, 40, 99, 20 };
	int iTreinta [ 1 ] = { 30 };
	SSecuencia * p_secObj = CrearSecEnteros ( iVal, 5 );
	SSecuencia * p_secBus = CrearSecEnteros ( iBus, 4 );
	SLista * p_lisBus = CrearListaEnteros ( iTreinta, 1 );
	if ( ES_VALIDO ( p_secObj ) && ES_VALIDO ( p_secBus ) && ES_VALIDO ( p_lisBus ) )
	{
		SSecuencia * p_secRes = SSecExtraerSecuencia ( p_secObj, p_secBus );
		int iEspRes [ 3 ] = { 20, 40, 20 };
		int iEspObj [ 2 ] = { 10, 30 };
		if ( ( VerificarYDestruir ( &p_secRes, iEspRes, 3 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarSec ( p_secObj, iEspObj, 2 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarSec ( p_secBus, iBus, 4 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 1: se esperaba extraer { 20, 40, 20 } y dejar { 10, 30 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_secRes = SSecExtraerLista ( p_secObj, p_lisBus );
		int iEspObj2 [ 1 ] = { 10 };
		if ( ( VerificarYDestruir ( &p_secRes, iTreinta, 1 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarSec ( p_secObj, iEspObj2, 1 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 2: se esperaba extraer { 30 } y dejar { 10 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SSecExtraerSecuencia ( p_secObj, p_secObj ) ) ||
			 ES_VALIDO ( SSecExtraerLista ( p_secObj, SSecLista ( p_secObj ) ) ) ||
			 ES_VALIDO ( SSecExtraerLista ( p_secObj, NULL ) ) ||
			 ES_VALIDO ( SSecExtraerSecuencia ( NULL, p_secBus ) ) ||
			 ( VerificarSec ( p_secObj, iEspObj2, 1 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 3: con la misma secuencia o una nula se esperaba nulo sin cambios\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las secuencias\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecDestruir ( &p_secObj );
	SSecDestruir ( &p_secBus );
	SLisDestruir ( &p_lisBus );
	return ( iRes );
}

/* La union es la concatenacion; la interseccion y la diferencia, en el orden
   de la primera. */
static int TestSSecConjuntos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecConjuntos 01:\n" );

	int iV1 [ 4 ] = { 1, 2, 3, 4 };
	int iV2 [ 3 ] = { 4, 2, 5 };
	SSecuencia * p_sec1 = CrearSecEnteros ( iV1, 4 );
	SSecuencia * p_sec2 = CrearSecEnteros ( iV2, 3 );
	SLista * p_lis2 = CrearListaEnteros ( iV2, 3 );
	if ( ES_VALIDO ( p_sec1 ) && ES_VALIDO ( p_sec2 ) && ES_VALIDO ( p_lis2 ) )
	{
		int iUnion [ 7 ] = { 1, 2, 3, 4, 4, 2, 5 };
		int iInter [ 2 ] = { 2, 4 };
		int iDif [ 2 ] = { 1, 3 };
		SSecuencia * p_secRes = SSecUnion ( p_sec1, p_sec2 );
		if ( VerificarYDestruir ( &p_secRes, iUnion, 7 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 1: la union deberia ser { 1, 2, 3, 4, 4, 2, 5 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_secRes = SSecInterseccion ( p_sec1, p_sec2 );
		if ( VerificarYDestruir ( &p_secRes, iInter, 2 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 2: la interseccion deberia ser { 2, 4 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_secRes = SSecDiferencia ( p_sec1, p_sec2 );
		if ( VerificarYDestruir ( &p_secRes, iDif, 2 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 3: la diferencia deberia ser { 1, 3 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_secRes = SSecUnionLista ( p_sec1, p_lis2 );
		if ( VerificarYDestruir ( &p_secRes, iUnion, 7 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 4: la union con la lista deberia ser { 1, 2, 3, 4, 4, 2, 5 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_secRes = SSecInterseccionLista ( p_sec1, p_lis2 );
		if ( VerificarYDestruir ( &p_secRes, iInter, 2 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 5: la interseccion con la lista deberia ser { 2, 4 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_secRes = SSecDiferenciaLista ( p_sec1, p_lis2 );
		if ( VerificarYDestruir ( &p_secRes, iDif, 2 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 6: la diferencia con la lista deberia ser { 1, 3 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( VerificarSec ( p_sec1, iV1, 4 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarSec ( p_sec2, iV2, 3 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarLista ( p_lis2, iV2, 3 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 7: los operandos no deberian cambiar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SSecUnion ( p_sec1, NULL ) ) || ES_VALIDO ( SSecUnion ( NULL, p_sec2 ) ) ||
			 ES_VALIDO ( SSecInterseccionLista ( p_sec1, NULL ) ) || ES_VALIDO ( SSecDiferenciaLista ( NULL, p_lis2 ) ) )
		{
			printf( "Error caso 8: con un nulo se esperaba nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las secuencias\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecDestruir ( &p_sec1 );
	SSecDestruir ( &p_sec2 );
	SLisDestruir ( &p_lis2 );
	return ( iRes );
}

static int TestSSecInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecInvalidos 01:\n" );

	if ( SSecEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: una secuencia nula no deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SSecEstaVacia ( NULL ) != 1 )
	{
		printf( "Error caso 2: una secuencia nula deberia considerarse vacia\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SSecElemento ( NULL, 0 ) ) )
	{
		printf( "Error caso 3: el elemento de una secuencia nula deberia ser nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecuencia * p_secNula = NULL;
	SSecDestruir ( &p_secNula );
	return ( iRes );
}



int TestSSecuencia ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SSecuencia]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSSecOperaciones01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecExtraer01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecCrearDesdeLista01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecBuscar01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecBuscarSiguiente01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecOperacionesListas01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecExtraerSecuencia01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecConjuntos01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecInvalidos01 () == BOOL_VAL_CIERTO ) )
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
