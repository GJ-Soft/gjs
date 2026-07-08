#ifndef _ORG_GJS_C_CC_CPP_NOENCONTRADOEXCEPCION_H
#define _ORG_GJS_C_CC_CPP_NOENCONTRADOEXCEPCION_H

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

			class NoEncontradoExcepcion : public Excepcion
			{

			public:
				NoEncontradoExcepcion ( const std::string & sModulo, const std::string & sRutina, const std::string & sTipo, const std::string & sObjeto );
			};

            }
		}
	}
}

#endif
