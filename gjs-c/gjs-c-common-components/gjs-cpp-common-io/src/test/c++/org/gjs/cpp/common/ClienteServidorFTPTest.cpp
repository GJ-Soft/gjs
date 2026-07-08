#include "CppCommonIo.h"
#include <CppBase.h>




using namespace std;
using namespace org::gjs::cpp::common;


static const string DIR_RECURSOS = "../../test-classes";
static const string FICHERO_USUARIO = "../../test-classes/data/usuarios.info";
static const string DIR_SERVIDOR_FTP = "../../test-classes/servidorFTP";
static const string DIR_CLIENTE_FTP = "../results";

static string sDirTest;
static string sDirRecursos;
static string sFicheroUsuario;
static string sDirServidorFtp;
static string sDirClienteFtp;



static bool _bResTestFTPCliente1 = false;
static bool _bResTestFTPServidor = false;




class ServidorFTPTest : public ServidorFTP
{
private:
	int iCont = 0;
	
public:
	ServidorFTPTest( int iPuerto, int iPuertoDatos ) : ServidorFTP( iPuerto, iPuertoDatos, sDirServidorFtp, sFicheroUsuario )
	{
	}
	
	virtual ~ServidorFTPTest()
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

	void SesionIniciada( const string & sUsuario )
	{
		cout << "{SERVIDOR} Inicio sesion de [" << sUsuario << "]" << endl;
	}
	
	void SesionFinalizada( const string & sUsuario )
	{
		cout << "{SERVIDOR} Fin sesion de [" << sUsuario << "]" << endl;
	}
	
	bool ExcepcionProducida( const exception & ex )
	{
		_bResTestFTPServidor = false;
		cout << "{SERVIDOR} Excepcion recibida: " << ex.what() << endl;
		return( true );
	}
	
	void ExcepcionProducidaEnPeticion( const exception & ex )
	{
		_bResTestFTPServidor = false;
		cout << "{SERVIDOR} Excepcion recibida: " << ex.what() << endl;
	}

};




static ServidorFTPTest * servidorTestFTP = NULL;


static void Servidor1()
{
	try
	{
		servidorTestFTP = new ServidorFTPTest( 44338, 44339 );
		if ( servidorTestFTP->EsValido() ) 
		{
			cout << "{SERVIDOR} Iniciando bucle de espera..." << endl;			
			servidorTestFTP->Iniciar();
			_bResTestFTPServidor = true;
		}
		else
		{
			cout << "{SERVIDOR} No se ha inicializado bien el servidorTestFTP" << endl;
		}
	}
	catch ( exception & ex )
	{
		cout << "{SERVIDOR} Se ha producido una excepcion :" << ex.what () << endl;		
		_bResTestFTPServidor = false;
	}
	catch ( ... )
	{
		cout << "{SERVIDOR} Excepcion indefinida" << endl;
		_bResTestFTPServidor = false;
	}
}

static void Cliente1()
{
	bool bRes = true;
	try
	{
		cout << "{CLIENTE1} Iniciando..." << endl;
		ClienteFTP * cliente = new ClienteFTP( "localhost", 44338, "vladimiro", "patin1" );
		cout << "{CLIENTE1} EsValido=" << ToString( cliente->EsValido() ) << endl;
		string sRespuesta = "";
		cout << "{CLIENTE1} Abriendo sesion..." << endl;
		cliente->AbrirSesion();
		if ( cliente->SesionAbierta() )
		{
			cout << "{CLIENTE1} Sesion abierta" << endl;
			string sDir = cliente->DirectorioRemoto();
			cout << "{CLIENTE1} Directorio remoto: [" << sDir << "]" << endl;
			if ( !TerminaPor( sDir, "/test-classes/servidorFTP" ) )
			{
				cout << "Directorio erroneo:[" <<  sDir << "]" << endl;
				bRes = false;
			}
			Esperar( 100 );
			string sSubdir( "." );
			string sDir1( "" );
			if ( cliente->CambiarDirectorioRemoto( sSubdir ) )
			{
				Esperar( 100 );
				sDir1 = cliente->DirectorioRemoto();
				cout << "{CLIENTE1} Directorio remoto: [" << sDir1 << "]" << endl;
				if ( sDir1.compare( sDir ) != 0 )
				{
					cout << "Directorio erroneo:[" <<  sDir1 << "]" << endl;
					bRes = false;
				}
			}
			else
			{
				cout << "Error cambiando a directorio: [" << sSubdir << "]" << endl;
				bRes = false;
			}
			Esperar( 100 );
			sSubdir = "carpeta1";
			if ( cliente->CambiarDirectorioRemoto( sSubdir ) )
			{
				Esperar( 100 );
				sDir1 = cliente->DirectorioRemoto();
				string sDirEsperado = Concatenar( sDir, "/carpeta1" );
				cout << "{CLIENTE1} Directorio remoto: [" << sDir1 << "]" << endl;
				if ( sDir1.compare( sDirEsperado ) != 0 )
				{
					cout << "Directorio erroneo:[" <<  sDir1 << "]" << endl;
					bRes = false;
				}
			}
			else
			{
				cout << "Error cambiando a directorio: [" << sSubdir << "]" << endl;
				bRes = false;
			}
			Esperar( 100 );
			sSubdir = "..";
			if ( cliente->CambiarDirectorioRemoto( sSubdir ) )
			{
				Esperar( 100 );
				sDir1 = cliente->DirectorioRemoto();
				cout << "{CLIENTE1} Directorio remoto: [" << sDir1 << "]" << endl;
				if ( sDir1.compare( sDir ) != 0 )
				{
					cout << "Directorio erroneo:[" <<  sDir1 << "]" << endl;
					bRes = false;
				}
			}
			else
			{
				cout << "Error cambiando a directorio: [" << sSubdir << "]" << endl;
				bRes = false;
			}
			Esperar( 100 );
			sSubdir = "noexiste";
			if ( cliente->CambiarDirectorioRemoto( sSubdir ) )
			{
				cout << "Error: Ha cambiado a directorio inexistente" << endl;
				bRes = false;
			}
			Esperar( 100 );
			sDir1 = cliente->DirectorioRemoto();
			cout << "{CLIENTE1} Directorio remoto: [" << sDir1 << "]" << endl;
			if ( sDir1.compare( sDir ) != 0 )
			{
				cout << "Directorio erroneo:[" <<  sDir1 << "]" << endl;
				bRes = false;
			}
			Esperar( 100 );
			sSubdir = "..";
			if ( cliente->CambiarDirectorioRemoto( sSubdir ) )
			{
				cout << "Error: Ha cambiado a directorio prohibido" << endl;
				bRes = false;
			}
			Esperar( 100 );
			sDir1 = cliente->DirectorioRemoto();
			cout << "{CLIENTE1} Directorio remoto: [" << sDir1 << "]" << endl;
			if ( sDir1.compare( sDir ) != 0 )
			{
				cout << "Directorio erroneo:[" <<  sDir1 << "]" << endl;
				bRes = false;
			}
			Esperar( 100 );
			if ( !cliente->PingServidor() )
			{
				cout << "Error en el Ping al servidor" << endl;
				bRes = false;
			}
			cout << "{CLIENTE1} Ping realizado" << endl;
			Esperar( 100 );
			string sResultado( "" );
			if ( !cliente->EstadoServidor( sResultado ) )
			{
				cout << "Error en la consulta del estado servidor" << endl;
				bRes = false;
			}
			else if ( sResultado.compare( "Ok" ) != 0 )
			{
				cout << "Error en la consulta del estado servidor: [" << sResultado << "]" << endl;
				bRes = false;
			}			
			cout << "{CLIENTE1} Estado servidor: [" << sResultado << "]" << endl;
			Esperar( 100 );
			sResultado = cliente->InfoSistemaServidor();
			cout << "{CLIENTE1} Info servidor: [" << sResultado << "]" << endl;
			if ( sResultado.compare( "Respuesta inesperada" ) == 0 )
			{
				cout << "Error en la consulta del sistema" << endl;
				bRes = false;
			}
			Esperar( 100 );
			sSubdir = "carpeta2";
			if ( cliente->CrearDirectorioRemoto( sSubdir ) )
			{
				Esperar( 100 );
				if ( cliente->CambiarDirectorioRemoto( sSubdir ) )
				{
					Esperar( 100 );
					sDir1 = cliente->DirectorioRemoto();
					string sDirEsperado = Concatenar( sDir, "/carpeta2" );
					cout << "{CLIENTE1} Directorio remoto: [" << sDir1 << "]" << endl;
					if ( sDir1.compare( sDirEsperado ) != 0 )
					{
						cout << "Directorio erroneo:[" <<  sDir1 << "]" << endl;
						bRes = false;
					}
				}
				else
				{
					cout << "Error: Ha cambiado a directorio inexistente" << endl;
					bRes = false;
				}
			}
			else
			{
				cout << "Error: No se ha creado el directorio" << endl;
				bRes = false;
			}
			if ( bRes )
			{
				vector<string> vecContenido;
				Esperar( 100 );
				cliente->setModoActivo( 5654 );
				if ( cliente->ContenidoDirectorioRemoto( vecContenido ) )
				{
					cout << "Error: se esperaba fallo por no haber cambiado a modo pasivo" << endl;
					bRes = false;
				}
				Esperar( 100 );
				cliente->setModoPasivo();
				if ( cliente->ContenidoDirectorioRemoto( vecContenido ) )
				{
					cout << "CONTENIDO:" << endl;
					cout << ToString( vecContenido ) << endl;
					cout << "--------------" << endl;
					if ( vecContenido.size() != 0 )
					{
						cout << "Error: Contenido inesperado: " << vecContenido.size() << endl;
						bRes = false;
					}					
				}
				else
				{
					cout << "Error: Obteniendo el contenido del directorio" << endl;
					bRes = false;
				}
				Esperar( 100 );
				if ( cliente->CambiarDirectorioRemoto( ".." ) )
				{
					Esperar( 100 );
					if ( cliente->ContenidoDirectorioRemoto( vecContenido ) )
					{
						cout << "CONTENIDO:" << endl;
						cout << ToString( vecContenido ) << endl;
						cout << "--------------" << endl;
						if ( vecContenido.size() != 4 )
						{
							cout << "Error: Contenido inesperado:" << vecContenido.size() << endl;
							bRes = false;
						}					
					}
					else
					{
						cout << "Error: Obteniendo el contenido del directorio" << endl;
						bRes = false;
					}
				}
			}
			if ( bRes )
			{
				if ( !cliente->isAscii() || cliente->isBinario() )
				{
					cout << "Error en valor inicial del TYPE" << endl;
					bRes = false;
				}
				Esperar( 100 );
				if ( cliente->setBinario() )
				{
					if ( cliente->isAscii() || !cliente->isBinario() )
					{
						cout << "Error en valor del TYPE I" << endl;
						bRes = false;
					}
					Esperar( 100 );
					if ( cliente->setAscii() )
					{
						if ( !cliente->isAscii() || cliente->isBinario() )
						{
							cout << "Error en valor inicial del TYPE A" << endl;
							bRes = false;
						}
					}
					else
					{
						cout << "Error al ejecutar TYPE A" << endl;
						bRes = false;
					}
				}
				else
				{
					cout << "Error al ejecutar TYPE I" << endl;
					bRes = false;
				}
			}
			if ( bRes )
			{
				string sRutaLocal = Concatenar( sDirClienteFtp, "/ficheroX_bajado.txt" );
				cout << "{CLIENTE1} Bajando fichero [" << sRutaLocal << "]..." << endl;
				Esperar( 100 );
				if ( cliente->BajarFichero( "ficheroX.txt", sRutaLocal ) )
				{
					cout << "El fichero no deberia existir" << endl;
					bRes = false;
				}
				sRutaLocal = Concatenar( sDirClienteFtp, "/fichero1_bajado.txt" );
				string sRutaRemota = Concatenar( sDirServidorFtp, "/fichero1.txt" );
				cout << "{CLIENTE1} Bajando fichero [" << sRutaRemota << "]..." << endl;
				Esperar( 100 );
				if ( cliente->BajarFichero( "fichero1.txt", sRutaLocal ) )
				{
					cout << "{CLIENTE1} Recuperado fichero [" << sRutaLocal << "]" << endl;
					if ( !FicherosIguales( sRutaLocal, sRutaRemota ) )
					{
						cout << "El fichero recuperado es diferente: [" << sRutaLocal << "]" << endl;
						bRes = false;
					}
				}
				else
				{
					cout << "Error al recuparar el fichero [" << sRutaLocal << "]" << endl;
					bRes = false;
				}
			}
			if ( bRes )
			{
				Esperar( 100 );
				if ( cliente->CambiarDirectorioRemoto( "carpeta1" ) )
				{
					string sRutaLocal = Concatenar( sDirRecursos, "/data/ficheroPUT.txt" );
					string sRutaRemota = Concatenar( sDirServidorFtp, "/carpeta1/fichero_subido.txt" );
					cout << "{CLIENTE1} Subiendo fichero [" << sRutaLocal << "]..." << endl;
					Esperar( 100 );
					if ( cliente->SubirFichero( "fichero_subido.txt", sRutaLocal ) )
					{
						cout << "{CLIENTE1} Subido fichero [" << sRutaRemota << "]" << endl;
						if ( !FicherosIguales( sRutaLocal, sRutaRemota ) )
						{
							cout << "El fichero subido es diferente: [" << sRutaRemota << "]" << endl;
							bRes = false;
						}
					}
					else
					{
						cout << "Error al subir el fichero [" << sRutaLocal << "]" << endl;
						bRes = false;
					}
				}
				else
				{
					cout << "Error al moverse a la carpeta donde subir el fichero" << endl;
					bRes = false;
				}
			}
			Esperar( 100 );
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
	_bResTestFTPCliente1 = bRes;
	cout << "{CLIENTE1} Fin" << endl;
}

static bool TestClienteServidorFTP01 ()
{
	cout << "Test ClienteServidorFTP 01:" << endl;
	bool bRes = true;

	try
	{
		thread thServidor ( Servidor1 );
		Esperar( 500 );
		if ( servidorTestFTP->EsValido() ) 
		{
			Esperar( 2000 );
			thread thCliente1 ( Cliente1 );
			thCliente1.join();
		}
		else
		{
			bRes = false;
		}
		cout << "Parando servidorTestFTP..." << endl;
		servidorTestFTP->Parar();
		thServidor.join();
		bRes = bRes && _bResTestFTPServidor && _bResTestFTPCliente1;
		if ( !bRes )
		{
			cout << "Resultado Servidor=" << ToString( _bResTestFTPServidor ) << endl;
			cout << "Resultado Cliente1=" << ToString( _bResTestFTPCliente1 ) << endl;
		}
		delete servidorTestFTP;
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

bool TestClienteServidorFTP ()
{
	bool bResTestFTP = true;
	sDirTest = DirectorioActual();
	sDirRecursos = ResolverDirectorioRelativo( sDirTest, DIR_RECURSOS );
	sFicheroUsuario = ResolverDirectorioRelativo( sDirTest, FICHERO_USUARIO );
	sDirServidorFtp = ResolverDirectorioRelativo( sDirTest, DIR_SERVIDOR_FTP );
	sDirClienteFtp = ResolverDirectorioRelativo( sDirTest, DIR_CLIENTE_FTP );
	cout << endl << ANSI::AMARILLO << "[Test ClienteServidorFTP]" << ANSI::RESETEAR << endl;
	if ( TestClienteServidorFTP01() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bResTestFTP = false;
	}
	EstablecerDirectorio( sDirTest );
	cout << ANSI::AMARILLO << "[Fin]" << ANSI::RESETEAR << endl;	
	return ( bResTestFTP );
}

