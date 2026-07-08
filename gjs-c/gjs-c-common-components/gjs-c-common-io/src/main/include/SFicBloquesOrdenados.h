

#ifndef _ORG_GJS_C_CC_SFICBLOQUESORDENADOS_H
#define _ORG_GJS_C_CC_SFICBLOQUESORDENADOS_H







#include <SFicBloquesIdentificados.h>
#include <SRuta.h>




typedef struct
{
	unsigned long				ulPrimero;
	unsigned long				ulUltimo;
	unsigned long				ulActual;
	unsigned long				ulPosActual;

	SFicBloquesIdentificados *	p_ficObj;

} SFicBloquesOrdenados;



// Crear y CrearExt reinicalizan el fichero. 
// Si ya existe y se quiere conservar hay que usar Asignar o AsignarExt
SFicBloquesOrdenados * SFicBloqOrdCrear ( const char * p_cRuta, unsigned long ulTamDatosBloque, unsigned long ulTamDatosCab ); 
SFicBloquesOrdenados * SFicBloqOrdAsignar ( const char * p_cRuta ); 
SFicBloquesOrdenados * SFicBloqOrdCrearExt ( const char * p_cDir, const char * p_cFic, unsigned long ulTamDatosBloque, unsigned long ulTamDatosCab, int iNumMagico ); 
SFicBloquesOrdenados * SFicBloqOrdAsignarExt ( const char * p_cDir, const char * p_cFic, int iNumMagico ); 
SFicBloquesOrdenados * SFicBloqOrdCrearRuta ( SRuta * p_rutRuta, unsigned long ulTamDatosBloque, unsigned long ulTamDatosCab ); 

void SFicBloqOrdDestruir ( SFicBloquesOrdenados ** p_p_ficObj );
void SFicBloqOrdEliminar ( SFicBloquesOrdenados ** p_p_ficObj );

int SFicBloqOrdEsValido ( SFicBloquesOrdenados * p_ficObj ); 
const char * SFicBloqOrdRuta ( SFicBloquesOrdenados * p_ficObj ); 
char * SFicBloqOrdDirectorio ( SFicBloquesOrdenados * p_ficObj ); 
char * SFicBloqOrdFichero ( SFicBloquesOrdenados * p_ficObj ); 
int SFicBloqOrdEstablecerRuta ( SFicBloquesOrdenados * p_ficObj, const char * p_cRuta );
int SFicBloqOrdEstablecerRutaExt ( SFicBloquesOrdenados * p_ficObj, const char * p_cDir, const char * p_cFic );

unsigned long SFicBloqOrdNumeroMagico ( SFicBloquesOrdenados * p_ficObj );
int SFicBloqOrdEstablecerNumeroMagico ( SFicBloquesOrdenados * p_ficObj, unsigned long ulNumero );

unsigned long SFicBloqOrdTamBloque ( SFicBloquesOrdenados * p_ficObj );
unsigned long SFicBloqOrdTamDatosBloque ( SFicBloquesOrdenados * p_ficObj );
int SFicBloqOrdEstablecerTamDatosBloque ( SFicBloquesOrdenados * p_ficObj, unsigned long ulTam );

unsigned long SFicBloqOrdTamDatosCabecera ( SFicBloquesOrdenados * p_ficObj );
int SFicBloqOrdEstablecerTamDatosCabecera ( SFicBloquesOrdenados * p_ficObj, unsigned long ulTam );

int SFicBloqOrdAbrir ( SFicBloquesOrdenados * p_ficObj );
int SFicBloqOrdAbrirExt ( SFicBloquesOrdenados * p_ficObj, int iVaciar );
int SFicBloqOrdCerrar ( SFicBloquesOrdenados * p_ficObj );

int SFicBloqOrdEstaAbierto ( SFicBloquesOrdenados * p_ficObj );

unsigned long SFicBloqOrdMinId ( SFicBloquesOrdenados * p_ficObj );
unsigned long SFicBloqOrdMaxId ( SFicBloquesOrdenados * p_ficObj );

unsigned long SFicBloqOrdTam ( SFicBloquesOrdenados * p_ficObj );
unsigned long SFicBloqOrdTamDatos ( SFicBloquesOrdenados * p_ficObj );
unsigned long SFicBloqOrdNumBloques ( SFicBloquesOrdenados * p_ficObj );
int SFicBloqOrdEstaVacio ( SFicBloquesOrdenados * p_ficObj );

byte * SFicBloqOrdLeerDatosCabecera ( SFicBloquesOrdenados * p_ficObj );
int SFicBloqOrdEscribirDatosCabecera ( SFicBloquesOrdenados * p_ficObj, byte * p_byCabecera );

int SFicBloqOrdMoverAPrimero ( SFicBloquesOrdenados * p_ficObj );
int SFicBloqOrdMoverAUltimo ( SFicBloquesOrdenados * p_ficObj );
int SFicBloqOrdMoverASiguiente ( SFicBloquesOrdenados * p_ficObj );
int SFicBloqOrdMoverAAnterior ( SFicBloquesOrdenados * p_ficObj );
int SFicBloqOrdMoverAId ( SFicBloquesOrdenados * p_ficObj, unsigned long ulId );
int SFicBloqOrdEstaEnInicio ( SFicBloquesOrdenados * p_ficObj );
int SFicBloqOrdEstaEnFinal ( SFicBloquesOrdenados * p_ficObj );
int SFicBloqOrdEstaPosicionado ( SFicBloquesOrdenados * p_ficObj );
unsigned long  SFicBloqOrdActual ( SFicBloquesOrdenados * p_ficObj );

unsigned long  SFicBloqOrdLeerId ( SFicBloquesOrdenados * p_ficObj );
byte * SFicBloqOrdLeer ( SFicBloquesOrdenados * p_ficObj );
int SFicBloqOrdLeerExt ( SFicBloquesOrdenados * p_ficObj, byte * p_byContenido );
int SFicBloqOrdModificar ( SFicBloquesOrdenados * p_ficObj, byte * p_byContenido );
int SFicBloqOrdInsertar ( SFicBloquesOrdenados * p_ficObj, unsigned long ulId, byte * p_byContenido, int iDelante );
int SFicBloqOrdInsertarDetras ( SFicBloquesOrdenados * p_ficObj, unsigned long ulId, byte * p_byContenido );
int SFicBloqOrdInsertarDelante ( SFicBloquesOrdenados * p_ficObj, unsigned long ulId, byte * p_byContenido );
int SFicBloqOrdSuprimir ( SFicBloquesOrdenados * p_ficObj );

byte * SFicBloqOrdLeerPorId ( SFicBloquesOrdenados * p_ficObj, unsigned long ulId );
int SFicBloqOrdLeerPorIdExt ( SFicBloquesOrdenados * p_ficObj, unsigned long ulId, byte * p_byContenido );
int SFicBloqOrdModificarPorId ( SFicBloquesOrdenados * p_ficObj, unsigned long ulId, byte * p_byContenido );




#endif

