#include "CppCommonTypes.h"

#include <map>

using namespace std;

extern bool TestCalendario ();
extern bool TestFechas ();
extern bool TestHoras ();
extern bool TestSistemasHorarios ();
extern bool TestTiempoNumerico ();
extern bool TestTiempoSistema ();
extern bool TestFecha ();
extern bool TestHora ();
extern bool TestFechaHora ();
extern bool TestCronometro ();

int main ( int argc, char * argv[] )
{
	InicializarBase();
	int iRes = 0;

	map<string, FUNCION_BOOL> mapTests;
	mapTests[ "CalendarioTest" ] = TestCalendario;
	mapTests[ "FechasTest" ] = TestFechas;
	mapTests[ "HorasTest" ] = TestHoras;
	mapTests[ "SistemasHorariosTest" ] = TestSistemasHorarios;
	mapTests[ "TiempoNumericoTest" ] = TestTiempoNumerico;
	mapTests[ "TiempoSistemaTest" ] = TestTiempoSistema;
	mapTests[ "FechaTest" ] = TestFecha;
	mapTests[ "HoraTest" ] = TestHora;
	mapTests[ "FechaHoraTest" ] = TestFechaHora;
	mapTests[ "CronometroTest" ] = TestCronometro;


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
