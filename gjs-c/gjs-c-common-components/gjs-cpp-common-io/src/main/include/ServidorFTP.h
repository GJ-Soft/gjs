#ifndef _ORG_GJS_C_CC_CPP_SERVIDOR_FTP_H
#define _ORG_GJS_C_CC_CPP_SERVIDOR_FTP_H



#include <ServidorIETF.h>
#include <SocketServidor.h>
#include <SocketAbierto.h>

#include <filesystem>




namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

			// TODO: Subdirectorios por usuario + concurrencia (multiples usuarios en diferentes directorios)
			class ServidorFTP : private ServidorIETF
			{
			private:
				std::string 				sDirectorioRaiz;
				std::filesystem::path 		pathDirectorioRaiz;
				bool						bModoBinario = false;
				int							iPuertoDatos = 0;
				common::SocketServidor *	sockDatos = NULL;

			public:
				ServidorFTP( const std::string & sDirectorio, const std::string & sRutaUsuarios = "", const std::string & sRutaContexto = "" );
				ServidorFTP( int iPuerto, int iPuertoDatos, const std::string & sDirectorio, const std::string & sRutaUsuarios = "", const std::string & sRutaContexto = "" );
				virtual ~ServidorFTP();

				int getPuerto();
				int getPuertoDatos();
				void setPuertoDatos( int iPuerto );
				bool EsValido();

				void Iniciar();
				void Parar();

			private:
				void ComandoRecibido( Comando & comando ) = 0;
				void ComandoProcesado( Comando & comando, bool & bResultado ) = 0;
				void SesionIniciada( const std::string & sUsuario ) = 0;
				void SesionFinalizada( const std::string & sUsuario ) = 0;

				bool EsComandoValido( Comando & comando );
				void ProcesarComandoSesion( Comando & comando, bool & bResponder, std::string & sRespuesta, bool & bResultadoProcesarComandoSesion, SocketAbierto * socket );

			};

 			}
		}
	}
}

#endif
