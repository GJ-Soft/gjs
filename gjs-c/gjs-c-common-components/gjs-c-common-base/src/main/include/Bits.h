/******************************************************************************/
/*                                Bits.h                                      */
/*----------------------------------------------------------------------------*/
/* Librería:  GBase                                                           */
/* Versión:   1.0.0                                                           */
/* Fecha:     28/06/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene los prototipos de algunas rutinas de      */
/* carácter general de manejo de mapas de bits.                               */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _BITS_H
#define _BITS_H


#include <BaseConfig.h>








/* Número de bits de cada palabra del mapa: la unidad de almacenamiento es 'word'. */
#define BMP_BITS_PALABRA				( (int) ( sizeof ( word ) * TAM_BYTE ) )


/* Número de palabras necesarias para almacenar un número determinado de bits.*/
#define BMP_TAM_NECESARIO( lBits )		(unsigned int)( ( ( lBits ) + BMP_BITS_PALABRA - 1 ) / BMP_BITS_PALABRA )


#define BMP_FIJO( lBits )				word bmpDatos [ BMP_TAM_NECESARIO( lBits ) ] 


/* Valor auxiliar para construir las máscaras. */
#define BMP_MAS_BASE					0x0001


/* Macros. */
#define BMP_NUM_PALABRA( lBit )			( ( lBit ) / BMP_BITS_PALABRA )
#define BMP_POSICION_BIT( lBit )		( ( lBit ) % BMP_BITS_PALABRA )
#define BMP_MASCARA_BIT( lBit )			(word) ( BMP_MAS_BASE << BMP_POSICION_BIT(lBit) )

#define BMP_BIT_CON( bmpObj, lBit )		(bit)( ( ( *( bmpObj + BMP_NUM_PALABRA(lBit) )  \
										& BMP_MASCARA_BIT(lBit) ) ) >> BMP_POSICION_BIT(lBit) )

#define BMP_BIT_ACT( bmpObj, lBit )		*( bmpObj + BMP_NUM_PALABRA(lBit) ) |= BMP_MASCARA_BIT(lBit)

#define BMP_BIT_DES( bmpObj, lBit )		*( bmpObj + BMP_NUM_PALABRA(lBit) ) &= (word) ( ~ BMP_MASCARA_BIT(lBit) )

#define BMP_LIMPIAR( bmpObj, lBits )	memset ( bmpObj, 0x0, BMP_TAM_NECESARIO(lBits) * sizeof ( word ) )



byte ByMascaraBitsSuperiores ( int iNumBits ); 
byte2 By2MascaraBitsSuperiores ( int iNumBits ); 
byte4 By4MascaraBitsSuperiores ( int iNumBits ); 
byte ByMascaraBitsInferiores ( int iNumBits ); 
byte2 By2MascaraBitsInferiores ( int iNumBits ); 
byte4 By4MascaraBitsInferiores ( int iNumBits ); 
 


#endif

