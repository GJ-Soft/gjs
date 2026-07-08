#include "CasoTestAislado.h"
#include "CppTestConfig.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
// #include <fcntl.h>
                                                            


using namespace std;
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

CasoTestAislado::CasoTestAislado ( const string & sId, FUNCION_BOOL funcion, int iCodigoEsperado ) : CasoTest ( sId, funcion )
{
	iCodigo = iCodigoEsperado;
}

ResultadoCasoTest CasoTestAislado::Ejecutar ()
{
	ResultadoCasoTest rctRes = ResultadoCasoTest::OK;
	pid_t pid = fork();
	if ( pid == -1 )
	{
		LogFatal ( Concatenar( "No se ha podido lanzar el test. Error=", ToString( errno ) ) );
		rctRes = ResultadoCasoTest::FAIL;
	}
	else if ( pid == 0 )
	{
		// sigset_t   set; 
		// sigemptyset( &set );                                                             
		// sigaddset( &set, SIGUSR1 );                                               
		// sigwait( &set );
		
		rctRes = CasoTest::Ejecutar();
		LogAviso ( "El codigo del test ha terminado normalmente: puede que haya que implementarlo como CasoTest normal" );
		if ( rctRes == ResultadoCasoTest::OK )
		{
			exit ( EXIT_SUCCESS );
		}
		else
		{
			exit( EXIT_FAILURE );
		}
	}
	else
	{
		int iCodigoRecibido = 0;
		// kill( pid, SIGUSR1 );
		waitpid( pid, &iCodigoRecibido, 0 ); 
		LogInfo ( Concatenar ( "Proceso terminado con ", ToString( WEXITSTATUS( iCodigoRecibido ) ) ) );
		if ( WEXITSTATUS( iCodigoRecibido ) == iCodigo )
		{
			LogInfo ( "Caso terminado correctamente" );
		}
		else
		{
			rctRes = ResultadoCasoTest::KO;
			LogError ( Concatenar ( "Caso terminado con error: se esperaba ", ToString( iCodigo ) ) );
		}	
	}
	return ( rctRes );
}		

				}
 			}
		}
	}
}
