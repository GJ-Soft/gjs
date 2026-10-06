#include "CppCommonSystem.h"
#include <CppBase.h>

#include <CGestorSignals.h>
#include <SistemaSignals.h>

#include <iostream>


using namespace std;
using namespace org::gjs::cpp::common;




static bool TestCGestorSignals01 ()
{
	cout << "Test CGestorSignals 01:" << endl;
	bool bRes = true;

#if ( defined ( POSIX ) )
	try
	{
		// El constructor instala los manejadores; el destructor los restaura al
		// salir del ambito. No se envian senales.
		CGestorSignals gestor;

		if ( gestor.EsValido () != 1 )
		{
			cout << "Error caso 1: el gestor recien creado deberia ser valido" << endl;
			bRes = false;
		}
		// Sin rutina asignada una senal no esta activada.
		if ( gestor.EstaSignalActivado ( SIS_SIG_INTERRUPCION ) != 0 )
		{
			cout << "Error caso 2: sin rutina la senal no deberia estar activada" << endl;
			bRes = false;
		}
		// Activar una senal sin rutina asignada la deja desactivada.
		gestor.ActivarSignal ( SIS_SIG_INTERRUPCION );
		if ( gestor.EstaSignalActivado ( SIS_SIG_INTERRUPCION ) != 0 )
		{
			cout << "Error caso 3: activar sin rutina no deberia activar la senal" << endl;
			bRes = false;
		}
		// Desactivar no lanza y la senal sigue desactivada.
		gestor.DesactivarSignal ( SIS_SIG_INTERRUPCION );
		if ( gestor.EstaSignalActivado ( SIS_SIG_INTERRUPCION ) != 0 )
		{
			cout << "Error caso 4: la senal deberia seguir desactivada" << endl;
			bRes = false;
		}
		// Un indice de senal fuera de rango se consulta de forma segura.
		if ( gestor.EstaSignalActivado ( -1 ) != 0 )
		{
			cout << "Error caso 5: un indice invalido deberia dar 0" << endl;
			bRes = false;
		}
		// Regresion: con un indice fuera de rango se leia la tabla de rutinas por
		// defecto fuera de sus limites. Ahora no hace nada.
		gestor.Procesar ( -1 );
		gestor.Procesar ( SIS_NUM_SIGNALS );
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
#else
	cout << "  ( omitido: CGestorSignals solo existe en POSIX )" << endl;
#endif

	return ( bRes );
}



bool TestCGestorSignals ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test CGestorSignals]" << ANSI::RESETEAR << endl;
	if ( TestCGestorSignals01 () )
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
