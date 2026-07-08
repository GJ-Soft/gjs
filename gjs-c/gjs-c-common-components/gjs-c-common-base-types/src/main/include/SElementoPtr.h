#ifndef _ORG_GJS_C_CC_C_COMMON_SELEMENTOPTR_H
#define _ORG_GJS_C_CC_C_COMMON_SELEMENTOPTR_H





#include <Base.h>





typedef struct 
{
	void *	p_elpAnt;  // SElementoPtr
	void *	p_elpSig;  // SElementoPtr

	byte *	p_byDatos;
	int		iLiberar;

} SElementoPtr; 




SElementoPtr * SElpCrear ( byte * p_byDatos, int iLiberar );

void SElpDestruir ( SElementoPtr ** p_p_elpObj );

int SElpEsValido ( SElementoPtr * p_elpObj );

byte * SElpDatos ( SElementoPtr * p_elpObj );

int SElpModificar ( SElementoPtr * p_elpObj, byte * p_byDatos, int iLiberar );

SElementoPtr * SElpAntecesor ( SElementoPtr * p_elpObj );	
SElementoPtr * SElpSucesor ( SElementoPtr * p_elpObj );	
int SElpTieneAntecesor ( SElementoPtr * p_elpObj );
int SElpTieneSucesor ( SElementoPtr * p_elpObj );
int SElpEncadenarAntecesor ( SElementoPtr * p_elpObj, SElementoPtr * p_elpAnt );
int SElpEncadenarSucesor ( SElementoPtr * p_elpObj, SElementoPtr * p_elpSuc );
int SElpDesencadenarAntecesor ( SElementoPtr * p_elpObj );
int SElpDesencadenarSucesor ( SElementoPtr * p_elpObj );
int SElpDesencadenar ( SElementoPtr * p_elpObj );

int SElpEsIgual ( SElementoPtr * p_elpObj1, SElementoPtr * p_elpObj2, int iNumBytes );
int SElpEsIgualExt ( SElementoPtr * p_elpObj, byte * p_byObj, int iNumBytes );

int	SElpLiberacionMemoriaActivada ( SElementoPtr * p_elpObj );
//void SElpActivarLiberacionMemoria ( SElementoPtr * p_elpObj );
//void SElpDesactivarLiberacionMemoria ( SElementoPtr * p_elpObj );

SElementoPtr * SElpDuplicar ( SElementoPtr * p_elpObj );

#endif
