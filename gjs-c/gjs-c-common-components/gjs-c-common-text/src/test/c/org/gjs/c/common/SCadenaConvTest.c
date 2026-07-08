#include "Base.h"

#include "SCadenaConv.h"



static int TestSCadcCrearLit01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCadcCrearLit 01:\n" );

	SCadenaConv * p_cadObj = SCadcCrearLit ( "123" );
	if ( ES_NULO ( p_cadObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SCadcEsValida ( p_cadObj ) != 1 )
		{
			printf( "Error caso 2: la cadena recien creada deberia ser valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( CadComparar ( (char *) SCadcValorConstante ( p_cadObj ), "123" ) != COMP_IGUAL )
		{
			printf( "Error caso 3: el valor deberia ser \"123\": [%s]\n", SCadcValorConstante ( p_cadObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* "123" es numerica y su valor entero es 123. */
		if ( SCadcEsNumerica ( p_cadObj ) != 1 )
		{
			printf( "Error caso 4: \"123\" deberia ser numerica\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadcValorEntero ( p_cadObj ) != 123 )
		{
			printf( "Error caso 5: el valor entero deberia ser 123: %d\n", SCadcValorEntero ( p_cadObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SCadcDestruir ( &p_cadObj );

	if ( ES_VALIDO ( p_cadObj ) )
	{
		printf( "Error caso 6: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSCadcCopiar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCadcCopiar 01:\n" );

	SCadenaConv * p_cadObj = SCadcCrear ( 20 );
	if ( ES_VALIDO ( p_cadObj ) )
	{
		SCadcCopiarLit ( p_cadObj, "hola" );
		if ( SCadcEsIgualLit ( p_cadObj, "hola" ) != 1 )
		{
			printf( "Error caso 1: se esperaba \"hola\": [%s]\n", SCadcValorConstante ( p_cadObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadcLongitud ( p_cadObj ) != 4 )
		{
			printf( "Error caso 2: la longitud deberia ser 4: %d\n", SCadcLongitud ( p_cadObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* "hola" no es numerica. */
		if ( SCadcEsNumerica ( p_cadObj ) != 0 )
		{
			printf( "Error caso 3: \"hola\" no deberia ser numerica\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la cadena\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCadcDestruir ( &p_cadObj );
	return ( iRes );
}

static int TestSCadcEntero01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCadcEntero 01:\n" );

	SCadenaConv * p_cadObj = SCadcCrear ( 20 );
	if ( ES_VALIDO ( p_cadObj ) )
	{
		/* Volcar un entero y releerlo. */
		SCadcCopiarEntero ( p_cadObj, 45 );
		if ( SCadcEsIgualLit ( p_cadObj, "45" ) != 1 )
		{
			printf( "Error caso 1: se esperaba \"45\": [%s]\n", SCadcValorConstante ( p_cadObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadcValorEntero ( p_cadObj ) != 45 )
		{
			printf( "Error caso 2: el valor entero deberia ser 45: %d\n", SCadcValorEntero ( p_cadObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la cadena\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCadcDestruir ( &p_cadObj );
	return ( iRes );
}



int TestSCadenaConv ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SCadenaConv]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSCadcCrearLit01 () == BOOL_VAL_CIERTO ) &&
			( TestSCadcCopiar01 () == BOOL_VAL_CIERTO ) &&
			( TestSCadcEntero01 () == BOOL_VAL_CIERTO ) )
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
