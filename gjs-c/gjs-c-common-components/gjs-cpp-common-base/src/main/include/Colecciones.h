#ifndef _ORG_GJS_C_CC_CPP_COLECCIONES_H
#define _ORG_GJS_C_CC_CPP_COLECCIONES_H

#include <string>
#include <list>
#include <vector>




namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

			std::vector<std::string> ToVector ( const std::initializer_list<std::string> & args );
			std::list<std::string> ToList ( const std::initializer_list<std::string> & args );

			bool SonIguales ( std::list<std::string> & lisObj1, std::list<std::string> & lisObj2 );
			bool SonIguales ( std::vector<std::string> & vecObj1, std::vector<std::string> & vecObj2 );

            }
		}
	}
}

#endif
