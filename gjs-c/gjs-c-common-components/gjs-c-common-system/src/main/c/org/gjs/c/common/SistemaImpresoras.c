/******************************************************************************/
/*                           SistemaImpresoras.cpp                            */
/*----------------------------------------------------------------------------*/
/* Librería:  Sistema                                                         */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de código fuente que contiene la implementación de las rutinas     */
/* de carácter general de manejo de impresoras.                               */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#include "SistemaImpresoras.h"

#include "SistemaConfig.h"






#if ( defined ( WIN ) )




int SisImpresionPosible ()
{
	int	iRes;

	iRes = 1;
	return ( iRes );
}

int SisImprimir ( const char * p_cTexto )
{
	int			iRes;
	PRINTDLG	prndlgObj;
	DOCINFO		dociObj;
	HDC			hImpresora; 

	if ( ES_VALIDO ( p_cTexto ) )
	{
		MemLimpiar ( (void *) &prndlgObj, sizeof ( PRINTDLG ) );
		prndlgObj.lStructSize = sizeof ( PRINTDLG );
		// Para que cree el HDC automáticamente, se suele añadir el flag PD_RETURNDC
		prndlgObj.Flags = PD_RETURNDC;

		if( PrintDlg ( &prndlgObj ) != 0 )
		{
			hImpresora = prndlgObj.hDC;

			MemLimpiar ( (void *) &dociObj, sizeof ( DOCINFO ) );
			dociObj.cbSize = sizeof ( DOCINFO );

			StartDoc ( hImpresora, &dociObj );
			StartPage ( hImpresora );

			// SetTextColor( hPrinter, 0x0000FF );

			TextOut ( hImpresora, 100, 100, p_cTexto, CadLongitud ( p_cTexto ) );

			EndPage ( hImpresora );
			EndDoc ( hImpresora );
			DeleteDC ( hImpresora );

			iRes = 1;
			if ( prndlgObj.hDevMode != NULL )
			{
				GlobalFree( prndlgObj.hDevMode );
			}
			if ( prndlgObj.hDevNames != NULL )
			{
				GlobalFree(prndlgObj.hDevNames);	
			}
		}
		else
		{
			iRes = 0;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


#endif
