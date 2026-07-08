#include <CppBase.h>
#include "CppCommonIo.h"

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



int main ( int argc, char * argv[] )
{
	InicializarBase();
	int iRes = 0;

	map<std::string, FUNCION_BOOL> mapTests;
	mapTests[ "SocketExcepcion" ] = TestSocketExcepcion;
	mapTests[ "Socket" ] = TestSocket;
	mapTests[ "GestorUsuarios" ] = TestGestorUsuarios;
	mapTests[ "ClienteServidor" ] = TestClienteServidor;
	mapTests[ "Comando" ] = TestComando;
	mapTests[ "ResultadoComando" ] = TestResultadoComando;
	mapTests[ "GestorSesiones" ] = TestGestorSesiones;
	mapTests[ "ClienteServidorComandos" ] = TestClienteServidorComandos;
	mapTests[ "ClienteServidorSesion" ] = TestClienteServidorSesion;
	mapTests[ "ClienteServidorIETF" ] = TestClienteServidorIETF;
	mapTests[ "CodigosIETF" ] = TestCodigosIETF;
	mapTests[ "ClienteServidorFTP" ] = TestClienteServidorFTP;
	mapTests[ "URI" ] = TestURI;
	mapTests[ "ClienteServidorHTTP" ] = TestClienteServidorHTTP;

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

	if ( ! TestSocketExcepcion () ||
		! TestSocket () ||
		! TestGestorUsuarios() ||
		! TestClienteServidor() ||
		! TestComando() ||
		! TestResultadoComando() ||
		! TestGestorSesiones() ||
		! TestClienteServidorComandos () ||
		! TestClienteServidorSesion ()  ||
		! TestCodigosIETF () ||
		! TestClienteServidorIETF() ||
		! TestClienteServidorFTP () ||
		! TestURI () ||
		! TestClienteServidorHTTP () )
	{
		iRes = -1;
	}
	fflush ( stdout );
	return ( iRes );
}
