#ifndef _ORG_GJS_C_CC_SVECTORLITERALES_H
#define _ORG_GJS_C_CC_SVECTORLITERALES_H








#include <SVectorPtr.h>




typedef struct
{
	SVectorPtr * p_vecDatos;

} SVectorLiterales;





SVectorLiterales * SVecLitCrear ( int iNumElementos );
SVectorLiterales * SVecLitCrearDesdeVector ( const char * const * p_p_cValores, int iNumValores );

/* Vector con una posicion por cadena que se le pase, cuantas sean, con su
   copia; NULL deja la posicion vacia. El numero lo cuenta el compilador,
   sin marca de fin. Necesita al menos un valor: un vector no puede tener 0
   posiciones. Cada valor se evalua una vez: el segundo vector solo lo mide
   sizeof. */
#define SVecLitCrearConValores( ... ) \
	SVecLitCrearDesdeVector ( (const char * const []) { __VA_ARGS__ }, \
		(int) ( sizeof ( (const char * const []) { __VA_ARGS__ } ) / sizeof ( char * ) ) )


void SVecLitDestruir ( SVectorLiterales ** p_p_vecObj );

int SVecLitEsValido ( SVectorLiterales * p_vecObj );

int SVecLitNumElementos ( SVectorLiterales * p_vecObj );

char * SVecLitElemento ( SVectorLiterales * p_vecObj, int iElem );

int SVecLitAsignar ( SVectorLiterales * p_vecObj, int iElem, char * p_cDato );
int SVecLitAsignarDup ( SVectorLiterales * p_vecObj, int iElem, const char * p_cDato );
int SVecLitLimpiarElemento ( SVectorLiterales * p_vecObj, int iElem );
int SVecLitLimpiar ( SVectorLiterales * p_vecObj );

int	SVecLitLiberacionMemoriaActivada ( SVectorLiterales * p_vecObj );
void SVecLitActivarLiberacionMemoria ( SVectorLiterales * p_vecObj );
void SVecLitDesactivarLiberacionMemoria ( SVectorLiterales * p_vecObj );

int SVecLitExiste ( SVectorLiterales * p_vecObj, const char * p_cDato );

#endif