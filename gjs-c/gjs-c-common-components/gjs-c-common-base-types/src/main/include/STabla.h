#ifndef _ORG_GJS_C_CC_C_COMMON_STABLA_H
#define _ORG_GJS_C_CC_C_COMMON_STABLA_H








#include <SVector.h>
#include <SContenido.h>



typedef struct
{
	SVector *	p_vecElementos;
	int			iNumFilas;
	int			iNumColumnas;

} STabla;




STabla * STabCrear ( int iNumFilas, int iNumColumnas );

void STabDestruir ( STabla ** p_p_tabObj );

int STabEsValida ( STabla * p_tabObj );

int STabNumFilas ( STabla * p_tabObj );
int STabNumColumnas ( STabla * p_tabObj );
int STabNumElementos ( STabla * p_tabObj );

SContenido * STabElemento ( STabla * p_tabObj, int iFila, int iColumna );
int STabAsignar ( STabla * p_tabObj, int iFila, int iColumna, SContenido * p_conElem ); 

int STabLimpiarElemento ( STabla * p_tabObj, int iFila, int iColumna ); 
int STabLimpiar ( STabla * p_tabObj );

SVector * STabVector ( STabla * p_tabObj );


#endif
