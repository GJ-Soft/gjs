#include "Base.h"



#define NUM_TESTS        16

extern int TestModosApertura ();
extern int TestEstilosFicheroTexto ();
extern int TestSRuta ();
extern int TestSistemaFicheros ();
extern int TestSFicSecuencial ();
extern int TestSFicTexto ();
extern int TestSEntradaDirectorio ();
extern int TestSDirectorio ();
extern int TestSFicAleatorio ();
extern int TestSFicSecuencialBuffer ();
extern int TestSFicEncabezado ();
extern int TestSFicBloques ();
extern int TestSFicBloquesIdentificados ();
extern int TestSFicBloquesOrdenados ();
extern int TestSFicEstructura ();
extern int TestEntradaSalida ();

char ** testArrayInit ()
{
    char ** p_p_cTests = (char **) MemReservar ( NUM_TESTS * sizeof( char *));
    p_p_cTests[ 0 ] = CadDuplicar ( "ModosAperturaTest" );
    p_p_cTests[ 1 ] = CadDuplicar ( "EstilosFicheroTextoTest" );
    p_p_cTests[ 2 ] = CadDuplicar ( "SRutaTest" );
    p_p_cTests[ 3 ] = CadDuplicar ( "SistemaFicherosTest" );
    p_p_cTests[ 4 ] = CadDuplicar ( "SFicSecuencialTest" );
    p_p_cTests[ 5 ] = CadDuplicar ( "SFicTextoTest" );
    p_p_cTests[ 6 ] = CadDuplicar ( "SEntradaDirectorioTest" );
    p_p_cTests[ 7 ] = CadDuplicar ( "SDirectorioTest" );
    p_p_cTests[ 8 ] = CadDuplicar ( "SFicAleatorioTest" );
    p_p_cTests[ 9 ] = CadDuplicar ( "SFicSecuencialBufferTest" );
    p_p_cTests[ 10 ] = CadDuplicar ( "SFicEncabezadoTest" );
    p_p_cTests[ 11 ] = CadDuplicar ( "SFicBloquesTest" );
    p_p_cTests[ 12 ] = CadDuplicar ( "SFicBloquesIdentificadosTest" );
    p_p_cTests[ 13 ] = CadDuplicar ( "SFicBloquesOrdenadosTest" );
    p_p_cTests[ 14 ] = CadDuplicar ( "SFicEstructuraTest" );
    p_p_cTests[ 15 ] = CadDuplicar ( "EntradaSalidaTest" );
    return p_p_cTests;
}

PFUNINTV * functionArrayInit ()
{
    PFUNINTV * p_fTests = (PFUNINTV *) MemReservar ( NUM_TESTS * sizeof( PFUNINTV ));
    p_fTests[ 0 ] = TestModosApertura;
    p_fTests[ 1 ] = TestEstilosFicheroTexto;
    p_fTests[ 2 ] = TestSRuta;
    p_fTests[ 3 ] = TestSistemaFicheros;
    p_fTests[ 4 ] = TestSFicSecuencial;
    p_fTests[ 5 ] = TestSFicTexto;
    p_fTests[ 6 ] = TestSEntradaDirectorio;
    p_fTests[ 7 ] = TestSDirectorio;
    p_fTests[ 8 ] = TestSFicAleatorio;
    p_fTests[ 9 ] = TestSFicSecuencialBuffer;
    p_fTests[ 10 ] = TestSFicEncabezado;
    p_fTests[ 11 ] = TestSFicBloques;
    p_fTests[ 12 ] = TestSFicBloquesIdentificados;
    p_fTests[ 13 ] = TestSFicBloquesOrdenados;
    p_fTests[ 14 ] = TestSFicEstructura;
    p_fTests[ 15 ] = TestEntradaSalida;
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
