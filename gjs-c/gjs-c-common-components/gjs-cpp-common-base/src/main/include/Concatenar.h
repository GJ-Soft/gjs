#ifndef _ORG_GJS_C_CC_CPP_CONCATENAR_H
#define _ORG_GJS_C_CC_CPP_CONCATENAR_H

#include <string>
#include <list>
#include <initializer_list>





namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

			std::string Concatenar ( const std::initializer_list<std::string> & args );
			std::string Concatenar ( const std::list<std::string> & args );
			template<typename... Types> std::string Concatenar ( Types... args );

 			}
		}
	}
}

#endif
