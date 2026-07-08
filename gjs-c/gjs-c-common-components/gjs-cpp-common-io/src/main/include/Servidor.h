#ifndef _ORG_GJS_C_CC_CPP_SERVIDOR_H
#define _ORG_GJS_C_CC_CPP_SERVIDOR_H



#include <SocketServidor.h>
#include <SocketAtencion.h>
#include <Propiedades.h>
#include <Contador.h>
 



namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

			class Servidor : private SocketServidor, public Contador 
			{				
			private:
				Propiedades 						contexto;
				bool								bEjecucion = false;
				bool								bParar = false;
				std::thread *						thServidor = NULL;
				
			public:
				Servidor( int iPuerto, const std::string & sRutaContexto = "" );
				virtual ~Servidor();
				
				int getPuerto();
				std::string getHost();
				virtual bool EsValido();

				void Iniciar();
				void Parar();				
				
			protected:
				Propiedades Contexto();
				int Enviar( const std::string & sMensaje );
				
			private:
				void RutinaAtencion();
				void RutinaPeticion( SocketAtencion * socket );
				
				virtual void PeticionRecibida(); 
				virtual void PeticionFinalizada( bool bResultado ); 
				virtual void ProcesarMensaje( const std::string & sMensaje, bool & bResponder, std::string & sRespuesta, bool & bResultado, bool & bFin, SocketAtencion * socket ) = 0;

			protected:
				virtual bool ExcepcionProducida( const std::exception & ex );
				virtual void ExcepcionProducidaEnPeticion( const std::exception & ex );
				
			};

 			}
		}
	}
}


#endif