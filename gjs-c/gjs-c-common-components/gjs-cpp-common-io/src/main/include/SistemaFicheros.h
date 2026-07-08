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

#ifndef _ORG_GJS_C_CC_CPP_SISTEMAFICHEROS_H
#define _ORG_GJS_C_CC_CPP_SISTEMAFICHEROS_H


#include <string>



namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {


bool SisEsDirectorioValido ( const std::string & sDirectorio );
bool SisEsSubdirectorioValido ( const std::string & sSubdirectorio );
bool SisEsFicheroValido ( const std::string & sFichero );
int SisFicheroTieneExtension ( const std::string & sFichero );

int SisDirectorioNumSubdirectorios ( const std::string & sDirectorio );
std::string SisDirectorioSubdirectorio ( const std::string & sDirectorio, int iNivel = -1 );
std::string SisDirectorioSuperior ( const std::string & sDirectorio );

std::string SisFicheroExtension ( const std::string & sFichero );
std::string SisFicheroNombre ( const std::string & sFichero );
std::string SisComponerFichero ( const std::string & sNombre, const std::string & sExtension );

std::string SisRutaDirectorio ( const std::string & sRuta );
std::string SisRutaFichero ( const std::string & sRuta );
int SisRutaNumSubdirectorios ( const std::string & sRuta );
std::string SisRutaSubdirectorio ( const std::string & sRuta, int iNivel = -1 );
std::string SisComponerRuta ( const std::string & sDirectorio, const std::string & sFichero, int iDirActualPorDef = 1 );
std::string SisComponerRutaExt ( const std::string & sDirectorio, const std::string & sSubdirectorio, const std::string & sFichero, int iDirActualPorDef = 1 );

std::string SisNormalizarRuta ( std::string & sRuta );

bool SisEsRutaValida ( const std::string & sRuta );


std::string SisDirectorioActual ();
bool SisEstDirectorioActual ( const std::string & sDirectorio );

std::string SisCadenaDirectorioSistema ();

bool SisExisteFichero ( const std::string & sRuta );
bool SisExisteFicheroExt ( const std::string & sDirectorio, const std::string & sFichero );
bool SisExisteDirectorio ( const std::string & sRuta );
bool SisExisteDirectorioExt ( const std::string & sDirectorio, const std::string & sSubdirectorio );

bool SisCrearFichero ( const std::string & sRuta );
bool SisCrearFicheroExt ( const std::string & sDirectorio, const std::string & sFichero );
bool SisCrearDirectorio ( const std::string & sDirectorio );
bool SisCrearDirectorioExt ( const std::string & sDirectorio, const std::string & sSubdirectorio );

bool SisEliminarFichero ( const std::string & sRuta );
bool SisEliminarFicheroExt ( const std::string & sDirectorio, const std::string & sFichero );
std::string SisMascaraBusquedaEnDirectorio ( const std::string & sDirectorio );
bool SisEliminarDirectorio ( const std::string & sDirectorio );
bool SisEliminarDirectorioExt ( const std::string & sDirectorio, const std::string & sSubdirectorio );
bool SisVaciarDirectorio ( const std::string & sDirectorio );
bool SisVaciarDirectorioExt ( const std::string & sDirectorio, const std::string & sSubdirectorio );
bool SisCopiarFichero ( const std::string & sRutaOrig, const std::string & sRutaDest, bool bEliminar = 1 );
bool SisCopiarFicheroExt ( const std::string & sDirOrig, const std::string & sFicOrig, const std::string & sDirDest, const std::string & sFicDest = NULL, bool bEliminar = 1 );
bool SisMoverFichero ( const std::string & sRutaOrig, const std::string & sRutaDest, bool bEliminar = 1 );
bool SisMoverFicheroExt ( const std::string & sDirOrig, const std::string & sFicOrig, const std::string & sDirDest, const std::string & sFicDest = NULL, bool bEliminar = 1 );

bool SisRutaComprimida ( const std::string & sRuta );
bool SisRutaEncriptada ( const std::string & sRuta );
bool SisRutaOculta ( const std::string & sRuta );
bool SisFicheroEsAccesible ( const std::string & sRuta );
bool SisRutaDeSoloLectura ( const std::string & sRuta );
bool SisRutaDelSistema ( const std::string & sRuta );
bool SisFicheroEsTemporal ( const std::string & sRuta );
bool SisFicheroAsociadoAAplicacion ( const std::string & sRuta );
bool SisFicheroConOptimizacionEspacial ( const std::string & sRuta );

bool SisRutaDesactivarModoSoloLectura ( const std::string & sRuta );


bool SisEsFicheroC ( const std::string & sRuta );
bool SisEsFicheroCodigoC ( const std::string & sRuta );
bool SisEsFicheroCabeceraC ( const std::string & sRuta );
bool SisEsFicheroXML ( const std::string & sRuta );
bool SisEsFicheroHTML ( const std::string & sRuta );
bool SisEsFicheroSHP ( const std::string & sRuta );
bool SisEsFicheroDBF ( const std::string & sRuta );


		
 			}
		}
	}
}

#endif

