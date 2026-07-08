#ifndef _ORG_GJS_C_CC_CPP_TEST_CASOTESTAISLADO_H
#define _ORG_GJS_C_CC_CPP_TEST_CASOTESTAISLADO_H

#include <CasoTest.h>
#include <CppBase.h>

#include <string>
#include <cstdlib>


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

			class CasoTestAislado : public CasoTest
			{
				private:
					int iCodigo = 0;
					
				public:
					CasoTestAislado ( const std::string & sId, FUNCION_BOOL funcion, int iCodigoEsperado = EXIT_SUCCESS );
					virtual ~CasoTestAislado () {};
					
				public:
					ResultadoCasoTest Ejecutar () override; 
			};

				}
 			}
		}
	}
}

#endif