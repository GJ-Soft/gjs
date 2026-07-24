#set( $symbol_pound = '#' )
#set( $symbol_dollar = '$' )
#set( $symbol_escape = '\' )
#set( $capitalizedName = $shortName.substring(0,1).toUpperCase() + $shortName.substring(1))

${symbol_pound}include <CTest.h>



extern int Test${capitalizedName} ();






int main( int argc, char * argv[] )
{
	int iRes = 0;
	EntInicializar ( 1, "Test${capitalizedName}", 1, 0 );
	EntActivarModoTest ();
	thread thHilo = SisLanzarHiloVigilanciaPadre ();
	printf ( "****** HILO = %lu\n", (unsigned long) thHilo );

	SBancoTests * p_banTests = SBanTstCrear ();
	SBanTstNuevoTest ( p_banTests, "${capitalizedName}Test", Test${capitalizedName} );

	char * p_cTest = NULL;
	if ( argc > 1 )
	{
		p_cTest = argv [ 1 ];
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
