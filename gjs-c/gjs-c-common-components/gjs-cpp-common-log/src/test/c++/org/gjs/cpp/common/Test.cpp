#include <CppBase.h>



#include <iostream>

#include <Log.h>


using namespace std;
using namespace org::gjs::cpp::common;

extern bool TestMDC ();
extern bool TestLog ();


int main ( int argc, char * argv[] )
{
	InicializarBase();
	int iRes = 0;

	map<string, FUNCION_BOOL> mapTests;
	mapTests[ "MDCTest" ] = TestMDC;
	mapTests[ "LogTest" ] = TestLog;

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
		/* Ya no hay log4cxx: LogFin suelta los appenders. */
		log::LogFin ();
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
	log::LogFin ();
	fflush ( stdout );
	return ( iRes );
}
