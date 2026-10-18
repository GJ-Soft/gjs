#include "CppBase.h"

#include <cstdio>
#include <iostream>


using namespace std;
using namespace org::gjs::cpp::common;


/* Los valores esperados son los de la norma, no salidas de las propias funciones:
   "a" + U+00F1 (n con tilde) + U+20AC (euro)
     UTF-8              61 C3 B1 E2 82 AC
     UTF-16 big-endian  00 61 00 F1 20 AC   ( el orden por defecto de codecvt_utf16 )
   Los errores se escriben por cout en hexadecimal: wcout, con el locale "C", se
   queda en estado de error con el primer caracter que no sabe convertir y a
   partir de ahi no escribe nada mas. */
static const wstring WS_NO_ASCII = L"a\u00F1\u20AC";
static const string S_NO_ASCII_UTF8 = "a\xC3\xB1\xE2\x82\xAC";
static const string S_NO_ASCII_UTF16 = string ( "\x00" "a" "\x00\xF1\x20\xAC", 6 );

static string _Hex ( const string & sValor )
{
	string sRes;
	char cBuf[4];
	for ( unsigned char c : sValor )
	{
		snprintf ( cBuf, sizeof ( cBuf ), " %02X", c );
		sRes += cBuf;
	}
	return ( sRes );
}

static string _Hex ( const wstring & wsValor )
{
	string sRes;
	char cBuf[12];
	for ( wchar_t c : wsValor )
	{
		snprintf ( cBuf, sizeof ( cBuf ), " U+%04X", (unsigned int) c );
		sRes += cBuf;
	}
	return ( sRes );
}

/* UTF-16 big-endian de un texto ASCII: un 0x00 delante de cada caracter. */
static string _Utf16BeDeAscii ( const string & sAscii )
{
	string sRes;
	for ( char c : sAscii )
	{
		sRes += '\0';
		sRes += c;
	}
	return ( sRes );
}

static bool TestUnicodeAUtf801 ()
{
	cout << "Test UnicodeAUtf8 01:" << endl;
	bool bRes = true;
	string sRes = UnicodeAUtf8( wstring( L"" ) );
	if ( sRes.size() != 0 )
	{
		cout << "Error caso 1: [" << _Hex( sRes ) << " ]" << endl;
		bRes = false;
	}
	sRes = UnicodeAUtf8( wstring( L"Esto es una cadena" ) );
	if ( sRes.compare( "Esto es una cadena" ) != 0 )
	{
		cout << "Error caso 2: [" << _Hex( sRes ) << " ]" << endl;
		bRes = false;
	}
	sRes = UnicodeAUtf8( WS_NO_ASCII );
	if ( sRes.compare( S_NO_ASCII_UTF8 ) != 0 )
	{
		cout << "Error caso 3: [" << _Hex( sRes ) << " ]" << endl;
		bRes = false;
	}
	return( bRes );
}

static bool TestUnicodeAUtf1601 ()
{
	cout << "Test UnicodeAUtf16 01:" << endl;
	bool bRes = true;
	string sRes = UnicodeAUtf16( wstring( L"" ) );
	if ( sRes.size() != 0 )
	{
		cout << "Error caso 1: [" << _Hex( sRes ) << " ]" << endl;
		bRes = false;
	}
	sRes = UnicodeAUtf16( wstring( L"Esto es una cadena" ) );
	if ( sRes.compare( _Utf16BeDeAscii( "Esto es una cadena" ) ) != 0 )
	{
		cout << "Error caso 2: [" << _Hex( sRes ) << " ]" << endl;
		bRes = false;
	}
	sRes = UnicodeAUtf16( WS_NO_ASCII );
	if ( sRes.compare( S_NO_ASCII_UTF16 ) != 0 )
	{
		cout << "Error caso 3: [" << _Hex( sRes ) << " ]" << endl;
		bRes = false;
	}
	return( bRes );
}

static bool TestUtf8AUnicode01 ()
{
	cout << "Test Utf8AUnicode 01:" << endl;
	bool bRes = true;
	wstring wsRes = Utf8AUnicode( string( "" ) );
	if ( wsRes.size() != 0 )
	{
		cout << "Error caso 1: [" << _Hex( wsRes ) << " ]" << endl;
		bRes = false;
	}
	wsRes = Utf8AUnicode( string( "Esto es una cadena" ) );
	if ( wsRes.compare( wstring( L"Esto es una cadena" ) ) != 0 )
	{
		cout << "Error caso 2: [" << _Hex( wsRes ) << " ]" << endl;
		bRes = false;
	}
	wsRes = Utf8AUnicode( S_NO_ASCII_UTF8 );
	if ( wsRes.compare( WS_NO_ASCII ) != 0 )
	{
		cout << "Error caso 3: [" << _Hex( wsRes ) << " ]" << endl;
		bRes = false;
	}
	return( bRes );
}

/* La entrada es UTF-16, dos bytes por caracter: un texto ASCII tal cual no lo es
   ( "Esto es una cadena" se lee como 9 caracteres CJK, U+4573... ), asi que se
   construye con _Utf16BeDeAscii. */
static bool TestUtf16AUnicode01 ()
{
	cout << "Test Utf16AUnicode 01:" << endl;
	bool bRes = true;
	wstring wsRes = Utf16AUnicode( string( "" ) );
	if ( wsRes.size() != 0 )
	{
		cout << "Error caso 1: [" << _Hex( wsRes ) << " ]" << endl;
		bRes = false;
	}
	wsRes = Utf16AUnicode( _Utf16BeDeAscii( "Esto es una cadena" ) );
	if ( wsRes.compare( wstring( L"Esto es una cadena" ) ) != 0 )
	{
		cout << "Error caso 2: [" << _Hex( wsRes ) << " ]" << endl;
		bRes = false;
	}
	wsRes = Utf16AUnicode( S_NO_ASCII_UTF16 );
	if ( wsRes.compare( WS_NO_ASCII ) != 0 )
	{
		cout << "Error caso 3: [" << _Hex( wsRes ) << " ]" << endl;
		bRes = false;
	}
	return( bRes );
}


bool TestCodificacion ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test Cadenas]" << ANSI::RESETEAR << endl;
	if ( TestUnicodeAUtf801() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestUnicodeAUtf1601() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestUtf8AUnicode01() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestUtf16AUnicode01() )
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
