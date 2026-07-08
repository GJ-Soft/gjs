#include "CommonIoConfig.h"

#include "ClienteComandos.h"



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

ClienteComandos::ClienteComandos( const string & sIP, int iPuerto ) : Cliente( sIP, iPuerto )
{
}

ClienteComandos::~ClienteComandos()
{
}

void ClienteComandos::EnviarComando( Comando & comando, string & sRespuesta )
{
	Cliente::EnviarMensaje( comando.toString(), sRespuesta );
}

void ClienteComandos::EnviarComando( string sComando, const initializer_list<string> & lisArgumentos, string & sRespuesta )
{
	Comando comando( sComando, lisArgumentos );
	EnviarComando( comando, sRespuesta );
}

 			}
		}
	}
}

