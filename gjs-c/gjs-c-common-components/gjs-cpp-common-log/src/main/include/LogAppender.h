#ifndef _ORG_GJS_C_CC_CPP_LOG_LOG_APPENDER_H
#define _ORG_GJS_C_CC_CPP_LOG_LOG_APPENDER_H

#include <NivelLog.h>

#include <mutex>
#include <shared_mutex>





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

class LogAppender
{
	private:
		NivelLog 	nivel;
		bool		bActivo;
		/* Los que anotan toman el cerrojo compartido; quien necesita parar el
		   logado un momento ( una rotacion de ficheros, por ejemplo ) toma el
		   exclusivo con PausarLogado (). Los hilos duermen en vez de girar, y
		   el cerrojo se suelta solo aunque salte una excepcion, asi que no hay
		   forma de quedarse pausado para siempre. */
		std::shared_mutex	mtxPausa;
		
	public:
		LogAppender ();
		virtual ~LogAppender() = default;					

		bool Ini ();

		NivelLog Nivel ();
		void EstablecerNivel ( NivelLog nivel );
		void EstablecerNivel ( int iNivel );

		bool Activo ();
		void Activar ();
		void Desactivar ();

		void LogInfo ( const std::string & sMensaje );
		void LogDepuracion ( const std::string & sMensaje );
		void LogTraza ( const std::string & sMensaje );
		void LogAviso ( const std::string & sMensaje );
		void LogAvisoEx ( const std::string & sMensaje, const std::exception & exInfo );
		void LogError ( const std::string & sMensaje );
		void LogErrorEx ( const std::string & sMensaje, const std::exception & exInfo );
		void LogError ( const std::exception & exInfo );
		void LogForzado ( NivelLog nivel, const std::string & sMensaje );
		void LogForzadoEx ( NivelLog nivel, const std::string & sMensaje, const std::exception & exInfo );
		void LogForzado ( NivelLog nivel, const std::exception & exInfo );

		void Log ( NivelLog nivel, const std::string & sMensaje );
		void LogEx ( NivelLog nivel, const std::string & sMensaje, const std::exception & exInfo );


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

		template<typename... Args> auto LogForzado ( NivelLog nivel, const std::string & sFormato, Args&&... argumentos )
		 -> std::enable_if_t<!(... || std::is_base_of_v<std::exception, std::decay_t<Args>>)>
		{
			LogForzado ( nivel, ToString ( sFormato, std::forward<Args> ( argumentos )... ) );
		}

	protected:
		/* Detiene el logado mientras viva el cerrojo devuelto. Se usa asi:
		       {
		           auto lckPausa = PausarLogado ();
		           ...rotar el fichero...
		       }   // aqui se reanuda, pase lo que pase
		   No hace falta plazo maximo: no hay bandera que se pueda quedar puesta. */
		std::unique_lock < std::shared_mutex > PausarLogado ();

		virtual bool Inicializar () = 0;
		virtual std::string FormatearMensaje ( NivelLog nivel, const std::string & sMensaje ) = 0;
		virtual void LogInterno ( const std::string & sMensaje ) = 0;
};

                }
            }
        }
    }
}

#endif
