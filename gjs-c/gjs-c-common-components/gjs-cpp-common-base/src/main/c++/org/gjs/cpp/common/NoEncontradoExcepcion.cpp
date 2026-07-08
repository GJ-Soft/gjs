#include "BaseConfig.h"

#include "NoEncontradoExcepcion.h"
#include "Concatenar.h"


using namespace std;

namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

NoEncontradoExcepcion::NoEncontradoExcepcion( const string & _sModulo, const string & _sRutina, const string & _sTipo, const string & _sObjeto ) :
										Excepcion( _sModulo, _sRutina, Concatenar( "No se ha encontrado el/la ", _sTipo, " [", _sObjeto, "]" ) )
{
}


            }
		}
	}
}
