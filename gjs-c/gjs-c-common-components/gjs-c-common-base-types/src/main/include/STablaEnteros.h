#ifndef _ORG_GJS_C_CC_STABLAENTEROS_H
#define _ORG_GJS_C_CC_STABLAENTEROS_H








#include <STabla.h>



typedef struct
{
	STabla * p_tabDatos;

} STablaEnteros;





STablaEnteros * STabIntCrear ( int iNumFilas, int iNumColumnas );


void STabIntDestruir ( STablaEnteros ** p_p_tabObj );

int STabIntEsValida ( STablaEnteros * p_tabObj );

int STabIntNumFilas ( STablaEnteros * p_tabObj );
int STabIntNumColumnas ( STablaEnteros * p_tabObj );
int STabIntNumElementos ( STablaEnteros * p_tabObj );
int STabIntElemento ( STablaEnteros * p_tabObj, int iFila, int iColumna );

int STabIntAsignar ( STablaEnteros * p_tabObj, int iFila, int iColumna, int iDato );
int STabIntInicializar ( STablaEnteros * p_tabObj );

int STabIntExiste ( STablaEnteros * p_tabObj, int iDato );



#endif



