#set( $symbol_pound = '#' )
#set( $symbol_dollar = '$' )
#set( $symbol_escape = '\' )
#set( $capitalizedName = $shortName.substring(0,1).toUpperCase() + $shortName.substring(1))
#set( $packageNamespace = ${package.replaceAll("\.","::")})

${symbol_pound}include <CppTest.h>

${symbol_pound}include "${capitalizedName}.h"




${symbol_pound}define  NOMBRE_MODULO 			"SampleType"



using namespace std;
using namespace org::gjs::cpp::common;
using namespace org::gjs::cpp::common::test;
using namespace ${packageNamespace};





static bool TestSampleType01 ()
{
	cout << "Test SampleType 01:" << endl;
	bool bRes = true;

	try
	{
		SampleType * ejemplo = new SampleType();
		if ( !ejemplo->IsValid() )
		{
			cout << "Error caso 1" << endl;
			bRes = false;
		}
		delete ejemplo;
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



bool TestSampleType ()
{
	bool bRes = true;

	Test * testModulo = new Test ( NOMBRE_MODULO );
	testModulo->NuevoCaso ( "TestSampleType01", TestSampleType01 );

	bRes = testModulo->Ejecutar ();
	delete testModulo;
	return ( bRes );
}
