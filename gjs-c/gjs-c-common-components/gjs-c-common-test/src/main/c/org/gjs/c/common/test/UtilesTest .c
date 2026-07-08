#include "UtilesTest.h"
#include "CTestConfig.h"


int LanzarEjecutable ( const char * p_cExe, const char * p_cParametros )
{
	return ( SisEjecutarComando ( p_cExe, p_cParametros, 0 ) );
}

void VerificarValorLit ( const char * p_cInfoCaso, const char * p_cResultado, const char * p_cEsperado, int * iRes )
{
	AplicLogAnotar ( "    Caso: [%s]: Resultado: [%s]", p_cInfoCaso, p_cResultado );
	if ( CadLongitud ( p_cResultado ) != CadLongitud ( p_cEsperado ) )
	{
		AplicLogAnotarError ( "    -> longitud incorrecta (esperada %d)", CadLongitud ( p_cEsperado ) );
		*iRes = 0;
	}	
	if ( CadComparar ( p_cResultado, p_cEsperado ) == COMP_IGUAL )
	{
		AplicLogAnotarError ( "    -> valor inesperado (esperado [%s]", p_cEsperado );
		*iRes = 0;
	}	
}

void VerificarValorEnteroLargo ( const char * p_cInfoCaso, long lResultado, long lEsperado, int * iRes )
{
	AplicLogAnotar ( "    Caso: [%s]: Resultado: [%ld]", p_cInfoCaso, lResultado );
	if ( lResultado != lEsperado )
	{
		AplicLogAnotarError ( "    -> valor inesperado" );
		*iRes = 0;
	}	
}

void VerificarValorEntero ( const char * p_cInfoCaso, int iResultado, int iEsperado, int * iRes )		
{
	VerificarValorEnteroLargo ( p_cInfoCaso, (long) iResultado, (long) iEsperado, iRes );
}

void VerificarValorRealDoble ( const char * p_cInfoCaso, double dResultado, double dEsperado, int * iRes )
{
	AplicLogAnotar ( "    Caso: [%s]: Resultado: [%lf]", p_cInfoCaso, dResultado );
	if ( MatEsIgual ( dResultado, dEsperado ) == 0 )
	{
		AplicLogAnotarError ( "    -> valor inesperado" );
		*iRes = 0;
	}	
}

void VerificarValorReal ( const char * p_cInfoCaso, float fResultado, float fEsperado, int * iRes )		
{
	VerificarValorRealDoble ( p_cInfoCaso, (double) fResultado, (double) fEsperado, iRes );
}

void VerificarEsCierto ( const char * p_cInfoCaso, int iResultado, int * iRes )
{
	AplicLogAnotar ( "    Caso: [%s]: Resultado: [%d]", p_cInfoCaso, iResultado );
	if ( iResultado == 0 ) 
	{
		AplicLogAnotarError ( "    -> valor inesperado (esperado [1]" );
		*iRes = 0;
	}	
}

void VerificarEsFalso ( const char * p_cInfoCaso, int iResultado, int * iRes )
{
	AplicLogAnotar ( "    Caso: [%s]: Resultado: [%d]", p_cInfoCaso, iResultado );
	if ( iResultado == 1 ) 
	{
		AplicLogAnotarError ( "    -> valor inesperado (esperado [0])" );
		*iRes = 0;
	}	
}

void VerificarEsNulo ( const char * p_cInfoCaso, void * p_vResultado, int * iRes )
{
	AplicLogAnotar ( "    Caso: [%s]: Resultado: [%ld]", p_cInfoCaso, p_vResultado );
	if ( p_vResultado != NULL ) 
	{
		AplicLogAnotarError ( "    -> valor inesperado (esperado [NULO])"  );
		*iRes = 0;
	}	
}

void VerificarNoEsNulo ( const char * p_cInfoCaso, void * p_vResultado, int * iRes )
{
	AplicLogAnotar ( "    Caso: [%s]: Resultado: [%ld]", p_cInfoCaso, p_vResultado );
	if ( p_vResultado == NULL ) 
	{
		AplicLogAnotarError ( "    -> valor inesperado (esperado [NO NULO])" );
		*iRes = 0;
	}	
}

