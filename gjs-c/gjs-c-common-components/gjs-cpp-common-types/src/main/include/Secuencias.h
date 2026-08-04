#ifndef _ORG_GJS_C_CC_CPP_SECUENCIAS_H
#define _ORG_GJS_C_CC_CPP_SECUENCIAS_H

#include <string>
#include <list>


namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

			// Esta pensada para arrays que terminan en un elemento 0x00
			template<typename T> bool SonIguales ( const T val1[], const T val2[] );

 			}
		}
	}
}

#endif
