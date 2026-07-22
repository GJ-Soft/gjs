#include "Base.h"

#include "SIdAdap.h"



static int TestSIdAdpCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SIdAdpCrear 01:\n" );
	SIdAdap * p_idObj = SIdAdpCrearExt ( 3, "999" );
	if ( ES_VALIDO ( p_idObj ) )
	{
		if ( SIdAdpTam ( p_idObj ) != 3 )
		{
			printf( "Error caso 1: se esperaba tam 3: %d\n", SIdAdpTam ( p_idObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_NULO ( SIdAdpPatron ( p_idObj ) ) || ( CadComparar ( SIdAdpPatron ( p_idObj ), "999" ) != COMP_IGUAL ) )
		{
			printf( "Error caso 2: se esperaba patron \"999\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_NULO ( SIdAdpValor ( p_idObj ) ) || ( CadComparar ( SIdAdpValor ( p_idObj ), "000" ) != COMP_IGUAL ) )
		{
			printf( "Error caso 3: se esperaba valor inicial \"000\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SIdAdpEsValido ( p_idObj ) != 1 )
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
	SIdAdpDestruir ( &p_idObj );

	/* Sin patron no se puede crear. */
	SIdAdap * p_idNulo = SIdAdpCrear ( 3 );
	if ( ES_VALIDO ( p_idNulo ) )
	{
		printf( "Error caso 5: no se esperaba crear sin patron\n" );
		iRes = BOOL_VAL_FALSO;
		SIdAdpDestruir ( &p_idNulo );
	}
	return ( iRes );
}

static int TestSIdAdpIncrementar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SIdAdpIncrementar 01:\n" );
	SIdAdap * p_idObj = SIdAdpCrearExt ( 3, "999" );
	if ( ES_VALIDO ( p_idObj ) )
	{
		if ( SIdAdpIncrementar ( p_idObj ) != 1 )
		{
			printf( "Error caso 1: se esperaba incrementar correcto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( CadComparar ( SIdAdpValor ( p_idObj ), "001" ) != COMP_IGUAL )
		{
			printf( "Error caso 2: se esperaba valor \"001\": %s\n", SIdAdpValor ( p_idObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SIdAdpDecrementar ( p_idObj ) != 1 )
		{
			printf( "Error caso 3: se esperaba decrementar correcto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( CadComparar ( SIdAdpValor ( p_idObj ), "000" ) != COMP_IGUAL )
		{
			printf( "Error caso 4: se esperaba valor \"000\": %s\n", SIdAdpValor ( p_idObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SIdAdpDestruir ( &p_idObj );
	return ( iRes );
}

static int TestSIdAdpEstablecer01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SIdAdpEstablecer 01:\n" );
	SIdAdap * p_idObj = SIdAdpCrearExt ( 3, "999" );
	if ( ES_VALIDO ( p_idObj ) )
	{
		if ( SIdAdpEstablecer ( p_idObj, "123" ) != 1 )
		{
			printf( "Error caso 1: se esperaba establecer correcto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( CadComparar ( SIdAdpValor ( p_idObj ), "123" ) != COMP_IGUAL )
		{
			printf( "Error caso 2: se esperaba valor \"123\": %s\n", SIdAdpValor ( p_idObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* Un valor que no cumple el patron debe rechazarse. */
		if ( SIdAdpEstablecer ( p_idObj, "12a" ) != 0 )
		{
			printf( "Error caso 3: se esperaba rechazo de valor no valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SIdAdpEstablecerValorInicial ( p_idObj ) != 1 )
		{
			printf( "Error caso 4: se esperaba establecer valor inicial correcto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( CadComparar ( SIdAdpValor ( p_idObj ), "000" ) != COMP_IGUAL )
		{
			printf( "Error caso 5: se esperaba valor \"000\": %s\n", SIdAdpValor ( p_idObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SIdAdpDestruir ( &p_idObj );
	return ( iRes );
}

static int TestSIdAdpComparar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SIdAdpComparar 01:\n" );
	SIdAdap * p_idA = SIdAdpCrearExt ( 3, "999" );
	SIdAdap * p_idB = SIdAdpCrearExt ( 3, "999" );
	if ( ES_VALIDO ( p_idA ) && ES_VALIDO ( p_idB ) )
	{
		SIdAdpEstablecer ( p_idB, "005" );
		if ( SIdAdpEsMenor ( p_idA, p_idB ) != 1 )
		{
			printf( "Error caso 1: se esperaba A menor que B\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SIdAdpEsMayor ( p_idB, p_idA ) != 1 )
		{
			printf( "Error caso 2: se esperaba B mayor que A\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SIdAdap * p_idDup = SIdAdpDuplicar ( p_idB );
		if ( ES_VALIDO ( p_idDup ) )
		{
			if ( SIdAdpEsIgual ( p_idB, p_idDup ) != 1 )
			{
				printf( "Error caso 3: se esperaba duplicado igual\n" );
				iRes = BOOL_VAL_FALSO;
			}
		}
		else
		{
			printf( "Error caso 3: no se pudo duplicar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SIdAdpDestruir ( &p_idDup );
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SIdAdpDestruir ( &p_idA );
	SIdAdpDestruir ( &p_idB );
	return ( iRes );
}

static int TestSIdAdpNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SIdAdpNulo 01:\n" );
	if ( SIdAdpEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: se esperaba no valido con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SIdAdpIncrementar ( NULL ) != 0 )
	{
		printf( "Error caso 2: se esperaba fallo al incrementar nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SIdAdpValor ( NULL ) ) )
	{
		printf( "Error caso 3: se esperaba valor nulo con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

int TestSIdAdap ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SIdAdap]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSIdAdpCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSIdAdpIncrementar01 () == BOOL_VAL_CIERTO ) &&
			( TestSIdAdpEstablecer01 () == BOOL_VAL_CIERTO ) &&
			( TestSIdAdpComparar01 () == BOOL_VAL_CIERTO ) &&
			( TestSIdAdpNulo01 () == BOOL_VAL_CIERTO ) )
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
