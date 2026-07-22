#include "MockServidorFTP.h"


#include <CppBase.h>

#include <iostream>


using namespace std;
using namespace org::gjs::cpp::common;
using namespace org::gjs::cpp::common::test::mock;



MockServidorFTP * mockServidorFTP = NULL;



bool TestMockServidorFTP01 ()
{
	cout << "Test MockServidorFTP01: " << endl;
	bool bRes = true;
	/* El constructor de ServidorFTP puede cambiar el directorio de trabajo: se
	   guarda para restaurarlo al terminar. */
	string sDirInicial = DirectorioActual();
	try
	{
		/* MockServidorFTP es un doble de servidor FTP (infraestructura de test): un
		   test funcional completo exigiria levantar el servidor y un cliente. Aqui se
		   comprueba, de forma robusta, que construirlo con un fichero de usuarios que
		   no puede cargarse NO deja un servidor en pie: el constructor de
		   ServidorSesion lanza Excepcion (y, si el puerto no se pudiera enlazar,
		   SocketExcepcion, que tambien deriva de Excepcion). Se usa un puerto alto
		   poco habitual. */
		bool bLanzo = false;
		try
		{
			MockServidorFTP servidor ( 50210, 50211, ".", "no-existe-usuarios.info" );
			cout << "Error caso 1: se esperaba una excepcion al construir con un fichero de usuarios invalido" << endl;
		}
		catch ( const Excepcion & ex )
		{
			bLanzo = true;
		}
		if ( !bLanzo )
		{
			bRes = false;
		}
	}
	catch ( const exception & ex )
	{
		cout << "Error al probar la funcionalidad del test: " << ex.what () << endl;
		bRes = false;
	}
	catch ( ... )
	{
		cout << "Terminado con throwable inesperado" << endl;
		bRes = false;
	}
	EstablecerDirectorio( sDirInicial );
	return( bRes );
}


bool TestMockServidorFTP ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test MockServidorFTP]" << ANSI::RESETEAR << endl;
	if ( TestMockServidorFTP01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	return ( bRes );
}
