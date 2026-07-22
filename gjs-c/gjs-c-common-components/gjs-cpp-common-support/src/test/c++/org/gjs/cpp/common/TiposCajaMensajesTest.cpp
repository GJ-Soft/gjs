#include "CppCommonSupport.h"
#include <CppBase.h>

#include <TiposCajaMensajes.h>

#include <iostream>


using namespace std;
using namespace org::gjs::cpp::common;




static bool TestTipCajMsjValidoInt01 ()
{
	cout << "Test TipCajMsjEsValido ( int ) 01:" << endl;
	bool bRes = true;

	if ( ! TipCajMsjEsValido ( TIP_CAJ_MSJ_INFORMACION ) )
	{
		cout << "Error caso 1: INFORMACION deberia ser valido" << endl;
		bRes = false;
	}
	if ( ! TipCajMsjEsValido ( TIP_CAJ_MSJ_ERROR_ABRREINIGN ) )
	{
		cout << "Error caso 2: ERROR_ABRREINIGN ( 12 ) deberia ser valido" << endl;
		bRes = false;
	}
	if ( TipCajMsjEsValido ( 13 ) )
	{
		cout << "Error caso 3: 13 esta fuera de rango, no deberia ser valido" << endl;
		bRes = false;
	}
	if ( TipCajMsjEsValido ( -1 ) )
	{
		cout << "Error caso 4: -1 no deberia ser valido" << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestTipCajMsjValidoEnum01 ()
{
	cout << "Test TipCajMsjEsValido ( enum ) 01:" << endl;
	bool bRes = true;

	if ( ! TipCajMsjEsValido ( TipoCajaMensajes::Informacion ) )
	{
		cout << "Error caso 1: TipoCajaMensajes::Informacion deberia ser valido" << endl;
		bRes = false;
	}
	if ( ! TipCajMsjEsValido ( TipoCajaMensajes::Error ) )
	{
		cout << "Error caso 2: TipoCajaMensajes::Error deberia ser valido" << endl;
		bRes = false;
	}
	// Un valor fuera del enumerado ( forzado por casting ) no es valido.
	if ( TipCajMsjEsValido ( (TipoCajaMensajes) 99 ) )
	{
		cout << "Error caso 3: un tipo fuera de rango no deberia ser valido" << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestTipCajMsjEnumValores01 ()
{
	cout << "Test valores del enum 01:" << endl;
	bool bRes = true;

	// Los enum class deben coincidir con los #define ( compatibilidad ).
	if ( (int) TipoCajaMensajes::Informacion != TIP_CAJ_MSJ_INFORMACION )
	{
		cout << "Error caso 1: Informacion deberia valer TIP_CAJ_MSJ_INFORMACION" << endl;
		bRes = false;
	}
	if ( (int) TipoCajaMensajes::Error != TIP_CAJ_MSJ_ERROR )
	{
		cout << "Error caso 2: Error deberia valer TIP_CAJ_MSJ_ERROR ( 9 )" << endl;
		bRes = false;
	}
	if ( (int) TipoCajaMensajes::ErrorAbrReinIgn != 12 )
	{
		cout << "Error caso 3: ErrorAbrReinIgn deberia valer 12" << endl;
		bRes = false;
	}
	// Respuesta: Ninguna es el valor cero ( "no mostrada / invalida" ).
	if ( (int) RespuestaCajaMensajes::Ninguna != 0 )
	{
		cout << "Error caso 4: RespuestaCajaMensajes::Ninguna deberia valer 0" << endl;
		bRes = false;
	}
	return ( bRes );
}



bool TestTiposCajaMensajes ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test TiposCajaMensajes]" << ANSI::RESETEAR << endl;

	if ( TestTipCajMsjValidoInt01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}

	if ( TestTipCajMsjValidoEnum01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}

	if ( TestTipCajMsjEnumValores01 () )
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
