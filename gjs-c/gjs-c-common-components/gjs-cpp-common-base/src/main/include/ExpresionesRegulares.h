#ifndef _ORG_GJS_C_CC_CPP_EXPRESIONES_REGULARES_H
#define _ORG_GJS_C_CC_CPP_EXPRESIONES_REGULARES_H



#include <string>


#define REGEX_NUM_REAL           "-?[0-9]+(\\.[0-9]+)?"
#define REGEX_NUM_ENTERO         "-?[0-9]+"
#define REGEX_NUM_HEXADECIMAL    "([0-9ABCDEFGabcdefg]{2} ?)+"


#define REGEX_URL 			    "([a-z0-9-]+://)?(localhost|[0-9]+\\.[0-9]+\\.[0-9]+\\.[0-9]+|[-a-z0-9]+(\\.[-a-z0-9]+)+)(:[0-9]+)?/?"
#define REGEX_URN 			    "/([-a-zA-Z0-9_%]+(/[-a-zA-Z0-9_%]+)*)?(\\.[a-zA-Z]+)?(\\?(([a-zA-Z0-9-_%]+=[a-zA-Z0-9-_%]+)(&([a-zA-Z0-9-_%]+=[a-zA-Z0-9-_%]+))*))?"
#define REGEX_URI 			    "([a-z0-9-]+://)?(localhost|[0-9]+\\.[0-9]+\\.[0-9]+\\.[0-9]+|[-a-z0-9]+(\\.[-a-z0-9]+)+)(:[0-9]+)?(/([-a-zA-Z0-9_%]+(/[-a-zA-Z0-9_%]+)*)?(\\.[a-zA-Z]+)?)?(\\?(([a-zA-Z0-9-_%]+=[a-zA-Z0-9-_%]+)(&([a-zA-Z0-9-_%]+=[a-zA-Z0-9-_%]+))*))?"




namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

// TODO: Falta el test
bool CumpleExpresionRegular( const std::string & cadena, const std::string & patron );

	


            }
		}
	}
}

#endif






