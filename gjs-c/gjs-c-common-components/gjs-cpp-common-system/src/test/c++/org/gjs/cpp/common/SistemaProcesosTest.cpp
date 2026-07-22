#include "CppCommonSystem.h"
#include <CppBase.h>

#include <SistemaProcesos.h>

#include <iostream>


using namespace std;
using namespace org::gjs::cpp::common;




static bool TestSisProcesos01 ()
{
	cout << "Test SisProcesos 01:" << endl;
	bool bRes = true;

	try
	{
		// El PID del proceso actual es positivo.
		long lPID = SisPID ();
		if ( lPID <= 0 )
		{
			cout << "Error caso 1: el PID deberia ser positivo: " << lPID << endl;
			bRes = false;
		}
		// La cadena del PID no esta vacia.
		if ( SisPIDCadena ().size () == 0 )
		{
			cout << "Error caso 2: la cadena del PID no deberia estar vacia" << endl;
			bRes = false;
		}
	
		// Llamadas defensivas ( varias pueden devolver 0/"" segun plataforma;
		// solo se comprueba que no lanzan y no se lanzan procesos ni hilos ).
		( void ) SisTID ();
		( void ) SisTIDCadena ();
		( void ) SisNombreProceso ();
		( void ) SisRutaEjecutable ();
		( void ) SisFicheroEjecutable ();
		( void ) SisNumProcesos ();
		( void ) SisNumSubprocesos ();
		( void ) SisNumHilos ();
		( void ) SisExisteProceso ( lPID );
		( void ) SisProcesoEnEjecucion ( lPID );
	}
	catch ( exception & ex )
	{
		cout << "Se ha producido una excepcion: " << ex.what () << endl;
		bRes = false;
	}
	catch ( ... )
	{
		cout << "Excepcion indefinida" << endl;
		bRes = false;
	}
	return ( bRes );
}



bool TestSistemaProcesos ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test SistemaProcesos]" << ANSI::RESETEAR << endl;
	if ( TestSisProcesos01 () )
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
