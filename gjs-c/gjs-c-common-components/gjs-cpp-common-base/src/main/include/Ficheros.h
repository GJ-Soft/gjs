#ifndef _ORG_GJS_C_CC_CPP_FICHEROS_H
#define _ORG_GJS_C_CC_CPP_FICHEROS_H

#include <string>
#include <vector>




namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

			std::vector<std::string> LeerFichero ( const std::string & sRuta );
			void GuardarFichero ( const std::string & sRuta, const std::vector<std::string> & vecLineas );
			void GuardarFichero ( const std::string & sRuta, const std::string & sContenido );
			void ImprimirFichero ( const std::string & sRuta );
			void EliminarFichero ( const std::string & sRuta );

			bool FicherosIguales ( const std::string & sRuta1, const std::string & sRuta2 );

            }
		}
	}
}

#endif
