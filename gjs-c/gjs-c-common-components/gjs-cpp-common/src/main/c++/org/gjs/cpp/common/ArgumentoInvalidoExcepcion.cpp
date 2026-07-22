


#include "CppCommonConfig.h"
#include "ArgumentoInvalidoExcepcion.h"



#define MENSAJE_EXCEPCION		"El valor del argumento {} es invalido"



using namespace std;


namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {


ArgumentoInvalidoExcepcion::ArgumentoInvalidoExcepcion( const string & sModulo, const string & sRutina, const string & sArgumento ) : Excepcion( sModulo, sRutina, format( MENSAJE_EXCEPCION, sArgumento ) )
{
}


            }
		}
	}
}
