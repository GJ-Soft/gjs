/***************************************************************************/
/*                        AplicacionInformacion.cpp                        */
/*-------------------------------------------------------------------------*/
/* Librer�a: Aplicacion                                                    */
/* Versi�n:  2.0.0                                                         */
/* Fecha:    01/09/2007                                                    */
/* Autor:    Gin�s Jim�nez S�nchez                                         */
/*-------------------------------------------------------------------------*/
/* Descripci�n:                                                            */
/* Fichero de c�digo fuente que contiene la implementaci�n de algunas      */
/* rutinas para inicializar y consultar algunas variables globales que     */
/* contendr�n informaci�n general acerca de una librer�a o aplicaci�n.     */
/*-------------------------------------------------------------------------*/
/*                    gines_jimenez@safe-mail.net                          */
/***************************************************************************/
#include "AplicacionInformacion.h"

#include "CommonSupportConfig.h"

#include "Version.h"
#include "AplicacionConsola.h"



using namespace std;

namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {



// PID del proceso:
static long							g_lAplicPID = -1;

// Nombre de la aplicaci�n:
static string 						g_sAplicNombre = string ( "" ); 

// Informaci�n de la versi�n:
static Version *					g_p_verAplicInfo = NULL; 

// Control de inicializaci�n:
static bool							g_bAplicInicializada = false;





bool AplicInicializar ( const string & sNombre, int iVersion, int iSubversion, int iRevision, long lFecha, bool bConsola )
{
	if ( !g_bAplicInicializada )
	{
		// Consola:
		if ( !bConsola )
		{
			AplicConCerrar ();
		}

		// Nombre:
		g_sAplicNombre = string ( sNombre );

		// PID:
		g_lAplicPID = SisPID ();

		// Versi�n:
		if ( ES_NULO ( g_p_verAplicInfo ) )
		{
			g_p_verAplicInfo = new Version ( iVersion, iSubversion, iRevision, lFecha );
			if ( ES_VALIDO ( g_p_verAplicInfo ) ) 
			{
				g_bAplicInicializada = true;
			}
		}
		else
		{
			// ( se corrigio el orden: antes se pasaba iRevision antes que iSubversion ).
			g_bAplicInicializada = g_p_verAplicInfo->Establecer ( iVersion, iSubversion, iRevision, lFecha );
		}
	}
	return ( g_bAplicInicializada );
}

string AplicNombre ()
{
	return ( g_sAplicNombre );
}

int AplicVersion ()
{
	int iRes;

	if ( ES_VALIDO ( g_p_verAplicInfo ) )
	{
		iRes = g_p_verAplicInfo->Ver();
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
		iRes = g_p_verAplicInfo->Subver ();
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
		iRes = g_p_verAplicInfo->Rev ();
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

string AplicCadenaVersion ()
{
	string sRes = "";

	if ( ES_VALIDO ( g_p_verAplicInfo ) )
	{
		sRes = g_p_verAplicInfo->CadenaVersion ();
	}
	return ( sRes );
}

Fecha AplicFechaVersion ()
{
	Fecha fecRes = Fecha ();

	if ( ES_VALIDO ( g_p_verAplicInfo ) )
	{
		fecRes = g_p_verAplicInfo->Fecha();
	}
	return ( fecRes );
}

long AplicValorFechaVersion ()
{
	long lRes = 0;

	if ( ES_VALIDO ( g_p_verAplicInfo ) )
	{
		lRes = g_p_verAplicInfo->Fecha ().Valor();
	}
	return ( lRes );
}

long AplicPID ()
{
	return ( g_lAplicPID );
}

bool AplicEstaInicializada ()
{
	return ( g_bAplicInicializada );
}

void AplicImprimirInfoVersion ()
{
	cout << g_sAplicNombre << ' ';
	if ( ES_VALIDO ( g_p_verAplicInfo ) )
	{
		g_p_verAplicInfo->Imprimir ();
	}
}

void AplicFinalizar ()
{
	delete g_p_verAplicInfo; 
	g_p_verAplicInfo = NULL;
	g_lAplicPID = -1;
	g_bAplicInicializada = false;
	g_sAplicNombre = "";
}




 			}
		}
	}
}



