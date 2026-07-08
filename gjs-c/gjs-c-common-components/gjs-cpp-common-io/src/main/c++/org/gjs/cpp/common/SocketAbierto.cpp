#include "CommonIoConfig.h"

#include "SocketAbierto.h"




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

SocketAbierto::SocketAbierto( SocketAtencion * _sockAtencion ) //, PROCEDIMIENTO_PROCESAR_COMANDO _procProcesarComando )
{
	sockAtencion = _sockAtencion;
	//procProcesarComando =_procProcesarComando;
}

SocketAbierto::~SocketAbierto()
{
}

void SocketAbierto::Responder( string & sRespuesta )
{
	if ( sockAtencion != NULL )
	{
		try
		{
			sockAtencion->Enviar( sRespuesta );
		}
		catch ( exception & ex )
		{
			throw( ex );
		}
	}
}

/*
void SocketAbierto::EnviarComando( Comando & comando, string & sRespuesta )
{
	if ( sockAtencion != NULL )
	{
		try
		{
			sockAtencion->Enviar( comando.toString() );
			sRespuesta = "";
			sockAtencion->Recibir( sRespuesta );
		}
		catch ( exception & ex )
		{
			throw( ex );
		}
	}
}

void SocketAbierto::EnviarComando( string sComando, const initializer_list<string> & lisArgumentos, string & sRespuesta )
{
	Comando comando( sComando, lisArgumentos );
	EnviarComando( comando, sRespuesta );
}
*/

 			}
		}
	}
}
