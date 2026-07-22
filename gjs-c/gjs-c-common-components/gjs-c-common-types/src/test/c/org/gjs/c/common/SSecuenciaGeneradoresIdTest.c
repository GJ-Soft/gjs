#include "Base.h"

#include "SSecuenciaGeneradoresId.h"



static int TestSSecGenIdCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecGenIdCrear 01:\n" );
	SSecuenciaGeneradoresId * p_secObj = SSecGenIdCrear ();
	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( SSecGenIdEsValida ( p_secObj ) != 1 )
		{
			printf( "Error caso 1: se esperaba valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SSecGenIdEstaVacia ( p_secObj ) != 1 )
		{
			printf( "Error caso 2: se esperaba vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SSecGenIdNumElementos ( p_secObj ) != 0 )
		{
			printf( "Error caso 3: se esperaban 0 elementos: %d\n", SSecGenIdNumElementos ( p_secObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecGenIdDestruir ( &p_secObj );
	return ( iRes );
}

static int TestSSecGenIdInsertar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecGenIdInsertar 01:\n" );
	SSecuenciaGeneradoresId * p_secObj = SSecGenIdCrear ();
	if ( ES_VALIDO ( p_secObj ) )
	{
		/* La secuencia toma la propiedad de los generadores insertados. */
		SSecGenIdInsertar ( p_secObj, SGenIdCrear ( 1, 1, 100 ) );
		SSecGenIdInsertar ( p_secObj, SGenIdCrear ( 200, 200, 300 ) );
		if ( SSecGenIdNumElementos ( p_secObj ) != 2 )
		{
			printf( "Error caso 1: se esperaban 2 elementos: %d\n", SSecGenIdNumElementos ( p_secObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_NULO ( SSecGenIdElemento ( p_secObj, 0 ) ) )
		{
			printf( "Error caso 2: se esperaba elemento 0 no nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SSecGenIdEliminar ( p_secObj, 0 ) != 1 )
		{
			printf( "Error caso 3: se esperaba eliminar correcto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SSecGenIdNumElementos ( p_secObj ) != 1 )
		{
			printf( "Error caso 4: se esperaba 1 elemento: %d\n", SSecGenIdNumElementos ( p_secObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		SSecGenIdVaciar ( p_secObj );
		if ( SSecGenIdEstaVacia ( p_secObj ) != 1 )
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
	SSecGenIdDestruir ( &p_secObj );
	return ( iRes );
}

static int TestSSecGenIdNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecGenIdNulo 01:\n" );
	if ( SSecGenIdEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: se esperaba no valida con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SSecGenIdNumElementos ( NULL ) != 0 )
	{
		printf( "Error caso 2: se esperaban 0 elementos con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SSecGenIdElemento ( NULL, 0 ) ) )
	{
		printf( "Error caso 3: se esperaba elemento nulo con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

int TestSSecuenciaGeneradoresId ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SSecuenciaGeneradoresId]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSSecGenIdCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecGenIdInsertar01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecGenIdNulo01 () == BOOL_VAL_CIERTO ) )
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
