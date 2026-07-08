#ifndef _ORG_GJS_C_CC_CPP_CODIFICACION_H
#define _ORG_GJS_C_CC_CPP_CODIFICACION_H

#include <string>





namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {
// TODO UTF32 UCS2
// Utf8 ascii
// Utf 16x -> utf8
// Utf 16x -> ascii

			std::string UnicodeAUtf8 ( const std::wstring & valor );
			std::string UnicodeAUtf16 ( const std::wstring & valor );

			std::wstring Utf8AUnicode ( const std::string & valor );
			std::wstring Utf16AUnicode ( const std::string & valor );

			}
		}
	}
}

#endif
