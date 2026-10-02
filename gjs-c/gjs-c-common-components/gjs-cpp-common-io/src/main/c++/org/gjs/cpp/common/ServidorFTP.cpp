#include "CommonIoConfig.h"


#include "ServidorFTP.h"
#include "CodigosIETF.h"
#include "ComandosIETF.h"
#include "PuertosIETF.h"


using namespace org::gjs::cpp::common;
using namespace std;


namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

/* Primera linea con algo escrito, ya sin blancos de los extremos. Ver el
   comentario del comando SYST: una respuesta IETF tiene que caber en una linea. */
static string _PrimeraLineaConTexto ( const string & sTexto )
{
	string sRes ( "" );

	for ( const string & sLinea : Separar ( sTexto, { "\n" } ) )
	{
		if ( sRes.empty () )
		{
			/* Trim () solo quita espacios, y al partir por \n cada linea se queda
			   con su \r: la primera vuelta devolvia una linea con un \r solo, que
			   no esta vacia, y el SYST contestaba con ese \r suelto. */
			sRes = sLinea;
			sRes.erase ( 0, sRes.find_first_not_of ( " \t\r\n" ) );
			sRes.erase ( sRes.find_last_not_of ( " \t\r\n" ) + 1 );
		}
	}
	return ( sRes );
}

ServidorFTP::ServidorFTP( const string & sDirectorio, const string & sRutaUsuarios, const string & sRutaContexto ) :
					ServidorFTP( IETF_PUERTO_FTP, IETF_PUERTO_DATOS_FTP, sDirectorio, sRutaUsuarios, sRutaContexto )
{
}


ServidorFTP::ServidorFTP( int iPuerto, int _iPuertoDatos, const string & sDirectorio, const string & sRutaUsuarios, const string & sRutaContexto ) :
					ServidorIETF( iPuerto, lisComandosFtp, sRutaUsuarios, sRutaContexto )
{
	sDirectorioRaiz = sDirectorio;
	iPuertoDatos = _iPuertoDatos;
	try
	{
		EstablecerDirectorio( sDirectorioRaiz );
		pathDirectorioRaiz = filesystem::current_path();
	}
	catch ( exception & ex )
	{
		ServidorIETF::ExcepcionProducida ( ex );
	}
}

ServidorFTP::~ServidorFTP()
{
}

int ServidorFTP::getPuerto()
{
	return( ServidorIETF::getPuerto() );
}

int ServidorFTP::getPuertoDatos()
{
	return( iPuertoDatos );
}

void ServidorFTP::setPuertoDatos( int iPuerto )
{
	if ( ( iPuerto > 0 ) && ( sockDatos == NULL ) )
	{
		iPuertoDatos = iPuerto;
	}
}

bool ServidorFTP::EsValido()
{
	return( ExisteDirectorio( pathDirectorioRaiz.string() ) && ServidorIETF::EsValido() );
}

void ServidorFTP::Iniciar()
{
	ServidorIETF::Iniciar();
}

void ServidorFTP::Parar()
{
	if ( sockDatos != NULL )
	{
		sockDatos->Cerrar();
		delete sockDatos;
		sockDatos = NULL;
	}
	ServidorIETF::Parar();
}



// TODO: IETF_CMD_AYUDA, IETF_CMD_CUENTA, IETF_CMD_RESERVAR, IETF_CMD_ANEXAR,
//													IETF_CMD_ELIMINAR, , IETF_CMD_MODO_TRANSFER, IETF_CMD_LISTAR_NOMBRES,
//													, IETF_CMD_PUERTO, , IETF_CMD_RENOMBRAR_ORIG, IETF_CMD_RENOMBRAR_DEST,
//													, IETF_CMD_ESTRUCTURA_FIC, IETF_CMD_TAM, IETF_CMD_DIR_PADRE, ,
//													, IETF_CMD_ELIMINAR_DIR, IETF_CMD_MONTAR_ESTRUCTURA, IETF_CMD_GUARDAR_UNICO,
//													IETF_CMD_REINICIALIZAR, IETF_CMD_REINICIAR, IETF_CMD_ABORTAR, IETF_CMD_CONFIGURACION, ,
bool ServidorFTP::EsComandoValido( Comando & comando )
{
	bool bRes = false;
	if ( ServidorIETF::EsComandoValido( comando ) )
	{
		if( comando.isComando( IETF_CMD_CAMBIAR_DIR ) ||
			comando.isComando( IETF_CMD_CREAR_DIR ) ||
			comando.isComando( IETF_CMD_TIPO ) ||
			comando.isComando( IETF_CMD_GUARDAR ) ||
			comando.isComando( IETF_CMD_RECUPERAR ) )
		{
			bRes = ( comando.NumArgumentos() == 1 );
		}
		else if( comando.isComando( IETF_CMD_NADA ) ||
			comando.isComando( IETF_CMD_SISTEMA )  ||
			comando.isComando( IETF_CMD_ESTADO ) ||
			comando.isComando( IETF_CMD_OBTENER_DIR ) ||
			comando.isComando( IETF_CMD_LISTAR ) ||
			comando.isComando( IETF_CMD_MODO_PASIVO ) )
		{
			bRes = ( comando.NumArgumentos() == 0 );
		}
		else
		{
			// Caso comandos de manejo de sesion
			bRes = true;
		}
	}
	return( bRes );
}

/*
void ServidorIETF::ComandoRecibido( Comando & comando )
{
	ServidorFTP::ComandoRecibido( comando );
}

void ServidorIETF::ComandoProcesado( Comando & comando, bool & bResultado )
{
	ServidorFTP::ComandoProcesado( comando, bResultado );
}

void ServidorIETF::SesionIniciada( const string & sUsuario )
{
	ServidorFTP::SesionIniciada( sUsuario ;
}

void ServidorIETF::SesionFinalizada( const string & sUsuario )
{
	ServidorFTP::SesionFinalizada( sUsuario );
}
*/

void ServidorFTP::ProcesarComandoSesion( Comando & comando, bool & bResponder, string & sRespuesta, bool & bResultado, SocketAbierto * socket )
{
	try
	{
		bResponder = true;
		if ( comando.isComando ( IETF_CMD_NADA ) )
		{
			bResultado = true;
			sRespuesta = MensajeOk();
		}
		else if ( comando.isComando ( IETF_CMD_ESTADO ) )
		{
			bResultado = true;
			if ( EsValido() )
			{
				sRespuesta = ConstruirRespuestaIETF( IETF_ESTADO_SISTEMA, "Ok" );
			}
			else
			{
				sRespuesta = ConstruirRespuestaIETF( IETF_ERROR_INTERNO, "Servidor no inicializado correctamente" );
			}
		}
		else if ( comando.isComando ( IETF_CMD_SISTEMA ) )
		{
			bResultado = true;
			/* La respuesta tiene que caber en UNA linea: ConstruirRespuestaIETF le
			   pega el 
 del final y el cliente lee una sola linea. Con uname -a
			   no se notaba, pero systeminfo devuelve un informe de miles de bytes y
			   decenas de lineas: el cliente tomaba la primera como respuesta y el
			   resto se quedaba en el socket, descolocando TODOS los comandos que
			   vinieran detras ( MKD y QUIT fallaban sin motivo ninguno ). No se
			   puede sanear en ConstruirRespuestaIETF, que es de los dos protocolos
			   y en HTTP si le llega un cuerpo de varias lineas.

			   ver, ademas, contesta lo que el RFC 959 pide para SYST: una linea
			   corta que nombra el sistema, en vez de un inventario de la maquina. */
			string sInstruccion = "uname -a";
			if ( EsWindows() )
			{
				sInstruccion = "ver";
			}
			string sResultado = _PrimeraLineaConTexto ( EjecutarComando ( sInstruccion ) );
			sRespuesta = ConstruirRespuestaIETF( IETF_INFO_SISTEMA, sResultado );
		}
		else if ( comando.isComando ( IETF_CMD_OBTENER_DIR ) )
		{
			bResultado = true;
			sRespuesta = ConstruirRespuestaIETF( IETF_DIRECTORIO, DirectorioActual () );
		}
		else if ( comando.isComando ( IETF_CMD_CAMBIAR_DIR ) )
		{
			string sDirectorio = comando.getArgumento( 0 );
			if ( EsNombreFichero( sDirectorio ) &&
				EmpiezaPor( filesystem::current_path().string(), pathDirectorioRaiz.string() ) )
			{
				try
				{
					filesystem::path pathSubdirectorio = filesystem::current_path() / sDirectorio;
					filesystem::current_path( pathSubdirectorio );
					bResultado = true;
					sRespuesta = ConstruirRespuestaIETF( IETF_ACCION_COMPLETADA, "Directorio cambiado" );
				}
				catch( exception & ex )
				{
					bResultado = false;
					sRespuesta = ConstruirRespuestaIETF( IETF_ACCION_NO_REALIZADA, ex.what() );
				}
			}
			else if ( sDirectorio.compare( ".." ) == 0 )
			{
				if ( EmpiezaPor( filesystem::current_path().string(), pathDirectorioRaiz.string() ) &&
						( filesystem::current_path().string().size() > pathDirectorioRaiz.string().size() + 1 ) )
				{
					filesystem::path pathSubdirectorio = filesystem::current_path() / sDirectorio;
					filesystem::current_path( pathSubdirectorio );
					bResultado = true;
					sRespuesta = ConstruirRespuestaIETF( IETF_ACCION_COMPLETADA, "Directorio cambiado" );
				}
				else
				{
					bResultado = false;
					sRespuesta = ConstruirRespuestaIETF( IETF_ACCION_NO_REALIZADA, "Directorio incorrecto" );
				}
			}
			else if ( sDirectorio.compare( "." ) == 0 )
			{
				bResultado = true;
				sRespuesta = ConstruirRespuestaIETF( IETF_ACCION_COMPLETADA, "Directorio cambiado" );
			}
			else
			{
				bResultado = false;
				sRespuesta = ConstruirRespuestaIETF( IETF_ACCION_NO_REALIZADA, "Directorio incorrecto" );
			}
		}
		else if ( comando.isComando ( IETF_CMD_LISTAR ) )
		{
			if( sockDatos != NULL )
			{
				try
				{
					string sContenido( "" );
					for ( auto const& dir_entry : std::filesystem::directory_iterator ( filesystem::current_path() ) )
					{
						sContenido.append( dir_entry.path().filename().string() );
						sContenido.push_back( '\n' );
					}
					bResultado = true;
					string sRespuestaParcial = ConstruirRespuestaIETF( IETF_FICHERO_PREPARADO, "El contenido del directorio esta preparado" );
					socket->Responder( sRespuestaParcial );

					SocketAtencion * sockEnvio = sockDatos->Aceptar();
					int iPos = 0;
					int iTam = sContenido.size();
					if ( iTam == 0 )
					{
						*sockEnvio << "";
					}
					else
					{
						while ( iPos < iTam )
						{
							int iEnviar = min( 2048, iTam - iPos );
							*sockEnvio << sContenido.substr( iPos, iEnviar );
							iPos = iPos + iTam;
						}
					}
					iPos = iTam + 1;
					if ( iPos >= iTam )
					{
						bResultado = true;
						sRespuesta = ConstruirRespuestaIETF( IETF_CERRANDO_CONEXION, "Contenido enviado" );
					}
					else
					{
						bResultado = false;
						sRespuesta = ConstruirRespuestaIETF( IETF_FICHERO_NO_DISPONIBLE, "No se ha enviado el contenido del directorio" );
					}
					sockEnvio->Cerrar();
					delete sockEnvio;
				}
				catch( exception & ex )
				{
					bResultado = false;
					sRespuesta = ConstruirRespuestaIETF( IETF_FICHERO_NO_DISPONIBLE, ex.what() );
				}
			}
			else
			{
				bResultado = false;
				sRespuesta = ConstruirRespuestaIETF( IETF_ERROR_CONEXION, "Necesario usar PASV" );
			}
		}
		else if ( comando.isComando ( IETF_CMD_TIPO ) )
		{
			if( comando.getArgumento( 0 ).compare( "I" ) == 0 )
			{
				bResultado = true;
				bModoBinario = true;
				sRespuesta = ConstruirRespuestaIETF( IETF_OK, "Cambiando a modo binario" );
			}
			else if( comando.getArgumento( 0 ).compare( "A" ) == 0 )
			{
				bResultado = true;
				bModoBinario = false;
				sRespuesta = ConstruirRespuestaIETF( IETF_OK, "Cambiando a modo ASCII" );
			}
			else
			{
				bResultado = false;
				bModoBinario = false;
				sRespuesta = ConstruirRespuestaIETF( IETF_CASO_NO_IMPLEMENTADO, "Modo no implementado" );
			}
		}
		else if ( comando.isComando ( IETF_CMD_MODO_PASIVO ) )
		{
			bResultado = true;
			if ( sockDatos == NULL )
			{
				sockDatos = new common::SocketServidor( iPuertoDatos );
			}
			string sDireccion = Concatenar( ReemplazarTodos( ServidorIETF::getHost(), '.', ',' ), ToString( iPuertoDatos / 256 ) , ",", ToString( iPuertoDatos % 256 ) );
			sRespuesta = ConstruirRespuestaIETF( IETF_MODO_PASIVO, sDireccion );
		}
		else if ( comando.isComando ( IETF_CMD_CREAR_DIR ) )
		{
			string sDirectorio = comando.getArgumento( 0 );
			try
			{
				filesystem::path pathSubdirectorio = filesystem::current_path() / sDirectorio;
				if ( ExisteDirectorio( pathSubdirectorio.string() ) )
				{
					bResultado = true;
					sRespuesta = ConstruirRespuestaIETF( IETF_DIRECTORIO, sDirectorio );
				}
				else if ( filesystem::create_directory( pathSubdirectorio ) )
				{
					bResultado = ExisteDirectorio( pathSubdirectorio.string() );
					if ( bResultado )
					{
						sRespuesta = ConstruirRespuestaIETF( IETF_DIRECTORIO, sDirectorio );
					}
					else
					{
						sRespuesta = ConstruirRespuestaIETF( IETF_ACCION_NO_REALIZADA, "No se ha creado correctamente el directorio" );
					}
				}
				else
				{
					bResultado = false;
					sRespuesta = ConstruirRespuestaIETF( IETF_ACCION_NO_REALIZADA, "Imposible crear el directorio" );
				}
			}
			catch( exception & ex )
			{
				bResultado = false;
				sRespuesta = ConstruirRespuestaIETF( IETF_ACCION_NO_REALIZADA, ex.what() );
			}
		}
		else if ( comando.isComando ( IETF_CMD_GUARDAR ) )
		{
			if( sockDatos != NULL )
			{
				try
				{
					string sFichero = comando.getArgumento( 0 );
					ios_base::openmode modo = ios::out;
					if  ( bModoBinario )
					{
						modo = modo | ios::binary;
					}
					ofstream fichero( sFichero, modo );
					if ( fichero )
					{
						bResultado = true;
						string sRespuestaParcial = ConstruirRespuestaIETF( IETF_FICHERO_PREPARADO, "Listo para recibir datos" );
						socket->Responder( sRespuestaParcial );

						SocketAtencion * sockRecepcion = sockDatos->Aceptar();
						string sDatos;
						do
						{
							sDatos = "";
							*sockRecepcion >> sDatos;
							if ( sDatos.size() > 0 )
							{
								fichero << sDatos;
							}
						}
						while( sRespuesta.size() > 0 );
						fichero.close();

						bResultado = true;
						sRespuesta = ConstruirRespuestaIETF( IETF_CERRANDO_CONEXION, "Contenido enviado" );
						sockRecepcion->Cerrar();
						delete sockRecepcion;
					}
					else
					{
						bResultado = false;
						sRespuesta = ConstruirRespuestaIETF( IETF_ACCION_NO_REALIZADA, "No se ha podido abrir el fichero" );
					}
				}
				catch( exception & ex )
				{
					bResultado = false;
					sRespuesta = ConstruirRespuestaIETF( IETF_FICHERO_NO_DISPONIBLE, ex.what() );
				}
			}
			else
			{
				bResultado = false;
				sRespuesta = ConstruirRespuestaIETF( IETF_ERROR_CONEXION, "Necesario usar PASV" );
			}
		}
		else if ( comando.isComando ( IETF_CMD_RECUPERAR ) )
		{
			if( sockDatos != NULL )
			{
				try
				{
					string sFichero = comando.getArgumento( 0 );
					ios_base::openmode modo = ios::in | ios::ate;
					if  ( bModoBinario )
					{
						modo = modo | ios::binary;
					}
					ifstream fichero( sFichero, modo );
					if ( fichero )
					{
						long lTam = fichero.tellg();
						fichero.seekg( 0, fichero.beg );

						bResultado = true;
						string sRespuestaParcial = ConstruirRespuestaIETF( IETF_FICHERO_PREPARADO,
								Concatenar( "Abriendo conexion de datos en modo ", ( bModoBinario ? "BINARIO" : "ASCII" ), " para ",
											sFichero, "( ", ToString( lTam ), " bytes )." ) );
						socket->Responder( sRespuestaParcial );

						SocketAtencion * sockEnvio = sockDatos->Aceptar();
						char cBuffer [ 2048 ];
						string sDatos;

						/* Se envia lo que read () haya dejado de verdad, que es lo que
						   dice gcount (), y no lo que se le pidio.

						   Antes el bucle se guiaba por el tamano en disco ( lTam ) y
						   hacia assign ( cBuffer, lEnviar ) a ciegas. En Windows, con
						   el fichero abierto en modo texto ( TYPE A, sin ios::binary ),
						   cada \r\n del disco llega como un solo \n: read () devuelve
						   MENOS caracteres de los pedidos, y assign () se llevaba por
						   delante bytes del buffer sin inicializar. De ahi el \0 de mas
						   al final del fichero recibido. En POSIX no se notaba porque
						   no hay traduccion que valga y los dos numeros coinciden.

						   El || del while es el modismo de siempre: la ultima lectura
						   parcial pone failbit pero deja gcount () > 0, y hay que
						   enviarla igual. */
						while ( fichero.read ( cBuffer, sizeof ( cBuffer ) ) || ( fichero.gcount () > 0 ) )
						{
							sDatos.assign ( cBuffer, fichero.gcount () );
							*sockEnvio << sDatos;
						}
						fichero.close();

						bResultado = true;
						sRespuesta = ConstruirRespuestaIETF( IETF_CERRANDO_CONEXION, "Contenido enviado" );
						sockEnvio->Cerrar();
						delete sockEnvio;
					}
					else
					{
						bResultado = false;
						sRespuesta = ConstruirRespuestaIETF( IETF_ACCION_NO_REALIZADA, "No se ha podido abrir el fichero" );
					}
				}
				catch( exception & ex )
				{
					bResultado = false;
					sRespuesta = ConstruirRespuestaIETF( IETF_FICHERO_NO_DISPONIBLE, ex.what() );
				}
			}
			else
			{
				bResultado = false;
				sRespuesta = ConstruirRespuestaIETF( IETF_ERROR_CONEXION, "Necesario usar PASV" );
			}
		}
		else
		{
			bResultado = false;
			sRespuesta = ConstruirRespuestaIETF( IETF_COMANDO_NO_IMPLEMENTADO, "Comando no implementado" );
		}
	}
	catch ( exception & ex )
	{
		cerr << "{SERVIDOR} Excepcion inesperada: " << ex.what() << endl;
	}
}

 			}
		}
	}
}
