
#ifndef _ORG_GJS_C_CC_C_COMMON_SID_H
#define _ORG_GJS_C_CC_C_COMMON_SID_H








typedef struct
{
	unsigned long	ulValor;

} SId;




SId * SIdCrear ();

void SIdDestruir ( SId ** p_p_idObj );

int SIdEsValido ( SId * p_idObj );

unsigned long SIdValor ( SId * p_idObj );
int SIdEstablecer ( SId * p_idObj, unsigned long ulValor );

int SIdEsIgual ( SId * p_idObj, SId * p_idVal );
int SIdEsMenor ( SId * p_idObj, SId * p_idVal );
int SIdEsMayor ( SId * p_idObj, SId * p_idVal );
int SIdEstaEnRango ( SId * p_idObj, SId * p_idVal1, SId * p_idVal2 );
int SIdEsMenorIg ( SId * p_idObj, SId * p_idVal );
int SIdEsMayorIg ( SId * p_idObj, SId * p_idVal );
int SIdEstaEnRangoIg ( SId * p_idObj, SId * p_idVal1, SId * p_idVal2 );

int SIdEsIgualEnt ( SId * p_idObj, unsigned long ulId );
int SIdEsMenorEnt ( SId * p_idObj, unsigned long ulId );
int SIdEsMayorEnt ( SId * p_idObj, unsigned long ulId );
int SIdEstaEnRangoEnt ( SId * p_idObj, unsigned long ulId1, unsigned long ulId2 );
int SIdEsMenorIgEnt ( SId * p_idObj, unsigned long ulId );
int SIdEsMayorIgEnt ( SId * p_idObj, unsigned long ulId );
int SIdEstaEnRangoIgEnt ( SId * p_idObj, unsigned long ulId1, unsigned long ulId2 );

unsigned int SIdHash ( SId * p_idObj );






#endif

