#ifndef _ORG_GJS_C_CC_SPILACADENAS_H
#define _ORG_GJS_C_CC_SPILACADENAS_H








#include <SCadena.h>
#include <SPilaPtr.h>



// NOTA: Siempre duplica la cadena.


typedef struct
{
	SPilaPtr * p_pilDatos;

} SPilaCadenas;





SPilaCadenas * SPilCadCrear ();


void SPilCadDestruir ( SPilaCadenas ** p_p_pilObj );

int SPilCadEsValida ( SPilaCadenas * p_pilObj );

int SPilCadNumElementos ( SPilaCadenas * p_pilObj );
int SPilCadEstaVacia ( SPilaCadenas * p_pilObj );

SCadena * SPilCadPrimero ( SPilaCadenas * p_pilObj );
SCadena * SPilCadDesapilar ( SPilaCadenas * p_pilObj );

int SPilCadApilar ( SPilaCadenas * p_pilObj, SCadena * p_cadDato );
int SPilCadApilarLit ( SPilaCadenas * p_pilObj, const char * p_cDato );
int SPilCadApilarDup ( SPilaCadenas * p_pilObj, SCadena * p_cadDato );
int SPilCadEliminarPrimero ( SPilaCadenas * p_pilObj );
int SPilCadVaciar ( SPilaCadenas * p_pilObj );



#endif



