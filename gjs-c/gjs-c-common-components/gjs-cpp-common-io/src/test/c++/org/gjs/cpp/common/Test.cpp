
#include "CppCommonIo.h"
#include <CppBase.h>

using namespace std;


extern bool TestSocketExcepcion ();
extern bool TestSocket();
extern bool TestGestorUsuarios();
extern bool TestClienteServidor();
extern bool TestComando();
extern bool TestResultadoComando();
extern bool TestGestorSesiones();
extern bool TestClienteServidorComandos ();
extern bool TestClienteServidorSesion ();
extern bool TestClienteServidorIETF ();
extern bool TestCodigosIETF ();
extern bool TestClienteServidorFTP ();
extern bool TestURI ();
extern bool TestClienteServidorHTTP ();
extern bool TestSistemaFicheros ();



int main ( int argc, char * argv[] )
{
	InicializarBase();
	int iRes = 0;

	map<std::string, FUNCION_BOOL> mapTests;
	mapTests[ "SocketExcepcionTest" ] = TestSocketExcepcion;
	mapTests[ "SocketTest" ] = TestSocket;
	mapTests[ "GestorUsuariosTest" ] = TestGestorUsuarios;
	mapTests[ "ClienteServidorTest" ] = TestClienteServidor;
	mapTests[ "ComandoTest" ] = TestComando;
	mapTests[ "ResultadoComandoTest" ] = TestResultadoComando;
	mapTests[ "GestorSesionesTest" ] = TestGestorSesiones;
	mapTests[ "ClienteServidorComandosTest" ] = TestClienteServidorComandos;
	mapTests[ "ClienteServidorSesionTest" ] = TestClienteServidorSesion;
	mapTests[ "ClienteServidorIETFTest" ] = TestClienteServidorIETF;
	mapTests[ "CodigosIETFTest" ] = TestCodigosIETF;
	mapTests[ "ClienteServidorFTPTest" ] = TestClienteServidorFTP;
	mapTests[ "URITest" ] = TestURI;
	mapTests[ "ClienteServidorHTTPTest" ] = TestClienteServidorHTTP;
	mapTests[ "SistemaFicherosTest" ] = TestSistemaFicheros;

	std::string sTest ( "null" );
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
			cerr << "Test [ " << sTest << " ] no encontrado." << endl;
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
