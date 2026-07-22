#include "CommonTypesConfig.h"

#include "FicheroFormateado.h"
#include <Cadenas.h>
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

FicheroFormateado::FicheroFormateado ( const initializer_list<string> & delimitadores )
{
	lisSeparadores.insert( lisSeparadores.begin(), delimitadores );
}

FicheroFormateado::~FicheroFormateado ()
{
	Vaciar();
}

string FicheroFormateado::getRuta() const
{
	return( sFichero );
}

int FicheroFormateado::NumLineas () const
{
	int iRes = 0;
	if ( bCargado )
	{
		iRes = vecContenido.size();
	}
	return ( iRes );
}

vector<string> & FicheroFormateado::Linea( int iLinea )
{
	if ( !bCargado )
	{
		throw Excepcion( "FicheroFormateado", "Linea", "Fichero no cargado en memoria" );
	}
	if ( ( iLinea < 0 ) ||( iLinea >= vecContenido.size() ) )
	{
		throw Excepcion( "FicheroFormateado", "Linea", "Indice fuera de rango" );
	}
	return( vecContenido[ iLinea ] );
}

int FicheroFormateado::NumCamposLinea( int iLinea ) const
{
	if ( !bCargado )
	{
		throw Excepcion( "FicheroFormateado", "Linea", "Fichero no cargado en memoria" );
	}
	if ( ( iLinea < 0 ) ||( iLinea >= vecContenido.size() ) )
	{
		throw Excepcion( "FicheroFormateado", "Linea", "Linea fuera de rango" );
	}
	return( vecContenido[ iLinea ].size() );
}

string FicheroFormateado::Campo( int iLinea, int iCampo )
{
	if ( !bCargado )
	{
		throw Excepcion( "FicheroFormateado", "Linea", "Fichero no cargado en memoria" );
	}
	if ( ( iLinea < 0 ) || ( iLinea >= vecContenido.size() ) )
	{
		throw Excepcion( "FicheroFormateado", "Linea", "Linea fuera de rango" );
	}
	vector<string> vecLinea = vecContenido[ iLinea ];
	if ( ( iCampo < 0 ) || ( iCampo >= vecLinea.size() ) )
	{
		throw Excepcion( "FicheroFormateado", "Linea", "Campo fuera de rango" );
	}
	return( vecLinea[ iCampo ] );
}

void FicheroFormateado::Vaciar ()
{
	for ( vector<string> vecLinea : vecContenido )
	{
		vecLinea.clear();
	}
	vecContenido.clear();
}

bool FicheroFormateado::Cargar( const string & sRuta )
{
	bool bRes = false;
	ifstream fichero( sRuta, ios::in | ios::binary );
	try
	{
		if( fichero.is_open() )
		{
			fichero.clear();
			sFichero = sRuta;
			bRes = true;
			string sLinea;
			while ( getline( fichero, sLinea ) )
			{
				while ( !sLinea.empty() && ( ( sLinea[ sLinea.size() - 1 ] == '\n' ) || ( sLinea[ sLinea.size() - 1 ] == '\r' ) ) )
				{
					sLinea.erase( sLinea.size() - 1 );
				}
				if ( !sLinea.empty() )
				{
					vector<string> vecCampos = Separar( sLinea, lisSeparadores );
					vecContenido.push_back( vecCampos );
				}
			}
			bCargado = true;
		}
	}
	catch( exception & ex )
	{
		if( fichero.is_open() )
		{
			fichero.close();
		}
		throw Excepcion( "FicheroFormateado", "Cargar", Concatenar( "Error cargando el fichero [", sRuta, "]" ), ex );
	}
	if( fichero.is_open() )
	{
		fichero.close();
	}
	return( bRes );
}

 			}
		}
	}
}
