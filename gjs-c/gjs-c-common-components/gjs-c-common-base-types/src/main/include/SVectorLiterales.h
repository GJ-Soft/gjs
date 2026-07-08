#ifndef _ORG_GJS_C_CC_SVECTORLITERALES_H
#define _ORG_GJS_C_CC_SVECTORLITERALES_H








#include <SVectorPtr.h>




typedef struct
{
	SVectorPtr * p_vecDatos;

} SVectorLiterales;





SVectorLiterales * SVecLitCrear ( int iNumElementos );


void SVecLitDestruir ( SVectorLiterales ** p_p_vecObj );

int SVecLitEsValido ( SVectorLiterales * p_vecObj );

int SVecLitNumElementos ( SVectorLiterales * p_vecObj );

char * SVecLitElemento ( SVectorLiterales * p_vecObj, int iElem );

int SVecLitAsignar ( SVectorLiterales * p_vecObj, int iElem, char * p_cDato );
int SVecLitAsignarDup ( SVectorLiterales * p_vecObj, int iElem, const char * p_cDato );
int SVecLitLimpiarElemento ( SVectorLiterales * p_vecObj, int iElem );
int SVecLitLimpiar ( SVectorLiterales * p_vecObj );

int	SVecLitLiberacionMemoriaActivada ( SVectorLiterales * p_vecObj );
void SVecLitActivarLiberacionMemoria ( SVectorLiterales * p_vecObj );
void SVecLitDesactivarLiberacionMemoria ( SVectorLiterales * p_vecObj );

int SVecLitExiste ( SVectorLiterales * p_vecObj, const char * p_cDato );

#endif