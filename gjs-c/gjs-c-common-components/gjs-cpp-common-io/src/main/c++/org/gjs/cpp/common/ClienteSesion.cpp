#include "CommonIoConfig.h"

#include "ClienteSesion.h"



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

ClienteSesion::ClienteSesion( const string & sIP, int iPuerto, const string & _sUsuario, const string & _sClave ) : ClienteComandos( sIP, iPuerto )
{
	EstablecerUsuario( _sUsuario, _sClave, true );
}

ClienteSesion::~ClienteSesion()
{
	// No se puede llamar a carrar sesion por llamar a métodos virtuales puros.
}

string ClienteSesion::getUsuario()
{
	return ( sUsuario );
}

string ClienteSesion::getClave()
{
	return ( sClave );
}

void ClienteSesion::setUsuario( const string & _sUsuario, const string & _sClave )
{
	EstablecerUsuario( _sUsuario, _sClave, false );
}				

void ClienteSesion::setUsuarioAnonimo()
{
	setUsuario( CS_USUARIO_ANONIMO );
}

bool ClienteSesion::SesionAbierta()
{
	return ( bSesionAbierta );
}

bool ClienteSesion::AbrirSesion()
{
	bool bRes = !bSesionNecesaria;
	if ( bSesionNecesaria && !bSesionAbierta && EsValido() )
	{
		bRes = true;
		for ( ResultadoComando & comando : ComandoInicioSesion() )
		{
			string sRespuesta;
			ClienteComandos::EnviarComando( comando, sRespuesta );
			if ( !comando.getRespuestaEsperada().empty() )
			{
				if ( sRespuesta.compare( comando.getRespuestaEsperada() ) != 0 )
				{
					bRes = false;
					break;
				}
			}
		}
		if ( bRes )
		{
			bSesionAbierta = true;
		}
	}
	return( bRes );
}

void ClienteSesion::CerrarSesion()
{
	if ( bSesionNecesaria && bSesionAbierta )
	{
		ResultadoComando comando = ComandoFinSesion();
		string sRespuesta;
		ClienteComandos::EnviarComando( comando, sRespuesta );
		if ( !comando.getRespuestaEsperada().empty() )
		{
			if ( sRespuesta.compare( comando.getRespuestaEsperada() ) == 0 )
			{
				bSesionAbierta = false;
			}
		}
		else
		{
			bSesionAbierta = false;
		}	
	}
}

bool ClienteSesion::EsValido()
{
	return ( ( !bSesionNecesaria || ( EsToken( sUsuario ) && ( ( sClave.size() == 0 ) || EsToken( sClave ) ) ) ) && Cliente::EsValido() );
}

void ClienteSesion::EnviarComando( Comando & comando, string & sRespuesta )
{
	if ( bSesionAbierta || !bSesionNecesaria )
	{
		ClienteComandos::EnviarComando( comando, sRespuesta );
	}
}

void ClienteSesion::EnviarComando( string sComando, const initializer_list<string> & lisArgumentos, string & sRespuesta )
{
	if ( bSesionAbierta || !bSesionNecesaria )
	{
		ClienteComandos::EnviarComando( sComando, lisArgumentos, sRespuesta );
	}
}

void ClienteSesion::EnviarMensaje( const string & sMensaje, string & sRespuesta )
{
	if ( bSesionAbierta || !bSesionNecesaria )
	{
		Cliente::EnviarMensaje( sMensaje, sRespuesta );
	}
}

void ClienteSesion::EnviarMensaje( const string & sMensaje )
{
	if ( bSesionAbierta || !bSesionNecesaria )
	{
		Cliente::EnviarMensaje( sMensaje );
	}
}

void ClienteSesion::EstablecerUsuario( const string & _sUsuario, const string & _sClave, bool bConstructor )
{
	if ( !bSesionAbierta )
	{
		sUsuario = _sUsuario;
		sClave = _sClave;
		bSesionNecesaria = !sUsuario.empty();
		if ( !bConstructor )
		{
			ModificadoUsuario();
		}
	}
}				

 			}
		}
	}
}

