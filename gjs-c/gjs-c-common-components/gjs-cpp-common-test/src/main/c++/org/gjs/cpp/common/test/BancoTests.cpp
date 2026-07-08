#include "BancoTests.h"
#include "CppTestConfig.h"





using namespace std;
using namespace org::gjs::cpp::common::log;
using namespace org::gjs::cpp::common;


namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {
				namespace test
				{

BancoTests::BancoTests ()
{
}

BancoTests::~BancoTests()
{
	mapTests.clear();
}

void BancoTests::NuevoTest( const string & sNombre, FUNCION_BOOL funcion )
{
	mapTests.push_back( sNombre, funcion );
}

int BancoTests::NumTests()
{
	return ( (int) mapTests.size() );
}


int BancoTests::Ejecutar( const string & sTest )
{
	int iRes = 0;
	if ( sTest.size() > 0 )
	{
		if ( mapTests.exists( sTest ) )
		{
			FUNCION_BOOL fTest = mapTests[ sTest ];
			if( !fTest() )
			{
				iRes = -1;
			}
		}
		else
		{
			cerr << "Test [" << sTest << "] no encontrado." << endl;
			iRes = -1;
		}
	}
	else
	{
		int iTest = 0;
		while ( ( iRes == 0 ) && ( iTest < mapTests.size() ) )
		{
			FUNCION_BOOL fTest = mapTests.at( iTest );
			if( !fTest() )
			{
				iRes = -1;
			}
		}
	}
	return( iRes );
}		

int BancoTests::Ejecutar ( int argc, char * argv[] )
{
	string sTest( "" );
	if ( argc > 1 )
	{
		sTest = argv[1];
	}
	return( Ejecutar( sTest ) );
}

 				}
			}
		}
	}
}
