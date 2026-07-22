/******************************************************************************/
/*                         AplicacionPortapapeles.cpp                         */
/*----------------------------------------------------------------------------*/
/* Librería:  Aplicacion                                                      */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de código fuente que contiene la implementación de algunas         */
/* para manejo del portapapeles de Windows.                                   */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#include "AplicacionConfig.h"


#include "AplicacionPortapapeles.h"


#if ( defined ( WIN ) ) 





void AplicPplesLimpiar ()
{
	if ( OpenClipboard ( GetActiveWindow () ) != 0 )
	{
		EmptyClipboard ();
	    CloseClipboard ();
	}
}

void AplicPplesCopiar ( const char * p_cTexto )
{
	DWORD	dwTam;
	HANDLE	hMem;

	if ( OpenClipboard ( GetActiveWindow () ) != 0 )
	{
		EmptyClipboard ();

		dwTam = ((DWORD) CadLongitud ( p_cTexto )) + 1;
		if ( dwTam > 0 )
		{
			hMem = GlobalAlloc ( GMEM_FIXED, dwTam );
			if ( hMem != NULL )
			{
				CopyMemory ( hMem, p_cTexto, dwTam );
				//if ( SetClipboardData ( CF_DSPTEXT, hMem ) == NULL )
				if ( SetClipboardData ( CF_OEMTEXT, hMem ) == NULL )
				{
					// Error:
					GlobalFree ( hMem );
				}
			}
		}
	    CloseClipboard();
	}
}

const char * AplicPplesContenido ( int iLimpiar )
{
	DWORD		dwTam;
	HANDLE		hMem;
	char *	p_cRes;

	if ( OpenClipboard ( GetActiveWindow () ) != 0 )
	{
		//hMem = GetClipboardData ( CF_DSPTEXT );
		hMem = GetClipboardData ( CF_OEMTEXT );
		if ( hMem != NULL )
		{
			dwTam =  GlobalSize ( hMem );
			if ( dwTam > 1 )
			{
				p_cRes = CadCrear ( dwTam - 1 );
				CopyMemory ( p_cRes, hMem, dwTam - 1 );
				if ( iLimpiar == 1 )
				{
					EmptyClipboard ();
				}
			}
			else
			{
				p_cRes = CadCrear ( 0 );
			}
		}
		else
		{
			p_cRes = NULL;
		}
		CloseClipboard();
	}
	else
	{
		p_cRes = NULL;
	}
	return ( (const char *) p_cRes );
}


#endif

