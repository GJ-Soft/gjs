#include "CppBase.h"


#include <iostream>



using namespace std;
using namespace org::gjs::cpp::common;




static bool TestExpresionesRegulares01 ()
{
	cout << "Test ExpresionesRegulares01:" << endl;
	bool bRes = true;

	// Coincidencia literal (sin comodines).
	if ( ! CumpleExpresionRegular ( "hola", "hola" ) )
	{
		cout << "Error caso 1" << endl;
		bRes = false;
	}
	if ( CumpleExpresionRegular ( "adios", "hola" ) )
	{
		cout << "Error caso 2" << endl;
		bRes = false;
	}
	// regex_match exige coincidencia total: un prefijo no basta.
	if ( CumpleExpresionRegular ( "holamundo", "hola" ) )
	{
		cout << "Error caso 3" << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestExpresionesRegulares02 ()
{
	cout << "Test ExpresionesRegulares02:" << endl;
	bool bRes = true;

	// El comodin '?' representa un unico caracter cualquiera.
	if ( ! CumpleExpresionRegular ( "hola", "h?la" ) )
	{
		cout << "Error caso 1" << endl;
		bRes = false;
	}
	if ( ! CumpleExpresionRegular ( "hxla", "h?la" ) )
	{
		cout << "Error caso 2" << endl;
		bRes = false;
	}
	// '?' exige que exista el caracter: 'hla' tiene una letra de menos.
	if ( CumpleExpresionRegular ( "hla", "h?la" ) )
	{
		cout << "Error caso 3" << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestExpresionesRegulares03 ()
{
	cout << "Test ExpresionesRegulares03:" << endl;
	bool bRes = true;

	// El comodin '*' representa cualquier numero de caracteres (incluido ninguno).
	if ( ! CumpleExpresionRegular ( "holamundo", "hola*" ) )
	{
		cout << "Error caso 1" << endl;
		bRes = false;
	}
	if ( ! CumpleExpresionRegular ( "hola", "hola*" ) )
	{
		cout << "Error caso 2" << endl;
		bRes = false;
	}
	if ( CumpleExpresionRegular ( "adios", "hola*" ) )
	{
		cout << "Error caso 3" << endl;
		bRes = false;
	}
	if ( ! CumpleExpresionRegular ( "archivo.txt", "*.txt" ) )
	{
		cout << "Error caso 4" << endl;
		bRes = false;
	}
	if ( CumpleExpresionRegular ( "archivo.doc", "*.txt" ) )
	{
		cout << "Error caso 5" << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestExpresionesRegulares04 ()
{
	cout << "Test ExpresionesRegulares04:" << endl;
	bool bRes = true;

	// El '.' del patron es LITERAL ( metacaracter escapado ): 'archivoXtxt' no
	// casa con '*.txt' aunque tenga la misma longitud que 'archivo.txt'.
	if ( CumpleExpresionRegular ( "archivoXtxt", "*.txt" ) )
	{
		cout << "Error caso 1: el punto del patron deberia ser literal" << endl;
		bRes = false;
	}
	// '?*' exige al menos un caracter ( no equivale a '*' ).
	if ( ! CumpleExpresionRegular ( "x", "?*" ) )
	{
		cout << "Error caso 2: '?*' deberia aceptar un caracter" << endl;
		bRes = false;
	}
	if ( CumpleExpresionRegular ( "", "?*" ) )
	{
		cout << "Error caso 3: '?*' no deberia aceptar la cadena vacia" << endl;
		bRes = false;
	}
	// Patron de fichero 'nombre.ext': exige el punto literal.
	if ( ! CumpleExpresionRegular ( "datos.txt", "?*.?*" ) )
	{
		cout << "Error caso 4: 'datos.txt' deberia casar con '?*.?*'" << endl;
		bRes = false;
	}
	if ( CumpleExpresionRegular ( "sinextension", "?*.?*" ) )
	{
		cout << "Error caso 5: 'sinextension' no deberia casar con '?*.?*'" << endl;
		bRes = false;
	}
	// Los parentesis son grupo OPCIONAL: '/(?*/)(?*)' casa rutas unix absolutas.
	if ( ! CumpleExpresionRegular ( "/home/gjs", "/(?*/)(?*)" ) )
	{
		cout << "Error caso 6: '/home/gjs' deberia casar con '/(?*/)(?*)'" << endl;
		bRes = false;
	}
	if ( ! CumpleExpresionRegular ( "/", "/(?*/)(?*)" ) )
	{
		cout << "Error caso 7: '/' deberia casar ( grupos opcionales vacios )" << endl;
		bRes = false;
	}
	if ( CumpleExpresionRegular ( "home/gjs", "/(?*/)(?*)" ) )
	{
		cout << "Error caso 8: 'home/gjs' no deberia casar ( falta la barra inicial )" << endl;
		bRes = false;
	}
	return ( bRes );
}

bool TestExpresionesRegulares ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test ExpresionesRegulares]" << ANSI::RESETEAR << endl;
	if ( TestExpresionesRegulares01() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestExpresionesRegulares02() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestExpresionesRegulares03() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestExpresionesRegulares04() )
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
