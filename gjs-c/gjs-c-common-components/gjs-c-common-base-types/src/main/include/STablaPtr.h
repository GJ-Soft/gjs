#ifndef _ORG_GJS_C_CC_C_COMMON_STABLAPTR_H
#define _ORG_GJS_C_CC_C_COMMON_STABLAPTR_H








#include <SVectorPtr.h>




typedef struct
{
	SVectorPtr *	p_vecElementos;
	int				iNumFilas;
	int				iNumColumnas;

} STablaPtr;


STablaPtr * STabpCrear ( int iNumFilas, int iNumColumnas );

void STabpDestruir ( STablaPtr ** p_p_tabObj );

int STabpEsValida ( STablaPtr * p_tabObj );

int STabpNumFilas ( STablaPtr * p_tabObj );
int STabpNumColumnas ( STablaPtr * p_tabObj );
int STabpNumElementos ( STablaPtr * p_tabObj );

byte * STabpElemento ( STablaPtr * p_tabObj, int iFila, int iColumna );
int STabpAsignar ( STablaPtr * p_tabObj, int iFila, int iColumna, byte * p_byElem ); 

int STabpLimpiarElemento ( STablaPtr * p_tabObj, int iFila, int iColumna ); 
int STabpLimpiar ( STablaPtr * p_tabObj );

SVectorPtr * STabpVector ( STablaPtr * p_tabObj );

int	STabpLiberacionMemoriaActivada ( STablaPtr * p_tabObj );
void STabpActivarLiberacionMemoria ( STablaPtr * p_tabObj );
void STabpDesactivarLiberacionMemoria ( STablaPtr * p_tabObj );


#endif
