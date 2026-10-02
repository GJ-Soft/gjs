#ifndef _ORG_GJS_C_CC_CPP_TEST_TEST_H
#define _ORG_GJS_C_CC_CPP_TEST_TEST_H

#include <string>
#include <list>
#include <initializer_list>
#include <iostream>

#include <CasoTest.h>
#include <CasoTestAislado.h>
#include <ContextoTest.h>
#include <UtilesTest.h>
#include <BancoTests.h>


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

			// TODO: Añadir lista de parametros, y gestión automatizada de la llamada al procedimiento a testear
			class Test
			{
				private:
					std::string 		sNombreTest = "Test";
					PROCEDIMIENTO		procInicializarTest = NULL;
					PROCEDIMIENTO		procFinalizarTest = NULL;
					PROCEDIMIENTO_1CAD	procInicializarCasoTest = NULL;
					PROCEDIMIENTO_1CAD	procFinalizarCasoTest = NULL;

					std::list<CasoTest *> 	listCasos;

					//Simbolos		parametros;

					std::string			sDirInicial;
					bool 				bResultado = false;
					int 				iEjecutados = 0;
					int 				iCorrectos = 0;
					int 				iErroneos = 0;
					int 				iFallidos = 0;
					int 				iNoSoportados = 0;

				public:
					Test ( const std::string & sNombre, PROCEDIMIENTO procInicializar = NULL, PROCEDIMIENTO procFinalizar = NULL, PROCEDIMIENTO_1CAD procInicializarCaso = NULL, PROCEDIMIENTO_1CAD procFinalizarCaso = NULL );
					~Test ();

				private:
					void Inicializar ();
					void Finalizar ();
					void InicializarCaso ( const std::string & sId );
					void FinalizarCaso ( const std::string & sId );

				public:
					//void EstablecerParametros ( const std::initializer_list<std::string> & args );
					//void EstablecerParametros ( const std::list<std::string> & args );
					//void EstablecerParametros ( const std::vector<std::string> & args );
					//void EstablecerParametro ( std::string sParametro );

					void NuevoCaso ( const std::string & sNombre, FUNCION_BOOL funcion );
					void NuevoCasoAislado ( const std::string & sNombre, FUNCION_BOOL funcion, int iCodigoEsperado = 0 );
					int NumCasos ();

					bool Ejecutar ();

					bool Resultado ();
					int CasosEjecutados ();
					int CasosCorrectos ();
					int CasosErroneos ();
					int CasosFallidos ();
					int CasosNoSoportados ();

			};

				}
 			}
		}
	}
}

#endif
