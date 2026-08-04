
#include "Valor.h"
#include <ToString.h>
#include <ToInt.h>
#include <Cadenas.h>

//#include <clocale>



using namespace org::gjs::cpp::common;
using namespace std;



namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

Valor::Valor ()
{
	sDato = "";
	bNulo = true;
}

Valor::Valor ( const string & _sDato )
{
	setValor ( _sDato );
}

Valor::Valor ( const char * p_cValor )
{
	setValor ( p_cValor );
}

Valor::Valor ( bool _valor )
{
	setValor ( _valor );
}

Valor::Valor ( short _valor )
{
	setValor ( _valor );
}

Valor::Valor ( int _valor )
{
	setValor ( _valor );
}

Valor::Valor ( long _valor )
{
	setValor ( _valor );
}

Valor::Valor ( long long _valor )
{
	setValor ( _valor );
}

Valor::Valor ( unsigned short _valor )
{
	setValor ( _valor );
}

Valor::Valor ( unsigned int _valor )
{
	setValor ( _valor );
}

Valor::Valor ( unsigned long _valor )
{
	setValor ( _valor );
}

Valor::Valor ( unsigned long long _valor )
{
	setValor ( _valor );
}

Valor::Valor ( float _valor )
{
	setValor ( _valor );
}

Valor::Valor ( double _valor )
{
	setValor ( _valor );
}

Valor::Valor ( long double _valor )
{
	setValor ( _valor );
}

Valor::Valor ( char _valor )
{
	setValor ( _valor );
}

Valor::Valor ( unsigned char _valor )
{
	setValor ( _valor );
}

Valor::Valor ( const Valor & obj )
{
	Asignar( obj );
}

Valor::Valor ( const Valor * obj )
{
	Asignar( obj );
}

Valor::~Valor ()
{
}

long Valor::getHash () const
{
	return( 10 * hash<string>{}( sDato ) +hash<bool>{}( bNulo ) );
}

bool Valor::EsNulo () const
{
	return( bNulo );
}

void Valor::Anular ()
{
	sDato = "";
	bNulo = true;
}


string Valor::getValor () const
{
	return( sDato );
}

bool Valor::getValorBool () const
{
	return ( ( sDato.compare( "1" ) == 0 ) || SonIgualesIn( sDato, "true" ) ||  SonIgualesIn( sDato, "cierto" ) ||
				SonIgualesIn( sDato, "t" )|| SonIgualesIn( sDato, "c" ) );
}

long Valor::getValorEntero () const
{
	return ( ToInt( sDato ) );
}

long long Valor::getValorEnteroLargo () const
{
	long long lRes = 0;
	try
	{
		if ( sDato.size() > 0 )
		{
			lRes = atoll( sDato.c_str() );
		}
	}
	catch (...)
	{
	}
	return ( lRes );
}

double Valor::getValorReal () const
{
	double dRes = 0;
	try
	{
		if ( sDato.size() > 0 )
		{
			//const string viejoLocale = setlocale( LC_NUMERIC, "C" );
			dRes = stod( sDato.c_str() );
			//setlocale( LC_NUMERIC, viejoLocale.c_str()  );
		}
	}
	catch (...)
	{
	}
	return ( dRes );
}

long double Valor::getValorRealLargo () const
{
	long double dRes = 0;
	try
	{
		if ( sDato.size() > 0 )
		{
			//const string viejoLocale = setlocale( LC_NUMERIC, "C" );
			dRes = stold( sDato.c_str() );
			//setlocale( LC_NUMERIC, viejoLocale.c_str()  );
		}
	}
	catch (...)
	{
	}
	return ( dRes );
}

void Valor::setValor ( const string & sValor )
{
	sDato = sValor;
	bNulo = false;
}

void Valor::setValor( const char * p_cValor )
{
	if ( p_cValor != NULL )
	{
		sDato = string ( p_cValor );
		bNulo = false;
	}
	else
	{
		Anular();
	}
}

void Valor::setValor( bool _valor )
{
	setValor ( ToString( _valor ) );
}

void Valor::setValor( short _valor )
{
	setValor ( ToString( _valor ) );
}

void Valor::setValor( int _valor )
{
	setValor ( ToString( _valor ) );
}

void Valor::setValor( long _valor )
{
	setValor ( ToString( _valor ) );
}

void Valor::setValor( long long _valor )
{
	setValor ( ToString( _valor ) );
}

void Valor::setValor( unsigned short _valor )
{
	setValor ( ToString( _valor ) );
}

void Valor::setValor( unsigned int _valor )
{
	setValor ( ToString( _valor ) );
}

void Valor::setValor( unsigned long _valor )
{
	setValor ( ToString( _valor ) );
}

void Valor::setValor( unsigned long long _valor )
{
	setValor ( ToString( _valor ) );
}

void Valor::setValor( float _valor )
{
	setValor ( ToString( _valor ) );
}

void Valor::setValor( double _valor )
{
	setValor ( ToString( _valor ) );
}

void Valor::setValor( long double _valor )
{
	setValor ( ToString( _valor ) );
}

void Valor::setValor( char _valor )
{
	setValor ( ToString( _valor ) );
}

void Valor::setValor( unsigned char _valor )
{
	setValor ( ToString( _valor ) );
}

void Valor::Asignar( const Valor & obj )
{
	sDato = obj.getValor();
	bNulo = obj.EsNulo();
}

void Valor::Asignar( const Valor * obj )
{
	if ( obj != NULL )
	{
		sDato = obj->getValor();
		bNulo = obj->EsNulo();
	}
}

Valor * Valor::Clonar()
{
	Valor * valCopia = new Valor( sDato );
	if ( bNulo )
	{
		valCopia->Anular();
	}
	return ( valCopia );
}

bool Valor::EsValido () const
{
	return( !bNulo || ( sDato.size() == 0 ) );
}

string Valor::toString ()
{
	return ( sDato );
}

Valor & Valor::operator= ( const Valor & obj )
{
	Asignar( obj );
	return ( *this );
}

bool Valor::operator== ( const Valor & obj )
{
	return ( IComparable::operator==( obj ) );
}

bool Valor::operator!= ( const Valor & obj )
{
	return ( IComparable::operator!=( obj ) );
}

 			}
		}
	}
}
