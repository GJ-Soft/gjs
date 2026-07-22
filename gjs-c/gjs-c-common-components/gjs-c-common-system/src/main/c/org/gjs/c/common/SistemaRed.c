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
		if ( GetComputerName ( (LPTSTR) SBufDireccion ( p_bufDatos ), (LPDWORD) &dwTam ) > 0 )
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
		if ( GetComputerNameEx ( ComputerNameDnsFullyQualified, (LPTSTR) SBufDireccion ( p_bufDatos ), (LPDWORD) &dwTam ) > 0 )
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

// PENDIENTE: La siguiente rutina no parce funcionar.
int SisRedEnviarMensaje ( const char * p_cDestino, const char * p_cOrigen, const char * p_cMensaje )
{
	int		iRes;
# if ( defined ( WIN ) )
	DWORD		dwTam;
	DWORD		dwRes;
	unichar *	p_cDestUnicode;
	unichar *	p_cOrigUnicode;
# endif	
	if ( ES_VALIDO ( p_cDestino ) && ES_VALIDO ( p_cOrigen ) && ES_VALIDO ( p_cMensaje ) )
	{
#	 if ( defined ( WIN ) )
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
#	 else
		// PENDIENTE:
		iRes = 0;
#	 endif
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

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
					(LPDWORD) &dwRead, (LPDWORD) &dwTotal, SV_TYPE_ALL, NULL, NULL ) == NERR_Success )
	{
		for ( int i = 0; i < dwRead; i = i + 1 )
		{
			char * p_cNombre = CadUnicodeAAsciiz ( p_srvInfo[ i ].sv100_name );
			SLisLitInsertarAlFinal ( p_lisOrdenadores, p_cNombre );
		}
	}
	if ( ES_VALIDO ( p_srvInfo ) )
	{
		NetApiBufferFree( p_srvInfo );
	}
# else
# endif
	return ( p_lisOrdenadores );
}

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
			if ( dwRes == 0 ) // NERR_Success )
			{
				iRes = 0;
			}
			else
			{
				iRes = 1;
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
		// PENDIENTE
		iRes = 0;
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
	// PENDIENTE:
	iRes = 0;
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
