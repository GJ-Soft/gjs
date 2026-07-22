/***************************************************************************/
/*                          CajaMensajes.cpp                               */
/*-------------------------------------------------------------------------*/
/* Libreria: GAplicacion                                                   */
/* Version:  2.0.0                                                         */
/* Fecha:    01/09/2007                                                    */
/* Autor:    Gines Jimenez Sanchez                                         */
/*-------------------------------------------------------------------------*/
/* Descripcion:                                                            */
/* Fichero de codigo fuente que contiene la implementacion de la rutina    */
/* para controlar el dialogo de mensajes del sistema.                      */
/*-------------------------------------------------------------------------*/
/*                    gines_jimenez@safe-mail.net                          */
/***************************************************************************/

#include "CajaMensajes.h"

#include "CommonSupportConfig.h"



using namespace std;

namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {




#if ( defined ( WIN ) )


// Traduce el boton pulsado ( IDOK, IDYES, ... ) a la respuesta portable.
static RespuestaCajaMensajes _CajMsjRespuestaDeBoton ( int iBoton )
{
	switch ( iBoton )
	{
		case IDOK:		return ( RespuestaCajaMensajes::Aceptar );
		case IDYES:		return ( RespuestaCajaMensajes::Aceptar );
		case IDCANCEL:	return ( RespuestaCajaMensajes::Cancelar );
		case IDNO:		return ( RespuestaCajaMensajes::No );
		case IDRETRY:	return ( RespuestaCajaMensajes::Reintentar );
		case IDABORT:	return ( RespuestaCajaMensajes::Abortar );
		case IDIGNORE:	return ( RespuestaCajaMensajes::Ignorar );
		default:		return ( RespuestaCajaMensajes::Ninguna );
	}
}

RespuestaCajaMensajes CajMsjMostrar ( TipoCajaMensajes tipo, const string & sTitulo, const string & sMensaje )
{
	RespuestaCajaMensajes respRes = RespuestaCajaMensajes::Ninguna;

	if ( ! sMensaje.empty () && TipCajMsjEsValido ( tipo ) )
	{
		UINT	uiFlags;
		switch ( tipo )
		{
			case TipoCajaMensajes::Informacion:		uiFlags = MB_ICONINFORMATION | MB_OK;				break;
			case TipoCajaMensajes::Pregunta:		uiFlags = MB_ICONQUESTION | MB_YESNO;				break;
			case TipoCajaMensajes::PreguntaOkCan:	uiFlags = MB_ICONQUESTION | MB_OKCANCEL;			break;
			case TipoCajaMensajes::PreguntaReinCan:	uiFlags = MB_ICONQUESTION | MB_RETRYCANCEL;			break;
			case TipoCajaMensajes::PreguntaSiNoCan:	uiFlags = MB_ICONQUESTION | MB_YESNOCANCEL;			break;
			case TipoCajaMensajes::Aviso:			uiFlags = MB_ICONEXCLAMATION | MB_OK;				break;
			case TipoCajaMensajes::AvisoOkCan:		uiFlags = MB_ICONEXCLAMATION | MB_OKCANCEL;			break;
			case TipoCajaMensajes::AvisoReinCan:	uiFlags = MB_ICONEXCLAMATION | MB_RETRYCANCEL;		break;
			case TipoCajaMensajes::AvisoAbrReinIgn:	uiFlags = MB_ICONEXCLAMATION | MB_ABORTRETRYIGNORE;	break;
			case TipoCajaMensajes::Error:			uiFlags = MB_ICONERROR | MB_OK;						break;
			case TipoCajaMensajes::ErrorOkCan:		uiFlags = MB_ICONERROR | MB_OKCANCEL;				break;
			case TipoCajaMensajes::ErrorReinCan:	uiFlags = MB_ICONERROR | MB_RETRYCANCEL;			break;
			default:								uiFlags = MB_ICONERROR | MB_ABORTRETRYIGNORE;		break;
		}
		uiFlags = uiFlags | MB_APPLMODAL;
		HWND hVentana = GetActiveWindow ();
		respRes = _CajMsjRespuestaDeBoton ( MessageBox ( hVentana, sMensaje.c_str(), sTitulo.c_str(), uiFlags ) );
	}
	return ( respRes );
}


#else


// Imprime una cadena ( caracter de borde multi-byte ) iVeces veces.
static void _CajMsjRepetir ( const char * p_cCar, int iVeces )
{
	for ( int i = 0; i < iVeces; i = i + 1 )
	{
		cout << p_cCar;
	}
}

// Linea " texto ... " entre bordes verticales, rellenando hasta iInterior columnas.
static void _CajMsjLineaTexto ( const char * p_cVer, const string & sTexto, int iInterior )
{
	string sVis = sTexto;
	if ( (int) sVis.length () > iInterior - 2 )
	{
		sVis = sVis.substr ( 0, iInterior - 2 );
	}
	cout << p_cVer << " " << sVis;
	int iRelleno = iInterior - 1 - (int) sVis.length ();
	for ( int i = 0; i < iRelleno; i = i + 1 )
	{
		cout << " ";
	}
	cout << p_cVer << endl;
}

RespuestaCajaMensajes CajMsjMostrar ( TipoCajaMensajes tipo, const string & sTitulo, const string & sMensaje )
{
	RespuestaCajaMensajes respRes = RespuestaCajaMensajes::Ninguna;

	if ( ! sMensaje.empty () && TipCajMsjEsValido ( tipo ) )
	{
		// Los tipos de error ( >= TIP_CAJ_MSJ_ERROR ) se dibujan con borde doble.
		bool bDoble = ( (int) tipo >= TIP_CAJ_MSJ_ERROR );

		const char * pSupIzq = bDoble ? _CON_BRD_D_SUP_IZQ : _CON_BRD_S_SUP_IZQ;
		const char * pSupDer = bDoble ? _CON_BRD_D_SUP_DER : _CON_BRD_S_SUP_DER;
		const char * pInfIzq = bDoble ? _CON_BRD_D_INF_IZQ : _CON_BRD_S_INF_IZQ;
		const char * pInfDer = bDoble ? _CON_BRD_D_INF_DER : _CON_BRD_S_INF_DER;
		const char * pHor    = bDoble ? _CON_BRD_D_HOR     : _CON_BRD_S_HOR;
		const char * pVer    = bDoble ? _CON_BRD_D_VER     : _CON_BRD_S_VER;
		const char * pTeeIzq = bDoble ? _CON_BRD_D_TEE_IZQ : _CON_BRD_S_TEE_IZQ;
		const char * pTeeDer = bDoble ? _CON_BRD_D_TEE_DER : _CON_BRD_S_TEE_DER;

		int iAncho = CAJ_MSJ_ANCHO_DEFECTO;
		int iInterior = iAncho - 2;

		cout << endl;
		// Borde superior.
		cout << pSupIzq; _CajMsjRepetir ( pHor, iInterior ); cout << pSupDer << endl;
		// Titulo.
		_CajMsjLineaTexto ( pVer, sTitulo, iInterior );
		// Separador titulo / cuerpo.
		cout << pTeeIzq; _CajMsjRepetir ( pHor, iInterior ); cout << pTeeDer << endl;
		// Cuerpo.
		_CajMsjLineaTexto ( pVer, "", iInterior );
		_CajMsjLineaTexto ( pVer, sMensaje, iInterior );
		_CajMsjLineaTexto ( pVer, "", iInterior );
		_CajMsjLineaTexto ( pVer, "Pulsa <retorno> para continuar...", iInterior );
		// Borde inferior.
		cout << pInfIzq; _CajMsjRepetir ( pHor, iInterior ); cout << pInfDer << endl;
		cout << endl;

		// Bloqueante: espera a que el usuario pulse <retorno>.
		getchar ();
		respRes = RespuestaCajaMensajes::Aceptar;
	}
	return ( respRes );
}


#endif


 			}
		}
	}
}
