#set( $symbol_pound = '#' )
#set( $symbol_dollar = '$' )
#set( $symbol_escape = '\' )
#set( $capitalizedName = $shortName.substring(0,1).toUpperCase() + $shortName.substring(1))
#set( $packageNamespace = ${package.replaceAll("\.","::")})

${symbol_pound}include <CppTest.h>

${symbol_pound}include "${capitalizedName}.h"



#define  NOMBRE_MODULO 			"Sample"



using namespace ${packageNamespace};
using namespace org::gjs::cpp::common;
using namespace org::gjs::cpp::common::test;
using namespace std;




static bool TestSample01 ()
{
	cout << "Test Sample 01:" << endl;
	bool bRes = true;

	try
	{
		if ( !SmpDoSomething () )
		{
			cout << "Error caso 1" << endl;
			bRes = false;
		}
	}
	catch ( exception & ex )
	{
		cout << "Se ha producido una excepcion :" << ex.what () << endl;
		bRes = false;
	}
	catch ( ... )
	{
		cout << "Excepcion indefinida" << endl;
		bRes = false;
	}
	return( bRes );
}



bool TestSample ()
{
	bool bRes = true;

	Test * testModulo = new Test ( NOMBRE_MODULO );
	testModulo->NuevoCaso ( "TestSample01", TestSample01 );

	bRes = testModulo->Ejecutar ();
	delete testModulo;
	return ( bRes );
}
