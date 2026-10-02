#ifndef _ORG_GJS_C_CC_CPP_SOCKET_H
#define _ORG_GJS_C_CC_CPP_SOCKET_H



#include <Precompilacion.h>


/* Winsock solo en Windows nativo. Bajo Cygwin los sockets son los POSIX, que es
   lo que Cygwin implementa; mezclar los dos juegos choca. Mismo criterio que
   BaseConfig.h. */
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
#if ( defined ( WIN ) )
			bool SockInicializar();
			void SockFinalizar();
#endif	

			/* Vino de Sistema.h ( gjs-cpp-common-base ): era lo unico que ataba
			   aquel modulo a winsock, y su unico consumidor esta aqui. */
			int ResolverIP( const std::string & sIP );

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