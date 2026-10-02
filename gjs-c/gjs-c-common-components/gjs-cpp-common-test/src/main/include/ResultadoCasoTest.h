#ifndef _ORG_GJS_C_CC_CPP_TEST_RESULTADO_CASO_TEST_H
#define _ORG_GJS_C_CC_CPP_TEST_RESULTADO_CASO_TEST_H


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

			enum ResultadoCasoTest
			{
				OK = 0,
				KO = 1,
				FAIL = 2,
				/* El caso no se puede ejecutar en esta plataforma. Ni correcto ni
				   erroneo: se cuenta aparte para no dar por bueno lo que no se ha
				   ejecutado. */
				NO_SOPORTADO = 3
			};

 				}
			}
		}
	}
}

#endif