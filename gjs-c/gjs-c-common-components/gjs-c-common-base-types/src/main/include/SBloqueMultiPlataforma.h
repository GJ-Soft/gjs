#ifndef _ORG_GJS_C_CC_C_COMMON_SBLOQUEMULTIPLATAFORMA_H
#define _ORG_GJS_C_CC_C_COMMON_SBLOQUEMULTIPLATAFORMA_H


#include <SBloque.h>



/* Bloque cuyo contenido tipado está en el formato binario de
   TiposMultiPlataforma: cada tipo ocupa siempre lo mismo y en el mismo orden
   de bytes, así que lo escrito en una plataforma se lee igual en otra. */

typedef struct
{
	SBloque * p_blqDatos;

} SBloqueMultiPlataforma;


SBloqueMultiPlataforma * SBlqMplCrear ( int iTam );
SBloqueMultiPlataforma * SBlqMplAsignar ( byte * p_byDirDatos, int iTam, int iLiberar );
SBloqueMultiPlataforma * SBlqMplEncapsular ( SBloque * p_blqDatos );

SBloqueMultiPlataforma * SBlqMplCrearEntero ();
SBloqueMultiPlataforma * SBlqMplCrearEnteroLargo ();
SBloqueMultiPlataforma * SBlqMplCrearEnteroSinSigno ();
SBloqueMultiPlataforma * SBlqMplCrearEnteroLargoSinSigno ();
SBloqueMultiPlataforma * SBlqMplCrearReal ();
SBloqueMultiPlataforma * SBlqMplCrearRealDoble ();
SBloqueMultiPlataforma * SBlqMplCrearCadena ( const char * p_cValor );

void SBlqMplDestruir ( SBloqueMultiPlataforma ** p_p_blqObj );

int SBlqMplEsValido ( SBloqueMultiPlataforma * p_blqObj );

int SBlqMplTam ( SBloqueMultiPlataforma * p_blqObj );
byte * SBlqMplDatos ( SBloqueMultiPlataforma * p_blqObj );
byte * SBlqMplDuplicarDatos ( SBloqueMultiPlataforma * p_blqObj );
byte * SBlqMplDatosEnPos ( SBloqueMultiPlataforma * p_blqObj, int iPos );

int SBlqMplEntero ( SBloqueMultiPlataforma * p_blqObj );
long SBlqMplEnteroLargo ( SBloqueMultiPlataforma * p_blqObj );
unsigned int SBlqMplEnteroSinSigno ( SBloqueMultiPlataforma * p_blqObj );
unsigned long SBlqMplEnteroLargoSinSigno ( SBloqueMultiPlataforma * p_blqObj );
float SBlqMplReal ( SBloqueMultiPlataforma * p_blqObj );
double SBlqMplRealDoble ( SBloqueMultiPlataforma * p_blqObj );
char * SBlqMplCadena ( SBloqueMultiPlataforma * p_blqObj );

int SBlqMplEsIgual ( SBloqueMultiPlataforma * p_blqObj1, SBloqueMultiPlataforma * p_blqObj2 );
int SBlqMplEsIgualBloque ( SBloqueMultiPlataforma * p_blqObj1, SBloque * p_blqObj2 );
int SBlqMplEsIgualExt ( SBloqueMultiPlataforma * p_blqObj, byte * p_byDatos );

int SBlqMplLiberacionMemoriaActivada ( SBloqueMultiPlataforma * p_blqObj );

int SBlqMplLimpiar ( SBloqueMultiPlataforma * p_blqObj );

byte SBlqMplLeerByte ( SBloqueMultiPlataforma * p_blqObj, int iPos );
int SBlqMplEscribirByte ( SBloqueMultiPlataforma * p_blqObj, int iPos, byte byValor );

int SBlqMplEscribirEntero ( SBloqueMultiPlataforma * p_blqObj, int iValor );
int SBlqMplEscribirEnteroLargo ( SBloqueMultiPlataforma * p_blqObj, long lValor );
int SBlqMplEscribirReal ( SBloqueMultiPlataforma * p_blqObj, float fValor );
int SBlqMplEscribirEnteroSinSigno ( SBloqueMultiPlataforma * p_blqObj, unsigned int uiValor );
int SBlqMplEscribirEnteroLargoSinSigno ( SBloqueMultiPlataforma * p_blqObj, unsigned long ulValor );
int SBlqMplEscribirRealDoble ( SBloqueMultiPlataforma * p_blqObj, double dValor );
int SBlqMplEscribirCadena ( SBloqueMultiPlataforma * p_blqObj, const char * p_cValor );

int SBlqMplLeerEnteroEnPos ( SBloqueMultiPlataforma * p_blqObj, int iPos );
long SBlqMplLeerEnteroLargoEnPos ( SBloqueMultiPlataforma * p_blqObj, int iPos );
float SBlqMplLeerRealEnPos ( SBloqueMultiPlataforma * p_blqObj, int iPos );
unsigned int SBlqMplLeerEnteroSinSignoEnPos ( SBloqueMultiPlataforma * p_blqObj, int iPos );
unsigned long SBlqMplLeerEnteroLargoSinSignoEnPos ( SBloqueMultiPlataforma * p_blqObj, int iPos );
double SBlqMplLeerRealDobleEnPos ( SBloqueMultiPlataforma * p_blqObj, int iPos );
char * SBlqMplLeerCadenaEnPos ( SBloqueMultiPlataforma * p_blqObj, int iPos );
int SBlqMplEscribirEnteroEnPos ( SBloqueMultiPlataforma * p_blqObj, int iPos, int iValor );
int SBlqMplEscribirEnteroLargoEnPos ( SBloqueMultiPlataforma * p_blqObj, int iPos, long lValor );
int SBlqMplEscribirRealEnPos ( SBloqueMultiPlataforma * p_blqObj, int iPos, float fValor );
int SBlqMplEscribirEnteroSinSignoEnPos ( SBloqueMultiPlataforma * p_blqObj, int iPos, unsigned int uiValor );
int SBlqMplEscribirEnteroLargoSinSignoEnPos ( SBloqueMultiPlataforma * p_blqObj, int iPos, unsigned long ulValor );
int SBlqMplEscribirRealDobleEnPos ( SBloqueMultiPlataforma * p_blqObj, int iPos, double dValor );
int SBlqMplEscribirCadenaEnPos ( SBloqueMultiPlataforma * p_blqObj, int iPos, const char * p_cValor );

int SBlqMplLeerBuffer ( SBloqueMultiPlataforma * p_blqObj, int iPos, byte * p_byValor, int iTam );
int SBlqMplEscribirBuffer ( SBloqueMultiPlataforma * p_blqObj, int iPos, byte * p_byValor, int iTam );

byte SBlqMplLeerByteExt ( SBloqueMultiPlataforma * p_blqObj, int * p_iPos );
int SBlqMplEscribirByteExt ( SBloqueMultiPlataforma * p_blqObj, int * p_iPos, byte byValor );

int SBlqMplLeerEnteroEnPosExt ( SBloqueMultiPlataforma * p_blqObj, int * p_iPos );
long SBlqMplLeerEnteroLargoEnPosExt ( SBloqueMultiPlataforma * p_blqObj, int * p_iPos );
float SBlqMplLeerRealEnPosExt ( SBloqueMultiPlataforma * p_blqObj, int * p_iPos );
unsigned int SBlqMplLeerEnteroSinSignoEnPosExt ( SBloqueMultiPlataforma * p_blqObj, int * p_iPos );
unsigned long SBlqMplLeerEnteroLargoSinSignoEnPosExt ( SBloqueMultiPlataforma * p_blqObj, int * p_iPos );
double SBlqMplLeerRealDobleEnPosExt ( SBloqueMultiPlataforma * p_blqObj, int * p_iPos );
char * SBlqMplLeerCadenaEnPosExt ( SBloqueMultiPlataforma * p_blqObj, int * p_iPos );
int SBlqMplEscribirEnteroEnPosExt ( SBloqueMultiPlataforma * p_blqObj, int * p_iPos, int iValor );
int SBlqMplEscribirEnteroLargoEnPosExt ( SBloqueMultiPlataforma * p_blqObj, int * p_iPos, long lValor );
int SBlqMplEscribirRealEnPosExt ( SBloqueMultiPlataforma * p_blqObj, int * p_iPos, float fValor );
int SBlqMplEscribirEnteroSinSignoEnPosExt ( SBloqueMultiPlataforma * p_blqObj, int * p_iPos, unsigned int uiValor );
int SBlqMplEscribirEnteroLargoSinSignoEnPosExt ( SBloqueMultiPlataforma * p_blqObj, int * p_iPos, unsigned long ulValor );
int SBlqMplEscribirRealDobleEnPosExt ( SBloqueMultiPlataforma * p_blqObj, int * p_iPos, double dValor );
int SBlqMplEscribirCadenaEnPosExt ( SBloqueMultiPlataforma * p_blqObj, int * p_iPos, const char * p_cValor );

int SBlqMplLeerBufferExt ( SBloqueMultiPlataforma * p_blqObj, int * p_iPos, byte * p_byValor, int iTam );
int SBlqMplEscribirBufferExt ( SBloqueMultiPlataforma * p_blqObj, int * p_iPos, byte * p_byValor, int iTam );


int SBlqMplCopiarDe ( SBloqueMultiPlataforma * p_blqObj, byte * p_byValor );
int SBlqMplCopiarEn ( SBloqueMultiPlataforma * p_blqObj, byte * p_byValor );
int SBlqMplCopiar ( SBloqueMultiPlataforma * p_blqDest, SBloqueMultiPlataforma * p_blqOrig );
int SBlqMplCopiarBloque ( SBloqueMultiPlataforma * p_blqDest, SBloque * p_blqOrig );

SBloqueMultiPlataforma * SBlqMplDuplicar ( SBloqueMultiPlataforma * p_blqObj );
int SBlqMplEsCompatible ( SBloqueMultiPlataforma * p_blqObj, SBloqueMultiPlataforma * p_blqComp );
int SBlqMplEsCompatibleBloque ( SBloqueMultiPlataforma * p_blqObj, SBloque * p_blqComp );
int SBlqMplTamCompatible ( SBloqueMultiPlataforma * p_blqObj, int iTam );

int SBlqMplVolcar ( SBloqueMultiPlataforma * p_blqObj, int iPos, SBloqueMultiPlataforma * p_blqDatos );
int SBlqMplVolcarBloque ( SBloqueMultiPlataforma * p_blqObj, int iPos, SBloque * p_blqDatos );
SBloqueMultiPlataforma * SBlqMplExtraer ( SBloqueMultiPlataforma * p_blqObj, int iPos, int iTam );
int SBlqMplVolcarExt ( SBloqueMultiPlataforma * p_blqObj, int * p_iPos, SBloqueMultiPlataforma * p_blqDatos );
int SBlqMplVolcarBloqueExt ( SBloqueMultiPlataforma * p_blqObj, int * p_iPos, SBloque * p_blqDatos );
SBloqueMultiPlataforma * SBlqMplExtraerExt ( SBloqueMultiPlataforma * p_blqObj, int * p_iPos, int iTam );

unsigned int SBlqMplHash ( SBloqueMultiPlataforma * p_blqObj );

SBloque * SBlqMplBloque ( SBloqueMultiPlataforma * p_blqObj );

#endif
