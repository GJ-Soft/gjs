#ifndef _ORG_GJS_C_CC_C_COMMON_SBUFFER_H
#define _ORG_GJS_C_CC_C_COMMON_SBUFFER_H




#include <Base.h>






typedef struct
{
	byte *				p_byContenido;
	unsigned long		ulTam;

} SBuffer;






SBuffer * SBufCrear ( unsigned long	ulTam );

void SBufDestruir ( SBuffer ** p_p_bufObj );

int SBufEsValido ( SBuffer * p_bufObj );
unsigned long SBufTam ( SBuffer * p_bufObj );
byte * SBufDireccion ( SBuffer * p_bufObj );
byte * SBufDuplicarValor ( SBuffer * p_bufObj );
byte * SBufDuplicarContenido ( SBuffer * p_bufObj, unsigned long ulPos, unsigned long ulTam );
char * SBufDuplicarCadena ( SBuffer * p_bufObj );

byte SBufLeer ( SBuffer * p_bufObj, unsigned long ulPos );
int SBufLeerBuffer ( SBuffer * p_bufObj, unsigned long ulPos, byte * p_byContenido, unsigned long * p_ulTam );
int SBufEscribir ( SBuffer * p_bufObj, unsigned long ulPos, byte byValor );
int SBufEscribirBuffer ( SBuffer * p_bufObj, unsigned long ulPos, byte * p_byContenido, unsigned long * p_ulTam );

int SBufLimpiar ( SBuffer * p_bufObj );

unsigned long SBufPosicionPrimerNulo ( SBuffer * p_bufObj );

int SBufInicializar ( SBuffer * p_bufObj, unsigned long	ulTam );
int SBufRedimensionar ( SBuffer * p_bufObj, unsigned long ulTam, int iConservarCont );

unsigned int SBufHash ( SBuffer * p_bufObj );


#endif

