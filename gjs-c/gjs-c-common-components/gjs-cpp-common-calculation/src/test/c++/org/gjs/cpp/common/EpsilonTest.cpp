#include <CppBase.h>

#include <iostream>


using namespace std;
using namespace org::gjs::cpp::common;



#include "Epsilon.h"



static bool TestEpsilon01 ()
{
	bool bRes = true;
	cout << "Test Epsilon 01:" << endl;

	double dEps = Epsilon ();
	/* El epsilon de la maquina es un valor positivo muy pequeno. */
	if ( dEps <= 0.0 )
	{
		cout << "Error caso 1: el epsilon deberia ser positivo: " << dEps << endl;
		bRes = false;
	}
	if ( dEps >= 0.001 )
	{
		cout << "Error caso 2: el epsilon deberia ser muy pequeno: " << dEps << endl;
		bRes = false;
	}
	/* 1 + epsilon deja de ser distinguible de 1 ( propiedad del epsilon ). */
	if ( ( 1.0 + dEps ) != 1.0 )
	{
		cout << "Error caso 3: 1 + epsilon deberia seguir siendo 1: " << 1.0 + dEps << endl;
		bRes = false;
	}
	/* El valor se cachea: dos llamadas devuelven lo mismo. */
	if ( Epsilon () != dEps )
	{
		cout << "Error caso 4: llamadas sucesivas deberian devolver el mismo epsilon" << endl;
		bRes = false;
	}
	return ( bRes );
}



bool TestEpsilon ()
{
	bool bRes = true;
	cout  << ANSI::AMARILLO << "[Test Epsilon]" << ANSI::RESETEAR << endl;
	if ( TestEpsilon01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO <<  "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	cout << ANSI::AMARILLO << "[Fin]" << ANSI::RESETEAR << endl;
	return ( bRes );
}
