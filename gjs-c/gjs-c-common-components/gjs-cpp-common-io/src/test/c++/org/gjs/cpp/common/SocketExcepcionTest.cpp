#include "CppCommonIo.h"
#include <CppBase.h>


using namespace std;
using namespace org::gjs::cpp::common;



void RutinaPruebaSocketExcepcion ()
{
	throw SocketExcepcion ( "TestExcepcion", "RutinaPruebaNoEncomntradoExcepcion", EWOULDBLOCK );
}


static bool TestSocketExcepcion01 ()
{
	cout << "Test SocketExcepcion01:" << endl;
	bool bRes = true;
	
	try
	{
		RutinaPruebaSocketExcepcion ();
		cout << "No se ha produdido el throw" << endl;
		bRes = false;
	}
	catch ( const SocketExcepcion & ex )
	{
	}
	catch ( ... )
	{
		cout << "No se ha capturado la excepcion" << endl;
		bRes = false;
	}
	return( bRes );
}

static bool TestSocketExcepcion02 ()
{
	cout << "Test SocketExcepcion02:" << endl;
	bool bRes = true;

	SocketExcepcion ex( "TestExcepcion", "TestSocketExcepcion01", EWOULDBLOCK );
	/* El texto lo pone strerror, y no dice lo mismo en todas partes: EWOULDBLOCK
	   vale 11 en Cygwin y en Linux, el mismo numero que EAGAIN, y de ahi salia
	   "Resource temporarily unavailable". En la libreria de Windows vale 140, un
	   valor propio del que strerror no sabe nada y para el que contesta "Unknown
	   error". Se comprueba que el mensaje sea el que el sistema da para ese
	   codigo, que es el contrato de SistemaExcepcion, en lugar de un literal que
	   solo vale en una plataforma. */
	if ( ( ex.getModulo () != "TestExcepcion" ) ||
	     ( ex.getRutina () != "TestSocketExcepcion01" ) ||
	     ( ex.getMensaje () != strerror ( EWOULDBLOCK ) ) ) 
	{
		cout << "Error caso 1: [" << ex.whatExt () << "]" << endl;
		bRes = false;
	}
	return( bRes );
}

bool TestSocketExcepcion ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test Excepcion]" << ANSI::RESETEAR << endl;
	if ( TestSocketExcepcion01() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestSocketExcepcion02() )
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
