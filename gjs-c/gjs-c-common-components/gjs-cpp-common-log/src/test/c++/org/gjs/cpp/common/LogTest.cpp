#include "Log.h"

#include <CppBase.h>

#include <iostream>
#include <filesystem>
#include <vector>



using namespace std;
using namespace org::gjs::cpp::common;
using namespace org::gjs::cpp::common::log;

/*
static const vector<string> vecResultados = {
				"] root INFO  - Mensaje de info",
				"] root DEBUG - Mensaje de depuracion",
				"] root TRACE - Mensaje de traza",
				"] root WARN  - Mensaje de aviso",
				"] root ERROR - Mensaje de error 1",
				"] root FATAL - Mensaje de error fatal 1",
				"] root ERROR - Mensaje de error 2: [Excepcion error 2]",
				"] root FATAL - Mensaje de error fatal 2: [Excepcion error fatal 2]",
				"] root ERROR - Excepcion error 3",
				"] root FATAL - Excepcion error fatal 3" };

bool ValidarLinea ( vector<string> vecLineas, int iLin, int iLinRes )
{
	bool bRes = true;
	if ( ! vecLineas[ iLin ].ends_with ( vecResultados [ iLinRes ] )  )
	{
		cout << "Error Caso 1: linea [" << iLin << "] incorrecto: [" << vecLineas[ iLin ] << "]" << endl;
		bRes = false;
	}
	return ( bRes );
}

*/

void LogCompletoParaTest ()
{
	LogInfo ( "Mensaje de info" );
	LogDepuracion ( "Mensaje de depuracion" );
	LogTraza ( "Mensaje de traza" );
	LogAviso ( "Mensaje de aviso" );
	LogError ( "Mensaje de error 1" );
	LogFatal ( "Mensaje de error fatal 1" );
	runtime_error ex1 ( "Excepcion error 2" );
	runtime_error ex2 ( "Excepcion error fatal 2" );
	LogErrorEx ( "Mensaje de error 2", ex1 );
	LogFatalEx ( "Mensaje de error fatal 2", ex2 );
	runtime_error ex3 ( "Excepcion error 3" );
	runtime_error ex4 ( "Excepcion error fatal 3" );
	LogError ( ex3 );
	LogFatal ( ex4 );
}

bool TestContenido ()
{
	bool bRes = true;

	try
	{
		// TODO: validar lo que sale por pantalla
		cout << ANSI::SUBRAYADO_INI << "Nivel maximo" << ANSI::SUBRAYADO_FIN << endl;
		//captor.Ini ();
		LogCompletoParaTest ();
		/*
		captor.Fin ();
		vector<string> vecLineas = captor.getLineas();
		if ( vecLineas.size () == 10 )
		{
			bRes = ValidarLinea ( vecLineas, 0, 0 ) &&
					ValidarLinea ( vecLineas, 1, 1 ) &&
					ValidarLinea ( vecLineas, 2, 2 ) &&
					ValidarLinea ( vecLineas, 3, 3 ) &&
					ValidarLinea ( vecLineas, 4, 4 ) &&
					ValidarLinea ( vecLineas, 5, 5 ) &&
					ValidarLinea ( vecLineas, 6, 6 ) &&
					ValidarLinea ( vecLineas, 7, 7 ) &&
					ValidarLinea ( vecLineas, 8, 8 ) &&
					ValidarLinea ( vecLineas, 9, 9 );
		}
		else
		{
			cout << "Error Caso 1: numero incorrecto de lineas impresas en log: " << vecLineas.size () << endl;
			bRes = false;
		}
		*/

		LogSetNivel ( Nivel::TRAZA );
		cout << ANSI::SUBRAYADO_INI << "Nivel traza" << ANSI::SUBRAYADO_FIN << endl;
		LogCompletoParaTest ();

		LogSetNivel ( Nivel::DEPUR );
		cout << ANSI::SUBRAYADO_INI << "Nivel depuracion" << ANSI::SUBRAYADO_FIN << endl;
		LogCompletoParaTest ();

		LogSetNivel ( Nivel::INFO );
		cout << ANSI::SUBRAYADO_INI << "Nivel informacion" << ANSI::SUBRAYADO_FIN << endl;
		LogCompletoParaTest ();

		LogSetNivel ( Nivel::AVISO );
		cout << ANSI::SUBRAYADO_INI << "Nivel aviso" << ANSI::SUBRAYADO_FIN << endl;
		LogCompletoParaTest ();

		LogSetNivel ( Nivel::ERROR );
		cout << ANSI::SUBRAYADO_INI << "Nivel error" << ANSI::SUBRAYADO_FIN << endl;
		LogCompletoParaTest ();

		LogSetNivel ( Nivel::FATAL );
		cout << ANSI::SUBRAYADO_INI << "Nivel error fatal" << ANSI::SUBRAYADO_FIN << endl;
		LogCompletoParaTest ();

		LogSetNivel ( Nivel::NINGUNO );
		cout << ANSI::SUBRAYADO_INI << "Nivel ninguno" << ANSI::SUBRAYADO_FIN << endl;
		LogCompletoParaTest ();

		cout << endl;
	}
	catch ( ... )
	{
		cout << "Error al finalizar la funcionalidad de log" << endl;
		bRes = false;
	}
	return ( bRes );
}

bool TestContenidoMinimo ()
{
	bool bRes = true;

	try
	{
		LogCompletoParaTest ();
		cout << endl;
	}
	catch ( ... )
	{
		cout << "Error al finalizar la funcionalidad de log" << endl;
		bRes = false;
	}
	return ( bRes );
}

bool TestLog01 ()
{
	cout << "Test Log01: Consola" << endl;
	bool bRes = true;
	try
	{
		if ( ! LogIniConsola () )
		{
			cout << "Funcionalidad de log no inicializada" << endl;
			bRes = false;
		}
		else
		{
			if ( ! LogIniConsola () )
			{
				cout << "La segunda inicializacion deberia no hacer nada y haber retornado cierto" << endl;
				bRes = false;
			}
		}
	}
	catch ( const exception & ex )
	{
		cout << "Error al inicializar la funcionalidad de log: " << ex.what () << endl;
		bRes = false;
	}

	if ( bRes )
	{
		cout << "Log inicializado" << endl << endl;
		bRes = TestContenido ();
	}

	try
	{
		LogFin ();
		// La segunda finalizacion no deberia hacer nada.
		LogFin ();
	}
	catch ( ... )
	{
		cout << "Error al finalizar la funcionalidad de log" << endl;
		bRes = false;
	}
	return( bRes );
}

bool TestLog02 ()
{
	cout << "Test Log02: Fichero" << endl;
	bool bRes = true;
	try
	{
		if ( ! LogIniFichero ( "TestLog02.log" ) )
		{
			cout << "Funcionalidad de log no inicializada" << endl;
			bRes = false;
		}
	}
	catch ( const exception & ex )
	{
		cout << "Error al inicializar la funcionalidad de log: " << ex.what () << endl;
		bRes = false;
	}

	if ( bRes )
	{
		cout << "Log inicializado" << endl << endl;
		bRes = TestContenido ();
		try
		{
			if ( ExisteFichero ( "TestLog02.log" ) )
			{
				cout << ANSI::SUBRAYADO_INI << "Contenido del fichero:" << ANSI::SUBRAYADO_FIN << endl;
				ImprimirFichero ( "TestLog02.log" );
				// TODO: Validar contenido del fichero
			}
			else
			{
				cout << "No se ha creado el fichero" << endl;
				bRes = false;
			}
		}
		catch ( const exception & ex )
		{
			cout << "Error al consultar el contenido del log: " << ex.what () << endl;
			bRes = false;
		}
	}

	try
	{
		LogFin ();
	}
	catch ( ... )
	{
		cout << "Error al finalizar la funcionalidad de log" << endl;
		bRes = false;
	}
	return( bRes );
}

bool TestLog03 ()
{
	cout << "Test Log03: Fichero+Consola" << endl;
	bool bRes = true;
	try
	{
		if ( ! LogIniFichero ( "TestLog03.log", true ) )
		{
			cout << "Funcionalidad de log no inicializada" << endl;
			bRes = false;
		}
	}
	catch ( const exception & ex )
	{
		cout << "Error al inicializar la funcionalidad de log: " << ex.what () << endl;
		bRes = false;
	}

	if ( bRes )
	{
		cout << "Log inicializado" << endl << endl;
		bRes = TestContenidoMinimo ();
		try
		{
			if ( ExisteFichero ( "TestLog03.log" ) )
			{
				cout << ANSI::SUBRAYADO_INI << "Contenido del fichero:" << ANSI::SUBRAYADO_FIN << endl;
				ImprimirFichero ( "TestLog03.log" );
			}
			else
			{
				cout << "No se ha creado el fichero" << endl;
				bRes = false;
			}
		}
		catch ( const exception & ex )
		{
			cout << "Error al consultar el contenido del log: " << ex.what () << endl;
			bRes = false;
		}
	}

	try
	{
		LogFin ();
	}
	catch ( ... )
	{
		cout << "Error al finalizar la funcionalidad de log" << endl;
		bRes = false;
	}
	return( bRes );
}

bool TestLog04 ()
{
	cout << "Test Log04: Mapa de propiedades" << endl;
	bool bRes = true;
	try
	{
		string sVarEntDir = VariableEntorno ( LOG_VAR_DIRECTORIO );
		if ( sVarEntDir.size () == 0 )
		{
			sVarEntDir = DirectorioActual();
		}
		map<string, string> mapPropiedades = LogPropiedadesDefecto ();
		string sFichero = mapPropiedades [ LOG_PROP_FICHERO ];
		string sDirectorio = mapPropiedades [ LOG_PROP_DIRECTORIO ];
		if ( sFichero != "log" )
		{
			cout << "Caso 1: Nombre de fichero erroneo: [" << sFichero << "]" << endl;
			bRes = false;
		}
		if ( sDirectorio != sVarEntDir )
		{
			cout << "Caso 1: Directorio erroneo: [" << sDirectorio << "]" << endl;
			bRes = false;
		}

		mapPropiedades = LogPropiedadesDefecto ( "TestLog04", "/tmp" );
		sFichero = mapPropiedades [ LOG_PROP_FICHERO ];
		sDirectorio = mapPropiedades [ LOG_PROP_DIRECTORIO ];
		if ( sFichero != "TestLog04" )
		{
			cout << "Caso 2: Nombre de fichero erroneo: [" << sFichero << "]" << endl;
			bRes = false;
		}
		if ( sDirectorio != "/tmp" )
		{
			cout << "Caso 2: Directorio erroneo: [" << sDirectorio << "]" << endl;
			bRes = false;
		}

	}
	catch ( const exception & ex )
	{
		cout << "Error al probar el mapa de propiedades: " << ex.what () << endl;
		bRes = false;
	}
	return ( bRes );
}

bool TestLog05 ()
{
	cout << "Test Log05: Configuracion por Fichero" << endl;
	bool bRes = true;
	try
	{
		// TODO: log4cxx coge las propiedades pero no las encuentra al realizar la sustitucion por un bug
		//map<string, string> mapPropiedades = LogPropiedadesDefecto ( "TestLog05" );
		map<string, string> mapPropiedades;
		if ( ! LogIni ( "../../test-classes/config/file-log.xml", mapPropiedades ) )
		{
			cout << "Funcionalidad de log no inicializada" << endl;
			bRes = false;
		}
	}
	catch ( const exception & ex )
	{
		cout << "Error al inicializar la funcionalidad de log: " << ex.what () << endl;
		bRes = false;
	}

	if ( bRes )
	{
		cout << "Log inicializado" << endl << endl;
		bRes = TestContenidoMinimo ();
		try
		{
			if ( ExisteFichero ( "./log/ejemplo.log" ) )
			{
				cout << ANSI::SUBRAYADO_INI << "Contenido del fichero:" << ANSI::SUBRAYADO_FIN << endl;
				ImprimirFichero ( "./log/ejemplo.log" );
			}
			else
			{
				cout << "No se ha creado el fichero" << endl;
				bRes = false;
			}
		}
		catch ( const exception & ex )
		{
			cout << "Error al consultar el contenido del log: " << ex.what () << endl;
			bRes = false;
		}
	}

	try
	{
		LogFin ();
	}
	catch ( ... )
	{
		cout << "Error al finalizar la funcionalidad de log" << endl;
		bRes = false;
	}
	return( bRes );
}


bool TestLog ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test Log]" << ANSI::RESETEAR << endl;
	if ( TestLog01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestLog02 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestLog03 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestLog04 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestLog05 () )
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
