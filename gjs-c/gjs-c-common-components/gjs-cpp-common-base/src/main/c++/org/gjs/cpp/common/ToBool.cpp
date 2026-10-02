#include "BaseConfig.h"
#include "ToBool.h"

/* ToLowerCase. */
#include <Cadenas.h>





using namespace std;



namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

bool ToBool ( char * t )
{
	return ( ToBool( static_cast < const char * > ( t ) ) );
}

bool ToBool ( const char * t )
{
	bool bRes = false;

	/* string ( nullptr ) es comportamiento indefinido. La version ancha ya lo
	   comprobaba; esta no. */
	if ( t != NULL )
	{
		bRes = ToBool ( string ( t ) );
	}
	return ( bRes );
}

bool ToBool ( const string & t )
{
	bool bRes = false;
	string lt = ToLowerCase ( t );
	if ( ( lt == "true" ) ||
	     ( lt == "cierto" ) ||
		 ( lt == "t" ) ||
	     ( lt == "c" ) ||
	     ( lt == "1" ) )
	{
		bRes = true;
	}
	return ( bRes );
}


bool ToBool ( IToString & t )
{
	return ( ToBool ( t.toString() ) );
}

bool ToBool ( IToString * t )
{
	bool bRes = false;
	if ( t != NULL )
	{
		bRes = ToBool ( *t );
	}
	return ( bRes );
}

bool ToBool ( const wstring & t )
{
	return ( ToBool( string( t.begin(), t.end() ) ) );
}

bool ToBool ( wchar_t * t )
{
	return ( ToBool ( static_cast < const wchar_t * > ( t ) ) );
}

bool ToBool ( const wchar_t * t )
{
	bool bRes = false;
	if ( t != NULL )
	{
		bRes = ToBool ( wstring( t ) );
	}
	return ( bRes );
}


			}
		}
	}
}

