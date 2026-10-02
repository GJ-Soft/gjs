#include <CTest.h>

#if ( ! defined ( WIN ) )
#	include <signal.h>
#	include <unistd.h>
#endif


#define  NOMBRE_MODULO 			"SCasoTestAislado"



static int _CasoDevuelve1 ()
{
	return ( 1 );
}


static int _CasoDevuelve0 ()
{
	printf ( "    (caso que falla a proposito)\n" );
	return ( 0 );
}


static int _CasoSaleConExito ()
{
	printf ( "    (caso que sale con exit ( EXIT_SUCCESS ))\n" );
	exit ( EXIT_SUCCESS );
	return ( 1 );
}


static int _CasoMuertoPorSenal ()
{
	printf ( "    (caso que muere por una senal)\n" );
#if ( ! defined ( WIN ) )
	/* SIGKILL no se puede interceptar, ni siquiera por _TestSignalHandler: el hijo
	   muere sin pasar por exit (). Es el caso que WEXITSTATUS por si solo daba por
	   bueno, porque con un hijo senalizado vale 0, que es EXIT_SUCCESS. */
	kill ( getpid (), SIGKILL );
#endif
	return ( 1 );
}


static int CasoSCasoTestAislado_01 ()
{
	int iRes = 1;
	printf( "Test CasoSCasoTestAislado_01:\n" );

	SCasoTestAislado * p_caso = SCasTstaCrear ( "casoAislado", _CasoDevuelve1, 0 );
	VerificarNoEsNulo ( "crear caso aislado", p_caso, &iRes );
	if ( ES_VALIDO ( p_caso ) )
	{
		VerificarEsCierto ( "id correcto",
			( SCasTstaObtenerId ( p_caso ) != NULL ) && ( strcmp ( SCasTstaObtenerId ( p_caso ), "casoAislado" ) == 0 ), &iRes );
		SCasTstaDestruir ( &p_caso );
	}
	VerificarEsNulo ( "crear con id nulo", SCasTstaCrear ( NULL, _CasoDevuelve1, 0 ), &iRes );
	VerificarEsNulo ( "crear con funcion nula", SCasTstaCrear ( "x", NULL, 0 ), &iRes );
	VerificarEsNulo ( "id de caso nulo", (void *) SCasTstaObtenerId ( NULL ), &iRes );
	return ( iRes );
}


static int CasoSCasoTestAislado_02 ()
{
	int					iRes = 1;
	SCasoTestAislado *	p_caso;

	printf( "Test CasoSCasoTestAislado_02:\n" );

	/* En Windows el caso aislado no se ejecuta: no hay fork (), y por decision de
	   diseno SCasTstaEjecutar lo da por bueno en vez de intentarlo. Asi que alli
	   todos los casos salen OK, incluidos los que aqui fallan. */
#if ( defined ( WIN ) )
	const int	iOk = RESULTADO_CASO_TEST_OK;
	const int	iKo = RESULTADO_CASO_TEST_OK;
#else
	const int	iOk = RESULTADO_CASO_TEST_OK;
	const int	iKo = RESULTADO_CASO_TEST_KO;
#endif

	/* El hijo sale con EXIT_SUCCESS porque la funcion devuelve 1, y es lo esperado. */
	p_caso = SCasTstaCrear ( "aisladoBien", _CasoDevuelve1, EXIT_SUCCESS );
	VerificarValorEntero ( "caso que va bien", SCasTstaEjecutar ( p_caso ), iOk, &iRes );
	SCasTstaDestruir ( &p_caso );

	/* El mismo hijo, pero esperando EXIT_FAILURE: el codigo no coincide. */
	p_caso = SCasTstaCrear ( "aisladoCodigoDistinto", _CasoDevuelve1, EXIT_FAILURE );
	VerificarValorEntero ( "codigo de salida distinto del esperado", SCasTstaEjecutar ( p_caso ), iKo, &iRes );
	SCasTstaDestruir ( &p_caso );

	/* La funcion devuelve 0, asi que el hijo sale con EXIT_FAILURE. */
	p_caso = SCasTstaCrear ( "aisladoFalla", _CasoDevuelve0, EXIT_SUCCESS );
	VerificarValorEntero ( "caso que devuelve 0", SCasTstaEjecutar ( p_caso ), iKo, &iRes );
	SCasTstaDestruir ( &p_caso );

	/* El hijo llama a exit () por su cuenta, sin devolver el control. */
	p_caso = SCasTstaCrear ( "aisladoSaleSolo", _CasoSaleConExito, EXIT_SUCCESS );
	VerificarValorEntero ( "caso que sale con exit ()", SCasTstaEjecutar ( p_caso ), iOk, &iRes );
	SCasTstaDestruir ( &p_caso );

	/* El hijo muere por una senal, sin llegar a salir. WEXITSTATUS vale 0 en ese
	   caso, asi que sin mirar antes WIFSIGNALED se contaba como correcto. */
	p_caso = SCasTstaCrear ( "aisladoMuerto", _CasoMuertoPorSenal, EXIT_SUCCESS );
	VerificarValorEntero ( "caso muerto por una senal", SCasTstaEjecutar ( p_caso ), iKo, &iRes );
	SCasTstaDestruir ( &p_caso );

	VerificarValorEntero ( "ejecutar un caso nulo", SCasTstaEjecutar ( NULL ), RESULTADO_CASO_TEST_FAIL, &iRes );
	return ( iRes );
}


int TestSCasoTestAislado ()
{
	int iRes;

	STest * testModulo = STestCrear ( NOMBRE_MODULO );
	STestNuevoCaso ( testModulo, "CasoSCasoTestAislado_01", CasoSCasoTestAislado_01 );
	STestNuevoCaso ( testModulo, "CasoSCasoTestAislado_02", CasoSCasoTestAislado_02 );

	iRes = STestEjecutar ( testModulo );
	STestDestruir ( &testModulo );
	return ( iRes );
}
