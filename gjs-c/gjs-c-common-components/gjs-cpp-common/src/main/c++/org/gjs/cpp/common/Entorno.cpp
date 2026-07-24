/***************************************************************************/
/*                         Entorno.cpp                                     */
/*-------------------------------------------------------------------------*/
/* Librer�a: Entorno                                                       */
/* Versi�n:  1.1.0                                                         */
/* Fecha:    25/10/2006                                                    */
/* Autor:    Gin�s Jim�nez S�nchez                                         */
/*-------------------------------------------------------------------------*/
/* Descripci�n:                                                            */
/* Fichero de c�digo fuente que contiene la implementaci�n de las rutinas  */
/* de car�cter general de inicializaci�n del entorno.                      */
/*-------------------------------------------------------------------------*/
/* NOTA DEL AUTOR:                                                         */
/* Este m�dulo est� extra�do de una librer�a m�s completa creada por el    */
/* mismo autor. Por favor, el autor ruega que se le informe de cualquier   */
/* error detectado, as� como cualquier a�adido o modificaci�n realizado.   */
/* Pueden reportar de los mismos enviando un correo electr�nico a la       */
/* direcci�n: gines_jimenez@safe-mail.net. Gracias.                        */
/***************************************************************************/


#include "CppCommonConfig.h"
#include "CppEntorno.h"




using namespace std;



namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {



static bool		g_bEntInicializado = false;
static string *	g_p_sEntDirDatos = NULL;
static string *	g_p_sEntDirSeguridad = NULL;
static string *	g_p_sEntDirLog = NULL;






#if ( defined ( WIN ) )
bool EntInicializar ( bool bConsola, const string & sNombre, int iVersion, int iSubversion, int iRevision, unsigned long ulFecha, const string & sDirTemporal, bool bVaciarDirTemporal )
#else
bool EntInicializar ( bool bConsola, const string & sNombre, int iVersion, int iSubversion, int iRevision, unsigned long ulFecha, const string & sDirTemporal, const string & sNomProceso, bool bVaciarDirTemporal )
#endif
{
	if ( !g_bEntInicializado )
	{
		InicializarBase();
		if ( ! sDirTemporal.empty() )
		{
			SisInicializarDirectorios ( sDirTemporal );

		}
		g_p_sEntDirDatos = SisDirectorioTemporal ();
		g_p_sEntDirSeguridad = SisDirectorioTemporal ();
		g_p_sEntDirLog = SisDirectorioTemporal ();
# if ( ! defined ( WIN ) )
		SisProcInicializar ( sNomProceso );
#  endif

		if ( AplicInicializar ( sNombre, iVersion, iSubversion, iRevision, ulFecha, bConsola ) )
		{
#		  if ( defined ( WIN )  )
			//if ( _WinSckInicializar () == 0 )
			//{
			//	// PENDIENTE: Tratar el error:
			//}
#		  elif ( ( defined ( UNIX ) ) || ( defined ( LINUX ) ) )
			//signal ( SIGPIPE, sigpipe_handle );
#		  endif

			if ( bVaciarDirTemporal )
			{
				SisVaciarDirectorio ( *SisDirectorioTemporal () );
			}
			g_bEntInicializado = true;
		}
	}
	return ( g_bEntInicializado );
}

void EntFinalizar ()
{
	if ( g_bEntInicializado )
	{
		delete g_p_sEntDirDatos;
		g_p_sEntDirDatos = NULL;
		delete g_p_sEntDirSeguridad;
		g_p_sEntDirSeguridad = NULL;
		delete g_p_sEntDirLog;
		g_p_sEntDirLog = NULL;
		AplicFinalizar ();

#	  if ( defined ( WIN )  )
		//_WinSckFinalizar ();
#	  endif

		SisFinalizar ();
		//ErrLimpiar ();
		g_bEntInicializado = false;

#	 if ( defined ( MODO_DEPURACION_2 ) || defined ( MODO_DEPURACION ) )
		char cVal;

#	  if ( defined ( MODO_DEPURACION_2 ) )
		// TODO: Esto todavia no se ha pasado a lo nuevo
		GesClsImprimirEstado ();
		MemImprimirInforme ( 1 );
#	  endif

		if ( iParar )
		{
			cout << endl << "Pulse <RETORNO> para continuar...";
			cVal = getchar ();
			cout << endl << endl;
		}
#	 endif
		log::LogLiberar ();
	}
}

bool EntEstaInicializado ()
{
	return ( g_bEntInicializado );
}

const string * EntDirectorioDatos ()
{
	return ( g_p_sEntDirDatos );
}

const string * EntDirectorioSeguridad ()
{
	return ( g_p_sEntDirSeguridad );
}

const string * EntDirectorioLog ()
{
	return ( g_p_sEntDirLog );
}

void EntEstablecerDirectorioDatos ( const string & sDir, bool bVaciar, bool bCrear )
{
	if ( bCrear )
	{
		if ( ! SisExisteDirectorio ( sDir ) )
		{
			SisCrearDirectorio ( sDir );
		}
	}
	if ( SisExisteDirectorio ( sDir ) )
	{
		delete g_p_sEntDirDatos;
		g_p_sEntDirDatos = new string ( sDir );
		if ( bVaciar )
		{
			SisVaciarDirectorio ( *g_p_sEntDirDatos );
		}
	}
}

void EntEstablecerDirectorioSeguridad ( const string & sDir, bool bVaciar, bool bCrear )
{
	if ( bCrear )
	{
		if ( !SisExisteDirectorio ( sDir ) )
		{
			SisCrearDirectorio ( sDir );
		}
	}
	if ( SisExisteDirectorio ( sDir ) )
	{
		delete g_p_sEntDirSeguridad;
		g_p_sEntDirSeguridad = new string ( sDir );
		if ( bVaciar )
		{
			SisVaciarDirectorio ( *g_p_sEntDirSeguridad );
		}
	}
}

void EntEstablecerDirectorioLog ( const string & sDir, bool bVaciar, bool bCrear )
{
	if ( bCrear )
	{
		if ( !SisExisteDirectorio ( sDir )  )
		{
			SisCrearDirectorio ( sDir );
		}
	}
	if ( SisExisteDirectorio ( sDir ) )
	{
		delete g_p_sEntDirLog;
		g_p_sEntDirLog = new string ( sDir );
		if ( bVaciar )
		{
			SisVaciarDirectorio ( *g_p_sEntDirLog );
		}
	}
}




 			}
		}
	}
}
