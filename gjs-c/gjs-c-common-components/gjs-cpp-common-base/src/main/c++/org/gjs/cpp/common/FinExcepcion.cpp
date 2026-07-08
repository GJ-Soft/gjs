#include "FinExcepcion.h"
#include "ToString.h"
#include "Concatenar.h"


#define MENSAJE_EXCEPCION		"Se ha llamado exit() con codigo: "


using namespace std;


namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {


FinExcepcion::FinExcepcion( const string & sModulo, const string & sRutina, int iCodigo ) : Excepcion( sModulo,sRutina, Concatenar( MENSAJE_EXCEPCION, ToString( iCodigo ) ) )
{
}


            }
		}
	}
}
