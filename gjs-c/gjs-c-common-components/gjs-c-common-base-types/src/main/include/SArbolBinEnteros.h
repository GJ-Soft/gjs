
#ifndef _ORG_GJS_C_CC_SARBOLBINENTEROS_H
#define _ORG_GJS_C_CC_SARBOLBINENTEROS_H












#include <SArbolBin.h>




typedef struct
{
	SArbolBin * p_arbbObj;
	
} SArbolBinEnteros;




SArbolBinEnteros * SArbBinIntCrear ();

void SArbBinIntDestruir ( SArbolBinEnteros ** p_p_arbbObj );

int SArbBinIntRaiz ( SArbolBinEnteros * p_arbbObj );
int SArbBinIntEstablecerRaiz ( SArbolBinEnteros * p_arbbObj, int iValor );

int SArbBinIntEstaVacio ( SArbolBinEnteros * p_arbbObj );
int SArbBinIntNiveles ( SArbolBinEnteros * p_arbbObj );
int SArbBinIntNumNodos ( SArbolBinEnteros * p_arbbObj );

void SArbBinIntVaciar ( SArbolBinEnteros * p_arbbObj );

int SArbBinIntActual ( SArbolBinEnteros * p_arbbObj );
int SArbBinIntEstActual ( SArbolBinEnteros * p_arbbObj, int iValor );

int SArbBinIntPadre ( SArbolBinEnteros * p_arbbObj );
int SArbBinIntHijoDer ( SArbolBinEnteros * p_arbbObj );
int SArbBinIntHijoIzq ( SArbolBinEnteros * p_arbbObj );

int SArbBinIntTienePadre ( SArbolBinEnteros * p_arbbObj );
int SArbBinIntTieneHijos ( SArbolBinEnteros * p_arbbObj );
int SArbBinIntTieneHermano ( SArbolBinEnteros * p_arbbObj );
int SArbBinIntEsHijoIzqDelPadre ( SArbolBinEnteros * p_arbbObj );
int SArbBinIntEsHijoDerDelPadre ( SArbolBinEnteros * p_arbbObj );
int SArbBinIntTieneHijoIzq ( SArbolBinEnteros * p_arbbObj );
int SArbBinIntTieneHijoDer ( SArbolBinEnteros * p_arbbObj );
int SArbBinIntTieneHermanoIzq ( SArbolBinEnteros * p_arbbObj );
int SArbBinIntTieneHermanoDer ( SArbolBinEnteros * p_arbbObj );

int SArbBinIntMoverARaiz ( SArbolBinEnteros * p_arbbObj );
int SArbBinIntMoverAPadre ( SArbolBinEnteros * p_arbbObj );
int SArbBinIntMoverAHijoIzq ( SArbolBinEnteros * p_arbbObj );
int SArbBinIntMoverAHijoDer ( SArbolBinEnteros * p_arbbObj );
int SArbBinIntMoverAHermano ( SArbolBinEnteros * p_arbbObj );

int SArbBinIntMoverAPrimPreorden ( SArbolBinEnteros * p_arbbObj );
int SArbBinIntMoverASigPreorden ( SArbolBinEnteros * p_arbbObj );
int SArbBinIntMoverAPrimPostorden ( SArbolBinEnteros * p_arbbObj );
int SArbBinIntMoverASigPostorden ( SArbolBinEnteros * p_arbbObj );
int SArbBinIntMoverAPrimInorden ( SArbolBinEnteros * p_arbbObj );
int SArbBinIntMoverASigInorden ( SArbolBinEnteros * p_arbbObj );

void SArbBinIntDesposicionar ( SArbolBinEnteros * p_arbbObj );
int	SArbBinIntEstaPosicionado ( SArbolBinEnteros * p_arbbObj );

int SArbBinIntEnraizar ( SArbolBinEnteros * p_arbbObj, int iValor );

int SArbBinIntVerificar ( SArbolBinEnteros * p_arbbObj, int iCorregir );


#endif



