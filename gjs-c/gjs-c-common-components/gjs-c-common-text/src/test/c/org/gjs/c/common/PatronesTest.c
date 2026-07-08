#include "Base.h"

#include "Patrones.h"



static int TestPatEsValido01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test PatEsValido 01:\n" );

	/* Todos los codigos de tipo forman un patron valido. */
	if ( PatEsValido ( "9@&#$?" ) != 1 )
	{
		printf( "Error caso 1: el patron de codigos deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Un patron con caracteres que no son codigos de tipo es invalido. */
	if ( PatEsValido ( "AB" ) != 0 )
	{
		printf( "Error caso 2: un patron con letras no deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( PatEsValido ( "" ) != 0 )
	{
		printf( "Error caso 3: un patron vacio no deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( PatEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 4: un patron nulo no deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestPatEvaluar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test PatEvaluar 01:\n" );

	if ( PatEvaluar ( "999", "123" ) != 1 )
	{
		printf( "Error caso 1: \"123\" deberia cumplir el patron \"999\"\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( PatEvaluar ( "999", "12a" ) != 0 )
	{
		printf( "Error caso 2: \"12a\" no deberia cumplir el patron \"999\"\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( PatEvaluar ( "@@@", "ABC" ) != 1 )
	{
		printf( "Error caso 3: \"ABC\" deberia cumplir el patron \"@@@\"\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( PatEvaluar ( "@@@", "AB1" ) != 0 )
	{
		printf( "Error caso 4: \"AB1\" no deberia cumplir el patron \"@@@\"\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* El comodin '?' acepta cualquier caracter. */
	if ( PatEvaluar ( "???", "xY9" ) != 1 )
	{
		printf( "Error caso 5: \"xY9\" deberia cumplir el patron \"???\"\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Un patron mas largo que la cadena no puede cumplirse. */
	if ( PatEvaluar ( "9999", "12" ) != 0 )
	{
		printf( "Error caso 6: una cadena mas corta que el patron no deberia cumplirlo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestPatValores01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test PatValores 01:\n" );

	char * p_cIni = PatValorInicial ( "999" );
	char * p_cFin = PatValorFinal ( "999" );
	if ( ES_VALIDO ( p_cIni ) && ES_VALIDO ( p_cFin ) )
	{
		if ( CadComparar ( p_cIni, "000" ) != COMP_IGUAL )
		{
			printf( "Error caso 1: el valor inicial de \"999\" deberia ser \"000\": [%s]\n", p_cIni );
			iRes = BOOL_VAL_FALSO;
		}
		if ( CadComparar ( p_cFin, "999" ) != COMP_IGUAL )
		{
			printf( "Error caso 2: el valor final de \"999\" deberia ser \"999\": [%s]\n", p_cFin );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron generar los valores del patron\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_cIni );
	MemLiberar ( (void **) &p_cFin );

	char * p_cIniLet = PatValorInicial ( "@@" );
	char * p_cFinLet = PatValorFinal ( "@@" );
	if ( ES_VALIDO ( p_cIniLet ) && ES_VALIDO ( p_cFinLet ) )
	{
		if ( CadComparar ( p_cIniLet, "AA" ) != COMP_IGUAL )
		{
			printf( "Error caso 3: el valor inicial de \"@@\" deberia ser \"AA\": [%s]\n", p_cIniLet );
			iRes = BOOL_VAL_FALSO;
		}
		if ( CadComparar ( p_cFinLet, "ZZ" ) != COMP_IGUAL )
		{
			printf( "Error caso 4: el valor final de \"@@\" deberia ser \"ZZ\": [%s]\n", p_cFinLet );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron generar los valores del patron de letras\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_cIniLet );
	MemLiberar ( (void **) &p_cFinLet );
	return ( iRes );
}

static int TestPatIncrementar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test PatIncrementar 01:\n" );

	char * p_cValor = PatValorInicial ( "999" );
	if ( ES_VALIDO ( p_cValor ) )
	{
		/* "000" -> "001" */
		if ( PatIncrementarValor ( "999", p_cValor ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al incrementar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( CadComparar ( p_cValor, "001" ) != COMP_IGUAL )
		{
			printf( "Error caso 2: se esperaba \"001\": [%s]\n", p_cValor );
			iRes = BOOL_VAL_FALSO;
		}
		/* "001" -> "000" */
		if ( PatDecrementarValor ( "999", p_cValor ) != 1 )
		{
			printf( "Error caso 3: se esperaba resultado 1 al decrementar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( CadComparar ( p_cValor, "000" ) != COMP_IGUAL )
		{
			printf( "Error caso 4: se esperaba \"000\": [%s]\n", p_cValor );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo generar el valor inicial\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_cValor );
	return ( iRes );
}

static int TestPatCaracter01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test PatCaracter 01:\n" );

	char * p_cPatron = PatCrear ( 3 );
	if ( ES_VALIDO ( p_cPatron ) )
	{
		if ( PatEstablecerCaracter ( p_cPatron, 0, '9' ) != 1 )
		{
			printf( "Error caso 1: se esperaba poder establecer un codigo valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( PatCaracter ( p_cPatron, 0 ) != '9' )
		{
			printf( "Error caso 2: se esperaba '9': %c\n", PatCaracter ( p_cPatron, 0 ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* Un codigo que no es de tipo no debe poder establecerse. */
		if ( PatEstablecerCaracter ( p_cPatron, 1, 'x' ) != 0 )
		{
			printf( "Error caso 3: no deberia poder establecerse un codigo invalido\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el patron\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_cPatron );
	return ( iRes );
}



int TestPatrones ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test Patrones]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestPatEsValido01 () == BOOL_VAL_CIERTO ) &&
			( TestPatEvaluar01 () == BOOL_VAL_CIERTO ) &&
			( TestPatValores01 () == BOOL_VAL_CIERTO ) &&
			( TestPatIncrementar01 () == BOOL_VAL_CIERTO ) &&
			( TestPatCaracter01 () == BOOL_VAL_CIERTO ) )
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
