#ifndef _ORG_GJS_C_CC_SCADENANUMERICA_H
#define _ORG_GJS_C_CC_SCADENANUMERICA_H



#include <SCadenaConv.h>
#include <SPtr.h>






typedef  struct 
{
	SCadenaConv *	p_cadInfo;
	int				iTam;
	int				iAlin;	
	int				iCeros; 

	int				iVal;

} SCadenaNumerica;


SCadenaNumerica * SCadnCrearDef  ();
SCadenaNumerica * SCadnCrear  ( int iTam );
SCadenaNumerica * SCadnCrearValor ( int iTam, int iVal );

void SCadnDestruir ( SCadenaNumerica ** p_p_cadObj );

SCadenaConv * SCadnCadenaConv ( SCadenaNumerica * p_cadObj );

int SCadnObtValor ( SCadenaNumerica * p_cadObj );
void SCadnEstablecerValor ( SCadenaNumerica * p_cadObj, int iVal );
void SCadnEstablecerValorLit ( SCadenaNumerica * p_cadObj, const char * p_cVal );
	
void SCadnAlinearDerecha ( SCadenaNumerica * p_cadObj );
void SCadnAlinearIzquierda ( SCadenaNumerica * p_cadObj );
void SCadnActivarCompletarConCeros ( SCadenaNumerica * p_cadObj );
void SCadnDesactivarCompletarConCeros ( SCadenaNumerica * p_cadObj );

SCadenaNumerica * SCadnDuplicar ( SCadenaNumerica * p_cadObj );

SPtr * SCadnPtr ( SCadenaNumerica * p_cadObj );


#endif


