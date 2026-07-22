#ifndef _ORG_GJS_C_CC_SFICSECUENCIALBUFFER_H
#define _ORG_GJS_C_CC_SFICSECUENCIALBUFFER_H







#include <ModosApertura.h>
#include <SFicSecuencial.h>
#include <SBuffer.h>
#include <SRuta.h>




typedef struct
{
	SFicSecuencial *	p_ficObj;
	SBuffer *			p_bufObj;
	unsigned long		ulPosBuf;
	unsigned long		ulLonBuf;
} SFicSecuencialBuffer;






SFicSecuencialBuffer * SFicSecBufCrear ( const char * p_cRuta, unsigned long ulTamBuf ); 
SFicSecuencialBuffer * SFicSecBufCrearExt ( const char * p_cDir, const char * p_cFic, unsigned long ulTamBuf );
SFicSecuencialBuffer * SFicSecBufCrearRuta ( SRuta * p_rutRuta, unsigned long ulTamBuf ); 

void SFicSecBufDestruir ( SFicSecuencialBuffer ** p_p_ficObj );
void SFicSecBufEliminar ( SFicSecuencialBuffer ** p_p_ficObj );

int SFicSecBufEsValido ( SFicSecuencialBuffer * p_ficObj ); 
const char * SFicSecBufRuta ( SFicSecuencialBuffer * p_ficObj ); 
char * SFicSecBufDirectorio ( SFicSecuencialBuffer * p_ficObj ); 
char * SFicSecBufFichero ( SFicSecuencialBuffer * p_ficObj ); 
int SFicSecBufEstablecerRuta ( SFicSecuencialBuffer * p_ficObj, const char * p_cRuta );
int SFicSecBufEstablecerRutaExt ( SFicSecuencialBuffer * p_ficObj, const char * p_cDir, const char * p_cFic );
unsigned long SFicSecBufTamBuffer ( SFicSecuencialBuffer * p_ficObj ); 

int SFicSecBufAbrir ( SFicSecuencialBuffer * p_ficObj, int iModo );
int SFicSecBufCerrar ( SFicSecuencialBuffer * p_ficObj );

int SFicSecBufEstaAbierto ( SFicSecuencialBuffer * p_ficObj );
int SFicSecBufModoApertura ( SFicSecuencialBuffer * p_ficObj );
int SFicSecBufEstaAbiertoParaLectura ( SFicSecuencialBuffer * p_ficObj );
int SFicSecBufEstaAbiertoParaEscritura ( SFicSecuencialBuffer * p_ficObj );

int SFicSecBufEstaEnFinal ( SFicSecuencialBuffer * p_ficObj );

byte SFicSecBufLeer ( SFicSecuencialBuffer * p_ficObj );
int SFicSecBufLeerBuffer ( SFicSecuencialBuffer * p_ficObj, byte * p_byContenido, unsigned long * p_ulTam );
int SFicSecBufEscribir ( SFicSecuencialBuffer * p_ficObj, byte byValor );
int SFicSecBufEscribirBuffer ( SFicSecuencialBuffer * p_ficObj, byte * p_byContenido, unsigned long * p_ulTam );


#endif

