#ifndef _ORG_GJS_C_CC_SVECTORENTEROS_H
#define _ORG_GJS_C_CC_SVECTORENTEROS_H








#include <SVector.h>



typedef struct
{
	SVector * p_vecDatos;

} SVectorEnteros;





SVectorEnteros * SVecIntCrear ( int iNumElementos );
SVectorEnteros * SVecIntCrearDesdeVector ( const int * p_iValores, int iNumValores );

/* Vector con una posicion por valor que se le pase, cuantos sean y sean
   cuales sean (el 0 tambien). El numero lo cuenta el compilador, sin marca
   de fin. Necesita al menos un valor: un vector no puede tener 0
   posiciones. Cada valor se evalua una vez: el segundo vector solo lo mide
   sizeof. */
#define SVecIntCrearConValores( ... ) \
	SVecIntCrearDesdeVector ( (const int []) { __VA_ARGS__ }, \
		(int) ( sizeof ( (const int []) { __VA_ARGS__ } ) / sizeof ( int ) ) )


void SVecIntDestruir ( SVectorEnteros ** p_p_vecObj );

int SVecIntEsValido ( SVectorEnteros * p_vecObj );

int SVecIntNumElementos ( SVectorEnteros * p_vecObj );
int SVecIntElemento ( SVectorEnteros * p_vecObj, int iElem );
int SVecIntAsignar ( SVectorEnteros * p_vecObj, int iElem, int iDato );

int SVecIntInicializar ( SVectorEnteros * p_vecObj );

int SVecIntExiste ( SVectorEnteros * p_vecObj, int iDato );



#endif


