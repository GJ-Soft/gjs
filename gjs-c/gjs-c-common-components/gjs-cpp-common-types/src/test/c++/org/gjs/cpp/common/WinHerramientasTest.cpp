#include "CppCommonTypes.h"

#include <iostream>


using namespace std;
using namespace org::gjs::cpp::common;


#if ( defined( WIN ) )
	

static bool TestDLLEjecutar01 ()
{
	cout << "Test DLLEjecutar01:" << endl;
	bool bRes = true;
	try
	{
		if ( ! DLLEjecutar ( "C:\\Windows\\System32\\Kernel32.dll", "GetLastError" ) )
		{
			cout << "Error: retorna falso" << endl;
			bRes = false;
		}
	}
	catch ( Excepcion& ex )
	{
		bRes = false;
		cout << "Excepcion recibida: " << ex.what () << endl;
	}
	catch ( ... )
	{
		bRes = false;
		cout << "Excepcion inesperada recibida: "  << endl;
	}
	return( bRes );
}

#endif

bool TestWinHerramientas ()
{
	bool bRes = true;
	
	cout << endl << ANSI::AMARILLO << "[Test WinHerramientas]" << ANSI::RESETEAR << endl;
#if ( defined( WIN ) )
	if ( TestDLLEjecutar01() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
#else
	cout << "  (Esta clase sólo está disponible si se compila para Windows)" << endl;	
#endif
	cout << ANSI::AMARILLO << "[Fin]" << ANSI::RESETEAR << endl;	
	
	return ( bRes );
}
