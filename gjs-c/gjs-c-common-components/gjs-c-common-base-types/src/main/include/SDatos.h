

#ifndef _ORG_GJS_C_CC_C_COMMON_SDATOS_H
#define _ORG_GJS_C_CC_C_COMMON_SDATOS_H




#include <SBuffer.h>



typedef struct
{
	SBuffer * p_bufDatos;

} SDatos;


SDatos * SDatCrear ( int iTam );

void SDatDestruir ( SDatos ** p_p_datObj );

int SDatEsValido ( SDatos * p_datObj );

int SDatEstablecerByte ( SDatos * p_datObj, int iPos, byte byVal );
byte SDatByte ( SDatos * p_datObj, int iPos );

int SDatAsignarContenido ( SDatos * p_datObj, byte * p_byDatos, int iTam );
int SDatAsignarContenidoEnPos ( SDatos * p_datObj, int iPos, byte * p_byDatos, int iTam );

byte * SDatContenido ( SDatos * p_datObj );
byte * SDatContenidoEnPos ( SDatos * p_datObj, int iPos, int iTam );
byte * SDatDuplicarContenido ( SDatos * p_datObj );
byte * SDatDuplicarContenidoEnPos ( SDatos * p_datObj, int iPos, int iTam );

int SDatAsignar ( SDatos * p_datObj, SDatos * p_datValor );
int SDatCopiar ( SDatos * p_datObj, SDatos * p_datValor );
int SDatCopiarEnPos ( SDatos * p_datObj, int iPos, SDatos * p_datValor );
SDatos * SDatDuplicar ( SDatos * p_datObj );
SDatos * SDatExtraer ( SDatos * p_datObj, int iTam );
SDatos * SDatExtraerEnPos ( SDatos * p_datObj, int iPos, int iTam );
char * SDatExtraerCadena ( SDatos * p_datObj, int iTam );
char * SDatExtraerCadenaEnPos ( SDatos * p_datObj, int iPos, int iTam );
SDatos * SDatExtraerHastaNulo ( SDatos * p_datObj, int iIncluirNulo );

int SDatTam ( SDatos * p_datObj );
int SDatPosicionPrimerNulo ( SDatos * p_datObj );

void SDatLimpiar ( SDatos * p_datObj );

void SDatLiberar ( SDatos * p_datObj );
int SDatInicializar ( SDatos * p_datObj, int iTam );
int SDatRedimensionar ( SDatos * p_datObj, int iTam, int iConservarCont );

char * SDatCadenaHex ( SDatos * p_datObj );
int SDatAsignarCadenaHex ( SDatos * p_datObj, const char * p_cHex );

void SDatImprimir ( SDatos * p_datObj );

unsigned int SDatHash ( SDatos * p_datObj );




#endif

