#ifndef _ORG_GJS_C_CC_MODOSAPERTURA_H
#define _ORG_GJS_C_CC_MODOSAPERTURA_H


#define MOD_APR_NINGUNO					-1

#define MOD_APR_LECTURA					0
#define MOD_APR_ESCRITURA				1
#define MOD_APR_REESCRITURA				2


int ModAprEsValido ( int iModo );
int ModAprPermiteEscritura ( int iModo );


#endif
