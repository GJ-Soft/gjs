#include "BaseConfig.h"

#include "SistemaExcepcion.h"



using namespace std;

namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

# if ( defined ( WIN ) )

/* Rango reservado de Winsock. Ningun errno cae dentro, ni en la biblioteca de
   Microsoft ni en ninguna otra, asi que un codigo de aqui es de socket seguro. */
#	define SIS_EXC_MIN_ERROR_WINSOCK		10000
#	define SIS_EXC_MAX_ERROR_WINSOCK		11999

# endif


/* Texto del sistema para un codigo de error.

   En Windows conviven dos numeraciones dentro del mismo int. Los sockets rellenan
   el codigo con WSAGetLastError (), que devuelve valores del rango de Winsock, y
   strerror no sabe nada de ellos: contestaba "Unknown error" a TODOS los errores
   de socket, que es tanto como no dar mensaje. Esos se le piden al sistema con
   FormatMessage.

   El resto se queda en strerror, que es quien entiende los errno de verdad,
   incluidos los que Microsoft numera por su cuenta ( EWOULDBLOCK vale 140 alli, y
   11 en Cygwin y en Linux ): pasar esos a FormatMessage daria el mensaje de Win32
   que lleve ese numero, que no tiene nada que ver con el error que hubo. */
static string _DescribirError ( int iCodigo )
{
	string sRes ( "" );

# if ( defined ( WIN ) )
	if ( ( iCodigo >= SIS_EXC_MIN_ERROR_WINSOCK ) && ( iCodigo <= SIS_EXC_MAX_ERROR_WINSOCK ) )
	{
		LPSTR	p_cMensaje = NULL;
		DWORD	dwTam;

		/* IGNORE_INSERTS: sin el, un mensaje con parametros ( %1 ) hace que
		   FormatMessage vaya a buscarlos a una lista que no le hemos pasado. */
		dwTam = FormatMessageA ( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
								 FORMAT_MESSAGE_IGNORE_INSERTS,
								 NULL, (DWORD) iCodigo,
								 MAKELANGID ( LANG_NEUTRAL, SUBLANG_DEFAULT ),
								 (LPSTR) &p_cMensaje, 0, NULL );
		if ( ( dwTam > 0 ) && ( p_cMensaje != NULL ) )
		{
			/* FormatMessage remata con ".\r\n", y el mensaje de una excepcion no
			   puede llevar saltos de linea dentro: se cuelan donde una linea es una
			   unidad ( en las respuestas IETF, sin ir mas lejos ). RTrim solo quita
			   espacios, asi que aqui se recorta a mano. */
			sRes = string ( p_cMensaje, dwTam );
			sRes.erase ( sRes.find_last_not_of ( " \t\r\n" ) + 1 );
		}
		if ( p_cMensaje != NULL )
		{
			/* Con ALLOCATE_BUFFER el buffer lo reserva FormatMessage y hay que
			   soltarlo. SisErrDescripcion () de gjs-cpp-common-system no lo hace:
			   pierde memoria en cada error. */
			LocalFree ( p_cMensaje );
		}
	}
# endif

	if ( sRes.empty () )
	{
		sRes = string ( strerror ( iCodigo ) );
	}
	return ( sRes );
}

SistemaExcepcion::SistemaExcepcion( const string & _sModulo, const string & _sRutina, int _iErrno ) :
										Excepcion( _sModulo, _sRutina, _DescribirError( _iErrno ) )
{
}


            }
		}
	}
}
