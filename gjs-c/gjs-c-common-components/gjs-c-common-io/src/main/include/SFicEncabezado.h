
#ifndef _ORG_GJS_C_CC_SFICENCABEZADO_H
#define _ORG_GJS_C_CC_SFICENCABEZADO_H






#include <SFicAleatorio.h>
#include <SRuta.h>




typedef struct
{
	int				iNumMagico;
	unsigned long	ulTamCabecera;

	SFicAleatorio *	p_ficObj;
} SFicEncabezado;






SFicEncabezado * SFicEncCrear ( const char * p_cRuta, unsigned long ulTamCabecera ); 
SFicEncabezado * SFicEncAsignar ( const char * p_cRuta ); 
SFicEncabezado * SFicEncCrearExt ( const char * p_cDir, const char * p_cFic, unsigned long ulTamCabecera, int iNumMagico ); 
SFicEncabezado * SFicEncAsignarExt ( const char * p_cDir, const char * p_cFic, int iNumMagico ); 
SFicEncabezado * SFicEncCrearRuta ( SRuta * p_rutRuta, unsigned long ulTamCabecera ); 

void SFicEncDestruir ( SFicEncabezado ** p_p_ficObj );
void SFicEncEliminar ( SFicEncabezado ** p_p_ficObj );

int SFicEncEsValido ( SFicEncabezado * p_ficObj ); 
const char * SFicEncRuta ( SFicEncabezado * p_ficObj ); 
char * SFicEncDirectorio ( SFicEncabezado * p_ficObj ); 
char * SFicEncFichero ( SFicEncabezado * p_ficObj ); 
int SFicEncEstablecerRuta ( SFicEncabezado * p_ficObj, const char * p_cRuta );
int SFicEncEstablecerRutaExt ( SFicEncabezado * p_ficObj, const char * p_cDir, const char * p_cFic );

int SFicEncTieneNumeroMagico ( SFicEncabezado * p_ficObj ); 
unsigned long SFicEncNumeroMagico ( SFicEncabezado * p_ficObj );
int SFicEncEstablecerNumeroMagico ( SFicEncabezado * p_ficObj, unsigned long ulNumero );

unsigned long SFicEncTamCabecera ( SFicEncabezado * p_ficObj );
int SFicEncEstablecerTamCabecera ( SFicEncabezado * p_ficObj, unsigned long ulTam );

int SFicEncAbrir ( SFicEncabezado * p_ficObj );
int SFicEncAbrirExt ( SFicEncabezado * p_ficObj, int iVaciar );
int SFicEncCerrar ( SFicEncabezado * p_ficObj );

int SFicEncEstaAbierto ( SFicEncabezado * p_ficObj );

unsigned long SFicEncTam ( SFicEncabezado * p_ficObj );
unsigned long SFicEncTamDatos ( SFicEncabezado * p_ficObj );
int SFicEncEstaVacio ( SFicEncabezado * p_ficObj );
unsigned long SFicEncPos ( SFicEncabezado * p_ficObj );
int SFicEncPosicionar ( SFicEncabezado * p_ficObj, unsigned long ulPos );
int SFicEncMoverAInicio ( SFicEncabezado * p_ficObj );
int SFicEncMoverAFinal ( SFicEncabezado * p_ficObj );
int SFicEncEstaEnFinal ( SFicEncabezado * p_ficObj );

byte * SFicEncLeerCabecera ( SFicEncabezado * p_ficObj );
byte * SFicEncCrearBufferCabecera( SFicEncabezado * p_ficObj );
int SFicEncEscribirCabecera ( SFicEncabezado * p_ficObj, byte * p_byCabecera );

byte SFicEncLeer ( SFicEncabezado * p_ficObj );
int SFicEncLeerBuffer ( SFicEncabezado * p_ficObj, byte * p_byContenido, unsigned long * p_ulTam );
int SFicEncEscribir ( SFicEncabezado * p_ficObj, byte byValor );
int SFicEncEscribirBuffer ( SFicEncabezado * p_ficObj, byte * p_byContenido, unsigned long * p_ulTam );

byte SFicEncLeerEn ( SFicEncabezado * p_ficObj, unsigned long ulPos );
int SFicEncLeerBufferEn ( SFicEncabezado * p_ficObj, unsigned long ulPos, byte * p_byContenido, unsigned long * p_ulTam );
int SFicEncEscribirEn ( SFicEncabezado * p_ficObj, unsigned long ulPos, byte byValor );
int SFicEncEscribirBufferEn ( SFicEncabezado * p_ficObj, unsigned long ulPos, byte * p_byContenido, unsigned long * p_ulTam );


#endif

