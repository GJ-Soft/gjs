#include "CommonTypesConfig.h"

#include "ListaValores.h"



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

ListaValores::ListaValores ()
{
	bPermiteInsercion = true;
}

ListaValores::ListaValores ( int _iTam, bool _bPermiteInsercion )
{
	bPermiteInsercion = _bPermiteInsercion;
	for ( int iVal = 0; iVal < _iTam; iVal = iVal + 1 )
	{
		vecValores.push_back( new Valor () );
	}
}

ListaValores::~ListaValores ()
{
	bPermiteInsercion = true;
	LimpiarValores();
}

long ListaValores::getHash () const
{
	long lHash = 0;
	for ( int iIndice = 0; iIndice < vecValores.size(); iIndice = iIndice + 1 )
	{
		lHash = lHash + vecValores[ iIndice ]->getHash();
	}
	return( lHash );
}

bool ListaValores::EsValida ()
{
	bool bRes = true;
	for ( Valor * valor : vecValores )
	{
		bRes = bRes && valor->EsValido();
	}
	return( bRes );
}

int ListaValores::NumValores () const
{
	return ( vecValores.size() );
}

Valor * ListaValores::getValor ( int iIndice )
{
	Valor * valor = NULL;
	if ( ( iIndice >= 0 ) && ( iIndice < vecValores.size() ) )
	{
		valor = vecValores[ iIndice ];
	}
	return ( valor );
}

void ListaValores::InsertarValor ( Valor * valor )
{
	if ( ( valor != NULL ) && bPermiteInsercion )
	{
		vecValores.push_back( valor );
	}
	else
	{
		// No se inserta: el objeto es propiedad de la lista, hay que liberarlo
		// para no fugarlo (delete de NULL es inocuo).
		delete valor;
	}
}

void ListaValores::InsertarValor ( const string & _valor )
{
	InsertarValor( new Valor( _valor ) );
}

void ListaValores::InsertarValor ( const char * _valor )
{
	InsertarValor( new Valor( _valor ) );
}

void ListaValores::InsertarValor ( bool _valor )
{
	InsertarValor( new Valor( _valor ) );
}

void ListaValores::InsertarValor ( short _valor )
{
	InsertarValor( new Valor( _valor ) );
}

void ListaValores::InsertarValor ( int _valor )
{
	InsertarValor( new Valor( _valor ) );
}

void ListaValores::InsertarValor ( long _valor )
{
	InsertarValor( new Valor( _valor ) );
}

void ListaValores::InsertarValor ( long long _valor )
{
	InsertarValor( new Valor( _valor ) );
}

void ListaValores::InsertarValor ( unsigned short _valor )
{
	InsertarValor( new Valor( _valor ) );
}

void ListaValores::InsertarValor ( unsigned int _valor )
{
	InsertarValor( new Valor( _valor ) );
}

void ListaValores::InsertarValor ( unsigned long _valor )
{
	InsertarValor( new Valor( _valor ) );
}

void ListaValores::InsertarValor ( unsigned long long _valor )
{
	InsertarValor( new Valor( _valor ) );
}

void ListaValores::InsertarValor ( float _valor )
{
	InsertarValor( new Valor( _valor ) );
}

void ListaValores::InsertarValor ( double _valor )
{
	InsertarValor( new Valor( _valor ) );
}

void ListaValores::InsertarValor ( long double _valor )
{
	InsertarValor( new Valor( _valor ) );
}

void ListaValores::InsertarValor ( char _valor )
{
	InsertarValor( new Valor( _valor ) );
}

void ListaValores::InsertarValor ( unsigned char _valor )
{
	InsertarValor( new Valor( _valor ) );
}

void ListaValores::EliminarValor ( int iIndice )
{
	if ( ( iIndice >= 0 ) && ( iIndice < vecValores.size() ) && bPermiteInsercion )
	{
		delete vecValores[ iIndice ];
		vecValores.erase( vecValores.begin() + iIndice );
	}
}

void ListaValores::LimpiarValores ()
{
	if ( bPermiteInsercion )
	{
		for ( Valor * valor : vecValores )
		{
			delete valor;
		}
		vecValores.clear();
	}
}

string ListaValores::toString ()
{
	try
	{
		ostringstream conv;
		for ( Valor * valor : vecValores )
		{
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
