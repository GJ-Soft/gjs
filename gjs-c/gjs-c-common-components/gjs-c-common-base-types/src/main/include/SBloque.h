#ifndef _ORG_GJS_C_CC_C_COMMON_SBLOQUE_H
#define _ORG_GJS_C_CC_C_COMMON_SBLOQUE_H


#include <Base.h>





typedef struct
{
	byte *	p_byDatos;
	int		iTam;
	int		iLiberar;

} SBloque;


SBloque * SBlqCrear ( int iTam );
SBloque * SBlqAsignar ( byte * p_byDirDatos, int iTam, int iLiberar );

SBloque * SBlqCrearEntero ();
SBloque * SBlqCrearEnteroLargo ();
SBloque * SBlqCrearEnteroSinSigno ();
SBloque * SBlqCrearEnteroLargoSinSigno ();
SBloque * SBlqCrearReal ();
SBloque * SBlqCrearRealDoble ();
SBloque * SBlqCrearCadena ();

void SBlqDestruir ( SBloque ** p_p_blqObj );

int SBlqEsValido ( SBloque * p_blqObj );

int SBlqTam ( SBloque * p_blqObj );
byte * SBlqDatos ( SBloque * p_blqObj );
byte * SBlqDuplicarDatos ( SBloque * p_blqObj );
byte * SBlqDatosEnPos ( SBloque * p_blqObj, int iPos );

int SBlqEntero ( SBloque * p_blqObj );
long SBlqEnteroLargo ( SBloque * p_blqObj );
unsigned int SBlqEnteroSinSigno ( SBloque * p_blqObj );
unsigned long SBlqEnteroLargoSinSigno ( SBloque * p_blqObj );
float SBlqReal ( SBloque * p_blqObj );
double SBlqRealDoble ( SBloque * p_blqObj );
char * SBlqCadena ( SBloque * p_blqObj );

int SBlqEsIgual ( SBloque * p_blqObj1, SBloque * p_blqObj2 );
int SBlqEsIgualExt ( SBloque * p_blqObj, byte * p_byDatos );

int SBlqLiberacionMemoriaActivada ( SBloque * p_blqObj );

int SBlqLimpiar ( SBloque * p_blqObj );
byte SBlqLeerByte ( SBloque * p_blqObj, int iPos );
int SBlqEscribirByte ( SBloque * p_blqObj, int iPos, byte byValor );
int SBlqEscribirEntero ( SBloque * p_blqObj, int iValor );
int SBlqEscribirEnteroLargo ( SBloque * p_blqObj, long lValor );
int SBlqEscribirReal ( SBloque * p_blqObj, float fValor );
int SBlqEscribirEnteroSinSigno ( SBloque * p_blqObj, unsigned int uiValor );
int SBlqEscribirEnteroLargoSinSigno ( SBloque * p_blqObj, unsigned long ulValor );
int SBlqEscribirRealDoble ( SBloque * p_blqObj, double dValor );
int SBlqEscribirCadena ( SBloque * p_blqObj, const char * p_cValor );
int SBlqEscribirEnteroEnPos ( SBloque * p_blqObj, int iPos, int iValor );
int SBlqEscribirEnteroLargoEnPos ( SBloque * p_blqObj, int iPos, long lValor );
int SBlqEscribirRealEnPos ( SBloque * p_blqObj, int iPos, float fValor );
int SBlqEscribirEnteroSinSignoEnPos ( SBloque * p_blqObj, int iPos, unsigned int uiValor );
int SBlqEscribirEnteroLargoSinSignoEnPos ( SBloque * p_blqObj, int iPos, unsigned long ulValor );
int SBlqEscribirRealDobleEnPos ( SBloque * p_blqObj, int iPos, double dValor );
int SBlqEscribirCadenaEnPos ( SBloque * p_blqObj, int iPos, const char * p_cValor );
int SBlqEscribirBuffer ( SBloque * p_blqObj, int iPos, byte * p_byValor, int iTam );
int SBlqCopiarDe ( SBloque * p_blqObj, byte * p_byValor );
int SBlqCopiarEn ( SBloque * p_blqObj, byte * p_byValor );
int SBlqCopiar ( SBloque * p_blqDest, SBloque * p_blqOrig );

SBloque * SBlqDuplicar ( SBloque * p_blqObj );
int SBlqEsCompatible ( SBloque * p_blqObj, SBloque * p_blqComp );
int SBlqTamCompatible ( SBloque * p_blqObj, int iTam );

int SBlqVolcar ( SBloque * p_blqObj, int iPos, SBloque * p_blqDatos );
SBloque * SBlqExtraer ( SBloque * p_blqObj, int iPos, int iTam );

unsigned int SBlqHash ( SBloque * p_blqObj );

#endif
