#ifndef _ORG_GJS_C_CC_C_TEST_TEST_H
#define _ORG_GJS_C_CC_C_TEST_TEST_H

#include <Funciones.h>
#include <SListaPtr.h>

#include <SCasoTest.h>
#include <SCasoTestAislado.h>
#include <UtilesTest.h>
#include <STest.h>


// TODO: Añadir lista de parametros, y gestión automatizada de la llamada al procedimiento a testear
typedef struct
{
	char *		p_cNombreTest;
	PPRCV		procInicializarTest;
	PPRCV		procFinalizarTest;
	PPRCT		procInicializarCasoTest;
	PPRCT		procFinalizarCasoTest;

	SListaPtr *	p_lisCasos;

	char *		p_cDirInicial;
	int 		iResultado;
	int 		iEjecutados;
	int 		iCorrectos;
	int 		iErroneos;
	int 		iFallidos;

} STest;


STest * STestCrear ( const char * p_cNombre );
STest * STestCrearExt ( const char * p_cNombre, PPRCV procInicializar, PPRCV procFinalizar, PPRCT procInicializarCaso, PPRCT procFinalizarCaso  );
void STestDestruir ( STest ** p_p_testObj );

void STestInicializar ( STest * p_testObj );
void STestFinalizar ( STest * p_testObj );
void STestInicializarCaso ( STest * p_testObj, const char * p_cId );
void STestFinalizarCaso ( STest * p_testObj, const char * p_cId );

void STestNuevoCaso ( STest * p_testObj, const char * p_cNombre, PFUNINTV p_fTest );
void STestNuevoCasoAislado ( STest * p_testObj, const char * p_cNombre, PFUNINTV p_fTest, int iCodigoEsperado );
int STestNumCasos ( STest * p_testObj );

int STestEjecutar ( STest * p_testObj );

int Resultado ( STest * p_testObj );
int CasosEjecutados ( STest * p_testObj );
int CasosCorrectos ( STest * p_testObj );
int CasosErroneos ( STest * p_testObj );
int CasosFallidos ( STest * p_testObj );


int STestEjecutar ( STest * p_testObj );
int STestEjecutarTest ( STest * p_testObj, const char * p_cTest );
int STestEjecutarTextExe ( STest * p_testObj, int argc, char * argv[] );

#endif
