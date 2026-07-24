#set( $symbol_pound = '#' )
#set( $symbol_dollar = '$' )
#set( $symbol_escape = '\' )
#set( $capitalizedName = $shortName.substring(0,1).toUpperCase() + $shortName.substring(1))
#set( $packageNamespace = ${package.replaceAll("\.","::")})

${symbol_pound}include <CppTest.h>




#define  NOMBRE_MODULO 			"${capitalizedName}"







using namespace ${packageNamespace};
using namespace org::gjs::cpp::common;
using namespace org::gjs::cpp::common::test;
using namespace std;






static bool Test${capitalizedName}01 ()
{
	cout <<  "Test ${capitalizedName} 01:" << endl;
	bool bRes = true;
	try
	{
# if( $parameters > 0 )
		int iNumArgs = $parameters;
		char * p_p_cArgs [] = MemReservar ( ( iNumArgs + 1 ) * sizeof ( char * ) );
		p_p_cArgs [ 0 ] = string ( "${capitalizedName}.exe" ).c_str(); 
		for ( int i = 0; i < iNumArgs; i = i + 1 )
		{
			p_p_cArgs [ i + 1 ] = string ( "0" ).c_str(); 
		}
		if ( main ( iNumArgs, p_p_cArgs [] ) != 0 )
#else
		if ( main () != 0 )
#end	
		{
			cout <<  "Error caso 1" << endl;
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

# if( $parameters > 0 )
static bool Test${capitalizedName}02 ()
{
	cout <<  "Test ${capitalizedName} 02" << endl;
	bool bRes = true;
	try
	{
		int iNumArgs = $parameters;
		char * p_p_cArgs [] = MemReservar ( ( iNumArgs + 1 ) * sizeof ( char * ) );
		p_p_cArgs [ 0 ] = string ( "${capitalizedName}.exe" ).c_str (); 
		for ( int i = 0; i < iNumArgs; i = i + 1 )
		{
			p_p_cArgs [ i + 1 ] = string ( "" ).c_str(); 
		}
		if ( main ( iNumArgs, p_p_cArgs [] ) != 0 )
		{
			cout <<  "Error caso 1" << endl;
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
#end	



bool Test${capitalizedName} ()
{
	bool bRes = true;

	Test * testModulo = new Test ( NOMBRE_MODULO );
	testModulo->NuevoCasoAislado ( "Test${capitalizedName}01", Test${capitalizedName}01 );
# if( $parameters > 0 )
	testModulo->NuevoCasoAislado ( "Test${capitalizedName}02", Test${capitalizedName}02 );
#end	
	bRes = testModulo->Ejecutar ();
	delete testModulo;
	return ( bRes );
}
