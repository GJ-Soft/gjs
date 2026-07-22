#include <CTest.h>


#define  NOMBRE_MODULO 			"SCasoTest"



static int _CasoDevuelve1 ()
{
	return ( 1 );
}


static int CasoSCasoTest_01_Simple ()
{
	int iRes = 1;
	printf( "Test CasoSCasoTest_01_Simple:\n" );

	SCasoTest * p_caso = SCasTstCrearSimple ( "cs", _CasoDevuelve1 );
	VerificarNoEsNulo ( "crear simple", p_caso, &iRes );
	if ( ES_VALIDO ( p_caso ) )
	{
		VerificarEsCierto ( "es caso simple", SCasTstEsCasoSimple ( p_caso ), &iRes );
		VerificarEsFalso ( "no es caso aislado", SCasTstEsCasoAislado ( p_caso ), &iRes );
		VerificarNoEsNulo ( "caso simple interno", SCasTstCasoSimple ( p_caso ), &iRes );
		VerificarEsNulo ( "caso aislado interno nulo", SCasTstCasoAislado ( p_caso ), &iRes );
		VerificarEsCierto ( "id correcto",
			( SCasTstObtenerId ( p_caso ) != NULL ) && ( strcmp ( SCasTstObtenerId ( p_caso ), "cs" ) == 0 ), &iRes );
		VerificarValorEntero ( "ejecutar OK", SCasTstEjecutar ( p_caso ), RESULTADO_CASO_TEST_OK, &iRes );
		SCasTstDestruir ( &p_caso );
	}
	return ( iRes );
}

static int CasoSCasoTest_02_Aislado ()
{
	int iRes = 1;
	printf( "Test CasoSCasoTest_02_Aislado:\n" );

	/* No se ejecuta (el aislado hace fork): solo tipo y encapsulacion. */
	SCasoTest * p_caso = SCasTstCrearAislado ( "ca", _CasoDevuelve1, 0 );
	VerificarNoEsNulo ( "crear aislado", p_caso, &iRes );
	if ( ES_VALIDO ( p_caso ) )
	{
		VerificarEsCierto ( "es caso aislado", SCasTstEsCasoAislado ( p_caso ), &iRes );
		VerificarEsFalso ( "no es caso simple", SCasTstEsCasoSimple ( p_caso ), &iRes );
		VerificarNoEsNulo ( "caso aislado interno", SCasTstCasoAislado ( p_caso ), &iRes );
		VerificarEsNulo ( "caso simple interno nulo", SCasTstCasoSimple ( p_caso ), &iRes );
		SCasTstDestruir ( &p_caso );
	}
	return ( iRes );
}


int TestSCasoTest ()
{
	int iRes;

	STest * testModulo = STestCrear ( NOMBRE_MODULO );
	STestNuevoCaso ( testModulo, "CasoSCasoTest_01_Simple", CasoSCasoTest_01_Simple );
	STestNuevoCaso ( testModulo, "CasoSCasoTest_02_Aislado", CasoSCasoTest_02_Aislado );

	iRes = STestEjecutar ( testModulo );
	STestDestruir ( &testModulo );
	return ( iRes );
}
