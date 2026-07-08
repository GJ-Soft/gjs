
#include "TipoDatos.h"


using namespace std;


namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

string ToString ( TipoDatos tipo )
{
	if ( tipo == TipoDatos::ENTERO )
	{
		return ( string ( "Entero" ) );
	}
	else if ( tipo == TipoDatos::REAL )
	{
		return ( string ( "Real" ) );
	}
	else if ( tipo == TipoDatos::CADENA )
	{
		return ( string ( "Cadena" ) );
	}
	else if ( tipo == TipoDatos::BOOLEANO )
	{
		return ( string ( "Booleano" ) );
	}
	return ( string ( "Indefinido" ) );
}

 			}
		}
	}
}


