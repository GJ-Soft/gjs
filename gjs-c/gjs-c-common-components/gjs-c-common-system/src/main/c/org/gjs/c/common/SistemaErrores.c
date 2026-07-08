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

#include "SistemaErrores.h"

#include "SistemaConfig.h"




static int					g_iSisUltError = 0;
static SPilaLiterales	*	g_pillitErrores = NULL;


int SisHaHabidoError ()
{ 
	return ( SisHayError ( 0 ) );
}

int SisHaHabidoErrorDeMemoriaAgotada ()
{ 
	return ( SisHayErrorDeMemoriaAgotada ( 0 ) );
}

int SisHayError ( int iRefrescar )
{
	int iRes;

	if ( iRefrescar == 1 )
	{
#	 if ( defined ( WIN ) )
		g_iSisUltError = (int) GetLastError ();
#	 else
		g_iSisUltError = errno;
#	 endif
	}

	if ( g_iSisUltError != 0 )
	{
		iRes = 1;
	}
	else
	{
 		iRes = 0;
	}
	return ( iRes );
}

int SisHayErrorDeMemoriaAgotada ( int iRefrescar )
{
	int iRes;

	if ( iRefrescar == 1 )
	{
#	 if ( defined ( WIN ) )
		g_iSisUltError = (int) GetLastError ();
#	 else
		g_iSisUltError = errno;
#	 endif
	}
# if ( defined ( WIN ) )
	if ( g_iSisUltError == ERROR_NOT_ENOUGH_MEMORY )
	{
		iRes = 1;
	}
# else
	if ( g_iSisUltError == ENOMEM ) 
	{
		iRes = 1;
	}
# endif
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SisErrTipo ()
{
	int iTipo;

	if ( g_iSisUltError < 0 )
	{
		iTipo = SIS_TIP_ERR_INDEFINIDO;
	}
	else if ( g_iSisUltError == 0 )
	{
		iTipo = SIS_TIP_ERR_NINGUNO;
	}
# if ( defined ( WIN ) )
	else if ( ( g_iSisUltError == ERROR_NOT_ENOUGH_MEMORY ) || ( g_iSisUltError == ERROR_OUTOFMEMORY ) )
	{
		iTipo = SIS_TIP_ERR_MEMORIA;
	}
# else
	else if ( ( g_iSisUltError == ENOMEM ) || ( g_iSisUltError == EFAULT ) )
	{
		iTipo = SIS_TIP_ERR_MEMORIA;
	}
# endif
	else if ( g_iSisUltError <= SisMaxError () )
	{
		iTipo = SIS_TIP_ERR_SISTEMA;
	}
	else
	{
		iTipo = SIS_TIP_ERR_INDEFINIDO;
	}
	return ( iTipo );
}

int SisErrCodigo ()
{
	return ( g_iSisUltError );
}

const char * SisErrDescripcion ()
{
	const char * p_cRes = NULL;

	if ( g_iSisUltError != 0 )
	{
#     if ( defined ( WIN ) )
		LPTSTR lpMsgBuf;

		FormatMessage ( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, (DWORD) g_iSisUltError,
						MAKELANGID ( LANG_NEUTRAL, SUBLANG_DEFAULT ), (LPTSTR) &lpMsgBuf, 0, NULL );
		p_cRes = CadDuplicar ( (const char *) lpMsgBuf );
		LocalFree ( lpMsgBuf );

#     elif ( defined ( GNU ) )
		p_cRes = (const char *) strerror ( g_iSisUltError );
#     else
		if ( ES_VALIDO ( sys_errlist ) )
		{
			if ( ES_VALIDO ( sys_errlist [ g_iSisUltError ] ) )
			{
				p_cRes = (const char *) sys_errlist [ g_iSisUltError ];
			}
		}
# endif
		if ( ES_NULO ( p_cRes ) )
		{
				p_cRes = (const char *) ERR_MSJ_DEFECTO;
		}
	}
	else
	{
		p_cRes = (const char *) ERR_MSJ_OK;
	}
	return ( p_cRes );
}

char * SisErrMensaje ( int iMostrarCodigo )
{
	SCadena *		p_cadMsj;
	char *			p_cRes;

	p_cadMsj = SCadCrear ( ERR_MAX_TAM_MSJ );
	if ( ES_VALIDO ( p_cadMsj ) )
	{
		if ( iMostrarCodigo == 1 )
		{
			SCadCopiarConFormato ( p_cadMsj, "Error sistema %d", g_iSisUltError );
		}
		else
		{
			SCadCopiarConFormato ( p_cadMsj, "Error sistema" );
		}
		SCadConcatenarConFormato ( p_cadMsj, " - %s", SisErrDescripcion () );
		p_cRes = SCadDuplicarValor ( p_cadMsj );
		SCadDestruir ( &p_cadMsj );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

char * SisErrMensajeExt ( const char * p_cModulo, const char * p_cRutina )
{
	SCadena *		p_cadMsj;
	char *			p_cRes;

	p_cadMsj = SCadCrear ( ERR_MAX_TAM_MSJ );
	if ( ES_VALIDO ( p_cadMsj ) )
	{
		if ( ES_VALIDO ( p_cModulo ) && ES_VALIDO ( p_cRutina ) )
		{
			SCadCopiarConFormato ( p_cadMsj, "[Modulo: %s; Rutina: %s] ",  p_cModulo, p_cRutina );
		}
		else if ( ES_VALIDO ( p_cModulo ) )
		{
			SCadCopiarConFormato ( p_cadMsj, "[Modulo: %s] ",  p_cModulo );
		}
		else if ( ES_VALIDO ( p_cRutina ) )
		{
			SCadCopiarConFormato ( p_cadMsj, "[Rutina: %s] ",  p_cRutina );
		}
		SCadConcatenarConFormato ( p_cadMsj, "Error sistema %d", g_iSisUltError );
		SCadConcatenarConFormato ( p_cadMsj, " - %s", SisErrDescripcion ( ) );
		p_cRes = SCadDuplicarValor ( p_cadMsj );
		SCadDestruir ( &p_cadMsj );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

void SisErrImprimir ()
{
	char * p_cMsj = SisErrMensaje ( 1 );
	printf ( "%s\n", p_cMsj );
	MemLiberar ( (void **) &p_cMsj );
}

void SisErrApilar ( const char * p_cModulo, const char * p_cRutina, int iRefrescar )
{
	char * p_cMsj;
	
	if ( SisHayError ( iRefrescar ) == 1 )
	{
		if ( ES_NULO ( g_pillitErrores ) )
		{
			g_pillitErrores = SPilLitCrear ();
		}
		if ( ES_VALIDO ( g_pillitErrores ) )
		{
			p_cMsj = SisErrMensajeExt ( p_cModulo, p_cRutina );
			if ( SPilLitApilar ( g_pillitErrores, p_cMsj ) == 0 )
			{
				MemLiberar ( (void **) &p_cMsj );
			}
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
	char	*	p_cMsj;

	g_iSisUltError = 1;
	p_cMsj = strerror ( g_iSisUltError );
	while ( ES_VALIDO ( p_cMsj ) &&
		    ( CadLongitud ( p_cMsj ) > 0 ) &&
			( CadEmpiezaPor ( p_cMsj, "Unknown" ) == 0 ) )  
	{
		g_iSisUltError = g_iSisUltError + 1;
		p_cMsj = strerror ( g_iSisUltError );
	}
	iMaxError = g_iSisUltError - 1;
# else
	g_iSisUltError = 1;
	while ( ES_VALIDO ( sys_errlist [ g_iSisUltError ] ) &&
		    ( CadLongitud ( sys_errlist [ g_iSisUltError ] ) > 0 ) )  
	{
		g_iSisUltError = g_iSisUltError + 1;
	}
	iMaxError = g_iSisUltError - 1;
# endif
	return ( iMaxError );
}

void SisErrImprimirPila ()
{
	char * p_cMsj;
	
	while ( SPilLitEstaVacia ( g_pillitErrores ) == 0 )
	{
		p_cMsj = SPilLitDesapilar ( g_pillitErrores );
		printf ( "%s\n", p_cMsj );
		MemLiberar ( (void **) &p_cMsj );
	}
}

void SisErrLimpiarPila ()
{
	SPilLitVaciar ( g_pillitErrores );
	SPilLitDestruir ( &g_pillitErrores );
}
