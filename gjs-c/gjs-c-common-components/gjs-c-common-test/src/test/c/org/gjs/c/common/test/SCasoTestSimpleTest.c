#include <CTest.h>


#define  NOMBRE_MODULO 			"SCasoTestSimple"



static int _CasoDevuelve1 ()
{
	return ( 1 );
}

static int _CasoDevuelve0 ()
{
	return ( 0 );
}


static int CasoSCasoTestSimple_01 ()
{
	int iRes = 1;
	printf( "Test CasoSCasoTestSimple_01:\n" );

	SCasoTestSimple * p_caso = SCasTstsCrear ( "casoOk", _CasoDevuelve1 );
	VerificarNoEsNulo ( "crear caso simple", p_caso, &iRes );
	if ( ES_VALIDO ( p_caso ) )
	{
		VerificarEsCierto ( "id correcto",
			( SCasTstsObtenerId ( p_caso ) != NULL ) && ( strcmp ( SCasTstsObtenerId ( p_caso ), "casoOk" ) == 0 ), &iRes );
		/* Una funcion que devuelve 1 se mapea a RESULTADO_CASO_TEST_OK. */
		VerificarValorEntero ( "ejecutar OK", SCasTstsEjecutar ( p_caso ), RESULTADO_CASO_TEST_OK, &iRes );
		SCasTstsDestruir ( &p_caso );
	}

	SCasoTestSimple * p_casoKo = SCasTstsCrear ( "casoKo", _CasoDevuelve0 );
	if ( ES_VALIDO ( p_casoKo ) )
	{
		/* Una funcion que devuelve 0 se mapea a RESULTADO_CASO_TEST_KO. */
		VerificarValorEntero ( "ejecutar KO", SCasTstsEjecutar ( p_casoKo ), RESULTADO_CASO_TEST_KO, &iRes );
		SCasTstsDestruir ( &p_casoKo );
	}
	return ( iRes );
}

static int CasoSCasoTestSimple_02_Nulo ()
{
	int iRes = 1;
	printf( "Test CasoSCasoTestSimple_02_Nulo:\n" );

	VerificarEsNulo ( "crear con id nulo", SCasTstsCrear ( NULL, _CasoDevuelve1 ), &iRes );
	VerificarEsNulo ( "crear con funcion nula", SCasTstsCrear ( "x", NULL ), &iRes );
	VerificarEsNulo ( "id de caso nulo", (void *) SCasTstsObtenerId ( NULL ), &iRes );
	VerificarValorEntero ( "ejecutar caso nulo", SCasTstsEjecutar ( NULL ), RESULTADO_CASO_TEST_FAIL, &iRes );
	return ( iRes );
}


int TestSCasoTestSimple ()
{
	int iRes;

	STest * testModulo = STestCrear ( NOMBRE_MODULO );
	STestNuevoCaso ( testModulo, "CasoSCasoTestSimple_01", CasoSCasoTestSimple_01 );
	STestNuevoCaso ( testModulo, "CasoSCasoTestSimple_02_Nulo", CasoSCasoTestSimple_02_Nulo );

	iRes = STestEjecutar ( testModulo );
	STestDestruir ( &testModulo );
	return ( iRes );
}
