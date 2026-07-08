#include "BaseConfig.h"
#include "Colecciones.h"

using namespace std;


namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

vector<string> ToVector ( const initializer_list<string> & args )
{
	vector<string> vector;
	vector.insert( vector.begin(), args );
	return ( vector );
}

list<string> ToList ( const initializer_list<string> & args )
{
	return ( args );
}

bool SonIguales ( list<string> & lisObj1, list<string> & lisObj2 )
{
	bool bRes = true;

	if ( lisObj1.size() != lisObj2.size() )
	{
		bRes = false;
	}
	else if ( ! lisObj1.empty() )
	{
		list<string>::iterator it1 = lisObj1.begin ();
		list<string>::iterator it2 = lisObj2.begin ();
		do
		{
			if ( *it1 != *it2 )
			{
				bRes = false;
			}
			++it1;
			++it2;
		}
		while ( bRes && ( it1 != lisObj1.end () ) );
	}
	return ( bRes );
}

bool SonIguales ( vector<string> & vecObj1, vector<string> & vecObj2 )
{
	bool bRes = true;

	if ( vecObj1.size() != vecObj2.size() )
	{
		bRes = false;
	}
	else if ( vecObj1.size() > 0 )
	{
		int i = 0;
		do
		{
			if ( vecObj1[ i ] != vecObj2[ i ] )
			{
				bRes = false;
			}
			i = i + 1;
		}
		while ( bRes && ( i < vecObj1.size () ) );
	}
	return ( bRes );
}

            }
		}
	}
}
