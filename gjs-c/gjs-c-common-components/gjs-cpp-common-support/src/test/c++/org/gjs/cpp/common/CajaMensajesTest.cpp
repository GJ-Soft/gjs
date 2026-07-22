#include "CppCommonSupport.h"
#include <CppBase.h>

#include <CajaMensajes.h>
#include <SimulacionUsuarioConsola.h>

#include <iostream>


using namespace std;
using namespace org::gjs::cpp::common;




static bool TestCajMsjEnum01 ()
{
	cout << "Test CajaMensajes enum 01:" << endl;
	bool bRes = true;

	if ( (int) TipoCajaMensajes::Informacion != 0 )
	{
		cout << "Error caso 1: Informacion deberia valer 0" << endl;
		bRes = false;
	}
	if ( (int) TipoCajaMensajes::Error != 9 )
	{
		cout << "Error caso 2: Error deberia valer 9" << endl;
		bRes = false;
	}
	// Los tipos de error ( >= 9 ) se distinguen para el borde doble en POSIX.
	if ( ! ( (int) TipoCajaMensajes::ErrorReinCan >= (int) TipoCajaMensajes::Error ) )
	{
		cout << "Error caso 3: los tipos de error deberian ser >= Error" << endl;
		bRes = false;
	}
	if ( (int) RespuestaCajaMensajes::Ninguna != 0 )
	{
		cout << "Error caso 4: Respuesta Ninguna deberia valer 0" << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestCajMsjDefensivo01 ()
{
	cout << "Test CajMsjMostrar defensivo ( tipo invalido ) 01:" << endl;
	bool bRes = true;

	// Ramas defensivas no bloqueantes ( en ambas plataformas ): un tipo invalido o
	// un mensaje vacio devuelven Ninguna sin abrir el dialogo ( WIN ) ni bloquear
	// en el getchar() ( POSIX ).
	if ( CajMsjMostrar ( (TipoCajaMensajes) 99, "Titulo", "Mensaje" ) != RespuestaCajaMensajes::Ninguna )
	{
		cout << "Error caso 1: con tipo invalido se esperaba Ninguna" << endl;
		bRes = false;
	}
	if ( CajMsjMostrarConFormato ( (TipoCajaMensajes) 99, "Titulo", "Valor: {}", 7 ) != RespuestaCajaMensajes::Ninguna )
	{
		cout << "Error caso 2: con tipo invalido ( con formato ) se esperaba Ninguna" << endl;
		bRes = false;
	}
	// Mensaje vacio con tipo valido -> Ninguna ( igualado a la rama WIN ).
	if ( CajMsjMostrar ( TipoCajaMensajes::Informacion, "Titulo", "" ) != RespuestaCajaMensajes::Ninguna )
	{
		cout << "Error caso 3: con mensaje vacio se esperaba Ninguna" << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestCajMsjPositivo01 ()
{
	cout << "Test CajMsjMostrar positivo ( entrada simulada ) 01:" << endl;
	bool bRes = true;

	// En POSIX, CajMsjMostrar imprime la caja y bloquea con getchar(). Se simula
	// que el usuario pulsa <retorno> para probar el camino de exito. En WIN la
	// caja es un dialogo modal ( MessageBox ), que no se puede simular asi.
#if ( !defined ( WIN ) )
	if ( ! SimularEntradaConsola ( "" ) )
	{
		cout << "Error caso 0: no se pudo preparar la entrada simulada" << endl;
		bRes = false;
	}
	else
	{
		if ( CajMsjMostrar ( TipoCajaMensajes::Informacion, "Titulo", "Mensaje de prueba" ) != RespuestaCajaMensajes::Aceptar )
		{
			cout << "Error caso 1: se esperaba Aceptar al mostrar la caja de informacion" << endl;
			bRes = false;
		}
		RestaurarEntradaConsola ();
	}
	// Variante con formato ( ademas de instanciar/enlazar la plantilla, se ejecuta ).
	if ( ! SimularEntradaConsola ( "" ) )
	{
		cout << "Error caso 2: no se pudo preparar la entrada simulada ( formato )" << endl;
		bRes = false;
	}
	else
	{
		if ( CajMsjMostrarConFormato ( TipoCajaMensajes::Aviso, "Aviso", "Valor: {}", 7 ) != RespuestaCajaMensajes::Aceptar )
		{
			cout << "Error caso 3: se esperaba Aceptar con la caja con formato" << endl;
			bRes = false;
		}
		RestaurarEntradaConsola ();
	}
#endif
	return ( bRes );
}

static bool TestCajMsjError01 ()
{
	cout << "Test CajMsjMostrar error ( borde doble, entrada simulada ) 01:" << endl;
	bool bRes = true;

	// Un tipo de error se dibuja con borde doble; se simula <retorno> igual que en
	// el caso positivo para no bloquear en el getchar() de POSIX.
#if ( !defined ( WIN ) )
	if ( ! SimularEntradaConsola ( "" ) )
	{
		cout << "Error caso 0: no se pudo preparar la entrada simulada" << endl;
		bRes = false;
	}
	else
	{
		if ( CajMsjMostrar ( TipoCajaMensajes::Error, "Error", "Algo ha fallado" ) != RespuestaCajaMensajes::Aceptar )
		{
			cout << "Error caso 1: se esperaba Aceptar al mostrar la caja de error" << endl;
			bRes = false;
		}
		RestaurarEntradaConsola ();
	}
#endif
	return ( bRes );
}



bool TestCajaMensajes ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test CajaMensajes]" << ANSI::RESETEAR << endl;

	if ( TestCajMsjEnum01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}

	if ( TestCajMsjDefensivo01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}

	if ( TestCajMsjPositivo01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}

	if ( TestCajMsjError01 () )
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
