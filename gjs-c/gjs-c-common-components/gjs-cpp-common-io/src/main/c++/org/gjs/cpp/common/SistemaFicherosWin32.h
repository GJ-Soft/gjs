/***************************************************************************/
/*                      SistemaFicherosWin32.h                             */
/*-------------------------------------------------------------------------*/
/* Libreria: Sistema                                                       */
/*-------------------------------------------------------------------------*/
/* Descripcion:                                                            */
/* Cabecera PRIVADA del modulo. Da acceso a los atributos de fichero de    */
/* NTFS ( oculto, solo lectura, comprimido... ) a traves de la API de      */
/* Windows, tanto desde un binario nativo como desde uno de Cygwin.        */
/*                                                                         */
/* Los atributos son una propiedad del SISTEMA DE FICHEROS, no del sistema */
/* operativo: desde Cygwin se consultan igual de bien que desde Windows,   */
/* y lo unico que cambia es que la ruta POSIX hay que traducirla antes.    */
/*                                                                         */
/* Por que esto vive en su propia unidad de compilacion y no dentro de     */
/* SistemaFicheros.cpp: para dejar windows.h fuera de un fichero que usa   */
/* <filesystem>, <algorithm> y compania. Es el mismo reparto que en el     */
/* stack de C, donde ademas es obligatorio porque alli BaseConfig.h define */
/* BYTE, WORD y DWORD como macros y rompen los typedef de windows.h.       */
/* En la frontera solo se usan tipos del lenguaje.                         */
/***************************************************************************/


#ifndef _ORG_GJS_CPP_COMMON_SISTEMA_FICHEROS_WIN32_H
#define _ORG_GJS_CPP_COMMON_SISTEMA_FICHEROS_WIN32_H


#include <Precompilacion.h>


#if ( defined ( WIN ) || defined ( CYGWIN ) )


/* Valores de los FILE_ATTRIBUTE_* de windows.h. Se replican aqui para no        */
/* tener que incluir windows.h desde SistemaFicheros.cpp. No es un riesgo:       */
/* SistemaFicherosWin32.cpp comprueba uno por uno, EN TIEMPO DE COMPILACION, que */
/* coinciden con los de verdad; si algun dia dejaran de coincidir, no compila.   */
#define SFW32_ATRIB_INVALIDO			0xFFFFFFFFU

#define SFW32_ATRIB_SOLO_LECTURA		0x00000001U
#define SFW32_ATRIB_OCULTO				0x00000002U
#define SFW32_ATRIB_SISTEMA				0x00000004U
#define SFW32_ATRIB_TEMPORAL			0x00000100U
#define SFW32_ATRIB_DISPERSO			0x00000200U
#define SFW32_ATRIB_PUNTO_ANALISIS		0x00000400U
#define SFW32_ATRIB_COMPRIMIDO			0x00000800U
#define SFW32_ATRIB_FUERA_DE_LINEA		0x00001000U
#define SFW32_ATRIB_ENCRIPTADO			0x00004000U


/* Devuelve los atributos de la ruta, o SFW32_ATRIB_INVALIDO si no se pudieron
   obtener. La ruta se espera en el estilo del modo de compilacion: POSIX en
   Cygwin-POSIX, Windows en los otros dos. */
unsigned int SFW32Atributos ( const char * p_cRuta );

/* Fija los atributos de la ruta. Devuelve true si lo consiguio. */
bool SFW32PonerAtributos ( const char * p_cRuta, unsigned int uiAtributos );


#endif


#endif
