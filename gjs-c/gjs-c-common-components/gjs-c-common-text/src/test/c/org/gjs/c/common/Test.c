#include "Base.h"



#define NUM_TESTS        15

extern int TestCadenas ();
extern int TestExpresionesRegulares ();
extern int TestASCII ();
extern int TestTiposCaracter ();
extern int TestPatrones ();
extern int TestSCadena ();
extern int TestSCadenaConv ();
extern int TestSCadenaNumerica ();
extern int TestSDescripcion ();
extern int TestSDivisor ();
extern int TestSLinea ();
extern int TestSListaCadenas ();
extern int TestSNombre ();
extern int TestSTexto ();
extern int TestSToken ();


char ** testArrayInit ()
{
    char ** p_p_cTests = (char **) MemReservar ( NUM_TESTS * sizeof( char *));
    p_p_cTests[ 0 ] = CadDuplicar ( "CadenasTest" );
    p_p_cTests[ 1 ] = CadDuplicar ( "ExpresionesRegularesTest" );
    p_p_cTests[ 2 ] = CadDuplicar ( "ASCIITest" );
    p_p_cTests[ 3 ] = CadDuplicar ( "TiposCaracterTest" );
    p_p_cTests[ 4 ] = CadDuplicar ( "PatronesTest" );
    p_p_cTests[ 5 ] = CadDuplicar ( "SCadenaTest" );
    p_p_cTests[ 6 ] = CadDuplicar ( "SCadenaConvTest" );
    p_p_cTests[ 7 ] = CadDuplicar ( "SCadenaNumericaTest" );
    p_p_cTests[ 8 ] = CadDuplicar ( "SDescripcionTest" );
    p_p_cTests[ 9 ] = CadDuplicar ( "SDivisorTest" );
    p_p_cTests[ 10 ] = CadDuplicar ( "SLineaTest" );
    p_p_cTests[ 11 ] = CadDuplicar ( "SListaCadenasTest" );
    p_p_cTests[ 12 ] = CadDuplicar ( "SNombreTest" );
    p_p_cTests[ 13 ] = CadDuplicar ( "STextoTest" );
    p_p_cTests[ 14 ] = CadDuplicar ( "STokenTest" );
    return p_p_cTests;
}

PFUNINTV * functionArrayInit ()
{
    PFUNINTV* p_fTests = (PFUNINTV *) MemReservar ( NUM_TESTS * sizeof( PFUNINTV ));
    p_fTests[ 0 ] = TestCadenas;
    p_fTests[ 1 ] = TestExpresionesRegulares;
    p_fTests[ 2 ] = TestASCII;
    p_fTests[ 3 ] = TestTiposCaracter;
    p_fTests[ 4 ] = TestPatrones;
    p_fTests[ 5 ] = TestSCadena;
    p_fTests[ 6 ] = TestSCadenaConv;
    p_fTests[ 7 ] = TestSCadenaNumerica;
    p_fTests[ 8 ] = TestSDescripcion;
    p_fTests[ 9 ] = TestSDivisor;
    p_fTests[ 10 ] = TestSLinea;
    p_fTests[ 11 ] = TestSListaCadenas;
    p_fTests[ 12 ] = TestSNombre;
    p_fTests[ 13 ] = TestSTexto;
    p_fTests[ 14 ] = TestSToken;
    return p_fTests;
}

void freeArrays( char ** p_p_cTests, PFUNINTV* p_fTests )
{
    for ( int i = 0; i < NUM_TESTS; i = i + 1 ) {
        MemLiberar ( (void **) &(p_p_cTests[ i ]) );
    }
    MemLiberar ( (void **) p_p_cTests );
    MemLiberar ( (void **) &p_fTests );
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

	char ** p_p_cTests = testArrayInit ();
    PFUNINTV * p_fTests = functionArrayInit ();

	printf ( "%s[Inicio de los test]%s\n", ANSI_AZUL, ANSI_RESETEAR );
	char * p_cTest = 0x0;
	if ( argc > 1 )
	{
		p_cTest = argv[1];
	}
	if ( CadLongitud ( p_cTest ) > 0 )
	{
	    int iTest = findTest ( p_p_cTests, p_cTest );
		if ( iTest >= 0 )
		{
			PFUNINTV fTest = p_fTests[ iTest ];
			if( fTest () != 1 )
			{
				iRes = -1;
			}
		}
		else
		{
			printf ( "%sTest [%s] no encontrado.%s\n", ANSI_ROJO, p_cTest, ANSI_RESETEAR );
			iRes = -1;
		}
		return( iRes );
	}

	for ( int iTest = 0; iTest < NUM_TESTS; iTest = iTest + 1 )
	{
		PFUNINTV fTest = p_fTests[ iTest ];
		if( fTest () != 1 )
		{
			iRes = -1;
		}
	}
	freeArrays( p_p_cTests, p_fTests );
	printf ( "%s[Fin de los test]%s\n", ANSI_AZUL, ANSI_RESETEAR );
	if ( iRes == 0 )
	{
		printf ("%sResultado global: OK%s\n", ANSI_VERDE, ANSI_RESETEAR );
	}
	else
	{
		printf ("%sResultado global: KO%s\n", ANSI_ROJO, ANSI_RESETEAR );
	}
	fflush ( stdout );
	return ( iRes );
}
