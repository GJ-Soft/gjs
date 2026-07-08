#ifndef _ORG_GJS_C_CC_SFICTEXTO_H
#define _ORG_GJS_C_CC_SFICTEXTO_H







#include <EstilosFicheroTexto.h>
#include <SFicSecuencial.h>
#include <SRuta.h>




typedef struct
{
	int					iEstilo;
	SFicSecuencial *	p_ficObj;
} SFicTexto;






SFicTexto * SFicTxtCrear ( const char * p_cRuta  ); 
SFicTexto * SFicTxtCrearExt ( const char * p_cDir, const char * p_cFic, int iEstilo );
SFicTexto * SFicTxtCrearRuta ( SRuta * p_rutRuta  ); 

void SFicTxtDestruir ( SFicTexto ** p_p_ficObj );
void SFicTxtEliminar ( SFicTexto ** p_p_ficObj );

int SFicTxtEsValido ( SFicTexto * p_ficObj ); 
const char * SFicTxtRuta ( SFicTexto * p_ficObj ); 
char * SFicTxtDirectorio ( SFicTexto * p_ficObj ); 
char * SFicTxtFichero ( SFicTexto * p_ficObj ); 
int SFicTxtEstablecerRuta ( SFicTexto * p_ficObj, const char * p_cRuta );
int SFicTxtEstablecerRutaExt ( SFicTexto * p_ficObj, const char * p_cDir, const char * p_cFic );

int SFicTxtEstilo ( SFicTexto * p_ficObj );
int SFicTxtEsEstiloUNIX ( SFicTexto * p_ficObj );
int SFicTxtEsEstiloDOS ( SFicTexto * p_ficObj );

int SFicTxtAbrir ( SFicTexto * p_ficObj, int iModo );
int SFicTxtAbrirExt ( SFicTexto * p_ficObj, int iModo, int iVaciar );
int SFicTxtCerrar ( SFicTexto * p_4icObj );

int SFicTxtEstaAbierto ( SFicTexto * p_ficObj );
int SFicTxtModoApertura ( SFicTexto * p_ficObj );
int SFicTxtEstaAbiertoParaLectura ( SFicTexto * p_ficObj );
int SFicTxtEstaAbiertoParaEscritura ( SFicTexto * p_ficObj );

int SFicTxtEstaEnFinal ( SFicTexto * p_ficObj );

char SFicTxtLeer ( SFicTexto * p_ficObj );
char * SFicTxtLeerLinea ( SFicTexto * p_ficObj );
int SFicTxtEscribirCaracter ( SFicTexto * p_ficObj, char cValor );
int SFicTxtEscribir ( SFicTexto * p_ficObj, const char * p_cCadena );
int SFicTxtEscribirLinea ( SFicTexto * p_ficObj, const char * p_cLinea );
int SFicTxtEscribirSaltoLinea ( SFicTexto * p_ficObj );
int SFicTxtEscribirEspacios ( SFicTexto * p_ficObj, int iNum );
int SFicTxtEscribirTabulador ( SFicTexto * p_ficObj );
int SFicTxtEscribirEntreComparadores ( SFicTexto * p_ficObj, const char * p_cCadena );

#endif

