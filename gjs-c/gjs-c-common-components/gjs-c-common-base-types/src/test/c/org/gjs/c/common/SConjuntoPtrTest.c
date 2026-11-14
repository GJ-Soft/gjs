#include "Base.h"

#include "SConjuntoPtr.h"



static int CompararEnteros ( void * p_v1, void * p_v2 )
{
	int iRes;
	int i1 = *( (int *) p_v1 );
	int i2 = *( (int *) p_v2 );

	if ( i1 < i2 )
	{
		iRes = -1;
	}
	else if ( i1 > i2 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

static byte * CrearDatoEntero ( int iValor )
{
	int * p_iDato = (int *) MemReservar ( sizeof ( int ) );
	if ( ES_VALIDO ( p_iDato ) )
	{
		*p_iDato = iValor;
	}
	return ( (byte *) p_iDato );
}

static int ValorElem ( SConjuntoPtr * p_cnjObj, int iElem )
{
	return ( *( (int *) SCnjpElemento ( p_cnjObj, iElem ) ) );
}



static int TestSCnjpOperaciones01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjpOperaciones 01:\n" );

	/* La memoria de los datos la gestiona el test ( liberacion desactivada ). */
	byte * p_d1 = CrearDatoEntero ( 10 );
	byte * p_d2 = CrearDatoEntero ( 20 );
	byte * p_d3 = CrearDatoEntero ( 10 );
	byte * p_q99 = CrearDatoEntero ( 99 );
	SConjuntoPtr * p_cnjObj = SCnjpCrear ( CompararEnteros );
	if ( ES_VALIDO ( p_cnjObj ) && ES_VALIDO ( p_d1 ) && ES_VALIDO ( p_d2 ) && ES_VALIDO ( p_d3 ) && ES_VALIDO ( p_q99 ) )
	{
		SCnjpDesactivarLiberacionMemoria ( p_cnjObj );

		if ( ( SCnjpInsertarElem ( p_cnjObj, p_d1 ) != 1 ) || ( SCnjpInsertarElem ( p_cnjObj, p_d2 ) != 1 ) )
		{
			printf( "Error caso 1: se esperaba poder insertar 10 y 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Un valor ya presente ( 10 ) se rechaza: semantica de conjunto. */
		if ( SCnjpInsertarElem ( p_cnjObj, p_d3 ) == 1 )
		{
			printf( "Error caso 2: insertar un valor duplicado no deberia tener exito\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnjpNumElementos ( p_cnjObj ) != 2 )
		{
			printf( "Error caso 3: el conjunto deberia tener 2 elementos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Los elementos quedan ordenados. */
		if ( ( ValorElem ( p_cnjObj, 0 ) != 10 ) || ( ValorElem ( p_cnjObj, 1 ) != 20 ) )
		{
			printf( "Error caso 4: los elementos deberian estar ordenados ( 10, 20 )\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SCnjpExiste ( p_cnjObj, p_d1 ) != 1 ) || ( SCnjpExiste ( p_cnjObj, p_q99 ) != 0 ) )
		{
			printf( "Error caso 5: existe deberia encontrar 10 y no 99\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnjpBuscar ( p_cnjObj, p_d2 ) != 1 )
		{
			printf( "Error caso 6: buscar 20 deberia devolver el indice 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Eliminar el primero. */
		SCnjpEliminarElem ( p_cnjObj, 0 );
		if ( ( SCnjpNumElementos ( p_cnjObj ) != 1 ) || ( ValorElem ( p_cnjObj, 0 ) != 20 ) )
		{
			printf( "Error caso 7: tras eliminar el 10 deberia quedar solo el 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SCnjpVaciar ( p_cnjObj );
		if ( SCnjpNumElementos ( p_cnjObj ) != 0 )
		{
			printf( "Error caso 8: tras vaciar no deberia quedar ningun elemento\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear el conjunto o los datos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCnjpDestruir ( &p_cnjObj );
	/* El test libera sus propios datos. */
	MemLiberar ( (void **) &p_d1 );
	MemLiberar ( (void **) &p_d2 );
	MemLiberar ( (void **) &p_d3 );
	MemLiberar ( (void **) &p_q99 );
	return ( iRes );
}

static int TestSCnjpPrimeroUltimo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjpPrimeroUltimo 01:\n" );

	/* La memoria de los datos la gestiona el test ( liberacion desactivada ). */
	byte * p_d10 = CrearDatoEntero ( 10 );
	byte * p_d20 = CrearDatoEntero ( 20 );
	byte * p_d30 = CrearDatoEntero ( 30 );
	SConjuntoPtr * p_cnjObj = SCnjpCrear ( CompararEnteros );
	if ( ES_VALIDO ( p_cnjObj ) && ES_VALIDO ( p_d10 ) && ES_VALIDO ( p_d20 ) && ES_VALIDO ( p_d30 ) )
	{
		SCnjpDesactivarLiberacionMemoria ( p_cnjObj );

		/* Vacio: no hay ni primero ni ultimo. */
		if ( ES_VALIDO ( SCnjpPrimero ( p_cnjObj ) ) )
		{
			printf( "Error caso 1: el primero de un conjunto vacio deberia ser nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SCnjpUltimo ( p_cnjObj ) ) )
		{
			printf( "Error caso 2: el ultimo de un conjunto vacio deberia ser nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Con un solo elemento, primero y ultimo son el mismo puntero. */
		SCnjpInsertarElem ( p_cnjObj, p_d20 );
		if ( SCnjpPrimero ( p_cnjObj ) != p_d20 )
		{
			printf( "Error caso 3: con un elemento, el primero deberia ser el 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnjpUltimo ( p_cnjObj ) != p_d20 )
		{
			printf( "Error caso 4: con un elemento, el ultimo deberia ser el 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Se insertan por fuera de los extremos: primero y ultimo siguen el orden, no la insercion. */
		SCnjpInsertarElem ( p_cnjObj, p_d30 );
		SCnjpInsertarElem ( p_cnjObj, p_d10 );
		if ( SCnjpPrimero ( p_cnjObj ) != p_d10 )
		{
			printf( "Error caso 5: el primero deberia ser el 10\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnjpUltimo ( p_cnjObj ) != p_d30 )
		{
			printf( "Error caso 6: el ultimo deberia ser el 30\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Tras eliminar el ultimo, el nuevo ultimo es el 20. */
		SCnjpEliminarElem ( p_cnjObj, 2 );
		if ( SCnjpUltimo ( p_cnjObj ) != p_d20 )
		{
			printf( "Error caso 7: tras eliminar el 30, el ultimo deberia ser el 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SCnjpPrimero ( NULL ) ) || ES_VALIDO ( SCnjpUltimo ( NULL ) ) )
		{
			printf( "Error caso 8: primero y ultimo de un conjunto nulo deberian ser nulos\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear el conjunto o los datos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCnjpDestruir ( &p_cnjObj );
	/* El test libera sus propios datos. */
	MemLiberar ( (void **) &p_d10 );
	MemLiberar ( (void **) &p_d20 );
	MemLiberar ( (void **) &p_d30 );
	return ( iRes );
}

static int TestSCnjpPosicion01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjpPosicion 01:\n" );

	/* La memoria de los datos la gestiona el test ( liberacion desactivada ). */
	byte * p_d10 = CrearDatoEntero ( 10 );
	byte * p_d20 = CrearDatoEntero ( 20 );
	byte * p_d30 = CrearDatoEntero ( 30 );
	byte * p_q20 = CrearDatoEntero ( 20 );
	byte * p_q = CrearDatoEntero ( 0 );
	SConjuntoPtr * p_cnjObj = SCnjpCrear ( CompararEnteros );
	if ( ES_VALIDO ( p_cnjObj ) && ES_VALIDO ( p_d10 ) && ES_VALIDO ( p_d20 ) && ES_VALIDO ( p_d30 ) &&
		 ES_VALIDO ( p_q20 ) && ES_VALIDO ( p_q ) )
	{
		SCnjpDesactivarLiberacionMemoria ( p_cnjObj );

		/* Vacio: nada tiene posicion. */
		if ( SCnjpPosicion ( p_cnjObj, p_d20 ) != -1 )
		{
			printf( "Error caso 1: en un conjunto vacio la posicion deberia ser -1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SCnjpInsertarElem ( p_cnjObj, p_d30 );
		SCnjpInsertarElem ( p_cnjObj, p_d10 );
		SCnjpInsertarElem ( p_cnjObj, p_d20 );

		if ( ( SCnjpPosicion ( p_cnjObj, p_d10 ) != 0 ) ||
			 ( SCnjpPosicion ( p_cnjObj, p_d20 ) != 1 ) ||
			 ( SCnjpPosicion ( p_cnjObj, p_d30 ) != 2 ) )
		{
			printf( "Error caso 2: 10, 20 y 30 deberian estar en las posiciones 0, 1 y 2\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Posicion por valor: otro puntero con el mismo dato da la misma posicion. */
		if ( SCnjpPosicion ( p_cnjObj, p_q20 ) != 1 )
		{
			printf( "Error caso 3: un 20 en otro puntero deberia dar la posicion 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SCnjpPosicion ( p_cnjObj, SCnjpPrimero ( p_cnjObj ) ) != 0 ) ||
			 ( SCnjpPosicion ( p_cnjObj, SCnjpUltimo ( p_cnjObj ) ) != 2 ) )
		{
			printf( "Error caso 4: el primero y el ultimo deberian estar en las posiciones 0 y 2\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Valores que no estan: menor que el minimo, intermedio y mayor que el maximo. */
		*( (int *) p_q ) = 5;
		if ( SCnjpPosicion ( p_cnjObj, p_q ) != -1 )
		{
			printf( "Error caso 5: el 5 no deberia tener posicion\n" );
			iRes = BOOL_VAL_FALSO;
		}
		*( (int *) p_q ) = 15;
		if ( SCnjpPosicion ( p_cnjObj, p_q ) != -1 )
		{
			printf( "Error caso 6: el 15 no deberia tener posicion\n" );
			iRes = BOOL_VAL_FALSO;
		}
		*( (int *) p_q ) = 99;
		if ( SCnjpPosicion ( p_cnjObj, p_q ) != -1 )
		{
			printf( "Error caso 7: el 99 no deberia tener posicion\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnjpPosicion ( p_cnjObj, NULL ) != -1 )
		{
			printf( "Error caso 8: un dato nulo no deberia tener posicion\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnjpPosicion ( NULL, p_d20 ) != -1 )
		{
			printf( "Error caso 9: en un conjunto nulo la posicion deberia ser -1\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear el conjunto o los datos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCnjpDestruir ( &p_cnjObj );
	/* El test libera sus propios datos. */
	MemLiberar ( (void **) &p_d10 );
	MemLiberar ( (void **) &p_d20 );
	MemLiberar ( (void **) &p_d30 );
	MemLiberar ( (void **) &p_q20 );
	MemLiberar ( (void **) &p_q );
	return ( iRes );
}

static int TestSCnjpInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjpInvalidos 01:\n" );

	if ( SCnjpEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: un conjunto nulo no deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SCnjpNumElementos ( NULL ) != 0 )
	{
		printf( "Error caso 2: un conjunto nulo deberia tener 0 elementos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SCnjpEstaVacio ( NULL ) != 1 )
	{
		printf( "Error caso 3: un conjunto nulo deberia considerarse vacio\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SConjuntoPtr * p_cnjNulo = NULL;
	SCnjpDestruir ( &p_cnjNulo );
	return ( iRes );
}



/* Duplica contando las llamadas, para ver que las Ext copian con ella. */
static int iCopiasHechas = 0;

static byte * DuplicarEnteroContando ( byte * p_byDato )
{
	iCopiasHechas = iCopiasHechas + 1;
	return ( CrearDatoEntero ( *( (int *) p_byDato ) ) );
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

static SListaOrdenadaPtr * CrearOrdenadaEnteros ( int * p_iValores, int iNum )
{
	SListaOrdenadaPtr * p_lisObj = SLispOrdCrear ( CompararEnteros );
	int iPos = 0;
	while ( ES_VALIDO ( p_lisObj ) && ( iPos < iNum ) )
	{
		SLispOrdInsertarElem ( p_lisObj, CrearDatoEntero ( p_iValores [ iPos ] ) );
		iPos = iPos + 1;
	}
	return ( p_lisObj );
}

static SConjuntoPtr * CrearConjuntoEnteros ( int * p_iValores, int iNum )
{
	SListaPtr * p_lisObj = CrearListaEnteros ( p_iValores, iNum );
	SConjuntoPtr * p_cnjObj = SCnjpCrearDesdeLista ( p_lisObj, CompararEnteros, sizeof ( int ) );
	SLispDestruir ( &p_lisObj );
	return ( p_cnjObj );
}

/* Numero y valores, en orden, sin desreferenciar un nulo. */
static int VerificarConjunto ( SConjuntoPtr * p_cnjObj, int * p_iEsperados, int iNum )
{
	int iRes = BOOL_VAL_CIERTO;

	if ( ( SCnjpEsValido ( p_cnjObj ) != 1 ) || ( SCnjpNumElementos ( p_cnjObj ) != iNum ) )
	{
		printf( "  Verificacion: se esperaba un conjunto de %d elementos: %d\n", iNum, SCnjpNumElementos ( p_cnjObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	int iPos = 0;
	while ( ( iPos < iNum ) && ( iRes == BOOL_VAL_CIERTO ) )
	{
		byte * p_byDato = SCnjpElemento ( p_cnjObj, iPos );
		if ( ES_NULO ( p_byDato ) || ( *( (int *) p_byDato ) != p_iEsperados [ iPos ] ) )
		{
			printf( "  Verificacion: en pos %d se esperaba %d\n", iPos, p_iEsperados [ iPos ] );
			iRes = BOOL_VAL_FALSO;
		}
		iPos = iPos + 1;
	}
	return ( iRes );
}

/* Comprueba un conjunto devuelto por una operacion, que sea dueno de sus
   datos, y lo destruye. */
static int VerificarYDestruir ( SConjuntoPtr ** p_p_cnjObj, int * p_iEsperados, int iNum )
{
	int iRes = VerificarConjunto ( *p_p_cnjObj, p_iEsperados, iNum );
	if ( SCnjpLiberacionMemoriaActivada ( *p_p_cnjObj ) != 1 )
	{
		printf( "  Verificacion: el conjunto deberia ser dueno de sus datos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCnjpDestruir ( p_p_cnjObj );
	return ( iRes );
}

/* CrearDesdeLista y Duplicar copian y quitan los repetidos; EncapsularLista se
   queda con la lista, salvo que tenga repetidos. */
static int TestSCnjpCrearDesdeLista01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjpCrearDesdeLista 01:\n" );

	int iVal [ 5 ] = { 30, 10, 30, 20, 10 };
	int iEsp [ 3 ] = { 10, 20, 30 };
	int iRep [ 3 ] = { 20, 10, 20 };
	SListaPtr * p_lisVal = CrearListaEnteros ( iVal, 5 );
	SListaOrdenadaPtr * p_lisOrd = CrearOrdenadaEnteros ( iEsp, 3 );
	SListaOrdenadaPtr * p_lisRep = CrearOrdenadaEnteros ( iRep, 3 );
	SConjuntoPtr * p_cnjObj = NULL;
	SConjuntoPtr * p_cnjEnc = NULL;
	SConjuntoPtr * p_cnjRes = NULL;
	if ( ES_VALIDO ( p_lisVal ) && ES_VALIDO ( p_lisOrd ) && ES_VALIDO ( p_lisRep ) )
	{
		p_cnjObj = SCnjpCrearDesdeLista ( p_lisVal, CompararEnteros, sizeof ( int ) );
		if ( ( VerificarConjunto ( p_cnjObj, iEsp, 3 ) != BOOL_VAL_CIERTO ) ||
			 ( SCnjpLiberacionMemoriaActivada ( p_cnjObj ) != 1 ) ||
			 ( SLispNumElementos ( p_lisVal ) != 5 ) ||
			 ( SCnjpElemento ( p_cnjObj, 2 ) == SLispElemento ( p_lisVal, 0 ) ) )
		{
			printf( "Error caso 1: se esperaban copias propias de { 10, 20, 30 } y la lista sin tocar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		iCopiasHechas = 0;
		p_cnjRes = SCnjpCrearDesdeListaExt ( p_lisVal, CompararEnteros, DuplicarEnteroContando );
		if ( ( iCopiasHechas != 3 ) || ( VerificarYDestruir ( &p_cnjRes, iEsp, 3 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 2: con fDuplicar se esperaban 3 copias de { 10, 20, 30 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_cnjRes = SCnjpDuplicar ( p_cnjObj, sizeof ( int ) );
		if ( ( SCnjpElemento ( p_cnjRes, 0 ) == SCnjpElemento ( p_cnjObj, 0 ) ) ||
			 ( VerificarYDestruir ( &p_cnjRes, iEsp, 3 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 3: el duplicado deberia tener copias de { 10, 20, 30 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		iCopiasHechas = 0;
		p_cnjRes = SCnjpDuplicarExt ( p_cnjObj, DuplicarEnteroContando );
		if ( ( iCopiasHechas != 3 ) || ( VerificarYDestruir ( &p_cnjRes, iEsp, 3 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 4: el duplicado con fDuplicar deberia tener 3 copias\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_cnjEnc = SCnjpEncapsularLista ( p_lisOrd );
		if ( ( VerificarConjunto ( p_cnjEnc, iEsp, 3 ) != BOOL_VAL_CIERTO ) ||
			 ( SCnjpLista ( p_cnjEnc ) != p_lisOrd ) )
		{
			printf( "Error caso 5: se esperaba un conjunto con la misma lista\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			/* Ahora es del conjunto. */
			p_lisOrd = NULL;
		}
		if ( ES_VALIDO ( SCnjpEncapsularLista ( p_lisRep ) ) ||
			 ( SLispOrdNumElementos ( p_lisRep ) != 3 ) )
		{
			printf( "Error caso 6: con repetidos se esperaba nulo y la lista intacta\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SCnjpCrearDesdeLista ( NULL, CompararEnteros, sizeof ( int ) ) ) ||
			 ES_VALIDO ( SCnjpCrearDesdeListaExt ( p_lisVal, CompararEnteros, NULL ) ) ||
			 ES_VALIDO ( SCnjpEncapsularLista ( NULL ) ) ||
			 ES_VALIDO ( SCnjpDuplicar ( NULL, sizeof ( int ) ) ) ||
			 ES_VALIDO ( SCnjpLista ( NULL ) ) )
		{
			printf( "Error caso 7: con nulos se esperaba nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLispDestruir ( &p_lisVal );
	SLispOrdDestruir ( &p_lisOrd );
	SLispOrdDestruir ( &p_lisRep );
	SCnjpDestruir ( &p_cnjObj );
	SCnjpDestruir ( &p_cnjEnc );
	return ( iRes );
}

/* ElementoPtr, ExistePtr, BuscarPtr, ExtraerElem y ExtraerElemPtr. */
static int TestSCnjpExtraerElem01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjpExtraerElem 01:\n" );

	int iVal [ 4 ] = { 10, 20, 30, 40 };
	SConjuntoPtr * p_cnjObj = CrearConjuntoEnteros ( iVal, 4 );
	SElementoPtr * p_elpObj = NULL;
	byte * p_byDato = NULL;
	if ( ES_VALIDO ( p_cnjObj ) )
	{
		p_elpObj = SCnjpElementoPtr ( p_cnjObj, 2 );
		if ( ES_NULO ( p_elpObj ) || ( SElpDatos ( p_elpObj ) != SCnjpElemento ( p_cnjObj, 2 ) ) ||
			 ( SCnjpExistePtr ( p_cnjObj, p_elpObj ) != 1 ) || ( SCnjpBuscarPtr ( p_cnjObj, p_elpObj ) != 2 ) )
		{
			printf( "Error caso 1: el nodo 2 deberia tener el 30 y encontrarse en la posicion 2\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_elpObj = NULL;
		p_byDato = SCnjpExtraerElem ( p_cnjObj, 1 );
		int iEsp1 [ 3 ] = { 10, 30, 40 };
		if ( ES_NULO ( p_byDato ) || ( *( (int *) p_byDato ) != 20 ) ||
			 ( VerificarConjunto ( p_cnjObj, iEsp1, 3 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 2: se esperaba extraer el 20 y dejar { 10, 30, 40 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* El dato es ahora del test. */
		MemLiberar ( (void **) &p_byDato );
		p_elpObj = SCnjpExtraerElemPtr ( p_cnjObj, 2 );
		int iEsp2 [ 2 ] = { 10, 30 };
		if ( ES_NULO ( p_elpObj ) || ( *( (int *) SElpDatos ( p_elpObj ) ) != 40 ) ||
			 ( SElpTieneAntecesor ( p_elpObj ) != 0 ) ||
			 ( VerificarConjunto ( p_cnjObj, iEsp2, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 3: se esperaba extraer suelto el 40 y dejar { 10, 30 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Ya no esta: ni Existe ni Buscar lo encuentran. */
		if ( ( SCnjpExistePtr ( p_cnjObj, p_elpObj ) != 0 ) || ( SCnjpBuscarPtr ( p_cnjObj, p_elpObj ) != -1 ) )
		{
			printf( "Error caso 4: el 40 ya no deberia estar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SCnjpElementoPtr ( p_cnjObj, 5 ) ) || ES_VALIDO ( SCnjpElementoPtr ( NULL, 0 ) ) ||
			 ES_VALIDO ( SCnjpExtraerElem ( p_cnjObj, 5 ) ) || ES_VALIDO ( SCnjpExtraerElem ( NULL, 0 ) ) ||
			 ES_VALIDO ( SCnjpExtraerElemPtr ( p_cnjObj, -1 ) ) || ES_VALIDO ( SCnjpExtraerElemPtr ( NULL, 0 ) ) ||
			 ( SCnjpExistePtr ( NULL, p_elpObj ) != 0 ) || ( SCnjpExistePtr ( p_cnjObj, NULL ) != 0 ) ||
			 ( SCnjpBuscarPtr ( NULL, p_elpObj ) != -1 ) || ( SCnjpBuscarPtr ( p_cnjObj, NULL ) != -1 ) ||
			 ( VerificarConjunto ( p_cnjObj, iEsp2, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 5: con nulos o fuera de rango se esperaba nulo, 0 o -1 sin cambios\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el conjunto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SElpDestruir ( &p_elpObj );
	SCnjpDestruir ( &p_cnjObj );
	return ( iRes );
}

static int TestSCnjpExistenTodos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjpExistenTodos 01:\n" );

	int iA [ 3 ] = { 10, 20, 30 };
	int iTodos [ 2 ] = { 30, 20 };
	int iAlguno [ 2 ] = { 40, 20 };
	int iNinguno [ 1 ] = { 40 };
	SConjuntoPtr * p_cnjA = CrearConjuntoEnteros ( iA, 3 );
	SConjuntoPtr * p_cnjTodos = CrearConjuntoEnteros ( iTodos, 2 );
	SConjuntoPtr * p_cnjAlguno = CrearConjuntoEnteros ( iAlguno, 2 );
	SListaOrdenadaPtr * p_lisOrdTodos = CrearOrdenadaEnteros ( iTodos, 2 );
	SListaOrdenadaPtr * p_lisOrdNinguno = CrearOrdenadaEnteros ( iNinguno, 1 );
	SListaPtr * p_lisAlguno = CrearListaEnteros ( iAlguno, 2 );
	SListaPtr * p_lisNinguno = CrearListaEnteros ( iNinguno, 1 );
	if ( ES_VALIDO ( p_cnjA ) && ES_VALIDO ( p_cnjTodos ) && ES_VALIDO ( p_cnjAlguno ) && ES_VALIDO ( p_lisOrdTodos ) &&
		 ES_VALIDO ( p_lisOrdNinguno ) && ES_VALIDO ( p_lisAlguno ) && ES_VALIDO ( p_lisNinguno ) )
	{
		if ( ( SCnjpExistenTodos ( p_cnjA, p_cnjTodos ) != 1 ) || ( SCnjpExistenTodos ( p_cnjA, p_cnjAlguno ) != 0 ) ||
			 ( SCnjpExisteAlguno ( p_cnjA, p_cnjAlguno ) != 1 ) )
		{
			printf( "Error caso 1: con conjuntos se esperaba 1, 0 y 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SCnjpExistenTodosListaOrd ( p_cnjA, p_lisOrdTodos ) != 1 ) ||
			 ( SCnjpExistenTodosListaOrd ( p_cnjA, p_lisOrdNinguno ) != 0 ) ||
			 ( SCnjpExisteAlgunoListaOrd ( p_cnjA, p_lisOrdTodos ) != 1 ) ||
			 ( SCnjpExisteAlgunoListaOrd ( p_cnjA, p_lisOrdNinguno ) != 0 ) )
		{
			printf( "Error caso 2: con listas ordenadas se esperaba 1, 0, 1 y 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SCnjpExistenTodosLista ( p_cnjA, p_lisAlguno ) != 0 ) ||
			 ( SCnjpExisteAlgunoLista ( p_cnjA, p_lisAlguno ) != 1 ) ||
			 ( SCnjpExisteAlgunoLista ( p_cnjA, p_lisNinguno ) != 0 ) )
		{
			printf( "Error caso 3: con listas se esperaba 0, 1 y 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SCnjpExistenTodos ( NULL, p_cnjTodos ) != 0 ) || ( SCnjpExistenTodos ( p_cnjA, NULL ) != 0 ) ||
			 ( SCnjpExisteAlguno ( p_cnjA, NULL ) != 0 ) || ( SCnjpExistenTodosLista ( NULL, p_lisAlguno ) != 0 ) ||
			 ( SCnjpExisteAlgunoListaOrd ( NULL, p_lisOrdTodos ) != 0 ) )
		{
			printf( "Error caso 4: con nulos se esperaba 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear los conjuntos o las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCnjpDestruir ( &p_cnjA );
	SCnjpDestruir ( &p_cnjTodos );
	SCnjpDestruir ( &p_cnjAlguno );
	SLispOrdDestruir ( &p_lisOrdTodos );
	SLispOrdDestruir ( &p_lisOrdNinguno );
	SLispDestruir ( &p_lisAlguno );
	SLispDestruir ( &p_lisNinguno );
	return ( iRes );
}

/* Insertan copias de lo que no esta; lo repetido entra una vez. */
static int TestSCnjpInsertarLista01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjpInsertarLista 01:\n" );

	int iA [ 2 ] = { 10, 30 };
	int iVal [ 4 ] = { 30, 20, 20, 40 };
	int iCnj [ 2 ] = { 5, 10 };
	int iOrd [ 2 ] = { 50, 50 };
	int iExt [ 3 ] = { 60, 5, 60 };
	SConjuntoPtr * p_cnjA = CrearConjuntoEnteros ( iA, 2 );
	SConjuntoPtr * p_cnjVal = CrearConjuntoEnteros ( iCnj, 2 );
	SListaPtr * p_lisVal = CrearListaEnteros ( iVal, 4 );
	SListaOrdenadaPtr * p_lisOrd = CrearOrdenadaEnteros ( iOrd, 2 );
	SListaPtr * p_lisExt = CrearListaEnteros ( iExt, 3 );
	if ( ES_VALIDO ( p_cnjA ) && ES_VALIDO ( p_cnjVal ) && ES_VALIDO ( p_lisVal ) && ES_VALIDO ( p_lisOrd ) &&
		 ES_VALIDO ( p_lisExt ) )
	{
		int iEsp1 [ 4 ] = { 10, 20, 30, 40 };
		if ( ( SCnjpInsertarLista ( p_cnjA, p_lisVal, sizeof ( int ) ) != 1 ) ||
			 ( VerificarConjunto ( p_cnjA, iEsp1, 4 ) != BOOL_VAL_CIERTO ) ||
			 ( SLispNumElementos ( p_lisVal ) != 4 ) )
		{
			printf( "Error caso 1: deberia quedar { 10, 20, 30, 40 } y la lista sin tocar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		int iEsp2 [ 5 ] = { 5, 10, 20, 30, 40 };
		if ( ( SCnjpInsertar ( p_cnjA, p_cnjVal, sizeof ( int ) ) != 1 ) ||
			 ( VerificarConjunto ( p_cnjA, iEsp2, 5 ) != BOOL_VAL_CIERTO ) ||
			 ( SCnjpElemento ( p_cnjA, 0 ) == SCnjpElemento ( p_cnjVal, 0 ) ) )
		{
			printf( "Error caso 2: deberia quedar { 5, 10, 20, 30, 40 } con copias\n" );
			iRes = BOOL_VAL_FALSO;
		}
		int iEsp3 [ 6 ] = { 5, 10, 20, 30, 40, 50 };
		if ( ( SCnjpInsertarListaOrd ( p_cnjA, p_lisOrd, sizeof ( int ) ) != 1 ) ||
			 ( VerificarConjunto ( p_cnjA, iEsp3, 6 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 3: el 50 repetido deberia entrar una vez\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Con fDuplicar: solo se copia el 60, una vez. */
		int iEsp4 [ 7 ] = { 5, 10, 20, 30, 40, 50, 60 };
		iCopiasHechas = 0;
		if ( ( SCnjpInsertarListaExt ( p_cnjA, p_lisExt, DuplicarEnteroContando ) != 1 ) ||
			 ( iCopiasHechas != 1 ) ||
			 ( SCnjpInsertarExt ( p_cnjA, p_cnjVal, DuplicarEnteroContando ) != 1 ) ||
			 ( SCnjpInsertarListaOrdExt ( p_cnjA, p_lisOrd, DuplicarEnteroContando ) != 1 ) ||
			 ( iCopiasHechas != 1 ) ||
			 ( VerificarConjunto ( p_cnjA, iEsp4, 7 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 4: con fDuplicar solo deberia copiarse el 60\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SCnjpInsertar ( p_cnjA, p_cnjA, sizeof ( int ) ) != 1 ) ||
			 ( VerificarConjunto ( p_cnjA, iEsp4, 7 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 5: consigo mismo se esperaba 1 sin cambios\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SCnjpInsertarLista ( NULL, p_lisVal, sizeof ( int ) ) != 0 ) ||
			 ( SCnjpInsertarLista ( p_cnjA, NULL, sizeof ( int ) ) != 0 ) ||
			 ( SCnjpInsertar ( p_cnjA, NULL, sizeof ( int ) ) != 0 ) ||
			 ( SCnjpInsertarListaOrd ( p_cnjA, NULL, sizeof ( int ) ) != 0 ) ||
			 ( SCnjpInsertarListaExt ( p_cnjA, p_lisVal, NULL ) != 0 ) ||
			 ( VerificarConjunto ( p_cnjA, iEsp4, 7 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 6: con nulos se esperaba 0 sin cambios\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear los conjuntos o las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCnjpDestruir ( &p_cnjA );
	SCnjpDestruir ( &p_cnjVal );
	SLispDestruir ( &p_lisVal );
	SLispOrdDestruir ( &p_lisOrd );
	SLispDestruir ( &p_lisExt );
	return ( iRes );
}

/* Eliminar destruye y Extraer mueve a un conjunto nuevo con la liberacion
   del original. */
static int TestSCnjpExtraerLista01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjpExtraerLista 01:\n" );

	int iA [ 6 ] = { 10, 20, 30, 40, 50, 60 };
	int iEli [ 3 ] = { 20, 99, 20 };
	int iEliCnj [ 1 ] = { 40 };
	int iExt [ 2 ] = { 50, 10 };
	int iExtOrd [ 1 ] = { 60 };
	SConjuntoPtr * p_cnjA = CrearConjuntoEnteros ( iA, 6 );
	SConjuntoPtr * p_cnjEli = CrearConjuntoEnteros ( iEliCnj, 1 );
	SListaPtr * p_lisEli = CrearListaEnteros ( iEli, 3 );
	SListaPtr * p_lisExt = CrearListaEnteros ( iExt, 2 );
	SListaOrdenadaPtr * p_lisExtOrd = CrearOrdenadaEnteros ( iExtOrd, 1 );
	SConjuntoPtr * p_cnjRes = NULL;
	if ( ES_VALIDO ( p_cnjA ) && ES_VALIDO ( p_cnjEli ) && ES_VALIDO ( p_lisEli ) && ES_VALIDO ( p_lisExt ) &&
		 ES_VALIDO ( p_lisExtOrd ) )
	{
		int iEsp1 [ 4 ] = { 10, 30, 50, 60 };
		if ( ( SCnjpEliminarLista ( p_cnjA, p_lisEli ) != 1 ) ||
			 ( SCnjpEliminarConjunto ( p_cnjA, p_cnjEli ) != 1 ) ||
			 ( VerificarConjunto ( p_cnjA, iEsp1, 4 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 1: deberia quedar { 10, 30, 50, 60 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		byte * p_by50 = SCnjpElemento ( p_cnjA, 2 );
		p_cnjRes = SCnjpExtraerLista ( p_cnjA, p_lisExt );
		int iEspRes [ 2 ] = { 10, 50 };
		int iEsp2 [ 2 ] = { 30, 60 };
		if ( ( SCnjpElemento ( p_cnjRes, 1 ) != p_by50 ) ||
			 ( VerificarYDestruir ( &p_cnjRes, iEspRes, 2 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarConjunto ( p_cnjA, iEsp2, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 2: se esperaba mover { 10, 50 } y dejar { 30, 60 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_cnjRes = SCnjpExtraerListaOrd ( p_cnjA, p_lisExtOrd );
		int iEsp3 [ 1 ] = { 30 };
		if ( ( VerificarYDestruir ( &p_cnjRes, iExtOrd, 1 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarConjunto ( p_cnjA, iEsp3, 1 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 3: se esperaba mover { 60 } y dejar { 30 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SCnjpExtraerConjunto ( p_cnjA, p_cnjA ) ) ||
			 ES_VALIDO ( SCnjpExtraerLista ( p_cnjA, NULL ) ) ||
			 ES_VALIDO ( SCnjpExtraerListaOrd ( NULL, p_lisExtOrd ) ) ||
			 ( SCnjpEliminarConjunto ( p_cnjA, p_cnjA ) != 0 ) ||
			 ( SCnjpEliminarLista ( NULL, p_lisEli ) != 0 ) ||
			 ( SCnjpEliminarListaOrd ( p_cnjA, NULL ) != 0 ) ||
			 ( VerificarConjunto ( p_cnjA, iEsp3, 1 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 4: con el mismo conjunto o un nulo se esperaba nulo o 0 sin cambios\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear los conjuntos o las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCnjpDestruir ( &p_cnjA );
	SCnjpDestruir ( &p_cnjEli );
	SLispDestruir ( &p_lisEli );
	SLispDestruir ( &p_lisExt );
	SLispOrdDestruir ( &p_lisExtOrd );
	return ( iRes );
}

/* Union, Interseccion y Diferencia de conjuntos: copias propias, sin
   repetidos, y los de entrada sin tocar; las Ext copian con fDuplicar. */
static int TestSCnjpUnion01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjpUnion 01:\n" );

	int iA [ 3 ] = { 10, 20, 30 };
	int iB [ 2 ] = { 20, 40 };
	int iL [ 3 ] = { 40, 20, 40 };
	SConjuntoPtr * p_cnjA = CrearConjuntoEnteros ( iA, 3 );
	SConjuntoPtr * p_cnjB = CrearConjuntoEnteros ( iB, 2 );
	SListaOrdenadaPtr * p_lisOrd = CrearOrdenadaEnteros ( iL, 3 );
	SListaPtr * p_lisVal = CrearListaEnteros ( iL, 3 );
	SConjuntoPtr * p_cnjRes = NULL;
	if ( ES_VALIDO ( p_cnjA ) && ES_VALIDO ( p_cnjB ) && ES_VALIDO ( p_lisOrd ) && ES_VALIDO ( p_lisVal ) )
	{
		int iUni [ 4 ] = { 10, 20, 30, 40 };
		int iInt [ 1 ] = { 20 };
		int iDif [ 2 ] = { 10, 30 };
		int iTam = sizeof ( int );
		p_cnjRes = SCnjpUnion ( p_cnjA, p_cnjB, iTam );
		if ( ( SCnjpElemento ( p_cnjRes, 0 ) == SCnjpElemento ( p_cnjA, 0 ) ) ||
			 ( VerificarYDestruir ( &p_cnjRes, iUni, 4 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 1: la union deberia ser { 10, 20, 30, 40 }, con copias\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_cnjRes = SCnjpInterseccion ( p_cnjA, p_cnjB, iTam );
		if ( VerificarYDestruir ( &p_cnjRes, iInt, 1 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 2: la interseccion deberia ser { 20 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_cnjRes = SCnjpDiferencia ( p_cnjA, p_cnjB, iTam );
		if ( VerificarYDestruir ( &p_cnjRes, iDif, 2 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 3: la diferencia deberia ser { 10, 30 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Con listas que repiten el 40: sale una vez. */
		p_cnjRes = SCnjpUnionLista ( p_cnjA, p_lisVal, iTam );
		if ( VerificarYDestruir ( &p_cnjRes, iUni, 4 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 4: la union con la lista deberia ser { 10, 20, 30, 40 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_cnjRes = SCnjpUnionListaOrd ( p_cnjA, p_lisOrd, iTam );
		if ( VerificarYDestruir ( &p_cnjRes, iUni, 4 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 5: la union con la ordenada deberia ser { 10, 20, 30, 40 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_cnjRes = SCnjpInterseccionLista ( p_cnjA, p_lisVal, iTam );
		if ( VerificarYDestruir ( &p_cnjRes, iInt, 1 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 6: la interseccion con la lista deberia ser { 20 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_cnjRes = SCnjpInterseccionListaOrd ( p_cnjA, p_lisOrd, iTam );
		if ( VerificarYDestruir ( &p_cnjRes, iInt, 1 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 7: la interseccion con la ordenada deberia ser { 20 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_cnjRes = SCnjpDiferenciaLista ( p_cnjA, p_lisVal, iTam );
		if ( VerificarYDestruir ( &p_cnjRes, iDif, 2 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 8: la diferencia con la lista deberia ser { 10, 30 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_cnjRes = SCnjpDiferenciaListaOrd ( p_cnjA, p_lisOrd, iTam );
		if ( VerificarYDestruir ( &p_cnjRes, iDif, 2 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 9: la diferencia con la ordenada deberia ser { 10, 30 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Las Ext: union 3 + 1 copias, interseccion 1, diferencia 2, por cada forma. */
		iCopiasHechas = 0;
		p_cnjRes = SCnjpUnionExt ( p_cnjA, p_cnjB, DuplicarEnteroContando );
		int iUniOk = VerificarYDestruir ( &p_cnjRes, iUni, 4 );
		p_cnjRes = SCnjpUnionListaExt ( p_cnjA, p_lisVal, DuplicarEnteroContando );
		iUniOk = ( VerificarYDestruir ( &p_cnjRes, iUni, 4 ) == BOOL_VAL_CIERTO ) ? iUniOk : BOOL_VAL_FALSO;
		p_cnjRes = SCnjpUnionListaOrdExt ( p_cnjA, p_lisOrd, DuplicarEnteroContando );
		iUniOk = ( VerificarYDestruir ( &p_cnjRes, iUni, 4 ) == BOOL_VAL_CIERTO ) ? iUniOk : BOOL_VAL_FALSO;
		if ( ( iUniOk != BOOL_VAL_CIERTO ) || ( iCopiasHechas != 12 ) )
		{
			printf( "Error caso 10: las uniones Ext deberian ser { 10, 20, 30, 40 } con 12 copias: %d\n", iCopiasHechas );
			iRes = BOOL_VAL_FALSO;
		}
		iCopiasHechas = 0;
		p_cnjRes = SCnjpInterseccionExt ( p_cnjA, p_cnjB, DuplicarEnteroContando );
		int iOtrasOk = VerificarYDestruir ( &p_cnjRes, iInt, 1 );
		p_cnjRes = SCnjpInterseccionListaExt ( p_cnjA, p_lisVal, DuplicarEnteroContando );
		iOtrasOk = ( VerificarYDestruir ( &p_cnjRes, iInt, 1 ) == BOOL_VAL_CIERTO ) ? iOtrasOk : BOOL_VAL_FALSO;
		p_cnjRes = SCnjpInterseccionListaOrdExt ( p_cnjA, p_lisOrd, DuplicarEnteroContando );
		iOtrasOk = ( VerificarYDestruir ( &p_cnjRes, iInt, 1 ) == BOOL_VAL_CIERTO ) ? iOtrasOk : BOOL_VAL_FALSO;
		p_cnjRes = SCnjpDiferenciaExt ( p_cnjA, p_cnjB, DuplicarEnteroContando );
		iOtrasOk = ( VerificarYDestruir ( &p_cnjRes, iDif, 2 ) == BOOL_VAL_CIERTO ) ? iOtrasOk : BOOL_VAL_FALSO;
		p_cnjRes = SCnjpDiferenciaListaExt ( p_cnjA, p_lisVal, DuplicarEnteroContando );
		iOtrasOk = ( VerificarYDestruir ( &p_cnjRes, iDif, 2 ) == BOOL_VAL_CIERTO ) ? iOtrasOk : BOOL_VAL_FALSO;
		p_cnjRes = SCnjpDiferenciaListaOrdExt ( p_cnjA, p_lisOrd, DuplicarEnteroContando );
		iOtrasOk = ( VerificarYDestruir ( &p_cnjRes, iDif, 2 ) == BOOL_VAL_CIERTO ) ? iOtrasOk : BOOL_VAL_FALSO;
		if ( ( iOtrasOk != BOOL_VAL_CIERTO ) || ( iCopiasHechas != 9 ) )
		{
			printf( "Error caso 11: interseccion { 20 } y diferencia { 10, 30 } Ext con 9 copias: %d\n", iCopiasHechas );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( VerificarConjunto ( p_cnjA, iA, 3 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarConjunto ( p_cnjB, iB, 2 ) != BOOL_VAL_CIERTO ) ||
			 ( SLispNumElementos ( p_lisVal ) != 3 ) || ( SLispOrdNumElementos ( p_lisOrd ) != 3 ) )
		{
			printf( "Error caso 12: los de entrada no deberian cambiar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SCnjpUnion ( NULL, p_cnjB, iTam ) ) || ES_VALIDO ( SCnjpUnion ( p_cnjA, NULL, iTam ) ) ||
			 ES_VALIDO ( SCnjpInterseccion ( NULL, p_cnjB, iTam ) ) || ES_VALIDO ( SCnjpDiferencia ( p_cnjA, NULL, iTam ) ) ||
			 ES_VALIDO ( SCnjpUnionLista ( p_cnjA, NULL, iTam ) ) || ES_VALIDO ( SCnjpUnionListaOrd ( NULL, p_lisOrd, iTam ) ) ||
			 ES_VALIDO ( SCnjpUnionListaExt ( p_cnjA, p_lisVal, NULL ) ) ||
			 ES_VALIDO ( SCnjpInterseccionListaExt ( NULL, p_lisVal, DuplicarEnteroContando ) ) )
		{
			printf( "Error caso 13: con nulos se esperaba nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear los conjuntos o las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCnjpDestruir ( &p_cnjA );
	SCnjpDestruir ( &p_cnjB );
	SLispOrdDestruir ( &p_lisOrd );
	SLispDestruir ( &p_lisVal );
	return ( iRes );
}

int TestSConjuntoPtr ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SConjuntoPtr]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSCnjpOperaciones01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjpPrimeroUltimo01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjpPosicion01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjpInvalidos01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjpCrearDesdeLista01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjpExtraerElem01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjpExistenTodos01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjpInsertarLista01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjpExtraerLista01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjpUnion01 () == BOOL_VAL_CIERTO ) )
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
