#ifndef _ORG_GJS_C_CC_SVECTORCADENAS_H
#define _ORG_GJS_C_CC_SVECTORCADENAS_H








#include <SCadena.h>
#include <SVectorPtr.h>




typedef struct
{
	SVectorPtr * p_vecDatos;

} SVectorCadenas;





SVectorCadenas * SVecCadCrear ( int iNumElementos );


void SVecCadDestruir ( SVectorCadenas ** p_p_vecObj );

int SVecCadEsValida ( SVectorCadenas * p_vecObj );

int SVecCadNumElementos ( SVectorCadenas * p_vecObj );

SCadena * SVecCadElemento ( SVectorCadenas * p_vecObj, int iElem );

int SVecCadAsignar ( SVectorCadenas * p_vecObj, int iElem, SCadena * p_cadDato );
int SVecCadAsignarDup ( SVectorCadenas * p_vecObj, int iElem, SCadena * p_cadDato );
int SVecCadLimpiarElemento ( SVectorCadenas * p_vecObj, int iElem );
int SVecCadLimpiar ( SVectorCadenas * p_vecObj );

int SVecCadExiste ( SVectorCadenas * p_vecObj, SCadena * p_cadDato );

#endif