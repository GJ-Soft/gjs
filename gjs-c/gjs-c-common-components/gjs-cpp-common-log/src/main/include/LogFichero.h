#ifndef _ORG_GJS_C_CC_CPP_LOG_LOG_FICHERO_H
#define _ORG_GJS_C_CC_CPP_LOG_LOG_FICHERO_H

#include <LogEncabezado.h>





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

class LogFichero : public LogEncabezado
{
	private:
		std::string	sDirectorio;
		std::string	sRutaFichero;
		bool    	bHoraEnNombre;
		bool    	bHoraAlInicioNombre;
		char 		cSepHoraNombre;
		bool    	bPIDEnNombre;
		
	public:
		LogFichero ();
		LogFichero ( std::string sDirectorio );
		LogFichero ( std::string sDirectorio, std::string sNomProceso );
		virtual ~LogFichero() = default;					

		const std::string RutaFichero ();

		bool HoraEnNombreActivada ();
		void ActivarHoraEnNombre ();
		void DesactivarHoraEnNombre ();
		bool ApareceHoraEnNombreAlInicio ();
		bool ApareceHoraEnNombreAlFinal ();
		void PonerHoraEnNombreAlInicio ();
		void PonerHoraEnNombreAlFinal ();
		char SeparadorHoraEnNombre ();
		void EstablecerSeparadorHoraEnNombre ( char cSep );

		bool PIDEnNombreActivado ();
		void ActivarPIDEnNombre ();
		void DesactivarPIDEnNombre ();

	protected:
		bool Inicializar () override;
		void LogInterno ( const std::string & sMensaje ) override;
		virtual bool CriterioCambioFichero () { return ( false ); }
		
	private:
		std::string GenerarNombreFichero ();
		void GestionarCambioFichero ();
};


                }
            }
        }
    }
}

#endif
