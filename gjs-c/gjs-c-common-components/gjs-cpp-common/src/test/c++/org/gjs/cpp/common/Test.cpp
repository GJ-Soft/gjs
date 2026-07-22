#include "CppCommon.h"


using namespace org::gjs::cpp::common;
using namespace std;


extern bool TestExcepcion ();
extern bool TestArgumentos ();
extern bool TestMensajes ();
extern bool TestEntorno ();
extern bool TestAplicacionLog ();


int main( int argc, char * argv[] )
{
	int iRes = 0;
	InicializarBase();

	map<string, FUNCION_BOOL> mapTests;
	mapTests[ "ExcepcionTest" ] = TestExcepcion;
	mapTests[ "ArgumentosTest" ] = TestArgumentos;
	mapTests[ "MensajesTest" ] = TestMensajes;
	mapTests[ "EntornoTest" ] = TestEntorno;
	mapTests[ "AplicacionLogTest" ] = TestAplicacionLog;

	string sTest( "null" );
	if ( argc > 1 )
	{
		sTest = argv[1];
	}
	if ( ( sTest.size() > 0 ) && ( sTest.compare( "null" ) != 0 ) )
	{
		if ( mapTests.find( sTest ) != mapTests.end() )
		{
			FUNCION_BOOL fTest = mapTests[ sTest ];
			if( !fTest() )
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
	return ( iRes );
}
