#include "CommonIoConfig.h"

#include "Cliente.h"



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

Cliente::Cliente( const string & sIP, int iPuerto ) : SocketCliente( sIP, iPuerto )
{
}

Cliente::~Cliente()
{
	SocketCliente::Cerrar();
}


bool Cliente::EsValido()
{
	return ( SocketCliente::EsValido() );
}

int Cliente::getPuerto()
{
	return( SocketCliente::getPuerto() );
}

string Cliente::getHost()
{
	return( SocketCliente::getHost() );
}

void Cliente::EnviarMensaje( const string & sMensaje, string & sRespuesta )
{
	if ( !sMensaje.empty() )
	{
		try
		{
			*this << sMensaje; 
			sRespuesta = "";
			*this >> sRespuesta;
			// if ( sRespuesta.empty() )
			// {
			// 	// TODO: Revisar este caso: ruido recibido?
			// 	cerr<< "{Cliente} : Ruido recibido!" << endl;
			// }
		}
		catch ( exception & ex )
		{
			ExcepcionProducida( ex );
		}
	}
}

void Cliente::EnviarMensaje( const string & sMensaje )
{
	if ( !sMensaje.empty() )
	{
		try
		{
			*this << sMensaje; 
		}
		catch ( exception & ex )
		{
			ExcepcionProducida( ex );
		}
	}
}

int Cliente::Recibir( string & sMensaje, int iMaxTam )
{
	return( SocketCliente::Recibir( sMensaje, iMaxTam ) );
}

 			}
		}
	}
}

