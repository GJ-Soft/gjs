#include <CTest.h>


#define  NOMBRE_MODULO 			"STest"



static int _CasoDummy ()
{
	return ( 1 );
}


/* Prueba estructural de STest: creacion, alta de casos y numero de casos. NO se
   ejecuta STestEjecutar sobre el STest interno (anidaria la inicializacion del
   entorno de test). */
static int CasoSTest_01 ()
{
	int iRes = 1;
	printf( "Test CasoSTest_01:\n" );

	STest * p_test = STestCrear ( "mitest" );
	VerificarNoEsNulo ( "crear STest", p_test, &iRes );
	if ( ES_VALIDO ( p_test ) )
	{
		VerificarValorEntero ( "num casos inicial", STestNumCasos ( p_test ), 0, &iRes );
		STestNuevoCaso ( p_test, "c1", _CasoDummy );
		STestNuevoCaso ( p_test, "c2", _CasoDummy );
		VerificarValorEntero ( "num casos tras insertar", STestNumCasos ( p_test ), 2, &iRes );
		STestDestruir ( &p_test );
	}
	VerificarValorEntero ( "num casos de STest nulo", STestNumCasos ( NULL ), 0, &iRes );
	return ( iRes );
}


int TestSTest ()
{
	int iRes;

	STest * testModulo = STestCrear ( NOMBRE_MODULO );
	STestNuevoCaso ( testModulo, "CasoSTest_01", CasoSTest_01 );

	iRes = STestEjecutar ( testModulo );
	STestDestruir ( &testModulo );
	return ( iRes );
}
