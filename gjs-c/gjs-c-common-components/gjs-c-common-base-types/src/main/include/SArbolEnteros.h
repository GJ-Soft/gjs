#ifndef _ORG_GJS_C_CC_SARBOLENTEROS_H
#define _ORG_GJS_C_CC_SARBOLENTEROS_H













#include <SArbol.h>



typedef struct 
{
	SArbol * p_arbObj;
	
} SArbolEnteros;



SArbolEnteros * SArbEntCrear ();

void SArbEntDestruir ( SArbolEnteros ** p_p_arbObj );

int SArbEntRaiz ( SArbolEnteros * p_arbObj );

int SArbEntEstablecerRaiz ( SArbolEnteros * p_arbObj, int iValor );

int SArbEntEstaVacio ( SArbolEnteros * p_arbObj );
int SArbEntNiveles ( SArbolEnteros * p_arbObj );
int SArbEntNumNodos ( SArbolEnteros * p_arbObj );

int SArbEntVaciar ( SArbolEnteros * p_arbObj );

int SArbEntActual ( SArbolEnteros * p_arbObj );
int SArbEntEstActual ( SArbolEnteros * p_arbObj, int iValor );

int SArbEntMoverARaiz ( SArbolEnteros * p_arbObj );
int SArbEntMoverAPadre ( SArbolEnteros * p_arbObj );
int SArbEntMoverAHijo ( SArbolEnteros * p_arbObj, int iHijo );
int SArbEntMoverAPrimHijo ( SArbolEnteros * p_arbObj );
int SArbEntMoverAUltHijo ( SArbolEnteros * p_arbObj );
int SArbEntMoverAPrimHermano ( SArbolEnteros * p_arbObj );
int SArbEntMoverASigHermano ( SArbolEnteros * p_arbObj );
int SArbEntMoverAAntHermano ( SArbolEnteros * p_arbObj );
int SArbEntMoverAUltHermano ( SArbolEnteros * p_arbObj );

int SArbEntMoverAPrimPreorden ( SArbolEnteros * p_arbObj );
int SArbEntMoverASigPreorden ( SArbolEnteros * p_arbObj );
int SArbEntMoverAPrimPostorden ( SArbolEnteros * p_arbObj );
int SArbEntMoverASigPostorden ( SArbolEnteros * p_arbObj );

void SArbEntDesposicionar ( SArbolEnteros * p_arbObj );
int	SArbEntEstaPosicionado ( SArbolEnteros * p_arbObj );
int SArbEntMoverAPrimPostorden ( SArbolEnteros * p_arbObj );
int SArbEntMoverASigPostorden ( SArbolEnteros * p_arbObj );
int SArbEntMoverAPrimInorden ( SArbolEnteros * p_arbObj );
int SArbEntMoverASigInorden ( SArbolEnteros * p_arbObj );

int SArbEntEnraizar ( SArbolEnteros * p_arbObj, int iValor );

int SArbEntVerificar ( SArbolEnteros * p_arbObj, int iCorregir );




#endif

