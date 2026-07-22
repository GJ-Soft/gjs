#include "Base.h"



#define NUM_TESTS        21

extern int TestCadenasBase ();
extern int TestFormatoCadena ();
extern int TestSConversor ();
extern int TestNibble ();
extern int TestByte ();
extern int TestWord ();
extern int TestDWord ();
extern int TestBits ();
extern int TestHexadecimal ();
extern int TestNumeros ();
extern int TestBooleano ();
extern int TestIntercambios ();
extern int TestOrdenBytes ();
extern int TestTipos ();
extern int TestConversionesTipos ();
extern int TestMemoria ();
extern int TestErrores ();
extern int TestHash ();
extern int TestASCIIEstandar ();
extern int TestUniChar ();
extern int TestVersiones ();

char ** testArrayInit ()
{
    char ** p_p_cTests = (char **) MemReservar ( NUM_TESTS * sizeof( char *) );
    p_p_cTests[  0 ] = CadDuplicar ( "CadenasBaseTest" );
    p_p_cTests[  1 ] = CadDuplicar ( "FormatoCadenaTest" );
    p_p_cTests[  2 ] = CadDuplicar ( "SConversorTest" );
    p_p_cTests[  3 ] = CadDuplicar ( "NibbleTest" );
    p_p_cTests[  4 ] = CadDuplicar ( "ByteTest" );
    p_p_cTests[  5 ] = CadDuplicar ( "WordTest" );
    p_p_cTests[  6 ] = CadDuplicar ( "DWordTest" );
    p_p_cTests[  7 ] = CadDuplicar ( "BitsTest" );
    p_p_cTests[  8 ] = CadDuplicar ( "HexadecimalTest" );
    p_p_cTests[  9 ] = CadDuplicar ( "NumerosTest" );
    p_p_cTests[ 10 ] = CadDuplicar ( "BooleanoTest" );
    p_p_cTests[ 11 ] = CadDuplicar ( "IntercambiosTest" );
    p_p_cTests[ 12 ] = CadDuplicar ( "OrdenBytesTest" );
    p_p_cTests[ 13 ] = CadDuplicar ( "TiposTest" );
    p_p_cTests[ 14 ] = CadDuplicar ( "ConversionesTiposTest" );
    p_p_cTests[ 15 ] = CadDuplicar ( "MemoriaTest" );
    p_p_cTests[ 16 ] = CadDuplicar ( "ErroresTest" );
    p_p_cTests[ 17 ] = CadDuplicar ( "HashTest" );
    p_p_cTests[ 18 ] = CadDuplicar ( "ASCIIEstandarTest" );
    p_p_cTests[ 19 ] = CadDuplicar ( "UniCharTest" );
    p_p_cTests[ 20 ] = CadDuplicar ( "VersionesTest" );
    return p_p_cTests;
}

PFUNINTV * functionArrayInit ()
{
    PFUNINTV * p_fTests = (PFUNINTV *) MemReservar ( NUM_TESTS * sizeof( PFUNINTV ) );
    p_fTests[  0 ] = TestCadenasBase;
    p_fTests[  1 ] = TestFormatoCadena;
    p_fTests[  2 ] = TestSConversor;
    p_fTests[  3 ] = TestNibble;
    p_fTests[  4 ] = TestByte;
    p_fTests[  5 ] = TestWord;
    p_fTests[  6 ] = TestDWord;
    p_fTests[  7 ] = TestBits;
    p_fTests[  8 ] = TestHexadecimal;
    p_fTests[  9 ] = TestNumeros;
    p_fTests[ 10 ] = TestBooleano;
    p_fTests[ 11 ] = TestIntercambios;
    p_fTests[ 12 ] = TestOrdenBytes;
    p_fTests[ 13 ] = TestTipos;
    p_fTests[ 14 ] = TestConversionesTipos;
    p_fTests[ 15 ] = TestMemoria;
    p_fTests[ 16 ] = TestErrores;
    p_fTests[ 17 ] = TestHash;
    p_fTests[ 18 ] = TestASCIIEstandar;
    p_fTests[ 19 ] = TestUniChar;
    p_fTests[ 20 ] = TestVersiones;
    return p_fTests;
}

void freeArrays ( char ** p_p_cTests, PFUNINTV* p_fTests )
{
    for ( int i = 0; i < NUM_TESTS; i = i + 1 )
	{
        MemLiberar( (void **) &(p_p_cTests[ i ]) );
    }
    MemLiberar( (void **) p_p_cTests );
    MemLiberar( (void **) &p_fTests );
}

int findTest ( char ** p_p_cTests, char * p_cTest )
{
    int iIndex = -1;
    int i = 0;
    while ( ( i < NUM_TESTS) && ( iIndex < 0 ) )
    {
        if ( CadComparar ( p_p_cTests[ i ], p_cTest ) == COMP_IGUAL )
        {
            iIndex = i;
        }
        i = i + 1;
    }
    return ( iIndex );
}

int main ( int argc, char * argv[] )
{
	int iRes = 0;

	char ** p_p_cTests = testArrayInit();
    PFUNINTV * p_fTests = functionArrayInit();

	printf ( "%s[Inicio de los test]%s\n", ANSI_AZUL, ANSI_RESETEAR );
	char * p_cTest =  NULL;
	if ( argc > 1 )
	{
		p_cTest = argv [ 1 ];
	}
	if ( CadLongitud ( p_cTest ) > 0 )
	{
	    int iTest = findTest( p_p_cTests, p_cTest );
		if ( iTest >= 0 )
		{
			PFUNINTV fTest = p_fTests[ iTest ];
			if( fTest() != 1 )
			{
				iRes = -1;
			}
		}
		else
		{
			printf ( "%sTest [%s] no encontrado.%s\n", ANSI_ROJO, p_cTest, ANSI_RESETEAR );
			iRes = -1;
		}
		freeArrays ( p_p_cTests, p_fTests );
		return( iRes );
	}
	for ( int iTest = 0; iTest < NUM_TESTS; iTest = iTest + 1 )
	{
		PFUNINTV fTest = p_fTests[ iTest ];
		if( fTest() != 1 )
		{
			iRes = -1;
		}
	}
	freeArrays ( p_p_cTests, p_fTests );
	printf ( "%s[Fin de los test]%s\n", ANSI_AZUL, ANSI_RESETEAR );
	if ( iRes == 0 )
	{
		printf ("%sResultado global: OK%s\n", ANSI_VERDE, ANSI_RESETEAR );
	}
	else
	{
		printf ("%sResultado global: KO%s\n", ANSI_ROJO, ANSI_RESETEAR );
	}
	return ( iRes );
}
