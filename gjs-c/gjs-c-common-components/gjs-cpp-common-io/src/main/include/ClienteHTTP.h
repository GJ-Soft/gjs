#ifndef _ORG_GJS_C_CC_CPP_CLIENTE_HTTP_H
#define _ORG_GJS_C_CC_CPP_CLIENTE_HTTP_H

#include <string>

#include <ClienteIETF.h>
#include <HTTPConstantes.h>
#include <PuertosIETF.h>


using namespace org::gjs::cpp::common;


namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

			class ClienteHTTP : private ClienteIETF
			{
			private:
				std::string sURL;
				std::string sVersion;

			public:
				ClienteHTTP ( const std::string & sIP, int iPuerto = IETF_PUERTO_HTTP, const std::string & _sVersion = HTTP_VERSION_1_1 );
				virtual ~ClienteHTTP ();

				bool EsValido();

				bool Head( const std::string & sURN, const std::string & sRutaLocal );
				bool Get( const std::string & sURN, const std::string & sRutaLocal );
				bool Post( const std::string & sURN, const std::string & sRutaLocal );

			private:
				void ExcepcionProducida( const std::exception & ex );
			};

 			}
		}
	}
}

#endif
