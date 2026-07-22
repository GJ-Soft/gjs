#include "Base.h"

#include "SArgumentos.h"



static int TestSArgCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SArgCrear 01:\n" );
	/* SArgCrear ignora argv[0] (el programa) y toma el resto de argumentos. */
	char * p_p_cArgv [] = { "programa", "hola", "42", "2.5", "-7" };
	SArgumentos * p_argObj = SArgCrear ( 5, p_p_cArgv );
	if ( ES_NULO ( p_argObj ) )
	{
		printf( "Error caso 0: no se pudo crear el objeto de argumentos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SArgNumArgumentos ( p_argObj ) != 4 )
		{
			printf( "Error caso 1: se esperaban 4 argumentos: %d\n", SArgNumArgumentos ( p_argObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		char * p_cArg = SArgArgumento ( p_argObj, 0 );
		if ( ES_NULO ( p_cArg ) || ( strcmp ( p_cArg, "hola" ) != 0 ) )
		{
			printf( "Error caso 2: se esperaba \"hola\": [%s]\n", ES_VALIDO ( p_cArg ) ? p_cArg : "(nulo)" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SArgArgumento ( p_argObj, 99 ) ) )
		{
			printf( "Error caso 3: se esperaba nulo para un indice fuera de rango\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Deteccion de argumentos numericos. */
		if ( SArgEsArgumentoNumerico ( p_argObj, 1 ) != 1 )
		{
			printf( "Error caso 4: \"42\" deberia ser numerico\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SArgEsArgumentoNumerico ( p_argObj, 0 ) != 0 )
		{
			printf( "Error caso 5: \"hola\" no deberia ser numerico\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Conversiones. */
		if ( SArgArgumentoEntero ( p_argObj, 1 ) != 42 )
		{
			printf( "Error caso 6: se esperaba entero 42: %d\n", SArgArgumentoEntero ( p_argObj, 1 ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SArgArgumentoEntero ( p_argObj, 0 ) != 0 )
		{
			printf( "Error caso 7: un argumento no entero debe convertirse a 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SArgArgumentoEnteroLargo ( p_argObj, 3 ) != -7 )
		{
			printf( "Error caso 8: se esperaba entero largo -7: %ld\n", SArgArgumentoEnteroLargo ( p_argObj, 3 ) );
			iRes = BOOL_VAL_FALSO;
		}
		double dReal = SArgArgumentoRealDoble ( p_argObj, 2 );
		if ( ( dReal < 2.4 ) || ( dReal > 2.6 ) )
		{
			printf( "Error caso 9: se esperaba real ~2.5: %f\n", dReal );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SArgDestruir ( &p_argObj );
	return ( iRes );
}

static int TestSArgSinArgumentos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SArgSinArgumentos 01:\n" );
	/* Solo el nombre del programa: no hay argumentos. */
	char * p_p_cArgv [] = { "programa" };
	SArgumentos * p_argObj = SArgCrear ( 1, p_p_cArgv );
	if ( ES_VALIDO ( p_argObj ) )
	{
		if ( SArgNumArgumentos ( p_argObj ) != 0 )
		{
			printf( "Error caso 1: se esperaban 0 argumentos: %d\n", SArgNumArgumentos ( p_argObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto de argumentos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SArgDestruir ( &p_argObj );
	return ( iRes );
}

static int TestSArgNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SArgNulo 01:\n" );
	if ( SArgNumArgumentos ( NULL ) != 0 )
	{
		printf( "Error caso 1: se esperaban 0 argumentos con objeto nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SArgArgumento ( NULL, 0 ) ) )
	{
		printf( "Error caso 2: se esperaba nulo al obtener argumento de objeto nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SArgEsArgumentoNumerico ( NULL, 0 ) != 0 )
	{
		printf( "Error caso 3: se esperaba 0 al comprobar numerico de objeto nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



int TestSArgumentos ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SArgumentos]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSArgCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSArgSinArgumentos01 () == BOOL_VAL_CIERTO ) &&
			( TestSArgNulo01 () == BOOL_VAL_CIERTO ) )
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
