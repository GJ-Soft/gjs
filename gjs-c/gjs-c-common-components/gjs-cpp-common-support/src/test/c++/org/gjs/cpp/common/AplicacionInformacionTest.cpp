#include "CppCommonSupport.h"
#include <CppBase.h>

#include <AplicacionInformacion.h>

#include <iostream>


using namespace std;
using namespace org::gjs::cpp::common;




static bool TestAplicInfoCicloVida01 ()
{
	cout << "Test AplicacionInformacion ciclo de vida 01:" << endl;
	bool bRes = true;

	// Estado limpio de partida ( por si otro test dejo algo inicializado ).
	AplicFinalizar ();
	if ( AplicEstaInicializada () )
	{
		cout << "Error caso 1: tras AplicFinalizar no deberia estar inicializada" << endl;
		bRes = false;
	}

	// Inicializacion ( bConsola = true para NO tocar los flujos estandar ).
	if ( ! AplicInicializar ( "miapp", 2, 3, 4, (long) 0, true ) )
	{
		cout << "Error caso 2: AplicInicializar deberia devolver true" << endl;
		bRes = false;
	}
	if ( ! AplicEstaInicializada () )
	{
		cout << "Error caso 3: deberia estar inicializada" << endl;
		bRes = false;
	}
	if ( AplicNombre () != "miapp" )
	{
		cout << "Error caso 4: AplicNombre deberia ser miapp" << endl;
		bRes = false;
	}
	if ( ( AplicVersion () != 2 ) || ( AplicSubversion () != 3 ) || ( AplicRevision () != 4 ) )
	{
		cout << "Error caso 5: version/subversion/revision incorrectas ( "
			 << AplicVersion () << "." << AplicSubversion () << "." << AplicRevision () << " )" << endl;
		bRes = false;
	}
	if ( AplicCadenaVersion () != "2.3.4" )
	{
		cout << "Error caso 6: AplicCadenaVersion deberia ser 2.3.4 y es [" << AplicCadenaVersion () << "]" << endl;
		bRes = false;
	}
	if ( AplicPID () <= 0 )
	{
		cout << "Error caso 7: AplicPID deberia ser positivo" << endl;
		bRes = false;
	}

	// Finalizacion.
	AplicFinalizar ();
	if ( AplicEstaInicializada () )
	{
		cout << "Error caso 8: tras AplicFinalizar no deberia estar inicializada" << endl;
		bRes = false;
	}
	if ( AplicVersion () != 0 )
	{
		cout << "Error caso 9: sin inicializar, AplicVersion deberia ser 0" << endl;
		bRes = false;
	}
	return ( bRes );
}



bool TestAplicacionInformacion ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test AplicacionInformacion]" << ANSI::RESETEAR << endl;

	if ( TestAplicInfoCicloVida01 () )
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
