#include <CppTest.h>


#define  NOMBRE_MODULO 			"Ejemplo2"




using namespace std;
using namespace org::gjs::cpp::common;
using namespace org::gjs::cpp::common::test;





static bool CasoEjemplo2_01 ()
{
	bool 	bRes = true;
	cout << "Test CasoEjemplo2_01:" << endl;
	return ( bRes );
}

bool TestEjemplo2 ()
{
	bool bRes = true;

	Test * testModulo = new Test ( NOMBRE_MODULO );
	testModulo->NuevoCaso ( "CasoEjemplo2_01", CasoEjemplo2_01 );

	bRes = testModulo->Ejecutar ();
	delete testModulo;
	return ( bRes );
}


