#include "LogConfig.h"
#include "Log.h"


using namespace std;
using namespace org::gjs::cpp::common::MDC;


namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {
                namespace log
                {

static bool _bLogInicializado = false;

static log4cxx::ConsoleAppenderPtr _p_consoleAppender = nullptr;
static log4cxx::LevelPtr _p_levelConsole = nullptr;
static log4cxx::LevelPtr _p_level = nullptr;


static void _LogIniConsola ( bool bSoloMensaje )
{
	if ( _p_consoleAppender == nullptr )
	{
		_p_consoleAppender = log4cxx::ConsoleAppenderPtr( new log4cxx::ConsoleAppender() );
		log4cxx::PatternLayout * layout = new log4cxx::PatternLayout ();
		log4cxx::LogString conversionPattern = log4cxx::LogString ( ( bSoloMensaje ? LOG_PATRON_CONSOLA_MIN : LOG_PATRON_DEF ) );
		layout-> setConversionPattern( conversionPattern );
		_p_consoleAppender->setLayout( log4cxx::LayoutPtr( layout ) );
		log4cxx::helpers::Pool pool;
		_p_consoleAppender->activateOptions( pool );
		log4cxx::Logger::getRootLogger()->addAppender( _p_consoleAppender );
		log4cxx::Logger::getRootLogger()->setLevel( log4cxx::Level::getAll() );
	}
}

static void _LogIniFichero ( string sFicLog )
{
	log4cxx::rolling::RollingFileAppenderPtr appender( new log4cxx::rolling::RollingFileAppender() );
	appender->setFile( sFicLog );
	appender->setDatePattern( LOG_PATRON_FECHA_DEF );
	log4cxx::PatternLayout * layout = new log4cxx::PatternLayout ();
	log4cxx::LogString conversionPattern = log4cxx::LogString ( LOG_PATRON_DEF );
	layout-> setConversionPattern( conversionPattern );
	appender->setLayout( log4cxx::LayoutPtr( layout ) );
	log4cxx::helpers::Pool pool;
	appender->activateOptions( pool );
	log4cxx::Logger::getRootLogger()->addAppender( appender );
	log4cxx::Logger::getRootLogger()->setLevel( log4cxx::Level::getAll() );
}

static void _LogBuscarConsola ()
{
	log4cxx::AppenderList appenders = log4cxx::Logger::getRootLogger()->getAllAppenders();
    for ( auto it = appenders.begin(); it != appenders.end(); ++it ) 
	{
        // Hacer cast dinámico a ConsoleAppenderPtr
        _p_consoleAppender = std::dynamic_pointer_cast<log4cxx::ConsoleAppender>(*it);
        if ( _p_consoleAppender != nullptr ) {
            break;
        }
    }
    if ( _p_consoleAppender != nullptr ) {
		_p_levelConsole = _p_consoleAppender->getThreshold ();
    }
}


// Niveles TRACE < DEBUG < INFO < WARN < ERROR < FATAL
static int _ToLog4cxx ( Nivel nivel )
{
	int iRes = log4cxx::Level::ALL_INT;
	switch ( nivel )
	{
		case Nivel::TRAZA:
		{
			iRes = log4cxx::Level::TRACE_INT;
			break;
		}
		case Nivel::DEPUR:
		{
			iRes = log4cxx::Level::DEBUG_INT;
			break;
		}
		case Nivel::INFO:
		{
			iRes = log4cxx::Level::INFO_INT;
			break;
		}
		case Nivel::AVISO:
		{
			iRes = log4cxx::Level::WARN_INT;
			break;
		}
		case Nivel::ERROR:
		{
			iRes = log4cxx::Level::ERROR_INT;
			break;
		}
		case Nivel::FATAL:
		{
			iRes = log4cxx::Level::FATAL_INT;
			break;
		}
		case Nivel::NINGUNO:
		{
			iRes = log4cxx::Level::OFF_INT;
			break;
		}
	}
	return ( iRes );
}

static Nivel _FromLog4cxx ( int iNivel )
{
	Nivel nivel = Nivel::TODOS;
	switch ( iNivel )
	{
		case log4cxx::Level::TRACE_INT:
		{
			nivel = Nivel::TRAZA;
			break;
		}
		case log4cxx::Level::DEBUG_INT:
		{
			nivel = Nivel::DEPUR;
			break;
		}
		case log4cxx::Level::INFO_INT:
		{
			nivel = Nivel::INFO;
			break;
		}
		case log4cxx::Level::WARN_INT:
		{
			nivel = Nivel::AVISO;
			break;
		}
		case log4cxx::Level::ERROR_INT:
		{
			nivel = Nivel::ERROR;
			break;
		}
		case log4cxx::Level::FATAL_INT:
		{
			nivel = Nivel::FATAL;
			break;
		}
		case log4cxx::Level::OFF_INT:
		{
			nivel = Nivel::NINGUNO;
			break;
		}
	}
	return ( nivel );
}

static log4cxx::LevelPtr _ToLevel ( Nivel nivel )
{
	return log4cxx::Level::toLevel ( _ToLog4cxx ( nivel ) );
}

static log4cxx::LevelPtr _ToLevel ( int iNivel )
{
	return log4cxx::Level::toLevel ( _ToLog4cxx ( static_cast<Nivel>( iNivel ) ) );
}

static Nivel _ToNivel ( log4cxx::LevelPtr p_level )
{
	return ( _FromLog4cxx ( p_level->toInt() ) );
}



map<string, string> LogPropiedadesDefecto ( string sNombreFichero, string sDirectorio )
{
	map<string, string> mapPropiedades;
	if ( sNombreFichero.size () > 0 )
	{
		mapPropiedades [ LOG_PROP_FICHERO ] = sNombreFichero;
	}
	else
	{
		mapPropiedades [ LOG_PROP_FICHERO ] = "log";
	}
	if ( sDirectorio.size () == 0 )
	{
		sDirectorio = VariableEntorno ( LOG_VAR_DIRECTORIO );
	}
	if ( sDirectorio.size () > 0 )
	{
		mapPropiedades [ LOG_PROP_DIRECTORIO ] = sDirectorio;
	}
	else
	{
		mapPropiedades [ LOG_PROP_DIRECTORIO ] = DirectorioActual();
	}
	return ( mapPropiedades );
}



bool LogIni ()
{
	return ( LogIni ( Concatenar( DirectorioActual(), ToString( "config/" ) , ToString( LOG_FIC_CFG_DEF ) ) ) );
}

bool LogIni ( const string & sRutaFicheroCfg )
{
	bool bRes = true;
	if ( !_bLogInicializado )
	{
		setlocale( LC_ALL, "" );
		try
		{
			log4cxx::xml::DOMConfigurator::configureAndWatch( sRutaFicheroCfg, LOG_TMP_RECONFIGURACION );
			_bLogInicializado = true;
			_LogBuscarConsola ();
		}
		catch ( const exception & ex )
		{
			bRes = false;
			cout << ex.what() << endl;
		}
	}
	return( bRes );
}

bool LogIni ( map<string, string> & mapPropiedades )
{
	return ( LogIni ( Concatenar( DirectorioActual(), ToString( "config/" ) , ToString( LOG_FIC_CFG_DEF ) ), mapPropiedades ) );
}

bool LogIni ( const string & sRutaFicheroCfg, map<string, string> & mapPropiedades )
{
	for ( map<string, string>::iterator it = mapPropiedades.begin(); it != mapPropiedades.end(); ++it )
	{
		MDCGuardar ( it->first, it->second );
		cout <<  "PROP: [" << it->first << "]=[" << it->second << "]" << endl;
	}
	return ( LogIni ( sRutaFicheroCfg ) );
}

bool LogActivado ()
{
	return ( log4cxx::Logger::getRootLogger()->getLevel () != log4cxx::Level::getOff() );
}

void LogActivar ()
{
	if ( _p_level != nullptr ) 
	{
		log4cxx::Logger::getRootLogger()->setLevel ( _p_level );
		_p_level = nullptr;
	}
}
	
void LogDesactivar ()
{
	if ( _p_level == nullptr ) 
	{
		_p_level = log4cxx::Logger::getRootLogger()->getLevel ();
		log4cxx::Logger::getRootLogger()->setLevel ( log4cxx::Level::getOff() );
	}
}


bool LogIniConsola ( bool bSoloMensaje )
{
	bool bRes = true;
	if ( !_bLogInicializado )
	{
		setlocale( LC_ALL, "" );
		try
		{
			_LogIniConsola ( bSoloMensaje );
			log4cxx::LogManager::getLoggerRepository()->setConfigured( true );
			_bLogInicializado = true;
		}
		catch ( const exception & ex )
		{
			bRes = false;
			cout << ex.what() << endl;
		}
	}
	return( bRes );
}

bool LogHaySalidaPorConsola ()
{
	return ( _p_consoleAppender != nullptr );
}

bool LogSalidaPorConsolaActivada ()
{
	bool bRes = false;
	if ( _p_consoleAppender != nullptr ) 
	{
		bRes = ( _p_consoleAppender->getThreshold () != log4cxx::Level::getOff() );
	}
	return ( bRes );
}

void LogActivarConsola ()
{
	if ( _p_consoleAppender != nullptr ) 
	{
		_p_consoleAppender->setThreshold ( _p_levelConsole );
	}
}
	
void LogDesactivarConsola ()
{
	if ( _p_consoleAppender != nullptr ) 
	{
		_p_levelConsole = _p_consoleAppender->getThreshold ();
		_p_consoleAppender->setThreshold ( log4cxx::Level::getOff() );
	}
}

bool LogIniFichero ( const string & sFicLog, bool consola )
{
	bool bRes = true;
	if ( !_bLogInicializado )
	{
		setlocale( LC_ALL, "" );
		try
		{
			_LogIniFichero( sFicLog );
			if ( consola )
			{
				_LogIniConsola( false );
			}
			log4cxx::LogManager::getLoggerRepository()->setConfigured( true );
			_bLogInicializado = true;
		}
		catch ( const exception & ex )
		{
			bRes = false;
			cout << ex.what() << endl;
		}
	}
	return( bRes );
}

void LogFin ()
{
	if ( _bLogInicializado )
	{
		log4cxx::Logger::getRootLogger()->closeNestedAppenders ();
		log4cxx::LogManager::getLoggerRepository()->resetConfiguration();
		log4cxx::LogManager::getLoggerRepository()->setConfigured( false );
		// Se sueltan las referencias estaticas a objetos log4cxx antes de la
		// destruccion estatica del proceso; en caso contrario sus destructores
		// se ejecutan tras el teardown interno de log4cxx/APR y abortan.
		_p_consoleAppender = nullptr;
		_p_levelConsole = nullptr;
		_p_level = nullptr;
		_bLogInicializado = false;
	}
}

void LogLiberar ()
{
	log4cxx::LogManager::shutdown();
}

void LogInfo ( const string & sMensaje )
{
	if ( _bLogInicializado )
	{
		try
		{
			log4cxx::Logger::getRootLogger()->info( sMensaje );
		}
		catch ( const exception & ex )
		{
			cout << ex.what() << endl;
		}
	}
}

void LogDepuracion ( const string & sMensaje )
{
	if ( _bLogInicializado )
	{
		try
		{
			log4cxx::Logger::getRootLogger()->debug( sMensaje );
		}
		catch ( const exception & ex )
		{
			cout << ex.what() << endl;
		}
	}
}

void LogTraza ( const string & sMensaje )
{
	if ( _bLogInicializado )
	{
		try
		{
			log4cxx::Logger::getRootLogger()->trace( sMensaje );
		}
		catch ( const exception & ex )
		{
			cout << ex.what() << endl;
		}
	}
}

void LogAviso ( const string & sMensaje )
{
	if ( _bLogInicializado )
	{
		try
		{
			log4cxx::Logger::getRootLogger()->warn( sMensaje );
		}
		catch ( const exception & ex )
		{
			cout << ex.what() << endl;
		}
	}
}

void LogError ( const string & sMensaje )
{
	if ( _bLogInicializado )
	{
		try
		{
			log4cxx::Logger::getRootLogger()->error( sMensaje );
		}
		catch ( const exception & ex )
		{
			cout << ex.what() << endl;
		}
	}
}

void LogFatal ( const string & sMensaje )
{
	if ( _bLogInicializado )
	{
		try
		{
			log4cxx::Logger::getRootLogger()->fatal( sMensaje );
		}
		catch ( const exception & ex )
		{
			cout << ex.what() << endl;
		}
	}
}

void LogErrorEx ( const string & sMensaje, const exception & exInfo )
{
	if ( _bLogInicializado )
	{
		try
		{
			string sTexto = Concatenar( sMensaje, ToString( ": [" ), ToString( exInfo.what() ), ToString( "]" ) );
			log4cxx::Logger::getRootLogger()->error( sTexto );
		}
		catch ( const exception & ex )
		{
			cout << ex.what() << endl;
		}
	}
}

void LogFatalEx ( const string & sMensaje, const exception & exInfo )
{
	if ( _bLogInicializado )
	{
		try
		{
			string sTexto = Concatenar( sMensaje, ToString( ": [" ), ToString( exInfo.what() ), ToString( "]" ) );
			log4cxx::Logger::getRootLogger()->fatal( sTexto );
		}
		catch ( const exception & ex )
		{
			cout << ex.what() << endl;
		}
	}
}
void LogError ( const exception & exInfo )
{
	if ( _bLogInicializado )
	{
		try
		{
			log4cxx::Logger::getRootLogger()->error( exInfo.what() );
		}
		catch ( const exception & ex )
		{
			cout << ex.what() << endl;
		}
	}
}

void LogFatal ( const exception & exInfo )
{
	if ( _bLogInicializado )
	{
		try
		{
			log4cxx::Logger::getRootLogger()->fatal( exInfo.what() );
		}
		catch ( const exception & ex )
		{
			cout << ex.what() << endl;
		}
	}
}

Nivel LogGetNivel ()
{
	Nivel nivel = Nivel::NINGUNO;
	if ( _bLogInicializado )
	{
		try
		{
			nivel = _ToNivel ( log4cxx::Logger::getRootLogger()->getLevel() );
		}
		catch ( const exception & ex )
		{
			cout << ex.what() << endl;
		}
	}
	return ( nivel );
}

void LogSetNivel ( Nivel nivel )
{
	try
	{
		log4cxx::Logger::getRootLogger()->setLevel( _ToLevel ( nivel ) );
	}
	catch ( const exception & ex )
	{
		cout << ex.what() << endl;
	}
}

void LogSetNivel ( int iNivel )
{
	try
	{
		log4cxx::Logger::getRootLogger()->setLevel( _ToLevel ( iNivel ) );
	}
	catch ( const exception & ex )
	{
		cout << ex.what() << endl;
	}
}


template<typename... Args> void LogInfo ( const string & sFormato, Args&&... argumentos )
{
	LogInfo( ToString ( sFormato, forward<Args>( argumentos )... ) );
}

template<typename... Args> void LogDepuracion ( const string & sFormato, Args&&... argumentos )
{
	LogDepuracion( ToString ( sFormato, forward<Args>( argumentos )... ) );
}

template<typename... Args> void LogTraza ( const string & sFormato, Args&&... argumentos )
{
	LogTraza( ToString ( sFormato, forward<Args>( argumentos )... ) );
}

template<typename... Args> void LogAviso ( const string & sFormato, Args&&... argumentos )
{
	LogAviso( ToString ( sFormato, forward<Args>( argumentos )... ) );
}

template<typename... Args> auto LogError ( const string & sFormato, Args&&... argumentos )
 -> std::enable_if_t<!(... || std::is_base_of_v<std::exception, std::decay_t<Args>>)>
{
	LogError( ToString ( sFormato, forward<Args>( argumentos )... ) );
}

template<typename... Args> auto LogFatal ( const string & sFormato, Args&&... argumentos )
 -> std::enable_if_t<!(... || std::is_base_of_v<std::exception, std::decay_t<Args>>)>
{
	LogFatal( ToString ( sFormato, forward<Args>( argumentos )... ) );
}


Nivel ToNivel ( int iNivel ) 
{
	return ( static_cast<Nivel> ( iNivel ) );
}

int ToInt ( Nivel nivel )
{
	return  ( static_cast<int> ( nivel ) );
}



                }
            }
        }
    }
}
