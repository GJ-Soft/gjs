#include "Base.h"

#include "SListaEntradas.h"



static int TestSLisEtrCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisEtrCrear 01:\n" );
	SListaEntradas * p_lisObj = SLisEtrCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( SLisEtrEsValida ( p_lisObj ) != 1 )
		{
			printf( "Error caso 1: se esperaba valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisEtrEstaVacia ( p_lisObj ) != 1 )
		{
			printf( "Error caso 2: se esperaba vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisEtrNumElementos ( p_lisObj ) != 0 )
		{
			printf( "Error caso 3: se esperaban 0 elementos: %d\n", SLisEtrNumElementos ( p_lisObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisEtrDestruir ( &p_lisObj );
	return ( iRes );
}

static int TestSLisEtrInsertar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisEtrInsertar 01:\n" );
	SListaEntradas * p_lisObj = SLisEtrCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		SLisEtrInsertarExt ( p_lisObj, "manzana", "fruta roja" );
		SLisEtrInsertarExt ( p_lisObj, "pera", "fruta verde" );
		if ( SLisEtrNumElementos ( p_lisObj ) != 2 )
		{
			printf( "Error caso 1: se esperaban 2 elementos: %d\n", SLisEtrNumElementos ( p_lisObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisEtrExiste ( p_lisObj, "manzana" ) != 1 )
		{
			printf( "Error caso 2: se esperaba que exista \"manzana\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisEtrExiste ( p_lisObj, "platano" ) != 0 )
		{
			printf( "Error caso 3: no se esperaba que exista \"platano\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_NULO ( SLisEtrBuscar ( p_lisObj, "manzana" ) ) )
		{
			printf( "Error caso 4: se esperaba encontrar \"manzana\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisEtrEliminar ( p_lisObj, "manzana" ) != 1 )
		{
			printf( "Error caso 5: se esperaba eliminar correcto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisEtrNumElementos ( p_lisObj ) != 1 )
		{
			printf( "Error caso 6: se esperaba 1 elemento: %d\n", SLisEtrNumElementos ( p_lisObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisEtrDestruir ( &p_lisObj );
	return ( iRes );
}

static int TestSLisEtrNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisEtrNulo 01:\n" );
	if ( SLisEtrEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: se esperaba no valida con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLisEtrNumElementos ( NULL ) != 0 )
	{
		printf( "Error caso 2: se esperaban 0 elementos con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLisEtrExiste ( NULL, "x" ) != 0 )
	{
		printf( "Error caso 3: no se esperaba existencia con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

int TestSListaEntradas ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SListaEntradas]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSLisEtrCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisEtrInsertar01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisEtrNulo01 () == BOOL_VAL_CIERTO ) )
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
