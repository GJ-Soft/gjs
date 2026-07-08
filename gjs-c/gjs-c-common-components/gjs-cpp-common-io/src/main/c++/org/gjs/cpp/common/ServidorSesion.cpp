#include "CommonIoConfig.h"


#include "ServidorSesion.h"



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

ServidorSesion::ServidorSesion( int iPuerto, const string & sRutaUsuarios, const string & sRutaContexto, bool _bPermiteAnonimo ) : ServidorComandos( iPuerto, sRutaContexto )
{
	bPermiteAnonimo = _bPermiteAnonimo;
	if ( !sRutaUsuarios.empty() )
	{
		if ( !gestorUsuarios.Cargar( sRutaUsuarios ) )
		{
			throw Excepcion( "ServidorSesion", "ServidorSesion", "No se ha cargado correctamente el fichero de usuarios" );
		}
	}
	else
	{
		bSesionNecesaria = false;
	}
}

ServidorSesion::~ServidorSesion()
{
	gestorUsuarios.Limpiar();
	gestorSesiones.Limpiar();
}

bool ServidorSesion::EsValido()
{
	return ( ServidorComandos::EsValido() && ( !bSesionNecesaria || ( gestorUsuarios.NumUsuarios() > 0 ) ) );
}

bool ServidorSesion::RequiereSesion()
{
	return ( bSesionNecesaria );
}

void ServidorSesion::ProcesarComando( Comando & comando, bool & bResponder, string & sRespuesta, bool & bResultado, SocketAbierto * socket )
{
	if ( !bSesionNecesaria )
	{
		ProcesarComandoSesion( comando, bResponder, sRespuesta, bResultado, socket );
	}
	else if( !gestorSesiones.EstaAbierta() )
	{
		bResponder = true;
		bResultado = false;
		string sUsuario = gestorSesiones.getUsuario(); 
		string sClave;
		if ( EsComandoInicioSesion( comando, sUsuario, sClave ) )
		{
			if ( sUsuario.empty() )
			{
				sUsuario = gestorSesiones.getUsuario(); 
			}
			else if ( sClave.empty() )
			{
				if ( bPermiteAnonimo && ( sUsuario.compare( CS_USUARIO_ANONIMO ) == 0 ) )
				{
					if ( gestorSesiones.Abrir( sUsuario ) )
					{
						bResultado = true;
						sRespuesta = MensajeSesionAbierta();
						SesionIniciada( sUsuario );
					}
					else
					{
						sRespuesta = MensajeImposibleAperturaSesion();
					}
				}
				else if ( gestorUsuarios.Existe( sUsuario ) )
				{
					gestorSesiones.setUsuario( sUsuario );
					bResultado = true;
					sRespuesta = MensajeFaltaClave();
				}
				else
				{
					sRespuesta = MensajeUsuarioInvalido();
				}
			}
			else 
			{
				if ( gestorUsuarios.Validar( sUsuario, sClave ) )
				{
					if ( gestorSesiones.Abrir( sUsuario ) )
					{
						bResultado = true;
						sRespuesta = MensajeSesionAbierta();
						SesionIniciada( sUsuario );
					}
					else
					{
						sRespuesta = MensajeImposibleAperturaSesion();
					}
				}
				else
				{
					sRespuesta = MensajeUsuarioInvalido();
				}
				if ( !bResultado )
				{
					gestorSesiones.Cerrar( sUsuario );
				}
			}
		}
		else
		{
			sRespuesta = MensajeSesionNoAbierta();
		}
	}
	else
	{
		if ( EsComandoFinSesion( comando ) )
		{
			string sUsuario = gestorSesiones.getUsuario();
			gestorSesiones.Cerrar();
			SesionFinalizada( sUsuario );
			bResponder = true;
			bResultado = true;
			sRespuesta = MensajeSesionCerrada();
		}
		else
		{
			ProcesarComandoSesion( comando, bResponder, sRespuesta, bResultado, socket );
		}
	}	
}

void ServidorSesion::SesionIniciada( const string & sUsuario )
{
}

void ServidorSesion::SesionFinalizada( const string & sUsuario )
{
}

 			}
		}
	}
}


