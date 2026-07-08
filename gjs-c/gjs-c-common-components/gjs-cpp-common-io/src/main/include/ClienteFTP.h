#ifndef _ORG_GJS_C_CC_CPP_CLIENTE_FTP_H
#define _ORG_GJS_C_CC_CPP_CLIENTE_FTP_H


#include <string>

#include <ClienteIETF.h>
#include <SocketCliente.h>
#include <PuertosIETF.h>


using namespace org::gjs::cpp::common;


namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

			class ClienteFTP : private ClienteIETF
			{
			private:
				bool 			bModoActivo = false;
				bool 			bModoBinario = false;
				int				iPuertoDatos = 0;

			public:
				ClienteFTP ( const std::string & sIP, int iPuerto = IETF_PUERTO_FTP );
				ClienteFTP ( const std::string & sIP, int iPuerto, const std::string & _sUsuario, const std::string & _sClave = "" );
				virtual ~ClienteFTP ();

				bool EsValido();

				bool SesionAbierta();
				bool AbrirSesion();
				void CerrarSesion();

				bool isModoActivo();
				bool isModoPasivo();
				void setModoActivo( int iPuerto );
				void setModoPasivo();

				bool isAscii();
				bool isBinario();
				bool setAscii();
				bool setBinario();

				bool EstadoServidor( std::string & sResultado );
				bool PingServidor();
				std::string InfoSistemaServidor();

				std::string DirectorioRemoto();
				bool CambiarDirectorioRemoto( const std::string & sSubdirectorio );
				bool CrearDirectorioRemoto( const std::string & sSubdirectorio );

				bool ContenidoDirectorioRemoto( std::vector<std::string> & vecContenido );

				bool BajarFichero( const std::string & sFichero, const std::string & sRutaLocal );
				bool SubirFichero( const std::string & sFichero, const std::string & sRutaLocal );

			private:
				void PrepararSocketDatos();
				common::SocketCliente * AbrirSocketDatos();
				void CerrarSocketDatos( common::SocketCliente ** sockDatos );
				void ExcepcionProducida( const std::exception & ex );
			};

 			}
		}
	}
}


#endif
