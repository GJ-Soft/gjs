#include "Base.h"

// TODO

#define NUM_TESTS        70

extern int TestSId ();
extern int TestSBloque ();
extern int TestSBuffer ();
extern int TestSElemento ();
extern int TestSLista ();
extern int TestSVector ();
extern int TestSPila ();
extern int TestSCola ();
extern int TestSListaEnteros ();
extern int TestSVectorEnteros ();
extern int TestSVectorFlags ();
extern int TestSListaPtr ();
extern int TestSVectorPtr ();
extern int TestSPilaPtr ();
extern int TestSColaPtr ();
extern int TestSTabla ();
extern int TestSListaOrdenada ();
extern int TestSConjunto ();
extern int TestSRango ();
extern int TestSContador ();
extern int TestSGeneradorId ();
extern int TestSPareja ();
extern int TestSComparador ();
extern int TestSContenido ();
extern int TestSNodoBin ();
extern int TestSArbolBin ();
extern int TestSNodo ();
extern int TestSArbol ();
extern int TestSArbolBinEnteros ();
extern int TestSArbolEnteros ();
extern int TestSNodoPtr ();
extern int TestSArbolPtr ();
extern int TestSNodoBinPtr ();
extern int TestSArbolBinPtr ();
extern int TestSArbolLiterales ();
extern int TestSNodoPorBloques ();
extern int TestSNodoPorBloquesPtr ();
extern int TestSAristaGrafo ();
extern int TestSNodoGrafo ();
extern int TestSGrafo ();
extern int TestSCursor ();
extern int TestSIndicador ();
extern int TestSReferencia ();
extern int TestSIndicador2D ();
extern int TestSMatrizFlags ();
extern int TestSDatos ();
extern int TestSDefDato ();
extern int TestSDefPrimitiva ();
extern int TestSInterfaz ();
extern int TestSSecuencia ();
extern int TestSSecuenciaPtr ();
extern int TestSSecuenciaEnteros ();
extern int TestSSecuenciaEnterosLargos ();
extern int TestSSecuenciaEnterosLargosSinSigno ();
extern int TestSTablaPtr ();
extern int TestSTablaEnteros ();
extern int TestSTablaLiterales ();
extern int TestSConjuntoPtr ();
extern int TestSConjuntoLiterales ();
extern int TestSListaOrdenadaPtr ();
extern int TestSVectorLiterales ();
extern int TestSPilaEnteros ();
extern int TestSListaLiterales ();
extern int TestSListaEnterosLargos ();
extern int TestSListaParejas ();
extern int TestSListaReferencias ();
extern int TestSListaVec ();
extern int TestSElementoPtr ();
extern int TestSPilaLiterales ();
extern int TestSSecuenciaLiterales ();

char ** testArrayInit ()
{
    char ** p_p_cTests = (char **) MemReservar ( NUM_TESTS * sizeof ( char * ) );
    p_p_cTests [ 0 ] = CadDuplicar ( "SId" );
    p_p_cTests [ 1 ] = CadDuplicar ( "SBloque" );
    p_p_cTests [ 2 ] = CadDuplicar ( "SBuffer" );
    p_p_cTests [ 3 ] = CadDuplicar ( "SElemento" );
    p_p_cTests [ 4 ] = CadDuplicar ( "SLista" );
    p_p_cTests [ 5 ] = CadDuplicar ( "SVector" );
    p_p_cTests [ 6 ] = CadDuplicar ( "SPila" );
    p_p_cTests [ 7 ] = CadDuplicar ( "SCola" );
    p_p_cTests [ 8 ] = CadDuplicar ( "SListaEnteros" );
    p_p_cTests [ 9 ] = CadDuplicar ( "SVectorEnteros" );
    p_p_cTests [ 10 ] = CadDuplicar ( "SVectorFlags" );
    p_p_cTests [ 11 ] = CadDuplicar ( "SListaPtr" );
    p_p_cTests [ 12 ] = CadDuplicar ( "SVectorPtr" );
    p_p_cTests [ 13 ] = CadDuplicar ( "SPilaPtr" );
    p_p_cTests [ 14 ] = CadDuplicar ( "SColaPtr" );
    p_p_cTests [ 15 ] = CadDuplicar ( "STabla" );
    p_p_cTests [ 16 ] = CadDuplicar ( "SListaOrdenada" );
    p_p_cTests [ 17 ] = CadDuplicar ( "SConjunto" );
    p_p_cTests [ 18 ] = CadDuplicar ( "SRango" );
    p_p_cTests [ 19 ] = CadDuplicar ( "SContador" );
    p_p_cTests [ 20 ] = CadDuplicar ( "SGeneradorId" );
    p_p_cTests [ 21 ] = CadDuplicar ( "SPareja" );
    p_p_cTests [ 22 ] = CadDuplicar ( "SComparador" );
    p_p_cTests [ 23 ] = CadDuplicar ( "SContenido" );
    p_p_cTests [ 24 ] = CadDuplicar ( "SNodoBin" );
    p_p_cTests [ 25 ] = CadDuplicar ( "SArbolBin" );
    p_p_cTests [ 26 ] = CadDuplicar ( "SNodo" );
    p_p_cTests [ 27 ] = CadDuplicar ( "SArbol" );
    p_p_cTests [ 28 ] = CadDuplicar ( "SArbolBinEnteros" );
    p_p_cTests [ 29 ] = CadDuplicar ( "SArbolEnteros" );
    p_p_cTests [ 30 ] = CadDuplicar ( "SNodoPtr" );
    p_p_cTests [ 31 ] = CadDuplicar ( "SArbolPtr" );
    p_p_cTests [ 32 ] = CadDuplicar ( "SNodoBinPtr" );
    p_p_cTests [ 33 ] = CadDuplicar ( "SArbolBinPtr" );
    p_p_cTests [ 34 ] = CadDuplicar ( "SArbolLiterales" );
    p_p_cTests [ 35 ] = CadDuplicar ( "SNodoPorBloques" );
    p_p_cTests [ 36 ] = CadDuplicar ( "SNodoPorBloquesPtr" );
    p_p_cTests [ 37 ] = CadDuplicar ( "SAristaGrafo" );
    p_p_cTests [ 38 ] = CadDuplicar ( "SNodoGrafo" );
    p_p_cTests [ 39 ] = CadDuplicar ( "SGrafo" );
    p_p_cTests [ 40 ] = CadDuplicar ( "SCursor" );
    p_p_cTests [ 41 ] = CadDuplicar ( "SIndicador" );
    p_p_cTests [ 42 ] = CadDuplicar ( "SReferencia" );
    p_p_cTests [ 43 ] = CadDuplicar ( "SIndicador2D" );
    p_p_cTests [ 44 ] = CadDuplicar ( "SMatrizFlags" );
    p_p_cTests [ 45 ] = CadDuplicar ( "SDatos" );
    p_p_cTests [ 46 ] = CadDuplicar ( "SDefDato" );
    p_p_cTests [ 47 ] = CadDuplicar ( "SDefPrimitiva" );
    p_p_cTests [ 48 ] = CadDuplicar ( "SInterfaz" );
    p_p_cTests [ 49 ] = CadDuplicar ( "SSecuencia" );
    p_p_cTests [ 50 ] = CadDuplicar ( "SSecuenciaPtr" );
    p_p_cTests [ 51 ] = CadDuplicar ( "SSecuenciaEnteros" );
    p_p_cTests [ 52 ] = CadDuplicar ( "SSecuenciaEnterosLargos" );
    p_p_cTests [ 53 ] = CadDuplicar ( "SSecuenciaEnterosLargosSinSigno" );
    p_p_cTests [ 54 ] = CadDuplicar ( "STablaPtr" );
    p_p_cTests [ 55 ] = CadDuplicar ( "STablaEnteros" );
    p_p_cTests [ 56 ] = CadDuplicar ( "STablaLiterales" );
    p_p_cTests [ 57 ] = CadDuplicar ( "SConjuntoPtr" );
    p_p_cTests [ 58 ] = CadDuplicar ( "SConjuntoLiterales" );
    p_p_cTests [ 59 ] = CadDuplicar ( "SListaOrdenadaPtr" );
    p_p_cTests [ 60 ] = CadDuplicar ( "SVectorLiterales" );
    p_p_cTests [ 61 ] = CadDuplicar ( "SPilaEnteros" );
    p_p_cTests [ 62 ] = CadDuplicar ( "SListaLiterales" );
    p_p_cTests [ 63 ] = CadDuplicar ( "SListaEnterosLargos" );
    p_p_cTests [ 64 ] = CadDuplicar ( "SListaParejas" );
    p_p_cTests [ 65 ] = CadDuplicar ( "SListaReferencias" );
    p_p_cTests [ 66 ] = CadDuplicar ( "SListaVec" );
    p_p_cTests [ 67 ] = CadDuplicar ( "SElementoPtr" );
    p_p_cTests [ 68 ] = CadDuplicar ( "SPilaLiterales" );
    p_p_cTests [ 69 ] = CadDuplicar ( "SSecuenciaLiterales" );
    return p_p_cTests;
}

PFUNINTV * functionArrayInit ()
{
    PFUNINTV * p_fTests = (PFUNINTV *) MemReservar ( NUM_TESTS * sizeof ( PFUNINTV ) );
    p_fTests [ 0 ] = TestSId;
    p_fTests [ 1 ] = TestSBloque;
    p_fTests [ 2 ] = TestSBuffer;
    p_fTests [ 3 ] = TestSElemento;
    p_fTests [ 4 ] = TestSLista;
    p_fTests [ 5 ] = TestSVector;
    p_fTests [ 6 ] = TestSPila;
    p_fTests [ 7 ] = TestSCola;
    p_fTests [ 8 ] = TestSListaEnteros;
    p_fTests [ 9 ] = TestSVectorEnteros;
    p_fTests [ 10 ] = TestSVectorFlags;
    p_fTests [ 11 ] = TestSListaPtr;
    p_fTests [ 12 ] = TestSVectorPtr;
    p_fTests [ 13 ] = TestSPilaPtr;
    p_fTests [ 14 ] = TestSColaPtr;
    p_fTests [ 15 ] = TestSTabla;
    p_fTests [ 16 ] = TestSListaOrdenada;
    p_fTests [ 17 ] = TestSConjunto;
    p_fTests [ 18 ] = TestSRango;
    p_fTests [ 19 ] = TestSContador;
    p_fTests [ 20 ] = TestSGeneradorId;
    p_fTests [ 21 ] = TestSPareja;
    p_fTests [ 22 ] = TestSComparador;
    p_fTests [ 23 ] = TestSContenido;
    p_fTests [ 24 ] = TestSNodoBin;
    p_fTests [ 25 ] = TestSArbolBin;
    p_fTests [ 26 ] = TestSNodo;
    p_fTests [ 27 ] = TestSArbol;
    p_fTests [ 28 ] = TestSArbolBinEnteros;
    p_fTests [ 29 ] = TestSArbolEnteros;
    p_fTests [ 30 ] = TestSNodoPtr;
    p_fTests [ 31 ] = TestSArbolPtr;
    p_fTests [ 32 ] = TestSNodoBinPtr;
    p_fTests [ 33 ] = TestSArbolBinPtr;
    p_fTests [ 34 ] = TestSArbolLiterales;
    p_fTests [ 35 ] = TestSNodoPorBloques;
    p_fTests [ 36 ] = TestSNodoPorBloquesPtr;
    p_fTests [ 37 ] = TestSAristaGrafo;
    p_fTests [ 38 ] = TestSNodoGrafo;
    p_fTests [ 39 ] = TestSGrafo;
    p_fTests [ 40 ] = TestSCursor;
    p_fTests [ 41 ] = TestSIndicador;
    p_fTests [ 42 ] = TestSReferencia;
    p_fTests [ 43 ] = TestSIndicador2D;
    p_fTests [ 44 ] = TestSMatrizFlags;
    p_fTests [ 45 ] = TestSDatos;
    p_fTests [ 46 ] = TestSDefDato;
    p_fTests [ 47 ] = TestSDefPrimitiva;
    p_fTests [ 48 ] = TestSInterfaz;
    p_fTests [ 49 ] = TestSSecuencia;
    p_fTests [ 50 ] = TestSSecuenciaPtr;
    p_fTests [ 51 ] = TestSSecuenciaEnteros;
    p_fTests [ 52 ] = TestSSecuenciaEnterosLargos;
    p_fTests [ 53 ] = TestSSecuenciaEnterosLargosSinSigno;
    p_fTests [ 54 ] = TestSTablaPtr;
    p_fTests [ 55 ] = TestSTablaEnteros;
    p_fTests [ 56 ] = TestSTablaLiterales;
    p_fTests [ 57 ] = TestSConjuntoPtr;
    p_fTests [ 58 ] = TestSConjuntoLiterales;
    p_fTests [ 59 ] = TestSListaOrdenadaPtr;
    p_fTests [ 60 ] = TestSVectorLiterales;
    p_fTests [ 61 ] = TestSPilaEnteros;
    p_fTests [ 62 ] = TestSListaLiterales;
    p_fTests [ 63 ] = TestSListaEnterosLargos;
    p_fTests [ 64 ] = TestSListaParejas;
    p_fTests [ 65 ] = TestSListaReferencias;
    p_fTests [ 66 ] = TestSListaVec;
    p_fTests [ 67 ] = TestSElementoPtr;
    p_fTests [ 68 ] = TestSPilaLiterales;
    p_fTests [ 69 ] = TestSSecuenciaLiterales;
    return p_fTests;
}

void freeArrays ( char ** p_p_cTests, PFUNINTV * p_fTests )
{
    for ( int i = 0; i < NUM_TESTS; i = i + 1 ) {
        MemLiberar ( (void **) &( p_p_cTests [ i ] ) );
    }
    MemLiberar ( (void **) p_p_cTests );
    MemLiberar ( (void **) &p_fTests );
}

int findTest ( char ** p_p_cTests, char * p_cTest )
{
    int iIndex = -1;
    int i = 0;
    while ( ( i < NUM_TESTS ) && ( iIndex < 0 ) )
    {
        if ( CadComparar ( p_p_cTests [ i ], p_cTest ) == COMP_IGUAL )
        {
            iIndex = i;
        }
        i = i + 1;
    }
    return ( iIndex );
}

int main ( int argc, char * argv [] )
{
	int iRes = 0;

	char ** p_p_cTests = testArrayInit ();
    PFUNINTV * p_fTests = functionArrayInit ();

	char * p_cTest = 0x0;
	if ( argc > 1 )
	{
		p_cTest = argv [ 1 ];
	}
	if ( CadLongitud ( p_cTest ) > 0 )
	{
	    int iTest = findTest ( p_p_cTests, p_cTest );
		if ( iTest >= 0 )
		{
			PFUNINTV fTest = p_fTests [ iTest ];
			if ( fTest () != 1 )
			{
				iRes = -1;
			}
		}
		else
		{
			printf ( "Test [%s] no encontrado.", p_cTest );
			iRes = -1;
		}
		return ( iRes );
	}

	for ( int iTest = 0; iTest < NUM_TESTS; iTest = iTest + 1 )
	{
		PFUNINTV fTest = p_fTests [ iTest ];
		if ( fTest () != 1 )
		{
			iRes = -1;
		}
	}
	freeArrays ( p_p_cTests, p_fTests );
	return ( iRes );
}
