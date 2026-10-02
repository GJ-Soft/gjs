#include "AplicacionConfig.h"
#include "SimulacionUsuarioConsola.h"


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


/* Descriptor de stdin original mientras hay una simulacion de entrada activa. */
static int g_iSimStdinOrig = -1;



/* Simula una entrada de usuario por consola para los tests cuyo codigo bajo
   prueba lee de stdin de forma bloqueante (p. ej. el getchar() de CajMsjMostrar
   en POSIX). Engancha stdin a una tuberia precargada con p_cEntrada + retorno
   ("" simula pulsar solo <retorno>). El extremo de escritura se cierra tras
   escribir, de modo que el lector ve la entrada y despues EOF: nunca se queda
   bloqueado, aunque lea de mas. Hay que llamar a RestaurarEntradaConsola tras
   la lectura para devolver stdin a su estado original. Devuelve 1 si prepara la
   entrada, 0 en caso de error.

   Antes renunciaba en WIN porque la consola no leia de stdin, sino con getche y
   kbhit de conio.h. Eso era cosa de Visual C++ y ya no existe: AplicConLeerCadena
   y compania leen de stdin en los cuatro modos de compilacion, asi que la
   simulacion vale en todos. */
int SimularEntradaConsola ( const char * p_cEntrada )
{
	int iRes;
	int p_iTuberia [ 2 ];

	if ( g_iSimStdinOrig != -1 )
	{
		/* Ya hay una simulacion activa: no se anida. */
		iRes = 0;
	}
	else if ( SIM_CREAR_TUBERIA ( p_iTuberia ) != 0 )
	{
		iRes = 0;
	}
	else
	{
		fflush ( stdout );
		if ( ES_VALIDO ( p_cEntrada ) )
		{
			write ( p_iTuberia [ 1 ], p_cEntrada, (size_t) CadLongitud ( p_cEntrada ) );
		}
		write ( p_iTuberia [ 1 ], "\n", 1 );
		close ( p_iTuberia [ 1 ] );

		g_iSimStdinOrig = dup ( 0 );
		if ( dup2 ( p_iTuberia [ 0 ], 0 ) == -1 )
		{
			close ( g_iSimStdinOrig );
			g_iSimStdinOrig = -1;
			iRes = 0;
		}
		else
		{
			iRes = 1;
		}
		close ( p_iTuberia [ 0 ] );
		clearerr ( stdin );
	}
	return ( iRes );
}


/* Deshace la redireccion hecha por SimularEntradaConsola, devolviendo stdin a
   su descriptor original. Es inocuo llamarla si no habia simulacion activa. */
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
