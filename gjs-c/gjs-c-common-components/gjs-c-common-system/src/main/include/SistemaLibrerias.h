/******************************************************************************/
/*                             SistemaLibrerias.h                             */
/*----------------------------------------------------------------------------*/
/* Librería:  Sistema                                                         */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene los prototipos de algunas rutinas de      */
/* de carácter general de información y gestión de librerías dinámicas.       */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_SISTEMALIBRERIAS_H
#define _ORG_GJS_C_CC_SISTEMALIBRERIAS_H



#include <Funciones.h>
#include <SListaLiterales.h>





int SisLibCargar ( const char * p_cLibreria );
int SisLibEstaCargada ( const char * p_cLibreria );

void * SisLibPrimitiva ( const char * p_cLibreria, const char * p_cPrimitiva );



SListaLiterales * SisLibCargadas ();

char * SisLibRutaFichero ( const char * p_cLibreria );
char * SisLibDirectorioFichero ( const char * p_cLibreria );
char * SisLibFichero ( const char * p_cLibreria );

void * SisLibRutinaPuntoDeEntrada ( const char * p_cLibreria );
void * SisLibDireccionMemoria ( const char * p_cLibreria );
unsigned long SisLibTamMemoria ( const char * p_cLibreria );

char * SisLibCadenaVersion ( const char * p_cLibreria );
int SisLibVersion ( const char * p_cLibreria, int * p_iVersion, int * p_iSubversion, int * p_iRevision, int * p_iBug );


#endif





