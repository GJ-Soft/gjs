#include "CppTestConfig.h"
#include "CasoTest.h"


using namespace std;
using namespace org::gjs::cpp::common::log;


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

CasoTest::CasoTest ( const string & sId, FUNCION_BOOL funcion, bool bEsperaExcep )
{
	sIdCaso = sId;
	funcionCaso = funcion;
	bEsperaExcepcion = bEsperaExcep;
}

string CasoTest::getId()
{
	return( sIdCaso );
}

ResultadoCasoTest CasoTest::Ejecutar ()
{
	ResultadoCasoTest rctRes = ResultadoCasoTest::OK;
	LogInfo( "" );
	LogInfo ( Concatenar ( ToString( "- Caso " ), sIdCaso , ToString( ":" ) ) );
	try
	{
		if ( funcionCaso != NULL )
		{
			if ( ! funcionCaso() )
			{
				cout << "KO!!" << endl;
				rctRes = ResultadoCasoTest::KO;
			}
			if ( bEsperaExcepcion )
			{
				rctRes = ResultadoCasoTest::KO;
				LogError ( "Se esperaba excepcion para el caso" );
			}
		}
		else
		{
			LogError ( "Funcion no definida para el caso" );
			rctRes = ResultadoCasoTest::FAIL;
		}
	}
	catch ( const exception& ex )
	{
		if ( ! bEsperaExcepcion ) 
		{
			LogFatalEx ( "Error inesperado", ex );
			rctRes = ResultadoCasoTest::FAIL;
		}
		else
		{
			LogInfo ( Concatenar ( "Excepcion recibida: [", ex.what (), "]" ) );
		}
	}
	catch ( ... )
	{
		LogFatal ( "Capturado throwable inesperado" );
		rctRes = ResultadoCasoTest::FAIL;
	}
	if ( rctRes == ResultadoCasoTest::OK ) 
	{
		LogInfo ( "Caso terminado correctamente" );
	}
	else
	{
		LogError ( "Caso terminado con errores" );
	}
	return ( rctRes );
}		

				}
 			}
		}
	}
}
