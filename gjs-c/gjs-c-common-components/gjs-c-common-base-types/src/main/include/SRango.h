#ifndef _ORG_GJS_C_CC_C_COMMON_SRANGO_H
#define _ORG_GJS_C_CC_C_COMMON_SRANGO_H







typedef struct
{
	int iMin;
	int iMax;

} SRango;


SRango * SRngCrear ( int iMin, int iMax );

void SRngDestruir ( SRango ** p_p_rngObj );

int SRngEsValido ( SRango * p_rngObj );

int SRngMin ( SRango * p_rngObj );
int SRngMax ( SRango * p_rngObj );
int SRngAmplitud ( SRango * p_rngObj );
int SRngEstablecerMin ( SRango * p_rngObj, int iMin );
int SRngEstablecerMax ( SRango * p_rngObj, int iMax  );

int SRngEstaIncluido ( SRango * p_rngObj, int iVal );



#endif
