#include "Base.h"

#include "ASCII.h"



static int TestASCIIEsLetra01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test ASCIIEsLetra 01:\n" );

	if ( ASCIIEsLetra ( 'A' ) != 1 )
	{
		printf( "Error caso 1: 'A' deberia ser letra\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ASCIIEsLetra ( 'z' ) != 1 )
	{
		printf( "Error caso 2: 'z' deberia ser letra\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ASCIIEsLetra ( '5' ) != 0 )
	{
		printf( "Error caso 3: '5' no deberia ser letra\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ASCIIEsLetra ( ' ' ) != 0 )
	{
		printf( "Error caso 4: el espacio no deberia ser letra\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Distincion mayusculas / minusculas. */
	if ( ASCIIEsLetraMin ( 'a' ) != 1 )
	{
		printf( "Error caso 5: 'a' deberia ser letra minuscula\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ASCIIEsLetraMin ( 'A' ) != 0 )
	{
		printf( "Error caso 6: 'A' no deberia ser letra minuscula\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ASCIIEsLetraMay ( 'A' ) != 1 )
	{
		printf( "Error caso 7: 'A' deberia ser letra mayuscula\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ASCIIEsLetraMay ( 'a' ) != 0 )
	{
		printf( "Error caso 8: 'a' no deberia ser letra mayuscula\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestASCIIEsVocalConsonante01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test ASCIIEsVocalConsonante 01:\n" );

	if ( ASCIIEsVocal ( 'a' ) != 1 )
	{
		printf( "Error caso 1: 'a' deberia ser vocal\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ASCIIEsVocal ( 'E' ) != 1 )
	{
		printf( "Error caso 2: 'E' deberia ser vocal\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ASCIIEsVocal ( 'b' ) != 0 )
	{
		printf( "Error caso 3: 'b' no deberia ser vocal\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ASCIIEsConsonante ( 'b' ) != 1 )
	{
		printf( "Error caso 4: 'b' deberia ser consonante\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ASCIIEsConsonante ( 'a' ) != 0 )
	{
		printf( "Error caso 5: 'a' no deberia ser consonante\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestASCIIEsDigito01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test ASCIIEsDigito 01:\n" );

	if ( ASCIIEsDigito ( '0' ) != 1 )
	{
		printf( "Error caso 1: '0' deberia ser digito\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ASCIIEsDigito ( '9' ) != 1 )
	{
		printf( "Error caso 2: '9' deberia ser digito\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ASCIIEsDigito ( 'a' ) != 0 )
	{
		printf( "Error caso 3: 'a' no deberia ser digito\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ASCIIEsAlfanumerico ( 'a' ) != 1 )
	{
		printf( "Error caso 4: 'a' deberia ser alfanumerico\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ASCIIEsAlfanumerico ( '5' ) != 1 )
	{
		printf( "Error caso 5: '5' deberia ser alfanumerico\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ASCIIEsAlfanumerico ( ' ' ) != 0 )
	{
		printf( "Error caso 6: el espacio no deberia ser alfanumerico\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestASCIISignos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test ASCIISignos 01:\n" );

	if ( ASCIIEsEspacio ( ' ' ) != 1 )
	{
		printf( "Error caso 1: el espacio deberia ser espacio\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ASCIIEsEspacio ( 'a' ) != 0 )
	{
		printf( "Error caso 2: 'a' no deberia ser espacio\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ASCIIEsGuion ( '-' ) != 1 )
	{
		printf( "Error caso 3: '-' deberia ser guion\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ASCIIEsPunto ( '.' ) != 1 )
	{
		printf( "Error caso 4: '.' deberia ser punto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ASCIIEsComa ( ',' ) != 1 )
	{
		printf( "Error caso 5: ',' deberia ser coma\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ASCIIEsSigno ( '+' ) != 1 )
	{
		printf( "Error caso 6: '+' deberia ser signo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ASCIIEsSigno ( 'a' ) != 0 )
	{
		printf( "Error caso 7: 'a' no deberia ser signo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestASCIIConversiones01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test ASCIIConversiones 01:\n" );

	if ( ASCIILetraMinAMay ( 'a' ) != 'A' )
	{
		printf( "Error caso 1: se esperaba 'A': %c\n", ASCIILetraMinAMay ( 'a' ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ASCIILetraMinAMay ( 'z' ) != 'Z' )
	{
		printf( "Error caso 2: se esperaba 'Z': %c\n", ASCIILetraMinAMay ( 'z' ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ASCIILetraMayAMin ( 'A' ) != 'a' )
	{
		printf( "Error caso 3: se esperaba 'a': %c\n", ASCIILetraMayAMin ( 'A' ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ASCIILetraMayAMin ( 'Z' ) != 'z' )
	{
		printf( "Error caso 4: se esperaba 'z': %c\n", ASCIILetraMayAMin ( 'Z' ) );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



int TestASCII ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test ASCII]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestASCIIEsLetra01 () == BOOL_VAL_CIERTO ) &&
			( TestASCIIEsVocalConsonante01 () == BOOL_VAL_CIERTO ) &&
			( TestASCIIEsDigito01 () == BOOL_VAL_CIERTO ) &&
			( TestASCIISignos01 () == BOOL_VAL_CIERTO ) &&
			( TestASCIIConversiones01 () == BOOL_VAL_CIERTO ) )
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
