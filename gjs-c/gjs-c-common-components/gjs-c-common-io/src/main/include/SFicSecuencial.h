#ifndef _ORG_GJS_C_CC_SFICSECUENCIAL_H
#define _ORG_GJS_C_CC_SFICSECUENCIAL_H







#include <Base.h>
#include <ModosApertura.h>
#include <SRuta.h>



typedef struct
{
	char *			p_cRuta;	
	int				iAbierto;
	int				iModo;
	FILE *			p_fObj;
} SFicSecuencial;






SFicSecuencial * SFicSecCrear ( const char * p_cRuta ); 
SFicSecuencial * SFicSecCrearExt ( const char * p_cDir, const char * p_cFic );
SFicSecuencial * SFicSecCrearRuta ( SRuta * p_rutRuta ); 

void SFicSecDestruir ( SFicSecuencial ** p_p_ficObj );
void SFicSecEliminar ( SFicSecuencial ** p_p_ficObj );

int SFicSecEsValido ( SFicSecuencial * p_ficObj ); 
const char * SFicSecRuta ( SFicSecuencial * p_ficObj ); 
char * SFicSecDirectorio ( SFicSecuencial * p_ficObj ); 
char * SFicSecFichero ( SFicSecuencial * p_ficObj ); 
int SFicSecEstablecerRuta ( SFicSecuencial * p_ficObj, const char * p_cRuta );
int SFicSecEstablecerRutaExt ( SFicSecuencial * p_ficObj, const char * p_cDir, const char * p_cFic );

int SFicSecAbrir ( SFicSecuencial * p_ficObj, int iModo );
int SFicSecAbrirExt ( SFicSecuencial * p_ficObj, int iModo, int iVaciar );
int SFicSecCerrar ( SFicSecuencial * p_ficObj );

int SFicSecEstaAbierto ( SFicSecuencial * p_ficObj );
int SFicSecModoApertura ( SFicSecuencial * p_ficObj );
int SFicSecEstaAbiertoParaLectura ( SFicSecuencial * p_ficObj );
int SFicSecEstaAbiertoParaEscritura ( SFicSecuencial * p_ficObj );

int SFicSecEstaEnFinal ( SFicSecuencial * p_ficObj );

byte SFicSecLeer ( SFicSecuencial * p_ficObj );
int SFicSecLeerBuffer ( SFicSecuencial * p_ficObj, byte * p_byContenido, unsigned long * p_ulTam );
int SFicSecEscribir ( SFicSecuencial * p_ficObj, byte byValor );
int SFicSecEscribirBuffer ( SFicSecuencial * p_ficObj, byte * p_byContenido, unsigned long * p_ulTam );

#endif

