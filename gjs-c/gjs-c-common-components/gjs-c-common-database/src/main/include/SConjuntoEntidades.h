#ifndef _ORG_GJS_C_CC_SCONJUNTOENTIDADES_H
#define _ORG_GJS_C_CC_SCONJUNTOENTIDADES_H








#include <SConjuntoPtr.h>
#include <SEntidad.h>



typedef struct
{
	SConjuntoPtr * p_cnjDatos;

} SConjuntoEntidades;





SConjuntoEntidades * SCnjEntCrear ();


void SCnjEntDestruir ( SConjuntoEntidades ** p_p_cnjObj );

int SCnjEntEsValido ( SConjuntoEntidades * p_cnjObj );

int SCnjEntNumElementos ( SConjuntoEntidades * p_cnjObj );
int SCnjEntEstaVacio ( SConjuntoEntidades * p_cnjObj );

SEntidad * SCnjEntElemento ( SConjuntoEntidades * p_cnjObj, int iElem );
SEntidad * SCnjEntPrimero ( SConjuntoEntidades * p_cnjObj );
SEntidad * SCnjEntUltimo ( SConjuntoEntidades * p_cnjObj );
int SCnjEntPosicion ( SConjuntoEntidades * p_cnjObj, SEntidad * p_entDato );

int SCnjEntInsertar ( SConjuntoEntidades * p_cnjObj, SEntidad * p_entDato );
int SCnjEntEliminar ( SConjuntoEntidades * p_cnjObj, int iElem );
SEntidad * SCnjEntExtraer ( SConjuntoEntidades * p_cnjObj, int iElem );
int SCnjEntVaciar ( SConjuntoEntidades * p_cnjObj );

int SCnjEntExiste ( SConjuntoEntidades * p_cnjObj, SEntidad * p_entDato );
int SCnjEntBuscar ( SConjuntoEntidades * p_cnjObj, SEntidad * p_entDato );
int SCnjEntExisteId ( SConjuntoEntidades * p_cnjObj, SId * p_idEntidad );
int SCnjEntExisteValorId ( SConjuntoEntidades * p_cnjObj, unsigned long ulId );
int SCnjEntBuscarId ( SConjuntoEntidades * p_cnjObj, SId * p_idEntidad );
int SCnjEntBuscarValorId ( SConjuntoEntidades * p_cnjObj, unsigned long ulId );

#endif