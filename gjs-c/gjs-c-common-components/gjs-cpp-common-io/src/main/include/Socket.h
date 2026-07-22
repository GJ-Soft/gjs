#ifndef _ORG_GJS_C_CC_CPP_SOCKET_H
#define _ORG_GJS_C_CC_CPP_SOCKET_H



#include <Precompilacion.h>


#if ( defined ( WIN ) )
#	include <winsock2.h>
#else 
# 	include <sys/socket.h>
# 	include <netinet/in.h>
#endif	

#include <SocketExcepcion.h>

#include <string>



namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

			class Socket
			{
			private:
				int 				iSocket;
				struct sockaddr_in 	sockaddrSocket;
				
			public:
				Socket();
				virtual ~Socket();
				
				int getId();
				int getPuerto();
				std::string getHost();

			protected:
				void setId( int valor );
				
			public:
				bool EsValido();
				bool AceptaConexiones();
				bool EstaConectado();

				bool Crear();
				bool Enlazar( int iPuerto );
				bool Conectar( int iIP, int iPuerto );
				bool Conectar( const std::string & sIP, int iPuerto );
				bool Escuchar( int iTamCola = SOMAXCONN );
				int Aceptar();
				int Enviar( const std::string & sMensaje );
				int Recibir( std::string & sMensaje, int iMaxTam = 2048 );
				bool Cerrar();
			};

 			}
		}
	}
}


#endif