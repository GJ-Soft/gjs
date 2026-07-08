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


int main ( int argc, char * argv[] )
{
	InicializarBase();
	int iRes = 0;

	map<string, FUNCION_BOOL> mapTests;
	mapTests[ "StringStreamOut" ] = TestStringStreamOut;
	mapTests[ "CaptorSalida" ] = TestCaptorSalida;
	mapTests[ "Simbolos" ] = TestSimbolos;
	mapTests[ "WinHerramientas" ] = TestWinHerramientas;
	mapTests[ "Secuencias" ] = TestSecuencias;
	mapTests[ "Constantes" ] = TestConstantes;
	mapTests[ "Ptr" ] = TestPtr;
	mapTests[ "NodoBin" ] = TestNodoBin;
	mapTests[ "ArbolBin" ] = TestArbolBin;
	mapTests[ "TipoDatos" ] = TestTipoDatos;
	mapTests[ "Tipo" ] = TestTipo;
	mapTests[ "Atributo" ] = TestAtributo;
	mapTests[ "Valor" ] = TestValor;
	mapTests[ "Entidad" ] = TestEntidad;
	mapTests[ "ListaValores" ] = TestListaValores;
	mapTests[ "ConjuntoValores" ] = TestConjuntoValores;
	mapTests[ "Propiedades" ] = TestPropiedades;
	mapTests[ "Contador" ] = TestContador;
	mapTests[ "FicheroFormateado" ] = TestFicheroFormateado;
	mapTests[ "ControlConcurrencia" ] = TestControlConcurrencia;
	mapTests[ "MapaVector" ] = TestMapaVector;


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

	if (! TestStringStreamOut () ||
		! TestCaptorSalida () ||
		! TestSimbolos () ||
		! TestWinHerramientas () ||
		! TestSecuencias () ||
		! TestConstantes () ||
		! TestPtr () ||
		! TestNodoBin () ||
		! TestArbolBin () ||
		! TestTipoDatos () ||
		! TestTipo () ||
		! TestAtributo () ||
		! TestValor () ||
		! TestEntidad () ||
		! TestListaValores () ||
		! TestConjuntoValores () ||
		! TestPropiedades () ||
		! TestContador () ||
		! TestFicheroFormateado() ||
		! TestControlConcurrencia() ||
		! TestMapaVector() )
	{
		iRes = -1;
	}
	fflush ( stdout );
	return ( iRes );
}
