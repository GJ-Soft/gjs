#include "CommonIoConfig.h"

#include "CodigosIETF.h"



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

const string IETF_FINALIZADOR = "\r\n";


		
bool EsCodigoIETF( const string & sCodigo )
{
	return( EsNatural( sCodigo ) && ( sCodigo.size() == 3 ) );
}

string ConstruirRespuestaIETF( const string & sCodigo, const string sMensaje )
{
	string sRes( "" );
	string sCodTemp = sCodigo;
	if ( !EsCodigoIETF( sCodigo ) )
	{
		sCodTemp = IETF_DESCONOCIDO;
	}
	if ( sMensaje.empty() )
	{
		sRes = Concatenar( sCodTemp, IETF_FINALIZADOR );
	}
	else
	{
		sRes = Concatenar( sCodTemp, " ", sMensaje, IETF_FINALIZADOR );
	}
	return( sRes );
}

bool ProcesarRespuestaIETF( const string & sRespuesta, string & sCodigo, string & sMensaje )
{
	bool 	bRes = false;
	string 	sTemp = sRespuesta;
	if ( TerminaPor( sRespuesta, IETF_FINALIZADOR ) )
	{
		sTemp = EliminarTodos( sRespuesta, IETF_FINALIZADOR );
	}
	// En el caso de HTTP antes del código viene la versión de HTTP
	if ( EmpiezaPor( sTemp, "HTTP" ) )
	{
		sTemp = LTrim( SubcadenaDesde( sTemp, ' ' ) );
	}
	sCodigo = SubcadenaHasta( sTemp, ' ' );			
	sMensaje = SubcadenaDesde( sTemp, ' ' );			
	bRes = EsCodigoIETF( sCodigo );
	return( bRes );
}

string ConstruirMensajeIETF( const string sMensaje )
{
	return( Concatenar( sMensaje, IETF_FINALIZADOR ) );
}

string ProcesarMensajeIETF( const string & sMensaje )
{
	return( EliminarTodos( sMensaje, IETF_FINALIZADOR ) );
}

 			}
		}
	}
}


