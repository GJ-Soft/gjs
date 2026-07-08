#include "Base.h"

#include "UniChar.h"



static int TestAsciiAUnicode01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test AsciiAUnicode 01:\n" );
	if ( AsciiAUnicode ( 'A' ) != (unichar) 0x0041 )
	{
		printf( "Error caso 1: se esperaba 0x0041: 0x%04X\n", AsciiAUnicode ( 'A' ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( AsciiAUnicode ( '0' ) != (unichar) 0x0030 )
	{
		printf( "Error caso 2: se esperaba 0x0030: 0x%04X\n", AsciiAUnicode ( '0' ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( AsciiAUnicode ( 0 ) != (unichar) 0x0000 )
	{
		printf( "Error caso 3: se esperaba 0x0000: 0x%04X\n", AsciiAUnicode ( 0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestUnicodeAscii01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test UnicodeAscii 01:\n" );
	/* Se comprueba la conversion inversa de un caracter latino basico. */
	if ( UnicodeAscii ( (unichar) 0x0041 ) != 'A' )
	{
		printf( "Error caso 1: se esperaba 'A': [%c] (0x%02X)\n",
				UnicodeAscii ( (unichar) 0x0041 ), (unsigned char) UnicodeAscii ( (unichar) 0x0041 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( UnicodeAscii ( (unichar) 0x0030 ) != '0' )
	{
		printf( "Error caso 2: se esperaba '0': [%c] (0x%02X)\n",
				UnicodeAscii ( (unichar) 0x0030 ), (unsigned char) UnicodeAscii ( (unichar) 0x0030 ) );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestCadConversion01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test CadConversion 01:\n" );
	/* Con puntero nulo ambas conversiones devuelven nulo. */
	if ( ES_VALIDO ( CadAsciizAUnicode ( NULL ) ) )
	{
		printf( "Error caso 1: se esperaba nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( CadUnicodeAAsciiz ( NULL ) ) )
	{
		printf( "Error caso 2: se esperaba nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Ida y vuelta ASCII -> Unicode -> ASCII. */
	unichar * p_ucUni = CadAsciizAUnicode ( "ABC" );
	if ( ES_NULO ( p_ucUni ) )
	{
		printf( "Error caso 3: no se pudo convertir a unicode\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( CadUniLongitud ( p_ucUni ) != 3 )
		{
			printf( "Error caso 4: se esperaba longitud 3: %d\n", CadUniLongitud ( p_ucUni ) );
			iRes = BOOL_VAL_FALSO;
		}
		char * p_cAscii = CadUnicodeAAsciiz ( p_ucUni );
		if ( ES_NULO ( p_cAscii ) || ( strcmp ( p_cAscii, "ABC" ) != 0 ) )
		{
			printf( "Error caso 5: ida y vuelta incorrecta: [%s]\n",
					ES_VALIDO ( p_cAscii ) ? p_cAscii : "(nulo)" );
			iRes = BOOL_VAL_FALSO;
		}
		MemLiberar ( (void **) &p_cAscii );
	}
	MemLiberar ( (void **) &p_ucUni );
	return ( iRes );
}



int TestUniChar ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test UniChar]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestAsciiAUnicode01 () == BOOL_VAL_CIERTO ) &&
			( TestUnicodeAscii01 () == BOOL_VAL_CIERTO ) &&
			( TestCadConversion01 () == BOOL_VAL_CIERTO ) )
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
