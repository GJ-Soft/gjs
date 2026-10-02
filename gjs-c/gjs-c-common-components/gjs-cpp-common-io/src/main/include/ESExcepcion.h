#ifndef _ORG_GJS_C_CC_CPP_ESEXCEPCION_H
#define _ORG_GJS_C_CC_CPP_ESEXCEPCION_H

#include <string>
#include <ios>
#include <Excepcion.h>



namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

			class ESExcepcion : public Excepcion
			{

			public:
				ESExcepcion ( const std::string & sModulo, const std::string & sRutina, const std::ios_base::failure & exOcurrida );
			};

            }
		}
	}
}

#endif
