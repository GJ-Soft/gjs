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
				
				void EnviarComando( Comando & comando, std::string & sRespuesta );
				void EnviarComando( std::string sComando, const std::initializer_list<std::string> & lisArgumentos, std::string & sRespuesta );
				
			};

 			}
		}
	}
}

#endif