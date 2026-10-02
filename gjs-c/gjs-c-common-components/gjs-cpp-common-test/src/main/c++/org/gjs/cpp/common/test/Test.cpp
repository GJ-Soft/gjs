#include "CppTestConfig.h"
#include "Test.h"

#include <signal.h>
#include <stdexcept>



using namespace std;
using namespace org::gjs::cpp::common::log;
using namespace org::gjs::cpp::common;



namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {
				namespace test
				{

extern void _PrepararContexto();
extern void _LiberarContexto();

		
static void SignalHandler( int signal )
{
    throw runtime_error ( Concatenar ( "RECIBIDA INTERRUPCION = ", ToString( signal ) ).c_str() );
}		

static bool _bEntornoTestInicializado = false;

static void InicializarEntorno()
{
	if ( !_bEntornoTestInicializado )
	{
		EstablecerManejadorInterrupciones( SignalHandler );
		_PrepararContexto();
		_bEntornoTestInicializado = true;
	}
}
	
	
Test::Test ( const string & sNombre, PROCEDIMIENTO procInicializar, PROCEDIMIENTO procFinalizar, PROCEDIMIENTO_1CAD procInicializarCaso, PROCEDIMIENTO_1CAD procFinalizarCaso )
{
	LogFin();
	// TODO: Establecer metodología estándar de definición de Log en test: 1) buscar un xml de definicion en un /config...
	LogIni();
	sNombreTest = sNombre;
	procInicializarTest = procInicializar;
	procFinalizarTest = procFinalizar;
	procInicializarCasoTest = procInicializarCaso;
	procFinalizarCasoTest = procFinalizarCaso;
	InicializarEntorno();
}

Test::~Test ()
{
	for ( CasoTest * caso : listCasos )
	{
		delete caso;
	}
	listCasos.clear();
	LogFin();
}

void Test::Inicializar()
{
	LogInfo( "" );
	LogInfo( Concatenar ( ToString( "* Iniciando test " ), sNombreTest , ToString( ":" ) ) );
	sDirInicial = DirectorioActual();
	if ( procInicializarTest != NULL )
	{
		procInicializarTest ();
	}
}

void Test::Finalizar()
{
	if ( procFinalizarTest != NULL )
	{
		procFinalizarTest ();
	}
	EstablecerDirectorio( sDirInicial );
	_LiberarContexto();
	LogInfo( "" );
	LogInfo( Concatenar ( ToString( "* Test " ), sNombreTest , ToString( " finalizado." ) ) );
}

void Test::InicializarCaso( const string & sId )
{
	if ( procInicializarCasoTest != NULL )
	{
		procInicializarCasoTest ( sId );
	}
}

void Test::FinalizarCaso( const string & sId )
{
	if ( procFinalizarCasoTest != NULL )
	{
		procFinalizarCasoTest ( sId );
	}
}

void Test::NuevoCaso( const string & sNombre, FUNCION_BOOL funcion )
{
	listCasos.push_back( new CasoTest ( sNombre, funcion ) );
}

void Test::NuevoCasoAislado( const string & sNombre, FUNCION_BOOL funcion, int iCodigoEsperado )
{
	listCasos.push_back( new CasoTestAislado( sNombre, funcion, iCodigoEsperado ) );
}

int Test::NumCasos()
{
	return ( listCasos.size() );
}


bool Test::Ejecutar()
{
	bool bRes = true;
	bResultado = false;
	iEjecutados = 0;
	iCorrectos = 0;
	iErroneos = 0;
	iFallidos = 0;
	iNoSoportados = 0;
	try
	{
		Inicializar();
		for ( CasoTest * caso : listCasos )
		{
			LogInfo ( "" );
			InicializarCaso( caso->getId() );
			ResultadoCasoTest rctRes = caso->Ejecutar ();
			FinalizarCaso( caso->getId() );
			iEjecutados = iEjecutados + 1;
			if ( rctRes == ResultadoCasoTest::OK )
			{
				iCorrectos = iCorrectos + 1;
			}
			else if ( rctRes == ResultadoCasoTest::KO )
			{
				iErroneos = iErroneos + 1;
				bRes = false;
			}
			else if ( rctRes == ResultadoCasoTest::NO_SOPORTADO )
			{
				iNoSoportados = iNoSoportados + 1;
			}
			else
			{
				iFallidos = iFallidos + 1;
				bRes = false;
			}
		}
		Finalizar ();
	}
	catch ( const exception& ex )
	{
		LogErrorEx ( "Error inesperado", ex );
		bRes = false;
	}
	catch ( ... )
	{
		LogError ( "Lanzado objeto inesperado" );
		bRes = false;
	}	
	LogInfo ( "" );
	LogInfo ( Concatenar ( "Ejecutados = ", ToString ( iEjecutados ), "/",  ToString ( listCasos.size() ), "; Correctos = ",  ToString ( iCorrectos ), 
							"; Erroneos = ",  ToString ( iErroneos ), "; Fallidos = ",  ToString ( iFallidos ),
							"; No soportados = ",  ToString ( iNoSoportados ) ) );
	LogInfo ( "" );
	if ( bRes ) 
	{
		LogInfo( "Test terminado correctamente" );
	}
	else
	{
		LogInfo( "Test terminado con erorres" );
	}
	LogInfo ( "" );
	bResultado = bRes;
	fflush ( stdout );
	return( bRes );
}		

bool Test::Resultado ()
{
	return ( bResultado );
}

int Test::CasosEjecutados ()
{
	return ( iEjecutados );
}

int Test::CasosCorrectos ()
{
	return ( iCorrectos );
}

int Test::CasosErroneos ()
{
	return ( iErroneos );
}

int Test::CasosFallidos ()
{
	return ( iFallidos );
}

int Test::CasosNoSoportados ()
{
	return ( iNoSoportados );
}
		
		
				}
			}
		}
	}
}