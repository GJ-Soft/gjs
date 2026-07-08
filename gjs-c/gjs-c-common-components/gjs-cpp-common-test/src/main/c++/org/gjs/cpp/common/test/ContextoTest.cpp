#include "ContextoTest.h"
#include "CppTestConfig.h"


using namespace std;
using namespace org::gjs::cpp::common;
using namespace org::gjs::cpp::common::log;


namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {
				namespace test
				{

#define TEST_FIC_PROPIEDADES	"../internal/test.properties"

		
		
static Propiedades * propContexto = NULL;		



void _PrepararContexto()
{
	if ( propContexto == NULL )
	{
		propContexto = new Propiedades( TEST_FIC_PROPIEDADES );	

	}
}	

void _LiberarContexto()
{
	if ( propContexto != NULL )
	{
		delete propContexto;	
		propContexto = NULL;
	}
}	
		
string DirectorioProyecto()
{
	string sDir;
	if ( propContexto != NULL )
	{
		if ( propContexto->ExistePropiedad( "project.basedir" ) )
		{
			sDir = propContexto->getPropiedad( "project.basedir" );
		}
	}
	if ( sDir.size() == 0 )
	{
		sDir = ResolverDirectorioRelativo( DirectorioActual(), "../../.." );
	}
	return( sDir );
}

string DirectorioTrabajo()
{
	string sDir;
	if ( propContexto != NULL )
	{
		if ( propContexto->ExistePropiedad( "project.build.directory" ) )
		{
			sDir = propContexto->getPropiedad( "project.build.directory" );
		}
	}
	if ( sDir.size() == 0 )
	{
		sDir = ResolverDirectorioRelativo( DirectorioActual(), "../.." );
	}
	return( sDir );
}
				
string DirectorioTest()
{
	string sDir = "..";
	if ( propContexto != NULL )
	{
		if ( propContexto->ExistePropiedad( "project.build.testDirectory" ) )
		{
			sDir = propContexto->getPropiedad( "project.build.testDirectory" );
		}
	}
	if ( sDir.size() == 0 )
	{
		sDir = ResolverDirectorioRelativo( DirectorioActual(), ".." );
	}
	return( sDir );
}

string DirectorioTestRecursos()
{
	return( ResolverDirectorioRelativo( DirectorioTest(), "resources" ) );
}

string DirectorioTestResultados()
{
	return( ResolverDirectorioRelativo( DirectorioTest(), "results" ) );
}

				}
 			}
		}
	}
}
