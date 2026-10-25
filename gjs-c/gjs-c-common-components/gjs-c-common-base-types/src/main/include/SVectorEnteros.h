#ifndef _ORG_GJS_C_CC_SVECTORENTEROS_H
#define _ORG_GJS_C_CC_SVECTORENTEROS_H








#include <SVector.h>



typedef struct
{
	SVector * p_vecDatos;

} SVectorEnteros;





SVectorEnteros * SVecIntCrear ( int iNumElementos );


void SVecIntDestruir ( SVectorEnteros ** p_p_vecObj );

int SVecIntEsValido ( SVectorEnteros * p_vecObj );

int SVecIntNumElementos ( SVectorEnteros * p_vecObj );
int SVecIntElemento ( SVectorEnteros * p_vecObj, int iElem );
int SVecIntAsignar ( SVectorEnteros * p_vecObj, int iElem, int iDato );

int SVecIntInicializar ( SVectorEnteros * p_vecObj );

int SVecIntExiste ( SVectorEnteros * p_vecObj, int iDato );



#endif


