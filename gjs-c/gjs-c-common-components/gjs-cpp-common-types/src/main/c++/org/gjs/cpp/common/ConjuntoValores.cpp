#include "CommonTypesConfig.h"

#include "ConjuntoValores.h"



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

ConjuntoValores::ConjuntoValores ()
{
	bPermiteInsercion = true;
}

ConjuntoValores::ConjuntoValores ( const initializer_list<string> & lisAtributos, bool _bPermiteInsercion )
{
	bPermiteInsercion = _bPermiteInsercion;
	for ( string const & sAtributo : lisAtributos )
	{
		mapValores[ sAtributo ] = new Valor ();
	}
}

ConjuntoValores::ConjuntoValores ( const list<string> & lisAtributos, bool _bPermiteInsercion )
{
	bPermiteInsercion = _bPermiteInsercion;
	for ( string const & sAtributo : lisAtributos )
	{
		mapValores[ sAtributo ] = new Valor ();
	}
}

ConjuntoValores::ConjuntoValores ( const string & sRuta, bool _bPermiteInsercion )
{
	bPermiteInsercion = true;
	Cargar( sRuta );
	bPermiteInsercion = _bPermiteInsercion;
}


ConjuntoValores::~ConjuntoValores ()
{
	bPermiteInsercion = true;
	LimpiarValores();
}

long ConjuntoValores::getHash () const
{
	long lHash = 0;
	for ( const auto & par : mapValores )
	{
		Valor * valor = par.second;
		lHash = lHash + valor->getHash();
	}
	return( lHash );
}

bool ConjuntoValores::EsValido () const
{
	bool bRes = true;
	for ( const auto & par : mapValores )
	{
		Valor * valor = par.second;
		bRes = bRes && valor->EsValido();
	}
	return( bRes );
}

int ConjuntoValores::NumValores () const
{
	return ( mapValores.size() );
}

Valor * ConjuntoValores::getValor ( const string & sAtributo )
{
	Valor * valor = NULL;
	map<string, Valor *>::iterator it = mapValores.find( sAtributo );
	if ( it != mapValores.end() )
	{
		valor = it->second;
	}
	return ( valor );
}

bool ConjuntoValores::ExisteValor ( const string & sAtributo )
{
	map<string, Valor *>::iterator it = mapValores.find( sAtributo );
	return ( it != mapValores.end() );
}


void ConjuntoValores::InsertarValor ( const string & sAtributo, Valor * valor )
{
	if ( ( valor != NULL ) && bPermiteInsercion && !ExisteValor( sAtributo ) )
	{
		mapValores[ sAtributo ] = valor;
	}
	else
	{
		// No se inserta: el objeto es propiedad del conjunto, hay que liberarlo
		// para no fugarlo (delete de NULL es inocuo).
		delete valor;
	}
}

void ConjuntoValores::InsertarValor ( const string & sAtributo, const string & _valor )
{
	InsertarValor( sAtributo, new Valor( _valor ) );
}

void ConjuntoValores::InsertarValor ( const string & sAtributo, const char * _valor )
{
	InsertarValor( sAtributo, new Valor( _valor ) );
}

void ConjuntoValores::InsertarValor ( const string & sAtributo, bool _valor )
{
	InsertarValor( sAtributo, new Valor( _valor ) );
}

void ConjuntoValores::InsertarValor ( const string & sAtributo, short _valor )
{
	InsertarValor( sAtributo, new Valor( _valor ) );
}

void ConjuntoValores::InsertarValor ( const string & sAtributo, int _valor )
{
	InsertarValor( sAtributo, new Valor( _valor ) );
}

void ConjuntoValores::InsertarValor ( const string & sAtributo, long _valor )
{
	InsertarValor( sAtributo, new Valor( _valor ) );
}

void ConjuntoValores::InsertarValor ( const string & sAtributo, long long _valor )
{
	InsertarValor( sAtributo, new Valor( _valor ) );
}

void ConjuntoValores::InsertarValor ( const string & sAtributo, unsigned short _valor )
{
	InsertarValor( sAtributo, new Valor( _valor ) );
}

void ConjuntoValores::InsertarValor ( const string & sAtributo, unsigned int _valor )
{
	InsertarValor( sAtributo, new Valor( _valor ) );
}

void ConjuntoValores::InsertarValor ( const string & sAtributo, unsigned long _valor )
{
	InsertarValor( sAtributo, new Valor( _valor ) );
}

void ConjuntoValores::InsertarValor ( const string & sAtributo, unsigned long long _valor )
{
	InsertarValor( sAtributo, new Valor( _valor ) );
}

void ConjuntoValores::InsertarValor ( const string & sAtributo, float _valor )
{
	InsertarValor( sAtributo, new Valor( _valor ) );
}

void ConjuntoValores::InsertarValor ( const string & sAtributo, double _valor )
{
	InsertarValor( sAtributo, new Valor( _valor ) );
}

void ConjuntoValores::InsertarValor ( const string & sAtributo, long double _valor )
{
	InsertarValor( sAtributo, new Valor( _valor ) );
}

void ConjuntoValores::InsertarValor ( const string & sAtributo, char _valor )
{
	InsertarValor( sAtributo, new Valor( _valor ) );
}

void ConjuntoValores::InsertarValor ( const string & sAtributo, unsigned char _valor )
{
	InsertarValor( sAtributo, new Valor( _valor ) );
}

void ConjuntoValores::EliminarValor ( const string & sAtributo )
{
	if ( bPermiteInsercion )
	{
		map<string, Valor *>::iterator it = mapValores.find( sAtributo );
		if ( it != mapValores.end() )
		{
			delete it->second;
			mapValores.erase( it );
		}
	}
}

void ConjuntoValores::LimpiarValores ()
{
	if ( bPermiteInsercion )
	{
		for ( const auto & par : mapValores )
		{
			Valor * valor = par.second;
			delete valor;
		}
		mapValores.clear();
	}
}


bool ConjuntoValores::Cargar( const string & sRuta )
{
	bool bRes = false;
	try
	{
		ifstream fichero ( sRuta, ios::in | ios::binary );
		if( fichero )
		{
			bRes = true;
			string sAtributo;
			string sValor;
			while ( fichero >> sAtributo >> sValor )
			{
				cout << "[" << sAtributo << "]=[" << sValor << "]" << endl;
				InsertarValor( sAtributo, sValor );
			}
		}
	}
	catch( exception & ex )
	{
		cerr << "Error cargando el fichero [" << sRuta << "]: " << ex.what() << endl;
		bRes = false;
	}
	return( bRes );
}

string ConjuntoValores::toString ()
{
	try
	{
		ostringstream conv;
		for ( const auto & par : mapValores )
		{
			Valor * valor = par.second;
			conv << valor->toString() << endl;
		}
		return ( conv.str() );
	}
	catch (...)
	{
		return ( string ( "[Object Error]" ) );
	}
}

 			}
		}
	}
}
