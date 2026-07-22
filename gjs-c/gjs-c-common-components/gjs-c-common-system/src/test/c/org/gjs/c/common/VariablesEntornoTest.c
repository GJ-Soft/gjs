#include "Base.h"

#include "VariablesEntorno.h"



static int TestVarEntEstablecerObtener01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test VarEntEstablecerObtener 01:\n" );
	/* El valor se filtra internamente (solo alfanumericos), por eso se usa un
	   valor sin espacios ni signos. */
	if ( VarEntEstValor ( "GJS_TEST_VAR", "valor123" ) != 1 )
	{
		printf( "Error caso 1: no se pudo establecer la variable\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( VarEntExiste ( "GJS_TEST_VAR" ) != 1 )
	{
		printf( "Error caso 2: se esperaba que la variable exista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	char * p_cValor = VarEntObtValor ( "GJS_TEST_VAR" );
	if ( ES_NULO ( p_cValor ) || ( strcmp ( p_cValor, "valor123" ) != 0 ) )
	{
		printf( "Error caso 3: se esperaba \"valor123\": [%s]\n", ES_VALIDO ( p_cValor ) ? p_cValor : "(nulo)" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_cValor );
	return ( iRes );
}

static int TestVarEntInexistente01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test VarEntInexistente 01:\n" );
	if ( VarEntExiste ( "GJS_TEST_VAR_INEXISTENTE_XYZ" ) != 0 )
	{
		printf( "Error caso 1: no se esperaba que exista una variable inexistente\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( VarEntObtValor ( "GJS_TEST_VAR_INEXISTENTE_XYZ" ) ) )
	{
		printf( "Error caso 2: se esperaba valor nulo para variable inexistente\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestVarEntNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test VarEntNulo 01:\n" );
	if ( ES_VALIDO ( VarEntObtValor ( NULL ) ) )
	{
		printf( "Error caso 1: se esperaba nulo al obtener con variable nula\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( VarEntEstValor ( NULL, "x" ) != 0 )
	{
		printf( "Error caso 2: se esperaba 0 al establecer con variable nula\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( VarEntExiste ( NULL ) != 0 )
	{
		printf( "Error caso 3: se esperaba 0 al comprobar variable nula\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



int TestVariablesEntorno ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test VariablesEntorno]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestVarEntEstablecerObtener01 () == BOOL_VAL_CIERTO ) &&
			( TestVarEntInexistente01 () == BOOL_VAL_CIERTO ) &&
			( TestVarEntNulo01 () == BOOL_VAL_CIERTO ) )
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
