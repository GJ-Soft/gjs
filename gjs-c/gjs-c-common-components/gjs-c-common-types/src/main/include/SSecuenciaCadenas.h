#ifndef _ORG_GJS_C_CC_SSECUENCIACADENAS_H
#define _ORG_GJS_C_CC_SSECUENCIACADENAS_H







#include <SCadena.h>
#include <SSecuenciaPtr.h>



// NOTA: Siempre duplica la cadena.


typedef struct
{
	SSecuenciaPtr * p_secDatos;

} SSecuenciaCadenas;





SSecuenciaCadenas * SSecCadCrear ();


void SSecCadDestruir ( SSecuenciaCadenas ** p_p_secObj );

int SSecCadEsValida ( SSecuenciaCadenas * p_secObj );

int SSecCadNumElementos ( SSecuenciaCadenas * p_secObj );
int SSecCadEstaVacia ( SSecuenciaCadenas * p_secObj );

SCadena * SSecCadElemento ( SSecuenciaCadenas * p_secObj, int iElem );

int SSecCadInsertar ( SSecuenciaCadenas * p_secObj, SCadena * p_cadDato );
int SSecCadInsertarDup ( SSecuenciaCadenas * p_secObj, SCadena * p_cadDato );
int SSecCadEliminar ( SSecuenciaCadenas * p_secObj, int iElem );
int SSecCadVaciar ( SSecuenciaCadenas * p_secObj );

int SSecCadExiste ( SSecuenciaCadenas * p_secObj, SCadena * p_cadDato );


#endif