#ifndef _ORG_GJS_C_CC_C_COMMON_SDEFPRIMITIVA_H
#define _ORG_GJS_C_CC_C_COMMON_SDEFPRIMITIVA_H





#include <SDefDato.h>
#include <SSecuenciaPtr.h>



typedef struct 
{
	int				iTipo;
	unsigned long	ulId;
	char *			p_cNombre;

	SDefDato *		p_ddatRetorno;
	SSecuenciaPtr *	p_secParametros;


} SDefPrimitiva; 



SDefPrimitiva * SDefPrimCrear ( unsigned long ulId, const char * p_cNombre, int iTipo );

void SDefPrimDestruir ( SDefPrimitiva ** p_p_dprimObj );

int SDefPrimEsValida ( SDefPrimitiva * p_dprimObj );

unsigned long SDefPrimId ( SDefPrimitiva * p_dprimObj );
int SDefPrimTipo ( SDefPrimitiva * p_dprimObj );
int SDefPrimEsFuncion ( SDefPrimitiva * p_dprimObj );
int SDefPrimEsProcedimiento ( SDefPrimitiva * p_dprimObj );
const char * SDefPrimNombre ( SDefPrimitiva * p_dprimObj );

int SDefPrimDefinirValorRetorno ( SDefPrimitiva * p_dprimObj, int iTipo, int iReferencia, int iTam, int iDecimales );
SDefDato * SDefPrimValorRetorno ( SDefPrimitiva * p_dprimObj );

int SDefPrimCrearParametro ( SDefPrimitiva * p_dprimObj, const char * p_cNombre, int iTipo, int iReferencia, int iTam, int iDecimales, const char * p_cValorDef );
int SDefPrimNumParametros ( SDefPrimitiva * p_dprimObj );
SDefDato * SDefPrimParametro ( SDefPrimitiva * p_dprimObj, int iParametro );



#endif
