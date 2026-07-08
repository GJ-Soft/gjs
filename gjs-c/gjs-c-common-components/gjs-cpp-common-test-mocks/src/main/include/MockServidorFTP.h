#ifndef _ORG_GJS_C_CC_CPP_TEST_MOCK_SERVIDOR_FTP_H
#define _ORG_GJS_C_CC_CPP_TEST_MOCK_SERVIDOR_FTP_H


#include <string>
#include <thread>


#include <Comando.h>
#include <ServidorFTP.h>


using namespace org::gjs::cpp::common;


namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {
				namespace test
				{
                    namespace mock
                    {

class MockServidorFTP : public ServidorFTP
{
public:
	MockServidorFTP( int iPuerto, int iPuertoDatos, const std::string & sSubdirectorioRaiz, const std::string & sFicheroUsuarios = "usuarios.info" );

	virtual ~MockServidorFTP();

private:
	void ComandoRecibido( Comando & comando );
	void ComandoProcesado( Comando & comando, bool & bResultado );
	void SesionIniciada( const std::string & sUsuario );
	void SesionFinalizada( const std::string & sUsuario );
	bool ExcepcionProducida( std::exception & ex );
	void ExcepcionProducidaEnPeticion( std::exception & ex );

};

                    }
				}
 			}
		}
	}
}

#endif
