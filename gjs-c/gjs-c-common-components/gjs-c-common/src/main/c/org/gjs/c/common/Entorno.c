/***************************************************************************/
/*                         Entorno.cpp                                     */
/*-------------------------------------------------------------------------*/
/* Librería: Entorno                                                       */
/* Versión:  1.1.0                                                         */
/* Fecha:    25/10/2006                                                    */
/* Autor:    Ginés Jiménez Sánchez                                         */
/*-------------------------------------------------------------------------*/
/* Descripción:                                                            */
/* Fichero de código fuente que contiene la implementación de las rutinas  */
/* de carácter general de inicialización del entorno.                      */
/*-------------------------------------------------------------------------*/
/* NOTA DEL AUTOR:                                                         */
/* Este módulo está extraído de una librería más completa creada por el    */
/* mismo autor. Por favor, el autor ruega que se le informe de cualquier   */
/* error detectado, así como cualquier añadido o modificación realizado.   */
/* Pueden reportar de los mismos enviando un correo electrónico a la       */
/* dirección: gines_jimenez@safe-mail.net. Gracias.                        */
/***************************************************************************/

#include "CommonConfig.h"
#include "CEntorno.h"





static int			g_iEntInicializado = 0;
static char *		g_p_cEntDirDatos = NULL;
static char *		g_p_cEntDirSeguridad = NULL;
static char *		g_p_cEntDirLog = NULL;

static int			g_iEntModoTest = 0;

# if ( defined ( WIN ) ) 
static DWORD      	g_pidProcesoInicializador;
# else
static pid_t 		g_pidProcesoInicializador;
# endif


int EntInicializar ( int iConsola, const char * p_cNombre, int iVersion, int iSubversion )
{
#if ( defined ( WIN ) )
	return ( EntInicializarExt ( iConsola, p_cNombre, iVersion, iSubversion, 0, 0, NULL, 0 ) );
#else
	return ( EntInicializarExt ( iConsola, p_cNombre, iVersion, iSubversion, 0, 0, NULL, NULL, 0 ) );
#endif
}

#if ( defined ( WIN ) )
int EntInicializarExt ( int iConsola, const char * p_cNombre, int iVersion, int iSubversion, int iRevision, unsigned long ulFecha, const char * p_cDirTemporal, int iVaciarDirTemporal )
#else
int EntInicializarExt ( int iConsola, const char * p_cNombre, int iVersion, int iSubversion, int iRevision, unsigned long ulFecha, const char * p_cDirTemporal, const char * p_cNomProceso, int iVaciarDirTemporal )
#endif
{
	int iRes;

	if ( g_iEntInicializado == 0 )
	{
		if ( ES_VALIDO ( p_cDirTemporal ) )
		{
			SisInicializarDirectorios ( p_cDirTemporal );

		}
		EntEstablecerDirectorioDatos ( SisDirectorioTemporal () );
		EntEstablecerDirectorioSeguridad ( SisDirectorioTemporal () );
		EntEstablecerDirectorioLog ( SisDirectorioTemporal () );
# if ( ! defined ( WIN ) )
		if ( ES_VALIDO ( p_cNomProceso ) )
		{
			SisProcInicializar ( p_cNomProceso );
		}
#  endif

		if ( AplicInicializar ( p_cNombre, iVersion, iSubversion, iRevision, ulFecha, iConsola ) == 1 )
		{
#		  if ( defined ( WIN )  )
			//if ( _WinSckInicializar () == 0 )
			//{
			//	Tratar el error:
			//}
#		  else
			//signal ( SIGPIPE, sigpipe_handle );
#		  endif

			if ( iVaciarDirTemporal == 1 )
			{
				if ( SisVaciarDirectorio ( SisDirectorioTemporal () ) == 1 )
				{
					iRes = 1;
					g_iEntInicializado = 1;
				}
				else
				{
					iRes = 0;
					g_iEntInicializado = 1;
				}
			}
			else
			{
				iRes = 1;
				g_iEntInicializado = 1;
			}
		}
		else
		{
			iRes = 0;
		}
		if ( g_iEntInicializado == 1 )
		{
# 		 if ( defined ( WIN ) ) 
			g_pidProcesoInicializador = GetCurrentProcessId ();
#		 else
			g_pidProcesoInicializador = getpid ();
#		 endif
		}
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

void EntFinalizar ()
{
	if ( g_iEntInicializado == 1 )
	{
# 	 if ( defined ( WIN ) ) 
		if ( g_pidProcesoInicializador == GetCurrentProcessId () )
#	 else
		if ( g_pidProcesoInicializador == getpid () )
#	 endif
		{
			MemLiberarCadena ( &g_p_cEntDirSeguridad );
			MemLiberarCadena ( &g_p_cEntDirLog );
			MemLiberarCadena ( &g_p_cEntDirDatos );
			AplicFinalizar ();


#		  if ( defined ( WIN )  )
			//_WinSckFinalizar ();
#		  endif

			SisFinalizar ();
			ErrLimpiar ();
			g_iEntInicializado = 0;
			g_pidProcesoInicializador = 0;

#		 if ( defined ( MODO_DEPURACION_2 ) || defined ( MODO_DEPURACION ) )
			char 	cVal;
			int		iParar = 0;

#		  if ( defined ( MODO_DEPURACION_2 ) )
			// TODO: Esto todavia no se ha pasado a lo nuevo
			GesClsImprimirEstado ();
			MemImprimirInforme ( 1 );
#		  endif

			if ( iParar == 1 )
			{
				printf ( "\nPulse <RETORNO> para continuar...");
				cVal = getchar ();
				printf ( "\n\n" );
			}
#	 endif
		}
	}
}

int EntEstaInicializado ()
{
	return ( g_iEntInicializado );
}

int EntEstaEnModoTest ()
{
	return ( g_iEntModoTest );
}

void EntActivarModoTest ()
{
	g_iEntModoTest = 1;
}

void EntDesactivarModoTest ()
{
	g_iEntModoTest = 0;
}

const char * EntDirectorioDatos ()
{
	return ( g_p_cEntDirDatos );
}

const char * EntDirectorioSeguridad ()
{
	return ( g_p_cEntDirSeguridad );
}

const char * EntDirectorioLog ()
{
	return ( g_p_cEntDirLog );
}

void EntEstablecerDirectorioDatos ( const char * p_cDir )
{
	EntEstablecerDirectorioDatosExt ( p_cDir, 0, 1 );
}

void EntEstablecerDirectorioSeguridad ( const char * p_cDir )
{
	EntEstablecerDirectorioSeguridadExt ( p_cDir, 0, 1 );
}

void EntEstablecerDirectorioLog ( const char * p_cDir )
{
	EntEstablecerDirectorioLogExt ( p_cDir, 0, 1 );
}

void EntEstablecerDirectorioDatosExt ( const char * p_cDir, int iVaciar, int iCrear )
{
	if ( iCrear == 1 )
	{
		if ( SisExisteDirectorio ( p_cDir ) == 0 )
		{
			SisCrearDirectorio ( p_cDir );
		}
	}
	if ( SisExisteDirectorio ( p_cDir ) == 1 )
	{
		MemLiberarCadena ( &g_p_cEntDirDatos );
		g_p_cEntDirDatos = CadDuplicar ( p_cDir );
		if ( iVaciar == 1 )
		{
			SisVaciarDirectorio ( g_p_cEntDirDatos );
		}
	}
}

void EntEstablecerDirectorioSeguridadExt ( const char * p_cDir, int iVaciar, int iCrear )
{
	if ( iCrear == 1 )
	{
		if ( SisExisteDirectorio ( p_cDir ) == 0 )
		{
			SisCrearDirectorio ( p_cDir );
		}
	}
	if ( SisExisteDirectorio ( p_cDir ) == 1 )
	{
		MemLiberarCadena ( &g_p_cEntDirSeguridad );
		g_p_cEntDirSeguridad = CadDuplicar ( p_cDir );
		if ( iVaciar == 1 )
		{
			SisVaciarDirectorio ( g_p_cEntDirSeguridad );
		}
	}
}

void EntEstablecerDirectorioLogExt ( const char * p_cDir, int iVaciar, int iCrear )
{
	if ( iCrear == 1 )
	{
		if ( SisExisteDirectorio ( p_cDir ) == 0 )
		{
			SisCrearDirectorio ( p_cDir );
		}
	}
	if ( SisExisteDirectorio ( p_cDir ) == 1 )
	{
		MemLiberarCadena ( &g_p_cEntDirLog );
		g_p_cEntDirLog = CadDuplicar ( p_cDir );
		if ( iVaciar == 1 )
		{
			SisVaciarDirectorio ( g_p_cEntDirLog );
		}
	}
}



