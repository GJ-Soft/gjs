#ifndef _ORG_GJS_C_CC_CPP_LOG_LOG_H
#define _ORG_GJS_C_CC_CPP_LOG_LOG_H

#include <MDC.h>

/* ToString.h hace falta aqui porque las plantillas Log* estan definidas en esta
   cabecera y lo llaman; <exception>, <type_traits> y <utility>, por la guarda de
   LogError / LogFatal y por el forward. */
#include <ToString.h>

#include <string>
#include <map>
#include <exception>
#include <type_traits>
#include <utility>



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
			void LogLiberar ();

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

            /* Las definiciones van aqui, en la cabecera, y no en Log.cpp: una
               plantilla solo se instancia donde se ve su cuerpo, asi que definidas
               en el .cpp no las podia usar nadie de fuera del modulo. */

            template<typename... Args> void LogInfo ( const std::string & sFormato, Args&&... argumentos )
            {
            	LogInfo ( ToString ( sFormato, std::forward<Args> ( argumentos )... ) );
            }

            template<typename... Args> void LogDepuracion ( const std::string & sFormato, Args&&... argumentos )
            {
            	LogDepuracion ( ToString ( sFormato, std::forward<Args> ( argumentos )... ) );
            }

            template<typename... Args> void LogTraza ( const std::string & sFormato, Args&&... argumentos )
            {
            	LogTraza ( ToString ( sFormato, std::forward<Args> ( argumentos )... ) );
            }

            template<typename... Args> void LogAviso ( const std::string & sFormato, Args&&... argumentos )
            {
            	LogAviso ( ToString ( sFormato, std::forward<Args> ( argumentos )... ) );
            }

            /* LogError y LogFatal llevan guarda: si alguno de los argumentos es una
               excepcion, esta plantilla se descarta y gana la sobrecarga
               LogError ( const std::exception & ). Sin ella, LogError ( unaExcepcion )
               entraria aqui y acabaria en vformat, que no sabe formatear una
               excepcion. Ojo: la cabecera las declaraba void y Log.cpp las definia
               con este tipo de retorno; se conserva el del .cpp, que es el bueno. */
            template<typename... Args> auto LogError ( const std::string & sFormato, Args&&... argumentos )
             -> std::enable_if_t<!(... || std::is_base_of_v<std::exception, std::decay_t<Args>>)>
            {
            	LogError ( ToString ( sFormato, std::forward<Args> ( argumentos )... ) );
            }

            template<typename... Args> auto LogFatal ( const std::string & sFormato, Args&&... argumentos )
             -> std::enable_if_t<!(... || std::is_base_of_v<std::exception, std::decay_t<Args>>)>
            {
            	LogFatal ( ToString ( sFormato, std::forward<Args> ( argumentos )... ) );
            }

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
