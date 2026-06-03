
#ifndef _ORG_GJS_C_CC_SDIVISOR_H
#define _ORG_GJS_C_CC_SDIVISOR_H





#include <SSecuenciaLiterales.h>


typedef struct 
{
	char					cSeparador;	
    char *            		p_cTexto;
    SSecuenciaLiterales *   p_secPartes;

} SDivisor;



SDivisor * SDivCrear ( char cSeparador ); 
SDivisor * SDivCrearExt ( char cSeparador, const char * p_cTexto ); 

void SDivDestruir ( SDivisor ** p_p_divObj );

int SDivEsValido ( SDivisor * p_divObj ); 
int SDivTieneTexto ( SDivisor * p_divObj ); 

char SDivSeparador ( SDivisor * p_divObj );
const char * SDivTexto ( SDivisor * p_divObj );
int SDivInicializar ( SDivisor * p_divObj, const char * p_cTexto );
int SDivInicializarExt ( SDivisor * p_divObj, char cSeparador, const char * p_cTexto );

SSecuenciaLiterales * SDivPartes ( SDivisor * p_divObj );
int SDivNumPartes ( SDivisor * p_divObj );
const char * SDivParte ( SDivisor * p_divObj, int iParte );
char * SDivSubtexto ( SDivisor * p_divObj );
char * SDivSubtextoExt ( SDivisor * p_divObj, int iAvances );
SDivisor * SDivSubdivisor ( SDivisor * p_divObj );
SDivisor * SDivSubdivisorExt ( SDivisor * p_divObj, int iAvances );




#endif

