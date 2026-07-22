#include "CppCommonSystem.h"
#include <CppBase.h>

#include <CVariablesEntorno.h>

#include <iostream>
#include <string>


using namespace std;
using namespace org::gjs::cpp::common;




static bool TestCVariablesEntorno01 ()
{
	cout << "Test CVariablesEntorno 01:" << endl;
	bool bRes = true;

	try
	{
		CVariablesEntorno ve;

		// PATH existe en cualquier sistema.
		if ( ! ve.ExisteVariable ( "PATH" ) )
		{
			cout << "Error caso 1: la variable PATH deberia existir" << endl;
			bRes = false;
		}
		// Una variable inventada no existe.
		if ( ve.ExisteVariable ( "GJS_VARIABLE_INEXISTENTE_XYZ" ) )
		{
			cout << "Error caso 2: una variable inventada no deberia existir" << endl;
			bRes = false;
		}

		// ObtValor de una variable existente devuelve un string reservado ( a liberar ).
		string * p_sValor = ve.ObtValor ( "PATH" );
		if ( p_sValor == NULL )
		{
			cout << "Error caso 3: ObtValor de PATH no deberia ser NULL" << endl;
			bRes = false;
		}
		else
		{
			if ( p_sValor->size () == 0 )
			{
				cout << "Error caso 4: el valor de PATH no deberia estar vacio" << endl;
				bRes = false;
			}
			delete p_sValor;
		}

		// ObtValor de una variable inexistente devuelve NULL.
		string * p_sNulo = ve.ObtValor ( "GJS_VARIABLE_INEXISTENTE_XYZ" );
		if ( p_sNulo != NULL )
		{
			cout << "Error caso 5: ObtValor de una variable inexistente deberia ser NULL" << endl;
			bRes = false;
			delete p_sNulo;
		}
		// Ciclo establecer/leer ( EstValor implementado con putenv ).
		if ( ! ve.EstValor ( "GJS_TEST_VAR_XYZ", "valor123" ) )
		{
			cout << "Error caso 6: EstValor deberia devolver cierto" << endl;
			bRes = false;
		}
		if ( ! ve.ExisteVariable ( "GJS_TEST_VAR_XYZ" ) )
		{
			cout << "Error caso 7: la variable establecida deberia existir" << endl;
			bRes = false;
		}
		string * p_sPuesto = ve.ObtValor ( "GJS_TEST_VAR_XYZ" );
		if ( ( p_sPuesto == NULL ) || ( *p_sPuesto != "valor123" ) )
		{
			cout << "Error caso 8: el valor recuperado deberia ser valor123: ["
				 << ( p_sPuesto != NULL ? *p_sPuesto : string ( "(nulo)" ) ) << "]" << endl;
			bRes = false;
		}
		if ( p_sPuesto != NULL )
		{
			delete p_sPuesto;
		}
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



bool TestCVariablesEntorno ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test CVariablesEntorno]" << ANSI::RESETEAR << endl;
	if ( TestCVariablesEntorno01 () )
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
