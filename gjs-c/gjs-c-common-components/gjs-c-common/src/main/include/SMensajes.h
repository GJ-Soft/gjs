
#ifndef _ORG_GJS_C_CC_SMENSAJES_H
#define _ORG_GJS_C_CC_SMENSAJES_H



// TODO: Cambiar a lista ordenada
#include <SListaPtr.h>
#include <SCadena.h>


typedef struct
{
	SListaPtr * p_lisMensajes;
	
} SMensajes;



SMensajes * SMsjsCrear ();

void SMsjsDestruir ( SMensajes ** p_p_msjObj );

int SMsjsInsertar ( SMensajes * p_msjObj, unsigned long uiCodigo, SCadena * p_cadTexto );
int SMsjsInsertarLit ( SMensajes * p_msjObj, unsigned long uiCodigo, const char * p_cTexto );

int SMsjsExisteCodigo ( SMensajes * p_msjObj, unsigned long uiCodigo );
int SMsjsNumMensajes ( SMensajes * p_msjObj );
SCadena * SMsjsTexto ( SMensajes * p_msjObj, unsigned long uiCodigo );

void SMsjsLimpiar ( SMensajes * p_msjObj );
int SMsjsCargar ( SMensajes * p_msjObj, const char * p_cFichero );




#endif

