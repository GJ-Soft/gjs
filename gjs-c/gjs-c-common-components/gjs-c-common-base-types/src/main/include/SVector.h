#ifndef SVECTOR_H
#define SVECTOR_H








#include <SContenido.h>




typedef struct
{
	SContenido **	p_p_conElementos;
	int				iNumElementos;

} SVector;




SVector * SVecCrear ( int iNumElementos );

void SVecDestruir ( SVector ** p_p_vecObj );

int SVecEsValido ( SVector * p_vecObj );

int SVecNumElementos ( SVector * p_vecObj );
SContenido * SVecElemento ( SVector * p_vecObj, int iElem );
int SVecAsignar ( SVector * p_vecObj, int iElem, SContenido * p_conElem ); 

int SVecLimpiarElemento ( SVector * p_vecObj, int iElem ); 
int SVecLimpiar ( SVector * p_vecObj );



#endif
