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



int TestSListaOrdenada ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SListaOrdenada]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSLisOrdCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisOrdInsertarOrdenado01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisOrdBuscar01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisOrdBuscarExt01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisOrdEliminar01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisOrdInvalidos01 () == BOOL_VAL_CIERTO ) )
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
