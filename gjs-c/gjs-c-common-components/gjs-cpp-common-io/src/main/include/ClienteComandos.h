#ifndef _ORG_GJS_C_CC_CPP_CLIENTE_COMANDOS_H
#define _ORG_GJS_C_CC_CPP_CLIENTE_COMANDOS_H




#include <Cliente.h>
#include <Comando.h>
#include <string>
#include <initializer_list>





namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

			class ClienteComandos : public Cliente
			{
			public:
				ClienteComandos( const std::string & sIP, int iPuerto );
				virtual ~ClienteComandos();
				
				// Virtuales, como Cliente::EnviarMensaje: ClienteSesion las redefine para
				// no enviar sin sesion, y por una referencia a esta clase se la saltaba.
				virtual void EnviarComando( Comando & comando, std::string & sRespuesta );
				virtual void EnviarComando( std::string sComando, const std::initializer_list<std::string> & lisArgumentos, std::string & sRespuesta );
				
			};

 			}
		}
	}
}

#endif