#include "Configuracion.h"
#include "ESExcepcion.h"

#include <CppBase.h>

#include <iostream>
#include <map>
#include <string>



using namespace std;
using namespace org::gjs::cpp::common;
using namespace org::gjs::cpp::common::config;


/* El test corre con el directorio de trabajo en target/test-nar/test-reports,
   asi que ".." es donde el build deja los recursos de src/test/resources. El
   subdirectorio data se copia SIN filtrar, que es lo que interesa aqui: el
   fichero lleva escapes y no queremos que Maven toque nada. */
#define FIC_TEST_DIR_DATA			"../data"
#define FIC_TEST_PROPIEDADES		FIC_TEST_DIR_DATA "/prueba.properties"
#define FIC_TEST_INEXISTENTE		FIC_TEST_DIR_DATA "/no-existe.properties"


static bool _Comprobar ( map<string, string> & mapProp, const string & sClave,
						 const string & sEsperado, int iCaso )
{
	map<string, string>::const_iterator itDato = mapProp.find ( sClave );
	string sObtenido = ( itDato != mapProp.end () ) ? itDato->second : string ( "<AUSENTE>" );

	if ( sObtenido != sEsperado )
	{
		cout << "Error caso " << iCaso << ": [" << sClave << "] = [" << sObtenido
			 << "], se esperaba [" << sEsperado << "]" << endl;
		return ( false );
	}
	return ( true );
}


/* Las reglas del formato properties de Java, una por caso. */
static bool TestConfiguracion01 ()
{
	cout << "Test Configuracion 01 ( formato properties ):" << endl;
	bool bRes = true;

	try
	{
		map<string, string> mapProp = LeerPropiedades ( FIC_TEST_PROPIEDADES );

		bRes = _Comprobar ( mapProp, "nombre", "aplicacion", 1 ) && bRes;
		bRes = _Comprobar ( mapProp, "version", "3.2.1", 2 ) && bRes;
		bRes = _Comprobar ( mapProp, "autor", "gjs", 3 ) && bRes;
		bRes = _Comprobar ( mapProp, "puerto", "8080", 4 ) && bRes;
		bRes = _Comprobar ( mapProp, "sinvalor", "", 5 ) && bRes;
		bRes = _Comprobar ( mapProp, "conIgual", "a=b=c", 6 ) && bRes;
		bRes = _Comprobar ( mapProp, "ruta", "C:\\temp\\log", 7 ) && bRes;
		bRes = _Comprobar ( mapProp, "espacios", "con blancos al final", 8 ) && bRes;
		bRes = _Comprobar ( mapProp, "clave con blanco", "valor", 9 ) && bRes;
		bRes = _Comprobar ( mapProp, "tabulador", "uno\tdos", 10 ) && bRes;
		bRes = _Comprobar ( mapProp, "saltoLinea", "uno\ndos", 11 ) && bRes;
		bRes = _Comprobar ( mapProp, "larga",
							"primera parte, segunda parte, tercera parte", 12 ) && bRes;
		/* El fichero esta en UTF-8 y se lee tal cual, byte a byte. */
		bRes = _Comprobar ( mapProp, "acentos", "caf\xc3\xa9 y a\xc3\xb1o", 13 ) && bRes;
		/* Una secuencia unicode mal formada deja la 'u', como hace Java. */
		bRes = _Comprobar ( mapProp, "malformado", "uZZZZ", 14 ) && bRes;

		if ( mapProp.size () != 14 )
		{
			cout << "Error caso 15: se esperaban 14 propiedades, hay " << mapProp.size () << endl;
			bRes = false;
		}
	}
	catch ( const exception & ex )
	{
		cout << "Error caso 0: excepcion inesperada: " << ex.what () << endl;
		bRes = false;
	}
	return ( bRes );
}

/* Un fichero que no existe tiene que lanzar ESExcepcion, no devolver un mapa
   vacio en silencio. */
static bool TestConfiguracion02 ()
{
	cout << "Test Configuracion 02 ( fichero inexistente ):" << endl;
	bool bRes = false;

	try
	{
		map<string, string> mapProp = LeerPropiedades ( FIC_TEST_INEXISTENTE );
		cout << "Error caso 1: se esperaba excepcion, y devolvio "
			 << mapProp.size () << " propiedades" << endl;
	}
	catch ( const ESExcepcion & ex )
	{
		bRes = true;
	}
	catch ( const exception & ex )
	{
		cout << "Error caso 2: se esperaba ESExcepcion, llego otra: " << ex.what () << endl;
	}
	return ( bRes );
}


bool TestConfiguracion ()
{
	bool bRes = true;

	cout << endl << ANSI::AMARILLO << "[Test Configuracion]" << ANSI::RESETEAR << endl;
	if ( TestConfiguracion01 () && TestConfiguracion02 () )
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
