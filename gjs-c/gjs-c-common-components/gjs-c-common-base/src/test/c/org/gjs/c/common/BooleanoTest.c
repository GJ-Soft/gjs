#include "Base.h"

#include "Booleano.h"



static int TestBoolCierto01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test BoolCierto 01:\n" );
	if ( BoolCierto () != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 1: se esperaba cierto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( BoolFalso () != BOOL_VAL_FALSO )
	{
		printf( "Error caso 2: se esperaba falso\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestBoolNormalizar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test BoolNormalizar 01:\n" );
	if ( BoolNormalizar ( 1 ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 1: se esperaba cierto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( BoolNormalizar ( 5 ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 2: se esperaba cierto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( BoolNormalizar ( 0 ) != BOOL_VAL_FALSO )
	{
		printf( "Error caso 3: se esperaba falso\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( BoolNormalizar ( -3 ) != BOOL_VAL_FALSO )
	{
		printf( "Error caso 4: se esperaba falso\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestBoolNo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test BoolNo 01:\n" );
	if ( BoolNo ( BOOL_VAL_FALSO ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 1: se esperaba cierto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( BoolNo ( BOOL_VAL_CIERTO ) != BOOL_VAL_FALSO )
	{
		printf( "Error caso 2: se esperaba falso\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestBoolY01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test BoolY 01:\n" );
	if ( BoolY ( BOOL_VAL_CIERTO, BOOL_VAL_CIERTO ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 1: se esperaba cierto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( BoolY ( BOOL_VAL_CIERTO, BOOL_VAL_FALSO ) != BOOL_VAL_FALSO )
	{
		printf( "Error caso 2: se esperaba falso\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( BoolY ( BOOL_VAL_FALSO, BOOL_VAL_FALSO ) != BOOL_VAL_FALSO )
	{
		printf( "Error caso 3: se esperaba falso\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestBoolO01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test BoolO 01:\n" );
	if ( BoolO ( BOOL_VAL_CIERTO, BOOL_VAL_FALSO ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 1: se esperaba cierto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( BoolO ( BOOL_VAL_FALSO, BOOL_VAL_CIERTO ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 2: se esperaba cierto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( BoolO ( BOOL_VAL_FALSO, BOOL_VAL_FALSO ) != BOOL_VAL_FALSO )
	{
		printf( "Error caso 3: se esperaba falso\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



int TestBooleano ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test Booleano]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestBoolCierto01 () == BOOL_VAL_CIERTO ) &&
			( TestBoolNormalizar01 () == BOOL_VAL_CIERTO ) &&
			( TestBoolNo01 () == BOOL_VAL_CIERTO ) &&
			( TestBoolY01 () == BOOL_VAL_CIERTO ) &&
			( TestBoolO01 () == BOOL_VAL_CIERTO ) )
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
