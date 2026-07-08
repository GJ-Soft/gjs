
#ifndef _ORG_GJS_C_CC_C_COMMON_SARBOLBIN_H
#define _SARBOLBIN_H











#include <SNodoBin.h>




typedef struct
{
	SNodoBin * p_nodbRaiz;
	SNodoBin * p_nodbActual;

} SArbolBin;




SArbolBin * SArbBinCrear ();

void SArbBinDestruir ( SArbolBin ** p_p_arbbObj );

SNodoBin * SArbBinRaiz ( SArbolBin * p_arbbObj );

int SArbBinEstablecerRaiz ( SArbolBin * p_arbbObj, SNodoBin * p_nodbObj );

int SArbBinEstaVacio ( SArbolBin * p_arbbObj );
int SArbBinNiveles ( SArbolBin * p_arbbObj );
int SArbBinNumNodos ( SArbolBin * p_arbbObj );

void SArbBinVaciar ( SArbolBin * p_arbbObj );

SNodoBin * SArbBinActual ( SArbolBin * p_arbbObj );

SNodoBin * SArbBinPadre ( SArbolBin * p_arbbObj );
SNodoBin * SArbBinHijoDer ( SArbolBin * p_arbbObj );
SNodoBin * SArbBinHijoIzq ( SArbolBin * p_arbbObj );

int SArbBinTienePadre ( SArbolBin * p_arbbObj );
int SArbBinTieneHijos ( SArbolBin * p_arbbObj );
int SArbBinTieneHermano ( SArbolBin * p_arbbObj );
int SArbBinEsHijoIzqDelPadre ( SArbolBin * p_arbbObj );
int SArbBinEsHijoDerDelPadre ( SArbolBin * p_arbbObj );
int SArbBinTieneHijoIzq ( SArbolBin * p_arbbObj );
int SArbBinTieneHijoDer ( SArbolBin * p_arbbObj );
int SArbBinTieneHermanoIzq ( SArbolBin * p_arbbObj );
int SArbBinTieneHermanoDer ( SArbolBin * p_arbbObj );

int SArbBinMoverARaiz ( SArbolBin * p_arbbObj );
int SArbBinMoverAPadre ( SArbolBin * p_arbbObj );
int SArbBinMoverAHijoIzq ( SArbolBin * p_arbbObj );
int SArbBinMoverAHijoDer ( SArbolBin * p_arbbObj );
int SArbBinMoverAHermano ( SArbolBin * p_arbbObj );

int SArbBinMoverAPrimPreorden ( SArbolBin * p_arbbObj );
int SArbBinMoverASigPreorden ( SArbolBin * p_arbbObj );
int SArbBinMoverAPrimPostorden ( SArbolBin * p_arbbObj );
int SArbBinMoverASigPostorden ( SArbolBin * p_arbbObj );
int SArbBinMoverAPrimInorden ( SArbolBin * p_arbbObj );
int SArbBinMoverASigInorden ( SArbolBin * p_arbbObj );

void SArbBinDesposicionar ( SArbolBin * p_arbbObj );
int	SArbBinEstaPosicionado ( SArbolBin * p_arbbObj );

int SArbBinEnraizar ( SArbolBin * p_arbbObj, SNodoBin * p_nodbObj );

int SArbBinVerificar ( SArbolBin * p_arbbObj, int iCorregir );


#endif



