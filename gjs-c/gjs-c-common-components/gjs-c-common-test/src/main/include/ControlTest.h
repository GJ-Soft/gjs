#ifndef _ORG_GJS_C_CC_C_TEST_UTILESTEST_H
#define _ORG_GJS_C_CC_C_TEST_UTILESTEST_H



void VerificarValor ( const char * p_cInfoCaso, const char * p_cResultado, const char * p_cEsperado, int & iRes );
void VerificarValor ( const char * p_cInfoCaso, const char * p_cResultado, const char * p_cEsperado, int & iRes );			
void VerificarValor ( const char * p_cInfoCaso, const char * p_cResultado, const char * p_cEsperado, int & iRes );			
void VerificarValor ( const char * p_cInfoCaso, long lResultado, long lEsperado, int & iRes );			
void VerificarValor ( const char * p_cInfoCaso, long lResultado, int iEsperado, int & iRes );			
void VerificarValor ( const char * p_cInfoCaso, int iResultado, int iEsperado, int & iRes );			
void VerificarValor ( const char * p_cInfoCaso, double dResultado, double dEsperado, int & iRes );			
void VerificarValor ( const char * p_cInfoCaso, float fResultado, float fEsperado, int & iRes );			
void VerificarValor ( const char * p_cInfoCaso, const wchar * p_cResultado, const wchar * p_cEsperado, int & iRes );
void VerificarValor ( const char * p_cInfoCaso, const wchar * p_cResultado, const wchar_t * p_cEsperado, int & iRes );			
void VerificarValor ( const char * p_cInfoCaso, const wchar_t * p_cResultado, const wchar_t * p_cEsperado, int & iRes );		

void VerificarEsCierto ( const char * p_cInfoCaso, int iResultado, int & iRes );
void VerificarEsFalso ( const char * p_cInfoCaso, int iResultado, int & iRes );
void VerificarEsNulo ( const char * p_cInfoCaso, void * p_vResultado, int & iRes );
void VerificarNoEsNulo ( const char * p_cInfoCaso, void * p_vResultado, int & iRes );

void VerificarExistenciaFichero ( const char * p_cRuta, int & iRes );
void VerificarFichero ( const char * p_cRuta, int iLineasEsperadas, int & iRes );
void VerificarFichero ( const char * p_cRuta, std::vector<std::string> & vecLineas, int & iRes );
void VerificarFichero ( const char * p_cRuta, const char * p_cEsperado, int & iRes );
void VerificarFichero ( const char * p_cRuta, const char * p_cRutaEsperado, int & iRes );


#endif