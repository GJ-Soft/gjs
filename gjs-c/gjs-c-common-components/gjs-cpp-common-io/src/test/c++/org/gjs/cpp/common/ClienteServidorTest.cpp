#include "CppCommonIo.h"
#include <CppBase.h>




using namespace std;
using namespace org::gjs::cpp::common;


static bool _bResCliente = false;
static bool _bExcepCliente = false;
static bool _bResServidor = false;

class ServidorTest : public Servidor
{
public:
	ServidorTest( int iPuerto ) : Servidor( iPuerto )
	{
	}
	
	virtual ~ServidorTest()
	{
	}
	
private:
	void PeticionRecibida()
	{
		cout << "{SERVIDOR} Inicio peticion" << endl;
	}
	
	void PeticionFinalizada( bool bResultado )
	{
		cout << "{SERVIDOR} Fin peticion: " << toString() << endl;
	}

	void ProcesarMensaje( const string & sMensaje, bool & bResponder, string & sRespuesta, bool & bResultado, bool & bFin, SocketAtencion * socket )
	{
		cout << "{SERVIDOR} Mensaje recibido: [" << sMensaje << "]" << endl;
		bFin = false;
		bResponder = true;
		bResultado = true;
		if ( sMensaje.compare ( "CMD1" ) == 0 )
		{
			sRespuesta = "OK";
		}
		else if ( sMensaje.compare ( "CMD2" ) == 0 )
		{
			sRespuesta = "KO";
		}
		else if ( sMensaje.compare ( "FIN" ) == 0 )
		{
			bResponder = false;
			bFin = true;
		}
	}
	
	bool ExcepcionProducida( const exception & ex )
	{
		cout << "{SERVIDOR} Excepcion recibida: " << ex.what() << endl;
		return( true );
	}
	
	void ExcepcionProducidaEnPeticion( const exception & ex )
	{
		cout << "{SERVIDOR} Excepcion recibida: " << ex.what() << endl;
	}

};

class ClienteTest : public Cliente
{
public:
	ClienteTest( const string & sIP, int iPuerto ) : Cliente( sIP, iPuerto )
	{
	}
	
	virtual ~ClienteTest()
	{
	}
	
private:
	void ExcepcionProducida( const exception & ex )
	{
					cout << "**** 5" << endl;

		_bExcepCliente = true;
		cout << "{CLIENTE} Excepcion recibida: " << ex.what() << endl;
	}

};


static ServidorTest * servidor = NULL;


static void Servidor1( int iPuerto )
{
	try
	{
		servidor = new ServidorTest( iPuerto );
		servidor->Iniciar();
		_bResServidor = true;
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
		ClienteTest * cliente = new ClienteTest( "localhost", 43234 );
		string sRespuesta = "";
		cliente->EnviarMensaje( "CMD1", sRespuesta );
		cout << "{CLIENTE} Mensaje recibido: [" << sRespuesta << "]" << endl;
		Esperar( 100 );
		sRespuesta = "";
		cliente->EnviarMensaje( "CMD2", sRespuesta );
		cout << "{CLIENTE} Mensaje recibido: [" << sRespuesta << "]" << endl;
		Esperar( 100 );
		sRespuesta = "";
		cliente->EnviarMensaje( "FIN" );
		_bResCliente = true;
		delete cliente;
	}
	catch ( ... )
	{
		cout << "Excepcion indefinida" << endl;
	}
}


static bool TestClienteServidor01 ()
{
	cout << "Test ClienteServidor 01:" << endl;
	bool bRes = true;
	try
	{
		thread thServidor ( Servidor1, 43234 );
		Esperar( 2000 );
		thread thCliente1 ( Cliente1 );
		thCliente1.join();
		bRes = _bResCliente;
		_bResCliente = false;
		thread thCliente2 ( Cliente1 );
		thCliente2.join();
		servidor->Parar();
		thServidor.join();
		bRes = bRes && _bResServidor && _bResCliente;
		delete servidor;
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

static bool TestClienteServidor02 ()
{
	cout << "Test ClienteServidor 02:" << endl;
	bool bRes = true;
	_bResServidor = false;
	_bExcepCliente = false;
	try
	{
		Esperar( 1000 );
		cout << "Ejecutando servidor..." << endl;
		thread thServidor ( Servidor1, 43334 );
		Esperar( 2000 );
		cout << "Ejecutando cliente..." << endl;
		ClienteTest * cliente = NULL;
		try
		{
			cliente = new ClienteTest( "localhost", 43235 );
			bRes = false;
		}
		catch ( exception & ex )
		{
			cout << "Se ha producido una excepcion :" << ex.what () << endl;
			_bExcepCliente = true;
		}
		catch ( ... )
		{
			cout << "Excepcion indefinida" << endl;
			bRes = false;
		}
		servidor->Parar();
		thServidor.join();
		bRes = bRes && _bResServidor && _bExcepCliente;
		if ( !bRes )
		{
			cout << "Resultado Servidor=" << ToString( _bResServidor ) << endl;
			cout << "Resultado Cliente=" << ToString( _bExcepCliente ) << endl;
		}
		delete cliente;
		delete servidor;
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

bool TestClienteServidor ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test ClienteServidor]" << ANSI::RESETEAR << endl;
	if ( TestClienteServidor01() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestClienteServidor02() )
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
