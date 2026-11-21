#ifndef _ORG_GJS_C_CC_SVECTORREALESDOBLES_H
#define _ORG_GJS_C_CC_SVECTORREALESDOBLES_H








#include <SVector.h>



typedef struct
{
	SVector * p_vecDatos;

} SVectorRealesDobles;





SVectorRealesDobles * SVecRealdCrear ( int iNumElementos );
SVectorRealesDobles * SVecRealdCrearDesdeVector ( const double * p_dValores, int iNumValores );

/* Vector con una posicion por valor que se le pase, cuantos sean y sean
   cuales sean (el 0 tambien). El numero lo cuenta el compilador, sin marca
   de fin. Necesita al menos un valor: un vector no puede tener 0
   posiciones. Cada valor se evalua una vez: el segundo vector solo lo mide
   sizeof. */
#define SVecRealdCrearConValores( ... ) \
	SVecRealdCrearDesdeVector ( (const double []) { __VA_ARGS__ }, \
		(int) ( sizeof ( (const double []) { __VA_ARGS__ } ) / sizeof ( double ) ) )



void SVecRealdDestruir ( SVectorRealesDobles ** p_p_vecObj );

int SVecRealdEsValido ( SVectorRealesDobles * p_vecObj );

int SVecRealdNumElementos ( SVectorRealesDobles * p_vecObj );
double SVecRealdElemento ( SVectorRealesDobles * p_vecObj, int iElem );
int SVecRealdAsignar ( SVectorRealesDobles * p_vecObj, int iElem, double dDato );

int SVecRealdInicializar ( SVectorRealesDobles * p_vecObj );

int SVecRealdExiste ( SVectorRealesDobles * p_vecObj, double dDato );


#endif