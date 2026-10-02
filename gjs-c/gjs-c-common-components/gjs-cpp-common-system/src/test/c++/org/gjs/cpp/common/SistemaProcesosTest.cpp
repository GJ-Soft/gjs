#include "CppCommonSystem.h"
#include <CppBase.h>

#include <SistemaProcesos.h>

#include <iostream>
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <thread>


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



/* ---------------------------------------------------------------------------
   Hilos. El apreton de manos va con condition_variable, no con esperas al
   tuntun: un test de concurrencia que duerme un rato "por si acaso" falla una
   vez de cada veinte en la maquina de compilacion.
   --------------------------------------------------------------------------- */

static std::mutex				_mtxPrueba;
static std::condition_variable	_cvPrueba;
static bool						_bHiloArrancado = false;
static bool						_bHiloPuedeSalir = false;

static void * _FuncionHiloPrueba ( void * p_vParam )
{
	( void ) p_vParam;
	{
		std::lock_guard < std::mutex > lckGuarda ( _mtxPrueba );
		_bHiloArrancado = true;
	}
	_cvPrueba.notify_all ();
	{
		std::unique_lock < std::mutex > lckGuarda ( _mtxPrueba );
		_cvPrueba.wait ( lckGuarda, [] { return ( _bHiloPuedeSalir ); } );
	}
	return ( NULL );
}

/* Espera a que el hilo se dé de baja del registro, con tope: el aviso de que
   ha terminado lo da el propio hilo al volver, y la baja ocurre justo despues,
   asi que hay una ventana corta que no se puede sincronizar desde fuera. */
static bool _EsperarBaja ( std::thread::id thTID )
{
	for ( int iIntento = 0; iIntento < 200; iIntento = iIntento + 1 )
	{
		if ( ! SisExisteHilo ( thTID ) )
		{
			return ( true );
		}
		std::this_thread::sleep_for ( std::chrono::milliseconds ( 10 ) );
	}
	return ( false );
}

static bool TestSisHilos01 ()
{
	cout << "Test SisHilos 01:" << endl;
	bool bRes = true;

	_bHiloArrancado = false;
	_bHiloPuedeSalir = false;

	int iAntes = SisNumHilos ();
	std::thread::id thTID = SisCrearHilo ( _FuncionHiloPrueba );
	if ( thTID == std::thread::id () )
	{
		cout << "Error caso 1: no se pudo crear el hilo" << endl;
		return ( false );
	}
	if ( thTID == SisTID () )
	{
		cout << "Error caso 2: el hilo nuevo no puede tener el id del principal" << endl;
		bRes = false;
	}
	/* Se espera a que arranque de verdad antes de mirar el registro. */
	{
		std::unique_lock < std::mutex > lckGuarda ( _mtxPrueba );
		_cvPrueba.wait ( lckGuarda, [] { return ( _bHiloArrancado ); } );
	}
	if ( ! SisExisteHilo ( thTID ) )
	{
		cout << "Error caso 3: el hilo deberia existir mientras corre" << endl;
		bRes = false;
	}
	if ( SisNumHilos () != ( iAntes + 1 ) )
	{
		cout << "Error caso 4: se esperaban " << ( iAntes + 1 ) << " hilos: " << SisNumHilos () << endl;
		bRes = false;
	}
	/* Se le deja salir. */
	{
		std::lock_guard < std::mutex > lckGuarda ( _mtxPrueba );
		_bHiloPuedeSalir = true;
	}
	_cvPrueba.notify_all ();
	if ( ! _EsperarBaja ( thTID ) )
	{
		cout << "Error caso 5: el hilo no se dio de baja del registro" << endl;
		bRes = false;
	}
	else if ( SisNumHilos () != iAntes )
	{
		cout << "Error caso 6: el contador no volvio a " << iAntes << ": " << SisNumHilos () << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestSisHilos02 ()
{
	cout << "Test SisHilos 02:" << endl;
	bool bRes = true;
	std::thread::id thVacio;

	if ( SisCrearHilo ( NULL ) != thVacio )
	{
		cout << "Error caso 1: crear con funcion nula deberia dar el id vacio" << endl;
		bRes = false;
	}
	if ( SisExisteHilo ( thVacio ) )
	{
		cout << "Error caso 2: el id vacio no deberia existir" << endl;
		bRes = false;
	}
	if ( SisExisteHilo ( SisTID () ) )
	{
		cout << "Error caso 3: el hilo principal no lo creo esta API" << endl;
		bRes = false;
	}
	if ( ! SisCambiarASiguienteHilo () )
	{
		cout << "Error caso 4: ceder el turno no puede fallar" << endl;
		bRes = false;
	}
	/* Sin soporte por contrato: si algun dia se implementan, este test avisa. */
	if ( SisSuspenderHilo ( thVacio ) )
	{
		cout << "Error caso 5: suspender no esta soportado, deberia dar false" << endl;
		bRes = false;
	}
	if ( SisReanudarHilo ( thVacio ) )
	{
		cout << "Error caso 6: reanudar no esta soportado, deberia dar false" << endl;
		bRes = false;
	}
	if ( SisHiloPrioridad ( thVacio ) != 0 )
	{
		cout << "Error caso 7: la prioridad de un id desconocido deberia ser 0" << endl;
		bRes = false;
	}
	if ( SisFinalizarHilo ( thVacio ) )
	{
		cout << "Error caso 8: finalizar un id desconocido deberia dar false" << endl;
		bRes = false;
	}
	return ( bRes );
}

bool TestSistemaProcesos ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test SistemaProcesos]" << ANSI::RESETEAR << endl;
	if ( TestSisProcesos01 () && TestSisHilos01 () && TestSisHilos02 () )
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
