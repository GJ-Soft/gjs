#ifndef _ORG_GJS_C_CC_CPP_FINEXCEPCION_H
#define _ORG_GJS_C_CC_CPP_FINEXCEPCION_H


#include <string>
#include <Excepcion.h>




namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

			class FinExcepcion : public Excepcion
			{
			public:
				FinExcepcion( const std::string & sModulo, const std::string & sRutina, int iCodigo );
			};

            }
		}
	}
}

#endif
