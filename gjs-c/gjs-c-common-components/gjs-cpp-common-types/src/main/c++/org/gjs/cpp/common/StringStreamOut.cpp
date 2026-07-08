#include "CommonTypesConfig.h"
#include "StringStreamOut.h"

using namespace std;

namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

StringStreamOut::StringStreamOut () : stringstream ()
{
}

StringStreamOut::~StringStreamOut ()
{
}

StringStreamOut& StringStreamOut::put ( char c )
{
	cout.put ( c );
	stringstream::put ( c );
	return ( *this );
}

StringStreamOut& StringStreamOut::write ( const char * s, streamsize n )
{
	cout.write ( s, n );
	stringstream::write ( s, n );
	return ( *this );
}

StringStreamOut& StringStreamOut::operator<< ( const string & val )
{
	cout << val;
	static_cast<std::ostream&>( *this ) << val;
	return( *this );
}

StringStreamOut& StringStreamOut::operator<< ( streambuf * sb )
{
	cout << sb;
	static_cast<std::ostream&>( *this ) << sb;
	return( *this );
}

StringStreamOut& StringStreamOut::operator<< ( ostream& (*pf)(ostream&) )
{
	cout << pf;
	static_cast<std::ostream&>( *this ) << pf;
	return( *this );
}

StringStreamOut& StringStreamOut::operator<< ( ios& (*pf)(ios&) )
{
	cout << pf;
	static_cast<std::ostream&>( *this ) << pf;
	return( *this );
}

StringStreamOut& StringStreamOut::operator<< ( ios_base& (*pf)(ios_base&) )
{
	cout << pf;
	static_cast<std::ostream&>( *this ) << pf;
	return( *this );
}

 			}
		}
	}
}
