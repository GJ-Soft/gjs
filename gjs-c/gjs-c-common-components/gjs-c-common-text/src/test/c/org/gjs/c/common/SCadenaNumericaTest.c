#include "Base.h"

#include "SCadenaNumerica.h"



static int TestSCadnCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCadnCrear 01:\n" );

	SCadenaNumerica * p_cadObj = SCadnCrear ( 10 );
	if ( ES_NULO ( p_cadObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		/* Una cadena numerica recien creada vale 0. */
		if ( SCadnObtValor ( p_cadObj ) != 0 )
		{
			printf( "Error caso 2: el valor inicial deberia ser 0: %d\n", SCadnObtValor ( p_cadObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SCadnDestruir ( &p_cadObj );

	if ( ES_VALIDO ( p_cadObj ) )
	{
		printf( "Error caso 3: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSCadnValor01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCadnValor 01:\n" );

	SCadenaNumerica * p_cadObj = SCadnCrearValor ( 10, 42 );
	if ( ES_VALIDO ( p_cadObj ) )
	{
		if ( SCadnObtValor ( p_cadObj ) != 42 )
		{
			printf( "Error caso 1: el valor deberia ser 42: %d\n", SCadnObtValor ( p_cadObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* La representacion textual del valor es "42". */
		if ( CadComparar ( (char *) SCadcValorConstante ( SCadnCadenaConv ( p_cadObj ) ), "42" ) != COMP_IGUAL )
		{
			printf( "Error caso 2: la representacion deberia ser \"42\": [%s]\n",
					SCadcValorConstante ( SCadnCadenaConv ( p_cadObj ) ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* Establecer un nuevo valor. */
		SCadnEstablecerValor ( p_cadObj, 100 );
		if ( SCadnObtValor ( p_cadObj ) != 100 )
		{
			printf( "Error caso 3: el valor deberia ser 100: %d\n", SCadnObtValor ( p_cadObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* Establecer desde un literal numerico. */
		SCadnEstablecerValorLit ( p_cadObj, "55" );
		if ( SCadnObtValor ( p_cadObj ) != 55 )
		{
			printf( "Error caso 4: el valor deberia ser 55: %d\n", SCadnObtValor ( p_cadObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* Un literal no numerico deja el valor a 0. Se usa "xyz" porque
		   "abc" seria un hexadecimal valido y la libreria lo aceptaria. */
		SCadnEstablecerValorLit ( p_cadObj, "xyz" );
		if ( SCadnObtValor ( p_cadObj ) != 0 )
		{
			printf( "Error caso 5: un literal no numerico deberia dejar el valor a 0: %d\n", SCadnObtValor ( p_cadObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la cadena numerica\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCadnDestruir ( &p_cadObj );
	return ( iRes );
}

static int TestSCadnDuplicar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCadnDuplicar 01:\n" );

	SCadenaNumerica * p_cadObj = SCadnCrearValor ( 10, 77 );
	if ( ES_VALIDO ( p_cadObj ) )
	{
		SCadenaNumerica * p_cadCopia = SCadnDuplicar ( p_cadObj );
		if ( ES_VALIDO ( p_cadCopia ) )
		{
			if ( SCadnObtValor ( p_cadCopia ) != 77 )
			{
				printf( "Error caso 1: la copia deberia valer 77: %d\n", SCadnObtValor ( p_cadCopia ) );
				iRes = BOOL_VAL_FALSO;
			}
		}
		else
		{
			printf( "Error caso 1: no se pudo duplicar la cadena numerica\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SCadnDestruir ( &p_cadCopia );
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la cadena numerica\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCadnDestruir ( &p_cadObj );
	return ( iRes );
}



int TestSCadenaNumerica ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SCadenaNumerica]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSCadnCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSCadnValor01 () == BOOL_VAL_CIERTO ) &&
			( TestSCadnDuplicar01 () == BOOL_VAL_CIERTO ) )
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
