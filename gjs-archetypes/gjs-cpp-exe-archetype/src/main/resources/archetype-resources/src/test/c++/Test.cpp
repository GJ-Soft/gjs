#set( $symbol_pound = '#' )
#set( $symbol_dollar = '$' )
#set( $symbol_escape = '\' )
#set( $capitalizedName = $shortName.substring(0,1).toUpperCase() + $shortName.substring(1))

${symbol_pound}include <CppTest.h>

${symbol_pound}include <iostream>



using namespace std;
using namespace org::gjs::cpp::common;
using namespace org::gjs::cpp::common::test;



extern bool Test${capitalizedName} ();




int main( int argc, char * argv[] )
{
	int iRes = 0;
	EntInicializar ( true, "Test${capitalizedName}", 1, 0 );
	EstablecerManejadorInterrupcionesDefecto ();

	BancoTests * p_banTests = new BancoTests ();
	p_banTests->NuevoTest ( "${capitalizedName}Test", Test${capitalizedName} );

	string sTest ( "null" );
	if ( argc > 1 )
	{
		sTest = argv[ 1 ];
	}
	if ( p_banTests->Ejecutar ( sTest ) )
	{
		iRes = 0;
	}
	else
	{
		iRes = -1;
	}
	delete p_banTests;
	EntFinalizar ();
	return ( iRes );
}
