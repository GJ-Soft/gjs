#set( $symbol_pound = '#' )
#set( $symbol_dollar = '$' )
#set( $symbol_escape = '\' )
#set( $capitalizedName = $shortName.substring(0,1).toUpperCase() + $shortName.substring(1))
#set( $includeConfig = "${capitalizedName}Config.h")
#set($cleanVersion = $version.split("-")[0])
#set($parts = $cleanVersion.split("."))
#if($parts.size() > 0)
  #set($major = $parts[0])
#else
  #set($major = "1" )
#end
#if($parts.size() > 1)
  #set($minor = $parts[1])
#else
  #set($minor = "0" )
#end
#if($parts.size() > 2)
  #set($patch = $parts[2])
#else
  #set($patch = "0" )
#end


${symbol_pound}include "${includeConfig}"


using namespace std;
using namespace org::gjs::cpp::common;
using namespace org::gjs::cpp::common::log;


#if( $parameters > 0 )
static bool validateArgument ( int iArg, string sArg );
#end

#if( $parameters > 0 )
int execute${capitalizedName} ( const vector <string> & vArgs )
#else
int execute${capitalizedName} ()
#end
{
	int					iRes;
#if( $parameters > 0 )
	Argumentos	*		p_argParametros;
#end

	EntInicializar ( true, "${shortName}", ${major}, ${minor}, ${patch} );
#if( $log.equals( "y" )	)
	LogIni( "/log4cxx.xml" );
#end

	iRes = EXIT_SUCCESS;
#if( $parameters > 0 )
	p_argParametros = new Argumentos ( vArgs );
	if ( ES_VALIDO ( p_argParametros ) )
	{
		if ( p_argParametros->NumArgumentos () == ${parameters} )
		{
			for ( int iArg = 0; iArg < p_argParametros->NumArgumentos (); iArg = iArg + 1 )
			{
				if ( !validateArgument ( iArg, p_argParametros->Argumento ( iArg ) ) )
				{
					cout << format( "Invalid argument {} (Value={}).", iArg,  
							p_argParametros->Argumento ( iArg ) ) << endl; 
					iRes = EXIT_FAILURE;
				}
			}
		}
		else
		{
			cout << "Invalid number of arguments." << endl;
			//TODO
			cout << "Use: ${shortName} <Param1> ..." << endl;
			iRes = EXIT_FAILURE;
		}

		delete p_argParametros;
	}
	else
	{
		cout << "Se han producido un error al procesar los parametros." << endl;
		iRes = EXIT_FAILURE;
	}
#end

	if ( iRes == EXIT_SUCCESS )
	{
		// TODO: Add source main code
	}
	
#if( $log.equals( "y" )	)
	LogFin();
#end
	EntFinalizar ();
	return ( iRes );
}

#if( $parameters > 0 )
static bool validateArgument ( int iArg, string sArg )
{
	bool bRes = false;
	switch ( iArg ) 
	{
#foreach($i in [1..$parameters])
#set( $iCase = $i - 1 )
			case ${iCase}:
				// TODO
				bRes = !sArg.empty();
				break;
#end				
	}
	return ( bRes );
}
#end		 
	




