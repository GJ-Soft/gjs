#ifndef _GJS_BNF_LIB_SARBOLLITERALES_H
#define _GJS_BNF_LIB_SARBOLLITERALES_H




#include <SArbolPtr.h>




typedef struct
{
	SArbolPtr * p_arbContenido;

} SArbolLiterales;





SArbolLiterales * SArbLitCrear ();

void SArbLitDestruir ( SArbolLiterales ** p_p_arbObj );

char * SArbLitRaiz ( SArbolLiterales * p_arbObj );

int SArbLitEstablecerRaiz ( SArbolLiterales * p_arbObj, const char * p_cValor );

int SArbLitEstaVacio ( SArbolLiterales * p_arbObj );
int SArbLitNiveles ( SArbolLiterales * p_arbObj );
int SArbLitNumNodos ( SArbolLiterales * p_arbObj );

int SArbLitVaciar ( SArbolLiterales * p_arbObj );

char * SArbLitActual ( SArbolLiterales * p_arbObj );

int SArbLitMoverARaiz ( SArbolLiterales * p_arbObj );
int SArbLitMoverAPadre ( SArbolLiterales * p_arbObj );
int SArbLitMoverAHijo ( SArbolLiterales * p_arbObj, int iHijo );
int SArbLitMoverAPrimHijo ( SArbolLiterales * p_arbObj );
int SArbLitMoverAUltHijo ( SArbolLiterales * p_arbObj );
int SArbLitMoverAPrimHermano ( SArbolLiterales * p_arbObj );
int SArbLitMoverASigHermano ( SArbolLiterales * p_arbObj );
int SArbLitMoverAAntHermano ( SArbolLiterales * p_arbObj );
int SArbLitMoverAUltHermano ( SArbolLiterales * p_arbObj );

int SArbLitMoverAPrimPreorden ( SArbolLiterales * p_arbObj );
int SArbLitMoverASigPreorden ( SArbolLiterales * p_arbObj );
int SArbLitMoverAPrimPostorden ( SArbolLiterales * p_arbObj );
int SArbLitMoverASigPostorden ( SArbolLiterales * p_arbObj );

void SArbLitDesposicionar ( SArbolLiterales * p_arbObj );
int	SArbLitEstaPosicionado ( SArbolLiterales * p_arbObj );

int SArbLitEnraizar ( SArbolLiterales * p_arbObj, const char * p_cValor );

int SArbLitActualEsValido ( SArbolLiterales * p_arbObj );
int SArbLitActualTieneDatos ( SArbolLiterales * p_arbObj );

int SArbLitActualModificar ( SArbolLiterales * p_arbObj, const char * p_cValor );

int SArbLitActualNumHijos ( SArbolLiterales * p_arbObj );
char * SArbLitActualPadre ( SArbolLiterales * p_arbObj );
char * SArbLitActualHijo ( SArbolLiterales * p_arbObj, int iHijo );

int SArbLitActualTienePadre ( SArbolLiterales * p_arbObj );
int SArbLitActualTieneHijos ( SArbolLiterales * p_arbObj );
int SArbLitActualTieneHermanos ( SArbolLiterales * p_arbObj );
int SArbLitActualTieneHermanosIzq ( SArbolLiterales * p_arbObj );
int SArbLitActualTieneHermanosDer ( SArbolLiterales * p_arbObj );

int SArbLitActualNodosInferiores ( SArbolLiterales * p_arbObj );
int SArbLitActualProfundidad ( SArbolLiterales * p_arbObj );
int SArbLitActualNivelesInferiores ( SArbolLiterales * p_arbObj );

int SArbLitActualInsertarHijo ( SArbolLiterales * p_arbObj, const char * p_cValor );
int SArbLitActualEliminarHijo ( SArbolLiterales * p_arbObj, int iHijo );
int SArbLitActualEstablecerHijo ( SArbolLiterales * p_arbObj, int iHijo, const char * p_cValor );
void SArbLitActualLimpiarHijos ( SArbolLiterales * p_arbObj  );

int	SArbLitActualEsHijo ( SArbolLiterales * p_arbObj );

int SArbLitVerificar ( SArbolLiterales * p_arbObj, int iCorregir );


void SArbLitImprimir  ( SArbolLiterales * p_arbObj );




#endif

