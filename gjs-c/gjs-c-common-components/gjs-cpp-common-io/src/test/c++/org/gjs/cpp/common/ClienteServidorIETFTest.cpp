#include "CppCommonIo.h"
#include <CppBase.h>




using namespace std;
using namespace org::gjs::cpp::common;


static const string FICHERO_USUARIO = "../../test-classes/data/usuarios.info";
static const list<string> COMANDOS_TEST1( { "ADD", "GET", IETF_CMD_REINICIALIZAR, IETF_CMD_AYUDA, IETF_CMD_NADA, IETF_CMD_SALIR } );


static bool _bResTestIETFCliente1 = false;
static bool _bResTestIETFServidor = false;




class ServidorIETFTest : public ServidorIETF
{
private:
	int iCont = 0;
	
public:
	ServidorIETFTest( int iPuerto ) : ServidorIETF( iPuerto, COMANDOS_TEST1, FICHERO_USUARIO )
	{
	}
	
	virtual ~ServidorIETFTest()
	{
	}
	
private:
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
		return ( ServidorIETF::EsComandoValido( comando ) );
	}
	
	void SesionIniciada( const string & sUsuario )
	{
		cout << "{SERVIDOR} Inicio sesion de [" << sUsuario << "]" << endl;
	}
	
	void SesionFinalizada( const string & sUsuario )
	{
		cout << "{SERVIDOR} Fin sesion de [" << sUsuario << "]" << endl;
	}

	void ProcesarComandoSesion( Comando & comando, bool & bResponder, string & sRespuesta, bool & bResultado, SocketAbierto * socket ) 
	{
		try
		{
			bResponder = true;
			if ( comando.isComando ( "ADD" ) )
			{
				bResultado = true;
				iCont = iCont + 1;
				sRespuesta = MensajeOk();
			}
			else if ( comando.isComando ( "GET" ) )
			{
				bResultado = true;
				sRespuesta = ToString( iCont );
			}
			else if ( comando.isComando ( IETF_CMD_REINICIALIZAR ) )
			{
				bResultado = true;
				iCont = 0;
				sRespuesta = MensajeOk();
			}
			else if ( comando.isComando ( IETF_CMD_AYUDA ) )
			{
				bResultado = true;
				sRespuesta = Concatenar( "Comandos: ADD, GET, ", IETF_CMD_REINICIALIZAR );
			}
			else if ( comando.isComando ( IETF_CMD_NADA ) )
			{
				bResultado = true;
				sRespuesta = MensajeOk();
			}
		}
		catch ( exception & ex )
		{
			cout << "{SERVIDOR} Excepcion inesperada: " << ex.what() << endl;
		}
	}
	
	bool ExcepcionProducida( const exception & ex )
	{
		_bResTestIETFServidor = false;
		cout << "{SERVIDOR} Excepcion recibida: " << ex.what() << endl;
		return( true );
	}
	
	void ExcepcionProducidaEnPeticion( const exception & ex )
	{
		_bResTestIETFServidor = false;
		cout << "{SERVIDOR} Excepcion recibida: " << ex.what() << endl;
	}

};

class ClienteIETFTest : public ClienteIETF
{
public:
	ClienteIETFTest( const string & sIP, int iPuerto, const string & _sUsuario, const string & _sClave = "" ) : ClienteIETF( sIP, iPuerto, _sUsuario, _sClave )
	{
	}
	
	virtual ~ClienteIETFTest()
	{
	}
	
private:
	
	void ExcepcionProducida( const exception & ex )
	{
		cout << "{CLIENTE} Excepcion recibida: " << ex.what() << endl;
	}

};




static ServidorIETFTest * servidorTestIETF = NULL;


static void Servidor1()
{
	try
	{
		servidorTestIETF = new ServidorIETFTest( 44238 );
		if ( servidorTestIETF->EsValido() ) 
		{

			cout << "{SERVIDOR} Iniciando bucle de espera..." << endl;			
			servidorTestIETF->Iniciar();
			_bResTestIETFServidor = true;
		}
		else
		{
			cout << "{SERVIDOR} No se ha inicializado bien el servidorTestIETF" << endl;
		}
	}
	catch ( exception & ex )
	{
		cout << "{SERVIDOR} Se ha producido una excepcion :" << ex.what () << endl;		
		_bResTestIETFServidor = false;
	}
	catch ( ... )
	{
		cout << "{SERVIDOR} Excepcion indefinida" << endl;
		_bResTestIETFServidor = false;
	}
}

static void Cliente1()
{
	bool bRes = true;
	try
	{
		cout << "{CLIENTE1} Iniciando..." << endl;
		ClienteIETFTest * cliente = new ClienteIETFTest( "localhost", 44238, "vladimiro", "patin1" );
		string sRespuesta = "";
		cout << "{CLIENTE1} Abriendo sesion..." << endl;
		cliente->AbrirSesion();
		if ( cliente->SesionAbierta() )
		{
			cout << "{CLIENTE1} Sesion abierta" << endl;
			cliente->EnviarMensaje( "GET", sRespuesta );
			cout << "{CLIENTE1} Mensaje recibido: [" << sRespuesta << "]" << endl;
			if ( sRespuesta.compare( "0" ) != 0 )
			{
				cout << "Respuesta inesperada:[" <<  sRespuesta << "]" << endl;
				bRes = false;
			}
			Esperar( 100 );
			sRespuesta = "";
			cliente->EnviarMensaje( "ADD", sRespuesta );
			cout << "{CLIENTE1} Mensaje recibido: [" << sRespuesta << "]" << endl;
			string sCodigo = "";
			string sMensaje = "";
			ProcesarRespuestaIETF( sRespuesta, sCodigo, sMensaje );
			if ( sCodigo.compare( IETF_OK ) != 0 )
			{
				cout << "Respuesta inesperada:[" <<  sRespuesta << "]" << endl;
				bRes = false;
			}
			Esperar( 100 );
			sRespuesta = "";
			cliente->EnviarMensaje( "GET", sRespuesta );
			cout << "{CLIENTE1} Mensaje recibido: [" << sRespuesta << "]" << endl;
			if ( sRespuesta.compare( "1" ) != 0 )
			{
				cout << "Respuesta inesperada:[" <<  sRespuesta << "]" << endl;
				bRes = false;
			}
			Esperar( 100 );
			sRespuesta = "";
			cliente->EnviarMensaje( "ADD", sRespuesta );
			cout << "{CLIENTE1} Mensaje recibido: [" << sRespuesta << "]" << endl;
			sCodigo = "";
			sMensaje = "";
			ProcesarRespuestaIETF( sRespuesta, sCodigo, sMensaje );
			if ( sCodigo.compare( IETF_OK ) != 0 )
			{
				cout << "Respuesta inesperada:[" <<  sRespuesta << "]" << endl;
				bRes = false;
			}
			Esperar( 100 );
			sRespuesta = "";
			cliente->EnviarMensaje( "ADD", sRespuesta );
			cout << "{CLIENTE1} Mensaje recibido: [" << sRespuesta << "]" << endl;
			sCodigo = "";
			sMensaje = "";
			ProcesarRespuestaIETF( sRespuesta, sCodigo, sMensaje );
			if ( sCodigo.compare( IETF_OK ) != 0 )
			{
				cout << "Respuesta inesperada:[" <<  sRespuesta << "]" << endl;
				bRes = false;
			}
			Esperar( 100 );
			sRespuesta = "";
			cliente->EnviarMensaje( "GET", sRespuesta );
			cout << "{CLIENTE1} Mensaje recibido: [" << sRespuesta << "]" << endl;
			if ( sRespuesta.compare( "3" ) != 0 )
			{
				cout << "Respuesta inesperada:[" <<  sRespuesta << "]" << endl;
				bRes = false;
			}
			Esperar( 100 );
			sRespuesta = "";
			cliente->EnviarMensaje( "NOOP", sRespuesta );
			cout << "{CLIENTE1} Mensaje recibido: [" << sRespuesta << "]" << endl;
			sCodigo = "";
			sMensaje = "";
			ProcesarRespuestaIETF( sRespuesta, sCodigo, sMensaje );
			if ( sCodigo.compare( IETF_OK ) != 0 )
			{
				cout << "Respuesta inesperada:[" <<  sRespuesta << "]" << endl;
				bRes = false;
			}
			Esperar( 100 );
			sRespuesta = "";
			cliente->EnviarMensaje( "HELP", sRespuesta );
			cout << "{CLIENTE1} Mensaje recibido: [" << sRespuesta << "]" << endl;
			if ( sRespuesta.compare( "Comandos: ADD, GET, REIN" ) != 0 )
			{
				cout << "Respuesta inesperada:[" <<  sRespuesta << "]" << endl;
				bRes = false;
			}
			Esperar( 100 );
			sRespuesta = "";
			cliente->EnviarMensaje( "GET", sRespuesta );
			cout << "{CLIENTE1} Mensaje recibido: [" << sRespuesta << "]" << endl;
			if ( sRespuesta.compare( "3" ) != 0 )
			{
				cout << "Respuesta inesperada:[" <<  sRespuesta << "]" << endl;
				bRes = false;
			}
			Esperar( 100 );
			sRespuesta = "";
			cliente->EnviarMensaje( "REIN", sRespuesta );
			cout << "{CLIENTE1} Mensaje recibido: [" << sRespuesta << "]" << endl;
			sCodigo = "";
			sMensaje = "";
			ProcesarRespuestaIETF( sRespuesta, sCodigo, sMensaje );
			if ( sCodigo.compare( IETF_OK ) != 0 )
			{
				cout << "Respuesta inesperada:[" <<  sRespuesta << "]" << endl;
				bRes = false;
			}
			Esperar( 100 );
			sRespuesta = "";
			cliente->EnviarMensaje( "GET", sRespuesta );
			cout << "{CLIENTE1} Mensaje recibido: [" << sRespuesta << "]" << endl;
			if ( sRespuesta.compare( "0" ) != 0 )
			{
				cout << "Respuesta inesperada:[" <<  sRespuesta << "]" << endl;
				bRes = false;
			}
			Esperar( 100 );
			sRespuesta = "";
			cout << "{CLIENTE1} Cerrando sesion..." << endl;
			cliente->CerrarSesion();
			if ( cliente->SesionAbierta() )
			{
				cout << "{CLIENTE1} No se ha podido cerrar la sesion" << endl;
				bRes = false;
			}		
		}
		else
		{
			cout << "{CLIENTE1} No se ha podido abrir la sesion" << endl;
			bRes = false;
		}
		delete cliente;
	}
	catch ( ... )
	{
		cout << "{CLIENTE1} Excepcion indefinida" << endl;
		bRes = false;
	}
	_bResTestIETFCliente1 = bRes;
	cout << "{CLIENTE1} Fin" << endl;
}

static bool TestClienteServidorIETF01 ()
{
	cout << "Test ClienteServidorIETF 01:" << endl;
	bool bRes = true;

	try
	{
		thread thServidor ( Servidor1 );
		Esperar( 500 );
		if ( servidorTestIETF->EsValido() ) 
		{
			Esperar( 2000 );
			thread thCliente1 ( Cliente1 );
			thCliente1.join();
		}
		else
		{
			bRes = false;
		}
		cout << "Parando servidorTestIETF..." << endl;
		servidorTestIETF->Parar();
		thServidor.join();
		bRes = bRes && _bResTestIETFServidor && _bResTestIETFCliente1;
		if ( !bRes )
		{
			cout << "Resultado Servidor=" << ToString( _bResTestIETFServidor ) << endl;
			cout << "Resultado Cliente1=" << ToString( _bResTestIETFCliente1 ) << endl;
		}
		delete servidorTestIETF;
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

bool TestClienteServidorIETF ()
{
	bool bResTestIETF = true;
	cout << endl << ANSI::AMARILLO << "[Test ClienteServidorIETF]" << ANSI::RESETEAR << endl;
	if ( TestClienteServidorIETF01() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bResTestIETF = false;
	}
	cout << ANSI::AMARILLO << "[Fin]" << ANSI::RESETEAR << endl;	
	return ( bResTestIETF );
}

