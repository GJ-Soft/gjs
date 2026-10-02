/***************************************************************************/
/*                      SistemaFicherosWin32.c                             */
/*-------------------------------------------------------------------------*/
/* Libreria: Sistema                                                       */
/*-------------------------------------------------------------------------*/
/* Descripcion:                                                            */
/* Implementacion de los accesos a los atributos de fichero de NTFS.       */
/* Es la UNICA unidad de compilacion del modulo que incluye windows.h, y   */
/* a proposito no incluye BaseConfig.h: el motivo esta en la cabecera.     */
/***************************************************************************/


#include "SistemaFicherosWin32.h"


#if ( defined ( WIN ) || defined ( CYGWIN ) )


#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <stdlib.h>

/* En Cygwin-POSIX las rutas llegan en estilo POSIX y hay que traducirlas. En
   Windows puro y en Cygwin estilo Windows ya vienen como las quiere la API. */
#if ( defined ( CYGWIN ) && defined ( POSIX ) )
#	include <sys/cygwin.h>
#endif


/* La red de seguridad de la que habla la cabecera: si alguno de los valores
   replicados dejara de coincidir con el de windows.h, esto no compila. */
_Static_assert ( SFW32_ATRIB_INVALIDO == INVALID_FILE_ATTRIBUTES,
                 "SFW32_ATRIB_INVALIDO no coincide con INVALID_FILE_ATTRIBUTES" );
_Static_assert ( SFW32_ATRIB_SOLO_LECTURA == FILE_ATTRIBUTE_READONLY,
                 "SFW32_ATRIB_SOLO_LECTURA no coincide con FILE_ATTRIBUTE_READONLY" );
_Static_assert ( SFW32_ATRIB_OCULTO == FILE_ATTRIBUTE_HIDDEN,
                 "SFW32_ATRIB_OCULTO no coincide con FILE_ATTRIBUTE_HIDDEN" );
_Static_assert ( SFW32_ATRIB_SISTEMA == FILE_ATTRIBUTE_SYSTEM,
                 "SFW32_ATRIB_SISTEMA no coincide con FILE_ATTRIBUTE_SYSTEM" );
_Static_assert ( SFW32_ATRIB_TEMPORAL == FILE_ATTRIBUTE_TEMPORARY,
                 "SFW32_ATRIB_TEMPORAL no coincide con FILE_ATTRIBUTE_TEMPORARY" );
_Static_assert ( SFW32_ATRIB_DISPERSO == FILE_ATTRIBUTE_SPARSE_FILE,
                 "SFW32_ATRIB_DISPERSO no coincide con FILE_ATTRIBUTE_SPARSE_FILE" );
_Static_assert ( SFW32_ATRIB_PUNTO_ANALISIS == FILE_ATTRIBUTE_REPARSE_POINT,
                 "SFW32_ATRIB_PUNTO_ANALISIS no coincide con FILE_ATTRIBUTE_REPARSE_POINT" );
_Static_assert ( SFW32_ATRIB_COMPRIMIDO == FILE_ATTRIBUTE_COMPRESSED,
                 "SFW32_ATRIB_COMPRIMIDO no coincide con FILE_ATTRIBUTE_COMPRESSED" );
_Static_assert ( SFW32_ATRIB_FUERA_DE_LINEA == FILE_ATTRIBUTE_OFFLINE,
                 "SFW32_ATRIB_FUERA_DE_LINEA no coincide con FILE_ATTRIBUTE_OFFLINE" );
_Static_assert ( SFW32_ATRIB_ENCRIPTADO == FILE_ATTRIBUTE_ENCRYPTED,
                 "SFW32_ATRIB_ENCRIPTADO no coincide con FILE_ATTRIBUTE_ENCRYPTED" );


/* Traduce la ruta al estilo que espera la API de Windows. Devuelve una copia
   que hay que liberar con free, o NULL si no hay nada que traducir ( modos en
   los que la ruta ya viene en estilo Windows ) o si la traduccion fallo. En
   los dos ultimos casos se usa la ruta original tal cual, que es lo correcto:
   si cygwin_create_path no supo con ella, la API de Windows tampoco sabra, y
   devolvera el error por su cuenta. */
static char * _SFW32RutaWindows ( const char * p_cRuta )
{
	char *	p_cRes;

#if ( defined ( CYGWIN ) && defined ( POSIX ) )
	p_cRes = ( char * ) cygwin_create_path ( CCP_POSIX_TO_WIN_A, p_cRuta );
#else
	( void ) p_cRuta;
	p_cRes = NULL;
#endif
	return ( p_cRes );
}


unsigned int SFW32Atributos ( const char * p_cRuta )
{
	unsigned int	uiRes;
	char *			p_cRutaWin;

	if ( p_cRuta != NULL )
	{
		p_cRutaWin = _SFW32RutaWindows ( p_cRuta );
		if ( p_cRutaWin != NULL )
		{
			uiRes = ( unsigned int ) GetFileAttributesA ( p_cRutaWin );
			free ( p_cRutaWin );
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


int SFW32PonerAtributos ( const char * p_cRuta, unsigned int uiAtributos )
{
	int		iRes;
	char *	p_cRutaWin;

	if ( p_cRuta != NULL )
	{
		p_cRutaWin = _SFW32RutaWindows ( p_cRuta );
		if ( p_cRutaWin != NULL )
		{
			if ( SetFileAttributesA ( p_cRutaWin, ( DWORD ) uiAtributos ) != 0 )
			{
				iRes = 1;
			}
			else
			{
				iRes = 0;
			}
			free ( p_cRutaWin );
		}
		else
		{
			if ( SetFileAttributesA ( p_cRuta, ( DWORD ) uiAtributos ) != 0 )
			{
				iRes = 1;
			}
			else
			{
				iRes = 0;
			}
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


#else


/* Fuera de Windows y de Cygwin esta unidad no aporta nada, pero el C estandar
   no admite una unidad de compilacion vacia. */
typedef int _SFW32UnidadSinContenido;


#endif
