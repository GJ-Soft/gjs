#include "BaseConfig.h"
#include "ToReal.h"





using namespace std;



namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

double ToDouble ( char * t )
{
	return ( ToDouble( (const char *)t ) );
}

double ToDouble ( const char * t )
{
	double dRes = 0.0;
	if ( t != NULL ) 
	{
		dRes = ToDouble ( string ( t ) );
	}
	return ( dRes );
}

double ToDouble ( const string & t )
{
	double dRes = 0.0;
	try
	{
		from_chars_result result = std::from_chars ( t.data(), t.data() + t.size(), dRes );
		if ( result.ec != std::errc{} ) 
		{
			throw std::runtime_error( "from_chars fallo" );
		}
		return dRes;
	}
	catch (...)
	{
	}
	return ( dRes );
}


double ToDouble ( IToString & t )
{
	return ( ToDouble ( t.toString() ) );
}

double ToDouble ( IToString * t )
{
	double dRes = 0;
	if ( t != NULL )
	{
		dRes = ToDouble ( *t );
	}
	return ( dRes );
}

double ToDouble ( const wstring & t )
{
	return ( ToDouble( string( t.begin(), t.end() ) ) );
}

double ToDouble ( wchar_t * t )
{
	return ( ToDouble ( (const wchar_t *) t ) );
}

double ToDouble ( const wchar_t * t )
{
	double dRes = 0.0;
	if ( t != NULL )
	{
		dRes = ToDouble ( wstring( t ) );
	}
	return ( dRes );
}
			}
		}
	}
}

