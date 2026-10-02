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


/* MinGW no trae pipe (): su equivalente es _pipe (), que ademas pide tamano y
   modo, y esta en <io.h>; _O_BINARY viene de <fcntl.h>. dup, dup2, close y write
   si existen con su nombre POSIX. Cygwin tiene pipe () de verdad, asi que solo
   se distingue el caso de MinGW puro. */
#if ( defined ( WIN ) )
#	include <io.h>
#	include <fcntl.h>
#	define SIM_CREAR_TUBERIA( p_i )		_pipe ( ( p_i ), 4096, _O_BINARY )
#else
#	define SIM_CREAR_TUBERIA( p_i )		pipe ( p_i )
#endif


using namespace std;

namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {




// Descriptor de stdin original mientras hay una simulacion de entrada activa.
static int g_iSimStdinOrig = -1;




/* Antes renunciaba en WIN porque la consola no leia de stdin, sino con getche y
   kbhit de conio.h. Eso era cosa de Visual C++ y ya no existe: AplicConLeerCadena
   y compania leen de stdin en los cuatro modos de compilacion, asi que la
   simulacion vale en todos. */
bool SimularEntradaConsola ( const string & sEntrada )
{
	bool	bRes = false;
	int		p_iTuberia [ 2 ];

	if ( g_iSimStdinOrig != -1 )
	{
		// Ya hay una simulacion activa: no se anida.
		bRes = false;
	}
	else if ( SIM_CREAR_TUBERIA ( p_iTuberia ) != 0 )
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
}


void RestaurarEntradaConsola ()
{
	if ( g_iSimStdinOrig != -1 )
	{
		fflush ( stdin );
		dup2 ( g_iSimStdinOrig, 0 );
		close ( g_iSimStdinOrig );
		g_iSimStdinOrig = -1;
		clearerr ( stdin );
	}
}



 			}
		}
	}
}
