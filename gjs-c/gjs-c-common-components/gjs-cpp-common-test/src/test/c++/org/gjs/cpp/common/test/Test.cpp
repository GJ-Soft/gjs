#include <CppBase.h>

#include <iostream>


using namespace std;
using namespace org::gjs::cpp::common;


extern bool TestCasoTest ();
extern bool TestCasoTestAislado ();
extern bool TestTest ();
extern bool TestUtilesTest ();
extern bool TestBancoTests ();
extern bool TestContextoTest ();



int main ( int argc, char * argv[] )
{
	InicializarBase();
	int iRes = 0;
	EstablecerManejadorInterrupcionesDefecto ();

	map<string, FUNCION_BOOL> mapTests;
	mapTests[ "CasoTestTest" ] = TestCasoTest;
	mapTests[ "CasoTestAisladoTest" ] = TestCasoTestAislado;
	mapTests[ "TestTest" ] = TestTest;
	mapTests[ "UtilesTestTest" ] = TestUtilesTest;
	mapTests[ "BancoTestsTest" ] = TestBancoTests;
	mapTests[ "ContextoTestTest" ] = TestContextoTest;

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
