#ifndef _ORG_GJS_C_CC_C_COMMON_SINDICADOR2D_H
#define _ORG_GJS_C_CC_C_COMMON_SINDICADOR2D_H




#include <SIndicador.h>




typedef struct
{
	SIndicador * p_indDimension1;
	SIndicador * p_indDimension2;

} SIndicador2D;


SIndicador2D * SInd2DCrear ( unsigned long ulMax1, unsigned long ulMax2 );

void SInd2DDestruir ( SIndicador2D ** p_p_indObj );

int SInd2DEsValido ( SIndicador2D * p_indObj );

SIndicador * SInd2DDimension1 ( SIndicador2D * p_indObj );
SIndicador * SInd2DDimension2 ( SIndicador2D * p_indObj );

unsigned long SInd2DValor1 ( SIndicador2D * p_indObj );
unsigned long SInd2DValor2 ( SIndicador2D * p_indObj );
unsigned long SInd2DMax1 ( SIndicador2D * p_indObj );
unsigned long SInd2DMax2 ( SIndicador2D * p_indObj );

int SInd2DInicio ( SIndicador2D * p_indObj );
int SInd2DFinal ( SIndicador2D * p_indObj );
int SInd2DIncrementar ( SIndicador2D * p_indObj, unsigned long ulValor1, unsigned long ulValor2 );
int SInd2DDecrementar ( SIndicador2D * p_indObj, unsigned long ulValor1, unsigned long ulValor2 );
int SInd2DMoverA ( SIndicador2D * p_indObj, unsigned long ulValor1, unsigned long ulValor2 );

int SInd2DEstaEnInicio ( SIndicador2D * p_indObj );
int SInd2DEstaEnFinal ( SIndicador2D * p_indObj );
int SInd2DEstaEnInicio1 ( SIndicador2D * p_indObj );
int SInd2DEstaEnFinal1 ( SIndicador2D * p_indObj );
int SInd2DEstaEnInicio2 ( SIndicador2D * p_indObj );
int SInd2DEstaEnFinal2 ( SIndicador2D * p_indObj );



#endif
