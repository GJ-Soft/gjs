#ifndef _ORG_GJS_C_CC_SSECUENCIALITERALES_H
#define _ORG_GJS_C_CC_SSECUENCIALITERALES_H








#include <SSecuenciaPtr.h>
#include <SListaLiterales.h>



// NOTA: Siempre duplica la cadena.


typedef struct
{
	SSecuenciaPtr * p_secDatos;

} SSecuenciaLiterales;





SSecuenciaLiterales * SSecLitCrear ();
SSecuenciaLiterales * SSecLitCrearDesdeLista ( SListaLiterales * p_lisValores );


void SSecLitDestruir ( SSecuenciaLiterales ** p_p_secObj );

int SSecLitEsValida ( SSecuenciaLiterales * p_secObj );

int SSecLitNumElementos ( SSecuenciaLiterales * p_secObj );
int SSecLitEstaVacia ( SSecuenciaLiterales * p_secObj );

char * SSecLitElemento ( SSecuenciaLiterales * p_secObj, int iElem );

int SSecLitInsertar ( SSecuenciaLiterales * p_secObj, const char * p_cDato );
int SSecLitEliminar ( SSecuenciaLiterales * p_secObj, int iElem );
int SSecLitVaciar ( SSecuenciaLiterales * p_secObj );

int SSecLitExiste ( SSecuenciaLiterales * p_secObj, const char * p_cDato );
int SSecLitBuscar ( SSecuenciaLiterales * p_secObj, const char * p_cDato );
int SSecLitRepeticiones ( SSecuenciaLiterales * p_secObj, const char * p_cDato );
int SSecLitBuscarPrimero ( SSecuenciaLiterales * p_secObj, const char * p_cDato );
int SSecLitBuscarSiguiente ( SSecuenciaLiterales * p_secObj, const char * p_cDato, int iPos );

SSecuenciaLiterales * SSecLitExtraerUnicos ( SSecuenciaLiterales * p_secObj );
int SSecLitTieneRepetidos ( SSecuenciaLiterales * p_secObj );

SSecuenciaPtr * SSecLitSecuencia ( SSecuenciaLiterales * p_secObj );
SListaPtr * SSecLitLista ( SSecuenciaLiterales * p_secObj );


#endif