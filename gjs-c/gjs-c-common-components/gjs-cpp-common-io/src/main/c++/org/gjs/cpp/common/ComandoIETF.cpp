#include "CommonIoConfig.h"

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

ComandoIETF::ComandoIETF() : Comando()
{
}

ComandoIETF::ComandoIETF( const string & _sComando, const initializer_list<string> & lisArgumentos ) : Comando( _sComando, lisArgumentos )
{
}

ComandoIETF::ComandoIETF( const string & sExpresion ) : Comando( sExpresion )
{
}

ComandoIETF::~ComandoIETF()
{
}

string ComandoIETF::toString()
{
	return( ConstruirMensajeIETF( Comando::toString() ) ); 
}

 			}
		}
	}
}


