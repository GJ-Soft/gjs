/******************************************************************************/
/*                             SistemaFicheros.h                              */
/*----------------------------------------------------------------------------*/
/* Librería:  Sistema                                                         */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene los prototipos de algunas rutinas de      */
/* de carácter general de operaciones con el sistema de ficheros.             */
/* Mantiene un objeto global privado de clase CSistemaFicheros que puede      */
/* utilizarse para moverse por el árbol de directorios.                       */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_SISTEMAFICHEROS_H
#define _ORG_GJS_C_CC_SISTEMAFICHEROS_H


#include <BaseConfig.h>


int SisEsDirectorioValido ( const char * p_cDirectorio );
int SisEsDirectorioValidoSistema ( const char * p_cDirectorio );
int SisEsSubdirectorioValido ( const char * p_cSubdirectorio );
int SisEsFicheroValido ( const char * p_cFichero );
int SisFicheroTieneExtension ( const char * p_cFichero );

int SisDirectorioNumSubdirectorios ( const char * p_cDirectorio );
char * SisDirectorioSubdirectorio ( const char * p_cDirectorio );
char * SisDirectorioSubdirectorioExt ( const char * p_cDirectorio, int iNivel );
char * SisDirectorioSuperior ( const char * p_cDirectorio );

char * SisFicheroExtension ( const char * p_cFichero );
char * SisFicheroNombre ( const char * p_cFichero );
char * SisComponerFichero ( const char * p_cNombre, const char * p_cExtension );

char * SisRutaDirectorio ( const char * p_cRuta );
char * SisRutaFichero ( const char * p_cRuta );
int SisRutaNumSubdirectorios ( const char * p_cRuta );
char * SisRutaSubdirectorio ( const char * p_cRuta );
char * SisRutaSubdirectorioExt ( const char * p_cRuta, int iNivel );
char * SisComponerRuta ( const char * p_cDirectorio, const char * p_cFichero, int iDirActualPorDef );
char * SisComponerRutaExt ( const char * p_cDirectorio, const char * p_cSubdirectorio, const char * p_cFichero, int iDirActualPorDef );

void SisNormalizarRutaWindows ( char * p_cRuta );
void SisNormalizarRuta ( char * p_cRuta );

int SisEsRutaValida ( const char * p_cRuta );
int SisEsRutaValidaSistema ( const char * p_cRuta );
int SisRutaEsEstiloWindows ( const char * p_cRuta );
char * SisRutaEstiloWindows ( const char * p_cRuta );
char * SisRutaEstiloWindowsExt ( const char * p_cRuta, char cUnidad );
char * SisRutaEstiloUnix ( const char * p_cRuta );
char * SisRutaEstiloCygwin ( const char * p_cRuta );
char * SisRutaEstiloSistema ( const char * p_cRuta );

int SisEsRutaAbsoluta ( const char * p_cRuta );
int SisEsRutaRelativa ( const char * p_cRuta );

char * SisDirectorioActual ();
int SisEstDirectorioActual ( const char * p_cDirectorio );

const char * SisCadenaDirectorioSistema ();
const char * SisCadenaDirectorioFuentes ();

int SisExisteFichero ( const char * p_cRuta );
int SisExisteFicheroExt ( const char * p_cDirectorio, const char * p_cFichero );
int SisExisteDirectorio ( const char * p_cRuta );
int SisExisteDirectorioExt ( const char * p_cDirectorio, const char * p_cSubdirectorio );
//int SisExisteDirectorio ( const char * p_cRuta, int iCrear );
//int SisExisteDirectorio ( const char * p_cDirectorio, const char * p_cSubdirectorio, int iCrear );

int SisCrearFichero ( const char * p_cRuta );
int SisCrearFicheroExt ( const char * p_cDirectorio, const char * p_cFichero );
int SisCrearDirectorio ( const char * p_cDirectorio );
int SisCrearDirectorioExt ( const char * p_cDirectorio, const char * p_cSubdirectorio );

int SisEliminarFichero ( const char * p_cRuta );
int SisEliminarFicheroExt ( const char * p_cDirectorio, const char * p_cFichero );
const char * SisMascaraBusquedaEnDirectorio ( const char * p_cDirectorio );
int SisEliminarDirectorio ( const char * p_cDirectorio );
int SisEliminarDirectorioExt ( const char * p_cDirectorio, const char * p_cSubdirectorio );
int SisVaciarDirectorio ( const char * p_cDirectorio );
int SisVaciarDirectorioExt ( const char * p_cDirectorio, const char * p_cSubdirectorio );
int SisCopiarFichero ( const char * p_cRutaOrig, const char * p_cRutaDest );
int SisCopiarFicheroExt ( const char * p_cDirOrig, const char * p_cFicOrig, const char * p_cDirDest, const char * p_cFicDest, int iEliminar );
int SisMoverFichero ( const char * p_cRutaOrig, const char * p_cRutaDest, int iEliminar );
int SisMoverFicheroExt ( const char * p_cDirOrig, const char * p_cFicOrig, const char * p_cDirDest, const char * p_cFicDest, int iEliminar );

int SisRutaComprimida ( const char * p_cRuta );
int SisRutaEncriptada ( const char * p_cRuta );
int SisRutaOculta ( const char * p_cRuta );
int SisFicheroEsAccesible ( const char * p_cRuta );
int SisRutaDeSoloLectura ( const char * p_cRuta );
int SisRutaDelSistema ( const char * p_cRuta );
int SisFicheroEsTemporal ( const char * p_cRuta );
int SisFicheroAsociadoAAplicacion ( const char * p_cRuta );
int SisFicheroConOptimizacionEspacial ( const char * p_cRuta );

int SisRutaDesactivarModoSoloLectura ( const char * p_cRuta );


int SisEsFicheroC ( const char * p_cRuta );
int SisEsFicheroCodigoC ( const char * p_cRuta );
int SisEsFicheroCabeceraC ( const char * p_cRuta );
int SisEsFicheroXML ( const char * p_cRuta );
int SisEsFicheroHTML ( const char * p_cRuta );
int SisEsFicheroSHP ( const char * p_cRuta );
int SisEsFicheroDBF ( const char * p_cRuta );

char * SisResolverDirectorioRelativo ( const char * p_cRutaBase, const char * p_cRutaRelativa );

char * SisDirectorioRaiz ();
#if ( defined ( WIN ) || defined ( CYGWIN ) )
char * SisDirectorioRaizExt ( char cUnidad );
#endif
char SisSeparadorRutaFicheros ();



#endif

