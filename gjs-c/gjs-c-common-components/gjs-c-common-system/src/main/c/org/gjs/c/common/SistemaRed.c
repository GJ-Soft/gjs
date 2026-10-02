/******************************************************************************/
/*                               SistemaRed.c                                 */
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



#include "SistemaRed.h"

#include "SistemaConfig.h"






char * SisRedNombreOrdenador ()
{
	char *		p_cRes;
	SBuffer	*	p_bufDatos;
# if ( defined ( WIN ) )
	DWORD			dwTam;
# else
	int				iTam;
# endif	

	p_bufDatos = SBufCrear ( SIS_SO_MAX_TAM_BUFFER );
	if ( ES_VALIDO ( p_bufDatos ) )
	{
#	 if ( defined ( WIN ) )
		dwTam = (DWORD) SBufTam ( p_bufDatos );
		if ( GetComputerName ( (LPTSTR) SBufDireccion ( p_bufDatos ), &dwTam ) > 0 )
#	 else
		iTam = SBufTam ( p_bufDatos );
		if ( gethostname ( (char *) SBufDireccion ( p_bufDatos ), iTam ) == 0 )
#	 endif
		{
			p_cRes = SBufDuplicarCadena ( p_bufDatos );
		}
		else
		{
			p_cRes = NULL;
		}
		SBufDestruir ( &p_bufDatos );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

char * SisRedNombreDNSOrdenador ()
{
	char *		p_cRes;
	SBuffer	*	p_bufDatos;
# if ( defined ( WIN ) )
	DWORD		dwTam;
# else 
	int 		iTam;
# endif	
	p_bufDatos = SBufCrear ( SIS_SO_MAX_TAM_BUFFER );
	if ( ES_VALIDO ( p_bufDatos ) )
	{
#	 if ( defined ( WIN ) )
		dwTam = (DWORD) SBufTam ( p_bufDatos );
		if ( GetComputerNameEx ( ComputerNameDnsFullyQualified, (LPTSTR) SBufDireccion ( p_bufDatos ), &dwTam ) > 0 )
#	 else
		iTam = (int) SBufTam ( p_bufDatos );
		if ( gethostname( (char *) SBufDireccion ( p_bufDatos ), iTam ) == 0 )
#	 endif
		{
			p_cRes = SBufDuplicarCadena ( p_bufDatos );
			
#	 if ( !defined ( WIN ) )
			struct addrinfo hints;
			struct addrinfo *res;
			MemLimpiar ( (void *) &hints, sizeof( hints ) );
			hints.ai_flags = AI_CANONNAME;

			if ( getaddrinfo( p_cRes, NULL, &hints, &res ) == 0 )
			{
				if ( ES_VALIDO ( res->ai_canonname ) )
				{
					MemLiberar ( (void **) p_cRes );
					p_cRes = CadDuplicar ( res->ai_canonname );
				}
				freeaddrinfo( res );
			}
#	 endif
		}
		else
		{
			p_cRes = NULL;
		}
		SBufDestruir ( &p_bufDatos );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

/* Solo en Windows. Se apoya en NetMessageBufferSend, el servicio de
   mensajeria de Windows, que no tiene equivalente en POSIX: no existe un
   mecanismo estandar para hacerle llegar un aviso emergente a otra maquina.
   Fuera de Windows la funcion no se declara, para que quien la llame se
   encuentre un error de compilacion en vez de un 0 que no significa nada.

   OJO, sigue en pie la nota de siempre: tampoco en Windows se la ha visto
   funcionar. El servicio de mensajeria ( Messenger ) esta desactivado por
   defecto desde Windows Vista, asi que NetMessageBufferSend contesta error
   salvo que alguien lo levante a mano. Eso es del sistema, no del codigo. */
#if ( defined ( WIN ) )
int SisRedEnviarMensaje ( const char * p_cDestino, const char * p_cOrigen, const char * p_cMensaje )
{
	int			iRes;
	DWORD		dwTam;
	DWORD		dwRes;
	unichar *	p_cDestUnicode;
	unichar *	p_cOrigUnicode;

	if ( ES_VALIDO ( p_cDestino ) && ES_VALIDO ( p_cOrigen ) && ES_VALIDO ( p_cMensaje ) )
	{
		p_cDestUnicode = CadAsciizAUnicode ( p_cDestino );
		p_cOrigUnicode = CadAsciizAUnicode ( p_cOrigen );
		if ( ES_VALIDO ( p_cDestUnicode ) && ES_VALIDO ( p_cOrigUnicode ) )
		{
			dwTam = (DWORD) CadLongitud ( p_cMensaje ) + 1;
			dwRes = NetMessageBufferSend ( (LPCWSTR) NULL, (LPCWSTR) p_cDestUnicode, (LPCWSTR) p_cOrigUnicode, (LPBYTE) p_cMensaje, dwTam );
			if ( dwRes == 0 ) // NERR_Success )
			{
				iRes = 1;
			}
			else
			{
				iRes = 0;
			}
		}
		else
		{
			iRes = 0;
		}
		MemLiberarUnicode ( (unichar **) &p_cDestUnicode );
		MemLiberarUnicode ( (unichar **) &p_cOrigUnicode );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}
#endif

/* OJO: en POSIX devuelve la lista VACIA, y eso es una limitacion conocida, no
   un descuido. En Windows lo contesta NetServerEnum, que interroga al servicio
   de navegacion de SMB de la red local. Fuera de Windows no hay nada
   equivalente en la biblioteca estandar: enumerar las maquinas de la red pide
   o hablar SMB ( libsmbclient ) o mDNS ( Avahi ), dependencias externas que
   este stack no tiene. Se deja asi a proposito; quien necesite la lista, que
   pregunte maquina a maquina con SisRedServidorEsAccesible. */
SListaLiterales * SisRedOrdenadoresAccesibles ()
{
	SListaLiterales * 	p_lisOrdenadores;
# if ( defined ( WIN ) )
	DWORD 				dwRead;
	DWORD 				dwTotal;
	SERVER_INFO_100 *   p_srvInfo;
# endif

	p_lisOrdenadores = SLisLitCrear ();	
	
# if ( defined ( WIN ) )
	if ( NetServerEnum( NULL, 100, (LPBYTE *) &p_srvInfo, MAX_PREFERRED_LENGTH, 
					&dwRead, &dwTotal, SV_TYPE_ALL, NULL, NULL ) == NERR_Success )
	{
		for ( unsigned int i = 0; i < dwRead; i = i + 1 )
		{
			char * p_cNombre = CadUnicodeAAsciiz ( p_srvInfo[ i ].sv100_name );
			SLisLitInsertarAlFinal ( p_lisOrdenadores, p_cNombre );
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
/* En Windows esto lo contesta NetServerGetInfo: le pregunta al servicio de    */
/* servidor de la maquina y, si responde, es que esta ahi. En POSIX no hay una */
/* llamada equivalente, asi que se hace lo mismo por debajo: resolver el       */
/* nombre e intentar una conexion TCP al puerto de SMB, que es el servicio al  */
/* que pregunta Windows.                                                      */
/*                                                                            */
/* NO se usa ICMP ( el ping ), que seria lo primero que viene a la cabeza:     */
/* abrir un socket de ese tipo pide privilegios de root, y una libreria no     */
/* puede contar con eso.                                                      */
/******************************************************************************/

#include <sys/select.h>

#define SIS_RED_PUERTO_SMB			"445"
#define SIS_RED_ESPERA_SEGUNDOS		2

/* Espera a que el socket termine de conectar, como mucho los segundos que se
   digan. Devuelve 1 si la conexion cuajo. */
static int _SisRedEsperarConexion ( int iSocket, int iSegundos )
{
	int				iRes;
	fd_set			fdsEscritura;
	struct timeval	tvEspera;
	int				iError;
	socklen_t		sklTam;

	FD_ZERO ( &fdsEscritura );
	FD_SET ( iSocket, &fdsEscritura );
	tvEspera.tv_sec = iSegundos;
	tvEspera.tv_usec = 0;

	if ( select ( iSocket + 1, NULL, &fdsEscritura, NULL, &tvEspera ) > 0 )
	{
		/* El socket se vuelve escribible tanto si conecto como si fallo: hay
		   que preguntarle a el por el resultado. */
		iError = 0;
		sklTam = ( socklen_t ) sizeof ( iError );
		if ( getsockopt ( iSocket, SOL_SOCKET, SO_ERROR, &iError, &sklTam ) == 0 )
		{
			if ( iError == 0 )
			{
				iRes = 1;
			}
			else
			{
				iRes = 0;
			}
		}
		else
		{
			iRes = 0;
		}
	}
	else
	{
		/* Ni conecto ni fallo: se agoto la espera. */
		iRes = 0;
	}
	return ( iRes );
}

/* Cierto si la maquina responde en ese puerto. Se prueba con cada direccion
   que devuelva la resolucion del nombre, que pueden ser varias ( IPv4 e IPv6 ),
   y basta con que una conteste. */
static int _SisRedResponde ( const char * p_cMaquina, const char * p_cPuerto )
{
	int					iRes;
	struct addrinfo		addrinfPistas;
	struct addrinfo *	p_addrinfLista;
	struct addrinfo *	p_addrinfAct;
	int					iSocket;
	int					iBanderas;

	iRes = 0;
	MemLimpiar ( ( void * ) &addrinfPistas, ( int ) sizeof ( addrinfPistas ) );
	addrinfPistas.ai_family = AF_UNSPEC;
	addrinfPistas.ai_socktype = SOCK_STREAM;

	p_addrinfLista = NULL;
	if ( getaddrinfo ( p_cMaquina, p_cPuerto, &addrinfPistas, &p_addrinfLista ) == 0 )
	{
		p_addrinfAct = p_addrinfLista;
		while ( ( p_addrinfAct != NULL ) && ( iRes == 0 ) )
		{
			iSocket = socket ( p_addrinfAct->ai_family, p_addrinfAct->ai_socktype,
							   p_addrinfAct->ai_protocol );
			if ( iSocket >= 0 )
			{
				/* Sin bloquear: si la maquina esta apagada, un connect normal
				   se queda colgado hasta que el sistema se rinde, que pueden
				   ser minutos. */
				iBanderas = fcntl ( iSocket, F_GETFL, 0 );
				fcntl ( iSocket, F_SETFL, iBanderas | O_NONBLOCK );

				if ( connect ( iSocket, p_addrinfAct->ai_addr, p_addrinfAct->ai_addrlen ) == 0 )
				{
					iRes = 1;
				}
				else if ( errno == EINPROGRESS )
				{
					iRes = _SisRedEsperarConexion ( iSocket, SIS_RED_ESPERA_SEGUNDOS );
				}
				close ( iSocket );
			}
			p_addrinfAct = p_addrinfAct->ai_next;
		}
		freeaddrinfo ( p_addrinfLista );
	}
	return ( iRes );
}

# endif

int SisRedServidorEsAccesible ( const char * p_cServidor )
{
	int					iRes;
# if ( defined ( WIN ) )
	unichar *			p_ucOrdUnicode;
	LPSERVER_INFO_100 	p_srvinfDatos;
	DWORD				dwRes;
# endif
	if ( ES_VALIDO ( p_cServidor ) )
	{
#	 if ( defined ( WIN ) )
		p_ucOrdUnicode = CadAsciizAUnicode ( p_cServidor );
		if ( ES_VALIDO ( p_ucOrdUnicode ) )
		{
			dwRes = NetServerGetInfo ( (LMSTR) p_ucOrdUnicode, (DWORD) 100, (LPBYTE *) &p_srvinfDatos );
			/* NERR_Success es 0 y significa que el servidor RESPONDIO, o sea
			   que si es accesible. Estaba al reves: devolvia 0 al acertar y 1
			   al fallar, justo lo contrario que su gemela
			   SisRedEstacionEsAccesible, que hace la misma llamada. */
			if ( dwRes == 0 ) // NERR_Success )
			{
				iRes = 1;
			}
			else
			{
				iRes = 0;
			}
			MemLiberarUnicode ( &p_ucOrdUnicode );
			if ( ES_VALIDO ( p_srvinfDatos ) )
			{
				NetApiBufferFree( p_srvinfDatos );
			}
		}
		else
		{
			iRes = 0;
		}
#	else
		iRes = _SisRedResponde ( p_cServidor, SIS_RED_PUERTO_SMB );
#	endif
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SisRedEstacionEsAccesible ( const char * p_cEstacion )
{
	int				iRes;
# if ( defined ( WIN ) )
	unichar *			p_ucOrdUnicode;
	WKSTA_INFO_100 *	p_estinfDatos;
	DWORD				dwRes;
# endif	
	if ( ES_VALIDO ( p_cEstacion ) )
	{
#	 if ( defined ( WIN ) )
		p_ucOrdUnicode = CadAsciizAUnicode ( p_cEstacion );
		if ( ES_VALIDO ( p_ucOrdUnicode ) )
		{
			dwRes = NetWkstaGetInfo ( (LMSTR) p_ucOrdUnicode, (DWORD) 100, (LPBYTE *) &p_estinfDatos );
			if ( dwRes == 0 ) // NERR_Success )
			{
				iRes = 1;
			}
			else
			{
				iRes = 0;
			}
			MemLiberarUnicode ( &p_ucOrdUnicode );
			if ( ES_VALIDO ( p_estinfDatos ) )
			{
				NetApiBufferFree( p_estinfDatos );
			}
		}
		else
		{
			iRes = 0;
		}
#	else
		iRes = _SisRedResponde ( p_cEstacion, SIS_RED_PUERTO_SMB );
#	endif
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


/*
#include <lm.h>

int wmain (int argc, wchar_t *argv[])
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
int main ( int argc, char *argv[] )
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



*/
