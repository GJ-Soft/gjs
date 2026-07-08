#ifndef _ORG_GJS_C_CC_CPP_ARGUUMENTOINVALIDOEXCEPCION_H
#define _ORG_GJS_C_CC_CPP_ARGUUMENTOINVALIDOEXCEPCION_H

#include <Excepcion.h>




namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

			class ArgumentoInvalidoExcepcion : public Excepcion
			{
			public:
				ArgumentoInvalidoExcepcion( const std::string & sModulo, const std::string & sRutina, const std::string & sArgumento );
			};

            }
		}
	}
}

#endif
