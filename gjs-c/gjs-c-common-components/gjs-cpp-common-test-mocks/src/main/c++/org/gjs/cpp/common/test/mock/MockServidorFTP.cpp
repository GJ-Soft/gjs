#include "CppMockConfig.h"
#include "MockServidorFTP.h"

#include "ContextoTest.h"



using namespace std;
using namespace org::gjs::cpp::common;
using namespace org::gjs::cpp::common::test;
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
                    namespace mock
                    {

MockServidorFTP::MockServidorFTP( int iPuerto, int iPuertoDatos, const string & sSubdirectorioRaiz, const string & sFicheroUsuarios ) :
			/* Las partes relativas se prefijan con "./" porque ResolverDirectorioRelativo
			   solo compone la ruta cuando empieza por "." o ".."; sin el prefijo devolveria
			   el directorio de recursos sin anadir el subdirectorio ni el fichero. */
			ServidorFTP( iPuerto, iPuertoDatos, ResolverDirectorioRelativo( DirectorioTestRecursos(), Concatenar( "./", sSubdirectorioRaiz ) ),
							ResolverDirectorioRelativo( DirectorioTestRecursos(), Concatenar( "./data/", sFicheroUsuarios ) ) )
{
}

MockServidorFTP::~MockServidorFTP()
{
}

void MockServidorFTP::ComandoRecibido( Comando & comando )
{
	LogInfo ( Concatenar( "{SERVIDORFTP} Recibido comando [", comando.toString(), "]" ) );
}

void MockServidorFTP::ComandoProcesado( Comando & comando, bool & bResultado )
{
	LogInfo ( Concatenar( "{SERVIDORFTP} Procesado comando [", comando.toString(), "]" ) );
}

void MockServidorFTP::SesionIniciada( const string & sUsuario )
{
	LogInfo ( Concatenar( "{SERVIDORFTP} Inicio sesion de [", sUsuario, "]" ) );
}

void MockServidorFTP::SesionFinalizada( const string & sUsuario )
{
	LogInfo ( Concatenar( "{SERVIDORFTP} Fin sesion de [", sUsuario, "]" ) );
}

bool MockServidorFTP::ExcepcionProducida( exception & ex )
{
	LogErrorEx ( "{SERVIDORFTP} Excepcion recibida", ex );
	return( true );
}

void MockServidorFTP::ExcepcionProducidaEnPeticion( exception & ex )
{
	LogErrorEx ( "{SERVIDORFTP} Excepcion recibida", ex );
}

                    }
				}
 			}
		}
	}
}
