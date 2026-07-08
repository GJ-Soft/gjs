#include <CppBase.h>

#include <iostream>

using namespace std;
using namespace org::gjs::cpp::common;


extern bool TestMockServidorFTP ();



int main ( int argc, char * argv[] )
{
	InicializarBase();
	int iRes = 0;
	EstablecerManejadorInterrupcionesDefecto ();

	map<string, FUNCION_BOOL> mapTests;
	mapTests[ "MockServidorFTP" ] = TestMockServidorFTP;

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

	if ( ! TestMockServidorFTP () )
	{
		iRes = -1;
	}
	fflush ( stdout );
	return ( iRes );
}
