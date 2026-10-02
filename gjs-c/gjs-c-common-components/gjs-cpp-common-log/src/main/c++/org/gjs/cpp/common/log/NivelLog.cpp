#include "../LogConfig.h"
#include "NivelLog.h"


using namespace std;


namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {
                namespace log
                {

NivelLog ToNivelLog ( int iNivel )
{
	return ( static_cast<NivelLog> ( iNivel ) );
}

int ToInt ( NivelLog nivel )
{
	return  ( static_cast<int> ( nivel ) );
}

string ToString ( NivelLog nivel )
{
	if ( nivel == NivelLog::NIVEL_TRAZA )
	{
		return ( string ( LOG_TXT_NIVEL_TRAZA ) );
	}
	else if ( nivel == NivelLog::NIVEL_INFORMACION )
	{
		return ( string ( LOG_TXT_NIVEL_INFORMACION ) );
	}
	else if ( nivel == NivelLog::NIVEL_AVISO )
	{
		return ( string ( LOG_TXT_NIVEL_AVISO ) );
	}
	else if ( nivel == NivelLog::NIVEL_ERROR )
	{
		return ( string ( LOG_TXT_NIVEL_ERROR ) );
	}
	else if ( nivel == NivelLog::NIVEL_DEPURACION )
	{
		return ( string ( LOG_TXT_NIVEL_DEPURACION ) );
	}
	else if ( nivel == NivelLog::NIVEL_TODOS )
	{
		return ( string ( LOG_TXT_NIVEL_TODOS ) );
	}
	else if ( nivel == NivelLog::NIVEL_NINGUNO )
	{
		return ( string ( LOG_TXT_NIVEL_NINGUNO ) );
	}
	else
	{
		return ( "" );
	}
}



                }
            }
        }
    }
}
