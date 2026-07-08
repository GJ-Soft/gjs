#ifndef _ORG_GJS_C_CC_C_TEST_UTILESTEST_H
#define _ORG_GJS_C_CC_C_TEST_UTILESTEST_H


#include <SListaCadenas.h>



int LanzarEjecutable ( const char * p_cExe, const char * p_cParametros );


void VerificarValorLit ( const char * p_cInfoCaso, const char * p_cResultado, const char * p_cEsperado, int * iRes );
void VerificarValorEnteroLargo ( const char * p_cInfoCaso, long lResultado, long lEsperado, int * iRes );			
void VerificarValorEntero ( const char * p_cInfoCaso, int iResultado, int iEsperado, int * iRes );			
void VerificarValorRealDoble ( const char * p_cInfoCaso, double dResultado, double dEsperado, int * iRes );			
void VerificarValorReal ( const char * p_cInfoCaso, float fResultado, float fEsperado, int * iRes );			

void VerificarEsCierto ( const char * p_cInfoCaso, int iResultado, int * iRes );
void VerificarEsFalso ( const char * p_cInfoCaso, int iResultado, int * iRes );
void VerificarEsNulo ( const char * p_cInfoCaso, void * p_vResultado, int * iRes );
void VerificarNoEsNulo ( const char * p_cInfoCaso, void * p_vResultado, int * iRes );

 
#endif