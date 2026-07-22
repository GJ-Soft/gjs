#include "CppCommonTypes.h"

#include <map>


using namespace std;


extern bool TestToString ();
extern bool TestToInt ();
extern bool TestConcatenar ();
extern bool TestExcepcion ();
extern bool TestSistema ();
extern bool TestFicheros ();
extern bool TestColecciones ();
extern bool TestStringStreamOut ();
extern bool TestCaptorSalida ();
extern bool TestSimbolos ();
extern bool TestWinHerramientas ();
extern bool TestCadenas ();
extern bool TestSecuencias ();
extern bool TestConstantes ();
extern bool TestIToString ();
extern bool TestIComparable ();
extern bool TestPtr ();
extern bool TestHayError();
extern bool TestNodoBin ();
extern bool TestArbolBin ();
extern bool TestTipoDatos ();
extern bool TestTipo ();
extern bool TestAtributo ();
extern bool TestValor ();
extern bool TestEntidad ();
extern bool TestListaValores ();
extern bool TestConjuntoValores ();
extern bool TestPropiedades();
extern bool TestContador();
extern bool TestFicheroFormateado();
extern bool TestControlConcurrencia();
extern bool TestMapaVector();
extern bool TestCalculo();
extern bool TestMemoriaGlobal();


int main ( int argc, char * argv[] )
{
	InicializarBase();
	int iRes = 0;

	map<string, FUNCION_BOOL> mapTests;
	mapTests[ "StringStreamOutTest" ] = TestStringStreamOut;
	mapTests[ "CaptorSalidaTest" ] = TestCaptorSalida;
	mapTests[ "SimbolosTest" ] = TestSimbolos;
	mapTests[ "WinHerramientasTest" ] = TestWinHerramientas;
	mapTests[ "SecuenciasTest" ] = TestSecuencias;
	mapTests[ "ConstantesTest" ] = TestConstantes;
	mapTests[ "PtrTest" ] = TestPtr;
	mapTests[ "NodoBinTest" ] = TestNodoBin;
	mapTests[ "ArbolBinTest" ] = TestArbolBin;
	mapTests[ "TipoDatosTest" ] = TestTipoDatos;
	mapTests[ "TipoTest" ] = TestTipo;
	mapTests[ "AtributoTest" ] = TestAtributo;
	mapTests[ "ValorTest" ] = TestValor;
	mapTests[ "EntidadTest" ] = TestEntidad;
	mapTests[ "ListaValoresTest" ] = TestListaValores;
	mapTests[ "ConjuntoValoresTest" ] = TestConjuntoValores;
	mapTests[ "PropiedadesTest" ] = TestPropiedades;
	mapTests[ "ContadorTest" ] = TestContador;
	mapTests[ "FicheroFormateadoTest" ] = TestFicheroFormateado;
	mapTests[ "ControlConcurrenciaTest" ] = TestControlConcurrencia;
	mapTests[ "MapaVectorTest" ] = TestMapaVector;
	mapTests[ "CalculoTest" ] = TestCalculo;
	mapTests[ "MemoriaGlobalTest" ] = TestMemoriaGlobal;


	string sTest ( "null" );
	if ( argc > 1 )
	{
		sTest = argv[1];
	}
	if ( ( sTest.size() > 0 ) && ( sTest.compare( "null" ) != 0 ) )
	{
		if ( mapTests.find( sTest ) != mapTests.end() )
		{
			FUNCION_BOOL fTest = mapTests[ sTest ];
			if( !fTest () )
			{
				iRes = -1;
			}
		}
		else
		{
			cerr << "Test [" << sTest << "] no encontrado." << endl;
			iRes = -1;
		}
		return( iRes );
	}


	for ( auto it = mapTests.begin(); it != mapTests.end(); ++it )
	{
		FUNCION_BOOL fTest = it->second;
		if( fTest () != 1 )
		{
			iRes = -1;
		}
	}
	fflush ( stdout );
	return ( iRes );
}
