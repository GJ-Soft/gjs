#include "ConsolaDepuracion.h"
#include "AplicacionConsola.h"

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




static bool	g_bConsolaDepuracionDisponible = false;
static bool	g_bConsolaDepuracionAbierta = false;




bool ConDepAbrir ()
{
	bool bRes = false;

	if ( !g_bConsolaDepuracionDisponible )
	{
		if ( !AplicConEstaAbierta () )
		{
			bRes = AplicConAbrir ();
			g_bConsolaDepuracionDisponible = bRes;
			g_bConsolaDepuracionAbierta = bRes;
		}
		else
		{
			g_bConsolaDepuracionDisponible = true;
			bRes = true;
		}
	}
	else
	{
		bRes = true;
	}
	return ( bRes );
}

void ConDepCerrar ()
{
	if ( g_bConsolaDepuracionDisponible )
	{
		if ( g_bConsolaDepuracionAbierta )
		{
			AplicConCerrar ();
		}
		g_bConsolaDepuracionDisponible = false;
		g_bConsolaDepuracionAbierta = false;
	}
}

bool ConDepEstaAbierta ()
{
	return ( g_bConsolaDepuracionDisponible );
}

bool ConDepEscribir ( const string & sTexto )
{
	bool bRes = false;

	if ( g_bConsolaDepuracionDisponible )
	{
		// Se trunca al ancho de la consola si esta disponible ( > 0 ).
		int iAncho = AplicConAncho ();
		cout << ( ( iAncho > 0 ) ? sTexto.substr ( 0, (size_t) iAncho ) : sTexto );
		bRes = true;
	}
	return ( bRes );
}

bool ConDepEscribirLinea ( const string & sTexto )
{
	bool bRes = ConDepEscribir ( sTexto );
	if ( bRes )
	{
		cout << endl;
	}
	return ( bRes );
}



 			}
		}
	}
}
