#set( $symbol_pound = '#' )
#set( $symbol_dollar = '$' )
#set( $symbol_escape = '\' )
#set( $capitalizedName = $shortName.substring(0,1).toUpperCase() + $shortName.substring(1))
#set( $packageNamespace = ${package.replaceAll("\.","::")})

${symbol_pound}include <CTest.h>

${symbol_pound}include "${capitalizedName}.h"



#define  NOMBRE_MODULO 			"SampleType"



static int TestSampleType01 ()
{
	printf ( "Test SampleType 01:\n" );
	int iRes = 1;

	SampleType * ejemplo = SmpCrear ();
	if ( SmpEsValido ( ejemplo ) == 0 )
	{
		printf ( "Error caso 1\n" );;
		iRes = 0;
	}
	SmpDestruir ( &ejemplo );
	return( iRes );
}



int TestSampleType ()
{
	int iRes = 1;

	STest * testModulo = STestCrear ( NOMBRE_MODULO );
	STestNuevoCaso ( testModulo, "TestSampleType01", TestSampleType01 );

	iRes = STestEjecutar ( testModulo );
	STestDestruir ( &testModulo );
	return ( iRes );
}
