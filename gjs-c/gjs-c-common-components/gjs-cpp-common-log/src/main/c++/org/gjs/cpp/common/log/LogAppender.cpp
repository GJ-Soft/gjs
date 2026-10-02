#include "../LogConfig.h"
#include "LogAppender.h"


using namespace std;


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


LogAppender::LogAppender ()
{
	/* Solo los valores por defecto. Inicializar () es virtual pura y desde aqui
	   no se puede alcanzar, ni directa ni a traves de Ini (): durante la
	   construccion de la base la tabla de virtuales es todavia la de
	   LogAppender, donde no hay implementacion, y el proceso muere en silencio.
	   Para eso esta Ini (), que se llama con el objeto ya completo. */
	nivel = NivelLog::NIVEL_INFORMACION;
	bActivo = true;
}

bool LogAppender::Ini ()
{
	return ( Inicializar () );
}

bool LogAppender::Activo ()
{
	return ( bActivo );
}

void LogAppender::Activar ()
{
	bActivo = true;
}

void LogAppender::Desactivar ()
{
	bActivo = false;
}


NivelLog LogAppender::Nivel ()
{
	return ( nivel );
}

void LogAppender::EstablecerNivel ( NivelLog nivelNuevo )
{
	nivel = nivelNuevo;
}

void LogAppender::EstablecerNivel ( int iNivel )
{
	nivel = ToNivelLog ( iNivel );
}


void LogAppender::LogInfo ( const string & sMensaje )
{
	Log ( NivelLog::NIVEL_INFORMACION, sMensaje );
}

void LogAppender::LogDepuracion ( const string & sMensaje )
{
	Log ( NivelLog::NIVEL_DEPURACION, sMensaje );
}

void LogAppender::LogTraza ( const string & sMensaje )
{
	Log ( NivelLog::NIVEL_TRAZA, sMensaje );
}

void LogAppender::LogAviso ( const string & sMensaje )
{
	Log ( NivelLog::NIVEL_AVISO, sMensaje );
}

void LogAppender::LogAvisoEx ( const std::string & sMensaje, const std::exception & exInfo )
{
	LogEx ( NivelLog::NIVEL_AVISO, sMensaje, exInfo );
}

void LogAppender::LogError ( const string & sMensaje )
{
	Log ( NivelLog::NIVEL_ERROR, sMensaje );
}

void LogAppender::LogErrorEx ( const string & sMensaje, const exception & exInfo )
{
	LogEx ( NivelLog::NIVEL_ERROR, sMensaje, exInfo );
}

void LogAppender::LogError ( const exception & exInfo )
{
	LogEx ( NivelLog::NIVEL_ERROR, "", exInfo );
}

void LogAppender::LogForzado ( NivelLog nivel, const string & sMensaje )
{
	Log ( nivel, sMensaje );
}

void LogAppender::LogForzadoEx ( NivelLog nivel, const string & sMensaje, const exception & exInfo )
{
	LogEx ( nivel, sMensaje, exInfo );
}

void LogAppender::LogForzado ( NivelLog nivel, const exception & exInfo )
{
	LogEx ( nivel, "", exInfo );
}

/* El parametro se llama nivelMensaje y no nivel para no tapar al atributo: la
   comparacion es "el nivel del mensaje llega al minimo configurado". */
void LogAppender::Log ( NivelLog nivelMensaje, const std::string & sMensaje )
{
	if ( bActivo && ( nivelMensaje >= nivel ) )
	{
		/* Compartido: varios hilos pueden anotar a la vez; solo una pausa los
		   detiene, y duermen mientras dure. */
		std::shared_lock < std::shared_mutex > lckLogado ( mtxPausa );
		try
		{
			LogInterno ( FormatearMensaje ( nivelMensaje, sMensaje ) );
		}
		catch ( const exception & ex )
		{
			/* Si falla el propio log, lo unico que queda es la salida de error. */
			cerr << ex.what () << endl;
		}
	}
}

void LogAppender::LogEx ( NivelLog nivelMensaje, const std::string & sMensaje, const std::exception & exInfo )
{
	if ( !sMensaje.empty () )
	{
		Log ( nivelMensaje, Concatenar ( sMensaje, ": ", exInfo.what () ) );
	}
	else
	{
		Log ( nivelMensaje, exInfo.what () );
	}
}

std::unique_lock < std::shared_mutex > LogAppender::PausarLogado ()
{
	return ( std::unique_lock < std::shared_mutex > ( mtxPausa ) );
}


/* Las seis variadicas Log* estan definidas en Log.h: aqui no se instanciaban
   para nadie de fuera del modulo. */




                }
            }
        }
    }
}
