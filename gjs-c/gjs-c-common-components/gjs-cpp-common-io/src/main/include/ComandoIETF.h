#ifndef _ORG_GJS_C_CC_CPP_COMANDO_IETF_H
#define _ORG_GJS_C_CC_CPP_COMANDO_IETF_H


#include <initializer_list>

#include <Comando.h>
#include <CodigosIETF.h>




namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {


			class ComandoIETF : public Comando
			{
			public:
				ComandoIETF();
				ComandoIETF( const std::string & _sComando, const std::initializer_list<std::string> & lisArgumentos );
				ComandoIETF( const std::string & sExpresion );
				virtual ~ComandoIETF();

				virtual std::string toString();
			};

 			}
		}
	}
}


#endif