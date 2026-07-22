#include "DWord.h"


/* Máscaras de obtenciónde los dos words contenidos en un dword: */
#define DWORD_MASC_WORD_SUP		0xFFFF0000
#define DWORD_MASC_WORD_INF		0x0000FFFF

/* Desplazamientos de los dos words en un dword: */
#define DWORD_DESP_WORD_SUP		0x00010000
#define DWORD_DESP_WORD_INF		0x00000001




/* Rutinas: */
word DWordWordInferior ( dword dwDato )
{
	return ( (word) ( dwDato & DWORD_MASC_WORD_INF ) );
}


word DWordWordSuperior ( dword dwDato )
{
	return ( (word) ( ( dwDato & DWORD_MASC_WORD_SUP ) / DWORD_DESP_WORD_SUP ) );
}


dword DWordComponer ( word wSup, word wInf )
{
	return ( (dword) ( ( ( (dword) wSup & DWORD_MASC_WORD_INF ) * DWORD_DESP_WORD_SUP ) | ( (dword) wInf & DWORD_MASC_WORD_INF ) ) );
}

