/***************************************************************************/
/*                         SGeneradorIdAdap.h                              */
/*-------------------------------------------------------------------------*/
/* Librería: TiposDatos                                                    */
/* Versión:  1.1.0                                                         */
/* Fecha:    24/10/2006                                                    */
/* Autor:    Ginés Jiménez Sánchez                                         */
/*-------------------------------------------------------------------------*/
/* Descripción:                                                            */
/* Fichero de cabecera que contiene la definición de la clase de datos     */
/* SGeneradorIdAdap, destinada a gestionar la producción de identificadores*/
/* únicos dentro de una aplicación.                                        */
/*-------------------------------------------------------------------------*/
/***************************************************************************/

#ifndef _ORG_GJS_C_CC_SGENERADORIDADAP_H
#define _ORG_GJS_C_CC_SGENERADORIDADAP_H








#include <SIdAdap.h>







typedef struct
{
	SIdAdap	* p_idInicial;
	SIdAdap	* p_idFinal;
	SIdAdap	* p_idUltimo;

} SGeneradorIdAdap;




SGeneradorIdAdap * SGenIdAdpCrear ( int iTam, const char * p_cPatron );
SGeneradorIdAdap * SGenIdAdpCrearExt ( int iTam, const char * p_cPatron, const char * p_cInicial, const char * p_cFinal );

void SGenIdAdpDestruir ( SGeneradorIdAdap ** p_p_genidObj );

const char * SGenIdAdpPatron ( SGeneradorIdAdap * p_genidObj );
const char * SGenIdAdpInicial ( SGeneradorIdAdap * p_genidObj );
const char * SGenIdAdpFinal ( SGeneradorIdAdap * p_genidObj );
const char * SGenIdAdpUltimo ( SGeneradorIdAdap * p_genidObj );
const char * SGenIdAdpAsignarSig ( SGeneradorIdAdap * p_genidObj );

int SGenIdAdpEsValido ( SGeneradorIdAdap * p_genidObj );

int SGenIdAdpIniciar ( SGeneradorIdAdap * p_genidObj );
int SGenIdAdpEstablecerUltimo ( SGeneradorIdAdap * p_genidObj, const char * p_cValor );

int SGenIdAdpEsCompatibleValor ( SGeneradorIdAdap * p_genidObj, const char * p_cValor ); 


#endif
