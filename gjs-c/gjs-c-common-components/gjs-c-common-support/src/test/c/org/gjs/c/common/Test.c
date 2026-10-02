#include "Base.h"



#define NUM_TESTS        9

extern int TestTiposCajaMensajes ();
extern int TestCajaMensajes ();
extern int TestAplicacionValidaciones ();
extern int TestAplicacionConsola ();
extern int TestAplicacionInformacion ();
extern int TestAplicacionPortapapeles ();
extern int TestSVersion ();
extern int TestSPropiedades ();
extern int TestUtilidadesRecursos ();

char ** testArrayInit ()
{
    char ** p_p_cTests = (char **) MemReservar ( NUM_TESTS * sizeof( char *));
    p_p_cTests[ 0 ] = CadDuplicar ( "TiposCajaMensajesTest" );
    p_p_cTests[ 1 ] = CadDuplicar ( "CajaMensajesTest" );
    p_p_cTests[ 2 ] = CadDuplicar ( "AplicacionValidacionesTest" );
    p_p_cTests[ 3 ] = CadDuplicar ( "AplicacionConsolaTest" );
    p_p_cTests[ 4 ] = CadDuplicar ( "AplicacionInformacionTest" );
    p_p_cTests[ 5 ] = CadDuplicar ( "AplicacionPortapapelesTest" );
    p_p_cTests[ 6 ] = CadDuplicar ( "SVersionTest" );
    p_p_cTests[ 7 ] = CadDuplicar ( "SPropiedadesTest" );
    p_p_cTests[ 8 ] = CadDuplicar ( "UtilidadesRecursosTest" );
    return p_p_cTests;
}

PFUNINTV * functionArrayInit ()
{
    PFUNINTV* p_fTests = (PFUNINTV *) MemReservar ( NUM_TESTS * sizeof( PFUNINTV ));
    p_fTests[ 0 ] = TestTiposCajaMensajes;
    p_fTests[ 1 ] = TestCajaMensajes;
    p_fTests[ 2 ] = TestAplicacionValidaciones;
    p_fTests[ 3 ] = TestAplicacionConsola;
    p_fTests[ 4 ] = TestAplicacionInformacion;
    p_fTests[ 5 ] = TestAplicacionPortapapeles;
    p_fTests[ 6 ] = TestSVersion;
    p_fTests[ 7 ] = TestSPropiedades;
    p_fTests[ 8 ] = TestUtilidadesRecursos;
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
