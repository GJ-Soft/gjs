#include "CommonIoConfig.h"

#include "SocketServidor.h"



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

SocketServidor::SocketServidor( int iPuerto ) : Socket ()
{
	int iError = 0;
	if ( Socket::Crear () )
	{
		if ( Socket::Enlazar( iPuerto ) )
		{
			if ( ! Socket::Escuchar() )
			{
#			 if ( defined ( WIN ) )
				iError = WSAGetLastError();
#			 else
				iError = errno;
#			 endif
				Socket::Cerrar();			
			}
		}
		else
		{
#		 if ( defined ( WIN ) )
			iError = WSAGetLastError();
#		 else
			iError = errno;
#		 endif
			Socket::Cerrar();
		}
	}
	else
	{
#	 if ( defined ( WIN ) )
		iError = WSAGetLastError();
#	 else
		iError = errno;
#	 endif
	}
	if ( iError != 0 )
	{
		throw SocketExcepcion( "SocketServidor", "Constructor", iError );
	}
}

SocketServidor::~SocketServidor()
{
}

bool SocketServidor::EsValido()
{
	return ( Socket::AceptaConexiones() );
}

int SocketServidor::getId()
{
	return ( Socket::getId() );
}

int SocketServidor::getPuerto()
{
	return( Socket::getPuerto() );
}

string SocketServidor::getHost()
{
	return( Socket::getHost() );
}

SocketAtencion * SocketServidor::Aceptar()
{
	int iSocketHijo = Socket::Aceptar();
	return( new SocketAtencion( iSocketHijo ) );
}

int SocketServidor::Enviar( const string & sMensaje ) 
{
	return( Socket::Enviar( sMensaje ) );
}

int SocketServidor::Recibir( string & sMensaje, int iMaxTam )
{
	return( Socket::Recibir( sMensaje, iMaxTam ) );
}

bool SocketServidor::Cerrar()
{
	return( Socket::Cerrar() );
}

SocketServidor & SocketServidor::operator << ( const string & sMensaje )
{
	int iError = 0;
	
	if ( Socket::Enviar( sMensaje ) != sMensaje.length() )
	{
#	 if ( defined ( WIN ) )
		iError = WSAGetLastError();
#	 else
		iError = errno;
#	 endif
		throw SocketExcepcion( "SocketServidor", "operator<<", iError );
	}
	return( *this );
}

SocketServidor & SocketServidor::operator >> ( string & sMensaje )
{
	int iError = 0;
	
	if ( Socket::Recibir( sMensaje ) < 0 )
	{
#	 if ( defined ( WIN ) )
		iError = WSAGetLastError();
#	 else
		iError = errno;
#	 endif
		throw SocketExcepcion( "SocketServidor", "operator>>", iError );
	}
	return( *this );
}

 			}
		}
	}
}

