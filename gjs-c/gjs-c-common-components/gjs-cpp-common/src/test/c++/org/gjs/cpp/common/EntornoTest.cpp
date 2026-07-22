#include "CppCommon.h"
#include <CppEntorno.h>

#include <iostream>

using namespace std;
using namespace org::gjs::cpp::common;




static bool TestEntorno01 ()
{
	cout << "Test Entorno 01:" << endl;
	bool bRes = true;

	try
	{
		/* Sin llamar a EntInicializar, el entorno no esta inicializado.
		   No se prueba EntInicializar/EntFinalizar por ser pesados y con
		   efectos globales sobre el proceso. */
		if ( EntEstaInicializado () )
		{
			cout << "Error caso 1: el entorno no deberia estar inicializado" << endl;
			bRes = false;
		}

		/* Establecer y leer los directorios del entorno (dentro de target) */
		SisCrearDirectorio ( "../results" );
		string sDirDatos = "../results/ent-datos";
		string sDirSeguridad = "../results/ent-seguridad";
		string sDirLog = "../results/ent-log";

		EntEstablecerDirectorioDatos ( sDirDatos );
		EntEstablecerDirectorioSeguridad ( sDirSeguridad );
		EntEstablecerDirectorioLog ( sDirLog );

		if ( ( EntDirectorioDatos () == NULL ) ||
			 ( EntDirectorioSeguridad () == NULL ) ||
			 ( EntDirectorioLog () == NULL ) )
		{
			cout << "Error caso 2: algun directorio del entorno es NULL tras establecerlo" << endl;
			bRes = false;
		}
		else if ( ( EntDirectorioDatos ()->compare ( sDirDatos ) != 0 ) ||
				  ( EntDirectorioSeguridad ()->compare ( sDirSeguridad ) != 0 ) ||
				  ( EntDirectorioLog ()->compare ( sDirLog ) != 0 ) )
		{
			cout << "Error caso 3: los directorios del entorno no son los establecidos" << endl;
			bRes = false;
		}

		/* Con creacion por defecto (bCrear=true) los directorios existen en disco */
		if ( !SisExisteDirectorio ( sDirDatos ) ||
			 !SisExisteDirectorio ( sDirSeguridad ) ||
			 !SisExisteDirectorio ( sDirLog ) )
		{
			cout << "Error caso 4: los directorios del entorno no se crearon" << endl;
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


bool TestEntorno ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test Entorno]" << ANSI::RESETEAR << endl;
	if ( TestEntorno01() )
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
