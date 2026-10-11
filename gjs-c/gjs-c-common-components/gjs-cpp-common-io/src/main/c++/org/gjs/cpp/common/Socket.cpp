#include "CommonIoConfig.h"

#include "Socket.h"



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
#if ( defined ( WIN ) )
bool SockInicializar()
{
    WSADATA wsaData;

    int result = WSAStartup( MAKEWORD( 2, 2 ), &wsaData );
    return ( result == 0 ); 
}

void SockFinalizar()
{
	WSACleanup();
}
#endif	

/* Los simbolos que usa ( sockaddr_in, inet_addr, getaddrinfo, addrinfo,
   AF_INET, INADDR_ANY ) los da CommonIoConfig.h: winsock2.h y ws2tcpip.h en
   Windows nativo, netdb.h y arpa/inet.h en POSIX. */
int ResolverIP( const string & sIP )
{
	int iIP = INADDR_ANY;
	if ( sIP.size() > 0 )
	{
		struct sockaddr_in inaddr;

		memset ((char * ) &inaddr, 0, sizeof( inaddr ) );
		inaddr.sin_addr.s_addr = inet_addr( sIP.c_str() );
		if ( (int)( inaddr.sin_addr.s_addr ) == -1 )
		{
			/* getaddrinfo y no gethostbyname, que devuelve un hostent estatico
			   comun a todos los hilos. Solo IPv4, como antes: ResolverIP
			   devuelve la direccion en un int. */
			struct addrinfo		addrPista;
			struct addrinfo *	p_addrRes = NULL;

			memset ( &addrPista, 0, sizeof ( addrPista ) );
			addrPista.ai_family = AF_INET;
			if ( getaddrinfo ( sIP.c_str (), NULL, &addrPista, &p_addrRes ) == 0 )
			{
				if ( p_addrRes != NULL )
				{
					memcpy ( &inaddr, p_addrRes->ai_addr, sizeof ( inaddr ) );
					iIP = inaddr.sin_addr.s_addr;
				}
				freeaddrinfo ( p_addrRes );
			}
		}
		else
		{
			iIP = inaddr.sin_addr.s_addr;
		}
	}
	return( iIP );
}

Socket::Socket()
{
	memset( &sockaddrSocket, 0, sizeof( sockaddrSocket ) );
	iSocket = -1;
}

Socket::~Socket()
{
	Cerrar();
}

bool Socket::EsValido()
{
	return ( iSocket !=-1 );
}

bool Socket::EstaConectado()
{
	bool bRes = false;
	if( EsValido() ) 
	{
		char buffer;
#if ( defined ( WIN ) )
		fd_set fds;
		FD_ZERO ( &fds );
		FD_SET ( iSocket, &fds );

		TIMEVAL tv;
		tv.tv_sec = 0;
		tv.tv_usec = 0;

		if ( select ( 0, &fds, NULL, NULL, &tv ) > 0 )
		{
			bRes = (recv(iSocket, &buffer, 1, MSG_PEEK) == 0);
		}
#else
		bRes = ( recv ( iSocket, &buffer, 1, MSG_PEEK | MSG_DONTWAIT ) == 0 );
#endif
	}
	return( bRes );
}

bool Socket::AceptaConexiones()
{
	bool bRes = false;
	if( EsValido() ) 
	{
		socklen_t lon = sizeof( int );
		int valor = 0;
#if ( defined ( WIN ) )
		if ( getsockopt ( iSocket, SOL_SOCKET, SO_ACCEPTCONN, (char *) &valor, &lon ) == 0 )
#else
		if ( getsockopt ( iSocket, SOL_SOCKET, SO_ACCEPTCONN, &valor, &lon ) == 0 )
#endif
		{
			bRes = ( valor == 1 );
		}
	}
	return( bRes );
}

int Socket::getId()
{
	return( iSocket );
}

void Socket::setId( int valor )
{
	if ( valor < -1 )
	{
		valor = - 1;
	}
	iSocket = valor;
}

int Socket::getPuerto()
{
	int iPuerto = 0;
	if( EsValido() ) 
	{
		struct sockaddr_in sockaddrLocal;
		socklen_t address_length = sizeof( sockaddrLocal );
		getsockname( iSocket, (struct sockaddr*)&sockaddrLocal, &address_length );
		iPuerto = ntohs( sockaddrLocal.sin_port );
	}
	return( iPuerto );
}

string Socket::getHost()
{
	string sHost;
	if( EsValido() ) 
	{
		struct sockaddr_in sockaddrLocal;
		socklen_t address_length = sizeof(sockaddrLocal);
		getsockname( iSocket, (struct sockaddr*)&sockaddrLocal, &address_length );
		/* inet_ntop y no inet_ntoa, que escribe en un buffer estatico. */
		char cDireccion [ INET_ADDRSTRLEN ];
		if ( inet_ntop ( AF_INET, &sockaddrLocal.sin_addr, cDireccion, sizeof ( cDireccion ) ) != NULL )
		{
			sHost = string ( cDireccion );
		}
	}
	return( sHost );
}

bool Socket::Crear()
{
	bool bRes = false;
	iSocket = socket( PF_INET, SOCK_STREAM, 0 );
	if( EsValido() ) 
	{
		int valor = 1;	
#if ( defined ( WIN ) )
		bRes = ( setsockopt( iSocket, SOL_SOCKET, SO_REUSEADDR, (const char *)&valor, sizeof( int ) ) == 0 );
#else	
		bRes = ( setsockopt( iSocket, SOL_SOCKET, SO_REUSEADDR, &valor, sizeof( int ) ) == 0 );
#endif
	}
	return( bRes );
}

bool Socket::Enlazar( int iPuerto )
{
	bool bRes = false;
	if( EsValido() )
	{
		sockaddrSocket.sin_family = AF_INET;
		sockaddrSocket.sin_port = htons( iPuerto );
		memset( sockaddrSocket.sin_zero, '\0', sizeof( sockaddrSocket.sin_zero ) );

		bRes = ( bind( iSocket, (struct sockaddr *)&sockaddrSocket, sizeof( sockaddrSocket ) ) == 0 );
	}
	return( bRes );
}

bool Socket::Conectar( int iIP, int iPuerto )
{
	bool bRes = false;
	if( EsValido() && ( iIP != INADDR_ANY ) && ( iPuerto > 0 ) )
	{
		sockaddrSocket.sin_family = AF_INET;
		sockaddrSocket.sin_port = htons(iPuerto);
		sockaddrSocket.sin_addr.s_addr = iIP;

		bRes = ( connect( iSocket, (sockaddr *)&sockaddrSocket, sizeof( sockaddrSocket ) ) == 0 );
	}
	return( bRes );
}

bool Socket::Conectar( const string & sIP, int iPuerto )
{
	int iIP = ResolverIP( sIP );
	return ( Conectar( iIP, iPuerto ) );
}

bool Socket::Escuchar( int iTamCola )
{
	bool bRes = false;
	if( EsValido() )
	{
		bRes = ( listen( iSocket, iTamCola ) == 0 );
	}
	return( bRes );
}

int Socket::Aceptar()
{
	int iRes = -1;
	if( EsValido() )
	{
		int iTam = sizeof( sockaddrSocket );
		iRes = accept( iSocket, (struct sockaddr *)&sockaddrSocket, (socklen_t *) &iTam );
	}
	return( iRes );
}

int Socket::Enviar( const string & sMensaje ) 
{
	int iRes = 0;
	if( EsValido() )
	{
		iRes = send( iSocket, sMensaje.c_str(), sMensaje.length(), 0x0 );
	}
	return( iRes );
}

int Socket::Recibir( string & sMensaje, int iMaxTam )
{
	int iRes = 0;
	if( EsValido() && ( iMaxTam > 0 ) )
	{
		sMensaje.clear();
		char buffer[ iMaxTam + 5 ];
		iRes = recv( iSocket, buffer, iMaxTam, 0x0 );
		if( iRes > 0 )
		{
			sMensaje.assign( buffer, iRes );
		}
	}
	return( iRes );
}

bool Socket::Cerrar()
{
	bool bRes = false;
	if( EsValido() )
	{
#if ( defined ( WIN ) )
		// shutdown explicito antes de cerrar: fuerza el envio del FIN para que el
		// extremo remoto detecte el cierre (en winsock, closesocket a secas
		// no siempre hace que un recv() bloqueado del cliente devuelva EOF).
		shutdown ( iSocket, SD_BOTH );
		bRes = ( closesocket ( iSocket ) == 0 );
#else
		shutdown ( iSocket, SHUT_RDWR );
		bRes = ( close ( iSocket ) == 0 );
#endif
		iSocket = -1;
	}
	return( bRes );
}

 			}
		}
	}
}
