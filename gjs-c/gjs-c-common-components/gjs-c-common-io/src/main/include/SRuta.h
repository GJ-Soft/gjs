
#ifndef _ORG_GJS_C_CC_SRUTA_H
#define _ORG_GJS_C_CC_SRUTA_H





#include <SCadena.h>


typedef struct 
{
	SCadena * p_cadDirectorio;
	SCadena * p_cadFichero;
	
} SRuta;


SRuta * SRutCrearFichero ( SCadena * p_cadDirectorio, SCadena * p_cadFichero );
SRuta * SRutCrearFicheroLit ( const char * p_cDirectorio, const char * p_cFichero );
SRuta * SRutCrearDirectorio ( SCadena * p_cadDirectorio );
SRuta * SRutCrearDirectorioLit ( const char * p_cDirectorio );
SRuta * SRutCrearDirectorioActual ();

void SRutDestruir ( SRuta ** p_p_rutObj );

SCadena * SRutDirectorio ( SRuta * p_rutObj );
const char * SRutDirectorioLit ( SRuta * p_rutObj );
SCadena * SRutFichero ( SRuta * p_rutObj );
const char * SRutFicheroLit ( SRuta * p_rutObj );

int SRutEsValida ( SRuta * p_rutObj );
int SRutEsDirectorioValido ( SRuta * p_rutObj );
int SRutEsFicheroValido ( SRuta * p_rutObj );
int SRutEsDirectorio ( SRuta * p_rutObj );
int SRutEsFichero ( SRuta * p_rutObj );
int SRutEsAbsoluta ( SRuta * p_rutObj );
int SRutEsRelativa ( SRuta * p_rutObj );

int SRutEsEstiloUNIX ( SRuta * p_rutObj );
int SRutEsEstiloDOS ( SRuta * p_rutObj );

int SRutExiste ( SRuta * p_rutObj );
int SRutExisteDirectorio ( SRuta * p_rutObj );
int SRutExisteFichero ( SRuta * p_rutObj );

int SRutTieneExtension ( SRuta * p_rutObj );
int SRutTieneExtensionExt ( SRuta * p_rutObj, const char * p_cExt );

SCadena * SRutRuta ( SRuta * p_rutObj );
char * SRutRutaLit ( SRuta * p_rutObj );
SCadena * SRutRutaAbsoluta ( SRuta * p_rutObj );
char * SRutRutaAbsolutaLit ( SRuta * p_rutObj );
SCadena * SRutSubdirectorio ( SRuta * p_rutObj );
char * SRutSubdirectorioLit ( SRuta * p_rutObj );
SCadena * SRutExtension ( SRuta * p_rutObj );
char * SRutExtensionLit ( SRuta * p_rutObj );
SCadena * SRutFicheroSinExtension ( SRuta * p_rutObj );
char * SRutFicheroSinExtensionLit ( SRuta * p_rutObj );

SCadena * SRutMascaraBusqueda ( SRuta * p_rutObj );
char * SRutMascaraBusquedaLit ( SRuta * p_rutObj );

int SRutEstablecerDirectorio ( SRuta * p_rutObj, SCadena * p_cadDirectorio );
int SRutEstablecerDirectorioLit ( SRuta * p_rutObj, const char * p_cDirectorio );
int SRutEstablecerFichero ( SRuta * p_rutObj, SCadena * p_cadFichero );
int SRutEstablecerFicheroLit ( SRuta * p_rutObj, const char * p_cFichero );
int SRutEstablecer ( SRuta * p_rutObj, SCadena * p_cadDirectorio, SCadena * p_cadFichero );
int SRutEstablecerLit ( SRuta * p_rutObj, const char * p_cDirectorio, const char * p_cFichero );
int SRutEstablecerDirectorioActual ( SRuta * p_rutObj );
int SRutAsignar ( SRuta * p_rutObj, SRuta * p_rutValor );
int SRutEstablecerExtension ( SRuta * p_rutObj, SCadena * p_cadExt );
int SRutEstablecerExtensionLit ( SRuta * p_rutObj, const char * p_cExt );
int SRutAgregarExtension ( SRuta * p_rutObj, SCadena * p_cadExt );
int SRutAgregarExtensionLit ( SRuta * p_rutObj, const char * p_cExt );
int SRutEliminarExtension ( SRuta * p_rutObj );

int SRutMoverA ( SRuta * p_rutObj, SCadena * p_cadSubdirectorio );
int SRutMoverALit ( SRuta * p_rutObj, const char * p_cSubdirectorio );

int SRutEliminar ( SRuta * p_rutObj );

SRuta * SRutDuplicar ( SRuta * p_rutObj );

int SRutEsOculto ( SRuta * p_rutObj );
int SRutEsAccesible ( SRuta * p_rutObj );
int SRutEsDeSoloLectura ( SRuta * p_rutObj );
int SRutEsDelSistema ( SRuta * p_rutObj );
int SRutEsTemporal ( SRuta * p_rutObj );

int SRutDesactivarDeSoloLectura ( SRuta * p_rutObj );



#endif

