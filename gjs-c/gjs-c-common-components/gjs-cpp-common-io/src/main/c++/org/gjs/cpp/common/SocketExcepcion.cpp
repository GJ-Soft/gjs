#include "CommonIoConfig.h"

#include "SocketExcepcion.h"



using namespace std;

namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

SocketExcepcion::SocketExcepcion( const string & _sModulo, const string & _sRutina, int _iErrno ) : 
										SistemaExcepcion( _sModulo, _sRutina, _iErrno )
{
}				

 			}
		}
	}
}
