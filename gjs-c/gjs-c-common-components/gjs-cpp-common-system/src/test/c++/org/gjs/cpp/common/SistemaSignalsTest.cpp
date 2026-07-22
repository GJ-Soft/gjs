#include "CppCommonSystem.h"
#include <CppBase.h>

#include <SistemaSignals.h>

#include <iostream>


using namespace std;
using namespace org::gjs::cpp::common;




static bool TestSisSigDescripcion01 ()
{
	cout << "Test SisSigDescripcion 01:" << endl;
	bool bRes = true;

	try
	{
		// La descripcion mapea por id en cualquier plataforma.
		if ( SisSigDescripcion ( SIS_SIG_ABORTAR ) != SIS_SIG_TXT_ABORTAR )
		{
			cout << "Error caso 1: descripcion de ABORTAR incorrecta: [" << SisSigDescripcion ( SIS_SIG_ABORTAR ) << "]" << endl;
			bRes = false;
		}
		if ( SisSigDescripcion ( SIS_SIG_INTERRUPCION ) != SIS_SIG_TXT_INTERRUPCION )
		{
			cout << "Error caso 2: descripcion de INTERRUPCION incorrecta: [" << SisSigDescripcion ( SIS_SIG_INTERRUPCION ) << "]" << endl;
			bRes = false;
		}
		// Un id no reconocido devuelve cadena vacia.
		if ( ! SisSigDescripcion ( 9999 ).empty () )
		{
			cout << "Error caso 3: un id de senal invalido deberia dar cadena vacia" << endl;
			bRes = false;
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

static bool TestSisSigCodigos01 ()
{
	cout << "Test SisSigCodigos 01:" << endl;
	bool bRes = true;

	try
	{
		if ( SisSigEstanPermitidos () )
		{
			// El codigo de una senal base coincide con la constante del sistema.
			if ( SisSigCodigo ( SIS_SIG_ABORTAR ) != SIS_COD_SIG_ABORTAR )
			{
				cout << "Error caso 1: el codigo de ABORTAR es incorrecto" << endl;
				bRes = false;
			}
			// Una senal valida tiene codigo >= 0; una invalida no.
			if ( ! SisSigEsValida ( SIS_SIG_INTERRUPCION ) )
			{
				cout << "Error caso 2: INTERRUPCION deberia ser una senal valida" << endl;
				bRes = false;
			}
			if ( SisSigEsValida ( 9999 ) )
			{
				cout << "Error caso 3: 9999 no deberia ser una senal valida" << endl;
				bRes = false;
			}
			// Programable: la mayoria si, la finalizacion obligada ( SIGKILL ) no.
			if ( ! SisSigEsProgramable ( SIS_SIG_INTERRUPCION ) )
			{
				cout << "Error caso 4: INTERRUPCION deberia ser programable" << endl;
				bRes = false;
			}
			if ( SisSigEsProgramable ( SIS_SIG_FINALIZACION_OBLIGADA ) )
			{
				cout << "Error caso 5: la finalizacion obligada no deberia ser programable" << endl;
				bRes = false;
			}
			// Inversa codigo -> id ( estable para todas las senales, incluida ABORTAR ).
			if ( SisSigId ( SisSigCodigo ( SIS_SIG_INTERRUPCION ) ) != SIS_SIG_INTERRUPCION )
			{
				cout << "Error caso 6: la inversa codigo/id de INTERRUPCION deberia ser estable" << endl;
				bRes = false;
			}
			if ( SisSigId ( SisSigCodigo ( SIS_SIG_USUARIO_1 ) ) != SIS_SIG_USUARIO_1 )
			{
				cout << "Error caso 7: la inversa codigo/id de USUARIO_1 deberia ser estable" << endl;
				bRes = false;
			}
			if ( SisSigId ( SisSigCodigo ( SIS_SIG_ABORTAR ) ) != SIS_SIG_ABORTAR )
			{
				cout << "Error caso 8: la inversa codigo/id de ABORTAR deberia ser estable" << endl;
				bRes = false;
			}
		}
		else
		{
			// Plataforma sin senales ( p.ej. WIN ): las consultas dan -1/false.
			if ( SisSigCodigo ( SIS_SIG_ABORTAR ) != -1 )
			{
				cout << "Error caso 1: sin senales el codigo deberia ser -1" << endl;
				bRes = false;
			}
			if ( SisSigEsValida ( SIS_SIG_ABORTAR ) )
			{
				cout << "Error caso 2: sin senales ninguna es valida" << endl;
				bRes = false;
			}
			if ( SisSigEsProgramable ( SIS_SIG_INTERRUPCION ) )
			{
				cout << "Error caso 3: sin senales ninguna es programable" << endl;
				bRes = false;
			}
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



bool TestSistemaSignals ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test SistemaSignals]" << ANSI::RESETEAR << endl;
	if ( TestSisSigDescripcion01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestSisSigCodigos01 () )
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
