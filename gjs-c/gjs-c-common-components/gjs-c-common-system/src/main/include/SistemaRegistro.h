/******************************************************************************/
/*                             SistemaRegistro.h                              */
/*----------------------------------------------------------------------------*/
/* Librería:  Sistema                                                         */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene la definición de algunas rutinas de       */
/* carácter general de manejo del registro de Windows.                        */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_SISTEMAREGISTRO_H
#define _ORG_GJS_C_CC_SISTEMAREGISTRO_H



#include <Precompilacion.h>
/* HKEY y los demas tipos del registro salen de windows.h, que entra por
   BaseConfig.h. Precompilacion.h por si solo no lo trae. */
#include <BaseConfig.h>


#if ( defined ( WIN ) )




int SisRegExisteClave ( const char * p_cClave );
int SisRegCrearClave ( const char * p_cClave );
int SisRegEliminarClave ( const char * p_cClave );
int SisRegExisteClaveExt ( const char * p_cClave, int iClavePrinc );
int SisRegCrearClaveExt ( const char * p_cClave, int iClavePrinc );
int SisRegEliminarClaveExt ( const char * p_cClave, int iClavePrinc );

const char * SisRegObtValorCadena ( const char * p_cClave, const char * p_cValor );
unsigned long SisRegObtValorNumerico ( const char * p_cClave, const char * p_cValor );
const char * SisRegObtValorCadenaExt ( const char * p_cClave, const char * p_cValor, int iClavePrinc );
unsigned long SisRegObtValorNumericoExt ( const char * p_cClave, const char * p_cValor, int iClavePrinc );

int SisRegEstValorCadena ( const char * p_cClave, const char * p_cValor, const char * p_cDato );
int SisRegEstValorNumerico ( const char * p_cClave, const char * p_cValor, unsigned long ulDato );
int SisRegCrearValorCadena ( const char * p_cClave, const char * p_cValor, const char * p_cDato );
int SisRegCrearValorNumerico ( const char * p_cClave, const char * p_cValor, unsigned long ulDato );
int SisRegEstValorCadenaExt ( const char * p_cClave, const char * p_cValor, const char * p_cDato, int iClavePrinc );
int SisRegEstValorNumericoExt ( const char * p_cClave, const char * p_cValor, unsigned long ulDato, int iClavePrinc );
int SisRegCrearValorCadenaExt ( const char * p_cClave, const char * p_cValor, const char * p_cDato, int iClavePrinc );
int SisRegCrearValorNumericoExt ( const char * p_cClave, const char * p_cValor, unsigned long ulDato, int iClavePrinc );


/* Rutinas gestion del registro: */
HKEY SisRegClaveInfoClases ();
HKEY SisRegClaveInfoConfigActual ();
HKEY SisRegClaveInfoUsuarioActual ();
HKEY SisRegClaveInfoLocal ();
HKEY SisRegClaveInfoUsuarios ();
//HKEY SisRegAbrirUsuarioActual ( int iSoloLectura );
//HKEY SisRegAbrirClasesUsuarioActual ( int iSoloLectura );
HKEY SisRegCrear ( HKEY hkeyPadre, const char * p_cClave );
/* SisRegAbrir abre con KEY_READ. Antes pedia KEY_ALL_ACCESS sin opcion, y eso
   sobre HKEY_LOCAL_MACHINE exige administrador: un proceso normal no podia ni
   leer. Quien necesite escribir usa la Ext y pasa el acceso que quiera
   ( KEY_WRITE, KEY_ALL_ACCESS... ). En C no hay argumentos por defecto, de ahi
   el par, que es el mismo idioma que el resto del modulo. */
HKEY SisRegAbrir ( HKEY hkeyPadre, const char * p_cClave );
HKEY SisRegAbrirExt ( HKEY hkeyPadre, const char * p_cClave, REGSAM samAcceso );
void SisRegCerrar ( HKEY hkeyClave );
int SisRegEsClaveValida ( HKEY hkeyClave );
long SisRegNumSubclaves ( HKEY hkeyClave );
int SisRegTieneSubclaves ( HKEY hkeyClave );
long SisRegNumValores ( HKEY hkeyClave );
int SisRegTieneValores ( HKEY hkeyClave );
int SisRegExisteSubclave ( HKEY hkeyClave, const char * p_cSubclave );
int SisRegExisteValor (  HKEY hkeyClave, const char * p_cNomValor );
int SisRegEliminarSubclave (  HKEY hkeyClave, const char * p_cSubclave );
int SisRegEliminarTodasSubclaves ( HKEY hkeyClave );
int SisRegConsultarClave (  HKEY hkeyClave, const char * p_cValor, unsigned int uiMaxTamValor );
int SisRegConsultarClaveEnt (  HKEY hkeyClave, DWORD * pdwValor );
int SisRegEstablecerClave (  HKEY hkeyClave, const char * p_cValor );
int SisRegEstablecerClaveEnt (  HKEY hkeyClave, DWORD dwValor );
int SisRegConsultarValor (  HKEY hkeyClave, const char * p_cNomValor, const char * p_cValor, unsigned int uiMaxTamValor );
int SisRegConsultarValorEnt (  HKEY hkeyClave, const char * p_cNomValor, DWORD * pdwValor );
int SisRegEstablecerValor (  HKEY hkeyClave, const char * p_cNomValor, const char * p_cValor );
int SisRegEstablecerValorEnt (  HKEY hkeyClave, const char * p_cNomValor, DWORD dwValor );
int SisRegEliminarValor (  HKEY hkeyClave, const char * p_cNomValor );
int SisRegEliminarTodosValores (  HKEY hkeyClave );
int SisRegEliminarContenido (  HKEY hkeyClave );
int SisRegImportarFichero ( HKEY hkeyPadre, const char * p_cClave, const char * p_cFichero );
int SisRegExportarFichero ( HKEY hkeyClave, const char * p_cFichero );



/* Rutinas de alto nivel para módulos DLL: */
int SisRegistrarModulo ( const GUID guidModulo, const char * p_cFicModulo, const char * p_cVersion );
int SisRegistrarGUID ( const GUID guidCodigo, const char * p_cNombre, const char * p_cDescripcion,
					 		 const GUID guidModulo, const char * p_cFicModulo, const char * p_cVersion );

void SisRegDesregistrarModulo ( const GUID guidModulo, const char * p_cVersion );
/* p_cFicModulo entra aqui, y en SisRegEstaRegistradoGUID, porque el ProgId se
   arma con el: SisRegistrarGUID lo escribe como ficheroModulo.nombre. Sin ese
   dato estas dos lo reconstruian como nombre.nombre y no encontraban nada de lo
   que habia registrado la otra. */
void SisRegDesregistrarGUID ( const GUID guidCodigo, const char * p_cNombre,
							  const char * p_cFicModulo );


int SisRegEstaRegistradoModulo ( const GUID guidModulo );
/* La cabecera declaraba esta con un solo parametro y la implementacion se
   llamaba EstaRegistradoGUID, sin el prefijo SisReg: ni casaban ni habia forma
   de llegar a ella desde fuera. */
int SisRegEstaRegistradoGUID ( const GUID guidCodigo, const char * p_cNombre,
							   const char * p_cFicModulo );




#endif

#endif





