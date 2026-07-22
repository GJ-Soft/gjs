#include "CppCommonIo.h"

#include <CppBase.h>


using namespace std;
using namespace org::gjs::cpp::common;


static const string FICHERO_USUARIO = "../data/usuarios.info";


static bool _bResTestSesionCliente1 = false;
static bool _bResTestSesionCliente2 = false;
static bool _bResTestSesionServidor = false;


class ServidorSesionTest : public ServidorSesion
{
private:
	const string MSJ_FIN = "Adios";
	const string MSJ_COMANDO_INVALIDO = "Comando invalido";
	const string MSJ_ERROR_SINTACTICO = "Error de sintaxis";
	const string MSJ_VACIO = "";
	const string MSJ_OK = "Ok";
	const string MSJ_IMPOSIBLE_ABRIR_SESION = "Imposible abrir la sesion";
	const string MSJ_USUARIO_INVALIDO = "Usuario/clave invalidos";
	const string MSJ_SESION_NO_ABIERTA = "No hay una sesion abierta";

public:
	ServidorSesionTest( int iPuerto ) : ServidorSesion( iPuerto, FICHERO_USUARIO )
	{
	}

	virtual ~ServidorSesionTest()
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

	string MensajeSesionAbierta()
	{
		return( MSJ_OK );
	}

	string MensajeSesionCerrada()
	{
		return( MSJ_OK );
	}

	string MensajeFaltaClave()
	{
		return( MSJ_VACIO );
	}

	string MensajeImposibleAperturaSesion()
	{
		return( MSJ_IMPOSIBLE_ABRIR_SESION );
	}

	string MensajeUsuarioInvalido()
	{
		return( MSJ_USUARIO_INVALIDO );
	}

	string MensajeSesionNoAbierta()
	{
		return( MSJ_SESION_NO_ABIERTA );
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
		return ( comando.isComando( "ABRIR" ) ||
					comando.isComando( "CERRAR" ) ||
					comando.isComando( "CMD1" ) ||
					comando.isComando( "CMD2" ) ||
					comando.isComando( "FIN" ) );
	}

	bool EsComandoFin( Comando & comando, bool & bResponder )
	{
		return ( comando.isComando( "FIN" ) );
	}

	bool EsComandoInicioSesion( Comando & comando, string & sUsuario, string & sClave )
	{
		bool bRes = false;
		if ( comando.isComando( "ABRIR" ) &&
			 ( comando.NumArgumentos() == 2 ) )
		{
			bRes = true;
			sUsuario = comando.getArgumento( 0 );
			sClave = comando.getArgumento( 1 );
		}
		cout << "{SERVIDOR} InicioSesion=" << ToString( bRes ) << ": Usuario=[" << sUsuario << "]; Clave=[" << sClave << "]" << endl;
		return( bRes );
	}

	bool EsComandoFinSesion( Comando & comando )
	{
		return( comando.isComando( "CERRAR" ) &&
			 ( comando.NumArgumentos() == 0 ) );
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
		_bResTestSesionServidor = false;
		cout << "{SERVIDOR} Excepcion recibida: " << ex.what() << endl;
		return( true );
	}

	void ExcepcionProducidaEnPeticion( const exception & ex )
	{
		_bResTestSesionServidor = false;
		cout << "{SERVIDOR} Excepcion recibida: " << ex.what() << endl;
	}

};

class ClienteSesionTest : public ClienteSesion
{
private:
	list<ResultadoComando> 	comandoApertura;
	ResultadoComando 		comandoCierre;

public:
	ClienteSesionTest( const string & sIP, int iPuerto, const string & _sUsuario, const string & _sClave = "" ) : ClienteSesion( sIP, iPuerto, _sUsuario, _sClave )
	{
		ModificadoUsuario();
	}

	virtual ~ClienteSesionTest()
	{
	}

private:

	list<ResultadoComando> & ComandoInicioSesion()
	{
		return( comandoApertura );
	}

	ResultadoComando & ComandoFinSesion()
	{
		return( comandoCierre );
	}

	void ModificadoUsuario()
	{
		comandoApertura.clear();
		comandoApertura.push_back( ResultadoComando( "ABRIR", { getUsuario(), getClave() }, "Ok" ) );
		comandoCierre.setComando( "CERRAR" );
		comandoCierre.setRespuestaEsperada( "Ok" );
	}

	void ExcepcionProducida( const exception & ex )
	{
		cout << "{CLIENTE} Excepcion recibida: " << ex.what() << endl;
	}

};


class ServidorSesionTest2 : public ServidorSesion
{
private:
	const string MSJ_FIN = "Adios";
	const string MSJ_COMANDO_INVALIDO = "Comando invalido";
	const string MSJ_ERROR_SINTACTICO = "Error de sintaxis";
	const string MSJ_VACIO = "";
	const string MSJ_OK = "Ok";

public:
	ServidorSesionTest2( int iPuerto ) : ServidorSesion( iPuerto )
	{
	}

	virtual ~ServidorSesionTest2()
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

	string MensajeSesionAbierta()
	{
		return( MSJ_VACIO );
	}

	string MensajeSesionCerrada()
	{
		return( MSJ_VACIO );
	}

	string MensajeFaltaClave()
	{
		return( MSJ_VACIO );
	}

	string MensajeImposibleAperturaSesion()
	{
		return( MSJ_VACIO );
	}

	string MensajeUsuarioInvalido()
	{
		return( MSJ_VACIO );
	}

	string MensajeSesionNoAbierta()
	{
		return( MSJ_VACIO );
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
					comando.isComando( "FIN" ) );
	}

	bool EsComandoFin( Comando & comando, bool & bResponder )
	{
		return ( comando.isComando( "FIN" ) );
	}

	bool EsComandoInicioSesion( Comando & comando, string & sUsuario, string & sClave )
	{
		return( false );
	}

	bool EsComandoFinSesion( Comando & comando )
	{
		return( false );
	}

	void SesionIniciada( const string & sUsuario )
	{
	}

	void SesionFinalizada( const string & sUsuario )
	{
	}

	void ProcesarComandoSesion( Comando & comando, bool & bResponder, string & sRespuesta, bool & bResultado, SocketAbierto * socket )
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
		_bResTestSesionServidor = false;
		cout << "{SERVIDOR} Excepcion recibida: " << ex.what() << endl;
		return( true );
	}

	void ExcepcionProducidaEnPeticion( const exception & ex )
	{
		_bResTestSesionServidor = false;
		cout << "{SERVIDOR} Excepcion recibida: " << ex.what() << endl;
	}

};

class ClienteSesionTest2 : public ClienteSesion
{
private:
	list<ResultadoComando> 	comandoApertura;
	ResultadoComando 		comandoCierre;

public:
	ClienteSesionTest2( const string & sIP, int iPuerto ) : ClienteSesion( sIP, iPuerto )
	{
		ModificadoUsuario();
	}

	virtual ~ClienteSesionTest2()
	{
	}

private:

	list<ResultadoComando> & ComandoInicioSesion()
	{
		return( comandoApertura );
	}

	ResultadoComando & ComandoFinSesion()
	{
		return( comandoCierre );
	}

	void ModificadoUsuario()
	{
	}

	void ExcepcionProducida( const exception & ex )
	{
		cout << "{CLIENTE} Excepcion recibida: " << ex.what() << endl;
	}

};

class ServidorSesionTest3 : public ServidorSesion
{
private:
	const string MSJ_FIN = "Adios";
	const string MSJ_COMANDO_INVALIDO = "Comando invalido";
	const string MSJ_ERROR_SINTACTICO = "Error de sintaxis";
	const string MSJ_VACIO = "";
	const string MSJ_OK = "Ok";
	const string MSJ_IMPOSIBLE_ABRIR_SESION = "Imposible abrir la sesion";
	const string MSJ_USUARIO_INVALIDO = "Usuario/clave invalidos";
	const string MSJ_SESION_NO_ABIERTA = "No hay una sesion abierta";

public:
	ServidorSesionTest3( int iPuerto ) : ServidorSesion( iPuerto, FICHERO_USUARIO, "", true )
	{
	}

	virtual ~ServidorSesionTest3()
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

	string MensajeSesionAbierta()
	{
		return( MSJ_OK );
	}

	string MensajeSesionCerrada()
	{
		return( MSJ_OK );
	}

	string MensajeFaltaClave()
	{
		return( MSJ_VACIO );
	}

	string MensajeImposibleAperturaSesion()
	{
		return( MSJ_IMPOSIBLE_ABRIR_SESION );
	}

	string MensajeUsuarioInvalido()
	{
		return( MSJ_USUARIO_INVALIDO );
	}

	string MensajeSesionNoAbierta()
	{
		return( MSJ_SESION_NO_ABIERTA );
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
		return ( comando.isComando( "ABRIR" ) ||
					comando.isComando( "CERRAR" ) ||
					comando.isComando( "CMD1" ) ||
					comando.isComando( "CMD2" ) ||
					comando.isComando( "FIN" ) );
	}

	bool EsComandoFin( Comando & comando, bool & bResponder )
	{
		return ( comando.isComando( "FIN" ) );
	}

	bool EsComandoInicioSesion( Comando & comando, string & sUsuario, string & sClave )
	{
		bool bRes = false;
		if ( comando.isComando( "ABRIR" ) &&
			 ( ( comando.NumArgumentos() == 1 ) || ( comando.NumArgumentos() == 2 ) ) )
		{
			bRes = true;
			sUsuario = comando.getArgumento( 0 );
			if ( comando.NumArgumentos() == 2 )
			{
				sClave = comando.getArgumento( 1 );
			}
		}
		cout << "{SERVIDOR} InicioSesion=" << ToString( bRes ) << ": Usuario=[" << sUsuario << "]; Clave=[" << sClave << "]" << endl;
		return( bRes );
	}

	bool EsComandoFinSesion( Comando & comando )
	{
		return( comando.isComando( "CERRAR" ) &&
			 ( comando.NumArgumentos() == 0 ) );
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
		_bResTestSesionServidor = false;
		cout << "{SERVIDOR} Excepcion recibida: " << ex.what() << endl;
		return( true );
	}

	void ExcepcionProducidaEnPeticion( const exception & ex )
	{
		_bResTestSesionServidor = false;
		cout << "{SERVIDOR} Excepcion recibida: " << ex.what() << endl;
	}

};

static ServidorSesionTest * servidorTestSesion = NULL;
static ServidorSesionTest2 * servidorTestSesion2 = NULL;
static ServidorSesionTest3 * servidorTestSesion3 = NULL;


static void Servidor1()
{
	try
	{
		servidorTestSesion = new ServidorSesionTest( 44236 );
		if ( servidorTestSesion->EsValido() )
		{

			cout << "{SERVIDOR} Iniciando bucle de espera..." << endl;
			servidorTestSesion->Iniciar();
			_bResTestSesionServidor = true;
		}
		else
		{
			cout << "{SERVIDOR} No se ha inicializado bien el servidorTestSesion" << endl;
		}
	}
	catch ( exception & ex )
	{
		cout << "{SERVIDOR} Se ha producido una excepcion :" << ex.what () << endl;
		_bResTestSesionServidor = false;
	}
	catch ( ... )
	{
		cout << "{SERVIDOR} Excepcion indefinida" << endl;
		_bResTestSesionServidor = false;
	}
}

static void Cliente1()
{
	bool bRes = true;
	try
	{
		cout << "{CLIENTE1} Iniciando..." << endl;
		ClienteSesionTest * cliente = new ClienteSesionTest( "localhost", 44236, "vladimiro", "patin1" );
		string sRespuesta = "";
		cliente->EnviarMensaje( "CMD2", sRespuesta );
		if ( sRespuesta.compare( "" ) != 0 )
		{
			cout << "Respuesta inesperada:[" <<  sRespuesta << "]" << endl;
			bRes = false;
		}
		cout << "{CLIENTE1} Abriendo sesion..." << endl;
		cliente->AbrirSesion();
		if ( cliente->SesionAbierta() )
		{
			cout << "{CLIENTE1} Sesion abierta" << endl;
			cliente->EnviarMensaje( "CMD1", sRespuesta );
			cout << "{CLIENTE1} Mensaje recibido: [" << sRespuesta << "]" << endl;
			if ( sRespuesta.compare( "Ok" ) != 0 )
			{
				cout << "Respuesta inesperada:[" <<  sRespuesta << "]" << endl;
				bRes = false;
			}
			Esperar( 100 );
			sRespuesta = "";
			cliente->EnviarMensaje( "CMD2", sRespuesta );
			cout << "{CLIENTE1} Mensaje recibido: [" << sRespuesta << "]" << endl;
			if ( sRespuesta.compare( "Ko" ) != 0 )
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
	_bResTestSesionCliente1 = bRes;
	cout << "{CLIENTE1} Fin" << endl;
}

static void Cliente2()
{
	_bResTestSesionCliente2 = false;
	try
	{
		cout << "{CLIENTE2} Iniciando..." << endl;
		ClienteSesionTest * cliente = new ClienteSesionTest( "localhost", 44236, "volodimir", "chiripitiflautico" );
		string sRespuesta = "";
		cout << "{CLIENTE2} Abriendo sesion..." << endl;
		cliente->AbrirSesion();
		if ( !cliente->SesionAbierta() )
		{
			_bResTestSesionCliente2 = true;
		}
		else
		{
			cout << "{CLIENTE2} No se ha podido abrir la sesion" << endl;
		}
		delete cliente;
	}
	catch ( ... )
	{
		cout << "{CLIENTE2} Excepcion indefinida" << endl;
	}
	cout << "{CLIENTE2} Fin" << endl;
}

static void Servidor2()
{
	try
	{
		servidorTestSesion2 = new ServidorSesionTest2( 44237 );
		if ( servidorTestSesion2->EsValido() )
		{

			cout << "{SERVIDOR2} Iniciando bucle de espera..." << endl;
			servidorTestSesion2->Iniciar();
			_bResTestSesionServidor = true;
		}
		else
		{
			cout << "{SERVIDOR2} No se ha inicializado bien el servidorTestSesion" << endl;
		}
	}
	catch ( exception & ex )
	{
		cout << "{SERVIDOR2} Se ha producido una excepcion :" << ex.what () << endl;
		_bResTestSesionServidor = false;
	}
	catch ( ... )
	{
		cout << "{SERVIDO2R} Excepcion indefinida" << endl;
		_bResTestSesionServidor = false;
	}
}

static void Cliente3()
{
	bool bRes = true;
	try
	{
		cout << "{CLIENTE3} Iniciando..." << endl;
		ClienteSesionTest2 * cliente = new ClienteSesionTest2( "localhost", 44237 );
		string sRespuesta = "";
		cliente->EnviarMensaje( "CMD1", sRespuesta );
		cout << "{CLIENTE3} Mensaje recibido: [" << sRespuesta << "]" << endl;
		if ( sRespuesta.compare( "Ok" ) != 0 )
		{
			cout << "Respuesta inesperada:[" <<  sRespuesta << "]" << endl;
			bRes = false;
		}
		Esperar( 100 );
		sRespuesta = "";
		cliente->EnviarMensaje( "CMD2", sRespuesta );
		cout << "{CLIENTE3} Mensaje recibido: [" << sRespuesta << "]" << endl;
		if ( sRespuesta.compare( "Ko" ) != 0 )
		{
			cout << "Respuesta inesperada:[" <<  sRespuesta << "]" << endl;
			bRes = false;
		}
		delete cliente;
	}
	catch ( ... )
	{
		cout << "{CLIENTE3} Excepcion indefinida" << endl;
		bRes = false;
	}
	_bResTestSesionCliente1 = bRes;
	cout << "{CLIENTE3} Fin" << endl;
}

static void Servidor3()
{
	try
	{
		servidorTestSesion3 = new ServidorSesionTest3( 44240 );
		if ( servidorTestSesion3->EsValido() )
		{

			cout << "{SERVIDOR} Iniciando bucle de espera..." << endl;
			servidorTestSesion3->Iniciar();
			_bResTestSesionServidor = true;
		}
		else
		{
			cout << "{SERVIDOR} No se ha inicializado bien el servidorTestSesion" << endl;
		}
	}
	catch ( exception & ex )
	{
		cout << "{SERVIDOR} Se ha producido una excepcion :" << ex.what () << endl;
		_bResTestSesionServidor = false;
	}
	catch ( ... )
	{
		cout << "{SERVIDOR} Excepcion indefinida" << endl;
		_bResTestSesionServidor = false;
	}
}

static void Cliente4()
{
	bool bRes = true;
	try
	{
		cout << "{CLIENTE4} Iniciando..." << endl;
		ClienteSesionTest * cliente = new ClienteSesionTest( "localhost", 44240, "" );
		cliente->setUsuarioAnonimo();
		string sRespuesta = "";
		cout << "{CLIENTE4} Abriendo sesion..." << endl;
		cliente->AbrirSesion();
		if ( cliente->SesionAbierta() )
		{
			cout << "{CLIENTE4} Sesion abierta" << endl;
			cliente->EnviarMensaje( "CMD1", sRespuesta );
			cout << "{CLIENTE4} Mensaje recibido: [" << sRespuesta << "]" << endl;
			if ( sRespuesta.compare( "Ok" ) != 0 )
			{
				cout << "Respuesta inesperada:[" <<  sRespuesta << "]" << endl;
				bRes = false;
			}
			Esperar( 100 );
			sRespuesta = "";
			cliente->EnviarMensaje( "CMD2", sRespuesta );
			cout << "{CLIENTE4} Mensaje recibido: [" << sRespuesta << "]" << endl;
			if ( sRespuesta.compare( "Ko" ) != 0 )
			{
				cout << "Respuesta inesperada:[" <<  sRespuesta << "]" << endl;
				bRes = false;
			}
			Esperar( 100 );
			sRespuesta = "";
			cout << "{CLIENTE4} Cerrando sesion..." << endl;
			cliente->CerrarSesion();
			if ( cliente->SesionAbierta() )
			{
				cout << "{CLIENTE4} No se ha podido cerrar la sesion" << endl;
				bRes = false;
			}
		}
		else
		{
			cout << "{CLIENTE4} No se ha podido abrir la sesion" << endl;
			bRes = false;
		}
		delete cliente;
	}
	catch ( ... )
	{
		cout << "{CLIENTE4} Excepcion indefinida" << endl;
		bRes = false;
	}
	_bResTestSesionCliente2 = bRes;
	cout << "{CLIENTE4} Fin" << endl;
}

static void Cliente5()
{
	bool bRes = true;
	try
	{
		cout << "{CLIENTE5} Iniciando..." << endl;
		ClienteSesionTest * cliente = new ClienteSesionTest( "localhost", 44240, "vladimiro", "patin1" );
		string sRespuesta = "";
		cliente->EnviarMensaje( "CMD2", sRespuesta );
		if ( sRespuesta.compare( "" ) != 0 )
		{
			cout << "Respuesta inesperada:[" <<  sRespuesta << "]" << endl;
			bRes = false;
		}
		cout << "{CLIENTE5} Abriendo sesion..." << endl;
		cliente->AbrirSesion();
		if ( cliente->SesionAbierta() )
		{
			cout << "{CLIENTE5} Sesion abierta" << endl;
			cliente->EnviarMensaje( "CMD1", sRespuesta );
			cout << "{CLIENTE5} Mensaje recibido: [" << sRespuesta << "]" << endl;
			if ( sRespuesta.compare( "Ok" ) != 0 )
			{
				cout << "Respuesta inesperada:[" <<  sRespuesta << "]" << endl;
				bRes = false;
			}
			Esperar( 100 );
			sRespuesta = "";
			cliente->EnviarMensaje( "CMD2", sRespuesta );
			cout << "{CLIENTE5} Mensaje recibido: [" << sRespuesta << "]" << endl;
			if ( sRespuesta.compare( "Ko" ) != 0 )
			{
				cout << "Respuesta inesperada:[" <<  sRespuesta << "]" << endl;
				bRes = false;
			}
			Esperar( 100 );
			sRespuesta = "";
			cout << "{CLIENTE5} Cerrando sesion..." << endl;
			cliente->CerrarSesion();
			if ( cliente->SesionAbierta() )
			{
				cout << "{CLIENTE5} No se ha podido cerrar la sesion" << endl;
				bRes = false;
			}
		}
		else
		{
			cout << "{CLIENTE5} No se ha podido abrir la sesion" << endl;
			bRes = false;
		}
		delete cliente;
	}
	catch ( ... )
	{
		cout << "{CLIENTE5} Excepcion indefinida" << endl;
		bRes = false;
	}
	_bResTestSesionCliente1 = bRes;
	cout << "{CLIENTE5} Fin" << endl;
}


static bool TestClienteServidorSesion01 ()
{
	cout << "Test ClienteServidorSesion 01:" << endl;
	bool bRes = true;

	try
	{
		thread thServidor ( Servidor1 );
		Esperar( 500 );
		if ( servidorTestSesion->EsValido() )
		{
			Esperar( 2000 );
			thread thCliente1 ( Cliente1 );
			thCliente1.join();
			thread thCliente2 ( Cliente2 );
			thCliente2.join();
		}
		else
		{
			bRes = false;
		}
		cout << "Parando servidorTestSesion..." << endl;
		servidorTestSesion->Parar();
		thServidor.join();
		bRes = bRes && _bResTestSesionServidor && _bResTestSesionCliente1 && _bResTestSesionCliente2;
		if ( !bRes )
		{
			cout << "Resultado Servidor=" << ToString( _bResTestSesionServidor ) << endl;
			cout << "Resultado Cliente1=" << ToString( _bResTestSesionCliente1 ) << endl;
			cout << "Resultado Cliente2=" << ToString( _bResTestSesionCliente2 ) << endl;
		}
		delete servidorTestSesion;
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

static bool TestClienteServidorSesion02 ()
{
	cout << "Test ClienteServidorSesion 02:" << endl;
	bool bRes = true;

	_bResTestSesionServidor = false;
	_bResTestSesionCliente1 = false;
	try
	{
		thread thServidor ( Servidor2 );
		Esperar( 500 );
		if ( servidorTestSesion2->EsValido() )
		{
			Esperar( 2000 );
			thread thCliente ( Cliente3 );
			thCliente.join();
		}
		else
		{
			bRes = false;
		}
		cout << "Parando servidorTestSesion..." << endl;
		servidorTestSesion2->Parar();
		thServidor.join();
		bRes = bRes && _bResTestSesionServidor && _bResTestSesionCliente1;
		if ( !bRes )
		{
			cout << "Resultado Servidor=" << ToString( _bResTestSesionServidor ) << endl;
			cout << "Resultado Cliente=" << ToString( _bResTestSesionCliente1 ) << endl;
		}
		delete servidorTestSesion2;
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

static bool TestClienteServidorSesion03 ()
{
	cout << "Test ClienteServidorSesion 03:" << endl;
	bool bRes = true;

	_bResTestSesionServidor = false;
	_bResTestSesionCliente1 = false;
	_bResTestSesionCliente2 = false;
	try
	{
		thread thServidor ( Servidor3 );
		Esperar( 500 );
		if ( servidorTestSesion3->EsValido() )
		{
			Esperar( 2000 );
			thread thCliente1 ( Cliente4 );
			thCliente1.join();
			thread thCliente2 ( Cliente5 );
			thCliente2.join();
		}
		else
		{
			bRes = false;
		}
		cout << "Parando servidorTestSesion..." << endl;
		servidorTestSesion3->Parar();
		thServidor.join();
		bRes = bRes && _bResTestSesionServidor && _bResTestSesionCliente1 && _bResTestSesionCliente2;
		if ( !bRes )
		{
			cout << "Resultado Servidor=" << ToString( _bResTestSesionServidor ) << endl;
			cout << "Resultado Cliente1=" << ToString( _bResTestSesionCliente1 ) << endl;
			cout << "Resultado Cliente2=" << ToString( _bResTestSesionCliente2 ) << endl;
		}
		delete servidorTestSesion3;
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


bool TestClienteServidorSesion ()
{
	bool bResTestSesion = true;
	cout << endl << ANSI::AMARILLO << "[Test ClienteServidorSesion]" << ANSI::RESETEAR << endl;
	if ( TestClienteServidorSesion01() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bResTestSesion = false;
	}
	if ( TestClienteServidorSesion02() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bResTestSesion = false;
	}
	if ( TestClienteServidorSesion03() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bResTestSesion = false;
	}
	cout << ANSI::AMARILLO << "[Fin]" << ANSI::RESETEAR << endl;
	return ( bResTestSesion );
}

