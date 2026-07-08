#ifndef _ORG_GJS_C_CC_STABLAENTEROS_H
#define _ORG_GJS_C_CC_STABLAENTEROS_H








#include <STabla.h>



typedef struct
{
	STabla * p_tabDatos;

} STablaEnteros;





STablaEnteros * STabEntCrear ( int iNumFilas, int iNumColumnas );


void STabEntDestruir ( STablaEnteros ** p_p_tabObj );

int STabEntEsValida ( STablaEnteros * p_tabObj );

int STabEntNumFilas ( STablaEnteros * p_tabObj );
int STabEntNumColumnas ( STablaEnteros * p_tabObj );
int STabEntNumElementos ( STablaEnteros * p_tabObj );
int STabEntElemento ( STablaEnteros * p_tabObj, int iFila, int iColumna );

int STabEntAsignar ( STablaEnteros * p_tabObj, int iFila, int iColumna, int iDato );
int STabEntInicializar ( STablaEnteros * p_tabObj );

int STabEntExiste ( STablaEnteros * p_tabObj, int iDato );



#endif



