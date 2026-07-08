#ifndef _ORG_GJS_C_CC_CPP_SERVIDOR_HTTP_H
#define _ORG_GJS_C_CC_CPP_SERVIDOR_HTTP_H



#include <ServidorIETF.h>
#include <HTTPConstantes.h>

#include <filesystem>




namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

			class ServidorHTTP : private ServidorIETF
			{
			private:
				// TODO: conjunto de versiones soportadas
				std::string 			sVersion;
				std::string 			sDirectorioRaiz;
				std::filesystem::path 	pathDirectorioRaiz;
				
			public:
				ServidorHTTP( const std::string & sDirectorio, const std::string & _sVersion = HTTP_VERSION_1_1, const std::string & sRutaContexto = "" );
				ServidorHTTP( int iPuerto, const std::string & sDirectorio, const std::string & _sVersion = HTTP_VERSION_1_1, const std::string & sRutaContexto = "" );
				virtual ~ServidorHTTP();
				
				int getPuerto();
				bool EsValido();

				void Iniciar();
				void Parar();				
				
			private:
				void ComandoRecibido( Comando & comando ) = 0;
				void ComandoProcesado( Comando & comando, bool & bResultado ) = 0;
				void SesionIniciada( const std::string & sUsuario );
				void SesionFinalizada( const std::string & sUsuario );

				bool EsComandoValido( Comando & comando );
				void ProcesarComandoSesion( Comando & comando, bool & bResponder, std::string & sRespuesta, bool & bResultadoProcesarComandoSesion, SocketAbierto * socket );
				
			};

 			}
		}
	}
}


#endif