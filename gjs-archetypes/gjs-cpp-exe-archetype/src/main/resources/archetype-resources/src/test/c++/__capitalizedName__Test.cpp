#set( $symbol_pound = '#' )
#set( $symbol_dollar = '$' )
#set( $symbol_escape = '\' )
#set( $capitalizedName = $shortName.substring(0,1).toUpperCase() + $shortName.substring(1))
#set( $packageNamespace = ${package.replaceAll("\.","::")})

${symbol_pound}include <CppTest.h>

${symbol_pound}include <iostream>



using namespace std;
using namespace org::gjs::cpp::common;
using namespace org::gjs::cpp::common::test;



${symbol_pound}define  NOMBRE_MODULO 			"${capitalizedName}"


#if( $parameters > 0 )
extern int execute${capitalizedName} ( const vector<string> & vArgs );
#else
extern int execute${capitalizedName} ();
#end



static bool Test${capitalizedName}01 ()
{
	cout << "Test ${capitalizedName} 01:" << endl;
	bool bRes = true;

#if( $parameters > 0 )
	/* El vector imita a argv: el nombre del programa y despues los parametros. */
	int iNumArgs = ${parameters};
	vector<string> vecArgs ( iNumArgs + 1 );

	vecArgs [ 0 ] = "${capitalizedName}.exe";
	for ( int i = 0; i < iNumArgs; i = i + 1 )
	{
		vecArgs [ i + 1 ] = "0";
	}
	cout << "Llamando con " << iNumArgs << " argumentos" << endl;
	if ( execute${capitalizedName} ( vecArgs ) != 0 )
#else
	cout << "Llamando sin argumentos" << endl;
	if ( execute${capitalizedName} () != 0 )
#end
	{
		cout << "Error caso 1" << endl;
		bRes = false;
	}
	return( bRes );
}

#if( $parameters > 0 )
static bool Test${capitalizedName}02 ()
{
	cout << "Test ${capitalizedName} 02" << endl;
	bool bRes = true;

	/* Los mismos parametros pero vacios: se espera que el programa los rechace. */
	int iNumArgs = ${parameters};
	vector<string> vecArgs ( iNumArgs + 1 );

	vecArgs [ 0 ] = "${capitalizedName}.exe";
	for ( int i = 0; i < iNumArgs; i = i + 1 )
	{
		vecArgs [ i + 1 ] = "";
	}
	if ( execute${capitalizedName} ( vecArgs ) == 0 )
	{
		cout << "Error caso 1: Se esperaba error" << endl;
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
