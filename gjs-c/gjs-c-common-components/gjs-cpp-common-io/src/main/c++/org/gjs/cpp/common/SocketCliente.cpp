#include "CommonIoConfig.h"

#include "SocketCliente.h"




using namespace std;

namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

SocketCliente::SocketCliente( int iIP, int iPuerto ) : Socket ()
{
	int iError = 0;
	
	if ( Socket::Crear () )
	{
		if ( !Socket::Conectar( iIP, iPuerto ) )
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
		throw SocketExcepcion( "SocketCliente", "Constructor", iError );
	}
	bConectado = true;
}

SocketCliente::SocketCliente( const string & sIP, int iPuerto ) : Socket ()
{
	int iError = 0;
	
	if ( Socket::Crear () )
	{
		if ( !Socket::Conectar( sIP, iPuerto ) )
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
		throw SocketExcepcion( "SocketCliente", "Constructor", iError );
	}
	bConectado = true;
}


SocketCliente::~SocketCliente()
{
}

bool SocketCliente::EsValido()
{
	return ( Socket::EsValido() && 	bConectado );
}

bool SocketCliente::EstaConectado()
{
	return ( bConectado );
}

int SocketCliente::getId()
{
	return ( Socket::getId() );
}

int SocketCliente::getPuerto()
{
	return( Socket::getPuerto() );
}

string SocketCliente::getHost()
{
	return( Socket::getHost() );
}

int SocketCliente::Enviar( const string & sMensaje ) 
{
	int iRes = 0;
	if ( EsValido() )
	{
		iRes = Socket::Enviar( sMensaje );
	}
	return( iRes );
}

int SocketCliente::Recibir( string & sMensaje, int iMaxTam )
{
	int iRes = 0;
	if ( EsValido() )
	{
		iRes = Socket::Recibir( sMensaje, iMaxTam );
	}
	return( iRes );
}

bool SocketCliente::Cerrar()
{
	bConectado = false;
	return( Socket::Cerrar() );
}

SocketCliente & SocketCliente::operator << ( const string & sMensaje )
{
	int iError = 0;
	
	if ( Socket::Enviar( sMensaje ) != sMensaje.length() )
	{
#	 if ( defined ( WIN ) )
		iError = WSAGetLastError();
#	 else
		iError = errno;
#	 endif
		throw SocketExcepcion( "SocketCliente", "operator<<", iError );
	}
	return( *this );
}

SocketCliente & SocketCliente::operator >> ( string & sMensaje )
{
	int iError = 0;
	
	if ( Socket::Recibir( sMensaje ) < 0 )
	{
#	 if ( defined ( WIN ) )
		iError = WSAGetLastError();
#	 else
		iError = errno;
#	 endif
		throw SocketExcepcion( "SocketCliente", "operator>>", iError );
	}
	return( *this );
}

 			}
		}
	}
}
