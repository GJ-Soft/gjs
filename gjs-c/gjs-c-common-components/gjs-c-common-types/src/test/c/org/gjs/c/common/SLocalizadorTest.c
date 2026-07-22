#include "Base.h"

#include "SLocalizador.h"



static int TestSLczCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLczCrear 01:\n" );
	SLocalizador * p_lczObj = SLczCrear ( "clave" );
	if ( ES_VALIDO ( p_lczObj ) )
	{
		if ( ES_NULO ( SLczClave ( p_lczObj ) ) || ( CadComparar ( SLczClave ( p_lczObj ), "clave" ) != COMP_IGUAL ) )
		{
			printf( "Error caso 1: se esperaba clave \"clave\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Recien creado la posicion es 0, por lo que aun no es valido. */
		if ( SLczEsValido ( p_lczObj ) != 0 )
		{
			printf( "Error caso 2: se esperaba no valido (posicion 0)\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLczDestruir ( &p_lczObj );
	return ( iRes );
}

static int TestSLczEstablecer01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLczEstablecer 01:\n" );
	SLocalizador * p_lczObj = SLczCrearDef ();
	if ( ES_VALIDO ( p_lczObj ) )
	{
		if ( SLczEstablecer ( p_lczObj, "manzana", 7 ) != 1 )
		{
			printf( "Error caso 1: se esperaba establecer correcto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLczPosicion ( p_lczObj ) != 7 )
		{
			printf( "Error caso 2: se esperaba posicion 7: %d\n", SLczPosicion ( p_lczObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLczEsValido ( p_lczObj ) != 1 )
		{
			printf( "Error caso 3: se esperaba valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLczEstablecerPosicion ( p_lczObj, 12 ) != 1 )
		{
			printf( "Error caso 4: se esperaba establecer posicion correcto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLczPosicion ( p_lczObj ) != 12 )
		{
			printf( "Error caso 5: se esperaba posicion 12: %d\n", SLczPosicion ( p_lczObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLczDestruir ( &p_lczObj );
	return ( iRes );
}

static int TestSLczComparar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLczComparar 01:\n" );
	SLocalizador * p_lczObj = SLczCrearDef ();
	if ( ES_VALIDO ( p_lczObj ) )
	{
		SLczEstablecer ( p_lczObj, "manzana", 3 );
		if ( SLczEsIgual ( p_lczObj, "manzana" ) != 1 )
		{
			printf( "Error caso 1: se esperaba igual a \"manzana\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLczEsMenor ( p_lczObj, "pera" ) != 1 )
		{
			printf( "Error caso 2: se esperaba menor que \"pera\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLczEsMayor ( p_lczObj, "limon" ) != 1 )
		{
			printf( "Error caso 3: se esperaba mayor que \"limon\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLczDestruir ( &p_lczObj );
	return ( iRes );
}

static int TestSLczDuplicar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLczDuplicar 01:\n" );
	SLocalizador * p_lczObj = SLczCrearDef ();
	if ( ES_VALIDO ( p_lczObj ) )
	{
		SLczEstablecer ( p_lczObj, "clave", 4 );
		SLocalizador * p_lczDup = SLczDuplicar ( p_lczObj );
		if ( ES_VALIDO ( p_lczDup ) )
		{
			if ( SLczEsIgual ( p_lczDup, "clave" ) != 1 )
			{
				printf( "Error caso 1: el duplicado no conserva la clave\n" );
				iRes = BOOL_VAL_FALSO;
			}
			if ( SLczPosicion ( p_lczDup ) != 4 )
			{
				printf( "Error caso 2: el duplicado no conserva la posicion: %d\n", SLczPosicion ( p_lczDup ) );
				iRes = BOOL_VAL_FALSO;
			}
		}
		else
		{
			printf( "Error caso 1: no se pudo duplicar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLczDestruir ( &p_lczDup );
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLczDestruir ( &p_lczObj );
	return ( iRes );
}

static int TestSLczNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLczNulo 01:\n" );
	if ( SLczEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: se esperaba no valido con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLczEstablecer ( NULL, "clave", 1 ) != 0 )
	{
		printf( "Error caso 2: se esperaba fallo con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SLczClave ( NULL ) ) )
	{
		printf( "Error caso 3: se esperaba clave nula con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

int TestSLocalizador ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SLocalizador]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSLczCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSLczEstablecer01 () == BOOL_VAL_CIERTO ) &&
			( TestSLczComparar01 () == BOOL_VAL_CIERTO ) &&
			( TestSLczDuplicar01 () == BOOL_VAL_CIERTO ) &&
			( TestSLczNulo01 () == BOOL_VAL_CIERTO ) )
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
