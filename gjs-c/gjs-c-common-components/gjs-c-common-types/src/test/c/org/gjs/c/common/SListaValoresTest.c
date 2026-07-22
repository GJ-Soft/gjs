#include "Base.h"

#include "SListaValores.h"



static int TestSLisValCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisValCrear 01:\n" );
	SListaValores * p_lisObj = SLisValCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( SLisValEsValida ( p_lisObj ) != 1 )
		{
			printf( "Error caso 1: se esperaba valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisValEstaVacia ( p_lisObj ) != 1 )
		{
			printf( "Error caso 2: se esperaba vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisValNumElementos ( p_lisObj ) != 0 )
		{
			printf( "Error caso 3: se esperaban 0 elementos: %d\n", SLisValNumElementos ( p_lisObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisValDestruir ( &p_lisObj );
	return ( iRes );
}

static int TestSLisValInsertar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisValInsertar 01:\n" );
	SListaValores * p_lisObj = SLisValCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		/* La lista toma la propiedad de los valores insertados. */
		SLisValInsertarAlFinal ( p_lisObj, SValCrearEntero ( 11 ) );
		SLisValInsertarAlFinal ( p_lisObj, SValCrearEntero ( 22 ) );
		if ( SLisValNumElementos ( p_lisObj ) != 2 )
		{
			printf( "Error caso 1: se esperaban 2 elementos: %d\n", SLisValNumElementos ( p_lisObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SValValorEntero ( SLisValElemento ( p_lisObj, 0 ) ) != 11 )
		{
			printf( "Error caso 2: se esperaba valor 11 en el elemento 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisValInicio ( p_lisObj );
		if ( SLisValActual ( p_lisObj ) != SLisValElemento ( p_lisObj, 0 ) )
		{
			printf( "Error caso 3: el actual no coincide con el elemento 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisValSiguiente ( p_lisObj );
		if ( SValValorEntero ( SLisValActual ( p_lisObj ) ) != 22 )
		{
			printf( "Error caso 4: se esperaba valor 22 en el actual tras avanzar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisValVaciar ( p_lisObj );
		if ( SLisValEstaVacia ( p_lisObj ) != 1 )
		{
			printf( "Error caso 5: se esperaba vacia tras vaciar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisValDestruir ( &p_lisObj );
	return ( iRes );
}

static int TestSLisValNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisValNulo 01:\n" );
	if ( SLisValEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: se esperaba no valida con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLisValNumElementos ( NULL ) != 0 )
	{
		printf( "Error caso 2: se esperaban 0 elementos con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SLisValElemento ( NULL, 0 ) ) )
	{
		printf( "Error caso 3: se esperaba elemento nulo con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

int TestSListaValores ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SListaValores]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSLisValCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisValInsertar01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisValNulo01 () == BOOL_VAL_CIERTO ) )
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
