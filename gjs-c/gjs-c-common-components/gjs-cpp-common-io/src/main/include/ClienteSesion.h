#ifndef _ORG_GJS_C_CC_CPP_CLIENTE_SESION_H
#define _ORG_GJS_C_CC_CPP_CLIENTE_SESION_H




#include <ClienteComandos.h>
#include <ResultadoComando.h>
#include <string>
#include <list>





namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {


			class ClienteSesion : public ClienteComandos
			{
			private:
				std::string sUsuario;
				std::string sClave;
				bool 		bSesionNecesaria = true;
				bool		bSesionAbierta = false;
				
			public:
				ClienteSesion( const std::string & sIP, int iPuerto, const std::string & _sUsuario = "", const std::string & _sClave = "" );
				virtual ~ClienteSesion();
				
				std::string getUsuario();
				std::string getClave();
				void setUsuario( const std::string & _sUsuario, const std::string & _sClave = "" );
				void setUsuarioAnonimo();
				
				bool EsValido();

				bool SesionAbierta();
				bool AbrirSesion();
				void CerrarSesion();
				
				void EnviarComando( Comando & comando, std::string & sRespuesta );
				void EnviarComando( std::string sComando, const std::initializer_list<std::string> & lisArgumentos, std::string & sRespuesta );
				void EnviarMensaje( const std::string & sMensaje, std::string & sRespuesta );
				void EnviarMensaje( const std::string & sMensaje );

			private:
				void EstablecerUsuario( const std::string & _sUsuario, const std::string & _sClave, bool bConstructor );
				virtual void ModificadoUsuario() = 0; 
				virtual std::list<ResultadoComando> & ComandoInicioSesion() = 0;
				virtual ResultadoComando & ComandoFinSesion() = 0;

			};

 			}
		}
	}
}

#endif