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




#if( $parameters > 0 )
static int validateArgument ( int iArg, const char * p_cArg );
#end



#if( $parameters > 0 )
int execute${capitalizedName} ( int iNumArgs, char * p_p_cArgs [] )
#else
int execute${capitalizedName} ()
#end
{
	int					iRes;
#if( $parameters > 0 )
	SArgumentos	*		p_argParametros;
#end

	EntInicializar ( 1, "${shortName}", ${major}, ${minor} );
#if( $log.equals( "y" )	)
	AplicLogInicializar ( EntDirectorioLog (), "${capitalizedName}.log" );
#end                                               

	iRes = EXIT_SUCCESS;
#if( $parameters > 0 )
	p_argParametros = SArgCrear ( iNumArgs, p_p_cArgs );
	if ( ES_VALIDO ( p_argParametros ) )
	{
		if ( SArgNumArgumentos ( p_argParametros ) == ${parameters} )
		{
			for ( int iArg = 0; iArg < SArgNumArgumentos ( p_argParametros ); iArg = iArg + 1 )
			{
				if ( validateArgument ( iArg, SArgArgumento ( p_argParametros, iArg ) ) == 0 )
				{
					printf ( "Invalid argument %d (Value=%s).\n", iArg,  
							SArgArgumento ( p_argParametros, iArg ) ); 
					iRes = EXIT_FAILURE;
				}
			}
		}
		else
		{
			printf ( "Invalid number of arguments: %d.\n", SArgNumArgumentos ( p_argParametros ) );
			//TODO
			printf ( "Use: ${shortName} <Param1> ...\n" );
			iRes = EXIT_FAILURE;
		}

		SArgDestruir (  &p_argParametros );
	}
	else
	{
		printf ( "Se han producido un error al procesar los parametros.\n" );
		iRes = EXIT_FAILURE;
	}
#end

	if ( iRes == EXIT_SUCCESS )
	{
		// TODO: Add source main code
	}
	
#if( $log.equals( "y" )	)
	AplicLogFinalizar( NULL );
#end
	EntFinalizar ();
	return ( iRes );
}

#if( $parameters > 0 )
static int validateArgument ( int iArg, const char * p_cArg )
{
	int iRes = 1;
	switch ( iArg ) 
	{
#foreach($i in [0..$parameters])
			case $i:
				// TODO
				if ( CadEstaVacia( p_cArg ) == 1 ) 
				{
					iRes = 0;
				}
				break;
#end				
	}
	return ( iRes );
}
#end		 





