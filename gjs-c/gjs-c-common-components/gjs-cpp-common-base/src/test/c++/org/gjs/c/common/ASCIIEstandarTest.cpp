#include "CppBase.h"


#include <iostream>



using namespace std;
using namespace org::gjs::cpp::common;




static bool TestASCIIEstandar01 ()
{
	cout << "Test ASCIIEstandar01:" << endl;
	bool bRes = true;

	// ASCIICodigo / ASCIICaracter: conversion en ambos sentidos.
	if ( ASCIICodigo ( 'A' ) != 65 )
	{
		cout << "Error caso 1: [" << ASCIICodigo ( 'A' ) << "]" << endl;
		bRes = false;
	}
	if ( ASCIICaracter ( 65 ) != 'A' )
	{
		cout << "Error caso 2: [" << ASCIICaracter ( 65 ) << "]" << endl;
		bRes = false;
	}
	if ( ASCIICaracter ( ASCIICodigo ( 'z' ) ) != 'z' )
	{
		cout << "Error caso 3" << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestASCIIEstandar02 ()
{
	cout << "Test ASCIIEstandar02:" << endl;
	bool bRes = true;

	// ASCIIEsCodigoControl: todo el rango 0..31 (incluido US) y el 127 (DEL)
	// son codigos de control; los imprimibles (32..126) no lo son.
	if ( ! ASCIIEsCodigoControl ( (char) 0 ) )
	{
		cout << "Error caso 1 (NUL)" << endl;
		bRes = false;
	}
	if ( ! ASCIIEsCodigoControl ( '\t' ) )
	{
		cout << "Error caso 2 (TAB)" << endl;
		bRes = false;
	}
	if ( ! ASCIIEsCodigoControl ( (char) 31 ) )
	{
		cout << "Error caso 3 (US)" << endl;
		bRes = false;
	}
	if ( ! ASCIIEsCodigoControl ( (char) 127 ) )
	{
		cout << "Error caso 4 (DEL)" << endl;
		bRes = false;
	}
	if ( ASCIIEsCodigoControl ( ' ' ) )
	{
		cout << "Error caso 5 (espacio)" << endl;
		bRes = false;
	}
	if ( ASCIIEsCodigoControl ( 'A' ) )
	{
		cout << "Error caso 6 (A)" << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestASCIIEstandar03 ()
{
	cout << "Test ASCIIEstandar03:" << endl;
	bool bRes = true;

	// Comprobadores concretos por codigo.
	if ( ! ASCIIEsNUL ( (char) 0 ) || ASCIIEsNUL ( 'A' ) )
	{
		cout << "Error caso 1 (NUL)" << endl;
		bRes = false;
	}
	if ( ! ASCIIEsTAB ( '\t' ) || ASCIIEsTAB ( ' ' ) )
	{
		cout << "Error caso 2 (TAB)" << endl;
		bRes = false;
	}
	if ( ! ASCIIEsLF ( '\n' ) || ! ASCIIEsCR ( '\r' ) )
	{
		cout << "Error caso 3 (LF/CR)" << endl;
		bRes = false;
	}
	if ( ! ASCIIEsESC ( (char) 27 ) )
	{
		cout << "Error caso 4 (ESC)" << endl;
		bRes = false;
	}
	if ( ! ASCIIEsUS ( (char) 31 ) )
	{
		cout << "Error caso 5 (US)" << endl;
		bRes = false;
	}
	if ( ! ASCIIEsDEL ( (char) 127 ) )
	{
		cout << "Error caso 6 (DEL)" << endl;
		bRes = false;
	}
	return ( bRes );
}

bool TestASCIIEstandar ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test ASCIIEstandar]" << ANSI::RESETEAR << endl;
	if ( TestASCIIEstandar01() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestASCIIEstandar02() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestASCIIEstandar03() )
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
