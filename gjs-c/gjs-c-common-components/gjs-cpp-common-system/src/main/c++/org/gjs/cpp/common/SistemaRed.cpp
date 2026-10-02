/******************************************************************************/
/*                               SistemaRed.cpp                               */
/*----------------------------------------------------------------------------*/
/* Librería:  Sistema                                                         */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de código fuente que contiene la implementación de la algunas      */
/* rutinas generales de información de red.                                   */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/


#include "CommonSystemConfig.h"


#include "SistemaRed.h"

#include <vector>


using namespace std;
using namespace org::gjs::cpp::common;

namespace org
{
	namespace gjs
	{
		namespace cpp
		{
			namespace common
			{

extern void MemLimpiar ( void * p_vBloque, int iNumBytes );


wstring SisRedNombreOrdenador ()
{
	wstring sRes = L"";
# if ( defined ( WIN ) )
	vector<wchar_t> buffer = vector<wchar_t> ( SIS_SO_MAX_TAM_BUFFER );
	DWORD			dwTam;
# else
	vector<char> 	buffer = vector<char> ( SIS_SO_MAX_TAM_BUFFER );
	int				iTam;
# endif	

# if ( defined ( WIN ) )
	dwTam = (DWORD) buffer.size();
	if ( GetComputerName ( (LPTSTR) buffer.data(), ( LPDWORD ) &dwTam) > 0 )
	{
		sRes = wstring ( buffer.data() );
	}
# else
	iTam = buffer.size();
	if ( gethostname( (char *) buffer.data(), iTam ) == 0 )
	{
		sRes = Utf8AUnicode ( buffer.data() );
	}
# endif
	return ( sRes );
}

wstring SisRedNombreDNSOrdenador ()
{
	wstring sRes = L"";
# if ( defined ( WIN ) )
	vector<wchar_t> buffer = vector<wchar_t> ( SIS_SO_MAX_TAM_BUFFER );
	DWORD			dwTam;
# else
	vector<char> 	buffer = vector<char> ( SIS_SO_MAX_TAM_BUFFER );
	int				iTam;
# endif	
# if ( defined ( WIN ) )
	dwTam = (DWORD) buffer.size();
	if ( GetComputerNameEx ( ComputerNameDnsFullyQualified, (LPTSTR) buffer.data(), &dwTam ) > 0 )
	{
		sRes = wstring ( buffer.data () );
	}
# else
	iTam = (int) buffer.size();
	if ( gethostname( (char *) buffer.data(), iTam ) == 0 )
	{
		sRes = Utf8AUnicode ( buffer.data() );

		struct addrinfo hints;
		struct addrinfo *res;
		MemLimpiar ( (void *) &hints, (int) sizeof( hints ) );
		hints.ai_flags = AI_CANONNAME;

		if ( getaddrinfo( buffer.data(), NULL, &hints, &res ) == 0 )
		{
			if ( ES_VALIDO ( res->ai_canonname ) )
			{
				sRes = Utf8AUnicode ( res->ai_canonname );
			}
			freeaddrinfo( res );
		}
	}
# endif
	return ( sRes );
}

/* Solo en Windows. Se apoya en NetMessageBufferSend, el servicio de
   mensajeria de Windows, que no tiene equivalente en POSIX: no existe un
   mecanismo estandar para hacerle llegar un aviso emergente a otra maquina.
   Fuera de Windows la funcion no se declara, para que quien la llame se
   encuentre un error de compilacion en vez de un false que no significa nada.

   OJO, sigue en pie la nota de siempre: tampoco en Windows se la ha visto
   funcionar. El servicio de mensajeria ( Messenger ) esta desactivado por
   defecto desde Windows Vista, asi que NetMessageBufferSend contesta error
   salvo que alguien lo levante a mano. Eso es del sistema, no del codigo. */
#if ( defined ( WIN ) )
bool SisRedEnviarMensaje ( const wstring & sDestino, const wstring & sOrigen, const string & sMensaje )
{
	bool	bRes = false;
	DWORD	dwTam;
	DWORD	dwRes;

	if ( !sDestino.empty() && ! sOrigen.empty () && ! sMensaje.empty () )
	{
		dwTam = (DWORD) sMensaje.length();
		dwRes = NetMessageBufferSend ( (LPCWSTR) NULL, (LPCWSTR) sDestino.c_str(), ( LPCWSTR ) sOrigen.c_str (), ( LPBYTE ) sMensaje.c_str (), dwTam);
		if ( dwRes == 0 ) // NERR_Success )
		{
			bRes = true;
		}
	}
	return ( bRes );
}
#endif

/* OJO: en POSIX devuelve la lista VACIA, y eso es una limitacion conocida, no
   un descuido. En Windows lo contesta NetServerEnum, que interroga al servicio
   de navegacion de SMB de la red local. Fuera de Windows no hay nada
   equivalente en la biblioteca estandar: enumerar las maquinas de la red pide
   o hablar SMB ( libsmbclient ) o mDNS ( Avahi ), dependencias externas que
   este stack no tiene. Se deja asi a proposito; quien necesite la lista, que
   pregunte maquina a maquina con SisRedServidorEsAccesible. */
list<wstring> * SisRedOrdenadoresAccesibles ()
{
	list<wstring> * 		p_lisOrdenadores = new list<wstring>;
# if ( defined ( WIN ) )
	DWORD 				dwRead;
	DWORD 				dwTotal;
	SERVER_INFO_100 *   p_srvInfo;
# endif

# if ( defined ( WIN ) )
	if ( NetServerEnum( NULL, 100, (LPBYTE *) &p_srvInfo, MAX_PREFERRED_LENGTH, 
					&dwRead, &dwTotal, SV_TYPE_ALL, NULL, NULL ) == NERR_Success )
	{
		for ( unsigned int i = 0; i < dwRead; i = i + 1 )
		{
			wstring wsNombre = wstring ( p_srvInfo[ i ].sv100_name );
			p_lisOrdenadores->push_back ( wsNombre );
		}
	}
	if ( ES_VALIDO ( p_srvInfo ) )
	{
		NetApiBufferFree( p_srvInfo );
	}
# endif
	return ( p_lisOrdenadores );
}

# if ( ! defined ( WIN ) )

/******************************************************************************/
/* Accesibilidad de una maquina                                               */
/*----------------------------------------------------------------------------*/
/* En Windows lo contestan NetServerGetInfo y NetWkstaGetInfo: le preguntan al */
/* servicio de la maquina y, si responde, es que esta ahi. En POSIX no hay una */
/* llamada equivalente, asi que se hace lo mismo por debajo: resolver el       */
/* nombre e intentar una conexion TCP al puerto de SMB, que es el servicio al  */
/* que pregunta Windows.                                                      */
/*                                                                            */
/* NO se usa ICMP ( el ping ), que seria lo primero que viene a la cabeza:     */
/* abrir un socket de ese tipo pide privilegios de root, y una libreria no     */
/* puede contar con eso.                                                      */
/******************************************************************************/

#include <sys/select.h>
#include <fcntl.h>

#define SIS_RED_PUERTO_SMB			"445"
#define SIS_RED_ESPERA_SEGUNDOS		2

/* Espera a que el socket termine de conectar, como mucho los segundos que se
   digan. Cierto si la conexion cuajo. */
static bool _SisRedEsperarConexion ( int iSocket, int iSegundos )
{
	bool			bRes = false;
	fd_set			fdsEscritura;
	struct timeval	tvEspera;

	FD_ZERO ( &fdsEscritura );
	FD_SET ( iSocket, &fdsEscritura );
	tvEspera.tv_sec = iSegundos;
	tvEspera.tv_usec = 0;

	if ( select ( iSocket + 1, NULL, &fdsEscritura, NULL, &tvEspera ) > 0 )
	{
		/* El socket se vuelve escribible tanto si conecto como si fallo: hay
		   que preguntarle a el por el resultado. */
		int			iError = 0;
		socklen_t	sklTam = ( socklen_t ) sizeof ( iError );

		if ( getsockopt ( iSocket, SOL_SOCKET, SO_ERROR, &iError, &sklTam ) == 0 )
		{
			bRes = ( iError == 0 );
		}
	}
	return ( bRes );
}

/* Cierto si la maquina responde en ese puerto. Se prueba con cada direccion
   que devuelva la resolucion del nombre, que pueden ser varias ( IPv4 e IPv6 ),
   y basta con que una conteste. */
static bool _SisRedResponde ( const wstring & sMaquina, const char * p_cPuerto )
{
	bool				bRes = false;
	string				sNombre = UnicodeAUtf8 ( sMaquina );
	struct addrinfo		addrinfPistas;
	struct addrinfo *	p_addrinfLista = NULL;

	MemLimpiar ( ( void * ) &addrinfPistas, ( int ) sizeof ( addrinfPistas ) );
	addrinfPistas.ai_family = AF_UNSPEC;
	addrinfPistas.ai_socktype = SOCK_STREAM;

	if ( getaddrinfo ( sNombre.c_str (), p_cPuerto, &addrinfPistas, &p_addrinfLista ) == 0 )
	{
		struct addrinfo * p_addrinfAct = p_addrinfLista;

		while ( ( p_addrinfAct != NULL ) && ( ! bRes ) )
		{
			int iSocket = socket ( p_addrinfAct->ai_family, p_addrinfAct->ai_socktype,
								   p_addrinfAct->ai_protocol );
			if ( iSocket >= 0 )
			{
				/* Sin bloquear: si la maquina esta apagada, un connect normal
				   se queda colgado hasta que el sistema se rinde, que pueden
				   ser minutos. */
				int iBanderas = fcntl ( iSocket, F_GETFL, 0 );
				fcntl ( iSocket, F_SETFL, iBanderas | O_NONBLOCK );

				if ( connect ( iSocket, p_addrinfAct->ai_addr, p_addrinfAct->ai_addrlen ) == 0 )
				{
					bRes = true;
				}
				else if ( errno == EINPROGRESS )
				{
					bRes = _SisRedEsperarConexion ( iSocket, SIS_RED_ESPERA_SEGUNDOS );
				}
				close ( iSocket );
			}
			p_addrinfAct = p_addrinfAct->ai_next;
		}
		freeaddrinfo ( p_addrinfLista );
	}
	return ( bRes );
}

# endif

bool SisRedServidorEsAccesible ( const wstring & sServidor )
{
	bool	bRes = false;
# if ( defined ( WIN ) )
	SERVER_INFO_100	*	p_srvinfDatos;
	DWORD				dwRes;
# endif	
	if ( ! sServidor.empty () )
	{
#	 if ( defined ( WIN ) )
		dwRes = NetServerGetInfo ( (LMSTR) sServidor.c_str(), (DWORD) 100, (LPBYTE *) &p_srvinfDatos );
		if ( dwRes == 0 ) // NERR_Success )
		{
			bRes = true;
		}
		if ( ES_VALIDO ( p_srvinfDatos ) )
		{
			NetApiBufferFree( p_srvinfDatos );
		}
#	 else
		bRes = _SisRedResponde ( sServidor, SIS_RED_PUERTO_SMB );
#	 endif
	}
	return ( bRes );
}
bool SisRedEstacionEsAccesible ( const wstring & sEstacion )
{
	bool	bRes = false;
# if ( defined ( WIN ) )
	WKSTA_INFO_100	* 	p_estinfDatos;
	DWORD				dwRes;
# endif	
	if ( ! sEstacion.empty () )
	{
#	 if ( defined ( WIN ) )
		dwRes = NetWkstaGetInfo ( (LMSTR) sEstacion.c_str(), (DWORD) 100, (LPBYTE *) &p_estinfDatos );
		if ( dwRes == 0 ) // NERR_Success )
		{
			bRes = true;
		}
		if ( ES_VALIDO ( p_estinfDatos ) )
		{
			NetApiBufferFree( p_estinfDatos );
		}
#	 else
		bRes = _SisRedResponde ( sEstacion, SIS_RED_PUERTO_SMB );
#	 endif
	}
	return ( bRes );
}


/*
#include <lm.h>

int wmain(int argc, wchar_t *argv[])
{
   DWORD dwLevel = 101;
   LPSERVER_INFO_101 pBuf = NULL;
   NET_API_STATUS nStatus;
   LPTSTR pszServerName = NULL;

   if (argc > 2)
   {
      fwprintf(stderr, L"Usage: %s [\\\\ServerName]\n", argv[0]);
      exit(1);
   }
   // The server is not the default local computer.
   //
   if (argc == 2)
      pszServerName = argv[1];
   //
   // Call the NetServerGetInfo function, specifying level 101.
   //
   nStatus = NetServerGetInfo(pszServerName,
                              dwLevel,
                              (LPBYTE *)&pBuf);
   //
   // If the call succeeds,
   //
   if (nStatus == NERR_Success)
   {
      //
      // Check for the type of server.
      //
      if ((pBuf->sv101_type & SV_TYPE_DOMAIN_CTRL) ||
         (pBuf->sv101_type & SV_TYPE_DOMAIN_BAKCTRL) ||
         (pBuf->sv101_type & SV_TYPE_SERVER_NT))
         printf("This is a server\n");
      else
         printf("This is a workstation\n");
   }
   //
   // Otherwise, print the system error.
   //
   else
      fprintf(stderr, "A system error has occurred: %d\n", nStatus);
   //
   // Free the allocated memory.
   //
   if (pBuf != NULL)
      NetApiBufferFree(pBuf);

   return 0;
}
*/
/*
int main( int argc, char *argv[] )
{
	DWORD rc;
	wchar_t server[MAXLEN], name[MAXLEN], from[MAXLEN], msg[MAXLEN];

	if ( argc != 5 && argc != 2 )
	{
		puts( "\nusage: nmbs \\\\server message-name from-name \"message\"" );
		puts( "       nmbs \\\\server\n" );
		puts( "First form: Sends the message to the <message-name> alias on <server>." );
		puts( "       Use whatever you like as <fromname>." );
		puts( "Second form: Lists <message-name>s on <server>. Note that not all of" );
		puts( "       them may work." );

		return 1;
	}

	mbstowcs( server, argv[1], MAXLEN );
	server[MAXLEN - 1] = L'\0';

	if ( argc == 2 )
	{
		enum_names( server );
	}
	else
	{
		mbstowcs( name, argv[2], MAXLEN );
		name[MAXLEN - 1] = L'\0';
		mbstowcs( from, argv[3], MAXLEN );
		from[MAXLEN - 1] = L'\0';
		mbstowcs( msg, argv[4], MAXLEN );
		msg[MAXLEN - 1] = L'\0';

		printf( "\nTrying ... " );
		rc = NetMessageBufferSend( server, name, from, (byte *) &msg[0], wcslen( msg ) * 2 );

		if ( rc != NERR_Success )
		{
			printf( "NMBS() returned %lu\n", rc );
			return 1;
		}

		puts( "Done." );
	}

	return 0;
}



void enum_names( const wchar_t *server )
{
	MSG_INFO_1 *buf, *cur;
	DWORD read, total, resumeh, rc, i;

	printf( "\nAvailable message-names on server %S:\n", server );
	resumeh = 0;
	do
	{
		buf = NULL;
		rc = NetMessageNameEnum( server, 1, (BYTE **) &buf,
			512, &read, &total, &resumeh );
		if ( rc != ERROR_MORE_DATA && rc != ERROR_SUCCESS )
			break;

		for ( i = 0, cur = buf; i < read; ++ i, ++ cur )
		{
			// Note: the capital S in the format string will expect Unicode
			// strings, as this is a program written/compiled for ANSI.
			printf( "%S\n", cur->msgi1_name );
		}

		if ( buf != NULL )
			NetApiBufferFree( buf );

	} while ( rc == ERROR_MORE_DATA );

	if ( rc != ERROR_SUCCESS )
		printf( "NMNE() returned %lu\n", rc );
}

*/

			}
		}
	}
}

