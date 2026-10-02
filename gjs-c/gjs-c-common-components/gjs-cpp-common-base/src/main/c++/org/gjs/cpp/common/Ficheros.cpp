#include "BaseConfig.h"
#include "Sistema.h"

#include "Excepcion.h"
#include "Concatenar.h"
#include "Colecciones.h"
#include "Cadenas.h"
#include <filesystem>

using namespace std;



namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

vector<string> LeerFichero ( const string & sRuta )
{
    vector<string> vecLineas;
	ifstream fic;

	try
	{
		fic.open ( sRuta );

		if ( fic.is_open () )
		{
			string sLinea ( "" );
			while ( ! fic.eof () )
			{
				getline ( fic, sLinea );
				if ( ! fic.bad () && ! fic.fail () )
				{
					sLinea = EliminarTodos( EliminarTodos( sLinea, '\r' ), '\b' );
					vecLineas.push_back( sLinea );
				}
			}
			fic.close ();
		}
		else
		{
			throw ( Excepcion ( "Ficheros", "LeerFichero", Concatenar ( "No se puede abrir el fichero: ", sRuta ) ) );
		}
	}
	catch ( const exception& ex )
	{
		if ( fic.is_open () )
		{
			fic.close ();
		}
		throw ( Excepcion ( "Ficheros", "LeerFichero", Concatenar ( "No se puede abrir el fichero: ", sRuta ), ex ) );
	}
	return ( vecLineas );
}

void GuardarFichero ( const string & sRuta, const vector<string> & vecLineas )
{
	ofstream fic;

	try
	{
		fic.open ( sRuta, ios_base::out | ios_base::trunc );

		if ( fic.is_open () )
		{
			for ( auto const& sLinea : vecLineas )
			{
				fic << sLinea << endl;
			}
			fic.flush ();
			fic.close ();
		}
		else
		{
			throw ( Excepcion ( "Ficheros", "GuardarFichero", "No se puede abrir el fichero: " + sRuta ) );
		}
	}
	catch ( const exception& ex )
	{
		if ( fic.is_open () )
		{
			fic.flush ();
			fic.close ();
		}
		throw ( Excepcion ( "Ficheros", "GuardarFichero", "Error al escribir en el fichero", ex ) );
	}
}

void GuardarFichero ( const string & sRuta, const string & sContenido )
{
	ofstream fic;

	try
	{
		fic.open ( sRuta, ios_base::out | ios_base::trunc );

		if ( fic.is_open () )
		{
			fic << sContenido << endl;
			fic.flush ();
			fic.close ();
		}
		else
		{
			throw ( Excepcion ( "Ficheros", "GuardarFichero", "No se puede abrir el fichero: " + sRuta ) );
		}
	}
	catch ( const exception& ex )
	{
		if ( fic.is_open () )
		{
			fic.flush ();
			fic.close ();
		}
		throw ( Excepcion ( "Ficheros", "GuardarFichero", "Error al escribir en el fichero", ex ) );
	}
}

void ImprimirFichero ( const string & sRuta )
{
	ifstream fic;
	try
	{
		fic.open ( sRuta );

		if ( fic.is_open () )
		{
			string sLinea;
			while ( ! fic.eof () )
			{
				getline ( fic, sLinea );
				if ( ! fic.bad () && ! fic.fail () )
				{
					cout << sLinea << endl;
				}
			}
			fic.close ();
		}
		else
		{
			throw ( Excepcion ( "Ficheros", "ImprimirFichero", Concatenar ( "No se puede abrir el fichero: ", sRuta ) ) );
		}
	}
	catch ( const exception& ex )
	{
		if ( fic.is_open () )
		{
			fic.close ();
		}
		throw ( Excepcion ( "Ficheros", "ImprimirFichero", "Error al leer el fichero", ex ) );
	}
}

void EliminarFichero ( const string & sRuta )
{
	try
	{
		filesystem::remove( sRuta );
	}
	catch( ... )
	{
	}
}

bool FicherosIguales ( const string & sRuta1, const string & sRuta2 )
{
	vector<string> vecContenido1 = LeerFichero ( sRuta1 );
	vector<string> vecContenido2 = LeerFichero ( sRuta2 );
	return ( SonIguales ( vecContenido1, vecContenido2 ) );
}


            }
		}
	}
}
