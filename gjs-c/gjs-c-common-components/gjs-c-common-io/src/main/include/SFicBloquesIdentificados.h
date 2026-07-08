
#ifndef _ORG_GJS_C_CC_SFICBLOQUESIDENTIFICADOS_H
#define _ORG_GJS_C_CC_SFICBLOQUESIDENTIFICADOS_H







#include <SFicBloques.h>
#include <SRuta.h>


#define FIC_BLOQID_IDNULO				0xFFFFFFFFUL
#define FIC_BLOQID_TAM_ID				sizeof ( unsigned long )





typedef struct
{
	unsigned long		ulMinId;
	unsigned long		ulMaxId;

	SFicBloques *		p_ficObj;

} SFicBloquesIdentificados;


// Crear y CrearExt reinicalizan el fichero. 
// Si ya existe y se quiere conservar hay que usar Asignar o AsignarExt
SFicBloquesIdentificados * SFicBloqIdCrear ( const char * p_cRuta, unsigned long ulTamDatosBloque, unsigned long ulTamDatosCab ); 
SFicBloquesIdentificados * SFicBloqIdAsignar ( const char * p_cRuta ); 
SFicBloquesIdentificados * SFicBloqIdCrearExt ( const char * p_cDir, const char * p_cFic, unsigned long ulTamDatosBloque, unsigned long ulTamDatosCab, int iNumMagico ); 
SFicBloquesIdentificados * SFicBloqIdAsignarExt ( const char * p_cDir, const char * p_cFic, int iNumMagico ); 
SFicBloquesIdentificados * SFicBloqIdCrearRuta ( SRuta * p_rutRuta, unsigned long ulTamDatosBloque, unsigned long ulTamDatosCab ); 

void SFicBloqIdDestruir ( SFicBloquesIdentificados ** p_p_ficObj );
void SFicBloqIdEliminar ( SFicBloquesIdentificados ** p_p_ficObj );

int SFicBloqIdEsValido ( SFicBloquesIdentificados * p_ficObj ); 
const char * SFicBloqIdRuta ( SFicBloquesIdentificados * p_ficObj ); 
char * SFicBloqIdDirectorio ( SFicBloquesIdentificados * p_ficObj ); 
char * SFicBloqIdFichero ( SFicBloquesIdentificados * p_ficObj ); 
int SFicBloqIdEstablecerRuta ( SFicBloquesIdentificados * p_ficObj, const char * p_cRuta );
int SFicBloqIdEstablecerRutaExt ( SFicBloquesIdentificados * p_ficObj, const char * p_cDir, const char * p_cFic );

unsigned long SFicBloqIdNumeroMagico ( SFicBloquesIdentificados * p_ficObj );
int SFicBloqIdEstablecerNumeroMagico ( SFicBloquesIdentificados * p_ficObj, unsigned long ulNumero );

unsigned long SFicBloqIdTamBloque ( SFicBloquesIdentificados * p_ficObj );
unsigned long SFicBloqIdTamDatosBloque ( SFicBloquesIdentificados * p_ficObj );
int SFicBloqIdEstablecerTamDatosBloque ( SFicBloquesIdentificados * p_ficObj, unsigned long ulTam );

unsigned long SFicBloqIdTamDatosCabecera ( SFicBloquesIdentificados * p_ficObj );
int SFicBloqIdEstablecerTamDatosCabecera ( SFicBloquesIdentificados * p_ficObj, unsigned long ulTam );

int SFicBloqIdAbrir ( SFicBloquesIdentificados * p_ficObj );
int SFicBloqIdAbrirExt ( SFicBloquesIdentificados * p_ficObj, int iVaciar );
int SFicBloqIdCerrar ( SFicBloquesIdentificados * p_ficObj );

int SFicBloqIdEstaAbierto ( SFicBloquesIdentificados * p_ficObj );

unsigned long SFicBloqIdMinId ( SFicBloquesIdentificados * p_ficObj );
unsigned long SFicBloqIdMaxId ( SFicBloquesIdentificados * p_ficObj );

unsigned long SFicBloqIdTam ( SFicBloquesIdentificados * p_ficObj );
unsigned long SFicBloqIdTamDatos ( SFicBloquesIdentificados * p_ficObj );
unsigned long SFicBloqIdNumBloques ( SFicBloquesIdentificados * p_ficObj );
int SFicBloqIdEstaVacio ( SFicBloquesIdentificados * p_ficObj );

byte * SFicBloqIdLeerDatosCabecera ( SFicBloquesIdentificados * p_ficObj );
int SFicBloqIdEscribirDatosCabecera ( SFicBloquesIdentificados * p_ficObj, byte * p_byCabecera );

// NOTA: ulBloque hace referencia al orden físco del bloque; ulId hace referencia al identificador del bloque.
unsigned long SFicBloqIdLeerId ( SFicBloquesIdentificados * p_ficObj, unsigned long ulBloque );
int SFicBloqIdExisteId ( SFicBloquesIdentificados * p_ficObj, unsigned long ulId );
unsigned long SFicBloqIdBloqueId ( SFicBloquesIdentificados * p_ficObj, unsigned long ulId );

byte * SFicBloqIdLeer ( SFicBloquesIdentificados * p_ficObj, unsigned long ulId );
int SFicBloqIdLeerExt ( SFicBloquesIdentificados * p_ficObj, unsigned long ulId, byte * p_byContenido );
int SFicBloqIdModificar ( SFicBloquesIdentificados * p_ficObj, unsigned long ulId, byte * p_byContenido );
int SFicBloqIdInsertar ( SFicBloquesIdentificados * p_ficObj, unsigned long ulId, byte * p_byContenido );
int SFicBloqIdSuprimir ( SFicBloquesIdentificados * p_ficObj, unsigned long ulId );

byte * SFicBloqIdLeerBloque ( SFicBloquesIdentificados * p_ficObj, unsigned long ulBloque );
int SFicBloqIdLeerBloqueExt ( SFicBloquesIdentificados * p_ficObj, unsigned long ulBloque, unsigned long * p_ulId, byte * p_byContenido );
int SFicBloqIdEscribirBloque ( SFicBloquesIdentificados * p_ficObj, unsigned long ulBloque, byte * p_byContenido );


#endif

