/******************************************************************************/
/*                                 Errores.h                                  */
/*----------------------------------------------------------------------------*/
/* Librería:  GBase                                                           */
/* Versión:   1.0.0                                                           */
/* Fecha:     28/06/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene los prototipos de las rutinas de          */
/* gestión del subsistema general de manejo de errores.                       */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_ERRORES_H
#define _ORG_GJS_C_CC_ERRORES_H


#include <BaseConfig.h>



#define ERROR_ESTABLECER( iCodigo )		ErrEstablecer ( __FILE__, __LINE__, iCodigo )

#define ERROR_ESTABLECER_FORM( iCodigo, p_cDescripcion, ... ) \
										ErrEstablecerConFormato ( __FILE__, __LINE__, iCodigo, p_cDescripcion, ##__VA_ARGS__ )





/* Lista de errores reconocidos: */
//int InfErrDarDeAlta ( int iCod, const char * p_cDesc, int iGrave );

//int InfErrExiste ( int iCod );
//const char * InfErrDescripcion ( int iCod );
//int InfErrEsGrave ( int iCod );



/* Rutinas de generación y consulta de errores producidos: */
void ErrEstablecer ( const char * p_cModulo, int iLinea, int iCodigo );
//void ErrEstablecer ( int iCodigo, const char * p_cDescripcion );
void ErrEstablecerConFormato ( const char * p_cModulo, int iLinea, int iCodigo, const char * p_cDescripcion, ... );

int ErrHayError ();

int ErrCodigo ();
const char * ErrDescripcion ();
const char * ErrModulo ();
unsigned int ErrLinea ();

void ErrLimpiar ();

const char * ErrMensaje ();
void ErrImprimir ();



#endif





