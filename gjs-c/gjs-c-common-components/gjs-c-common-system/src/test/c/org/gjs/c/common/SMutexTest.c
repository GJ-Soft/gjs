#include "Base.h"

#include "SMutex.h"



static int TestSMtxCicloVida01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SMtxCicloVida 01:\n" );
	SMutex * p_mtxObj = SMtxCrear ( "gjs_test_mtx" );
	if ( ES_NULO ( p_mtxObj ) )
	{
		printf( "Error caso 0: no se pudo crear el mutex\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SMtxEsValido ( p_mtxObj ) != 1 )
		{
			printf( "Error caso 1: se esperaba un mutex valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_NULO ( SMtxNombre ( p_mtxObj ) ) )
		{
			printf( "Error caso 2: se esperaba nombre de mutex no nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SMtxHayAcceso ( p_mtxObj ) != 0 )
		{
			printf( "Error caso 3: un mutex recien creado no debe tener acceso tomado\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SMtxAcceder ( p_mtxObj ) != 1 )
		{
			printf( "Error caso 4: se esperaba tomar el acceso del mutex\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SMtxHayAcceso ( p_mtxObj ) != 1 )
		{
			printf( "Error caso 5: tras acceder debe constar acceso tomado\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SMtxDejarLibre ( p_mtxObj ) != 1 )
		{
			printf( "Error caso 6: se esperaba dejar libre el mutex\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SMtxHayAcceso ( p_mtxObj ) != 0 )
		{
			printf( "Error caso 7: tras dejar libre no debe constar acceso tomado\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SMtxDestruir ( &p_mtxObj );
	return ( iRes );
}

static int TestSMtxNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SMtxNulo 01:\n" );
	if ( SMtxEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: un mutex nulo no debe ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SMtxNombre ( NULL ) ) )
	{
		printf( "Error caso 2: se esperaba nombre nulo para mutex nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SMtxAcceder ( NULL ) != 0 )
	{
		printf( "Error caso 3: se esperaba 0 al acceder a un mutex nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



int TestSMutex ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SMutex]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSMtxCicloVida01 () == BOOL_VAL_CIERTO ) &&
			( TestSMtxNulo01 () == BOOL_VAL_CIERTO ) )
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
