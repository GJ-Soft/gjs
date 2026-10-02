#include "ToBool.h"
#include "ToString.h"

#include <CppBase.h>

#include <iostream>
#include <string>



using namespace std;
using namespace org::gjs::cpp::common;


static bool _Comprobar ( bool bObtenido, bool bEsperado, const string & sQue, int iCaso )
{
	if ( bObtenido != bEsperado )
	{
		cout << "Error caso " << iCaso << ": " << sQue << " dio "
			 << ( bObtenido ? "cierto" : "falso" ) << endl;
		return ( false );
	}
	return ( true );
}


/* Las palabras que se admiten como verdadero, sin distinguir mayusculas. */
static bool TestToBool01 ()
{
	cout << "Test ToBool 01 ( cadenas ):" << endl;
	bool bRes = true;

	bRes = _Comprobar ( ToBool ( "true" ), true, "\"true\"", 1 ) && bRes;
	bRes = _Comprobar ( ToBool ( "TRUE" ), true, "\"TRUE\"", 2 ) && bRes;
	bRes = _Comprobar ( ToBool ( "cierto" ), true, "\"cierto\"", 3 ) && bRes;
	bRes = _Comprobar ( ToBool ( "Cierto" ), true, "\"Cierto\"", 4 ) && bRes;
	bRes = _Comprobar ( ToBool ( "t" ), true, "\"t\"", 5 ) && bRes;
	bRes = _Comprobar ( ToBool ( "c" ), true, "\"c\"", 6 ) && bRes;
	bRes = _Comprobar ( ToBool ( "1" ), true, "\"1\"", 7 ) && bRes;

	bRes = _Comprobar ( ToBool ( "false" ), false, "\"false\"", 8 ) && bRes;
	bRes = _Comprobar ( ToBool ( "Falso" ), false, "\"Falso\"", 9 ) && bRes;
	bRes = _Comprobar ( ToBool ( "0" ), false, "\"0\"", 10 ) && bRes;
	bRes = _Comprobar ( ToBool ( "" ), false, "cadena vacia", 11 ) && bRes;
	bRes = _Comprobar ( ToBool ( "cualquier cosa" ), false, "texto no reconocido", 12 ) && bRes;
	/* Con comillas NO vale: en un fichero properties las comillas son parte
	   del valor, y este caso lo deja fijado. */
	bRes = _Comprobar ( ToBool ( "\"true\"" ), false, "\"true\" entrecomillado", 13 ) && bRes;

	return ( bRes );
}

/* Los numericos: falso es cero, verdadero todo lo demas. Y un entero suelto
   tiene que compilar, que antes era ambiguo entre double y float. */
static bool TestToBool02 ()
{
	cout << "Test ToBool 02 ( numericos ):" << endl;
	bool bRes = true;

	bRes = _Comprobar ( ToBool ( 1 ), true, "1", 1 ) && bRes;
	bRes = _Comprobar ( ToBool ( 0 ), false, "0", 2 ) && bRes;
	bRes = _Comprobar ( ToBool ( -1 ), true, "-1", 3 ) && bRes;
	bRes = _Comprobar ( ToBool ( 1.0 ), true, "1.0", 4 ) && bRes;
	bRes = _Comprobar ( ToBool ( 0.0 ), false, "0.0", 5 ) && bRes;
	bRes = _Comprobar ( ToBool ( -1.0 ), true, "-1.0", 6 ) && bRes;
	bRes = _Comprobar ( ToBool ( 1.0f ), true, "1.0f", 7 ) && bRes;
	bRes = _Comprobar ( ToBool ( 42L ), true, "42L", 8 ) && bRes;

	return ( bRes );
}

/* Punteros nulos y cadenas anchas. */
static bool TestToBool03 ()
{
	cout << "Test ToBool 03 ( punteros y anchas ):" << endl;
	bool bRes = true;

	const char *	p_cNulo = NULL;
	const wchar_t *	p_wcNulo = NULL;

	bRes = _Comprobar ( ToBool ( p_cNulo ), false, "const char * nulo", 1 ) && bRes;
	bRes = _Comprobar ( ToBool ( p_wcNulo ), false, "const wchar_t * nulo", 2 ) && bRes;
	bRes = _Comprobar ( ToBool ( L"true" ), true, "L\"true\"", 3 ) && bRes;
	bRes = _Comprobar ( ToBool ( L"no" ), false, "L\"no\"", 4 ) && bRes;

	return ( bRes );
}

/* Ida y vuelta con ToString. */
static bool TestToBool04 ()
{
	cout << "Test ToBool 04 ( ida y vuelta con ToString ):" << endl;
	bool bRes = true;

	bRes = _Comprobar ( ToBool ( ToString ( true ) ), true, "ToString ( true )", 1 ) && bRes;
	bRes = _Comprobar ( ToBool ( ToString ( false ) ), false, "ToString ( false )", 2 ) && bRes;

	return ( bRes );
}


bool TestToBool ()
{
	bool bRes = true;

	cout << endl << ANSI::AMARILLO << "[Test ToBool]" << ANSI::RESETEAR << endl;
	if ( TestToBool01 () && TestToBool02 () && TestToBool03 () && TestToBool04 () )
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
