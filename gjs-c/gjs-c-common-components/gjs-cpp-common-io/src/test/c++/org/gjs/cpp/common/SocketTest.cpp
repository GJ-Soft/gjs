#include "CppCommonIo.h"
#include <CppBase.h>




using namespace std;
using namespace org::gjs::cpp::common;




static bool TestSocket01 ()
{
	cout << "Test Socket 01:" << endl;
	bool bRes = true;

	try
	{
		Socket * socket = new Socket();
		string sHost = socket->getHost();
		if ( socket->EsValido() || 
			 socket->EstaConectado() || 
			 socket->AceptaConexiones() || 
			 ( socket->getId() != -1 ) ||
			 ( socket->getPuerto() != 0 ) || 
			 ( sHost.size() > 0 ) )
		{
			cout << "Error caso 1" << endl;
			bRes = false;
		}
		delete socket;
	}
	catch ( exception & ex )
	{
		cout << "Se ha producido una excepcion :" << ex.what () << endl;
		bRes = false;
	}
	catch ( ... )
	{
		cout << "Excepcion indefinida" << endl;
		bRes = false;
	}
	return( bRes );
}

static bool _bResCliente1 = false;
static bool _bResCliente2 = false;
static bool _bResServidor = false;


static void Servidor1()
{
	try
	{
		SocketServidor * socket = new SocketServidor( 45672 );
		bool bFin = false;
		while( !bFin )
		{
			cout << "{SERVIDOR} Esperando conexion..." << endl;
			SocketAtencion * sockConectado = socket->Aceptar();
			cout << "{SERVIDOR} Conexion recibida: socket=" << sockConectado->getId() << endl;
			string sMensaje;
			*sockConectado >> sMensaje;
			cout << "{SERVIDOR} Mensaje recibido: [" << sMensaje << "]" << endl;
			*sockConectado << "OK";
			bFin = ( sMensaje.compare( "KILL" ) == 0 );
			sockConectado->Cerrar();
			delete sockConectado;
		}	
		_bResServidor = true;
		cout << "{SERVIDOR} Finalizado" << endl;
	}
	catch ( SocketExcepcion & ex )
	{
		cout << "Se ha producido una excepcion de sockets:" << ex.what () << endl;
	}
	catch ( exception & ex )
	{
		cout << "Se ha producido una excepcion :" << ex.what () << endl;
	}
	catch ( ... )
	{
		cout << "Excepcion indefinida" << endl;
	}
}

static void Cliente1()
{
	try
	{
		SocketCliente * socket = new SocketCliente( "localhost", 45672 );
		cout << "{CLIENTE1} Iniciado..." << endl;
		if ( socket->EsValido() )
		{
			string sRespuesta;
			*socket << "MENSAJE1";
			cout << "{CLIENTE1} Mensaje enviado" << endl;
			*socket >> sRespuesta;
			cout << "{CLIENTE1} Mensaje recibido: [" << sRespuesta << "]" << endl;
			Esperar( 3000 );
			socket->Cerrar();
			_bResCliente1 = ( sRespuesta.compare( "OK" ) == 0 );
		}	
		delete socket;
		cout << "{CLIENTE1} Finalizado" << endl;
	}
	catch ( SocketExcepcion & ex )
	{
		cout << "Se ha producido una excepcion de sockets:" << ex.what () << endl;
	}
	catch ( exception & ex )
	{
		cout << "Se ha producido una excepcion :" << ex.what () << endl;
	}
	catch ( ... )
	{
		cout << "Excepcion indefinida" << endl;
	}
}

void Cliente2()
{
	try
	{
		SocketCliente * socket = new SocketCliente( "127.0.0.1", 45672 );
		cout << "{CLIENTE2} Iniciado..." << endl;
		if ( socket->EsValido() )
		{
			string sRespuesta;
			*socket << "KILL";
			cout << "{CLIENTE2} Mensaje enviado" << endl;
			*socket >> sRespuesta;
			cout << "{CLIENTE2} Mensaje recibido: [" << sRespuesta << "]" << endl;
			Esperar( 3000 );
			socket->Cerrar();
			_bResCliente2 = ( sRespuesta.compare( "OK" ) == 0 );
		}	
		delete socket;
		cout << "{CLIENTE2} Finalizado" << endl;
	}
	catch ( SocketExcepcion & ex )
	{
		cout << "Se ha producido una excepcion de sockets:" << ex.what () << endl;
	}
	catch ( exception & ex )
	{
		cout << "Se ha producido una excepcion :" << ex.what () << endl;
	}
	catch ( ... )
	{
		cout << "Excepcion indefinida" << endl;
	}
}


static bool TestSocket02 ()
{
	cout << "Test Socket 01:" << endl;
	bool bRes = true;

	try
	{
		thread thServidor ( Servidor1 );
		Esperar( 2000 );
		thread thCliente1 ( Cliente1 );
		thCliente1.join();
		thread thCliente2 ( Cliente2 );
		thCliente2.join();
		thServidor.join();
		bRes = _bResServidor && _bResCliente1 && _bResCliente2;
	}
	catch ( exception & ex )
	{
		cout << "Se ha producido una excepcion :" << ex.what () << endl;
		bRes = false;
	}
	catch ( ... )
	{
		cout << "Excepcion indefinida" << endl;
		bRes = false;
	}
	return( bRes );
}

static bool TestResolverIP01 ()
{
	cout << "Test ResolverIP01:" << endl;
	bool bRes = true;

	string sTest1( "127.0.0.1" );
	string sTest2( "localhost" );

	try
	{
		int  iTest1 = ResolverIP( sTest1 );
		int  iTest2 = ResolverIP( sTest2 );
		if ( iTest1 != 16777343 )
		{
			cout << "Error caso 1: IP[" << sTest1 << "] = " << iTest1 << endl;
			bRes = false;
		}
		if ( iTest2 != 16777343 )
		{
			cout << "Error caso 2: IP[" << sTest2 << "] = " << iTest2 << endl;
			bRes = false;
		}
	}
	catch ( ... )
	{
		cout << "Error al recuperar la hora local del sistema" << endl;
		bRes = false;
	}
	return( bRes );
}

bool TestSocket ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test Socket]" << ANSI::RESETEAR << endl;
	if ( TestSocket01() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestSocket02() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestResolverIP01() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	cout << ANSI::AMARILLO << "[Fin]" << ANSI::RESETEAR << endl;	
	return ( bRes );
}
