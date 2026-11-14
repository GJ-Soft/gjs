#include "Base.h"

#include "SListaOrdenada.h"



/* Comparador de enteros ( formato -1 / 0 / 1 ) para la lista ordenada. */
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

static SElemento * CrearElementoEntero ( int iValor )
{
	SElemento * p_elmObj = SElmCrearEntero ();
	if ( ES_VALIDO ( p_elmObj ) )
	{
		SElmEscribirEntero ( p_elmObj, iValor );
	}
	return ( p_elmObj );
}

/* Comprueba numero y orden de los valores. */
static int VerificarOrdenada ( SListaOrdenada * p_lisObj, int * p_iEsperados, int iNum )
{
	int iRes = BOOL_VAL_CIERTO;

	if ( SLisOrdNumElementos ( p_lisObj ) != iNum )
	{
		printf( "  Verificacion: se esperaban %d elementos: %d\n", iNum, SLisOrdNumElementos ( p_lisObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	int iPos = 0;
	while ( ( iPos < iNum ) && ( iRes == BOOL_VAL_CIERTO ) )
	{
		SElemento * p_elmObj = SLisOrdElemento ( p_lisObj, iPos );
		if ( ES_NULO ( p_elmObj ) || ( SElmEntero ( p_elmObj ) != p_iEsperados [ iPos ] ) )
		{
			printf( "  Verificacion: en pos %d se esperaba %d\n", iPos, p_iEsperados [ iPos ] );
			iRes = BOOL_VAL_FALSO;
		}
		iPos = iPos + 1;
	}
	return ( iRes );
}

static int VerificarLista ( SLista * p_lisObj, int * p_iEsperados, int iNum )
{
	int iRes = BOOL_VAL_CIERTO;

	if ( SLisNumElementos ( p_lisObj ) != iNum )
	{
		printf( "  Verificacion: se esperaban %d elementos: %d\n", iNum, SLisNumElementos ( p_lisObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	int iPos = 0;
	while ( ( iPos < iNum ) && ( iRes == BOOL_VAL_CIERTO ) )
	{
		SElemento * p_elmObj = SLisElemento ( p_lisObj, iPos );
		if ( ES_NULO ( p_elmObj ) || ( SElmEntero ( p_elmObj ) != p_iEsperados [ iPos ] ) )
		{
			printf( "  Verificacion: en pos %d se esperaba %d\n", iPos, p_iEsperados [ iPos ] );
			iRes = BOOL_VAL_FALSO;
		}
		iPos = iPos + 1;
	}
	return ( iRes );
}

/* SLista sin ordenar, en el orden dado. */
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



static int TestSLisOrdCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisOrdCrear 01:\n" );

	SListaOrdenada * p_lisObj = SLisOrdCrear ( CompararEnteros );
	if ( ES_NULO ( p_lisObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SLisOrdEsValida ( p_lisObj ) != 1 )
		{
			printf( "Error caso 2: la lista recien creada deberia ser valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisOrdEstaVacia ( p_lisObj ) != 1 )
		{
			printf( "Error caso 3: la lista recien creada deberia estar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisOrdNumElementos ( p_lisObj ) != 0 )
		{
			printf( "Error caso 4: se esperaban 0 elementos\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SLisOrdDestruir ( &p_lisObj );

	if ( ES_VALIDO ( p_lisObj ) )
	{
		printf( "Error caso 5: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSLisOrdInsertarOrdenado01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisOrdInsertarOrdenado 01:\n" );

	SListaOrdenada * p_lisObj = SLisOrdCrear ( CompararEnteros );
	if ( ES_VALIDO ( p_lisObj ) )
	{
		/* Se insertan desordenados; la lista debe mantenerlos ordenados. */
		SLisOrdInsertarElem ( p_lisObj, CrearElementoEntero ( 20 ) );
		SLisOrdInsertarElem ( p_lisObj, CrearElementoEntero ( 10 ) );
		SLisOrdInsertarElem ( p_lisObj, CrearElementoEntero ( 30 ) );

		if ( SLisOrdNumElementos ( p_lisObj ) != 3 )
		{
			printf( "Error caso 1: se esperaban 3 elementos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		int iEsp [ 3 ] = { 10, 20, 30 };
		int iPos = 0;
		while ( ( iPos < 3 ) && ( iRes == BOOL_VAL_CIERTO ) )
		{
			SElemento * p_elmObj = SLisOrdElemento ( p_lisObj, iPos );
			if ( ES_NULO ( p_elmObj ) || ( SElmEntero ( p_elmObj ) != iEsp [ iPos ] ) )
			{
				printf( "Error caso 2: en la posicion %d se esperaba %d\n", iPos, iEsp [ iPos ] );
				iRes = BOOL_VAL_FALSO;
			}
			iPos = iPos + 1;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisOrdDestruir ( &p_lisObj );
	return ( iRes );
}

static int TestSLisOrdBuscar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisOrdBuscar 01:\n" );

	SListaOrdenada * p_lisObj = SLisOrdCrear ( CompararEnteros );
	if ( ES_VALIDO ( p_lisObj ) )
	{
		SLisOrdInsertarElem ( p_lisObj, CrearElementoEntero ( 10 ) );
		SLisOrdInsertarElem ( p_lisObj, CrearElementoEntero ( 20 ) );
		SLisOrdInsertarElem ( p_lisObj, CrearElementoEntero ( 30 ) );

		SBloque * p_blqBuscar = SBlqCrearEntero ();
		if ( ES_VALIDO ( p_blqBuscar ) )
		{
			SBlqEscribirEntero ( p_blqBuscar, 20 );
			if ( SLisOrdBuscar ( p_lisObj, p_blqBuscar ) != 1 )
			{
				printf( "Error caso 1: el 20 deberia estar en la posicion 1\n" );
				iRes = BOOL_VAL_FALSO;
			}
			/* Menor que el minimo: no encontrado. */
			SBlqEscribirEntero ( p_blqBuscar, 5 );
			if ( SLisOrdBuscar ( p_lisObj, p_blqBuscar ) != -1 )
			{
				printf( "Error caso 2: el 5 no deberia encontrarse\n" );
				iRes = BOOL_VAL_FALSO;
			}
			/* Mayor que el maximo: no encontrado ( antes daba un indice falso ). */
			SBlqEscribirEntero ( p_blqBuscar, 35 );
			if ( SLisOrdBuscar ( p_lisObj, p_blqBuscar ) != -1 )
			{
				printf( "Error caso 3: el 35 no deberia encontrarse\n" );
				iRes = BOOL_VAL_FALSO;
			}
			/* Intermedio no presente: no encontrado. */
			SBlqEscribirEntero ( p_blqBuscar, 25 );
			if ( SLisOrdBuscar ( p_lisObj, p_blqBuscar ) != -1 )
			{
				printf( "Error caso 4: el 25 no deberia encontrarse\n" );
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
	SLisOrdDestruir ( &p_lisObj );
	return ( iRes );
}

static int TestSLisOrdEliminar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisOrdEliminar 01:\n" );

	SListaOrdenada * p_lisObj = SLisOrdCrear ( CompararEnteros );
	if ( ES_VALIDO ( p_lisObj ) )
	{
		SLisOrdInsertarElem ( p_lisObj, CrearElementoEntero ( 10 ) );
		SLisOrdInsertarElem ( p_lisObj, CrearElementoEntero ( 20 ) );
		SLisOrdInsertarElem ( p_lisObj, CrearElementoEntero ( 30 ) );

		SLisOrdEliminarElem ( p_lisObj, 1 );
		if ( SLisOrdNumElementos ( p_lisObj ) != 2 )
		{
			printf( "Error caso 1: se esperaban 2 elementos tras eliminar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* El 20 ya no esta; siguen el 10 y el 30 ordenados. */
		if ( ( SElmEntero ( SLisOrdElemento ( p_lisObj, 0 ) ) != 10 ) ||
			 ( SElmEntero ( SLisOrdElemento ( p_lisObj, 1 ) ) != 30 ) )
		{
			printf( "Error caso 2: tras eliminar deberian quedar el 10 y el 30\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisOrdVaciar ( p_lisObj ) != 1 )
		{
			printf( "Error caso 3: se esperaba resultado 1 al vaciar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisOrdEstaVacia ( p_lisObj ) != 1 )
		{
			printf( "Error caso 4: la lista deberia quedar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisOrdDestruir ( &p_lisObj );
	return ( iRes );
}

static int TestSLisOrdInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisOrdInvalidos 01:\n" );

	if ( SLisOrdEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: una lista nula no deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLisOrdNumElementos ( NULL ) != 0 )
	{
		printf( "Error caso 2: el numero de elementos de una lista nula deberia ser 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Crear con comparador nulo debe fallar ( el comparador no seria valido ). */
	if ( ES_VALIDO ( SLisOrdCrear ( NULL ) ) )
	{
		printf( "Error caso 3: crear con comparador nulo deberia fallar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SListaOrdenada * p_lisNula = NULL;
	SLisOrdDestruir ( &p_lisNula );
	return ( iRes );
}

static int TestSLisOrdBuscarExt01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisOrdBuscarExt 01:\n" );

	SListaOrdenada * p_lisObj = SLisOrdCrear ( CompararEnteros );
	if ( ES_VALIDO ( p_lisObj ) )
	{
		SLisOrdInsertarElem ( p_lisObj, CrearElementoEntero ( 10 ) );
		SLisOrdInsertarElem ( p_lisObj, CrearElementoEntero ( 20 ) );
		SLisOrdInsertarElem ( p_lisObj, CrearElementoEntero ( 30 ) );

		int iBuscar = 20;
		if ( SLisOrdBuscarExt ( p_lisObj, (byte *) &iBuscar ) != 1 )
		{
			printf( "Error caso 1: el 20 deberia estar en la posicion 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Menor que el minimo: no encontrado. */
		iBuscar = 5;
		if ( SLisOrdBuscarExt ( p_lisObj, (byte *) &iBuscar ) != -1 )
		{
			printf( "Error caso 2: el 5 no deberia encontrarse\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Mayor que el maximo: no encontrado. */
		iBuscar = 35;
		if ( SLisOrdBuscarExt ( p_lisObj, (byte *) &iBuscar ) != -1 )
		{
			printf( "Error caso 3: el 35 no deberia encontrarse\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisOrdDestruir ( &p_lisObj );
	return ( iRes );
}



static int TestSLisOrdExtraerElem01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisOrdExtraerElem 01:\n" );

	SListaOrdenada * p_lisObj = SLisOrdCrear ( CompararEnteros );
	if ( ES_VALIDO ( p_lisObj ) )
	{
		/* Lista vacia: no hay nada que extraer. */
		if ( ES_VALIDO ( SLisOrdExtraerElem ( p_lisObj, 0 ) ) )
		{
			printf( "Error caso 1: extraer de una lista vacia deberia devolver nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisOrdInsertarElem ( p_lisObj, CrearElementoEntero ( 30 ) );
		SLisOrdInsertarElem ( p_lisObj, CrearElementoEntero ( 10 ) );
		SLisOrdInsertarElem ( p_lisObj, CrearElementoEntero ( 40 ) );
		SLisOrdInsertarElem ( p_lisObj, CrearElementoEntero ( 20 ) );

		/* Se extrae el mismo elemento que habia, vivo y desenganchado de la lista. */
		SElemento * p_elmEsp = SLisOrdElemento ( p_lisObj, 1 );
		SElemento * p_elmExt = SLisOrdExtraerElem ( p_lisObj, 1 );
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
		int iEsp [ 3 ] = { 10, 30, 40 };
		int iPos = 0;
		if ( SLisOrdNumElementos ( p_lisObj ) != 3 )
		{
			printf( "Error caso 4: tras extraer deberian quedar 3 elementos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		while ( ( iPos < 3 ) && ( iRes == BOOL_VAL_CIERTO ) )
		{
			if ( SElmEntero ( SLisOrdElemento ( p_lisObj, iPos ) ) != iEsp [ iPos ] )
			{
				printf( "Error caso 5: en la posicion %d se esperaba %d\n", iPos, iEsp [ iPos ] );
				iRes = BOOL_VAL_FALSO;
			}
			iPos = iPos + 1;
		}
		/* Posiciones fuera de rango: nulo, y la lista no cambia. */
		if ( ES_VALIDO ( SLisOrdExtraerElem ( p_lisObj, -1 ) ) || ES_VALIDO ( SLisOrdExtraerElem ( p_lisObj, 3 ) ) )
		{
			printf( "Error caso 6: extraer fuera de rango deberia devolver nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisOrdNumElementos ( p_lisObj ) != 3 )
		{
			printf( "Error caso 7: extraer fuera de rango no deberia cambiar la lista\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* El extraido se puede volver a insertar y recupera su sitio en el orden. */
		if ( ES_VALIDO ( p_elmExt ) )
		{
			if ( SLisOrdInsertarElem ( p_lisObj, p_elmExt ) != 1 )
			{
				printf( "Error caso 8: el elemento extraido deberia poder volver a insertarse\n" );
				iRes = BOOL_VAL_FALSO;
				SElmDestruir ( &p_elmExt );
			}
			else if ( SLisOrdElemento ( p_lisObj, 1 ) != p_elmExt )
			{
				printf( "Error caso 9: al reinsertarlo deberia volver a la posicion 1\n" );
				iRes = BOOL_VAL_FALSO;
			}
		}
		/* Los extremos; los extraidos son ya del llamador. */
		p_elmExt = SLisOrdExtraerElem ( p_lisObj, 0 );
		if ( ES_NULO ( p_elmExt ) || ( SElmEntero ( p_elmExt ) != 10 ) )
		{
			printf( "Error caso 10: extraer la posicion 0 deberia dar el 10\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SElmDestruir ( &p_elmExt );
		p_elmExt = SLisOrdExtraerElem ( p_lisObj, SLisOrdNumElementos ( p_lisObj ) - 1 );
		if ( ES_NULO ( p_elmExt ) || ( SElmEntero ( p_elmExt ) != 40 ) )
		{
			printf( "Error caso 11: extraer la ultima posicion deberia dar el 40\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SElmDestruir ( &p_elmExt );
		if ( ( SLisOrdNumElementos ( p_lisObj ) != 2 ) ||
			 ( SElmEntero ( SLisOrdElemento ( p_lisObj, 0 ) ) != 20 ) ||
			 ( SElmEntero ( SLisOrdElemento ( p_lisObj, 1 ) ) != 30 ) )
		{
			printf( "Error caso 12: deberian quedar el 20 y el 30\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SLisOrdExtraerElem ( NULL, 0 ) ) )
		{
			printf( "Error caso 13: extraer de una lista nula deberia devolver nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisOrdDestruir ( &p_lisObj );
	return ( iRes );
}


/* Encapsular se queda con el comparador ( lo destruye la lista ) y, si falla,
   no lo toca: aqui uno no valido en la pila, que no se puede liberar. */
static int TestSLisOrdEncapsular01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisOrdEncapsular 01:\n" );

	SComparador * p_cmpObj = SCmpCrear ( CompararEnteros );
	SListaOrdenada * p_lisObj = SLisOrdEncapsular ( p_cmpObj );
	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( ( SLisOrdEsValida ( p_lisObj ) != 1 ) || ( SLisOrdEstaVacia ( p_lisObj ) != 1 ) ||
			 ( p_lisObj->p_cmpObj != p_cmpObj ) )
		{
			printf( "Error caso 1: se esperaba una lista vacia con ese mismo comparador\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisOrdInsertarElem ( p_lisObj, CrearElementoEntero ( 20 ) );
		SLisOrdInsertarElem ( p_lisObj, CrearElementoEntero ( 10 ) );
		int iEsp [ 2 ] = { 10, 20 };
		if ( VerificarOrdenada ( p_lisObj, iEsp, 2 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 2: se esperaba { 10, 20 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SComparador cmpMalo = { NULL };
		if ( ES_VALIDO ( SLisOrdEncapsular ( &cmpMalo ) ) || ES_VALIDO ( SLisOrdEncapsular ( NULL ) ) )
		{
			printf( "Error caso 3: con un comparador no valido o nulo se esperaba nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo encapsular\n" );
		iRes = BOOL_VAL_FALSO;
		SCmpDestruir ( &p_cmpObj );
	}
	/* Destruye tambien p_cmpObj. */
	SLisOrdDestruir ( &p_lisObj );
	return ( iRes );
}

/* Ordena copias de los elementos; la lista de valores no cambia. */
static int TestSLisOrdCrearDesdeLista01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisOrdCrearDesdeLista 01:\n" );

	int iVal [ 4 ] = { 30, 10, 20, 10 };
	SLista * p_lisVal = CrearListaEnteros ( iVal, 4 );
	SLista * p_lisVacia = SLisCrear ();
	SListaOrdenada * p_lisObj = NULL;
	SListaOrdenada * p_lisDeVacia = NULL;
	if ( ES_VALIDO ( p_lisVal ) && ES_VALIDO ( p_lisVacia ) )
	{
		p_lisObj = SLisOrdCrearDesdeLista ( p_lisVal, CompararEnteros );
		int iEsp [ 4 ] = { 10, 10, 20, 30 };
		if ( ES_NULO ( p_lisObj ) || ( VerificarOrdenada ( p_lisObj, iEsp, 4 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 1: se esperaba { 10, 10, 20, 30 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( VerificarLista ( p_lisVal, iVal, 4 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 2: los valores deberian seguir { 30, 10, 20, 10 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisOrdElemento ( p_lisObj, 3 ) == SLisElemento ( p_lisVal, 0 ) )
		{
			printf( "Error caso 3: la lista ordenada deberia tener copias\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_lisDeVacia = SLisOrdCrearDesdeLista ( p_lisVacia, CompararEnteros );
		if ( ES_NULO ( p_lisDeVacia ) || ( SLisOrdEsValida ( p_lisDeVacia ) != 1 ) ||
			 ( SLisOrdNumElementos ( p_lisDeVacia ) != 0 ) )
		{
			printf( "Error caso 4: de una lista vacia se esperaba otra vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SLisOrdCrearDesdeLista ( NULL, CompararEnteros ) ) ||
			 ES_VALIDO ( SLisOrdCrearDesdeLista ( p_lisVal, NULL ) ) )
		{
			printf( "Error caso 5: sin lista o sin funcion se esperaba nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisDestruir ( &p_lisVal );
	SLisDestruir ( &p_lisVacia );
	SLisOrdDestruir ( &p_lisObj );
	SLisOrdDestruir ( &p_lisDeVacia );
	return ( iRes );
}

/* La copia tiene su propio comparador y sus propios elementos: sigue ordenando
   despues de destruir el original. El cursor del original no se mueve. */
static int TestSLisOrdDuplicar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisOrdDuplicar 01:\n" );

	int iVal [ 3 ] = { 30, 10, 20 };
	SLista * p_lisVal = CrearListaEnteros ( iVal, 3 );
	SListaOrdenada * p_lisObj = SLisOrdCrearDesdeLista ( p_lisVal, CompararEnteros );
	SListaOrdenada * p_lisVacia = SLisOrdCrear ( CompararEnteros );
	SListaOrdenada * p_lisDup = NULL;
	SListaOrdenada * p_lisDupVacia = NULL;
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisVacia ) )
	{
		SLisOrdMoverA ( p_lisObj, 1 );
		p_lisDup = SLisOrdDuplicar ( p_lisObj );
		if ( SLisOrdPosicion ( p_lisObj ) != 1 )
		{
			printf( "Error caso 1: el cursor del original deberia seguir en 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		int iEsp [ 3 ] = { 10, 20, 30 };
		if ( ES_NULO ( p_lisDup ) || ( p_lisDup == p_lisObj ) ||
			 ( VerificarOrdenada ( p_lisDup, iEsp, 3 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 2: la copia deberia ser otra lista con { 10, 20, 30 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			if ( ( p_lisDup->p_cmpObj == p_lisObj->p_cmpObj ) ||
				 ( SLisOrdElemento ( p_lisDup, 0 ) == SLisOrdElemento ( p_lisObj, 0 ) ) )
			{
				printf( "Error caso 3: la copia no deberia compartir comparador ni elementos\n" );
				iRes = BOOL_VAL_FALSO;
			}
			SLisOrdDestruir ( &p_lisObj );
			SLisOrdInsertarElem ( p_lisDup, CrearElementoEntero ( 15 ) );
			int iEsp2 [ 4 ] = { 10, 15, 20, 30 };
			if ( VerificarOrdenada ( p_lisDup, iEsp2, 4 ) != BOOL_VAL_CIERTO )
			{
				printf( "Error caso 4: sin el original la copia deberia seguir ordenando\n" );
				iRes = BOOL_VAL_FALSO;
			}
		}
		p_lisDupVacia = SLisOrdDuplicar ( p_lisVacia );
		if ( ES_NULO ( p_lisDupVacia ) || ( SLisOrdEsValida ( p_lisDupVacia ) != 1 ) ||
			 ( SLisOrdNumElementos ( p_lisDupVacia ) != 0 ) )
		{
			printf( "Error caso 5: la copia de una vacia deberia ser otra vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SLisOrdDuplicar ( NULL ) ) )
		{
			printf( "Error caso 6: con una lista nula se esperaba nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisDestruir ( &p_lisVal );
	SLisOrdDestruir ( &p_lisObj );
	SLisOrdDestruir ( &p_lisVacia );
	SLisOrdDestruir ( &p_lisDup );
	SLisOrdDestruir ( &p_lisDupVacia );
	return ( iRes );
}

static int TestSLisOrdDuplicarLista01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisOrdDuplicarLista 01:\n" );

	int iVal [ 3 ] = { 30, 10, 20 };
	SLista * p_lisVal = CrearListaEnteros ( iVal, 3 );
	SListaOrdenada * p_lisObj = SLisOrdCrearDesdeLista ( p_lisVal, CompararEnteros );
	SLista * p_lisRes = NULL;
	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_lisRes = SLisOrdDuplicarLista ( p_lisObj );
		int iEsp [ 3 ] = { 10, 20, 30 };
		if ( ES_NULO ( p_lisRes ) || ( VerificarLista ( p_lisRes, iEsp, 3 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 1: se esperaba una SLista con { 10, 20, 30 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisElemento ( p_lisRes, 0 ) == SLisOrdElemento ( p_lisObj, 0 ) ) ||
			 ( p_lisRes == p_lisObj->p_lisContenido ) )
		{
			printf( "Error caso 2: se esperaba una copia, no el contenido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SLisOrdDuplicarLista ( NULL ) ) )
		{
			printf( "Error caso 3: con una lista nula se esperaba nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisDestruir ( &p_lisVal );
	SLisOrdDestruir ( &p_lisObj );
	SLisDestruir ( &p_lisRes );
	return ( iRes );
}

/* Compara por decenas: 11 y 13 son iguales. Para ver que manda el comparador. */
static int CompararDecenas ( void * p_vVal1, void * p_vVal2 )
{
	int iVal1 = *( (int *) p_vVal1 ) / 10;
	int iVal2 = *( (int *) p_vVal2 ) / 10;
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

static SListaOrdenada * CrearOrdenadaEnteros ( int * p_iValores, int iNum, PFUNINTPVPV fComparar )
{
	SLista * p_lisVal = CrearListaEnteros ( p_iValores, iNum );
	SListaOrdenada * p_lisRes = SLisOrdCrearDesdeLista ( p_lisVal, fComparar );
	SLisDestruir ( &p_lisVal );
	return ( p_lisRes );
}

/* Vacia, con su propio comparador: sigue ordenando sin el ejemplo. */
static int TestSLisOrdCrearIgual01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisOrdCrearIgual 01:\n" );

	int iVal [ 2 ] = { 30, 10 };
	SListaOrdenada * p_lisEje = CrearOrdenadaEnteros ( iVal, 2, CompararEnteros );
	SListaOrdenada * p_lisObj = NULL;
	if ( ES_VALIDO ( p_lisEje ) )
	{
		p_lisObj = SLisOrdCrearIgual ( p_lisEje );
		if ( ES_NULO ( p_lisObj ) || ( SLisOrdEsValida ( p_lisObj ) != 1 ) ||
			 ( SLisOrdNumElementos ( p_lisObj ) != 0 ) )
		{
			printf( "Error caso 1: se esperaba una lista valida y vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			if ( p_lisObj->p_cmpObj == p_lisEje->p_cmpObj )
			{
				printf( "Error caso 2: no deberia compartir el comparador\n" );
				iRes = BOOL_VAL_FALSO;
			}
			int iEje [ 2 ] = { 10, 30 };
			if ( VerificarOrdenada ( p_lisEje, iEje, 2 ) != BOOL_VAL_CIERTO )
			{
				printf( "Error caso 3: el ejemplo deberia seguir { 10, 30 }\n" );
				iRes = BOOL_VAL_FALSO;
			}
			SLisOrdDestruir ( &p_lisEje );
			SLisOrdInsertarElem ( p_lisObj, CrearElementoEntero ( 20 ) );
			SLisOrdInsertarElem ( p_lisObj, CrearElementoEntero ( 5 ) );
			int iEsp [ 2 ] = { 5, 20 };
			if ( VerificarOrdenada ( p_lisObj, iEsp, 2 ) != BOOL_VAL_CIERTO )
			{
				printf( "Error caso 4: sin el ejemplo deberia seguir ordenando\n" );
				iRes = BOOL_VAL_FALSO;
			}
		}
		if ( ES_VALIDO ( SLisOrdCrearIgual ( NULL ) ) )
		{
			printf( "Error caso 5: con una lista nula se esperaba nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisOrdDestruir ( &p_lisEje );
	SLisOrdDestruir ( &p_lisObj );
	return ( iRes );
}

/* Las dos formas, con SListaOrdenada y con SLista. El cursor no se mueve. */
static int TestSLisOrdExistenTodos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisOrdExistenTodos 01:\n" );

	int iObj [ 3 ] = { 30, 10, 20 };
	int iTodos [ 2 ] = { 30, 10 };
	int iAlguno [ 2 ] = { 40, 10 };
	int iNinguno [ 2 ] = { 50, 40 };
	SListaOrdenada * p_lisObj = CrearOrdenadaEnteros ( iObj, 3, CompararEnteros );
	SListaOrdenada * p_lisTodos = CrearOrdenadaEnteros ( iTodos, 2, CompararEnteros );
	SListaOrdenada * p_lisAlguno = CrearOrdenadaEnteros ( iAlguno, 2, CompararEnteros );
	SListaOrdenada * p_lisNinguno = CrearOrdenadaEnteros ( iNinguno, 2, CompararEnteros );
	SListaOrdenada * p_lisVacia = SLisOrdCrear ( CompararEnteros );
	SLista * p_lisTodosL = CrearListaEnteros ( iTodos, 2 );
	SLista * p_lisAlgunoL = CrearListaEnteros ( iAlguno, 2 );
	SLista * p_lisNingunoL = CrearListaEnteros ( iNinguno, 2 );
	SLista * p_lisVaciaL = SLisCrear ();
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisTodos ) && ES_VALIDO ( p_lisAlguno ) &&
		 ES_VALIDO ( p_lisNinguno ) && ES_VALIDO ( p_lisVacia ) && ES_VALIDO ( p_lisTodosL ) &&
		 ES_VALIDO ( p_lisAlgunoL ) && ES_VALIDO ( p_lisNingunoL ) && ES_VALIDO ( p_lisVaciaL ) )
	{
		SLisOrdMoverA ( p_lisObj, 1 );
		if ( ( SLisOrdExistenTodos ( p_lisObj, p_lisTodos ) != 1 ) ||
			 ( SLisOrdExisteAlguno ( p_lisObj, p_lisTodos ) != 1 ) )
		{
			printf( "Error caso 1: { 10, 30 } estan todos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisOrdExistenTodos ( p_lisObj, p_lisAlguno ) != 0 ) ||
			 ( SLisOrdExisteAlguno ( p_lisObj, p_lisAlguno ) != 1 ) )
		{
			printf( "Error caso 2: de { 10, 40 } solo esta alguno\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisOrdExistenTodos ( p_lisObj, p_lisNinguno ) != 0 ) ||
			 ( SLisOrdExisteAlguno ( p_lisObj, p_lisNinguno ) != 0 ) )
		{
			printf( "Error caso 3: de { 40, 50 } no esta ninguno\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisOrdExistenTodos ( p_lisObj, p_lisVacia ) != 1 ) ||
			 ( SLisOrdExisteAlguno ( p_lisObj, p_lisVacia ) != 0 ) )
		{
			printf( "Error caso 4: con una vacia, todos 1 y alguno 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisOrdExistenTodosLista ( p_lisObj, p_lisTodosL ) != 1 ) ||
			 ( SLisOrdExisteAlgunoLista ( p_lisObj, p_lisTodosL ) != 1 ) ||
			 ( SLisOrdExistenTodosLista ( p_lisObj, p_lisAlgunoL ) != 0 ) ||
			 ( SLisOrdExisteAlgunoLista ( p_lisObj, p_lisAlgunoL ) != 1 ) ||
			 ( SLisOrdExistenTodosLista ( p_lisObj, p_lisNingunoL ) != 0 ) ||
			 ( SLisOrdExisteAlgunoLista ( p_lisObj, p_lisNingunoL ) != 0 ) ||
			 ( SLisOrdExistenTodosLista ( p_lisObj, p_lisVaciaL ) != 1 ) ||
			 ( SLisOrdExisteAlgunoLista ( p_lisObj, p_lisVaciaL ) != 0 ) )
		{
			printf( "Error caso 5: las de SLista deberian dar lo mismo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisOrdExistenTodos ( p_lisObj, NULL ) != 0 ) ||
			 ( SLisOrdExisteAlguno ( p_lisObj, NULL ) != 0 ) ||
			 ( SLisOrdExistenTodos ( NULL, p_lisTodos ) != 0 ) ||
			 ( SLisOrdExisteAlguno ( NULL, p_lisTodos ) != 0 ) ||
			 ( SLisOrdExistenTodosLista ( p_lisObj, NULL ) != 0 ) ||
			 ( SLisOrdExisteAlgunoLista ( NULL, p_lisTodosL ) != 0 ) )
		{
			printf( "Error caso 6: con una lista nula se esperaba 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisOrdPosicion ( p_lisObj ) != 1 )
		{
			printf( "Error caso 7: el cursor deberia seguir en 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisOrdDestruir ( &p_lisObj );
	SLisOrdDestruir ( &p_lisTodos );
	SLisOrdDestruir ( &p_lisAlguno );
	SLisOrdDestruir ( &p_lisNinguno );
	SLisOrdDestruir ( &p_lisVacia );
	SLisDestruir ( &p_lisTodosL );
	SLisDestruir ( &p_lisAlgunoL );
	SLisDestruir ( &p_lisNingunoL );
	SLisDestruir ( &p_lisVaciaL );
	return ( iRes );
}

/* Mueven: los elementos son los mismos y el origen queda vacio. */
static int TestSLisOrdInsertarLista01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisOrdInsertarLista 01:\n" );

	int iObj [ 2 ] = { 30, 10 };
	int iVal [ 3 ] = { 40, 20, 5 };
	SListaOrdenada * p_lisObj = CrearOrdenadaEnteros ( iObj, 2, CompararEnteros );
	SListaOrdenada * p_lisValOrd = CrearOrdenadaEnteros ( iVal, 3, CompararEnteros );
	SLista * p_lisVal = CrearListaEnteros ( iVal, 3 );
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisValOrd ) && ES_VALIDO ( p_lisVal ) )
	{
		SElemento * p_elm5 = SLisOrdElemento ( p_lisValOrd, 0 );
		if ( SLisOrdInsertarListaOrd ( p_lisObj, p_lisValOrd ) != 1 )
		{
			printf( "Error caso 1: se esperaba 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		int iEsp [ 5 ] = { 5, 10, 20, 30, 40 };
		if ( VerificarOrdenada ( p_lisObj, iEsp, 5 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 2: se esperaba { 5, 10, 20, 30, 40 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisOrdNumElementos ( p_lisValOrd ) != 0 ) || ( SLisOrdElemento ( p_lisObj, 0 ) != p_elm5 ) )
		{
			printf( "Error caso 3: los elementos se deberian haber movido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SElemento * p_elm40 = SLisElemento ( p_lisVal, 0 );
		if ( SLisOrdInsertarLista ( p_lisObj, p_lisVal ) != 1 )
		{
			printf( "Error caso 4: se esperaba 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		int iEsp2 [ 8 ] = { 5, 5, 10, 20, 20, 30, 40, 40 };
		if ( VerificarOrdenada ( p_lisObj, iEsp2, 8 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 5: se esperaba { 5, 5, 10, 20, 20, 30, 40, 40 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Los iguales van detras de los que ya estaban. */
		if ( ( SLisNumElementos ( p_lisVal ) != 0 ) || ( SLisOrdElemento ( p_lisObj, 7 ) != p_elm40 ) )
		{
			printf( "Error caso 6: los elementos se deberian haber movido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisOrdInsertarListaOrd ( p_lisObj, p_lisValOrd ) != 1 ) ||
			 ( SLisOrdInsertarLista ( p_lisObj, p_lisVal ) != 1 ) ||
			 ( SLisOrdNumElementos ( p_lisObj ) != 8 ) )
		{
			printf( "Error caso 7: de una vacia se esperaba 1 sin cambios\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisOrdInsertarListaOrd ( p_lisObj, p_lisObj ) != 0 ) ||
			 ( SLisOrdInsertarLista ( p_lisObj, p_lisObj->p_lisContenido ) != 0 ) ||
			 ( VerificarOrdenada ( p_lisObj, iEsp2, 8 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 8: con la misma lista se esperaba 0 sin cambios\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisOrdInsertarListaOrd ( p_lisObj, NULL ) != 0 ) ||
			 ( SLisOrdInsertarListaOrd ( NULL, p_lisValOrd ) != 0 ) ||
			 ( SLisOrdInsertarLista ( p_lisObj, NULL ) != 0 ) ||
			 ( SLisOrdInsertarLista ( NULL, p_lisVal ) != 0 ) )
		{
			printf( "Error caso 9: con una lista nula se esperaba 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisOrdDestruir ( &p_lisObj );
	SLisOrdDestruir ( &p_lisValOrd );
	SLisDestruir ( &p_lisVal );
	return ( iRes );
}

/* Un elemento que no se puede insertar: vuelve a la cabeza del origen, lo
   movido antes se queda y se anota ERR_INSERCION_LISTA. Con tamaño 0 el
   elemento no es valido para SLisOrdInsertarElem ni para SElmDuplicar. */
static int TestSLisOrdInsertarListaError01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisOrdInsertarListaError 01:\n" );

	int iObj [ 2 ] = { 30, 10 };
	SListaOrdenada * p_lisObj = CrearOrdenadaEnteros ( iObj, 2, CompararEnteros );
	SLista * p_lisVal = SLisCrear ();
	SElemento * p_elmMalo = CrearElementoEntero ( 20 );
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisVal ) && ES_VALIDO ( p_elmMalo ) )
	{
		p_elmMalo->p_blqDatos->iTam = 0;
		SLisInsertarAlFinal ( p_lisVal, CrearElementoEntero ( 40 ) );
		SLisInsertarAlFinal ( p_lisVal, p_elmMalo );
		SLisInsertarAlFinal ( p_lisVal, CrearElementoEntero ( 5 ) );
		ErrLimpiar ();
		if ( ( SLisOrdInsertarLista ( p_lisObj, p_lisVal ) != 0 ) ||
			 ( ErrCodigo () != ERR_INSERCION_LISTA ) )
		{
			printf( "Error caso 1: se esperaba 0 con ERR_INSERCION_LISTA\n" );
			iRes = BOOL_VAL_FALSO;
		}
		int iEsp [ 3 ] = { 10, 30, 40 };
		if ( VerificarOrdenada ( p_lisObj, iEsp, 3 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 2: el 40 se deberia haber movido: { 10, 30, 40 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisNumElementos ( p_lisVal ) != 2 ) || ( SLisElemento ( p_lisVal, 0 ) != p_elmMalo ) ||
			 ( SElmEntero ( SLisElemento ( p_lisVal, 1 ) ) != 5 ) )
		{
			printf( "Error caso 3: en el origen deberian quedar el malo, en cabeza, y el 5\n" );
			iRes = BOOL_VAL_FALSO;
		}
		ErrLimpiar ();
		if ( ( SLisOrdInsertarListaDup ( p_lisObj, p_lisVal ) != 0 ) ||
			 ( ErrCodigo () != ERR_COPIA_OBJETO ) )
		{
			printf( "Error caso 4: al copiar el malo se esperaba 0 con ERR_COPIA_OBJETO\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( VerificarOrdenada ( p_lisObj, iEsp, 3 ) != BOOL_VAL_CIERTO ) ||
			 ( SLisNumElementos ( p_lisVal ) != 2 ) )
		{
			printf( "Error caso 5: la copia deberia parar sin tocar nada\n" );
			iRes = BOOL_VAL_FALSO;
		}
		ErrLimpiar ();
		/* Se repara para poder destruirlo. */
		p_elmMalo->p_blqDatos->iTam = sizeof ( int );
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
		SElmDestruir ( &p_elmMalo );
	}
	SLisOrdDestruir ( &p_lisObj );
	SLisDestruir ( &p_lisVal );
	return ( iRes );
}

/* Copian: el origen no cambia y los elementos son otros. */
static int TestSLisOrdInsertarListaDup01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisOrdInsertarListaDup 01:\n" );

	int iObj [ 2 ] = { 30, 10 };
	int iVal [ 2 ] = { 40, 20 };
	SListaOrdenada * p_lisObj = CrearOrdenadaEnteros ( iObj, 2, CompararEnteros );
	SListaOrdenada * p_lisValOrd = CrearOrdenadaEnteros ( iVal, 2, CompararEnteros );
	SLista * p_lisVal = CrearListaEnteros ( iVal, 2 );
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisValOrd ) && ES_VALIDO ( p_lisVal ) )
	{
		if ( SLisOrdInsertarListaOrdDup ( p_lisObj, p_lisValOrd ) != 1 )
		{
			printf( "Error caso 1: se esperaba 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		int iEsp [ 4 ] = { 10, 20, 30, 40 };
		if ( VerificarOrdenada ( p_lisObj, iEsp, 4 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 2: se esperaba { 10, 20, 30, 40 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		int iOrd [ 2 ] = { 20, 40 };
		if ( ( VerificarOrdenada ( p_lisValOrd, iOrd, 2 ) != BOOL_VAL_CIERTO ) ||
			 ( SLisOrdElemento ( p_lisObj, 1 ) == SLisOrdElemento ( p_lisValOrd, 0 ) ) )
		{
			printf( "Error caso 3: el origen deberia seguir igual y tener sus elementos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisOrdInsertarListaDup ( p_lisObj, p_lisVal ) != 1 )
		{
			printf( "Error caso 4: se esperaba 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		int iEsp2 [ 6 ] = { 10, 20, 20, 30, 40, 40 };
		if ( VerificarOrdenada ( p_lisObj, iEsp2, 6 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 5: se esperaba { 10, 20, 20, 30, 40, 40 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( VerificarLista ( p_lisVal, iVal, 2 ) != BOOL_VAL_CIERTO ) ||
			 ( SLisOrdElemento ( p_lisObj, 5 ) == SLisElemento ( p_lisVal, 0 ) ) )
		{
			printf( "Error caso 6: el origen deberia seguir { 40, 20 } y tener sus elementos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisOrdInsertarListaOrdDup ( p_lisObj, p_lisObj ) != 0 ) ||
			 ( SLisOrdInsertarListaDup ( p_lisObj, p_lisObj->p_lisContenido ) != 0 ) ||
			 ( VerificarOrdenada ( p_lisObj, iEsp2, 6 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 7: con la misma lista se esperaba 0 sin cambios\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisOrdInsertarListaOrdDup ( p_lisObj, NULL ) != 0 ) ||
			 ( SLisOrdInsertarListaOrdDup ( NULL, p_lisValOrd ) != 0 ) ||
			 ( SLisOrdInsertarListaDup ( p_lisObj, NULL ) != 0 ) ||
			 ( SLisOrdInsertarListaDup ( NULL, p_lisVal ) != 0 ) )
		{
			printf( "Error caso 8: con una lista nula se esperaba 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisOrdDestruir ( &p_lisObj );
	SLisOrdDestruir ( &p_lisValOrd );
	SLisDestruir ( &p_lisVal );
	return ( iRes );
}

/* Saca todas las apariciones de cada valor, moviendolas, a una lista nueva. */
static int TestSLisOrdExtraerLista01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisOrdExtraerLista 01:\n" );

	int iObj [ 6 ] = { 40, 20, 10, 30, 20, 20 };
	int iValOrd [ 3 ] = { 50, 40, 20 };
	int iVal [ 4 ] = { 20, 10, 20, 50 };
	SListaOrdenada * p_lisObj = CrearOrdenadaEnteros ( iObj, 6, CompararEnteros );
	SListaOrdenada * p_lisValOrd = CrearOrdenadaEnteros ( iValOrd, 3, CompararEnteros );
	SLista * p_lisVal = CrearListaEnteros ( iVal, 4 );
	SListaOrdenada * p_lisRes = NULL;
	SListaOrdenada * p_lisRes2 = NULL;
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisValOrd ) && ES_VALIDO ( p_lisVal ) )
	{
		/* p_lisObj = { 10, 20, 20, 20, 30, 40 } */
		SElemento * p_elm40 = SLisOrdElemento ( p_lisObj, 5 );
		p_lisRes = SLisOrdExtraerListaOrd ( p_lisObj, p_lisValOrd );
		int iEsp [ 4 ] = { 20, 20, 20, 40 };
		if ( ES_NULO ( p_lisRes ) || ( VerificarOrdenada ( p_lisRes, iEsp, 4 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 1: se esperaba { 20, 20, 20, 40 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			if ( ( SLisOrdElemento ( p_lisRes, 3 ) != p_elm40 ) || ( p_lisRes->p_cmpObj == p_lisObj->p_cmpObj ) )
			{
				printf( "Error caso 2: se esperaba el mismo elemento y otro comparador\n" );
				iRes = BOOL_VAL_FALSO;
			}
		}
		int iQueda [ 2 ] = { 10, 30 };
		if ( ( VerificarOrdenada ( p_lisObj, iQueda, 2 ) != BOOL_VAL_CIERTO ) ||
			 ( SLisOrdNumElementos ( p_lisValOrd ) != 3 ) )
		{
			printf( "Error caso 3: deberian quedar { 10, 30 } y los valores sin tocar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_lisRes2 = SLisOrdExtraerLista ( p_lisObj, p_lisVal );
		int iEsp2 [ 1 ] = { 10 };
		int iQueda2 [ 1 ] = { 30 };
		if ( ES_NULO ( p_lisRes2 ) || ( VerificarOrdenada ( p_lisRes2, iEsp2, 1 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarOrdenada ( p_lisObj, iQueda2, 1 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarLista ( p_lisVal, iVal, 4 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 4: se esperaba { 10 } y que quedara { 30 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SLisOrdExtraerListaOrd ( p_lisObj, p_lisObj ) ) ||
			 ES_VALIDO ( SLisOrdExtraerLista ( p_lisObj, p_lisObj->p_lisContenido ) ) ||
			 ( VerificarOrdenada ( p_lisObj, iQueda2, 1 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 5: con la misma lista se esperaba nulo sin cambios\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SLisOrdExtraerListaOrd ( p_lisObj, NULL ) ) ||
			 ES_VALIDO ( SLisOrdExtraerListaOrd ( NULL, p_lisValOrd ) ) ||
			 ES_VALIDO ( SLisOrdExtraerLista ( p_lisObj, NULL ) ) ||
			 ES_VALIDO ( SLisOrdExtraerLista ( NULL, p_lisVal ) ) )
		{
			printf( "Error caso 6: con una lista nula se esperaba nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisOrdDestruir ( &p_lisObj );
	SLisOrdDestruir ( &p_lisValOrd );
	SLisDestruir ( &p_lisVal );
	SLisOrdDestruir ( &p_lisRes );
	SLisOrdDestruir ( &p_lisRes2 );
	return ( iRes );
}

/* La union es la concatenacion, ordenada: lo comun sale dos veces. */
static int TestSLisOrdUnion01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisOrdUnion 01:\n" );

	int iVal1 [ 2 ] = { 30, 10 };
	int iVal2 [ 2 ] = { 30, 20 };
	int iValL [ 2 ] = { 25, 5 };
	SListaOrdenada * p_lisVal1 = CrearOrdenadaEnteros ( iVal1, 2, CompararEnteros );
	SListaOrdenada * p_lisVal2 = CrearOrdenadaEnteros ( iVal2, 2, CompararEnteros );
	SLista * p_lisValL = CrearListaEnteros ( iValL, 2 );
	SListaOrdenada * p_lisRes = NULL;
	SListaOrdenada * p_lisRes2 = NULL;
	SListaOrdenada * p_lisRes3 = NULL;
	if ( ES_VALIDO ( p_lisVal1 ) && ES_VALIDO ( p_lisVal2 ) && ES_VALIDO ( p_lisValL ) )
	{
		p_lisRes = SLisOrdUnion ( p_lisVal1, p_lisVal2 );
		int iEsp [ 4 ] = { 10, 20, 30, 30 };
		if ( ES_NULO ( p_lisRes ) || ( VerificarOrdenada ( p_lisRes, iEsp, 4 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 1: se esperaba { 10, 20, 30, 30 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			if ( ( SLisOrdElemento ( p_lisRes, 0 ) == SLisOrdElemento ( p_lisVal1, 0 ) ) ||
				 ( p_lisRes->p_cmpObj == p_lisVal1->p_cmpObj ) )
			{
				printf( "Error caso 2: se esperaban copias y otro comparador\n" );
				iRes = BOOL_VAL_FALSO;
			}
		}
		int iOrd1 [ 2 ] = { 10, 30 };
		int iOrd2 [ 2 ] = { 20, 30 };
		if ( ( VerificarOrdenada ( p_lisVal1, iOrd1, 2 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarOrdenada ( p_lisVal2, iOrd2, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 3: los valores no deberian cambiar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_lisRes2 = SLisOrdUnionLista ( p_lisVal1, p_lisValL );
		int iEsp2 [ 4 ] = { 5, 10, 25, 30 };
		if ( ES_NULO ( p_lisRes2 ) || ( VerificarOrdenada ( p_lisRes2, iEsp2, 4 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarLista ( p_lisValL, iValL, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 4: se esperaba { 5, 10, 25, 30 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_lisRes3 = SLisOrdUnion ( p_lisVal1, p_lisVal1 );
		int iEsp3 [ 4 ] = { 10, 10, 30, 30 };
		if ( ES_NULO ( p_lisRes3 ) || ( VerificarOrdenada ( p_lisRes3, iEsp3, 4 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 5: consigo misma se esperaba { 10, 10, 30, 30 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SLisOrdUnion ( p_lisVal1, NULL ) ) ||
			 ES_VALIDO ( SLisOrdUnion ( NULL, p_lisVal2 ) ) ||
			 ES_VALIDO ( SLisOrdUnionLista ( p_lisVal1, NULL ) ) ||
			 ES_VALIDO ( SLisOrdUnionLista ( NULL, p_lisValL ) ) )
		{
			printf( "Error caso 6: con una lista nula se esperaba nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisOrdDestruir ( &p_lisVal1 );
	SLisOrdDestruir ( &p_lisVal2 );
	SLisDestruir ( &p_lisValL );
	SLisOrdDestruir ( &p_lisRes );
	SLisOrdDestruir ( &p_lisRes2 );
	SLisOrdDestruir ( &p_lisRes3 );
	return ( iRes );
}

/* Interseccion y diferencia: copias de los de V1, segun el comparador de V1. */
static int TestSLisOrdInterseccion01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisOrdInterseccion 01:\n" );

	int iVal1 [ 4 ] = { 30, 20, 10, 20 };
	int iVal2 [ 3 ] = { 40, 30, 20 };
	int iDec1 [ 2 ] = { 25, 11 };
	int iDec2 [ 1 ] = { 13 };
	SListaOrdenada * p_lisVal1 = CrearOrdenadaEnteros ( iVal1, 4, CompararEnteros );
	SListaOrdenada * p_lisVal2 = CrearOrdenadaEnteros ( iVal2, 3, CompararEnteros );
	SLista * p_lisVal2L = CrearListaEnteros ( iVal2, 3 );
	SLista * p_lisVacia = SLisCrear ();
	SListaOrdenada * p_lisDec1 = CrearOrdenadaEnteros ( iDec1, 2, CompararDecenas );
	SLista * p_lisDec2 = CrearListaEnteros ( iDec2, 1 );
	SListaOrdenada * p_lisRes [ 8 ] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };
	if ( ES_VALIDO ( p_lisVal1 ) && ES_VALIDO ( p_lisVal2 ) && ES_VALIDO ( p_lisVal2L ) &&
		 ES_VALIDO ( p_lisVacia ) && ES_VALIDO ( p_lisDec1 ) && ES_VALIDO ( p_lisDec2 ) )
	{
		int iInt [ 3 ] = { 20, 20, 30 };
		int iDif [ 1 ] = { 10 };
		p_lisRes [ 0 ] = SLisOrdInterseccion ( p_lisVal1, p_lisVal2 );
		if ( ES_NULO ( p_lisRes [ 0 ] ) || ( VerificarOrdenada ( p_lisRes [ 0 ], iInt, 3 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 1: se esperaba la interseccion { 20, 20, 30 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			if ( ( SLisOrdElemento ( p_lisRes [ 0 ], 0 ) == SLisOrdElemento ( p_lisVal1, 1 ) ) ||
				 ( p_lisRes [ 0 ]->p_cmpObj == p_lisVal1->p_cmpObj ) )
			{
				printf( "Error caso 2: se esperaban copias y otro comparador\n" );
				iRes = BOOL_VAL_FALSO;
			}
			/* Sigue ordenando: tiene su comparador. */
			SLisOrdInsertarElem ( p_lisRes [ 0 ], CrearElementoEntero ( 25 ) );
			int iInt2 [ 4 ] = { 20, 20, 25, 30 };
			if ( VerificarOrdenada ( p_lisRes [ 0 ], iInt2, 4 ) != BOOL_VAL_CIERTO )
			{
				printf( "Error caso 3: la interseccion deberia seguir ordenando\n" );
				iRes = BOOL_VAL_FALSO;
			}
		}
		p_lisRes [ 1 ] = SLisOrdDiferencia ( p_lisVal1, p_lisVal2 );
		if ( ES_NULO ( p_lisRes [ 1 ] ) || ( VerificarOrdenada ( p_lisRes [ 1 ], iDif, 1 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 4: se esperaba la diferencia { 10 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_lisRes [ 2 ] = SLisOrdInterseccionLista ( p_lisVal1, p_lisVal2L );
		p_lisRes [ 3 ] = SLisOrdDiferenciaLista ( p_lisVal1, p_lisVal2L );
		if ( ES_NULO ( p_lisRes [ 2 ] ) || ( VerificarOrdenada ( p_lisRes [ 2 ], iInt, 3 ) != BOOL_VAL_CIERTO ) ||
			 ES_NULO ( p_lisRes [ 3 ] ) || ( VerificarOrdenada ( p_lisRes [ 3 ], iDif, 1 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 5: las de SLista deberian dar { 20, 20, 30 } y { 10 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		int iOrd1 [ 4 ] = { 10, 20, 20, 30 };
		if ( ( VerificarOrdenada ( p_lisVal1, iOrd1, 4 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarLista ( p_lisVal2L, iVal2, 3 ) != BOOL_VAL_CIERTO ) ||
			 ( SLisOrdNumElementos ( p_lisVal2 ) != 3 ) )
		{
			printf( "Error caso 6: los valores no deberian cambiar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_lisRes [ 4 ] = SLisOrdInterseccionLista ( p_lisVal1, p_lisVacia );
		p_lisRes [ 5 ] = SLisOrdDiferenciaLista ( p_lisVal1, p_lisVacia );
		if ( ES_NULO ( p_lisRes [ 4 ] ) || ( SLisOrdEsValida ( p_lisRes [ 4 ] ) != 1 ) ||
			 ( SLisOrdNumElementos ( p_lisRes [ 4 ] ) != 0 ) ||
			 ES_NULO ( p_lisRes [ 5 ] ) || ( VerificarOrdenada ( p_lisRes [ 5 ], iOrd1, 4 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 7: con una vacia, interseccion vacia y diferencia entera\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Con el comparador por decenas, 11 y 13 son iguales aunque sus bytes no. */
		p_lisRes [ 6 ] = SLisOrdInterseccionLista ( p_lisDec1, p_lisDec2 );
		p_lisRes [ 7 ] = SLisOrdDiferenciaLista ( p_lisDec1, p_lisDec2 );
		int iDecInt [ 1 ] = { 11 };
		int iDecDif [ 1 ] = { 25 };
		if ( ES_NULO ( p_lisRes [ 6 ] ) || ( VerificarOrdenada ( p_lisRes [ 6 ], iDecInt, 1 ) != BOOL_VAL_CIERTO ) ||
			 ES_NULO ( p_lisRes [ 7 ] ) || ( VerificarOrdenada ( p_lisRes [ 7 ], iDecDif, 1 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 8: por decenas se esperaba { 11 } y { 25 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SLisOrdInterseccion ( p_lisVal1, NULL ) ) ||
			 ES_VALIDO ( SLisOrdInterseccion ( NULL, p_lisVal2 ) ) ||
			 ES_VALIDO ( SLisOrdDiferencia ( p_lisVal1, NULL ) ) ||
			 ES_VALIDO ( SLisOrdDiferencia ( NULL, p_lisVal2 ) ) ||
			 ES_VALIDO ( SLisOrdInterseccionLista ( p_lisVal1, NULL ) ) ||
			 ES_VALIDO ( SLisOrdInterseccionLista ( NULL, p_lisVal2L ) ) ||
			 ES_VALIDO ( SLisOrdDiferenciaLista ( p_lisVal1, NULL ) ) ||
			 ES_VALIDO ( SLisOrdDiferenciaLista ( NULL, p_lisVal2L ) ) )
		{
			printf( "Error caso 9: con una lista nula se esperaba nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisOrdDestruir ( &p_lisVal1 );
	SLisOrdDestruir ( &p_lisVal2 );
	SLisDestruir ( &p_lisVal2L );
	SLisDestruir ( &p_lisVacia );
	SLisOrdDestruir ( &p_lisDec1 );
	SLisDestruir ( &p_lisDec2 );
	int iPos = 0;
	while ( iPos < 8 )
	{
		SLisOrdDestruir ( &( p_lisRes [ iPos ] ) );
		iPos = iPos + 1;
	}
	return ( iRes );
}

/* Con dos ordenadas del mismo comparador se recorren en paralelo: repetidos en
   las dos, valores que se pasan del final de la otra, vacias y la misma lista.
   Con otro comparador en la segunda se busca uno a uno, con el de la primera. */
static int TestSLisOrdInterseccion02 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisOrdInterseccion 02:\n" );

	int iVal1 [ 7 ] = { 50, 10, 35, 5, 20, 10, 40 };
	int iVal2 [ 5 ] = { 45, 10, 40, 30, 10 };
	int iDec1 [ 2 ] = { 25, 11 };
	int iDec2 [ 1 ] = { 13 };
	SListaOrdenada * p_lisVal1 = CrearOrdenadaEnteros ( iVal1, 7, CompararEnteros );
	SListaOrdenada * p_lisVal2 = CrearOrdenadaEnteros ( iVal2, 5, CompararEnteros );
	SListaOrdenada * p_lisVacia = SLisOrdCrear ( CompararEnteros );
	SListaOrdenada * p_lisDec1 = CrearOrdenadaEnteros ( iDec1, 2, CompararEnteros );
	SListaOrdenada * p_lisDec2 = CrearOrdenadaEnteros ( iDec2, 1, CompararDecenas );
	SListaOrdenada * p_lisRes [ 10 ] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };
	if ( ES_VALIDO ( p_lisVal1 ) && ES_VALIDO ( p_lisVal2 ) && ES_VALIDO ( p_lisVacia ) &&
		 ES_VALIDO ( p_lisDec1 ) && ES_VALIDO ( p_lisDec2 ) )
	{
		/* p_lisVal1 = { 5, 10, 10, 20, 35, 40, 50 }, p_lisVal2 = { 10, 10, 30, 40, 45 } */
		SLisOrdMoverA ( p_lisVal1, 2 );
		SLisOrdMoverA ( p_lisVal2, 3 );
		int iInt [ 3 ] = { 10, 10, 40 };
		int iDif [ 4 ] = { 5, 20, 35, 50 };
		p_lisRes [ 0 ] = SLisOrdInterseccion ( p_lisVal1, p_lisVal2 );
		p_lisRes [ 1 ] = SLisOrdDiferencia ( p_lisVal1, p_lisVal2 );
		if ( ES_NULO ( p_lisRes [ 0 ] ) || ( VerificarOrdenada ( p_lisRes [ 0 ], iInt, 3 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 1: se esperaba la interseccion { 10, 10, 40 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_NULO ( p_lisRes [ 1 ] ) || ( VerificarOrdenada ( p_lisRes [ 1 ], iDif, 4 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 2: se esperaba la diferencia { 5, 20, 35, 50 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisOrdPosicion ( p_lisVal1 ) != 2 ) || ( SLisOrdPosicion ( p_lisVal2 ) != 3 ) )
		{
			printf( "Error caso 3: los cursores no se deberian mover\n" );
			iRes = BOOL_VAL_FALSO;
		}
		int iOrd1 [ 7 ] = { 5, 10, 10, 20, 35, 40, 50 };
		p_lisRes [ 2 ] = SLisOrdInterseccion ( p_lisVal1, p_lisVacia );
		p_lisRes [ 3 ] = SLisOrdDiferencia ( p_lisVal1, p_lisVacia );
		p_lisRes [ 4 ] = SLisOrdInterseccion ( p_lisVacia, p_lisVal1 );
		p_lisRes [ 5 ] = SLisOrdDiferencia ( p_lisVacia, p_lisVal1 );
		if ( ES_NULO ( p_lisRes [ 2 ] ) || ( SLisOrdNumElementos ( p_lisRes [ 2 ] ) != 0 ) ||
			 ES_NULO ( p_lisRes [ 3 ] ) || ( VerificarOrdenada ( p_lisRes [ 3 ], iOrd1, 7 ) != BOOL_VAL_CIERTO ) ||
			 ES_NULO ( p_lisRes [ 4 ] ) || ( SLisOrdNumElementos ( p_lisRes [ 4 ] ) != 0 ) ||
			 ES_NULO ( p_lisRes [ 5 ] ) || ( SLisOrdNumElementos ( p_lisRes [ 5 ] ) != 0 ) )
		{
			printf( "Error caso 4: con vacias se esperaban { }, la primera, { } y { }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_lisRes [ 6 ] = SLisOrdInterseccion ( p_lisVal1, p_lisVal1 );
		p_lisRes [ 7 ] = SLisOrdDiferencia ( p_lisVal1, p_lisVal1 );
		if ( ES_NULO ( p_lisRes [ 6 ] ) || ( VerificarOrdenada ( p_lisRes [ 6 ], iOrd1, 7 ) != BOOL_VAL_CIERTO ) ||
			 ES_NULO ( p_lisRes [ 7 ] ) || ( SLisOrdNumElementos ( p_lisRes [ 7 ] ) != 0 ) )
		{
			printf( "Error caso 5: consigo misma se esperaba ella entera y { }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Por decenas 11 y 13 serian iguales, pero manda el comparador de la primera. */
		int iDecDif [ 2 ] = { 11, 25 };
		p_lisRes [ 8 ] = SLisOrdInterseccion ( p_lisDec1, p_lisDec2 );
		p_lisRes [ 9 ] = SLisOrdDiferencia ( p_lisDec1, p_lisDec2 );
		if ( ES_NULO ( p_lisRes [ 8 ] ) || ( SLisOrdNumElementos ( p_lisRes [ 8 ] ) != 0 ) ||
			 ES_NULO ( p_lisRes [ 9 ] ) || ( VerificarOrdenada ( p_lisRes [ 9 ], iDecDif, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 6: con otro comparador en la segunda se esperaba { } y { 11, 25 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisOrdDestruir ( &p_lisVal1 );
	SLisOrdDestruir ( &p_lisVal2 );
	SLisOrdDestruir ( &p_lisVacia );
	SLisOrdDestruir ( &p_lisDec1 );
	SLisOrdDestruir ( &p_lisDec2 );
	int iPos = 0;
	while ( iPos < 10 )
	{
		SLisOrdDestruir ( &( p_lisRes [ iPos ] ) );
		iPos = iPos + 1;
	}
	return ( iRes );
}


/* 1 solo con el cursor sobre un elemento: no en una vacia, ni deposicionada,
   ni con la lista nula. */
/* Busca por contenido con el comparador de la lista: con CompararDecenas el 25
   es igual que el 20. */
static int TestSLisOrdBuscarElem01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisOrdBuscarElem 01:\n" );

	int iVal [ 4 ] = { 30, 20, 10, 20 };
	SListaOrdenada * p_lisObj = CrearOrdenadaEnteros ( iVal, 4, CompararEnteros );
	SListaOrdenada * p_lisDec = CrearOrdenadaEnteros ( iVal, 4, CompararDecenas );
	SElemento * p_elm20 = CrearElementoEntero ( 20 );
	SElemento * p_elm25 = CrearElementoEntero ( 25 );
	SElemento * p_elm99 = CrearElementoEntero ( 99 );
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisDec ) && ES_VALIDO ( p_elm20 ) &&
		 ES_VALIDO ( p_elm25 ) && ES_VALIDO ( p_elm99 ) )
	{
		/* { 10, 20, 20, 30 }: el primero igual. */
		if ( SLisOrdBuscarElem ( p_lisObj, p_elm20 ) != 1 )
		{
			printf( "Error caso 1: el 20 deberia estar en la posicion 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisOrdBuscarElem ( p_lisObj, p_elm25 ) != -1 ) || ( SLisOrdBuscarElem ( p_lisObj, p_elm99 ) != -1 ) )
		{
			printf( "Error caso 2: ni el 25 ni el 99 deberian encontrarse\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisOrdBuscarElem ( p_lisDec, p_elm25 ) != 1 )
		{
			printf( "Error caso 3: por decenas el 25 deberia encontrarse en la posicion 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisOrdBuscarElem ( p_lisObj, NULL ) != -1 ) || ( SLisOrdBuscarElem ( NULL, p_elm20 ) != -1 ) )
		{
			printf( "Error caso 4: con un nulo se esperaba -1\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas o los elementos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SElmDestruir ( &p_elm20 );
	SElmDestruir ( &p_elm25 );
	SElmDestruir ( &p_elm99 );
	SLisOrdDestruir ( &p_lisObj );
	SLisOrdDestruir ( &p_lisDec );
	return ( iRes );
}

/* Repetidos en una ordenada: estan juntos y la igualdad la decide el
   comparador. Por bloque, por memoria cruda y por elemento. */
static int TestSLisOrdBuscarSiguiente01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisOrdBuscarSiguiente 01:\n" );

	int iVal [ 6 ] = { 40, 20, 10, 20, 30, 20 };
	int iDec [ 5 ] = { 12, 25, 21, 33, 28 };
	int iVeinte = 20;
	SListaOrdenada * p_lisObj = CrearOrdenadaEnteros ( iVal, 6, CompararEnteros );
	SListaOrdenada * p_lisDec = CrearOrdenadaEnteros ( iDec, 5, CompararDecenas );
	SElemento * p_elm20 = CrearElementoEntero ( 20 );
	SElemento * p_elm24 = CrearElementoEntero ( 24 );
	SBloque * p_blqDato = SBlqCrearEntero ();
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisDec ) && ES_VALIDO ( p_elm20 ) &&
		 ES_VALIDO ( p_elm24 ) && ES_VALIDO ( p_blqDato ) )
	{
		/* p_lisObj = { 10, 20, 20, 20, 30, 40 } */
		SBlqEscribirEntero ( p_blqDato, 20 );
		if ( ( SLisOrdBuscarPrimero ( p_lisObj, p_blqDato ) != 1 ) ||
			 ( SLisOrdBuscarSiguiente ( p_lisObj, p_blqDato, 1 ) != 2 ) ||
			 ( SLisOrdBuscarSiguiente ( p_lisObj, p_blqDato, 2 ) != 3 ) ||
			 ( SLisOrdBuscarSiguiente ( p_lisObj, p_blqDato, 3 ) != -1 ) )
		{
			printf( "Error caso 1: el 20 deberia estar en 1, 2 y 3\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisOrdBuscarPrimeroExt ( p_lisObj, (byte *) &iVeinte ) != 1 ) ||
			 ( SLisOrdBuscarSiguienteExt ( p_lisObj, (byte *) &iVeinte, 2 ) != 3 ) ||
			 ( SLisOrdBuscarSiguienteExt ( p_lisObj, (byte *) &iVeinte, 3 ) != -1 ) ||
			 ( SLisOrdBuscarPrimeroElem ( p_lisObj, p_elm20 ) != 1 ) ||
			 ( SLisOrdBuscarSiguienteElem ( p_lisObj, p_elm20, 1 ) != 2 ) ||
			 ( SLisOrdBuscarSiguienteElem ( p_lisObj, p_elm20, 3 ) != -1 ) )
		{
			printf( "Error caso 2: con memoria cruda y por elemento, lo mismo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Desde delante del primero se llega a el; desde detras del ultimo, ya no hay. */
		if ( ( SLisOrdBuscarSiguiente ( p_lisObj, p_blqDato, 0 ) != 1 ) ||
			 ( SLisOrdBuscarSiguiente ( p_lisObj, p_blqDato, 4 ) != -1 ) ||
			 ( SLisOrdBuscarSiguiente ( p_lisObj, p_blqDato, 5 ) != -1 ) ||
			 ( SLisOrdBuscarSiguiente ( p_lisObj, p_blqDato, -2 ) != -1 ) ||
			 ( SLisOrdBuscar ( p_lisObj, p_blqDato ) != 1 ) )
		{
			printf( "Error caso 3: detras de la 0 se esperaba la 1, y detras de la 4 nada\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisOrdRepeticiones ( p_lisObj, p_blqDato ) != 3 ) ||
			 ( SLisOrdRepeticionesExt ( p_lisObj, (byte *) &iVeinte ) != 3 ) ||
			 ( SLisOrdRepeticionesElem ( p_lisObj, p_elm20 ) != 3 ) ||
			 ( SLisOrdExiste ( p_lisObj, p_blqDato ) != 1 ) ||
			 ( SLisOrdExisteExt ( p_lisObj, (byte *) &iVeinte ) != 1 ) ||
			 ( SLisOrdExisteElem ( p_lisObj, p_elm20 ) != 1 ) )
		{
			printf( "Error caso 4: el 20 deberia estar 3 veces\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* El primero, el ultimo, uno intermedio que no esta y los de fuera. */
		SBlqEscribirEntero ( p_blqDato, 10 );
		int iRepUno = SLisOrdRepeticiones ( p_lisObj, p_blqDato );
		SBlqEscribirEntero ( p_blqDato, 40 );
		int iRepUlt = SLisOrdRepeticiones ( p_lisObj, p_blqDato );
		SBlqEscribirEntero ( p_blqDato, 25 );
		int iRepMed = SLisOrdRepeticiones ( p_lisObj, p_blqDato );
		int iExiMed = SLisOrdExiste ( p_lisObj, p_blqDato );
		SBlqEscribirEntero ( p_blqDato, 5 );
		int iRepMin = SLisOrdRepeticiones ( p_lisObj, p_blqDato );
		SBlqEscribirEntero ( p_blqDato, 99 );
		int iRepMax = SLisOrdRepeticiones ( p_lisObj, p_blqDato );
		if ( ( iRepUno != 1 ) || ( iRepUlt != 1 ) || ( iRepMed != 0 ) || ( iExiMed != 0 ) ||
			 ( iRepMin != 0 ) || ( iRepMax != 0 ) )
		{
			printf( "Error caso 5: el 10 y el 40 una vez; el 25, el 5 y el 99 ninguna\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Por decenas: { 12, 25, 21, 28, 33 }; el 24 es igual que los tres veintes. */
		if ( ( SLisOrdRepeticionesElem ( p_lisDec, p_elm24 ) != 3 ) ||
			 ( SLisOrdBuscarPrimeroElem ( p_lisDec, p_elm24 ) != 1 ) ||
			 ( SLisOrdBuscarSiguienteElem ( p_lisDec, p_elm24, 3 ) != -1 ) )
		{
			printf( "Error caso 6: por decenas el 24 deberia estar 3 veces, de la 1 a la 3\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisOrdBuscarSiguiente ( NULL, p_blqDato, -1 ) != -1 ) ||
			 ( SLisOrdBuscarSiguiente ( p_lisObj, NULL, -1 ) != -1 ) ||
			 ( SLisOrdBuscarSiguienteExt ( p_lisObj, NULL, -1 ) != -1 ) ||
			 ( SLisOrdBuscarSiguienteElem ( p_lisObj, NULL, -1 ) != -1 ) ||
			 ( SLisOrdRepeticiones ( NULL, p_blqDato ) != 0 ) ||
			 ( SLisOrdRepeticionesExt ( p_lisObj, NULL ) != 0 ) ||
			 ( SLisOrdRepeticionesElem ( p_lisObj, NULL ) != 0 ) ||
			 ( SLisOrdExiste ( p_lisObj, NULL ) != 0 ) ||
			 ( SLisOrdExisteElem ( NULL, p_elm20 ) != 0 ) )
		{
			printf( "Error caso 7: con un nulo se esperaba -1 al buscar y 0 al contar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas o los datos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SElmDestruir ( &p_elm20 );
	SElmDestruir ( &p_elm24 );
	SBlqDestruir ( &p_blqDato );
	SLisOrdDestruir ( &p_lisObj );
	SLisOrdDestruir ( &p_lisDec );
	return ( iRes );
}

/* Destruye todas las apariciones de cada valor buscado; la igualdad la decide
   el comparador. */
static int TestSLisOrdEliminarLista01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisOrdEliminarLista 01:\n" );

	int iObj [ 6 ] = { 40, 20, 10, 30, 20, 20 };
	int iValOrd [ 3 ] = { 50, 40, 20 };
	int iVal [ 4 ] = { 20, 10, 20, 50 };
	int iDec [ 4 ] = { 33, 12, 25, 35 };
	int iValDec [ 2 ] = { 39, 21 };
	SListaOrdenada * p_lisObj = CrearOrdenadaEnteros ( iObj, 6, CompararEnteros );
	SListaOrdenada * p_lisValOrd = CrearOrdenadaEnteros ( iValOrd, 3, CompararEnteros );
	SLista * p_lisVal = CrearListaEnteros ( iVal, 4 );
	SListaOrdenada * p_lisDec = CrearOrdenadaEnteros ( iDec, 4, CompararDecenas );
	SLista * p_lisValDec = CrearListaEnteros ( iValDec, 2 );
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisValOrd ) && ES_VALIDO ( p_lisVal ) &&
		 ES_VALIDO ( p_lisDec ) && ES_VALIDO ( p_lisValDec ) )
	{
		/* p_lisObj = { 10, 20, 20, 20, 30, 40 }: se van los tres 20; el 50 no esta
		   y se ignora. */
		int iQueda [ 2 ] = { 10, 30 };
		if ( ( SLisOrdEliminarListaOrd ( p_lisObj, p_lisValOrd ) != 1 ) ||
			 ( VerificarOrdenada ( p_lisObj, iQueda, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 1: se esperaba 1 y que quedara { 10, 30 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		int iEspValOrd [ 3 ] = { 20, 40, 50 };
		if ( VerificarOrdenada ( p_lisValOrd, iEspValOrd, 3 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 2: los valores no deberian cambiar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Que el 20 este dos veces en los valores no elimina mas: queda { 30 }. */
		int iQueda2 [ 1 ] = { 30 };
		if ( ( SLisOrdEliminarLista ( p_lisObj, p_lisVal ) != 1 ) ||
			 ( VerificarOrdenada ( p_lisObj, iQueda2, 1 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarLista ( p_lisVal, iVal, 4 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 3: se esperaba 1 y que quedara { 30 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Ya no queda ninguno: no hay nada que eliminar, y no es un error. */
		if ( ( SLisOrdEliminarLista ( p_lisObj, p_lisVal ) != 1 ) ||
			 ( VerificarOrdenada ( p_lisObj, iQueda2, 1 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 4: sin nada que eliminar se esperaba 1 sin cambios\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Por decenas el 39 es igual que el 33 y el 35, y el 21 que el 25. */
		int iQuedaDec [ 1 ] = { 12 };
		if ( ( SLisOrdEliminarLista ( p_lisDec, p_lisValDec ) != 1 ) ||
			 ( VerificarOrdenada ( p_lisDec, iQuedaDec, 1 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 5: por decenas deberia quedar { 12 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisOrdEliminarListaOrd ( p_lisObj, p_lisObj ) != 0 ) ||
			 ( SLisOrdEliminarLista ( p_lisObj, p_lisObj->p_lisContenido ) != 0 ) ||
			 ( VerificarOrdenada ( p_lisObj, iQueda2, 1 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 6: con la misma lista se esperaba 0 sin cambios\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisOrdEliminarListaOrd ( p_lisObj, NULL ) != 0 ) ||
			 ( SLisOrdEliminarListaOrd ( NULL, p_lisValOrd ) != 0 ) ||
			 ( SLisOrdEliminarLista ( p_lisObj, NULL ) != 0 ) ||
			 ( SLisOrdEliminarLista ( NULL, p_lisVal ) != 0 ) )
		{
			printf( "Error caso 7: con una lista nula se esperaba 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisOrdDestruir ( &p_lisObj );
	SLisOrdDestruir ( &p_lisValOrd );
	SLisDestruir ( &p_lisVal );
	SLisOrdDestruir ( &p_lisDec );
	SLisDestruir ( &p_lisValDec );
	return ( iRes );
}

static int TestSLisOrdEstaPosicionada01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisOrdEstaPosicionada 01:\n" );

	SListaOrdenada * p_lisObj = SLisOrdCrear ( CompararEnteros );
	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( SLisOrdEstaPosicionada ( p_lisObj ) != 0 )
		{
			printf( "Error caso 1: una lista vacia no deberia estar posicionada\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisOrdInsertarElem ( p_lisObj, CrearElementoEntero ( 10 ) );
		SLisOrdInsertarElem ( p_lisObj, CrearElementoEntero ( 20 ) );
		SLisOrdInicio ( p_lisObj );
		if ( SLisOrdEstaPosicionada ( p_lisObj ) != 1 )
		{
			printf( "Error caso 2: tras Inicio deberia estar posicionada\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisOrdSiguiente ( p_lisObj );
		SLisOrdSiguiente ( p_lisObj );
		if ( SLisOrdEstaPosicionada ( p_lisObj ) != 0 )
		{
			printf( "Error caso 3: pasado el ultimo no deberia estar posicionada\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisOrdFinal ( p_lisObj );
		SLisOrdDeposicionar ( p_lisObj );
		if ( SLisOrdEstaPosicionada ( p_lisObj ) != 0 )
		{
			printf( "Error caso 4: tras Deposicionar no deberia estar posicionada\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisOrdEstaPosicionada ( NULL ) != 0 )
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
	SLisOrdDestruir ( &p_lisObj );
	return ( iRes );
}

int TestSListaOrdenada ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SListaOrdenada]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSLisOrdCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisOrdInsertarOrdenado01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisOrdBuscar01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisOrdBuscarExt01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisOrdEliminar01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisOrdExtraerElem01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisOrdInvalidos01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisOrdEncapsular01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisOrdCrearDesdeLista01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisOrdDuplicar01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisOrdDuplicarLista01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisOrdCrearIgual01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisOrdExistenTodos01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisOrdInsertarLista01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisOrdInsertarListaDup01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisOrdInsertarListaError01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisOrdExtraerLista01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisOrdEliminarLista01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisOrdUnion01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisOrdInterseccion01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisOrdInterseccion02 () == BOOL_VAL_CIERTO ) &&
			( TestSLisOrdBuscarElem01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisOrdBuscarSiguiente01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisOrdEstaPosicionada01 () == BOOL_VAL_CIERTO ) )
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
