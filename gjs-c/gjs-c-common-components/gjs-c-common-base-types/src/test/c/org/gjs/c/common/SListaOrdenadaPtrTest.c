#include "Base.h"

#include "SListaOrdenadaPtr.h"



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

static int ValorElem ( SListaOrdenadaPtr * p_lisObj, int iElem )
{
	return ( *( (int *) SLispOrdElemento ( p_lisObj, iElem ) ) );
}

static int ValorActual ( SListaOrdenadaPtr * p_lisObj )
{
	return ( *( (int *) SLispOrdActual ( p_lisObj ) ) );
}



static int TestSLispOrdInsertar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLispOrdInsertar 01:\n" );

	/* La memoria de los datos la gestiona el test ( liberacion desactivada ). */
	byte * p_d10 = CrearDatoEntero ( 10 );
	byte * p_d20 = CrearDatoEntero ( 20 );
	byte * p_d30 = CrearDatoEntero ( 30 );
	byte * p_q99 = CrearDatoEntero ( 99 );
	byte * p_q5 = CrearDatoEntero ( 5 );
	SListaOrdenadaPtr * p_lisObj = SLispOrdCrear ( CompararEnteros );
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_d10 ) && ES_VALIDO ( p_d20 ) &&
		 ES_VALIDO ( p_d30 ) && ES_VALIDO ( p_q99 ) && ES_VALIDO ( p_q5 ) )
	{
		SLispOrdDesactivarLiberacionMemoria ( p_lisObj );

		if ( ( SLispOrdEsValida ( p_lisObj ) != 1 ) || ( SLispOrdEstaVacia ( p_lisObj ) != 1 ) )
		{
			printf( "Error caso 1: la lista recien creada deberia ser valida y estar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Buscar en una lista vacia debe devolver -1 ( valida el arreglo de Buscar ). */
		if ( SLispOrdBuscar ( p_lisObj, p_d10 ) != -1 )
		{
			printf( "Error caso 2: buscar en una lista vacia deberia devolver -1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Se insertan en desorden; la lista los mantiene ordenados. */
		SLispOrdInsertarElem ( p_lisObj, p_d20 );
		SLispOrdInsertarElem ( p_lisObj, p_d10 );
		SLispOrdInsertarElem ( p_lisObj, p_d30 );
		if ( SLispOrdNumElementos ( p_lisObj ) != 3 )
		{
			printf( "Error caso 3: la lista deberia tener 3 elementos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( ValorElem ( p_lisObj, 0 ) != 10 ) || ( ValorElem ( p_lisObj, 1 ) != 20 ) || ( ValorElem ( p_lisObj, 2 ) != 30 ) )
		{
			printf( "Error caso 4: los elementos deberian quedar ordenados ( 10, 20, 30 )\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Buscar: encontrado devuelve indice; no encontrado ( mayor o menor que todos ) devuelve -1. */
		if ( SLispOrdBuscar ( p_lisObj, p_d20 ) != 1 )
		{
			printf( "Error caso 5: buscar 20 deberia devolver el indice 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLispOrdBuscar ( p_lisObj, p_q99 ) != -1 ) || ( SLispOrdBuscar ( p_lisObj, p_q5 ) != -1 ) )
		{
			printf( "Error caso 6: buscar valores fuera del rango deberia devolver -1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Eliminar el del medio ( 20 ). */
		SLispOrdEliminarElem ( p_lisObj, 1 );
		if ( ( SLispOrdNumElementos ( p_lisObj ) != 2 ) || ( ValorElem ( p_lisObj, 1 ) != 30 ) )
		{
			printf( "Error caso 7: tras eliminar el 20 deberian quedar 10 y 30\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear la lista o los datos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLispOrdDestruir ( &p_lisObj );
	/* El test libera sus propios datos. */
	MemLiberar ( (void **) &p_d10 );
	MemLiberar ( (void **) &p_d20 );
	MemLiberar ( (void **) &p_d30 );
	MemLiberar ( (void **) &p_q99 );
	MemLiberar ( (void **) &p_q5 );
	return ( iRes );
}

static int TestSLispOrdCursor01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLispOrdCursor 01:\n" );

	byte * p_d10 = CrearDatoEntero ( 10 );
	byte * p_d20 = CrearDatoEntero ( 20 );
	byte * p_d30 = CrearDatoEntero ( 30 );
	SListaOrdenadaPtr * p_lisObj = SLispOrdCrear ( CompararEnteros );
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_d10 ) && ES_VALIDO ( p_d20 ) && ES_VALIDO ( p_d30 ) )
	{
		SLispOrdDesactivarLiberacionMemoria ( p_lisObj );
		SLispOrdInsertarElem ( p_lisObj, p_d30 );
		SLispOrdInsertarElem ( p_lisObj, p_d10 );
		SLispOrdInsertarElem ( p_lisObj, p_d20 );

		/* Recorrido con cursor: inicio -> siguiente -> final. */
		SLispOrdInicio ( p_lisObj );
		if ( ( ValorActual ( p_lisObj ) != 10 ) || ( SLispOrdEstaEnInicio ( p_lisObj ) != 1 ) )
		{
			printf( "Error caso 1: el inicio deberia ser 10\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLispOrdSiguiente ( p_lisObj );
		if ( ValorActual ( p_lisObj ) != 20 )
		{
			printf( "Error caso 2: el siguiente del inicio deberia ser 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLispOrdFinal ( p_lisObj );
		if ( ( ValorActual ( p_lisObj ) != 30 ) || ( SLispOrdEstaEnFinal ( p_lisObj ) != 1 ) )
		{
			printf( "Error caso 3: el final deberia ser 30\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear la lista o los datos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLispOrdDestruir ( &p_lisObj );
	MemLiberar ( (void **) &p_d10 );
	MemLiberar ( (void **) &p_d20 );
	MemLiberar ( (void **) &p_d30 );
	return ( iRes );
}

static int TestSLispOrdInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLispOrdInvalidos 01:\n" );

	if ( SLispOrdEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: una lista nula no deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLispOrdNumElementos ( NULL ) != 0 )
	{
		printf( "Error caso 2: una lista nula deberia tener 0 elementos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SListaOrdenadaPtr * p_lisNula = NULL;
	SLispOrdDestruir ( &p_lisNula );
	return ( iRes );
}



int TestSListaOrdenadaPtr ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SListaOrdenadaPtr]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSLispOrdInsertar01 () == BOOL_VAL_CIERTO ) &&
			( TestSLispOrdCursor01 () == BOOL_VAL_CIERTO ) &&
			( TestSLispOrdInvalidos01 () == BOOL_VAL_CIERTO ) )
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
