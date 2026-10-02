#ifndef _ORG_GJS_C_CC_SINDICELITERALES_H
#define _ORG_GJS_C_CC_SINDICELITERALES_H








#include <SConjuntoPtr.h>
#include <SLocalizador.h>





typedef struct
{
	SConjuntoPtr * 	p_cnjpDatos;

} SIndiceLiterales;





SIndiceLiterales * SIndLitCrear ();

void SIndLitDestruir ( SIndiceLiterales ** p_p_indlObj );

int SIndLitEsValido ( SIndiceLiterales * p_indlObj );

int SIndLitNumElementos ( SIndiceLiterales * p_indlObj );
int SIndLitEstaVacio ( SIndiceLiterales * p_indlObj );

SLocalizador * SIndLitElemento ( SIndiceLiterales * p_indlObj, int iElem );
const char * SIndLitElementoClave ( SIndiceLiterales * p_indlObj, int iElem );
unsigned long SIndLitElementoPosicion ( SIndiceLiterales * p_indlObj, int iElem );


int SIndLitInsertar ( SIndiceLiterales * p_indlObj, SLocalizador * p_lczDato );
int SIndLitInsertarExt ( SIndiceLiterales * p_indlObj, const char * p_cClave, unsigned long ulPosicion );
int SIndLitEliminar ( SIndiceLiterales * p_indlObj, int iElem );
int SIndLitEliminarClave ( SIndiceLiterales * p_indlObj, const char * p_cClave );
int SIndLitVaciar ( SIndiceLiterales * p_indlObj );

int SIndLitExiste ( SIndiceLiterales * p_indlObj, const char * p_cClave );
int SIndLitBuscar ( SIndiceLiterales * p_indlObj, const char * p_cClave );
unsigned long SIndLitPosicion ( SIndiceLiterales * p_indlObj, const char * p_cClave );

#endif