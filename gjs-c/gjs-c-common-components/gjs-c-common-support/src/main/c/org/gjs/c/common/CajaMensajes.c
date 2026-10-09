/***************************************************************************/
/*                          CajaMensajes.cpp                               */
/*-------------------------------------------------------------------------*/
/* Librería: GAplicacion                                                  */
/* Versión:  2.0.0                                                         */
/* Fecha:    01/09/2007                                                    */
/* Autor:    Ginés Jiménez Sánchez                                         */
/*-------------------------------------------------------------------------*/
/* Autor:    Ginés Jiménez Sánchez                                         */
/*-------------------------------------------------------------------------*/
/* Descripción:                                                            */
/* Fichero de código fuente que contiene la implementación de la rutina    */
/* para controlar el diálogo de mensajes del sistema.                      */
/*-------------------------------------------------------------------------*/
/*                    gines_jimenez@safe-mail.net                          */
/***************************************************************************/

#include "CajaMensajes.h"
#include "AplicacionConsola.h"


#include "AplicacionConfig.h"





#if ( defined ( WIN ) )


//extern HWND ExeVentanaPrincipal ();




int CajMsjMostrar ( int iTipo, const char * p_cTitulo, const char * p_cMensaje )
{
	int		iRes;
	UINT	uiFlags;
	HWND    hVentana;

	
	if ( ES_VALIDO ( p_cMensaje ) && ( TipCajMsjEsValido ( iTipo ) == 1 ) )
	{
		if ( iTipo == TIP_CAJ_MSJ_INFORMACION )
		{
			uiFlags = MB_ICONINFORMATION | MB_OK;
		}
		else if ( iTipo == TIP_CAJ_MSJ_PREGUNTA )
		{
			uiFlags = MB_ICONQUESTION | MB_YESNO;
		}
		else if ( iTipo == TIP_CAJ_MSJ_PREGUNTA_OKCAN )
		{
			uiFlags = MB_ICONQUESTION | MB_OKCANCEL;
		}
		else if ( iTipo == TIP_CAJ_MSJ_PREGUNTA_REINCAN )
		{
			uiFlags = MB_ICONQUESTION | MB_RETRYCANCEL;
		}
		else if ( iTipo == TIP_CAJ_MSJ_PREGUNTA_SINOCAN )
		{
			uiFlags = MB_ICONQUESTION | MB_YESNOCANCEL;
		}
		else if ( iTipo == TIP_CAJ_MSJ_AVISO )
		{
			uiFlags = MB_ICONEXCLAMATION | MB_OK;
		}
		else if ( iTipo == TIP_CAJ_MSJ_AVISO_OKCAN )
		{
			uiFlags = MB_ICONEXCLAMATION | MB_OKCANCEL;
		}
		else if ( iTipo == TIP_CAJ_MSJ_AVISO_REINCAN )
		{
			uiFlags = MB_ICONEXCLAMATION | MB_RETRYCANCEL;
		}
		else if ( iTipo == TIP_CAJ_MSJ_AVISO_ABRREINIGN )
		{
			uiFlags = MB_ICONEXCLAMATION | MB_ABORTRETRYIGNORE;
		}
		else if ( iTipo == TIP_CAJ_MSJ_ERROR )
		{
			uiFlags = MB_ICONERROR | MB_OK;
		}
		else if ( iTipo == TIP_CAJ_MSJ_ERROR_OKCAN )
		{
			uiFlags = MB_ICONERROR | MB_OKCANCEL;
		}
		else if ( iTipo == TIP_CAJ_MSJ_ERROR_REINCAN )
		{
			uiFlags = MB_ICONERROR | MB_RETRYCANCEL;
		}
		else //if ( iTipo == TIP_CAJ_MSJ_ERROR_ABRREINIGN )
		{
			uiFlags = MB_ICONERROR | MB_ABORTRETRYIGNORE;
		}
		uiFlags = uiFlags | MB_APPLMODAL;
		hVentana = GetActiveWindow ();
		if ( ES_NULO ( p_cTitulo ) )
		{
			p_cTitulo = "";
		}
		iRes = MessageBox ( hVentana, p_cMensaje, p_cTitulo, uiFlags );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CajMsjMostrarConFormato ( int iTipo, const char * p_cTitulo, const char * p_cFormato, ... )
{
	int 		iRes;
	SCadena *	p_cadMensaje;
	va_list		valArgumentos;

	p_cadMensaje = SCadCrear ( CAJ_MSJ_MAX_TAM_LINEA );
	if ( ES_VALIDO ( p_cadMensaje ) )
	{
		va_start ( valArgumentos, p_cFormato );
		SCadCopiarConFormato ( p_cadMensaje, p_cFormato, valArgumentos );
		va_end ( valArgumentos );
		iRes = CajMsjMostrar ( iTipo, p_cTitulo, SCadValorConstante ( p_cadMensaje ) );
		SCadDestruir ( &p_cadMensaje );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

#else

/* Ancho de la caja de mensajes cuando no se puede detectar el de la consola
   (p. ej. salida redirigida a un fichero). */
#define CAJ_MSJ_ANCHO_DEFECTO		80


/* Imprime una linea horizontal enmarcada de iAncho columnas: izquierda +
   (iAncho-2) medios + derecha. Los codigos son cadenas (los caracteres de
   dibujo pueden ser multibyte en UTF-8, pero ocupan una columna). */
static void _CajMsjLineaBorde ( int iAncho, const char * p_cIzq, const char * p_cMedio, const char * p_cDer )
{
	int iCol;

	printf ( "%s", p_cIzq );
	for ( iCol = 1; iCol < iAncho - 1; iCol = iCol + 1 )
	{
		printf ( "%s", p_cMedio );
	}
	if ( iAncho > 1 )
	{
		printf ( "%s", p_cDer );
	}
	printf ( "\n" );
}

/* Imprime una linea de texto enmarcada de iAncho columnas: vertical + "  " +
   texto (truncado o rellenado) + "  " + vertical. */
static void _CajMsjLineaTexto ( int iAncho, const char * p_cVer, const char * p_cTexto )
{
	int iCol;
	int iMaxTexto;
	int iLong;

	iMaxTexto = iAncho - 6;
	if ( iMaxTexto < 0 )
	{
		iMaxTexto = 0;
	}
	iLong = CadLongitud ( p_cTexto );
	if ( iLong > iMaxTexto )
	{
		iLong = iMaxTexto;
	}
	printf ( "%s  ", p_cVer );
	for ( iCol = 0; iCol < iLong; iCol = iCol + 1 )
	{
		printf ( "%c", p_cTexto [ iCol ] );
	}
	for ( iCol = iLong; iCol < iMaxTexto; iCol = iCol + 1 )
	{
		printf ( " " );
	}
	printf ( "  %s\n", p_cVer );
}

int CajMsjMostrar ( int iTipo, const char * p_cTitulo, const char * p_cMensaje )
{
	int				iRes;
	int				iAncho;
	const char *	p_cSupIzq;
	const char *	p_cSupDer;
	const char *	p_cInfIzq;
	const char *	p_cInfDer;
	const char *	p_cHor;
	const char *	p_cVer;
	const char *	p_cTeeIzq;
	const char *	p_cTeeDer;
	char __attribute__ ( ( unused ) ) cVal;

	if ( ES_VALIDO ( p_cMensaje ) && ( TipCajMsjEsValido ( iTipo ) == 1 ) )
	{
		if ( ES_NULO ( p_cTitulo ) )
		{
			p_cTitulo = "";
		}
		/* Los mensajes de error se enmarcan con borde doble; el resto con simple. */
		if ( iTipo >= TIP_CAJ_MSJ_ERROR )
		{
			p_cSupIzq = _CON_BRD_D_SUP_IZQ;
			p_cSupDer = _CON_BRD_D_SUP_DER;
			p_cInfIzq = _CON_BRD_D_INF_IZQ;
			p_cInfDer = _CON_BRD_D_INF_DER;
			p_cHor    = _CON_BRD_D_HOR;
			p_cVer    = _CON_BRD_D_VER;
			p_cTeeIzq = _CON_BRD_D_TEE_IZQ;
			p_cTeeDer = _CON_BRD_D_TEE_DER;
		}
		else
		{
			p_cSupIzq = _CON_BRD_S_SUP_IZQ;
			p_cSupDer = _CON_BRD_S_SUP_DER;
			p_cInfIzq = _CON_BRD_S_INF_IZQ;
			p_cInfDer = _CON_BRD_S_INF_DER;
			p_cHor    = _CON_BRD_S_HOR;
			p_cVer    = _CON_BRD_S_VER;
			p_cTeeIzq = _CON_BRD_S_TEE_IZQ;
			p_cTeeDer = _CON_BRD_S_TEE_DER;
		}
		/* La caja se ajusta al ancho de la consola; si no se puede detectar
		   (p. ej. salida redirigida) se usa un ancho por defecto. */
		iAncho = AplicConAncho ();
		if ( iAncho <= 0 )
		{
			iAncho = CAJ_MSJ_ANCHO_DEFECTO;
		}
		printf ( "\n" );
		_CajMsjLineaBorde ( iAncho, p_cSupIzq, p_cHor, p_cSupDer );
		_CajMsjLineaTexto ( iAncho, p_cVer, p_cTitulo );
		_CajMsjLineaBorde ( iAncho, p_cTeeIzq, p_cHor, p_cTeeDer );
		_CajMsjLineaTexto ( iAncho, p_cVer, "" );
		_CajMsjLineaTexto ( iAncho, p_cVer, p_cMensaje );
		_CajMsjLineaTexto ( iAncho, p_cVer, "" );
		_CajMsjLineaTexto ( iAncho, p_cVer, "Pulsa <retorno> para continuar..." );
		_CajMsjLineaBorde ( iAncho, p_cInfIzq, p_cHor, p_cInfDer );
		printf ( "\n" );
		cVal = getchar ();
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CajMsjMostrarConFormato ( int iTipo, const char * p_cTitulo, const char * p_cFormato, ... )
{
	int 		iRes;
	SCadena *	p_cadMensaje;
	va_list		valArgumentos;

	p_cadMensaje = SCadCrear ( CAJ_MSJ_MAX_TAM_LINEA );
	if ( ES_VALIDO ( p_cadMensaje ) )
	{
		va_start ( valArgumentos, p_cFormato );
		SCadCopiarConFormato ( p_cadMensaje, p_cFormato, valArgumentos );
		iRes = CajMsjMostrar ( iTipo, p_cTitulo, SCadValorConstante ( p_cadMensaje ) );
		SCadDestruir ( &p_cadMensaje );
		va_end ( valArgumentos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}



#endif

