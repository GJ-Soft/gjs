#include "UtilesTest.h"

#include <CppBase.h>
#include <CppLog.h>

#include <string>
#include <iostream>
#include <stdexcept>



using namespace std;
using namespace org::gjs::cpp::common;
using namespace org::gjs::cpp::common::log;
using namespace org::gjs::cpp::common::test;



bool TestVerificarValor01 ()
{
	cout << "Test VerificarValor01: " << endl;
	bool bRes = true;
	try
	{
		string sValor1( "" );
		string sResultado1( "" ); 
		string sEsperado1 ( "" );
		string sValor2( "Valor" );
		string sResultado2( "Resultado" ); 
		string sValor3( "Valor" );
		wstring sResultado3( L"Resultado" ); 
		wstring sEsperado3( L"Resultado" ); 
		bool bRes1 = true;
		VerificarValor ( sValor1, sResultado1, sEsperado1, bRes1 );
		if ( ! bRes1 )
		{
			cout << "Error caso 1: Resultado incorrecto" << endl;
			bRes = false;
		}
		bRes1 = true;
		VerificarValor ( sValor1, sResultado1, "A", bRes1 );
		if ( bRes1 )
		{
			cout << "Error caso 2: Resultado incorrecto" << endl;
			bRes = false;
		}
		bRes1 = true;
		VerificarValor ( sValor2, sResultado2, "Resultado", bRes1 );
		if ( ! bRes1 )
		{
			cout << "Error caso 3: Resultado incorrecto" << endl;
			bRes = false;
		}
		bRes1 = true;
		VerificarValor ( sValor2, sResultado2, "Aesultado", bRes1 );
		if ( bRes1 )
		{
			cout << "Error caso 4: Resultado incorrecto" << endl;
			bRes = false;
		}
		bRes1 = true;
		VerificarValor ( sValor2, sResultado2, "ResultadoX", bRes1 );
		if ( bRes1 )
		{
			cout << "Error caso 5: Resultado incorrecto" << endl;
			bRes = false;
		}
		bRes1 = true;
		VerificarValor ( sValor2, sResultado2, NULL, bRes1 );
		if ( bRes1 )
		{
			cout << "Error caso 6: Resultado incorrecto" << endl;
			bRes = false;
		}
		bRes1 = true;
		VerificarValor ( sValor2, sResultado2.c_str(), "Aesultado", bRes1 );
		if ( bRes1 )
		{
			cout << "Error caso 7: Resultado incorrecto" << endl;
			bRes = false;
		}
		bRes1 = true;
		VerificarValor ( sValor3, sResultado3, sEsperado3, bRes1 );
		if ( ! bRes1 )
		{
			cout << "Error caso 8: Resultado incorrecto" << endl;
			bRes = false;
		}
		bRes1 = true;
		VerificarValor ( sValor3, sResultado3, L"Azpitarte", bRes1 );
		if ( bRes1 )
		{
			cout << "Error caso 9: Resultado incorrecto" << endl;
			bRes = false;
		}
		bRes1 = true;
		VerificarValor ( sValor3, L"Resultado", L"Aesultado", bRes1 );
		if ( bRes1 )
		{
			cout << "Error caso 10: Resultado incorrecto" << endl;
			bRes = false;
		}
	}
	catch ( const exception & ex )
	{
		cout << "Excepcion inesperada  al probar la funcionalidad del UtilesTest: " << ex.what () << endl;
		bRes = false;
	}	
	catch ( ... )
	{
		cout << "Terminado con throwable inesperado" << endl;
		bRes = false;
	}	
	return( bRes );
}

bool TestVerificarValor02 ()
{
	cout << "Test VerificarValor02: " << endl;
	bool bRes = true;
	try
	{
		string sValor( "Valor" );
		long lResultado = 0;
		bool bRes1 = true;
		VerificarValor ( sValor, lResultado, 0, bRes1 );
		if ( ! bRes1 )
		{
			cout << "Error caso 1: Resultado incorrecto" << endl;
			bRes = false;
		}
		bRes1 = true;
		VerificarValor ( sValor, lResultado, 1, bRes1 );
		if ( bRes1 )
		{
			cout << "Error caso 2: Resultado incorrecto" << endl;
			bRes = false;
		}
		lResultado = 1;
		bRes1 = true;
		VerificarValor ( sValor, lResultado, 17, bRes1 );
		if ( bRes1 )
		{
			cout << "Error caso 3: Resultado incorrecto" << endl;
			bRes = false;
		}
		lResultado = 2;
		bRes1 = true;
		VerificarValor ( sValor, lResultado, 2, bRes1 );
		if ( !bRes1 )
		{
			cout << "Error caso 4: Resultado incorrecto" << endl;
			bRes = false;
		}
	}
	catch ( const exception & ex )
	{
		cout << "Excepcion inesperada  al probar la funcionalidad del UtilesTest: " << ex.what () << endl;
		bRes = false;
	}	
	catch ( ... )
	{
		cout << "Terminado con throwable inesperado" << endl;
		bRes = false;
	}	
	return( bRes );
}

bool TestVerificarValor03 ()
{
	cout << "Test VerificarValor03: " << endl;
	bool bRes = true;
	try
	{
		string sValor( "Valor real" );
		bool bRes1 = true;
		double dResultado = 0.0;
		VerificarValor ( sValor, dResultado, 1.0, bRes1 );
		if ( bRes1 )
		{
			cout << "Error caso 1: Resultado incorrecto" << endl;
			bRes = false;
		}
		dResultado = 1.0;
		bRes1 = true;
		VerificarValor ( sValor, dResultado, 1.0, bRes1 );
		if ( !bRes1 )
		{
			cout << "Error caso 2: Resultado incorrecto" << endl;
			bRes = false;
		}
	}
	catch ( const exception & ex )
	{
		cout << "Excepcion inesperada  al probar la funcionalidad del UtilesTest: " << ex.what () << endl;
		bRes = false;
	}	
	catch ( ... )
	{
		cout << "Terminado con throwable inesperado" << endl;
		bRes = false;
	}	
	return( bRes );
}

bool TestEsNuloNoEsNulo01 ()
{
	cout << "Test EsNuloNoEsNulo: " << endl;
	bool bRes = true;
	try
	{
		string * p_sValor1 = new string( "test" );
		string * p_sValor2 = NULL;
		bool bRes1 = true;
		VerificarNoEsNulo ( "Caso 1", p_sValor1, bRes1 );
		if ( !bRes1 )
		{
			cout << "Error caso 1: Resultado incorrecto" << endl;
			bRes = false;
		}
		bRes1 = true;
		VerificarEsNulo ( "Caso 2", p_sValor2, bRes1 );
		if ( !bRes1 )
		{
			cout << "Error caso 2: Resultado incorrecto" << endl;
			bRes = false;
		}
		bRes1 = true;
		VerificarEsNulo ( "Caso 3", p_sValor1, bRes1 );
		if ( bRes1 )
		{
			cout << "Error caso 3: Resultado incorrecto" << endl;
			bRes = false;
		}
		bRes1 = true;
		VerificarNoEsNulo ( "Caso 4", p_sValor2, bRes1 );
		if ( bRes1 )
		{
			cout << "Error caso 4: Resultado incorrecto" << endl;
			bRes = false;
		}
	}
	catch ( const exception & ex )
	{
		cout << "Excepcion inesperada  al probar la funcionalidad del UtilesTest: " << ex.what () << endl;
		bRes = false;
	}	
	catch ( ... )
	{
		cout << "Terminado con throwable inesperado" << endl;
		bRes = false;
	}	
	return( bRes );
}

bool TestEsCiertoEsFalso01 ()
{
	cout << "Test EsCiertoEsFalso: " << endl;
	bool bRes = true;
	try
	{
		bool bValor1 = true;
		bool bValor2 = false;
		bool bRes1 = true;
		VerificarEsCierto ( "Caso 1", bValor1, bRes1 );
		if ( !bRes1 )
		{
			cout << "Error caso 1: Resultado incorrecto" << endl;
			bRes = false;
		}
		bRes1 = true;
		VerificarEsFalso ( "Caso 2", bValor2, bRes1 );
		if ( !bRes1 )
		{
			cout << "Error caso 2: Resultado incorrecto" << endl;
			bRes = false;
		}
		bRes1 = true;
		VerificarEsFalso ( "Caso 3", bValor1, bRes1 );
		if ( bRes1 )
		{
			cout << "Error caso 3: Resultado incorrecto" << endl;
			bRes = false;
		}
		bRes1 = true;
		VerificarEsCierto ( "Caso 4", bValor2, bRes1 );
		if ( bRes1 )
		{
			cout << "Error caso 4: Resultado incorrecto" << endl;
			bRes = false;
		}
	}
	catch ( const exception & ex )
	{
		cout << "Excepcion inesperada  al probar la funcionalidad del UtilesTest: " << ex.what () << endl;
		bRes = false;
	}	
	catch ( ... )
	{
		cout << "Terminado con throwable inesperado" << endl;
		bRes = false;
	}	
	return( bRes );
}

bool TestVerificarFichero01 ()
{
	cout << "Test VerificarFichero01: " << endl;
	bool bRes = true;
	try
	{
		string sDir = DirectorioActual() + "/../../test-classes/data";
		bool bRes1 = true;
		string sFic = sDir + "/noexiste.txt";
		VerificarExistenciaFichero ( sFic, bRes1 );
		if ( bRes1 )
		{
			cout << "Error caso 1: Resultado incorrecto" << endl;
			bRes = false;
		}
		bRes1 = true;
		sFic = sDir + "/test1.txt";
		VerificarExistenciaFichero ( sFic, bRes1 );
		if ( !bRes1 )
		{
			cout << "Error caso 2: Resultado incorrecto" << endl;
			bRes = false;
		}
	}
	catch ( const exception & ex )
	{
		cout << "Excepcion inesperada  al probar la funcionalidad del UtilesTest: " << ex.what () << endl;
		bRes = false;
	}	
	catch ( ... )
	{
		cout << "Terminado con throwable inesperado" << endl;
		bRes = false;
	}	
	return( bRes );
}

bool TestVerificarFichero02 ()
{
	cout << "Test VerificarFichero02: " << endl;
	bool bRes = true;
	try
	{
		string sDir = DirectorioActual() + "/../../test-classes/data";
		bool bRes1 = true;
		string sFic = sDir + "/test1.txt";
		VerificarFichero ( sFic, 0, bRes1 );
		if ( !bRes1 )
		{
			cout << "Error caso 1: Resultado incorrecto" << endl;
			bRes = false;
		}
		bRes1 = true;
		VerificarFichero ( sFic, 1, bRes1 );
		if ( bRes1 )
		{
			cout << "Error caso 2: Resultado incorrecto" << endl;
			bRes = false;
		}
		bRes1 = true;
		sFic = sDir + "/test2.txt";
		VerificarFichero ( sFic, 3, bRes1 );
		if ( !bRes1 )
		{
			cout << "Error caso 3: Resultado incorrecto" << endl;
			bRes = false;
		}
	}
	catch ( const exception & ex )
	{
		cout << "Excepcion inesperada  al probar la funcionalidad del UtilesTest: " << ex.what () << endl;
		bRes = false;
	}	
	catch ( ... )
	{
		cout << "Terminado con throwable inesperado" << endl;
		bRes = false;
	}	
	return( bRes );
}

bool TestVerificarFichero03 ()
{
	cout << "Test VerificarFichero03: " << endl;
	bool bRes = true;
	try
	{
		string sDir = DirectorioActual() + "/../../test-classes/data";
		bool bRes1 = true;
		string sFic = sDir + "/test1.txt";
		vector<string> vecLineas;
		VerificarFichero ( sFic, vecLineas, bRes1 );
		if ( !bRes1 )
		{
			cout << "Error caso 1: Resultado incorrecto" << endl;
			bRes = false;
		}
		bRes1 = true;
		sFic = sDir + "/test2.txt";
		VerificarFichero ( sFic, vecLineas, bRes1 );
		if ( bRes1 )
		{
			cout << "Error caso 2: Resultado incorrecto" << endl;
			bRes = false;
		}
		bRes1 = true;
		vecLineas.push_back( "Esto es un test" );
		vecLineas.push_back( "" );
		vecLineas.push_back( "Viva el surf!" );
		VerificarFichero ( sFic, vecLineas, bRes1 );
		if ( !bRes1 )
		{
			cout << "Error caso 3: Resultado incorrecto" << endl;
			bRes = false;
		}
	}
	catch ( const exception & ex )
	{
		cout << "Excepcion inesperada  al probar la funcionalidad del UtilesTest: " << ex.what () << endl;
		bRes = false;
	}	
	catch ( ... )
	{
		cout << "Terminado con throwable inesperado" << endl;
		bRes = false;
	}	
	return( bRes );
}

bool TestVerificarFichero04 ()
{
	cout << "Test VerificarFichero04: " << endl;
	bool bRes = true;
	try
	{
		string sDir = DirectorioActual() + "/../../test-classes/data";
		bool bRes1 = true;
		string sFic = sDir + "/test1.txt";
		VerificarFichero ( sFic, "", bRes1 );
		if ( !bRes1 )
		{
			cout << "Error caso 1: Resultado incorrecto" << endl;
			bRes = false;
		}
		bRes1 = true;
		sFic = sDir + "/test2.txt";
		VerificarFichero ( sFic, "", bRes1 );
		if ( bRes1 )
		{
			cout << "Error caso 2: Resultado incorrecto" << endl;
			bRes = false;
		}
		bRes1 = true;
		VerificarFichero ( sFic, "Esto es un test\n\nViva el surf!\n", bRes1 );
		if ( !bRes1 )
		{
			cout << "Error caso 3: Resultado incorrecto" << endl;
			bRes = false;
		}
	}
	catch ( const exception & ex )
	{
		cout << "Excepcion inesperada  al probar la funcionalidad del UtilesTest: " << ex.what () << endl;
		bRes = false;
	}	
	catch ( ... )
	{
		cout << "Terminado con throwable inesperado" << endl;
		bRes = false;
	}	
	return( bRes );
}

bool TestUtilesTest ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test UtilesTest]" << ANSI::RESETEAR << endl;
	LogIniConsola ();
	if ( TestVerificarValor01 () &&
			TestVerificarValor02 () &&
			TestVerificarValor03 () &&
			TestEsNuloNoEsNulo01 () &&
			TestEsCiertoEsFalso01 () &&
			TestVerificarFichero01 () &&
			TestVerificarFichero02 () &&
			TestVerificarFichero03 () &&
			TestVerificarFichero04 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	} 
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	LogFin ();
	return ( bRes );
}
