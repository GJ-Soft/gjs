
#ifndef _ORG_GJS_C_CC_C_COMMON_SERROR_H
#define _ORG_GJS_C_CC_C_COMMON_SERROR_H








typedef struct
{
	char * 	p_cCodigo;
	char * 	p_cDescripcion;
	int 	iAdvertencia;

} SError;




SError * SErrCrear ( const char * p_cCodigo, const char * p_cDescripcion );
SError * SErrCrearAdvertencia ( const char * p_cCodigo, const char * p_cDescripcion );
SError * SErrCrearForm ( const char * p_cCodigo, const char * p_cFormato, ... );
SError * SErrCrearAdvertenciaForm ( const char * p_cCodigo, const char * p_cFormato, ... );

void SErrDestruir ( SError ** p_p_errObj );

int SErrEsValido ( SError * p_errObj );

const char * SErrCodigo ( SError * p_errObj );
const char * SErrDescripcion ( SError * p_errObj );
int SErrEsAdvertencia ( SError * p_errObj );

SError * SErrClonar ( SError * p_errObj );


#endif

