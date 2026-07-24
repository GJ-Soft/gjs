#include <CppTest.h>


#define  NOMBRE_MODULO 			"Ejemplo1"



using namespace std;
using namespace org::gjs::cpp::common;
using namespace org::gjs::cpp::common::test;





static bool CasoEjemplo1_01 ()
{
	string	sDir;
	bool 	bRes = true;
	cout << "Test CasoEjemplo1_01:" << endl;
	try
	{
		sDir = DirectorioProyecto ();
		cout << "DirectorioProyecto: " << sDir << endl;
		sDir = DirectorioTrabajo ();
		cout << "DirectorioTrabajo: " << sDir << endl;
		sDir = DirectorioTest ();
		cout << "DirectorioTest: " << sDir << endl;
		sDir = DirectorioTestRecursos ();
		cout << "DirectorioTestRecursos: " << sDir << endl;
		sDir = DirectorioTestResultados ();
		cout << "DirectorioTestResultados: " << sDir << endl;
	}
	catch ( exception & ex )
	{
		cout << "Se ha producido una excepcion :" << ex.what () << endl;
		bRes = false;
	}
	catch ( ... )
	{
		cout << "Excepcion indefinida" << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool CasoEjemplo1_02 ()
{
	bool 	bRes = true;
	cout << "Test CasoEjemplo1_02:" << endl;
	return ( bRes );
}


bool TestEjemplo1 ()
{
	bool bRes = true;

	Test * testModulo = new Test ( NOMBRE_MODULO );
	testModulo->NuevoCaso ( "CasoEjemplo2_01", CasoEjemplo1_01 );
	testModulo->NuevoCaso ( "CasoEjemplo2_02", CasoEjemplo1_02 );

	bRes = testModulo->Ejecutar ();
	delete testModulo;
	return ( bRes );
}


