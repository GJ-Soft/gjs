#ifndef _ORG_GJS_C_CC_SFICESTRUCTURA_H
#define _ORG_GJS_C_CC_SFICESTRUCTURA_H





#include <SFicBloques.h>
#include <SBloque.h>
#include <SRuta.h>




typedef struct
{
	SFicBloques *	p_ficDatos;
	SBloque *		p_blqBufDatos;

} SFicEstructura;




SFicEstructura * SFicEstCrear ( const char * p_cRuta, int iTamElemento );
SFicEstructura * SFicEstAbrir ( const char * p_cRuta );
SFicEstructura * SFicEstCrearExt ( const char * p_cDir, const char * p_cFic, int iTamElemento );
SFicEstructura * SFicEstAbrirExt ( const char * p_cDir, const char * p_cFic, int * p_iTamElemento );
SFicEstructura * SFicEstAbrirOCrear ( const char * p_cRuta, int iTamElemento );
SFicEstructura * SFicEstAbrirOCrearExt ( const char * p_cDir, const char * p_cFic, int * p_iTamElemento );
SFicEstructura * SFicEstCrearRuta ( SRuta * p_rutRuta, int iTamElemento );

void SFicEstDestruir ( SFicEstructura ** p_p_ficObj );
void SFicEstEliminar ( SFicEstructura ** p_p_ficObj );

int SFicEstEsValido ( SFicEstructura * p_ficObj );

const char * SFicEstRuta ( SFicEstructura * p_ficObj ); 
char * SFicEstDirectorio ( SFicEstructura * p_ficObj ); 
char * SFicEstFichero ( SFicEstructura * p_ficObj ); 
int SFicEstEstablecerRuta ( SFicEstructura * p_ficObj, const char * p_cRuta );
int SFicEstEstablecerRutaExt ( SFicEstructura * p_ficObj, const char * p_cDir, const char * p_cFic );

SBloque * SFicEstContenido ( SFicEstructura * p_ficObj );
int SFicEstAsignar ( SFicEstructura * p_ficObj, SBloque * p_blqElem ); 
int SFicEstGuardarCambios ( SFicEstructura * p_ficObj );

int SFicEstLimpiar ( SFicEstructura * p_ficObj );




#endif