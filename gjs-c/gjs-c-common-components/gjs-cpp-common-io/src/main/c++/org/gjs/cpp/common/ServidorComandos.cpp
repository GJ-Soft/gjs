#include "CommonIoConfig.h"


#include "ServidorComandos.h"



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

ServidorComandos::ServidorComandos( int iPuerto, const string & sRutaContexto ) : Servidor( iPuerto, sRutaContexto )
{
}

ServidorComandos::~ServidorComandos()
{
}


void ServidorComandos::PeticionRecibida()
{
}

void ServidorComandos::PeticionFinalizada( bool bResultado )
{
}

void ServidorComandos::ProcesarMensaje( const string & sMensaje, bool & bResponder, string & sRespuesta, bool & bResultado, bool & bFin, SocketAtencion * socket )
{
	Comando comando( sMensaje );
	if( comando.EsValido() )
	{
		if ( EsComandoValido( comando ) )
		{
			ComandoRecibido( comando );
			if ( EsComandoFin( comando, bResponder ) )
			{
				bFin = true;
				bResultado = true;
				if ( bResponder )
				{
					sRespuesta = MensajeComandoFin();
				}
			}
			else
			{
				SocketAbierto * socketComandos = new SocketAbierto ( socket ); //, ProcesarMensaje ); 
				ProcesarComando( comando, bResponder, sRespuesta, bResultado, socketComandos );
				delete socketComandos;
			}
			ComandoProcesado( comando, bResultado );
		}
		else
		{
			bResponder = true;
			bResultado = false;
			sRespuesta = MensajeComandoInvalido();
		}		
	}
	else
	{
		bResponder = true;
		bResultado = false;
		sRespuesta = MensajeErrorSintactico();
	}		
}

void ServidorComandos::ComandoRecibido( Comando & comando )
{
}

void ServidorComandos::ComandoProcesado( Comando & comando, bool & bResultado )
{
}

 			}
		}
	}
}


