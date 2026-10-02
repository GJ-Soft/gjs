#set( $symbol_pound = '#' )
#set( $symbol_dollar = '$' )
#set( $symbol_escape = '\' )
#set( $capitalizedName = $shortName.substring(0,1).toUpperCase() + $shortName.substring(1))
#set( $packageNamespace = ${package.replaceAll("\.","::")})
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
extern int execute${capitalizedName} ( const vector <string> & vArgs );
#else
extern int execute${capitalizedName} ();
#end



#if( $parameters > 0 )
int main ( int iNumArgs, char * p_p_cArgs [] )
#else
int main ()
#end
{
#if( $parameters > 0 )
	return ( execute${capitalizedName} ( vector <string> ( p_p_cArgs, p_p_cArgs + iNumArgs ) ) );
#else
	return ( execute${capitalizedName} () );
#end
}



