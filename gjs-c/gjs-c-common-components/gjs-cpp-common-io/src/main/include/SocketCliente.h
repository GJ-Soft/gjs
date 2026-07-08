#ifndef _ORG_GJS_C_CC_CPP_SOCKET_CLIENTE_H
#define _ORG_GJS_C_CC_CPP_SOCKET_CLIENTE_H




#include <Socket.h>





namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

			class SocketCliente : private Socket
			{
			private:
				bool bConectado = false;
			
			public:
				SocketCliente( int iIP, int iPuerto );
				SocketCliente( const std::string & sIP, int iPuerto );
				virtual ~SocketCliente();
				
				int getId();
				int getPuerto();
				std::string getHost();
				
				bool EsValido();
				bool EstaConectado();

				int Enviar( const std::string & sMensaje );
				int Recibir( std::string & sMensaje, int iMaxTam = 2048 );
				bool Cerrar();
				
				SocketCliente & operator << ( const std::string & sMensaje );
				SocketCliente & operator >> ( std::string & sMensaje );

			};

 			}
		}
	}
}


#endif