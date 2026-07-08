#ifndef _ORG_GJS_C_CC_C_TEST_CASOTESTSIMPLE_H
#define _ORG_GJS_C_CC_C_TEST_CASOTESTSIMPLE_H

#include <ResultadoCasoTest.h>
#include <Funciones.h>




typedef struct
{
	char * 		p_cIdCaso;
	PFUNINTV 	p_fTestCaso;

} SCasoTestSimple;

SCasoTestSimple * SCasTstsCrear ( const char * p_cId, PFUNINTV p_fTest );
void SCasTstsDestruir ( SCasoTestSimple ** p_p_caststsObj );
		
const char * SCasTstsObtenerId ( SCasoTestSimple * p_caststsObj );
int SCasTstsEjecutar ( SCasoTestSimple * p_caststsObj );


#endif