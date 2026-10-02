#include "CppCommonTypes.h"

#include <map>

using namespace std;

extern bool TestVersion ();
extern bool TestTiposCajaMensajes ();
extern bool TestAplicacionValidaciones ();
extern bool TestAplicacionInformacion ();
extern bool TestAplicacionConsola ();
extern bool TestConsolaDepuracion ();
extern bool TestCajaMensajes ();
extern bool TestConfiguracion ();
extern bool TestUtilidadesRecursos ();

int main( int argc, char * argv[] )
{
	InicializarBase();
	int iRes = 0;

	map<string, FUNCION_BOOL> mapTests;
	mapTests[ "VersionTest" ] = TestVersion;
	mapTests[ "TiposCajaMensajesTest" ] = TestTiposCajaMensajes;
	mapTests[ "AplicacionValidacionesTest" ] = TestAplicacionValidaciones;
	mapTests[ "AplicacionInformacionTest" ] = TestAplicacionInformacion;
	mapTests[ "AplicacionConsolaTest" ] = TestAplicacionConsola;
	mapTests[ "ConsolaDepuracionTest" ] = TestConsolaDepuracion;
	mapTests[ "CajaMensajesTest" ] = TestCajaMensajes;
	/* Estaba declarada arriba pero se registraba DENTRO de la rama de un solo
	   test, y encima despues del find: no se ejecutaba ni en la pasada completa ni
	   pidiendola por nombre. */
	mapTests[ "ConfiguracionTest" ] = TestConfiguracion;
	mapTests[ "UtilidadesRecursosTest" ] = TestUtilidadesRecursos;


	string sTest( "null" );
	if ( argc > 1 )
	{
		sTest = argv[1];
	}
	if ( ( sTest.size() > 0 ) && ( sTest.compare( "null" ) != 0 ) )
	{
		if ( mapTests.find( sTest ) != mapTests.end() )
		{
			FUNCION_BOOL fTest = mapTests[ sTest ];
			if( !fTest() )
			{
				iRes = -1;
			}
		}
		else
		{
			cerr << "Test [" << sTest << "] no encontrado." << endl;
			iRes = -1;
		}
		return( iRes );
	}


	for ( auto it = mapTests.begin(); it != mapTests.end(); ++it )
	{
		FUNCION_BOOL fTest = it->second;
		if( fTest () != 1 )
		{
			iRes = -1;
		}
	}
	fflush ( stdout );
	return ( iRes );
}
