#include "../LogConfig.h"
#include "LogEncabezado.h"


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


/* Sin nombre delega en el de abajo con la cadena vacia, que es donde esta la
   cadena de respaldo. */
LogEncabezado::LogEncabezado () : LogEncabezado ( "" )
{
}

LogEncabezado::LogEncabezado ( std::string	sNombre ) : LogAppender ()
{
	/* Mismo criterio que LogPropiedadesDefecto, para que el log se llame igual
	   venga por donde venga: el nombre que den, si no el del proceso, y solo si
	   tampoco hay, el valor por defecto. Antes esta rama se quedaba con la cadena
	   vacia y la de arriba iba directa a LOG_TXT_NOMBRE_DEFECTO. */
	if ( ! sNombre.empty () )
	{
		sNomProceso = sNombre;
	}
	else
	{
		sNomProceso = SisNombreProceso ();

		if ( sNomProceso.empty () )
		{
			sNomProceso = string ( LOG_TXT_NOMBRE_DEFECTO );
		}
	}
	bEncabezado = true;
	bAnotarTipoMensaje = true;
	bPartirLinea = false;
}

const string LogEncabezado::NombreProceso ()
{
	return ( sNomProceso );
}

void LogEncabezado::EstablecerNombreProceso ( const string & sNombre )
{
	sNomProceso = sNombre;
}


void LogEncabezado::ActivarEncabezadoLinea ()
{
	bEncabezado = true;
}

void LogEncabezado::DesactivarEncabezadoLinea ()
{
	bEncabezado = false;
}

bool LogEncabezado::EncabezadoLineaActivado ()
{
	return ( bEncabezado );
}

void LogEncabezado::ActivarAnotacionTipoMensaje ()
{
	bAnotarTipoMensaje = true;
}

void LogEncabezado::DesactivarAnotacionTipoMensaje ()
{
	bAnotarTipoMensaje = false;
}

bool LogEncabezado::AnotacionTipoMensajeActivada ()
{
	return ( bAnotarTipoMensaje );
}

void LogEncabezado::ActivarParticionLinea ()
{
	bPartirLinea = true;
}

void LogEncabezado::DesactivarParticionLinea ()
{
	bPartirLinea = false;
}

bool LogEncabezado::ParticionLineaActivada ()
{
	return ( bPartirLinea );
}


string LogEncabezado::FormatearMensaje ( NivelLog nivel, const std::string & sMensaje )
{
	stringstream ssEncabezado;

	if ( EncabezadoLineaActivado () )
	{
		ssEncabezado << "[";
		if ( ! sNomProceso.empty () )
		{
			ssEncabezado << sNomProceso << " | ";
		}
		FechaHora fechaHora;
		fechaHora.EstablecerValorDeAhora ();
		string * p_sFechaHora = fechaHora.Cadena ( LOG_FORMATO_FECHA_HORA );
		ssEncabezado << *p_sFechaHora << "] - ";
		delete p_sFechaHora;
	}
	if ( AnotacionTipoMensajeActivada () )
	{
		ssEncabezado << ToString ( nivel );
	}
	ssEncabezado << ": ";
	string sCabecera = ssEncabezado.str ();

	stringstream ssTexto;
	if ( ParticionLineaActivada () )
	{
		/* Cada trozo lleva su propia cabecera delante, asi que lo que cabe de
		   mensaje es lo que sobra de la linea. Si la cabecera se come la linea
		   entera se deja un minimo, o el bucle no avanzaria nunca. */
		size_t uTamCabecera = sCabecera.length ();
		size_t uMaxTamLinea = ( uTamCabecera < LOG_MAX_TAM_LINEA )
							  ? ( LOG_MAX_TAM_LINEA - uTamCabecera )
							  : LOG_MIN_TAM_TEXTO_LINEA;
		size_t uPos = 0;
		int    iLinea = 0;

		while ( ( uPos < sMensaje.length () ) && ( iLinea < LOG_MAX_LINEAS_MENSAJE ) )
		{
			ssTexto << ( ( uPos > 0 ) ? "\n" : "" ) << sCabecera
					<< sMensaje.substr ( uPos, uMaxTamLinea );
			uPos = uPos + uMaxTamLinea;
			iLinea = iLinea + 1;
		}
		if ( uPos < sMensaje.length () )
		{
			ssTexto << "\n" << sCabecera << LOG_MSJ_TXT_TRUNCADO;
		}
	}
	else
	{
		ssTexto << sCabecera << sMensaje;
	}
	return ( ssTexto.str () );
}



                }
            }
        }
    }
}
