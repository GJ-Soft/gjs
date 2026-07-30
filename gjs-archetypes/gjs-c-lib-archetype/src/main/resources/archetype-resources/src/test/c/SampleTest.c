#set( $symbol_pound = '#' )
#set( $symbol_dollar = '$' )
#set( $symbol_escape = '\' )
#set( $capitalizedName = $shortName.substring(0,1).toUpperCase() + $shortName.substring(1))
#set( $packageNamespace = ${package.replaceAll("\.","::")})

${symbol_pound}include <CTest.h>

${symbol_pound}include "${capitalizedName}.h"





${symbol_pound}define  NOMBRE_MODULO 			"Sample"




static int TestSample01 ()
{
	printf ( "Test Sample 01:\n" );
	int iRes = 1;

	if ( SmpDoSomething () == 0 )
	{
		printf ( "Error caso 1\n" );
		iRes = 0;
	}
	return( iRes );
}



int TestSample ()
{
	int iRes = 1;

	STest * testModulo = STestCrear ( NOMBRE_MODULO );
	STestNuevoCaso ( testModulo, "TestSample01", TestSample01 );

	iRes = STestEjecutar ( testModulo );
	STestDestruir ( &testModulo );
	return ( iRes );
}
