#ifndef _ORG_GJS_C_CC_CPP_LOG_LOG_H
#define _ORG_GJS_C_CC_CPP_LOG_LOG_H

#include <MDC.h>


#include <string>
#include <map>



#define LOG_PROP_FICHERO				"logFilename"
#define LOG_PROP_DIRECTORIO				"logDirectory"

#define LOG_VAR_DIRECTORIO				"LOG_DIR"


#ifdef ERROR
#	undef ERROR
#endif




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
					
            enum Nivel
            {
                TODOS = 0,
                TRAZA = 1,
                DEPUR = 2,
                INFO = 3,
                AVISO = 4,
                ERROR = 5,
                FATAL = 6,
                NINGUNO = 7
            };


            std::map<std::string, std::string> LogPropiedadesDefecto ( std::string sNombreFichero = "", std::string sDirectorio = "" );

            bool LogIni ();
            bool LogIni ( const std::string & sRutaFicheroCfg );

            // TODO: Por un bug en log4cxx no funciona la substitucion de propiedades y no se pueden usar xml de configuración customizados
            bool LogIni ( std::map<std::string, std::string> & mapPropiedades );
            bool LogIni ( const std::string & sRutaFicheroCfg, std::map<std::string, std::string> & mapPropiedades );

			bool LogActivado ();
			void LogActivar ();
            void LogDesactivar ();


            bool LogIniConsola ( bool bSoloMensaje = false );
			bool LogHaySalidaPorConsola ();
			bool LogSalidaPorConsolaActivada ();
			void LogActivarConsola ();
            void LogDesactivarConsola ();
			
            bool LogIniFichero ( const std::string & sFicLog, bool consola = false );

            void LogFin ();

            void LogInfo ( const std::string & sMensaje );
            void LogDepuracion ( const std::string & sMensaje );
            void LogTraza ( const std::string & sMensaje );
            void LogAviso ( const std::string & sMensaje );
            void LogError ( const std::string & sMensaje );
            void LogFatal ( const std::string & sMensaje );
            void LogErrorEx ( const std::string & sMensaje, const std::exception & exInfo );
            void LogFatalEx ( const std::string & sMensaje, const std::exception & exInfo );
            void LogError ( const std::exception & exInfo );
            void LogFatal ( const std::exception & exInfo );

            template<typename... Args> void LogInfo ( const std::string & sFormato, Args&&... argumentos );
            template<typename... Args> void LogDepuracion ( const std::string & sFormato, Args&&... argumentos );
            template<typename... Args> void LogTraza ( const std::string & sFormato, Args&&... argumentos );
            template<typename... Args> void LogAviso ( const std::string & sFormato, Args&&... argumentos );
            template<typename... Args> void LogError ( const std::string & sFormato, Args&&... argumentos );
            template<typename... Args> void LogFatal ( const std::string & sFormato, Args&&... argumentos );

            Nivel LogGetNivel ();
            void LogSetNivel ( Nivel nivel );
            void LogSetNivel ( int iNivel );

			Nivel ToNivel ( int iNivel );
			int ToInt ( Nivel nivel );
            /*
                TODO:
                    Colores en caso consola
                    Reconfiguracion forzada
                    Test reconfiguración periodica y forzada
             */
                }
            }
        }
    }
}

#endif
