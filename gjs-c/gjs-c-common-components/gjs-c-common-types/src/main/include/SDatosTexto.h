

#ifndef _ORG_GJS_C_CC_SDATOSTEXTO_H
#define _ORG_GJS_C_CC_SDATOSTEXTO_H


#include <SDatos.h>
#include <SCadena.h>



typedef struct 
{
	SDatos * 	p_datTexto;
	int 		iTamFijo;
	int 		iPos;
	int 		iPrimerLibre;

} SDatosTexto;




SDatosTexto * SDatTxtCrearDef ();
SDatosTexto * SDatTxtCrear ( int iTam, int iTamFijo );
SDatosTexto * SDatTxtEncapsular ( SDatos * p_datTexto, int iTamFijo );

void SDatTxtDestruir ( SDatosTexto ** p_p_datObj );

int SDatTxtEstablecerTam ( SDatosTexto * p_datObj, int iTam );

int SDatTxtEsDeTamFijo ( SDatosTexto * p_datObj );
void SDatTxtActivarTamFijo ( SDatosTexto * p_datObj );
void SDatTxtDesactivarTamFijo ( SDatosTexto * p_datObj );

int SDatTxtEstaVacio ( SDatosTexto * p_datObj );
int SDatTxtEstaLleno ( SDatosTexto * p_datObj );

int SDatTxtEstablecerCaracter ( SDatosTexto * p_datObj, int iPos, byte byVal );
char SDatTxtCaracter ( SDatosTexto * p_datObj, int iPos );

int SDatTxtAsignarContenidoLit ( SDatosTexto * p_datObj, const char * p_cTexto );
int SDatTxtAsignarContenidoEnPosLit ( SDatosTexto * p_datObj, int iPos, const char * p_cTexto );
int SDatTxtAsignarContenido ( SDatosTexto * p_datObj, SCadena * p_cadTexto );
int SDatTxtAsignarContenidoEnPos ( SDatosTexto * p_datObj, int iPos, SCadena * p_cadTexto );
	
SDatos * SDatTxtDatos ( SDatosTexto * p_datObj );

int SDatTxtAsignar ( SDatosTexto * p_datObj, SDatosTexto * p_datValor );
int SDatTxtAsignarDat ( SDatosTexto * p_datObj, SDatos * p_datValor );

SDatosTexto * SDatTxtDuplicar ( SDatosTexto * p_datObj );
SDatos * SDatTxtDuplicarDatos ( SDatosTexto * p_datObj );

int SDatTxtLongitud ( SDatosTexto * p_datObj );
int SDatTxtPosicion ( SDatosTexto * p_datObj );
int SDatTxtPosicionar ( SDatosTexto * p_datObj, int iPos );
void SDatTxtPosicionarEnInicio ( SDatosTexto * p_datObj );
void SDatTxtPosicionarEnFinal ( SDatosTexto * p_datObj );

int SDatTxtEscribirCar ( SDatosTexto * p_datObj, char cVal );
int SDatTxtEscribirLit ( SDatosTexto * p_datObj, const char * p_cTexto );
int SDatTxtEscribir ( SDatosTexto * p_datObj, SCadena * p_cadTexto );
int SDatTxtEscribirLineaLit ( SDatosTexto * p_datObj, const char * p_cTexto ); 
int SDatTxtEscribirLinea ( SDatosTexto * p_datObj, SCadena * p_cadTexto );
int SDatTxtEscribirSaltoLinea ( SDatosTexto * p_datObj );
int SDatTxtEscribirEspacio ( SDatosTexto * p_datObj );
int SDatTxtEscribirEspacios ( SDatosTexto * p_datObj, int iNum );

int SDatTxtTam ( SDatosTexto * p_datObj );

void SDatTxtLimpiar ( SDatosTexto * p_datObj );

void SDatTxtLiberar ( SDatosTexto * p_datObj );

SCadena * SDatTxtContenido ( SDatosTexto * p_datObj );
char * SDatTxtContenidoValor ( SDatosTexto * p_datObj );
char * SDatTxtDuplicarContenidoValor ( SDatosTexto * p_datObj );
int SDatTxtNumLineas ( SDatosTexto * p_datObj );
SCadena * SDatTxtLinea ( SDatosTexto * p_datObj, int iLinea );


void SDatTxtImprimir ( SDatosTexto * p_datObj );




#endif

