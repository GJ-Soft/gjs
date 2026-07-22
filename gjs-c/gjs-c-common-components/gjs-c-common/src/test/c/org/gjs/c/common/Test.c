#include "Base.h"



#define NUM_TESTS        5

extern int TestSArgumentos ();
extern int TestSMensajes ();
extern int TestEntorno ();
extern int TestConsolaDepuracion ();
extern int TestAplicacionLog ();

char ** testArrayInit ()
{
    char ** p_p_cTests = (char **) MemReservar ( NUM_TESTS * sizeof( char *));
    p_p_cTests[ 0 ] = CadDuplicar ( "SArgumentosTest" );
    p_p_cTests[ 1 ] = CadDuplicar ( "SMensajesTest" );
    p_p_cTests[ 2 ] = CadDuplicar ( "EntornoTest" );
    p_p_cTests[ 3 ] = CadDuplicar ( "ConsolaDepuracionTest" );
    p_p_cTests[ 4 ] = CadDuplicar ( "AplicacionLogTest" );
    return p_p_cTests;
}

PFUNINTV * functionArrayInit ()
{
    PFUNINTV* p_fTests = (PFUNINTV *) MemReservar ( NUM_TESTS * sizeof( PFUNINTV ));
    p_fTests[ 0 ] = TestSArgumentos;
    p_fTests[ 1 ] = TestSMensajes;
    p_fTests[ 2 ] = TestEntorno;
    p_fTests[ 3 ] = TestConsolaDepuracion;
    p_fTests[ 4 ] = TestAplicacionLog;
    return p_fTests;
}

void freeArrays ( char ** p_p_cTests, PFUNINTV* p_fTests )
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
			printf( "Test [%s] no encontrado.", p_cTest );
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
	freeArrays ( p_p_cTests, p_fTests );
	fflush ( stdout );
	return ( iRes );
}
