#include "CppCommonTypes.h"

#include <map>

using namespace std;

extern bool TestTiposSistema ();
extern bool TestSistemaTiempo ();
extern bool TestSistemaEstado ();
extern bool TestSistemaErrores ();
extern bool TestSistemaInformacion ();
extern bool TestSistemaMemoria ();
extern bool TestSistemaProcesos ();
extern bool TestSistemaRed ();
extern bool TestSistemaSignals ();
extern bool TestCContadorCiclos ();
extern bool TestCTemporizador ();
extern bool TestCVariablesEntorno ();
extern bool TestSistemaSincronizacion ();
extern bool TestCGestorSignals ();


int main ( int argc, char * argv[] )
{
	InicializarBase();
	int iRes = 0;

	map<string, FUNCION_BOOL> mapTests;
	mapTests[ "TiposSistemaTest" ] = TestTiposSistema;
	mapTests[ "SistemaTiempoTest" ] = TestSistemaTiempo;
	mapTests[ "SistemaEstadoTest" ] = TestSistemaEstado;
	mapTests[ "SistemaErroresTest" ] = TestSistemaErrores;
	mapTests[ "SistemaInformacionTest" ] = TestSistemaInformacion;
	mapTests[ "SistemaMemoriaTest" ] = TestSistemaMemoria;
	mapTests[ "SistemaProcesosTest" ] = TestSistemaProcesos;
	mapTests[ "SistemaRedTest" ] = TestSistemaRed;
	mapTests[ "SistemaSignalsTest" ] = TestSistemaSignals;
	mapTests[ "CContadorCiclosTest" ] = TestCContadorCiclos;
	mapTests[ "CTemporizadorTest" ] = TestCTemporizador;
	mapTests[ "CVariablesEntornoTest" ] = TestCVariablesEntorno;
	mapTests[ "SistemaSincronizacionTest" ] = TestSistemaSincronizacion;
	mapTests[ "CGestorSignalsTest" ] = TestCGestorSignals;

	string sTest ( "null" );
	if ( argc > 1 )
	{
		sTest = argv[1];
	}
	if ( ( sTest.size() > 0 ) && ( sTest.compare( "null" ) != 0 ) )
	{
		if ( mapTests.find( sTest ) != mapTests.end() )
		{
			FUNCION_BOOL fTest = mapTests[ sTest ];
			if( !fTest () )
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
