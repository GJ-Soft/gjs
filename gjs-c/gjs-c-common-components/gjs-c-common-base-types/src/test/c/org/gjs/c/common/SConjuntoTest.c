#include "Base.h"

#include "SConjunto.h"



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



static int TestSCnjCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjCrear 01:\n" );

	SConjunto * p_cnjObj = SCnjCrear ( CompararEnteros );
	if ( ES_NULO ( p_cnjObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SCnjEsValido ( p_cnjObj ) != 1 )
		{
			printf( "Error caso 2: el conjunto recien creado deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnjEstaVacio ( p_cnjObj ) != 1 )
		{
			printf( "Error caso 3: el conjunto recien creado deberia estar vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnjNumElementos ( p_cnjObj ) != 0 )
		{
			printf( "Error caso 4: se esperaban 0 elementos\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SCnjDestruir ( &p_cnjObj );

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		printf( "Error caso 5: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSCnjInsertar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjInsertar 01:\n" );

	SConjunto * p_cnjObj = SCnjCrear ( CompararEnteros );
	if ( ES_VALIDO ( p_cnjObj ) )
	{
		/* Se insertan desordenados; el conjunto los mantiene ordenados y sin repetir. */
		if ( SCnjInsertarElem ( p_cnjObj, CrearElementoEntero ( 30 ) ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al insertar el primero\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SCnjInsertarElem ( p_cnjObj, CrearElementoEntero ( 10 ) );
		SCnjInsertarElem ( p_cnjObj, CrearElementoEntero ( 20 ) );

		if ( SCnjNumElementos ( p_cnjObj ) != 3 )
		{
			printf( "Error caso 2: se esperaban 3 elementos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		int iEsp [ 3 ] = { 10, 20, 30 };
		int iPos = 0;
		while ( ( iPos < 3 ) && ( iRes == BOOL_VAL_CIERTO ) )
		{
			SElemento * p_elmObj = SCnjElemento ( p_cnjObj, iPos );
			if ( ES_NULO ( p_elmObj ) || ( SElmEntero ( p_elmObj ) != iEsp [ iPos ] ) )
			{
				printf( "Error caso 3: en la posicion %d se esperaba %d\n", iPos, iEsp [ iPos ] );
				iRes = BOOL_VAL_FALSO;
			}
			iPos = iPos + 1;
		}
		/* Insertar un duplicado no debe anadirse; el conjunto no toma el elemento. */
		SElemento * p_elmDup = CrearElementoEntero ( 20 );
		if ( SCnjInsertarElem ( p_cnjObj, p_elmDup ) != 0 )
		{
			printf( "Error caso 4: insertar un duplicado deberia devolver 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SElmDestruir ( &p_elmDup );
		if ( SCnjNumElementos ( p_cnjObj ) != 3 )
		{
			printf( "Error caso 5: el conjunto no deberia crecer con un duplicado\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el conjunto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCnjDestruir ( &p_cnjObj );
	return ( iRes );
}

static int TestSCnjExiste01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjExiste 01:\n" );

	SConjunto * p_cnjObj = SCnjCrear ( CompararEnteros );
	if ( ES_VALIDO ( p_cnjObj ) )
	{
		SCnjInsertarElem ( p_cnjObj, CrearElementoEntero ( 10 ) );
		SCnjInsertarElem ( p_cnjObj, CrearElementoEntero ( 20 ) );
		SCnjInsertarElem ( p_cnjObj, CrearElementoEntero ( 30 ) );

		SBloque * p_blqBuscar = SBlqCrearEntero ();
		if ( ES_VALIDO ( p_blqBuscar ) )
		{
			SBlqEscribirEntero ( p_blqBuscar, 20 );
			if ( SCnjExiste ( p_cnjObj, p_blqBuscar ) != 1 )
			{
				printf( "Error caso 1: el 20 deberia existir\n" );
				iRes = BOOL_VAL_FALSO;
			}
			if ( SCnjBuscar ( p_cnjObj, p_blqBuscar ) != 1 )
			{
				printf( "Error caso 2: el 20 deberia estar en la posicion 1\n" );
				iRes = BOOL_VAL_FALSO;
			}
			/* Mayor que el maximo: no existe ( valida el arreglo de la busqueda ). */
			SBlqEscribirEntero ( p_blqBuscar, 99 );
			if ( SCnjExiste ( p_cnjObj, p_blqBuscar ) != 0 )
			{
				printf( "Error caso 3: el 99 no deberia existir\n" );
				iRes = BOOL_VAL_FALSO;
			}
		}
		SBlqDestruir ( &p_blqBuscar );
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el conjunto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCnjDestruir ( &p_cnjObj );
	return ( iRes );
}

static int TestSCnjExisteExt01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjExisteExt 01:\n" );

	SConjunto * p_cnjObj = SCnjCrear ( CompararEnteros );
	if ( ES_VALIDO ( p_cnjObj ) )
	{
		SCnjInsertarElem ( p_cnjObj, CrearElementoEntero ( 10 ) );
		SCnjInsertarElem ( p_cnjObj, CrearElementoEntero ( 20 ) );
		SCnjInsertarElem ( p_cnjObj, CrearElementoEntero ( 30 ) );

		int iBuscar = 20;
		if ( SCnjExisteExt ( p_cnjObj, (byte *) &iBuscar ) != 1 )
		{
			printf( "Error caso 1: el 20 deberia existir\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnjBuscarExt ( p_cnjObj, (byte *) &iBuscar ) != 1 )
		{
			printf( "Error caso 2: el 20 deberia estar en la posicion 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Mayor que el maximo: no existe. */
		iBuscar = 99;
		if ( SCnjExisteExt ( p_cnjObj, (byte *) &iBuscar ) != 0 )
		{
			printf( "Error caso 3: el 99 no deberia existir\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el conjunto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCnjDestruir ( &p_cnjObj );
	return ( iRes );
}

static int TestSCnjEliminar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjEliminar 01:\n" );

	SConjunto * p_cnjObj = SCnjCrear ( CompararEnteros );
	if ( ES_VALIDO ( p_cnjObj ) )
	{
		SCnjInsertarElem ( p_cnjObj, CrearElementoEntero ( 10 ) );
		SCnjInsertarElem ( p_cnjObj, CrearElementoEntero ( 20 ) );
		SCnjInsertarElem ( p_cnjObj, CrearElementoEntero ( 30 ) );

		SCnjEliminarElem ( p_cnjObj, 1 );
		if ( SCnjNumElementos ( p_cnjObj ) != 2 )
		{
			printf( "Error caso 1: se esperaban 2 elementos tras eliminar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* El 20 ya no debe existir. */
		SBloque * p_blqBuscar = SBlqCrearEntero ();
		if ( ES_VALIDO ( p_blqBuscar ) )
		{
			SBlqEscribirEntero ( p_blqBuscar, 20 );
			if ( SCnjExiste ( p_cnjObj, p_blqBuscar ) != 0 )
			{
				printf( "Error caso 2: el 20 no deberia existir tras eliminarlo\n" );
				iRes = BOOL_VAL_FALSO;
			}
		}
		SBlqDestruir ( &p_blqBuscar );

		if ( SCnjVaciar ( p_cnjObj ) != 1 )
		{
			printf( "Error caso 3: se esperaba resultado 1 al vaciar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnjEstaVacio ( p_cnjObj ) != 1 )
		{
			printf( "Error caso 4: el conjunto deberia quedar vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el conjunto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCnjDestruir ( &p_cnjObj );
	return ( iRes );
}

static int TestSCnjPrimeroUltimo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjPrimeroUltimo 01:\n" );

	SConjunto * p_cnjObj = SCnjCrear ( CompararEnteros );
	if ( ES_VALIDO ( p_cnjObj ) )
	{
		/* Vacio: no hay ni primero ni ultimo. */
		if ( ES_VALIDO ( SCnjPrimero ( p_cnjObj ) ) )
		{
			printf( "Error caso 1: el primero de un conjunto vacio deberia ser nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SCnjUltimo ( p_cnjObj ) ) )
		{
			printf( "Error caso 2: el ultimo de un conjunto vacio deberia ser nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Con un solo elemento, primero y ultimo son el mismo. */
		SCnjInsertarElem ( p_cnjObj, CrearElementoEntero ( 20 ) );
		SElemento * p_elmPri = SCnjPrimero ( p_cnjObj );
		SElemento * p_elmUlt = SCnjUltimo ( p_cnjObj );
		if ( ES_NULO ( p_elmPri ) || ( SElmEntero ( p_elmPri ) != 20 ) )
		{
			printf( "Error caso 3: con un elemento, el primero deberia ser el 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( p_elmUlt != p_elmPri )
		{
			printf( "Error caso 4: con un elemento, el ultimo deberia ser el mismo que el primero\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Se insertan por fuera de los extremos: primero y ultimo siguen el orden, no la insercion. */
		SCnjInsertarElem ( p_cnjObj, CrearElementoEntero ( 30 ) );
		SCnjInsertarElem ( p_cnjObj, CrearElementoEntero ( 10 ) );
		p_elmPri = SCnjPrimero ( p_cnjObj );
		p_elmUlt = SCnjUltimo ( p_cnjObj );
		if ( ES_NULO ( p_elmPri ) || ( SElmEntero ( p_elmPri ) != 10 ) )
		{
			printf( "Error caso 5: el primero deberia ser el 10\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_NULO ( p_elmUlt ) || ( SElmEntero ( p_elmUlt ) != 30 ) )
		{
			printf( "Error caso 6: el ultimo deberia ser el 30\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Tras eliminar el ultimo, el nuevo ultimo es el 20. */
		SCnjEliminarElem ( p_cnjObj, 2 );
		p_elmUlt = SCnjUltimo ( p_cnjObj );
		if ( ES_NULO ( p_elmUlt ) || ( SElmEntero ( p_elmUlt ) != 20 ) )
		{
			printf( "Error caso 7: tras eliminar el 30, el ultimo deberia ser el 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SCnjPrimero ( NULL ) ) || ES_VALIDO ( SCnjUltimo ( NULL ) ) )
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
	SCnjDestruir ( &p_cnjObj );
	return ( iRes );
}

static int TestSCnjPosicion01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjPosicion 01:\n" );

	SConjunto * p_cnjObj = SCnjCrear ( CompararEnteros );
	if ( ES_VALIDO ( p_cnjObj ) )
	{
		/* Vacio: nada tiene posicion. */
		SElemento * p_elmFuera = CrearElementoEntero ( 20 );
		if ( SCnjPosicion ( p_cnjObj, p_elmFuera ) != -1 )
		{
			printf( "Error caso 1: en un conjunto vacio la posicion deberia ser -1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SCnjInsertarElem ( p_cnjObj, CrearElementoEntero ( 30 ) );
		SCnjInsertarElem ( p_cnjObj, CrearElementoEntero ( 10 ) );
		SCnjInsertarElem ( p_cnjObj, CrearElementoEntero ( 20 ) );

		/* Los elementos del propio conjunto estan en la posicion que da SCnjElemento. */
		int iPos = 0;
		while ( iPos < 3 )
		{
			if ( SCnjPosicion ( p_cnjObj, SCnjElemento ( p_cnjObj, iPos ) ) != iPos )
			{
				printf( "Error caso 2: el elemento %d deberia estar en la posicion %d\n", iPos, iPos );
				iRes = BOOL_VAL_FALSO;
			}
			iPos = iPos + 1;
		}
		/* Posicion por valor: un elemento ajeno con el mismo dato da la posicion del del conjunto. */
		if ( SCnjPosicion ( p_cnjObj, p_elmFuera ) != 1 )
		{
			printf( "Error caso 3: un 20 ajeno al conjunto deberia dar la posicion 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnjPosicion ( p_cnjObj, SCnjPrimero ( p_cnjObj ) ) != 0 )
		{
			printf( "Error caso 4: el primero deberia estar en la posicion 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnjPosicion ( p_cnjObj, SCnjUltimo ( p_cnjObj ) ) != 2 )
		{
			printf( "Error caso 5: el ultimo deberia estar en la posicion 2\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Valores que no estan: menor que el minimo, intermedio y mayor que el maximo. */
		SElmEscribirEntero ( p_elmFuera, 5 );
		if ( SCnjPosicion ( p_cnjObj, p_elmFuera ) != -1 )
		{
			printf( "Error caso 6: el 5 no deberia tener posicion\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SElmEscribirEntero ( p_elmFuera, 15 );
		if ( SCnjPosicion ( p_cnjObj, p_elmFuera ) != -1 )
		{
			printf( "Error caso 7: el 15 no deberia tener posicion\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SElmEscribirEntero ( p_elmFuera, 99 );
		if ( SCnjPosicion ( p_cnjObj, p_elmFuera ) != -1 )
		{
			printf( "Error caso 8: el 99 no deberia tener posicion\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnjPosicion ( p_cnjObj, NULL ) != -1 )
		{
			printf( "Error caso 9: un elemento nulo no deberia tener posicion\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SElmEscribirEntero ( p_elmFuera, 20 );
		if ( SCnjPosicion ( NULL, p_elmFuera ) != -1 )
		{
			printf( "Error caso 10: en un conjunto nulo la posicion deberia ser -1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SElmDestruir ( &p_elmFuera );
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el conjunto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCnjDestruir ( &p_cnjObj );
	return ( iRes );
}

static int TestSCnjExtraerElem01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjExtraerElem 01:\n" );

	SConjunto * p_cnjObj = SCnjCrear ( CompararEnteros );
	if ( ES_VALIDO ( p_cnjObj ) )
	{
		/* Conjunto vacio: no hay nada que extraer. */
		if ( ES_VALIDO ( SCnjExtraerElem ( p_cnjObj, 0 ) ) )
		{
			printf( "Error caso 1: extraer de un conjunto vacio deberia devolver nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SCnjInsertarElem ( p_cnjObj, CrearElementoEntero ( 30 ) );
		SCnjInsertarElem ( p_cnjObj, CrearElementoEntero ( 10 ) );
		SCnjInsertarElem ( p_cnjObj, CrearElementoEntero ( 40 ) );
		SCnjInsertarElem ( p_cnjObj, CrearElementoEntero ( 20 ) );

		/* Se extrae el mismo elemento que habia, vivo y desenganchado del conjunto. */
		SElemento * p_elmEsp = SCnjElemento ( p_cnjObj, 1 );
		SElemento * p_elmExt = SCnjExtraerElem ( p_cnjObj, 1 );
		if ( ES_NULO ( p_elmExt ) || ( p_elmExt != p_elmEsp ) || ( SElmEntero ( p_elmExt ) != 20 ) )
		{
			printf( "Error caso 2: se esperaba extraer el 20 de la posicion 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			if ( ES_VALIDO ( SElmSucesor ( p_elmExt ) ) || ES_VALIDO ( SElmAntecesor ( p_elmExt ) ) )
			{
				printf( "Error caso 3: el elemento extraido no deberia conservar enlaces\n" );
				iRes = BOOL_VAL_FALSO;
			}
			/* Su valor ya no esta en el conjunto. */
			if ( SCnjExiste ( p_cnjObj, SElmDatos ( p_elmExt ) ) != 0 )
			{
				printf( "Error caso 4: el 20 no deberia existir tras extraerlo\n" );
				iRes = BOOL_VAL_FALSO;
			}
		}
		if ( ( SCnjNumElementos ( p_cnjObj ) != 3 ) ||
			 ( SElmEntero ( SCnjElemento ( p_cnjObj, 0 ) ) != 10 ) ||
			 ( SElmEntero ( SCnjElemento ( p_cnjObj, 1 ) ) != 30 ) ||
			 ( SElmEntero ( SCnjElemento ( p_cnjObj, 2 ) ) != 40 ) )
		{
			printf( "Error caso 5: tras extraer deberian quedar 10, 30 y 40\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Posiciones fuera de rango: nulo, y el conjunto no cambia. */
		if ( ES_VALIDO ( SCnjExtraerElem ( p_cnjObj, -1 ) ) || ES_VALIDO ( SCnjExtraerElem ( p_cnjObj, 3 ) ) )
		{
			printf( "Error caso 6: extraer fuera de rango deberia devolver nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnjNumElementos ( p_cnjObj ) != 3 )
		{
			printf( "Error caso 7: extraer fuera de rango no deberia cambiar el conjunto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* El extraido se puede volver a insertar y recupera su sitio en el orden. */
		if ( ES_VALIDO ( p_elmExt ) )
		{
			if ( SCnjInsertarElem ( p_cnjObj, p_elmExt ) != 1 )
			{
				printf( "Error caso 8: el elemento extraido deberia poder volver a insertarse\n" );
				iRes = BOOL_VAL_FALSO;
				SElmDestruir ( &p_elmExt );
			}
			else if ( SCnjElemento ( p_cnjObj, 1 ) != p_elmExt )
			{
				printf( "Error caso 9: al reinsertarlo deberia volver a la posicion 1\n" );
				iRes = BOOL_VAL_FALSO;
			}
		}
		/* Los extremos; los extraidos son ya del llamador. */
		p_elmExt = SCnjExtraerElem ( p_cnjObj, 0 );
		if ( ES_NULO ( p_elmExt ) || ( SElmEntero ( p_elmExt ) != 10 ) )
		{
			printf( "Error caso 10: extraer la posicion 0 deberia dar el 10\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SElmDestruir ( &p_elmExt );
		p_elmExt = SCnjExtraerElem ( p_cnjObj, SCnjNumElementos ( p_cnjObj ) - 1 );
		if ( ES_NULO ( p_elmExt ) || ( SElmEntero ( p_elmExt ) != 40 ) )
		{
			printf( "Error caso 11: extraer la ultima posicion deberia dar el 40\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SElmDestruir ( &p_elmExt );
		if ( ( SCnjNumElementos ( p_cnjObj ) != 2 ) ||
			 ( SElmEntero ( SCnjPrimero ( p_cnjObj ) ) != 20 ) ||
			 ( SElmEntero ( SCnjUltimo ( p_cnjObj ) ) != 30 ) )
		{
			printf( "Error caso 12: deberian quedar el 20 y el 30\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SCnjExtraerElem ( NULL, 0 ) ) )
		{
			printf( "Error caso 13: extraer de un conjunto nulo deberia devolver nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el conjunto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCnjDestruir ( &p_cnjObj );
	return ( iRes );
}

static int TestSCnjInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjInvalidos 01:\n" );

	if ( SCnjEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: un conjunto nulo no deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SCnjNumElementos ( NULL ) != 0 )
	{
		printf( "Error caso 2: el numero de elementos de un conjunto nulo deberia ser 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SCnjEstaVacio ( NULL ) != 1 )
	{
		printf( "Error caso 3: un conjunto nulo deberia considerarse vacio\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SConjunto * p_cnjNulo = NULL;
	SCnjDestruir ( &p_cnjNulo );
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

static SListaOrdenada * CrearOrdenadaEnteros ( int * p_iValores, int iNum )
{
	SListaOrdenada * p_lisObj = SLisOrdCrear ( CompararEnteros );
	int iPos = 0;
	while ( ES_VALIDO ( p_lisObj ) && ( iPos < iNum ) )
	{
		SLisOrdInsertarElem ( p_lisObj, CrearElementoEntero ( p_iValores [ iPos ] ) );
		iPos = iPos + 1;
	}
	return ( p_lisObj );
}

static SConjunto * CrearConjuntoEnteros ( int * p_iValores, int iNum )
{
	SLista * p_lisObj = CrearListaEnteros ( p_iValores, iNum );
	SConjunto * p_cnjObj = SCnjCrearDesdeLista ( p_lisObj, CompararEnteros );
	SLisDestruir ( &p_lisObj );
	return ( p_cnjObj );
}

/* Numero y valores, en orden, sin desreferenciar un nulo. */
static int VerificarConjunto ( SConjunto * p_cnjObj, int * p_iEsperados, int iNum )
{
	int iRes = BOOL_VAL_CIERTO;

	if ( ( SCnjEsValido ( p_cnjObj ) != 1 ) || ( SCnjNumElementos ( p_cnjObj ) != iNum ) )
	{
		printf( "  Verificacion: se esperaba un conjunto de %d elementos: %d\n", iNum, SCnjNumElementos ( p_cnjObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	int iPos = 0;
	while ( ( iPos < iNum ) && ( iRes == BOOL_VAL_CIERTO ) )
	{
		SElemento * p_elmObj = SCnjElemento ( p_cnjObj, iPos );
		if ( ES_NULO ( p_elmObj ) || ( SElmEntero ( p_elmObj ) != p_iEsperados [ iPos ] ) )
		{
			printf( "  Verificacion: en pos %d se esperaba %d\n", iPos, p_iEsperados [ iPos ] );
			iRes = BOOL_VAL_FALSO;
		}
		iPos = iPos + 1;
	}
	return ( iRes );
}

/* Comprueba un conjunto devuelto por una operacion y lo destruye. */
static int VerificarYDestruir ( SConjunto ** p_p_cnjObj, int * p_iEsperados, int iNum )
{
	int iRes = VerificarConjunto ( *p_p_cnjObj, p_iEsperados, iNum );
	SCnjDestruir ( p_p_cnjObj );
	return ( iRes );
}

/* CrearDesdeLista y Duplicar copian y quitan los repetidos; EncapsularLista se
   queda con la lista, salvo que tenga repetidos. */
static int TestSCnjCrearDesdeLista01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjCrearDesdeLista 01:\n" );

	int iVal [ 5 ] = { 30, 10, 30, 20, 10 };
	int iEsp [ 3 ] = { 10, 20, 30 };
	int iRep [ 3 ] = { 20, 10, 20 };
	SLista * p_lisVal = CrearListaEnteros ( iVal, 5 );
	SListaOrdenada * p_lisOrd = CrearOrdenadaEnteros ( iEsp, 3 );
	SListaOrdenada * p_lisRep = CrearOrdenadaEnteros ( iRep, 3 );
	SConjunto * p_cnjObj = NULL;
	SConjunto * p_cnjEnc = NULL;
	SConjunto * p_cnjDup = NULL;
	if ( ES_VALIDO ( p_lisVal ) && ES_VALIDO ( p_lisOrd ) && ES_VALIDO ( p_lisRep ) )
	{
		p_cnjObj = SCnjCrearDesdeLista ( p_lisVal, CompararEnteros );
		if ( ( VerificarConjunto ( p_cnjObj, iEsp, 3 ) != BOOL_VAL_CIERTO ) ||
			 ( SLisNumElementos ( p_lisVal ) != 5 ) ||
			 ( SCnjElemento ( p_cnjObj, 2 ) == SLisElemento ( p_lisVal, 0 ) ) )
		{
			printf( "Error caso 1: se esperaban copias de { 10, 20, 30 } y la lista sin tocar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_cnjDup = SCnjDuplicar ( p_cnjObj );
		if ( ( VerificarConjunto ( p_cnjDup, iEsp, 3 ) != BOOL_VAL_CIERTO ) ||
			 ( SCnjElemento ( p_cnjDup, 0 ) == SCnjElemento ( p_cnjObj, 0 ) ) )
		{
			printf( "Error caso 2: el duplicado deberia tener copias de { 10, 20, 30 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_cnjEnc = SCnjEncapsularLista ( p_lisOrd );
		if ( ( VerificarConjunto ( p_cnjEnc, iEsp, 3 ) != BOOL_VAL_CIERTO ) ||
			 ( SCnjLista ( p_cnjEnc ) != p_lisOrd ) )
		{
			printf( "Error caso 3: se esperaba un conjunto con la misma lista\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			/* Ahora es del conjunto. */
			p_lisOrd = NULL;
		}
		/* Con repetidos no es un conjunto: la lista sigue siendo del test. */
		if ( ES_VALIDO ( SCnjEncapsularLista ( p_lisRep ) ) ||
			 ( SLisOrdNumElementos ( p_lisRep ) != 3 ) )
		{
			printf( "Error caso 4: con repetidos se esperaba nulo y la lista intacta\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SCnjCrearDesdeLista ( NULL, CompararEnteros ) ) ||
			 ES_VALIDO ( SCnjEncapsularLista ( NULL ) ) ||
			 ES_VALIDO ( SCnjDuplicar ( NULL ) ) ||
			 ES_VALIDO ( SCnjLista ( NULL ) ) )
		{
			printf( "Error caso 5: con nulos se esperaba nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisDestruir ( &p_lisVal );
	SLisOrdDestruir ( &p_lisOrd );
	SLisOrdDestruir ( &p_lisRep );
	SCnjDestruir ( &p_cnjObj );
	SCnjDestruir ( &p_cnjEnc );
	SCnjDestruir ( &p_cnjDup );
	return ( iRes );
}

static int TestSCnjExistenTodos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjExistenTodos 01:\n" );

	int iA [ 3 ] = { 10, 20, 30 };
	int iTodos [ 2 ] = { 30, 20 };
	int iAlguno [ 2 ] = { 40, 20 };
	int iNinguno [ 1 ] = { 40 };
	SConjunto * p_cnjA = CrearConjuntoEnteros ( iA, 3 );
	SConjunto * p_cnjTodos = CrearConjuntoEnteros ( iTodos, 2 );
	SConjunto * p_cnjAlguno = CrearConjuntoEnteros ( iAlguno, 2 );
	SListaOrdenada * p_lisOrdTodos = CrearOrdenadaEnteros ( iTodos, 2 );
	SListaOrdenada * p_lisOrdNinguno = CrearOrdenadaEnteros ( iNinguno, 1 );
	SLista * p_lisAlguno = CrearListaEnteros ( iAlguno, 2 );
	SLista * p_lisNinguno = CrearListaEnteros ( iNinguno, 1 );
	if ( ES_VALIDO ( p_cnjA ) && ES_VALIDO ( p_cnjTodos ) && ES_VALIDO ( p_cnjAlguno ) && ES_VALIDO ( p_lisOrdTodos ) &&
		 ES_VALIDO ( p_lisOrdNinguno ) && ES_VALIDO ( p_lisAlguno ) && ES_VALIDO ( p_lisNinguno ) )
	{
		if ( ( SCnjExistenTodos ( p_cnjA, p_cnjTodos ) != 1 ) || ( SCnjExistenTodos ( p_cnjA, p_cnjAlguno ) != 0 ) ||
			 ( SCnjExisteAlguno ( p_cnjA, p_cnjAlguno ) != 1 ) )
		{
			printf( "Error caso 1: con conjuntos se esperaba 1, 0 y 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SCnjExistenTodosListaOrd ( p_cnjA, p_lisOrdTodos ) != 1 ) ||
			 ( SCnjExistenTodosListaOrd ( p_cnjA, p_lisOrdNinguno ) != 0 ) ||
			 ( SCnjExisteAlgunoListaOrd ( p_cnjA, p_lisOrdTodos ) != 1 ) ||
			 ( SCnjExisteAlgunoListaOrd ( p_cnjA, p_lisOrdNinguno ) != 0 ) )
		{
			printf( "Error caso 2: con listas ordenadas se esperaba 1, 0, 1 y 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SCnjExistenTodosLista ( p_cnjA, p_lisAlguno ) != 0 ) ||
			 ( SCnjExisteAlgunoLista ( p_cnjA, p_lisAlguno ) != 1 ) ||
			 ( SCnjExisteAlgunoLista ( p_cnjA, p_lisNinguno ) != 0 ) )
		{
			printf( "Error caso 3: con listas se esperaba 0, 1 y 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SCnjExistenTodos ( NULL, p_cnjTodos ) != 0 ) || ( SCnjExistenTodos ( p_cnjA, NULL ) != 0 ) ||
			 ( SCnjExisteAlguno ( p_cnjA, NULL ) != 0 ) || ( SCnjExistenTodosLista ( NULL, p_lisAlguno ) != 0 ) ||
			 ( SCnjExisteAlgunoListaOrd ( NULL, p_lisOrdTodos ) != 0 ) )
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
	SCnjDestruir ( &p_cnjA );
	SCnjDestruir ( &p_cnjTodos );
	SCnjDestruir ( &p_cnjAlguno );
	SLisOrdDestruir ( &p_lisOrdTodos );
	SLisOrdDestruir ( &p_lisOrdNinguno );
	SLisDestruir ( &p_lisAlguno );
	SLisDestruir ( &p_lisNinguno );
	return ( iRes );
}

/* Insertan copias de lo que no esta; lo repetido entra una vez. */
static int TestSCnjInsertarLista01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjInsertarLista 01:\n" );

	int iA [ 2 ] = { 10, 30 };
	int iVal [ 4 ] = { 30, 20, 20, 40 };
	int iCnj [ 2 ] = { 5, 10 };
	int iOrd [ 2 ] = { 50, 50 };
	SConjunto * p_cnjA = CrearConjuntoEnteros ( iA, 2 );
	SConjunto * p_cnjVal = CrearConjuntoEnteros ( iCnj, 2 );
	SLista * p_lisVal = CrearListaEnteros ( iVal, 4 );
	SListaOrdenada * p_lisOrd = CrearOrdenadaEnteros ( iOrd, 2 );
	if ( ES_VALIDO ( p_cnjA ) && ES_VALIDO ( p_cnjVal ) && ES_VALIDO ( p_lisVal ) && ES_VALIDO ( p_lisOrd ) )
	{
		int iEsp1 [ 4 ] = { 10, 20, 30, 40 };
		if ( ( SCnjInsertarLista ( p_cnjA, p_lisVal ) != 1 ) ||
			 ( VerificarConjunto ( p_cnjA, iEsp1, 4 ) != BOOL_VAL_CIERTO ) ||
			 ( SLisNumElementos ( p_lisVal ) != 4 ) )
		{
			printf( "Error caso 1: deberia quedar { 10, 20, 30, 40 } y la lista sin tocar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		int iEsp2 [ 5 ] = { 5, 10, 20, 30, 40 };
		if ( ( SCnjInsertarConjunto ( p_cnjA, p_cnjVal ) != 1 ) ||
			 ( VerificarConjunto ( p_cnjA, iEsp2, 5 ) != BOOL_VAL_CIERTO ) ||
			 ( SCnjElemento ( p_cnjA, 0 ) == SCnjElemento ( p_cnjVal, 0 ) ) )
		{
			printf( "Error caso 2: deberia quedar { 5, 10, 20, 30, 40 } con copias\n" );
			iRes = BOOL_VAL_FALSO;
		}
		int iEsp3 [ 6 ] = { 5, 10, 20, 30, 40, 50 };
		if ( ( SCnjInsertarListaOrd ( p_cnjA, p_lisOrd ) != 1 ) ||
			 ( VerificarConjunto ( p_cnjA, iEsp3, 6 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 3: el 50 repetido deberia entrar una vez\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Consigo mismo no hay nada que insertar. */
		if ( ( SCnjInsertarConjunto ( p_cnjA, p_cnjA ) != 1 ) ||
			 ( VerificarConjunto ( p_cnjA, iEsp3, 6 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 4: consigo mismo se esperaba 1 sin cambios\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SCnjInsertarLista ( NULL, p_lisVal ) != 0 ) || ( SCnjInsertarLista ( p_cnjA, NULL ) != 0 ) ||
			 ( SCnjInsertarConjunto ( p_cnjA, NULL ) != 0 ) || ( SCnjInsertarListaOrd ( p_cnjA, NULL ) != 0 ) ||
			 ( VerificarConjunto ( p_cnjA, iEsp3, 6 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 5: con nulos se esperaba 0 sin cambios\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear los conjuntos o las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCnjDestruir ( &p_cnjA );
	SCnjDestruir ( &p_cnjVal );
	SLisDestruir ( &p_lisVal );
	SLisOrdDestruir ( &p_lisOrd );
	return ( iRes );
}

/* Eliminar destruye y Extraer mueve a un conjunto nuevo. */
static int TestSCnjExtraerLista01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjExtraerLista 01:\n" );

	int iA [ 6 ] = { 10, 20, 30, 40, 50, 60 };
	int iEli [ 3 ] = { 20, 99, 20 };
	int iEliCnj [ 1 ] = { 40 };
	int iExt [ 2 ] = { 50, 10 };
	int iExtOrd [ 1 ] = { 60 };
	SConjunto * p_cnjA = CrearConjuntoEnteros ( iA, 6 );
	SConjunto * p_cnjEli = CrearConjuntoEnteros ( iEliCnj, 1 );
	SLista * p_lisEli = CrearListaEnteros ( iEli, 3 );
	SLista * p_lisExt = CrearListaEnteros ( iExt, 2 );
	SListaOrdenada * p_lisExtOrd = CrearOrdenadaEnteros ( iExtOrd, 1 );
	SConjunto * p_cnjRes = NULL;
	if ( ES_VALIDO ( p_cnjA ) && ES_VALIDO ( p_cnjEli ) && ES_VALIDO ( p_lisEli ) && ES_VALIDO ( p_lisExt ) &&
		 ES_VALIDO ( p_lisExtOrd ) )
	{
		int iEsp1 [ 4 ] = { 10, 30, 50, 60 };
		if ( ( SCnjEliminarLista ( p_cnjA, p_lisEli ) != 1 ) ||
			 ( SCnjEliminarConjunto ( p_cnjA, p_cnjEli ) != 1 ) ||
			 ( VerificarConjunto ( p_cnjA, iEsp1, 4 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 1: deberia quedar { 10, 30, 50, 60 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SElemento * p_elm50 = SCnjElemento ( p_cnjA, 2 );
		p_cnjRes = SCnjExtraerLista ( p_cnjA, p_lisExt );
		int iEspRes [ 2 ] = { 10, 50 };
		int iEsp2 [ 2 ] = { 30, 60 };
		if ( ( SCnjElemento ( p_cnjRes, 1 ) != p_elm50 ) ||
			 ( VerificarYDestruir ( &p_cnjRes, iEspRes, 2 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarConjunto ( p_cnjA, iEsp2, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 2: se esperaba mover { 10, 50 } y dejar { 30, 60 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_cnjRes = SCnjExtraerListaOrd ( p_cnjA, p_lisExtOrd );
		int iEsp3 [ 1 ] = { 30 };
		if ( ( VerificarYDestruir ( &p_cnjRes, iExtOrd, 1 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarConjunto ( p_cnjA, iEsp3, 1 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 3: se esperaba mover { 60 } y dejar { 30 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SCnjExtraerConjunto ( p_cnjA, p_cnjA ) ) ||
			 ES_VALIDO ( SCnjExtraerLista ( p_cnjA, NULL ) ) ||
			 ES_VALIDO ( SCnjExtraerListaOrd ( NULL, p_lisExtOrd ) ) ||
			 ( SCnjEliminarConjunto ( p_cnjA, p_cnjA ) != 0 ) ||
			 ( SCnjEliminarLista ( NULL, p_lisEli ) != 0 ) ||
			 ( SCnjEliminarListaOrd ( p_cnjA, NULL ) != 0 ) ||
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
	SCnjDestruir ( &p_cnjA );
	SCnjDestruir ( &p_cnjEli );
	SLisDestruir ( &p_lisEli );
	SLisDestruir ( &p_lisExt );
	SLisOrdDestruir ( &p_lisExtOrd );
	return ( iRes );
}

/* Union, Interseccion y Diferencia de conjuntos: copias, sin repetidos, y los
   de entrada sin tocar. */
static int TestSCnjUnion01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjUnion 01:\n" );

	int iA [ 3 ] = { 10, 20, 30 };
	int iB [ 2 ] = { 20, 40 };
	int iL [ 3 ] = { 40, 20, 40 };
	SConjunto * p_cnjA = CrearConjuntoEnteros ( iA, 3 );
	SConjunto * p_cnjB = CrearConjuntoEnteros ( iB, 2 );
	SListaOrdenada * p_lisOrd = CrearOrdenadaEnteros ( iL, 3 );
	SLista * p_lisVal = CrearListaEnteros ( iL, 3 );
	SConjunto * p_cnjRes = NULL;
	if ( ES_VALIDO ( p_cnjA ) && ES_VALIDO ( p_cnjB ) && ES_VALIDO ( p_lisOrd ) && ES_VALIDO ( p_lisVal ) )
	{
		int iUni [ 4 ] = { 10, 20, 30, 40 };
		int iInt [ 1 ] = { 20 };
		int iDif [ 2 ] = { 10, 30 };
		p_cnjRes = SCnjUnion ( p_cnjA, p_cnjB );
		if ( ( SCnjElemento ( p_cnjRes, 0 ) == SCnjElemento ( p_cnjA, 0 ) ) ||
			 ( VerificarYDestruir ( &p_cnjRes, iUni, 4 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 1: la union deberia ser { 10, 20, 30, 40 }, con copias\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_cnjRes = SCnjInterseccion ( p_cnjA, p_cnjB );
		if ( VerificarYDestruir ( &p_cnjRes, iInt, 1 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 2: la interseccion deberia ser { 20 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_cnjRes = SCnjDiferencia ( p_cnjA, p_cnjB );
		if ( VerificarYDestruir ( &p_cnjRes, iDif, 2 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 3: la diferencia deberia ser { 10, 30 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Con listas que repiten el 40: sale una vez. */
		p_cnjRes = SCnjUnionLista ( p_cnjA, p_lisVal );
		if ( VerificarYDestruir ( &p_cnjRes, iUni, 4 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 4: la union con la lista deberia ser { 10, 20, 30, 40 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_cnjRes = SCnjUnionListaOrd ( p_cnjA, p_lisOrd );
		if ( VerificarYDestruir ( &p_cnjRes, iUni, 4 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 5: la union con la ordenada deberia ser { 10, 20, 30, 40 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_cnjRes = SCnjInterseccionLista ( p_cnjA, p_lisVal );
		if ( VerificarYDestruir ( &p_cnjRes, iInt, 1 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 6: la interseccion con la lista deberia ser { 20 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_cnjRes = SCnjInterseccionListaOrd ( p_cnjA, p_lisOrd );
		if ( VerificarYDestruir ( &p_cnjRes, iInt, 1 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 7: la interseccion con la ordenada deberia ser { 20 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_cnjRes = SCnjDiferenciaLista ( p_cnjA, p_lisVal );
		if ( VerificarYDestruir ( &p_cnjRes, iDif, 2 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 8: la diferencia con la lista deberia ser { 10, 30 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_cnjRes = SCnjDiferenciaListaOrd ( p_cnjA, p_lisOrd );
		if ( VerificarYDestruir ( &p_cnjRes, iDif, 2 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 9: la diferencia con la ordenada deberia ser { 10, 30 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( VerificarConjunto ( p_cnjA, iA, 3 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarConjunto ( p_cnjB, iB, 2 ) != BOOL_VAL_CIERTO ) ||
			 ( SLisNumElementos ( p_lisVal ) != 3 ) || ( SLisOrdNumElementos ( p_lisOrd ) != 3 ) )
		{
			printf( "Error caso 10: los de entrada no deberian cambiar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SCnjUnion ( NULL, p_cnjB ) ) || ES_VALIDO ( SCnjUnion ( p_cnjA, NULL ) ) ||
			 ES_VALIDO ( SCnjInterseccion ( NULL, p_cnjB ) ) || ES_VALIDO ( SCnjDiferencia ( p_cnjA, NULL ) ) ||
			 ES_VALIDO ( SCnjUnionLista ( p_cnjA, NULL ) ) || ES_VALIDO ( SCnjUnionListaOrd ( NULL, p_lisOrd ) ) ||
			 ES_VALIDO ( SCnjInterseccionLista ( NULL, p_lisVal ) ) || ES_VALIDO ( SCnjDiferenciaListaOrd ( NULL, p_lisOrd ) ) )
		{
			printf( "Error caso 11: con nulos se esperaba nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear los conjuntos o las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCnjDestruir ( &p_cnjA );
	SCnjDestruir ( &p_cnjB );
	SLisOrdDestruir ( &p_lisOrd );
	SLisDestruir ( &p_lisVal );
	return ( iRes );
}

int TestSConjunto ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SConjunto]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSCnjCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjInsertar01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjExiste01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjExisteExt01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjEliminar01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjPrimeroUltimo01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjPosicion01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjExtraerElem01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjInvalidos01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjCrearDesdeLista01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjExistenTodos01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjInsertarLista01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjExtraerLista01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjUnion01 () == BOOL_VAL_CIERTO ) )
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
