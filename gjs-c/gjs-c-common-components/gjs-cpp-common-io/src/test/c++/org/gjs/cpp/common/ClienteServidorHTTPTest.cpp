#include "CppCommonIo.h"
#include <CppBase.h>




using namespace std;
using namespace org::gjs::cpp::common;


static const string DIR_RECURSOS = "..";
static const string DIR_SERVIDOR_HTTP = "../servidorHTTP";
static const string DIR_CLIENTE_HTTP = "../results";

static string sDirRecursos;
static string sDirServidorHttp;
static string sDirClienteHttp;



static bool _bResTestHTTPCliente1 = false;
static bool _bResTestHTTPServidor = false;




class ServidorHTTPTest : public ServidorHTTP
{
private:
	int iCont = 0;
	
public:
	ServidorHTTPTest( int iPuerto ) : ServidorHTTP( iPuerto, sDirServidorHttp )
	{
	}
	
	virtual ~ServidorHTTPTest()
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
	
	bool ExcepcionProducida( const exception & ex )
	{
		_bResTestHTTPServidor = false;
		cout << "{SERVIDOR} Excepcion recibida: " << ex.what() << endl;
		return( true );
	}
	
	void ExcepcionProducidaEnPeticion( const exception & ex )
	{
		_bResTestHTTPServidor = false;
		cout << "{SERVIDOR} Excepcion recibida: " << ex.what() << endl;
	}

};




/* ClienteHTTP valida la URN antes de enviarla. Este manda el comando tal
   cual, para probar lo que hace el servidor con lo que el cliente no deja. */
class ClienteCrudoHTTP : public ClienteIETF
{
public:
	ClienteCrudoHTTP( int iPuerto ) : ClienteIETF( "localhost", iPuerto )
	{
	}

private:
	void ExcepcionProducida( const exception & ex )
	{
		cout << "{CLIENTE CRUDO} Excepcion recibida: " << ex.what() << endl;
	}
};


static ServidorHTTPTest * servidorTestHTTP = NULL;


static void Servidor1()
{
	try
	{
		servidorTestHTTP = new ServidorHTTPTest( 45301 );
		if ( servidorTestHTTP->EsValido() ) 
		{
			cout << "{SERVIDOR} Iniciando bucle de espera..." << endl;			
			servidorTestHTTP->Iniciar();
			_bResTestHTTPServidor = true;
		}
		else
		{
			cout << "{SERVIDOR} No se ha inicializado bien el servidorTestHTTP" << endl;
		}
	}
	catch ( exception & ex )
	{
		cout << "{SERVIDOR} Se ha producido una excepcion :" << ex.what () << endl;		
		_bResTestHTTPServidor = false;
	}
	catch ( ... )
	{
		cout << "{SERVIDOR} Excepcion indefinida" << endl;
		_bResTestHTTPServidor = false;
	}
}

static bool ValidarContenido( vector<string> vecContenido, initializer_list<string> lisEsperado )
{
	bool bRes = true;
	if ( vecContenido.size () != lisEsperado.size () )
	{
		cout << "Numero de lineas incorrecto: " << vecContenido.size () << endl;
		bRes = false;
	}	
	else
	{
		for ( int i = 0; i < vecContenido.size(); i = i + 1 )
		{
			string sLinea = Trim( EliminarTodos( vecContenido[ i ], '\t' ) );
			initializer_list<string>::iterator it = lisEsperado.begin() + i;
			string sEsperada = Trim( *it );
			if ( sLinea.compare( sEsperada ) != 0 )
			{
				cout << "Linea " << i + 1 << " incorrecta: [" << sLinea << "] - [" << sEsperada << "]" << endl;
				bRes = false;
			}
		}
	}	
	return( bRes );
}

static void Cliente1()
{
	bool bRes = true;
	try
	{
		cout << "{CLIENTE1} Iniciando..." << endl;
		ClienteHTTP * cliente = new ClienteHTTP( "localhost", 45301 );
		if ( cliente->EsValido() ) 
		{
			string sURN = "site1/index.html";
			string sFichero = Concatenar( sDirClienteHttp, "/test1.html" );
			if ( cliente->Get( sURN, sFichero ) )
			{
				cout << "{CLIENTE1} GET " << sURN << " realizado" << endl;
				if ( ExisteFichero( sFichero ) )
				{
					bRes = ValidarContenido( LeerFichero( sFichero ), { "<html>", "<head>", "<title>Prueba 1</title>", "</head>", "<body>", 
																		"<p>", "Hola mundo!", "</p>", "</body>", "</html>" } ) && bRes;
				}
				else
				{
					cout << "Fichero no descargado: [" <<  sFichero << "]" << endl;
					bRes = false;
				}
			}
			else
			{
				cout << "{CLIENTE1} No se ha podido acceder a " << sURN <<  endl;
				bRes = false;
			}
			Esperar( 100 );
			sURN = "site1/noexiste.html";
			if ( cliente->Get( sURN, sFichero ) )
			{
				cout << "{CLIENTE1} No debería haber podido acceder a " << sURN <<  endl;
				bRes = false;
			}
			Esperar( 100 );
			/* Salir de la raiz con "..": ClienteHTTP ya lo rechaza sin enviarlo,
			   asi que va en crudo por ClienteCrudoHTTP para que lo vea el servidor. El
			   destino existe ( la raiz es servidorHTTP, y su padre la contiene ),
			   asi que solo da error si el servidor rechaza la ruta. */
			ClienteCrudoHTTP clienteCrudo( 45301 );
			string sRespuesta;
			string sCodigo;
			string sResultado;
			sURN = "../servidorHTTP/site1/index.html";
			clienteCrudo.EnviarComando( IETF_CMD_METODO_GET, { sURN, "HTTP/1.1" }, sRespuesta );
			if ( !ProcesarRespuestaIETF( sRespuesta, sCodigo, sResultado ) )
			{
				cout << "{CLIENTE1} Sin respuesta valida a " << sURN << ": [" << sRespuesta << "]" << endl;
				bRes = false;
			}
			else if ( sCodigo.compare( IETF_OK ) == 0 )
			{
				cout << "{CLIENTE1} No debería haber podido salir de la raíz con " << sURN <<  endl;
				bRes = false;
			}
			Esperar( 100 );
			sURN = "site3/index.html";
			if ( cliente->Get( sURN, sFichero ) )
			{
				cout << "{CLIENTE1} No debería haber podido acceder a " << sURN <<  endl;
				bRes = false;
			}
			Esperar( 100 );
			sURN = "site1";
			sFichero = Concatenar( sDirClienteHttp, "/test2.html" );
			if ( cliente->Get( sURN, sFichero ) )
			{
				cout << "{CLIENTE1} GET " << sURN << " realizado" << endl;
				if ( ExisteFichero( sFichero ) )
				{
					bRes = ValidarContenido( LeerFichero( sFichero ), { "<html>", "<head>", "<title>Prueba 1</title>", "</head>", "<body>", 
																		"<p>", "Hola mundo!", "</p>", "</body>", "</html>" } ) && bRes;																		
				}
				else
				{
					cout << "Fichero no descargado: [" <<  sFichero << "]" << endl;
					bRes = false;
				}
			}
			else
			{
				cout << "{CLIENTE1} No se ha podido acceder a " << sURN <<  endl;
				bRes = false;
			}
			Esperar( 100 );
			sURN = "site2";
			if ( cliente->Get( sURN, sFichero ) )
			{
				cout << "{CLIENTE1} No debería haber podido acceder a " << sURN <<  endl;
				bRes = false;
			}
			Esperar( 100 );
			sURN = "site1/pagina1";
			sFichero = Concatenar( sDirClienteHttp, "/test3.html" );
			if ( cliente->Get( sURN, sFichero ) )
			{
				cout << "{CLIENTE1} GET " << sURN << " realizado" << endl;
				if ( ExisteFichero( sFichero ) )
				{
					bRes = ValidarContenido( LeerFichero( sFichero ), { "<html>", "<head>", "<title>Pagina 1</title>", "</head>", "<body>", 
																		"<p>", "Esto es la página 1", "</p>", "</body>", "</html>" } ) && bRes;
				}
				else
				{
					cout << "Fichero no descargado: [" <<  sFichero << "]" << endl;
					bRes = false;
				}
			}
			else
			{
				cout << "{CLIENTE1} No se ha podido acceder a " << sURN <<  endl;
				bRes = false;
			}
			Esperar( 100 );
			sURN = "site1/subsite1/pagina3.html";
			sFichero = Concatenar( sDirClienteHttp, "/test4.html" );
			if ( cliente->Get( sURN, sFichero ) )
			{
				cout << "{CLIENTE1} GET " << sURN << " realizado" << endl;
				if ( ExisteFichero( sFichero ) )
				{
					bRes = ValidarContenido( LeerFichero( sFichero ), { "<html>", "<head>", "<title>Pagina 3</title>", "</head>", "<body>", 
																		"<p>", "Esto es la pagina 3", "</p>", "</body>", "</html>" } ) && bRes;
				}
				else
				{
					cout << "Fichero no descargado: [" <<  sFichero << "]" << endl;
					bRes = false;
				}
			}
			else
			{
				cout << "{CLIENTE1} No se ha podido acceder a " << sURN <<  endl;
				bRes = false;
			}
		}
		else
		{
			cout << "{CLIENTE1} No se ha inicializado correctamente" <<  endl;
			bRes = false;
		}
		delete cliente;
	}
	catch ( ... )
	{
		cout << "{CLIENTE1} Excepcion indefinida" << endl;
		bRes = false;
	}
	_bResTestHTTPCliente1 = bRes;
	cout << "{CLIENTE1} Fin" << endl;
}

static bool TestClienteServidorHTTP01 ()
{
	cout << "Test ClienteServidorHTTP 01:" << endl;
	bool bRes = true;

	try
	{
		thread thServidor ( Servidor1 );
		Esperar( 500 );
		if ( servidorTestHTTP->EsValido() ) 
		{
			Esperar( 2000 );
			thread thCliente1 ( Cliente1 );
			thCliente1.join();
		}
		else
		{
			bRes = false;
		}
		cout << "Parando servidorTestHTTP..." << endl;
		servidorTestHTTP->Parar();
		thServidor.join();
		bRes = bRes && _bResTestHTTPServidor && _bResTestHTTPCliente1;
		if ( !bRes )
		{
			cout << "Resultado Servidor=" << ToString( _bResTestHTTPServidor ) << endl;
			cout << "Resultado Cliente1=" << ToString( _bResTestHTTPCliente1 ) << endl;
		}
		delete servidorTestHTTP;
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

bool TestClienteServidorHTTP ()
{
	bool bResTestHTTP = true;
	sDirRecursos = ResolverDirectorioRelativo( DirectorioActual(), DIR_RECURSOS );
	sDirServidorHttp = ResolverDirectorioRelativo( DirectorioActual(), DIR_SERVIDOR_HTTP );
	sDirClienteHttp = ResolverDirectorioRelativo( DirectorioActual(), DIR_CLIENTE_HTTP );
	cout << DirectorioActual() << endl;
	cout << sDirServidorHttp << endl;
	cout << endl << ANSI::AMARILLO << "[Test ClienteServidorHTTP]" << ANSI::RESETEAR << endl;
	if ( TestClienteServidorHTTP01() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bResTestHTTP = false;
	}
	cout << ANSI::AMARILLO << "[Fin]" << ANSI::RESETEAR << endl;	
	return ( bResTestHTTP );
}

