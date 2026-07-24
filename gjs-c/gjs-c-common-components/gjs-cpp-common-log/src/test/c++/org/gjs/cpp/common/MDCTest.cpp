#include "MDC.h"

#include <CppBase.h>

#include <iostream>
#include <filesystem>



using namespace std;
using namespace org::gjs::cpp::common;
using namespace org::gjs::cpp::common::MDC;




bool TestMDC01 ()
{
	cout << "Test MDC01: " << endl;
	bool bRes = true;
	try
	{
		string sClave1 ( "Clave1" );
		string sClave2 ( "Clave2" );
		string sValor1 ( "Valor1" );
		string sValor2 ( "Valor2" );

		MDCLimpiar ();

		string sValorRet = MDCRecuperar( sClave1 );
		if ( sValorRet.size () > 0 )
		{
			cout << "No deberia haberse recuperado ningun valor para [" << sClave1 << "]" << endl;
			bRes = false;
		}

		MDCGuardar ( sClave1, sValor1 );
		sValorRet = MDCRecuperar( sClave1 );
		if ( sValorRet != sValor1 )
		{
			cout << "Caso 1: Se ha recuperado un valor erroneo para [" << sClave1 << "]=[" << sValorRet << "]" << endl;
			bRes = false;
		}
		MDCGuardar ( sClave1, "" );
		sValorRet = MDCRecuperar( sClave1 );
		if ( sValorRet.size () > 0 )
		{
			cout << "Caso 2: Se ha recuperado un valor erroneo para [" << sClave1 << "]=[" << sValorRet << "]" << endl;
			bRes = false;
		}
		MDCGuardar ( sClave1, sValor1 );
		MDCGuardar ( sClave2, sValor2 );
		sValorRet = MDCRecuperar( sClave2 );
		if ( sValorRet != sValor2 )
		{
			cout << "Caso 3: Se ha recuperado un valor erroneo para [" << sClave2 << "]=[" << sValorRet << "]" << endl;
			bRes = false;
		}
		MDCEliminar ( sClave1 );
		sValorRet = MDCRecuperar( sClave1 );
		if ( sValorRet.size () > 0 )
		{
			cout << "Caso 4: Se ha recuperado un valor erroneo para [" << sClave1 << "]=[" << sValorRet << "]" << endl;
			bRes = false;
		}
		sValorRet = MDCRecuperar( sClave2 );
		if ( sValorRet != sValor2 )
		{
			cout << "Caso 5: Se ha recuperado un valor erroneo para [" << sClave2 << "]=[" << sValorRet << "]" << endl;
			bRes = false;
		}
		MDCLimpiar ();
		sValorRet = MDCRecuperar( sClave2 );
		if ( sValorRet.size () > 0 )
		{
			cout << "Caso 6: Se ha recuperado un valor erroneo para [" << sClave2 << "]=[" << sValorRet << "]" << endl;
			bRes = false;
		}
	}
	catch ( const exception & ex )
	{
		cout << "Error al probar la funcionalidad del MDC: " << ex.what () << endl;
		bRes = false;
	}
	return( bRes );
}



bool TestMDC ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test MDC]" << ANSI::RESETEAR << endl;
	if ( TestMDC01 () )
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
