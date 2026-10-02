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
		// SisVersion puede devolver NULL en Windows nativo, y mandar un const char*
		// nulo a cout es comportamiento indefinido.
		const char * p_cVer = SisVersion ();
		cout << "Version                  : " << ( p_cVer != NULL ? p_cVer : "(no disponible)" ) << endl;
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
			cout << "SisDirectorioTemporal       : " << *p_sDirTmp << endl;
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



static bool TestSisOrdenBytes01 ()
{
	cout << "Test SisOrdenBytes 01:" << endl;
	bool bRes = true;

	int iOrden = SisOrdenBytes ();
	if ( ( iOrden != 0 ) && ( iOrden != 1 ) )
	{
		cout << "Error caso 1: orden de bytes no reconocido: " << iOrden << endl;
		bRes = false;
	}
	if ( SisOrdenBytesEsNormal () == SisOrdenBytesEsInvertido () )
	{
		cout << "Error caso 2: el orden no puede ser normal e invertido a la vez" << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestSisArquitectura01 ()
{
	cout << "Test SisArquitectura 01:" << endl;
	bool bRes = true;

	int iPalabra = SisTamPalabraMemoria ();
	if ( ( iPalabra != 4 ) && ( iPalabra != 8 ) )
	{
		cout << "Error caso 1: tamano de palabra inesperado: " << iPalabra << endl;
		bRes = false;
	}
	if ( SisEsArquitectura64Bits () == SisEsArquitectura32Bits () )
	{
		cout << "Error caso 2: no puede ser de 32 y de 64 bits a la vez" << endl;
		bRes = false;
	}
	if ( SisEsArquitectura64Bits () != ( iPalabra == 8 ) )
	{
		cout << "Error caso 3: EsArquitectura64Bits incoherente con el tamano de palabra" << endl;
		bRes = false;
	}
	if ( ! SisAdmiteSubprocesos () )
	{
		cout << "Error caso 4: se esperaba admision de subprocesos" << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestSisNombres01 ()
{
	cout << "Test SisNombres 01:" << endl;
	bool bRes = true;

	const char * p_cSistema = SisSistema ();
	if ( ( p_cSistema == NULL ) || ( p_cSistema [ 0 ] == 0 ) )
	{
		cout << "Error caso 1: se esperaba un nombre de sistema no vacio" << endl;
		bRes = false;
	}
	else
	{
		cout << "Sistema                  : " << p_cSistema << endl;
	}
	// SisVersion devuelve NULL en Windows nativo a proposito: aqui solo se
	// comprueba que, si contesta, no conteste con la cadena vacia.
	const char * p_cVersion = SisVersion ();
	if ( ( p_cVersion != NULL ) && ( p_cVersion [ 0 ] == 0 ) )
	{
		cout << "Error caso 2: la version no puede ser la cadena vacia" << endl;
		bRes = false;
	}
	return ( bRes );
}

// Comprobaciones de RANGO, no de valor: lo que devuelven estas depende de la
// maquina y de los limites del usuario. Lo que se verifica es que contesten algo
// plausible, no un cero por haberse ido por la rama que no toca.
static bool TestSisLimites01 ()
{
	cout << "Test SisLimites 01:" << endl;
	bool bRes = true;

	double dVelocidad = SisVelocidadCPU ();
	if ( ( dVelocidad < 100.0 ) || ( dVelocidad > 100000.0 ) )
	{
		cout << "Error caso 1: velocidad fuera de rango: " << dVelocidad << " MHz" << endl;
		bRes = false;
	}
#if ( defined ( POSIX ) )
	long lTotales = SisDescriptoresESTotalesProceso ();
	if ( lTotales <= 0 )
	{
		cout << "Error caso 2: se esperaban descriptores totales > 0: " << lTotales << endl;
		bRes = false;
	}
	long lUtilizados = SisDescriptoresESUtilizadosProceso ();
	if ( ( lUtilizados < 0 ) || ( lUtilizados > lTotales ) )
	{
		cout << "Error caso 3: descriptores usados fuera de rango: " << lUtilizados << endl;
		bRes = false;
	}
	long lDisponibles = SisDescriptoresESDisponiblesProceso ();
	if ( lDisponibles != ( lTotales - lUtilizados ) )
	{
		cout << "Error caso 4: disponibles no cuadra con totales menos usados" << endl;
		bRes = false;
	}
	if ( SisMaxNumProcesosPorUsuario () <= 0 )
	{
		cout << "Error caso 5: se esperaba un maximo de procesos > 0" << endl;
		bRes = false;
	}
	if ( SisMaxTamFicheroProceso () == 0 )
	{
		cout << "Error caso 6: se esperaba un maximo de tamano de fichero distinto de 0" << endl;
		bRes = false;
	}
	/* Los limites tienen tres respuestas: un valor, LONG_MAX ( sin limite ) y
	   -1 ( no se sabe ). El -1 NO vale aqui: getrlimit no falla en un sistema
	   sano, y hasta el 2026-09-19 estas dos lo devolvian en el caso normal,
	   porque el RLIM_INFINITY de getrlimit se convertia en -1 al pasarlo a
	   long. Este caso es el que impide que vuelva a pasar. */
	if ( SisMaxTamFicheroProceso () == -1 )
	{
		cout << "Error caso 7: SisMaxTamFicheroProceso dice que no lo sabe" << endl;
		bRes = false;
	}
	if ( SisMaxTiempoCPUProceso () == -1 )
	{
		cout << "Error caso 8: SisMaxTiempoCPUProceso dice que no lo sabe" << endl;
		bRes = false;
	}
#endif
	return ( bRes );
}

bool TestSistemaInformacion ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test SistemaInformacion]" << ANSI::RESETEAR << endl;
	if ( TestSisInformacion01 () &&
			TestSisOrdenBytes01 () &&
			TestSisArquitectura01 () &&
			TestSisNombres01 () &&
			TestSisLimites01 () )
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
