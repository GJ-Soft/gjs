#ifndef _ORG_GJS_C_CC_SVECTORENTEROS_H
#define _ORG_GJS_C_CC_SVECTORENTEROS_H








#include <SVector.h>



typedef struct
{
	SVector * p_vecDatos;

} SVectorEnteros;





SVectorEnteros * SVecEntCrear ( int iNumElementos );


void SVecEntDestruir ( SVectorEnteros ** p_p_vecObj );

int SVecEntEsValido ( SVectorEnteros * p_vecObj );

int SVecEntNumElementos ( SVectorEnteros * p_vecObj );
int SVecEntElemento ( SVectorEnteros * p_vecObj, int iElem );
int SVecEntAsignar ( SVectorEnteros * p_vecObj, int iElem, int iDato );

int SVecEntInicializar ( SVectorEnteros * p_vecObj );

int SVecEntExiste ( SVectorEnteros * p_vecObj, int iDato );



#endif


