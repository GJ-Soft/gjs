#include "BaseConfig.h"
#include "Excepcion.h"

#include "Concatenar.h"

using namespace std;


namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

Excepcion::Excepcion( const string & _sModulo, const string & _sRutina, const string & _sMensaje ) : runtime_error( _sMensaje.c_str () )
{
	sModulo = _sModulo;
	sRutina = _sRutina;
	sMensaje = _sMensaje;
}

Excepcion::Excepcion ( const string & _sModulo, const string & _sRutina, const string & _sMensaje, const exception & ex ) : runtime_error( _sMensaje.c_str () )
{
	sModulo = _sModulo;
	sRutina = _sRutina;
	sMensaje = Concatenar ( _sMensaje, " [", ex.what(), "]" );
}

Excepcion::Excepcion ( const string & _sModulo, const string & _sRutina, const exception & ex ) : runtime_error( ex.what() )
{
	sModulo = _sModulo;
	sRutina = _sRutina;
	sMensaje = string( ex.what() );
}

string Excepcion::getModulo () const
{
	return ( sModulo );
}

string Excepcion::getRutina () const
{
	return ( sRutina );
}

string Excepcion::getMensaje() const
{
	return ( sMensaje );
}

const char * Excepcion::what() const noexcept
{
	return ( Concatenar( "[", sModulo, "::", sRutina, "] ", sMensaje ).c_str () );
}

string Excepcion::whatExt() const
{
	return ( Concatenar( "[", sModulo, "::", sRutina, "] ", sMensaje ) );
}

exception & Excepcion::toException()
{
	return ( (exception &) *this );
}


            }
		}
	}
}
