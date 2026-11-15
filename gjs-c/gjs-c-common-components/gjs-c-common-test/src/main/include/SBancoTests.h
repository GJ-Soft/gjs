#ifndef _ORG_GJS_C_CC_C_TEST_BANCOTEST_H
#define _ORG_GJS_C_CC_C_TEST_BANCOTEST_H



#include <Funciones.h>
#include <SConjuntoReferencias.h>






typedef struct
{
	SConjuntoReferencias * p_cnjTests;

} SBancoTests;

SBancoTests * SBanTstCrear ();
void SBanTstDestruir ( SBancoTests ** p_p_bantstObj );

void SBanTstNuevoTest ( SBancoTests * p_bantstObj, const char * p_cNombre, PFUNINTV p_fTest );
int SBanTstNumTests ( SBancoTests * p_bantstObj );

int SBanTstEjecutar ( SBancoTests * p_bantstObj );
int SBanTstEjecutarTest ( SBancoTests * p_bantstObj, const char * p_cTest );
int SBanTstEjecutarTextExe ( SBancoTests * p_bantstObj, int argc, char * argv[] );



#endif
