#ifndef _ORG_GJS_C_CC_FICHEROSCONFIG_H
#define _ORG_GJS_C_CC_FICHEROSCONFIG_H






#include <Base.h>


#include <Tipos.h>
#include <Texto.h>


/* Ficheros de cabecera de C particulares de cada entorno: */
#if ( defined ( POSIX ) ) 

#	include <sys/param.h>
#	include <sys/dir.h>
#	include <sys/stat.h>
#	include <unistd.h>
	
#else

	/* Paraguas estandar: incluye windef -> winnt -> winbase en el orden correcto
	   y con la deteccion de target bien (DWORD queda a 32 bits de forma
	   consistente, incluso en Cygwin LP64). No incluir esas cabeceras a trozos:
	   el orden piecemeal rompe el dimensionado de DWORD via __LONG32/__LP64__. */
#	include <windows.h>
# if ( defined ( CYGWIN ) )
#	include <unistd.h>
# endif
#	include <io.h>

#endif


#if ( defined ( WIN ) )
	/* En Cygwin/LP64 DWORD es unsigned long de 64 bits, por lo que el
	   (DWORD)-1 de las cabeceras vale 0xFFFFFFFFFFFFFFFF y NO coincide con el
	   0x00000000FFFFFFFF (32 bits a 1 extendidos con ceros) que devuelve
	   GetFileAttributes al fallar. Forzamos un centinela de 32 bits para que
	   la comparacion de existencia funcione tanto en 32 como en 64 bits. */
#	undef  INVALID_FILE_ATTRIBUTES
#	define INVALID_FILE_ATTRIBUTES		((DWORD)0xFFFFFFFFUL)
#endif


/* Desplazamiento de fichero de 64 bits. fseek y ftell trabajan con long,
   que en Windows mide 32 bits y en los tres modos deja fuera la mitad del
   rango de un unsigned long: por eso no se usan en SFicAleatorio. */
#if ( defined ( WIN ) )
#	define FIC_DESP					__int64
#	define FIC_SITUAR( f, d, o )		_fseeki64 ( (f), (d), (o) )
#	define FIC_POSICION( f )			_ftelli64 ( (f) )
#else
#	define FIC_DESP					off_t
#	define FIC_SITUAR( f, d, o )		fseeko ( (f), (d), (o) )
#	define FIC_POSICION( f )			ftello ( (f) )
#endif

#include <FicherosDefs.h>

#include <ExtensionesFicheros.h>
#include <ModosApertura.h>
#include <EstilosFicheroTexto.h>
#include <SistemaFicheros.h>


#define FIC_ESTR_NUM_MAG	0xDADADA00




#define SF_DIR_ACTUAL				"."
#define SF_DIR_PADRE				".."
#define SF_DIR_SEPARADOR			'/'
#define SF_DIR_SEPARADOR_WIN		'\\'
#define SF_UNI_SEPARADOR			':'
#define SF_FIC_SEPARADOR			'.'


#if ( defined ( WIN ) )
#	define SIS_SEPARADOR_PATH		SF_DIR_SEPARADOR_WIN
#else
#	define SIS_SEPARADOR_PATH		SF_DIR_SEPARADOR
#endif


#define SF_PATRON_RUTA				"/(?*/)(?*)"
#define SF_PATRON_RUTA_REL			".(/?*)"		
#define SF_PATRON_RUTA_REL_2		"..(/?*)"		
#define SF_PATRON_RUTA_WIN			"?:\\(?*\\)(?*)"
#define SF_PATRON_RUTA_REL_WIN		".(\\?*)"		
#define SF_PATRON_RUTA_REL_WIN_2	"..(\\?*)"	
/* Directorio de estilo UNIX o DOS, para SRutEsEstiloUNIX / SRutEsEstiloDOS:
   separadores opcionales al principio y despues tramos separados. El motor
   no puede excluir caracteres, asi que el separador del otro estilo y la
   unidad ( "C:" ) se descartan aparte. */
#define SF_PATRON_DIR_UNIX		"(/)?*(/?*)"
#define SF_PATRON_DIR_DOS		"(\\)?*(\\?*)"
#define SF_PATRON_SUBDIRECTORIO		"?*"
#define SF_PATRON_FICHERO			"?*.?*"
#define SF_PATRON_FICHERO_2			"?*"
#define SF_MASCARA_BUSQUEDA			"*.*"

#define SF_MASCARA_FICHERO			"%s.%s"
#define SF_MASCARA_RUTA				"%s/%s"

#define SF_ESTILO_DOS				0
#define SF_ESTILO_UNIX				1



// Errores específicos:
#define ERR_FIC_ESCRIBIR					400


#define ERR_TXT_FIC_ESCRIBIR				"No se ha podido escribir correctamente en el fichero %s."



#endif