#include "CommonIoConfig.h"

#include "ClienteFTP.h"
#include "CodigosIETF.h"
#include "ComandoIETF.h"
#include "ComandosIETF.h"



using namespace std;
using namespace org::gjs::cpp::common;

namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

ClienteFTP::ClienteFTP( const string & sIP, int iPuerto ) : ClienteIETF( sIP, iPuerto )
{
}

ClienteFTP::ClienteFTP( const string & sIP, int iPuerto, const string & _sUsuario, const string & _sClave ) : ClienteIETF( sIP, iPuerto, _sUsuario, _sClave )
{
}

ClienteFTP::~ClienteFTP()
{
}

bool ClienteFTP::EsValido()
{
	return( ClienteIETF::EsValido() );
}

bool ClienteFTP::SesionAbierta()
{
	return( ClienteIETF::SesionAbierta() );
}

bool ClienteFTP::AbrirSesion()
{
	return( ClienteIETF::AbrirSesion() );
}

void ClienteFTP::CerrarSesion()
{	iPuertoDatos = 0;
	bModoActivo = false;
	ClienteIETF::CerrarSesion();
}

bool ClienteFTP::isModoActivo()
{
	return( bModoActivo );
}

bool ClienteFTP::isModoPasivo()
{
	return( !bModoActivo );
}

void ClienteFTP::setModoActivo( int iPuerto )
{
	bModoActivo = true;
	iPuertoDatos = iPuerto;
}

void ClienteFTP::setModoPasivo()
{
	iPuertoDatos = 0;
	bModoActivo = false;
}

bool ClienteFTP::isAscii()
{
	return( !bModoBinario );
}

bool ClienteFTP::isBinario()
{
	return( bModoBinario );
}

bool ClienteFTP::setAscii()
{
	bool bRes = true;
	if ( bModoBinario )
	{
		bRes = false;
		string 	sRespuesta( "" );
		string 	sCodigo( "" );
		string 	sResultado( "" );
		EnviarComando( IETF_CMD_TIPO, { "A" }, sRespuesta );
		if ( ProcesarRespuestaIETF( sRespuesta, sCodigo, sResultado ) )
		{
			bRes = ( sCodigo.compare( IETF_OK ) == 0 );
		}
		if ( bRes )
		{
			bModoBinario = false;
		}
	}
	return( bRes );
}

bool ClienteFTP::setBinario()
{
	bool bRes = true;
	if ( !bModoBinario )
	{
		bRes = false;
		string 	sRespuesta( "" );
		string 	sCodigo( "" );
		string 	sResultado( "" );
		EnviarComando( IETF_CMD_TIPO, { "I" }, sRespuesta );
		if ( ProcesarRespuestaIETF( sRespuesta, sCodigo, sResultado ) )
		{
			bRes = ( sCodigo.compare( IETF_OK ) == 0 );
		}
		if ( bRes )
		{
			bModoBinario = true;
		}
	}
	return( bRes );
}

bool ClienteFTP::EstadoServidor( string & sResultado )
{
	bool	bRes = false;
	string 	sRespuesta( "" );
	string 	sCodigo( "" );
	sResultado = "";
	EnviarComando( IETF_CMD_ESTADO, {}, sRespuesta );
	if ( ProcesarRespuestaIETF( sRespuesta, sCodigo, sResultado ) )
	{
		bRes = ( sCodigo.compare( IETF_ESTADO_SISTEMA ) == 0 );
	}
	return( bRes );
}

bool ClienteFTP::PingServidor()
{
	bool	bRes = false;
	string 	sResultado( "" );
	string 	sRespuesta( "" );
	string 	sCodigo( "" );
	EnviarComando( IETF_CMD_NADA, {}, sRespuesta );
	if ( ProcesarRespuestaIETF( sRespuesta, sCodigo, sResultado ) )
	{
		bRes = ( sCodigo.compare( IETF_OK ) == 0 );
	}
	return( bRes );
}

string ClienteFTP::InfoSistemaServidor()
{
	string 	sResultado( "" );
	string 	sRespuesta( "" );
	string 	sCodigo( "" );
	EnviarComando( IETF_CMD_SISTEMA, {}, sRespuesta );
	if ( ProcesarRespuestaIETF( sRespuesta, sCodigo, sResultado ) )
	{
		if ( sCodigo.compare( IETF_INFO_SISTEMA ) != 0 )
		{
			sResultado = "Respuesta inesperada";
		}
	}
	return( sResultado );
}

string ClienteFTP::DirectorioRemoto()
{
	string sResultado( "" );
	string sRespuesta( "" );
	string sCodigo( "" );
	EnviarComando( IETF_CMD_OBTENER_DIR, {}, sRespuesta );
	if ( ProcesarRespuestaIETF( sRespuesta, sCodigo, sResultado ) )
	{
		if ( sCodigo.compare( IETF_DIRECTORIO ) != 0 )
		{
			sResultado = "";
		}
	}
	return( sResultado );
}

bool ClienteFTP::CambiarDirectorioRemoto( const string & sSubdirectorio )
{
	bool	bRes = false;
	string 	sResultado( "" );
	string 	sRespuesta( "" );
	string 	sCodigo( "" );
	EnviarComando( IETF_CMD_CAMBIAR_DIR, { sSubdirectorio }, sRespuesta );
	if ( ProcesarRespuestaIETF( sRespuesta, sCodigo, sResultado ) )
	{
		bRes = ( sCodigo.compare( IETF_ACCION_COMPLETADA ) == 0 );
	}
	return( bRes );
}

bool ClienteFTP::CrearDirectorioRemoto( const string & sSubdirectorio )
{
	bool	bRes = false;
	string 	sResultado( "" );
	string 	sRespuesta( "" );
	string 	sCodigo( "" );
	EnviarComando( IETF_CMD_CREAR_DIR, { sSubdirectorio }, sRespuesta );
	if ( ProcesarRespuestaIETF( sRespuesta, sCodigo, sResultado ) )
	{
		bRes = ( sCodigo.compare( IETF_DIRECTORIO ) == 0 );
	}
	return( bRes );
}

bool ClienteFTP::ContenidoDirectorioRemoto( vector<string> & vecContenido )
{
	bool bRes = false;
	vecContenido.clear();
	if ( bModoActivo )
	{
		// No implementado
	}
	else
	{
		string 	sResultado( "" );
		string 	sRespuesta( "" );
		string 	sCodigo( "" );
		common::SocketCliente * sockDatos = NULL;
		try
		{
			PrepararSocketDatos();
			EnviarComando( IETF_CMD_LISTAR, {}, sRespuesta );
			if ( ProcesarRespuestaIETF( sRespuesta, sCodigo, sResultado ) )
			{
				if ( sCodigo.compare( IETF_FICHERO_PREPARADO ) == 0 )
				{
					sockDatos = AbrirSocketDatos();
					string sContenido( "" );
					do
					{
						sRespuesta = "";
						*sockDatos >> sRespuesta;
						sContenido.append( sRespuesta );
					}
					while( sRespuesta.size() > 0 );
					vecContenido = Separar( sContenido, { "\n" } );
					if ( vecContenido.size() > 0 )
					{
						if ( Trim( vecContenido[ vecContenido.size()-1 ] ).size() == 0 )
						{
							/* Era erase ( end () ), que es comportamiento indefinido: a erase
							   hay que darle un iterador desreferenciable, y end () no lo es.
							   Para quitar el ultimo, pop_back (). */
							vecContenido.pop_back();
						}
					}

					sRespuesta = "";
					Recibir( sRespuesta );
					if ( ProcesarRespuestaIETF( sRespuesta, sCodigo, sResultado ) )
					{
						if ( sCodigo.compare( IETF_CERRANDO_CONEXION ) == 0 )
						{
							bRes = true;
						}
					}
				}
			}
		}
		catch( exception & ex )
		{
			ExcepcionProducida( ex );
		}
		CerrarSocketDatos( &sockDatos );
	}
	return( bRes );
}

bool ClienteFTP::BajarFichero( const string & sFichero, const string & sRutaLocal )
{
	bool bRes = false;
	if ( bModoActivo )
	{
		// No implementado
	}
	else
	{
		string 	sResultado( "" );
		string 	sRespuesta( "" );
		string 	sCodigo( "" );
		common::SocketCliente * sockDatos = NULL;
		try
		{
			PrepararSocketDatos();
			EnviarComando( IETF_CMD_RECUPERAR, { sFichero }, sRespuesta );
			if ( ProcesarRespuestaIETF( sRespuesta, sCodigo, sResultado ) )
			{
				if ( sCodigo.compare( IETF_FICHERO_PREPARADO ) == 0 )
				{
					ios_base::openmode modo = ios::out;
					if  ( bModoBinario )
					{
						modo = modo | ios::binary;
					}
					ofstream fichero( sRutaLocal, modo );
					sockDatos = AbrirSocketDatos();
					do
					{
						sRespuesta = "";
						*sockDatos >> sRespuesta;
						if ( sRespuesta.size() > 0 )
						{
							fichero << sRespuesta;
						}
					}
					while( sRespuesta.size() > 0 );
					fichero.close();
					sRespuesta = "";
					Recibir( sRespuesta );
					if ( ProcesarRespuestaIETF( sRespuesta, sCodigo, sResultado ) )
					{
						if ( sCodigo.compare( IETF_CERRANDO_CONEXION ) == 0 )
						{
							bRes = true;
						}
					}
				}
			}
		}
		catch( exception & ex )
		{
			ExcepcionProducida( ex );
		}
		CerrarSocketDatos( &sockDatos );
	}
	return( bRes );
}

bool ClienteFTP::SubirFichero( const string & sFichero, const string & sRutaLocal )
{
	bool bRes = false;
	if ( bModoActivo )
	{
		// No implementado
	}
	else
	{
		string 	sResultado( "" );
		string 	sRespuesta( "" );
		string 	sCodigo( "" );
		common::SocketCliente * sockDatos = NULL;
		try
		{
			ios_base::openmode modo = ios::in | ios::ate;
			if  ( bModoBinario )
			{
				modo = modo | ios::binary;
			}
			ifstream fichero( sRutaLocal, modo );
			if ( fichero )
			{
				PrepararSocketDatos();
				EnviarComando( IETF_CMD_GUARDAR, { sFichero }, sRespuesta );
				if ( ProcesarRespuestaIETF( sRespuesta, sCodigo, sResultado ) )
				{
					if ( sCodigo.compare( IETF_FICHERO_PREPARADO ) == 0 )
					{
						/* El fichero se abrio con ios::ate para poder medirlo; ahora
						   el tamano ya no se usa para nada ( el bucle de abajo va por
						   gcount () ), pero hay que volver al principio igual. */
						fichero.seekg( 0, fichero.beg );

						sockDatos = AbrirSocketDatos();
						char cBuffer [ 2048 ];
						string sDatos;

						/* Se envia lo que read () haya dejado de verdad, que es lo que
						   dice gcount (), y no lo que se le pidio. Mismo defecto y
						   mismo arreglo que en el RETR de ServidorFTP: en Windows, con
						   el fichero en modo texto ( TYPE A, sin ios::binary ), cada
						   \r\n del disco llega como un solo \n, read () devuelve menos
						   caracteres de los pedidos, y assign () copiaba bytes del
						   buffer sin inicializar. Se veia como \0 de mas al final del
						   fichero subido, uno por cada salto de linea. */
						while ( fichero.read ( cBuffer, sizeof ( cBuffer ) ) || ( fichero.gcount () > 0 ) )
						{
							sDatos.assign ( cBuffer, fichero.gcount () );
							*sockDatos << sDatos;
						}
						fichero.close();

						sRespuesta = "";
						Recibir( sRespuesta );
						if ( ProcesarRespuestaIETF( sRespuesta, sCodigo, sResultado ) )
						{
							if ( sCodigo.compare( IETF_CERRANDO_CONEXION ) == 0 )
							{
								bRes = true;
							}
						}
					}
				}
			}
		}
		catch( exception & ex )
		{
			ExcepcionProducida( ex );
		}
		CerrarSocketDatos( &sockDatos );
	}
	return( bRes );
}

void ClienteFTP::PrepararSocketDatos()
{
	if ( !bModoActivo )
	{
		if ( iPuertoDatos == 0 )
		{
			string 	sResultado( "" );
			string 	sRespuesta( "" );
			string 	sCodigo( "" );
			EnviarComando( IETF_CMD_MODO_PASIVO, {}, sRespuesta );
			if ( ProcesarRespuestaIETF( sRespuesta, sCodigo, sResultado ) )
			{
				if ( sCodigo.compare( IETF_MODO_PASIVO ) == 0 )
				{
					vector<string> vecCampos = Separar( sResultado, { "," } );
					if ( vecCampos.size() > 1 )
					{
						iPuertoDatos = ToInt( vecCampos[ vecCampos.size()-2 ] ) * 256 + ToInt( vecCampos[ vecCampos.size() - 1 ] );
					}
				}
			}
		}
	}
}

common::SocketCliente * ClienteFTP::AbrirSocketDatos()
{
	common::SocketCliente * sockDatos = NULL;
	if ( !bModoActivo )
	{
		if ( iPuertoDatos > 0 )
		{
			Esperar( 100 );
			sockDatos = new common::SocketCliente ( getHost(), iPuertoDatos );
		}
	}
	return ( sockDatos );
}

void ClienteFTP::CerrarSocketDatos( common::SocketCliente ** sockDatos )
{
	try
	{
		if ( sockDatos != NULL )
		{
			if ( *sockDatos != NULL )
			{
				if ( (*sockDatos)->EstaConectado() )
				{
					(*sockDatos)->Cerrar();
				}
				delete *sockDatos;
				*sockDatos = NULL;
			}
		}
	}
	catch( ... )
	{
	}
}

void ClienteFTP::ExcepcionProducida( const exception & ex )
{
	throw ex;
}

 			}
		}
	}
}

