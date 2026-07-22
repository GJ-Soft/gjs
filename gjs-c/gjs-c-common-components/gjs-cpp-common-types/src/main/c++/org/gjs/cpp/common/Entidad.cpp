#include "CommonTypesConfig.h"

#include "Entidad.h"
#include <Cadenas.h>
#include <ToString.h>
#include <Concatenar.h>



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

Entidad::Entidad ()
{
	sNombre = string( "" );
}

Entidad::Entidad ( const string & _sNombre )
{
	sNombre = _sNombre;
}

Entidad::Entidad ( Entidad & obj )
{
	Asignar( obj );
}

Entidad::Entidad ( Entidad * obj )
{
	Asignar( obj );
}

Entidad::~Entidad ()
{
	LimpiarAtributos();
}

long Entidad::getHash () const
{
	long lHash = hash<string>{}( sNombre );
	for ( const auto & par : mapDefinicion )
	{
		Atributo * atributo = reinterpret_cast<Atributo *>( par.second );
		lHash = lHash + 1000 * atributo->getHash();
	}
	return( lHash );
}

string Entidad::getNombre () const
{
	return( sNombre );
}

void Entidad::setNombre( const string & sValor )
{
	sNombre = sValor;
}

bool Entidad::EsValida () const
{
	bool bRes = EsToken( sNombre ) && ( mapDefinicion.size() > 0 );
	if ( bRes )
	{
		for ( const auto & par : mapDefinicion )
		{
			Atributo * atributo = reinterpret_cast<Atributo *>( par.second );
			bRes = bRes && atributo->EsValido();
		}
	}
	return( bRes );
}

int Entidad::NumAtributos ()
{
	return ( mapDefinicion.size() );
}

bool Entidad::TieneAtributo ( const string & sAtributo )
{
	map<string, Atributo *>::iterator it = mapDefinicion.find( sAtributo );
	return ( it != mapDefinicion.end() );
}

Atributo * Entidad::getAtributo ( const string & sAtributo )
{
	Atributo * atributo = NULL;
	map<string, Atributo *>::iterator it = mapDefinicion.find( sAtributo );
	if ( it != mapDefinicion.end() )
	{
		atributo = it->second;
	}
	return ( atributo );
}

Atributo * Entidad::getAtributo ( int iIndice )
{
	Atributo * atributo = NULL;
	if ( ( iIndice >= 0 ) && ( iIndice < mapDefinicion.size() ) )
	{
		map<string, Atributo *>::iterator it = mapDefinicion.begin();
		int iPos = 0;
		while ( ( iPos < iIndice ) && ( it != mapDefinicion.end() ) )
		{
			iPos = iPos + 1;
			++it;
		}
		if ( it != mapDefinicion.end() )
		{
			atributo = it->second;
		}
	}
	return ( atributo );
}

int Entidad::getIndiceAtributo ( const string & sAtributo )
{
	int iRes = -1;
	map<string, Atributo *>::iterator it = mapDefinicion.find( sAtributo );
	if ( it != mapDefinicion.end() )
	{
		iRes = distance( mapDefinicion.begin(), it );
	}
	return ( iRes );
}

vector<string> * Entidad::ListaAtributos ()
{
	vector<string> * vecAtributos = new vector<string>();
	for ( const auto & par : mapDefinicion )
	{
		vecAtributos->push_back( par.first );
	}
	return ( vecAtributos );
}

void Entidad::InsertarAtributo ( Atributo * atributo )
{
	if ( atributo != NULL )
	{
		if ( !TieneAtributo( atributo->getNombre() ) )
		{
			mapDefinicion[ atributo->getNombre() ] = atributo;
		}
	}
}

void Entidad::InsertarAtributo ( TipoDatos tipo, const string & sAtributo, bool bAnulable )
{
	InsertarAtributo( new Atributo( tipo, sAtributo, bAnulable ) );
}

void Entidad::InsertarAtributo ( Tipo & tipo, const string & sAtributo, bool bAnulable )
{
	InsertarAtributo( new Atributo( tipo, sAtributo, bAnulable ) );
}

void Entidad::EliminarAtributo ( const string & sAtributo )
{
	map<string, Atributo *>::iterator it = mapDefinicion.find( sAtributo );
	if ( it != mapDefinicion.end() )
	{
		delete it->second;
		mapDefinicion.erase( it );
	}
}

void Entidad::EliminarAtributo ( int iIndice )
{
	if ( ( iIndice >= 0 ) && ( iIndice < mapDefinicion.size() ) )
	{
		map<string, Atributo *>::iterator it = mapDefinicion.begin();
		int iPos = 0;
		while ( ( iPos < iIndice ) && ( it != mapDefinicion.end() ) )
		{
			iPos = iPos + 1;
			++it;
		}
		if ( it != mapDefinicion.end() )
		{
			delete it->second;
			mapDefinicion.erase( it );
		}
	}
}

void Entidad::LimpiarAtributos ()
{
	for ( const auto & par : mapDefinicion )
	{
		Atributo * atributo = reinterpret_cast<Atributo *>( par.second );
		delete atributo;
	}
	mapDefinicion.clear();
}

bool Entidad::EsCompatible ( Entidad & obj )
{
	bool bRes = false;
	if ( EsValida() && obj.EsValida() && ( NumAtributos() <= obj.NumAtributos() ) )
	{
		bRes = true;
		for ( int i = 0; i < NumAtributos(); i = i + 1 )
		{
			bRes = bRes && getAtributo( i )->EsCompatible ( obj.getAtributo( i ) );
		}
	}
	return ( bRes );
}

bool Entidad::EsCompatible ( Entidad * obj )
{
	bool bRes = false;
	if ( obj != NULL )
	{
		bRes = EsCompatible ( *obj );
	}
	return ( bRes );
}

void Entidad::Asignar( Entidad & entidad )
{
	sNombre = entidad.getNombre();
	for ( int i = 0; i < entidad.NumAtributos(); i = i + 1 )
	{
		InsertarAtributo ( entidad.getAtributo( i )->Clonar() );
	}
}

void Entidad::Asignar( Entidad * entidad )
{
	if ( entidad != NULL )
	{
		Asignar( *entidad );
	}
}

Entidad * Entidad::Clonar()
{
	return( new Entidad( this ) );
}

string Entidad::toString ()
{
	try
	{
		ostringstream conv;
		bool bIni = true;
		conv << "(";
		for ( auto & obj : mapDefinicion )
		{
			if ( !bIni )
			{
				conv << "; ";
			}
			conv << obj.first << "=" << obj.second->toString();
			bIni = false;
		}
		conv << ")";
		return ( Concatenar( "[Entidad={Nombre=[", getNombre(), "]; Atributos=", conv.str(), "}]" ) );
	}
	catch (...)
	{
		return ( Concatenar( "[Entidad={Nombre=[", getNombre(), "]; Atributos=[Object Error]}]" ) );
	}
}

Entidad & Entidad::operator= ( Entidad & entidad )
{
	Asignar( entidad );
	return ( *this );
}


bool Entidad::operator== ( Entidad & obj )
{
	return ( IComparable::operator==( obj ) );
}

bool Entidad::operator!= ( Entidad & obj )
{
	return ( IComparable::operator!=( obj ) );
}

 			}
		}
	}
}

