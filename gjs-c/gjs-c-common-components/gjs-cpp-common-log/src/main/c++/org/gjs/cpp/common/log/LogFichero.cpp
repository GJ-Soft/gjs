#include "../LogConfig.h"
#include "LogFichero.h"


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

LogFichero::LogFichero () : LogEncabezado ()
{
	sDirectorio = DirectorioActual ();
	bHoraEnNombre = true;
	bHoraAlInicioNombre = false;
	cSepHoraNombre = '-';
	bPIDEnNombre = false;
}

LogFichero::LogFichero ( std::string sDirectorioNuevo ) : LogEncabezado ()
{
	sDirectorio = sDirectorioNuevo;
	bHoraEnNombre = true;
	bHoraAlInicioNombre = false;
	cSepHoraNombre = '-';
	bPIDEnNombre = false;
}

LogFichero::LogFichero ( std::string sDirectorioNuevo, std::string sNomProceso ) : LogEncabezado ( sNomProceso )
{
	sDirectorio = sDirectorioNuevo;
	bHoraEnNombre = true;
	bHoraAlInicioNombre = false;
	cSepHoraNombre = '-';
	bPIDEnNombre = false;
}

const string LogFichero::RutaFichero ()
{
	return ( sRutaFichero );
}


bool LogFichero::HoraEnNombreActivada ()
{
	return ( bHoraEnNombre );
}

void LogFichero::ActivarHoraEnNombre ()
{
	bHoraEnNombre = true;
}

void LogFichero::DesactivarHoraEnNombre ()
{
	bHoraEnNombre = false;
}

bool LogFichero::ApareceHoraEnNombreAlInicio ()
{
	return ( bHoraAlInicioNombre );
}

bool LogFichero::ApareceHoraEnNombreAlFinal ()
{
	return ( ! bHoraAlInicioNombre );
}

void LogFichero::PonerHoraEnNombreAlInicio ()
{
	bHoraAlInicioNombre = true;
}

void LogFichero::PonerHoraEnNombreAlFinal ()
{
	bHoraAlInicioNombre = false;
}

char LogFichero::SeparadorHoraEnNombre ()
{
	return ( cSepHoraNombre );
}

void LogFichero::EstablecerSeparadorHoraEnNombre ( char cSep )
{
	cSepHoraNombre = cSep;
}


bool LogFichero::PIDEnNombreActivado ()
{
	return ( bPIDEnNombre );
}

void LogFichero::ActivarPIDEnNombre ()
{
	bPIDEnNombre = true;
}

void LogFichero::DesactivarPIDEnNombre ()
{
	bPIDEnNombre = false;
}


bool LogFichero::Inicializar ()
{
	/* Si el directorio configurado no existe, LogInterno no podria abrir nada y
	   cada anotacion acabaria en cerr sin que nadie se entere. Se crea aqui. */
	if ( ! sDirectorio.empty () && ! SisExisteDirectorio ( sDirectorio ) )
	{
		SisCrearDirectorio ( sDirectorio );
	}
	sRutaFichero = SisComponerRuta ( sDirectorio, GenerarNombreFichero () );
	return ( ! sRutaFichero.empty () && SisExisteDirectorio ( sDirectorio ) );
}


void LogFichero::LogInterno ( const std::string & sMensaje )
{
	std::ofstream ofsFichero ( sRutaFichero, std::ios::app );
	if ( ofsFichero.is_open () )
	{
		ofsFichero << sMensaje << '\n';
		ofsFichero.close ();
	}
	else
	{
		cerr << "No se puede abrir el fichero " << sRutaFichero << endl;
	}
}

string LogFichero::GenerarNombreFichero ()
{
	stringstream ssNombre;

	if ( HoraEnNombreActivada () )
	{
		/* Formato propio, sin ':' ni espacios: los dos puntos no valen en un
		   nombre de fichero de Windows. */
		FechaHora fechaHora;
		fechaHora.EstablecerValorDeAhora ();
		string * p_sFechaHora = fechaHora.Cadena ( LOG_FORMATO_FECHA_FICHERO );
		if ( ApareceHoraEnNombreAlInicio () )
		{
			ssNombre << *p_sFechaHora << cSepHoraNombre << NombreProceso ();
		}
		else
		{
			ssNombre << NombreProceso () << cSepHoraNombre << *p_sFechaHora;
		}
		delete p_sFechaHora;
	}
	else
	{
		ssNombre << NombreProceso ();
	}
	if ( PIDEnNombreActivado () )
	{
		ssNombre << '_' << SisPID ();
	}
	ssNombre << '.' << LOG_EXT_NOM_FICHERO_DEF;
	return ( ssNombre.str () );
}

/* Cierra el fichero actual y abre el siguiente.

   Las dos anotaciones van por LogInterno y no por LogForzado a proposito: aqui
   ya se tiene el cerrojo exclusivo de la pausa, y LogForzado acabaria en Log (),
   que pide el compartido del mismo std::shared_mutex, que no es reentrante. Se
   quedaria bloqueado contra si mismo. */
void LogFichero::GestionarCambioFichero ()
{
	if ( HoraEnNombreActivada () && CriterioCambioFichero () )
	{
		auto lckPausa = PausarLogado ();
		LogInterno ( FormatearMensaje ( NivelLog::NIVEL_INFORMACION, LOG_MSJ_TXT_CAMBIO_FICHERO ) );
		Inicializar ();
		LogInterno ( FormatearMensaje ( NivelLog::NIVEL_INFORMACION, LOG_MSJ_TXT_CONTINUACION_FICHERO ) );
	}
}



                }
            }
        }
    }
}
