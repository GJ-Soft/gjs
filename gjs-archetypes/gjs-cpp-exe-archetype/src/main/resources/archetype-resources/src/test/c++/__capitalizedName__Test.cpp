#set( $symbol_pound = '#' )
#set( $symbol_dollar = '$' )
#set( $symbol_escape = '\' )
#set( $capitalizedName = $shortName.substring(0,1).toUpperCase() + $shortName.substring(1))
#set( $packageNamespace = ${package.replaceAll("\.","::")})

${symbol_pound}include <CppTest.h>




${symbol_pound}define  NOMBRE_MODULO 			"${capitalizedName}"







using namespace std;
using namespace org::gjs::cpp::common;
using namespace org::gjs::cpp::common::test;



#if( $parameters > 0 )
extern int execute${capitalizedName} ( int iNumArgs, char * p_p_cArgs [] );
#else
extern int execute${capitalizedName} ();
#end




static bool Test${capitalizedName}01 ()
{
	cout <<  "Test ${capitalizedName} 01:" << endl;
	bool bRes = true;
	try
	{
#if( $parameters > 0 )
		int iNumArgs = ${parameters};
		char ** p_p_cArgs = new char * [ iNumArgs + 1 ];
		p_p_cArgs [ 0 ] = (char *)string ( "${capitalizedName}.exe" ).c_str(); 
		string sArgumento ( "0" );
		for ( int i = 0; i < iNumArgs; i = i + 1 )
		{
			p_p_cArgs [ i + 1 ] = (char *)sArgumento.c_str(); 
		}
		cout << "Llamando con " << iNumArgs << " argumentos" << endl; 
		if ( execute${capitalizedName} ( iNumArgs + 1, p_p_cArgs ) != 0 )
#else
		cout << "Llamando con sin argumentos" << endl; 
		if ( execute${capitalizedName} () != 0 )
#end	
		{
			cout <<  "Error caso 1" << endl;
			bRes = false;
		}
#if( $parameters > 0 )
		delete[] p_p_cArgs;
#end
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

#if( $parameters > 0 )
static bool Test${capitalizedName}02 ()
{
	cout <<  "Test ${capitalizedName} 02" << endl;
	bool bRes = true;
	try
	{
		int iNumArgs = $parameters;
		char ** p_p_cArgs = new char * [ iNumArgs + 1 ];
		p_p_cArgs [ 0 ] = (char *)string ( "${capitalizedName}.exe" ).c_str (); 
		for ( int i = 0; i < iNumArgs; i = i + 1 )
		{
			p_p_cArgs [ i + 1 ] = (char *)string ( "" ).c_str(); 
		}
		if ( execute${capitalizedName} ( iNumArgs + 1, p_p_cArgs ) == 0 )
		{
			cout <<  "Error caso 1: Se esperaba error" << endl;
			bRes = false;
		}
		delete[] p_p_cArgs;
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
	testModulo->NuevoCasoAislado ( "Test${capitalizedName}01", Test${capitalizedName}01, EXIT_SUCCESS );
#if( $parameters > 0 )
	testModulo->NuevoCasoAislado ( "Test${capitalizedName}02", Test${capitalizedName}02, EXIT_SUCCESS );
#end	
	bRes = testModulo->Ejecutar ();
	delete testModulo;
	return ( bRes );
}
