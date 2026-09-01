/******************************************************************************/
/*                                UniChar.cpp                                 */
/*----------------------------------------------------------------------------*/
/* Librería:  GBase                                                           */
/* Versión:   1.0.0                                                           */
/* Fecha:     28/06/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de código fuente que contiene la implementación de algunas ru-     */
/* tinas relacionadas con el tratamiento de cadenas Unicode.                  */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#include "UniChar.h"

#include "Memoria.h"
#include "CadenasBase.h"


char UnicodeAscii ( unichar ucValor )
{
	return ( (char) ( ucValor & 0x00FF ) );
}

unichar AsciiAUnicode ( char cValor )
{
	return ( 0x00FF & (unichar) cValor );
}

char * CadUnicodeAAsciiz ( const unichar * p_ucUnicode )
{
	char *	p_cRes;
	int		iLong;

	if ( ES_VALIDO ( p_ucUnicode ) )
	{
		//iLong = wcslen ( p_ucUnicode );
		p_cRes = NULL;
#    if ( defined ( WIN ) )
		SetLastError ( 0 );
		iLong = WideCharToMultiByte ( JUEG_CAR_OEM_LATIN_I, 0, (LPCWSTR) p_ucUnicode, -1, (LPSTR) p_cRes, 0, NULL, NULL );
		if ( ( iLong == 0 ) && ( GetLastError () != 0 ) )
		{
			iLong = -1;
		}
#    else
		iLong = wcstombs( NULL, p_ucUnicode, 0 );
#    endif
		if ( iLong > 0 )
		{
			/* En WIN iLong ya incluye el terminador; en POSIX wcstombs no lo cuenta,
			   asi que se reserva siempre uno de mas para no escribir fuera. */
			p_cRes = (char *) MemReservar ( ( iLong + 1 ) * sizeof ( char ) );
#	     if ( defined ( WIN ) )
			if ( WideCharToMultiByte ( JUEG_CAR_OEM_LATIN_I, 0, (LPCWSTR) p_ucUnicode, -1, (LPSTR) p_cRes, iLong, NULL, NULL ) == 0 )
#		 else
			if ( wcstombs ( p_cRes, p_ucUnicode, iLong + 1 ) == (size_t) -1 )
#	     endif
			{
				MemLiberarCadena ( &p_cRes );
			}
		}
		else
		{
			p_cRes = NULL;
		}
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

unichar * CadAsciizAUnicode ( const char * p_cAsciiz )
{
	unichar *	p_ucRes;
	int			iLongWC;
# if ( defined ( WIN ) )
	int			iLong;
# endif

	if ( ES_VALIDO ( p_cAsciiz ) )
	{
		p_ucRes = NULL;
#    if ( defined ( WIN ) )
		iLong = CadLongitud ( p_cAsciiz );
		SetLastError ( 0 );
		iLongWC = MultiByteToWideChar ( JUEG_CAR_OEM_LATIN_I, 0, (LPCSTR) p_cAsciiz, iLong + 1, (LPWSTR) p_ucRes, 0 );
		if ( ( iLongWC == 0 ) && ( GetLastError () != 0 ) )
		{
			iLongWC = -1;
		}
#    else
		iLongWC = mbstowcs ( NULL, p_cAsciiz, 0 );
#    endif
		if ( iLongWC >= 0 )
		{
			p_ucRes = (unichar *) MemReservar ( ( iLongWC + 1 ) * sizeof ( unichar ) );
#	     if ( defined ( WIN ) )
			if ( MultiByteToWideChar ( JUEG_CAR_OEM_LATIN_I, 0, (LPCSTR) p_cAsciiz, iLong + 1, (LPWSTR) p_ucRes, iLongWC ) == 0)
#		 else
			if ( mbstowcs( p_ucRes, p_cAsciiz, iLongWC + 1 ) == (size_t) -1 )
#	     endif
			{
				MemLiberarUnicode ( &p_ucRes );
			}
		}
		else
		{
			p_ucRes = NULL;
		}
	}
	else
	{
		p_ucRes = NULL;
	}
	return ( p_ucRes );
}







