#include "Base.h"

#include "SGeneradorIdAdap.h"



static int TestSGenIdAdpCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SGenIdAdpCrear 01:\n" );
	SGeneradorIdAdap * p_genObj = SGenIdAdpCrear ( 3, "999" );
	if ( ES_VALIDO ( p_genObj ) )
	{
		if ( ES_NULO ( SGenIdAdpPatron ( p_genObj ) ) || ( CadComparar ( SGenIdAdpPatron ( p_genObj ), "999" ) != COMP_IGUAL ) )
		{
			printf( "Error caso 1: se esperaba patron \"999\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_NULO ( SGenIdAdpInicial ( p_genObj ) ) || ( CadComparar ( SGenIdAdpInicial ( p_genObj ), "000" ) != COMP_IGUAL ) )
		{
			printf( "Error caso 2: se esperaba inicial \"000\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_NULO ( SGenIdAdpFinal ( p_genObj ) ) || ( CadComparar ( SGenIdAdpFinal ( p_genObj ), "999" ) != COMP_IGUAL ) )
		{
			printf( "Error caso 3: se esperaba final \"999\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SGenIdAdpEsValido ( p_genObj ) != 1 )
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
	SGenIdAdpDestruir ( &p_genObj );
	return ( iRes );
}

static int TestSGenIdAdpAsignarSig01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SGenIdAdpAsignarSig 01:\n" );
	SGeneradorIdAdap * p_genObj = SGenIdAdpCrear ( 3, "999" );
	if ( ES_VALIDO ( p_genObj ) )
	{
		const char * p_cPrimero = SGenIdAdpAsignarSig ( p_genObj );
		if ( ES_NULO ( p_cPrimero ) || ( CadComparar ( p_cPrimero, "000" ) != COMP_IGUAL ) )
		{
			printf( "Error caso 1: se esperaba primer id \"000\": [%s]\n", ES_VALIDO ( p_cPrimero ) ? p_cPrimero : "(nulo)" );
			iRes = BOOL_VAL_FALSO;
		}
		const char * p_cSegundo = SGenIdAdpAsignarSig ( p_genObj );
		if ( ES_NULO ( p_cSegundo ) || ( CadComparar ( p_cSegundo, "001" ) != COMP_IGUAL ) )
		{
			printf( "Error caso 2: se esperaba segundo id \"001\": [%s]\n", ES_VALIDO ( p_cSegundo ) ? p_cSegundo : "(nulo)" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_NULO ( SGenIdAdpUltimo ( p_genObj ) ) || ( CadComparar ( SGenIdAdpUltimo ( p_genObj ), "001" ) != COMP_IGUAL ) )
		{
			printf( "Error caso 3: se esperaba ultimo \"001\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SGenIdAdpDestruir ( &p_genObj );
	return ( iRes );
}

static int TestSGenIdAdpNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SGenIdAdpNulo 01:\n" );
	if ( SGenIdAdpEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: se esperaba no valido con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SGenIdAdpAsignarSig ( NULL ) ) )
	{
		printf( "Error caso 2: se esperaba nulo al asignar con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SGenIdAdpPatron ( NULL ) ) )
	{
		printf( "Error caso 3: se esperaba patron nulo con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

int TestSGeneradorIdAdap ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SGeneradorIdAdap]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSGenIdAdpCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSGenIdAdpAsignarSig01 () == BOOL_VAL_CIERTO ) &&
			( TestSGenIdAdpNulo01 () == BOOL_VAL_CIERTO ) )
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
