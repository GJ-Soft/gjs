#include "Base.h"

#include "SListaErrores.h"



static int TestSLisErrCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisErrCrear 01:\n" );
	SListaErrores * p_lisObj = SLisErrCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( SLisErrEsValida ( p_lisObj ) != 1 )
		{
			printf( "Error caso 1: se esperaba valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisErrEstaVacia ( p_lisObj ) != 1 )
		{
			printf( "Error caso 2: se esperaba vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisErrContieneErrores ( p_lisObj ) != 0 )
		{
			printf( "Error caso 3: no se esperaban errores\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisErrDestruir ( &p_lisObj );
	return ( iRes );
}

static int TestSLisErrInsertar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisErrInsertar 01:\n" );
	SListaErrores * p_lisObj = SLisErrCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		SLisErrInsertarExt ( p_lisObj, "COD001", "descripcion del error" );
		if ( SLisErrNumElementos ( p_lisObj ) != 1 )
		{
			printf( "Error caso 1: se esperaba 1 elemento: %d\n", SLisErrNumElementos ( p_lisObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisErrExiste ( p_lisObj, "COD001" ) != 1 )
		{
			printf( "Error caso 2: se esperaba que exista \"COD001\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_NULO ( SLisErrCodigoElemento ( p_lisObj, 0 ) ) || ( CadComparar ( SLisErrCodigoElemento ( p_lisObj, 0 ), "COD001" ) != COMP_IGUAL ) )
		{
			printf( "Error caso 3: se esperaba codigo \"COD001\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisErrContieneErrores ( p_lisObj ) != 1 )
		{
			printf( "Error caso 4: se esperaba que contenga errores\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisErrEliminar ( p_lisObj, "COD001" ) != 1 )
		{
			printf( "Error caso 5: se esperaba eliminar correcto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisErrNumElementos ( p_lisObj ) != 0 )
		{
			printf( "Error caso 6: se esperaban 0 elementos tras eliminar: %d\n", SLisErrNumElementos ( p_lisObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisErrDestruir ( &p_lisObj );
	return ( iRes );
}

static int TestSLisErrNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisErrNulo 01:\n" );
	if ( SLisErrEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: se esperaba no valida con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLisErrNumElementos ( NULL ) != 0 )
	{
		printf( "Error caso 2: se esperaban 0 elementos con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLisErrContieneErrores ( NULL ) != 0 )
	{
		printf( "Error caso 3: no se esperaban errores con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

int TestSListaErrores ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SListaErrores]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSLisErrCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisErrInsertar01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisErrNulo01 () == BOOL_VAL_CIERTO ) )
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
