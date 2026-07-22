#include "Base.h"

#include "SListaEntradasExt.h"



static int TestSLisEtxCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisEtxCrear 01:\n" );
	SListaEntradasExt * p_lisObj = SLisEtxCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( SLisEtxEsValida ( p_lisObj ) != 1 )
		{
			printf( "Error caso 1: se esperaba valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisEtxEstaVacia ( p_lisObj ) != 1 )
		{
			printf( "Error caso 2: se esperaba vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisEtxNumElementos ( p_lisObj ) != 0 )
		{
			printf( "Error caso 3: se esperaban 0 elementos: %d\n", SLisEtxNumElementos ( p_lisObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisEtxDestruir ( &p_lisObj );
	return ( iRes );
}

static int TestSLisEtxInsertar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisEtxInsertar 01:\n" );
	SListaEntradasExt * p_lisObj = SLisEtxCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		/* La lista toma la propiedad de las entradas insertadas. */
		SLisEtxInsertar ( p_lisObj, SEtxCrearExt ( "manzana", "fruta roja" ) );
		SLisEtxInsertar ( p_lisObj, SEtxCrearExt ( "pera", "fruta verde" ) );
		if ( SLisEtxNumElementos ( p_lisObj ) != 2 )
		{
			printf( "Error caso 1: se esperaban 2 elementos: %d\n", SLisEtxNumElementos ( p_lisObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisEtxExiste ( p_lisObj, "manzana" ) != 1 )
		{
			printf( "Error caso 2: se esperaba que exista \"manzana\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_NULO ( SLisEtxBuscar ( p_lisObj, "pera" ) ) )
		{
			printf( "Error caso 3: se esperaba encontrar \"pera\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisEtxEliminar ( p_lisObj, "manzana" ) != 1 )
		{
			printf( "Error caso 4: se esperaba eliminar correcto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisEtxNumElementos ( p_lisObj ) != 1 )
		{
			printf( "Error caso 5: se esperaba 1 elemento: %d\n", SLisEtxNumElementos ( p_lisObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisEtxDestruir ( &p_lisObj );
	return ( iRes );
}

static int TestSLisEtxNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisEtxNulo 01:\n" );
	if ( SLisEtxEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: se esperaba no valida con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLisEtxNumElementos ( NULL ) != 0 )
	{
		printf( "Error caso 2: se esperaban 0 elementos con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLisEtxExiste ( NULL, "x" ) != 0 )
	{
		printf( "Error caso 3: no se esperaba existencia con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

int TestSListaEntradasExt ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SListaEntradasExt]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSLisEtxCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisEtxInsertar01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisEtxNulo01 () == BOOL_VAL_CIERTO ) )
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
