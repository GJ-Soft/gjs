#ifndef _ORG_GJS_C_CC_SLISTACADENAS_H
#define _ORG_GJS_C_CC_SLISTACADENAS_H







#include <SCadena.h>
#include <SListaPtr.h>



typedef struct
{
	SListaPtr * p_lisDatos;

} SListaCadenas;


SListaCadenas * SLisCadCrear ();


void SLisCadDestruir ( SListaCadenas ** p_p_lisObj );

int SLisCadEsValida ( SListaCadenas * p_lisObj );
int SLisCadEstaVacia ( SListaCadenas * p_lisObj );

// Operaciones sin cursor:
int SLisCadNumElementos ( SListaCadenas * p_lisObj );
SCadena * SLisCadElemento ( SListaCadenas * p_lisObj, int iElem );

int SLisCadEstablecerElem ( SListaCadenas * p_lisObj, int iElem, SCadena * p_cadDatos );
int SLisCadInsertarElem ( SListaCadenas * p_lisObj, int iPosAnt, SCadena * p_cadDatos );
int SLisCadInsertarAlInicio ( SListaCadenas * p_lisObj, SCadena * p_cadDatos );
int SLisCadInsertarAlFinal ( SListaCadenas * p_lisObj, SCadena * p_cadDatos );
int SLisCadEstablecerElemDup ( SListaCadenas * p_lisObj, int iElem, SCadena * p_cadDatos );
int SLisCadInsertarElemDup ( SListaCadenas * p_lisObj, int iPosAnt, SCadena * p_cadDatos );
int SLisCadInsertarDupAlInicio ( SListaCadenas * p_lisObj, SCadena * p_cadDatos );
int SLisCadInsertarDupAlFinal ( SListaCadenas * p_lisObj, SCadena * p_cadDatos );

int SLisCadEliminarElem ( SListaCadenas * p_lisObj, int iElem );

int SLisCadVaciar ( SListaCadenas * p_lisObj );

// Operaciones dependientes del cursor:
int SLisCadPosicion ( SListaCadenas * p_lisObj );
SCadena * SLisCadActual ( SListaCadenas * p_lisObj );

void SLisCadInicio ( SListaCadenas * p_lisObj );
void SLisCadFinal ( SListaCadenas * p_lisObj );
void SLisCadSiguiente ( SListaCadenas * p_lisObj );
void SLisCadAnterior ( SListaCadenas * p_lisObj );
void SLisCadMoverA ( SListaCadenas * p_lisObj, int iElem );
void SLisCadDeposicionar ( SListaCadenas * p_lisObj );

int SLisCadEsNulo ( SListaCadenas * p_lisObj );
int SLisCadEstaEnFinal ( SListaCadenas * p_lisObj );
int SLisCadEstaEnInicio ( SListaCadenas * p_lisObj );

int SLisCadEstablecer ( SListaCadenas * p_lisObj, SCadena * p_cadDatos );
int SLisCadInsertar ( SListaCadenas * p_lisObj, SCadena * p_cadDatos );
int SLisCadInsertarDelante ( SListaCadenas * p_lisObj, SCadena * p_cadDatos );
int SLisCadInsertarDetras ( SListaCadenas * p_lisObj, SCadena * p_cadDatos );
int SLisCadEstablecerDup ( SListaCadenas * p_lisObj, SCadena * p_cadDatos );
int SLisCadInsertarDup ( SListaCadenas * p_lisObj, SCadena * p_cadDatos );
int SLisCadInsertarDupDelante ( SListaCadenas * p_lisObj, SCadena * p_cadDatos );
int SLisCadInsertarDupDetras ( SListaCadenas * p_lisObj, SCadena * p_cadDatos );
int SLisCadEliminar ( SListaCadenas * p_lisObj );

int SLisCadExiste ( SListaCadenas * p_lisObj, SCadena * p_cadDatos );
int SLisCadBuscar ( SListaCadenas * p_lisObj, SCadena * p_cadDatos );
int SLisCadBuscarExt ( SListaCadenas * p_lisObj, const char * p_cDatos );



#endif



