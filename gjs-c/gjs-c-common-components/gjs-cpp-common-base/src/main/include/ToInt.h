#ifndef _ORG_GJS_CC_CPP_BASE_TOINT_H
#define _ORG_GJS_CC_CPP_BASE_TOINT_H



#include <string>

#include <IToString.h>




namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {
			long ToInt ( double t );
			long ToInt ( float t );

			long ToInt ( const std::string & t );
			long ToInt ( char * t );
			long ToInt ( const char * t );
			long ToInt ( const std::wstring & t );
			long ToInt ( wchar_t * t );
			long ToInt ( const wchar_t * t );

			long ToInt ( IToString & t );
			long ToInt ( IToString * t );

			long long ToLLong ( const std::string & t );
			long long ToLLong ( char * t );
			long long ToLLong ( const char * t );
			long long ToLLong ( const std::wstring & t );
			long long ToLLong ( wchar_t * t );
			long long ToLLong ( const wchar_t * t );

			long long ToLLong ( IToString & t );
			long long ToLLong ( IToString * t );

 			}
		}
	}
}


#endif
