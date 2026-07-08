#ifndef _ORG_GJS_C_CC_CPP_SERVIDOR_SESION_H
#define _ORG_GJS_C_CC_CPP_SERVIDOR_SESION_H



#include <ServidorComandos.h>
#include <GestorUsuarios.h>
#include <GestorSesiones.h>
#include <SocketAbierto.h>





namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

			class ServidorSesion : public ServidorComandos
			{
			private:
				GestorUsuarios 	gestorUsuarios;
				GestorSesiones 	gestorSesiones;
				bool 			bSesionNecesaria = true;
				bool			bPermiteAnonimo = false;
				
			public:
				ServidorSesion( int iPuerto, const std::string & sRutaUsuarios = "", const std::string & sRutaContexto = "", bool _bPermiteAnonimo = false );
				virtual ~ServidorSesion();

				virtual bool EsValido();
			
			protected:
				bool RequiereSesion();
				
			private:
				void ProcesarComando( Comando & comando, bool & bResponder, std::string & sRespuesta, bool & bResultado, SocketAbierto * socket );

				virtual std::string MensajeSesionAbierta() = 0;
				virtual std::string MensajeSesionCerrada() = 0;
				virtual std::string MensajeFaltaClave() = 0;
				virtual std::string MensajeImposibleAperturaSesion() = 0;
				virtual std::string MensajeUsuarioInvalido() = 0;
				virtual std::string MensajeSesionNoAbierta() = 0;
				
				virtual bool EsComandoInicioSesion( Comando & comando, std::string & sUsuario, std::string & sClave ) = 0;
				virtual bool EsComandoFinSesion( Comando & comando ) = 0;
				virtual void SesionIniciada( const std::string & sUsuario ); 
				virtual void SesionFinalizada( const std::string & sUsuario ); 
				virtual void ProcesarComandoSesion( Comando & comando, bool & bResponder, std::string & sRespuesta, bool & bResultado, SocketAbierto * socket ) = 0;
				
			};

 			}
		}
	}
}


#endif