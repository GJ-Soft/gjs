
#ifndef _ORG_GJS_C_CC_SCONECTOR_H
#define _ORG_GJS_C_CC_SCONECTOR_H




typedef struct
{
	void * 	p_vObjeto;
	int		iTipo;

} SConector;



SConector * SCnctCrear ( void * p_vObjeto );
SConector * SCnctCrearExt ( void * p_vObjeto, int iTipo );

void SCnctDestruir ( SConector ** p_p_cnctObj );
void SCnctDestruirExt ( SConector ** p_p_cnctObj, int iDestruirContenido );

void * SCnctObjeto ( SConector * p_cnctObj );
int SCnctTipo ( SConector * p_cnctObj );
int SCnctEsValido ( SConector * p_cnctObj ); 
int SCnctEstablecer ( SConector * p_cnctObj, void * p_vObjeto, int iTipo );
int SCnctEstablecerObjeto ( SConector * p_cnctObj, void * p_vObjeto );
int SCnctEstablecerTipo ( SConector * p_cnctObj, int iTipo );

void SCnctLimpiar ( SConector * p_cnctObj );



 



#endif
