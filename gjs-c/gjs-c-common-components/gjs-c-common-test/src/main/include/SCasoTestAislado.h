#ifndef _ORG_GJS_C_CC_C_TEST_CASOTESTAISLADO_H
#define _ORG_GJS_C_CC_C_TEST_CASOTESTAISLADO_H

#include <Funciones.h>

#include <SCasoTestSimple.h>

// Los test aislados están pensados para testear ejecutables directmente o llamando a los
// main en la función del caso
// TODO: Está pendiente de terminar

typedef struct
{
	SCasoTestSimple * 	p_caststsObj;
	int					iCodigo;

} SCasoTestAislado;

SCasoTestAislado * SCasTstaCrear ( const char * p_cId, PFUNINTV p_fTest, int iCodigoEsperado );
//SCasoTestAislado * SCasTstaCrearPruebaExe ( const char * p_cId, const char * p_cExe, int iCodigoEsperado );
void SCasTstaDestruir ( SCasoTestAislado ** p_p_caststaObj );

const char * SCasTstaObtenerId ( SCasoTestAislado * p_caststaObj );
int SCasTstaEjecutar ( SCasoTestAislado * p_caststaObj );


#endif