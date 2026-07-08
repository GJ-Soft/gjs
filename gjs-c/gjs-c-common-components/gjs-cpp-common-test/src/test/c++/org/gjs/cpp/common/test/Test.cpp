#include <CppBase.h>

#include <iostream>


using namespace std;
using namespace org::gjs::cpp::common;


extern bool TestCasoTest ();
extern bool TestCasoTestAislado ();
extern bool TestTest ();
extern bool TestUtilesTest ();
extern bool TestBancoTests ();



int main ( int argc, char * argv[] )
{
	InicializarBase();
	int iRes = 0;
	EstablecerManejadorInterrupcionesDefecto ();

	map<string, FUNCION_BOOL> mapTests;
	mapTests[ "CasoTest" ] = TestCasoTest;
	mapTests[ "CasoTestAislado" ] = TestCasoTestAislado;
	mapTests[ "Test" ] = TestTest;
	mapTests[ "UtilesTest" ] = TestUtilesTest;
	mapTests[ "BancoTests" ] = TestBancoTests;

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
			cerr << "Test [ " << sTest << " ] no encontrado." << endl;
			iRes = -1;
		}
		return( iRes );
	}

	if ( ! TestUtilesTest () ||
		! TestCasoTest () ||
		! TestCasoTestAislado () ||
		! TestTest () )
	{
		iRes = -1;
	}
	fflush ( stdout );
	return ( iRes );
}
