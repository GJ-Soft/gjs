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

int CajMsjMostrar ( int iTipo,const char * p_cTitulo, const char * p_cMensaje )
{
	int									iRes;
	char __attribute__ ( ( unused ) )	cVal;
	if ( ES_VALIDO ( p_cMensaje ) && ( TipCajMsjEsValido ( iTipo ) == 1 ) )
	{
		if ( ES_NULO ( p_cTitulo ) )
		{
			p_cTitulo = "";
		}
		printf ( "\n" );
		printf ( "********************************************************************************************\n" );
		printf ( "*  %.86s  *\n", p_cTitulo );
		printf ( "*------------------------------------------------------------------------------------------*\n" );
		printf ( "*                                                                                          *\n" );
		printf ( "*  %.86s  *\n", p_cMensaje );
		printf ( "*                                                                                          *\n" );
		printf ( "*                        Pulsa <retorno> para continuar...                                 *\n" );
		printf ( "********************************************************************************************\n" );
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

