#include "CTestConfig.h"




// TODO: Cuando uun caso aislado sale con un exit(0) y algo falla que provoca que no se controle esa salida, 
// Maven se piensa que el test ha ido bien: Hace falta un mecanismo para distinguir al salir cuando ha finalizado o no el test 

//static bool __bEjecutandoTest = false;

/*

		// TODO: proteger con test&set o semaforo
void IniTest()
{
	__bEjecutandoTest = true;
}	

void FinTest()
{
	__bEjecutandoTest = false;
}	
*/
__attribute__((destructor)) void Finalizacion () 
{
	SisConAsincEscribir ( TEST_MSJ_FINALIZADO );
	/*
	if ( __bEjecutandoTest )
	{
		LogError( "Un proceso de test ha finalizado con exit() no controlado." );
		__bEjecutandoTest = false;
		exit( EXIT_FAILURE );
	}
	else
	{
	LogInfo( "Un proceso ha finalizado." );
	//}
	*/
}
