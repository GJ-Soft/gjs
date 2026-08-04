
#include "Tipo.h"
#include <ToString.h>
#include <Cadenas.h>


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

Tipo::Tipo ()
{
	tipo = TipoDatos::INDEFINIDO;
}

Tipo::Tipo ( TipoDatos _tipo )
{
	tipo = _tipo;
}

Tipo::Tipo( const Tipo & _tipo )
{
	Asignar( _tipo );
}

Tipo::Tipo ( const Tipo * _tipo )
{
	Asignar( _tipo );
}

Tipo::~Tipo ()
{
}

long Tipo::getHash () const
{
	return( (long) tipo );
}

TipoDatos Tipo::getTipo () const
{
	return( tipo );
}

void Tipo::setTipo( TipoDatos valor )
{
	tipo = valor;
}

void Tipo::Asignar( const Tipo & _tipo )
{
	tipo = _tipo.getTipo();
}

void Tipo::Asignar( const Tipo * _tipo )
{
	if ( _tipo != NULL )
	{
		tipo = _tipo->getTipo();
	}
}

Tipo * Tipo::Clonar()
{
	return ( new Tipo( tipo ) );
}

bool Tipo::EsValido () const
{
	return( tipo != TipoDatos::INDEFINIDO );
}

bool Tipo::isEntero () const
{
	return( tipo == TipoDatos::ENTERO );
}

bool Tipo::isReal () const
{
	return( tipo == TipoDatos::REAL );
}

bool Tipo::isCadena () const
{
	return( tipo == TipoDatos::CADENA );
}

bool Tipo::isBooleano () const
{
	return( tipo == TipoDatos::BOOLEANO );
}

bool Tipo::EsCompatible ( const Tipo & _tipo ) const
{
	bool bRes = false;
	if ( isEntero () )
	{
		bRes = _tipo.isEntero() || _tipo.isBooleano();
	}
	else if ( isReal () )
	{
		bRes = _tipo.isEntero() || _tipo.isReal() || _tipo.isBooleano();
	}
	else if ( isCadena () )
	{
		bRes = true;
	}
	else if ( isBooleano () )
	{
		bRes = _tipo.isEntero() || _tipo.isBooleano() || _tipo.isCadena();
	}
	return ( bRes );
}

bool Tipo::EsCompatible ( const Tipo * _tipo ) const
{
	bool bRes = false;
	if ( _tipo != NULL )
	{
		bRes = EsCompatible ( *_tipo );
	}
	return ( bRes );
}

bool Tipo::EsCompatible ( const string & sValor ) const
{
	bool bRes = false;
	if ( isEntero () )
	{
		bRes = EsEntero( sValor );
	}
	else if ( isReal () )
	{
		bRes = EsReal( sValor );
	}
	else if ( isCadena () )
	{
		bRes = true;
	}
	else if ( isBooleano () )
	{
		bRes = EsBooleano( sValor );
	}
	return ( bRes );
}

string Tipo::toString ()
{
	return ( ToString( getTipo() ) );
}

Tipo & Tipo::operator= ( const Tipo & _tipo )
{
	Asignar( _tipo );
	return ( *this );
}

bool Tipo::operator== ( const Tipo & obj ) const
{
	return ( IComparable::operator==( obj ) );
}

bool Tipo::operator!= ( const Tipo & obj ) const
{
	return ( IComparable::operator!=( obj ) );
}

 			}
		}
	}
}
