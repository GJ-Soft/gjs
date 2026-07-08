#ifndef _ORG_GJS_C_CC_CPP_STRINGSTREAMOUT_H
#define _ORG_GJS_C_CC_CPP_STRINGSTREAMOUT_H

#include <sstream>
#include <iostream>


namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

			class StringStreamOut : public std::stringstream
			{

			public:
				StringStreamOut ();
				~StringStreamOut ();

				StringStreamOut& put ( char c );
				StringStreamOut& write ( const char * s, std::streamsize n );

				template<typename T> StringStreamOut& operator<< ( T val )
				{
					std::cout << val;
					static_cast<std::ostream&>( *this ) << val;
					return( *this );
				}

				StringStreamOut& operator<< ( const std::string & val );
				StringStreamOut& operator<< ( std::streambuf * sb );
				StringStreamOut& operator<< ( std::ostream& (*pf)(std::ostream&) );
				StringStreamOut& operator<< ( std::ios& (*pf)(std::ios&) );
				StringStreamOut& operator<< ( std::ios_base& (*pf)(std::ios_base&) );

			};

 			}
		}
	}
}

#endif
