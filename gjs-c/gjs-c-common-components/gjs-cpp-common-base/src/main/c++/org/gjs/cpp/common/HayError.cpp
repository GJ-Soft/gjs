
#include "HayError.h"


using namespace std;
using namespace org::gjs::cpp::common;




namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {


HayError::HayError()
{
}

HayError::~HayError()
{
}

bool HayError::isError()
{
	return( bError );
}

void HayError::setError( bool bValor )
{
	bError = bValor;
}


            }
		}
	}
}
