#include "BaseConfig.h"
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


/* Las plantillas _Concatenar y Concatenar estan definidas en Concatenar.h,
   junto con las 2.136 instanciaciones explicitas que hacian falta aqui y que
   han dejado de ser necesarias. */

string Concatenar ( const initializer_list<string> & args )
{
    stringstream ss;
	for ( auto const& arg : args )
	{
		ss << arg;
	}
    return ( ss.str() );
}

string Concatenar ( const list<string> & args )
{
    stringstream ss;
	for ( auto const& arg : args )
	{
		ss << arg;
	}
    return ( ss.str() );
}












			}
		}
	}
}
