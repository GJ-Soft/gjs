
#ifndef _ORG_GJS_C_CC_SFICALEATORIO_H
#define _ORG_GJS_C_CC_SFICALEATORIO_H






#include <Base.h>
#include <SRuta.h>





typedef struct
{
	char *			p_cRuta;	
	int				iAbierto;
	FILE *			p_fObj;
} SFicAleatorio;






SFicAleatorio * SFicAlCrear ( const char * p_cRuta ); 
SFicAleatorio * SFicAlCrearExt ( const char * p_cDir, const char * p_cFic );
SFicAleatorio * SFicAlCrearRuta ( SRuta * p_rutRuta ); 

void SFicAlDestruir ( SFicAleatorio ** p_p_ficObj );
void SFicAlEliminar ( SFicAleatorio ** p_p_ficObj );

int SFicAlEsValido ( SFicAleatorio * p_ficObj ); 
const char * SFicAlRuta ( SFicAleatorio * p_ficObj ); 
char * SFicAlDirectorio ( SFicAleatorio * p_ficObj ); 
char * SFicAlFichero ( SFicAleatorio * p_ficObj ); 
int SFicAlEstablecerRuta ( SFicAleatorio * p_ficObj, const char * p_cRuta );
int SFicAlEstablecerRutaExt ( SFicAleatorio * p_ficObj, const char * p_cDir, const char * p_cFic );

int SFicAlAbrir ( SFicAleatorio * p_ficObj );
int SFicAlAbrirExt ( SFicAleatorio * p_ficObj, int iVaciar );
int SFicAlCerrar ( SFicAleatorio * p_ficObj );

int SFicAlEstaAbierto ( SFicAleatorio * p_ficObj );

unsigned long SFicAlTam  ( SFicAleatorio * p_ficObj );
int SFicAlEstaVacio ( SFicAleatorio * p_ficObj );
unsigned long SFicAlPos ( SFicAleatorio * p_ficObj );
int SFicAlPosicionar ( SFicAleatorio * p_ficObj, unsigned long ulPos );
int SFicAlMoverAInicio ( SFicAleatorio * p_ficObj );
int SFicAlMoverAInicioExt ( SFicAleatorio * p_ficObj, int iSaltarNumMagico );
int SFicAlMoverAFinal ( SFicAleatorio * p_ficObj );
int SFicAlEstaEnFinal ( SFicAleatorio * p_ficObj );

byte SFicAlLeer ( SFicAleatorio * p_ficObj );
int SFicAlLeerBuffer ( SFicAleatorio * p_ficObj, byte * p_byContenido, unsigned long * p_ulTam );
int SFicAlEscribir ( SFicAleatorio * p_ficObj, byte byValor );
int SFicAlEscribirBuffer ( SFicAleatorio * p_ficObj, byte * p_byContenido, unsigned long * p_ulTam );

byte SFicAlLeerEn ( SFicAleatorio * p_ficObj, unsigned long ulPos );
int SFicAlLeerBufferEn ( SFicAleatorio * p_ficObj, unsigned long ulPos, byte * p_byContenido, unsigned long * p_ulTam );
int SFicAlEscribirEn ( SFicAleatorio * p_ficObj, unsigned long ulPos, byte byValor );
int SFicAlEscribirBufferEn ( SFicAleatorio * p_ficObj, unsigned long ulPos, byte * p_byContenido, unsigned long * p_ulTam );

unsigned long SFicAlNumeroMagico ( SFicAleatorio * p_ficObj );
int SFicAlEstablecerNumeroMagico ( SFicAleatorio * p_ficObj, unsigned long ulNumero );


#endif

