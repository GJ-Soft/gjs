#ifndef _ORG_GJS_C_CC_C_COMMON_SINTERFAZ_H
#define _ORG_GJS_C_CC_C_COMMON_SINTERFAZ_H





#include <SDefPrimitiva.h>
#include <SSecuenciaPtr.h>



typedef struct 
{
	unsigned long	ulId;
	char *			p_cNombre;

	SSecuenciaPtr *	p_secPrimitivas;

} SInterfaz; 



SInterfaz * SIntrfzCrear ( unsigned long ulId, const char * p_cNombre );

void SIntrfzDestruir ( SInterfaz ** p_p_intrfzObj );

int SIntrfzEsValido ( SInterfaz * p_intrfzObj );

unsigned long SIntrfzId ( SInterfaz * p_intrfzObj );
const char * SIntrfzNombre ( SInterfaz * p_intrfzObj );

int SIntrfzCrearPrimitiva ( SInterfaz * p_intrfzObj, const char * p_cNombre, int iTipo );
int SIntrfzNumPrimitivas ( SInterfaz * p_intrfzObj );
SDefPrimitiva * SIntrfzPrimitiva ( SInterfaz * p_intrfzObj, int iPrimitiva );



#endif
