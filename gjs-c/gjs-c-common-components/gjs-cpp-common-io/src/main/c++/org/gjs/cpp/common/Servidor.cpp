#include "CommonIoConfig.h"

#include "Servidor.h"
#include "SocketCliente.h"



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
	if ( thServidor != NULL )
	{
		// Despertar el accept() bloqueante: en winsock closesocket no lo
		// desbloquea. Se abre una conexion al propio puerto y se MANTIENE abierta
		// hasta despues del join, para que accept() la recoja con seguridad.
		SocketCliente * pDespertar = NULL;
		try
		{
			pDespertar = new SocketCliente( "127.0.0.1", getPuerto() );
		}
		catch ( ... )
		{
		}
		thServidor->join();
		delete thServidor;
		thServidor = NULL;
		delete pDespertar;
	}
	SocketServidor::Cerrar();
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
			if ( !bParar )
			{
				function<void(SocketAtencion *)> rutina = bind( &Servidor::RutinaPeticion, this, placeholders::_1 );
				thread thPeticion ( rutina, sockPeticion );
				thPeticion.detach();
			}
			else
			{
				// Conexion efimera de despertar (auto-conexion de Parar): se
				// descarta sin atenderla.
				sockPeticion->Cerrar();
				delete sockPeticion;
			}
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

