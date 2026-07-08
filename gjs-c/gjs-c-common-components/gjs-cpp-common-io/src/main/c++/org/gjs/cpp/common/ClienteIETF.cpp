#include "CommonIoConfig.h"

#include "ClienteIETF.h"
#include "CodigosIETF.h"
#include "ComandosIETF.h"
#include "ComandoIETF.h"


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

ClienteIETF::ClienteIETF( const string & sIP, int iPuerto ) : ClienteIETF( sIP, iPuerto, "" )
{
}


ClienteIETF::ClienteIETF( const string & sIP, int iPuerto, const string & _sUsuario, const string & _sClave ) : ClienteSesion( sIP, iPuerto, _sUsuario, _sClave )
{
	ModificadoUsuario();
}

ClienteIETF::~ClienteIETF()
{
}

void ClienteIETF::ModificadoUsuario()
{
	comandoApertura.clear();
	ComandoIETF cmdUsuario = ComandoIETF( IETF_CMD_USUARIO, { getUsuario() } );
	comandoApertura.push_back( ResultadoComando( cmdUsuario, ConstruirRespuestaIETF( IETF_FALTA_CLAVE ) ) );
	if ( getUsuario().compare( CS_USUARIO_ANONIMO ) != 0 )
	{
		ComandoIETF cmdClave = ComandoIETF( IETF_CMD_CLAVE, { getClave() } );
		comandoApertura.push_back( ResultadoComando( cmdClave, ConstruirRespuestaIETF( IETF_SESION_INICIADA ) ) );
	}
	ComandoIETF cmdSalir = ComandoIETF( IETF_CMD_SALIR, {} );
	comandoCierre = ResultadoComando( cmdSalir, ConstruirRespuestaIETF( IETF_SALIR ) );
}

list<ResultadoComando> & ClienteIETF::ComandoInicioSesion()
{
	return ( comandoApertura );
}

ResultadoComando & ClienteIETF::ComandoFinSesion()
{
	return ( comandoCierre );
}

 			}
		}
	}
}

