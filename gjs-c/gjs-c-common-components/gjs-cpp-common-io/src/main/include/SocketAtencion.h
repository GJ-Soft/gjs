#ifndef _ORG_GJS_C_CC_CPP_SOCKET_ATENCION_H
#define _ORG_GJS_C_CC_CPP_SOCKET_ATENCION_H





#include <Socket.h>





namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

			class SocketAtencion : private Socket
			{
			public:
				SocketAtencion( int iSocket );
				virtual ~SocketAtencion();
				
				int getId();
				int getPuerto();
				std::string getHost();
				
				bool EsValido();

				int Enviar( const std::string & sMensaje );
				int Recibir( std::string & sMensaje, int iMaxTam = 2048 );
				bool Cerrar();
				
				SocketAtencion & operator << ( const std::string & sMensaje );
				SocketAtencion & operator >> ( std::string & sMensaje );
				
			};

 			}
		}
	}
}


#endif