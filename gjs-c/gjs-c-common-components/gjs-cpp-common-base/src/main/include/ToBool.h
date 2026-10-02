#ifndef _ORG_GJS_CC_CPP_BASE_TOBOOL_H
#define _ORG_GJS_CC_CPP_BASE_TOBOOL_H



#include <string>
#include <type_traits>

#include <IToString.h>




namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {
			/* Una sola plantilla para todo lo numerico.  */
			template < typename T >
			typename std::enable_if < std::is_arithmetic < T >::value, bool >::type
			ToBool ( T t )
			{
				return ( t != 0 );
			}

			bool ToBool ( const std::string & t );
			bool ToBool ( char * t );
			bool ToBool ( const char * t );
			bool ToBool ( const std::wstring & t );
			bool ToBool ( wchar_t * t );
			bool ToBool ( const wchar_t * t );

			bool ToBool ( IToString & t );
			bool ToBool ( IToString * t );
 			}
		}
	}
}


#endif
