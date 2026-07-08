#ifndef _ORG_GJS_C_CC_CPP_PROTOTIPOS_H
#define _ORG_GJS_C_CC_CPP_PROTOTIPOS_H


#include <string>




namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

			typedef void (*PROCEDIMIENTO)();
			typedef bool (*FUNCION_BOOL)();

			typedef void (*PROCEDIMIENTO_1CAD)( const std::string & );
			typedef void (*PROCEDIMIENTO_1ENT)( long );

            }
		}
	}
}


#endif
