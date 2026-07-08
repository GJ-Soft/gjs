#ifndef _ORG_GJS_C_CC_C_COMMON_SPAREJA_H
#define _ORG_GJS_C_CC_C_COMMON_SPAREJA_H





#include <Base.h>





typedef struct 
{
	void *	p_vPrimero; 
	void *	p_vSegundo;  

	int		iLiberar;

} SPareja; 




SPareja * SPrjCrear ( void * p_vPrimero, void * p_vSegundo, int iLiberar );
SPareja * SPrjCrearGestionando ( void * p_vPrimero, void * p_vSegundo );
SPareja * SPrjCrearSoloPtr ( void * p_vPrimero, void * p_vSegundo );

void SPrjDestruir ( SPareja ** p_p_prjObj );

int SPrjEsValido ( SPareja * p_prjObj );

void * SPrjObtenerPrimero ( SPareja * p_prjObj );
void * SPrjObtenerSegundo ( SPareja * p_prjObj );

void SPrjEstablecerPrimero ( SPareja * p_prjObj, void * p_vDatos );
void SPrjEstablecerSegundo ( SPareja * p_prjObj, void * p_vDatos );


int	SPrjLiberacionMemoriaActivada ( SPareja * p_prjObj );
void SPrjActivarLiberacionMemoria ( SPareja * p_prjObj );
void SPrjDesactivarLiberacionMemoria ( SPareja * p_prjObj );


#endif
