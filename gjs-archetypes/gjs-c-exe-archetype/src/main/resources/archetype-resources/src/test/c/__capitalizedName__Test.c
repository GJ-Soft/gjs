#set( $symbol_pound = '#' )
#set( $symbol_dollar = '$' )
#set( $symbol_escape = '\' )
#set( $capitalizedName = $shortName.substring(0,1).toUpperCase() + $shortName.substring(1))
#set( $packageNamespace = ${package.replaceAll("\.","::")})

${symbol_pound}include <CTest.h>




#define  NOMBRE_MODULO 			"${capitalizedName}"










static int Test${capitalizedName}01 ()
{
	printf ( "Test ${capitalizedName} 01:\n" );
	int iRes = 1;

# if( $parameters > 0 )
	int iNumArgs = $parameters;
	char * p_p_cArgs [] = MemReservar ( ( iNumArgs + 1 ) * sizeof ( char * ) );
	p_p_cArgs [ 0 ] = CadDuplicar ( "${capitalizedName}.exe" ); 
	for ( int i = 0; i < iNumArgs; i = i + 1 )
	{
		p_p_cArgs [ i + 1 ] = CadDuplicar ( "0" ); 
	}
	if ( main ( iNumArgs, p_p_cArgs [] ) != 0 )
#else
	if ( main () != 0 )
#end	
	{
		printf ( "Error caso 1\n" );
		iRes = 0;
	}
# if( $parameters > 0 )
	for ( int i = 0; i < iNumArgs + 1; i = i + 1 )
	{
		MemLiberarCadena ( &(p_p_cArgs [ i ]) ); 
	}
#end	
	return( iRes );
}

# if( $parameters > 0 )
static int Test${capitalizedName}02 ()
{
	printf ( "Test ${capitalizedName} 02:\n" );
	int iRes = 1;

	int iNumArgs = $parameters;
	char * p_p_cArgs [] = MemReservar ( ( iNumArgs + 1 ) * sizeof ( char * ) );
	p_p_cArgs [ 0 ] = CadDuplicar ( "${capitalizedName}.exe" ); 
	for ( int i = 0; i < iNumArgs; i = i + 1 )
	{
		p_p_cArgs [ i + 1 ] = CadDuplicar ( "" ); 
	}
	if ( main ( iNumArgs, p_p_cArgs [] ) != 0 )
	{
		printf ( "Error caso 1\n" );
		iRes = 0;
	}
	for ( int i = 0; i < iNumArgs + 1; i = i + 1 )
	{
		MemLiberarCadena ( &(p_p_cArgs [ i ]) ); 
	}
	return( iRes );
}
#end	



int Test${capitalizedName} ()
{
	int iRes = 1;

	STest * testModulo = STestCrear ( NOMBRE_MODULO );
	STestNuevoCasoAislado ( testModulo, "Test${capitalizedName}01", Test${capitalizedName}01 );
# if( $parameters > 0 )
	STestNuevoCasoAislado ( testModulo, "Test${capitalizedName}02", Test${capitalizedName}02 );
#end	

	iRes = STestEjecutar ( testModulo );
	STestDestruir ( &testModulo );
	return ( iRes );
}
