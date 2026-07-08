#ifndef _ORG_GJS_C_CC_STABLACADENAS_H
#define _ORG_GJS_C_CC_STABLACADENAS_H








#include <SCadena.h>
#include <STablaPtr.h>




typedef struct
{
	STablaPtr * p_tabDatos;

} STablaCadenas;





STablaCadenas * STabCadCrear ( int iNumFilas, int iNumColumnas );


void STabCadDestruir ( STablaCadenas ** p_p_tabObj );

int STabCadEsValida ( STablaCadenas * p_tabObj );

int STabCadNumFilas ( STablaCadenas * p_tabObj );
int STabCadNumColumnas ( STablaCadenas * p_tabObj );
int STabCadNumElementos ( STablaCadenas * p_tabObj );

SCadena * STabCadElemento ( STablaCadenas * p_tabObj, int iFila, int iColumna );

int STabCadAsignar ( STablaCadenas * p_tabObj, int iFila, int iColumna, SCadena * p_cadDato );
int STabCadAsignarDup ( STablaCadenas * p_tabObj, int iFila, int iColumna, SCadena * p_cadDato );
int STabCadLimpiarElemento ( STablaCadenas * p_tabObj, int iFila, int iColumna );
int STabCadLimpiar ( STablaCadenas * p_tabObj );

int STabCadExiste ( STablaCadenas * p_tabObj, SCadena * p_cadDato );

#endif