#ifndef _ORG_GJS_C_CC_CPP_TEST_UTILESTEST_H
#define _ORG_GJS_C_CC_CPP_TEST_UTILESTEST_H


#include <string>
#include <vector>

#include <IComparable.h>



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

			void VerificarValor ( const std::string & sInfoCaso, const std::string & sResultado, const std::string & sEsperado, bool & bRes );
			void VerificarValor ( const std::string & sInfoCaso, const std::string & sResultado, const char * p_cEsperado, bool & bRes );			
			void VerificarValor ( const std::string & sInfoCaso, const char * p_cResultado, const char * p_cEsperado, bool & bRes );			
			void VerificarValor ( const std::string & sInfoCaso, long lResultado, long lEsperado, bool & bRes );			
			void VerificarValor ( const std::string & sInfoCaso, long lResultado, int iEsperado, bool & bRes );			
			void VerificarValor ( const std::string & sInfoCaso, int iResultado, int iEsperado, bool & bRes );			
			void VerificarValor ( const std::string & sInfoCaso, bool bResultado, bool bEsperado, bool & bRes );			
			void VerificarValor ( const std::string & sInfoCaso, double dResultado, double dEsperado, bool & bRes );			
			void VerificarValor ( const std::string & sInfoCaso, float fResultado, float fEsperado, bool & bRes );			
			void VerificarValor ( const std::string & sInfoCaso, const std::wstring & sResultado, const std::wstring & sEsperado, bool & bRes );
			void VerificarValor ( const std::string & sInfoCaso, const std::wstring & sResultado, const wchar_t * p_cEsperado, bool & bRes );			
			void VerificarValor ( const std::string & sInfoCaso, const wchar_t * p_cResultado, const wchar_t * p_cEsperado, bool & bRes );		

			void VerificarValor ( const std::string & sInfoCaso, IComparable & objResultado, IComparable & objEsperado, bool & bRes );			
			void VerificarValor ( const std::string & sInfoCaso, IComparable * objResultado, IComparable * objEsperado, bool & bRes );			
			
			void VerificarEsCierto ( const std::string & sInfoCaso, bool bResultado, bool & bRes );
			void VerificarEsFalso ( const std::string & sInfoCaso, bool bResultado, bool & bRes );
			void VerificarEsNulo ( const std::string & sInfoCaso, void * p_vResultado, bool & bRes );
			void VerificarNoEsNulo ( const std::string & sInfoCaso, void * p_vResultado, bool & bRes );

			void VerificarExistenciaFichero ( const std::string & sRuta, bool & bRes );
			void VerificarFichero ( const std::string & sRuta, int iLineasEsperadas, bool & bRes );
			void VerificarFichero ( const std::string & sRuta, std::vector<std::string> & vecLineas, bool & bRes );
			void VerificarFichero ( const std::string & sRuta, const char * p_cEsperado, bool & bRes );
			void VerificarFichero ( const std::string & sRuta, const std::string & sRutaEsperado, bool & bRes );

				}
 			}
		}
	}
}

#endif