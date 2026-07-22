#include "Base.h"

#include "SMemoriaCompartida.h"



static int TestSMemCmpCicloVida01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SMemCmpCicloVida 01:\n" );
	SMemoriaCompartida * p_memcObj = SMemCmpCrear ( "gjs_test_shm", 128 );
	if ( ES_NULO ( p_memcObj ) )
	{
		printf( "Error caso 0: no se pudo crear la memoria compartida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SMemCmpEsValida ( p_memcObj ) != 1 )
		{
			printf( "Error caso 1: se esperaba una memoria compartida valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SMemCmpTam ( p_memcObj ) != 128 )
		{
			printf( "Error caso 2: se esperaba tam 128: %d\n", SMemCmpTam ( p_memcObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_NULO ( SMemCmpNombre ( p_memcObj ) ) )
		{
			printf( "Error caso 3: se esperaba nombre no nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SMemCmpDestruir ( &p_memcObj );
	return ( iRes );
}

static int TestSMemCmpNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SMemCmpNulo 01:\n" );
	if ( SMemCmpEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: una memoria compartida nula no debe ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SMemCmpTam ( NULL ) != 0 )
	{
		printf( "Error caso 2: se esperaba tam 0 para memoria compartida nula\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SMemCmpDatos ( NULL ) ) )
	{
		printf( "Error caso 3: se esperaban datos nulos para memoria compartida nula\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SMemCmpNombre ( NULL ) ) )
	{
		printf( "Error caso 4: se esperaba nombre nulo para memoria compartida nula\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



int TestSMemoriaCompartida ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SMemoriaCompartida]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSMemCmpCicloVida01 () == BOOL_VAL_CIERTO ) &&
			( TestSMemCmpNulo01 () == BOOL_VAL_CIERTO ) )
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
