#include "Base.h"



#define NUM_TESTS        34

extern int TestSError ();
extern int TestSTipo ();
extern int TestSValor ();
extern int TestSParametro ();
extern int TestSConector ();
extern int TestSUbicacion ();
extern int TestSLocalizador ();
extern int TestSLocalizadorExt ();
extern int TestSEntidad ();
extern int TestSEntidadNom ();
extern int TestSEntidadCod ();
extern int TestSEntidadCodNom ();
extern int TestSEntidadIdCod ();
extern int TestSMensaje ();
extern int TestSIdAdap ();
extern int TestSGeneradorIdAdap ();
extern int TestSAccion ();
extern int TestTiposAccion ();
extern int TestSHiloAriadna ();
extern int TestSHoja ();
extern int TestSDatosTexto ();
extern int TestSVectorCadenas ();
extern int TestSSecuenciaCadenas ();
extern int TestSTablaCadenas ();
extern int TestSPilaCadenas ();
extern int TestSArbolCadenas ();
extern int TestSSecuenciaGeneradoresId ();
extern int TestSEntrada ();
extern int TestSEntradaExt ();
extern int TestSListaEntradas ();
extern int TestSListaEntradasExt ();
extern int TestSListaParametros ();
extern int TestSListaValores ();
extern int TestSListaErrores ();

char ** testArrayInit()
{
    char ** p_p_cTests = (char **) MemReservar ( NUM_TESTS * sizeof( char *));
    p_p_cTests[ 0 ] = CadDuplicar ( "SErrorTest" );
    p_p_cTests[ 1 ] = CadDuplicar ( "STipoTest" );
    p_p_cTests[ 2 ] = CadDuplicar ( "SValorTest" );
    p_p_cTests[ 3 ] = CadDuplicar ( "SParametroTest" );
    p_p_cTests[ 4 ] = CadDuplicar ( "SConectorTest" );
    p_p_cTests[ 5 ] = CadDuplicar ( "SUbicacionTest" );
    p_p_cTests[ 6 ] = CadDuplicar ( "SLocalizadorTest" );
    p_p_cTests[ 7 ] = CadDuplicar ( "SLocalizadorExtTest" );
    p_p_cTests[ 8 ] = CadDuplicar ( "SEntidadTest" );
    p_p_cTests[ 9 ] = CadDuplicar ( "SEntidadNomTest" );
    p_p_cTests[ 10 ] = CadDuplicar ( "SEntidadCodTest" );
    p_p_cTests[ 11 ] = CadDuplicar ( "SEntidadCodNomTest" );
    p_p_cTests[ 12 ] = CadDuplicar ( "SEntidadIdCodTest" );
    p_p_cTests[ 13 ] = CadDuplicar ( "SMensajeTest" );
    p_p_cTests[ 14 ] = CadDuplicar ( "SIdAdapTest" );
    p_p_cTests[ 15 ] = CadDuplicar ( "SGeneradorIdAdapTest" );
    p_p_cTests[ 16 ] = CadDuplicar ( "SAccionTest" );
    p_p_cTests[ 17 ] = CadDuplicar ( "TiposAccionTest" );
    p_p_cTests[ 18 ] = CadDuplicar ( "SHiloAriadnaTest" );
    p_p_cTests[ 19 ] = CadDuplicar ( "SHojaTest" );
    p_p_cTests[ 20 ] = CadDuplicar ( "SDatosTextoTest" );
    p_p_cTests[ 21 ] = CadDuplicar ( "SVectorCadenasTest" );
    p_p_cTests[ 22 ] = CadDuplicar ( "SSecuenciaCadenasTest" );
    p_p_cTests[ 23 ] = CadDuplicar ( "STablaCadenasTest" );
    p_p_cTests[ 24 ] = CadDuplicar ( "SPilaCadenasTest" );
    p_p_cTests[ 25 ] = CadDuplicar ( "SArbolCadenasTest" );
    p_p_cTests[ 26 ] = CadDuplicar ( "SSecuenciaGeneradoresIdTest" );
    p_p_cTests[ 27 ] = CadDuplicar ( "SEntradaTest" );
    p_p_cTests[ 28 ] = CadDuplicar ( "SEntradaExtTest" );
    p_p_cTests[ 29 ] = CadDuplicar ( "SListaEntradasTest" );
    p_p_cTests[ 30 ] = CadDuplicar ( "SListaEntradasExtTest" );
    p_p_cTests[ 31 ] = CadDuplicar ( "SListaParametrosTest" );
    p_p_cTests[ 32 ] = CadDuplicar ( "SListaValoresTest" );
    p_p_cTests[ 33 ] = CadDuplicar ( "SListaErroresTest" );
    return p_p_cTests;
}

PFUNINTV * functionArrayInit()
{
    PFUNINTV* p_fTests = (PFUNINTV *) MemReservar ( NUM_TESTS * sizeof( PFUNINTV ));
    p_fTests[ 0 ] = TestSError;
    p_fTests[ 1 ] = TestSTipo;
    p_fTests[ 2 ] = TestSValor;
    p_fTests[ 3 ] = TestSParametro;
    p_fTests[ 4 ] = TestSConector;
    p_fTests[ 5 ] = TestSUbicacion;
    p_fTests[ 6 ] = TestSLocalizador;
    p_fTests[ 7 ] = TestSLocalizadorExt;
    p_fTests[ 8 ] = TestSEntidad;
    p_fTests[ 9 ] = TestSEntidadNom;
    p_fTests[ 10 ] = TestSEntidadCod;
    p_fTests[ 11 ] = TestSEntidadCodNom;
    p_fTests[ 12 ] = TestSEntidadIdCod;
    p_fTests[ 13 ] = TestSMensaje;
    p_fTests[ 14 ] = TestSIdAdap;
    p_fTests[ 15 ] = TestSGeneradorIdAdap;
    p_fTests[ 16 ] = TestSAccion;
    p_fTests[ 17 ] = TestTiposAccion;
    p_fTests[ 18 ] = TestSHiloAriadna;
    p_fTests[ 19 ] = TestSHoja;
    p_fTests[ 20 ] = TestSDatosTexto;
    p_fTests[ 21 ] = TestSVectorCadenas;
    p_fTests[ 22 ] = TestSSecuenciaCadenas;
    p_fTests[ 23 ] = TestSTablaCadenas;
    p_fTests[ 24 ] = TestSPilaCadenas;
    p_fTests[ 25 ] = TestSArbolCadenas;
    p_fTests[ 26 ] = TestSSecuenciaGeneradoresId;
    p_fTests[ 27 ] = TestSEntrada;
    p_fTests[ 28 ] = TestSEntradaExt;
    p_fTests[ 29 ] = TestSListaEntradas;
    p_fTests[ 30 ] = TestSListaEntradasExt;
    p_fTests[ 31 ] = TestSListaParametros;
    p_fTests[ 32 ] = TestSListaValores;
    p_fTests[ 33 ] = TestSListaErrores;
    return p_fTests;
}

void freeArrays( char ** p_p_cTests, PFUNINTV* p_fTests )
{
    for ( int i = 0; i < NUM_TESTS; i = i + 1 ) {
        MemLiberar( (void **) &(p_p_cTests[ i ]) );
    }
    MemLiberar( (void **) p_p_cTests );
    MemLiberar( (void **) &p_fTests );
}

int findTest( char ** p_p_cTests, char * p_cTest )
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

int main( int argc, char * argv[] )
{
	int iRes = 0;

	char ** p_p_cTests = testArrayInit();
    PFUNINTV * p_fTests = functionArrayInit();

	printf ( "%s[Inicio de los test]%s\n", ANSI_AZUL, ANSI_RESETEAR );
	char * p_cTest = 0x0;
	if ( argc > 1 )
	{
		p_cTest = argv[1];
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
