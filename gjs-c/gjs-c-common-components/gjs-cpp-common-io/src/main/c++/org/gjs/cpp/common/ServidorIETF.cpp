#include "CommonIoConfig.h"


#include "ServidorIETF.h"
#include "CodigosIETF.h"
#include "ComandosIETF.h"


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

ServidorIETF::ServidorIETF( int iPuerto, const string & sRutaUsuarios, const string & sRutaContexto, bool _bPermiteAnonimo ) : 
					ServidorSesion( iPuerto, sRutaUsuarios, sRutaContexto, _bPermiteAnonimo )
{
	setComandos = new set<string>();
}

ServidorIETF::ServidorIETF( int iPuerto, const list<string> & lisComandos, const string & sRutaUsuarios, const string & sRutaContexto, bool _bPermiteAnonimo ) : 
					ServidorSesion( iPuerto, sRutaUsuarios, sRutaContexto, _bPermiteAnonimo )
{
	setComandos = new set<string>( lisComandos.begin(), lisComandos.end() );
}

ServidorIETF::ServidorIETF( int iPuerto, const initializer_list<string> & lisComandos, const string & sRutaUsuarios, const string & sRutaContexto, bool _bPermiteAnonimo ) : 
					ServidorSesion( iPuerto, sRutaUsuarios, sRutaContexto, _bPermiteAnonimo )
{
	setComandos = new set<string>( lisComandos );
}

ServidorIETF::~ServidorIETF()
{
	setComandos->clear();
	delete setComandos;
}

void ServidorIETF::addComando( const string & sComando )
{
	setComandos->insert( sComando );
}

void ServidorIETF::addComandos( const list<string> & lisComandos )
{
	setComandos->insert( lisComandos.begin(), lisComandos.end() );
}

void ServidorIETF::addComandos( const initializer_list<string> & lisComandos )
{
	setComandos->insert( lisComandos );
}

bool ServidorIETF::isComando( const string & sComando )
{
	return( setComandos->find( sComando ) != setComandos->end() );
}

string ServidorIETF::MensajeComandoFin()
{
	return( ConstruirRespuestaIETF( IETF_SALIR ) );
}

string ServidorIETF::MensajeComandoInvalido()
{
	return( ConstruirRespuestaIETF( IETF_ERROR_INTERNO, "Comando desconocido" ) );
}

string ServidorIETF::MensajeErrorSintactico()
{
	return( ConstruirRespuestaIETF( IETF_ERROR_SINTACTICO ) );
}

string ServidorIETF::MensajeSesionAbierta()
{
	return( ConstruirRespuestaIETF( IETF_SESION_INICIADA ) );
}

string ServidorIETF::MensajeSesionCerrada()
{
	return( ConstruirRespuestaIETF( IETF_SALIR ) );
}

string ServidorIETF::MensajeFaltaClave()
{
	return( ConstruirRespuestaIETF( IETF_FALTA_CLAVE ) );
}

string ServidorIETF::MensajeImposibleAperturaSesion()
{
	return( ConstruirRespuestaIETF( IETF_SESION_NO_INICIADA ) );
}

string ServidorIETF::MensajeUsuarioInvalido()
{
	return( ConstruirRespuestaIETF( IETF_SESION_NO_INICIADA ) );
}

string ServidorIETF::MensajeSesionNoAbierta()
{
	return( ConstruirRespuestaIETF( IETF_NECESARIO_SESION ) );
}

string ServidorIETF::MensajeOk()
{
	return( ConstruirRespuestaIETF( IETF_OK ) );
}


bool ServidorIETF::EsComandoValido( Comando & comando )
{
	bool bRes = false;
	if ( RequiereSesion() )
	{
		if( comando.isComando( IETF_CMD_USUARIO ) || 
			comando.isComando( IETF_CMD_CLAVE ) )
		{
			bRes = ( comando.NumArgumentos() == 1 );
		}
		else if( comando.isComando( IETF_CMD_SALIR ) )
		{
			bRes = ( comando.NumArgumentos() == 0 );
		}
		else
		{
			bRes = isComando( comando.getComando() );
		}
	}
	else
	{
		bRes = isComando( comando.getComando() );
	}	
	return( bRes );
}

bool ServidorIETF::EsComandoFin( Comando & comando, bool & bResponder )
{
	bResponder = false;
	return ( false );
}

bool ServidorIETF::EsComandoInicioSesion( Comando & comando, string & sUsuario, string & sClave )
{
	bool bRes = false;
	if ( comando.isComando( IETF_CMD_USUARIO ) )
	{
		if ( comando.NumArgumentos() == 1 )
		{
			bRes = true;
			sUsuario = comando.getArgumento( 0 );
		}
	}
	else if ( comando.isComando( IETF_CMD_CLAVE ) )
	{
		bRes = true;
		if ( comando.NumArgumentos() == 1 )
		{
			sClave = comando.getArgumento( 0 );
		}
	}
	return( bRes );
}

bool ServidorIETF::EsComandoFinSesion( Comando & comando )
{
	bool bRes = false;
	if ( comando.isComando( IETF_CMD_SALIR ) )
	{
		if ( comando.NumArgumentos() == 0 )
		{
			bRes = true;
		}
	}
	return( bRes );
}

 			}
		}
	}
}
