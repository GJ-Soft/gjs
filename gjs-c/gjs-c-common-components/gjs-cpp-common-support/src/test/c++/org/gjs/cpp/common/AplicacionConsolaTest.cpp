#include "CppCommonSupport.h"
#include <CppBase.h>

#include <AplicacionConsola.h>

#include <iostream>


using namespace std;
using namespace org::gjs::cpp::common;


// NOTA: no se abre la consola ( AplicConAbrir redirige a /dev/tty y las lecturas
// son bloqueantes ). Se comprueban el estado inicial y la VALIDACION geometrica
// de las rutinas de dibujo, que con la consola cerrada usan el ancho efectivo
// por defecto ( CON_ANCHO_DEFECTO = 80 ).


static bool TestAplicConEstado01 ()
{
	cout << "Test AplicacionConsola estado 01:" << endl;
	bool bRes = true;

	if ( AplicConEstaAbierta () )
	{
		cout << "Error caso 1: la consola no deberia estar abierta al inicio" << endl;
		bRes = false;
	}
	// Con la consola cerrada, el ancho consultado es 0.
	if ( AplicConAncho () != 0 )
	{
		cout << "Error caso 2: con la consola cerrada AplicConAncho deberia ser 0" << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestAplicConDibujarLinea01 ()
{
	cout << "Test AplicConDibujarLinea ( geometria, ancho efectivo 80 ) 01:" << endl;
	bool bRes = true;

	// Casos validos ( se dibuja; anadimos endl para no ensuciar la salida ).
	if ( ! AplicConDibujarLineaExt ( 10, 0, '-' ) )
	{
		cout << endl << "Error caso 1: ( 10, 0 ) deberia ser valido" << endl;
		bRes = false;
	}
	cout << endl;
	// Limite justo: 80 + 0 <= 80 ( con el off-by-one antiguo < 80 fallaba ).
	if ( ! AplicConDibujarLineaExt ( 80, 0, '-' ) )
	{
		cout << endl << "Error caso 2: ( 80, 0 ) deberia ser valido ( limite )" << endl;
		bRes = false;
	}
	cout << endl;
	if ( ! AplicConDibujarLinea ( '=' ) )
	{
		cout << endl << "Error caso 3: AplicConDibujarLinea de ancho completo deberia ser valido" << endl;
		bRes = false;
	}
	cout << endl;

	// Casos invalidos ( no dibujan nada ).
	if ( AplicConDibujarLineaExt ( 81, 0, '-' ) )
	{
		cout << "Error caso 4: ( 81, 0 ) excede el ancho, deberia ser invalido" << endl;
		bRes = false;
	}
	if ( AplicConDibujarLineaExt ( 10, 75, '-' ) )
	{
		cout << "Error caso 5: ( 10, 75 ) -> 85 excede el ancho, invalido" << endl;
		bRes = false;
	}
	if ( AplicConDibujarLineaExt ( 0, 0, '-' ) )
	{
		cout << "Error caso 6: ancho 0 deberia ser invalido" << endl;
		bRes = false;
	}
	if ( AplicConDibujarLineaExt ( 10, -1, '-' ) )
	{
		cout << "Error caso 7: columna inicial negativa deberia ser invalido" << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestAplicConDibujarRectangulo01 ()
{
	cout << "Test AplicConDibujarRectangulo ( geometria ) 01:" << endl;
	bool bRes = true;

	if ( ! AplicConDibujarRectangulo ( 3, 20, 0 ) )
	{
		cout << endl << "Error caso 1: ( 3, 20, 0 ) deberia ser valido" << endl;
		bRes = false;
	}
	cout << endl;
	if ( ! AplicConDibujarRectanguloDoble ( 4, 30, 0 ) )
	{
		cout << endl << "Error caso 2: rectangulo doble ( 4, 30, 0 ) deberia ser valido" << endl;
		bRes = false;
	}
	cout << endl;

	// Invalidos ( minimo 2x2 y dentro del ancho ).
	if ( AplicConDibujarRectangulo ( 1, 20, 0 ) )
	{
		cout << "Error caso 3: alto 1 deberia ser invalido" << endl;
		bRes = false;
	}
	if ( AplicConDibujarRectangulo ( 3, 1, 0 ) )
	{
		cout << "Error caso 4: ancho 1 deberia ser invalido" << endl;
		bRes = false;
	}
	if ( AplicConDibujarRectangulo ( 3, 20, 65 ) )
	{
		cout << "Error caso 5: ( 3, 20, 65 ) -> 85 excede el ancho, invalido" << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestAplicConLineasBorde01 ()
{
	cout << "Test AplicConDibujarLineaSimple/Doble 01:" << endl;
	bool bRes = true;

	// Estas variantes exigen consola abierta ( se apoyan en el ancho real );
	// con la consola cerrada deben devolver false sin escribir nada.
	if ( AplicConDibujarLineaSimple () )
	{
		cout << "Error caso 1: LineaSimple con la consola cerrada deberia ser false" << endl;
		bRes = false;
	}
	if ( AplicConDibujarLineaDoble () )
	{
		cout << "Error caso 2: LineaDoble con la consola cerrada deberia ser false" << endl;
		bRes = false;
	}
	return ( bRes );
}



bool TestAplicacionConsola ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test AplicacionConsola]" << ANSI::RESETEAR << endl;

	if ( TestAplicConEstado01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}

	if ( TestAplicConDibujarLinea01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}

	if ( TestAplicConDibujarRectangulo01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}

	if ( TestAplicConLineasBorde01 () )
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
