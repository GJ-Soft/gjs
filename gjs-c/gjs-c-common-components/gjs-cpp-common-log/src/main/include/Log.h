#ifndef _ORG_GJS_C_CC_CPP_LOG_LOG_H
#define _ORG_GJS_C_CC_CPP_LOG_LOG_H

#include <NivelLog.h>
#include <LogAppender.h>
#include <LogConsola.h>
#include <LogFichero.h>

#include <memory>

/* ToString.h hace falta aqui porque las plantillas Log* estan definidas en esta
   cabecera y lo llaman; <exception>, <type_traits> y <utility>, por la guarda de
   LogError / LogFatal y por el forward. */
#include <ToString.h>

#include <string>
#include <map>
#include <exception>
#include <type_traits>
#include <utility>





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
					
			/* La cabecera declaraba dos parametros y la implementacion tiene cuatro: eran
			   dos sobrecargas distintas, y la de dos no la define nadie. */
			std::map<std::string, std::string> LogPropiedadesDefecto ( bool bConsola, bool bFichero,
																			std::string sNombre,
																			std::string sDirectorio );

            bool LogIni ();
            bool LogIni ( const std::string & sRutaFicheroCfg );
            bool LogIni ( std::map<std::string, std::string> & mapPropiedades );
            bool LogIni ( const std::string & sRutaFicheroCfg, std::map<std::string, std::string> & mapPropiedades );

			bool LogActivado ();
			void LogActivar ();
            void LogDesactivar ();

            NivelLog LogNivel ();
            void LogEstablecerNivel ( NivelLog nivel );
            void LogEstablecerNivel ( int iNivel );

            void LogFin ();

			/* Puntero compartido y no referencia: LogAppender es abstracta y los
			   appenders se guardan en una lista que sobrevive a quien los creo. */
			bool LogIncluirAppender ( std::shared_ptr < LogAppender > p_logger );
			
            bool LogIniConsola ( const std::string & sNomProceso );
			bool LogHaySalidaPorConsola ();
			bool LogSalidaPorConsolaActivada ();
			void LogActivarConsola ();
            void LogDesactivarConsola ();
			
            bool LogIniFichero ( const std::string & sNomProceso, const std::string & sDirectorio );

            void LogInfo ( const std::string & sMensaje );
            void LogDepuracion ( const std::string & sMensaje );
            void LogTraza ( const std::string & sMensaje );
            void LogAviso ( const std::string & sMensaje );
            void LogAvisoEx ( const std::string & sMensaje, const std::exception & exInfo );
            void LogError ( const std::string & sMensaje );
            void LogErrorEx ( const std::string & sMensaje, const std::exception & exInfo );
            void LogError ( const std::exception & exInfo );
            void LogAviso ( const std::exception & exInfo );

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

            /* LogError y LogAviso llevan guarda: si alguno de los argumentos es una
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

            template<typename... Args> auto LogAviso ( const std::string & sFormato, Args&&... argumentos )
             -> std::enable_if_t<!(... || std::is_base_of_v<std::exception, std::decay_t<Args>>)>
            {
            	LogAviso ( ToString ( sFormato, std::forward<Args> ( argumentos )... ) );
            }

			 
                }
            }
        }
    }
}

#endif
