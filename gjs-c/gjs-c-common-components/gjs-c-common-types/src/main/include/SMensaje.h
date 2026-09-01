#ifndef _ORG_GJS_C_CC_C_COMMON_SMENSAJE_H
#define _ORG_GJS_C_CC_C_COMMON_SMENSAJE_H



#include <SEntidad.h>
#include <SDescripcion.h>



typedef struct
{
	SEntidad *  	p_entInfo;  
	SDescripcion *	p_descTexto;

} SMensaje;


SMensaje * SMsjCrear ( unsigned long ulId, SCadena * p_cadTexto );
SMensaje * SMsjCrearLit ( unsigned long ulId, const char * p_cTexto );
SMensaje * SMsjEncapsular ( SId * p_idMensaje, SDescripcion * p_descTexto );

void SMsjDestruir ( SMensaje ** p_p_msjObj );

int SMsjEsValido ( SMensaje * p_msjObj );

SId * SMsjId ( SMensaje * p_msjObj );
unsigned long SMsjValorId ( SMensaje * p_msjObj );
SDescripcion * SMsjTexto ( SMensaje * p_msjObj );
SCadena * SMsjValorTexto ( SMensaje * p_msjObj );
const char * SMsjValorTextoLit ( SMensaje * p_msjObj );

int SMsjEsIgual ( SMensaje * p_msjObj, SMensaje * p_msjVal );
int SMsjEsMenor ( SMensaje * p_msjObj, SMensaje * p_msjVal );
int SMsjEsMayor ( SMensaje * p_msjObj, SMensaje * p_msjVal );
int SMsjEsMenorIg ( SMensaje * p_msjObj, SMensaje * p_msjVal );
int SMsjEsMayorIg ( SMensaje * p_msjObj, SMensaje * p_msjVal );

int SMsjEsIgualId ( SMensaje * p_msjObj, SId * p_idVal );
int SMsjEsMenorId ( SMensaje * p_msjObj, SId * p_idVal );
int SMsjEsMayorId ( SMensaje * p_msjObj, SId * p_idVal );
int SMsjEsMenorIgId ( SMensaje * p_msjObj, SId * p_idVal );
int SMsjEsMayorIgId ( SMensaje * p_msjObj, SId * p_idVal );

int SMsjEsIgualNum ( SMensaje * p_msjObj, unsigned long ulId );
int SMsjEsMenorNum ( SMensaje * p_msjObj, unsigned long ulId );
int SMsjEsMayorNum ( SMensaje * p_msjObj, unsigned long ulId );
int SMsjEsMenorIgNum ( SMensaje * p_msjObj, unsigned long ulId );
int SMsjEsMayorIgNum ( SMensaje * p_msjObj, unsigned long ulId );

int SMsjComparar ( SMensaje * p_msjObj, SMensaje * p_msjVal );
int SMsjCompararId ( SMensaje* p_msjObj, SId * p_idVal );
int SMsjCompararNum ( SMensaje * p_msjObj, unsigned long ulId );

unsigned int SMsjHash ( SMensaje * p_msjObj );



#endif
