#ifndef _ORG_GJS_C_CC_CPP_URI_H
#define _ORG_GJS_C_CC_CPP_URI_H




#include <string>
#include <MapaVector.h>



namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

			class URI
			{
			private:
				std::string 			sProtocolo;
				std::string 			sDominio;
				std::string 			sPuerto;
				std::string 			sRuta;
				
				MapaVector<std::string> mapParametros;
				
			public:
				URI();
				explicit URI( const std::string & sURI );
				URI( const std::string & sURL, const std::string & sURN );
				virtual ~URI();
				
				std::string getProtocolo();
				void setProtocolo( const std::string & valor );
				std::string getDominio();
				void setDominio( const std::string & valor );
				std::string getPuerto();
				void setPuerto( const std::string & valor );
				std::string getRuta();
				void setRuta( const std::string & valor );
				void setParametros( const std::string & valor );
				const std::vector<std::string> & getParametros();
				bool ExisteParametro( const std::string & sNombre );
				std::string getValorParametro( const std::string & sNombre );
				void EliminarParametro( const std::string & sNombre );
				int NumParametros();
				void LimpiarParametros();
				void addParametro( const std::string & sNombre, const std::string & sValor );

				std::string toString();
				std::string getURL();
				std::string getURN();
				
				void setURI( const std::string & sURI );
				void setURI( const std::string & sURL, const std::string & sURN );
				
				bool EsValido();
				
			};

 			}
		}
	}
}


#endif