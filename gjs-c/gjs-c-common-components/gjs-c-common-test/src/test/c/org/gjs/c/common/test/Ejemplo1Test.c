#include <CTest.h>


#define  NOMBRE_MODULO 			"Ejemplo1"






static int CasoEjemplo1_01 ()
{
	char *	p_cDir;
	int 	iRes;

	iRes = 1;
	printf( "Test CasoEjemplo1_01:\n" );
	p_cDir = DirectorioProyecto ();
	printf( "DirectorioProyecto: %s\n", p_cDir );
	MemLiberarCadena ( &p_cDir ); 
	p_cDir = DirectorioTrabajo ();
	printf( "DirectorioTrabajo: %s\n", p_cDir );
	MemLiberarCadena ( &p_cDir ); 
	p_cDir = DirectorioTest ();
	printf( "DirectorioTest: %s\n", p_cDir );
	MemLiberarCadena ( &p_cDir ); 
	p_cDir = DirectorioTestRecursos ();
	printf( "DirectorioTestRecursos: %s\n", p_cDir );
	MemLiberarCadena ( &p_cDir ); 
	p_cDir = DirectorioTestResultados ();
	printf( "DirectorioTestResultados: %s\n", p_cDir );
	MemLiberarCadena ( &p_cDir ); 
	return ( iRes );
}

static int CasoEjemplo1_02 ()
{
	int iRes = 1;
	printf( "Test CasoEjemplo1_02:\n" );
	return ( iRes );
}


int TestEjemplo1 ()
{
	int iRes = 1;

	STest * testModulo = STestCrear ( NOMBRE_MODULO );
	//STestNuevoCaso ( testModulo, "CasoEjemplo1_01", CasoEjemplo1_01 );
	//STestNuevoCaso ( testModulo, "CasoEjemplo1_02", CasoEjemplo1_02 );

	iRes = STestEjecutar ( testModulo );
	STestDestruir ( &testModulo );
	return ( iRes );
}


