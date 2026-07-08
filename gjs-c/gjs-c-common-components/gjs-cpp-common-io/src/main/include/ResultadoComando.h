#ifndef _ORG_GJS_C_CC_CPP_RESULTADO_COMANDO_H
#define _ORG_GJS_C_CC_CPP_RESULTADO_COMANDO_H



#include <string>
#include <initializer_list>
#include <Comando.h>
#include <ComandoIETF.h>




namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

			class ResultadoComando : public Comando
			{
			private:
				std::string	sRespuesta;
				
			public:
				ResultadoComando();
				ResultadoComando( ComandoIETF & comando, const std::string & _sRespuesta );
				ResultadoComando( Comando & comando, const std::string & _sRespuesta );
				ResultadoComando( const std::string & _sComando, const std::initializer_list<std::string> & lisArgumentos, const std::string & _sRespuesta );
				ResultadoComando( const std::string & sExpresion, const std::string & _sRespuesta );
				virtual ~ResultadoComando();

				std::string & getRespuestaEsperada();
				void setRespuestaEsperada( const std::string & sValor );
			};

 			}
		}
	}
}

#endif