#ifndef _ORG_GJS_C_CC_SREFERENCIA_H
#define _ORG_GJS_C_CC_SREFERENCIA_H








typedef struct
{
	char *		p_cAlias;
	void *		p_vDatos;

} SReferencia;




SReferencia * SRefCrear ( const char * p_cAlias, void * p_vDatos );

void SRefDestruir ( SReferencia ** p_p_refObj );

int SRefEsValida ( SReferencia * p_refObj );

const char * SRefObtenerAlias ( SReferencia * p_refObj );
void * SRefObtenerDatos ( SReferencia * p_refObj );
int SRefEstablecer ( SReferencia * p_refObj, const char * p_cAlias, void * p_vDatos );
int SRefEstablecerAlias ( SReferencia * p_refObj, const char * p_cAlias ); 
int SRefEstablecerDatos ( SReferencia * p_refObj,void * p_vDatos ); 

SReferencia * SRefDuplicar (  SReferencia * p_refObj );

int SRefEsIgual ( SReferencia * p_refObj1, SReferencia * p_refObj2 );
int SRefEsMenor ( SReferencia * p_refObj1, SReferencia * p_refObj2 );
int SRefEsMayor ( SReferencia * p_refObj1, SReferencia * p_refObj2 );
int SRefEsIgualLit ( SReferencia * p_refObj, const char * p_cAlias );
int SRefEsMenorLit ( SReferencia * p_refObj, const char * p_cAlias );
int SRefEsMayorLit ( SReferencia * p_refObj, const char * p_cAlias );

unsigned int SRefHash ( SReferencia * p_refObj );



#endif

