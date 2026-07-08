#include "CppBase.h"

#include <iostream>



using namespace std;
using namespace org::gjs::cpp::common;


static bool TestLeerFichero01 ()
{
	cout << "Test LeerFichero01:" << endl;
	bool bRes = true;
	string sFic1 ( "../../test-classes/data/fichero-vacio.txt" );
	string sFic2 ( "../../test-classes/data/fichero-lineas.txt" );

	try
	{
		vector<string> vecContenido = LeerFichero ( sFic1 );
		if ( vecContenido.size() != 0 )
		{
			cout << "Error caso 1: el fichero vacio deberia tener cero lineas" << endl;
			bRes = false;
		}
	}
	catch ( const Excepcion & ex )
	{
		cout << "Error al leer el fichero [" << sFic1 << "]: " << ex.what () << endl;
		bRes = false;
	}
	catch ( ... )
	{
		cout << "Error al leer el fichero[" << sFic1 << "]"  << endl;
		bRes = false;
	}
	try
	{
		vector<string> vecContenido = LeerFichero ( sFic2 );
		cout << ANSI::SUBRAYADO_INI << "Contenido fichero:" << ANSI::SUBRAYADO_FIN << endl;
		for ( auto const& sLinea : vecContenido )
		{
			cout << sLinea << endl;
		}
		if ( vecContenido.size() != 6 )
		{
			cout << "Error caso 2: Numero de lineas erroneo: " << vecContenido.size() << endl;
			bRes = false;
		}
	}
	catch ( const Excepcion & ex )
	{
		cout << "Error al leer el fichero [" << sFic2 << "]: " << ex.what () << endl;
		bRes = false;
	}
	catch ( ... )
	{
		cout << "Error al leer el fichero[" << sFic2 << "]"  << endl;
		bRes = false;
	}
	return( bRes );
}

static bool TestImprimirFichero01 ()
{
	cout << "Test ImprimirFichero01:" << endl;
	bool bRes = true;
	string sFic ( "../../test-classes/data/fichero-lineas.txt" );

	try
	{
		cout << ANSI::SUBRAYADO_INI << "Contenido fichero:" << ANSI::SUBRAYADO_FIN << endl;
		ImprimirFichero ( sFic );
	}
	catch ( ... )
	{
		cout << "Error al leer el fichero" << endl;
		bRes = false;
	}
	return( bRes );
}

static bool ValidarFichero ( string sFic, vector<string> vecContenido )
{
	bool bRes = true;
	try
	{
		vector<string> lisRecuperado = LeerFichero ( sFic );;

		cout << ANSI::SUBRAYADO_INI << "Contenido fichero:" << ANSI::SUBRAYADO_FIN << endl;
		for ( auto const& sLinea : lisRecuperado )
		{
			cout << sLinea << endl;
		}
		if ( vecContenido.size() != lisRecuperado.size() )
		{
			cout << "Numero de lineas erroneo: " << lisRecuperado.size() << endl;
			bRes = false;
		}
		else if ( vecContenido.size() > 0 )
		{
			int iLinea = 1;
			vector<string>::iterator it1 = vecContenido.begin ();
			vector<string>::iterator it2 = lisRecuperado.begin ();
			do
			{
				if ( *it1 != *it2 )
				{
					cout << "Linea [" << iLinea << "] erronea: [" << *it1 << "] - [" << *it2 << "]" << endl;
					bRes = false;
				}
				it1++;
				it2++;
				iLinea++;
			}
			while ( it1 != vecContenido.end () );
		}
	}
	catch ( ... )
	{
		cout << "Error al leer el fichero" << endl;
		bRes = false;
	}
	return( bRes );
}

static bool TestGuardarFichero ( string sFic, vector<string> vecContenido )
{
	bool bRes = true;

	try
	{
		GuardarFichero ( sFic, vecContenido );
		cout << "Fichero guardado" << endl;
	}
	catch ( ... )
	{
		cout << "Error al escribir en el fichero" << endl;
		bRes = false;
	}

	if ( bRes )
	{
		bRes = ValidarFichero( sFic, vecContenido );
	}
	return( bRes );
}

static bool TestGuardarFichero01 ()
{
	cout << "Test GuardarFichero01:" << endl;
	string sFic ( "fichero-guardado-01.txt" );
	vector<string> vecContenido = {};
	return( TestGuardarFichero ( sFic, vecContenido ) );
}

static bool TestGuardarFichero02 ()
{
	cout << "Test GuardarFichero02:" << endl;
	string sFic ( "fichero-guardado-02.txt" );
	vector<string> vecContenido = { "Linea 1", "Linea 2", "", "Linea 4" };
	return( TestGuardarFichero ( sFic, vecContenido ) );
}

static bool TestGuardarFichero03 ()
{
	cout << "Test GuardarFichero03:" << endl;
	string sFic ( "fichero-guardado-03.txt" );
	vector<string> vecContenido = { "Linea 1", "Linea 2", "", "Linea 4", "" };
	bool bRes = true;
	try
	{
		GuardarFichero ( sFic, "Linea 1\nLinea 2\n\nLinea 4\n" );
		cout << "Fichero guardado" << endl;
	}
	catch ( ... )
	{
		cout << "Error al escribir en el fichero" << endl;
		bRes = false;
	}
	if ( bRes )
	{
		bRes = ValidarFichero ( sFic, vecContenido );
	}
	return( bRes );
}


static bool TestFicherosIguales01 ()
{
	bool bRes = true;
	cout << "Test FicherosIguales01:" << endl;
	string sFic1 ( "../../test-classes/data/fichero-ejemplo-1.txt" );
	string sFic2 ( "../../test-classes/data/fichero-ejemplo-2.txt" );
	string sFic3 ( "../../test-classes/data/fichero-ejemplo-3.txt" );
	string sFic4 ( "../../test-classes/data/fichero-vacio.txt" );
	string sFic5 ( "../../test-classes/data/fichero-vacio-copia.txt" );
	try
	{
		if ( !FicherosIguales ( sFic4, sFic5 ) )
		{
			cout << "Error caso 1: Ficheros vacios deben ser iguales" << endl;
			bRes = false;
		}
		if ( !FicherosIguales ( sFic1, sFic1 ) )
		{
			cout << "Error caso 2: Un fichero ha de ser igual a si mismo" << endl;
			bRes = false;
		}
		if ( FicherosIguales ( sFic1, sFic2 ) )
		{
			cout << "Error caso 3: Ficheros han de ser diferentes" << endl;
			bRes = false;
		}
		if ( FicherosIguales ( sFic1, sFic3 ) )
		{
			cout << "Error caso 4: Ficheros han de ser diferentes" << endl;
			bRes = false;
		}
		if ( FicherosIguales ( sFic1, sFic4 ) )
		{
			cout << "Error caso 5: Ficheros han de ser diferentes" << endl;
			bRes = false;
		}
	}
	catch ( const Excepcion & ex )
	{
		cout << "Error al comparar los ficheros fichero: " << ex.what () << endl;
		bRes = false;
	}
	catch ( ... )
	{
		cout << "Error al comparar los ficheros fichero" << endl;
		bRes = false;
	}
	return( bRes );
}

static bool TestEliminarFichero01 ()
{
	cout << "Test EliminarFichero01:" << endl;
	bool bRes = true;
	string sFic1 ( "../../test-classes/data/fichero-eliminar.txt" );
	string sFic2 ( "../../test-classes/data/fichero-noexiste.txt" );

	try
	{
		EliminarFichero ( sFic1 );
		if ( ExisteFichero( sFic1 ) )
		{
			cout << "Error caso 1: el fichero no se ha eliminado" << endl;
			bRes = false;
		}
		EliminarFichero ( sFic2 );
	}
	catch ( const Excepcion & ex )
	{
		cout << "Error inesperado al eliminar un fichero: " << ex.what () << endl;
		bRes = false;
	}
	catch ( ... )
	{
		cout << "Error inesperado al eliminar un fichero: "  << endl;
		bRes = false;
	}
	return( bRes );
}


bool TestFicheros ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test Ficheros]" << ANSI::RESETEAR << endl;
	if ( TestLeerFichero01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestImprimirFichero01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestGuardarFichero01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestGuardarFichero02 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestGuardarFichero03 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestFicherosIguales01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestEliminarFichero01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	cout << ANSI::AMARILLO << "[Fin]" << ANSI::RESETEAR << endl;
	return ( bRes );
}
