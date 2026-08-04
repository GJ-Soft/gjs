#include "IComparable.h"

#include "Concatenar.h"
#include "ToString.h"
#include <cstddef>


using namespace std;


namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {


IComparable::IComparable() : IToString ()
{
}

IComparable::~IComparable()
{
}

string IComparable::toString()
{
	return ( Concatenar( "[Object=", ToString( getHash() ), "]" ) );
}

bool IComparable::esIgual( const IComparable & obj ) const
{
	return ( getHash() == obj.getHash() );
}

bool IComparable::esIgual( const IComparable * obj ) const
{
	if( obj != NULL )
	{
		return( esIgual( *obj ) );
	}
	return( false );
}

bool IComparable::operator== ( const IComparable & obj ) const
{
	return ( getHash() == obj.getHash() );
}

bool IComparable::operator!= ( const IComparable & obj ) const
{
	return ( getHash() != obj.getHash() );
}

bool IComparable::operator< ( const IComparable & obj ) const
{
	return ( getHash() < obj.getHash() );
}

bool IComparable::operator> ( const IComparable & obj ) const
{
	return ( getHash() > obj.getHash() );
}



bool IComparable::operator<= ( const IComparable & obj ) const
{
	return ( getHash() <= obj.getHash() );
}

bool IComparable::operator>= ( const IComparable & obj ) const
{
	return ( getHash() >= obj.getHash() );
}

            }
		}
	}
}


