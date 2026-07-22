#ifndef _ORG_GJS_C_CC_CPP_WINHERRAMIENTAS_H
#define _ORG_GJS_C_CC_CPP_WINHERRAMIENTAS_H


#include <BaseConfig.h>

#if ( defined( WIN ) )


#include <string>



namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

			// TODO: Añadir parametros y forma de retorno de resultado
			bool DLLEjecutar ( std::string sRutaDLL, std::string sFuncion );

 			}
		}
	}
}

#endif

#endif
