#ifndef _ORG_GJS_C_CC_C_COMMON_SCONTADOR_H
#define _ORG_GJS_C_CC_C_COMMON_SCONTADOR_H









typedef struct
{
	unsigned long	 ulValor;
	unsigned long	 ulMin;
	unsigned long	 ulMax;

} SContador;


SContador * SCntCrear ( unsigned long ulMin, unsigned long ulMax );

void SCntDestruir ( SContador ** p_p_cntObj );

unsigned long SCntValor ( SContador * p_cntObj );
unsigned long SCntMin ( SContador * p_cntObj );
unsigned long SCntMax ( SContador * p_cntObj );

int SCntIniciar ( SContador * p_cntObj );
int SCntIncrementar ( SContador * p_cntObj );
int SCntDecrementar ( SContador * p_cntObj );

int SCntEstaEnValorMax ( SContador * p_cntObj );
int SCntEstaEnValorMin ( SContador * p_cntObj );



#endif

