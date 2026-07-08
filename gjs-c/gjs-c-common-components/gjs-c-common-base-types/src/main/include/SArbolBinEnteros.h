
#ifndef _ORG_GJS_C_CC_SARBOLBINENTEROS_H
#define _ORG_GJS_C_CC_SARBOLBINENTEROS_H












#include <SArbolBin.h>




typedef struct
{
	SArbolBin * p_arbbObj;
	
} SArbolBinEnteros;




SArbolBinEnteros * SArbBinEntCrear ();

void SArbBinEntDestruir ( SArbolBinEnteros ** p_p_arbbObj );

int SArbBinEntRaiz ( SArbolBinEnteros * p_arbbObj );
int SArbBinEntEstablecerRaiz ( SArbolBinEnteros * p_arbbObj, int iValor );

int SArbBinEntEstaVacio ( SArbolBinEnteros * p_arbbObj );
int SArbBinEntNiveles ( SArbolBinEnteros * p_arbbObj );
int SArbBinEntNumNodos ( SArbolBinEnteros * p_arbbObj );

void SArbBinEntVaciar ( SArbolBinEnteros * p_arbbObj );

int SArbBinEntActual ( SArbolBinEnteros * p_arbbObj );
int SArbBinEntEstActual ( SArbolBinEnteros * p_arbbObj, int iValor );

int SArbBinEntPadre ( SArbolBinEnteros * p_arbbObj );
int SArbBinEntHijoDer ( SArbolBinEnteros * p_arbbObj );
int SArbBinEntHijoIzq ( SArbolBinEnteros * p_arbbObj );

int SArbBinEntTienePadre ( SArbolBinEnteros * p_arbbObj );
int SArbBinEntTieneHijos ( SArbolBinEnteros * p_arbbObj );
int SArbBinEntTieneHermano ( SArbolBinEnteros * p_arbbObj );
int SArbBinEntEsHijoIzqDelPadre ( SArbolBinEnteros * p_arbbObj );
int SArbBinEntEsHijoDerDelPadre ( SArbolBinEnteros * p_arbbObj );
int SArbBinEntTieneHijoIzq ( SArbolBinEnteros * p_arbbObj );
int SArbBinEntTieneHijoDer ( SArbolBinEnteros * p_arbbObj );
int SArbBinEntTieneHermanoIzq ( SArbolBinEnteros * p_arbbObj );
int SArbBinEntTieneHermanoDer ( SArbolBinEnteros * p_arbbObj );

int SArbBinEntMoverARaiz ( SArbolBinEnteros * p_arbbObj );
int SArbBinEntMoverAPadre ( SArbolBinEnteros * p_arbbObj );
int SArbBinEntMoverAHijoIzq ( SArbolBinEnteros * p_arbbObj );
int SArbBinEntMoverAHijoDer ( SArbolBinEnteros * p_arbbObj );
int SArbBinEntMoverAHermano ( SArbolBinEnteros * p_arbbObj );

int SArbBinEntMoverAPrimPreorden ( SArbolBinEnteros * p_arbbObj );
int SArbBinEntMoverASigPreorden ( SArbolBinEnteros * p_arbbObj );
int SArbBinEntMoverAPrimPostorden ( SArbolBinEnteros * p_arbbObj );
int SArbBinEntMoverASigPostorden ( SArbolBinEnteros * p_arbbObj );
int SArbBinEntMoverAPrimInorden ( SArbolBinEnteros * p_arbbObj );
int SArbBinEntMoverASigInorden ( SArbolBinEnteros * p_arbbObj );

void SArbBinEntDesposicionar ( SArbolBinEnteros * p_arbbObj );
int	SArbBinEntEstaPosicionado ( SArbolBinEnteros * p_arbbObj );

int SArbBinEntEnraizar ( SArbolBinEnteros * p_arbbObj, int iValor );

int SArbBinEntVerificar ( SArbolBinEnteros * p_arbbObj, int iCorregir );


#endif



