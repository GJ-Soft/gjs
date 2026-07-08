
#ifndef _ORG_GJS_C_CC_SFICBLOQUES_H
#define _ORG_GJS_C_CC_SFICBLOQUES_H







#include <SFicEncabezado.h>
#include <SRuta.h>





typedef struct
{
	unsigned long		ulTamBloque;
	unsigned long		ulNumBloques;

	SFicEncabezado *	p_ficObj;
} SFicBloques;


// Crear y CrearExt reinicalizan el fichero. 
// Si ya existe y se quiere conservar hay que usar Asignar o AsignarExt
SFicBloques * SFicBloqCrear ( const char * p_cRuta, unsigned long ulTamBloque, unsigned long ulTamDatosCab ); 
SFicBloques * SFicBloqAsignar ( const char * p_cRuta ); 
SFicBloques * SFicBloqCrearExt ( const char * p_cDir, const char * p_cFic, unsigned long ulTamBloque, unsigned long ulTamDatosCab, int iNumMagico ); 
SFicBloques * SFicBloqAsignarExt ( const char * p_cDir, const char * p_cFic, int iNumMagico ); 
SFicBloques * SFicBloqCrearRuta ( SRuta * p_rutRuta, unsigned long ulTamBloque, unsigned long ulTamDatosCab ); 

void SFicBloqDestruir ( SFicBloques ** p_p_ficObj );
void SFicBloqEliminar ( SFicBloques ** p_p_ficObj );

int SFicBloqEsValido ( SFicBloques * p_ficObj ); 
const char * SFicBloqRuta ( SFicBloques * p_ficObj ); 
char * SFicBloqDirectorio ( SFicBloques * p_ficObj ); 
char * SFicBloqFichero ( SFicBloques * p_ficObj ); 
int SFicBloqEstablecerRuta ( SFicBloques * p_ficObj, const char * p_cRuta );
int SFicBloqEstablecerRutaExt ( SFicBloques * p_ficObj, const char * p_cDir, const char * p_cFic );

int SFicBloqTieneNumeroMagico ( SFicBloques * p_ficObj ); 
unsigned long SFicBloqNumeroMagico ( SFicBloques * p_ficObj );
int SFicBloqEstablecerNumeroMagico ( SFicBloques * p_ficObj, unsigned long ulNumero );

unsigned long SFicBloqTamBloque ( SFicBloques * p_ficObj );
int SFicBloqEstablecerTamBloque ( SFicBloques * p_ficObj, unsigned long ulTam );

unsigned long SFicBloqTamDatosCabecera ( SFicBloques * p_ficObj );
int SFicBloqEstablecerTamDatosCabecera ( SFicBloques * p_ficObj, unsigned long ulTam );

int SFicBloqAbrir ( SFicBloques * p_ficObj );
int SFicBloqAbrirExt ( SFicBloques * p_ficObj, int iVaciar );
int SFicBloqCerrar ( SFicBloques * p_ficObj );

int SFicBloqEstaAbierto ( SFicBloques * p_ficObj );

unsigned long SFicBloqTam ( SFicBloques * p_ficObj );
unsigned long SFicBloqTamDatos ( SFicBloques * p_ficObj );
unsigned long SFicBloqNumBloques ( SFicBloques * p_ficObj );
int SFicBloqEstaVacio ( SFicBloques * p_ficObj );

byte * SFicBloqLeerDatosCabecera ( SFicBloques * p_ficObj );
int SFicBloqLeerDatosCabeceraExt ( SFicBloques * p_ficObj, byte * p_byContenido );
int SFicBloqEscribirDatosCabecera ( SFicBloques * p_ficObj, byte * p_byContenido );

byte * SFicBloqLeer ( SFicBloques * p_ficObj, unsigned long ulBloque );
int SFicBloqLeerExt ( SFicBloques * p_ficObj, unsigned long ulBloque, byte * p_byContenido );
int SFicBloqEscribir ( SFicBloques * p_ficObj, unsigned long ulBloque, byte * p_byContenido );
int SFicBloqLimpiar ( SFicBloques * p_ficObj, unsigned long ulBloque );

int SFicBloqLeerParte ( SFicBloques * p_ficObj, unsigned long ulBloque, unsigned long ulDespl, unsigned long ulTam, byte * p_byContenido );
int SFicBloqEscribirParte ( SFicBloques * p_ficObj, unsigned long ulBloque, unsigned long ulDespl, unsigned long ulTam, byte * p_byContenido );


#endif

