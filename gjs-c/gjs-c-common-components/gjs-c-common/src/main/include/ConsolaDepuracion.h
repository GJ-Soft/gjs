

#ifndef _ORG_GJS_C_CC_CONSOLADEPURACION_H
#define _ORG_GJS_C_CC_CONSOLADEPURACION_H

#include <Precompilacion.h>





#define						DEP_INIFUN			ConDepEscribirLinea ("<Mod: %s; Fun: %s> - INICIO", __FILE__, __FUNCTION__ )
#define						DEP_FINFUN			ConDepEscribirLinea ("<Mod: %s; Fun: %s> - FIN", __FILE__, __FUNCTION__ )




int ConDepAbrir ();
void ConDepCerrar ();
int ConDepEstaAbierta ();

void ConDepImprimir ( const char * p_cTexto, ... ) FORMATO_PRINTF ( 1, 2 );
int ConDepEscribir ( const char * p_cTexto, ... ) FORMATO_PRINTF ( 1, 2 );
int ConDepEscribirLinea ( const char * p_cTexto, ... ) FORMATO_PRINTF ( 1, 2 );

void ConDepEsperar ();

#endif

