#include "Word.h"



/* Máscaras de obtenciónde los dos bytes contenidos en un word: */
#define WORD_MASC_BYTE_SUP		0xFF00
#define WORD_MASC_BYTE_INF		0x00FF

/* Desplazamientos de los dos bytes en un word: */
#define WORD_DESP_BYTE_SUP		0x0100
#define WORD_DESP_BYTE_INF		0x0001


/* Rutinas: */
byte WordByteInferior ( word wDato )
{
	return ( (byte) ( wDato & WORD_MASC_BYTE_INF ) );
}


byte WordByteSuperior ( word wDato )
{
	return ( (byte) ( ( wDato & WORD_MASC_BYTE_SUP ) / WORD_DESP_BYTE_SUP ) );
}


word WordComponer ( byte bySup, byte byInf )
{
	return ( (word) ( ( ( bySup & WORD_MASC_BYTE_INF ) * WORD_DESP_BYTE_SUP ) | ( byInf & WORD_MASC_BYTE_INF ) ) );
}


