#include "CppCommonTypes.h"




using namespace std;
using namespace org::gjs::cpp::common;




static bool TestPtr01 ()
{
	cout << "Test Ptr 01:" << endl;
	bool bRes = true;

	try
	{
		Ptr<string> * ptr = new Ptr<string>();
		if ( ptr->EsValido() || 
			 ( ptr->getDatos() != NULL ) )
		{
			cout << "Error caso 1" << endl;
			bRes = false;
		}
		ptr->setDatos( new string( "DATO" ) ); 
		if ( !ptr->EsValido() || 
			 ( ptr->getDatos() == NULL ) )
		{
			cout << "Error caso 2" << endl;
			bRes = false;
		}
		delete ptr;
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

static bool TestPtr02 ()
{
	cout << "Test Ptr 02:" << endl;
	bool bRes = true;

	try
	{
		Ptr<string> ptr( new string( "DATO" ) );
		if ( !ptr.EsValido() || 
			 ( ptr.getDatos() == NULL ) )
		{
			cout << "Error caso 1" << endl;
			bRes = false;
		}
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


typedef struct 
{
	int i;
	char c;
} TipoTest;


static bool TestPtr03 ()
{
	cout << "Test Ptr 03:" << endl;
	bool bRes = true;

	try
	{
		Ptr<TipoTest> * ptr = new Ptr<TipoTest>();
		if ( ptr->EsValido() || 
			 ( ptr->getDatos() != NULL ) )
		{
			cout << "Error caso 1" << endl;
			bRes = false;
		}
		TipoTest tipoTest;
		tipoTest.i = 1;
		tipoTest.c = 'a';
		ptr->setDatos( &tipoTest ); 
		if ( !ptr->EsValido() || 
			 ( ptr->getDatos() == NULL ) ||
			 ( ptr->getDatos()->i != 1 ) )
		{
			cout << "Error caso 2" << endl;
			bRes = false;
		}
		// Esta en el Heap porque el dato interno lo esta
		//delete ptr;
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

class ClaseTest
{
	public:
	int i;
	char c;
};


static bool TestPtr04 ()
{
	cout << "Test Ptr 04:" << endl;
	bool bRes = true;

	try
	{
		Ptr<ClaseTest> * ptr = new Ptr<ClaseTest>();
		if ( ptr->EsValido() || 
			 ( ptr->getDatos() != NULL ) )
		{
			cout << "Error caso 1" << endl;
			bRes = false;
		}
		ClaseTest * tipoTest = new ClaseTest();
		tipoTest->i = 1;
		tipoTest->c = 'a';
		ptr->setDatos( tipoTest ); 
		if ( !ptr->EsValido() || 
			 ( ptr->getDatos() == NULL ) ||
			 ( ptr->getDatos()->i != 1 ) )
		{
			cout << "Error caso 2" << endl;
			bRes = false;
		}
		// Esta en el Heap porque el dato interno lo esta
		// delete ptr;
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


static bool _bTestPtr05Res = false;
static bool _bTestPtr05Int = false;

void SignalHandlerTestPtr05( int signal )
{
	cout << "INTERRUPCION RECIBIDA=" << signal << endl;
	_bTestPtr05Int = true;
	//RetornarAPrograma();
}
	

static void TestPtr05 ()
{
	cout << "Test Ptr 05 (En Hilo separado):" << endl;
	_bTestPtr05Res = true;
	try
	{
		string * dato = new string( "DATO" ); 
		Ptr<string> * ptr = new Ptr<string>( dato, false );
		if ( ! ptr->EsValido() || 
			 ( ptr->getDatos() == NULL ) )
		{
			cout << "Error caso 1: Valido=" << ToString( ptr->EsValido() ) << endl;
			_bTestPtr05Res = false;
		}
		delete ptr;
		cout << "Liberado caso 1: [" << *dato << "]" << endl;
	}
	catch ( exception & ex )
	{
		cout << "Se ha producido una excepcion :" << ex.what () << endl;
		_bTestPtr05Res = false;
	}
	catch ( ... )
	{
		cout << "Excepcion indefinida" << endl;
		_bTestPtr05Res = false;
	}
	EstablecerManejadorInterrupciones ( SignalHandlerTestPtr05 );	
	try
	{
		string * dato = new string( "DATO" ); 
		Ptr<string> * ptr = new Ptr<string>( dato, true );
		if ( ! ptr->EsValido() || 
			 ( ptr->getDatos() == NULL ) )
		{
			cout << "Error caso 2: Valido=" << ToString( ptr->EsValido() ) << endl;
			_bTestPtr05Res = false;
		}
		delete ptr;
		cout << "Liberado caso 2: [" << dato << "]" << endl;
		//delete dato; // --> Esto provoca un SIBABRT !!
		//cout << "Error: deberia haberse producido un SIGABRT" << endl;
		//_bTestPtr05Res = false;
	}
	catch ( exception & ex )
	{
		cout << "Se ha producido una excepcion :" << ex.what () << endl;
		_bTestPtr05Res = false;
	}
	catch ( ... )
	{
		cout << "Excepcion indefinida" << endl;
		_bTestPtr05Res = false;
	}
}


bool TestPtr ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test Ptr]" << ANSI::RESETEAR << endl;
	if ( TestPtr01() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestPtr02() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestPtr03() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestPtr04() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	thread hiloTestPtr05( TestPtr05 );
	hiloTestPtr05.join();
	cout << "Hilo terminado" << endl;
	LimpiarManejadorInterrupciones ();	
	if ( _bTestPtr05Res && !_bTestPtr05Int )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		cout  << ToString( _bTestPtr05Res ) << endl;
		cout  << ToString( _bTestPtr05Int ) << endl;
		bRes = false;
	}
	cout << ANSI::AMARILLO << "[Fin]" << ANSI::RESETEAR << endl;	
	return ( bRes );
}
