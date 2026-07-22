#include "CppCommonSupport.h"
#include <CppBase.h>

#include <ConsolaDepuracion.h>

#include <iostream>


using namespace std;
using namespace org::gjs::cpp::common;


// NOTA: no se abre la consola de depuracion ( ConDepAbrir redirige a /dev/tty ).
// Con la consola cerrada las escrituras devuelven false sin escribir nada. Ademas,
// invocar las variantes CON FORMATO fuerza la instanciacion de las plantillas
// ( ahora definidas en la cabecera ), lo que verifica que enlazan correctamente.


static bool TestConDepEstado01 ()
{
	cout << "Test ConsolaDepuracion estado 01:" << endl;
	bool bRes = true;

	if ( ConDepEstaAbierta () )
	{
		cout << "Error caso 1: la consola de depuracion no deberia estar abierta al inicio" << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestConDepEscribirCerrada01 ()
{
	cout << "Test ConDepEscribir con consola cerrada 01:" << endl;
	bool bRes = true;

	// Escritor base ( no plantilla ).
	if ( ConDepEscribir ( "hola" ) )
	{
		cout << "Error caso 1: ConDepEscribir con la consola cerrada deberia ser false" << endl;
		bRes = false;
	}
	if ( ConDepEscribirLinea ( "hola" ) )
	{
		cout << "Error caso 2: ConDepEscribirLinea con la consola cerrada deberia ser false" << endl;
		bRes = false;
	}
	// Variantes con formato ( plantilla en cabecera -> instanciacion + enlace ).
	if ( ConDepEscribir ( "valor = {}", 42 ) )
	{
		cout << "Error caso 3: ConDepEscribir con formato deberia ser false ( consola cerrada )" << endl;
		bRes = false;
	}
	if ( ConDepEscribirLinea ( "x = {}, y = {}", 1, 2 ) )
	{
		cout << "Error caso 4: ConDepEscribirLinea con formato deberia ser false ( consola cerrada )" << endl;
		bRes = false;
	}
	return ( bRes );
}



bool TestConsolaDepuracion ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test ConsolaDepuracion]" << ANSI::RESETEAR << endl;

	if ( TestConDepEstado01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}

	if ( TestConDepEscribirCerrada01 () )
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
