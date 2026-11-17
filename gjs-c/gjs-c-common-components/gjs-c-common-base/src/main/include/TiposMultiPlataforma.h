/******************************************************************************/
/*                          TiposMultiPlataforma.h                            */
/*----------------------------------------------------------------------------*/
/* Librería:  GBase                                                           */
/* Versión:   1.0.0                                                           */
/* Fecha:     16/11/2026                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene los prototipos de las rutinas que         */
/* escriben y leen tipos numéricos en un formato binario independiente de la  */
/* plataforma, para usar en ficheros y comunicaciones.                        */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_TIPOSMULTIPLATAFORMA_H
#define _ORG_GJS_C_CC_TIPOSMULTIPLATAFORMA_H


#include <BaseConfig.h>



/* Cada tipo ocupa siempre los mismos bytes y se guarda en little-endian
   (primero el byte de menor peso), sea cual sea la máquina. */

/* Tamaños en bytes: */
#define MPL_TAM_8							1
#define MPL_TAM_16							2
#define MPL_TAM_32							4
#define MPL_TAM_64							8
#define MPL_TAM_REAL						4
#define MPL_TAM_REAL_DOBLE					8

/* Tamaños con que se guardan los tipos de C, iguales en todas las plataformas: */
#define MPL_TAM_SHORT						MPL_TAM_16
#define MPL_TAM_INT							MPL_TAM_32
#define MPL_TAM_LONG						MPL_TAM_64
#define MPL_TAM_LLONG						MPL_TAM_64




/* Rutinas: */

/* Escritura: devuelven los bytes escritos, o 0 si el destino es nulo. */
int MplEscribirI8 ( byte * p_byDest, int8_t iValor );
int MplEscribirU8 ( byte * p_byDest, uint8_t uiValor );
int MplEscribirI16 ( byte * p_byDest, int16_t iValor );
int MplEscribirU16 ( byte * p_byDest, uint16_t uiValor );
int MplEscribirI32 ( byte * p_byDest, int32_t iValor );
int MplEscribirU32 ( byte * p_byDest, uint32_t uiValor );
int MplEscribirI64 ( byte * p_byDest, int64_t llValor );
int MplEscribirU64 ( byte * p_byDest, uint64_t ullValor );
int MplEscribirReal ( byte * p_byDest, float fValor );
int MplEscribirRealDoble ( byte * p_byDest, double dValor );

/* Lectura: devuelven 0 si el origen es nulo. */
int8_t MplLeerI8 ( const byte * p_byOrig );
uint8_t MplLeerU8 ( const byte * p_byOrig );
int16_t MplLeerI16 ( const byte * p_byOrig );
uint16_t MplLeerU16 ( const byte * p_byOrig );
int32_t MplLeerI32 ( const byte * p_byOrig );
uint32_t MplLeerU32 ( const byte * p_byOrig );
int64_t MplLeerI64 ( const byte * p_byOrig );
uint64_t MplLeerU64 ( const byte * p_byOrig );
float MplLeerReal ( const byte * p_byOrig );
double MplLeerRealDoble ( const byte * p_byOrig );

/* Tipos de C, sin pensar en su tamaño en cada plataforma. La escritura
   devuelve los bytes escritos, o 0 si el destino es nulo. La lectura devuelve
   0 si el origen es nulo o si el valor no cabe en el tipo de esta máquina (un
   long de más de 32 bits leído en Windows). */
int MplEscribirShort ( byte * p_byDest, short sValor );
int MplEscribirUShort ( byte * p_byDest, unsigned short usValor );
int MplEscribirInt ( byte * p_byDest, int iValor );
int MplEscribirUInt ( byte * p_byDest, unsigned int uiValor );
int MplEscribirLong ( byte * p_byDest, long lValor );
int MplEscribirULong ( byte * p_byDest, unsigned long ulValor );
int MplEscribirLLong ( byte * p_byDest, long long llValor );
int MplEscribirULLong ( byte * p_byDest, unsigned long long ullValor );

short MplLeerShort ( const byte * p_byOrig );
unsigned short MplLeerUShort ( const byte * p_byOrig );
int MplLeerInt ( const byte * p_byOrig );
unsigned int MplLeerUInt ( const byte * p_byOrig );
long MplLeerLong ( const byte * p_byOrig );
unsigned long MplLeerULong ( const byte * p_byOrig );
long long MplLeerLLong ( const byte * p_byOrig );
unsigned long long MplLeerULLong ( const byte * p_byOrig );

/* 1 si el valor guardado en p_byOrig cabe en el long (o unsigned long) de esta
   máquina; donde long mide 8 bytes, siempre. No anotan error si no cabe. */
int MplCabeLong ( const byte * p_byOrig );
int MplCabeULong ( const byte * p_byOrig );

/* Tamaño en bytes con que se guarda cada tipo, el mismo en todas las
   plataformas: el mayor que tiene el tipo en cualquiera de ellas. */
int MplTamShort ();
int MplTamUShort ();
int MplTamInt ();
int MplTamUInt ();
int MplTamLong ();
int MplTamULong ();
int MplTamLLong ();
int MplTamULLong ();
int MplTamReal ();
int MplTamRealDoble ();


#endif
