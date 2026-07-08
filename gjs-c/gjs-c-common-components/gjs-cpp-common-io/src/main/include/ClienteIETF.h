#ifndef _ORG_GJS_C_CC_CPP_CLIENTE_IETF_H
#define _ORG_GJS_C_CC_CPP_CLIENTE_IETF_H




#include <ClienteSesion.h>
#include <list>


using namespace org::gjs::cpp::common;


namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {


			class ClienteIETF : public ClienteSesion
			{
			private:
				std::list<ResultadoComando> comandoApertura;
				ResultadoComando 			comandoCierre;

			public:
				ClienteIETF ( const std::string & sIP, int iPuerto );
				ClienteIETF ( const std::string & sIP, int iPuerto, const std::string & _sUsuario, const std::string & _sClave = "" );
				virtual ~ClienteIETF ();

			private:
				void ModificadoUsuario();
				std::list<ResultadoComando> & ComandoInicioSesion();
				ResultadoComando & ComandoFinSesion();

			};

 			}
		}
	}
}


#endif
