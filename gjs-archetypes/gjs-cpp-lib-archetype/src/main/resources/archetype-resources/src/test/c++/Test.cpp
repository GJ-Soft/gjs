#set( $symbol_pound = '#' )
#set( $symbol_dollar = '$' )
#set( $symbol_escape = '\' )
#set( $capitalizedName = $shortName.substring(0,1).toUpperCase() + $shortName.substring(1))

${symbol_pound}include <CppTest.h>

${symbol_pound}include "${capitalizedName}.h"

#include <iostream>


using namespace org::gjs::cpp::common;
using namespace std;



extern bool TestSample ();
extern bool TestSampleType ();


int main( int argc, char * argv[] )
{
	int iRes = 0;
	InicializarBase();

	map<string, FUNCION_BOOL> mapTests;
	mapTests[ "Sample" ] = TestSample;
	mapTests[ "SampleType" ] = TestSampleType;
	int iRes = 0;
	InicializarBase();
	EstablecerManejadorInterrupcionesDefecto ();

	SBancoTests * p_banTests = SBanTstCrear ();
	p_banTests->NuevoTest ( "SampleTest", TestSample );
	p_banTests->NuevoTest ( "SampleTypeTest", TestSampleType );

	string sTest ( "null" );
	if ( argc > 1 )
	{
		sTest = argv[ 1 ];
	}
	if ( p_banTests->EjecutarTest ( sTest ) )
	{
		iRes = 0;
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}
