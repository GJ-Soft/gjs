#include "CppCommonTime.h"
#include <CppBase.h>

#include <Fecha.h>

#include <iostream>


using namespace std;
using namespace org::gjs::cpp::common;




static bool TestFechaConstruccion01 ()
{
	cout << "Test Fecha construccion / accesores 01:" << endl;
	bool bRes = true;

	Fecha fecObj ( 2008, 3, 25 );
	if ( ( fecObj.AAAA () != 2008 ) || ( fecObj.MM () != 3 ) || ( fecObj.DD () != 25 ) )
	{
		cout << "Error caso 1: accesores AAAA/MM/DD incorrectos" << endl;
		bRes = false;
	}
	if ( fecObj.Valor () != 20080325 )
	{
		cout << "Error caso 2: Valor() deberia ser 20080325 ( es " << fecObj.Valor () << " )" << endl;
		bRes = false;
	}
	if ( ! fecObj.EsValida () )
	{
		cout << "Error caso 3: 25/03/2008 deberia ser valida" << endl;
		bRes = false;
	}
	// Construccion desde long y desde string dan la misma fecha.
	Fecha fecLong ( (long) 20080325 );
	Fecha fecStr ( "20080325" );
	if ( ( fecLong.Valor () != 20080325 ) || ( fecStr.Valor () != 20080325 ) )
	{
		cout << "Error caso 4: construccion desde long/string incorrecta" << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestFechaEsValida01 ()
{
	cout << "Test Fecha EsValida ( retorno bool ) 01:" << endl;
	bool bRes = true;

	Fecha fecObj = Fecha ( 2010, 12, 31 );
	if ( !fecObj.EsValida () )
	{
		cout << "Error caso 1: deberia ser valida" << endl;
		bRes = false;
	}
	fecObj = Fecha ( 2010, 11, 31 );
	if ( fecObj.EsValida () )
	{
		cout << "Error caso 2: deberia ser invalida" << endl;
		bRes = false;
	}
	return ( bRes );
}


static bool TestFechaEstablecer01 ()
{
	cout << "Test Fecha Establecer ( retorno bool ) 01:" << endl;
	bool bRes = true;

	Fecha fecObj;
	// Establecer valido -> true.
	if ( ! fecObj.Establecer ( 2010, 12, 31 ) )
	{
		cout << "Error caso 1: Establecer(2010,12,31) deberia devolver true" << endl;
		bRes = false;
	}
	if ( fecObj.Valor () != 20101231 )
	{
		cout << "Error caso 2: Valor() deberia ser 20101231" << endl;
		bRes = false;
	}
	// Establecer invalido -> false ( 30 de febrero ).
	if ( fecObj.Establecer ( 2010, 2, 30 ) )
	{
		cout << "Error caso 3: Establecer(2010,2,30) deberia devolver false" << endl;
		bRes = false;
	}
	// Establecer desde long.
	if ( ! fecObj.Establecer ( (long) 19991231 ) || ( fecObj.Valor () != 19991231 ) )
	{
		cout << "Error caso 4: Establecer(long 19991231) incorrecto" << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestFechaComparacion01 ()
{
	cout << "Test Fecha comparaciones 01:" << endl;
	bool bRes = true;

	Fecha fecA ( 2008, 3, 25 );
	Fecha fecB ( 2008, 3, 26 );

	if ( ! fecA.EsMenor ( fecB ) || ! fecB.EsMayor ( fecA ) || ! fecA.EsDiferente ( fecB ) )
	{
		cout << "Error caso 1: EsMenor/EsMayor/EsDiferente incorrecto" << endl;
		bRes = false;
	}
	if ( ! fecA.EsIgual ( Fecha ( 2008, 3, 25 ) ) )
	{
		cout << "Error caso 2: EsIgual con una fecha equivalente deberia ser cierto" << endl;
		bRes = false;
	}
	if ( ! ( fecA < fecB ) || ( fecA >= fecB ) || ! ( fecA != fecB ) )
	{
		cout << "Error caso 3: operadores <, >=, != incorrectos" << endl;
		bRes = false;
	}
	// Sobrecarga por puntero: defensiva ante nulo.
	if ( fecA.EsIgual ( (Fecha *) NULL ) )
	{
		cout << "Error caso 4: EsIgual(NULL) deberia ser false" << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestFechaDiferencia01 ()
{
	cout << "Test Fecha Diferencia ( dias reales ) 01:" << endl;
	bool bRes = true;

	Fecha fecObj ( 2008, 3, 25 );
	// Un dia despues -> 1 dia.
	if ( fecObj.Diferencia ( Fecha ( 2008, 3, 26 ) ) != 1 )
	{
		cout << "Error caso 1: diferencia a un dia despues deberia ser 1" << endl;
		bRes = false;
	}
	// Un mes despues ( marzo tiene 31 dias ) -> 31 dias.
	if ( fecObj.Diferencia ( Fecha ( 2008, 4, 25 ) ) != 31 )
	{
		cout << "Error caso 2: 25/03 a 25/04 deberia ser 31 dias ( es "
			 << fecObj.Diferencia ( Fecha ( 2008, 4, 25 ) ) << " )" << endl;
		bRes = false;
	}
	// Misma fecha -> 0.
	if ( fecObj.Diferencia ( Fecha ( 2008, 3, 25 ) ) != 0 )
	{
		cout << "Error caso 3: la diferencia con la misma fecha deberia ser 0" << endl;
		bRes = false;
	}
	return ( bRes );
}



bool TestFecha ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test Fecha]" << ANSI::RESETEAR << endl;

	if ( TestFechaConstruccion01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	
	if ( TestFechaEsValida01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}

	if ( TestFechaEstablecer01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}

	if ( TestFechaComparacion01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}

	if ( TestFechaDiferencia01 () )
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
