#include "CommonTypesConfig.h"
#include "Secuencias.h"


using namespace std;

namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

template<typename T> bool SonIguales ( const T val1[], const T val2[] )
{
	bool bRes = true;
	int iPos = 0;
	while ( bRes && ( val1[ iPos ] != 0x00 )  && ( val2[ iPos ] != 0x00 ) )
	{
		bRes = ( val1[ iPos ] == val2[ iPos ] );
		iPos = iPos + 1;
	}
	if ( bRes )
	{
		bRes = ( val1[ iPos ] == 0x00 )  && ( val2[ iPos ] == 0x00 );
	}
	return ( bRes );
}


template bool SonIguales ( const unsigned char *, const unsigned char * );

 			}
		}
	}
}
