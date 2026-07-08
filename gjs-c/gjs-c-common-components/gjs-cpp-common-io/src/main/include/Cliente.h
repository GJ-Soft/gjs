#ifndef _ORG_GJS_C_CC_CPP_CLIENTE_H
#define _ORG_GJS_C_CC_CPP_CLIENTE_H


#include <string>

#include <SocketCliente.h>






namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

			class Cliente : private SocketCliente
			{
			public:
				Cliente( const std::string & sIP, int iPuerto );
				virtual ~Cliente();
				
				int getPuerto();
				std::string getHost();
				
				virtual bool EsValido();

				virtual void EnviarMensaje( const std::string & sMensaje, std::string & sRespuesta );
				virtual void EnviarMensaje( const std::string & sMensaje );

			protected:
				int Recibir( std::string & sMensaje, int iMaxTam = 2048 );
				
			private:
				virtual void ExcepcionProducida( const std::exception & ex ) = 0;

			};

 			}
		}
	}
}


#endif