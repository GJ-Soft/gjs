/******************************************************************************/
/*                                 Memoria.h                                  */
/*----------------------------------------------------------------------------*/
/* Librería:  GBase                                                           */
/* Versión:   1.0.0                                                           */
/* Fecha:     28/06/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene los prototipos de unas cuantas rutinas    */
/* para reservar, liberar y trabajar con espacios de memoria.                 */
/*                                                                            */
/* Trabajo con variables:                                                     */
/* Para evitar problemas de compatibilidad, se recomienda hacer uso de las    */
/* rutinas MemReservar y MemLiberar para reservar y liberar espacio de        */
/* memoria para variables dinámicas, manejadas a traves de punteros. No se    */
/* debe utilizar el new y el delete para estas variables, salvo cuando se     */
/* trate de objetos.                                                          */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_MEMORIA_H
#define _ORG_GJS_C_CC_MEMORIA_H




#include <BaseConfig.h>


#if ( defined ( VC ) )

//  Marcas de memoria VC++ en modo 'debug':
#	define MEM_DIN_NO_INICIALIZADA					0xCDCDCDCD
#	define MEM_DIN_NO_INICIALIZADA_2				0xBAADF00D
#	define MEM_DIN_LIBERADA							0xDDDDDDDD
#	define MEM_PIL_NO_INICIALIZADA					0xCCCCCCCC
#	define MEM_DIN_LIBERADA_2						0xFEEEFEEE

#	define MEM_DIN_MARCA_FIN						0xFDFDFDFD

#	if ( defined ( WIN ) )
#		define BAD_PTR								0x00000001
#		define BAD_STACK_PTR						0xCCCCCCCC
#		define DELETED_PTR							0xFFEEFFEE
#	endif
#else
	// No existe algo similar para GNU.
#endif




#if ( defined ( VC ) )
#	if ( defined ( WIN ) )
#		define ES_VALIDO( p_Obj )	( ( p_Obj != NULL ) && ( (const unsigned long)p_Obj != BAD_PTR ) && ( (const unsigned long)p_Obj != DELETED_PTR ) && ( (const unsigned long)p_Obj != BAD_STACK_PTR ) && ( (const unsigned long)p_Obj != MEM_DIN_LIBERADA ) && ( (const unsigned long)p_Obj != MEM_DIN_LIBERADA_2 ) )
#		define ES_NULO( p_Obj )		( ( p_Obj == NULL ) || ( (const unsigned long)p_Obj == BAD_PTR ) || ( (const unsigned long)p_Obj == BAD_STACK_PTR ) || ( (const unsigned long)p_Obj == DELETED_PTR ) || ( (const unsigned long)p_Obj == MEM_DIN_LIBERADA ) || ( (const unsigned long)p_Obj == MEM_DIN_LIBERADA_2 ) )
#	else
#		define ES_VALIDO( p_Obj )	( p_Obj != NULL )
#		define ES_NULO( p_Obj )		( p_Obj == NULL )
#	endif
#else
#	define ES_VALIDO( p_Obj )	( p_Obj != NULL )
#	define ES_NULO( p_Obj )		( p_Obj == NULL )
#endif


/*
#if ( defined ( WIN ) )
#	define ES_MANEJADOR( p_Obj )        ( ((ULONG)(p_Obj)) & 0x4 ) !=0 )
#	define ES_PUNTERO( p_Obj )         ( ( ((ULONG)(p_Obj)) & 0x4 ) ==0 )
#endif
*/

// TODO: MemValida HEAP


/* Operaciones basicas de memoria: */
void * MemReservar ( int iNumBytes );
void * MemReservarVector ( int iNumElems, int iNumBytesElem );
void * MemReservarTabla ( int iNumFilas, int iNumColumnas, int iNumBytesElem );
int MemRedimensionar ( void ** p_p_vBloque, int iNumBytes );
int MemLiberar ( void ** p_p_vBloque );
int MemLiberarCadena ( char ** p_p_cCadena );
int MemLiberarUnicode ( unichar ** p_p_uniCadena );

void MemLimpiar ( void * p_vBloque, int iNumBytes );
void MemLlenar ( void * p_vBloque, byte byValor, int iNumBytes );
void MemCopiar ( void * p_vDest, void * p_vOrig, int iNumBytes );

int MemEsValida ( void * p_vDireccion );

int MemEsIgual ( void * p_vBloque1, void * p_vBloque2, int iNumBytes );

#endif






