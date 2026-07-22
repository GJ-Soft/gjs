/***************************************************************************/
/*                        AplicacionInformacion.cpp                        */
/*-------------------------------------------------------------------------*/
/* Librería: Aplicacion                                                    */
/* Versión:  2.0.0                                                         */
/* Fecha:    01/09/2007                                                    */
/* Autor:    Ginés Jiménez Sánchez                                         */
/*-------------------------------------------------------------------------*/
/* Descripción:                                                            */
/* Fichero de código fuente que contiene la implementación de algunas      */
/* rutinas para inicializar y consultar algunas variables globales que     */
/* contendrán información general acerca de una librería o aplicación.     */
/*-------------------------------------------------------------------------*/
/*                    gines_jimenez@safe-mail.net                          */
/***************************************************************************/
#include "AplicacionConfig.h"
#include "AplicacionInformacion.h"
#include "AplicacionConsola.h"



#include <Base.h>
#include <Tipos.h>
#include <Texto.h>


#include "SVersion.h"




// PID del proceso:
static long							g_lAplicPID = -1;

// Nombre de la aplicación:
static char *						g_p_cAplicNombre = NULL; 

// Información de la versión:
static SVersion *					g_p_verAplicInfo = NULL; 

// Control de inicialización:
static int							g_iAplicInicializada = 0;








int AplicInicializar ( const char * p_cNombre, int iVersion, int iSubversion, int iRevision, unsigned long ulFecha, int iConsola )
{
	int iRes;

	if ( g_iAplicInicializada == 0 )
	{
		// Consola:
		if ( iConsola == 0 )
		{
			AplicConCerrar ();
		}

		// Nombre:
		g_p_cAplicNombre = CadDuplicar ( p_cNombre );

		// PID:
		g_lAplicPID = SisPID ();

		// Versión:
		if ( ES_NULO ( g_p_verAplicInfo ) )
		{
			g_p_verAplicInfo = SVerCrear ( iVersion, iSubversion, iRevision, ulFecha );
			if ( ES_VALIDO ( g_p_verAplicInfo ) )
			{
				iRes = 1;
				g_iAplicInicializada = 1;
			}
			else
			{
				//ErrEstablecer ( ERR_MEMORIA_INSUFICIENTE, _LIB_APLICACION_NOMBRE );
				iRes = 0;
			}
		}
		else
		{
			if ( SVerEstablecer ( g_p_verAplicInfo, iVersion, iRevision, iSubversion, ulFecha ) == 1 )
			{
				iRes = 1;
				g_iAplicInicializada = 1;
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

const char * AplicNombre ()
{
	const char * p_cRes;

	if ( ES_VALIDO ( g_p_cAplicNombre ) )
	{
		p_cRes = CadDuplicar ( g_p_cAplicNombre );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int AplicVersion ()
{
	int iRes;

	if ( ES_VALIDO ( g_p_verAplicInfo ) )
	{
		iRes = SVerVersion ( g_p_verAplicInfo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int AplicSubversion ()
{
	int iRes;

	if ( ES_VALIDO ( g_p_verAplicInfo ) )
	{
		iRes = SVerSubversion ( g_p_verAplicInfo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int AplicRevision ()
{
	int iRes;

	if ( ES_VALIDO ( g_p_verAplicInfo ) )
	{
		iRes = SVerRevision ( g_p_verAplicInfo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

const char * AplicCadenaVersion ()
{
	const char * p_cRes;

	if ( ES_VALIDO ( g_p_verAplicInfo ) )
	{
		p_cRes = SVerCadenaVersion ( g_p_verAplicInfo,  0 );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

SFecha * AplicFechaVersion ()
{
	SFecha * p_fecRes;

	if ( ES_VALIDO ( g_p_verAplicInfo ) )
	{
		p_fecRes = SVerFecha ( g_p_verAplicInfo );
	}
	else
	{
		p_fecRes = NULL;
	}
	return ( p_fecRes );
}

long AplicValorFechaVersion ()
{
	long lRes;

	if ( ES_VALIDO ( g_p_verAplicInfo ) )
	{
		if ( ES_VALIDO ( SVerFecha ( g_p_verAplicInfo ) ) )
		{
			lRes = SFecValor ( SVerFecha ( g_p_verAplicInfo ) );
		}
		else
		{
			lRes = 0;
		}
	}
	else
	{
		lRes = 0;
	}
	return ( lRes );
}

long AplicPID ()
{
	return ( g_lAplicPID );
}

int AplicEstaInicializada ()
{
	return ( g_iAplicInicializada );
}

void AplicImprimirInfoVersion ()
{
	if ( ES_VALIDO ( g_p_cAplicNombre ) )
	{
		printf ( "%s ", g_p_cAplicNombre );
	}
	if ( ES_VALIDO ( g_p_verAplicInfo ) )
	{
		SVerImprimir ( g_p_verAplicInfo );
	}
}

void AplicFinalizar ()
{
	SVerDestruir ( &g_p_verAplicInfo ); 
	g_lAplicPID = -1;
	g_iAplicInicializada = 0;
	MemLiberar ( (void **) &g_p_cAplicNombre );
}




