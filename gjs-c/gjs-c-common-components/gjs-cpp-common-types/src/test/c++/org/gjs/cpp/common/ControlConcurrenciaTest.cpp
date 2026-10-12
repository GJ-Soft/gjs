#include "CppCommonTypes.h"




using namespace std;
using namespace org::gjs::cpp::common;



class PruebaControlConcurrencia : ControlConcurrencia
{
private:
	int valor = 0;
	
public:
	void Sumar( int inc )
	{
		Bloquear();
		valor = valor + inc;
		Desbloquear();
	}
	
	int getValor()
	{
		return( valor );
	}
};

/* Expone el bloqueo para probar el anidado. */
class PruebaBloqueoAnidado : public ControlConcurrencia
{
public:
	void Entrar ()
	{
		Bloquear ();
	}

	void Salir ()
	{
		Desbloquear ();
	}
};

static PruebaControlConcurrencia _PruebaControlConcurrencia_test;
static bool _bFin_Hilo_Test_ControlConcurrencia1 = false;
static bool _bFin_Hilo_Test_ControlConcurrencia2 = false;


static void _Hilo_Test_ControlConcurrencia1()
{
	try
	{
		for( int i = 0; i < 10; i = i + 1 )
		{
			_PruebaControlConcurrencia_test.Sumar( 2 );
			Esperar( 100 );
		}
	}
	catch ( exception & ex )
	{
		cout << "Se ha producido una excepcion :" << ex.what () << endl;
	}
	catch ( ... )
	{
		cout << "Excepcion indefinida" << endl;
	}
	_bFin_Hilo_Test_ControlConcurrencia1 = true;
}

static void _Hilo_Test_ControlConcurrencia2()
{
	try
	{
		for( int i = 0; i < 10; i = i + 1 )
		{
			_PruebaControlConcurrencia_test.Sumar( - 1 );
			Esperar( 100 );
		}
	}
	catch ( exception & ex )
	{
		cout << "Se ha producido una excepcion :" << ex.what () << endl;
	}
	catch ( ... )
	{
		cout << "Excepcion indefinida" << endl;
	}
	_bFin_Hilo_Test_ControlConcurrencia2 = true;
}


static bool TestControlConcurrencia01 ()
{
	cout << "Test ControlConcurrencia 01:" << endl;
	bool bRes = true;

	try
	{
		thread thHilo1 ( _Hilo_Test_ControlConcurrencia1 );
		thread thHilo2 ( _Hilo_Test_ControlConcurrencia2 );
		while ( !_bFin_Hilo_Test_ControlConcurrencia1 || !_bFin_Hilo_Test_ControlConcurrencia2 )
		{
			cout << "Valor=" << _PruebaControlConcurrencia_test.getValor() << endl;
			Esperar( 20 );
		}
		thHilo1.join();
		thHilo2.join();
		bRes = ( _PruebaControlConcurrencia_test.getValor() == 10 );
	}
	catch ( exception & ex )
	{
		cout << "Se ha producido una excepcion :" << ex.what () << endl;
		bRes = false;
	}
	catch ( ... )
	{
		cout << "Excepcion indefinida" << endl;
		bRes = false;
	}
	return( bRes );
}

/* Un hilo bloquea dos veces y desbloquea una: sigue dentro, y otro hilo no
   puede entrar hasta el segundo desbloqueo. Antes el primer Desbloquear soltaba
   el cerrojo y el otro hilo entraba enseguida. */
static bool TestControlConcurrencia02 ()
{
	cout << "Test ControlConcurrencia 02:" << endl;
	bool bRes = true;
	PruebaBloqueoAnidado	bloqueo;
	atomic < bool >			bOtroDentro { false };

	bloqueo.Entrar ();
	bloqueo.Entrar ();
	bloqueo.Salir ();
	thread thOtro ( [ &bloqueo, &bOtroDentro ] () {
		bloqueo.Entrar ();
		bOtroDentro.store ( true );
		bloqueo.Salir ();
	} );
	Esperar ( 200 );
	if ( bOtroDentro.load () )
	{
		cout << "Error caso 1: otro hilo entro con el bloqueo exterior aun tomado" << endl;
		bRes = false;
	}
	bloqueo.Salir ();
	thOtro.join ();
	if ( ! bOtroDentro.load () )
	{
		cout << "Error caso 2: tras soltar el bloqueo exterior el otro hilo no entro" << endl;
		bRes = false;
	}
	return( bRes );
}

bool TestControlConcurrencia ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test ControlConcurrencia]" << ANSI::RESETEAR << endl;
	if ( TestControlConcurrencia01() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestControlConcurrencia02() )
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
