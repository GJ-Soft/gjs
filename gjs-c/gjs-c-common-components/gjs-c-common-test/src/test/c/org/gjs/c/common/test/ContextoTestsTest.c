#include <CTest.h>


#define  NOMBRE_MODULO 			"ContextoTests"



/* El entorno de test (que rellena el contexto) lo inicializa STestEjecutar antes
   de ejecutar los casos, asi que los directorios estan disponibles aqui. */
static int CasoContextoTests_01 ()
{
	int iRes = 1;
	printf( "Test CasoContextoTests_01:\n" );

	char * p_cDir;

	p_cDir = DirectorioProyecto ();
	VerificarNoEsNulo ( "DirectorioProyecto", p_cDir, &iRes );
	MemLiberarCadena ( &p_cDir );

	p_cDir = DirectorioTrabajo ();
	VerificarNoEsNulo ( "DirectorioTrabajo", p_cDir, &iRes );
	MemLiberarCadena ( &p_cDir );

	p_cDir = DirectorioTest ();
	VerificarNoEsNulo ( "DirectorioTest", p_cDir, &iRes );
	MemLiberarCadena ( &p_cDir );

	p_cDir = DirectorioTestRecursos ();
	VerificarNoEsNulo ( "DirectorioTestRecursos", p_cDir, &iRes );
	MemLiberarCadena ( &p_cDir );

	p_cDir = DirectorioTestResultados ();
	VerificarNoEsNulo ( "DirectorioTestResultados", p_cDir, &iRes );
	MemLiberarCadena ( &p_cDir );

	return ( iRes );
}


int TestContextoTests ()
{
	int iRes;

	STest * testModulo = STestCrear ( NOMBRE_MODULO );
	STestNuevoCaso ( testModulo, "CasoContextoTests_01", CasoContextoTests_01 );

	iRes = STestEjecutar ( testModulo );
	STestDestruir ( &testModulo );
	return ( iRes );
}
