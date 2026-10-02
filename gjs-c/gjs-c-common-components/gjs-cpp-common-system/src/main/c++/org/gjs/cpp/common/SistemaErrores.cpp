/******************************************************************************/
/*                             SistemaErrores.cpp                             */
/*----------------------------------------------------------------------------*/
/* Librería:  Sistema                                                         */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de código fuente que contiene la implementación de las rutinas     */
/* de obtención de información de los errores del sistema.                    */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#include "CommonSystemConfig.h"


#include "SistemaErrores.h"
#include <stack>  


using namespace std;

namespace org
{
	namespace gjs
	{
		namespace cpp
		{
			namespace common
			{



static int				g_iSisUltError = 0;
static stack<string> *	g_pilcadErrores = NULL;



bool SisHayError ( int iRefrescar )
{
	if ( iRefrescar == 1 )
	{
#	 if ( defined ( WIN ) )
		g_iSisUltError = (int) GetLastError ();
#	 else
		g_iSisUltError = errno;
#	 endif
	}

	return ( g_iSisUltError != 0 );
}

bool SisHayErrorDeMemoriaAgotada ( int iRefrescar )
{
	bool bRes = false;

	if ( iRefrescar == 1 )
	{
#	 if ( defined ( WIN ) )
		g_iSisUltError = (int) GetLastError ();
#	 else
		g_iSisUltError = errno;
#	 endif
	}
# if ( defined ( WIN ) )
	bRes = ( g_iSisUltError == 8 );
# elif ( defined ( UNIX ) )
	bRes = ( g_iSisUltError == 12 );
# else
	bRes = ( g_iSisUltError == 25 );
# endif
	return ( bRes );
}

int SisErrTipo ()
{
	int iTipo = SIS_TIP_ERR_INDEFINIDO;

	if ( g_iSisUltError < 0 )
	{
		iTipo = SIS_TIP_ERR_INDEFINIDO;
	}
	else if ( g_iSisUltError == 0 )
	{
		iTipo = SIS_TIP_ERR_NINGUNO;
	}
# if ( defined ( WIN ) )
	else if ( ( g_iSisUltError == 8 ) || ( g_iSisUltError == 14 ) )
	{
		iTipo = SIS_TIP_ERR_MEMORIA;
	}
# elif ( defined ( UNIX ) )
	else if ( ( g_iSisUltError == 12 ) || ( g_iSisUltError == 14 ) || ( g_iSisUltError == 49 ) )
	{
		iTipo = SIS_TIP_ERR_MEMORIA;
	}
# else
	else if ( ( g_iSisUltError == 11 ) || ( g_iSisUltError == 25 ) )
	{
		iTipo = SIS_TIP_ERR_MEMORIA;
	}
# endif
	else if ( g_iSisUltError <= SisMaxError () )
	{
		iTipo = SIS_TIP_ERR_SISTEMA;
	}
	return ( iTipo );
}

int SisErrCodigo ()
{
	return ( g_iSisUltError );
}

string SisErrDescripcion ()
{
	string sRes = "";

	if ( g_iSisUltError != 0 )
	{
#     if ( defined ( WIN ) )
		LPTSTR	lpMsgBuf = NULL;
		DWORD	dwTam;

		/* IGNORE_INSERTS: sin el, un mensaje con parametros ( %1 ) manda a
		   FormatMessage a buscarlos a una lista que no le hemos pasado. */
		dwTam = FormatMessage ( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
								FORMAT_MESSAGE_IGNORE_INSERTS, NULL, (DWORD) g_iSisUltError,
								MAKELANGID ( LANG_NEUTRAL, SUBLANG_DEFAULT ), (LPTSTR) &lpMsgBuf, 0, NULL );
		/* El puntero arrancaba sin inicializar y se construia el string sobre el
		   sin mirar si FormatMessage habia hecho algo: cuando falla no lo toca. */
		if ( ( dwTam > 0 ) && ES_VALIDO ( lpMsgBuf ) )
		{
			sRes = string ( (const char *) lpMsgBuf, dwTam );
			/* FormatMessage remata con ".\r\n", y este texto acaba dentro de una
			   linea de SisErrMensaje (). Mismo recorte que en SistemaExcepcion. */
			sRes.erase ( sRes.find_last_not_of ( " \t\r\n" ) + 1 );
		}
		if ( ES_VALIDO ( lpMsgBuf ) )
		{
			/* Con ALLOCATE_BUFFER el buffer lo reserva FormatMessage y hay que
			   soltarlo: sin esto se perdia memoria en cada error. La version C de
			   este mismo modulo si lo hacia. */
			LocalFree ( lpMsgBuf );
		}

#     elif ( defined ( GNU ) )
		sRes = string ( (const char *) strerror ( g_iSisUltError ) );
#     else
		if ( ES_VALIDO ( sys_errlist ) )
		{
			if ( ES_VALIDO ( sys_errlist [g_iSisUltError] ) )
			{
				sRes = string ( (const char *) sys_errlist [ g_iSisUltError ] );
			}
		}
# endif
		if ( sRes.empty () )
		{
			sRes = string ( (const char *) ERR_MSJ_DEFECTO );
		}
	}
	else
	{
		sRes = string ( (const char *) ERR_MSJ_OK );
	}
	return ( sRes );
}

string SisErrMensaje ( int iMostrarCodigo )
{
	string sRes;

	if ( iMostrarCodigo == 1 )
	{
		sRes = format ( "Error sistema {}", g_iSisUltError );
	}
	else
	{
		sRes = string ( "Error sistema" );
	}
	sRes = format ( "{} - {}", sRes, SisErrDescripcion () );
	return ( sRes );
}

string SisErrMensajeExt ( const string & sModulo, const string & sRutina )
{
	string sRes = "";

	if ( ! sModulo.empty () && ! sRutina.empty () )
	{
		sRes = format ( "[Modulo: {}; Rutina: {}] ", sModulo, sRutina );
	}
	else if ( ! sModulo.empty () )
	{
		sRes = format ( "[Modulo: {}] ", sModulo );
	}
	else if ( ! sRutina.empty () )
	{
		sRes = format ( "[Rutina: {}] ", sRutina );
	}
	sRes = format ( "{} Error sistema {} - {}", sRes, g_iSisUltError, SisErrDescripcion ( ) );
	return ( sRes );
}

void SisErrImprimir ()
{
	cout << SisErrMensaje () << endl;
}

void SisErrApilar ( const string & sModulo, const string & sRutina, int iRefrescar )
{
	if ( SisHayError ( iRefrescar ) )
	{
		if ( ES_NULO ( g_pilcadErrores ) )
		{
			g_pilcadErrores = new stack<string>();
			g_pilcadErrores->push ( SisErrMensajeExt ( sModulo, sRutina ) );
		}	
	}
}

void SisErrLimpiar ()
{
# if ( defined ( WIN ) )
	SetLastError ( 0 );
# else
	errno = 0;
# endif
	g_iSisUltError = 0;
}

int SisMaxError ()
{
	int iMaxError;

# if ( defined ( WIN ) )
	iMaxError = 16000;
# elif ( defined ( GNU ) )
	int			g_iSisUltError;

	g_iSisUltError = 1;
	string sMsj = string ( strerror ( g_iSisUltError ) );
	while ( ! sMsj.empty() &&
			! sMsj.starts_with ( "Unknown" ) )
	{
		g_iSisUltError = g_iSisUltError + 1;
		sMsj = string ( strerror ( g_iSisUltError ) );
	}
	iMaxError = g_iSisUltError - 1;
# else
	int g_iSisUltError;

	g_iSisUltError = 1;
	while ( ES_VALIDO ( sys_errlist [ g_iSisUltError ] ) &&
		    ( strlen ( sys_errlist [ g_iSisUltError ] ) > 0 ) )  
	{
		g_iSisUltError = g_iSisUltError + 1;
	}
	iMaxError = g_iSisUltError - 1;
# endif
	return ( iMaxError );
}

void SisErrImprimirPila ()
{
	if ( ES_VALIDO ( g_pilcadErrores ) )
	{
		while ( ! g_pilcadErrores->empty () )
		{
			cout << g_pilcadErrores->top () << endl;
			g_pilcadErrores->pop ();
		}
	}
}

void SisErrLimpiarPila ()
{
	delete g_pilcadErrores;
	g_pilcadErrores = NULL;
}


			}
		}
	}
}
