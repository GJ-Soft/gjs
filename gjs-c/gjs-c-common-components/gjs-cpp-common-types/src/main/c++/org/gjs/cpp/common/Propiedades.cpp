#include "CommonTypesConfig.h"
#include "Propiedades.h"
#include <Cadenas.h>
#include <Concatenar.h>

using namespace std;

namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

Propiedades::Propiedades()
{
}

Propiedades::Propiedades( const string & sRuta )
{
	Cargar( sRuta );
}

Propiedades::~Propiedades()
{
}

string Propiedades::getPropiedad( const string & sClave ) const
{
    if ( mapPropiedades.find( sClave ) == mapPropiedades.end() )
	{
        throw NoEncontradoExcepcion( "Propiedades", "getPropiedad", "propiedad", sClave );
    }
    return ( mapPropiedades.at( sClave ) );
}

string Propiedades::getPropiedad( const string & sClave, const string & sValorDef ) const
{
    if ( mapPropiedades.find( sClave ) == mapPropiedades.end() )
	{
        return ( sValorDef );
    }
    return ( mapPropiedades.at( sClave ) );
}

vector<string> Propiedades::getPropiedades() const
{
    return ( vecClaves );
}

bool Propiedades::ExistePropiedad( const string & sClave ) const
{
	return ( mapPropiedades.contains( sClave ) );
}

int Propiedades::NumPropiedades() const
{
    return ( vecClaves.size() );
}

void Propiedades::setPropiedad( const string & sClave, const string & sValor )
{
    if ( mapPropiedades.find( sClave ) == mapPropiedades.end() )
	{
        vecClaves.push_back( sClave );
    }
    mapPropiedades[ sClave ] = sValor;
}

void Propiedades::EliminarPropiedad( const string & sClave )
{
    if ( mapPropiedades.find( sClave ) != mapPropiedades.end() )
	{
		vecClaves.erase( remove( vecClaves.begin(), vecClaves.end(), sClave ), vecClaves.end() );
		mapPropiedades.erase( sClave );
	}
}


bool Propiedades::EsPropiedad( const string & sLinea )
{
    string sAjustado = LTrim( sLinea );
    string::size_type pos = sAjustado.find_first_of( "=" );
    return ( ( pos != string::npos ) && ( pos > 0 ) );
}

pair<string, string> Propiedades::ParsearPropiedad( const string & sLinea )
{
    string sAjustado = LTrim( sLinea );
    string::size_type pos = sAjustado.find_first_of( "=" );
    string sClave = Trim( sAjustado.substr( 0, pos ) );
    string sValor = Trim( sAjustado.substr( pos + 1 ) );
	if ( EmpiezaPor( sValor, "\"" ) && TerminaPor( sValor, "\"" ) )
	{
		sValor = sValor.substr( 1, sValor.size() - 2 );
	}
    return std::pair<std::string, std::string>( sClave, sValor );
}

bool Propiedades::Cargar( const string & sRuta )
{
	bool bRes = false;
    ifstream is;
    is.open( sRuta.c_str() );
    if ( is.is_open() )
	{
		try
		{
			size_t numLinea = 0;
			string sLinea;
			bRes = true;
			while ( getline( is, sLinea ) )
			{
				sLinea = Limpiar( sLinea );
				if ( EsPropiedad( sLinea ) )
				{
					pair<string, string> propiedad = ParsearPropiedad( sLinea );
					setPropiedad( propiedad.first, propiedad.second );
				}
				else
				{
					bRes = false;
					cerr << "Propiedades::Cargar(" << sRuta << "): Linea erronea " << numLinea << ": " << sLinea << endl;
				}
				numLinea = numLinea + 1;
			}
		}
		catch (...)
		{
		}
		if ( is.is_open() )
		{
			is.close();
		}
	}
	return ( bRes );
}

bool Propiedades::Guardar( const string & sRuta )
{
 	bool bRes = false;

    ofstream os;
    os.open( sRuta.c_str() );
    if ( os.is_open() )
	{
		try
		{
			for (vector<string>::const_iterator it = vecClaves.begin(); it != vecClaves.end(); ++it )
			{
				string sValor = mapPropiedades[ *it ];
				if ( TieneEspacios( sValor ) )
				{
					sValor = Concatenar( "\"", sValor,"\"" );
				}
				os << *it << " = " << sValor << endl;
			}
			bRes = true;
		}
		catch (...)
		{
		}
		if ( os.is_open() )
		{
			os.close();
		}
	}
	return ( bRes );
}

 			}
		}
	}
}

