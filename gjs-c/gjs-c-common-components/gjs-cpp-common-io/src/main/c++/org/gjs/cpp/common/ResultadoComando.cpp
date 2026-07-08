#include "CommonIoConfig.h"

#include "ResultadoComando.h"



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

ResultadoComando::ResultadoComando() : Comando()
{
}

ResultadoComando::ResultadoComando( ComandoIETF & comando, const string & _sRespuesta ) : Comando( comando.toString() )
{
	sRespuesta = _sRespuesta;
}

ResultadoComando::ResultadoComando( Comando & comando, const string & _sRespuesta ) : Comando( comando.toString() )
{
	sRespuesta = _sRespuesta;
}

ResultadoComando::ResultadoComando( const string & _sComando, const initializer_list<string> & lisArgumentos, const string & _sRespuesta ) : Comando( _sComando, lisArgumentos )
{
	sRespuesta = _sRespuesta;
}

ResultadoComando::ResultadoComando( const string & sExpresion, const string & _sRespuesta ) : Comando( sExpresion )
{
	sRespuesta = _sRespuesta;
}

ResultadoComando::~ResultadoComando()
{
}


string & ResultadoComando::getRespuestaEsperada() 
{
	return( sRespuesta );
}

void ResultadoComando::setRespuestaEsperada( const string & sValor )
{
	sRespuesta = sValor;
}

 			}
		}
	}
}


