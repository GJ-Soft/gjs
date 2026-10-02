#include "BaseConfig.h"
#include "ToInt.h"





using namespace std;



namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

long ToInt ( double t )
{
	return ( round ( t ) );
}

long ToInt ( float t )
{
	return ( round ( t ) );
}

long ToInt ( char * t )
{
	return ( ToInt( static_cast < const char * > ( t ) ) );
}

long ToInt ( const char * t )
{
	long lRes = 0;
	if ( t != NULL )
	{
		try
		{
			if ( strlen( t ) > 0 )
			{
				lRes = atol( t );
			}
		}
		catch (...)
		{
		}
	}
	return ( lRes );
}

long ToInt ( const string & t )
{
	long lRes = 0;
	try
	{
        lRes = stol( t );
	}
	catch (...)
	{
	}
	return ( lRes );
}


long ToInt ( IToString & t )
{
	return ( ToInt ( t.toString() ) );
}

long ToInt ( IToString * t )
{
	long lRes = 0;
	if ( t != NULL )
	{
		lRes = ToInt ( *t );
	}
	return ( lRes );
}

long ToInt ( const wstring & t )
{
	return ( ToInt( string( t.begin(), t.end() ) ) );
}

long ToInt ( wchar_t * t )
{
	return ( ToInt ( static_cast < const wchar_t * > ( t ) ) );
}

long ToInt ( const wchar_t * t )
{
	long lRes = 0;
	if ( t != NULL )
	{
		lRes = ToInt ( wstring( t ) );
	}
	return ( lRes );
}

long long ToLLong ( char * t )
{
	return ( ToLLong( static_cast < const char * > ( t ) ) );
}

long long ToLLong ( const char * t )
{
	long long lRes = 0;
	if ( t != NULL )
	{
		try
		{
			if ( strlen( t ) > 0 )
			{
				lRes = atoll( t );
			}
		}
		catch (...)
		{
		}
	}
	return ( lRes );
}

long long ToLLong ( const string & t )
{
	long long lRes = 0;
	try
	{
        lRes = stoll( t );
	}
	catch (...)
	{
	}
	return ( lRes );
}


long long ToLLong ( IToString & t )
{
	return ( ToLLong ( t.toString() ) );
}

long long ToLLong ( IToString * t )
{
	long long lRes = 0;
	if ( t != NULL )
	{
		lRes = ToLLong ( *t );
	}
	return ( lRes );
}

long long ToLLong ( const wstring & t )
{
	return ( ToLLong( string( t.begin(), t.end() ) ) );
}

long long ToLLong ( wchar_t * t )
{
	return ( ToLLong ( static_cast < const wchar_t * > ( t ) ) );
}

long long ToLLong ( const wchar_t * t )
{
	long long lRes = 0;
	if ( t != NULL )
	{
		lRes = ToLLong ( wstring( t ) );
	}
	return ( lRes );
}


			}
		}
	}
}

