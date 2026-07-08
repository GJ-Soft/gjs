#include <CTest.h>


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
	SBanTstNuevoTest ( p_banTests, "Ejemplo1", TestEjemplo1 );
	SBanTstNuevoTest ( p_banTests, "Ejemplo2", TestEjemplo2 );

	char * p_cTest = NULL;
	if ( argc > 1 )
	{
		p_cTest = argv[1];
	}
	if( SBanTstEjecutarTest ( p_banTests, p_cTest ) == 1 )
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
