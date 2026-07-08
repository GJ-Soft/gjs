#ifndef _ORG_GJS_C_CC_CPP_GESTOR_SESIONES_H
#define _ORG_GJS_C_CC_CPP_GESTOR_SESIONES_H

#include <map>
#include <thread>
#include <ControlConcurrencia.h>



namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

			// TODO: Añadir demonio limpiador de sesiones antiguas
			class GestorSesiones : private ControlConcurrencia
			{
			private:
				std::map<std::string, std::pair<time_t, time_t>>	mapSesiones;
				std::map<std::thread::id, std::string> 				mapHilos;
				
			public:
				GestorSesiones ();
				virtual ~GestorSesiones ();
				
			public:
				int NumSesiones ();
				bool Preparar( const std::string & sUsuario );
				bool Abrir( const std::string & sUsuario );
				void Cerrar( const std::string & sUsuario );				
				void Actividad( const std::string & sUsuario );	
				void Cerrar();				
				void Actividad();	
				
				bool EstaAbierta( const std::string & sUsuario );
				bool EstaAbierta();
				time_t TiempoInicio( const std::string & sUsuario );
				time_t TiempoTranscurrido( const std::string & sUsuario );
				time_t TiempoActividad( const std::string & sUsuario );
				time_t TiempoInicio();
				time_t TiempoTranscurrido();
				time_t TiempoActividad();

				std::string getUsuario( std::thread::id idHilo );
				std::string getUsuario();
				void setUsuario( std::string sValor, std::thread::id idHilo );
				void setUsuario( std::string sValor );

				void Limpiar ();
				
			};
		
 			}
		}
	}
}




#endif