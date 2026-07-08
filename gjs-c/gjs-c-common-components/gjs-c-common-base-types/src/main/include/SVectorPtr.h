#ifndef SVECTORPTR_H
#define SVECTORPTR_H








#include <SContenido.h>




typedef struct
{
	byte **	p_p_byElementos;
	int		iNumElementos;

	int		iLiberar;

} SVectorPtr;


//PENDIENTE: permitir elegir entre liberacion automatico y no

SVectorPtr * SVecpCrear ( int iNumElementos );

void SVecpDestruir ( SVectorPtr ** p_p_vecObj );

int SVecpEsValido ( SVectorPtr * p_vecObj );

int SVecpNumElementos ( SVectorPtr * p_vecObj );
byte * SVecpElemento ( SVectorPtr * p_vecObj, int iElem );
int SVecpAsignar ( SVectorPtr * p_vecObj, int iElem, byte * p_byElem ); 

int SVecpLimpiarElemento ( SVectorPtr * p_vecObj, int iElem ); 
int SVecpLimpiar ( SVectorPtr * p_vecObj );

int	SVecpLiberacionMemoriaActivada ( SVectorPtr * p_vecObj );
void SVecpActivarLiberacionMemoria ( SVectorPtr * p_vecObj );
void SVecpDesactivarLiberacionMemoria ( SVectorPtr * p_vecObj );


#endif