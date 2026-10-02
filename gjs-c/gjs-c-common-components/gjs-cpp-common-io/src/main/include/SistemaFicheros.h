/******************************************************************************/
/*                             SistemaFicheros.h                              */
/*----------------------------------------------------------------------------*/
/* Librer�a:  Sistema                                                         */
/* Versi�n:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Gin�s Jim�nez S�nchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripci�n:                                                               */
/* Fichero de cabecera que contiene los prototipos de algunas rutinas de      */
/* de car�cter general de operaciones con el sistema de ficheros.             */
/* Mantiene un objeto global privado de clase CSistemaFicheros que puede      */
/* utilizarse para moverse por el �rbol de directorios.                       */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_CPP_SISTEMAFICHEROS_H
#define _ORG_GJS_C_CC_CPP_SISTEMAFICHEROS_H



#include <Precompilacion.h>

#include <string>



namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {


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

std::string SisNormalizarRuta ( const std::string & sRuta );
std::string SisNormalizarRutaWindows ( const std::string & sRuta );

bool SisEsRutaValida ( const std::string & sRuta );
bool SisEsRutaValidaSistema ( const std::string & sRuta );
bool SisRutaEsEstiloWindows ( const std::string & sRuta );
std::string SisRutaEstiloWindows ( const std::string & sRuta );
std::string SisRutaEstiloWindowsExt ( const std::string & sRuta, char cUnidad );
std::string SisRutaEstiloUnix ( const std::string & sRuta );
std::string SisRutaEstiloCygwin ( const std::string & sRuta );
std::string SisRutaEstiloSistema ( const std::string & sRuta );

bool SisEsRutaAbsoluta ( const std::string & sRuta );
bool SisEsRutaRelativa ( const std::string & sRuta );


std::string SisDirectorioActual ();
bool SisEstDirectorioActual ( const std::string & sDirectorio );

/* Solo en Windows: el "directorio del sistema" es C:\Windows\System32, un
   concepto que no tiene equivalente en POSIX. Su gemela del stack C,
   SisDirectorioSistema, ya estaba declarada solo bajo WIN. */
#if ( defined ( WIN ) )
std::string SisCadenaDirectorioSistema ();
#endif
std::string SisCadenaDirectorioFuentes ();

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
bool SisCopiarFichero ( const std::string & sRutaOrig, const std::string & sRutaDest, bool bEliminar = true );
bool SisCopiarFicheroExt ( const std::string & sDirOrig, const std::string & sFicOrig, const std::string & sDirDest, const std::string & sFicDest = "", bool bEliminar = true );
bool SisMoverFichero ( const std::string & sRutaOrig, const std::string & sRutaDest, bool bEliminar = true );
bool SisMoverFicheroExt ( const std::string & sDirOrig, const std::string & sFicOrig, const std::string & sDirDest, const std::string & sFicDest = "", bool bEliminar = true );

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

std::string SisResolverDirectorioRelativo ( const std::string & sRutaBase, const std::string & sRutaRelativa );

std::string SisDirectorioRaiz ();
#if ( defined ( WIN ) || defined ( CYGWIN ) )
std::string SisDirectorioRaizExt ( char cUnidad );
#endif
char SisSeparadorRutaFicheros ();


			}
		}
	}
}

#endif
