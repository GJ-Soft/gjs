#ifndef _ORG_GJS_C_CC_C_COMMON_SINDICADOR_H
#define _ORG_GJS_C_CC_C_COMMON_SINDICADOR_H









typedef struct
{
	unsigned long	 ulValor;
	unsigned long	 ulMax;

} SIndicador;


SIndicador * SIndCrear ( unsigned long ulMax );

void SIndDestruir ( SIndicador ** p_p_indObj );

int SIndEsValido ( SIndicador * p_indObj );

unsigned long SIndValor ( SIndicador * p_indObj );
unsigned long SIndMax ( SIndicador * p_indObj );

int SIndInicio ( SIndicador * p_indObj );
int SIndFinal ( SIndicador * p_indObj );
int SIndIncrementar ( SIndicador * p_indObj );
int SIndDecrementar ( SIndicador * p_indObj );
int SIndIncrementarExt ( SIndicador * p_indObj, unsigned long ulValor );
int SIndDecrementarExt ( SIndicador * p_indObj, unsigned long ulValor );
int SIndMoverA ( SIndicador * p_indObj, unsigned long ulValor );

int SIndEstaEnInicio ( SIndicador * p_indObj );
int SIndEstaEnFinal ( SIndicador * p_indObj );

int SIndPuedeIncrementar ( SIndicador * p_indObj, unsigned long ulValor );
int SIndPuedeDecrementar ( SIndicador * p_indObj, unsigned long ulValor );
int SIndPuedeMoverA ( SIndicador * p_indObj, unsigned long ulValor );


#endif

