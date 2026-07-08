#ifndef _ORG_GJS_C_CC_SDIRECTORIO_H
#define _ORG_GJS_C_CC_SDIRECTORIO_H





#include <SCadena.h>
#include <SRuta.h>
#include <SListaPtr.h>
#include <SEntradaDirectorio.h>


typedef struct  
{
	SListaPtr *	p_lisEntradas;
	SRuta *		p_rutObj;
	SCadena * 	p_cadNombre;
	
} SDirectorio;



SDirectorio * SDirCrear ( SCadena * p_cadDirectorio );
SDirectorio * SDirCrearLit ( const char * p_cDirectorio );
SDirectorio * SDirCrearRuta ( SRuta * p_rutDirectorio );
SDirectorio * SDirCrearExt ( SCadena * p_cadDirectorio, SCadena * p_cadSubdirectorio );
SDirectorio * SDirCrearLitExt ( const char * p_cDirectorio, const char * p_cSubdirectorio );
SDirectorio * SDirCrearRutaExt ( SRuta * p_rutDirectorio, const char * p_cSubdirectorio );
SDirectorio * SDirCrearRaiz ();
SDirectorio * SDirCrearActual ();

void SDirDestruir ( SDirectorio ** p_p_dirObj );

SRuta * SDirRuta ( SDirectorio * p_dirObj );
SCadena * SDirNombre ( SDirectorio * p_dirObj );
const char * SDirEntradaLit ( SDirectorio * p_dirObj );
int SDirEsValido ( SDirectorio * p_dirObj );

int SDirCambiar ( SDirectorio * p_dirObj, SCadena * p_cadDirectorio );
int SDirCambiarLit ( SDirectorio * p_dirObj, const char * p_cDirectorio );
int SDirRefrescar ( SDirectorio * p_dirObj );

int SDirNumEntradas ( SDirectorio * p_dirObj );
SEntradaDirectorio * SDirEntrada ( SDirectorio * p_dirObj, int iEntrada );
SDirectorio * SDirAbrirSubdirectorio ( SDirectorio * p_dirObj, int iEntrada );
SDirectorio * SDirAbrirSubdirectorioExt ( SDirectorio * p_dirObj, SEntradaDirectorio * p_entdirEntrada );

int SDirCrearSubdirectorio ( SDirectorio * p_dirObj, SCadena * p_cadSubdirectorio );
int SDirCrearSubdirectorioLit ( SDirectorio * p_dirObj, const char * p_cSubdirectorio );

void SDirLiberarEntradas ( SDirectorio * p_dirObj );


/*
int SDirCopiarFicheroA ( SDirectorio * p_dirObj, const char * p_cDirDestino );
int SDirCopiarFicheroA ( SDirectorio * p_dirObj, SCadena * p_cadDirDestino );
int SDirCopiarFicheroA ( SDirectorio * p_dirObj, SDirectorio * p_dirDestino );
int SDirCopiarFicheroA ( SDirectorio * p_dirObj, const char * p_cDirDestino, const char * p_cFichero );
int SDirCopiarFicheroA ( SDirectorio * p_dirObj, SCadena * p_cadDirDestino, SCadena * p_cadFichero );
int SDirCopiarFicheroA ( SDirectorio * p_dirObj, SDirectorio * p_dirDestino, const char * p_cFichero );
int SDirCopiarFicheroA ( SDirectorio * p_dirObj, SDirectorio * p_dirDestino,  SCadena * p_cadFichero );
int SDirCopiarFicheroDesde ( SDirectorio * p_dirObj, const char * p_cDirOrigen, const char * p_cFichero );
int SDirCopiarFicheroDesde ( SDirectorio * p_dirObj, SCadena * p_cadDirOrigen, SCadena * p_cadFichero );
int SDirCopiarFicheroDesde ( SDirectorio * p_dirObj, SDirectorio * p_dirOrigen, const char * p_cFichero );
int SDirCopiarFicheroDesde ( SDirectorio * p_dirObj, SDirectorio * p_dirOrigen, SCadena * p_cadFichero );
int SDirMoverFicheroA ( SDirectorio * p_dirObj, const char * p_cDirDestino );
int SDirMoverFicheroA ( SDirectorio * p_dirObj, SCadena * p_cadDirDestino );
int SDirMoverFicheroA ( SDirectorio * p_dirObj, SDirectorio * p_dirDestino );
int SDirMoverFicheroA ( SDirectorio * p_dirObj, const char * p_cDirDestino, const char * p_cFichero );
int SDirMoverFicheroA ( SDirectorio * p_dirObj, SCadena * p_cadDirDestino, SCadena * p_cadFichero );
int SDirMoverFicheroA ( SDirectorio * p_dirObj, SDirectorio * p_dirDestino, const char * p_cFichero );
int SDirMoverFicheroA ( SDirectorio * p_dirObj, SDirectorio * p_dirDestino,  SCadena * p_cadFichero );
int SDirMoverFicheroDesde ( SDirectorio * p_dirObj, const char * p_cDirOrigen, const char * p_cFichero );
int SDirMoverFicheroDesde ( SDirectorio * p_dirObj, SCadena * p_cadDirOrigen, SCadena * p_cadFichero );
int SDirMoverFicheroDesde ( SDirectorio * p_dirObj, SDirectorio * p_dirOrigen, const char * p_cFichero );
int SDirMoverFicheroDesde ( SDirectorio * p_dirObj, SDirectorio * p_dirOrigen, SCadena * p_cadFichero );

*/


#endif



