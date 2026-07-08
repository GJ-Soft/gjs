#ifndef _ORG_GJS_C_CC_CPP_SOCKET_ABIERTO_H
#define _ORG_GJS_C_CC_CPP_SOCKET_ABIERTO_H





#include <SocketAtencion.h>





namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

			class SocketAbierto 
			{
			private:
				SocketAtencion * 				sockAtencion = NULL;
				
			public:
				SocketAbierto( SocketAtencion * _sockAtencion ); 
				virtual ~SocketAbierto();

				void Responder( std::string & sRespuesta );
				
			};

 			}
		}
	}
}


#endif