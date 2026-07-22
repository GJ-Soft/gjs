/******************************************************************************/
/*                        SimulacionUsuarioConsola.cpp                        */
/*----------------------------------------------------------------------------*/
/* Libreria:  Support                                                         */
/*----------------------------------------------------------------------------*/
/* Descripcion:                                                               */
/* Implementacion de la utilidad de simulacion de entrada de usuario por      */
/* consola para los tests. Version C++ de la clase homonima del modulo C.     */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#include "SimulacionUsuarioConsola.h"

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




#if ( !defined ( WIN ) )
// Descriptor de stdin original mientras hay una simulacion de entrada activa.
static int g_iSimStdinOrig = -1;
#endif




bool SimularEntradaConsola ( const string & sEntrada )
{
#if ( defined ( WIN ) )
	// En WIN la consola no lee de stdin ( getche/kbhit ): no aplica.
	(void) sEntrada;
	return ( false );
#else
	bool	bRes = false;
	int		p_iTuberia [ 2 ];

	if ( g_iSimStdinOrig != -1 )
	{
		// Ya hay una simulacion activa: no se anida.
		bRes = false;
	}
	else if ( pipe ( p_iTuberia ) != 0 )
	{
		bRes = false;
	}
	else
	{
		ssize_t	sEscrito;

		fflush ( stdout );
		if ( ! sEntrada.empty () )
		{
			sEscrito = write ( p_iTuberia [ 1 ], sEntrada.c_str (), sEntrada.length () );
		}
		sEscrito = write ( p_iTuberia [ 1 ], "\n", 1 );
		(void) sEscrito;
		close ( p_iTuberia [ 1 ] );

		g_iSimStdinOrig = dup ( 0 );
		if ( dup2 ( p_iTuberia [ 0 ], 0 ) == -1 )
		{
			close ( g_iSimStdinOrig );
			g_iSimStdinOrig = -1;
			bRes = false;
		}
		else
		{
			bRes = true;
		}
		close ( p_iTuberia [ 0 ] );
		clearerr ( stdin );
	}
	return ( bRes );
#endif
}


void RestaurarEntradaConsola ()
{
#if ( !defined ( WIN ) )
	if ( g_iSimStdinOrig != -1 )
	{
		fflush ( stdin );
		dup2 ( g_iSimStdinOrig, 0 );
		close ( g_iSimStdinOrig );
		g_iSimStdinOrig = -1;
		clearerr ( stdin );
	}
#endif
}



 			}
		}
	}
}
