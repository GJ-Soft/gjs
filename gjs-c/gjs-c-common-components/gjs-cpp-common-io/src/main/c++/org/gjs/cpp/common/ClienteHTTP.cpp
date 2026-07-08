#include "CommonIoConfig.h"

#include "ClienteHTTP.h"
#include "URI.h"
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

ClienteHTTP::ClienteHTTP( const string & sIP, int iPuerto, const string & _sVersion ) : ClienteIETF( sIP, iPuerto )
{
	sURL = Concatenar( "http://", sIP );
	if ( iPuerto != IETF_PUERTO_HTTP )
	{
		sURL = Concatenar( sURL, ":", ToString( iPuerto ) );
	}
	sVersion = HTTP_VERSION_1_1;
	if ( _sVersion.compare( HTTP_VERSION_2_0 ) == 0 )
	{
		sVersion = HTTP_VERSION_2_0;
	}
}

ClienteHTTP::~ClienteHTTP()
{
}

bool ClienteHTTP::EsValido()
{
	return( EsURL( sURL ) && ClienteIETF::EsValido() && 
			( ( sVersion.compare( HTTP_VERSION_1_1 ) == 0 ) ||
			 ( sVersion.compare( HTTP_VERSION_2_0 ) == 0 ) ) );
}

bool ClienteHTTP::Head( const string & sURN, const string & sRutaLocal )
{
	bool	bRes = false;
	URI 	uri( sURL, sURN );
	if ( uri.EsValido() )
	{
		string sParamVersion = Concatenar( "HTTP/", sVersion );
		string sRespuesta( "" );
		string sCodigo( "" );
		string sResultado( "" );
		EnviarComando( IETF_CMD_METODO_HEAD, { sURN, sParamVersion }, sRespuesta );
		if ( ProcesarRespuestaIETF( sRespuesta, sCodigo, sResultado ) )
		{
			bRes = ( sCodigo.compare( IETF_OK ) == 0 );
		}
		if ( bRes )
		{
			try 
			{
				GuardarFichero( sRutaLocal, sResultado );
			}
			catch ( const Excepcion & ex )
			{
				ExcepcionProducida( ex );
				bRes = false;
			}		
		}
	}
	return( bRes );
}

bool ClienteHTTP::Get( const string & sURN, const string & sRutaLocal )
{
	bool	bRes = false;
	URI 	uri( sURL, sURN );
	if ( uri.EsValido() )
	{
		string sParamVersion = Concatenar( "HTTP/", sVersion );
		string sRespuesta( "" );
		string sCodigo( "" );
		string sResultado( "" );
		EnviarComando( IETF_CMD_METODO_GET, { sURN, sParamVersion }, sRespuesta );
		if ( ProcesarRespuestaIETF( sRespuesta, sCodigo, sResultado ) )
		{
			bRes = ( sCodigo.compare( IETF_OK ) == 0 );
		}
		if ( bRes )
		{
			try 
			{
				// TODO: Procesar cabecera, validar el contenido y extracción segura del html
				size_t posHTML = sResultado.find( "<" );
				string sHTML;
				if ( posHTML != string::npos ) 
				{
					sHTML = EliminarUltimoSaltoLinea( sResultado.substr( posHTML ) );
				}
				GuardarFichero( sRutaLocal, sHTML );
			}
			catch ( const Excepcion & ex )
			{
				ExcepcionProducida( ex );
				bRes = false;
			}		
		}
	}
	return( bRes );
}

bool ClienteHTTP::Post( const string & sURN, const string & sRutaLocal )
{
	bool	bRes = false;
	URI 	uri( sURL, sURN );
	if ( uri.EsValido() )
	{
		string sParamVersion = Concatenar( "HTTP/", sVersion );
		string sRespuesta( "" );
		string sCodigo( "" );
		string sResultado( "" );
		EnviarComando( IETF_CMD_METODO_PUT, { sURN, sParamVersion }, sRespuesta );
		if ( ProcesarRespuestaIETF( sRespuesta, sCodigo, sResultado ) )
		{
			bRes = ( sCodigo.compare( IETF_OK ) == 0 );
		}
		if ( bRes )
		{
			try 
			{
				GuardarFichero( sRutaLocal, sResultado );
			}
			catch ( const Excepcion & ex )
			{
				ExcepcionProducida( ex );
				bRes = false;
			}		
		}
	}
	return( bRes );
}

void ClienteHTTP::ExcepcionProducida( const exception & ex )
{
cout << ex.what() << endl;
	throw ex;
}

 			}
		}
	}
}

