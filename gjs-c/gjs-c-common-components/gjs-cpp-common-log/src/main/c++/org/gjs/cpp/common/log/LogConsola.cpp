#include "../LogConfig.h"
#include "LogConsola.h"


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


LogConsola::LogConsola () : LogEncabezado ()
{
}

LogConsola::LogConsola ( string sNomProceso ) : LogEncabezado ( sNomProceso )
{
}

bool LogConsola::Inicializar ()
{
	/* La consola no necesita preparacion. */
	return ( true );
}

void LogConsola::LogInterno ( const std::string & sMensaje )
{
	cout << sMensaje << endl;
}

                }
            }
        }
    }
}
