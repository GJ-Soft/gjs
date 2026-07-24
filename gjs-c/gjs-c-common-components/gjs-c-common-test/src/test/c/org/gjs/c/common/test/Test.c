#include <CTest.h>


extern int TestUtilesTest ();
extern int TestSCasoTestSimple ();
extern int TestSCasoTestAislado ();
extern int TestSCasoTest ();
extern int TestSTest ();
extern int TestSBancoTests ();
extern int TestContextoTests ();
extern int TestEjemplo1 ();
extern int TestEjemplo2 ();


int main ( int argc, char * argv[] )
{
	int iRes = 0;
	EntInicializar ( 1, "TestCommonTestLib", 1, 0 );
	EntActivarModoTest ();
	thread thHilo = SisLanzarHiloVigilanciaPadre ();
	printf ( "****** HILO = %lu\n", (unsigned long) thHilo );

	SBancoTests * p_banTests = SBanTstCrear ();
	SBanTstNuevoTest ( p_banTests, "UtilesTest", TestUtilesTest );
	SBanTstNuevoTest ( p_banTests, "SCasoTestSimpleTest", TestSCasoTestSimple );
	SBanTstNuevoTest ( p_banTests, "SCasoTestAisladoTest", TestSCasoTestAislado );
	SBanTstNuevoTest ( p_banTests, "SCasoTestTest", TestSCasoTest );
	SBanTstNuevoTest ( p_banTests, "STestTest", TestSTest );
	SBanTstNuevoTest ( p_banTests, "SBancoTestsTest", TestSBancoTests );
	SBanTstNuevoTest ( p_banTests, "ContextoTestsTest", TestContextoTests );
	SBanTstNuevoTest ( p_banTests, "Ejemplo1Test", TestEjemplo1 );
	SBanTstNuevoTest ( p_banTests, "Ejemplo2Test", TestEjemplo2 );

	char * p_cTest = NULL;
	if ( argc > 1 )
	{
		p_cTest = argv [ 1 ];
	}
	if ( SBanTstEjecutarTest ( p_banTests, p_cTest ) == 1 )
	{
		iRes = 0;
	}
	else
	{
		iRes = -1;
	}
	EntFinalizar ();
	return ( iRes );
}
