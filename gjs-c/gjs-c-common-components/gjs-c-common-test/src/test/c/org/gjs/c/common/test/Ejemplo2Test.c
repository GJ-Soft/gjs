#include <CTest.h>


#define  NOMBRE_MODULO 			"Ejemplo2"






static int CasoEjemplo2_01 ()
{
	int iRes = 1;
	printf( "Test CasoEjemplo2_01:\n" );
	return ( iRes );
}

int TestEjemplo2 ()
{
	int iRes = 1;

	STest * testModulo = STestCrear ( NOMBRE_MODULO );
	STestNuevoCaso ( testModulo, "CasoEjemplo2_01", CasoEjemplo2_01 );

	iRes = STestEjecutar ( testModulo );
	STestDestruir ( &testModulo );
	return ( iRes );
}


