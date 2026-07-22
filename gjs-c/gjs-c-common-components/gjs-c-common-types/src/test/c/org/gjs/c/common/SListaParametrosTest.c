#include "Base.h"

#include "SListaParametros.h"



static int TestSLisParCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisParCrear 01:\n" );
	SListaParametros * p_lisObj = SLisParCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( SLisParEsValida ( p_lisObj ) != 1 )
		{
			printf( "Error caso 1: se esperaba valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisParEstaVacia ( p_lisObj ) != 1 )
		{
			printf( "Error caso 2: se esperaba vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisParNumElementos ( p_lisObj ) != 0 )
		{
			printf( "Error caso 3: se esperaban 0 elementos: %d\n", SLisParNumElementos ( p_lisObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisParDestruir ( &p_lisObj );
	return ( iRes );
}

static int TestSLisParInsertar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisParInsertar 01:\n" );
	SListaParametros * p_lisObj = SLisParCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		/* La lista toma la propiedad de los parametros insertados. */
		SLisParInsertarAlFinal ( p_lisObj, SParCrearExtLit ( TIP_NUMERO_ENTERO, "uno" ) );
		SLisParInsertarAlFinal ( p_lisObj, SParCrearExtLit ( TIP_NUMERO_ENTERO, "dos" ) );
		if ( SLisParNumElementos ( p_lisObj ) != 2 )
		{
			printf( "Error caso 1: se esperaban 2 elementos: %d\n", SLisParNumElementos ( p_lisObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_NULO ( SLisParElemento ( p_lisObj, 0 ) ) )
		{
			printf( "Error caso 2: se esperaba elemento 0 no nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisParInicio ( p_lisObj );
		if ( SLisParActual ( p_lisObj ) != SLisParElemento ( p_lisObj, 0 ) )
		{
			printf( "Error caso 3: el actual no coincide con el elemento 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisParSiguiente ( p_lisObj );
		if ( SLisParActual ( p_lisObj ) != SLisParElemento ( p_lisObj, 1 ) )
		{
			printf( "Error caso 4: el actual no coincide con el elemento 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisParVaciar ( p_lisObj );
		if ( SLisParEstaVacia ( p_lisObj ) != 1 )
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
	SLisParDestruir ( &p_lisObj );
	return ( iRes );
}

static int TestSLisParNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisParNulo 01:\n" );
	if ( SLisParEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: se esperaba no valida con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLisParNumElementos ( NULL ) != 0 )
	{
		printf( "Error caso 2: se esperaban 0 elementos con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SLisParElemento ( NULL, 0 ) ) )
	{
		printf( "Error caso 3: se esperaba elemento nulo con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

int TestSListaParametros ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SListaParametros]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSLisParCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisParInsertar01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisParNulo01 () == BOOL_VAL_CIERTO ) )
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
