#include "Log.h"
#include "TestConfig.h"

#include <CppBase.h>
#include <CppCommonIo.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>



using namespace std;
using namespace org::gjs::cpp::common;
using namespace org::gjs::cpp::common::log;


/* Deja el log parado y sin appenders, para que cada caso empiece de cero. */
static void _Reiniciar ()
{
	LogFin ();
}

/* Escribe una linea de cada nivel. */
static void _AnotarDeTodo ()
{
	LogTraza ( "Mensaje de traza" );
	LogDepuracion ( "Mensaje de depuracion" );
	LogInfo ( "Mensaje de info" );
	LogAviso ( "Mensaje de aviso" );
	LogError ( "Mensaje de error" );
}

/* Ficheros que hay ahora mismo en el directorio de log. */
static vector<string> _FicherosDeLog ()
{
	vector<string> vecRes;

	/* El modulo de E/S no tiene listado de directorio, asi que se usa el
	   estandar. Solo ficheros: el directorio de log no tiene subcarpetas. */
	if ( SisExisteDirectorio ( FIC_TEST_DIR_LOG ) )
	{
		for ( const auto & entrada : filesystem::directory_iterator ( FIC_TEST_DIR_LOG ) )
		{
			if ( entrada.is_regular_file () )
			{
				vecRes.push_back ( entrada.path ().filename ().string () );
			}
		}
	}
	return ( vecRes );
}

/* Cierto si algun fichero del directorio de log contiene el texto. */
static bool _AlgunFicheroContiene ( const string & sTexto )
{
	bool bRes = false;

	for ( const string & sFichero : _FicherosDeLog () )
	{
		ifstream ifsFichero ( SisComponerRuta ( FIC_TEST_DIR_LOG, sFichero ) );
		string sLinea;
		while ( ( ! bRes ) && getline ( ifsFichero, sLinea ) )
		{
			bRes = ( sLinea.find ( sTexto ) != string::npos );
		}
	}
	return ( bRes );
}


/* Configuracion de solo consola: hay salida por consola y no se crea fichero. */
static bool TestLog01 ()
{
	cout << "Test Log 01 ( solo consola ):" << endl;
	bool bRes = true;

	_Reiniciar ();
	size_t uFicherosAntes = _FicherosDeLog ().size ();

	if ( ! LogIni ( string ( FIC_TEST_CFG_CONSOLA ) ) )
	{
		cout << "Error caso 1: no se pudo inicializar con " << FIC_TEST_CFG_CONSOLA << endl;
		return ( false );
	}
	if ( ! LogHaySalidaPorConsola () )
	{
		cout << "Error caso 2: se esperaba salida por consola" << endl;
		bRes = false;
	}
	LogActivar ();
	if ( ! LogActivado () )
	{
		cout << "Error caso 3: el log deberia estar activo" << endl;
		bRes = false;
	}
	_AnotarDeTodo ();
	if ( _FicherosDeLog ().size () != uFicherosAntes )
	{
		cout << "Error caso 4: no deberia haberse creado ningun fichero de log" << endl;
		bRes = false;
	}
	_Reiniciar ();
	return ( bRes );
}

/* Configuracion de solo fichero: se crea el fichero, lleva el mensaje, y no
   hay appender de consola. */
static bool TestLog02 ()
{
	cout << "Test Log 02 ( solo fichero ):" << endl;
	bool bRes = true;

	_Reiniciar ();
	if ( ! LogIni ( string ( FIC_TEST_CFG_FICHERO ) ) )
	{
		cout << "Error caso 1: no se pudo inicializar con " << FIC_TEST_CFG_FICHERO << endl;
		return ( false );
	}
	if ( LogHaySalidaPorConsola () )
	{
		cout << "Error caso 2: no se esperaba salida por consola" << endl;
		bRes = false;
	}
	LogActivar ();
	LogEstablecerNivel ( NivelLog::NIVEL_TODOS );

	string sMarca ( "Marca del caso 02" );
	LogInfo ( sMarca );

	if ( _FicherosDeLog ().empty () )
	{
		cout << "Error caso 3: se esperaba al menos un fichero en " << FIC_TEST_DIR_LOG << endl;
		bRes = false;
	}
	else if ( ! _AlgunFicheroContiene ( sMarca ) )
	{
		cout << "Error caso 4: el mensaje no aparece en ningun fichero de log" << endl;
		bRes = false;
	}
	_Reiniciar ();
	return ( bRes );
}

/* Configuracion completa: consola y fichero a la vez. */
static bool TestLog03 ()
{
	cout << "Test Log 03 ( consola y fichero ):" << endl;
	bool bRes = true;

	_Reiniciar ();
	if ( ! LogIni ( string ( FIC_TEST_CFG_COMPLETA ) ) )
	{
		cout << "Error caso 1: no se pudo inicializar con " << FIC_TEST_CFG_COMPLETA << endl;
		return ( false );
	}
	if ( ! LogHaySalidaPorConsola () )
	{
		cout << "Error caso 2: se esperaba salida por consola" << endl;
		bRes = false;
	}
	LogActivar ();
	LogEstablecerNivel ( NivelLog::NIVEL_TODOS );

	string sMarca ( "Marca del caso 03" );
	LogInfo ( sMarca );

	if ( ! _AlgunFicheroContiene ( sMarca ) )
	{
		cout << "Error caso 3: el mensaje no aparece en ningun fichero de log" << endl;
		bRes = false;
	}
	_Reiniciar ();
	return ( bRes );
}

/* El nivel filtra: con el umbral en ERROR no debe salir un info. */
static bool TestLog04 ()
{
	cout << "Test Log 04 ( filtro por nivel ):" << endl;
	bool bRes = true;

	_Reiniciar ();
	if ( ! LogIni ( string ( FIC_TEST_CFG_FICHERO ) ) )
	{
		cout << "Error caso 1: no se pudo inicializar" << endl;
		return ( false );
	}
	LogActivar ();

	LogEstablecerNivel ( NivelLog::NIVEL_ERROR );
	if ( LogNivel () != NivelLog::NIVEL_ERROR )
	{
		cout << "Error caso 2: el nivel no se guardo" << endl;
		bRes = false;
	}
	string sFiltrado ( "Este info no deberia salir, caso 04" );
	string sPasa ( "Este error si deberia salir, caso 04" );
	LogInfo ( sFiltrado );
	LogError ( sPasa );

	if ( _AlgunFicheroContiene ( sFiltrado ) )
	{
		cout << "Error caso 3: el info salio con el umbral en ERROR" << endl;
		bRes = false;
	}
	if ( ! _AlgunFicheroContiene ( sPasa ) )
	{
		cout << "Error caso 4: el error no salio con el umbral en ERROR" << endl;
		bRes = false;
	}
	_Reiniciar ();
	return ( bRes );
}

/* Desactivar corta la salida; reactivar la devuelve. */
static bool TestLog05 ()
{
	cout << "Test Log 05 ( activar y desactivar ):" << endl;
	bool bRes = true;

	_Reiniciar ();
	if ( ! LogIni ( string ( FIC_TEST_CFG_FICHERO ) ) )
	{
		cout << "Error caso 1: no se pudo inicializar" << endl;
		return ( false );
	}
	LogActivar ();
	LogEstablecerNivel ( NivelLog::NIVEL_TODOS );

	LogDesactivar ();
	if ( LogActivado () )
	{
		cout << "Error caso 2: el log deberia estar desactivado" << endl;
		bRes = false;
	}
	string sMudo ( "Con el log desactivado, caso 05" );
	LogInfo ( sMudo );
	if ( _AlgunFicheroContiene ( sMudo ) )
	{
		cout << "Error caso 3: se anoto con el log desactivado" << endl;
		bRes = false;
	}

	LogActivar ();
	string sAudible ( "Con el log reactivado, caso 05" );
	LogInfo ( sAudible );
	if ( ! _AlgunFicheroContiene ( sAudible ) )
	{
		cout << "Error caso 4: no se anoto tras reactivar" << endl;
		bRes = false;
	}
	_Reiniciar ();
	return ( bRes );
}

/* Casos limite: fichero de configuracion inexistente, y anotar sin inicializar. */
static bool TestLog06 ()
{
	cout << "Test Log 06 ( casos limite ):" << endl;
	bool bRes = true;

	_Reiniciar ();
	if ( LogIni ( string ( FIC_TEST_DIR_CONFIG "/no-existe.properties" ) ) )
	{
		cout << "Error caso 1: inicializar con un fichero inexistente deberia fallar" << endl;
		bRes = false;
	}
	_Reiniciar ();
	/* Sin inicializar no debe reventar, simplemente no hace nada. */
	LogInfo ( "Sin inicializar, caso 06" );
	if ( LogActivado () )
	{
		cout << "Error caso 2: sin inicializar no deberia estar activo" << endl;
		bRes = false;
	}
	if ( LogHaySalidaPorConsola () )
	{
		cout << "Error caso 3: sin inicializar no deberia haber consola" << endl;
		bRes = false;
	}
	return ( bRes );
}


bool TestLog ()
{
	bool bRes = true;

	cout << endl << ANSI::AMARILLO << "[Test Log]" << ANSI::RESETEAR << endl;
	if ( TestLog01 () && TestLog02 () && TestLog03 () &&
		 TestLog04 () && TestLog05 () && TestLog06 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	cout << ANSI::AMARILLO << "[Fin]" << ANSI::RESETEAR << endl;
	return ( bRes );
}
