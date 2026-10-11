#include "CommonIoConfig.h"


#include "ServidorHTTP.h"
#include "CodigosIETF.h"
#include "ComandosIETF.h"
#include "PuertosIETF.h"
#include "URI.h"


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

ServidorHTTP::ServidorHTTP( const string & sDirectorio, const string & _sVersion, const string & sRutaContexto ) : 
					ServidorHTTP( IETF_PUERTO_HTTP, sDirectorio, _sVersion, sRutaContexto )
{
}

		
ServidorHTTP::ServidorHTTP( int iPuerto, const string & sDirectorio, const string & _sVersion, const string & sRutaContexto ) : 
					ServidorIETF( iPuerto, lisComandosHttp, "", sRutaContexto )
{
	sVersion = HTTP_VERSION_1_1;
	if ( _sVersion.compare( HTTP_VERSION_2_0 ) == 0 )
	{
		sVersion = HTTP_VERSION_2_0;
	}
	sDirectorioRaiz = sDirectorio;
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

ServidorHTTP::~ServidorHTTP()
{
}

int ServidorHTTP::getPuerto()
{
	return( ServidorIETF::getPuerto() );
}

bool ServidorHTTP::EsValido()
{
	return( ExisteDirectorio( pathDirectorioRaiz.string() ) && ServidorIETF::EsValido() );
}

void ServidorHTTP::Iniciar()
{
	ServidorIETF::Iniciar();
}

void ServidorHTTP::Parar()				
{
	ServidorIETF::Parar();
}



bool ServidorHTTP::EsComandoValido( Comando & comando )
{
	bool bRes = false;
	if ( ServidorIETF::EsComandoValido( comando ) )
	{
		bRes = ( comando.NumArgumentos() == 2 );
	}
	return( bRes );
}

void ServidorHTTP::ProcesarComandoSesion( Comando & comando, bool & bResponder, string & sRespuesta, bool & bResultado, SocketAbierto * socket ) 
{
	try
	{
		bResponder = true;
		bool bVersionValida = false;
		string sVersionReq = comando.getArgumento( 1 );
		if ( EmpiezaPor( sVersionReq, "HTTP/" ) && ( sVersionReq.size() > 7 ) )
		{
			sVersionReq = sVersionReq.substr( 5 );
			bVersionValida = ( sVersion.compare( sVersionReq ) == 0 );
			
		}		
		if ( bVersionValida )
		{			
			filesystem::path pathSitio;
			string sParamVersion = Concatenar( "HTTP/", sVersion );
			string sUrn = comando.getArgumento( 0 );
			if ( TerminaPor( sUrn, ".htm" ) )
			{
				sUrn = Concatenar( sUrn.substr( 0, sUrn.size() - 4 ), ".html" ); 
			}
			else if ( TerminaPor( sUrn, "/" ) )
			{
				sUrn = Concatenar( sUrn, "index.html" ); 
			}
			else if ( !TerminaPor( sUrn, ".html" ) )
			{
				sUrn = Concatenar( sUrn, ".html" ); 
			}
			URI uri( "http://localhost", sUrn );
			if ( uri.EsValido() && ( sVersion.compare( sVersionReq ) == 0 ) )
			{			
				try
				{
					pathSitio = pathDirectorioRaiz / uri.getRuta();
					if ( ExisteFichero( pathSitio.string() ) )
					{
						bResultado = true;
					}
					else
					{
						bResultado = false;
						sRespuesta = ConstruirRespuestaIETF( IETF_NO_ENCONTRADO, "Recurso no encontrado" );
					}
				}
				catch( exception & ex )
				{
					bResultado = false;
					sRespuesta = ConstruirRespuestaIETF( IETF_ERROR_INTERNO, ex.what() );
				}
				if ( bResultado )
				{
					ostringstream ssContenido;
					ostringstream ssRespuesta;
					
					if ( comando.isComando ( IETF_CMD_METODO_HEAD ) || comando.isComando ( IETF_CMD_METODO_GET ) )
					{
						bool bSoloCabecera = comando.isComando ( IETF_CMD_METODO_HEAD );
						bool bInicio = true;
						unsigned long ulTam = 0;
						vector<string> vecLineas = LeerFichero ( pathSitio.string() );
						for ( const string & sLinea : vecLineas )
						{
							if ( !bInicio || ( sLinea.size() > 0 ) )
							{
								ssContenido << sLinea << endl;
								ulTam = ulTam + sLinea.size() + 1;
								bInicio = false;
							}
						}
						while ( ( vecLineas.size() > 0 ) && ( vecLineas[ vecLineas.size() -1 ].size() == 0 ) )
						{
							vecLineas.pop_back();
						}
						ssRespuesta << "Content-Length: " << ulTam << "\r\n" << endl;
						ssRespuesta << "Content-Type: text/html\r\n" << endl;
						time_t ahora = Ahora();
						tm tmAhora;
						if ( HoraLocal ( ahora, tmAhora ) )
						{
							ssRespuesta << "Date: " << put_time( &tmAhora, "%a, %d %b %Y %T %Z" ) << "\r\n" << endl;
						}
						if ( !bSoloCabecera )
						{
							ssRespuesta << ssContenido.str();;
						}					
						sRespuesta = Concatenar( "HTTP/", sVersion, " ", ConstruirRespuestaIETF( IETF_OK, ssRespuesta.str() ) );
					}
					else if ( comando.isComando ( IETF_CMD_METODO_POST ) )
					{
						bResultado = false;
						sRespuesta = ConstruirRespuestaIETF( IETF_COMANDO_NO_IMPLEMENTADO, "Comando no implementado" );
					}
					else if ( comando.isComando ( IETF_CMD_METODO_PUT ) )
					{
						bResultado = false;
						sRespuesta = ConstruirRespuestaIETF( IETF_COMANDO_NO_IMPLEMENTADO, "Comando no implementado" );
					}
					else
					{
						bResultado = false;
						sRespuesta = ConstruirRespuestaIETF( IETF_COMANDO_NO_IMPLEMENTADO, "Comando no implementado" );
					}
				}
			}
			else
			{
				bResultado = false;
				sRespuesta = ConstruirRespuestaIETF( IETF_ERROR_SINTACTICO, "URN errónea" );
			}
		}
		else
		{
			bResultado = false;
			sRespuesta = ConstruirRespuestaIETF( IETF_VERSION_PROTOCOLO_NO_SOPORTADA, Concatenar( "Version HTTP no soportada: ", comando.getArgumento( 1 ) ) );
		}
	}
	catch ( exception & ex )
	{
		bResultado = false;
		sRespuesta = ConstruirRespuestaIETF( IETF_ERROR_INTERNO, ex.what() );
	}
}

void ServidorHTTP::SesionIniciada( const string & sUsuario )
{
	// No está orientado a sesiones
}

void ServidorHTTP::SesionFinalizada( const string & sUsuario )
{
	// No está orientado a sesiones
}

 			}
		}
	}
}
