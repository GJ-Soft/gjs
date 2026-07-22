#include "CppCommonTime.h"
#include <CppBase.h>

#include <Cronometro.h>

#include <iostream>


using namespace std;
using namespace org::gjs::cpp::common;


// NOTA: no se introducen esperas ( el test no debe bloquear ). Se comprueba la
// maquina de estados y que los tiempos son no negativos ( sin fijar un valor,
// que dependeria del reloj ).


static bool TestCronometroEstados01 ()
{
	cout << "Test Cronometro estados 01:" << endl;
	bool bRes = true;

	Cronometro cronObj;

	// Sin iniciar: computo y parada valen 0.
	if ( ( cronObj.Computo () != 0 ) || ( cronObj.Parar () != 0 ) )
	{
		cout << "Error caso 1: sin iniciar, Computo() y Parar() deberian ser 0" << endl;
		bRes = false;
	}

	// Tras iniciar, el computo es no negativo.
	cronObj.Iniciar ();
	long long llComputo = cronObj.Computo ();
	if ( llComputo < 0 )
	{
		cout << "Error caso 2: el computo deberia ser no negativo ( es " << llComputo << " )" << endl;
		bRes = false;
	}

	// Parar devuelve un tiempo no negativo y deja el cronometro en reposo.
	if ( cronObj.Parar () < 0 )
	{
		cout << "Error caso 3: Parar() deberia ser no negativo" << endl;
		bRes = false;
	}
	if ( cronObj.Computo () != 0 )
	{
		cout << "Error caso 4: tras Parar(), Computo() deberia volver a 0" << endl;
		bRes = false;
	}
	return ( bRes );
}



bool TestCronometro ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test Cronometro]" << ANSI::RESETEAR << endl;

	if ( TestCronometroEstados01 () )
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
