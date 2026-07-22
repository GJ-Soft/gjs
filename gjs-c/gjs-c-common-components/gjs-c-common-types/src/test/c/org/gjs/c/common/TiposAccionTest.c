#include "Base.h"

#include "TiposAccion.h"



static int TestTipAccEsValido01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test TipAccEsValido 01:\n" );
	if ( TipAccEsValido ( TIP_ACC_CODIGO ) != 1 )
	{
		printf( "Error caso 1: se esperaba valido para codigo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipAccEsValido ( TIP_ACC_VOLVER ) != 1 )
	{
		printf( "Error caso 2: se esperaba valido para volver\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipAccEsValido ( TIP_ACC_NULO ) != 0 )
	{
		printf( "Error caso 3: se esperaba no valido para nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipAccEsValido ( 99 ) != 0 )
	{
		printf( "Error caso 4: se esperaba no valido para 99\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestTipAccTipos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test TipAccTipos 01:\n" );
	if ( TipAccEsCodigo ( TIP_ACC_CODIGO ) != 1 )
	{
		printf( "Error caso 1: se esperaba es codigo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipAccEsFuncion ( TIP_ACC_FUNCION ) != 1 )
	{
		printf( "Error caso 2: se esperaba es funcion\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipAccEsMenu ( TIP_ACC_MENU ) != 1 )
	{
		printf( "Error caso 3: se esperaba es menu\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipAccEsSalir ( TIP_ACC_SALIR ) != 1 )
	{
		printf( "Error caso 4: se esperaba es salir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipAccEsVolver ( TIP_ACC_VOLVER ) != 1 )
	{
		printf( "Error caso 5: se esperaba es volver\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipAccEsCodigo ( TIP_ACC_FUNCION ) != 0 )
	{
		printf( "Error caso 6: no se esperaba es codigo para funcion\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestCodAcc01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test CodAcc 01:\n" );
	if ( CodAccEsValido ( 0 ) != 1 )
	{
		printf( "Error caso 1: se esperaba valido para 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CodAccEsValido ( 100 ) != 1 )
	{
		printf( "Error caso 2: se esperaba valido para 100\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CodAccEsValido ( 101 ) != 0 )
	{
		printf( "Error caso 3: se esperaba no valido para 101\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CodAccEsValido ( -1 ) != 0 )
	{
		printf( "Error caso 4: se esperaba no valido para -1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CodAccEsSalir ( COD_ACC_SALIR ) != 1 )
	{
		printf( "Error caso 5: se esperaba es salir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CodAccEsVolver ( COD_ACC_VOLVER ) != 1 )
	{
		printf( "Error caso 6: se esperaba es volver\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

int TestTiposAccion ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test TiposAccion]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestTipAccEsValido01 () == BOOL_VAL_CIERTO ) &&
			( TestTipAccTipos01 () == BOOL_VAL_CIERTO ) &&
			( TestCodAcc01 () == BOOL_VAL_CIERTO ) )
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
