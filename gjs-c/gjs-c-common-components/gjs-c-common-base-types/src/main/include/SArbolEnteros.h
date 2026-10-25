#ifndef _ORG_GJS_C_CC_SARBOLENTEROS_H
#define _ORG_GJS_C_CC_SARBOLENTEROS_H













#include <SArbol.h>



typedef struct 
{
	SArbol * p_arbObj;
	
} SArbolEnteros;



SArbolEnteros * SArbIntCrear ();

void SArbIntDestruir ( SArbolEnteros ** p_p_arbObj );

int SArbIntRaiz ( SArbolEnteros * p_arbObj );

int SArbIntEstablecerRaiz ( SArbolEnteros * p_arbObj, int iValor );

int SArbIntEstaVacio ( SArbolEnteros * p_arbObj );
int SArbIntNiveles ( SArbolEnteros * p_arbObj );
int SArbIntNumNodos ( SArbolEnteros * p_arbObj );

int SArbIntVaciar ( SArbolEnteros * p_arbObj );

int SArbIntActual ( SArbolEnteros * p_arbObj );
int SArbIntEstActual ( SArbolEnteros * p_arbObj, int iValor );

int SArbIntMoverARaiz ( SArbolEnteros * p_arbObj );
int SArbIntMoverAPadre ( SArbolEnteros * p_arbObj );
int SArbIntMoverAHijo ( SArbolEnteros * p_arbObj, int iHijo );
int SArbIntMoverAPrimHijo ( SArbolEnteros * p_arbObj );
int SArbIntMoverAUltHijo ( SArbolEnteros * p_arbObj );
int SArbIntMoverAPrimHermano ( SArbolEnteros * p_arbObj );
int SArbIntMoverASigHermano ( SArbolEnteros * p_arbObj );
int SArbIntMoverAAntHermano ( SArbolEnteros * p_arbObj );
int SArbIntMoverAUltHermano ( SArbolEnteros * p_arbObj );

int SArbIntMoverAPrimPreorden ( SArbolEnteros * p_arbObj );
int SArbIntMoverASigPreorden ( SArbolEnteros * p_arbObj );
int SArbIntMoverAPrimPostorden ( SArbolEnteros * p_arbObj );
int SArbIntMoverASigPostorden ( SArbolEnteros * p_arbObj );

void SArbIntDesposicionar ( SArbolEnteros * p_arbObj );
int	SArbIntEstaPosicionado ( SArbolEnteros * p_arbObj );
int SArbIntMoverAPrimPostorden ( SArbolEnteros * p_arbObj );
int SArbIntMoverASigPostorden ( SArbolEnteros * p_arbObj );
int SArbIntMoverAPrimInorden ( SArbolEnteros * p_arbObj );
int SArbIntMoverASigInorden ( SArbolEnteros * p_arbObj );

int SArbIntEnraizar ( SArbolEnteros * p_arbObj, int iValor );

int SArbIntVerificar ( SArbolEnteros * p_arbObj, int iCorregir );




#endif

