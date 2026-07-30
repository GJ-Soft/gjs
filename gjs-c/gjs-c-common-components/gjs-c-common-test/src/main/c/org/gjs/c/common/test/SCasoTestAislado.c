#include "SCasoTestAislado.h"
#include "CTestConfig.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
// #include <fcntl.h>
      

	  

SCasoTestAislado * SCasTstaCrearDef ( const char * p_cId, PFUNINTV p_fTest )
{
	return ( SCasTstaCrear ( p_cId, p_fTest, EXIT_SUCCESS ) );
}

SCasoTestAislado * SCasTstaCrear ( const char * p_cId, PFUNINTV p_fTest, int iCodigoEsperado )
{
	SCasoTestAislado * p_caststaObj;

	if ( CadEsToken ( p_cId ) && ES_VALIDO ( p_fTest ) )
	{
		p_caststaObj = ( SCasoTestAislado * ) MemReservar ( sizeof ( SCasoTestAislado ) );
		if ( ES_VALIDO ( p_caststaObj ) )
		{
			p_caststaObj->p_caststsObj = SCasTstsCrear ( p_cId, p_fTest );
			if ( ES_VALIDO ( p_caststaObj->p_caststsObj ) )
			{
				p_caststaObj->iCodigo = iCodigoEsperado;
			}
			else
			{
				MemLiberar ( (void **) &p_caststaObj );
			}
		}
	}
	else
	{
		p_caststaObj = NULL;
	}
	return ( p_caststaObj );
}


void SCasTstaDestruir ( SCasoTestAislado ** p_p_caststaObj )
{
	SCasoTestAislado * p_caststaObj;

	if ( ES_VALIDO ( p_p_caststaObj ) )
	{
		p_caststaObj = *p_p_caststaObj;
		if ( ES_VALIDO ( p_caststaObj ) )
		{
			SCasTstsDestruir ( &(p_caststaObj->p_caststsObj) );
			MemLiberar ( (void **) p_p_caststaObj );
		}
	}
}

const char * SCasTstaObtenerId ( SCasoTestAislado * p_caststaObj )
{
	const char * p_cRes;

	if ( ES_VALIDO ( p_caststaObj ) )
	{
		p_cRes = SCasTstsObtenerId ( p_caststaObj->p_caststsObj );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SCasTstaEjecutar ( SCasoTestAislado * p_caststaObj )
{
	int iRes;

	if ( ES_VALIDO ( p_caststaObj ) )
	{
		pid_t pid = fork ();
		if ( pid == -1 )
		{
			AplicLogAnotarError ( "No se ha podido lanzar el test. Error=%d", errno );
			iRes = RESULTADO_CASO_TEST_FAIL;
		}
		else if ( pid == 0 )
		{
			// sigset_t   set; 
			// sigemptyset( &set );                                                             
			// sigaddset( &set, SIGUSR1 );                                               
			// sigwait( &set );

			iRes = SCasTstsEjecutar ( p_caststaObj->p_caststsObj );
			AplicLogAnotarAviso ( "El codigo del test ha terminado normalmente: puede que haya que implementarlo como CasoTest normal" );
			if ( iRes == RESULTADO_CASO_TEST_OK )
			{
				exit ( EXIT_SUCCESS );
			}
			else
			{
				exit ( EXIT_FAILURE );
			}
		}
		else
		{
			int iCodigoRecibido = 0;
			// kill( pid, SIGUSR1 );
			waitpid ( pid, &iCodigoRecibido, 0 );
			AplicLogAnotar ( "Proceso terminado con %d", WEXITSTATUS ( iCodigoRecibido ) );
			if ( WEXITSTATUS ( iCodigoRecibido ) == p_caststaObj->iCodigo )
			{
				iRes = RESULTADO_CASO_TEST_OK;
				AplicLogAnotar ( "Caso terminado correctamente" );
			}
			else
			{
				iRes = RESULTADO_CASO_TEST_KO;
				AplicLogAnotarError ( "Caso terminado con error: se esperaba %d", p_caststaObj->iCodigo );
			}
		}
	}
	else
	{
		iRes = RESULTADO_CASO_TEST_FAIL;
	}
	return ( iRes );
}

