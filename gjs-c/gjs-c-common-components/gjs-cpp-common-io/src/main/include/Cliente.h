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
				/* Es dueña de el socket, que cierra y lo libera en el destructor: una copia
				   implícita compartiría los punteros y los liberaría dos veces. */
				Cliente ( const Cliente & ) = delete;
				Cliente & operator= ( const Cliente & ) = delete;
				
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