#include "../LogConfig.h"
#include "Log.h"

#include <Configuracion.h>
#include <ESExcepcion.h>


using namespace std;
using namespace org::gjs::cpp::common;


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

/* Punteros y no objetos: LogAppender es abstracta, no es copiable ( lleva
   un shared_mutex ) y guardarla por valor rebanaria cada appender derivado,
   con lo que el despacho virtual nunca llegaria a LogConsola ni LogFichero. */
static list < shared_ptr < LogAppender > >	_listLoggers;
static bool 				_bLogInicializado = false;
static bool 				_bLogActivo = false;
/* Con signo: -1 es "no hay consola". Con size_t se convertia en el valor
   maximo y la comprobacion daba siempre cierto. */
static long 				_iLogConsola = -1;
static NivelLog 			_nivel = NivelLog::NIVEL_NINGUNO;


map<string, string> LogPropiedadesDefecto ( bool bConsola, bool bFichero, string sNombre, string sDirectorio )
{
	map<string, string> mapPropiedades;
	if ( sNombre.size () > 0 )
	{
		mapPropiedades [ LOG_PROP_NOMBRE ] = sNombre;
	}
	else
	{
		mapPropiedades [ LOG_PROP_NOMBRE ] = SisNombreProceso ();
	}
	if ( sDirectorio.size () > 0 )
	{
		mapPropiedades [ LOG_PROP_DIRECTORIO ] = sDirectorio;
	}
	else
	{
		mapPropiedades [ LOG_PROP_DIRECTORIO ] = DirectorioActual();
	}
	mapPropiedades [ LOG_PROP_CONSOLA_ACTIVA ] = ToString( bConsola );
	mapPropiedades [ LOG_PROP_FICHERO_ACTIVO ] = ToString( bFichero );
	return ( mapPropiedades );
}


bool LogIni ()
{
	bool	bRes;
	/* Una sola busqueda: ResExiste llama por dentro a ResBuscar, asi que pedir
	   las dos cosas componia la ruta y miraba el disco dos veces. */
	string	sRutaCfg = ResBuscar ( LOG_FIC_CFG_DEF );

	if ( ! sRutaCfg.empty () )
	{
		bRes = LogIni ( sRutaCfg );
	}
	else
	{
		/* AplicNombre () tal cual, sin sustituirlo aqui por un valor por defecto: si
		   la aplicacion no ha fijado nombre viene vacio, y de ese caso ya se ocupa
		   LogPropiedadesDefecto usando SisNombreProceso (). Poniendo el respaldo
		   tambien aqui habia dos valores por defecto para lo mismo y el de
		   LogPropiedadesDefecto no llegaba a usarse nunca.

		   El mapa no puede ir como temporal: LogIni lo toma por referencia NO
		   constante, y a una referencia asi no se le ata un temporal. */
		map<string, string> mapPropiedades = LogPropiedadesDefecto ( true, true, AplicNombre (),
																	 SisDirectorioEjecutable () );

		bRes = LogIni ( mapPropiedades );
	}
	return ( bRes );
}

bool LogIni ( const string & sRutaFicheroCfg )
{
	bool bRes = true;
	if ( !_bLogInicializado )
	{
		try
		{
			map<string, string> mapPropiedades = config::LeerPropiedades ( sRutaFicheroCfg );
			bRes = LogIni ( mapPropiedades );
		}
		catch ( const ESExcepcion & ex )
		{
			bRes = false;
			cerr << ex.what() << endl;
		}
	}
	return( bRes );
}

bool LogIni ( map<string, string> & mapPropiedades )
{
	if ( !_bLogInicializado )
	{
		/* Fuera del bucle: dentro se redeclaraban en cada vuelta y no existian
		   ya al salir. Y con valor inicial, que una clave ausente no deje una
		   bandera con basura. */
		bool	bConsola = false;
		bool	bFichero = false;
		string	sNombre;
		string	sDirectorio;

		for ( map<string, string>::const_iterator it = mapPropiedades.begin ();
			  it != mapPropiedades.end (); ++it )
		{
			if ( it->first == LOG_PROP_NOMBRE )
			{
				sNombre = it->second;
			}
			else if ( it->first == LOG_PROP_DIRECTORIO )
			{
				sDirectorio = it->second;
			}
			else if ( it->first == LOG_PROP_CONSOLA_ACTIVA )
			{
				bConsola = ToBool ( it->second );
			}
			else if ( it->first == LOG_PROP_FICHERO_ACTIVO )
			{
				bFichero = ToBool ( it->second );
			}
		}
		if ( sNombre.empty () )
		{
			sNombre = SisNombreProceso ();
		}
		if ( sDirectorio.empty () )
		{
			sDirectorio = DirectorioActual ();
		}

		/* La marca va ANTES de crear los appenders: LogIniConsola y LogIniFichero
		   comprueban _bLogInicializado y no harian nada si se pusiera al final. */
		_bLogInicializado = true;
		if ( bConsola )
		{
			LogIniConsola ( sNombre );
		}
		if ( bFichero )
		{
			LogIniFichero ( sNombre, sDirectorio );
		}
	}
	return ( _bLogInicializado );
}

bool LogActivado ()
{
	return ( _bLogActivo );
}

void LogActivar ()
{
	if ( _bLogInicializado && !_bLogActivo ) 
	{
		for ( const shared_ptr < LogAppender > & p_logger : _listLoggers )
		{
			p_logger->Activar ();
		}
		_bLogActivo = true;
	}
}
	
void LogDesactivar ()
{
	if ( _bLogInicializado && _bLogActivo ) 
	{
		for ( const shared_ptr < LogAppender > & p_logger : _listLoggers )
		{
			p_logger->Desactivar ();
		}
		_bLogActivo = false;
	}
}

NivelLog LogNivel ()
{
	return ( _nivel );
}

void LogEstablecerNivel ( NivelLog nivel )
{
	_nivel = nivel;
	for ( const shared_ptr < LogAppender > & p_logger : _listLoggers )
	{
		p_logger->EstablecerNivel ( nivel );
	}
}

void LogEstablecerNivel ( int iNivel )
{
	LogEstablecerNivel ( ToNivelLog ( iNivel ) );
}


bool LogIncluirAppender ( shared_ptr < LogAppender > p_logger )
{
	bool bRes = false;

	if ( _bLogInicializado && !_bLogActivo && ( p_logger != nullptr ) )
	{
		p_logger->EstablecerNivel ( _nivel );
		_listLoggers.push_back ( p_logger );
		bRes = true;
	}
	return ( bRes );
}

bool LogIniConsola ( const string & sNomProceso )
{
	bool bRes = false;

	if ( _bLogInicializado && !_bLogActivo )
	{
		try
		{
			shared_ptr < LogConsola > p_logger = make_shared < LogConsola > ( sNomProceso );
			p_logger->Ini ();
			bRes = LogIncluirAppender ( p_logger );
			if ( bRes )
			{
				_iLogConsola = ( long ) ( _listLoggers.size () - 1 );
			}
		}
		catch ( const exception & ex )
		{
			bRes = false;
			cerr << ex.what () << endl;
		}
	}
	return ( bRes );
}

/* Devuelve el appender de consola, o nulo si no lo hay. */
static shared_ptr < LogAppender > _LogAppenderConsola ()
{
	shared_ptr < LogAppender > p_logger;

	if ( ( _iLogConsola >= 0 ) && ( ( ( size_t ) _iLogConsola ) < _listLoggers.size () ) )
	{
		p_logger = * next ( _listLoggers.begin (), _iLogConsola );
	}
	return ( p_logger );
}

bool LogHaySalidaPorConsola ()
{
	return ( _LogAppenderConsola () != nullptr );
}

bool LogSalidaPorConsolaActivada ()
{
	bool bRes = false;

	shared_ptr < LogAppender > p_logger = _LogAppenderConsola ();
	if ( p_logger != nullptr )
	{
		bRes = p_logger->Activo ();
	}
	return ( bRes );
}

void LogActivarConsola ()
{
	shared_ptr < LogAppender > p_logger = _LogAppenderConsola ();
	if ( p_logger != nullptr )
	{
		p_logger->Activar ();
	}
}

void LogDesactivarConsola ()
{
	shared_ptr < LogAppender > p_logger = _LogAppenderConsola ();
	if ( p_logger != nullptr )
	{
		p_logger->Desactivar ();
	}
}

bool LogIniFichero ( const std::string & sNomProceso, const string & sDirectorio )
{
	bool bRes = false;

	if ( _bLogInicializado && !_bLogActivo )
	{
		try
		{
			/* El constructor de LogFichero toma primero el directorio. */
			shared_ptr < LogFichero > p_logger =
						make_shared < LogFichero > ( sDirectorio, sNomProceso );
			p_logger->Ini ();
			bRes = LogIncluirAppender ( p_logger );
		}
		catch ( const exception & ex )
		{
			bRes = false;
			cerr << ex.what () << endl;
		}
	}
	return ( bRes );
}

void LogFin ()
{
	if ( _bLogInicializado )
	{
		LogDesactivar ();
		_listLoggers.clear ();
		_bLogInicializado = false;
		_bLogActivo = false;
		_iLogConsola = -1;
		_nivel = NivelLog::NIVEL_NINGUNO;
	}
}

void LogInfo ( const string & sMensaje )
{
	if ( _bLogInicializado && _bLogActivo )
	{
		for ( const shared_ptr < LogAppender > & p_logger : _listLoggers )
		{
			p_logger->LogInfo ( sMensaje );
		}
	}
}

void LogDepuracion ( const string & sMensaje )
{
	if ( _bLogInicializado && _bLogActivo )
	{
		for ( const shared_ptr < LogAppender > & p_logger : _listLoggers )
		{
			p_logger->LogDepuracion ( sMensaje );
		}
	}
}

void LogTraza ( const string & sMensaje )
{
	if ( _bLogInicializado && _bLogActivo )
	{
		for ( const shared_ptr < LogAppender > & p_logger : _listLoggers )
		{
			p_logger->LogTraza ( sMensaje );
		}
	}
}

void LogAviso ( const string & sMensaje )
{
	if ( _bLogInicializado && _bLogActivo )
	{
		for ( const shared_ptr < LogAppender > & p_logger : _listLoggers )
		{
			p_logger->LogAviso ( sMensaje );
		}
	}
}

void LogError ( const string & sMensaje )
{
	if ( _bLogInicializado && _bLogActivo )
	{
		for ( const shared_ptr < LogAppender > & p_logger : _listLoggers )
		{
			p_logger->LogError ( sMensaje );
		}
	}
}

void LogErrorEx ( const string & sMensaje, const exception & exInfo )
{
	if ( _bLogInicializado && _bLogActivo )
	{
		for ( const shared_ptr < LogAppender > & p_logger : _listLoggers )
		{
			p_logger->LogErrorEx ( sMensaje, exInfo );
		}
	}
}

void LogAvisoEx ( const string & sMensaje, const exception & exInfo )
{
	if ( _bLogInicializado && _bLogActivo )
	{
		for ( const shared_ptr < LogAppender > & p_logger : _listLoggers )
		{
			p_logger->LogAvisoEx ( sMensaje, exInfo );
		}
	}
}
void LogError ( const exception & exInfo )
{
	if ( _bLogInicializado && _bLogActivo )
	{
		for ( const shared_ptr < LogAppender > & p_logger : _listLoggers )
		{
			p_logger->LogError ( exInfo );
		}
	}
}

void LogAviso ( const exception & exInfo )
{
	if ( _bLogInicializado && _bLogActivo )
	{
		for ( const shared_ptr < LogAppender > & p_logger : _listLoggers )
		{
			p_logger->LogAvisoEx ( "", exInfo );
		}
	}
}


                }
            }
        }
    }
}
