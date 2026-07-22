#include "CppCommonSystem.h"
#include <CppBase.h>

#include <SistemaInformacion.h>
#include <TiposSistema.h>

#include <iostream>


using namespace std;
using namespace org::gjs::cpp::common;




static bool TestSisInformacion01 ()
{
	cout << "Test SisInformacion 01:" << endl;
	bool bRes = true;

	try
	{
		// Los predicados de tipo de sistema son coherentes con SisTipo().
		int iTipo = SisTipo ();
		if ( SisEsPosix () != ( iTipo == TIP_SIS_POSIX ) )
		{
			cout << "Error caso 1: SisEsPosix incoherente con SisTipo()" << endl;
			bRes = false;
		}
		if ( SisEsWindows () != ( iTipo == TIP_SIS_WINDOWS ) )
		{
			cout << "Error caso 2: SisEsWindows incoherente con SisTipo()" << endl;
			bRes = false;
		}
		if ( SisEsDos () != ( iTipo == TIP_SIS_DOS ) )
		{
			cout << "Error caso 3: SisEsDos incoherente con SisTipo()" << endl;
			bRes = false;
		}
		if ( SisEsMackintosh () != ( iTipo == TIP_SIS_MACKINTOSH ) )
		{
			cout << "Error caso 4: SisEsMackintosh incoherente con SisTipo()" << endl;
			bRes = false;
		}

		// El tamano de pagina de memoria es positivo.
		if ( SisTamPagina () == 0 )
		{
			cout << "Error caso 5: el tamano de pagina deberia ser positivo" << endl;
			bRes = false;
		}
		// Al menos un procesador.
		if ( SisNumProcesadores () < 1 )
		{
			cout << "Error caso 6: deberia haber al menos un procesador: " << SisNumProcesadores () << endl;
			bRes = false;
		}

		// Llamadas defensivas ( el valor depende del SO, solo se comprueba que no lanzan ).
		cout << "Version                  : " << SisVersion () << endl;
		cout << "Arquitectura             : " << SisArquitecturaProcesador () << endl;
		cout << "Procesador               : " << SisProcesador () << endl;
		cout << "IntegraGUI               : " << SisIntegraGUI () << endl;
		cout << "PermiteBifurcarProcesos  : " << SisPermiteBifurcarProcesos () << endl;
		cout << "VelocidadCPU             : " << SisVelocidadCPU () << endl;
		cout << "MenTamBloqueMinimo       : " << SisMemTamBloqueMinimo () << endl;
		
		// SisDirectorioTemporal devuelve un string reservado ( o NULL ): liberar si es valido.
		string * p_sDirTmp = SisDirectorioTemporal ();
		if ( p_sDirTmp != NULL )
		{
			cout << "SisDirectorioTemporal       : " << p_sDirTmp << endl;
			delete p_sDirTmp;
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



bool TestSistemaInformacion ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test SistemaInformacion]" << ANSI::RESETEAR << endl;
	if ( TestSisInformacion01 () )
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
