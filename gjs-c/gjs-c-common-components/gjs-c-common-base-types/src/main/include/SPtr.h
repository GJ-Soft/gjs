#ifndef _ORG_GJS_C_CC_C_COMMON_SPTR_H
#define _ORG_GJS_C_CC_C_COMMON_SPTR_H





#include <Base.h>


typedef PPRCPPV             PRC_DESTRUCTOR;





typedef struct 
{
	void *			p_vObjeto;
	PRC_DESTRUCTOR  p_fDestructor;

} SPtr; 




SPtr * SPtrCrearDef ( void * p_vObjeto );
SPtr * SPtrCrear ( void * p_vObjeto, PRC_DESTRUCTOR p_fDestructor );
SPtr * SPtrPreparar ( PRC_DESTRUCTOR p_fDestructor );
void SPtrDestruir ( SPtr ** p_p_ptrObj );
void SPtrDestruirSinLiberar ( SPtr ** p_p_ptrObj );

int SPtrEsValido ( SPtr * p_ptrObj );
int SPtrEstaVacio ( SPtr * p_ptrObj );

void * SPtrObjeto ( SPtr * p_ptrObj );
int SPtrEstablecer ( SPtr * p_ptrObj, void * p_vObjeto );


#endif
