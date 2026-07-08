#ifndef _ORG_GJS_C_CC_STABLALITERALES_H
#define _ORG_GJS_C_CC_STABLALITERALES_H








#include <STablaPtr.h>




typedef struct
{
	STablaPtr * p_tabDatos;

} STablaLiterales;





STablaLiterales * STabLitCrear ( int iNumFilas, int iNumColumnas );


void STabLitDestruir ( STablaLiterales ** p_p_tabObj );

int STabLitEsValida ( STablaLiterales * p_tabObj );

int STabLitNumFilas ( STablaLiterales * p_tabObj );
int STabLitNumColumnas ( STablaLiterales * p_tabObj );
int STabLitNumElementos ( STablaLiterales * p_tabObj );

char * STabLitElemento ( STablaLiterales * p_tabObj, int iFila, int iColumna );

int STabLitAsignar ( STablaLiterales * p_tabObj, int iFila, int iColumna, char * p_cDato );
int STabLitAsignarDup ( STablaLiterales * p_tabObj, int iFila, int iColumna, const char * p_cDato );
int STabLitLimpiarElemento ( STablaLiterales * p_tabObj, int iFila, int iColumna );
int STabLitLimpiar ( STablaLiterales * p_tabObj );

int	STabLitLiberacionMemoriaActivada ( STablaLiterales * p_tabObj );
void STabLitActivarLiberacionMemoria ( STablaLiterales * p_tabObj );
void STabLitDesactivarLiberacionMemoria ( STablaLiterales * p_tabObj );

int STabLitExiste ( STablaLiterales * p_tabObj, const char * p_cDato );

#endif