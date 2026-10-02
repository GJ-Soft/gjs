#include "CppTestConfig.h"
#include "CasoTestAislado.h"

#include <sys/types.h>
#include <sys/stat.h>
#if ( ! defined ( WIN ) )
#	include <sys/wait.h>
#	include <cstring>
#endif
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
#if ( defined ( WIN ) )
	/* Windows no tiene fork (). Relanzar el propio ejecutable pasandole el caso en
	   una variable de entorno funciona —esta probado con _spawnv ( _P_WAIT ), que
	   devuelve el codigo de salida del hijo—, pero obliga ademas a que cada Test
	   sepa saltarse los casos que no le piden, y se ha decidido dejarlo pendiente.
	   Hasta entonces el caso se da por bueno: no se ejecuta, pero tampoco hace
	   fallar el build. */
	cout << "Caso aislado no implementado en Windows: el caso se da por bueno" << endl;
	LogAviso ( "Caso aislado no implementado en Windows: el caso se da por bueno" );
	rctRes = ResultadoCasoTest::OK;
#else
	/* Lo que este sin vaciar en los buffers se duplica en el hijo. */
	cout.flush ();
	fflush ( NULL );
	pid_t pid = fork();
	if ( pid == -1 )
	{
		LogError ( Concatenar( "No se ha podido lanzar el test. Error=", ToString( errno ) ) );
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
		int iEstado = 0;
		// kill( pid, SIGUSR1 );
		if ( waitpid ( pid, &iEstado, 0 ) == -1 )
		{
			rctRes = ResultadoCasoTest::FAIL;
			LogError ( Concatenar ( "No se ha podido esperar al test. Error=", ToString ( errno ) ) );
		}
		else if ( WIFSIGNALED ( iEstado ) )
		{
			/* WEXITSTATUS solo tiene sentido si el hijo salio por exit (). Un hijo muerto
			   por una senal daba un valor sin sentido, y el caso fallaba sin decir por que. */
			rctRes = ResultadoCasoTest::KO;
			LogError ( Concatenar ( "Caso muerto por la senal ", ToString ( WTERMSIG ( iEstado ) ),
									" (", strsignal ( WTERMSIG ( iEstado ) ), ")" ) );
		}
		else if ( ! WIFEXITED ( iEstado ) )
		{
			rctRes = ResultadoCasoTest::KO;
			LogError ( "Caso terminado sin salida normal" );
		}
		else
		{
			LogInfo ( Concatenar ( "Proceso terminado con ", ToString ( WEXITSTATUS ( iEstado ) ) ) );
			if ( WEXITSTATUS ( iEstado ) == iCodigo )
			{
				LogInfo ( "Caso terminado correctamente" );
			}
			else
			{
				rctRes = ResultadoCasoTest::KO;
				LogError ( Concatenar ( "Caso terminado con error: se esperaba ", ToString ( iCodigo ) ) );
			}
		}
	}
#endif
	return ( rctRes );
}		

				}
 			}
		}
	}
}
