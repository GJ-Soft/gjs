#include "CppCommon.h"

#include <iostream>
#include <fstream>

using namespace std;
using namespace org::gjs::cpp::common;




static bool TestMensajes01 ()
{
	cout << "Test Mensajes 01:" << endl;
	bool bRes = true;

	try
	{
		Mensajes mensajes;

		if ( mensajes.NumMensajes () != 0 )
		{
			cout << "Error caso 1: los mensajes recien creados no estan vacios" << endl;
			bRes = false;
		}

		/* Insercion valida */
		if ( !mensajes.Insertar ( 1, "Hola" ) ||
			 !mensajes.Insertar ( 2, "Adios" ) ||
			 ( mensajes.NumMensajes () != 2 ) )
		{
			cout << "Error caso 2: no se insertaron los mensajes validos" << endl;
			bRes = false;
		}

		/* Inserciones invalidas: codigo negativo y texto vacio */
		if ( mensajes.Insertar ( -1, "Malo" ) ||
			 mensajes.Insertar ( 3, "" ) ||
			 ( mensajes.NumMensajes () != 2 ) )
		{
			cout << "Error caso 3: se admitio una insercion invalida" << endl;
			bRes = false;
		}

		/* Consultas */
		if ( !mensajes.ExisteCodigo ( 1 ) ||
			 mensajes.ExisteCodigo ( 99 ) ||
			 ( mensajes.Texto ( 1 ).compare ( "Hola" ) != 0 ) ||
			 ( mensajes[ 2 ].compare ( "Adios" ) != 0 ) )
		{
			cout << "Error caso 4: las consultas no devuelven lo esperado" << endl;
			bRes = false;
		}

		/* Codigo inexistente devuelve cadena vacia */
		if ( !mensajes.Texto ( 99 ).empty () ||
			 !mensajes[ 99 ].empty () )
		{
			cout << "Error caso 5: un codigo inexistente deberia devolver cadena vacia" << endl;
			bRes = false;
		}

		/* Reinsertar sobre un codigo existente sustituye el texto */
		if ( !mensajes.Insertar ( 1, "Hola de nuevo" ) ||
			 ( mensajes.NumMensajes () != 2 ) ||
			 ( mensajes.Texto ( 1 ).compare ( "Hola de nuevo" ) != 0 ) )
		{
			cout << "Error caso 6: reinsertar no sustituyo el texto" << endl;
			bRes = false;
		}

		/* Limpiar */
		mensajes.Limpiar ();
		if ( ( mensajes.NumMensajes () != 0 ) ||
			 mensajes.ExisteCodigo ( 1 ) )
		{
			cout << "Error caso 7: Limpiar no vacio los mensajes" << endl;
			bRes = false;
		}
	}
	catch ( exception & ex )
	{
		cout << "Se ha producido una excepcion :" << ex.what () << endl;
		bRes = false;
	}
	catch ( ... )
	{
		cout << "Excepcion indefinida" << endl;
		bRes = false;
	}
	return ( bRes );
}


static bool TestMensajes02 ()
{
	cout << "Test Mensajes 02:" << endl;
	bool bRes = true;

	try
	{
		SisCrearDirectorio ( "../results" );
		string sFichero = "../results/mensajes-test.txt";

		ofstream fichero ( sFichero );
		if ( !fichero.is_open () )
		{
			cout << "Error caso 0: no se pudo crear el fichero de prueba" << endl;
			bRes = false;
		}
		else
		{
			fichero << "1,Hola" << endl;
			fichero << "2,Mundo cruel" << endl;
			fichero << "noentero,se ignora" << endl;
			fichero.close ();

			Mensajes mensajes;
			bool bCarga = mensajes.Cargar ( sFichero );

			/* Cargar debe indicar exito al abrir y procesar el fichero */
			if ( !bCarga )
			{
				cout << "Error caso 1: Cargar devolvio false con un fichero valido" << endl;
				bRes = false;
			}
			/* Se cargan las 2 lineas con codigo entero; la de codigo no entero se descarta */
			if ( mensajes.NumMensajes () != 2 )
			{
				cout << "Error caso 2: se esperaban 2 mensajes cargados: " << mensajes.NumMensajes () << endl;
				bRes = false;
			}
			/* El separador (coma) y los espacios internos del mensaje se conservan */
			if ( ( mensajes.Texto ( 1 ).compare ( "Hola" ) != 0 ) ||
				 ( mensajes.Texto ( 2 ).compare ( "Mundo cruel" ) != 0 ) )
			{
				cout << "Error caso 3: los textos cargados no son los esperados: [" << mensajes.Texto ( 1 )
					<< "] [" << mensajes.Texto ( 2 ) << "]" << endl;
				bRes = false;
			}
		}

		/* Fichero inexistente: Cargar devuelve false y no carga nada */
		Mensajes mensajesVacio;
		if ( mensajesVacio.Cargar ( "../results/no-existe-este-fichero.txt" ) ||
			 ( mensajesVacio.NumMensajes () != 0 ) )
		{
			cout << "Error caso 4: Cargar de un fichero inexistente deberia devolver false y no cargar" << endl;
			bRes = false;
		}
	}
	catch ( exception & ex )
	{
		cout << "Se ha producido una excepcion :" << ex.what () << endl;
		bRes = false;
	}
	catch ( ... )
	{
		cout << "Excepcion indefinida" << endl;
		bRes = false;
	}
	return ( bRes );
}


bool TestMensajes ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test Mensajes]" << ANSI::RESETEAR << endl;
	if ( TestMensajes01() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestMensajes02() )
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
