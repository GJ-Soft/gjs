#include "CommonIoConfig.h"

#include "ESExcepcion.h"


using namespace std;

namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

ESExcepcion::ESExcepcion( const string & _sModulo, const string & _sRutina, const std::ios_base::failure & exOcurrida ) :
										Excepcion( _sModulo, _sRutina, exOcurrida )
{
}


            }
		}
	}
}
