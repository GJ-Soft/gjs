/***************************************************************************/
/*                      SistemaFicherosWin32.cpp                           */
/*-------------------------------------------------------------------------*/
/* Libreria: Sistema                                                       */
/*-------------------------------------------------------------------------*/
/* Descripcion:                                                            */
/* Implementacion de los accesos a los atributos de fichero de NTFS.       */
/* Es la UNICA unidad de compilacion del modulo que incluye windows.h.     */
/***************************************************************************/


#include "SistemaFicherosWin32.h"


#if ( defined ( WIN ) || defined ( CYGWIN ) )


#define NO_STRICT
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <cstdlib>
#include <memory>

/* En Cygwin-POSIX las rutas llegan en estilo POSIX y hay que traducirlas. En
   Windows puro y en Cygwin estilo Windows ya vienen como las quiere la API. */
#if ( defined ( CYGWIN ) && defined ( POSIX ) )
#	include <sys/cygwin.h>
#endif


/* La red de seguridad de la que habla la cabecera: si alguno de los valores
   replicados dejara de coincidir con el de windows.h, esto no compila. */
static_assert ( SFW32_ATRIB_INVALIDO == INVALID_FILE_ATTRIBUTES,
                "SFW32_ATRIB_INVALIDO no coincide con INVALID_FILE_ATTRIBUTES" );
static_assert ( SFW32_ATRIB_SOLO_LECTURA == FILE_ATTRIBUTE_READONLY,
                "SFW32_ATRIB_SOLO_LECTURA no coincide con FILE_ATTRIBUTE_READONLY" );
static_assert ( SFW32_ATRIB_OCULTO == FILE_ATTRIBUTE_HIDDEN,
                "SFW32_ATRIB_OCULTO no coincide con FILE_ATTRIBUTE_HIDDEN" );
static_assert ( SFW32_ATRIB_SISTEMA == FILE_ATTRIBUTE_SYSTEM,
                "SFW32_ATRIB_SISTEMA no coincide con FILE_ATTRIBUTE_SYSTEM" );
static_assert ( SFW32_ATRIB_TEMPORAL == FILE_ATTRIBUTE_TEMPORARY,
                "SFW32_ATRIB_TEMPORAL no coincide con FILE_ATTRIBUTE_TEMPORARY" );
static_assert ( SFW32_ATRIB_DISPERSO == FILE_ATTRIBUTE_SPARSE_FILE,
                "SFW32_ATRIB_DISPERSO no coincide con FILE_ATTRIBUTE_SPARSE_FILE" );
static_assert ( SFW32_ATRIB_PUNTO_ANALISIS == FILE_ATTRIBUTE_REPARSE_POINT,
                "SFW32_ATRIB_PUNTO_ANALISIS no coincide con FILE_ATTRIBUTE_REPARSE_POINT" );
static_assert ( SFW32_ATRIB_COMPRIMIDO == FILE_ATTRIBUTE_COMPRESSED,
                "SFW32_ATRIB_COMPRIMIDO no coincide con FILE_ATTRIBUTE_COMPRESSED" );
static_assert ( SFW32_ATRIB_FUERA_DE_LINEA == FILE_ATTRIBUTE_OFFLINE,
                "SFW32_ATRIB_FUERA_DE_LINEA no coincide con FILE_ATTRIBUTE_OFFLINE" );
static_assert ( SFW32_ATRIB_ENCRIPTADO == FILE_ATTRIBUTE_ENCRYPTED,
                "SFW32_ATRIB_ENCRIPTADO no coincide con FILE_ATTRIBUTE_ENCRYPTED" );


/* cygwin_create_path reserva la ruta con malloc y hay que soltarla con free:
   la suelta el unique_ptr, sin un free a la vista. */
typedef std::unique_ptr < char, decltype ( &std::free ) > _SFW32Ruta;

/* Traduce la ruta al estilo que espera la API de Windows. Devuelve la copia,
   o vacio si no hay nada que traducir ( modos en los que la ruta ya viene en
   estilo Windows ) o si la traduccion fallo. En los dos ultimos casos se usa
   la ruta original tal cual, que es lo correcto: si cygwin_create_path no supo
   con ella, la API de Windows tampoco sabra, y devolvera el error por su
   cuenta. */
static _SFW32Ruta _SFW32RutaWindows ( const char * p_cRuta )
{
#if ( defined ( CYGWIN ) && defined ( POSIX ) )
	return ( _SFW32Ruta ( ( char * ) cygwin_create_path ( CCP_POSIX_TO_WIN_A, p_cRuta ), &std::free ) );
#else
	( void ) p_cRuta;
	return ( _SFW32Ruta ( nullptr, &std::free ) );
#endif
}


unsigned int SFW32Atributos ( const char * p_cRuta )
{
	unsigned int	uiRes;

	if ( p_cRuta != NULL )
	{
		_SFW32Ruta rutaWin = _SFW32RutaWindows ( p_cRuta );
		if ( rutaWin )
		{
			uiRes = ( unsigned int ) GetFileAttributesA ( rutaWin.get () );
		}
		else
		{
			uiRes = ( unsigned int ) GetFileAttributesA ( p_cRuta );
		}
	}
	else
	{
		uiRes = SFW32_ATRIB_INVALIDO;
	}
	return ( uiRes );
}


bool SFW32PonerAtributos ( const char * p_cRuta, unsigned int uiAtributos )
{
	bool	bRes;

	if ( p_cRuta != NULL )
	{
		_SFW32Ruta rutaWin = _SFW32RutaWindows ( p_cRuta );
		if ( rutaWin )
		{
			bRes = ( SetFileAttributesA ( rutaWin.get (), ( DWORD ) uiAtributos ) != 0 );
		}
		else
		{
			bRes = ( SetFileAttributesA ( p_cRuta, ( DWORD ) uiAtributos ) != 0 );
		}
	}
	else
	{
		bRes = false;
	}
	return ( bRes );
}


#endif
