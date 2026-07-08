#include "CommonTypesConfig.h"
#include "Simbolos.h"

#include <Concatenar.h>

using namespace std;

namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

Simbolos::Simbolos ()
{
}

Simbolos::Simbolos ( const initializer_list<string> & args ) : vecContenido ( args.begin(), args.end() )
{
}

Simbolos::Simbolos ( const list<string> & args ) : vecContenido ( args.begin(), args.end() )
{
}

Simbolos::Simbolos ( const vector<string> & args ) : vecContenido ( args.begin(), args.end() )
{
}

int Simbolos::Tam ()
{
	return ( vecContenido.size () );
}

string Simbolos::Simbolo ( int i )
{
	return ( vecContenido.at ( i ) );
}

void Simbolos::Insertar ( const string & simbolo )
{
	// NOTA: push_back no va del todo bien según compilador que se utilice
	// vecContenido.push_back ( simbolo );
	vecContenido.resize( vecContenido.size() + 1 );
	vecContenido[ vecContenido.size() - 1 ] = simbolo;
}

string& Simbolos::operator[] ( int i )
{
	return ( vecContenido.at ( i ) );
}


ostream& operator<< ( ostream & strm, const Simbolos & simbolos )
{
	try
	{
		bool bIni = true;
		for ( const string & sValor : simbolos.vecContenido )
		{
			if ( !bIni )
			{
				strm << ", ";
			}
			strm << sValor;
			bIni = false;
		}
	}
	catch( ... )
	{
	}
	return ( strm );
}

 			}
		}
	}
}
