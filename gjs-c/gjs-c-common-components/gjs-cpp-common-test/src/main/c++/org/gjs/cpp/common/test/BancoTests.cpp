#include "CppTestConfig.h"
#include "BancoTests.h"





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


bool BancoTests::Ejecutar( const string & sTest )
{
	bool bRes = true;
	if ( ( sTest.size() > 0 ) && ( sTest != "null" ) )
	{
		if ( mapTests.exists( sTest ) )
		{
			FUNCION_BOOL fTest = mapTests[ sTest ];
			if( !fTest() )
			{
				bRes = false;
			}
		}
		else
		{
			cerr << "Test [" << sTest << "] no encontrado." << endl;
			bRes = false;
		}
	}
	else
	{
		int iTest = 0;
		while ( iTest < mapTests.size() )
		{
			FUNCION_BOOL fTest = mapTests.at( iTest );
			if( !fTest() )
			{
				bRes = false;
			}
			iTest = iTest + 1;
		}
	}
	return( bRes );
}		

bool BancoTests::Ejecutar ( int argc, char * argv[] )
{
	string sTest( "null" );
	if ( argc > 1 )
	{
		sTest = argv[ 1 ];
	}
	return( Ejecutar( sTest ) );
}

 				}
			}
		}
	}
}
