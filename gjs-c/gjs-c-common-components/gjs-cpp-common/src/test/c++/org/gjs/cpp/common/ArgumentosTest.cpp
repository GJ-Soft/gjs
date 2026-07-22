#include "CppCommon.h"

#include <iostream>

using namespace std;
using namespace org::gjs::cpp::common;




static bool TestArgumentos01 ()
{
	cout << "Test Argumentos 01:" << endl;
	bool bRes = true;

	try
	{
		char a0[] = "programa";
		char a1[] = "hola";
		char a2[] = "42";
		char a3[] = "-3.5";
		char * p_p_cArg[] = { a0, a1, a2, a3 };
		Argumentos argumentos ( 4, p_p_cArg );

		/* Se descarta el nombre del programa: quedan 3 argumentos utiles */
		if ( argumentos.NumArgumentos () != 3 )
		{
			cout << "Error caso 1: se esperaban 3 argumentos: " << argumentos.NumArgumentos () << endl;
			bRes = false;
		}
		if ( ( argumentos.Argumento ( 0 ).compare ( "hola" ) != 0 ) ||
			 ( argumentos.Argumento ( 1 ).compare ( "42" ) != 0 ) ||
			 ( argumentos.Argumento ( 2 ).compare ( "-3.5" ) != 0 ) )
		{
			cout << "Error caso 2: los argumentos no son los esperados" << endl;
			bRes = false;
		}

		/* Indice fuera de rango: debe lanzar ArgumentoInvalidoExcepcion */
		try
		{
			argumentos.Argumento ( 3 );
			cout << "Error caso 3: no se lanzo excepcion con indice fuera de rango" << endl;
			bRes = false;
		}
		catch ( const ArgumentoInvalidoExcepcion & ex )
		{
		}
		try
		{
			argumentos.Argumento ( -1 );
			cout << "Error caso 4: no se lanzo excepcion con indice negativo" << endl;
			bRes = false;
		}
		catch ( const ArgumentoInvalidoExcepcion & ex )
		{
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


static bool TestArgumentos02 ()
{
	cout << "Test Argumentos 02:" << endl;
	bool bRes = true;

	try
	{
		char a0[] = "programa";
		char a1[] = "hola";
		char a2[] = "42";
		char a3[] = "-3.5";
		char * p_p_cArg[] = { a0, a1, a2, a3 };
		Argumentos argumentos ( 4, p_p_cArg );

		if ( argumentos.EsArgumentoNumerico ( 0 ) ||
			 !argumentos.EsArgumentoNumerico ( 1 ) ||
			 !argumentos.EsArgumentoNumerico ( 2 ) )
		{
			cout << "Error caso 1: EsArgumentoNumerico no da los resultados esperados" << endl;
			bRes = false;
		}

		if ( ( argumentos.ArgumentoEntero ( 1 ) != 42 ) ||
			 ( argumentos.ArgumentoEnteroLargo ( 1 ) != 42 ) )
		{
			cout << "Error caso 2: ArgumentoEntero no devuelve 42" << endl;
			bRes = false;
		}

		/* Un argumento no entero debe lanzar excepcion */
		try
		{
			argumentos.ArgumentoEnteroLargo ( 0 );
			cout << "Error caso 3: no se lanzo excepcion con argumento no entero" << endl;
			bRes = false;
		}
		catch ( const ArgumentoInvalidoExcepcion & ex )
		{
		}
		/* "-3.5" es real pero no entero: ArgumentoEntero debe lanzar excepcion */
		try
		{
			argumentos.ArgumentoEntero ( 2 );
			cout << "Error caso 4: no se lanzo excepcion al pedir un real como entero" << endl;
			bRes = false;
		}
		catch ( const ArgumentoInvalidoExcepcion & ex )
		{
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


static bool TestArgumentos03 ()
{
	cout << "Test Argumentos 03:" << endl;
	bool bRes = true;

	try
	{
		char a0[] = "programa";
		char a1[] = "hola";
		char a2[] = "42";
		char a3[] = "-3.5";
		char * p_p_cArg[] = { a0, a1, a2, a3 };
		Argumentos argumentos ( 4, p_p_cArg );

		if ( !real::equals ( argumentos.ArgumentoRealDoble ( 2 ), -3.5 ) )
		{
			cout << "Error caso 1: ArgumentoRealDoble no devuelve -3.5: " << argumentos.ArgumentoRealDoble ( 2 ) << endl;
			bRes = false;
		}
		/* ArgumentoReal debe interpretar el valor real, no truncarlo a entero */
		if ( !real::equals ( (double) argumentos.ArgumentoReal ( 2 ), -3.5 ) )
		{
			cout << "Error caso 2: ArgumentoReal no devuelve -3.5: " << argumentos.ArgumentoReal ( 2 ) << endl;
			bRes = false;
		}
		/* Un argumento no real debe lanzar excepcion */
		try
		{
			argumentos.ArgumentoRealDoble ( 0 );
			cout << "Error caso 3: no se lanzo excepcion con argumento no real" << endl;
			bRes = false;
		}
		catch ( const ArgumentoInvalidoExcepcion & ex )
		{
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


bool TestArgumentos ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test Argumentos]" << ANSI::RESETEAR << endl;
	if ( TestArgumentos01() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestArgumentos02() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestArgumentos03() )
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
