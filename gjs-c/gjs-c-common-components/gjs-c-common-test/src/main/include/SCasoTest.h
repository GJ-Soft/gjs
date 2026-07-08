#ifndef _ORG_GJS_C_CC_C_TEST_CASOTEST_H
#define _ORG_GJS_C_CC_C_TEST_CASOTEST_H

#include <SCasoTestSimple.h>
#include <SCasoTestAislado.h>




typedef struct
{
	int iTipo;  // 0 = SCasoTestSimple, 1 = SCasoTestAislado
	union
	{
		SCasoTestSimple * 	p_caststsObj;
		SCasoTestAislado * 	p_caststaObj;
	};

} SCasoTest;

SCasoTest * SCasTstCrearSimple ( const char * p_cId, PFUNINTV p_fTest );
SCasoTest * SCasTstCrearAislado ( const char * p_cId, PFUNINTV p_fTest, int iCodigoEsperado );
SCasoTest * SCasTstEncapsularSimple ( SCasoTestSimple * p_caststsObj );
SCasoTest * SCasTstEncapsularAislado ( SCasoTestAislado * p_caststsObj );
void SCasTstDestruir ( SCasoTest ** p_p_caststObj );
		
const char * SCasTstObtenerId ( SCasoTest * p_caststObj );
int SCasTstEjecutar ( SCasoTest * p_caststObj );

int SCasTstEsCasoSimple ( SCasoTest * p_caststObj );
int SCasTstEsCasoAislado ( SCasoTest * p_caststObj );
SCasoTestSimple * SCasTstCasoSimple ( SCasoTest * p_caststObj );
SCasoTestAislado * SCasTstCasoAislado ( SCasoTest * p_caststObj );

#endif