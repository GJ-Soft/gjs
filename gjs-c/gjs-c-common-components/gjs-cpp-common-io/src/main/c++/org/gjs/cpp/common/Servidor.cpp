#include "CommonIoConfig.h"

#include "Servidor.h"



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

Servidor::Servidor( int iPuerto, const string & sRutaContexto ) : SocketServidor( iPuerto )
{
	if ( !sRutaContexto.empty() )
	{
		contexto.Cargar( sRutaContexto );
	}
}

Servidor::~Servidor()
{
	Parar();
}


bool Servidor::EsValido()
{
	return ( SocketServidor::EsValido() );
}

int Servidor::getPuerto()
{
	return( SocketServidor::getPuerto() );
}

string Servidor::getHost()
{
	return( SocketServidor::getHost() );
}

void Servidor::Iniciar()
{
	if ( !bEjecucion && SocketServidor::EsValido() )
	{
		bParar = false;
		function<void()> rutina = bind( &Servidor::RutinaAtencion, this );
		thServidor = new thread( rutina );
		bEjecucion = true;
	}
}

void Servidor::Parar()
{
	bParar = true;
	SocketServidor::Cerrar();
	if ( thServidor != NULL )
	{
		thServidor->join();
		delete thServidor;
		thServidor = NULL;
	}
}

Propiedades Servidor::Contexto()
{
	return ( contexto );
}

int Servidor::Enviar( const string & sMensaje )
{
	return( SocketServidor::Enviar( sMensaje ) );
}

void Servidor::RutinaAtencion()
{
	while( !bParar )
	{
		try
		{
			SocketAtencion * sockPeticion = SocketServidor::Aceptar();
			function<void(SocketAtencion *)> rutina = bind( &Servidor::RutinaPeticion, this, placeholders::_1 );
			thread thPeticion ( rutina, sockPeticion );
			thPeticion.detach();
		}
		catch ( exception & ex )
		{
			if ( !bParar )
			{
				bParar = ExcepcionProducida( ex );
			}
		}
	}
}

void Servidor::RutinaPeticion( SocketAtencion * socket )
{
	bool bRes = false;
	try
	{
		PeticionRecibida(); 

		bool bFin = false;
		while( !bFin && !bParar  )
		{
			string sMensaje( "" );
			*socket >> sMensaje;
			if ( ! sMensaje.empty() )
			{
				bool bResponder = false;
				string sRespuesta( "" );			
				ProcesarMensaje( sMensaje, bResponder, sRespuesta, bRes, bFin, socket );
				if ( bResponder && !sRespuesta.empty() )
				{
					*socket << sRespuesta;
				}
			}
			// else
			// {
			// 	// TODO: Revisar este caso ¿Generar una callback tipo Ruido recibido?
			// 	cerr << "{Servidor} Ruido recibido!" << endl;
			// }
		}
		PeticionFinalizada( bRes ); 
	}
	catch ( exception & ex )
	{
		if ( !bParar )
		{
			ExcepcionProducidaEnPeticion( ex );
		}
		bRes = false;
	}
	try
	{
		socket->Cerrar();
		delete socket;
	}
	catch( ... )
	{
	}
	Incrementar( bRes );
}

void Servidor::PeticionRecibida()
{
}

void Servidor::PeticionFinalizada( bool bResultado )
{
}

bool Servidor::ExcepcionProducida( const exception & ex )
{
	cerr << ex.what() << endl;
	return( false );
}

void Servidor::ExcepcionProducidaEnPeticion( const exception & ex )
{
	cerr << ex.what() << endl;
}

 			}
		}
	}
}

