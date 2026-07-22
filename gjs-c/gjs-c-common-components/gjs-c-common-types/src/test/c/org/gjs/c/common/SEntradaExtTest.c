#include "Base.h"

#include "SEntradaExt.h"



static int TestSEtxCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEtxCrear 01:\n" );
	SEntradaExt * p_extObj = SEtxCrearExt ( "entrada", "definicion uno" );
	if ( ES_VALIDO ( p_extObj ) )
	{
		if ( ES_NULO ( SEtxNombre ( p_extObj ) ) || ( CadComparar ( SEtxNombre ( p_extObj ), "entrada" ) != COMP_IGUAL ) )
		{
			printf( "Error caso 1: se esperaba nombre \"entrada\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEtxNumDefiniciones ( p_extObj ) != 1 )
		{
			printf( "Error caso 2: se esperaba 1 definicion: %d\n", SEtxNumDefiniciones ( p_extObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_NULO ( SEtxDefinicionPrinc ( p_extObj ) ) || ( CadComparar ( SEtxDefinicionPrinc ( p_extObj ), "definicion uno" ) != COMP_IGUAL ) )
		{
			printf( "Error caso 3: se esperaba definicion principal \"definicion uno\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEtxEsValido ( p_extObj ) != 1 )
		{
			printf( "Error caso 4: se esperaba valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEtxDestruir ( &p_extObj );
	return ( iRes );
}

static int TestSEtxDefiniciones01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEtxDefiniciones 01:\n" );
	SEntradaExt * p_extObj = SEtxCrearExt ( "entrada", "definicion uno" );
	if ( ES_VALIDO ( p_extObj ) )
	{
		if ( SEtxInsertarDefinicion ( p_extObj, "definicion dos" ) != 1 )
		{
			printf( "Error caso 1: se esperaba insertar definicion correcto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEtxNumDefiniciones ( p_extObj ) != 2 )
		{
			printf( "Error caso 2: se esperaban 2 definiciones: %d\n", SEtxNumDefiniciones ( p_extObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_NULO ( SEtxDefinicion ( p_extObj, 1 ) ) || ( CadComparar ( SEtxDefinicion ( p_extObj, 1 ), "definicion dos" ) != COMP_IGUAL ) )
		{
			printf( "Error caso 3: se esperaba definicion 1 \"definicion dos\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEtxDestruir ( &p_extObj );
	return ( iRes );
}

static int TestSEtxNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEtxNulo 01:\n" );
	if ( SEtxEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: se esperaba no valido con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SEtxNumDefiniciones ( NULL ) != 0 )
	{
		printf( "Error caso 2: se esperaban 0 definiciones con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SEtxNombre ( NULL ) ) )
	{
		printf( "Error caso 3: se esperaba nombre nulo con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

int TestSEntradaExt ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SEntradaExt]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSEtxCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSEtxDefiniciones01 () == BOOL_VAL_CIERTO ) &&
			( TestSEtxNulo01 () == BOOL_VAL_CIERTO ) )
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
