
#ifndef _ORG_GJS_C_CC_C_COMMON_SID_H
#define _ORG_GJS_C_CC_C_COMMON_SID_H








typedef struct
{
	unsigned long	ulValor;

} SId;




SId * SIdCrearDef ();
SId * SIdCrear ( unsigned long ulValor );

void SIdDestruir ( SId ** p_p_idObj );

int SIdEsValido ( SId * p_idObj );

unsigned long SIdValor ( SId * p_idObj );
int SIdEstablecer ( SId * p_idObj, unsigned long ulValor );

int SIdAsignar ( SId * p_idObj, SId * p_idValor );

int SIdEsIgual ( SId * p_idObj, SId * p_idVal );
int SIdEsMenor ( SId * p_idObj, SId * p_idVal );
int SIdEsMayor ( SId * p_idObj, SId * p_idVal );
int SIdEstaEnRango ( SId * p_idObj, SId * p_idVal1, SId * p_idVal2 );
int SIdEsMenorIg ( SId * p_idObj, SId * p_idVal );
int SIdEsMayorIg ( SId * p_idObj, SId * p_idVal );
int SIdEstaEnRangoIg ( SId * p_idObj, SId * p_idVal1, SId * p_idVal2 );

int SIdEsIgualNum ( SId * p_idObj, unsigned long ulId );
int SIdEsMenorNum ( SId * p_idObj, unsigned long ulId );
int SIdEsMayorNum ( SId * p_idObj, unsigned long ulId );
int SIdEstaEnRangoNum ( SId * p_idObj, unsigned long ulId1, unsigned long ulId2 );
int SIdEsMenorIgNum ( SId * p_idObj, unsigned long ulId );
int SIdEsMayorIgNum ( SId * p_idObj, unsigned long ulId );
int SIdEstaEnRangoIgNum ( SId * p_idObj, unsigned long ulId1, unsigned long ulId2 );

int SIdComparar ( SId * p_idObj, SId * p_idVal );
int SIdCompararNum ( SId * p_idObj, unsigned long ulId );

unsigned int SIdHash ( SId * p_idObj );






#endif

