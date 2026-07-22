#include <CTest.h>


#define  NOMBRE_MODULO 			"SBancoTests"



static int _TestDummy ()
{
	return ( 1 );
}


/* Prueba estructural del banco: creacion y alta de tests. NO se ejecuta
   SBanTstEjecutar (lanzaria la inicializacion del entorno y los propios tests). */
static int CasoSBancoTests_01 ()
{
	int iRes = 1;
	printf( "Test CasoSBancoTests_01:\n" );

	SBancoTests * p_ban = SBanTstCrear ();
	VerificarNoEsNulo ( "crear banco", p_ban, &iRes );
	if ( ES_VALIDO ( p_ban ) )
	{
		VerificarValorEntero ( "num tests inicial", SBanTstNumTests ( p_ban ), 0, &iRes );
		SBanTstNuevoTest ( p_ban, "t1", _TestDummy );
		SBanTstNuevoTest ( p_ban, "t2", _TestDummy );
		VerificarValorEntero ( "num tests tras insertar", SBanTstNumTests ( p_ban ), 2, &iRes );
		SBanTstDestruir ( &p_ban );
	}
	VerificarValorEntero ( "num tests de banco nulo", SBanTstNumTests ( NULL ), 0, &iRes );
	return ( iRes );
}


int TestSBancoTests ()
{
	int iRes;

	STest * testModulo = STestCrear ( NOMBRE_MODULO );
	STestNuevoCaso ( testModulo, "CasoSBancoTests_01", CasoSBancoTests_01 );

	iRes = STestEjecutar ( testModulo );
	STestDestruir ( &testModulo );
	return ( iRes );
}
