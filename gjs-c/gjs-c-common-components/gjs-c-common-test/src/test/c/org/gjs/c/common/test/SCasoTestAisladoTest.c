#include <CTest.h>


#define  NOMBRE_MODULO 			"SCasoTestAislado"



static int _CasoDevuelve1 ()
{
	return ( 1 );
}


static int CasoSCasoTestAislado_01 ()
{
	int iRes = 1;
	printf( "Test CasoSCasoTestAislado_01:\n" );

	/* Solo se prueba la construccion: SCasTstaEjecutar hace fork() y ejecuta el
	   caso en un proceso hijo, no procede en un test unitario. */
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


int TestSCasoTestAislado ()
{
	int iRes;

	STest * testModulo = STestCrear ( NOMBRE_MODULO );
	STestNuevoCaso ( testModulo, "CasoSCasoTestAislado_01", CasoSCasoTestAislado_01 );

	iRes = STestEjecutar ( testModulo );
	STestDestruir ( &testModulo );
	return ( iRes );
}
