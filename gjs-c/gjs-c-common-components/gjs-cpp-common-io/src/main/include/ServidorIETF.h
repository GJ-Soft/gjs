#ifndef _ORG_GJS_C_CC_CPP_SERVIDOR_IETF_H
#define _ORG_GJS_C_CC_CPP_SERVIDOR_IETF_H



#include <ServidorSesion.h>
#include <string>
#include <set>
#include <list>
#include <initializer_list>




namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

			class ServidorIETF : public ServidorSesion
			{
			private:
				std::set<std::string> * setComandos = NULL;
			
			public:
				ServidorIETF( int iPuerto, const std::string & sRutaUsuarios = "", const std::string & sRutaContexto = "", bool _bPermiteAnonimo = false );
				ServidorIETF( int iPuerto, const std::list<std::string> & lisComandos, const std::string & sRutaUsuarios = "", const std::string & sRutaContexto = "",
								bool _bPermiteAnonimo = false );
				ServidorIETF( int iPuerto, const std::initializer_list<std::string> & lisComandos, const std::string & sRutaUsuarios = "", const std::string & sRutaContexto = "",
								bool _bPermiteAnonimo = false );
				virtual ~ServidorIETF();
			
				void addComando( const std::string & sComando );
				void addComandos( const std::list<std::string> & lisComandos );
				void addComandos( const std::initializer_list<std::string> & lisComandos );
				bool isComando( const std::string & sComando );

			protected:
				std::string MensajeOk();
				
				virtual bool EsComandoValido( Comando & comando );
				
			private:
				std::string MensajeComandoFin();
				std::string MensajeComandoInvalido();
				std::string MensajeErrorSintactico();
				std::string MensajeSesionAbierta();
				std::string MensajeSesionCerrada();
				std::string MensajeFaltaClave();
				std::string MensajeImposibleAperturaSesion();
				std::string MensajeUsuarioInvalido();
				std::string MensajeSesionNoAbierta();

				bool EsComandoFin( Comando & comando, bool & bResponder );
				bool EsComandoInicioSesion( Comando & comando, std::string & sUsuario, std::string & sClave );
				bool EsComandoFinSesion( Comando & comando );				
			};

 			}
		}
	}
}


#endif