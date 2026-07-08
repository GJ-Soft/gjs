#include "CppCommonIo.h"
#include <CppBase.h>




using namespace std;
using namespace org::gjs::cpp::common;


static const string FICHERO_USUARIO = "../../test-classes/data/usuarios.info";



class ServidorComandosTest : public ServidorComandos
{
private:
	const string MSJ_FIN = "Adios"; 	
	const string MSJ_COMANDO_INVALIDO = "Comando invalido"; 	
	const string MSJ_ERROR_SINTACTICO = "Error de sintaxis"; 	
	
public:
	ServidorComandosTest( int iPuerto ) : ServidorComandos( iPuerto )
	{
	}
	
	virtual ~ServidorComandosTest()
	{
	}
	
private:
	string MensajeComandoFin()
	{
		return( MSJ_FIN );
	}
	
	string MensajeComandoInvalido() 
	{
		return( MSJ_COMANDO_INVALIDO );
	}
	
	string MensajeErrorSintactico()
	{
		return( MSJ_ERROR_SINTACTICO );
	}
	
	void ComandoRecibido( Comando & comando )
	{
		cout << "{SERVIDOR} Recibido comando [" << comando.toString() << "]" << endl;
	}
	
	void ComandoProcesado( Comando & comando, bool & bResultado )
	{
		cout << "{SERVIDOR} Procesado comando [" << comando.toString() << "]" << endl;
	}

	bool EsComandoValido( Comando & comando )
	{
		return ( comando.isComando( "CMD1" ) ||
					comando.isComando( "CMD2" ) ||
					comando.isComando( "FIN" )  );
	}
	
	bool EsComandoFin( Comando & comando, bool & bResponder )
	{
		bResponder = true;
		return ( comando.isComando( "FIN" ) );
	}
	
	void ProcesarComando( Comando & comando, bool & bResponder, string & sRespuesta, bool & bResultado, SocketAbierto * socket )
	{
		try
		{
			bResponder = true;
			if ( comando.isComando ( "CMD1" ) )
			{
				bResultado = true;
				sRespuesta = "Ok";
			}
			else if ( comando.isComando ( "CMD2" ) )
			{
				bResultado = false;
				sRespuesta = "Ko";
			}
		}
		catch ( exception & ex )
		{
			cout << "{SERVIDOR} Excepcion inesperada: " << ex.what() << endl;
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

class ClienteComandosTest : public ClienteComandos
{
public:
	ClienteComandosTest( const string & sIP, int iPuerto ) : ClienteComandos( sIP, iPuerto )
	{
	}
	
	virtual ~ClienteComandosTest()
	{
	}
	
private:
				
	void ExcepcionProducida( const exception & ex )
	{
		cout << "{CLIENTE} Excepcion recibida: " << ex.what() << endl;
	}

};

static bool _bResTestComandosCliente = false;
static bool _bResTestComandosServidor = false;
static ServidorComandosTest * servidorTestComandos = NULL;


static void Servidor1()
{
	try
	{
		servidorTestComandos = new ServidorComandosTest( 43235 );
		if ( servidorTestComandos->EsValido() ) 
		{

			cout << "{SERVIDOR} Iniciando bucle de espera..." << endl;			
			servidorTestComandos->Iniciar();
			_bResTestComandosServidor = true;
		}
		else
		{
			cout << "{SERVIDOR} No se ha inicializado bien el servidorTestComandos" << endl;
		}
	}
	catch ( exception & ex )
	{
		cout << "{SERVIDOR} Se ha producido una excepcion :" << ex.what () << endl;
		_bResTestComandosServidor = false;
	}
	catch ( ... )
	{
		cout << "{SERVIDOR} Excepcion indefinida" << endl;
		_bResTestComandosServidor = false;
	}
}

static void Cliente1()
{
	bool bRes = true;
	try
	{
		cout << "{CLIENTE} Iniciando..." << endl;
		ClienteComandosTest * cliente = new ClienteComandosTest( "localhost", 43235 );
		string sRespuesta = "";
		cliente->EnviarMensaje( "CMD1", sRespuesta );
		if ( sRespuesta.compare( "Ok" ) != 0 )
		{
			cout << "Respuesta inesperada 1:[" <<  sRespuesta << "]" << endl;
			bRes = false;
		}
		sRespuesta = "";
		cliente->EnviarMensaje( "CMD2", sRespuesta );
		if ( sRespuesta.compare( "Ko" ) != 0 )
		{
			cout << "Respuesta inesperada 2:[" <<  sRespuesta << "]" << endl;
			bRes = false;
		}
		cliente->EnviarMensaje( "CMD3", sRespuesta );
		if ( sRespuesta.compare( "Comando invalido" ) != 0 )
		{
			cout << "Respuesta inesperada 3:[" <<  sRespuesta << "]" << endl;
			bRes = false;
		}
		cliente->EnviarMensaje( "1 C%MD3", sRespuesta );
		if ( sRespuesta.compare( "Error de sintaxis" ) != 0 )
		{
			cout << "Respuesta inesperada 4:[" <<  sRespuesta << "]" << endl;
			bRes = false;
		}
		cliente->EnviarMensaje( "FIN", sRespuesta );
		if ( sRespuesta.compare( "Adios" ) != 0 )
		{
			cout << "Respuesta inesperada 5:[" <<  sRespuesta << "]" << endl;
			bRes = false;
		}
		delete cliente;
	}
	catch ( ... )
	{
		cout << "{CLIENTE} Excepcion indefinida" << endl;
		bRes = false;
	}
	_bResTestComandosCliente = bRes;
	cout << "{CLIENTE} Fin" << endl;
}


static bool TestClienteServidorComandos01 ()
{
	cout << "Test ClienteServidorComandos 01:" << endl;
	bool bRes = true;

	try
	{
		thread thServidor ( Servidor1 );
		Esperar( 500 );
		if ( servidorTestComandos->EsValido() ) 
		{
			Esperar( 2000 );
			thread thCliente1 ( Cliente1 );
			thCliente1.join();
		}
		else
		{
			bRes = false;
		}
		cout << "Parando servidorTestComandos..." << endl;
		servidorTestComandos->Parar();
		thServidor.join();
		bRes = bRes && _bResTestComandosServidor && _bResTestComandosCliente;
		if ( !bRes )
		{
			cout << "Resultado Servidor=" << ToString( _bResTestComandosServidor ) << endl;
			cout << "Resultado Cliente1=" << ToString( _bResTestComandosCliente ) << endl;
		}
		delete servidorTestComandos;
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

bool TestClienteServidorComandos ()
{
	bool bResTestComandos = true;
	cout << endl << ANSI::AMARILLO << "[Test ClienteServidorComandos]" << ANSI::RESETEAR << endl;
	if ( TestClienteServidorComandos01() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bResTestComandos = false;
	}
	cout << ANSI::AMARILLO << "[Fin]" << ANSI::RESETEAR << endl;	
	return ( bResTestComandos );
}

