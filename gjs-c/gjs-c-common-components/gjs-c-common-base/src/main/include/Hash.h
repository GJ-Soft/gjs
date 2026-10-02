#ifndef _ORG_GJS_C_CC_HASH_H
#define _ORG_GJS_C_CC_HASH_H




#include <BaseConfig.h>
#include <Funciones.h>


#define PFUNHASH	PFUNUINTPV



unsigned int HashByte ( byte byVal );
unsigned int HashCaracter ( char cVal );
unsigned int HashBinario ( byte * p_byVal, int iTam );
unsigned int HashEntero ( int iVal );
unsigned int HashEnteroLargo ( long lVal );
unsigned int HashEnteroSinSigno ( unsigned int uiVal );
unsigned int HashEnteroLargoSinSigno ( unsigned long ulVal );
unsigned int HashEnteroDobleLargo ( long long llVal );
unsigned int HashEnteroDobleLargoSinSigno ( unsigned long long ullVal );
unsigned int HashReal ( float fVal );
unsigned int HashRealDoble ( double dVal );

unsigned int HashCadena ( const char * p_cVal );


#endif






